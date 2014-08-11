// WebConn.cpp: implementation of the CWebConn class.
//
//////////////////////////////////////////////////////////////////////

#include <cassert>
#include "../Lite/stdafx.h"
#include "../Lite/pcman.h"
#include "../Lite/MainFrm.h"
#include "WebConnIE.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WebConnIE::WebConnIE()
{
	web_browser.web_conn = this;
}

WebConnIE::~WebConnIE()
{
	this->web_browser.wb_ctrl.Stop();
	LockWindowUpdate(this->web_browser.m_hWnd);
	this->web_browser.wb_ctrl.DestroyWindow();
	LockWindowUpdate(this->web_browser.m_hWnd);
	this->web_browser.DestroyWindow();
}


CString WebConnIE::GetLocationName() const 
{
    return this->web_browser.GetLocationName();
}


CString WebConnIE::GetLocationURL() const 
{
    return this->web_browser.GetLocationURL();
}


void WebConnIE::SetFocus()
{
    this->web_browser.SetFocus();
}


void WebConnIE::GoHome()
{
    this->web_browser.wb_ctrl.GoHome();
}


void WebConnIE::PrintPage()
{
    this->web_browser.SetFocus();
    this->web_browser.wb_ctrl.ExecWB(OLECMDID_PRINT, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}


void WebConnIE::PrintSetting()
{
    this->web_browser.SetFocus();
    this->web_browser.wb_ctrl.ExecWB(OLECMDID_PAGESETUP, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}


void WebConnIE::ViewSrc()
{
    LPDISPATCH lpd = this->web_browser.wb_ctrl.get_Document();
    if (!lpd)
    {
        return;
    }

    IOleCommandTarget* pcmd = NULL;
    if (SUCCEEDED(lpd->QueryInterface(IID_IOleCommandTarget, (void**)&pcmd)))
    {
        pcmd->Exec(&CGID_IWebBrowser, HTMLID_VIEWSOURCE, 0, NULL, NULL);
        pcmd->Release();
    }

    lpd->Release();
}


void WebConnIE::SaveAs()
{
    this->web_browser.SetFocus();
    this->web_browser.wb_ctrl.ExecWB(OLECMDID_SAVEAS, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}


void WebConnIE::GoBack( int count )
{
    this->web_browser.wb_ctrl.GoBack(count);
}


void WebConnIE::GoForward( int count )
{
    this->web_browser.wb_ctrl.GoForward(count);
}


void WebConnIE::SetFontSize( unsigned int size )
{
    COleVariant v = long(size);
    this->web_browser.wb_ctrl.ExecWB(OLECMDID_ZOOM, 0, &v, NULL);
}


void WebConnIE::Navigate( const CString &url )
{
    COleVariant v;
    COleVariant tmpUrl = url;
    this->web_browser.wb_ctrl.Navigate2(&tmpUrl, &v, &v, &v, &v);
}


bool WebConnIE::CanPaste() const
{
    return (this->web_browser.wb_ctrl.QueryStatusWB(OLECMDID_PASTE) & OLECMDF_ENABLED) > 0;
}


bool WebConnIE::CanCopy() const
{
    return (this->web_browser.wb_ctrl.QueryStatusWB(OLECMDID_COPY) & OLECMDF_ENABLED) > 0;
}


void WebConnIE::PasteText( const CString &text )
{
    this->web_browser.SendString(text);
}


void WebConnIE::ShowFindDialog()
{
    this->web_browser.Find();
}


void WebConnIE::Refresh()
{
    this->web_browser.wb_ctrl.Refresh();
}


void WebConnIE::Stop()
{
    this->web_browser.wb_ctrl.Stop();
}


void WebConnIE::CopySelectionToClipboard()
{
    this->web_browser.SetFocus();
    this->web_browser.wb_ctrl.ExecWB(OLECMDID_COPY, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}


void WebConnIE::PasteFromClipboard()
{
     this->web_browser.wb_ctrl.SetFocus();
     this->web_browser.wb_ctrl.ExecWB(OLECMDID_PASTE, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}


void WebConnIE::SelectAll()
{
    this->web_browser.SetFocus();
    this->web_browser.wb_ctrl.ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}


int WebConnIE::LoadingStatusMaxValue() const 
{
    return this->web_browser.pgsmax;
}


int WebConnIE::LoadingStatusNowValue() const 
{
    return this->web_browser.pgs;
}


void WebConnIE::CreateScene( CMainFrame &mainFrame, CTermView &termView )
{
    this->web_browser.view = &termView;
    this->web_browser.parent = &mainFrame;
    this->web_browser.Create(NULL, NULL, WS_CHILD, CRect(0, 0, 0, 0), &mainFrame, 0);
    this->web_browser.wb_ctrl.put_RegisterAsBrowser(TRUE);
    this->web_browser.wb_ctrl.put_RegisterAsDropTarget(TRUE);
}


void WebConnIE::SetWindowPos( const CWnd *pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags )
{
    this->web_browser.SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
}


void WebConnIE::MoveWindow( const CRect &rect, BOOL repaint )
{
    this->web_browser.MoveWindow(rect, repaint);
}


void WebConnIE::EnableWindow( BOOL enable )
{
    this->web_browser.EnableWindow(enable);
}


void WebConnIE::HideWindow()
{
    this->web_browser.ShowWindow(SW_HIDE);
    this->web_browser.EnableWindow(FALSE);
}


void WebConnIE::ShowWindow()
{
    this->web_browser.ShowWindow(SW_SHOW);
    this->web_browser.EnableWindow(TRUE);
    this->web_browser.SetFocus();
}


bool WebConnIE::IsTravelLogEmpty() const 
{
    if (!this->web_browser.m_TravelLog)
    {
        return true;
    }

    return false;
}


std::vector<CString> WebConnIE::TravelLogGoBack() const 
{


    CComPtr<IEnumTravelLogEntry> pTLEnum;
    this->web_browser.m_TravelLog->EnumEntries(TLEF_RELATIVE_BACK, &pTLEnum.p);

    std::vector<CString> travelLog;
    if (pTLEnum.p)
    {
        CComPtr<ITravelLogEntry> pTLEntry;
        while (S_FALSE != pTLEnum->Next(1, &pTLEntry.p, NULL))
        {
            LPOLESTR title;
            pTLEntry.p->GetTitle(&title);
            travelLog.push_back(CString(title));
            CoTaskMemFree(title);
        }
    }

    return travelLog;
}



std::vector<CString> WebConnIE::TravelLogGoForward() const 
{


    CComPtr<IEnumTravelLogEntry> pTLEnum;
    this->web_browser.m_TravelLog->EnumEntries(TLEF_RELATIVE_FORE, &pTLEnum.p);

    std::vector<CString> travelLog;
    if (pTLEnum.p)
    {
        CComPtr<ITravelLogEntry> pTLEntry;
        while (S_FALSE != pTLEnum->Next(1, &pTLEntry.p, NULL))
        {
            LPOLESTR title;
            pTLEntry.p->GetTitle(&title);
            travelLog.push_back(CString(title));
            CoTaskMemFree(title);
        }
    }

    return travelLog;
}
