#include "thread_name_win.h"
#include <Windows.h>

typedef struct tagTHREADNAME_INFO
{
	DWORD	dwType;     // must be 0x1000
	LPCSTR	szName;		// pointer to name (in user addr space)
	DWORD	dwThreadID; // thread ID (-1=caller thread)
	DWORD	dwFlags;    // reserved for future use, must be zero
} THREADNAME_INFO;

void		thread_name_win::set_thread_name_win(const char* name)
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = name;
	info.dwThreadID = -1;
	info.dwFlags = 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}



thread_name_win::thread_name_win(const char* name)
{
	set_thread_name_win (name);
}
