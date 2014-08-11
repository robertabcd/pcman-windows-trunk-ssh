#ifndef _PCMAN_COMBO_CLIENTLOADHANDLER_H_
#define _PCMAN_COMBO_CLIENTLOADHANDLER_H_


#include "include\cef_load_handler.h"
class ClientLoadHandler :
    public CefLoadHandler
{
    IMPLEMENT_REFCOUNTING(ClientLoadHandler)
public:
    ClientLoadHandler(void);
    virtual ~ClientLoadHandler(void);
};


#endif
