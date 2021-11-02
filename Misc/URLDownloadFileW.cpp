#include <Windows.h>
#include <stdio.h>
#pragma comment(lib, "urlmon.lib")

#define WIDE_MAX_PATH (MAX_PATH * sizeof(WCHAR))

SIZE_T StringLengthW(LPCWSTR String)
{
    LPCWSTR String2;

    for (String2 = String; *String2; ++String2);

    return (String2 - String);
}

PWCHAR StringCopyW(PWCHAR String1, PWCHAR String2)
{
    PWCHAR p = String1;

    while ((*p++ = *String2++) != 0);

    return String1;
}

PWCHAR StringConcatW(PWCHAR String, PWCHAR String2)
{
    StringCopyW(&String[StringLengthW(String)], String2);

    return String;
}

class DownloadProgressRoutine : public IBindStatusCallback {
public:

    HRESULT __stdcall QueryInterface(const IID&, void**) { return E_NOINTERFACE; }
    ULONG STDMETHODCALLTYPE AddRef(void) { return 1; }
    ULONG STDMETHODCALLTYPE Release(void) { return 1; }
    HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib) { return E_NOTIMPL; }
    virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG* pnPriority) { return E_NOTIMPL; }
    virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) { return S_OK; }
    virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) { return E_NOTIMPL; }
    virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) { return E_NOTIMPL; }
    virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) { return E_NOTIMPL; }
    virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk) { return E_NOTIMPL; }

    virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
    {
        /*
        * if(ulProgress == ulProgressMax) 
        *   DownloadComplete(...);
        */

        printf("In progress: %ld of %ld\r\n", ulProgress, ulProgressMax);
        
        return S_OK;
    }
};

DWORD Win32FromHResult(HRESULT Result)
{
    if ((Result & 0xFFFF0000) == MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, 0))
        return HRESULT_CODE(Result);

    if (Result == S_OK)
        return ERROR_SUCCESS;

    return ERROR_CAN_NOT_COMPLETE;
}

INT main(VOID)
{
	HRESULT Result = S_OK;
    DownloadProgressRoutine DownloadCallback;

    WCHAR wTempPath[WIDE_MAX_PATH] = { 0 };

    if (GetTempPathW(WIDE_MAX_PATH, wTempPath) == 0)
        return GetLastError();

    if (StringConcatW(wTempPath, (PWCHAR)L"code.c") == NULL)
        return GetLastError();

    Result = URLDownloadToFileW(0,
        L"https://github.com/vxunderground/WinAPI-Tricks/blob/main/Kernel32/GetCurrentDirectoryAlt/GetCurrentDirectoryAltW.c",
        wTempPath,
        0,
        (IBindStatusCallback*)(&DownloadCallback));

    if (Result != S_OK)
        return Win32FromHResult(Result);

    return ERROR_SUCCESS;
	
}