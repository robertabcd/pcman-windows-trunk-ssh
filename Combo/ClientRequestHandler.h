#ifndef _PCMAN_COMBO_CLIENTREQUESTHANDLER_H_
#define _PCMAN_COMBO_CLIENTREQUESTHANDLER_H_


#include "include\cef_request_handler.h"

class ClientRequestHandler :
    public CefRequestHandler
{
    IMPLEMENT_REFCOUNTING(ClientRequestHandler)
public:
    ClientRequestHandler(void);
    virtual ~ClientRequestHandler(void);
};


#endif
