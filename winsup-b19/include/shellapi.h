#ifndef _SHELLAPI_H
#define _SHELLAPI_H

#ifdef __cplusplus
extern "C"
{
#endif
/* For shell32.def
   EXPORTS
   _CheckEscapesA@8
   _CheckEscapesW@8
   DONE _CommandLineToArgvW@8
   _DoEnvironmentSubstA@8
   _DoEnvironmentSubstW@8
   DONE _DragAcceptFiles@8
   DONE _DragFinish@4
   DONE _DragQueryFileA@16
   _DragQueryFileAorW@24
   DONE _DragQueryFileW@16
   DONE _DragQueryPoint@8
   DONE _DuplicateIcon@8
   DONE _ExtractAssociatedIconA@12
   _ExtractAssociatedIconExA@16
   _ExtractAssociatedIconExW@16
   DONE _ExtractAssociatedIconW@12
   DONE _ExtractIconA@12
   _ExtractIconResInfoA@20
   _ExtractIconResInfoW@20
   DONE _ExtractIconW@12
   _ExtractVersionResource16W@8
   _FindExeDlgProc@16
   DONE _FindExecutableA@12
   DONE _FindExecutableW@12
   _FreeIconList@8
   _InternalExtractIconListA@12
   _InternalExtractIconListW@12
   _RealShellExecuteA@40
   _RealShellExecuteExA@44
   _RealShellExecuteExW@44
   _RealShellExecuteW@40
   _RegenerateUserEnvironment@8
   _RegisterShellHook@8
   _SheChangeDirA@4
   _SheChangeDirExA@4
   _SheChangeDirExW@4
   _SheChangeDirW@4
   _SheConvertPathW@12
   _SheFullPathA@12
   _SheFullPathW@12
   _SheGetCurDrive@0
   _SheGetDirA@8
   _SheGetDirExW@12
   _SheGetDirW@8
   _SheGetPathOffsetW@4
   _SheRemoveQuotesA@4
   _SheRemoveQuotesW@4
   _SheSetCurDrive@4
   _SheShortenPathA@8
   _SheShortenPathW@8
   DONE _ShellAboutA@16
   DONE _ShellAboutW@16
   DONE _ShellExecuteA@24
   DONE _ShellExecuteW@24
   _ShellHookProc@12
   _StrChrA@8
   _StrChrIA@8
   _StrChrIW@8
   _StrChrW@8
   _StrCmpNA@12
   _StrCmpNIA@12
   _StrCmpNIW@12
   _StrCmpNW@12
   _StrCpyNA@12
   _StrCpyNW@12
   _StrNCmpA@12
   _StrNCmpIA@12
   _StrNCmpIW@12
   _StrNCmpW@12
   _StrNCpyA@12
   _StrNCpyW@12
   _StrRChrA@12
   _StrRChrIA@12
   _StrRChrIW@12
   _StrRChrW@12
   _StrRStrA@12
   _StrRStrIA@12
   _StrRStrIW@12
   _StrRStrW@12
   _StrStrA@8
   _StrStrIA@8
   _StrStrIW@8
   _StrStrW@8
   _WOWShellExecute@28

 */


#ifdef UNICODE
#define DragQueryFile DragQueryFileW
#define ExtractIcon ExtractIconW
#define ShellExecute ShellExecuteA
#define FindExecutable FindExecutableA
#define ShellAbout ShellAboutA
#define ExtractAssociatedIcon ExtractAssociatedIconA
#else
#define DragQueryFile DragQueryFileA
#define ExtractIcon ExtractIconA
#define ShellExecute ShellExecuteW
#define FindExecutable FindExecutableW
#define ShellAbout ShellAboutW
#define ExtractAssociatedIcon ExtractAssociatedIconW
#endif


/*WINAPI TCHAR **  CommandLineToArgvW(TCHAR*, int); */

#define SE_ERR_SHARE                    26
#define SE_ERR_ASSOCINCOMPLETE       	27
#define SE_ERR_DDETIMEOUT               28
#define SE_ERR_DDEFAIL                  29
#define SE_ERR_DDEBUSY                  30
#define SE_ERR_NOASSOC                  31


DECLARE_HANDLE (HDROP);


unsigned int WINAPI DragQueryFileW (HDROP, unsigned int, wchar_t *, unsigned int);
unsigned int WINAPI DragQueryFileA (HDROP, unsigned int, char *, unsigned int);
BOOL WINAPI DragQueryPoint (HDROP, POint *);
void WINAPI DragFinish (HDROP);
void WINAPI DragAcceptFiles (HWND, BOOL);
HICON WINAPI DuplicateIcon (HINSTANCE, HICON );
HICON WINAPI ExtractAssociatedIconA (HINSTANCE, char *, WORD *);
HICON WINAPI ExtractAssociatedIconW (HINSTANCE, wchar_t *, WORD *);
HICON WINAPI ExtractIconW (HINSTANCE, const wchar_t *, unsigned int);
HICON WINAPI ExtractIconA (HINSTANCE, const char *, unsigned int);
HINSTANCE WINAPI FindExecutableA (const char *, const char *, char *);
HINSTANCE WINAPI FindExecutableW (const wchar_t *, const wchar_t *, wchar_t *);
int WINAPI ShellAboutA (HWND, const char *, const char *, HICON);
int WINAPI ShellAboutW (HWND, const wchar_t *, const wchar_t *, HICON);
HINSTANCE WINAPI ShellExecuteA (HWND, const char *, const char *, char *, const char *, int);
HINSTANCE WINAPI ShellExecuteW (HWND, const wchar_t *, const wchar_t *, wchar_t *, const wchar_t *, int);

#ifdef __cplusplus
}
#endif

#endif


