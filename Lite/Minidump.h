#ifndef PCMAN_MINIDUMP_H
#define PCMAN_MINIDUMP_H

namespace Minidump
{
	void RegisterHandler ();

	LONG WINAPI UnhandledExceptionFilter(_EXCEPTION_POINTERS* lpTopLevelExceptionFilter);
}

#endif