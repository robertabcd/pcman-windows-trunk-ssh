#include "NullBrowserHost.h"

#include "NullBrowser.h"
#include "ClientHandlerBasic.h"

NullBrowserHost::NullBrowserHost(CefRefPtr<ClientHandlerBasic> client) : client_(client)
{
}


NullBrowserHost::~NullBrowserHost(void)
{
}

CefRefPtr<CefBrowser> NullBrowserHost::GetBrowser()
{
	return new NullBrowser(client_);
}

void NullBrowserHost::ParentWindowWillClose()
{
}

void NullBrowserHost::CloseBrowser( bool force_close )
{
}

void NullBrowserHost::SetFocus( bool enable )
{
}

CefWindowHandle NullBrowserHost::GetWindowHandle()
{
	return nullptr;
}

CefWindowHandle NullBrowserHost::GetOpenerWindowHandle()
{
	return nullptr;
}

CefRefPtr<CefClient> NullBrowserHost::GetClient()
{
	return client_.get();
}

CefString NullBrowserHost::GetDevToolsURL( bool http_scheme )
{
	return "";
}

double NullBrowserHost::GetZoomLevel()
{
	return 0.0;
}

void NullBrowserHost::SetZoomLevel( double zoomLevel )
{
}

void NullBrowserHost::RunFileDialog( FileDialogMode mode, const CefString& title, const CefString& default_file_name, const std::vector<CefString>& accept_types, CefRefPtr<CefRunFileDialogCallback> callback )
{
}

void NullBrowserHost::StartDownload( const CefString& url )
{
}

void NullBrowserHost::SetMouseCursorChangeDisabled( bool disabled )
{
}

bool NullBrowserHost::IsMouseCursorChangeDisabled()
{
	return false;
}

bool NullBrowserHost::IsWindowRenderingDisabled()
{
	return false;
}

void NullBrowserHost::WasResized()
{
}

void NullBrowserHost::WasHidden( bool hidden )
{
}

void NullBrowserHost::NotifyScreenInfoChanged()
{
}

void NullBrowserHost::Invalidate( const CefRect& dirtyRect, PaintElementType type )
{
}

void NullBrowserHost::SendKeyEvent( const CefKeyEvent& event )
{
}

void NullBrowserHost::SendMouseClickEvent( const CefMouseEvent& event, MouseButtonType type, bool mouseUp, int clickCount )
{
}

void NullBrowserHost::SendMouseMoveEvent( const CefMouseEvent& event, bool mouseLeave )
{
}

void NullBrowserHost::SendMouseWheelEvent( const CefMouseEvent& event, int deltaX, int deltaY )
{
}

void NullBrowserHost::SendFocusEvent( bool setFocus )
{
}

void NullBrowserHost::SendCaptureLostEvent()
{
}

CefTextInputContext NullBrowserHost::GetNSTextInputContext()
{
    return nullptr;
}

void NullBrowserHost::HandleKeyEventBeforeTextInputClient( CefEventHandle keyEvent )
{
}

void NullBrowserHost::HandleKeyEventAfterTextInputClient( CefEventHandle keyEvent )
{
}
