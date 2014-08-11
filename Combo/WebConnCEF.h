#ifndef _PCMAN_COMBO_WEBCONNCEF_H_
#define _PCMAN_COMBO_WEBCONNCEF_H_

#include "webconn.h"

#include <memory>
#include "include/cef_base.h"

class ClientHandlerBasic;
class WebConnCEF :
    public WebConn
{
public:
    WebConnCEF(CefRefPtr<ClientHandlerBasic> client);
    virtual ~WebConnCEF(void);

    virtual CString GetLocationName() const override;

    virtual CString GetLocationURL() const override;

    virtual void SetFocus() override;

    virtual void GoHome() override;

    virtual void PrintPage() override;

    virtual void PrintSetting() override;

    virtual void ViewSrc() override;

    virtual void SaveAs() override;

    virtual void GoBack( int count ) override;

    virtual void GoForward( int count ) override;

    virtual void SetFontSize( unsigned int size ) override;

    virtual void Navigate( const CString &url ) override;

    virtual bool CanPaste() const override;

    virtual bool CanCopy() const override;

    virtual void PasteText( const CString &text ) override;

    virtual void ShowFindDialog() override;

    virtual void Refresh() override;

    virtual void Stop() override;

    virtual void CopySelectionToClipboard() override;

    virtual void PasteFromClipboard() override;

    virtual void SelectAll() override;

    virtual int LoadingStatusMaxValue() const override;

    virtual int LoadingStatusNowValue() const override;

    virtual void CreateScene( CMainFrame &mainFrame, CTermView &termView ) override;

    virtual void SetWindowPos( const CWnd *pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags ) override;

    virtual void MoveWindow( const CRect &rect, BOOL repaint ) override;

    virtual void EnableWindow( BOOL enable ) override;

    virtual void HideWindow() override;

    virtual void ShowWindow() override;

    virtual bool IsTravelLogEmpty() const override;

    virtual std::vector<CString> TravelLogGoBack() const override;

    virtual std::vector<CString> TravelLogGoForward() const override;

private:
    struct WebConnCEFImpl;
    std::unique_ptr<WebConnCEFImpl> m_impl;
};


#endif
