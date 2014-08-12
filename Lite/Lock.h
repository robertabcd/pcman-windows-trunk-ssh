#ifndef _LOCK_H
#	define _LOCK_H

#ifdef _WINDOWS
#include <winsock2.h>
#include <concrt.h>
typedef concurrency::critical_section Mutex;
typedef concurrency::critical_section::scoped_lock ScopedLock;
#endif

#endif