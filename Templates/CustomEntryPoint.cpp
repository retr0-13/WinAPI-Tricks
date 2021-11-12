#include <Windows.h>

#pragma comment(linker, "/entry:__EntryPointEx")
#pragma comment(linker, "/subsystem:windows")

INT __EntryPointEx(VOID)
{
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;


	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = GetLastError();

	return dwError;
}