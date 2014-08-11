#include "WebConnCEF.h"

#include <cassert>
#include <sstream>

#include "../Lite/MainFrm.h"
#include "../Lite/TermView.h"

#include "ClientHandler.h"
#include "ClientContextMenuHandler.h"
#include "ClientDialogHandler.h"
#include "ClientDisplayHandler.h"
#include "ClientDownloadHandler.h"
#include "ClientFocusHandler.h"
#include "ClientGeolocationHandler.h"
#include "ClientJSDialogHandler.h"
#include "ClientKeyboardHandler.h"
#include "ClientLifeSpanHandler.h"
#include "ClientLoadHandler.h"
#include "ClientRenderHandler.h"
#include "ClientRequestHandler.h"

#include "WebScene.h"

struct WebConnCEF::WebConnCEFImpl
{
    WebConnCEFImpl(CefRefPtr<ClientHandlerBasic> client) : client(client), scene(client)
    {}
    CefRefPtr<ClientHandlerBasic> client;
    CefWindowInfo winInfo;
    WebScene scene;

    CefRefPtr<CefBrowser> GetBrowser()
    {
        return this->client->GetBrowser();
    }
};


WebConnCEF::WebConnCEF(CefRefPtr<ClientHandlerBasic> client) : m_impl(new WebConnCEF::WebConnCEFImpl(client))
{
    assert(m_impl);
}


WebConnCEF::~WebConnCEF(void)
{
    m_impl->GetBrowser()->GetHost()->CloseBrowser(false);
}


CString WebConnCEF::GetLocationName() const
{
    return m_impl->GetBrowser()->GetMainFrame()->GetName().c_str();
}


CString WebConnCEF::GetLocationURL() const
{
    return m_impl->GetBrowser()->GetMainFrame()->GetURL().c_str();
}


void WebConnCEF::SetFocus()
{
    m_impl->scene.SetFocus();
    m_impl->GetBrowser()->GetHost()->SetFocus(true);
}


void WebConnCEF::GoHome()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::PrintPage()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::PrintSetting()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::ViewSrc()
{
    m_impl->GetBrowser()->GetMainFrame()->ViewSource();
}


void WebConnCEF::SaveAs()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::GoBack( int count )
{
    for (int i = 0; i < count && m_impl->GetBrowser()->CanGoBack(); ++i)
    {
        m_impl->GetBrowser()->GoBack();
    }
}


void WebConnCEF::GoForward( int count )
{
    for (int i = 0; i < count && m_impl->GetBrowser()->CanGoForward(); ++i)
    {
        m_impl->GetBrowser()->GoForward();
    }
}


void WebConnCEF::SetFontSize( unsigned int size )
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::Navigate( const CString &url )
{
    std::string stdurl(url);

    CefBrowserSettings setting;
    CefBrowserHost::CreateBrowser(m_impl->winInfo, m_impl->client.get(), stdurl, setting);
}


bool WebConnCEF::CanPaste() const
{
    throw std::exception("The method or operation is not implemented.");
}


bool WebConnCEF::CanCopy() const
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::PasteText( const CString &text )
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::ShowFindDialog()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::Refresh()
{
    m_impl->GetBrowser()->Reload();
}


void WebConnCEF::Stop()
{
    m_impl->GetBrowser()->StopLoad();
}


void WebConnCEF::CopySelectionToClipboard()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::PasteFromClipboard()
{
    throw std::exception("The method or operation is not implemented.");
}


void WebConnCEF::SelectAll()
{
    m_impl->GetBrowser()->GetMainFrame()->SelectAll();
}


int WebConnCEF::LoadingStatusMaxValue() const
{
    //throw std::exception("The method or operation is not implemented.");
    return 0;
}


int WebConnCEF::LoadingStatusNowValue() const
{
    //throw std::exception("The method or operation is not implemented.");
    return 0;
}


void WebConnCEF::CreateScene( CMainFrame &mainFrame, CTermView &termView )
{
    //this->web_browser.Create(NULL, NULL, WS_CHILD, CRect(0, 0, 0, 0), &mainFrame, 0);

    termView.ShowScrollBar(SB_VERT, FALSE);
    RECT rect;
    termView.GetClientRect(&rect);
    termView.ShowScrollBar(SB_VERT, TRUE);
    rect.right += 2;
    rect.bottom += 2;

    m_impl->scene.Create(NULL, NULL, WS_CHILD, rect, &mainFrame, 0);

    m_impl->winInfo.SetAsChild(m_impl->scene.GetSafeHwnd(), rect);
}


void WebConnCEF::SetWindowPos( const CWnd *pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags )
{
    m_impl->scene.SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
}


void WebConnCEF::MoveWindow( const CRect &rect, BOOL repaint )
{
    m_impl->scene.MoveWindow(rect, repaint);
}


void WebConnCEF::EnableWindow( BOOL enable )
{
    m_impl->scene.EnableWindow(enable);
}


void WebConnCEF::HideWindow()
{
    m_impl->scene.ShowWindow(SW_HIDE);
}


void WebConnCEF::ShowWindow()
{
    m_impl->scene.ShowWindow(SW_SHOW);
}


bool WebConnCEF::IsTravelLogEmpty() const
{
    throw std::exception("The method or operation is not implemented.");
}


std::vector<CString> WebConnCEF::TravelLogGoBack() const
{
    throw std::exception("The method or operation is not implemented.");
}


std::vector<CString> WebConnCEF::TravelLogGoForward() const
{
    throw std::exception("The method or operation is not implemented.");
}

