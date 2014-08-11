#ifndef _PCMAN_COMBO_CLIENTDISPLAYHANDLER_H_
#define _PCMAN_COMBO_CLIENTDISPLAYHANDLER_H_


#include "include\cef_display_handler.h"

class ClientDisplayHandler :
    public CefDisplayHandler
{
    IMPLEMENT_REFCOUNTING(ClientDisplayHandler)
public:
    ClientDisplayHandler(void);
    virtual ~ClientDisplayHandler(void);
};


#endif
