#ifndef _PCMAN_COMBO_WEBMANAGERIE_H_
#define _PCMAN_COMBO_WEBMANAGERIE_H_


#include "webmanager.h"
class WebManagerIE :
    public WebManager
{
public:
    WebManagerIE(void);
    virtual ~WebManagerIE(void);

    virtual int OnAppStart(HINSTANCE) override;

    virtual int OnAppEnd() override;

    virtual bool OnMessageLoopIdle() override;

    virtual WebConn * Create() override;

};


#endif
