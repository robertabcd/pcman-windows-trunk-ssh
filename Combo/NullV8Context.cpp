#include "NullV8Context.h"

#include "NullBrowser.h"
#include "NullFrame.h"

#include "NullTaskRunner.h"
#include "NullV8Value.h"

#include "ClientHandlerBasic.h"

NullV8Context::NullV8Context(CefRefPtr<ClientHandlerBasic> client) : client_(client)
{
}


NullV8Context::~NullV8Context(void)
{
}

CefRefPtr<CefTaskRunner> NullV8Context::GetTaskRunner()
{
    return new NullTaskRunner;
}

bool NullV8Context::IsValid()
{
    return false;
}

CefRefPtr<CefBrowser> NullV8Context::GetBrowser()
{
    return new NullBrowser(client_);
}

CefRefPtr<CefFrame> NullV8Context::GetFrame()
{
    return new NullFrame(client_);
}

CefRefPtr<CefV8Value> NullV8Context::GetGlobal()
{
    return new NullV8Value;
}

bool NullV8Context::Enter()
{
    return false;
}

bool NullV8Context::Exit()
{
    return false;
}

bool NullV8Context::IsSame( CefRefPtr<CefV8Context> that )
{
    return false;
}

bool NullV8Context::Eval( const CefString& code, CefRefPtr<CefV8Value>& retval, CefRefPtr<CefV8Exception>& exception )
{
    return false;
}
