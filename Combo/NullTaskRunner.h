#ifndef _PCMAN_COMBO_NULLTASKRUNNER_H_
#define _PCMAN_COMBO_NULLTASKRUNNER_H_


#include "include\cef_task.h"

class NullTaskRunner : public CefTaskRunner
{
	IMPLEMENT_REFCOUNTING(NullTaskRunner)

public:
	NullTaskRunner(void);
	virtual ~NullTaskRunner(void);

	virtual bool IsSame( CefRefPtr<CefTaskRunner> that ) override;

	virtual bool BelongsToCurrentThread() override;

	virtual bool BelongsToThread( CefThreadId threadId ) override;

	virtual bool PostTask( CefRefPtr<CefTask> task ) override;

	virtual bool PostDelayedTask( CefRefPtr<CefTask> task, int64 delay_ms ) override;

};


#endif
