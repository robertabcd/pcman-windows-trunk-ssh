#include "StdAfx.h"
#include <cassert>
#include <winsock2.h>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "../ThirdParty/libssh2/include/libssh2.h"
#include "NetConn.h"
#include "PCMan.h"

Mutex g_knownhosts_mutex;

INetConn::INetConn()
{
}

INetConn::~INetConn()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTcpConn
/////////////////////////////////////////////////////////////////////////////

CTcpConn::CTcpConn(SOCKET socket)
	: m_socket(socket)
{
}

CTcpConn::~CTcpConn()
{
}

void CTcpConn::OnConnect(int nErrorCode)
{
}

int CTcpConn::Send(const void *data, int len)
{
	const char *p = (const char *)data;
	int remain = len;
	while (remain > 0) {
		int n = ::send(m_socket, p, remain, 0);
		if (n < 0) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				// TODO select()
				continue;
			}
			return ErrUnknown;
		}
		p += n;
		remain -= n;
	}
	return len;
}

int CTcpConn::Receive(void *buf, int len)
{
	int n = ::recv(m_socket, (char*)buf, len, 0);
	if (n == 0)
		Close();
	if (n >= 0)
		return n;
	if (WSAGetLastError() == WSAEWOULDBLOCK)
		return ErrWouldBlock;
	Close();
	return ErrUnknown;
}

int CTcpConn::Shutdown()
{
	return ::shutdown(m_socket, SD_SEND);
}

void CTcpConn::Close()
{
	::closesocket(m_socket);
}

/////////////////////////////////////////////////////////////////////////////
// CSshConn
/////////////////////////////////////////////////////////////////////////////

CSshConn::CSshConn(SOCKET socket, const std::string &hostname, unsigned short port)
	: m_socket(socket)
	, m_session(NULL)
	, m_channel(NULL)
	, m_state(StateConnecting)
	, m_host(hostname)
	, m_port(port)
	, m_delegate(NULL)
{
	static bool init = 0;
	if (!init) {
		libssh2_init(0);
		init = 1;
	}
	m_session = libssh2_session_init();
	libssh2_session_set_blocking(m_session, 0);
}

CSshConn::~CSshConn()
{
	Shutdown();
}

void CSshConn::OnConnect(int nErrorCode)
{
	if (nErrorCode != 0)
		return;
	assert(m_state == StateConnecting);
	m_state = StateHandshaking;
	Receive(NULL, 0);
}

int CSshConn::Send(const void *data, int len)
{
	if (!m_channel)
		return ErrUnknown;

	const char *buf = (const char *)data;
	int remain = len;
	while (remain > 0) {
		int n = libssh2_channel_write(m_channel, buf, remain);
		if (n == LIBSSH2_ERROR_EAGAIN) {
			// TODO select()
			continue;
		} else if (n < 0) {
			return ErrUnknown;
		}
		buf += n;
		remain -= n;
	}
	return len;
}

int CSshConn::Receive(void *buf, int len)
{
	fprintf(stderr, "Receive(): m_state: %d\n", m_state);

	// Check session
	if (m_session == NULL)
		return ErrUnknown;

	if (m_state == StateHandshaking) {
		if (libssh2_session_handshake(m_session, m_socket) < 0)
			return AgainOrError();
		m_state = StateAuthenticating;
	}

	if (m_state == StateAuthenticating) {
		if (!CheckHostkey()) {
			Shutdown();
			return -1;
		}

		char *methods = libssh2_userauth_list(m_session, m_ssh_username.c_str(), m_ssh_username.size());
		if (methods) {
			fprintf(stderr, "AuthMethods: %s\n", methods);
			return -1;
		}
		if (!libssh2_userauth_authenticated(m_session))
			return AgainOrError();
		m_state = StateOpeningSession;
	}

	if (m_state == StateOpeningSession) {
		assert(m_channel == NULL);
		if (!(m_channel = libssh2_channel_open_session(m_session)))
			return AgainOrError();
		m_state = StateRequestingPty;
	}

	// Check channel
	if (m_channel == NULL)
		return ErrUnknown;

	if (m_state == StateRequestingPty) {
		int ret = libssh2_channel_request_pty(m_channel, "vt100");
		if (ret < 0)
			return AgainOrError(ret);
		m_state = StateStartingProcess;
	}

	if (m_state == StateStartingProcess) {
		int ret = libssh2_channel_shell(m_channel);
		if (ret < 0)
			return AgainOrError(ret);
		GenMethods();
		m_state = StateEstablished;
	}

	if (m_state == StateEstablished) {
		if (!buf || len == 0)
			return 0;
		char *p = (char *)buf;
		int remain = len;
		int n;
		while (remain > 0) {
			n = libssh2_channel_read(m_channel, p, remain);
			if (n <= 0)
				break;
			p += n;
			remain -= n;
		}
		if (len - remain > 0)
			return len - remain;
		if (n == LIBSSH2_ERROR_EAGAIN)
			return ErrWouldBlock;
		Shutdown();
		return ErrUnknown;
	}

	throw std::runtime_error("not reached");
	return ErrUnknown;
}

int CSshConn::AgainOrError()
{
	return AgainOrError(libssh2_session_last_errno(m_session));
}

int CSshConn::AgainOrError(int code)
{
	if (code == LIBSSH2_ERROR_EAGAIN)
		return ErrWouldBlock;
	return ErrUnknown;
}

int CSshConn::Shutdown()
{
	if (m_channel) {
		libssh2_channel_free(m_channel);
		m_channel = NULL;
	}
	if (m_session) {
		libssh2_session_disconnect(m_session, "bye");
		libssh2_session_free(m_session);
		m_session = NULL;
	}
	return 0;
}

void CSshConn::SetSshUsername(const char *username)
{
	m_ssh_username = username;
}

void CSshConn::SetDelegate(CSshConnDelegate *delegate)
{
	m_delegate = delegate;
}

void CSshConn::GenMethods()
{
	m_methods =
		std::string("kex(")
		+ libssh2_session_methods(m_session, LIBSSH2_METHOD_KEX)
		+ ") cs("
		+ libssh2_session_methods(m_session, LIBSSH2_METHOD_CRYPT_CS)
		+ ","
		+ libssh2_session_methods(m_session, LIBSSH2_METHOD_MAC_CS)
		+ ") sc("
		+ libssh2_session_methods(m_session, LIBSSH2_METHOD_CRYPT_SC)
		+ ","
		+ libssh2_session_methods(m_session, LIBSSH2_METHOD_MAC_SC)
		+ ")";
}

std::string CSshConn::GetMethods() const
{
	return m_methods;
}

std::string Hexify(const char *bin, size_t len)
{
	std::string h;
	char buf[4];
	for (int i = 0; i < len; i++) {
		if (i > 0)
			h.push_back(':');
		_snprintf(buf, sizeof(buf), "%02x", (unsigned char)bin[i]);
		h += buf;
	}
	return h;
}

std::string Hexify(const char *cstr)
{
	return Hexify(cstr, strlen(cstr));
}

bool CSshConn::CheckHostkey()
{
	CSshConnDelegate::Err err = CSshConnDelegate::ErrKnownHostsFile;
	std::string hostport = std::string("[") + m_host + "]:" + std::to_string(m_port);
	std::string hosts_file = CApp::GetInstance()->GetConfigPath("known_hosts");
	LIBSSH2_KNOWNHOSTS *hosts = libssh2_knownhost_init(m_session);
	
	{
		ScopedLock _(g_knownhosts_mutex);
		libssh2_knownhost_readfile(
			hosts,
			hosts_file.c_str(),
			LIBSSH2_KNOWNHOST_FILE_OPENSSH);
	}

	size_t keylen;
	int keytype;
	const char *key = libssh2_session_hostkey(m_session, &keylen, &keytype);
	if (key == NULL)
		goto out;

	switch (libssh2_knownhost_check(
		hosts, hostport.c_str(), key, keylen,
		LIBSSH2_KNOWNHOST_TYPE_PLAIN | LIBSSH2_KNOWNHOST_KEYENC_RAW, NULL))
	{
	case LIBSSH2_KNOWNHOST_CHECK_NOTFOUND:
		break;

	case LIBSSH2_KNOWNHOST_CHECK_MATCH:
		err = CSshConnDelegate::ErrOK;
		goto out;

	case LIBSSH2_KNOWNHOST_CHECK_MISMATCH:
		err = CSshConnDelegate::ErrHostKeyMismatch;
		goto out;

	case LIBSSH2_KNOWNHOST_CHECK_FAILURE:
	default:
		goto out;
	}

	if (!m_delegate || !m_delegate->AskAcceptHostKey(
		hostport, Hexify(libssh2_hostkey_hash(m_session, LIBSSH2_HOSTKEY_HASH_SHA1))))
	{
		err = CSshConnDelegate::ErrHostKeyRejected;
		goto out;
	}
	err = CSshConnDelegate::ErrOK;

	{
		ScopedLock _(g_knownhosts_mutex);

		libssh2_knownhost_readfile(
			hosts,
			hosts_file.c_str(),
			LIBSSH2_KNOWNHOST_FILE_OPENSSH);

		int typemask = LIBSSH2_KNOWNHOST_TYPE_PLAIN | LIBSSH2_KNOWNHOST_KEYENC_RAW;
		if (keytype == LIBSSH2_HOSTKEY_TYPE_RSA)
			typemask |= LIBSSH2_KNOWNHOST_KEY_SSHRSA;
		else if (keytype == LIBSSH2_HOSTKEY_TYPE_DSS)
			typemask |= LIBSSH2_KNOWNHOST_KEY_SSHDSS;
		libssh2_knownhost_addc(hosts, hostport.c_str(), "", key, keylen, "", 0, typemask, NULL);
		libssh2_knownhost_writefile(hosts, hosts_file.c_str(), LIBSSH2_KNOWNHOST_FILE_OPENSSH);
	}

out:
	libssh2_knownhost_free(hosts);

	if (err == CSshConnDelegate::ErrOK)
		return true;
	if (m_delegate)
		m_delegate->SetSshErrorState(err);
	return false;
}