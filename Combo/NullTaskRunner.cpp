#include "NullTaskRunner.h"


NullTaskRunner::NullTaskRunner(void)
{
}


NullTaskRunner::~NullTaskRunner(void)
{
}

bool NullTaskRunner::IsSame( CefRefPtr<CefTaskRunner> that )
{
	return false;
}

bool NullTaskRunner::BelongsToCurrentThread()
{
	return false;
}

bool NullTaskRunner::BelongsToThread( CefThreadId threadId )
{
	return false;
}

bool NullTaskRunner::PostTask( CefRefPtr<CefTask> task )
{
	return false;
}

bool NullTaskRunner::PostDelayedTask( CefRefPtr<CefTask> task, int64 delay_ms )
{
	return false;
}
