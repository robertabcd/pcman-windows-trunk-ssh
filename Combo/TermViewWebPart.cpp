#include "../Lite/MainFrm.h"
#include "../Lite/TermView.h"

#include "WebConnIE.h"
#include "WebConnCEF.h"

#ifdef	_COMBO_
#include "WebManagerIE.h"
extern WebManager *g_webmanager;
#endif


#if defined	_COMBO_


BOOL CTermView::SetWindowPos(const CWnd *pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags)
{
	if (con && !telnet)
    {
        static_cast<WebConn *>(con)->SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
    }

	return CWnd::SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
}


void CTermView::MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint)
{
	CWnd::MoveWindow(x, y, nWidth, nHeight, bRepaint);
	if (con && !telnet)
    {
        static_cast<WebConn *>(con)->MoveWindow(CRect(x, y, x + nWidth, y + nHeight), bRepaint);
    }
}


WebConn *CTermView::ConnectWeb(CString address, BOOL act)
{
	//WebConn* newcon = new WebConnIE;
    WebConn* newcon = g_webmanager->Create();
    newcon->name = newcon->address = address;
    newcon->CreateScene(*this->parent, *this);
	parent->NewTab(newcon);

	if (!address.IsEmpty())
	{
        newcon->Navigate(address);
	}
	if (act)
    {
		parent->SwitchToConn(newcon);
    }
	else
    {
		newcon->EnableWindow(FALSE);
    }

	parent->FilterWebConn(newcon);
	return newcon;
}


#endif

void CTermView::OnDisConnect()
{
#if defined	_COMBO_
	if (!con)
    {
		return;
    }

	if (!telnet)
	{
		static_cast<WebConn *>(con)->Stop();
		return;
	}
#else
	if (!telnet)
    {
		return;
    }
#endif

	if (telnet->is_connecting || telnet->is_lookup_host)
	{
		parent->OnConnectClose();
		return;
	}

	if (!telnet->is_ansi_editor)
	{
		telnet->Shutdown();
		telnet->Close();
		telnet->ClearAllFlags();
		telnet->is_disconnected = true;
		telnet->site_settings.auto_reconnect = 0;

		int idx = 0;
		TCITEM tcitem;
		tcitem.mask = TCIF_IMAGE;
		tcitem.iImage = 1;
		idx = parent->ConnToIndex(telnet);
		parent->tab.SetItem(idx, &tcitem);
	}
}


void CTermView::OnReconnect()
{
	if (telnet)
    {
		ReConnect(telnet);
    }
#if defined	_COMBO_
	else if (con)
    {
		static_cast<WebConn *>(con)->Refresh();
    }
#endif
}