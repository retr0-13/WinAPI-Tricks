#include <Windows.h>

INT main(VOID)
{
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;


	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = GetLastError();

	return dwError;
}