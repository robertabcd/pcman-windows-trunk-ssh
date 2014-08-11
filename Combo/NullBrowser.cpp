#include "NullBrowser.h"

#include "NullBrowserHost.h"
#include "NullFrame.h"
#include "ClientHandlerBasic.h"

NullBrowser::NullBrowser(CefRefPtr<ClientHandlerBasic> client) : client_(client)
{
}


NullBrowser::~NullBrowser(void)
{
}

CefRefPtr<CefBrowserHost> NullBrowser::GetHost()
{
	return new NullBrowserHost(client_);
}

bool NullBrowser::CanGoBack()
{
	return false;
}

void NullBrowser::GoBack()
{
}

bool NullBrowser::CanGoForward()
{
	return false;
}

void NullBrowser::GoForward()
{
}

bool NullBrowser::IsLoading()
{
	return false;
}

void NullBrowser::Reload()
{
}

void NullBrowser::ReloadIgnoreCache()
{
}

void NullBrowser::StopLoad()
{
}

int NullBrowser::GetIdentifier()
{
	return -1;
}

bool NullBrowser::IsSame( CefRefPtr<CefBrowser> that )
{
	return that->GetIdentifier() == this->GetIdentifier();
}

bool NullBrowser::IsPopup()
{
	return false;
}

bool NullBrowser::HasDocument()
{
	return false;
}

CefRefPtr<CefFrame> NullBrowser::GetMainFrame()
{
	return this->CreateNullFrame();
}

CefRefPtr<CefFrame> NullBrowser::GetFocusedFrame()
{
	return this->CreateNullFrame();
}

CefRefPtr<CefFrame> NullBrowser::GetFrame( int64 identifier )
{
	return this->CreateNullFrame();
}

CefRefPtr<CefFrame> NullBrowser::GetFrame( const CefString& name )
{
	return this->CreateNullFrame();
}

size_t NullBrowser::GetFrameCount()
{
	return 0;
}

void NullBrowser::GetFrameIdentifiers( std::vector<int64>& identifiers )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void NullBrowser::GetFrameNames( std::vector<CefString>& names )
{
}

bool NullBrowser::SendProcessMessage( CefProcessId target_process, CefRefPtr<CefProcessMessage> message )
{
	return false;
}

CefRefPtr<CefFrame> NullBrowser::CreateNullFrame() const
{
    return new NullFrame(this->client_);
}
