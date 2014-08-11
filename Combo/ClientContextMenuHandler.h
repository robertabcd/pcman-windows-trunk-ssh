#ifndef _PCMAN_COMBO_CLIENTCONTEXTMENUHANDLER_H_
#define _PCMAN_COMBO_CLIENTCONTEXTMENUHANDLER_H_


#include "include\cef_context_menu_handler.h"

class ClientContextMenuHandler :
    public CefContextMenuHandler
{
    IMPLEMENT_REFCOUNTING(ClientContextMenuHandler)
public:
    ClientContextMenuHandler(void);
    virtual ~ClientContextMenuHandler(void);
};


#endif
