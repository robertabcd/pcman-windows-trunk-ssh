#include "NullFrame.h"

#include "NullBrowser.h"
#include "NullV8Context.h"

#include "ClientHandlerBasic.h"

NullFrame::NullFrame(CefRefPtr<ClientHandlerBasic> client) : client_(client)
{
}


NullFrame::~NullFrame(void)
{
}

bool NullFrame::IsValid()
{
	return false;
}

void NullFrame::Undo()
{
}

void NullFrame::Redo()
{
}

void NullFrame::Cut()
{
}

void NullFrame::Copy()
{
}

void NullFrame::Paste()
{
}

void NullFrame::Delete()
{
}

void NullFrame::SelectAll()
{
}

void NullFrame::ViewSource()
{
}

void NullFrame::GetSource( CefRefPtr<CefStringVisitor> visitor )
{
}

void NullFrame::GetText( CefRefPtr<CefStringVisitor> visitor )
{
}

void NullFrame::LoadRequest( CefRefPtr<CefRequest> request )
{
}

void NullFrame::LoadURL( const CefString& url )
{
}

void NullFrame::LoadString( const CefString& string_val, const CefString& url )
{
}

void NullFrame::ExecuteJavaScript( const CefString& code, const CefString& script_url, int start_line )
{
}

bool NullFrame::IsMain()
{
	return false;
}

bool NullFrame::IsFocused()
{
	return false;
}

CefString NullFrame::GetName()
{
	return "";
}

int64 NullFrame::GetIdentifier()
{
	return -1;
}

CefRefPtr<CefFrame> NullFrame::GetParent()
{
	return this;
}

CefString NullFrame::GetURL()
{
	return "";
}

CefRefPtr<CefBrowser> NullFrame::GetBrowser()
{
	return new NullBrowser(client_);
}

CefRefPtr<CefV8Context> NullFrame::GetV8Context()
{
	return new NullV8Context(client_);
}

void NullFrame::VisitDOM( CefRefPtr<CefDOMVisitor> visitor )
{
}
