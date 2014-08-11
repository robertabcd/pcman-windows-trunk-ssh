#ifndef _PCMAN_COMBO_CLIENTKEYBOARDHANDLER_H_
#define _PCMAN_COMBO_CLIENTKEYBOARDHANDLER_H_


#include "include\cef_keyboard_handler.h"

class ClientKeyboardHandler :
    public CefKeyboardHandler
{
    IMPLEMENT_REFCOUNTING(ClientKeyboardHandler)
public:
    ClientKeyboardHandler(void);
    virtual ~ClientKeyboardHandler(void);
};


#endif
