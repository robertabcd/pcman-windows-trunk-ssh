#include <winsock2.h>
#include "NetConn.h"

INetConn::INetConn()
{
}

INetConn::~INetConn()
{
}

CTcpConn::CTcpConn(SOCKET socket)
	: m_socket(socket)
{
}

CTcpConn::~CTcpConn()
{
}

int CTcpConn::Send(const void *data, int len)
{
	return ::send(m_socket, (char*)data, len, 0);
}

int CTcpConn::Receive(void *buf, int len)
{
	return ::recv(m_socket, (char*)buf, len, 0);
}

int CTcpConn::Shutdown()
{
	return ::shutdown(m_socket, SD_SEND);
}

void CTcpConn::OnConnect(int nErrorCode)
{
}