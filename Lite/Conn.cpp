// Conn.cpp: implementation of the CConn class.
//
//////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include "stdafx.h"
#include "pcman.h"
#include "Conn.h"
#include "TelnetConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTermView* CConn::view = NULL;

CConn::CConn()
{
	ClearAllFlags();
}

CConn::~CConn()
{

}

void CConn::ClearAllFlags()
{
	is_ansi_editor = false;
	is_cancelled = false;
	is_connected = false;
	is_connecting = false;
	is_disconnected = false;
	is_web = false;
	is_lookup_host = false;
	is_telnet = false;
}

// static
CConn *CConn::CreateFromAddress(CString address, LPCTSTR cfg_path)
{
	Type type = TypeTelnet;
	CString host = address;
	unsigned short default_port = 23, port;
	CString username;
	int i;

	if (0 == strncmp("telnet://", host, 9))
	{
		host = host.Mid(9);
	}
	else if (0 == strncmp("bbs://", host, 6))
	{
		host = host.Mid(6);
	}
	else if (0 == strncmp("ssh://", host, 6))
	{
		default_port = 22;
		type = TypeSsh;
		host = host.Mid(6);
		i = host.Find('@');
		if (i > -1) {
			username = host.Left(i);
			host = host.Mid(i + 1);
		}
	}

	i = host.ReverseFind(':');
	if (i == -1)
		port = default_port;
	else
	{
		port = (unsigned short)atoi(LPCTSTR(host.Mid(i + 1)));
		host = host.Left(i);
	}

	switch (type) {
	case TypeTelnet:
	case TypeSsh:
	{
		CTelnetConn *tc = new CTelnetConn;
		tc->address = address;
		tc->type = type;
		tc->host = host;
		tc->port = port;
		tc->ssh_username = username;

		//為新的socket載入設定值
		if (!tc->LoadConfig(cfg_path))	//如果載入設定發生錯誤
		{
			//這很有可能會在密碼輸入錯誤的時候發生!
			delete tc;
			return NULL;
		}
		return tc;
	}

	default:
		throw std::runtime_error("not reached");
	}
}