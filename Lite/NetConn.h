#pragma once
#ifndef NETCONN_H
#	define NETCONN_H

#include <string>
#include "Lock.h"
#include "../ThirdParty/libssh2/include/libssh2.h"

class INetConn
{
public:
	INetConn();
	virtual ~INetConn();
	
	virtual void OnConnect(int nErrorCode) = 0;
	virtual int Send(const void *data, int len) = 0;
	virtual int Receive(void *buf, int len) = 0;
	virtual int Shutdown() = 0;

	enum Err {
		ErrWouldBlock = -1,
		ErrUnknown = -2,
	};
};

class CTcpConn : public INetConn
{
public:
	CTcpConn(SOCKET socket);
	virtual ~CTcpConn();
	
	virtual void OnConnect(int nErrorCode);
	virtual int Send(const void *data, int len);
	virtual int Receive(void *buf, int len);
	virtual int Shutdown();
private:
	SOCKET m_socket;

	void Close();
};

class CSshConnDelegate;

class CSshConn : public INetConn
{
public:
	CSshConn(SOCKET socket, const std::string &hostname, unsigned short port);
	virtual ~CSshConn();
	
	virtual void OnConnect(int nErrorCode);
	virtual int Send(const void *data, int len);
	virtual int Receive(void *buf, int len);
	virtual int Shutdown();
	void SetSshUsername(const char *username);
	void SetDelegate(CSshConnDelegate *delegate);
	std::string GetMethods() const;
private:
	SOCKET m_socket;
	LIBSSH2_SESSION *m_session;
	LIBSSH2_CHANNEL *m_channel;

	enum ConnState
	{
		StateConnecting = 0,
		StateHandshaking,
		StateAuthenticating,
		StateOpeningSession,
		StateRequestingPty,
		StateStartingProcess,
		StateEstablished,
	};

	ConnState m_state;
	std::string m_host;
	unsigned short m_port;
	std::string m_ssh_username;
	CSshConnDelegate *m_delegate;

	std::string m_methods;
	
	int AgainOrError();
	int AgainOrError(int code);
	void GenMethods();
	bool CheckHostkey();
};

class CSshConnDelegate
{
public:
	virtual bool AskAcceptHostKey(const std::string &hostport, const std::string &keysha1) = 0;

	enum Err {
		ErrOK = 0,
		ErrKnownHostsFile,
		ErrHostKeyMismatch,
		ErrHostKeyRejected,
	};
	virtual void SetSshErrorState(Err err) = 0;
};

extern Mutex g_knownhosts_mutex;

#endif