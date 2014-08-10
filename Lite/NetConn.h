#pragma once
#ifndef NETCONN_H
#	define NETCONN_H

#include <winsock2.h>

class INetConn
{
public:
	INetConn();
	virtual ~INetConn();

	virtual int Send(const void *data, int len) = 0;
	virtual int Receive(void *buf, int len) = 0;
	virtual int Shutdown() = 0;
	virtual void OnConnect(int nErrorCode) = 0;
};

class CTcpConn : public INetConn
{
public:
	CTcpConn(SOCKET socket);
	virtual ~CTcpConn();
	
	virtual int Send(const void *data, int len);
	virtual int Receive(void *buf, int len);
	virtual int Shutdown();
	virtual void OnConnect(int nErrorCode);
private:
	SOCKET m_socket;
};

#endif