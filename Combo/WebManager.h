#ifndef _PCMAN_COMBO_WEBMANAGER_H_
#define _PCMAN_COMBO_WEBMANAGER_H_

#include <afx.h>

class WebConn;
class WebManager
{
public:
	WebManager(void);
	virtual ~WebManager(void);

	virtual int OnAppStart(HINSTANCE instance) = 0;

	virtual int OnAppEnd() = 0;

    virtual bool OnMessageLoopIdle() = 0;

	virtual WebConn *Create() = 0;
};


#endif
