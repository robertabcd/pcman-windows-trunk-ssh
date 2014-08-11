#ifndef _PCMAN_COMBO_CLIENTDIALOGHANDLER_H_
#define _PCMAN_COMBO_CLIENTDIALOGHANDLER_H_


#include "include\cef_dialog_handler.h"

class ClientDialogHandler :
    public CefDialogHandler
{
    IMPLEMENT_REFCOUNTING(ClientDialogHandler)
public:
    ClientDialogHandler(void);
    virtual ~ClientDialogHandler(void);
};


#endif
