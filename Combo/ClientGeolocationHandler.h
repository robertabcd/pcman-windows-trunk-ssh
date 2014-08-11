#ifndef _PCMAN_COMBO_CLIENTGEOLOCATIONHANDLER_H_
#define _PCMAN_COMBO_CLIENTGEOLOCATIONHANDLER_H_


#include "include\cef_geolocation_handler.h"

class ClientGeolocationHandler :
    public CefGeolocationHandler
{
    IMPLEMENT_REFCOUNTING(ClientGeolocationHandler)
public:
    ClientGeolocationHandler(void);
    virtual ~ClientGeolocationHandler(void);
};


#endif
