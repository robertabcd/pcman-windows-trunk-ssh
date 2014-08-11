#ifndef _PCMAN_COMBO_CLIENTHANDLERBASIC_H_
#define _PCMAN_COMBO_CLIENTHANDLERBASIC_H_


#include "include\cef_client.h"

class ClientHandlerBasic :
    public CefClient
{
    IMPLEMENT_REFCOUNTING(ClientHandlerBasic)
public:
    ClientHandlerBasic(void);
    virtual ~ClientHandlerBasic(void);

    virtual CefRefPtr<CefBrowser> GetBrowser() = 0;
    virtual int GetBrowserId() = 0;
};


#endif
