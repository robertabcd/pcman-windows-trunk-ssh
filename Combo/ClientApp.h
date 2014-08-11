#ifndef _PCMAN_COMBO_CLIENTAPP_H_
#define _PCMAN_COMBO_CLIENTAPP_H_


#include "include/cef_app.h"

class ClientApp :
    public CefApp
{
public:
    ClientApp(void);
    virtual ~ClientApp(void);

private:
    IMPLEMENT_REFCOUNTING(ClientApp)
};


#endif
