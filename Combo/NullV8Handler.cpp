#include "NullV8Handler.h"


NullV8Handler::NullV8Handler(void)
{
}


NullV8Handler::~NullV8Handler(void)
{
}

bool NullV8Handler::Execute( const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception )
{
    return false;
}
