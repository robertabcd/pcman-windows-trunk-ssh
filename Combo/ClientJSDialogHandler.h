#ifndef _PCMAN_COMBO_CLIENTJSDIALOGHANDLER_H_
#define _PCMAN_COMBO_CLIENTJSDIALOGHANDLER_H_


#include "include\cef_jsdialog_handler.h"

class ClientJSDialogHandler :
    public CefJSDialogHandler
{
    IMPLEMENT_REFCOUNTING(ClientJSDialogHandler)
public:
    ClientJSDialogHandler(void);
    virtual ~ClientJSDialogHandler(void);
};


#endif
