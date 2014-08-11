#ifndef _PCMAN_COMBO_NULLV8HANDLER_H_
#define _PCMAN_COMBO_NULLV8HANDLER_H_


#include "include\cef_v8.h"

class NullV8Handler : public CefV8Handler
{
    IMPLEMENT_REFCOUNTING(NullV8Handler)

public:
    NullV8Handler(void);
    virtual ~NullV8Handler(void);

    virtual bool Execute( const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception ) override;

};


#endif
