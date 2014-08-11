#ifndef _PCMAN_COMBO_WEBMANAGERCEF_H_
#define _PCMAN_COMBO_WEBMANAGERCEF_H_


#include "webmanager.h"
class WebManagerCEF :
    public WebManager
{
public:
    WebManagerCEF(void);
    virtual ~WebManagerCEF(void);

    virtual int OnAppStart(HINSTANCE instance) override;

    virtual int OnAppEnd() override;

    virtual bool OnMessageLoopIdle() override;

    virtual WebConn * Create() override;

private:
    int exitcode_;
};


#endif
