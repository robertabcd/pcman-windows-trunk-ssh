#ifndef _PCMAN_COMBO_WEBCONN_H_
#define _PCMAN_COMBO_WEBCONN_H_

#include <afx.h>
#include <vector>

#include "../Lite/Conn.h"

class CMainFrame;
class CTermView;
class WebConn : public CConn
{
public:
	WebConn(void);
	virtual ~WebConn(void);

	void ClearAllFlags()
	{
		CConn::ClearAllFlags();
		this->is_web = true;
	}

    virtual CString GetLocationName() const = 0;

    virtual CString GetLocationURL() const = 0;

    virtual void SetFocus() = 0;

    virtual void GoHome() = 0;

    virtual void PrintPage() = 0;

    virtual void PrintSetting() = 0;

    virtual void ViewSrc() = 0;

    virtual void SaveAs() = 0;

    virtual void GoBack( int count ) = 0;

    virtual void GoForward( int count ) = 0;

    virtual void SetFontSize( unsigned int size ) = 0;

    virtual void Navigate( const CString &url ) = 0;

    virtual bool CanPaste() const = 0;

    virtual bool CanCopy() const = 0;

    virtual void PasteText( const CString &text ) = 0;

    virtual void ShowFindDialog() = 0;

    virtual void Refresh() = 0;

    virtual void Stop() = 0;

    virtual void CopySelectionToClipboard() = 0;

    virtual void PasteFromClipboard() = 0;

    virtual void SelectAll() = 0;

    virtual int LoadingStatusMaxValue() const = 0;

    virtual int LoadingStatusNowValue() const = 0;

    virtual void CreateScene(CMainFrame &mainFrame, CTermView &termView) = 0;

    virtual void SetWindowPos(const CWnd *pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags) = 0;

    virtual void MoveWindow( const CRect &rect, BOOL repaint ) = 0;

    virtual void EnableWindow(BOOL enable) = 0;

    virtual void HideWindow() = 0;

    virtual void ShowWindow() = 0;

    virtual bool IsTravelLogEmpty() const = 0;

    virtual std::vector<CString> TravelLogGoBack() const = 0;

    virtual std::vector<CString> TravelLogGoForward() const = 0;

};


#endif
