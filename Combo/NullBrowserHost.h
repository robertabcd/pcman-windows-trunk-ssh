#ifndef _PCMAN_COMBO_NULLBROWSERHOST_H_
#define _PCMAN_COMBO_NULLBROWSERHOST_H_


#include "include\cef_browser.h"

class ClientHandlerBasic;
class NullBrowserHost : public CefBrowserHost
{
	IMPLEMENT_REFCOUNTING(NullBrowserHost)

public:
	NullBrowserHost(CefRefPtr<ClientHandlerBasic> client);
	virtual ~NullBrowserHost(void);

	virtual CefRefPtr<CefBrowser> GetBrowser() override;

	virtual void ParentWindowWillClose() override;

	virtual void CloseBrowser( bool force_close ) override;

	virtual void SetFocus( bool enable ) override;

	virtual CefWindowHandle GetWindowHandle() override;

	virtual CefWindowHandle GetOpenerWindowHandle() override;

	virtual CefRefPtr<CefClient> GetClient() override;

	virtual CefString GetDevToolsURL( bool http_scheme ) override;

	virtual double GetZoomLevel() override;

	virtual void SetZoomLevel( double zoomLevel ) override;

	virtual void RunFileDialog( FileDialogMode mode, const CefString& title, const CefString& default_file_name, const std::vector<CefString>& accept_types, CefRefPtr<CefRunFileDialogCallback> callback ) override;

	virtual void StartDownload( const CefString& url ) override;

	virtual void SetMouseCursorChangeDisabled( bool disabled ) override;

	virtual bool IsMouseCursorChangeDisabled() override;

	virtual bool IsWindowRenderingDisabled() override;

	virtual void WasResized() override;

	virtual void WasHidden( bool hidden ) override;

	virtual void NotifyScreenInfoChanged() override;

	virtual void Invalidate( const CefRect& dirtyRect, PaintElementType type ) override;

	virtual void SendKeyEvent( const CefKeyEvent& event ) override;

	virtual void SendMouseClickEvent( const CefMouseEvent& event, MouseButtonType type, bool mouseUp, int clickCount ) override;

	virtual void SendMouseMoveEvent( const CefMouseEvent& event, bool mouseLeave ) override;

	virtual void SendMouseWheelEvent( const CefMouseEvent& event, int deltaX, int deltaY ) override;

	virtual void SendFocusEvent( bool setFocus ) override;

	virtual void SendCaptureLostEvent() override;

    virtual CefTextInputContext GetNSTextInputContext();

    virtual void HandleKeyEventBeforeTextInputClient( CefEventHandle keyEvent );

    virtual void HandleKeyEventAfterTextInputClient( CefEventHandle keyEvent );

private:
	CefRefPtr<ClientHandlerBasic> client_;
};


#endif
