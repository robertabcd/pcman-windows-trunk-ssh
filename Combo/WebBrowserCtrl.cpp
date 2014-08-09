// CWebBrowserCtrl.cpp  : �H Microsoft Visual C++ �إߤ� ActiveX ����]�˨禡���O���w�q


#include "../Lite/stdafx.h"
#include "WebBrowserCtrl.h"
#include ".\webbrowserctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CWebBrowserCtrl

//IMPLEMENT_DYNCREATE(CWebBrowserCtrl, CWnd)

// CWebBrowserCtrl �ݩ�

// CWebBrowserCtrl �@�~

void CWebBrowserCtrl::GoBack(int c)
{
	LPDISPATCH lpd = get_Application();
	IWebBrowser2* pwb = NULL;
	if (SUCCEEDED(lpd->QueryInterface(IID_IWebBrowser2, (void**)&pwb)))
	{
		for (; c > 0; c--)
			pwb->GoBack();
		pwb->Release();
	}
	lpd->Release();
}

void CWebBrowserCtrl::GoForward(int c)
{
	LPDISPATCH lpd = get_Application();
	IWebBrowser2* pwb = NULL;
	if (SUCCEEDED(lpd->QueryInterface(IID_IWebBrowser2, (void**)&pwb)))
	{
		for (; c > 0; c--)
			pwb->GoForward();
		pwb->Release();
	}
	lpd->Release();
}
