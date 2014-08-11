#ifndef _PCMAN_COMBO_NULLV8CONTEXT_H_
#define _PCMAN_COMBO_NULLV8CONTEXT_H_


#include "include\cef_v8.h"

class ClientHandlerBasic;
class NullV8Context : public CefV8Context
{
    IMPLEMENT_REFCOUNTING(NullV8Context)

public:
    NullV8Context(CefRefPtr<ClientHandlerBasic> client);
    virtual ~NullV8Context(void);

    virtual CefRefPtr<CefTaskRunner> GetTaskRunner() override;

    virtual bool IsValid() override;

    virtual CefRefPtr<CefBrowser> GetBrowser() override;

    virtual CefRefPtr<CefFrame> GetFrame() override;

    virtual CefRefPtr<CefV8Value> GetGlobal() override;

    virtual bool Enter() override;

    virtual bool Exit() override;

    virtual bool IsSame( CefRefPtr<CefV8Context> that ) override;

    virtual bool Eval( const CefString& code, CefRefPtr<CefV8Value>& retval, CefRefPtr<CefV8Exception>& exception ) override;

private:
    CefRefPtr<ClientHandlerBasic> client_;
};


#endif
