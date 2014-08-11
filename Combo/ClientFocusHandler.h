#ifndef _PCMAN_COMBO_CLIENTFOCUSHANDLER_H_
#define _PCMAN_COMBO_CLIENTFOCUSHANDLER_H_


#include "include\cef_focus_handler.h"

class ClientFocusHandler :
    public CefFocusHandler
{
    IMPLEMENT_REFCOUNTING(ClientFocusHandler)
public:
    ClientFocusHandler(void);
    virtual ~ClientFocusHandler(void);
};


#endif
