#pragma once

#define GH_INJ_VERSIONW L"4.0"
#define GH_INJ_VERSIONA "4.0"

#define GH_INJ_MOD_NAME64W L"GH Injector - x64.dll"
#define GH_INJ_MOD_NAME86W L"GH Injector - x86.dll"

#define GH_INJ_MOD_NAME64A "GH Injector - x64.dll"
#define GH_INJ_MOD_NAME86A "GH Injector - x86.dll"

#ifdef _WIN64
#define GH_INJ_MOD_NAMEW GH_INJ_MOD_NAME64W
#define GH_INJ_MOD_NAMEA GH_INJ_MOD_NAME64A
#else
#define GH_INJ_MOD_NAMEW GH_INJ_MOD_NAME86W
#define GH_INJ_MOD_NAMEA GH_INJ_MOD_NAME86A
#endif

#ifdef UNICODE
#define GH_INJ_MOD_NAME GH_INJ_MOD_NAMEW
#define GH_INJ_VERSION GH_INJ_VERSIONW
#else
#define GH_INJ_MOD_NAME GH_INJ_MOD_NAMEA
#define GH_INJ_VERSION GH_INJ_VERSIONA
#endif

#include <Windows.h>

enum class INJECTION_MODE
{
    IM_LoadLibraryExW,
    IM_LdrLoadDll,
    IM_LdrpLoadDll,
    IM_LdrpLoadDllInternal,
    IM_ManualMap
};

enum class LAUNCH_METHOD
{
    LM_NtCreateThreadEx,
    LM_HijackThread,
    LM_SetWindowsHookEx,
    LM_QueueUserAPC
};

//ansi version of the info structure:
struct INJECTIONDATAA
{
    char			szDllPath[MAX_PATH * 2];
    DWORD			ProcessID;
    INJECTION_MODE	Mode;
    LAUNCH_METHOD	Method;
    DWORD			Flags;
    DWORD			Timeout;
    DWORD			hHandleValue;
    HINSTANCE		hDllOut;
    bool			GenerateErrorLog;
};

struct INJECTIONDATAW
{
    wchar_t			szDllPath[MAX_PATH * 2];
    wchar_t			szTargetProcessExeFileName[MAX_PATH];
    DWORD			ProcessID;
    INJECTION_MODE	Mode;
    LAUNCH_METHOD	Method;
    DWORD			Flags;
    DWORD			Timeout;
    DWORD			hHandleValue;
    HINSTANCE		hDllOut;
    bool			GenerateErrorLog;
};

#ifdef _UNICODE
#define INJECTIONDATA INJECTIONDATAW
#else
#define INJECTIONDATA INJECTIONDATAA
#endif

//amount of bytes to be scanned by ValidateInjectionFunctions and restored by RestoreInjectionFunctions
#define HOOK_SCAN_BYTE_COUNT 0x10

//ValidateInjectionFunctions fills an std::vector with this info, result can simply be passed to RestoreInjectionFunctions
struct HookInfo
{
    const char * ModuleName;
    const char * FunctionName;

    HINSTANCE		hModuleBase;
    void		*	pFunc;
    UINT			ChangeCount;
    BYTE			OriginalBytes[HOOK_SCAN_BYTE_COUNT];

    DWORD ErrorCode;
};

//Cloaking options:
#define INJ_ERASE_HEADER				0x0001
#define INJ_FAKE_HEADER					0x0002
#define INJ_UNLINK_FROM_PEB				0x0004
#define INJ_THREAD_CREATE_CLOAKED		0x0008
#define INJ_SCRAMBLE_DLL_NAME			0x0010
#define INJ_LOAD_DLL_COPY				0x0020
#define INJ_HIJACK_HANDLE				0x0040

//Notes:
///(1) ignored when manual mapping
///(2) launch method must be NtCreateThreadEx, ignored otherwise

//Manual mapping options:
#define INJ_MM_CLEAN_DATA_DIR			0x00010000
#define INJ_MM_RESOLVE_IMPORTS			0x00020000
#define INJ_MM_RESOLVE_DELAY_IMPORTS	0x00040000
#define INJ_MM_EXECUTE_TLS				0x00080000
#define INJ_MM_ENABLE_EXCEPTIONS		0x00100000
#define INJ_MM_SET_PAGE_PROTECTIONS		0x00200000
#define INJ_MM_INIT_SECURITY_COOKIE		0x00400000
#define INJ_MM_RUN_DLL_MAIN				0x00800000


#define MM_DEFAULT (INJ_MM_RESOLVE_IMPORTS | INJ_MM_RESOLVE_DELAY_IMPORTS | INJ_MM_INIT_SECURITY_COOKIE | INJ_MM_EXECUTE_TLS | INJ_MM_ENABLE_EXCEPTIONS | INJ_MM_RUN_DLL_MAIN | INJ_MM_SET_PAGE_PROTECTIONS)

using f_InjectA = DWORD(__stdcall*)(INJECTIONDATAA * pData);
using f_InjectW = DWORD(__stdcall*)(INJECTIONDATAW * pData);

using f_ValidateInjectionFunctions = bool(__stdcall*)(DWORD dwTargetProcessId, DWORD & ErrorCode, DWORD & LastWin32Error, HookInfo * HookDataOut, UINT Count, UINT * CountOut);
using f_RestoreInjectionFunctions = bool(__stdcall*)(DWORD dwTargetProcessId, DWORD & ErrorCode, DWORD & LastWin32Error, HookInfo * HookDataIn, UINT Count, UINT * CountOut);

using f_GetVersionA = HRESULT(__stdcall *)(char		* out, size_t cb_size);
using f_GetVersionW = HRESULT(__stdcall *)(wchar_t	* out, size_t cb_size);

using f_GetSymbolState = DWORD(__stdcall *)();

using f_GetDownloadProgress = float(__stdcall *)(bool bWoW64);

using f_raw_print_callback = void(__stdcall *)(const char * szText);
using f_SetRawPrintCallback = DWORD(__stdcall *)(f_raw_print_callback callback);
