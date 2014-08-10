#pragma once
#ifndef NETCONN_H
#	define NETCONN_H

#include <winsock2.h>
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

class CSshConn : public INetConn
{
public:
	CSshConn(SOCKET socket);
	virtual ~CSshConn();
	
	virtual void OnConnect(int nErrorCode);
	virtual int Send(const void *data, int len);
	virtual int Receive(void *buf, int len);
	virtual int Shutdown();
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
	
	int AgainOrError();
	int AgainOrError(int code);
};

#endif