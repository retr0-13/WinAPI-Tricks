#include <Windows.h>

#pragma comment(linker, "/subsystem:windows")

int APIENTRY wWinMain(_In_ HINSTANCE hInst, 
		      _In_opt_ HINSTANCE hInstPrev, 
		      _In_ PWSTR cmdline, 
		      _In_ INT cmdshow)
{
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;


	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = GetLastError();

	return dwError;
}
