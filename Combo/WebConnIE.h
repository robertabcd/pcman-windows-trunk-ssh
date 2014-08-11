// WebConn.h: interface for the CWebConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CWebConn_H__6CA20F68_1FDA_11D6_8461_9C9E15C10000__INCLUDED_)
#define AFX_CWebConn_H__6CA20F68_1FDA_11D6_8461_9C9E15C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WebConn.h"
#include "webbrowser.h"
#include <afxtempl.h>

class WebConnIE : public WebConn
{
public:
	WebConnIE();
	virtual ~WebConnIE();

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

    virtual void EnableWindow(BOOL enable) override;

    virtual void HideWindow() override;

    virtual void ShowWindow() override;

    virtual bool IsTravelLogEmpty() const override;

    virtual std::vector<CString> TravelLogGoBack() const override;

    virtual std::vector<CString> TravelLogGoForward() const override;

private:
    friend CWebBrowser;
    mutable CWebBrowser web_browser;
};

#endif // !defined(AFX_CWebConn_H__6CA20F68_1FDA_11D6_8461_9C9E15C10000__INCLUDED_)
