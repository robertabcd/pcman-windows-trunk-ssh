#include "stdAfx.h"
#include "AppConfig.h"
#include <SdkDdkVer.h>
#include <DbgHelp.h>
#include <Shlobj.h>
#include <TCHAR.H>
#include <stdio.h>
#include "..\Resource\resource.h"
#include "minidump.h"

#ifdef	_COMBO_
#include "..\Combo\Version.h"
#else
#include "..\Lite\Version.h"
#endif



/* Some of these code are borrowed from mpc-hc.  */

namespace Minidump
{

static LPTOP_LEVEL_EXCEPTION_FILTER old_handler = NULL;
void RegisterHandler ()
{
	old_handler = SetUnhandledExceptionFilter(Minidump::UnhandledExceptionFilter);
}

typedef BOOL (WINAPI* MiniDumpWriteDump_ft) (
	HANDLE hProcess,
	DWORD ProcessId,
	HANDLE hFile,
	MINIDUMP_TYPE DumpType,
	PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
	PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	PMINIDUMP_CALLBACK_INFORMATION CallbackParam
	);

void ExploreToFile(LPCTSTR path)
{
    ITEMIDLIST *pidl = ILCreateFromPath(path);
    if(pidl) {
        SHOpenFolderAndSelectItems(pidl,0,0,0);
        ILFree(pidl);
    }
}

LONG WINAPI UnhandledExceptionFilter(_EXCEPTION_POINTERS* lpTopLevelExceptionFilter)
{
	HMODULE hDll = NULL;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	TCHAR minidumpPath[MAX_PATH];
	int r;
	int len;
	SYSTEMTIME st;
	_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
	TCHAR message[1024];
	int retval = EXCEPTION_CONTINUE_SEARCH;
	MINIDUMP_TYPE config2type[4] = {
		MiniDumpNormal, /* none actually.  */
		MiniDumpNormal,
		MiniDumpWithDataSegs,
		MiniDumpWithFullMemory,
	};
	MINIDUMP_TYPE dumptype;

	if (AppConfig.minidump_type == 0)
		goto out;
	dumptype = config2type[AppConfig.minidump_type];

	hDll = ::LoadLibrary(_T("dbghelp.dll"));

	if (hDll == NULL)
		goto out;

	MiniDumpWriteDump_ft pMiniDumpWriteDump = (MiniDumpWriteDump_ft)::GetProcAddress(hDll, "MiniDumpWriteDump");
	if (pMiniDumpWriteDump == NULL)
		goto out;

	if (FAILED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, minidumpPath)))
		goto out;

	GetSystemTime(&st);

#if defined (_COMBO_)
	_tcscat (minidumpPath, _T("\\PCMan Combo"));
#else
	_tcscat (minidumpPath, _T("\\PCMan"));
#endif
	CreateDirectory (minidumpPath, NULL);

	len = _tcslen (minidumpPath);
	/* pcmain-M.m.l-timestamp.dmp */
	_sntprintf (minidumpPath + len, sizeof (minidumpPath) - len,
		_T("\\%s-%d.%d.%d-%04d%02d%02d%02d%02d%02d.dmp"),	
#if defined (_COMBO_)
		_T("pcmancb"),
#else
		_T("pcman"),
#endif
		Version_Major,
		Version_Minor,
		Version_PatchLevel,
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);

	hFile = ::CreateFile(minidumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		goto out;

	ExInfo.ThreadId = ::GetCurrentThreadId();
	ExInfo.ExceptionPointers = lpTopLevelExceptionFilter;
	ExInfo.ClientPointers = NULL;

	// write the dump
	r = pMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, dumptype, &ExInfo, NULL, NULL);
	if (!r)
		goto out;
	CloseHandle (hFile);
	hFile = INVALID_HANDLE_VALUE;

	::LoadString(GetModuleHandle(NULL), IDS_MINIDUMP, message, sizeof (message));
	_tcscat(message, _T("\n"));
	_tcscat(message, minidumpPath);
	r = ::MessageBox (NULL, message, _T("PCMan - MiniDump"), MB_YESNO | MB_TASKMODAL);

	if (r == IDYES)
	{
		//ShellExecute(NULL, _T("open"), BUGS_URL, NULL, NULL, SW_SHOWDEFAULT);
		ExploreToFile(minidumpPath);
	}
out:
	if (hDll)
		FreeLibrary(hDll);
	if (hFile != INVALID_HANDLE_VALUE)
		CloseHandle (hFile);

	SetUnhandledExceptionFilter(old_handler);
	// ::ExitProcess(lpTopLevelExceptionFilter->ExceptionRecord->ExceptionCode);

	return retval;
}


}