# 1 "net.cc"
 









 



# 1 "winsup.h" 1
 









# 1 "include/windows.h" 1
 




























 





# 1 "include/limits.h" 1



 



 



 




 





 



 












 





 



 








 



 













 




 








 




 



 



 


 
 


 
 
 

















# 36 "include/windows.h" 2

# 1 "E:\\gcc-ms\\BIN\\include/stdarg.h" 1 3
 


































# 1 "E:\\gcc-ms\\BIN\\include/va-alpha.h" 1 3
 

 




 





 





typedef struct {
  char *__base;			 
  int __offset;			 
} __gnuc_va_list;




 







# 47 "E:\\gcc-ms\\BIN\\include/va-alpha.h" 3


 

 


















 

enum {
  __no_type_class = -1,
  __void_type_class,
  __integer_type_class,
  __char_type_class,
  __enumeral_type_class,
  __boolean_type_class,
  __pointer_type_class,
  __reference_type_class,
  __offset_type_class,
  __real_type_class,
  __complex_type_class,
  __function_type_class,
  __method_type_class,
  __record_type_class,
  __union_type_class,
  __array_type_class,
  __string_type_class,
  __set_type_class,
  __file_type_class,
  __lang_type_class
};



 


 




 





















 




# 36 "E:\\gcc-ms\\BIN\\include/stdarg.h" 2 3

# 123 "E:\\gcc-ms\\BIN\\include/stdarg.h" 3










 
 













# 162 "E:\\gcc-ms\\BIN\\include/stdarg.h" 3


 




 

 




























# 37 "include/windows.h" 2



 
# 1 "include/Windows32/Base.h" 1
 



























 





extern "C" {















 









typedef unsigned short ATOM;
 
typedef int WINBOOL;
typedef unsigned char BOOLEAN;
typedef unsigned char BYTE;
typedef unsigned long CALTYPE;
typedef unsigned long CALID;
typedef char CCHAR;
typedef unsigned long COLORREF;


 


typedef char CHAR;
typedef short SHORT;
typedef long LONG;


 



typedef unsigned int DWORD;  
typedef double DWORDLONG, *PDWORDLONG;
 






typedef float FLOAT;
 
typedef void *HANDLE;
typedef HANDLE HACCEL;
typedef HANDLE HBITMAP;
typedef HANDLE HBRUSH;
typedef HANDLE HCOLORSPACE;
typedef HANDLE HCONV;
typedef HANDLE HCONVLIST;
typedef HANDLE HCURSOR;
typedef HANDLE HDBC;
typedef HANDLE HDC;
typedef HANDLE HDDEDATA;
typedef HANDLE HDESK;
typedef HANDLE HDROP;
typedef HANDLE HDWP;
typedef HANDLE HENHMETAFILE;
typedef HANDLE HENV;
typedef int HFILE;
typedef HANDLE HFONT;
typedef HANDLE HGDIOBJ;
typedef HANDLE HGLOBAL;
typedef HANDLE HGLRC;
typedef HANDLE HHOOK;
typedef HANDLE HICON;
typedef HANDLE HIMAGELIST;
typedef HANDLE HINSTANCE;
typedef HANDLE HKEY, *PHKEY;
typedef HANDLE HKL;
typedef HANDLE HLOCAL;
typedef HANDLE HMENU;
typedef HANDLE HMETAFILE;
typedef HANDLE HMODULE;
typedef HANDLE HPALETTE;
typedef HANDLE HPEN;
typedef HANDLE HRASCONN;
typedef long HRESULT;
typedef HANDLE HRGN;
typedef HANDLE HRSRC;
typedef HANDLE HSTMT;
typedef HANDLE HSZ;
typedef HANDLE HWINSTA;
typedef HANDLE HWND;
typedef int INT;
typedef unsigned short LANGID;
typedef DWORD LCID;
typedef DWORD LCTYPE;
 
typedef double LONGLONG, *PLONGLONG;
typedef unsigned short *LP;
typedef long LPARAM;
typedef WINBOOL *LPBOOL;
typedef BYTE *LPBYTE;
typedef const  CHAR *LPCCH;
typedef CHAR *LPCH;
typedef COLORREF *LPCOLORREF;
typedef const char *LPCSTR;




typedef const char *LPCTSTR;


typedef const unsigned short *LPCWCH;
typedef const unsigned short *LPCWSTR;
typedef DWORD *LPDWORD;
 
typedef HANDLE *LPHANDLE;
 
typedef int *LPINT;
typedef long *LPLONG;
typedef char *LPSTR;





typedef char *LPTCH;
typedef char *LPTSTR;


typedef long LRESULT;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef unsigned short *LPWCH;
typedef unsigned short *LPWORD;
typedef unsigned short *LPWSTR;
 
typedef unsigned short *NWPSTR;
typedef WINBOOL *PWINBOOL;
typedef BYTE *PBOOLEAN;
typedef BYTE *PBYTE;
typedef const CHAR *PCCH;
typedef CHAR *PCH;
typedef CHAR *PCHAR;
typedef const char *PCSTR;
typedef const unsigned short *PCWCH;
typedef const unsigned short *PCWSTR;
typedef DWORD *PDWORD;
typedef float *PFLOAT;
typedef HANDLE *PHANDLE;
 
typedef int *PINT;
 
typedef long *PLONG;
typedef short *PSHORT;
 
typedef char *PSTR;
typedef char *PSZ;







typedef unsigned char *PTBYTE;
typedef char *PTCH;
typedef char *PTCHAR;
typedef char *PTSTR;


typedef unsigned char *PUCHAR;
typedef unsigned int *PUINT;
typedef unsigned long *PULONG;
typedef unsigned short *PUSHORT;
typedef void *PVOID;
typedef unsigned short *PWCH;
typedef unsigned short *PWCHAR;
typedef unsigned short *PWORD;
 




typedef short RETCODE;

typedef HANDLE SC_HANDLE;
typedef LPVOID  SC_LOCK;
typedef SC_HANDLE *LPSC_HANDLE;
typedef DWORD SERVICE_STATUS_HANDLE;
 






typedef unsigned char TBYTE;
typedef char TCHAR;
typedef BYTE BCHAR;


typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned short USHORT;
typedef unsigned short WCHAR;
typedef unsigned short WORD;
typedef unsigned int WPARAM;
 

 

















 


typedef enum _ACL_INFORMATION_CLASS {
  AclRevisionInformation = 1,   
  AclSizeInformation            
} ACL_INFORMATION_CLASS; 
 
typedef enum _MEDIA_TYPE { 
  Unknown,                
  F5_1Pt2_512,            
  F3_1Pt44_512,           
  F3_2Pt88_512,           
  F3_20Pt8_512,           
  F3_720_512,             
  F5_360_512,             
  F5_320_512,             
  F5_320_1024,            
  F5_180_512,             
  F5_160_512,             
  RemovableMedia,         
  FixedMedia              
} MEDIA_TYPE; 
 


typedef enum _RASCONNSTATE { 
    RASCS_OpenPort = 0, 
    RASCS_PortOpened, 
    RASCS_ConnectDevice, 
    RASCS_DeviceConnected, 
    RASCS_AllDevicesConnected, 
    RASCS_Authenticate, 
    RASCS_AuthNotify, 
    RASCS_AuthRetry, 
    RASCS_AuthCallback, 
    RASCS_AuthChangePassword, 
    RASCS_AuthProject, 
    RASCS_AuthLinkSpeed, 
    RASCS_AuthAck, 
    RASCS_ReAuthenticate, 
    RASCS_Authenticated, 
    RASCS_PrepareForCallback, 
    RASCS_WaitForModemReset, 
    RASCS_WaitForCallback,
    RASCS_Projected, 
 
    RASCS_StartAuthentication,  
    RASCS_CallbackComplete,     
    RASCS_LogonNetwork,         
 
    RASCS_Interactive = 0x1000 , 
    RASCS_RetryAuthentication, 
    RASCS_CallbackSetByCaller, 
    RASCS_PasswordExpired, 
 
    RASCS_Connected = 0x2000 , 
    RASCS_Disconnected 
} RASCONNSTATE ; 
 
typedef enum _RASPROJECTION {  
    RASP_Amb = 0x10000, 
    RASP_PppNbf = 0x803F, 
    RASP_PppIpx = 0x802B, 
    RASP_PppIp = 0x8021 
} RASPROJECTION ; 
 
typedef enum _SECURITY_IMPERSONATION_LEVEL {
    SecurityAnonymous, 
    SecurityIdentification, 
    SecurityImpersonation, 
    SecurityDelegation 
} SECURITY_IMPERSONATION_LEVEL; 
 
typedef enum _SID_NAME_USE { 
    SidTypeUser = 1, 
    SidTypeGroup, 
    SidTypeDomain, 
    SidTypeAlias, 
    SidTypeWellKnownGroup, 
    SidTypeDeletedAccount, 
    SidTypeInvalid, 
    SidTypeUnknown 
} SID_NAME_USE, *PSID_NAME_USE; 
 
typedef enum _TOKEN_INFORMATION_CLASS {
    TokenUser = 1, 
    TokenGroups, 
    TokenPrivileges, 
    TokenOwner, 
    TokenPrimaryGroup, 
    TokenDefaultDacl, 
    TokenSource, 
    TokenType, 
    TokenImpersonationLevel, 
    TokenStatistics 
} TOKEN_INFORMATION_CLASS; 
 
typedef enum tagTOKEN_TYPE {
    TokenPrimary = 1, 
    TokenImpersonation 
} TOKEN_TYPE; 
 


 

























 






















































 


typedef int   (*BFFCALLBACK) (HWND, UINT, LPARAM, LPARAM);
typedef UINT   (*LPCCHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef UINT   (*LPCFHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef DWORD   (*PTHREAD_START_ROUTINE) (LPVOID);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;
typedef DWORD   (*EDITSTREAMCALLBACK) (DWORD, LPBYTE, LONG, LONG);
typedef UINT   (*LPFRHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef UINT   (*LPOFNHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef UINT   (*LPPRINTHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef UINT   (*LPSETUPHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
typedef WINBOOL   (*DLGPROC) (HWND, UINT, WPARAM, LPARAM);
typedef int   (*PFNPROPSHEETCALLBACK) (HWND, UINT, LPARAM);
typedef void    (*LPSERVICE_MAIN_FUNCTION) (DWORD, LPTSTR);
typedef int   (*PFNTVCOMPARE) (LPARAM, LPARAM, LPARAM);
typedef LRESULT   (*WNDPROC) (HWND, UINT, WPARAM, LPARAM);
typedef int   (*FARPROC)();
typedef FARPROC PROC;
typedef WINBOOL   (*ENUMRESTYPEPROC) (HANDLE, LPTSTR, LONG);
typedef WINBOOL   (*ENUMRESNAMEPROC) (HANDLE, LPCTSTR, LPTSTR, LONG);
typedef WINBOOL   (*ENUMRESLANGPROC) (HANDLE, LPCTSTR, LPCTSTR, WORD, LONG);
typedef FARPROC DESKTOPENUMPROC;
typedef WINBOOL   (*ENUMWINDOWSPROC) (HWND, LPARAM);
typedef WINBOOL   (*ENUMWINDOWSTATIONPROC) (LPTSTR, LPARAM);
typedef void    (*SENDASYNCPROC) (HWND, UINT, DWORD, LRESULT);
typedef void    (*TIMERPROC) (HWND, UINT, UINT, DWORD);
typedef FARPROC GRAYSTRINGPROC;
typedef WINBOOL   (*DRAWSTATEPROC) (HDC, LPARAM, WPARAM, int, int);
typedef WINBOOL   (*PROPENUMPROCEX) (HWND, LPCTSTR, HANDLE, DWORD);
typedef WINBOOL   (*PROPENUMPROC) (HWND, LPCTSTR, HANDLE);
typedef LRESULT   (*HOOKPROC) (int, WPARAM, LPARAM);
typedef void    (*ENUMOBJECTSPROC) (LPVOID, LPARAM);
typedef void    (*LINEDDAPROC) (int, int, LPARAM);
typedef WINBOOL   (*ABORTPROC) (HDC, int);
typedef UINT   (*LPPAGEPAINTHOOK) (HWND, UINT, WPARAM, LPARAM );
typedef UINT   (*LPPAGESETUPHOOK) (HWND, UINT, WPARAM, LPARAM );
typedef int   (*ICMENUMPROC) (LPTSTR, LPARAM);
typedef LONG (*EDITWORDBREAKPROCEX) (char *, LONG, BYTE, INT);
typedef int   (*PFNLVCOMPARE) (LPARAM, LPARAM, LPARAM);
typedef WINBOOL   (*LOCALE_ENUMPROC) (LPTSTR);
typedef WINBOOL   (*CODEPAGE_ENUMPROC) (LPTSTR);
typedef WINBOOL   (*DATEFMT_ENUMPROC) (LPTSTR);
typedef WINBOOL   (*TIMEFMT_ENUMPROC) (LPTSTR);
typedef WINBOOL   (*CALINFO_ENUMPROC) (LPTSTR);
typedef WINBOOL   (*PHANDLER_ROUTINE) (DWORD);
typedef WINBOOL   (*LPHANDLER_FUNCTION) (DWORD);
typedef UINT   (*PFNGETPROFILEPATH) (LPCTSTR, LPSTR, UINT);
typedef UINT   (*PFNRECONCILEPROFILE) (LPCTSTR, LPCTSTR, DWORD);
typedef WINBOOL   (*PFNPROCESSPOLICIES) (HWND, LPCTSTR, LPCTSTR, LPCTSTR, DWORD);


















































 
 

typedef void (*CALLB) ();
typedef CALLB PFNCALLBACK;

typedef WINBOOL SECURITY_CONTEXT_TRACKING_MODE;

 
 

typedef FARPROC WNDENUMPROC;
typedef FARPROC ENHMFENUMPROC;
typedef DWORD CCSTYLE, *PCCSTYLE, *LPCCSTYLE;
typedef DWORD CCSTYLEFLAGA, *PCCSTYLEFLAGA, *LPCCSTYLEFLAGA;





}



# 41 "include/windows.h" 2


 
# 1 "include/Windows32/Messages.h" 1
 




























 





extern "C" {



 

 

 












 




















 



































 












 

 

 





 




 














































































 



















 

 

 




















 
















# 292 "include/Windows32/Messages.h"











 




 









































 







 




































# 408 "include/Windows32/Messages.h"










































 





























 









 

 






 




























 










 






















 









 





 





 


















































 





























 

















 



































 




 





















# 757 "include/Windows32/Messages.h"

















 










 










































 























# 864 "include/Windows32/Messages.h"














 











 


 































































































































































































 






}



# 44 "include/windows.h" 2


 
# 1 "include/Windows32/Defines.h" 1
 




























 





extern "C" {
































 



 







 




 

















 









 















 
















 

















 













 

 




 




 











 














 












 











 






 







 





 












 

 










 
































 

















 







 






 










 












 




 


















































































 






























 
























































 







 




 



 


 













 





















 



 














 




























 








 



















































































































































 






















 










 

 

 

 

 

 

 















 




 


























 

 










 





 








 



 



 




























 































 






 










 





 





















 












































 




 













 
















 


 



 



 




 














 

 

 















 



 



 



 



 






















 









 






 



 





 









 







 

 

 

 





 


 








 






 






 

 



 







 






 





















 












 


























 














 





 


 








 




 




 











 





































































































 








 





















 





 








 



 



 






















 









 



 




 



 




 







 





 


 













 






 





 



















 





































 































 




 



















































































 




 





 



 












 










 





 





 




 







 











 

















 







 










 











 






 




 




 























 


















 












 




 




 


 
















 






 



 



































 




 

















 



 

 

 







































 







 




 









 




 









 





 

 

 

 

 

 













 








 


 







 



 



 





 





 










 













 








 





 













 







 





 




 




 



 




 





 




 

 
































































































 















































 


 

 

 









 















 










 




 


















 

 

 

 









 

 

 
















 


 




























































































 








 




 





 






















 





 




















 


 









 









 



 


 



































































 































 










 






 


 








 











 




 











 















 



 



















 







































 
































































































 




 










 







































































































 


 


 



 
















 



 
















 


 



 












 









 














 



 







 













 





 










 
















 












 






 



 



















 













 



















# 3576 "include/Windows32/Defines.h"















 




 















 







 





























 









 







 



 





 





 



 




 









 



 





 









 






















 




































 






 










 






 









 








 





 





 



 







 











 










 





 













 





 



 











 




 














 





 





 




 





























 



































































 






 




 

















































 







 



 




























 






 


 





 







 










 





 























 




 








 








 









 


















 



































 














# 4330 "include/Windows32/Defines.h"










 





 


 
























 



















 





 











































































































 









 


 







 


 




 






 





 









 





 






 









 






















 






 















 






 























 




 








 



 







 


 





















 


 












 




 




 



 











 















 










 









 














 



 








 






 


 







 










 








 






 





 

 














 



 

 






 





 

 



























































 


 
 
 








 
 
 



















































 
 



























































 





 









# 5121 "include/Windows32/Defines.h"

 


 








 























 





}



# 47 "include/windows.h" 2




 
# 1 "include/Windows32/Structures.h" 1
 




























 





extern "C" {


typedef struct _ABC {
  int     abcA; 
  UINT    abcB; 
  int     abcC; 
} ABC, *LPABC; 

typedef struct _ABCFLOAT {
  FLOAT   abcfA; 
  FLOAT   abcfB; 
  FLOAT   abcfC; 
} ABCFLOAT, *LPABCFLOAT; 

typedef struct tagACCEL {
  BYTE   fVirt; 
  WORD   key; 
  WORD   cmd; 
} ACCEL, *LPACCEL; 

typedef struct _ACE_HEADER {
  BYTE AceType; 
  BYTE AceFlags; 
  WORD AceSize; 
} ACE_HEADER; 

typedef DWORD ACCESS_MASK; 
typedef ACCESS_MASK REGSAM;

typedef struct _ACCESS_ALLOWED_ACE {
  ACE_HEADER Header; 
  ACCESS_MASK Mask; 
  DWORD SidStart; 
} ACCESS_ALLOWED_ACE; 

typedef struct _ACCESS_DENIED_ACE {
  ACE_HEADER  Header; 
  ACCESS_MASK Mask; 
  DWORD       SidStart; 
} ACCESS_DENIED_ACE; 

typedef struct tagACCESSTIMEOUT {
  UINT  cbSize; 
  DWORD dwFlags; 
  DWORD iTimeOutMSec; 
} ACCESSTIMEOUT; 

typedef struct _ACL {
  BYTE AclRevision; 
  BYTE Sbz1; 
  WORD AclSize; 
  WORD AceCount; 
  WORD Sbz2; 
} ACL, *PACL; 

typedef struct _ACL_REVISION_INFORMATION {    
  DWORD   AclRevision; 
} ACL_REVISION_INFORMATION; 

typedef struct _ACL_SIZE_INFORMATION {
  DWORD   AceCount; 
  DWORD   AclBytesInUse; 
  DWORD   AclBytesFree; 
} ACL_SIZE_INFORMATION; 

typedef struct _ACTION_HEADER {
  ULONG   transport_id; 
  USHORT  action_code; 
  USHORT  reserved; 
} ACTION_HEADER; 

typedef struct _ADAPTER_STATUS {
  UCHAR   adapter_address[6]; 
  UCHAR   rev_major; 
  UCHAR   reserved0; 
  UCHAR   adapter_type; 
  UCHAR   rev_minor; 
  WORD    duration; 
  WORD    frmr_recv; 
  WORD    frmr_xmit; 
  WORD    iframe_recv_err; 
  WORD    xmit_aborts; 
  DWORD   xmit_success; 
  DWORD   recv_success; 
  WORD    iframe_xmit_err; 
  WORD    recv_buff_unavail; 
  WORD    t1_timeouts; 
  WORD    ti_timeouts; 
  DWORD   reserved1; 
  WORD    free_ncbs; 
  WORD    max_cfg_ncbs; 
  WORD    max_ncbs; 
  WORD    xmit_buf_unavail; 
  WORD    max_dgram_size; 
  WORD    pending_sess; 
  WORD    max_cfg_sess; 
  WORD    max_sess; 
  WORD    max_sess_pkt_size; 
  WORD    name_count; 
} ADAPTER_STATUS; 

typedef struct _ADDJOB_INFO_1 {
  LPTSTR  Path; 
  DWORD   JobId; 
} ADDJOB_INFO_1; 

typedef struct tagANIMATIONINFO { 
  UINT cbSize; 
  int  iMinAnimate; 
} ANIMATIONINFO, *LPANIMATIONINFO; 

typedef struct _RECT {  
  LONG left;       
  LONG top;        
  LONG right;      
  LONG bottom;     
} RECT, *LPRECT, *PRECT; 
 
typedef struct _RECTL { 
  LONG left;     
  LONG top;      
  LONG right;    
  LONG bottom;   
} RECTL; 
 
typedef struct _AppBarData {
  DWORD  cbSize;           
  HWND   hWnd;             
  UINT   uCallbackMessage; 
  UINT   uEdge;            
  RECT   rc;               
  LPARAM lParam;           
} APPBARDATA, *PAPPBARDATA; 

typedef struct tagBITMAP
{
  LONG        bmType;
  LONG        bmWidth;
  LONG        bmHeight;
  LONG        bmWidthBytes;
  WORD        bmPlanes;
  WORD        bmBitsPixel;
  LPVOID      bmBits;
} BITMAP, *PBITMAP,   *NPBITMAP,   *LPBITMAP;

typedef struct tagBITMAPCOREHEADER {
  DWORD   bcSize; 
  WORD    bcWidth; 
  WORD    bcHeight; 
  WORD    bcPlanes; 
  WORD    bcBitCount; 
} BITMAPCOREHEADER; 

typedef struct tagRGBTRIPLE { 
  BYTE rgbtBlue; 
  BYTE rgbtGreen; 
  BYTE rgbtRed; 
} RGBTRIPLE; 
 
typedef struct _BITMAPCOREINFO {
  BITMAPCOREHEADER  bmciHeader; 
  RGBTRIPLE         bmciColors[1]; 
} BITMAPCOREINFO, *PBITMAPCOREINFO, *LPBITMAPCOREINFO; 

typedef struct tagBITMAPFILEHEADER {
  WORD    bfType; 
  DWORD   bfSize; 
  WORD    bfReserved1; 
  WORD    bfReserved2; 
  DWORD   bfOffBits; 
} __attribute__((packed)) BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER {
  DWORD  biSize; 
  LONG   biWidth; 
  LONG   biHeight; 
  WORD   biPlanes; 
  WORD   biBitCount; 
  DWORD  biCompression; 
  DWORD  biSizeImage; 
  LONG   biXPelsPerMeter; 
  LONG   biYPelsPerMeter; 
  DWORD  biClrUsed; 
  DWORD  biClrImportant; 
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFO; 

typedef struct tagRGBQUAD { 
  BYTE    rgbBlue; 
  BYTE    rgbGreen; 
  BYTE    rgbRed; 
  BYTE    rgbReserved; 
} RGBQUAD; 
 
typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader; 
  RGBQUAD          bmiColors[1]; 
} BITMAPINFO, *LPBITMAPINFO; 

typedef long FXPT2DOT30,  * LPFXPT2DOT30;

typedef struct tagCIEXYZ
{
  FXPT2DOT30 ciexyzX; 
  FXPT2DOT30 ciexyzY; 
  FXPT2DOT30 ciexyzZ; 
} CIEXYZ;
typedef CIEXYZ  * LPCIEXYZ; 

typedef struct tagCIEXYZTRIPLE
{
  CIEXYZ  ciexyzRed; 
  CIEXYZ  ciexyzGreen; 
  CIEXYZ  ciexyzBlue; 
} CIEXYZTRIPLE;
typedef CIEXYZTRIPLE  * LPCIEXYZTRIPLE; 

typedef struct {
  DWORD        bV4Size;
  LONG         bV4Width;
  LONG         bV4Height;
  WORD         bV4Planes;
  WORD         bV4BitCount;
  DWORD        bV4V4Compression;
  DWORD        bV4SizeImage;
  LONG         bV4XPelsPerMeter;
  LONG         bV4YPelsPerMeter;
  DWORD        bV4ClrUsed;
  DWORD        bV4ClrImportant;
  DWORD        bV4RedMask;
  DWORD        bV4GreenMask;
  DWORD        bV4BlueMask;
  DWORD        bV4AlphaMask;
  DWORD        bV4CSType;
  CIEXYZTRIPLE bV4Endpoints;
  DWORD        bV4GammaRed;
  DWORD        bV4GammaGreen;
  DWORD        bV4GammaBlue;
} BITMAPV4HEADER,   *LPBITMAPV4HEADER, *PBITMAPV4HEADER; 

typedef struct _BLOB { 
  ULONG   cbSize; 
  BYTE    *pBlobData; 
} BLOB; 

typedef struct _SHITEMID {       
  USHORT cb;       
  BYTE   abID[1];  
} SHITEMID, * LPSHITEMID; 
typedef const SHITEMID  * LPCSHITEMID; 
 
typedef struct _ITEMIDLIST { 
  SHITEMID mkid;  
} ITEMIDLIST, * LPITEMIDLIST; 
typedef const ITEMIDLIST * LPCITEMIDLIST; 
 
typedef struct _browseinfo { 
  HWND hwndOwner;          
  LPCITEMIDLIST pidlRoot;  
  LPSTR pszDisplayName;    
  LPCSTR lpszTitle;        
  UINT ulFlags;            
  BFFCALLBACK lpfn;        
  LPARAM lParam;           
  int iImage;              
} BROWSEINFO, *PBROWSEINFO, *LPBROWSEINFO; 

typedef struct _FILETIME { 
  DWORD dwLowDateTime; 
  DWORD dwHighDateTime; 
} FILETIME, *LPFILETIME, *PFILETIME; 
 
typedef struct _BY_HANDLE_FILE_INFORMATION {
  DWORD    dwFileAttributes; 
  FILETIME ftCreationTime; 
  FILETIME ftLastAccessTime; 
  FILETIME ftLastWriteTime; 
  DWORD    dwVolumeSerialNumber; 
  DWORD    nFileSizeHigh; 
  DWORD    nFileSizeLow; 
  DWORD    nNumberOfLinks; 
  DWORD    nFileIndexHigh; 
  DWORD    nFileIndexLow; 
} BY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION; 

typedef struct _FIXED { 
  WORD  fract; 
  short value; 
} FIXED; 
 
typedef struct tagPOINT { 
  LONG x; 
  LONG y; 
} POINT, *LPPOINT, *PPOINT;
 
typedef struct tagPOINTFX { 
  FIXED x; 
  FIXED y; 
} POINTFX; 
 
typedef struct _POINTL { 
  LONG x; 
  LONG y; 
} POINTL; 
 
typedef struct tagPOINTS { 
  SHORT x;    
  SHORT y;    
} POINTS; 
 
typedef struct _tagCANDIDATEFORM {
  DWORD  dwIndex;       
  DWORD  dwStyle;       
  POINT  ptCurrentPos;  
  RECT   rcArea;        
} CANDIDATEFORM, *LPCANDIDATEFORM;

typedef struct _tagCANDIDATELIST {
  DWORD  dwSize;       
  DWORD  dwStyle;      
  DWORD  dwCount;      
  DWORD  dwSelection;  
  DWORD  dwPageStart;  
  DWORD  dwPageSize;   
  DWORD  dwOffset[1];
} CANDIDATELIST, *LPCANDIDATELIST;

typedef struct tagCREATESTRUCT { 
  LPVOID    lpCreateParams;  
  HINSTANCE hInstance;       
  HMENU     hMenu;           
  HWND      hwndParent;      
  int       cy;              
  int       cx;              
  int       y;               
  int       x;               
  LONG      style;           
  LPCTSTR   lpszName;        
  LPCTSTR   lpszClass;       
  DWORD     dwExStyle;       
} CREATESTRUCT, *LPCREATESTRUCT; 
 
typedef struct tagCBT_CREATEWND {
  LPCREATESTRUCT lpcs; 
  HWND           hwndInsertAfter; 
} CBT_CREATEWND; 

typedef struct tagCBTACTIVATESTRUCT {
  WINBOOL fMouse; 
  HWND hWndActive; 
} CBTACTIVATESTRUCT; 

typedef struct _CHAR_INFO {
  union {               
    WCHAR UnicodeChar; 
    CHAR AsciiChar; 
  } Char; 
  WORD Attributes;      
} CHAR_INFO, *PCHAR_INFO; 

typedef struct _charformat { 
  UINT     cbSize; 
  DWORD    dwMask; 
  DWORD    dwEffects; 
  LONG     yHeight; 
  LONG     yOffset; 
  COLORREF crTextColor; 
  BYTE     bCharSet; 
  BYTE     bPitchAndFamily; 
  TCHAR    szFaceName[(32) ]; 
} CHARFORMAT; 

typedef struct _charrange { 
  LONG cpMin; 
  LONG cpMax; 
} CHARRANGE; 

typedef struct tagCHARSET {
  DWORD aflBlock[3]; 
  DWORD flLang; 
} CHARSET; 

typedef struct tagFONTSIGNATURE {
  DWORD  fsUsb[4];
  DWORD  fsCsb[2];
} FONTSIGNATURE, *LPFONTSIGNATURE; 
 
typedef struct {
  UINT ciCharset;
  UINT ciACP;
  FONTSIGNATURE fs;
} CHARSETINFO, *LPCHARSETINFO;

typedef struct { 
  DWORD        lStructSize; 
  HWND         hwndOwner; 
  HWND         hInstance; 
  COLORREF     rgbResult; 
  COLORREF*    lpCustColors; 
  DWORD        Flags; 
  LPARAM       lCustData; 
  LPCCHOOKPROC lpfnHook; 
  LPCTSTR      lpTemplateName; 
} CHOOSECOLOR, *LPCHOOSECOLOR; 

typedef struct tagLOGFONT { 
  LONG lfHeight; 
  LONG lfWidth; 
  LONG lfEscapement; 
  LONG lfOrientation; 
  LONG lfWeight; 
  BYTE lfItalic; 
  BYTE lfUnderline; 
  BYTE lfStrikeOut; 
  BYTE lfCharSet; 
  BYTE lfOutPrecision; 
  BYTE lfClipPrecision; 
  BYTE lfQuality; 
  BYTE lfPitchAndFamily; 
  TCHAR lfFaceName[(32) ]; 
} LOGFONT, *LPLOGFONT, *PLOGFONT; 
 
typedef struct { 
  DWORD        lStructSize; 
  HWND         hwndOwner; 
  HDC          hDC; 
  LPLOGFONT    lpLogFont; 
  INT          iPointSize; 
  DWORD        Flags; 
  DWORD        rgbColors; 
  LPARAM       lCustData; 
  LPCFHOOKPROC lpfnHook; 
  LPCTSTR      lpTemplateName; 
  HINSTANCE    hInstance; 
  LPTSTR       lpszStyle; 
  WORD         nFontType; 
  WORD         ___MISSING_ALIGNMENT__; 
  INT          nSizeMin; 
  INT          nSizeMax; 
} CHOOSEFONT, *LPCHOOSEFONT; 

typedef struct _IDA { 
  UINT cidl;     
  UINT aoffset[1]; 
} CIDA, * LPIDA; 

typedef struct tagCLIENTCREATESTRUCT {
  HANDLE hWindowMenu; 
  UINT   idFirstChild; 
} CLIENTCREATESTRUCT; 

typedef CLIENTCREATESTRUCT *LPCLIENTCREATESTRUCT;

typedef struct _CMInvokeCommandInfo { 
  DWORD cbSize;       
  DWORD fMask;        
  HWND hwnd;          
  LPCSTR lpVerb;      
  LPCSTR lpParameters;
  LPCSTR lpDirectory; 
  int nShow;          
  DWORD dwHotKey;     
  HANDLE hIcon;       
} CMINVOKECOMMANDINFO, *LPCMINVOKECOMMANDINFO; 

typedef struct  tagCOLORADJUSTMENT {
  WORD  caSize; 
  WORD  caFlags; 
  WORD  caIlluminantIndex; 
  WORD  caRedGamma; 
  WORD  caGreenGamma; 
  WORD  caBlueGamma; 
  WORD  caReferenceBlack; 
  WORD  caReferenceWhite; 
  SHORT caContrast; 
  SHORT caBrightness; 
  SHORT caColorfulness; 
  SHORT caRedGreenTint; 
} COLORADJUSTMENT, *LPCOLORADJUSTMENT; 

typedef struct _COLORMAP { 
  COLORREF from; 
  COLORREF to; 
} COLORMAP,  * LPCOLORMAP; 

typedef struct _DCB { 
  DWORD DCBlength;          
  DWORD BaudRate;           
  DWORD fBinary: 1;         
  DWORD fParity: 1;         
  DWORD fOutxCtsFlow:1;     
  DWORD fOutxDsrFlow:1;     
  DWORD fDtrControl:2;      
  DWORD fDsrSensitivity:1;  
  DWORD fTXContinueOnXoff:1;
  DWORD fOutX: 1;        
  DWORD fInX: 1;         
  DWORD fErrorChar: 1;   
  DWORD fNull: 1;        
  DWORD fRtsControl:2;   
  DWORD fAbortOnError:1; 
  DWORD fDummy2:17;      
  WORD wReserved;        
  WORD XonLim;           
  WORD XoffLim;          
  BYTE ByteSize;         
  BYTE Parity;           
  BYTE StopBits;         
  char XonChar;          
  char XoffChar;         
  char ErrorChar;        
  char EofChar;          
  char EvtChar;          
  WORD wReserved1;       
} DCB, *LPDCB; 
 
typedef struct _COMM_CONFIG {
  DWORD dwSize;
  WORD  wVersion; 
  WORD  wReserved;
  DCB   dcb;
  DWORD dwProviderSubType;
  DWORD dwProviderOffset;
  DWORD dwProviderSize;
  WCHAR wcProviderData[1];
} COMMCONFIG, *LPCOMMCONFIG;

typedef struct _COMMPROP {
  WORD  wPacketLength;       
  WORD  wPacketVersion;      
  DWORD dwServiceMask;       
  DWORD dwReserved1;         
  DWORD dwMaxTxQueue;        
  DWORD dwMaxRxQueue;        
  DWORD dwMaxBaud;           
  DWORD dwProvSubType;       
  DWORD dwProvCapabilities;  
  DWORD dwSettableParams;    
  DWORD dwSettableBaud;      
  WORD  wSettableData;       
  WORD  wSettableStopParity; 
  DWORD dwCurrentTxQueue;    
  DWORD dwCurrentRxQueue;    
  DWORD dwProvSpec1;         
  DWORD dwProvSpec2;         
  WCHAR wcProvChar[1];       
} COMMPROP, *LPCOMMPROP; 

typedef struct _COMMTIMEOUTS {
  DWORD ReadIntervalTimeout; 
  DWORD ReadTotalTimeoutMultiplier; 
  DWORD ReadTotalTimeoutConstant; 
  DWORD WriteTotalTimeoutMultiplier; 
  DWORD WriteTotalTimeoutConstant; 
} COMMTIMEOUTS,*LPCOMMTIMEOUTS; 

typedef struct tagCOMPAREITEMSTRUCT {
  UINT  CtlType; 
  UINT  CtlID; 
  HWND  hwndItem; 
  UINT  itemID1; 
  DWORD itemData1; 
  UINT  itemID2; 
  DWORD itemData2; 
} COMPAREITEMSTRUCT; 

typedef struct {
  COLORREF crText;        
  COLORREF crBackground;  
  DWORD dwEffects;        
} COMPCOLOR;

typedef struct _tagCOMPOSITIONFORM {
  DWORD  dwStyle;       
  POINT  ptCurrentPos;  
  RECT   rcArea;        
} COMPOSITIONFORM, *LPCOMPOSITIONFORM;

typedef struct _COMSTAT {
  DWORD fCtsHold : 1;   
  DWORD fDsrHold : 1;   
  DWORD fRlsdHold : 1;  
  DWORD fXoffHold : 1;  
  DWORD fXoffSent : 1;  
  DWORD fEof : 1;       
  DWORD fTxim : 1;      
  DWORD fReserved : 25; 
  DWORD cbInQue;        
  DWORD cbOutQue;       
} COMSTAT, *LPCOMSTAT; 

typedef struct _CONSOLE_CURSOR_INFO {
  DWORD  dwSize; 
  WINBOOL   bVisible; 
} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO; 

typedef struct _COORD {
  SHORT X;    
  SHORT Y;    
} COORD; 

typedef struct _SMALL_RECT { 
  SHORT Left;      
  SHORT Top;       
  SHORT Right;     
  SHORT Bottom;    
} SMALL_RECT, *PSMALL_RECT; 
 
typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
  COORD      dwSize; 
  COORD      dwCursorPosition; 
  WORD       wAttributes; 
  SMALL_RECT srWindow; 
  COORD      dwMaximumWindowSize; 
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO ; 

# 698 "include/Windows32/Structures.h"


typedef struct
  {
     
    double Fpr0;
    double Fpr1;
    double Fpr2;
    double Fpr3;
    double Fpr4;
    double Fpr5;
    double Fpr6;
    double Fpr7;
    double Fpr8;
    double Fpr9;
    double Fpr10;
    double Fpr11;
    double Fpr12;
    double Fpr13;
    double Fpr14;
    double Fpr15;
    double Fpr16;
    double Fpr17;
    double Fpr18;
    double Fpr19;
    double Fpr20;
    double Fpr21;
    double Fpr22;
    double Fpr23;
    double Fpr24;
    double Fpr25;
    double Fpr26;
    double Fpr27;
    double Fpr28;
    double Fpr29;
    double Fpr30;
    double Fpr31;
    double Fpscr;

     
    DWORD Gpr0;
    DWORD Gpr1;
    DWORD Gpr2;
    DWORD Gpr3;
    DWORD Gpr4;
    DWORD Gpr5;
    DWORD Gpr6;
    DWORD Gpr7;
    DWORD Gpr8;
    DWORD Gpr9;
    DWORD Gpr10;
    DWORD Gpr11;
    DWORD Gpr12;
    DWORD Gpr13;
    DWORD Gpr14;
    DWORD Gpr15;
    DWORD Gpr16;
    DWORD Gpr17;
    DWORD Gpr18;
    DWORD Gpr19;
    DWORD Gpr20;
    DWORD Gpr21;
    DWORD Gpr22;
    DWORD Gpr23;
    DWORD Gpr24;
    DWORD Gpr25;
    DWORD Gpr26;
    DWORD Gpr27;
    DWORD Gpr28;
    DWORD Gpr29;
    DWORD Gpr30;
    DWORD Gpr31;

    DWORD Cr;			 
    DWORD Xer;			 

     
    DWORD Msr;			 
    DWORD Iar;			 
    DWORD Lr;			 
    DWORD Ctr;			 

     
    DWORD ContextFlags;
    DWORD Fill[3];

     
    DWORD Dr0;                           
    DWORD Dr1;                           
    DWORD Dr2;                           
    DWORD Dr3;                           
    DWORD Dr4;                           
    DWORD Dr5;                           
    DWORD Dr6;                           
    DWORD Dr7;                           
} CONTEXT, *PCONTEXT, *LPCONTEXT;


typedef struct _LIST_ENTRY { 
  struct _LIST_ENTRY *Flink; 
  struct _LIST_ENTRY *Blink; 
} LIST_ENTRY, *PLIST_ENTRY; 
 
typedef struct _CRITICAL_SECTION_DEBUG {
    WORD   Type;
    WORD   CreatorBackTraceIndex;
    struct _CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Depth;
    PVOID OwnerBackTrace[ 5 ];
} CRITICAL_SECTION_DEBUG, *PCRITICAL_SECTION_DEBUG;

typedef struct _CRITICAL_SECTION {
    PCRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    DWORD Reserved;
} CRITICAL_SECTION, *PCRITICAL_SECTION, *LPCRITICAL_SECTION;

typedef struct _SECURITY_QUALITY_OF_SERVICE { 
  DWORD Length; 
  SECURITY_IMPERSONATION_LEVEL ImpersonationLevel; 
   
  WINBOOL ContextTrackingMode; 
  BOOLEAN EffectiveOnly; 
} SECURITY_QUALITY_OF_SERVICE; 

typedef struct tagCONVCONTEXT { 
  UINT  cb; 
  UINT  wFlags; 
  UINT  wCountryID; 
  int   iCodePage; 
  DWORD dwLangID; 
  DWORD dwSecurity; 
  SECURITY_QUALITY_OF_SERVICE qos;
} CONVCONTEXT; 

typedef CONVCONTEXT *PCONVCONTEXT;

typedef struct tagCONVINFO { 
  DWORD       cb; 
  DWORD       hUser; 
  HCONV       hConvPartner; 
  HSZ         hszSvcPartner; 
  HSZ         hszServiceReq; 
  HSZ         hszTopic; 
  HSZ         hszItem; 
  UINT        wFmt; 
  UINT        wType; 
  UINT        wStatus; 
  UINT        wConvst; 
  UINT        wLastError; 
  HCONVLIST   hConvList; 
  CONVCONTEXT ConvCtxt; 
  HWND        hwnd; 
  HWND        hwndPartner; 
} CONVINFO; 

typedef struct tagCOPYDATASTRUCT { 
  DWORD dwData; 
  DWORD cbData; 
  PVOID lpData; 
} COPYDATASTRUCT; 

typedef struct _cpinfo { 
  UINT MaxCharSize; 
  BYTE DefaultChar[(2) ]; 
  BYTE LeadByte[(12) ]; 
} CPINFO, *LPCPINFO; 

typedef struct tagCPLINFO { 
  int  idIcon; 
  int  idName; 
  int  idInfo; 
  LONG lData; 
} CPLINFO; 

typedef struct _CREATE_PROCESS_DEBUG_INFO {
  HANDLE hFile; 
  HANDLE hProcess; 
  HANDLE hThread; 
  LPVOID lpBaseOfImage; 
  DWORD dwDebugInfoFileOffset; 
  DWORD nDebugInfoSize; 
  LPVOID lpThreadLocalBase; 
  LPTHREAD_START_ROUTINE lpStartAddress; 
  LPVOID lpImageName; 
  WORD fUnicode; 
} CREATE_PROCESS_DEBUG_INFO; 
 
typedef struct _CREATE_THREAD_DEBUG_INFO {
  HANDLE hThread; 
  LPVOID lpThreadLocalBase; 
  LPTHREAD_START_ROUTINE lpStartAddress; 
} CREATE_THREAD_DEBUG_INFO; 
 
 







 







 
typedef struct _currencyfmt { 
  UINT      NumDigits; 
  UINT      LeadingZero; 
  UINT      Grouping; 
  LPTSTR    lpDecimalSep; 
  LPTSTR    lpThousandSep; 
  UINT      NegativeOrder; 
  UINT      PositiveOrder; 
  LPTSTR    lpCurrencySymbol;
} CURRENCYFMT; 
 
typedef struct tagCURSORSHAPE {  
  int     xHotSpot; 
  int     yHotSpot; 
  int     cx; 
  int     cy; 
  int     cbWidth; 
  BYTE    Planes; 
  BYTE    BitsPixel; 
} CURSORSHAPE,   *LPCURSORSHAPE; 
 
typedef struct tagCWPRETSTRUCT {
  LRESULT lResult; 
  LPARAM  lParam; 
  WPARAM  wParam; 
  DWORD   message; 
  HWND    hwnd; 
} CWPRETSTRUCT; 

typedef struct tagCWPSTRUCT {
  LPARAM  lParam; 
  WPARAM  wParam; 
  UINT    message; 
  HWND    hwnd; 
} CWPSTRUCT; 
 
typedef struct _DATATYPES_INFO_1 { 
  LPTSTR pName; 
} DATATYPES_INFO_1; 
 
typedef struct { 
  unsigned short bAppReturnCode:8, 
    reserved:6, 
    fBusy:1, 
    fAck:1; 
} DDEACK; 
 
typedef struct { 
  unsigned short reserved:14, 
    fDeferUpd:1, 
    fAckReq:1; 
  short cfFormat; 
} DDEADVISE; 
 
typedef struct { 
  unsigned short unused:12, 
    fResponse:1, 
    fRelease:1, 
    reserved:1, 
    fAckReq:1; 
  short cfFormat; 
  BYTE  Value[1]; 
} DDEDATA; 
 
typedef struct { 
  unsigned short unused:13, 
    fRelease:1, 
    fDeferUpd:1, 
    fAckReq:1; 
  short cfFormat; 
} DDELN; 
 
typedef struct tagDDEML_MSG_HOOK_DATA { 
  UINT  uiLo; 
  UINT  uiHi; 
  DWORD cbData; 
  DWORD Data[8]; 
} DDEML_MSG_HOOK_DATA; 
 
typedef struct { 
  unsigned short unused:13, 
    fRelease:1, 
    fReserved:2; 
  short cfFormat; 
  BYTE  Value[1]; 
} DDEPOKE; 
 
typedef struct { 
  unsigned short unused:12, 
    fAck:1, 
    fRelease:1, 
    fReserved:1, 
    fAckReq:1; 
  short cfFormat; 
  BYTE rgb[1]; 
} DDEUP; 
 
typedef struct _EXCEPTION_RECORD { 
  DWORD ExceptionCode; 
  DWORD ExceptionFlags; 
  struct _EXCEPTION_RECORD *ExceptionRecord; 
  PVOID ExceptionAddress; 
  DWORD NumberParameters; 
  DWORD ExceptionInformation[(15) ]; 
} EXCEPTION_RECORD, *PEXCEPTION_RECORD, *LPEXCEPTION_RECORD; 
 
typedef struct _EXCEPTION_DEBUG_INFO {
  EXCEPTION_RECORD ExceptionRecord; 
  DWORD dwFirstChance; 
} EXCEPTION_DEBUG_INFO; 
 
typedef struct _EXIT_PROCESS_DEBUG_INFO { 
  DWORD dwExitCode; 
} EXIT_PROCESS_DEBUG_INFO; 
 
typedef struct _EXIT_THREAD_DEBUG_INFO { 
  DWORD dwExitCode; 
} EXIT_THREAD_DEBUG_INFO; 
 
typedef struct _LOAD_DLL_DEBUG_INFO { 
  HANDLE hFile; 
  LPVOID lpBaseOfDll; 
  DWORD  dwDebugInfoFileOffset; 
  DWORD  nDebugInfoSize; 
  LPVOID lpImageName; 
  WORD fUnicode; 
} LOAD_DLL_DEBUG_INFO; 
 
typedef struct _UNLOAD_DLL_DEBUG_INFO { 
  LPVOID lpBaseOfDll; 
} UNLOAD_DLL_DEBUG_INFO; 
 
typedef struct _OUTPUT_DEBUG_STRING_INFO { 
  LPSTR lpDebugStringData; 
  WORD  fUnicode; 
  WORD  nDebugStringLength; 
} OUTPUT_DEBUG_STRING_INFO; 
 
typedef struct _RIP_INFO { 
  DWORD  dwError; 
  DWORD  dwType; 
} RIP_INFO; 
 
typedef struct _DEBUG_EVENT { 
  DWORD dwDebugEventCode; 
  DWORD dwProcessId; 
  DWORD dwThreadId; 
  union { 
    EXCEPTION_DEBUG_INFO Exception; 
    CREATE_THREAD_DEBUG_INFO CreateThread; 
    CREATE_PROCESS_DEBUG_INFO CreateProcessInfo; 
    EXIT_THREAD_DEBUG_INFO ExitThread; 
    EXIT_PROCESS_DEBUG_INFO ExitProcess; 
    LOAD_DLL_DEBUG_INFO LoadDll; 
    UNLOAD_DLL_DEBUG_INFO UnloadDll; 
    OUTPUT_DEBUG_STRING_INFO DebugString; 
    RIP_INFO RipInfo; 
  } u; 
} DEBUG_EVENT, *LPDEBUG_EVENT; 
 
typedef struct tagDEBUGHOOKINFO {
  DWORD  idThread; 
  DWORD  idThreadInstaller; 
  LPARAM lParam; 
  WPARAM wParam; 
  int    code; 
} DEBUGHOOKINFO; 
 
typedef struct tagDELETEITEMSTRUCT { 
  UINT CtlType; 
  UINT CtlID; 
  UINT itemID; 
  HWND hwndItem; 
  UINT itemData; 
} DELETEITEMSTRUCT; 
 
typedef struct _DEV_BROADCAST_HDR {
  ULONG dbch_size; 
  ULONG dbch_devicetype; 
  ULONG dbch_reserved; 
} DEV_BROADCAST_HDR;
typedef DEV_BROADCAST_HDR *PDEV_BROADCAST_HDR;
 
typedef struct _DEV_BROADCAST_OEM {
  ULONG dbco_size; 
  ULONG dbco_devicetype; 
  ULONG dbco_reserved; 
  ULONG dbco_identifier; 
  ULONG dbco_suppfunc; 
} DEV_BROADCAST_OEM;
typedef DEV_BROADCAST_OEM *PDEV_BROADCAST_OEM;
 
typedef struct _DEV_BROADCAST_PORT {
  ULONG dbcp_size; 
  ULONG dbcp_devicetype; 
  ULONG dbcp_reserved; 
  char dbcp_name[1]; 
} DEV_BROADCAST_PORT;
typedef DEV_BROADCAST_PORT *PDEV_BROADCAST_PORT;
 
struct _DEV_BROADCAST_USERDEFINED { 
  struct _DEV_BROADCAST_HDR dbud_dbh; 
  char  dbud_szName[1];
  BYTE  dbud_rgbUserDefined[1];
}; 
 
typedef struct _DEV_BROADCAST_VOLUME {
  ULONG dbcv_size; 
  ULONG dbcv_devicetype; 
  ULONG dbcv_reserved; 
  ULONG dbcv_unitmask; 
  USHORT dbcv_flags; 
} DEV_BROADCAST_VOLUME;
typedef DEV_BROADCAST_VOLUME *PDEV_BROADCAST_VOLUME;
 
typedef struct _devicemode {  
  BCHAR  dmDeviceName[(32) ]; 
  WORD   dmSpecVersion; 
  WORD   dmDriverVersion; 
  WORD   dmSize; 
  WORD   dmDriverExtra; 
  DWORD  dmFields; 
  short  dmOrientation; 
  short  dmPaperSize; 
  short  dmPaperLength; 
  short  dmPaperWidth; 
  short  dmScale; 
  short  dmCopies; 
  short  dmDefaultSource; 
  short  dmPrintQuality; 
  short  dmColor; 
  short  dmDuplex; 
  short  dmYResolution; 
  short  dmTTOption; 
  short  dmCollate; 
  BCHAR  dmFormName[(32) ]; 
  WORD  dmLogPixels; 
  DWORD  dmBitsPerPel; 
  DWORD  dmPelsWidth; 
  DWORD  dmPelsHeight; 
  DWORD  dmDisplayFlags; 
  DWORD  dmDisplayFrequency; 
  DWORD  dmICMMethod;         
  DWORD  dmICMIntent;         
  DWORD  dmMediaType;         
  DWORD  dmDitherType;        
  DWORD  dmICCManufacturer;   
  DWORD  dmICCModel;          
} DEVMODE, *LPDEVMODE; 
 
typedef struct tagDEVNAMES { 
  WORD wDriverOffset; 
  WORD wDeviceOffset; 
  WORD wOutputOffset; 
  WORD wDefault; 
} DEVNAMES, *LPDEVNAMES; 
 
typedef struct tagDIBSECTION { 
  BITMAP              dsBm; 
  BITMAPINFOHEADER    dsBmih; 
  DWORD               dsBitfields[3]; 
  HANDLE              dshSection; 
  DWORD               dsOffset; 
} DIBSECTION; 
 
typedef struct _LARGE_INTEGER { 
  DWORD LowPart; 
  LONG  HighPart; 
} LARGE_INTEGER, *PLARGE_INTEGER; 
 
typedef struct _DISK_GEOMETRY { 
  LARGE_INTEGER  Cylinders; 
  MEDIA_TYPE  MediaType; 
  DWORD  TracksPerCylinder; 
  DWORD  SectorsPerTrack; 
  DWORD  BytesPerSector; 
} DISK_GEOMETRY ; 
 
typedef struct _DISK_PERFORMANCE { 
  LARGE_INTEGER BytesRead; 
  LARGE_INTEGER BytesWritten; 
  LARGE_INTEGER ReadTime; 
  LARGE_INTEGER WriteTime; 
  DWORD ReadCount; 
  DWORD WriteCount; 
  DWORD QueueDepth; 
} DISK_PERFORMANCE ; 
 
typedef struct { 
  DWORD style; 
  DWORD dwExtendedStyle; 
  short x; 
  short y; 
  short cx; 
  short cy; 
  WORD  id; 
} __attribute__((packed))  DLGITEMTEMPLATE; 

typedef DLGITEMTEMPLATE *LPDLGITEMTEMPLATE;
typedef DLGITEMTEMPLATE *PDLGITEMTEMPLATE;
 
typedef struct { 
  DWORD style; 
  DWORD dwExtendedStyle; 
  WORD  cdit; 
  short x; 
  short y; 
  short cx; 
  short cy; 
} __attribute__((packed))  DLGTEMPLATE;

typedef DLGTEMPLATE *LPDLGTEMPLATE; 
typedef const DLGTEMPLATE *LPCDLGTEMPLATE;
 
typedef struct _DOC_INFO_1 { 
  LPTSTR pDocName; 
  LPTSTR pOutputFile; 
  LPTSTR pDatatype; 
} DOC_INFO_1; 
 
typedef struct _DOC_INFO_2 { 
  LPTSTR pDocName; 
  LPTSTR pOutputFile; 
  LPTSTR pDatatype; 
  DWORD  dwMode; 
  DWORD  JobId; 
} DOC_INFO_2; 
 
typedef struct {    
  int     cbSize; 
  LPCTSTR lpszDocName; 
  LPCTSTR lpszOutput; 
  LPCTSTR lpszDatatype; 
  DWORD   fwType;       
} DOCINFO; 
 
typedef struct { 
  UINT uNotification; 
  HWND hWnd; 
  POINT ptCursor; 
} DRAGLISTINFO, *LPDRAGLISTINFO; 
 
typedef struct tagDRAWITEMSTRUCT { 
  UINT  CtlType; 
  UINT  CtlID; 
  UINT  itemID; 
  UINT  itemAction; 
  UINT  itemState; 
  HWND  hwndItem; 
  HDC   hDC; 
  RECT  rcItem; 
  DWORD itemData; 
} DRAWITEMSTRUCT, *LPDRAWITEMSTRUCT, *PDRAWITEMSTRUCT; 
 
typedef struct { 
  UINT cbSize;         
  int  iTabLength;     
  int  iLeftMargin;    
  int  iRightMargin;   
  UINT uiLengthDrawn;  
} DRAWTEXTPARAMS, *LPDRAWTEXTPARAMS; 
 
typedef struct _PARTITION_INFORMATION { 
  BYTE PartitionType; 
  BOOLEAN BootIndicator; 
  BOOLEAN RecognizedPartition; 
  BOOLEAN RewritePartition; 
  LARGE_INTEGER StartingOffset; 
  LARGE_INTEGER PartitionLength; 
  LARGE_INTEGER HiddenSectors; 
} PARTITION_INFORMATION ; 
 
typedef struct _DRIVE_LAYOUT_INFORMATION { 
  DWORD  PartitionCount; 
  DWORD  Signature; 
  PARTITION_INFORMATION  PartitionEntry[1]; 
} DRIVE_LAYOUT_INFORMATION; 
 
typedef struct _DRIVER_INFO_1 { 
  LPTSTR pName; 
} DRIVER_INFO_1; 
 
typedef struct _DRIVER_INFO_2 { 
  DWORD  cVersion; 
  LPTSTR pName; 
  LPTSTR pEnvironment; 
  LPTSTR pDriverPath; 
  LPTSTR pDataFile; 
  LPTSTR pConfigFile; 
} DRIVER_INFO_2; 
 
typedef struct _DRIVER_INFO_3 { 
  DWORD  cVersion; 
  LPTSTR pName; 
  LPTSTR pEnvironment; 
  LPTSTR pDriverPath; 
  LPTSTR pDataFile; 
  LPTSTR pConfigFile; 
  LPTSTR pHelpFile; 
  LPTSTR pDependentFiles; 
  LPTSTR pMonitorName; 
  LPTSTR pDefaultDataType; 
} DRIVER_INFO_3; 
 
typedef struct _editstream { 
  DWORD dwCookie; 
  DWORD dwError; 
  EDITSTREAMCALLBACK pfnCallback; 
} EDITSTREAM; 
 
typedef struct tagEMR
{
  DWORD iType; 
  DWORD nSize;
} EMR, *PEMR; 
 
typedef struct tagEMRANGLEARC
{
  EMR     emr;
  POINTL  ptlCenter; 
  DWORD   nRadius;
  FLOAT   eStartAngle;
  FLOAT   eSweepAngle;
} EMRANGLEARC, *PEMRANGLEARC; 
 
typedef struct tagEMRARC
{
  EMR    emr; 
  RECTL  rclBox;
  POINTL ptlStart;
  POINTL ptlEnd;
} EMRARC,   *PEMRARC,
    EMRARCTO, *PEMRARCTO,
    EMRCHORD, *PEMRCHORD,
    EMRPIE,   *PEMRPIE; 
 
typedef struct  _XFORM
{
  FLOAT   eM11;
  FLOAT   eM12;
  FLOAT   eM21;
  FLOAT   eM22;
  FLOAT   eDx;
  FLOAT   eDy;
} XFORM, *PXFORM, *LPXFORM;

typedef struct tagEMRBITBLT
{
  EMR      emr; 
  RECTL    rclBounds; 
  LONG     xDest; 
  LONG     yDest; 
  LONG     cxDest; 
  LONG     cyDest; 
  DWORD    dwRop; 
  LONG     xSrc; 
  LONG     ySrc; 
  XFORM    xformSrc; 
  COLORREF crBkColorSrc; 
  DWORD    iUsageSrc; 
  DWORD    offBmiSrc; 
  DWORD    offBitsSrc; 
  DWORD    cbBitsSrc; 
} EMRBITBLT, *PEMRBITBLT; 
 
typedef struct tagLOGBRUSH { 
  UINT     lbStyle; 
  COLORREF lbColor; 
  LONG     lbHatch; 
} LOGBRUSH; 
 
typedef struct tagEMRCREATEBRUSHINDIRECT
{
  EMR      emr; 
  DWORD    ihBrush; 
  LOGBRUSH lb; 
} EMRCREATEBRUSHINDIRECT, *PEMRCREATEBRUSHINDIRECT; 
 
typedef LONG LCSCSTYPE;
typedef LONG LCSGAMUTMATCH;

typedef struct tagLOGCOLORSPACE {
  DWORD         lcsSignature; 
  DWORD         lcsVersion; 
  DWORD         lcsSize; 

  LCSCSTYPE     lcsCSType; 
  LCSGAMUTMATCH lcsIntent; 
  CIEXYZTRIPLE  lcsEndpoints;
  DWORD         lcsGammaRed;
  DWORD         lcsGammaGreen; 
  DWORD         lcsGammaBlue;
  TCHAR         lcsFilename[(260) ]; 
} LOGCOLORSPACE, *LPLOGCOLORSPACE; 
 
typedef struct tagEMRCREATECOLORSPACE
{
  EMR           emr; 
  DWORD         ihCS; 
  LOGCOLORSPACE lcs; 
} EMRCREATECOLORSPACE, *PEMRCREATECOLORSPACE; 
 
typedef struct tagEMRCREATEDIBPATTERNBRUSHPT
{
  EMR   emr; 
  DWORD ihBrush; 
  DWORD iUsage; 
  DWORD offBmi; 
  DWORD cbBmi; 
  DWORD offBits; 
  DWORD cbBits; 
} EMRCREATEDIBPATTERNBRUSHPT, 
    PEMRCREATEDIBPATTERNBRUSHPT; 
 
typedef struct tagEMRCREATEMONOBRUSH
{
  EMR   emr; 
  DWORD ihBrush; 
  DWORD iUsage; 
  DWORD offBmi; 
  DWORD cbBmi; 
  DWORD offBits; 
  DWORD cbBits; 
} EMRCREATEMONOBRUSH, *PEMRCREATEMONOBRUSH; 
 
typedef struct tagPALETTEENTRY { 
  BYTE peRed; 
  BYTE peGreen; 
  BYTE peBlue; 
  BYTE peFlags; 
} PALETTEENTRY, *LPPALETTEENTRY, *PPALETTEENTRY; 
 
typedef struct tagLOGPALETTE { 
  WORD         palVersion; 
  WORD         palNumEntries; 
  PALETTEENTRY palPalEntry[1]; 
} LOGPALETTE, *LPLOGPALETTE, *PLOGPALETTE; 

typedef struct tagEMRCREATEPALETTE
{
  EMR        emr; 
  DWORD      ihPal; 
  LOGPALETTE lgpl; 
} EMRCREATEPALETTE, *PEMRCREATEPALETTE; 
 
typedef struct tagLOGPEN { 
  UINT     lopnStyle; 
  POINT    lopnWidth; 
  COLORREF lopnColor; 
} LOGPEN; 
 
typedef struct tagEMRCREATEPEN
{
  EMR    emr; 
  DWORD  ihPen; 
  LOGPEN lopn; 
} EMRCREATEPEN, *PEMRCREATEPEN; 
 
typedef struct tagEMRELLIPSE
{
  EMR   emr; 
  RECTL rclBox; 
} EMRELLIPSE,  *PEMRELLIPSE,
    EMRRECTANGLE, *PEMRRECTANGLE; 
 
typedef struct tagEMREOF
{
  EMR     emr;
  DWORD   nPalEntries; 
  DWORD   offPalEntries; 
  DWORD   nSizeLast; 
} EMREOF, *PEMREOF; 
 
typedef struct tagEMREXCLUDECLIPRECT
{
  EMR   emr;      
  RECTL rclClip;  
} EMREXCLUDECLIPRECT,   *PEMREXCLUDECLIPRECT,
    EMRINTERSECTCLIPRECT, *PEMRINTERSECTCLIPRECT; 
 
typedef struct tagPANOSE { 
  BYTE bFamilyType; 
  BYTE bSerifStyle; 
  BYTE bWeight; 
  BYTE bProportion; 
  BYTE bContrast; 
  BYTE bStrokeVariation; 
  BYTE bArmStyle; 
  BYTE bLetterform; 
  BYTE bMidline; 
  BYTE bXHeight; 
} PANOSE; 

typedef struct tagEXTLOGFONT { 
    LOGFONT elfLogFont; 
    BCHAR    elfFullName[(64) ]; 
    BCHAR    elfStyle[(32) ]; 
    DWORD   elfVersion; 
    DWORD   elfStyleSize; 
    DWORD   elfMatch; 
    DWORD   elfReserved; 
    BYTE    elfVendorId[(4) ]; 
    DWORD   elfCulture; 
    PANOSE  elfPanose; 
} EXTLOGFONT; 
 
typedef struct tagEMREXTCREATEFONTINDIRECTW
{
  EMR         emr; 
  DWORD       ihFont; 
  EXTLOGFONT  elfw; 
} EMREXTCREATEFONTINDIRECTW, 
    PEMREXTCREATEFONTINDIRECTW; 
 
typedef struct tagEXTLOGPEN { 
  UINT     elpPenStyle; 
  UINT     elpWidth; 
  UINT     elpBrushStyle; 
  COLORREF elpColor; 
  LONG     elpHatch; 
  DWORD    elpNumEntries; 
  DWORD    elpStyleEntry[1]; 
} EXTLOGPEN; 
 
typedef struct tagEMREXTCREATEPEN
{
  EMR       emr; 
  DWORD     ihPen; 
  DWORD     offBmi; 
  DWORD     cbBmi; 
  DWORD     offBits; 
  DWORD     cbBits; 
  EXTLOGPEN elp; 
} EMREXTCREATEPEN, *PEMREXTCREATEPEN; 
 
typedef struct tagEMREXTFLOODFILL
{
  EMR     emr; 
  POINTL  ptlStart; 
  COLORREF crColor; 
  DWORD   iMode; 
} EMREXTFLOODFILL, *PEMREXTFLOODFILL; 
 
typedef struct tagEMREXTSELECTCLIPRGN
{
  EMR   emr; 
  DWORD cbRgnData; 
  DWORD iMode; 
  BYTE  RgnData[1]; 
} EMREXTSELECTCLIPRGN, *PEMREXTSELECTCLIPRGN; 
 
typedef struct tagEMRTEXT 
{
  POINTL ptlReference; 
  DWORD  nChars; 
  DWORD  offString; 
  DWORD  fOptions; 
  RECTL  rcl; 
  DWORD  offDx; 
} EMRTEXT, *PEMRTEXT; 
 
typedef struct tagEMREXTTEXTOUTA
{
  EMR     emr; 
  RECTL   rclBounds; 
  DWORD   iGraphicsMode; 
  FLOAT   exScale; 
  FLOAT   eyScale;
  EMRTEXT emrtext; 
} EMREXTTEXTOUTA, *PEMREXTTEXTOUTA,
    EMREXTTEXTOUTW, *PEMREXTTEXTOUTW; 
 
typedef struct tagEMRFILLPATH
{
  EMR   emr; 
  RECTL rclBounds; 
} EMRFILLPATH,          *PEMRFILLPATH,
    EMRSTROKEANDFILLPATH, *PEMRSTROKEANDFILLPATH,
    EMRSTROKEPATH,        *PEMRSTROKEPATH; 
 
typedef struct tagEMRFILLRGN
{
  EMR   emr; 
  RECTL rclBounds; 
  DWORD cbRgnData; 
  DWORD ihBrush; 
  BYTE  RgnData[1]; 
} EMRFILLRGN, *PEMRFILLRGN; 
 
typedef struct tagEMRFORMAT { 
  DWORD   dSignature; 
  DWORD   nVersion; 
  DWORD   cbData; 
  DWORD   offData; 
} EMRFORMAT; 
 
typedef struct tagSIZE { 
  LONG cx; 
  LONG cy; 
} SIZE, *PSIZE, *LPSIZE, SIZEL, *PSIZEL, *LPSIZEL; 
 
typedef struct tagEMRFRAMERGN
{
  EMR   emr; 
  RECTL rclBounds; 
  DWORD cbRgnData; 
  DWORD ihBrush; 
  SIZEL szlStroke; 
  BYTE  RgnData[1]; 
} EMRFRAMERGN, *PEMRFRAMERGN; 

typedef struct tagEMRGDICOMMENT
{
  EMR   emr; 
  DWORD cbData; 
  BYTE  Data[1]; 
} EMRGDICOMMENT, *PEMRGDICOMMENT; 
 
typedef struct tagEMRINVERTRGN
{
  EMR   emr; 
  RECTL rclBounds; 
  DWORD cbRgnData; 
  BYTE  RgnData[1]; 
} EMRINVERTRGN, *PEMRINVERTRGN,
    EMRPAINTRGN,  *PEMRPAINTRGN; 
 
typedef struct tagEMRLINETO
{
  EMR    emr; 
  POINTL ptl; 
} EMRLINETO,   *PEMRLINETO,
    EMRMOVETOEX, *PEMRMOVETOEX; 
 
typedef struct tagEMRMASKBLT
{
  EMR     emr; 
  RECTL   rclBounds; 
  LONG    xDest; 
  LONG    yDest; 
  LONG    cxDest; 
  LONG    cyDest; 
  DWORD   dwRop; 
  LONG    xSrc; 
  LONG    ySrc; 
  XFORM   xformSrc; 
  COLORREF crBkColorSrc; 
  DWORD   iUsageSrc; 
  DWORD   offBmiSrc; 
  DWORD   cbBmiSrc; 
  DWORD   offBitsSrc; 
  DWORD   cbBitsSrc; 
  LONG    xMask; 
  LONG    yMask; 
  DWORD   iUsageMask; 
  DWORD   offBmiMask; 
  DWORD   cbBmiMask; 
  DWORD   offBitsMask; 
  DWORD   cbBitsMask; 
} EMRMASKBLT, *PEMRMASKBLT; 
 
typedef struct tagEMRMODIFYWORLDTRANSFORM
{
  EMR   emr; 
  XFORM xform; 
  DWORD iMode; 
} EMRMODIFYWORLDTRANSFORM, 
    PEMRMODIFYWORLDTRANSFORM; 
 
typedef struct tagEMROFFSETCLIPRGN
{
  EMR    emr; 
  POINTL ptlOffset; 
} EMROFFSETCLIPRGN, *PEMROFFSETCLIPRGN; 
 
typedef struct tagEMRPLGBLT
{
  EMR      emr; 
  RECTL    rclBounds; 
  POINTL   aptlDest[3]; 
  LONG    xSrc; 
  LONG    ySrc; 
  LONG     cxSrc; 
  LONG     cySrc; 
  XFORM   xformSrc; 
  COLORREF crBkColorSrc; 
  DWORD    iUsageSrc; 
  DWORD    offBmiSrc; 
  DWORD   cbBmiSrc; 
  DWORD   offBitsSrc; 
  DWORD   cbBitsSrc; 
  LONG    xMask;
  LONG    yMask; 
  DWORD   iUsageMask; 
  DWORD   offBmiMask; 
  DWORD   cbBmiMask;
  DWORD   offBitsMask;
  DWORD   cbBitsMask;
} EMRPLGBLT, *PEMRPLGBLT; 
 
typedef struct tagEMRPOLYDRAW
{
  EMR    emr; 
  RECTL  rclBounds; 
  DWORD  cptl; 
  POINTL aptl[1]; 
  BYTE   abTypes[1]; 
} EMRPOLYDRAW, *PEMRPOLYDRAW; 
 
typedef struct tagEMRPOLYDRAW16
{
  EMR    emr; 
  RECTL  rclBounds; 
  DWORD  cpts; 
  POINTS apts[1]; 
  BYTE   abTypes[1]; 
} EMRPOLYDRAW16, *PEMRPOLYDRAW16; 
 
typedef struct tagEMRPOLYLINE
{
  EMR    emr;
  RECTL  rclBounds; 
  DWORD  cptl; 
  POINTL aptl[1]; 
} EMRPOLYLINE,     *PEMRPOLYLINE,
    EMRPOLYBEZIER,   *PEMRPOLYBEZIER,
    EMRPOLYGON,      *PEMRPOLYGON,
    EMRPOLYBEZIERTO, *PEMRPOLYBEZIERTO,
    EMRPOLYLINETO,   *PEMRPOLYLINETO; 
 
typedef struct tagEMRPOLYLINE16
{
  EMR    emr; 
  RECTL  rclBounds; 
  DWORD  cpts; 
  POINTL apts[1]; 
} EMRPOLYLINE16,     *PEMRPOLYLINE16,
    EMRPOLYBEZIER16,   *PEMRPOLYBEZIER16,
    EMRPOLYGON16,      *PEMRPOLYGON16,
    EMRPOLYBEZIERTO16, *PEMRPOLYBEZIERTO16,
    EMRPOLYLINETO16,   *PEMRPOLYLINETO16; 
 
typedef struct tagEMRPOLYPOLYLINE
{
  EMR     emr; 
  RECTL   rclBounds; 
  DWORD   nPolys; 
  DWORD   cptl; 
  DWORD   aPolyCounts[1]; 
  POINTL  aptl[1]; 
} EMRPOLYPOLYLINE, *PEMRPOLYPOLYLINE,
    EMRPOLYPOLYGON,  *PEMRPOLYPOLYGON; 
 
typedef struct tagEMRPOLYPOLYLINE16
{
  EMR     emr; 
  RECTL   rclBounds;
  DWORD   nPolys; 
  DWORD   cpts; 
  DWORD   aPolyCounts[1]; 
  POINTS  apts[1]; 
} EMRPOLYPOLYLINE16, *PEMRPOLYPOLYLINE16,
    EMRPOLYPOLYGON16,  *PEMRPOLYPOLYGON16; 
 
typedef struct tagEMRPOLYTEXTOUTA
{
  EMR     emr; 
  RECTL   rclBounds; 
  DWORD   iGraphicsMode; 
  FLOAT   exScale; 
  FLOAT   eyScale; 
  LONG    cStrings; 
  EMRTEXT aemrtext[1]; 
} EMRPOLYTEXTOUTA, *PEMRPOLYTEXTOUTA,
    EMRPOLYTEXTOUTW, *PEMRPOLYTEXTOUTW; 
 
typedef struct tagEMRRESIZEPALETTE
{
  EMR   emr; 
  DWORD ihPal; 
  DWORD cEntries; 
} EMRRESIZEPALETTE, *PEMRRESIZEPALETTE; 
 
typedef struct tagEMRRESTOREDC
{
  EMR  emr; 
  LONG iRelative; 
} EMRRESTOREDC, *PEMRRESTOREDC; 
 
typedef struct tagEMRROUNDRECT
{
  EMR   emr; 
  RECTL rclBox; 
  SIZEL szlCorner; 
} EMRROUNDRECT, *PEMRROUNDRECT; 
 
typedef struct tagEMRSCALEVIEWPORTEXTEX
{
  EMR  emr; 
  LONG xNum; 
  LONG xDenom; 
  LONG yNum; 
  LONG yDenom; 
} EMRSCALEVIEWPORTEXTEX, *PEMRSCALEVIEWPORTEXTEX, 
    EMRSCALEWINDOWEXTEX,   *PEMRSCALEWINDOWEXTEX; 
 
typedef struct tagEMRSELECTCOLORSPACE 
{ 
  EMR     emr; 
  DWORD   ihCS; 
} EMRSELECTCOLORSPACE, *PEMRSELECTCOLORSPACE,
    EMRDELETECOLORSPACE, *PEMRDELETECOLORSPACE; 
typedef struct tagEMRSELECTOBJECT
{
  EMR   emr; 
  DWORD ihObject;
} EMRSELECTOBJECT, *PEMRSELECTOBJECT,
    EMRDELETEOBJECT, *PEMRDELETEOBJECT; 
 
typedef struct tagEMRSELECTPALETTE 
{
  EMR   emr; 
  DWORD ihPal; 
} EMRSELECTPALETTE, *PEMRSELECTPALETTE; 
 
typedef struct tagEMRSETARCDIRECTION
{
  EMR   emr; 
  DWORD iArcDirection;
} EMRSETARCDIRECTION, *PEMRSETARCDIRECTION; 
 
typedef struct tagEMRSETTEXTCOLOR
{
  EMR      emr; 
  COLORREF crColor; 
} EMRSETBKCOLOR,   *PEMRSETBKCOLOR,
    EMRSETTEXTCOLOR, *PEMRSETTEXTCOLOR; 
 
typedef struct tagEMRSETCOLORADJUSTMENT
{
  EMR  emr; 
  COLORADJUSTMENT ColorAdjustment; 
} EMRSETCOLORADJUSTMENT, *PEMRSETCOLORADJUSTMENT; 
 
typedef struct tagEMRSETDIBITSTODEVICE
{
  EMR   emr; 
  RECTL rclBounds; 
  LONG  xDest; 
  LONG  yDest; 
  LONG  xSrc; 
  LONG  ySrc; 
  LONG  cxSrc; 
  LONG  cySrc; 
  DWORD offBmiSrc; 
  DWORD cbBmiSrc; 
  DWORD offBitsSrc; 
  DWORD cbBitsSrc; 
  DWORD iUsageSrc; 
  DWORD iStartScan; 
  DWORD cScans; 
} EMRSETDIBITSTODEVICE, *PEMRSETDIBITSTODEVICE; 
 
typedef struct tagEMRSETMAPPERFLAGS
{
  EMR   emr; 
  DWORD dwFlags; 
} EMRSETMAPPERFLAGS, *PEMRSETMAPPERFLAGS; 
 
typedef struct tagEMRSETMITERLIMIT
{
  EMR   emr;
  FLOAT eMiterLimit; 
} EMRSETMITERLIMIT, *PEMRSETMITERLIMIT; 
 
typedef struct tagEMRSETPALETTEENTRIES
{
  EMR          emr; 
  DWORD        ihPal; 
  DWORD        iStart; 
  DWORD        cEntries; 
  PALETTEENTRY aPalEntries[1]; 
} EMRSETPALETTEENTRIES, *PEMRSETPALETTEENTRIES; 
 
typedef struct tagEMRSETPIXELV
{
  EMR     emr; 
  POINTL  ptlPixel; 
  COLORREF crColor; 
} EMRSETPIXELV, *PEMRSETPIXELV; 
 
typedef struct tagEMRSETVIEWPORTEXTEX
{
  EMR   emr; 
  SIZEL szlExtent; 
} EMRSETVIEWPORTEXTEX, *PEMRSETVIEWPORTEXTEX,
    EMRSETWINDOWEXTEX,   *PEMRSETWINDOWEXTEX; 
 
typedef struct tagEMRSETVIEWPORTORGEX
{
  EMR    emr; 
  POINTL ptlOrigin; 
} EMRSETVIEWPORTORGEX, *PEMRSETVIEWPORTORGEX,
    EMRSETWINDOWORGEX,   *PEMRSETWINDOWORGEX,
    EMRSETBRUSHORGEX,    *PEMRSETBRUSHORGEX; 
 
typedef struct tagEMRSETWORLDTRANSFORM
{
  EMR   emr; 
  XFORM xform; 
} EMRSETWORLDTRANSFORM, *PEMRSETWORLDTRANSFORM; 
 
typedef struct tagEMRSTRETCHBLT
{
  EMR      emr; 
  RECTL    rclBounds; 
  LONG     xDest; 
  LONG     yDest; 
  LONG     cxDest; 
  LONG     cyDest; 
  DWORD    dwRop; 
  LONG     xSrc; 
  LONG     ySrc; 
  XFORM    xformSrc; 
  COLORREF crBkColorSrc; 
  DWORD    iUsageSrc; 
  DWORD    offBmiSrc; 
  DWORD    cbBmiSrc; 
  DWORD    offBitsSrc; 
  DWORD    cbBitsSrc; 
  LONG     cxSrc; 
  LONG     cySrc; 
} EMRSTRETCHBLT, *PEMRSTRETCHBLT; 
 
typedef struct tagEMRSTRETCHDIBITS
{
  EMR   emr;
  RECTL rclBounds; 
  LONG  xDest; 
  LONG  yDest; 
  LONG  xSrc; 
  LONG  ySrc; 
  LONG  cxSrc; 
  LONG  cySrc;
  DWORD offBmiSrc;
  DWORD cbBmiSrc; 
  DWORD offBitsSrc; 
  DWORD cbBitsSrc; 
  DWORD iUsageSrc; 
  DWORD dwRop; 
  LONG  cxDest; 
  LONG  cyDest; 
} EMRSTRETCHDIBITS, *PEMRSTRETCHDIBITS; 
 
typedef struct tagABORTPATH 
{ 
  EMR emr; 
} EMRABORTPATH,      *PEMRABORTPATH,
    EMRBEGINPATH,      *PEMRBEGINPATH,
    EMRENDPATH,        *PEMRENDPATH,
    EMRCLOSEFIGURE,    *PEMRCLOSEFIGURE,
    EMRFLATTENPATH,    *PEMRFLATTENPATH,
    EMRWIDENPATH,      *PEMRWIDENPATH,
    EMRSETMETARGN,     *PEMRSETMETARGN,
    EMRSAVEDC,         *PEMRSAVEDC,
    EMRREALIZEPALETTE, *PEMRREALIZEPALETTE;
 
typedef struct tagEMRSELECTCLIPPATH
{
  EMR   emr; 
  DWORD iMode; 
} EMRSELECTCLIPPATH,    *PEMRSELECTCLIPPATH,
    EMRSETBKMODE,         *PEMRSETBKMODE,
    EMRSETMAPMODE,        *PEMRSETMAPMODE,
    EMRSETPOLYFILLMODE,   *PEMRSETPOLYFILLMODE,
    EMRSETROP2,           *PEMRSETROP2,
    EMRSETSTRETCHBLTMODE, *PEMRSETSTRETCHBLTMODE,
    EMRSETTEXTALIGN,      *PEMRSETTEXTALIGN,
    EMRENABLEICM,       *PEMRENABLEICM;
 
typedef struct tagNMHDR { 
  HWND hwndFrom; 
  UINT idFrom; 
  UINT code; 
} NMHDR; 
 
typedef struct _encorrecttext { 
  NMHDR nmhdr;     
  CHARRANGE chrg;  
  WORD seltyp;     
} ENCORRECTTEXT; 
 
typedef struct _endropfiles { 
  NMHDR nmhdr; 
  HANDLE hDrop; 
  LONG cp; 
  WINBOOL fProtected; 
} ENDROPFILES; 
 
typedef struct {
  NMHDR nmhdr;        
  LONG cObjectCount;  
  LONG cch;           
} ENSAVECLIPBOARD;

typedef struct {
  NMHDR nmhdr;  
  LONG iob;     
  LONG lOper;   
  HRESULT hr;   
} ENOLEOPFAILED;

typedef struct tagENHMETAHEADER { 
  DWORD iType; 
  DWORD nSize; 
  RECTL rclBounds; 
  RECTL rclFrame; 
  DWORD dSignature; 
  DWORD nVersion; 
  DWORD nBytes; 
  DWORD nRecords; 
  WORD  nHandles; 
  WORD  sReserved; 
  DWORD nDescription; 
  DWORD offDescription; 
  DWORD nPalEntries; 
  SIZEL szlDevice; 
  SIZEL szlMillimeters; 
} ENHMETAHEADER, *LPENHMETAHEADER; 
 
typedef struct tagENHMETARECORD { 
  DWORD iType; 
  DWORD nSize; 
  DWORD dParm[1]; 
} ENHMETARECORD, *PENHMETARECORD, *LPENHMETARECORD; 
 
typedef struct _enprotected { 
  NMHDR nmhdr; 
  UINT msg; 
  WPARAM wParam; 
  LPARAM lParam; 
  CHARRANGE chrg; 
} ENPROTECTED; 
 
typedef struct _SERVICE_STATUS {
  DWORD dwServiceType; 
  DWORD dwCurrentState; 
  DWORD dwControlsAccepted; 
  DWORD dwWin32ExitCode; 
  DWORD dwServiceSpecificExitCode; 
  DWORD dwCheckPoint; 
  DWORD dwWaitHint; 
} SERVICE_STATUS, *LPSERVICE_STATUS; 
 
typedef struct _ENUM_SERVICE_STATUS { 
  LPTSTR lpServiceName; 
  LPTSTR lpDisplayName; 
  SERVICE_STATUS ServiceStatus; 
} ENUM_SERVICE_STATUS, *LPENUM_SERVICE_STATUS; 
 
typedef struct tagENUMLOGFONT { 
  LOGFONT elfLogFont; 
  BCHAR    elfFullName[(64) ]; 
  BCHAR    elfStyle[(32) ]; 
} ENUMLOGFONT; 
 
typedef struct tagENUMLOGFONTEX {
  LOGFONT  elfLogFont;
  BCHAR  elfFullName[(64) ];
  BCHAR  elfStyle[(32) ];
  BCHAR  elfScript[(32) ];
} ENUMLOGFONTEX;
 
typedef struct _EVENTLOGRECORD {
  DWORD  Length; 
  DWORD  Reserved; 
  DWORD  RecordNumber; 
  DWORD  TimeGenerated; 
  DWORD  TimeWritten; 
  DWORD  EventID; 
  WORD   EventType; 
  WORD   NumStrings; 
  WORD   EventCategory; 
  WORD   ReservedFlags; 
  DWORD  ClosingRecordNumber; 
  DWORD  StringOffset; 
  DWORD  UserSidLength; 
  DWORD  UserSidOffset; 
  DWORD  DataLength; 
  DWORD  DataOffset; 

 










  
} EVENTLOGRECORD; 
 
typedef struct tagEVENTMSG {
  UINT  message; 
  UINT  paramL; 
  UINT  paramH; 
  DWORD time; 
  HWND  hwnd; 
} EVENTMSG; 
 
typedef struct _EXCEPTION_POINTERS { 
  PEXCEPTION_RECORD ExceptionRecord; 
  PCONTEXT ContextRecord; 
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS, *LPEXCEPTION_POINTERS; 
 
typedef struct _EXT_BUTTON { 
  WORD idCommand; 
  WORD idsHelp; 
  WORD fsStyle; 
} EXT_BUTTON, *LPEXT_BUTTON; 
 
typedef struct tagFILTERKEYS {   
  UINT  cbSize; 
  DWORD dwFlags; 
  DWORD iWaitMSec; 
  DWORD iDelayMSec; 
  DWORD iRepeatMSec; 
  DWORD iBounceMSec; 
} FILTERKEYS; 
 
typedef struct _FIND_NAME_BUFFER { 
  UCHAR length; 
  UCHAR access_control; 
  UCHAR frame_control; 
  UCHAR destination_addr[6]; 
  UCHAR source_addr[6]; 
  UCHAR routing_info[18]; 
} FIND_NAME_BUFFER; 
 
typedef struct _FIND_NAME_HEADER { 
  WORD  node_count; 
  UCHAR reserved; 
  UCHAR unique_group; 
} FIND_NAME_HEADER; 
 
typedef struct {   
  DWORD        lStructSize; 
  HWND         hwndOwner; 
  HINSTANCE    hInstance; 
  DWORD        Flags; 
  LPTSTR        lpstrFindWhat; 
  LPTSTR        lpstrReplaceWith; 
  WORD         wFindWhatLen; 
  WORD         wReplaceWithLen; 
  LPARAM        lCustData; 
  LPFRHOOKPROC lpfnHook; 
  LPCTSTR       lpTemplateName; 
} FINDREPLACE, *LPFINDREPLACE; 
 
typedef struct _findtext { 
  CHARRANGE chrg; 
  LPSTR lpstrText; 
} FINDTEXT; 
 
typedef struct _findtextex { 
  CHARRANGE chrg;  
  LPSTR lpstrText; 
  CHARRANGE chrgText; 
} FINDTEXTEX; 
 
typedef struct _FMS_GETDRIVEINFO { 
  DWORD dwTotalSpace; 
  DWORD dwFreeSpace; 
  TCHAR  szPath[260]; 
  TCHAR  szVolume[14]; 
  TCHAR  szShare[128]; 
} FMS_GETDRIVEINFO; 
 
typedef struct _FMS_GETFILESEL { 
  FILETIME ftTime; 
  DWORD    dwSize; 
  BYTE     bAttr; 
  TCHAR     szName[260]; 
} FMS_GETFILESEL; 
 
typedef struct _FMS_LOAD { 
  DWORD dwSize; 
  TCHAR  szMenuName[(40) ]; 
  HMENU hMenu; 
  UINT  wMenuDelta; 
} FMS_LOAD; 
 
typedef struct _FMS_TOOLBARLOAD { 
  DWORD        dwSize; 
  LPEXT_BUTTON lpButtons; 
  WORD         cButtons; 
  WORD         cBitmaps; 
  WORD         idBitmap; 
  HBITMAP      hBitmap; 
} FMS_TOOLBARLOAD; 
 
typedef struct _FOCUS_EVENT_RECORD { 
  WINBOOL bSetFocus; 
} FOCUS_EVENT_RECORD; 
 
typedef struct _FORM_INFO_1 { 
  DWORD Flags; 
  LPTSTR pName; 
  SIZEL  Size; 
  RECTL  ImageableArea; 
} FORM_INFO_1; 
 
typedef struct _FORMAT_PARAMETERS { 
  MEDIA_TYPE MediaType; 
  DWORD StartCylinderNumber; 
  DWORD EndCylinderNumber; 
  DWORD StartHeadNumber; 
  DWORD EndHeadNumber; 
} FORMAT_PARAMETERS ; 
 
typedef struct _formatrange { 
  HDC hdc; 
  HDC hdcTarget; 
  RECT rc; 
  RECT rcPage; 
  CHARRANGE chrg; 
} FORMATRANGE;       
 
typedef struct tagGCP_RESULTS {
  DWORD  lStructSize;
  LPTSTR  lpOutString;
  UINT  *lpOrder;
  INT  *lpDx;
  INT  *lpCaretPos;
  LPTSTR lpClass;
  UINT  *lpGlyphs;
  UINT  nGlyphs;
  UINT  nMaxFit;
} GCP_RESULTS, *LPGCP_RESULTS;
 
typedef struct _GENERIC_MAPPING { 
  ACCESS_MASK GenericRead; 
  ACCESS_MASK GenericWrite; 
  ACCESS_MASK GenericExecute; 
  ACCESS_MASK GenericAll; 
} GENERIC_MAPPING, *PGENERIC_MAPPING; 
 
typedef struct _GLYPHMETRICS { 
  UINT  gmBlackBoxX; 
  UINT  gmBlackBoxY; 
  POINT gmptGlyphOrigin; 
  short gmCellIncX; 
  short gmCellIncY; 
} GLYPHMETRICS, *LPGLYPHMETRICS; 
 
typedef struct tagHANDLETABLE { 
  HGDIOBJ objectHandle[1]; 
} HANDLETABLE, *LPHANDLETABLE; 

typedef struct _HD_HITTESTINFO { 
  POINT pt; 
  UINT flags; 
  int iItem; 
} HD_HITTESTINFO; 
 
typedef struct _HD_ITEM { 
  UINT    mask; 
  int     cxy; 
  LPTSTR   pszText; 
  HBITMAP hbm; 
  int     cchTextMax; 
  int     fmt; 
  LPARAM  lParam; 
} HD_ITEM; 
 
typedef struct _WINDOWPOS { 
  HWND hwnd; 
  HWND hwndInsertAfter; 
  int  x; 
  int  y; 
  int  cx; 
  int  cy; 
  UINT flags; 
} WINDOWPOS, *PWINDOWPOS, *LPWINDOWPOS; 
 
typedef struct _HD_LAYOUT { 
  RECT  * prc; 
  WINDOWPOS  * pwpos; 
} HD_LAYOUT; 
 
typedef struct _HD_NOTIFY { 
  NMHDR   hdr; 
  int     iItem; 
  int     iButton; 
  HD_ITEM  * pitem; 
} HD_NOTIFY; 
 
typedef  struct  tagHELPINFO { 
  UINT   cbSize; 
  int    iContextType; 
  int    iCtrlId; 
  HANDLE hItemHandle; 
  DWORD  dwContextId; 
  POINT  MousePos; 
} HELPINFO,   *LPHELPINFO; 
 
typedef struct {   
  int   wStructSize; 
  int   x; 
  int   y; 
  int   dx; 
  int   dy; 
  int   wMax; 
  TCHAR rgchMember[2]; 
} HELPWININFO; 
 
typedef struct tagHIGHCONTRAST {  
  UINT cbSize; 
  DWORD dwFlags; 
  LPTSTR lpszDefaultScheme; 
} HIGHCONTRAST,  * LPHIGHCONTRAST; 
 
typedef struct tagHSZPAIR { 
  HSZ hszSvc; 
  HSZ hszTopic; 
} HSZPAIR; 
 
typedef struct _ICONINFO { 
  WINBOOL    fIcon; 
  DWORD   xHotspot; 
  DWORD   yHotspot; 
  HBITMAP hbmMask; 
  HBITMAP hbmColor; 
} ICONINFO, *PICONINFO; 
 
typedef struct tagICONMETRICS { 
  UINT    cbSize; 
  int     iHorzSpacing; 
  int     iVertSpacing; 
  int     iTitleWrap; 
  LOGFONT lfFont; 
} ICONMETRICS,   *LPICONMETRICS; 
 
typedef struct _IMAGEINFO { 
  HBITMAP hbmImage; 
  HBITMAP hbmMask;  
  int     Unused1;  
  int     Unused2;  
  RECT    rcImage;  
} IMAGEINFO; 
 
typedef struct _KEY_EVENT_RECORD { 
  WINBOOL bKeyDown;             
  WORD wRepeatCount;         
  WORD wVirtualKeyCode;      
  WORD wVirtualScanCode; 

  char AsciiChar;
  char pad;






  DWORD dwControlKeyState;   
} __attribute__((packed))  KEY_EVENT_RECORD; 
 
typedef struct _MOUSE_EVENT_RECORD { 
  COORD dwMousePosition; 
  DWORD dwButtonState; 
  DWORD dwControlKeyState; 
  DWORD dwEventFlags; 
} MOUSE_EVENT_RECORD; 
 
typedef struct _WINDOW_BUFFER_SIZE_RECORD { 
  COORD dwSize; 
} WINDOW_BUFFER_SIZE_RECORD; 
 
typedef struct _MENU_EVENT_RECORD { 
  UINT dwCommandId; 
} MENU_EVENT_RECORD, *PMENU_EVENT_RECORD; 
 
typedef struct _INPUT_RECORD { 
  WORD EventType; 
  union { 

     
    KEY_EVENT_RECORD KeyEvent; 

    MOUSE_EVENT_RECORD MouseEvent; 
    WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent; 
    MENU_EVENT_RECORD MenuEvent; 
    FOCUS_EVENT_RECORD FocusEvent; 
  } Event; 
} INPUT_RECORD, *PINPUT_RECORD; 
 
typedef struct _SYSTEMTIME {  
  WORD wYear; 
  WORD wMonth; 
  WORD wDayOfWeek; 
  WORD wDay; 
  WORD wHour; 
  WORD wMinute; 
  WORD wSecond; 
  WORD wMilliseconds; 
} SYSTEMTIME, *LPSYSTEMTIME; 
 
typedef struct _JOB_INFO_1 {  
  DWORD  JobId; 
  LPTSTR pPrinterName; 
  LPTSTR pMachineName; 
  LPTSTR pUserName; 
  LPTSTR pDocument; 
  LPTSTR pDatatype; 
  LPTSTR pStatus; 
  DWORD  Status; 
  DWORD  Priority; 
  DWORD  Position; 
  DWORD  TotalPages; 
  DWORD  PagesPrinted; 
  SYSTEMTIME Submitted; 
} JOB_INFO_1; 
 
typedef struct _SID_IDENTIFIER_AUTHORITY { 
  BYTE Value[6]; 
} SID_IDENTIFIER_AUTHORITY, *PSID_IDENTIFIER_AUTHORITY, 
    *LPSID_IDENTIFIER_AUTHORITY; 
 
typedef struct _SID {
   BYTE  Revision;
   BYTE  SubAuthorityCount;
   SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
   DWORD SubAuthority[(1) ];
} SID, *PSID;

typedef WORD SECURITY_DESCRIPTOR_CONTROL, *PSECURITY_DESCRIPTOR_CONTROL;

typedef struct _SECURITY_DESCRIPTOR {
  BYTE  Revision;
  BYTE  Sbz1;
  SECURITY_DESCRIPTOR_CONTROL Control;
  PSID Owner;
  PSID Group;
  PACL Sacl;
  PACL Dacl;
} SECURITY_DESCRIPTOR, *PSECURITY_DESCRIPTOR;
 
typedef struct _JOB_INFO_2 { 
  DWORD      JobId; 
  LPTSTR     pPrinterName; 
  LPTSTR     pMachineName; 
  LPTSTR     pUserName; 
  LPTSTR     pDocument; 
  LPTSTR     pNotifyName; 
  LPTSTR     pDatatype; 
  LPTSTR     pPrintProcessor; 
  LPTSTR     pParameters; 
  LPTSTR     pDriverName; 
  LPDEVMODE  pDevMode; 
  LPTSTR     pStatus; 
  PSECURITY_DESCRIPTOR pSecurityDescriptor; 
  DWORD      Status; 
  DWORD      Priority; 
  DWORD      Position; 
  DWORD      StartTime; 
  DWORD      UntilTime; 
  DWORD      TotalPages; 
  DWORD      Size; 
  SYSTEMTIME Submitted; 
  DWORD      Time; 
  DWORD      PagesPrinted ; 
} JOB_INFO_2; 
 
typedef struct tagKERNINGPAIR { 
  WORD wFirst; 
  WORD wSecond; 
  int  iKernAmount; 
} KERNINGPAIR, *LPKERNINGPAIR; 
 
typedef struct _LANA_ENUM { 
  UCHAR length; 
  UCHAR lana[(254) ]; 
} LANA_ENUM; 
 
typedef struct _LDT_ENTRY { 
  WORD LimitLow; 
  WORD BaseLow; 
  union { 
    struct { 
      BYTE BaseMid; 
      BYTE Flags1; 
      BYTE Flags2; 
      BYTE BaseHi; 
    } Bytes; 
    struct { 
      DWORD BaseMid : 8; 
      DWORD Type : 5; 
      DWORD Dpl : 2; 
      DWORD Pres : 1; 
      DWORD LimitHi : 4; 
      DWORD Sys : 1; 
      DWORD Reserved_0 : 1; 
      DWORD Default_Big : 1; 
      DWORD Granularity : 1; 
      DWORD BaseHi : 8; 
    } Bits; 
  } HighWord; 
} LDT_ENTRY, *PLDT_ENTRY, *LPLDT_ENTRY; 
 
typedef struct tagLOCALESIGNATURE {
  DWORD  lsUsb[4];
  DWORD  lsCsbDefault[2];
  DWORD  lsCsbSupported[2];
} LOCALESIGNATURE; 
 
typedef struct _LOCALGROUP_MEMBERS_INFO_0 {  
  PSID  lgrmi0_sid; 
} LOCALGROUP_MEMBERS_INFO_0; 
 
typedef struct _LOCALGROUP_MEMBERS_INFO_3 {  
  LPWSTR  lgrmi3_domainandname; 
} LOCALGROUP_MEMBERS_INFO_3; 
 
typedef long FXPT16DOT16,  * LPFXPT16DOT16; 

typedef LARGE_INTEGER LUID, *PLUID;

typedef struct _LUID_AND_ATTRIBUTES { 
  LUID  Luid; 
  DWORD Attributes; 
} LUID_AND_ATTRIBUTES; 
 
typedef LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES_ARRAY[(1) ];
typedef LUID_AND_ATTRIBUTES_ARRAY *PLUID_AND_ATTRIBUTES_ARRAY;

typedef struct _LV_COLUMN { 
  UINT mask;       
  int fmt;         
  int cx;          
  LPTSTR pszText;  
  int cchTextMax;  
  int iSubItem;    
} LV_COLUMN; 
 
typedef struct _LV_ITEM { 
  UINT   mask;         
  int    iItem;        
  int    iSubItem;     
  UINT   state;        
  UINT   stateMask;    
  LPTSTR  pszText;     
  int    cchTextMax;   
  int    iImage;      
  LPARAM lParam;      
} LV_ITEM; 
 
typedef struct tagLV_DISPINFO { 
  NMHDR   hdr;   
  LV_ITEM item;  
} LV_DISPINFO; 
 
typedef struct _LV_FINDINFO { 
  UINT flags;        
  LPCTSTR psz;        
  LPARAM lParam;     
  POINT pt;          
  UINT vkDirection;  
} LV_FINDINFO; 
 
typedef struct _LV_HITTESTINFO { 
  POINT pt;    
  UINT flags;  
  int iItem;   
} LV_HITTESTINFO; 
 
typedef struct tagLV_KEYDOWN { 
  NMHDR hdr;   
  WORD wVKey;  
  UINT flags;  
} LV_KEYDOWN; 
 
typedef struct _MAT2 { 
  FIXED eM11; 
  FIXED eM12; 
  FIXED eM21; 
  FIXED eM22; 
} MAT2; 
 
typedef struct tagMDICREATESTRUCT { 
  LPCTSTR szClass; 
  LPCTSTR szTitle; 
  HANDLE  hOwner; 
  int     x; 
  int     y; 
  int     cx; 
  int     cy; 
  DWORD   style; 
  LPARAM  lParam; 
} MDICREATESTRUCT; 

typedef MDICREATESTRUCT *LPMDICREATESTRUCT;
 
typedef struct tagMEASUREITEMSTRUCT { 
  UINT  CtlType;      
  UINT  CtlID;        
  UINT  itemID;       
  UINT  itemWidth;    
  UINT  itemHeight;   
  DWORD itemData;     
} MEASUREITEMSTRUCT, *LPMEASUREITEMSTRUCT; 
 
typedef struct _MEMORY_BASIC_INFORMATION { 
  PVOID BaseAddress;            
  PVOID AllocationBase;         
  DWORD AllocationProtect;      
  DWORD RegionSize;             
  DWORD State;                  
  DWORD Protect;                
  DWORD Type;                   
} MEMORY_BASIC_INFORMATION; 
typedef MEMORY_BASIC_INFORMATION *PMEMORY_BASIC_INFORMATION; 
 
typedef struct _MEMORYSTATUS { 
  DWORD dwLength;        
  DWORD dwMemoryLoad;    
  DWORD dwTotalPhys;     
  DWORD dwAvailPhys;     
  DWORD dwTotalPageFile; 
  DWORD dwAvailPageFile; 
  DWORD dwTotalVirtual;  
  DWORD dwAvailVirtual;  
} MEMORYSTATUS, *LPMEMORYSTATUS; 
 
typedef struct {
  WORD  wVersion; 
  WORD  wOffset; 
  DWORD dwHelpId; 
} MENUEX_TEMPLATE_HEADER;

typedef struct { 
  DWORD  dwType; 
  DWORD  dwState; 
  UINT   uId; 
  BYTE   bResInfo; 
  WCHAR  szText[1]; 
  DWORD dwHelpId; 
} MENUEX_TEMPLATE_ITEM; 

typedef struct tagMENUITEMINFO {
  UINT    cbSize; 
  UINT    fMask; 
  UINT    fType; 
  UINT    fState; 
  UINT    wID; 
  HMENU   hSubMenu; 
  HBITMAP hbmpChecked; 
  HBITMAP hbmpUnchecked; 
  DWORD   dwItemData; 
  LPTSTR  dwTypeData; 
  UINT    cch; 
} MENUITEMINFO, *LPMENUITEMINFO; 
typedef MENUITEMINFO const  *LPCMENUITEMINFO;
 
typedef struct {   
  WORD mtOption;      
  WORD mtID;          
  WCHAR mtString[1];  
} MENUITEMTEMPLATE; 
 
typedef struct {      
  WORD versionNumber; 
  WORD offset;        
} MENUITEMTEMPLATEHEADER; 
typedef void  MENUTEMPLATE, *LPMENUTEMPLATE;
 
typedef struct tagMETAFILEPICT { 
  LONG      mm; 
  LONG      xExt; 
  LONG      yExt; 
  HMETAFILE hMF; 
} METAFILEPICT, *PMETAFILEPICT, *LPMETAFILEPICT; 
 
typedef struct tagMETAHEADER {  
  WORD  mtType; 
  WORD  mtHeaderSize; 
  WORD  mtVersion; 
  DWORD mtSize; 
  WORD  mtNoObjects; 
  DWORD mtMaxRecord; 
  WORD  mtNoParameters; 
} __attribute__((packed))  METAHEADER; 
 
typedef struct tagMETARECORD {  
  DWORD rdSize; 
  WORD  rdFunction; 
  WORD  rdParm[1]; 
} METARECORD, *LPMETARECORD; 
 
typedef struct tagMINIMIZEDMETRICS { 
  UINT    cbSize; 
  int     iWidth; 
  int     iHorzGap; 
  int     iVertGap; 
  int     iArrange; 
}   MINIMIZEDMETRICS,   *LPMINIMIZEDMETRICS; 
 
typedef struct tagMINMAXINFO {  
  POINT ptReserved;         
  POINT ptMaxSize;          
  POINT ptMaxPosition;      
  POINT ptMinTrackSize;     
  POINT ptMaxTrackSize;     
} MINMAXINFO; 
 
typedef struct modemdevcaps_tag {
  DWORD dwActualSize;           
  DWORD dwRequiredSize;         
  DWORD dwDevSpecificOffset;    
  DWORD dwDevSpecificSize;      

  DWORD dwModemProviderVersion; 
  DWORD dwModemManufacturerOffset; 
  DWORD dwModemManufacturerSize;   
  DWORD dwModemModelOffset;        
  DWORD dwModemModelSize;          
  DWORD dwModemVersionOffset;      
  DWORD dwModemVersionSize;        

  DWORD dwDialOptions;             
  DWORD dwCallSetupFailTimer;      
  DWORD dwInactivityTimeout;       
  DWORD dwSpeakerVolume;           
  DWORD dwSpeakerMode;             
  DWORD dwModemOptions;            
  DWORD dwMaxDTERate;              
  DWORD dwMaxDCERate;              

  BYTE abVariablePortion [1];    
} MODEMDEVCAPS, *PMODEMDEVCAPS, *LPMODEMDEVCAPS;
 
typedef struct modemsettings_tag {
  DWORD dwActualSize;            
  DWORD dwRequiredSize;          
  DWORD dwDevSpecificOffset;     
  DWORD dwDevSpecificSize;       

  DWORD dwCallSetupFailTimer;    
  DWORD dwInactivityTimeout;     
  DWORD dwSpeakerVolume;         
  DWORD dwSpeakerMode;           
  DWORD dwPreferredModemOptions; 

  DWORD dwNegotiatedModemOptions; 
  DWORD dwNegotiatedDCERate;      

  BYTE  abVariablePortion[1];     
} MODEMSETTINGS, *PMODEMSETTINGS, *LPMODEMSETTINGS;
 
typedef struct tagMONCBSTRUCT { 
  UINT   cb; 
  DWORD  dwTime; 
  HANDLE hTask; 
  DWORD  dwRet; 
  UINT   wType; 
  UINT   wFmt; 
  HCONV  hConv; 
  HSZ    hsz1; 
  HSZ    hsz2; 
  HDDEDATA hData; 
  DWORD    dwData1; 
  DWORD    dwData2; 
  CONVCONTEXT cc; 
  DWORD  cbData; 
  DWORD  Data[8]; 
} MONCBSTRUCT; 
 
typedef struct tagMONCONVSTRUCT { 
  UINT   cb; 
  WINBOOL   fConnect; 
  DWORD  dwTime; 
  HANDLE hTask; 
  HSZ    hszSvc; 
  HSZ    hszTopic; 
  HCONV  hConvClient; 
  HCONV  hConvServer; 
} MONCONVSTRUCT; 
 
typedef struct tagMONERRSTRUCT { 
  UINT   cb; 
  UINT   wLastError; 
  DWORD  dwTime; 
  HANDLE hTask; 
} MONERRSTRUCT; 
 
typedef struct tagMONHSZSTRUCT { 
  UINT   cb; 
  WINBOOL   fsAction; 
  DWORD  dwTime; 
  HSZ    hsz; 
  HANDLE hTask; 
  TCHAR   str[1]; 
} MONHSZSTRUCT; 
 
typedef struct _MONITOR_INFO_1 { 
  LPTSTR pName; 
} MONITOR_INFO_1; 
 
typedef struct _MONITOR_INFO_2 { 
  LPTSTR pName; 
  LPTSTR pEnvironment ; 
  LPTSTR pDLLName ; 
} MONITOR_INFO_2; 
 
typedef struct tagMONLINKSTRUCT { 
  UINT   cb; 
  DWORD  dwTime; 
  HANDLE hTask; 
  WINBOOL   fEstablished; 
  WINBOOL   fNoData; 
  HSZ    hszSvc; 
  HSZ    hszTopic; 
  HSZ    hszItem; 
  UINT   wFmt; 
  WINBOOL   fServer; 
  HCONV  hConvServer; 
  HCONV  hConvClient; 
} MONLINKSTRUCT; 
 
typedef struct tagMONMSGSTRUCT { 
  UINT   cb; 
  HWND   hwndTo; 
  DWORD  dwTime; 
  HANDLE hTask; 
  UINT   wMsg; 
  WPARAM wParam; 
  LPARAM lParam; 
  DDEML_MSG_HOOK_DATA dmhd; 
} MONMSGSTRUCT; 
 
typedef struct tagMOUSEHOOKSTRUCT { 
  POINT pt; 
  HWND  hwnd; 
  UINT  wHitTestCode; 
  DWORD dwExtraInfo; 
} MOUSEHOOKSTRUCT, *PMOUSEHOOKSTRUCT, *LPMOUSEHOOKSTRUCT; 
 
typedef struct _MOUSEKEYS { 
  DWORD cbSize; 
  DWORD dwFlags; 
  DWORD iMaxSpeed; 
  DWORD iTimeToMaxSpeed; 
  DWORD iCtrlSpeed; 
  DWORD dwReserved1; 
  DWORD dwReserved2; 
} MOUSEKEYS; 
 
typedef struct tagMSG {  
  HWND   hwnd;   
  UINT   message; 
  WPARAM wParam; 
  LPARAM lParam; 
  DWORD  time; 
  POINT  pt; 
} MSG, *LPMSG; 
 
typedef void   (*MSGBOXCALLBACK) (LPHELPINFO lpHelpInfo);

typedef struct { 
  UINT      cbSize; 
  HWND      hwndOwner; 
  HINSTANCE hInstance; 
  LPCSTR    lpszText; 
  LPCSTR    lpszCaption; 
  DWORD     dwStyle; 
  LPCSTR    lpszIcon; 
  DWORD     dwContextHelpId; 
  MSGBOXCALLBACK lpfnMsgBoxCallback; 
  DWORD     dwLanguageId; 
} MSGBOXPARAMS, *PMSGBOXPARAMS,   *LPMSGBOXPARAMS; 

typedef struct _msgfilter { 
  NMHDR nmhdr; 
  UINT msg; 
  WPARAM wParam; 
  LPARAM lParam; 
} MSGFILTER; 
 
typedef struct tagMULTIKEYHELP { 
  DWORD  mkSize; 
  TCHAR  mkKeylist; 
  TCHAR  szKeyphrase[1]; 
} MULTIKEYHELP; 
 
typedef struct _NAME_BUFFER { 
  UCHAR name[(16) ]; 
  UCHAR name_num; 
  UCHAR name_flags; 
} NAME_BUFFER; 
 
typedef struct _NCB { 
  UCHAR  ncb_command; 
  UCHAR  ncb_retcode; 
  UCHAR  ncb_lsn; 
  UCHAR  ncb_num; 
  PUCHAR ncb_buffer; 
  WORD   ncb_length; 
  UCHAR  ncb_callname[(16) ]; 
  UCHAR  ncb_name[(16) ]; 
  UCHAR  ncb_rto; 
  UCHAR  ncb_sto; 
  void (*ncb_post) (struct _NCB *); 
  UCHAR  ncb_lana_num; 
  UCHAR  ncb_cmd_cplt; 
  UCHAR  ncb_reserve[10]; 
  HANDLE ncb_event; 
} NCB; 
 
typedef struct _NCCALCSIZE_PARAMS { 
  RECT        rgrc[3]; 
  PWINDOWPOS  lppos; 
} NCCALCSIZE_PARAMS; 
 
typedef struct _NDDESHAREINFO { 
  LONG   lRevision; 
  LPTSTR lpszShareName; 
  LONG   lShareType; 
  LPTSTR lpszAppTopicList; 
  LONG   fSharedFlag; 
  LONG   fService; 
  LONG   fStartAppFlag; 
  LONG   nCmdShow; 
  LONG   qModifyId[2]; 
  LONG   cNumItems; 
  LPTSTR lpszItemList; 
}NDDESHAREINFO; 
 
typedef struct _NETRESOURCE { 
  DWORD  dwScope; 
  DWORD  dwType; 
  DWORD  dwDisplayType; 
  DWORD  dwUsage; 
  LPTSTR lpLocalName; 
  LPTSTR lpRemoteName; 
  LPTSTR lpComment; 
  LPTSTR lpProvider; 
} NETRESOURCE, *LPNETRESOURCE; 
 
typedef struct tagNEWCPLINFO {
  DWORD dwSize; 
  DWORD dwFlags; 
  DWORD dwHelpContext; 
  LONG  lData; 
  HICON hIcon; 
  TCHAR  szName[32]; 
  TCHAR  szInfo[64]; 
  TCHAR  szHelpFile[128]; 
} NEWCPLINFO; 
 
typedef struct tagNEWTEXTMETRIC { 
  LONG   tmHeight; 
  LONG   tmAscent; 
  LONG   tmDescent; 
  LONG   tmInternalLeading; 
  LONG   tmExternalLeading; 
  LONG   tmAveCharWidth; 
  LONG   tmMaxCharWidth; 
  LONG   tmWeight; 
  LONG   tmOverhang; 
  LONG   tmDigitizedAspectX; 
  LONG   tmDigitizedAspectY; 
  BCHAR  tmFirstChar; 
  BCHAR  tmLastChar; 
  BCHAR  tmDefaultChar; 
  BCHAR  tmBreakChar; 
  BYTE   tmItalic; 
  BYTE   tmUnderlined; 
  BYTE   tmStruckOut; 
  BYTE   tmPitchAndFamily; 
  BYTE   tmCharSet; 
  DWORD  ntmFlags; 
  UINT   ntmSizeEM; 
  UINT   ntmCellHeight; 
  UINT   ntmAvgWidth; 
} NEWTEXTMETRIC; 

 
typedef struct tagNEWTEXTMETRICEX {
  NEWTEXTMETRIC  ntmentm;
  FONTSIGNATURE  ntmeFontSignature;
} NEWTEXTMETRICEX;
 
typedef struct tagNM_LISTVIEW { 
  NMHDR hdr;        
  int   iItem;      
  int   iSubItem;   
  UINT  uNewState;  
  UINT  uOldState;  
  UINT  uChanged;   
  POINT ptAction;   
  LPARAM lParam;    
} NM_LISTVIEW; 
 
typedef struct _TREEITEM *HTREEITEM;

typedef struct _TV_ITEM { 
  UINT       mask;           
  HTREEITEM  hItem;           
  UINT       state;           
  UINT       stateMask;     
  LPTSTR     pszText;        
  int        cchTextMax;      
  int        iImage;          
  int        iSelectedImage;  
  int        cChildren;       
  LPARAM     lParam;          
} TV_ITEM,   *LPTV_ITEM; 
 
typedef struct _NM_TREEVIEW { 
  NMHDR    hdr;       
  UINT     action;        
  TV_ITEM  itemOld;   
  TV_ITEM  itemNew;   
  POINT    ptDrag;    
} NM_TREEVIEW; 
typedef NM_TREEVIEW   *LPNM_TREEVIEW; 

typedef struct _NM_UPDOWN {
  NMHDR    hdr;    
  int     iPos;    
  int  iDelta;     
} NM_UPDOWNW; 
 
typedef struct tagNONCLIENTMETRICS { 
  UINT    cbSize; 
  int     iBorderWidth; 
  int     iScrollWidth; 
  int     iScrollHeight; 
  int     iCaptionWidth; 
  int     iCaptionHeight; 
  LOGFONT lfCaptionFont; 
  int     iSmCaptionWidth; 
  int     iSmCaptionHeight; 
  LOGFONT lfSmCaptionFont; 
  int     iMenuWidth; 
  int     iMenuHeight; 
  LOGFONT lfMenuFont; 
  LOGFONT lfStatusFont; 
  LOGFONT lfMessageFont; 
} NONCLIENTMETRICS,  * LPNONCLIENTMETRICS; 
 
typedef struct _SERVICE_ADDRESS { 
  DWORD   dwAddressType; 
  DWORD   dwAddressFlags; 
  DWORD   dwAddressLength; 
  DWORD   dwPrincipalLength; 
  BYTE   *lpAddress;  
  BYTE   *lpPrincipal; 
} SERVICE_ADDRESS; 
 
typedef struct _SERVICE_ADDRESSES { 
  DWORD   dwAddressCount; 
  SERVICE_ADDRESS   Addresses[1]; 
} SERVICE_ADDRESSES, *LPSERVICE_ADDRESSES; 
 
typedef struct _GUID
{ 
    unsigned long  Data1; 
    unsigned short  Data2; 
    unsigned short  Data3; 
    unsigned char Data4[8]; 
} GUID, *LPGUID;
typedef GUID CLSID, *LPCLSID;
 
typedef struct _SERVICE_INFO { 
  LPGUID   lpServiceType; 
  LPTSTR   lpServiceName; 
  LPTSTR   lpComment; 
  LPTSTR   lpLocale; 
  DWORD    dwDisplayHint; 
  DWORD    dwVersion; 
  DWORD    dwTime; 
  LPTSTR   lpMachineName; 
  LPSERVICE_ADDRESSES lpServiceAddress; 
  BLOB ServiceSpecificInfo; 
} SERVICE_INFO; 
 
typedef struct _NS_SERVICE_INFO { 
  DWORD   dwNameSpace; 
  SERVICE_INFO ServiceInfo; 
} NS_SERVICE_INFO; 
 
typedef struct _numberfmt { 
  UINT      NumDigits; 
  UINT      LeadingZero; 
  UINT      Grouping; 
  LPTSTR    lpDecimalSep; 
  LPTSTR    lpThousandSep; 
  UINT      NegativeOrder; 
} NUMBERFMT; 
 
typedef struct _OFSTRUCT { 
  BYTE cBytes; 
  BYTE fFixedDisk; 
  WORD nErrCode; 
  WORD Reserved1; 
  WORD Reserved2; 
  CHAR szPathName[(128) ]; 
} OFSTRUCT, *LPOFSTRUCT; 
 
typedef struct tagOFN { 
  DWORD         lStructSize; 
  HWND          hwndOwner; 
  HINSTANCE     hInstance; 
  LPCTSTR       lpstrFilter; 
  LPTSTR        lpstrCustomFilter; 
  DWORD         nMaxCustFilter; 
  DWORD         nFilterIndex; 
  LPTSTR        lpstrFile; 
  DWORD         nMaxFile; 
  LPTSTR        lpstrFileTitle; 
  DWORD         nMaxFileTitle; 
  LPCTSTR       lpstrInitialDir; 
  LPCTSTR       lpstrTitle; 
  DWORD         Flags; 
  WORD          nFileOffset; 
  WORD          nFileExtension; 
  LPCTSTR       lpstrDefExt; 
  DWORD         lCustData; 
  LPOFNHOOKPROC lpfnHook; 
  LPCTSTR       lpTemplateName; 
} OPENFILENAME, *LPOPENFILENAME; 

typedef struct _OFNOTIFY {
  NMHDR          hdr; 
  LPOPENFILENAME lpOFN; 
  LPTSTR         pszFile; 
} OFNOTIFY, *LPOFNOTIFY; 
 
typedef struct _OSVERSIONINFO { 
  DWORD dwOSVersionInfoSize; 
  DWORD dwMajorVersion; 
  DWORD dwMinorVersion; 
  DWORD dwBuildNumber; 
  DWORD dwPlatformId; 
  TCHAR szCSDVersion[ 128 ]; 
} OSVERSIONINFO, *POSVERSIONINFO, *LPOSVERSIONINFO; 
 
typedef struct tagTEXTMETRIC { 
  LONG tmHeight; 
  LONG tmAscent; 
  LONG tmDescent; 
  LONG tmInternalLeading; 
  LONG tmExternalLeading; 
  LONG tmAveCharWidth; 
  LONG tmMaxCharWidth; 
  LONG tmWeight; 
  LONG tmOverhang; 
  LONG tmDigitizedAspectX; 
  LONG tmDigitizedAspectY; 
  BCHAR tmFirstChar; 
  BCHAR tmLastChar; 
  BCHAR tmDefaultChar; 
  BCHAR tmBreakChar; 
  BYTE tmItalic; 
  BYTE tmUnderlined; 
  BYTE tmStruckOut; 
  BYTE tmPitchAndFamily; 
  BYTE tmCharSet; 
} TEXTMETRIC, *LPTEXTMETRIC; 

typedef struct _OUTLINETEXTMETRIC { 
  UINT   otmSize; 
  TEXTMETRIC otmTextMetrics; 
  BYTE   otmFiller; 
  PANOSE otmPanoseNumber; 
  UINT   otmfsSelection; 
  UINT   otmfsType; 
  int    otmsCharSlopeRise; 
  int    otmsCharSlopeRun; 
  int    otmItalicAngle; 
  UINT   otmEMSquare; 
  int    otmAscent; 
  int    otmDescent; 
  UINT   otmLineGap; 
  UINT   otmsCapEmHeight; 
  UINT   otmsXHeight; 
  RECT   otmrcFontBox; 
  int    otmMacAscent; 
  int    otmMacDescent; 
  UINT   otmMacLineGap; 
  UINT   otmusMinimumPPEM; 
  POINT  otmptSubscriptSize; 
  POINT  otmptSubscriptOffset; 
  POINT  otmptSuperscriptSize; 
  POINT  otmptSuperscriptOffset; 
  UINT   otmsStrikeoutSize; 
  int    otmsStrikeoutPosition; 
  int    otmsUnderscoreSize; 
  int    otmsUnderscorePosition; 
  PSTR   otmpFamilyName; 
  PSTR   otmpFaceName; 
  PSTR   otmpStyleName; 
  PSTR   otmpFullName; 
} OUTLINETEXTMETRIC, *LPOUTLINETEXTMETRIC; 
 
typedef struct _OVERLAPPED { 
  DWORD  Internal; 
  DWORD  InternalHigh; 
  DWORD  Offset; 
  DWORD  OffsetHigh; 
  HANDLE hEvent; 
} OVERLAPPED, *LPOVERLAPPED; 

typedef struct tagPSD {
    DWORD           lStructSize; 
    HWND            hwndOwner; 
    HGLOBAL         hDevMode; 
    HGLOBAL         hDevNames; 
    DWORD           Flags; 
    POINT           ptPaperSize; 
    RECT            rtMinMargin; 
    RECT            rtMargin; 
    HINSTANCE       hInstance; 
    LPARAM          lCustData; 
    LPPAGESETUPHOOK lpfnPageSetupHook; 
    LPPAGEPAINTHOOK lpfnPagePaintHook; 
    LPCTSTR         lpPageSetupTemplateName; 
    HGLOBAL         hPageSetupTemplate; 
} PAGESETUPDLG, *LPPAGESETUPDLG; 

typedef struct tagPAINTSTRUCT { 
  HDC  hdc; 
  WINBOOL fErase; 
  RECT rcPaint; 
  WINBOOL fRestore; 
  WINBOOL fIncUpdate; 
  BYTE rgbReserved[32]; 
} PAINTSTRUCT, *LPPAINTSTRUCT; 
 
typedef struct _paraformat { 
  UINT cbSize; 
  DWORD dwMask; 
  WORD  wNumbering; 
  WORD  wReserved; 
  LONG  dxStartIndent; 
  LONG  dxRightIndent; 
  LONG  dxOffset; 
  WORD  wAlignment; 
  SHORT cTabCount; 
  LONG  rgxTabs[(32) ]; 
} PARAFORMAT; 
 
typedef struct _PERF_COUNTER_BLOCK { 
  DWORD ByteLength; 
} PERF_COUNTER_BLOCK; 
 
typedef struct _PERF_COUNTER_DEFINITION { 
  DWORD  ByteLength; 
  DWORD  CounterNameTitleIndex; 
  LPWSTR CounterNameTitle; 
  DWORD  CounterHelpTitleIndex; 
  LPWSTR CounterHelpTitle; 
  DWORD  DefaultScale; 
  DWORD  DetailLevel; 
  DWORD  CounterType; 
  DWORD  CounterSize; 
  DWORD  CounterOffset; 
} PERF_COUNTER_DEFINITION; 
 
typedef struct _PERF_DATA_BLOCK { 
  WCHAR         Signature[4]; 
  DWORD         LittleEndian; 
  DWORD         Version; 
  DWORD         Revision; 
  DWORD         TotalByteLength; 
  DWORD         HeaderLength; 
  DWORD         NumObjectTypes; 
  DWORD         DefaultObject; 
  SYSTEMTIME    SystemTime; 
  LARGE_INTEGER PerfTime; 
  LARGE_INTEGER PerfFreq; 
  LARGE_INTEGER PerfTime100nSec; 
  DWORD         SystemNameLength; 
  DWORD         SystemNameOffset; 
} PERF_DATA_BLOCK; 
 
typedef struct _PERF_INSTANCE_DEFINITION { 
  DWORD ByteLength; 
  DWORD ParentObjectTitleIndex; 
  DWORD ParentObjectInstance; 
  DWORD UniqueID; 
  DWORD NameOffset; 
  DWORD NameLength; 
} PERF_INSTANCE_DEFINITION; 
 
typedef struct _PERF_OBJECT_TYPE { 
  DWORD  TotalByteLength; 
  DWORD  DefinitionLength; 
  DWORD  HeaderLength; 
  DWORD  ObjectNameTitleIndex; 
  LPWSTR ObjectNameTitle; 
  DWORD  ObjectHelpTitleIndex; 
  LPWSTR ObjectHelpTitle; 
  DWORD  DetailLevel; 
  DWORD  NumCounters; 
  DWORD  DefaultCounter; 
  DWORD  NumInstances; 
  DWORD  CodePage; 
  LARGE_INTEGER PerfTime; 
  LARGE_INTEGER PerfFreq; 
} PERF_OBJECT_TYPE; 
 
typedef struct _POLYTEXT { 
  int     x; 
  int     y; 
  UINT    n; 
  LPCTSTR lpstr; 
  UINT    uiFlags; 
  RECT    rcl; 
  int     *pdx; 
} POLYTEXT; 
 
typedef struct _PORT_INFO_1 { 
  LPTSTR pName; 
} PORT_INFO_1; 
 
typedef struct _PORT_INFO_2 { 
  LPSTR pPortName; 
  LPSTR pMonitorName; 
  LPSTR pDescription; 
  DWORD fPortType; 
  DWORD Reserved; 
} PORT_INFO_2; 
 
typedef struct _PREVENT_MEDIA_REMOVAL { 
  BOOLEAN PreventMediaRemoval; 
} PREVENT_MEDIA_REMOVAL ; 
 
typedef struct tagPD {  
  DWORD     lStructSize; 
  HWND      hwndOwner; 
  HANDLE    hDevMode; 
  HANDLE    hDevNames; 
  HDC       hDC; 
  DWORD     Flags; 
  WORD      nFromPage; 
  WORD      nToPage; 
  WORD      nMinPage; 
  WORD      nMaxPage; 
  WORD      nCopies; 
  HINSTANCE hInstance; 
  DWORD     lCustData; 
  LPPRINTHOOKPROC lpfnPrintHook; 
  LPSETUPHOOKPROC lpfnSetupHook; 
  LPCTSTR    lpPrintTemplateName; 
  LPCTSTR    lpSetupTemplateName; 
  HANDLE    hPrintTemplate; 
  HANDLE    hSetupTemplate; 
} __attribute__((packed))  PRINTDLG, *LPPRINTDLG; 
 
typedef struct _PRINTER_DEFAULTS {  
  LPTSTR      pDatatype; 
  LPDEVMODE   pDevMode; 
  ACCESS_MASK DesiredAccess; 
} PRINTER_DEFAULTS; 
 
typedef struct _PRINTER_INFO_1 { 
  DWORD  Flags; 
  LPTSTR pDescription; 
  LPTSTR pName; 
  LPTSTR pComment; 
} PRINTER_INFO_1, *PPRINTER_INFO_1, *LPPRINTER_INFO_1; 
 
typedef struct _PRINTER_INFO_2 { 
  LPTSTR    pServerName; 
  LPTSTR    pPrinterName; 
  LPTSTR    pShareName; 
  LPTSTR    pPortName; 
  LPTSTR    pDriverName; 
  LPTSTR    pComment; 
  LPTSTR    pLocation; 
  LPDEVMODE pDevMode; 
  LPTSTR    pSepFile; 
  LPTSTR    pPrintProcessor; 
  LPTSTR    pDatatype; 
  LPTSTR    pParameters; 
  PSECURITY_DESCRIPTOR pSecurityDescriptor; 
  DWORD     Attributes; 
  DWORD     Priority; 
  DWORD     DefaultPriority; 
  DWORD     StartTime; 
  DWORD     UntilTime; 
  DWORD     Status; 
  DWORD     cJobs; 
  DWORD     AveragePPM; 
} PRINTER_INFO_2; 
 
typedef struct _PRINTER_INFO_3 { 
  PSECURITY_DESCRIPTOR pSecurityDescriptor; 
} PRINTER_INFO_3; 
 
typedef struct _PRINTER_INFO_4 { 
  LPTSTR  pPrinterName; 
  LPTSTR  pServerName; 
  DWORD  Attributes; 
} PRINTER_INFO_4; 
 
typedef struct _PRINTER_INFO_5 { 
  LPTSTR    pPrinterName; 
  LPTSTR    pPortName; 
  DWORD     Attributes; 
  DWORD     DeviceNotSelectedTimeout; 
  DWORD     TransmissionRetryTimeout; 
} PRINTER_INFO_5; 
 
typedef struct _PRINTER_NOTIFY_INFO_DATA { 
  WORD   Type; 
  WORD   Field; 
  DWORD  Reserved; 
  DWORD  Id; 
  union { 
    DWORD  adwData[2]; 
    struct { 
      DWORD  cbBuf; 
      LPVOID pBuf; 
    } Data; 
  } NotifyData; 
} PRINTER_NOTIFY_INFO_DATA; 
 
typedef struct _PRINTER_NOTIFY_INFO { 
  DWORD  Version; 
  DWORD  Flags; 
  DWORD  Count; 
  PRINTER_NOTIFY_INFO_DATA  aData[1]; 
} PRINTER_NOTIFY_INFO; 
 
typedef struct _PRINTER_NOTIFY_OPTIONS_TYPE { 
  WORD   Type; 
  WORD   Reserved0; 
  DWORD  Reserved1; 
  DWORD  Reserved2; 
  DWORD  Count; 
  PWORD  pFields; 
} PRINTER_NOTIFY_OPTIONS_TYPE, *PPRINTER_NOTIFY_OPTIONS_TYPE; 
 
typedef struct _PRINTER_NOTIFY_OPTIONS { 
  DWORD  Version; 
  DWORD  Flags; 
  DWORD  Count; 
  PPRINTER_NOTIFY_OPTIONS_TYPE  pTypes; 
} PRINTER_NOTIFY_OPTIONS; 
 
typedef struct _PRINTPROCESSOR_INFO_1 { 
  LPTSTR pName; 
} PRINTPROCESSOR_INFO_1; 
 
typedef struct _PRIVILEGE_SET { 
  DWORD PrivilegeCount; 
  DWORD Control; 
  LUID_AND_ATTRIBUTES Privilege[(1) ]; 
} PRIVILEGE_SET, *PPRIVILEGE_SET, *LPPRIVILEGE_SET; 
 
typedef struct _PROCESS_HEAP_ENTRY {  
  PVOID lpData; 
  DWORD cbData; 
  BYTE cbOverhead; 
  BYTE iRegionIndex; 
  WORD wFlags; 
  DWORD dwCommittedSize; 
  DWORD dwUnCommittedSize; 
  LPVOID lpFirstBlock; 
  LPVOID lpLastBlock; 
  HANDLE hMem; 
} PROCESS_HEAPENTRY, *LPPROCESS_HEAP_ENTRY; 
 
typedef struct _PROCESS_INFORMATION { 
  HANDLE hProcess; 
  HANDLE hThread; 
  DWORD dwProcessId; 
  DWORD dwThreadId; 
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION; 
 
typedef UINT   (*LPFNPSPCALLBACK) (HWND, UINT, LPVOID);

typedef struct _PROPSHEETPAGE { 
  DWORD     dwSize;     
  DWORD     dwFlags;    
  HINSTANCE hInstance;  
  union { 
    LPCTSTR        pszTemplate;      
    LPCDLGTEMPLATE pResource;        
  } u1; 
  union { 
    HICON  hIcon;     
    LPCTSTR pszIcon;  
  } u2; 
  LPCTSTR pszTitle;     
  DLGPROC pfnDlgProc;   
  LPARAM  lParam;       
  LPFNPSPCALLBACK pfnCallback;         
  UINT   * pcRefParent;              
} PROPSHEETPAGE,   *LPPROPSHEETPAGE; 
typedef const PROPSHEETPAGE   *LPCPROPSHEETPAGE; 
 
typedef struct _PSP *HPROPSHEETPAGE;
typedef struct _PROPSHEETHEADER { 
  DWORD      dwSize;     
  DWORD      dwFlags;    
  HWND       hwndParent; 
  HINSTANCE  hInstance;  
  union { 
    HICON  hIcon;      
    LPCTSTR pszIcon;   
  } u1; 
  LPCTSTR     pszCaption; 
  UINT       nPages; 
  union { 
    UINT  nStartPage; 
    LPCTSTR pStartPage; 
  } u2; 
  union { 
    LPCPROPSHEETPAGE    ppsp;   
    HPROPSHEETPAGE   *phpage; 
  } u3; 
  PFNPROPSHEETCALLBACK pfnCallback; 
} PROPSHEETHEADER,   *LPPROPSHEETHEADER; 
typedef const PROPSHEETHEADER   *LPCPROPSHEETHEADER; 

 
typedef WINBOOL   (*LPFNADDPROPSHEETPAGE) (HPROPSHEETPAGE, LPARAM);
typedef WINBOOL   (*LPFNADDPROPSHEETPAGES) (LPVOID, 
						   LPFNADDPROPSHEETPAGE, 
						   LPARAM);
 
typedef  struct _PROTOCOL_INFO {  
  DWORD  dwServiceFlags; 
  INT  iAddressFamily; 
  INT  iMaxSockAddr; 
  INT  iMinSockAddr; 
  INT  iSocketType; 
  INT  iProtocol; 
  DWORD  dwMessageSize; 
  LPTSTR  lpProtocol; 
} PROTOCOL_INFO; 
 
typedef struct _PROVIDOR_INFO_1 { 
  LPTSTR pName; 
  LPTSTR pEnvironment ; 
  LPTSTR pDLLName ; 
} PROVIDOR_INFO_1; 
 
typedef struct _PSHNOTIFY { 
  NMHDR hdr; 
  LPARAM lParam; 
} PSHNOTIFY,   *LPPSHNOTIFY; 
 
typedef struct _punctuation {
  UINT   iSize;          
  LPSTR  szPunctuation;  
} PUNCTUATION; 
 
typedef struct _QUERY_SERVICE_CONFIG { 
  DWORD dwServiceType; 
  DWORD dwStartType; 
  DWORD dwErrorControl; 
  LPTSTR lpBinaryPathName; 
  LPTSTR lpLoadOrderGroup; 
  DWORD dwTagId; 
  LPTSTR lpDependencies; 
  LPTSTR lpServiceStartName; 
  LPTSTR lpDisplayName; 
} QUERY_SERVICE_CONFIG, *LPQUERY_SERVICE_CONFIG; 
 
typedef struct _QUERY_SERVICE_LOCK_STATUS { 
  DWORD fIsLocked; 
  LPTSTR lpLockOwner; 
  DWORD dwLockDuration; 
} QUERY_SERVICE_LOCK_STATUS, *LPQUERY_SERVICE_LOCK_STATUS ; 
 
typedef  struct  _RASAMB {  
  DWORD    dwSize; 
  DWORD    dwError; 
  TCHAR    szNetBiosError[ (16)  + 1 ]; 
  BYTE     bLana; 
} RASAMB; 
 
typedef struct _RASCONN { 
  DWORD     dwSize; 
  HRASCONN  hrasconn; 
  TCHAR     szEntryName[(256)  + 1]; 
 
  CHAR      szDeviceType[ (16)  + 1 ]; 
  CHAR      szDeviceName[ (128)  + 1 ]; 
} RASCONN ; 
 
typedef struct _RASCONNSTATUS { 
  DWORD         dwSize; 
  RASCONNSTATE  rasconnstate; 
  DWORD         dwError; 
  TCHAR         szDeviceType[(16)  + 1]; 
  TCHAR         szDeviceName[(128)  + 1]; 
} RASCONNSTATUS; 
 
typedef  struct  _RASDIALEXTENSIONS { 
  DWORD    dwSize; 
  DWORD    dwfOptions; 
  HWND    hwndParent; 
  DWORD    reserved; 
} RASDIALEXTENSIONS; 
 
typedef struct _RASDIALPARAMS { 
  DWORD  dwSize; 
  TCHAR  szEntryName[(256)  + 1]; 
  TCHAR  szPhoneNumber[(128)  + 1]; 
  TCHAR  szCallbackNumber[(128)  + 1]; 
  TCHAR  szUserName[(256)  + 1]; 
  TCHAR  szPassword[(256)  + 1]; 
  TCHAR  szDomain[(15)  + 1] ; 
} RASDIALPARAMS; 
 
typedef struct _RASENTRYNAME { 
  DWORD  dwSize; 
  TCHAR  szEntryName[(256)  + 1]; 
}RASENTRYNAME; 
 
typedef  struct  _RASPPPIP { 
  DWORD    dwSize; 
  DWORD    dwError; 
  TCHAR    szIpAddress[ (15)  + 1 ]; 
} RASPPPIP; 
 
typedef  struct  _RASPPPIPX { 
  DWORD    dwSize; 
  DWORD    dwError; 
  TCHAR    szIpxAddress[ (21)  + 1 ]; 
} RASPPPIPX; 
 
typedef  struct  _RASPPPNBF { 
  DWORD    dwSize; 
  DWORD    dwError; 
  DWORD    dwNetBiosError; 
  TCHAR    szNetBiosError[ (16)  + 1 ]; 
  TCHAR    szWorkstationName[ (16)  + 1 ]; 
  BYTE     bLana; 
} RASPPPNBF; 
 
typedef struct _RASTERIZER_STATUS { 
  short nSize; 
  short wFlags; 
  short nLanguageID; 
} RASTERIZER_STATUS, *LPRASTERIZER_STATUS; 
 
typedef struct _REASSIGN_BLOCKS { 
  WORD   Reserved; 
  WORD   Count; 
  DWORD BlockNumber[1]; 
} REASSIGN_BLOCKS ; 
 
typedef struct _REMOTE_NAME_INFO {
  LPTSTR  lpUniversalName; 
  LPTSTR  lpConnectionName; 
  LPTSTR  lpRemainingPath;    
} REMOTE_NAME_INFO; 
 
 














 
typedef struct _repastespecial { 
  DWORD  dwAspect;  
  DWORD  dwParam;   
} REPASTESPECIAL; 
 
typedef struct _reqresize { 
  NMHDR nmhdr; 
  RECT rc; 
} REQRESIZE; 
 
typedef struct _RGNDATAHEADER { 
  DWORD dwSize; 
  DWORD iType; 
  DWORD nCount; 
  DWORD nRgnSize; 
  RECT  rcBound; 
} RGNDATAHEADER; 
 
typedef struct _RGNDATA { 
  RGNDATAHEADER rdh; 
  char          Buffer[1]; 
} RGNDATA, *LPRGNDATA; 
 
typedef struct tagSCROLLINFO {
  UINT cbSize; 
  UINT fMask; 
  int  nMin; 
  int  nMax; 
  UINT nPage; 
  int  nPos; 
  int  nTrackPos; 
}   SCROLLINFO, *LPSCROLLINFO; 
typedef SCROLLINFO const *LPCSCROLLINFO; 
 
typedef struct _SECURITY_ATTRIBUTES { 
  DWORD  nLength; 
  LPVOID lpSecurityDescriptor; 
  WINBOOL   bInheritHandle; 
} SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES; 
 
typedef DWORD SECURITY_INFORMATION, *PSECURITY_INFORMATION; 
 
typedef struct _selchange { 
  NMHDR nmhdr; 
  CHARRANGE chrg; 
  WORD seltyp; 
} SELCHANGE; 
 
typedef struct tagSERIALKEYS {  
  DWORD cbSize; 
  DWORD dwFlags; 
  LPSTR lpszActivePort; 
  LPSTR lpszPort; 
  DWORD iBaudRate; 
  DWORD iPortState; 
} SERIALKEYS,  * LPSERIALKEYS; 
 
typedef struct _SERVICE_TABLE_ENTRY { 
  LPTSTR lpServiceName; 
  LPSERVICE_MAIN_FUNCTION lpServiceProc; 
} SERVICE_TABLE_ENTRY, *LPSERVICE_TABLE_ENTRY; 
 
typedef struct _SERVICE_TYPE_VALUE_ABS { 
  DWORD   dwNameSpace; 
  DWORD   dwValueType; 
  DWORD   dwValueSize; 
  LPTSTR  lpValueName; 
  PVOID   lpValue; 
} SERVICE_TYPE_VALUE_ABS; 
 
typedef struct _SERVICE_TYPE_INFO_ABS { 
  LPTSTR                  lpTypeName; 
  DWORD                   dwValueCount; 
  SERVICE_TYPE_VALUE_ABS  Values[1]; 
} SERVICE_TYPE_INFO_ABS; 
 
typedef struct _SESSION_BUFFER { 
  UCHAR lsn; 
  UCHAR state; 
  UCHAR local_name[(16) ]; 
  UCHAR remote_name[(16) ]; 
  UCHAR rcvs_outstanding; 
  UCHAR sends_outstanding; 
} SESSION_BUFFER; 
 
typedef struct _SESSION_HEADER { 
  UCHAR sess_name; 
  UCHAR num_sess; 
  UCHAR rcv_dg_outstanding; 
  UCHAR rcv_any_outstanding; 
} SESSION_HEADER; 
 
typedef struct _SET_PARTITION_INFORMATION { 
  BYTE PartitionType; 
} SET_PARTITION_INFORMATION ; 
 
typedef enum tagSHCONTF { 
  SHCONTF_FOLDERS = 32,         
  SHCONTF_NONFOLDERS = 64,      
  SHCONTF_INCLUDEHIDDEN = 128,  
} SHCONTF; 
 
typedef struct _SHFILEINFO { 
  HICON hIcon;                   
  int   iIcon;                   
  DWORD dwAttributes;            
  char  szDisplayName[(260) ]; 
  char  szTypeName[80];          
} SHFILEINFO; 

typedef WORD FILEOP_FLAGS; 
typedef struct _SHFILEOPSTRUCT { 
  HWND         hwnd;                  
  UINT         wFunc;                 
  LPCSTR       pFrom;                 
  LPCSTR       pTo;                   
  FILEOP_FLAGS fFlags;                
  WINBOOL         fAnyOperationsAborted; 
  LPVOID       hNameMappings;         
  LPCSTR       lpszProgressTitle;     
} SHFILEOPSTRUCT,   *LPSHFILEOPSTRUCT; 
 
typedef enum tagSHGDN { 
  SHGDN_NORMAL = 0,           
  SHGDN_INFOLDER = 1,         
  SHGDN_FORPARSING = 0x8000,  
} SHGNO; 
 
typedef struct _SHNAMEMAPPING { 
  LPSTR pszOldPath; 
  LPSTR pszNewPath; 
  int   cchOldPath; 
  int   cchNewPath; 
} SHNAMEMAPPING,   *LPSHNAMEMAPPING; 
 
typedef struct _SID_AND_ATTRIBUTES { 
  PSID  Sid; 
  DWORD Attributes; 
} SID_AND_ATTRIBUTES ; 
 
typedef SID_AND_ATTRIBUTES SID_AND_ATTRIBUTES_ARRAY[(1) ];
typedef SID_AND_ATTRIBUTES_ARRAY *PSID_AND_ATTRIBUTES_ARRAY;

typedef struct _SINGLE_LIST_ENTRY { 
  struct _SINGLE_LIST_ENTRY *Next; 
} SINGLE_LIST_ENTRY; 
 
typedef struct tagSOUNDSENTRY {  
  UINT cbSize; 
  DWORD dwFlags; 
  DWORD iFSTextEffect; 
  DWORD iFSTextEffectMSec; 
  DWORD iFSTextEffectColorBits; 
  DWORD iFSGrafEffect; 
  DWORD iFSGrafEffectMSec; 
  DWORD iFSGrafEffectColor; 
  DWORD iWindowsEffect; 
  DWORD iWindowsEffectMSec; 
  LPTSTR lpszWindowsEffectDLL; 
  DWORD iWindowsEffectOrdinal; 
} SOUNDSENTRY, *LPSOUNDSENTRY; 
 
typedef struct _STARTUPINFO { 
  DWORD   cb; 
  LPTSTR  lpReserved; 
  LPTSTR  lpDesktop; 
  LPTSTR  lpTitle; 
  DWORD   dwX; 
  DWORD   dwY; 
  DWORD   dwXSize; 
  DWORD   dwYSize; 
  DWORD   dwXCountChars; 
  DWORD   dwYCountChars; 
  DWORD   dwFillAttribute; 
  DWORD   dwFlags; 
  WORD    wShowWindow; 
  WORD    cbReserved2; 
  LPBYTE  lpReserved2; 
  HANDLE  hStdInput; 
  HANDLE  hStdOutput; 
  HANDLE  hStdError; 
} STARTUPINFO, *LPSTARTUPINFO; 
 
typedef struct tagSTICKYKEYS {  
  DWORD cbSize; 
  DWORD dwFlags; 
} STICKYKEYS, *LPSTICKYKEYS; 
 
typedef struct _STRRET { 
  UINT uType; 
  union 
    { 
      LPWSTR pOleStr;        
      UINT   uOffset;        
      char   cStr[(260) ]; 
    } DUMMYUNIONNAME; 
} STRRET, *LPSTRRET; 
 
typedef struct _tagSTYLEBUF {
  DWORD  dwStyle;           
  CHAR  szDescription[32];  
} STYLEBUF, *LPSTYLEBUF;
 
typedef struct tagSTYLESTRUCT {  
  DWORD styleOld;    
  DWORD styleNew;    
} STYLESTRUCT, * LPSTYLESTRUCT; 
 
typedef struct _SYSTEM_AUDIT_ACE { 
  ACE_HEADER  Header; 
  ACCESS_MASK Mask; 
  DWORD       SidStart; 
} SYSTEM_AUDIT_ACE; 
 
typedef struct _SYSTEM_INFO
{ 
  union
    {
      DWORD dwOemId;
      struct
        {
          WORD wProcessorArchitecture;
          WORD wReserved;
        }
      s;
    }
  u;
  DWORD  dwPageSize; 
  LPVOID lpMinimumApplicationAddress; 
  LPVOID lpMaximumApplicationAddress; 
  DWORD  dwActiveProcessorMask; 
  DWORD  dwNumberOfProcessors; 
  DWORD  dwProcessorType; 
  DWORD  dwAllocationGranularity; 
  WORD  wProcessorLevel; 
  WORD  wProcessorRevision; 
} SYSTEM_INFO, *LPSYSTEM_INFO; 
 
typedef struct _SYSTEM_POWER_STATUS {
  BYTE ACLineStatus;           
  BYTE  BatteryFlag;           
  BYTE  BatteryLifePercent;    
  BYTE  Reserved1;             
  DWORD  BatteryLifeTime;      
  DWORD  BatteryFullLifeTime;  
} SYSTEM_POWER_STATUS;
typedef struct SYSTEM_POWER_STATUS *LPSYSTEM_POWER_STATUS;
 
typedef struct _TAPE_ERASE { 
  ULONG Type; 
} TAPE_ERASE; 
 
typedef struct _TAPE_GET_DRIVE_PARAMETERS { 
  BOOLEAN ECC; 
  BOOLEAN Compression; 
  BOOLEAN DataPadding; 
  BOOLEAN ReportSetmarks; 
  ULONG   DefaultBlockSize; 
  ULONG   MaximumBlockSize; 
  ULONG   MinimumBlockSize; 
  ULONG   MaximumPartitionCount; 
  ULONG   FeaturesLow; 
  ULONG   FeaturesHigh; 
  ULONG   EOTWarningZoneSize; 
} TAPE_GET_DRIVE_PARAMETERS; 
 
typedef struct _TAPE_GET_MEDIA_PARAMETERS {  
  LARGE_INTEGER   Capacity; 
  LARGE_INTEGER   Remaining; 
  DWORD   BlockSize; 
  DWORD   PartitionCount; 
  BOOLEAN WriteProtected; 
} TAPE_GET_MEDIA_PARAMETERS; 
 
typedef struct _TAPE_GET_POSITION { 
  ULONG Type; 
  ULONG Partition; 
  ULONG OffsetLow; 
  ULONG OffsetHigh; 
} TAPE_GET_POSITION; 
 
typedef struct _TAPE_PREPARE { 
  ULONG Operation; 
} TAPE_PREPARE; 
 
typedef struct _TAPE_SET_DRIVE_PARAMETERS { 
  BOOLEAN ECC; 
  BOOLEAN Compression; 
  BOOLEAN DataPadding; 
  BOOLEAN ReportSetmarks; 
  ULONG   EOTWarningZoneSize; 
} TAPE_SET_DRIVE_PARAMETERS; 
 
typedef struct _TAPE_SET_MEDIA_PARAMETERS { 
  ULONG BlockSize; 
} TAPE_SET_MEDIA_PARAMETERS; 
 
typedef struct _TAPE_SET_POSITION { 
  ULONG Method; 
  ULONG Partition; 
  ULONG OffsetLow; 
  ULONG OffsetHigh; 
} TAPE_SET_POSITION; 
 
typedef struct _TAPE_WRITE_MARKS { 
  ULONG Type; 
  ULONG Count; 
} TAPE_WRITE_MARKS; 
 
typedef struct {  
  HINSTANCE hInst; 
  UINT nID; 
} TBADDBITMAP, *LPTBADDBITMAP; 
 
typedef struct _TBBUTTON { 
  int iBitmap; 
  int idCommand; 
  BYTE fsState; 
  BYTE fsStyle; 
  DWORD dwData; 
  int iString; 
} TBBUTTON,  * PTBBUTTON,  * LPTBBUTTON; 
typedef const TBBUTTON  * LPCTBBUTTON; 
 
typedef struct { 
  NMHDR hdr; 
  int iItem; 
  TBBUTTON tbButton; 
  int cchText; 
  LPTSTR pszText; 
} TBNOTIFY,  *LPTBNOTIFY; 
 
typedef struct { 
  HKEY hkr; 
  LPCTSTR pszSubKey; 
  LPCTSTR pszValueName; 
} TBSAVEPARAMS; 
 
typedef struct _TC_HITTESTINFO { 
  POINT pt;     
  UINT  flags;  
} TC_HITTESTINFO; 
 
typedef struct _TC_ITEM { 
  UINT mask;         
  UINT lpReserved1;  
  UINT lpReserved2;  
  LPTSTR pszText;     
  int cchTextMax;    
  int iImage;        
  LPARAM lParam;     
} TC_ITEM; 
 
typedef struct _TC_ITEMHEADER { 
  UINT mask;         
  UINT lpReserved1;  
  UINT lpReserved2;  
  LPTSTR pszText;     
  int cchTextMax;    
  int iImage;        
} TC_ITEMHEADER; 
 
typedef struct _TC_KEYDOWN { 
  NMHDR hdr;    
  WORD wVKey;   
  UINT flags;
} TC_KEYDOWN; 
 
typedef struct _textrange { 
  CHARRANGE chrg; 
  LPSTR lpstrText; 
} TEXTRANGE; 
 
typedef struct _TIME_ZONE_INFORMATION { 
  LONG       Bias; 
  WCHAR      StandardName[ 32 ]; 
  SYSTEMTIME StandardDate; 
  LONG       StandardBias; 
  WCHAR      DaylightName[ 32 ]; 
  SYSTEMTIME DaylightDate; 
  LONG       DaylightBias; 
} TIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION; 
 
typedef struct tagTOGGLEKEYS {   
  DWORD cbSize; 
  DWORD dwFlags; 
} TOGGLEKEYS; 

typedef struct _TOKEN_SOURCE {
  CHAR SourceName[8]; 
  LUID SourceIdentifier; 
} TOKEN_SOURCE; 
 
typedef struct _TOKEN_CONTROL { 
  LUID TokenId; 
  LUID AuthenticationId; 
  LUID ModifiedId; 
  TOKEN_SOURCE TokenSource; 
} TOKEN_CONTROL ; 
 
typedef struct _TOKEN_DEFAULT_DACL {  
  PACL DefaultDacl; 
} TOKEN_DEFAULT_DACL; 
 
typedef struct _TOKEN_GROUPS { 
  DWORD GroupCount; 
  SID_AND_ATTRIBUTES Groups[(1) ]; 
} TOKEN_GROUPS, *PTOKEN_GROUPS, *LPTOKEN_GROUPS; 
 
typedef struct _TOKEN_OWNER { 
  PSID Owner; 
} TOKEN_OWNER; 
 
typedef struct _TOKEN_PRIMARY_GROUP { 
  PSID PrimaryGroup; 
} TOKEN_PRIMARY_GROUP; 
 
typedef struct _TOKEN_PRIVILEGES { 
  DWORD PrivilegeCount; 
  LUID_AND_ATTRIBUTES Privileges[(1) ]; 
} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES, *LPTOKEN_PRIVILEGES; 
 
typedef struct _TOKEN_STATISTICS { 
  LUID  TokenId; 
  LUID  AuthenticationId; 
  LARGE_INTEGER ExpirationTime; 
  TOKEN_TYPE    TokenType; 
  SECURITY_IMPERSONATION_LEVEL ImpersonationLevel; 
  DWORD DynamicCharged; 
  DWORD DynamicAvailable; 
  DWORD GroupCount; 
  DWORD PrivilegeCount; 
  LUID  ModifiedId; 
} TOKEN_STATISTICS; 
 
typedef struct _TOKEN_USER { 
  SID_AND_ATTRIBUTES User; 
} TOKEN_USER; 
 
typedef struct {  
  UINT      cbSize;    
  UINT      uFlags;    
  HWND      hwnd;      
  UINT      uId;       
  RECT      rect;      
  HINSTANCE hinst;     
  LPTSTR     lpszText;  
} TOOLINFO,   *PTOOLINFO,   *LPTOOLINFO; 
 
typedef struct { 
  NMHDR     hdr;        
  LPTSTR    lpszText;   
  char      szText[80]; 
  HINSTANCE hinst;      
  UINT      uFlags;     
} TOOLTIPTEXT,   *LPTOOLTIPTEXT; 
 
typedef struct tagTPMPARAMS { 
  UINT cbSize; 
  RECT rcExclude; 
} TPMPARAMS,   *LPTPMPARAMS; 
 
typedef struct _TRANSMIT_FILE_BUFFERS {  
  PVOID Head; 
  DWORD HeadLength; 
  PVOID Tail; 
  DWORD TailLength; 
} TRANSMIT_FILE_BUFFERS; 
 
typedef struct _TT_HITTESTINFO { 
  HWND hwnd;   
  POINT pt;    
  TOOLINFO ti; 
} TTHITTESTINFO,   * LPHITTESTINFO; 
 
typedef struct tagTTPOLYCURVE { 
  WORD    wType; 
  WORD    cpfx; 
  POINTFX apfx[1]; 
} TTPOLYCURVE,  * LPTTPOLYCURVE; 
 
typedef struct _TTPOLYGONHEADER { 
  DWORD   cb; 
  DWORD   dwType; 
  POINTFX pfxStart; 
} TTPOLYGONHEADER,  * LPTTPOLYGONHEADER; 
 
typedef struct _TV_DISPINFO { 
  NMHDR   hdr;  
  TV_ITEM item;  
} TV_DISPINFO; 
 
typedef struct _TVHITTESTINFO { 
  POINT     pt;     
  UINT      flags;  
  HTREEITEM hItem;  
} TV_HITTESTINFO,   *LPTV_HITTESTINFO; 
 
typedef struct _TV_INSERTSTRUCT { 
  HTREEITEM hParent;       
  HTREEITEM hInsertAfter;  
  TV_ITEM   item;          
} TV_INSERTSTRUCT,   *LPTV_INSERTSTRUCT; 
 
typedef struct _TV_KEYDOWN {
  NMHDR hdr;    
  WORD  wVKey;  
  UINT  flags;  
} TV_KEYDOWN; 
 
typedef struct _TV_SORTCB { 
  HTREEITEM    hParent;       
  PFNTVCOMPARE lpfnCompare;   
  LPARAM       lParam;        
} TV_SORTCB,   *LPTV_SORTCB;  
 
typedef struct { 
  UINT nSec;   
  UINT nInc;   
} UDACCEL; 
 
typedef struct _ULARGE_INTEGER { 
  DWORD LowPart; 
  DWORD HighPart; 
} ULARGE_INTEGER, *PULARGE_INTEGER; 
 
typedef struct _UNIVERSAL_NAME_INFO { 
  LPTSTR  lpUniversalName; 
} UNIVERSAL_NAME_INFO; 
 
typedef struct tagUSEROBJECTFLAGS { 
  WINBOOL fInherit; 
  WINBOOL fReserved; 
  DWORD dwFlags; 
} USEROBJECTFLAGS; 
 
typedef struct value_ent {
    LPTSTR   ve_valuename;
    DWORD ve_valuelen;
    DWORD ve_valueptr;
    DWORD ve_type;
} VALENT, *PVALENT;

typedef struct _VERIFY_INFORMATION { 
  LARGE_INTEGER  StartingOffset; 
  DWORD  Length; 
} VERIFY_INFORMATION ; 
 
typedef struct _VS_FIXEDFILEINFO { 
  DWORD dwSignature; 
  DWORD dwStrucVersion; 
  DWORD dwFileVersionMS; 
  DWORD dwFileVersionLS; 
  DWORD dwProductVersionMS; 
  DWORD dwProductVersionLS; 
  DWORD dwFileFlagsMask; 
  DWORD dwFileFlags; 
  DWORD dwFileOS; 
  DWORD dwFileType; 
  DWORD dwFileSubtype; 
  DWORD dwFileDateMS; 
  DWORD dwFileDateLS; 
} VS_FIXEDFILEINFO; 
 
typedef struct _WIN32_FIND_DATA { 
  DWORD dwFileAttributes; 
  FILETIME ftCreationTime; 
  FILETIME ftLastAccessTime; 
  FILETIME ftLastWriteTime; 
  DWORD    nFileSizeHigh; 
  DWORD    nFileSizeLow; 
  DWORD    dwReserved0; 
  DWORD    dwReserved1; 
  TCHAR    cFileName[ (260)  ]; 
  TCHAR    cAlternateFileName[ 14 ]; 
} WIN32_FIND_DATA, *LPWIN32_FIND_DATA, *PWIN32_FIND_DATA; 
 
typedef struct _WIN32_STREAM_ID { 
  DWORD dwStreamId; 
  DWORD dwStreamAttributes; 
  LARGE_INTEGER Size; 
  DWORD dwStreamNameSize; 
  WCHAR *cStreamName ; 
} WIN32_STREAM_ID;
 
typedef struct _WINDOWPLACEMENT {  
  UINT  length;               
  UINT  flags;                
  UINT  showCmd;              
  POINT ptMinPosition;        
  POINT ptMaxPosition;        
  RECT  rcNormalPosition;     
} WINDOWPLACEMENT; 
 
typedef struct _WNDCLASS {  
  UINT    style; 
  WNDPROC lpfnWndProc; 
  int     cbClsExtra; 
  int     cbWndExtra; 
  HANDLE  hInstance; 
  HICON   hIcon; 
  HCURSOR hCursor; 
  HBRUSH  hbrBackground; 
  LPCTSTR lpszMenuName; 
  LPCTSTR lpszClassName; 
} WNDCLASS, *LPWNDCLASS; 
 
typedef struct _WNDCLASSEX { 
  UINT    cbSize; 
  UINT    style; 
  WNDPROC lpfnWndProc; 
  int     cbClsExtra; 
  int     cbWndExtra; 
  HANDLE  hInstance; 
  HICON   hIcon; 
  HCURSOR hCursor; 
  HBRUSH  hbrBackground; 
  LPCTSTR lpszMenuName; 
  LPCTSTR lpszClassName; 
  HICON   hIconSm; 
} WNDCLASSEX, *LPWNDCLASSEX; 

typedef struct _CONNECTDLGSTRUCT {
  DWORD cbStructure;
  HWND hwndOwner;
  LPNETRESOURCE lpConnRes;
  DWORD dwFlags;
  DWORD dwDevNum;
} CONNECTDLGSTRUCT, *LPCONNECTDLGSTRUCT;

typedef struct _DISCDLGSTRUCT {
  DWORD           cbStructure;
  HWND            hwndOwner;
  LPTSTR           lpLocalName;
  LPTSTR           lpRemoteName;
  DWORD           dwFlags;
} DISCDLGSTRUCT, *LPDISCDLGSTRUCT;

typedef struct _NETINFOSTRUCT{
    DWORD cbStructure;
    DWORD dwProviderVersion;
    DWORD dwStatus;
    DWORD dwCharacteristics;
    DWORD dwHandle;
    WORD  wNetType;
    DWORD dwPrinters;
    DWORD dwDrives;
} NETINFOSTRUCT, *LPNETINFOSTRUCT;

typedef struct _NETCONNECTINFOSTRUCT{
  DWORD cbStructure;
  DWORD dwFlags;
  DWORD dwSpeed;
  DWORD dwDelay;
  DWORD dwOptDataSize;
} NETCONNECTINFOSTRUCT, *LPNETCONNECTINFOSTRUCT;

typedef int   (*ENUMMETAFILEPROC) (HDC, HANDLETABLE, 
					  METARECORD, int, LPARAM);
typedef int   (*ENHMETAFILEPROC) (HDC, HANDLETABLE, 
					 ENHMETARECORD, int, LPARAM);

typedef int   (*ENUMFONTSPROC) (LPLOGFONT, LPTEXTMETRIC, DWORD, LPARAM);
typedef int   (*FONTENUMPROC) (ENUMLOGFONT *, NEWTEXTMETRIC *, 
				      int, LPARAM);
typedef int   (*FONTENUMEXPROC) (ENUMLOGFONTEX *, NEWTEXTMETRICEX *, 
				      int, LPARAM);

typedef void    (*LPOVERLAPPED_COMPLETION_ROUTINE) (DWORD, DWORD, 
							  LPOVERLAPPED);

 


typedef struct _POINTFLOAT 
{
  FLOAT   x;
  FLOAT   y;
} POINTFLOAT, *PPOINTFLOAT;

typedef struct _GLYPHMETRICSFLOAT
{
  FLOAT       gmfBlackBoxX;
  FLOAT       gmfBlackBoxY;
  POINTFLOAT  gmfptGlyphOrigin;
  FLOAT       gmfCellIncX;
  FLOAT       gmfCellIncY;
} GLYPHMETRICSFLOAT, *PGLYPHMETRICSFLOAT, *LPGLYPHMETRICSFLOAT;

typedef struct tagLAYERPLANEDESCRIPTOR
{
  WORD  nSize; 
  WORD  nVersion; 
  DWORD dwFlags; 
  BYTE  iPixelType; 
  BYTE  cColorBits; 
  BYTE  cRedBits; 
  BYTE  cRedShift; 
  BYTE  cGreenBits; 
  BYTE  cGreenShift; 
  BYTE  cBlueBits; 
  BYTE  cBlueShift; 
  BYTE  cAlphaBits; 
  BYTE  cAlphaShift; 
  BYTE  cAccumBits; 
  BYTE  cAccumRedBits; 
  BYTE  cAccumGreenBits; 
  BYTE  cAccumBlueBits; 
  BYTE  cAccumAlphaBits; 
  BYTE  cDepthBits; 
  BYTE  cStencilBits; 
  BYTE  cAuxBuffers; 
  BYTE  iLayerPlane;
  BYTE  bReserved; 
  COLORREF crTransparent; 
} LAYERPLANEDESCRIPTOR, *PLAYERPLANEDESCRIPTOR, *LPLAYERPLANEDESCRIPTOR; 

typedef struct tagPIXELFORMATDESCRIPTOR
{
  WORD  nSize;
  WORD  nVersion;
  DWORD dwFlags;
  BYTE  iPixelType;
  BYTE  cColorBits;
  BYTE  cRedBits;
  BYTE  cRedShift;
  BYTE  cGreenBits;
  BYTE  cGreenShift;
  BYTE  cBlueBits;
  BYTE  cBlueShift;
  BYTE  cAlphaBits;
  BYTE  cAlphaShift;
  BYTE  cAccumBits;
  BYTE  cAccumRedBits;
  BYTE  cAccumGreenBits;
  BYTE  cAccumBlueBits;
  BYTE  cAccumAlphaBits;
  BYTE  cDepthBits;
  BYTE  cStencilBits;
  BYTE  cAuxBuffers;
  BYTE  iLayerType;
  BYTE  bReserved;
  DWORD dwLayerMask;
  DWORD dwVisibleMask;
  DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

typedef struct
{
  LPWSTR    usri2_name;
  LPWSTR    usri2_password;
  DWORD     usri2_password_age;
  DWORD     usri2_priv;
  LPWSTR    usri2_home_dir;
  LPWSTR    usri2_comment;
  DWORD     usri2_flags;
  LPWSTR    usri2_script_path;
  DWORD     usri2_auth_flags;
  LPWSTR    usri2_full_name;
  LPWSTR    usri2_usr_comment;
  LPWSTR    usri2_parms;
  LPWSTR    usri2_workstations;
  DWORD     usri2_last_logon;
  DWORD     usri2_last_logoff;
  DWORD     usri2_acct_expires;
  DWORD     usri2_max_storage;
  DWORD     usri2_units_per_week;
  PBYTE     usri2_logon_hours;
  DWORD     usri2_bad_pw_count;
  DWORD     usri2_num_logons;
  LPWSTR    usri2_logon_server;
  DWORD     usri2_country_code;
  DWORD     usri2_code_page;
} USER_INFO_2, *PUSER_INFO_2, *LPUSER_INFO_2;

typedef struct
{
  LPWSTR    usri0_name;
} USER_INFO_0, *PUSER_INFO_0, *LPUSER_INFO_0;

typedef struct
{
  LPWSTR    usri3_name;
  LPWSTR    usri3_password;
  DWORD     usri3_password_age;
  DWORD     usri3_priv;
  LPWSTR    usri3_home_dir;
  LPWSTR    usri3_comment;
  DWORD     usri3_flags;
  LPWSTR    usri3_script_path;
  DWORD     usri3_auth_flags;
  LPWSTR    usri3_full_name;
  LPWSTR    usri3_usr_comment;
  LPWSTR    usri3_parms;
  LPWSTR    usri3_workstations;
  DWORD     usri3_last_logon;
  DWORD     usri3_last_logoff;
  DWORD     usri3_acct_expires;
  DWORD     usri3_max_storage;
  DWORD     usri3_units_per_week;
  PBYTE     usri3_logon_hours;
  DWORD     usri3_bad_pw_count;
  DWORD     usri3_num_logons;
  LPWSTR    usri3_logon_server;
  DWORD     usri3_country_code;
  DWORD     usri3_code_page;
  DWORD     usri3_user_id;
  DWORD     usri3_primary_group_id;
  LPWSTR    usri3_profile;
  LPWSTR    usri3_home_dir_drive;
  DWORD     usri3_password_expired;
} USER_INFO_3, *PUSER_INFO_3, *LPUSER_INFO_3;

typedef struct
{
  LPWSTR   grpi2_name;
  LPWSTR   grpi2_comment;
  DWORD    grpi2_group_id;
  DWORD    grpi2_attributes;
} GROUP_INFO_2, *PGROUP_INFO_2;

typedef struct
{
  LPWSTR   lgrpi0_name;
} LOCALGROUP_INFO_0, *PLOCALGROUP_INFO_0, *LPLOCALGROUP_INFO_0;

 

typedef struct
{
  WORD e_magic;		 
  WORD e_cblp;		 
  WORD e_cp;		 
  WORD e_crlc;		 
  WORD e_cparhdr;	 
  WORD e_minalloc;	 
  WORD e_maxalloc;	 
  WORD e_ss;		 
  WORD e_sp;		 
  WORD e_csum;		 
  WORD e_ip;		 
  WORD e_cs;		 
  WORD e_lfarlc;	 
  WORD e_ovno;		 
  WORD e_res[4];	 
  WORD e_oemid;		 
  WORD e_oeminfo;	 
  WORD e_res2[10];	 
  LONG e_lfanew;	 
   

   
    
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;


}




# 52 "include/windows.h" 2


 
# 1 "include/Windows32/Functions.h" 1
 



























 





extern "C" {


 



# 1 "include/Windows32/UnicodeFunctions.h" 1
 




























 





extern "C" {


WINBOOL
 
GetBinaryTypeW(
    LPCWSTR lpApplicationName,
    LPDWORD lpBinaryType
    );

DWORD
 
GetShortPathNameW(
    LPCWSTR lpszLongPath,
    LPWSTR  lpszShortPath,
    DWORD    cchBuffer
    );

LPWSTR
 
GetEnvironmentStringsW(
    void 
    );

WINBOOL
 
FreeEnvironmentStringsW(
    LPWSTR
    );

DWORD
 
FormatMessageW(
    DWORD dwFlags,
    LPCVOID lpSource,
    DWORD dwMessageId,
    DWORD dwLanguageId,
    LPWSTR lpBuffer,
    DWORD nSize,
    __gnuc_va_list  *Arguments
    );

HANDLE
 
CreateMailslotW(
    LPCWSTR lpName,
    DWORD nMaxMessageSize,
    DWORD lReadTimeout,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

int
 
lstrcmpW(
    LPCWSTR lpString1,
    LPCWSTR lpString2
    );

int
 
lstrcmpiW(
    LPCWSTR lpString1,
    LPCWSTR lpString2
    );

LPWSTR
 
lstrcpynW(
    LPWSTR lpString1,
    LPCWSTR lpString2,
    int iMaxLength
    );

LPWSTR
 
lstrcpyW(
    LPWSTR lpString1,
    LPCWSTR lpString2
    );

LPWSTR
 
lstrcatW(
    LPWSTR lpString1,
    LPCWSTR lpString2
    );

int
 
lstrlenW(
    LPCWSTR lpString
    );

HANDLE
 
CreateMutexW(
    LPSECURITY_ATTRIBUTES lpMutexAttributes,
    WINBOOL bInitialOwner,
    LPCWSTR lpName
    );

HANDLE
 
OpenMutexW(
    DWORD dwDesiredAccess,
    WINBOOL bInheritHandle,
    LPCWSTR lpName
    );

HANDLE
 
CreateEventW(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    WINBOOL bManualReset,
    WINBOOL bInitialState,
    LPCWSTR lpName
    );

HANDLE
 
OpenEventW(
    DWORD dwDesiredAccess,
    WINBOOL bInheritHandle,
    LPCWSTR lpName
    );

HANDLE
 
CreateSemaphoreW(
		 LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
		 LONG lInitialCount,
		 LONG lMaximumCount,
		 LPCWSTR lpName
		 );

HANDLE
 
OpenSemaphoreW(
    DWORD dwDesiredAccess,
    WINBOOL bInheritHandle,
    LPCWSTR lpName
    );

HANDLE
 
CreateFileMappingW(
    HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    DWORD flProtect,
    DWORD dwMaximumSizeHigh,
    DWORD dwMaximumSizeLow,
    LPCWSTR lpName
    );

HANDLE
 
OpenFileMappingW(
    DWORD dwDesiredAccess,
    WINBOOL bInheritHandle,
    LPCWSTR lpName
    );

DWORD
 
GetLogicalDriveStringsW(
    DWORD nBufferLength,
    LPWSTR lpBuffer
    );

HINSTANCE
 
LoadLibraryW(
    LPCWSTR lpLibFileName
    );

HINSTANCE
 
LoadLibraryExW(
    LPCWSTR lpLibFileName,
    HANDLE hFile,
    DWORD dwFlags
    );

DWORD
 
GetModuleFileNameW(
    HINSTANCE hModule,
    LPWSTR lpFilename,
    DWORD nSize
    );

HMODULE
 
GetModuleHandleW(
    LPCWSTR lpModuleName
    );

void 
 
FatalAppExitW(
    UINT uAction,
    LPCWSTR lpMessageText
    );

LPWSTR
 
GetCommandLineW(
    void 
    );

DWORD
 
GetEnvironmentVariableW(
    LPCWSTR lpName,
    LPWSTR lpBuffer,
    DWORD nSize
    );

WINBOOL
 
SetEnvironmentVariableW(
    LPCWSTR lpName,
    LPCWSTR lpValue
    );

DWORD
 
ExpandEnvironmentStringsW(
    LPCWSTR lpSrc,
    LPWSTR lpDst,
    DWORD nSize
    );

void 
 
OutputDebugStringW(
    LPCWSTR lpOutputString
    );

HRSRC
 
FindResourceW(
    HINSTANCE hModule,
    LPCWSTR lpName,
    LPCWSTR lpType
    );

HRSRC
 
FindResourceExW(
    HINSTANCE hModule,
    LPCWSTR lpType,
    LPCWSTR lpName,
    WORD    wLanguage
    );

WINBOOL
 
EnumResourceTypesW(
    HINSTANCE hModule,
    ENUMRESTYPEPROC lpEnumFunc,
    LONG lParam
    );

WINBOOL
 
EnumResourceNamesW(
    HINSTANCE hModule,
    LPCWSTR lpType,
    ENUMRESNAMEPROC lpEnumFunc,
    LONG lParam
    );

WINBOOL
 
EnumResourceLanguagesW(
    HINSTANCE hModule,
    LPCWSTR lpType,
    LPCWSTR lpName,
    ENUMRESLANGPROC lpEnumFunc,
    LONG lParam
    );

HANDLE
 
BeginUpdateResourceW(
    LPCWSTR pFileName,
    WINBOOL bDeleteExistingResources
    );

WINBOOL
 
UpdateResourceW(
    HANDLE      hUpdate,
    LPCWSTR     lpType,
    LPCWSTR     lpName,
    WORD        wLanguage,
    LPVOID      lpData,
    DWORD       cbData
    );

WINBOOL
 
EndUpdateResourceW(
    HANDLE      hUpdate,
    WINBOOL        fDiscard
    );

ATOM
 
GlobalAddAtomW(
    LPCWSTR lpString
    );

ATOM
 
GlobalFindAtomW(
    LPCWSTR lpString
    );

UINT
 
GlobalGetAtomNameW(
    ATOM nAtom,
    LPWSTR lpBuffer,
    int nSize
    );

ATOM
 
AddAtomW(
    LPCWSTR lpString
    );

ATOM
 
FindAtomW(
    LPCWSTR lpString
    );

UINT
 
GetAtomNameW(
    ATOM nAtom,
    LPWSTR lpBuffer,
    int nSize
    );

UINT
 
GetProfileIntW(
    LPCWSTR lpAppName,
    LPCWSTR lpKeyName,
    INT nDefault
    );

DWORD
 
GetProfileStringW(
    LPCWSTR lpAppName,
    LPCWSTR lpKeyName,
    LPCWSTR lpDefault,
    LPWSTR lpReturnedString,
    DWORD nSize
    );

WINBOOL
 
WriteProfileStringW(
    LPCWSTR lpAppName,
    LPCWSTR lpKeyName,
    LPCWSTR lpString
    );

DWORD
 
GetProfileSectionW(
    LPCWSTR lpAppName,
    LPWSTR lpReturnedString,
    DWORD nSize
    );

WINBOOL
 
WriteProfileSectionW(
    LPCWSTR lpAppName,
    LPCWSTR lpString
    );

UINT
 
GetPrivateProfileIntW(
    LPCWSTR lpAppName,
    LPCWSTR lpKeyName,
    INT nDefault,
    LPCWSTR lpFileName
    );

DWORD
 
GetPrivateProfileStringW(
    LPCWSTR lpAppName,
    LPCWSTR lpKeyName,
    LPCWSTR lpDefault,
    LPWSTR lpReturnedString,
    DWORD nSize,
    LPCWSTR lpFileName
    );

WINBOOL
 
WritePrivateProfileStringW(
    LPCWSTR lpAppName,
    LPCWSTR lpKeyName,
    LPCWSTR lpString,
    LPCWSTR lpFileName
    );

DWORD
 
GetPrivateProfileSectionW(
    LPCWSTR lpAppName,
    LPWSTR lpReturnedString,
    DWORD nSize,
    LPCWSTR lpFileName
    );

WINBOOL
 
WritePrivateProfileSectionW(
    LPCWSTR lpAppName,
    LPCWSTR lpString,
    LPCWSTR lpFileName
    );

UINT
 
GetDriveTypeW(
    LPCWSTR lpRootPathName
    );

UINT
 
GetSystemDirectoryW(
    LPWSTR lpBuffer,
    UINT uSize
    );

DWORD
 
GetTempPathW(
    DWORD nBufferLength,
    LPWSTR lpBuffer
    );

UINT
 
GetTempFileNameW(
    LPCWSTR lpPathName,
    LPCWSTR lpPrefixString,
    UINT uUnique,
    LPWSTR lpTempFileName
    );

UINT
 
GetWindowsDirectoryW(
    LPWSTR lpBuffer,
    UINT uSize
    );

WINBOOL
 
SetCurrentDirectoryW(
    LPCWSTR lpPathName
    );

DWORD
 
GetCurrentDirectoryW(
    DWORD nBufferLength,
    LPWSTR lpBuffer
    );

WINBOOL
 
GetDiskFreeSpaceW(
    LPCWSTR lpRootPathName,
    LPDWORD lpSectorsPerCluster,
    LPDWORD lpBytesPerSector,
    LPDWORD lpNumberOfFreeClusters,
    LPDWORD lpTotalNumberOfClusters
    );

WINBOOL
 
CreateDirectoryW(
    LPCWSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

WINBOOL
 
CreateDirectoryExW(
    LPCWSTR lpTemplateDirectory,
    LPCWSTR lpNewDirectory,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

WINBOOL
 
RemoveDirectoryW(
    LPCWSTR lpPathName
    );

DWORD
 
GetFullPathNameW(
    LPCWSTR lpFileName,
    DWORD nBufferLength,
    LPWSTR lpBuffer,
    LPWSTR *lpFilePart
    );

WINBOOL
 
DefineDosDeviceW(
    DWORD dwFlags,
    LPCWSTR lpDeviceName,
    LPCWSTR lpTargetPath
    );

DWORD
 
QueryDosDeviceW(
    LPCWSTR lpDeviceName,
    LPWSTR lpTargetPath,
    DWORD ucchMax
    );

HANDLE
 
CreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );

WINBOOL
 
SetFileAttributesW(
    LPCWSTR lpFileName,
    DWORD dwFileAttributes
    );

DWORD
 
GetFileAttributesW(
    LPCWSTR lpFileName
    );

DWORD
 
GetCompressedFileSizeW(
    LPCWSTR lpFileName,
    LPDWORD lpFileSizeHigh
    );

WINBOOL
 
DeleteFileW(
    LPCWSTR lpFileName
    );

DWORD
 
SearchPathW(
    LPCWSTR lpPath,
    LPCWSTR lpFileName,
    LPCWSTR lpExtension,
    DWORD nBufferLength,
    LPWSTR lpBuffer,
    LPWSTR *lpFilePart
    );

WINBOOL
 
CopyFileW(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName,
    WINBOOL bFailIfExists
    );

WINBOOL
 
MoveFileW(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName
    );

WINBOOL
 
MoveFileExW(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName,
    DWORD dwFlags
    );

HANDLE
 
CreateNamedPipeW(
    LPCWSTR lpName,
    DWORD dwOpenMode,
    DWORD dwPipeMode,
    DWORD nMaxInstances,
    DWORD nOutBufferSize,
    DWORD nInBufferSize,
    DWORD nDefaultTimeOut,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

WINBOOL
 
GetNamedPipeHandleStateW(
    HANDLE hNamedPipe,
    LPDWORD lpState,
    LPDWORD lpCurInstances,
    LPDWORD lpMaxCollectionCount,
    LPDWORD lpCollectDataTimeout,
    LPWSTR lpUserName,
    DWORD nMaxUserNameSize
    );

WINBOOL
 
CallNamedPipeW(
    LPCWSTR lpNamedPipeName,
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesRead,
    DWORD nTimeOut
    );

WINBOOL
 
WaitNamedPipeW(
    LPCWSTR lpNamedPipeName,
    DWORD nTimeOut
    );

WINBOOL
 
SetVolumeLabelW(
    LPCWSTR lpRootPathName,
    LPCWSTR lpVolumeName
    );

WINBOOL
 
GetVolumeInformationW(
    LPCWSTR lpRootPathName,
    LPWSTR lpVolumeNameBuffer,
    DWORD nVolumeNameSize,
    LPDWORD lpVolumeSerialNumber,
    LPDWORD lpMaximumComponentLength,
    LPDWORD lpFileSystemFlags,
    LPWSTR lpFileSystemNameBuffer,
    DWORD nFileSystemNameSize
    );

WINBOOL
 
ClearEventLogW (
    HANDLE hEventLog,
    LPCWSTR lpBackupFileName
    );

WINBOOL
 
BackupEventLogW (
    HANDLE hEventLog,
    LPCWSTR lpBackupFileName
    );

HANDLE
 
OpenEventLogW (
    LPCWSTR lpUNCServerName,
    LPCWSTR lpSourceName
    );

HANDLE
 
RegisterEventSourceW (
    LPCWSTR lpUNCServerName,
    LPCWSTR lpSourceName
    );

HANDLE
 
OpenBackupEventLogW (
    LPCWSTR lpUNCServerName,
    LPCWSTR lpFileName
    );

WINBOOL
 
ReadEventLogW (
     HANDLE     hEventLog,
     DWORD      dwReadFlags,
     DWORD      dwRecordOffset,
     LPVOID     lpBuffer,
     DWORD      nNumberOfBytesToRead,
     DWORD      *pnBytesRead,
     DWORD      *pnMinNumberOfBytesNeeded
    );

WINBOOL
 
ReportEventW (
     HANDLE     hEventLog,
     WORD       wType,
     WORD       wCategory,
     DWORD      dwEventID,
     PSID       lpUserSid,
     WORD       wNumStrings,
     DWORD      dwDataSize,
     LPCWSTR   *lpStrings,
     LPVOID     lpRawData
    );

WINBOOL
 
AccessCheckAndAuditAlarmW (
    LPCWSTR SubsystemName,
    LPVOID HandleId,
    LPWSTR ObjectTypeName,
    LPWSTR ObjectName,
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    DWORD DesiredAccess,
    PGENERIC_MAPPING GenericMapping,
    WINBOOL ObjectCreation,
    LPDWORD GrantedAccess,
    LPBOOL AccessStatus,
    LPBOOL pfGenerateOnClose
    );

WINBOOL
 
ObjectOpenAuditAlarmW (
    LPCWSTR SubsystemName,
    LPVOID HandleId,
    LPWSTR ObjectTypeName,
    LPWSTR ObjectName,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    HANDLE ClientToken,
    DWORD DesiredAccess,
    DWORD GrantedAccess,
    PPRIVILEGE_SET Privileges,
    WINBOOL ObjectCreation,
    WINBOOL AccessGranted,
    LPBOOL GenerateOnClose
    );

WINBOOL
 
ObjectPrivilegeAuditAlarmW (
    LPCWSTR SubsystemName,
    LPVOID HandleId,
    HANDLE ClientToken,
    DWORD DesiredAccess,
    PPRIVILEGE_SET Privileges,
    WINBOOL AccessGranted
    );

WINBOOL
 
ObjectCloseAuditAlarmW (
    LPCWSTR SubsystemName,
    LPVOID HandleId,
    WINBOOL GenerateOnClose
    );

WINBOOL
 
PrivilegedServiceAuditAlarmW (
    LPCWSTR SubsystemName,
    LPCWSTR ServiceName,
    HANDLE ClientToken,
    PPRIVILEGE_SET Privileges,
    WINBOOL AccessGranted
    );

WINBOOL
 
SetFileSecurityW (
    LPCWSTR lpFileName,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor
    );

WINBOOL
 
GetFileSecurityW (
    LPCWSTR lpFileName,
    SECURITY_INFORMATION RequestedInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD nLength,
    LPDWORD lpnLengthNeeded
    );

HANDLE
 
FindFirstChangeNotificationW(
    LPCWSTR lpPathName,
    WINBOOL bWatchSubtree,
    DWORD dwNotifyFilter
    );

WINBOOL
 
IsBadStringPtrW(
    LPCWSTR lpsz,
    UINT ucchMax
    );

WINBOOL
 
LookupAccountSidW(
    LPCWSTR lpSystemName,
    PSID Sid,
    LPWSTR Name,
    LPDWORD cbName,
    LPWSTR ReferencedDomainName,
    LPDWORD cbReferencedDomainName,
    PSID_NAME_USE peUse
    );

WINBOOL
 
LookupAccountNameW(
    LPCWSTR lpSystemName,
    LPCWSTR lpAccountName,
    PSID Sid,
    LPDWORD cbSid,
    LPWSTR ReferencedDomainName,
    LPDWORD cbReferencedDomainName,
    PSID_NAME_USE peUse
    );

WINBOOL
 
LookupPrivilegeValueW(
    LPCWSTR lpSystemName,
    LPCWSTR lpName,
    PLUID   lpLuid
    );

WINBOOL
 
LookupPrivilegeNameW(
    LPCWSTR lpSystemName,
    PLUID   lpLuid,
    LPWSTR lpName,
    LPDWORD cbName
    );

WINBOOL
 
LookupPrivilegeDisplayNameW(
    LPCWSTR lpSystemName,
    LPCWSTR lpName,
    LPWSTR lpDisplayName,
    LPDWORD cbDisplayName,
    LPDWORD lpLanguageId
    );

WINBOOL
 
BuildCommDCBW(
    LPCWSTR lpDef,
    LPDCB lpDCB
    );

WINBOOL
 
BuildCommDCBAndTimeoutsW(
    LPCWSTR lpDef,
    LPDCB lpDCB,
    LPCOMMTIMEOUTS lpCommTimeouts
    );

WINBOOL
 
CommConfigDialogW(
    LPCWSTR lpszName,
    HWND hWnd,
    LPCOMMCONFIG lpCC
    );

WINBOOL
 
GetDefaultCommConfigW(
    LPCWSTR lpszName,
    LPCOMMCONFIG lpCC,
    LPDWORD lpdwSize
    );

WINBOOL
 
SetDefaultCommConfigW(
    LPCWSTR lpszName,
    LPCOMMCONFIG lpCC,
    DWORD dwSize
    );

WINBOOL
 
GetComputerNameW (
    LPWSTR lpBuffer,
    LPDWORD nSize
    );

WINBOOL
 
SetComputerNameW (
    LPCWSTR lpComputerName
    );

WINBOOL
 
GetUserNameW (
    LPWSTR lpBuffer,
    LPDWORD nSize
    );

int
 
wvsprintfW(
    LPWSTR,
    LPCWSTR,
    __gnuc_va_list  arglist);

int
 
wsprintfW(LPWSTR, LPCWSTR, ...);

HKL
 
LoadKeyboardLayoutW(
    LPCWSTR pwszKLID,
    UINT Flags);

WINBOOL
 
GetKeyboardLayoutNameW(
    LPWSTR pwszKLID);

HDESK
 
CreateDesktopW(
    LPWSTR lpszDesktop,
    LPWSTR lpszDevice,
    LPDEVMODE pDevmode,
    DWORD dwFlags,
    DWORD dwDesiredAccess,
    LPSECURITY_ATTRIBUTES lpsa);

HDESK
 
OpenDesktopW(
    LPWSTR lpszDesktop,
    DWORD dwFlags,
    WINBOOL fInherit,
    DWORD dwDesiredAccess);

WINBOOL
 
EnumDesktopsW(
    HWINSTA hwinsta,
    DESKTOPENUMPROC lpEnumFunc,
    LPARAM lParam);

HWINSTA
 
CreateWindowStationW(
    LPWSTR lpwinsta,
    DWORD dwReserved,
    DWORD dwDesiredAccess,
    LPSECURITY_ATTRIBUTES lpsa);

HWINSTA
 
OpenWindowStationW(
    LPWSTR lpszWinSta,
    WINBOOL fInherit,
    DWORD dwDesiredAccess);

WINBOOL
 
EnumWindowStationsW(
    ENUMWINDOWSTATIONPROC lpEnumFunc,
    LPARAM lParam);

WINBOOL
 
GetUserObjectInformationW(
    HANDLE hObj,
    int nIndex,
    PVOID pvInfo,
    DWORD nLength,
    LPDWORD lpnLengthNeeded);

WINBOOL
 
SetUserObjectInformationW(
    HANDLE hObj,
    int nIndex,
    PVOID pvInfo,
    DWORD nLength);

UINT
 
RegisterWindowMessageW(
    LPCWSTR lpString);

WINBOOL
 
GetMessageW(
    LPMSG lpMsg,
    HWND hWnd ,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax);

LONG
 
DispatchMessageW(
    const  MSG *lpMsg);

WINBOOL
 
PeekMessageW(
    LPMSG lpMsg,
    HWND hWnd ,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax,
    UINT wRemoveMsg);

LRESULT
 
SendMessageW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

LRESULT
 
SendMessageTimeoutW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam,
    UINT fuFlags,
    UINT uTimeout,
    LPDWORD lpdwResult);

WINBOOL
 
SendNotifyMessageW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

WINBOOL
 
SendMessageCallbackW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam,
    SENDASYNCPROC lpResultCallBack,
    DWORD dwData);

WINBOOL
 
PostMessageW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

WINBOOL
 
PostThreadMessageW(
    DWORD idThread,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

LRESULT
 
DefWindowProcW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

LRESULT
 
CallWindowProcW(
    WNDPROC lpPrevWndFunc,
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

ATOM
 
RegisterClassW(
    const  WNDCLASS *lpWndClass);

WINBOOL
 
UnregisterClassW(
    LPCWSTR lpClassName,
    HINSTANCE hInstance);

WINBOOL
 
GetClassInfoW(
    HINSTANCE hInstance ,
    LPCWSTR lpClassName,
    LPWNDCLASS lpWndClass);

ATOM
 
RegisterClassExW(const  WNDCLASSEX *);

WINBOOL
 
GetClassInfoExW(HINSTANCE, LPCWSTR, LPWNDCLASSEX);

HWND
 
CreateWindowExW(
    DWORD dwExStyle,
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent ,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam);

HWND
 
CreateDialogParamW(
    HINSTANCE hInstance,
    LPCWSTR lpTemplateName,
    HWND hWndParent ,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);

HWND
 
CreateDialogIndirectParamW(
    HINSTANCE hInstance,
    LPCDLGTEMPLATE lpTemplate,
    HWND hWndParent,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);

int
 
DialogBoxParamW(
    HINSTANCE hInstance,
    LPCWSTR lpTemplateName,
    HWND hWndParent ,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);

int
 
DialogBoxIndirectParamW(
    HINSTANCE hInstance,
    LPCDLGTEMPLATE hDialogTemplate,
    HWND hWndParent ,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);

WINBOOL
 
SetDlgItemTextW(
    HWND hDlg,
    int nIDDlgItem,
    LPCWSTR lpString);

UINT
 
GetDlgItemTextW(
    HWND hDlg,
    int nIDDlgItem,
    LPWSTR lpString,
    int nMaxCount);

LONG
 
SendDlgItemMessageW(
    HWND hDlg,
    int nIDDlgItem,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

LRESULT
 
DefDlgProcW(
    HWND hDlg,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);

WINBOOL
 
CallMsgFilterW(
    LPMSG lpMsg,
    int nCode);

UINT
 
RegisterClipboardFormatW(
    LPCWSTR lpszFormat);

int
 
GetClipboardFormatNameW(
    UINT format,
    LPWSTR lpszFormatName,
    int cchMaxCount);

WINBOOL
 
CharToOemW(
    LPCWSTR lpszSrc,
    LPSTR lpszDst);

WINBOOL
 
OemToCharW(
    LPCSTR lpszSrc,
    LPWSTR lpszDst);

WINBOOL
 
CharToOemBuffW(
    LPCWSTR lpszSrc,
    LPSTR lpszDst,
    DWORD cchDstLength);

WINBOOL
 
OemToCharBuffW(
    LPCSTR lpszSrc,
    LPWSTR lpszDst,
    DWORD cchDstLength);

LPWSTR
 
CharUpperW(
    LPWSTR lpsz);

DWORD
 
CharUpperBuffW(
    LPWSTR lpsz,
    DWORD cchLength);

LPWSTR
 
CharLowerW(
    LPWSTR lpsz);

DWORD
 
CharLowerBuffW(
    LPWSTR lpsz,
    DWORD cchLength);

LPWSTR
 
CharNextW(
    LPCWSTR lpsz);

LPWSTR
 
CharPrevW(
    LPCWSTR lpszStart,
    LPCWSTR lpszCurrent);

WINBOOL
 
IsCharAlphaW(
    WCHAR ch);

WINBOOL
 
IsCharAlphaNumericW(
    WCHAR ch);

WINBOOL
 
IsCharUpperW(
    WCHAR ch);

WINBOOL
 
IsCharLowerW(
    WCHAR ch);

int
 
GetKeyNameTextW(
    LONG lParam,
    LPWSTR lpString,
    int nSize
    );

SHORT
 
VkKeyScanW(
    WCHAR ch);

SHORT
  VkKeyScanExW(
    WCHAR  ch,
    HKL   dwhkl);

UINT
 
MapVirtualKeyW(
    UINT uCode,
    UINT uMapType);

UINT
 
MapVirtualKeyExW(
    UINT uCode,
    UINT uMapType,
    HKL dwhkl);

HACCEL
 
LoadAcceleratorsW(
    HINSTANCE hInstance,
    LPCWSTR lpTableName);

HACCEL
 
CreateAcceleratorTableW(
    LPACCEL, int);

int
 
CopyAcceleratorTableW(
    HACCEL hAccelSrc,
    LPACCEL lpAccelDst,
    int cAccelEntries);

int
 
TranslateAcceleratorW(
    HWND hWnd,
    HACCEL hAccTable,
    LPMSG lpMsg);

HMENU
 
LoadMenuW(
    HINSTANCE hInstance,
    LPCWSTR lpMenuName);

HMENU
 
LoadMenuIndirectW(
    const  MENUTEMPLATE *lpMenuTemplate);

WINBOOL
 
ChangeMenuW(
    HMENU hMenu,
    UINT cmd,
    LPCWSTR lpszNewItem,
    UINT cmdInsert,
    UINT flags);

int
 
GetMenuStringW(
    HMENU hMenu,
    UINT uIDItem,
    LPWSTR lpString,
    int nMaxCount,
    UINT uFlag);

WINBOOL
 
InsertMenuW(
    HMENU hMenu,
    UINT uPosition,
    UINT uFlags,
    UINT uIDNewItem,
    LPCWSTR lpNewItem
    );

WINBOOL
 
AppendMenuW(
    HMENU hMenu,
    UINT uFlags,
    UINT uIDNewItem,
    LPCWSTR lpNewItem
    );

WINBOOL
 
ModifyMenuW(
    HMENU hMnu,
    UINT uPosition,
    UINT uFlags,
    UINT uIDNewItem,
    LPCWSTR lpNewItem
    );

WINBOOL
 
InsertMenuItemW(
    HMENU,
    UINT,
    WINBOOL,
    LPCMENUITEMINFO
    );

WINBOOL
 
GetMenuItemInfoW(
    HMENU,
    UINT,
    WINBOOL,
    LPMENUITEMINFO
    );

WINBOOL
 
SetMenuItemInfoW(
    HMENU,
    UINT,
    WINBOOL,
    LPCMENUITEMINFO
    );

int
 
DrawTextW(
    HDC hDC,
    LPCWSTR lpString,
    int nCount,
    LPRECT lpRect,
    UINT uFormat);

int
 
DrawTextExW(HDC, LPWSTR, int, LPRECT, UINT, LPDRAWTEXTPARAMS);

WINBOOL
 
GrayStringW(
    HDC hDC,
    HBRUSH hBrush,
    GRAYSTRINGPROC lpOutputFunc,
    LPARAM lpData,
    int nCount,
    int X,
    int Y,
    int nWidth,
    int nHeight);

WINBOOL   DrawStateW(HDC, HBRUSH, DRAWSTATEPROC, LPARAM, WPARAM, int, int, int, int, UINT);

LONG
 
TabbedTextOutW(
    HDC hDC,
    int X,
    int Y,
    LPCWSTR lpString,
    int nCount,
    int nTabPositions,
    LPINT lpnTabStopPositions,
    int nTabOrigin);

DWORD
 
GetTabbedTextExtentW(
    HDC hDC,
    LPCWSTR lpString,
    int nCount,
    int nTabPositions,
    LPINT lpnTabStopPositions);

WINBOOL
 
SetPropW(
    HWND hWnd,
    LPCWSTR lpString,
    HANDLE hData);

HANDLE
 
GetPropW(
    HWND hWnd,
    LPCWSTR lpString);

HANDLE
 
RemovePropW(
    HWND hWnd,
    LPCWSTR lpString);

int
 
EnumPropsExW(
    HWND hWnd,
    PROPENUMPROCEX lpEnumFunc,
    LPARAM lParam);

int
 
EnumPropsW(
    HWND hWnd,
    PROPENUMPROC lpEnumFunc);

WINBOOL
 
SetWindowTextW(
    HWND hWnd,
    LPCWSTR lpString);

int
 
GetWindowTextW(
    HWND hWnd,
    LPWSTR lpString,
    int nMaxCount);

int
 
GetWindowTextLengthW(
    HWND hWnd);

int
 
MessageBoxW(
    HWND hWnd ,
    LPCWSTR lpText,
    LPCWSTR lpCaption,
    UINT uType);

int
 
MessageBoxExW(
    HWND hWnd ,
    LPCWSTR lpText,
    LPCWSTR lpCaption,
    UINT uType,
    WORD wLanguageId);

int
 
MessageBoxIndirectW(LPMSGBOXPARAMS);

LONG
 
GetWindowLongW(
    HWND hWnd,
    int nIndex);

LONG
 
SetWindowLongW(
    HWND hWnd,
    int nIndex,
    LONG dwNewLong);

DWORD
 
GetClassLongW(
    HWND hWnd,
    int nIndex);

DWORD
 
SetClassLongW(
    HWND hWnd,
    int nIndex,
    LONG dwNewLong);

HWND
 
FindWindowW(
    LPCWSTR lpClassName ,
    LPCWSTR lpWindowName);

HWND
 
FindWindowExW(HWND, HWND, LPCWSTR, LPCWSTR);

int
 
GetClassNameW(
    HWND hWnd,
    LPWSTR lpClassName,
    int nMaxCount);

HHOOK
 
SetWindowsHookExW(
    int idHook,
    HOOKPROC lpfn,
    HINSTANCE hmod,
    DWORD dwThreadId);

HBITMAP
 
LoadBitmapW(
    HINSTANCE hInstance,
    LPCWSTR lpBitmapName);

HCURSOR
 
LoadCursorW(
    HINSTANCE hInstance,
    LPCWSTR lpCursorName);

HCURSOR
 
LoadCursorFromFileW(
    LPCWSTR    lpFileName);

HICON
 
LoadIconW(
    HINSTANCE hInstance,
    LPCWSTR lpIconName);

HANDLE
 
LoadImageW(
    HINSTANCE,
    LPCWSTR,
    UINT,
    int,
    int,
    UINT);

int
 
LoadStringW(
    HINSTANCE hInstance,
    UINT uID,
    LPWSTR lpBuffer,
    int nBufferMax);

WINBOOL
 
IsDialogMessageW(
    HWND hDlg,
    LPMSG lpMsg);

int
 
DlgDirListW(
    HWND hDlg,
    LPWSTR lpPathSpec,
    int nIDListBox,
    int nIDStaticPath,
    UINT uFileType);

WINBOOL
 
DlgDirSelectExW(
    HWND hDlg,
    LPWSTR lpString,
    int nCount,
    int nIDListBox);

int
 
DlgDirListComboBoxW(
    HWND hDlg,
    LPWSTR lpPathSpec,
    int nIDComboBox,
    int nIDStaticPath,
    UINT uFiletype);

WINBOOL
 
DlgDirSelectComboBoxExW(
    HWND hDlg,
    LPWSTR lpString,
    int nCount,
    int nIDComboBox);

LRESULT
 
DefFrameProcW(
    HWND hWnd,
    HWND hWndMDIClient ,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam);

LRESULT
 
DefMDIChildProcW(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam);

HWND
 
CreateMDIWindowW(
    LPWSTR lpClassName,
    LPWSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HINSTANCE hInstance,
    LPARAM lParam
    );

WINBOOL
 
WinHelpW(
    HWND hWndMain,
    LPCWSTR lpszHelp,
    UINT uCommand,
    DWORD dwData
    );

LONG
 
ChangeDisplaySettingsW(
    LPDEVMODE lpDevMode,
    DWORD dwFlags);

WINBOOL
 
EnumDisplaySettingsW(
    LPCWSTR lpszDeviceName,
    DWORD iModeNum,
    LPDEVMODE lpDevMode);

WINBOOL
 
SystemParametersInfoW(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni);

int
 
AddFontResourceW(LPCWSTR);

HMETAFILE
 
CopyMetaFileW(HMETAFILE, LPCWSTR);

HFONT
 
CreateFontIndirectW(const  LOGFONT *);

HFONT
 
CreateFontW(int, int, int, int, int, DWORD,
                             DWORD, DWORD, DWORD, DWORD, DWORD,
                             DWORD, DWORD, LPCWSTR);

HDC
 
CreateICW(LPCWSTR, LPCWSTR , LPCWSTR , const  DEVMODE *);

HDC
 
CreateMetaFileW(LPCWSTR);

WINBOOL
 
CreateScalableFontResourceW(DWORD, LPCWSTR, LPCWSTR, LPCWSTR);

int
 
DeviceCapabilitiesW(LPCWSTR, LPCWSTR, WORD,
                                LPWSTR, const  DEVMODE *);

int
 
EnumFontFamiliesExW(HDC, LPLOGFONT, FONTENUMEXPROC, LPARAM, DWORD);

int
 
EnumFontFamiliesW(HDC, LPCWSTR, FONTENUMPROC, LPARAM);

int
 
EnumFontsW(HDC, LPCWSTR,  ENUMFONTSPROC, LPARAM);

WINBOOL
 
GetCharWidthW(HDC, UINT, UINT, LPINT);

WINBOOL
  
GetCharWidth32W(HDC, UINT, UINT, LPINT);

WINBOOL
 
GetCharWidthFloatW(HDC, UINT, UINT, PFLOAT);

WINBOOL
 
GetCharABCWidthsW(HDC, UINT, UINT, LPABC);

WINBOOL
 
GetCharABCWidthsFloatW(HDC, UINT, UINT, LPABCFLOAT);

DWORD
 
GetGlyphOutlineW(HDC, UINT, UINT, LPGLYPHMETRICS, DWORD, LPVOID, const  MAT2 *);

HMETAFILE
 
GetMetaFileW(LPCWSTR);

UINT
 
GetOutlineTextMetricsW(HDC, UINT, LPOUTLINETEXTMETRIC);

WINBOOL
  GetTextExtentPointW(
                    HDC,
                    LPCWSTR,
                    int,
                    LPSIZE
                    );

WINBOOL
 
GetTextExtentPoint32W(
                    HDC,
                    LPCWSTR,
                    int,
                    LPSIZE
                    );

WINBOOL
 
GetTextExtentExPointW(
                    HDC,
                    LPCWSTR,
                    int,
                    int,
                    LPINT,
                    LPINT,
                    LPSIZE
                    );

DWORD
 
GetCharacterPlacementW(HDC, LPCWSTR, int, int, LPGCP_RESULTS, DWORD);

HDC
 
ResetDCW(HDC, const  DEVMODE *);

WINBOOL
 
RemoveFontResourceW(LPCWSTR);

HENHMETAFILE
 
CopyEnhMetaFileW(HENHMETAFILE, LPCWSTR);

HDC
 
CreateEnhMetaFileW(HDC, LPCWSTR, const  RECT *, LPCWSTR);

HENHMETAFILE
 
GetEnhMetaFileW(LPCWSTR);

UINT
 
GetEnhMetaFileDescriptionW(HENHMETAFILE, UINT, LPWSTR );

WINBOOL
 
GetTextMetricsW(HDC, LPTEXTMETRIC);

int
 
StartDocW(HDC, const  DOCINFO *);

int
 
GetObjectW(HGDIOBJ, int, LPVOID);

WINBOOL
 
TextOutW(HDC, int, int, LPCWSTR, int);

WINBOOL
 
ExtTextOutW(HDC, int, int, UINT, const  RECT *,LPCWSTR, UINT, const  INT *);

WINBOOL
 
PolyTextOutW(HDC, const  POLYTEXT *, int);

int
 
GetTextFaceW(HDC, int, LPWSTR);

DWORD
 
GetKerningPairsW(HDC, DWORD, LPKERNINGPAIR);

WINBOOL
 
GetLogColorSpaceW(HCOLORSPACE,LPLOGCOLORSPACE,DWORD);

HCOLORSPACE
 
CreateColorSpaceW(LPLOGCOLORSPACE);

WINBOOL
 
GetICMProfileW(HDC,DWORD,LPWSTR);

WINBOOL
 
SetICMProfileW(HDC,LPWSTR);

WINBOOL
 
UpdateICMRegKeyW(DWORD, DWORD, LPWSTR, UINT);

int
 
EnumICMProfilesW(HDC,ICMENUMPROC,LPARAM);

HPROPSHEETPAGE
 
CreatePropertySheetPageW(LPCPROPSHEETPAGE lppsp);

int
 
PropertySheetW(LPCPROPSHEETHEADER lppsph);

HIMAGELIST
 
ImageList_LoadImageW(HINSTANCE hi, 
LPCWSTR lpbmp, 
int cx, 
int cGrow, 
COLORREF crMask, 
UINT uType, 
UINT uFlags);

HWND
 
CreateStatusWindowW(LONG style, LPCWSTR lpszText, HWND hwndParent, UINT wID);

void
 
DrawStatusTextW(HDC hDC, LPRECT lprc, LPCWSTR pszText, UINT uFlags);

WINBOOL
 
GetOpenFileNameW(LPOPENFILENAME);

WINBOOL
 
GetSaveFileNameW(LPOPENFILENAME);

short
 
GetFileTitleW(LPCWSTR, LPWSTR, WORD);

WINBOOL
 
ChooseColorW(LPCHOOSECOLOR);

HWND
 
ReplaceTextW(LPFINDREPLACE);

WINBOOL
 
ChooseFontW(LPCHOOSEFONT);

HWND
 
FindTextW(LPFINDREPLACE);

WINBOOL
 
PrintDlgW(LPPRINTDLG);

WINBOOL
 
PageSetupDlgW(LPPAGESETUPDLG);

WINBOOL
 
CreateProcessW(
    LPCWSTR lpApplicationName,
    LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    WINBOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );

void 
 
GetStartupInfoW(
    LPSTARTUPINFO lpStartupInfo
    );

HANDLE
 
FindFirstFileW(
    LPCWSTR lpFileName,
    LPWIN32_FIND_DATA lpFindFileData
    );

WINBOOL
 
FindNextFileW(
    HANDLE hFindFile,
    LPWIN32_FIND_DATA lpFindFileData
    );

WINBOOL
 
GetVersionExW(
    LPOSVERSIONINFO lpVersionInformation
    );


















HDC
 
CreateDCW(LPCWSTR, LPCWSTR , LPCWSTR , const  DEVMODE *);

HFONT
 
CreateFontA(int, int, int, int, int, DWORD,
                             DWORD, DWORD, DWORD, DWORD, DWORD,
                             DWORD, DWORD, LPCSTR);

DWORD
 
VerInstallFileW(
        DWORD uFlags,
        LPWSTR szSrcFileName,
        LPWSTR szDestFileName,
        LPWSTR szSrcDir,
        LPWSTR szDestDir,
        LPWSTR szCurDir,
        LPWSTR szTmpFile,
        PUINT lpuTmpFileLen
        );

DWORD
 
GetFileVersionInfoSizeW(
        LPWSTR lptstrFilename,
        LPDWORD lpdwHandle
        );

WINBOOL
 
GetFileVersionInfoW(
        LPWSTR lptstrFilename,
        DWORD dwHandle,
        DWORD dwLen,
        LPVOID lpData
        );

DWORD
 
VerLanguageNameW(
        DWORD wLang,
        LPWSTR szLang,
        DWORD nSize
        );

WINBOOL
 
VerQueryValueW(
        const LPVOID pBlock,
        LPWSTR lpSubBlock,
        LPVOID * lplpBuffer,
        PUINT puLen
        );

DWORD
 
VerFindFileW(
        DWORD uFlags,
        LPWSTR szFileName,
        LPWSTR szWinDir,
        LPWSTR szAppDir,
        LPWSTR szCurDir,
        PUINT lpuCurDirLen,
        LPWSTR szDestDir,
        PUINT lpuDestDirLen
        );

LONG
 
RegSetValueExW (
    HKEY hKey,
    LPCWSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    const  BYTE* lpData,
    DWORD cbData
    );

LONG
 
RegUnLoadKeyW (
    HKEY    hKey,
    LPCWSTR lpSubKey
    );

WINBOOL
 
InitiateSystemShutdownW(
    LPWSTR lpMachineName,
    LPWSTR lpMessage,
    DWORD dwTimeout,
    WINBOOL bForceAppsClosed,
    WINBOOL bRebootAfterShutdown
    );

WINBOOL
 
AbortSystemShutdownW(
    LPWSTR lpMachineName
    );

LONG
 
RegRestoreKeyW (
    HKEY hKey,
    LPCWSTR lpFile,
    DWORD   dwFlags
    );

LONG
 
RegSaveKeyW (
    HKEY hKey,
    LPCWSTR lpFile,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

LONG
 
RegSetValueW (
    HKEY hKey,
    LPCWSTR lpSubKey,
    DWORD dwType,
    LPCWSTR lpData,
    DWORD cbData
    );

LONG
 
RegQueryValueW (
    HKEY hKey,
    LPCWSTR lpSubKey,
    LPWSTR lpValue,
    PLONG   lpcbValue
    );

LONG
 
RegQueryMultipleValuesW (
    HKEY hKey,
    PVALENT val_list,
    DWORD num_vals,
    LPWSTR lpValueBuf,
    LPDWORD ldwTotsize
    );

LONG
 
RegQueryValueExW (
    HKEY hKey,
    LPCWSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    );

LONG
 
RegReplaceKeyW (
    HKEY     hKey,
    LPCWSTR  lpSubKey,
    LPCWSTR  lpNewFile,
    LPCWSTR  lpOldFile
    );

LONG
 
RegConnectRegistryW (
    LPWSTR lpMachineName,
    HKEY hKey,
    PHKEY phkResult
    );

LONG
 
RegCreateKeyW (
    HKEY hKey,
    LPCWSTR lpSubKey,
    PHKEY phkResult
    );

LONG
 
RegCreateKeyExW (
    HKEY hKey,
    LPCWSTR lpSubKey,
    DWORD Reserved,
    LPWSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
    );

LONG
 
RegDeleteKeyW (
    HKEY hKey,
    LPCWSTR lpSubKey
    );

LONG
 
RegDeleteValueW (
    HKEY hKey,
    LPCWSTR lpValueName
    );

LONG
 
RegEnumKeyW (
    HKEY hKey,
    DWORD dwIndex,
    LPWSTR lpName,
    DWORD cbName
    );

LONG
 
RegEnumKeyExW (
    HKEY hKey,
    DWORD dwIndex,
    LPWSTR lpName,
    LPDWORD lpcbName,
    LPDWORD lpReserved,
    LPWSTR lpClass,
    LPDWORD lpcbClass,
    PFILETIME lpftLastWriteTime
    );

LONG
 
RegEnumValueW (
    HKEY hKey,
    DWORD dwIndex,
    LPWSTR lpValueName,
    LPDWORD lpcbValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    );

LONG
 
RegLoadKeyW (
    HKEY    hKey,
    LPCWSTR  lpSubKey,
    LPCWSTR  lpFile
    );

LONG
 
RegOpenKeyW (
    HKEY hKey,
    LPCWSTR lpSubKey,
    PHKEY phkResult
    );

LONG
 
RegOpenKeyExW (
    HKEY hKey,
    LPCWSTR lpSubKey,
    DWORD ulOptions,
    REGSAM samDesired,
    PHKEY phkResult
    );

LONG
 
RegQueryInfoKeyW (
    HKEY hKey,
    LPWSTR lpClass,
    LPDWORD lpcbClass,
    LPDWORD lpReserved,
    LPDWORD lpcSubKeys,
    LPDWORD lpcbMaxSubKeyLen,
    LPDWORD lpcbMaxClassLen,
    LPDWORD lpcValues,
    LPDWORD lpcbMaxValueNameLen,
    LPDWORD lpcbMaxValueLen,
    LPDWORD lpcbSecurityDescriptor,
    PFILETIME lpftLastWriteTime
    );

int
 
CompareStringW(
    LCID     Locale,
    DWORD    dwCmpFlags,
    LPCWSTR lpString1,
    int      cchCount1,
    LPCWSTR lpString2,
    int      cchCount2);

int
 
LCMapStringW(
    LCID     Locale,
    DWORD    dwMapFlags,
    LPCWSTR lpSrcStr,
    int      cchSrc,
    LPWSTR  lpDestStr,
    int      cchDest);


int
 
GetLocaleInfoW(
    LCID     Locale,
    LCTYPE   LCType,
    LPWSTR  lpLCData,
    int      cchData);

WINBOOL
 
SetLocaleInfoW(
    LCID     Locale,
    LCTYPE   LCType,
    LPCWSTR lpLCData);

int
 
GetTimeFormatW(
    LCID     Locale,
    DWORD    dwFlags,
    const  SYSTEMTIME *lpTime,
    LPCWSTR lpFormat,
    LPWSTR  lpTimeStr,
    int      cchTime);

int
 
GetDateFormatW(
    LCID     Locale,
    DWORD    dwFlags,
    const  SYSTEMTIME *lpDate,
    LPCWSTR lpFormat,
    LPWSTR  lpDateStr,
    int      cchDate);

int
 
GetNumberFormatW(
    LCID     Locale,
    DWORD    dwFlags,
    LPCWSTR lpValue,
    const  NUMBERFMT *lpFormat,
    LPWSTR  lpNumberStr,
    int      cchNumber);

int
 
GetCurrencyFormatW(
    LCID     Locale,
    DWORD    dwFlags,
    LPCWSTR lpValue,
    const  CURRENCYFMT *lpFormat,
    LPWSTR  lpCurrencyStr,
    int      cchCurrency);

WINBOOL
 
EnumCalendarInfoW(
    CALINFO_ENUMPROC lpCalInfoEnumProc,
    LCID              Locale,
    CALID             Calendar,
    CALTYPE           CalType);

WINBOOL
 
EnumTimeFormatsW(
    TIMEFMT_ENUMPROC lpTimeFmtEnumProc,
    LCID              Locale,
    DWORD             dwFlags);

WINBOOL
 
EnumDateFormatsW(
    DATEFMT_ENUMPROC lpDateFmtEnumProc,
    LCID              Locale,
    DWORD             dwFlags);

WINBOOL
 
GetStringTypeExW(
    LCID     Locale,
    DWORD    dwInfoType,
    LPCWSTR lpSrcStr,
    int      cchSrc,
    LPWORD   lpCharType);

WINBOOL
 
GetStringTypeW(
    DWORD    dwInfoType,
    LPCWSTR  lpSrcStr,
    int      cchSrc,
    LPWORD   lpCharType);

int
 
FoldStringW(
    DWORD    dwMapFlags,
    LPCWSTR lpSrcStr,
    int      cchSrc,
    LPWSTR  lpDestStr,
    int      cchDest);

WINBOOL
 
EnumSystemLocalesW(
    LOCALE_ENUMPROC lpLocaleEnumProc,
    DWORD            dwFlags);

WINBOOL
 
EnumSystemCodePagesW(
    CODEPAGE_ENUMPROC lpCodePageEnumProc,
    DWORD              dwFlags);

WINBOOL
 
PeekConsoleInputW(
    HANDLE hConsoleInput,
    PINPUT_RECORD lpBuffer,
    DWORD nLength,
    LPDWORD lpNumberOfEventsRead
    );

WINBOOL
 
ReadConsoleInputW(
    HANDLE hConsoleInput,
    PINPUT_RECORD lpBuffer,
    DWORD nLength,
    LPDWORD lpNumberOfEventsRead
    );

WINBOOL
 
WriteConsoleInputW(
    HANDLE hConsoleInput,
    const  INPUT_RECORD *lpBuffer,
    DWORD nLength,
    LPDWORD lpNumberOfEventsWritten
    );

WINBOOL
 
ReadConsoleOutputW(
    HANDLE hConsoleOutput,
    PCHAR_INFO lpBuffer,
    COORD dwBufferSize,
    COORD dwBufferCoord,
    PSMALL_RECT lpReadRegion
    );

WINBOOL
 
WriteConsoleOutputW(
    HANDLE hConsoleOutput,
    const  CHAR_INFO *lpBuffer,
    COORD dwBufferSize,
    COORD dwBufferCoord,
    PSMALL_RECT lpWriteRegion
    );

WINBOOL
 
ReadConsoleOutputCharacterW(
    HANDLE hConsoleOutput,
    LPWSTR lpCharacter,
    DWORD nLength,
    COORD dwReadCoord,
    LPDWORD lpNumberOfCharsRead
    );

WINBOOL
 
WriteConsoleOutputCharacterW(
    HANDLE hConsoleOutput,
    LPCWSTR lpCharacter,
    DWORD nLength,
    COORD dwWriteCoord,
    LPDWORD lpNumberOfCharsWritten
    );

WINBOOL
 
FillConsoleOutputCharacterW(
    HANDLE hConsoleOutput,
    WCHAR  cCharacter,
    DWORD  nLength,
    COORD  dwWriteCoord,
    LPDWORD lpNumberOfCharsWritten
    );

WINBOOL
 
ScrollConsoleScreenBufferW(
    HANDLE hConsoleOutput,
    const  SMALL_RECT *lpScrollRectangle,
    const  SMALL_RECT *lpClipRectangle,
    COORD dwDestinationOrigin,
    const  CHAR_INFO *lpFill
    );

DWORD
 
GetConsoleTitleW(
    LPWSTR lpConsoleTitle,
    DWORD nSize
    );

WINBOOL
 
SetConsoleTitleW(
    LPCWSTR lpConsoleTitle
    );

WINBOOL
 
ReadConsoleW(
    HANDLE hConsoleInput,
    LPVOID lpBuffer,
    DWORD nNumberOfCharsToRead,
    LPDWORD lpNumberOfCharsRead,
    LPVOID lpReserved
    );

WINBOOL
 
WriteConsoleW(
    HANDLE hConsoleOutput,
    const  void  *lpBuffer,
    DWORD nNumberOfCharsToWrite,
    LPDWORD lpNumberOfCharsWritten,
    LPVOID lpReserved
    );

DWORD  
WNetAddConnectionW(
     LPCWSTR   lpRemoteName,
     LPCWSTR   lpPassword,
     LPCWSTR   lpLocalName
    );

DWORD  
WNetAddConnection2W(
     LPNETRESOURCE lpNetResource,
     LPCWSTR       lpPassword,
     LPCWSTR       lpUserName,
     DWORD          dwFlags
    );

DWORD  
WNetAddConnection3W(
     HWND           hwndOwner,
     LPNETRESOURCE lpNetResource,
     LPCWSTR       lpPassword,
     LPCWSTR       lpUserName,
     DWORD          dwFlags
    );

DWORD  
WNetCancelConnectionW(
     LPCWSTR lpName,
     WINBOOL     fForce
    );

DWORD  
WNetCancelConnection2W(
     LPCWSTR lpName,
     DWORD    dwFlags,
     WINBOOL     fForce
    );

DWORD  
WNetGetConnectionW(
     LPCWSTR lpLocalName,
     LPWSTR  lpRemoteName,
     LPDWORD  lpnLength
    );

DWORD  
WNetUseConnectionW(
    HWND            hwndOwner,
    LPNETRESOURCE  lpNetResource,
    LPCWSTR        lpUserID,
    LPCWSTR        lpPassword,
    DWORD           dwFlags,
    LPWSTR         lpAccessName,
    LPDWORD         lpBufferSize,
    LPDWORD         lpResult
    );

DWORD  
WNetSetConnectionW(
    LPCWSTR    lpName,
    DWORD       dwProperties,
    LPVOID      pvValues
    );

DWORD  
WNetConnectionDialog1W(
    LPCONNECTDLGSTRUCT lpConnDlgStruct
    );

DWORD  
WNetDisconnectDialog1W(
    LPDISCDLGSTRUCT lpConnDlgStruct
    );

DWORD  
WNetOpenEnumW(
     DWORD          dwScope,
     DWORD          dwType,
     DWORD          dwUsage,
     LPNETRESOURCE lpNetResource,
     LPHANDLE       lphEnum
    );

DWORD  
WNetEnumResourceW(
     HANDLE  hEnum,
     LPDWORD lpcCount,
     LPVOID  lpBuffer,
     LPDWORD lpBufferSize
    );

DWORD  
WNetGetUniversalNameW(
     LPCWSTR lpLocalPath,
     DWORD    dwInfoLevel,
     LPVOID   lpBuffer,
     LPDWORD  lpBufferSize
     );

DWORD  
WNetGetUserW(
     LPCWSTR  lpName,
     LPWSTR   lpUserName,
     LPDWORD   lpnLength
    );

DWORD  
WNetGetProviderNameW(
    DWORD   dwNetType,
    LPWSTR lpProviderName,
    LPDWORD lpBufferSize
    );

DWORD  
WNetGetNetworkInformationW(
    LPCWSTR          lpProvider,
    LPNETINFOSTRUCT   lpNetInfoStruct
    );

DWORD  
WNetGetLastErrorW(
     LPDWORD    lpError,
     LPWSTR    lpErrorBuf,
     DWORD      nErrorBufSize,
     LPWSTR    lpNameBuf,
     DWORD      nNameBufSize
    );

DWORD  
MultinetGetConnectionPerformanceW(
        LPNETRESOURCE lpNetResource,
        LPNETCONNECTINFOSTRUCT lpNetConnectInfoStruct
        );

WINBOOL
 
ChangeServiceConfigW(
    SC_HANDLE    hService,
    DWORD        dwServiceType,
    DWORD        dwStartType,
    DWORD        dwErrorControl,
    LPCWSTR     lpBinaryPathName,
    LPCWSTR     lpLoadOrderGroup,
    LPDWORD      lpdwTagId,
    LPCWSTR     lpDependencies,
    LPCWSTR     lpServiceStartName,
    LPCWSTR     lpPassword,
    LPCWSTR     lpDisplayName
    );

SC_HANDLE
 
CreateServiceW(
    SC_HANDLE    hSCManager,
    LPCWSTR     lpServiceName,
    LPCWSTR     lpDisplayName,
    DWORD        dwDesiredAccess,
    DWORD        dwServiceType,
    DWORD        dwStartType,
    DWORD        dwErrorControl,
    LPCWSTR     lpBinaryPathName,
    LPCWSTR     lpLoadOrderGroup,
    LPDWORD      lpdwTagId,
    LPCWSTR     lpDependencies,
    LPCWSTR     lpServiceStartName,
    LPCWSTR     lpPassword
    );

WINBOOL
 
EnumDependentServicesW(
    SC_HANDLE               hService,
    DWORD                   dwServiceState,
    LPENUM_SERVICE_STATUS  lpServices,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded,
    LPDWORD                 lpServicesReturned
    );

WINBOOL
 
EnumServicesStatusW(
    SC_HANDLE               hSCManager,
    DWORD                   dwServiceType,
    DWORD                   dwServiceState,
    LPENUM_SERVICE_STATUS  lpServices,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded,
    LPDWORD                 lpServicesReturned,
    LPDWORD                 lpResumeHandle
    );

WINBOOL
 
GetServiceKeyNameW(
    SC_HANDLE               hSCManager,
    LPCWSTR                lpDisplayName,
    LPWSTR                 lpServiceName,
    LPDWORD                 lpcchBuffer
    );

WINBOOL
 
GetServiceDisplayNameW(
    SC_HANDLE               hSCManager,
    LPCWSTR                lpServiceName,
    LPWSTR                 lpDisplayName,
    LPDWORD                 lpcchBuffer
    );

SC_HANDLE
 
OpenSCManagerW(
    LPCWSTR lpMachineName,
    LPCWSTR lpDatabaseName,
    DWORD   dwDesiredAccess
    );

SC_HANDLE
 
OpenServiceW(
    SC_HANDLE   hSCManager,
    LPCWSTR    lpServiceName,
    DWORD       dwDesiredAccess
    );

WINBOOL
 
QueryServiceConfigW(
    SC_HANDLE               hService,
    LPQUERY_SERVICE_CONFIG lpServiceConfig,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded
    );

WINBOOL
 
QueryServiceLockStatusW(
    SC_HANDLE                       hSCManager,
    LPQUERY_SERVICE_LOCK_STATUS    lpLockStatus,
    DWORD                           cbBufSize,
    LPDWORD                         pcbBytesNeeded
    );

SERVICE_STATUS_HANDLE
 
RegisterServiceCtrlHandlerW(
    LPCWSTR             lpServiceName,
    LPHANDLER_FUNCTION   lpHandlerProc
    );

WINBOOL
 
StartServiceCtrlDispatcherW(
    LPSERVICE_TABLE_ENTRY    lpServiceStartTable
    );

WINBOOL
 
StartServiceW(
    SC_HANDLE            hService,
    DWORD                dwNumServiceArgs,
    LPCWSTR             *lpServiceArgVectors
    );

 

WINBOOL  
wglUseFontBitmapsW(HDC, DWORD, DWORD, DWORD);

WINBOOL  
wglUseFontOutlinesW(HDC, DWORD, DWORD, DWORD, FLOAT,
		    FLOAT, int, LPGLYPHMETRICSFLOAT);

 
 

unsigned int   
DragQueryFileW(HDROP, unsigned int, LPCWSTR, unsigned int);

HICON   
ExtractAssociatedIconW (HINSTANCE, LPCWSTR, WORD *);

HICON   
ExtractIconW (HINSTANCE, const LPCWSTR, unsigned int);

HINSTANCE   
FindExecutableW (const LPCWSTR, const LPCWSTR, LPCWSTR);

int   
ShellAboutW (HWND, const LPCWSTR, const LPCWSTR, HICON);

HINSTANCE   
ShellExecuteW (HWND, const LPCWSTR, const LPCWSTR, LPCWSTR, const LPCWSTR, int);

 
 
 

HSZ   
DdeCreateStringHandleW (DWORD, LPCWSTR, int);

UINT   
DdeInitializeW (DWORD *, CALLB, DWORD, DWORD);

DWORD   
DdeQueryStringW (DWORD, HSZ, LPCWSTR, DWORD, int);

 
 

WINBOOL   LogonUserW (LPWSTR, LPWSTR, LPWSTR, DWORD, DWORD, HANDLE *);
WINBOOL   CreateProcessAsUserW (HANDLE, LPCWSTR, LPWSTR,
			SECURITY_ATTRIBUTES*, SECURITY_ATTRIBUTES*, WINBOOL,
			DWORD, LPVOID, LPCWSTR, STARTUPINFO*,
			PROCESS_INFORMATION*);


}



# 42 "include/Windows32/Functions.h" 2




# 1 "include/Windows32/ASCIIFunctions.h" 1
 



























 





extern "C" {


WINBOOL
 
GetBinaryTypeA(
	       LPCSTR lpApplicationName,
	       LPDWORD lpBinaryType
	       );

DWORD
 
GetShortPathNameA(
		  LPCSTR lpszLongPath,
		  LPSTR  lpszShortPath,
		  DWORD    cchBuffer
		  );

LPSTR
 
GetEnvironmentStringsA(
		       void 
		       );

WINBOOL
 
FreeEnvironmentStringsA(
			LPSTR
			);

DWORD
 
FormatMessageA(
	       DWORD dwFlags,
	       LPCVOID lpSource,
	       DWORD dwMessageId,
	       DWORD dwLanguageId,
	       LPSTR lpBuffer,
	       DWORD nSize,
	       __gnuc_va_list  *Arguments
	       );

HANDLE
 
CreateMailslotA(
		LPCSTR lpName,
		DWORD nMaxMessageSize,
		DWORD lReadTimeout,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes
		);

int
 
lstrcmpA(
	 LPCSTR lpString1,
	 LPCSTR lpString2
	 );

int
 
lstrcmpiA(
	  LPCSTR lpString1,
	  LPCSTR lpString2
	  );

LPSTR
 
lstrcpynA(
	  LPSTR lpString1,
	  LPCSTR lpString2,
	  int iMaxLength
	  );

LPSTR
 
lstrcpyA(
	 LPSTR lpString1,
	 LPCSTR lpString2
	 );

LPSTR
 
lstrcatA(
	 LPSTR lpString1,
	 LPCSTR lpString2
	 );

int
 
lstrlenA(
	 LPCSTR lpString
	 );

HANDLE
 
CreateMutexA(
	     LPSECURITY_ATTRIBUTES lpMutexAttributes,
	     WINBOOL bInitialOwner,
	     LPCSTR lpName
	     );

HANDLE
 
OpenMutexA(
	   DWORD dwDesiredAccess,
	   WINBOOL bInheritHandle,
	   LPCSTR lpName
	   );

HANDLE
 
CreateEventA(
	     LPSECURITY_ATTRIBUTES lpEventAttributes,
	     WINBOOL bManualReset,
	     WINBOOL bInitialState,
	     LPCSTR lpName
	     );

HANDLE
 
OpenEventA(
	   DWORD dwDesiredAccess,
	   WINBOOL bInheritHandle,
	   LPCSTR lpName
	   );

HANDLE
 
CreateSemaphoreA(
		 LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
		 LONG lInitialCount,
		 LONG lMaximumCount,
		 LPCSTR lpName
		 );

HANDLE
 
OpenSemaphoreA(
	       DWORD dwDesiredAccess,
	       WINBOOL bInheritHandle,
	       LPCSTR lpName
	       );

HANDLE
 
CreateFileMappingA(
		   HANDLE hFile,
		   LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
		   DWORD flProtect,
		   DWORD dwMaximumSizeHigh,
		   DWORD dwMaximumSizeLow,
		   LPCSTR lpName
		   );

HANDLE
 
OpenFileMappingA(
		 DWORD dwDesiredAccess,
		 WINBOOL bInheritHandle,
		 LPCSTR lpName
		 );

DWORD
 
GetLogicalDriveStringsA(
			DWORD nBufferLength,
			LPSTR lpBuffer
			);

HINSTANCE
 
LoadLibraryA(
	     LPCSTR lpLibFileName
	     );

HINSTANCE
 
LoadLibraryExA(
	       LPCSTR lpLibFileName,
	       HANDLE hFile,
	       DWORD dwFlags
	       );

DWORD
 
GetModuleFileNameA(
		   HINSTANCE hModule,
		   LPSTR lpFilename,
		   DWORD nSize
		   );

HMODULE
 
GetModuleHandleA(
		 LPCSTR lpModuleName
		 );

void 
 
FatalAppExitA(
	      UINT uAction,
	      LPCSTR lpMessageText
	      );

LPSTR
 
GetCommandLineA(
		void 
		);

DWORD
 
GetEnvironmentVariableA(
			LPCSTR lpName,
			LPSTR lpBuffer,
			DWORD nSize
			);

WINBOOL
 
SetEnvironmentVariableA(
			LPCSTR lpName,
			LPCSTR lpValue
			);

DWORD
 
ExpandEnvironmentStringsA(
			  LPCSTR lpSrc,
			  LPSTR lpDst,
			  DWORD nSize
			  );

void 
 
OutputDebugStringA(
		   LPCSTR lpOutputString
		   );

HRSRC
 
FindResourceA(
	      HINSTANCE hModule,
	      LPCSTR lpName,
	      LPCSTR lpType
	      );

HRSRC
 
FindResourceExA(
		HINSTANCE hModule,
		LPCSTR lpType,
		LPCSTR lpName,
		WORD    wLanguage
		);

WINBOOL
 
EnumResourceTypesA(
		   HINSTANCE hModule,
		   ENUMRESTYPEPROC lpEnumFunc,
		   LONG lParam
		   );

WINBOOL
 
EnumResourceNamesA(
		   HINSTANCE hModule,
		   LPCSTR lpType,
		   ENUMRESNAMEPROC lpEnumFunc,
		   LONG lParam
		   );

WINBOOL
 
EnumResourceLanguagesA(
		       HINSTANCE hModule,
		       LPCSTR lpType,
		       LPCSTR lpName,
		       ENUMRESLANGPROC lpEnumFunc,
		       LONG lParam
		       );

HANDLE
 
BeginUpdateResourceA(
		     LPCSTR pFileName,
		     WINBOOL bDeleteExistingResources
		     );

WINBOOL
 
UpdateResourceA(
		HANDLE      hUpdate,
		LPCSTR     lpType,
		LPCSTR     lpName,
		WORD        wLanguage,
		LPVOID      lpData,
		DWORD       cbData
		);

WINBOOL
 
EndUpdateResourceA(
		   HANDLE      hUpdate,
		   WINBOOL        fDiscard
		   );

ATOM
 
GlobalAddAtomA(
	       LPCSTR lpString
	       );

ATOM
 
GlobalFindAtomA(
		LPCSTR lpString
		);

UINT
 
GlobalGetAtomNameA(
		   ATOM nAtom,
		   LPSTR lpBuffer,
		   int nSize
		   );

ATOM
 
AddAtomA(
	 LPCSTR lpString
	 );

ATOM
 
FindAtomA(
	  LPCSTR lpString
	  );

UINT
 
GetAtomNameA(
	     ATOM nAtom,
	     LPSTR lpBuffer,
	     int nSize
	     );

UINT
 
GetProfileIntA(
	       LPCSTR lpAppName,
	       LPCSTR lpKeyName,
	       INT nDefault
	       );

DWORD
 
GetProfileStringA(
		  LPCSTR lpAppName,
		  LPCSTR lpKeyName,
		  LPCSTR lpDefault,
		  LPSTR lpReturnedString,
		  DWORD nSize
		  );

WINBOOL
 
WriteProfileStringA(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    LPCSTR lpString
    );

DWORD
 
GetProfileSectionA(
    LPCSTR lpAppName,
    LPSTR lpReturnedString,
    DWORD nSize
    );

WINBOOL
 
WriteProfileSectionA(
    LPCSTR lpAppName,
    LPCSTR lpString
    );

UINT
 
GetPrivateProfileIntA(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    INT nDefault,
    LPCSTR lpFileName
    );

DWORD
 
GetPrivateProfileStringA(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    LPCSTR lpDefault,
    LPSTR lpReturnedString,
    DWORD nSize,
    LPCSTR lpFileName
    );

WINBOOL
 
WritePrivateProfileStringA(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    LPCSTR lpString,
    LPCSTR lpFileName
    );

DWORD
 
GetPrivateProfileSectionA(
    LPCSTR lpAppName,
    LPSTR lpReturnedString,
    DWORD nSize,
    LPCSTR lpFileName
    );

WINBOOL
 
WritePrivateProfileSectionA(
    LPCSTR lpAppName,
    LPCSTR lpString,
    LPCSTR lpFileName
    );

UINT
 
GetDriveTypeA(
    LPCSTR lpRootPathName
    );

UINT
 
GetSystemDirectoryA(
    LPSTR lpBuffer,
    UINT uSize
    );

DWORD
 
GetTempPathA(
    DWORD nBufferLength,
    LPSTR lpBuffer
    );

UINT
 
GetTempFileNameA(
    LPCSTR lpPathName,
    LPCSTR lpPrefixString,
    UINT uUnique,
    LPSTR lpTempFileName
    );

UINT
 
GetWindowsDirectoryA(
    LPSTR lpBuffer,
    UINT uSize
    );

WINBOOL
 
SetCurrentDirectoryA(
    LPCSTR lpPathName
    );

DWORD
 
GetCurrentDirectoryA(
    DWORD nBufferLength,
    LPSTR lpBuffer
    );

WINBOOL
 
GetDiskFreeSpaceA(
    LPCSTR lpRootPathName,
    LPDWORD lpSectorsPerCluster,
    LPDWORD lpBytesPerSector,
    LPDWORD lpNumberOfFreeClusters,
    LPDWORD lpTotalNumberOfClusters
    );

WINBOOL
 
CreateDirectoryA(
    LPCSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

WINBOOL
 
CreateDirectoryExA(
    LPCSTR lpTemplateDirectory,
    LPCSTR lpNewDirectory,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

WINBOOL
 
RemoveDirectoryA(
    LPCSTR lpPathName
    );

DWORD
 
GetFullPathNameA(
    LPCSTR lpFileName,
    DWORD nBufferLength,
    LPSTR lpBuffer,
    LPSTR *lpFilePart
    );

WINBOOL
 
DefineDosDeviceA(
    DWORD dwFlags,
    LPCSTR lpDeviceName,
    LPCSTR lpTargetPath
    );

DWORD
 
QueryDosDeviceA(
    LPCSTR lpDeviceName,
    LPSTR lpTargetPath,
    DWORD ucchMax
    );

HANDLE
 
CreateFileA(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );

WINBOOL
 
SetFileAttributesA(
    LPCSTR lpFileName,
    DWORD dwFileAttributes
    );

DWORD
 
GetFileAttributesA(
    LPCSTR lpFileName
    );

DWORD
 
GetCompressedFileSizeA(
    LPCSTR lpFileName,
    LPDWORD lpFileSizeHigh
    );

WINBOOL
 
DeleteFileA(
    LPCSTR lpFileName
    );

DWORD
 
SearchPathA(
	    LPCSTR lpPath,
    LPCSTR lpFileName,
    LPCSTR lpExtension,
    DWORD nBufferLength,
    LPSTR lpBuffer,
    LPSTR *lpFilePart
    );

WINBOOL
 
CopyFileA(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName,
    WINBOOL bFailIfExists
    );

WINBOOL
 
MoveFileA(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName
    );

WINBOOL
 
MoveFileExA(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName,
    DWORD dwFlags
    );

HANDLE
 
CreateNamedPipeA(
    LPCSTR lpName,
    DWORD dwOpenMode,
    DWORD dwPipeMode,
    DWORD nMaxInstances,
    DWORD nOutBufferSize,
    DWORD nInBufferSize,
    DWORD nDefaultTimeOut,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

WINBOOL
 
GetNamedPipeHandleStateA(
    HANDLE hNamedPipe,
    LPDWORD lpState,
    LPDWORD lpCurInstances,
    LPDWORD lpMaxCollectionCount,
    LPDWORD lpCollectDataTimeout,
    LPSTR lpUserName,
    DWORD nMaxUserNameSize
    );

WINBOOL
 
CallNamedPipeA(
    LPCSTR lpNamedPipeName,
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesRead,
    DWORD nTimeOut
    );

WINBOOL
 
WaitNamedPipeA(
    LPCSTR lpNamedPipeName,
    DWORD nTimeOut
    );

WINBOOL
 
SetVolumeLabelA(
    LPCSTR lpRootPathName,
    LPCSTR lpVolumeName
    );

WINBOOL
 
GetVolumeInformationA(
    LPCSTR lpRootPathName,
    LPSTR lpVolumeNameBuffer,
    DWORD nVolumeNameSize,
    LPDWORD lpVolumeSerialNumber,
    LPDWORD lpMaximumComponentLength,
    LPDWORD lpFileSystemFlags,
    LPSTR lpFileSystemNameBuffer,
    DWORD nFileSystemNameSize
    );

WINBOOL
 
ClearEventLogA (
    HANDLE hEventLog,
    LPCSTR lpBackupFileName
    );

WINBOOL
 
BackupEventLogA (
    HANDLE hEventLog,
    LPCSTR lpBackupFileName
    );

HANDLE
 
OpenEventLogA (
    LPCSTR lpUNCServerName,
    LPCSTR lpSourceName
    );

HANDLE
 
RegisterEventSourceA (
    LPCSTR lpUNCServerName,
    LPCSTR lpSourceName
    );

HANDLE
 
OpenBackupEventLogA (
    LPCSTR lpUNCServerName,
    LPCSTR lpFileName
    );

WINBOOL
 
ReadEventLogA (
     HANDLE     hEventLog,
     DWORD      dwReadFlags,
     DWORD      dwRecordOffset,
     LPVOID     lpBuffer,
     DWORD      nNumberOfBytesToRead,
     DWORD      *pnBytesRead,
     DWORD      *pnMinNumberOfBytesNeeded
    );

WINBOOL
 
ReportEventA (
     HANDLE     hEventLog,
     WORD       wType,
     WORD       wCategory,
     DWORD      dwEventID,
     PSID       lpUserSid,
     WORD       wNumStrings,
     DWORD      dwDataSize,
     LPCSTR   *lpStrings,
     LPVOID     lpRawData
    );

WINBOOL
 
AccessCheckAndAuditAlarmA (
    LPCSTR SubsystemName,
    LPVOID HandleId,
    LPSTR ObjectTypeName,
    LPSTR ObjectName,
    PSECURITY_DESCRIPTOR SecurityDescriptor,
    DWORD DesiredAccess,
    PGENERIC_MAPPING GenericMapping,
    WINBOOL ObjectCreation,
    LPDWORD GrantedAccess,
    LPBOOL AccessStatus,
    LPBOOL pfGenerateOnClose
    );

WINBOOL
 
ObjectOpenAuditAlarmA (
    LPCSTR SubsystemName,
    LPVOID HandleId,
    LPSTR ObjectTypeName,
    LPSTR ObjectName,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    HANDLE ClientToken,
    DWORD DesiredAccess,
    DWORD GrantedAccess,
    PPRIVILEGE_SET Privileges,
    WINBOOL ObjectCreation,
    WINBOOL AccessGranted,
    LPBOOL GenerateOnClose
    );

WINBOOL
 
ObjectPrivilegeAuditAlarmA (
    LPCSTR SubsystemName,
    LPVOID HandleId,
    HANDLE ClientToken,
    DWORD DesiredAccess,
    PPRIVILEGE_SET Privileges,
    WINBOOL AccessGranted
    );

WINBOOL
 
ObjectCloseAuditAlarmA (
    LPCSTR SubsystemName,
    LPVOID HandleId,
    WINBOOL GenerateOnClose
    );

WINBOOL
 
PrivilegedServiceAuditAlarmA (
    LPCSTR SubsystemName,
    LPCSTR ServiceName,
    HANDLE ClientToken,
    PPRIVILEGE_SET Privileges,
    WINBOOL AccessGranted
    );

WINBOOL
 
SetFileSecurityA (
    LPCSTR lpFileName,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor
    );

WINBOOL
 
GetFileSecurityA (
    LPCSTR lpFileName,
    SECURITY_INFORMATION RequestedInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD nLength,
    LPDWORD lpnLengthNeeded
    );

HANDLE
 
FindFirstChangeNotificationA(
    LPCSTR lpPathName,
    WINBOOL bWatchSubtree,
    DWORD dwNotifyFilter
    );

WINBOOL
 
IsBadStringPtrA(
    LPCSTR lpsz,
    UINT ucchMax
    );

WINBOOL
 
LookupAccountSidA(
    LPCSTR lpSystemName,
    PSID Sid,
    LPSTR Name,
    LPDWORD cbName,
    LPSTR ReferencedDomainName,
    LPDWORD cbReferencedDomainName,
    PSID_NAME_USE peUse
    );

WINBOOL
 
LookupAccountNameA(
    LPCSTR lpSystemName,
    LPCSTR lpAccountName,
    PSID Sid,
    LPDWORD cbSid,
    LPSTR ReferencedDomainName,
    LPDWORD cbReferencedDomainName,
    PSID_NAME_USE peUse
    );

WINBOOL
 
LookupPrivilegeValueA(
    LPCSTR lpSystemName,
    LPCSTR lpName,
    PLUID   lpLuid
    );

WINBOOL
 
LookupPrivilegeNameA(
    LPCSTR lpSystemName,
    PLUID   lpLuid,
    LPSTR lpName,
    LPDWORD cbName
    );

WINBOOL
 
LookupPrivilegeDisplayNameA(
    LPCSTR lpSystemName,
    LPCSTR lpName,
    LPSTR lpDisplayName,
    LPDWORD cbDisplayName,
    LPDWORD lpLanguageId
    );

WINBOOL
 
BuildCommDCBA(
    LPCSTR lpDef,
    LPDCB lpDCB
    );

WINBOOL
 
BuildCommDCBAndTimeoutsA(
    LPCSTR lpDef,
    LPDCB lpDCB,
    LPCOMMTIMEOUTS lpCommTimeouts
    );

WINBOOL
 
CommConfigDialogA(
    LPCSTR lpszName,
    HWND hWnd,
    LPCOMMCONFIG lpCC
    );

WINBOOL
 
GetDefaultCommConfigA(
    LPCSTR lpszName,
    LPCOMMCONFIG lpCC,
    LPDWORD lpdwSize
    );

WINBOOL
 
SetDefaultCommConfigA(
    LPCSTR lpszName,
    LPCOMMCONFIG lpCC,
    DWORD dwSize
    );

WINBOOL
 
GetComputerNameA (
    LPSTR lpBuffer,
    LPDWORD nSize
    );

WINBOOL
 
SetComputerNameA (
    LPCSTR lpComputerName
    );

WINBOOL
 
GetUserNameA (
    LPSTR lpBuffer,
    LPDWORD nSize
    );

int
 
wvsprintfA(
    LPSTR,
    LPCSTR,
    __gnuc_va_list  arglist);
 
int
 
wsprintfA(LPSTR, LPCSTR, ...);

HKL
 
LoadKeyboardLayoutA(
    LPCSTR pwszKLID,
    UINT Flags);
 
WINBOOL
 
GetKeyboardLayoutNameA(
    LPSTR pwszKLID);
 
HDESK
 
CreateDesktopA(
    LPSTR lpszDesktop,
    LPSTR lpszDevice,
    LPDEVMODE pDevmode,
    DWORD dwFlags,
    DWORD dwDesiredAccess,
    LPSECURITY_ATTRIBUTES lpsa);
 
HDESK
 
OpenDesktopA(
    LPSTR lpszDesktop,
    DWORD dwFlags,
    WINBOOL fInherit,
    DWORD dwDesiredAccess);
 
WINBOOL
 
EnumDesktopsA(
    HWINSTA hwinsta,
    DESKTOPENUMPROC lpEnumFunc,
    LPARAM lParam);
 
HWINSTA
 
CreateWindowStationA(
    LPSTR lpwinsta,
    DWORD dwReserved,
    DWORD dwDesiredAccess,
    LPSECURITY_ATTRIBUTES lpsa);
 
HWINSTA
 
OpenWindowStationA(
    LPSTR lpszWinSta,
    WINBOOL fInherit,
    DWORD dwDesiredAccess);
 
WINBOOL
 
EnumWindowStationsA(
    ENUMWINDOWSTATIONPROC lpEnumFunc,
    LPARAM lParam);
 
WINBOOL
 
GetUserObjectInformationA(
    HANDLE hObj,
    int nIndex,
    PVOID pvInfo,
    DWORD nLength,
    LPDWORD lpnLengthNeeded);
 
WINBOOL
 
SetUserObjectInformationA(
    HANDLE hObj,
    int nIndex,
    PVOID pvInfo,
    DWORD nLength);
 
UINT
 
RegisterWindowMessageA(
    LPCSTR lpString);
 
WINBOOL
 
GetMessageA(
    LPMSG lpMsg,
    HWND hWnd ,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax);
 
LONG
 
DispatchMessageA(
    const  MSG *lpMsg);
 
WINBOOL
 
PeekMessageA(
    LPMSG lpMsg,
    HWND hWnd ,
    UINT wMsgFilterMin,
    UINT wMsgFilterMax,
    UINT wRemoveMsg);
 
LRESULT
 
SendMessageA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
LRESULT
 
SendMessageTimeoutA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam,
    UINT fuFlags,
    UINT uTimeout,
    LPDWORD lpdwResult);
 
WINBOOL
 
SendNotifyMessageA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
WINBOOL
 
SendMessageCallbackA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam,
    SENDASYNCPROC lpResultCallBack,
    DWORD dwData);
 
WINBOOL
 
PostMessageA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
WINBOOL
 
PostThreadMessageA(
    DWORD idThread,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
LRESULT
 
DefWindowProcA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
LRESULT
 
CallWindowProcA(
    WNDPROC lpPrevWndFunc,
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
ATOM
 
RegisterClassA(
    const  WNDCLASS *lpWndClass);
 
WINBOOL
 
UnregisterClassA(
    LPCSTR lpClassName,
    HINSTANCE hInstance);
 
WINBOOL
 
GetClassInfoA(
    HINSTANCE hInstance ,
    LPCSTR lpClassName,
    LPWNDCLASS lpWndClass);
 
ATOM
 
RegisterClassExA(const  WNDCLASSEX *);
 
WINBOOL
 
GetClassInfoExA(HINSTANCE, LPCSTR, LPWNDCLASSEX);
 
HWND
 
CreateWindowExA(
    DWORD dwExStyle,
    LPCSTR lpClassName,
    LPCSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent ,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam);
 
HWND
 
CreateDialogParamA(
    HINSTANCE hInstance,
    LPCSTR lpTemplateName,
    HWND hWndParent ,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);
 
HWND
 
CreateDialogIndirectParamA(
    HINSTANCE hInstance,
    LPCDLGTEMPLATE lpTemplate,
    HWND hWndParent,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);
 
int
 
DialogBoxParamA(
    HINSTANCE hInstance,
    LPCSTR lpTemplateName,
    HWND hWndParent ,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);
 
int
 
DialogBoxIndirectParamA(
    HINSTANCE hInstance,
    LPCDLGTEMPLATE hDialogTemplate,
    HWND hWndParent ,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam);
 
WINBOOL
 
SetDlgItemTextA(
    HWND hDlg,
    int nIDDlgItem,
    LPCSTR lpString);
 
UINT
 
GetDlgItemTextA(
    HWND hDlg,
    int nIDDlgItem,
    LPSTR lpString,
    int nMaxCount);
 
LONG
 
SendDlgItemMessageA(
    HWND hDlg,
    int nIDDlgItem,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
LRESULT
 
DefDlgProcA(
    HWND hDlg,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
 
WINBOOL
 
CallMsgFilterA(
    LPMSG lpMsg,
    int nCode);
 
UINT
 
RegisterClipboardFormatA(
    LPCSTR lpszFormat);
 
int
 
GetClipboardFormatNameA(
    UINT format,
    LPSTR lpszFormatName,
    int cchMaxCount);
 
WINBOOL
 
CharToOemA(
    LPCSTR lpszSrc,
    LPSTR lpszDst);
 
WINBOOL
 
OemToCharA(
    LPCSTR lpszSrc,
    LPSTR lpszDst);
 
WINBOOL
 
CharToOemBuffA(
    LPCSTR lpszSrc,
    LPSTR lpszDst,
    DWORD cchDstLength);
 
WINBOOL
 
OemToCharBuffA(
    LPCSTR lpszSrc,
    LPSTR lpszDst,
    DWORD cchDstLength);
 
LPSTR
 
CharUpperA(
    LPSTR lpsz);
 
DWORD
 
CharUpperBuffA(
    LPSTR lpsz,
    DWORD cchLength);
 
LPSTR
 
CharLowerA(
    LPSTR lpsz);
 
DWORD
 
CharLowerBuffA(
    LPSTR lpsz,
    DWORD cchLength);
 
LPSTR
 
CharNextA(
    LPCSTR lpsz);
 
LPSTR
 
CharPrevA(
    LPCSTR lpszStart,
    LPCSTR lpszCurrent);
 
WINBOOL
 
IsCharAlphaA(
    CHAR ch);
 
WINBOOL
 
IsCharAlphaNumericA(
    CHAR ch);
 
WINBOOL
 
IsCharUpperA(
    CHAR ch);
 
WINBOOL
 
IsCharLowerA(
    CHAR ch);
 
int
 
GetKeyNameTextA(
    LONG lParam,
    LPSTR lpString,
    int nSize
    );
 
SHORT
 
VkKeyScanA(
    CHAR ch);
 
SHORT
  VkKeyScanExA(
    CHAR  ch,
    HKL   dwhkl);
 
UINT
 
MapVirtualKeyA(
    UINT uCode,
    UINT uMapType);
 
UINT
 
MapVirtualKeyExA(
    UINT uCode,
    UINT uMapType,
    HKL dwhkl);
 
HACCEL
 
LoadAcceleratorsA(
    HINSTANCE hInstance,
    LPCSTR lpTableName);
 
HACCEL
 
CreateAcceleratorTableA(
    LPACCEL, int);
 
int
 
CopyAcceleratorTableA(
    HACCEL hAccelSrc,
    LPACCEL lpAccelDst,
    int cAccelEntries);
 
int
 
TranslateAcceleratorA(
    HWND hWnd,
    HACCEL hAccTable,
    LPMSG lpMsg);
 
HMENU
 
LoadMenuA(
    HINSTANCE hInstance,
    LPCSTR lpMenuName);
 
HMENU
 
LoadMenuIndirectA(
    const  MENUTEMPLATE *lpMenuTemplate);
 
WINBOOL
 
ChangeMenuA(
    HMENU hMenu,
    UINT cmd,
    LPCSTR lpszNewItem,
    UINT cmdInsert,
    UINT flags);
 
int
 
GetMenuStringA(
    HMENU hMenu,
    UINT uIDItem,
    LPSTR lpString,
    int nMaxCount,
    UINT uFlag);
 
WINBOOL
 
InsertMenuA(
    HMENU hMenu,
    UINT uPosition,
    UINT uFlags,
    UINT uIDNewItem,
    LPCSTR lpNewItem
    );
 
WINBOOL
 
AppendMenuA(
    HMENU hMenu,
    UINT uFlags,
    UINT uIDNewItem,
    LPCSTR lpNewItem
    );
 
WINBOOL
 
ModifyMenuA(
    HMENU hMnu,
    UINT uPosition,
    UINT uFlags,
    UINT uIDNewItem,
    LPCSTR lpNewItem
    );
 
WINBOOL
 
InsertMenuItemA(
    HMENU,
    UINT,
    WINBOOL,
    LPCMENUITEMINFO
    );
 
WINBOOL
 
GetMenuItemInfoA(
    HMENU,
    UINT,
    WINBOOL,
    LPMENUITEMINFO
    );
 
WINBOOL
 
SetMenuItemInfoA(
    HMENU,
    UINT,
    WINBOOL,
    LPCMENUITEMINFO
    );
 
int
 
DrawTextA(
    HDC hDC,
    LPCSTR lpString,
    int nCount,
    LPRECT lpRect,
    UINT uFormat);
 
int
 
DrawTextExA(HDC, LPSTR, int, LPRECT, UINT, LPDRAWTEXTPARAMS);
 
WINBOOL
 
GrayStringA(
    HDC hDC,
    HBRUSH hBrush,
    GRAYSTRINGPROC lpOutputFunc,
    LPARAM lpData,
    int nCount,
    int X,
    int Y,
    int nWidth,
    int nHeight);
 
WINBOOL
 
DrawStateA(HDC, HBRUSH, DRAWSTATEPROC, LPARAM, WPARAM, int, int, int, int, UINT);

LONG
 
TabbedTextOutA(
    HDC hDC,
    int X,
    int Y,
    LPCSTR lpString,
    int nCount,
    int nTabPositions,
    LPINT lpnTabStopPositions,
    int nTabOrigin);
 
DWORD
 
GetTabbedTextExtentA(
    HDC hDC,
    LPCSTR lpString,
    int nCount,
    int nTabPositions,
    LPINT lpnTabStopPositions);
 
WINBOOL
 
SetPropA(
    HWND hWnd,
    LPCSTR lpString,
    HANDLE hData);
 
HANDLE
 
GetPropA(
    HWND hWnd,
    LPCSTR lpString);
 
HANDLE
 
RemovePropA(
    HWND hWnd,
    LPCSTR lpString);
 
int
 
EnumPropsExA(
    HWND hWnd,
    PROPENUMPROCEX lpEnumFunc,
    LPARAM lParam);
 
int
 
EnumPropsA(
    HWND hWnd,
    PROPENUMPROC lpEnumFunc);
 
WINBOOL
 
SetWindowTextA(
    HWND hWnd,
    LPCSTR lpString);
 
int
 
GetWindowTextA(
    HWND hWnd,
    LPSTR lpString,
    int nMaxCount);
 
int
 
GetWindowTextLengthA(
    HWND hWnd);
 
int
 
MessageBoxA(
    HWND hWnd ,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType);
 
int
 
MessageBoxExA(
    HWND hWnd ,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType,
    WORD wLanguageId);
 
int
 
MessageBoxIndirectA(LPMSGBOXPARAMS);

LONG
 
GetWindowLongA(
    HWND hWnd,
    int nIndex);
 
LONG
 
SetWindowLongA(
    HWND hWnd,
    int nIndex,
    LONG dwNewLong);
 
DWORD
 
GetClassLongA(
    HWND hWnd,
    int nIndex);
 
DWORD
 
SetClassLongA(
    HWND hWnd,
    int nIndex,
    LONG dwNewLong);
 
HWND
 
FindWindowA(
    LPCSTR lpClassName ,
    LPCSTR lpWindowName);
 
HWND
 
FindWindowExA(HWND, HWND, LPCSTR, LPCSTR);

int
 
GetClassNameA(
    HWND hWnd,
    LPSTR lpClassName,
    int nMaxCount);
 
HHOOK
 
SetWindowsHookExA(
    int idHook,
    HOOKPROC lpfn,
    HINSTANCE hmod,
    DWORD dwThreadId);
 
HBITMAP
 
LoadBitmapA(
    HINSTANCE hInstance,
    LPCSTR lpBitmapName);
 
HCURSOR
 
LoadCursorA(
    HINSTANCE hInstance,
    LPCSTR lpCursorName);
 
HCURSOR
 
LoadCursorFromFileA(
    LPCSTR    lpFileName);
 
HICON
 
LoadIconA(
    HINSTANCE hInstance,
    LPCSTR lpIconName);
 
HANDLE
 
LoadImageA(
    HINSTANCE,
    LPCSTR,
    UINT,
    int,
    int,
    UINT);
 
int
 
LoadStringA(
    HINSTANCE hInstance,
    UINT uID,
    LPSTR lpBuffer,
    int nBufferMax);
 
WINBOOL
 
IsDialogMessageA(
    HWND hDlg,
    LPMSG lpMsg);
 
int
 
DlgDirListA(
    HWND hDlg,
    LPSTR lpPathSpec,
    int nIDListBox,
    int nIDStaticPath,
    UINT uFileType);
 
WINBOOL
 
DlgDirSelectExA(
    HWND hDlg,
    LPSTR lpString,
    int nCount,
    int nIDListBox);
 
int
 
DlgDirListComboBoxA(
    HWND hDlg,
    LPSTR lpPathSpec,
    int nIDComboBox,
    int nIDStaticPath,
    UINT uFiletype);
 
WINBOOL
 
DlgDirSelectComboBoxExA(
    HWND hDlg,
    LPSTR lpString,
    int nCount,
    int nIDComboBox);
 
LRESULT
 
DefFrameProcA(
    HWND hWnd,
    HWND hWndMDIClient ,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam);
 
LRESULT
 
DefMDIChildProcA(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam);
 
HWND
 
CreateMDIWindowA(
    LPSTR lpClassName,
    LPSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HINSTANCE hInstance,
    LPARAM lParam
    );
 
WINBOOL
 
WinHelpA(
    HWND hWndMain,
    LPCSTR lpszHelp,
    UINT uCommand,
    DWORD dwData
    );
 
LONG
 
ChangeDisplaySettingsA(
    LPDEVMODE lpDevMode,
    DWORD dwFlags);
 
WINBOOL
 
EnumDisplaySettingsA(
    LPCSTR lpszDeviceName,
    DWORD iModeNum,
    LPDEVMODE lpDevMode);
 
WINBOOL
 
SystemParametersInfoA(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni);
 
int
 
AddFontResourceA(LPCSTR);

HMETAFILE
 
CopyMetaFileA(HMETAFILE, LPCSTR);

HFONT
 
CreateFontIndirectA(const  LOGFONT *);

HDC
 
CreateICA(LPCSTR, LPCSTR , LPCSTR , const  DEVMODE *);

HDC
 
CreateMetaFileA(LPCSTR);

WINBOOL
 
CreateScalableFontResourceA(DWORD, LPCSTR, LPCSTR, LPCSTR);

int
 
DeviceCapabilitiesA(LPCSTR, LPCSTR, WORD,
                                LPSTR, const  DEVMODE *);

int
 
EnumFontFamiliesExA(HDC, LPLOGFONT, FONTENUMEXPROC, LPARAM,DWORD);

int
 
EnumFontFamiliesA(HDC, LPCSTR, FONTENUMPROC, LPARAM);

int
 
EnumFontsA(HDC, LPCSTR,  ENUMFONTSPROC, LPARAM);

WINBOOL
 
GetCharWidthA(HDC, UINT, UINT, LPINT);

WINBOOL
 
GetCharWidth32A(HDC, UINT, UINT, LPINT);

WINBOOL
 
GetCharWidthFloatA(HDC, UINT, UINT, PFLOAT);

WINBOOL
 
GetCharABCWidthsA(HDC, UINT, UINT, LPABC);

WINBOOL
 
GetCharABCWidthsFloatA(HDC, UINT, UINT, LPABCFLOAT);
DWORD
 
GetGlyphOutlineA(HDC, UINT, UINT, LPGLYPHMETRICS, DWORD, LPVOID, const  MAT2 *);

HMETAFILE
 
GetMetaFileA(LPCSTR);

UINT
 
GetOutlineTextMetricsA(HDC, UINT, LPOUTLINETEXTMETRIC);

WINBOOL
 
GetTextExtentPointA(
                    HDC,
                    LPCSTR,
                    int,
                    LPSIZE
                    );

WINBOOL
 
GetTextExtentPoint32A(
                    HDC,
                    LPCSTR,
                    int,
                    LPSIZE
                    );

WINBOOL
 
GetTextExtentExPointA(
                    HDC,
                    LPCSTR,
                    int,
                    int,
                    LPINT,
                    LPINT,
                    LPSIZE
                    );

DWORD
 
GetCharacterPlacementA(HDC, LPCSTR, int, int, LPGCP_RESULTS, DWORD);

HDC
 
ResetDCA(HDC, const  DEVMODE *);

WINBOOL
 
RemoveFontResourceA(LPCSTR);

HENHMETAFILE
 
CopyEnhMetaFileA(HENHMETAFILE, LPCSTR);

HDC
 
CreateEnhMetaFileA(HDC, LPCSTR, const  RECT *, LPCSTR);

HENHMETAFILE
 
GetEnhMetaFileA(LPCSTR);

UINT
 
GetEnhMetaFileDescriptionA(HENHMETAFILE, UINT, LPSTR );

WINBOOL
 
GetTextMetricsA(HDC, LPTEXTMETRIC);

int
 
StartDocA(HDC, const  DOCINFO *);

int
 
GetObjectA(HGDIOBJ, int, LPVOID);

WINBOOL
 
TextOutA(HDC, int, int, LPCSTR, int);

WINBOOL
 
ExtTextOutA(HDC, int, int, UINT, const  RECT *,LPCSTR, UINT, const  INT *);

WINBOOL
 
PolyTextOutA(HDC, const  POLYTEXT *, int); 

int
 
GetTextFaceA(HDC, int, LPSTR);

DWORD
 
GetKerningPairsA(HDC, DWORD, LPKERNINGPAIR);

HCOLORSPACE
 
CreateColorSpaceA(LPLOGCOLORSPACE);

WINBOOL
 
GetLogColorSpaceA(HCOLORSPACE,LPLOGCOLORSPACE,DWORD);

WINBOOL
 
GetICMProfileA(HDC,DWORD,LPSTR);

WINBOOL
 
SetICMProfileA(HDC,LPSTR);

WINBOOL
 
UpdateICMRegKeyA(DWORD, DWORD, LPSTR, UINT);

int
 
EnumICMProfilesA(HDC,ICMENUMPROC,LPARAM);

int
 
PropertySheetA(LPCPROPSHEETHEADER lppsph);

HIMAGELIST
 
ImageList_LoadImageA(HINSTANCE hi, LPCSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);

HWND
 
CreateStatusWindowA(LONG style, LPCSTR lpszText, HWND hwndParent, UINT wID);

void
 
DrawStatusTextA(HDC hDC, LPRECT lprc, LPCSTR pszText, UINT uFlags);

WINBOOL
 
GetOpenFileNameA(LPOPENFILENAME);

WINBOOL
 
GetSaveFileNameA(LPOPENFILENAME);

short
 
GetFileTitleA(LPCSTR, LPSTR, WORD);

WINBOOL
 
ChooseColorA(LPCHOOSECOLOR);

HWND
 
FindTextA(LPFINDREPLACE);

HWND
 
ReplaceTextA(LPFINDREPLACE);

WINBOOL
 
ChooseFontA(LPCHOOSEFONT);

WINBOOL
 
PrintDlgA(LPPRINTDLG);

WINBOOL
 
PageSetupDlgA( LPPAGESETUPDLG );

WINBOOL
 
CreateProcessA(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    WINBOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );

void 
 
GetStartupInfoA(
    LPSTARTUPINFO lpStartupInfo
    );

HANDLE
 
FindFirstFileA(
    LPCSTR lpFileName,
    LPWIN32_FIND_DATA lpFindFileData
    );

WINBOOL
 
FindNextFileA(
    HANDLE hFindFile,
    LPWIN32_FIND_DATA lpFindFileData
    );

WINBOOL
 
GetVersionExA(
    LPOSVERSIONINFO lpVersionInformation
    );


















HDC
 
CreateDCA(LPCSTR, LPCSTR , LPCSTR , const  DEVMODE *);

DWORD
 
VerInstallFileA(
        DWORD uFlags,
        LPSTR szSrcFileName,
        LPSTR szDestFileName,
        LPSTR szSrcDir,
        LPSTR szDestDir,
        LPSTR szCurDir,
        LPSTR szTmpFile,
        PUINT lpuTmpFileLen
        );

DWORD
 
GetFileVersionInfoSizeA(
        LPSTR lptstrFilename,
        LPDWORD lpdwHandle
        );

WINBOOL
 
GetFileVersionInfoA(
        LPSTR lptstrFilename,
        DWORD dwHandle,
        DWORD dwLen,
        LPVOID lpData
        );

DWORD
 
VerLanguageNameA(
        DWORD wLang,
        LPSTR szLang,
        DWORD nSize
        );

WINBOOL
 
VerQueryValueA(
        const LPVOID pBlock,
        LPSTR lpSubBlock,
        LPVOID * lplpBuffer,
        PUINT puLen
        );

DWORD
 
VerFindFileA(
        DWORD uFlags,
        LPSTR szFileName,
        LPSTR szWinDir,
        LPSTR szAppDir,
        LPSTR szCurDir,
        PUINT lpuCurDirLen,
        LPSTR szDestDir,
        PUINT lpuDestDirLen
        );

LONG
 
RegConnectRegistryA (
    LPSTR lpMachineName,
    HKEY hKey,
    PHKEY phkResult
    );

LONG
 
RegCreateKeyA (
    HKEY hKey,
    LPCSTR lpSubKey,
    PHKEY phkResult
    );

LONG
 
RegCreateKeyExA (
    HKEY hKey,
    LPCSTR lpSubKey,
    DWORD Reserved,
    LPSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
    );

LONG
 
RegDeleteKeyA (
    HKEY hKey,
    LPCSTR lpSubKey
    );

LONG
 
RegDeleteValueA (
    HKEY hKey,
    LPCSTR lpValueName
    );

LONG
 
RegEnumKeyA (
    HKEY hKey,
    DWORD dwIndex,
    LPSTR lpName,
    DWORD cbName
    );

LONG
 
RegEnumKeyExA (
    HKEY hKey,
    DWORD dwIndex,
    LPSTR lpName,
    LPDWORD lpcbName,
    LPDWORD lpReserved,
    LPSTR lpClass,
    LPDWORD lpcbClass,
    PFILETIME lpftLastWriteTime
    );

LONG
 
RegEnumValueA (
    HKEY hKey,
    DWORD dwIndex,
    LPSTR lpValueName,
    LPDWORD lpcbValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    );

LONG
 
RegLoadKeyA (
    HKEY    hKey,
    LPCSTR  lpSubKey,
    LPCSTR  lpFile
    );

LONG
 
RegOpenKeyA (
    HKEY hKey,
    LPCSTR lpSubKey,
    PHKEY phkResult
    );

LONG
 
RegOpenKeyExA (
    HKEY hKey,
    LPCSTR lpSubKey,
    DWORD ulOptions,
    REGSAM samDesired,
    PHKEY phkResult
    );

LONG
 
RegQueryInfoKeyA (
    HKEY hKey,
    LPSTR lpClass,
    LPDWORD lpcbClass,
    LPDWORD lpReserved,
    LPDWORD lpcSubKeys,
    LPDWORD lpcbMaxSubKeyLen,
    LPDWORD lpcbMaxClassLen,
    LPDWORD lpcValues,
    LPDWORD lpcbMaxValueNameLen,
    LPDWORD lpcbMaxValueLen,
    LPDWORD lpcbSecurityDescriptor,
    PFILETIME lpftLastWriteTime
    );

LONG
 
RegQueryValueA (
    HKEY hKey,
    LPCSTR lpSubKey,
    LPSTR lpValue,
    PLONG   lpcbValue
    );

LONG
 
RegQueryMultipleValuesA (
    HKEY hKey,
    PVALENT val_list,
    DWORD num_vals,
    LPSTR lpValueBuf,
    LPDWORD ldwTotsize
    );

LONG
 
RegQueryValueExA (
    HKEY hKey,
    LPCSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    );

LONG
 
RegReplaceKeyA (
    HKEY     hKey,
    LPCSTR  lpSubKey,
    LPCSTR  lpNewFile,
    LPCSTR  lpOldFile
    );

LONG
 
RegRestoreKeyA (
    HKEY hKey,
    LPCSTR lpFile,
    DWORD   dwFlags
    );

LONG
 
RegSaveKeyA (
    HKEY hKey,
    LPCSTR lpFile,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

LONG
 
RegSetValueA (
    HKEY hKey,
    LPCSTR lpSubKey,
    DWORD dwType,
    LPCSTR lpData,
    DWORD cbData
    );

LONG
 
RegSetValueExA (
    HKEY hKey,
    LPCSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    const  BYTE* lpData,
    DWORD cbData
    );

LONG
 
RegUnLoadKeyA (
    HKEY    hKey,
    LPCSTR lpSubKey
    );

WINBOOL
 
InitiateSystemShutdownA(
    LPSTR lpMachineName,
    LPSTR lpMessage,
    DWORD dwTimeout,
    WINBOOL bForceAppsClosed,
    WINBOOL bRebootAfterShutdown
    );

WINBOOL
 
AbortSystemShutdownA(
    LPSTR lpMachineName
    );

int
 
CompareStringA(
    LCID     Locale,
    DWORD    dwCmpFlags,
    LPCSTR lpString1,
    int      cchCount1,
    LPCSTR lpString2,
    int      cchCount2);

int
 
LCMapStringA(
    LCID     Locale,
    DWORD    dwMapFlags,
    LPCSTR lpSrcStr,
    int      cchSrc,
    LPSTR  lpDestStr,
    int      cchDest);

int
 
GetLocaleInfoA(
    LCID     Locale,
    LCTYPE   LCType,
    LPSTR  lpLCData,
    int      cchData);

WINBOOL
 
SetLocaleInfoA(
    LCID     Locale,
    LCTYPE   LCType,
    LPCSTR lpLCData);

int
 
GetTimeFormatA(
    LCID     Locale,
    DWORD    dwFlags,
    const  SYSTEMTIME *lpTime,
    LPCSTR lpFormat,
    LPSTR  lpTimeStr,
    int      cchTime);

int
 
GetDateFormatA(
    LCID     Locale,
    DWORD    dwFlags,
    const  SYSTEMTIME *lpDate,
    LPCSTR lpFormat,
    LPSTR  lpDateStr,
    int      cchDate);

int
 
GetNumberFormatA(
    LCID     Locale,
    DWORD    dwFlags,
    LPCSTR lpValue,
    const  NUMBERFMT *lpFormat,
    LPSTR  lpNumberStr,
    int      cchNumber);

int
 
GetCurrencyFormatA(
    LCID     Locale,
    DWORD    dwFlags,
    LPCSTR lpValue,
    const  CURRENCYFMT *lpFormat,
    LPSTR  lpCurrencyStr,
    int      cchCurrency);

WINBOOL
 
EnumCalendarInfoA(
    CALINFO_ENUMPROC lpCalInfoEnumProc,
    LCID              Locale,
    CALID             Calendar,
    CALTYPE           CalType);

WINBOOL
 
EnumTimeFormatsA(
    TIMEFMT_ENUMPROC lpTimeFmtEnumProc,
    LCID              Locale,
    DWORD             dwFlags);

WINBOOL
 
EnumDateFormatsA(
    DATEFMT_ENUMPROC lpDateFmtEnumProc,
    LCID              Locale,
    DWORD             dwFlags);

WINBOOL
 
GetStringTypeExA(
    LCID     Locale,
    DWORD    dwInfoType,
    LPCSTR lpSrcStr,
    int      cchSrc,
    LPWORD   lpCharType);

WINBOOL
 
GetStringTypeA(
    LCID     Locale,
    DWORD    dwInfoType,
    LPCSTR   lpSrcStr,
    int      cchSrc,
    LPWORD   lpCharType);


int
 
FoldStringA(
    DWORD    dwMapFlags,
    LPCSTR lpSrcStr,
    int      cchSrc,
    LPSTR  lpDestStr,
    int      cchDest);

WINBOOL
 
EnumSystemLocalesA(
    LOCALE_ENUMPROC lpLocaleEnumProc,
    DWORD            dwFlags);

WINBOOL
 
EnumSystemCodePagesA(
    CODEPAGE_ENUMPROC lpCodePageEnumProc,
    DWORD              dwFlags);

WINBOOL
 
PeekConsoleInputA(
    HANDLE hConsoleInput,
    PINPUT_RECORD lpBuffer,
    DWORD nLength,
    LPDWORD lpNumberOfEventsRead
    );

WINBOOL
 
ReadConsoleInputA(
    HANDLE hConsoleInput,
    PINPUT_RECORD lpBuffer,
    DWORD nLength,
    LPDWORD lpNumberOfEventsRead
    );

WINBOOL
 
WriteConsoleInputA(
    HANDLE hConsoleInput,
    const  INPUT_RECORD *lpBuffer,
    DWORD nLength,
    LPDWORD lpNumberOfEventsWritten
    );

WINBOOL
 
ReadConsoleOutputA(
    HANDLE hConsoleOutput,
    PCHAR_INFO lpBuffer,
    COORD dwBufferSize,
    COORD dwBufferCoord,
    PSMALL_RECT lpReadRegion
    );

WINBOOL
 
WriteConsoleOutputA(
    HANDLE hConsoleOutput,
    const  CHAR_INFO *lpBuffer,
    COORD dwBufferSize,
    COORD dwBufferCoord,
    PSMALL_RECT lpWriteRegion
    );

WINBOOL
 
ReadConsoleOutputCharacterA(
    HANDLE hConsoleOutput,
    LPSTR lpCharacter,
    DWORD nLength,
    COORD dwReadCoord,
    LPDWORD lpNumberOfCharsRead
    );

WINBOOL
 
WriteConsoleOutputCharacterA(
    HANDLE hConsoleOutput,
    LPCSTR lpCharacter,
    DWORD nLength,
    COORD dwWriteCoord,
    LPDWORD lpNumberOfCharsWritten
    );

WINBOOL
 
FillConsoleOutputCharacterA(
    HANDLE hConsoleOutput,
    CHAR  cCharacter,
    DWORD  nLength,
    COORD  dwWriteCoord,
    LPDWORD lpNumberOfCharsWritten
    );

WINBOOL
 
ScrollConsoleScreenBufferA(
    HANDLE hConsoleOutput,
    const  SMALL_RECT *lpScrollRectangle,
    const  SMALL_RECT *lpClipRectangle,
    COORD dwDestinationOrigin,
    const  CHAR_INFO *lpFill
    );

DWORD
 
GetConsoleTitleA(
    LPSTR lpConsoleTitle,
    DWORD nSize
    );

WINBOOL
 
SetConsoleTitleA(
    LPCSTR lpConsoleTitle
    );

WINBOOL
 
ReadConsoleA(
    HANDLE hConsoleInput,
    LPVOID lpBuffer,
    DWORD nNumberOfCharsToRead,
    LPDWORD lpNumberOfCharsRead,
    LPVOID lpReserved
    );

WINBOOL
 
WriteConsoleA(
    HANDLE hConsoleOutput,
    const  void  *lpBuffer,
    DWORD nNumberOfCharsToWrite,
    LPDWORD lpNumberOfCharsWritten,
    LPVOID lpReserved
    );

DWORD  
WNetAddConnectionA(
     LPCSTR   lpRemoteName,
     LPCSTR   lpPassword,
     LPCSTR   lpLocalName
    );

DWORD  
WNetAddConnection2A(
     LPNETRESOURCE lpNetResource,
     LPCSTR       lpPassword,
     LPCSTR       lpUserName,
     DWORD          dwFlags
    );

DWORD  
WNetAddConnection3A(
     HWND           hwndOwner,
     LPNETRESOURCE lpNetResource,
     LPCSTR       lpPassword,
     LPCSTR       lpUserName,
     DWORD          dwFlags
    );

DWORD  
WNetCancelConnectionA(
     LPCSTR lpName,
     WINBOOL     fForce
    );

DWORD  
WNetCancelConnection2A(
     LPCSTR lpName,
     DWORD    dwFlags,
     WINBOOL     fForce
    );

DWORD  
WNetGetConnectionA(
     LPCSTR lpLocalName,
     LPSTR  lpRemoteName,
     LPDWORD  lpnLength
    );

DWORD  
WNetUseConnectionA(
    HWND            hwndOwner,
    LPNETRESOURCE  lpNetResource,
    LPCSTR        lpUserID,
    LPCSTR        lpPassword,
    DWORD           dwFlags,
    LPSTR         lpAccessName,
    LPDWORD         lpBufferSize,
    LPDWORD         lpResult
    );

DWORD  
WNetSetConnectionA(
    LPCSTR    lpName,
    DWORD       dwProperties,
    LPVOID      pvValues
    );

DWORD  
WNetConnectionDialog1A(
    LPCONNECTDLGSTRUCT lpConnDlgStruct
    );

DWORD  
WNetDisconnectDialog1A(
    LPDISCDLGSTRUCT lpConnDlgStruct
    );

DWORD  
WNetOpenEnumA(
     DWORD          dwScope,
     DWORD          dwType,
     DWORD          dwUsage,
     LPNETRESOURCE lpNetResource,
     LPHANDLE       lphEnum
    );

DWORD  
WNetEnumResourceA(
     HANDLE  hEnum,
     LPDWORD lpcCount,
     LPVOID  lpBuffer,
     LPDWORD lpBufferSize
    );

DWORD  
WNetGetUniversalNameA(
     LPCSTR lpLocalPath,
     DWORD    dwInfoLevel,
     LPVOID   lpBuffer,
     LPDWORD  lpBufferSize
     );

DWORD  
WNetGetUserA(
     LPCSTR  lpName,
     LPSTR   lpUserName,
     LPDWORD   lpnLength
    );

DWORD  
WNetGetProviderNameA(
    DWORD   dwNetType,
    LPSTR lpProviderName,
    LPDWORD lpBufferSize
    );

DWORD  
WNetGetNetworkInformationA(
    LPCSTR          lpProvider,
    LPNETINFOSTRUCT   lpNetInfoStruct
    );

DWORD  
WNetGetLastErrorA(
     LPDWORD    lpError,
     LPSTR    lpErrorBuf,
     DWORD      nErrorBufSize,
     LPSTR    lpNameBuf,
     DWORD      nNameBufSize
    );

DWORD  
MultinetGetConnectionPerformanceA(
        LPNETRESOURCE lpNetResource,
        LPNETCONNECTINFOSTRUCT lpNetConnectInfoStruct
        );

WINBOOL
 
ChangeServiceConfigA(
    SC_HANDLE    hService,
    DWORD        dwServiceType,
    DWORD        dwStartType,
    DWORD        dwErrorControl,
    LPCSTR     lpBinaryPathName,
    LPCSTR     lpLoadOrderGroup,
    LPDWORD      lpdwTagId,
    LPCSTR     lpDependencies,
    LPCSTR     lpServiceStartName,
    LPCSTR     lpPassword,
    LPCSTR     lpDisplayName
    );

SC_HANDLE
 
CreateServiceA(
    SC_HANDLE    hSCManager,
    LPCSTR     lpServiceName,
    LPCSTR     lpDisplayName,
    DWORD        dwDesiredAccess,
    DWORD        dwServiceType,
    DWORD        dwStartType,
    DWORD        dwErrorControl,
    LPCSTR     lpBinaryPathName,
    LPCSTR     lpLoadOrderGroup,
    LPDWORD      lpdwTagId,
    LPCSTR     lpDependencies,
    LPCSTR     lpServiceStartName,
    LPCSTR     lpPassword
    );

WINBOOL
 
EnumDependentServicesA(
    SC_HANDLE               hService,
    DWORD                   dwServiceState,
    LPENUM_SERVICE_STATUS  lpServices,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded,
    LPDWORD                 lpServicesReturned
    );

WINBOOL
 
EnumServicesStatusA(
    SC_HANDLE               hSCManager,
    DWORD                   dwServiceType,
    DWORD                   dwServiceState,
    LPENUM_SERVICE_STATUS  lpServices,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded,
    LPDWORD                 lpServicesReturned,
    LPDWORD                 lpResumeHandle
    );

WINBOOL
 
GetServiceKeyNameA(
    SC_HANDLE               hSCManager,
    LPCSTR                lpDisplayName,
    LPSTR                 lpServiceName,
    LPDWORD                 lpcchBuffer
    );

WINBOOL
 
GetServiceDisplayNameA(
    SC_HANDLE               hSCManager,
    LPCSTR                lpServiceName,
    LPSTR                 lpDisplayName,
    LPDWORD                 lpcchBuffer
    );

SC_HANDLE
 
OpenSCManagerA(
    LPCSTR lpMachineName,
    LPCSTR lpDatabaseName,
    DWORD   dwDesiredAccess
    );

SC_HANDLE
 
OpenServiceA(
    SC_HANDLE   hSCManager,
    LPCSTR    lpServiceName,
    DWORD       dwDesiredAccess
    );

WINBOOL
 
QueryServiceConfigA(
    SC_HANDLE               hService,
    LPQUERY_SERVICE_CONFIG lpServiceConfig,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded
    );

WINBOOL
 
QueryServiceLockStatusA(
    SC_HANDLE                       hSCManager,
    LPQUERY_SERVICE_LOCK_STATUS    lpLockStatus,
    DWORD                           cbBufSize,
    LPDWORD                         pcbBytesNeeded
    );

SERVICE_STATUS_HANDLE
 
RegisterServiceCtrlHandlerA(
    LPCSTR             lpServiceName,
    LPHANDLER_FUNCTION   lpHandlerProc
    );

WINBOOL
 
StartServiceCtrlDispatcherA(
			    LPSERVICE_TABLE_ENTRY    lpServiceStartTable
			    );

WINBOOL
 
StartServiceA(
	      SC_HANDLE            hService,
	      DWORD                dwNumServiceArgs,
	      LPCSTR             *lpServiceArgVectors
	      );

 

WINBOOL  
wglUseFontBitmapsA(HDC, DWORD, DWORD, DWORD);

WINBOOL  
wglUseFontOutlinesA(HDC, DWORD, DWORD, DWORD, FLOAT,
		    FLOAT, int, LPGLYPHMETRICSFLOAT);

 
 

unsigned int   
DragQueryFileA(HDROP, unsigned int, char *, unsigned int);

HICON   
ExtractAssociatedIconA (HINSTANCE, char *, WORD *);

HICON   
ExtractIconA (HINSTANCE, const char *, unsigned int);

HINSTANCE   
FindExecutableA (const char *, const char *, char *);

int   
ShellAboutA (HWND, const char *, const char *, HICON);

HINSTANCE   
ShellExecuteA (HWND, const char *, const char *, char *, const char *, int);

 
 
 

HSZ   
DdeCreateStringHandleA (DWORD, char *, int);

UINT   
DdeInitializeA (DWORD *, CALLB, DWORD, DWORD);

DWORD   
DdeQueryStringA (DWORD, HSZ, char *, DWORD, int);

 
 

WINBOOL   LogonUserA (LPSTR, LPSTR, LPSTR, DWORD, DWORD, HANDLE *);
WINBOOL   CreateProcessAsUserA (HANDLE, LPCTSTR, LPTSTR,
	SECURITY_ATTRIBUTES*, SECURITY_ATTRIBUTES*, WINBOOL, DWORD, LPVOID,
	LPCTSTR, STARTUPINFO*, PROCESS_INFORMATION*);


}



# 46 "include/Windows32/Functions.h" 2



 

 
# 453 "include/Windows32/Functions.h"


















































































































































































































































































































































































































WINBOOL   AbnormalTermination(void );
int   AbortDoc(HDC);
WINBOOL   AbortPath(HDC);
WINBOOL   AbortPrinter(HANDLE);
WINBOOL   AbortProc(HDC, int);
WINBOOL   AbortSystemShutdownA (LPTSTR);
WINBOOL   AccessCheck(
		    PSECURITY_DESCRIPTOR  pSecurityDescriptor,
		    HANDLE  ClientToken,
		    DWORD  DesiredAccess,
		    PGENERIC_MAPPING  GenericMapping,
		    PPRIVILEGE_SET  PrivilegeSet,
		    LPDWORD  PrivilegeSetLength,
		    LPDWORD  GrantedAccess,
		    LPBOOL  AccessStatus
		    );

WINBOOL   AccessCheckAndAuditAlarmA (
				 LPCTSTR  SubsystemName,
				 LPVOID  HandleId,
				 LPTSTR  ObjectTypeName,
				 LPTSTR  ObjectName,
				 PSECURITY_DESCRIPTOR  SecurityDescriptor,
				 DWORD  DesiredAccess,
				 PGENERIC_MAPPING  GenericMapping,
				 WINBOOL  ObjectCreation,
				 LPDWORD  GrantedAccess,
				 LPBOOL  AccessStatus,
				 LPBOOL  pfGenerateOnClose
				 );

LONG
 
InterlockedIncrement(
		     LPLONG lpAddend
		     );

LONG
 
InterlockedDecrement(
		     LPLONG lpAddend
		     );

LONG
 
InterlockedExchange(
		    LPLONG Target,
		    LONG Value
		    );

WINBOOL
 
FreeResource(
	     HGLOBAL hResData
	     );

LPVOID
 
LockResource(
	     HGLOBAL hResData
	     );

int
 
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
	);

WINBOOL
 
FreeLibrary(
	    HINSTANCE hLibModule
	    );


void 
 
FreeLibraryAndExitThread(
			 HMODULE hLibModule,
			 DWORD dwExitCode
			 );

WINBOOL
 
DisableThreadLibraryCalls(
			  HMODULE hLibModule
			  );

FARPROC
 
GetProcAddress(
	       HINSTANCE hModule,
	       LPCSTR lpProcName
	       );

DWORD
 
GetVersion( void  );

HGLOBAL
 
GlobalAlloc(
	    UINT uFlags,
	    DWORD dwBytes
	    );

HGLOBAL
GlobalDiscard(
	      HGLOBAL hglbMem
	      );

HGLOBAL
 
GlobalReAlloc(
	      HGLOBAL hMem,
	      DWORD dwBytes,
	      UINT uFlags
	      );

DWORD
 
GlobalSize(
	   HGLOBAL hMem
	   );

UINT
 
GlobalFlags(
	    HGLOBAL hMem
	    );


LPVOID
 
GlobalLock(
	   HGLOBAL hMem
	   );

HGLOBAL
 
GlobalHandle(
	     LPCVOID pMem
	     );


WINBOOL
 
GlobalUnlock(
	     HGLOBAL hMem
	     );


HGLOBAL
 
GlobalFree(
	   HGLOBAL hMem
	   );

UINT
 
GlobalCompact(
	      DWORD dwMinFree
	      );


void 
 
GlobalFix(
	  HGLOBAL hMem
	  );


void 
 
GlobalUnfix(
	    HGLOBAL hMem
	    );


LPVOID
 
GlobalWire(
	   HGLOBAL hMem
	   );


WINBOOL
 
GlobalUnWire(
	     HGLOBAL hMem
	     );


void 
 
GlobalMemoryStatus(
		   LPMEMORYSTATUS lpBuffer
		   );


HLOCAL
 
LocalAlloc(
	   UINT uFlags,
	   UINT uBytes
	   );

HLOCAL
LocalDiscard(
	     HLOCAL hlocMem
	     );

HLOCAL
 
LocalReAlloc(
	     HLOCAL hMem,
	     UINT uBytes,
	     UINT uFlags
	     );


LPVOID
 
LocalLock(
	  HLOCAL hMem
	  );


HLOCAL
 
LocalHandle(
	    LPCVOID pMem
	    );


WINBOOL
 
LocalUnlock(
	    HLOCAL hMem
	    );


UINT
 
LocalSize(
	  HLOCAL hMem
	  );


UINT
 
LocalFlags(
	   HLOCAL hMem
	   );


HLOCAL
 
LocalFree(
	  HLOCAL hMem
	  );


UINT
 
LocalShrink(
	    HLOCAL hMem,
	    UINT cbNewSize
	    );


UINT
 
LocalCompact(
	     UINT uMinFree
	     );


WINBOOL
 
FlushInstructionCache(
		      HANDLE hProcess,
		      LPCVOID lpBaseAddress,
		      DWORD dwSize
		      );


LPVOID
 
VirtualAlloc(
	     LPVOID lpAddress,
	     DWORD dwSize,
	     DWORD flAllocationType,
	     DWORD flProtect
	     );


WINBOOL
 
VirtualFree(
	    LPVOID lpAddress,
	    DWORD dwSize,
	    DWORD dwFreeType
	    );


WINBOOL
 
VirtualProtect(
	       LPVOID lpAddress,
	       DWORD dwSize,
	       DWORD flNewProtect,
	       PDWORD lpflOldProtect
	       );


DWORD
 
VirtualQuery(
	     LPCVOID lpAddress,
	     PMEMORY_BASIC_INFORMATION lpBuffer,
	     DWORD dwLength
	     );


WINBOOL
 
VirtualProtectEx(
		 HANDLE hProcess,
		 LPVOID lpAddress,
		 DWORD dwSize,
		 DWORD flNewProtect,
		 PDWORD lpflOldProtect
		 );


DWORD
 
VirtualQueryEx(
	       HANDLE hProcess,
	       LPCVOID lpAddress,
	       PMEMORY_BASIC_INFORMATION lpBuffer,
	       DWORD dwLength
	       );


HANDLE
 
HeapCreate(
	   DWORD flOptions,
	   DWORD dwInitialSize,
	   DWORD dwMaximumSize
	   );

WINBOOL
 
HeapDestroy(
	    HANDLE hHeap
	    );

LPVOID
 
HeapAlloc(
	  HANDLE hHeap,
	  DWORD dwFlags,
	  DWORD dwBytes
	  );

LPVOID
 
HeapReAlloc(
	    HANDLE hHeap,
	    DWORD dwFlags,
	    LPVOID lpMem,
	    DWORD dwBytes
	    );

WINBOOL
 
HeapFree(
	 HANDLE hHeap,
	 DWORD dwFlags,
	 LPVOID lpMem
	 );

DWORD
 
HeapSize(
	 HANDLE hHeap,
	 DWORD dwFlags,
	 LPCVOID lpMem
	 );

WINBOOL
 
HeapValidate(
	     HANDLE hHeap,
	     DWORD dwFlags,
	     LPCVOID lpMem
	     );

UINT
 
HeapCompact(
	    HANDLE hHeap,
	    DWORD dwFlags
	    );

HANDLE
 
GetProcessHeap( void  );

DWORD
 
GetProcessHeaps(
		DWORD NumberOfHeaps,
		PHANDLE ProcessHeaps
		);

WINBOOL
 
HeapLock(
	 HANDLE hHeap
	 );

WINBOOL
 
HeapUnlock(
	   HANDLE hHeap
	   );

WINBOOL
 
HeapWalk(
	 HANDLE hHeap,
	 LPPROCESS_HEAP_ENTRY lpEntry
	 );

WINBOOL
 
GetProcessAffinityMask(
		       HANDLE hProcess,
		       LPDWORD lpProcessAffinityMask,
		       LPDWORD lpSystemAffinityMask
		       );

WINBOOL
 
GetProcessTimes(
		HANDLE hProcess,
		LPFILETIME lpCreationTime,
		LPFILETIME lpExitTime,
		LPFILETIME lpKernelTime,
		LPFILETIME lpUserTime
		);

WINBOOL
 
GetProcessWorkingSetSize(
			 HANDLE hProcess,
			 LPDWORD lpMinimumWorkingSetSize,
			 LPDWORD lpMaximumWorkingSetSize
			 );

WINBOOL
 
SetProcessWorkingSetSize(
			 HANDLE hProcess,
			 DWORD dwMinimumWorkingSetSize,
			 DWORD dwMaximumWorkingSetSize
			 );

HANDLE
 
OpenProcess(
	    DWORD dwDesiredAccess,
	    WINBOOL bInheritHandle,
	    DWORD dwProcessId
	    );

HANDLE
 
GetCurrentProcess(
		  void 
		  );

DWORD
 
GetCurrentProcessId(
		    void 
		    );

void 
 
ExitProcess(
	    UINT uExitCode
	    ) __attribute__ ((noreturn));

WINBOOL
 
TerminateProcess(
		 HANDLE hProcess,
		 UINT uExitCode
		 );

WINBOOL
 
GetExitCodeProcess(
		   HANDLE hProcess,
		   LPDWORD lpExitCode
		   );

void 
 
FatalExit(
	  int ExitCode
	  );

void 
 
RaiseException(
	       DWORD dwExceptionCode,
	       DWORD dwExceptionFlags,
	       DWORD nNumberOfArguments,
	       const  DWORD *lpArguments
	       );

LONG
 
UnhandledExceptionFilter(
			 struct _EXCEPTION_POINTERS *ExceptionInfo
			 );

 









HANDLE
 
CreateThread(
	     LPSECURITY_ATTRIBUTES lpThreadAttributes,
	     DWORD dwStackSize,
	     LPTHREAD_START_ROUTINE lpStartAddress,
	     LPVOID lpParameter,
	     DWORD dwCreationFlags,
	     LPDWORD lpThreadId
	     );


HANDLE
 
CreateRemoteThread(
		   HANDLE hProcess,
		   LPSECURITY_ATTRIBUTES lpThreadAttributes,
		   DWORD dwStackSize,
		   LPTHREAD_START_ROUTINE lpStartAddress,
		   LPVOID lpParameter,
		   DWORD dwCreationFlags,
		   LPDWORD lpThreadId
		   );


HANDLE
 
GetCurrentThread(
		 void 
		 );


DWORD
 
GetCurrentThreadId(
		   void 
		   );


DWORD
 
SetThreadAffinityMask(
		      HANDLE hThread,
		      DWORD dwThreadAffinityMask
		      );


WINBOOL
 
SetThreadPriority(
		  HANDLE hThread,
		  int nPriority
		  );


int
 
GetThreadPriority(
		  HANDLE hThread
		  );


WINBOOL
 
GetThreadTimes(
	       HANDLE hThread,
	       LPFILETIME lpCreationTime,
	       LPFILETIME lpExitTime,
	       LPFILETIME lpKernelTime,
	       LPFILETIME lpUserTime
	       );


void 
 
ExitThread(
	   DWORD dwExitCode
	   );


WINBOOL
 
TerminateThread(
		HANDLE hThread,
		DWORD dwExitCode
		);


WINBOOL
 
GetExitCodeThread(
		  HANDLE hThread,
		  LPDWORD lpExitCode
		  );

WINBOOL
 
GetThreadSelectorEntry(
		       HANDLE hThread,
		       DWORD dwSelector,
		       LPLDT_ENTRY lpSelectorEntry
		       );


DWORD
 
GetLastError(
	     void 
	     );


void 
 
SetLastError(
	     DWORD dwErrCode
	     );


WINBOOL
 
GetOverlappedResult(
		    HANDLE hFile,
		    LPOVERLAPPED lpOverlapped,
		    LPDWORD lpNumberOfBytesTransferred,
		    WINBOOL bWait
		    );


HANDLE
 
CreateIoCompletionPort(
		       HANDLE FileHandle,
		       HANDLE ExistingCompletionPort,
		       DWORD CompletionKey,
		       DWORD NumberOfConcurrentThreads
		       );


WINBOOL
 
GetQueuedCompletionStatus(
			  HANDLE CompletionPort,
			  LPDWORD lpNumberOfBytesTransferred,
			  LPDWORD lpCompletionKey,
			  LPOVERLAPPED *lpOverlapped,
			  DWORD dwMilliseconds
			  );

UINT
 
SetErrorMode(
	     UINT uMode
	     );


WINBOOL
 
ReadProcessMemory(
		  HANDLE hProcess,
		  LPCVOID lpBaseAddress,
		  LPVOID lpBuffer,
		  DWORD nSize,
		  LPDWORD lpNumberOfBytesRead
		  );


WINBOOL
 
WriteProcessMemory(
		   HANDLE hProcess,
		   LPVOID lpBaseAddress,
		   LPVOID lpBuffer,
		   DWORD nSize,
		   LPDWORD lpNumberOfBytesWritten
		   );


WINBOOL
 
GetThreadContext(
		 HANDLE hThread,
		 LPCONTEXT lpContext
		 );


WINBOOL
 
SetThreadContext(
		 HANDLE hThread,
		 const  CONTEXT *lpContext
		 );


DWORD
 
SuspendThread(
	      HANDLE hThread
	      );


DWORD
 
ResumeThread(
	     HANDLE hThread
	     );


void 
 
DebugBreak(
	   void 
	   );


WINBOOL
 
WaitForDebugEvent(
		  LPDEBUG_EVENT lpDebugEvent,
		  DWORD dwMilliseconds
		  );


WINBOOL
 
ContinueDebugEvent(
		   DWORD dwProcessId,
		   DWORD dwThreadId,
		   DWORD dwContinueStatus
		   );


WINBOOL
 
DebugActiveProcess(
		   DWORD dwProcessId
		   );


void 
 
InitializeCriticalSection(
			  LPCRITICAL_SECTION lpCriticalSection
			  );


void 
 
EnterCriticalSection(
		     LPCRITICAL_SECTION lpCriticalSection
		     );


void 
 
LeaveCriticalSection(
		     LPCRITICAL_SECTION lpCriticalSection
		     );


void 
 
DeleteCriticalSection(
		      LPCRITICAL_SECTION lpCriticalSection
		      );


WINBOOL
 
SetEvent(
	 HANDLE hEvent
	 );


WINBOOL
 
ResetEvent(
	   HANDLE hEvent
	   );


WINBOOL
 
PulseEvent(
	   HANDLE hEvent
	   );


WINBOOL
 
ReleaseSemaphore(
		 HANDLE hSemaphore,
		 LONG lReleaseCount,
		 LPLONG lpPreviousCount
		 );


WINBOOL
 
ReleaseMutex(
	     HANDLE hMutex
	     );


DWORD
 
WaitForSingleObject(
		    HANDLE hHandle,
		    DWORD dwMilliseconds
		    );


DWORD
 
WaitForMultipleObjects(
		       DWORD nCount,
		       const  HANDLE *lpHandles,
		       WINBOOL bWaitAll,
		       DWORD dwMilliseconds
		       );


void 
 
Sleep(
      DWORD dwMilliseconds
      );


HGLOBAL
 
LoadResource(
	     HINSTANCE hModule,
	     HRSRC hResInfo
	     );


DWORD
 
SizeofResource(
	       HINSTANCE hModule,
	       HRSRC hResInfo
	       );



ATOM
 
GlobalDeleteAtom(
		 ATOM nAtom
		 );


WINBOOL
 
InitAtomTable(
	      DWORD nSize
	      );


ATOM
 
DeleteAtom(
	   ATOM nAtom
	   );


UINT
 
SetHandleCount(
	       UINT uNumber
	       );


DWORD
 
GetLogicalDrives(
		 void 
		 );


WINBOOL
 
LockFile(
	 HANDLE hFile,
	 DWORD dwFileOffsetLow,
	 DWORD dwFileOffsetHigh,
	 DWORD nNumberOfBytesToLockLow,
	 DWORD nNumberOfBytesToLockHigh
	 );


WINBOOL
 
UnlockFile(
	   HANDLE hFile,
	   DWORD dwFileOffsetLow,
	   DWORD dwFileOffsetHigh,
	   DWORD nNumberOfBytesToUnlockLow,
	   DWORD nNumberOfBytesToUnlockHigh
	   );


WINBOOL
 
LockFileEx(
	   HANDLE hFile,
	   DWORD dwFlags,
	   DWORD dwReserved,
	   DWORD nNumberOfBytesToLockLow,
	   DWORD nNumberOfBytesToLockHigh,
	   LPOVERLAPPED lpOverlapped
	   );

WINBOOL
 
UnlockFileEx(
	     HANDLE hFile,
	     DWORD dwReserved,
	     DWORD nNumberOfBytesToUnlockLow,
	     DWORD nNumberOfBytesToUnlockHigh,
	     LPOVERLAPPED lpOverlapped
	     );

WINBOOL
 
GetFileInformationByHandle(
			   HANDLE hFile,
			   LPBY_HANDLE_FILE_INFORMATION lpFileInformation
			   );


DWORD
 
GetFileType(
	    HANDLE hFile
	    );


DWORD
 
GetFileSize(
	    HANDLE hFile,
	    LPDWORD lpFileSizeHigh
	    );


HANDLE
 
GetStdHandle(
	     DWORD nStdHandle
	     );


WINBOOL
 
SetStdHandle(
	     DWORD nStdHandle,
	     HANDLE hHandle
	     );


WINBOOL
 
WriteFile(
	  HANDLE hFile,
	  LPCVOID lpBuffer,
	  DWORD nNumberOfBytesToWrite,
	  LPDWORD lpNumberOfBytesWritten,
	  LPOVERLAPPED lpOverlapped
	  );


WINBOOL
 
ReadFile(
	 HANDLE hFile,
	 LPVOID lpBuffer,
	 DWORD nNumberOfBytesToRead,
	 LPDWORD lpNumberOfBytesRead,
	 LPOVERLAPPED lpOverlapped
	 );


WINBOOL
 
FlushFileBuffers(
		 HANDLE hFile
		 );


WINBOOL
 
DeviceIoControl(
		HANDLE hDevice,
		DWORD dwIoControlCode,
		LPVOID lpInBuffer,
		DWORD nInBufferSize,
		LPVOID lpOutBuffer,
		DWORD nOutBufferSize,
		LPDWORD lpBytesReturned,
		LPOVERLAPPED lpOverlapped
		);


WINBOOL
 
SetEndOfFile(
	     HANDLE hFile
	     );


DWORD
 
SetFilePointer(
	       HANDLE hFile,
	       LONG lDistanceToMove,
	       PLONG lpDistanceToMoveHigh,
	       DWORD dwMoveMethod
	       );


WINBOOL
 
FindClose(
	  HANDLE hFindFile
	  );


WINBOOL
 
GetFileTime(
	    HANDLE hFile,
	    LPFILETIME lpCreationTime,
	    LPFILETIME lpLastAccessTime,
	    LPFILETIME lpLastWriteTime
	    );


WINBOOL
 
SetFileTime(
	    HANDLE hFile,
	    const  FILETIME *lpCreationTime,
	    const  FILETIME *lpLastAccessTime,
	    const  FILETIME *lpLastWriteTime
	    );


WINBOOL
 
CloseHandle(
	    HANDLE hObject
	    );


WINBOOL
 
DuplicateHandle(
		HANDLE hSourceProcessHandle,
		HANDLE hSourceHandle,
		HANDLE hTargetProcessHandle,
		LPHANDLE lpTargetHandle,
		DWORD dwDesiredAccess,
		WINBOOL bInheritHandle,
		DWORD dwOptions
		);


WINBOOL
 
GetHandleInformation(
		     HANDLE hObject,
		     LPDWORD lpdwFlags
		     );


WINBOOL
 
SetHandleInformation(
		     HANDLE hObject,
		     DWORD dwMask,
		     DWORD dwFlags
		     );

DWORD
 
LoadModule(
	   LPCSTR lpModuleName,
	   LPVOID lpParameterBlock
	   );


UINT
 
WinExec(
	LPCSTR lpCmdLine,
	UINT uCmdShow
	);


WINBOOL
 
ClearCommBreak(
	       HANDLE hFile
	       );


WINBOOL
 
ClearCommError(
	       HANDLE hFile,
	       LPDWORD lpErrors,
	       LPCOMSTAT lpStat
	       );


WINBOOL
 
SetupComm(
	  HANDLE hFile,
	  DWORD dwInQueue,
	  DWORD dwOutQueue
	  );


WINBOOL
 
EscapeCommFunction(
		   HANDLE hFile,
		   DWORD dwFunc
		   );


WINBOOL
 
GetCommConfig(
	      HANDLE hCommDev,
	      LPCOMMCONFIG lpCC,
	      LPDWORD lpdwSize
	      );


WINBOOL
 
GetCommMask(
	    HANDLE hFile,
	    LPDWORD lpEvtMask
	    );


WINBOOL
 
GetCommProperties(
		  HANDLE hFile,
		  LPCOMMPROP lpCommProp
		  );


WINBOOL
 
GetCommModemStatus(
		   HANDLE hFile,
		   LPDWORD lpModemStat
		   );


WINBOOL
 
GetCommState(
	     HANDLE hFile,
	     LPDCB lpDCB
	     );


WINBOOL
 
GetCommTimeouts(
		HANDLE hFile,
		LPCOMMTIMEOUTS lpCommTimeouts
		);


WINBOOL
 
PurgeComm(
	  HANDLE hFile,
	  DWORD dwFlags
	  );


WINBOOL
 
SetCommBreak(
	     HANDLE hFile
	     );


WINBOOL
 
SetCommConfig(
	      HANDLE hCommDev,
	      LPCOMMCONFIG lpCC,
	      DWORD dwSize
	      );


WINBOOL
 
SetCommMask(
	    HANDLE hFile,
	    DWORD dwEvtMask
	    );


WINBOOL
 
SetCommState(
	     HANDLE hFile,
	     LPDCB lpDCB
	     );


WINBOOL
 
SetCommTimeouts(
		HANDLE hFile,
		LPCOMMTIMEOUTS lpCommTimeouts
		);


WINBOOL
 
TransmitCommChar(
		 HANDLE hFile,
		 char cChar
		 );


WINBOOL
 
WaitCommEvent(
	      HANDLE hFile,
	      LPDWORD lpEvtMask,
	      LPOVERLAPPED lpOverlapped
	      );



DWORD
 
SetTapePosition(
		HANDLE hDevice,
		DWORD dwPositionMethod,
		DWORD dwPartition,
		DWORD dwOffsetLow,
		DWORD dwOffsetHigh,
		WINBOOL bImmediate
		);


DWORD
 
GetTapePosition(
		HANDLE hDevice,
		DWORD dwPositionType,
		LPDWORD lpdwPartition,
		LPDWORD lpdwOffsetLow,
		LPDWORD lpdwOffsetHigh
		);


DWORD
 
PrepareTape(
	    HANDLE hDevice,
	    DWORD dwOperation,
	    WINBOOL bImmediate
	    );


DWORD
 
EraseTape(
	  HANDLE hDevice,
	  DWORD dwEraseType,
	  WINBOOL bImmediate
	  );


DWORD
 
CreateTapePartition(
		    HANDLE hDevice,
		    DWORD dwPartitionMethod,
		    DWORD dwCount,
		    DWORD dwSize
		    );


DWORD
 
WriteTapemark(
	      HANDLE hDevice,
	      DWORD dwTapemarkType,
	      DWORD dwTapemarkCount,
	      WINBOOL bImmediate
	      );


DWORD
 
GetTapeStatus(
	      HANDLE hDevice
	      );


DWORD
 
GetTapeParameters(
		  HANDLE hDevice,
		  DWORD dwOperation,
		  LPDWORD lpdwSize,
		  LPVOID lpTapeInformation
		  );

DWORD
 
SetTapeParameters(
		  HANDLE hDevice,
		  DWORD dwOperation,
		  LPVOID lpTapeInformation
		  );

WINBOOL
 
Beep(
     DWORD dwFreq,
     DWORD dwDuration
     );


void 
 
OpenSound(
	  void 
	  );


void 
 
CloseSound(
	   void 
	   );


void 
 
StartSound(
	   void 
	   );


void 
 
StopSound(
	  void 
	  );


DWORD
 
WaitSoundState(
	       DWORD nState
	       );


DWORD
 
SyncAllVoices(
	      void 
	      );


DWORD
 
CountVoiceNotes(
		DWORD nVoice
		);


LPDWORD
 
GetThresholdEvent(
		  void 
		  );


DWORD
 
GetThresholdStatus(
		   void 
		   );


DWORD
 
SetSoundNoise(
	      DWORD nSource,
	      DWORD nDuration
	      );


DWORD
 
SetVoiceAccent(
	       DWORD nVoice,
	       DWORD nTempo,
	       DWORD nVolume,
	       DWORD nMode,
	       DWORD nPitch
	       );


DWORD
 
SetVoiceEnvelope(
		 DWORD nVoice,
		 DWORD nShape,
		 DWORD nRepeat
		 );


DWORD
 
SetVoiceNote(
	     DWORD nVoice,
	     DWORD nValue,
	     DWORD nLength,
	     DWORD nCdots
	     );


DWORD
 
SetVoiceQueueSize(
		  DWORD nVoice,
		  DWORD nBytes
		  );


DWORD
 
SetVoiceSound(
	      DWORD nVoice,
	      DWORD Frequency,
	      DWORD nDuration
	      );


DWORD
 
SetVoiceThreshold(
		  DWORD nVoice,
		  DWORD nNotes
		  );


int
 
MulDiv(
       int nNumber,
       int nNumerator,
       int nDenominator
       );


void 
 
GetSystemTime(
	      LPSYSTEMTIME lpSystemTime
	      );


WINBOOL
 
SetSystemTime(
	      const  SYSTEMTIME *lpSystemTime
	      );


void 
 
GetLocalTime(
	     LPSYSTEMTIME lpSystemTime
	     );


WINBOOL
 
SetLocalTime(
	     const  SYSTEMTIME *lpSystemTime
	     );


void 
 
GetSystemInfo(
	      LPSYSTEM_INFO lpSystemInfo
	      );

WINBOOL
 
SystemTimeToTzSpecificLocalTime(
				LPTIME_ZONE_INFORMATION lpTimeZoneInformation,
				LPSYSTEMTIME lpUniversalTime,
				LPSYSTEMTIME lpLocalTime
				);


DWORD
 
GetTimeZoneInformation(
		       LPTIME_ZONE_INFORMATION lpTimeZoneInformation
		       );


WINBOOL
 
SetTimeZoneInformation(
		       const  TIME_ZONE_INFORMATION *lpTimeZoneInformation
		       );

WINBOOL
 
SystemTimeToFileTime(
		     const  SYSTEMTIME *lpSystemTime,
		     LPFILETIME lpFileTime
		     );


WINBOOL
 
FileTimeToLocalFileTime(
			const  FILETIME *lpFileTime,
			LPFILETIME lpLocalFileTime
			);


WINBOOL
 
LocalFileTimeToFileTime(
			const  FILETIME *lpLocalFileTime,
			LPFILETIME lpFileTime
			);


WINBOOL
 
FileTimeToSystemTime(
		     const  FILETIME *lpFileTime,
		     LPSYSTEMTIME lpSystemTime
		     );


LONG
 
CompareFileTime(
		const  FILETIME *lpFileTime1,
		const  FILETIME *lpFileTime2
		);


WINBOOL
 
FileTimeToDosDateTime(
		      const  FILETIME *lpFileTime,
		      LPWORD lpFatDate,
		      LPWORD lpFatTime
		      );


WINBOOL
 
DosDateTimeToFileTime(
		      WORD wFatDate,
		      WORD wFatTime,
		      LPFILETIME lpFileTime
		      );


DWORD
 
GetTickCount(
	     void 
	     );


WINBOOL
 
SetSystemTimeAdjustment(
			DWORD dwTimeAdjustment,
			WINBOOL  bTimeAdjustmentDisabled
			);


WINBOOL
 
GetSystemTimeAdjustment(
			PDWORD lpTimeAdjustment,
			PDWORD lpTimeIncrement,
			PWINBOOL  lpTimeAdjustmentDisabled
			);


WINBOOL
 
CreatePipe(
	   PHANDLE hReadPipe,
	   PHANDLE hWritePipe,
	   LPSECURITY_ATTRIBUTES lpPipeAttributes,
	   DWORD nSize
	   );


WINBOOL
 
ConnectNamedPipe(
		 HANDLE hNamedPipe,
		 LPOVERLAPPED lpOverlapped
		 );


WINBOOL
 
DisconnectNamedPipe(
		    HANDLE hNamedPipe
		    );


WINBOOL
 
SetNamedPipeHandleState(
			HANDLE hNamedPipe,
			LPDWORD lpMode,
			LPDWORD lpMaxCollectionCount,
			LPDWORD lpCollectDataTimeout
			);


WINBOOL
 
GetNamedPipeInfo(
		 HANDLE hNamedPipe,
		 LPDWORD lpFlags,
		 LPDWORD lpOutBufferSize,
		 LPDWORD lpInBufferSize,
		 LPDWORD lpMaxInstances
		 );


WINBOOL
 
PeekNamedPipe(
	      HANDLE hNamedPipe,
	      LPVOID lpBuffer,
	      DWORD nBufferSize,
	      LPDWORD lpBytesRead,
	      LPDWORD lpTotalBytesAvail,
	      LPDWORD lpBytesLeftThisMessage
	      );


WINBOOL
 
TransactNamedPipe(
		  HANDLE hNamedPipe,
		  LPVOID lpInBuffer,
		  DWORD nInBufferSize,
		  LPVOID lpOutBuffer,
		  DWORD nOutBufferSize,
		  LPDWORD lpBytesRead,
		  LPOVERLAPPED lpOverlapped
		  );



WINBOOL
 
GetMailslotInfo(
		HANDLE hMailslot,
		LPDWORD lpMaxMessageSize,
		LPDWORD lpNextSize,
		LPDWORD lpMessageCount,
		LPDWORD lpReadTimeout
		);


WINBOOL
 
SetMailslotInfo(
		HANDLE hMailslot,
		DWORD lReadTimeout
		);


LPVOID
 
MapViewOfFile(
	      HANDLE hFileMappingObject,
	      DWORD dwDesiredAccess,
	      DWORD dwFileOffsetHigh,
	      DWORD dwFileOffsetLow,
	      DWORD dwNumberOfBytesToMap
	      );


WINBOOL
 
FlushViewOfFile(
		LPCVOID lpBaseAddress,
		DWORD dwNumberOfBytesToFlush
		);


WINBOOL
 
UnmapViewOfFile(
		LPVOID lpBaseAddress
		);

HFILE
 
OpenFile(
	 LPCSTR lpFileName,
	 LPOFSTRUCT lpReOpenBuff,
	 UINT uStyle
	 );


HFILE
 
_lopen(
       LPCSTR lpPathName,
       int iReadWrite
       );


HFILE
 
_lcreat(
	LPCSTR lpPathName,
	int  iAttribute
	);


UINT
 
_lread(
       HFILE hFile,
       LPVOID lpBuffer,
       UINT uBytes
       );


UINT
 
_lwrite(
	HFILE hFile,
	LPCSTR lpBuffer,
	UINT uBytes
	);


long
 
_hread(
       HFILE hFile,
       LPVOID lpBuffer,
       long lBytes
       );


long
 
_hwrite(
	HFILE hFile,
	LPCSTR lpBuffer,
	long lBytes
	);


HFILE
 
_lclose(
	HFILE hFile
	);


LONG
 
_llseek(
	HFILE hFile,
	LONG lOffset,
	int iOrigin
	);


WINBOOL
 
IsTextUnicode(
	      const  LPVOID lpBuffer,
	      int cb,
	      LPINT lpi
	      );


DWORD
 
TlsAlloc(
	 void 
	 );

LPVOID
 
TlsGetValue(
	    DWORD dwTlsIndex
	    );


WINBOOL
 
TlsSetValue(
	    DWORD dwTlsIndex,
	    LPVOID lpTlsValue
	    );


WINBOOL
 
TlsFree(
	DWORD dwTlsIndex
	);

DWORD
 
SleepEx(
	DWORD dwMilliseconds,
	WINBOOL bAlertable
	);


DWORD
 
WaitForSingleObjectEx(
		      HANDLE hHandle,
		      DWORD dwMilliseconds,
		      WINBOOL bAlertable
		      );


DWORD
 
WaitForMultipleObjectsEx(
			 DWORD nCount,
			 const  HANDLE *lpHandles,
			 WINBOOL bWaitAll,
			 DWORD dwMilliseconds,
			 WINBOOL bAlertable
			 );


WINBOOL
 
ReadFileEx(
	   HANDLE hFile,
	   LPVOID lpBuffer,
	   DWORD nNumberOfBytesToRead,
	   LPOVERLAPPED lpOverlapped,
	   LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	   );


WINBOOL
 
WriteFileEx(
	    HANDLE hFile,
	    LPCVOID lpBuffer,
	    DWORD nNumberOfBytesToWrite,
	    LPOVERLAPPED lpOverlapped,
	    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	    );


WINBOOL
 
BackupRead(
	   HANDLE hFile,
	   LPBYTE lpBuffer,
	   DWORD nNumberOfBytesToRead,
	   LPDWORD lpNumberOfBytesRead,
	   WINBOOL bAbort,
	   WINBOOL bProcessSecurity,
	   LPVOID *lpContext
	   );


WINBOOL
 
BackupSeek(
	   HANDLE hFile,
	   DWORD  dwLowBytesToSeek,
	   DWORD  dwHighBytesToSeek,
	   LPDWORD lpdwLowByteSeeked,
	   LPDWORD lpdwHighByteSeeked,
	   LPVOID *lpContext
	   );


WINBOOL
 
BackupWrite(
	    HANDLE hFile,
	    LPBYTE lpBuffer,
	    DWORD nNumberOfBytesToWrite,
	    LPDWORD lpNumberOfBytesWritten,
	    WINBOOL bAbort,
	    WINBOOL bProcessSecurity,
	    LPVOID *lpContext
	    );

WINBOOL
 
SetProcessShutdownParameters(
			     DWORD dwLevel,
			     DWORD dwFlags
			     );


WINBOOL
 
GetProcessShutdownParameters(
			     LPDWORD lpdwLevel,
			     LPDWORD lpdwFlags
			     );


void 
 
SetFileApisToOEM( void  );


void 
 
SetFileApisToANSI( void  );


WINBOOL
 
AreFileApisANSI( void  );

WINBOOL
 
CloseEventLog (
	       HANDLE hEventLog
		);


WINBOOL
 
DeregisterEventSource (
		       HANDLE hEventLog
			);


WINBOOL
 
NotifyChangeEventLog (
		      HANDLE hEventLog,
		      HANDLE hEvent
		       );


WINBOOL
 
GetNumberOfEventLogRecords (
			    HANDLE hEventLog,
			    PDWORD NumberOfRecords
			     );


WINBOOL
 
GetOldestEventLogRecord (
			 HANDLE hEventLog,
			 PDWORD OldestRecord
			  );

WINBOOL
 
DuplicateToken(
	       HANDLE ExistingTokenHandle,
	       SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
	       PHANDLE DuplicateTokenHandle
	       );


WINBOOL
 
GetKernelObjectSecurity (
			 HANDLE Handle,
			 SECURITY_INFORMATION RequestedInformation,
			 PSECURITY_DESCRIPTOR pSecurityDescriptor,
			 DWORD nLength,
			 LPDWORD lpnLengthNeeded
			  );


WINBOOL
 
ImpersonateNamedPipeClient(
			   HANDLE hNamedPipe
			   );


WINBOOL
 
ImpersonateLoggedOnUser(
			   HANDLE hToken
			   );


WINBOOL
 
ImpersonateSelf(
		SECURITY_IMPERSONATION_LEVEL ImpersonationLevel
		);



WINBOOL
 
RevertToSelf (
	      void 
	       );


WINBOOL
 
SetThreadToken (
		PHANDLE Thread,
		HANDLE Token
		 );


WINBOOL
 
AccessCheck (
	     PSECURITY_DESCRIPTOR pSecurityDescriptor,
	     HANDLE ClientToken,
	     DWORD DesiredAccess,
	     PGENERIC_MAPPING GenericMapping,
	     PPRIVILEGE_SET PrivilegeSet,
	     LPDWORD PrivilegeSetLength,
	     LPDWORD GrantedAccess,
	     LPBOOL AccessStatus
	      );



WINBOOL
 
OpenProcessToken (
		  HANDLE ProcessHandle,
		  DWORD DesiredAccess,
		  PHANDLE TokenHandle
		   );



WINBOOL
 
OpenThreadToken (
		 HANDLE ThreadHandle,
		 DWORD DesiredAccess,
		 WINBOOL OpenAsSelf,
		 PHANDLE TokenHandle
		  );



WINBOOL
 
GetTokenInformation (
		     HANDLE TokenHandle,
		     TOKEN_INFORMATION_CLASS TokenInformationClass,
		     LPVOID TokenInformation,
		     DWORD TokenInformationLength,
		     PDWORD ReturnLength
		      );



WINBOOL
 
SetTokenInformation (
		     HANDLE TokenHandle,
		     TOKEN_INFORMATION_CLASS TokenInformationClass,
		     LPVOID TokenInformation,
		     DWORD TokenInformationLength
		      );



WINBOOL
 
AdjustTokenPrivileges (
		       HANDLE TokenHandle,
		       WINBOOL DisableAllPrivileges,
		       PTOKEN_PRIVILEGES NewState,
		       DWORD BufferLength,
		       PTOKEN_PRIVILEGES PreviousState,
		       PDWORD ReturnLength
			);



WINBOOL
 
AdjustTokenGroups (
		   HANDLE TokenHandle,
		   WINBOOL ResetToDefault,
		   PTOKEN_GROUPS NewState,
		   DWORD BufferLength,
		   PTOKEN_GROUPS PreviousState,
		   PDWORD ReturnLength
		    );



WINBOOL
 
PrivilegeCheck (
		HANDLE ClientToken,
		PPRIVILEGE_SET RequiredPrivileges,
		LPBOOL pfResult
		 );



WINBOOL
 
IsValidSid (
	    PSID pSid
	     );



WINBOOL
 
EqualSid (
	  PSID pSid1,
	  PSID pSid2
	   );



WINBOOL
 
EqualPrefixSid (
		PSID pSid1,
		PSID pSid2
		 );



DWORD
 
GetSidLengthRequired (
		      UCHAR nSubAuthorityCount
		       );



WINBOOL
 
AllocateAndInitializeSid (
			  PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
			  BYTE nSubAuthorityCount,
			  DWORD nSubAuthority0,
			  DWORD nSubAuthority1,
			  DWORD nSubAuthority2,
			  DWORD nSubAuthority3,
			  DWORD nSubAuthority4,
			  DWORD nSubAuthority5,
			  DWORD nSubAuthority6,
			  DWORD nSubAuthority7,
			  PSID *pSid
			   );


PVOID
 
FreeSid(
	PSID pSid
	);


WINBOOL
 
InitializeSid (
	       PSID Sid,
	       PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
	       BYTE nSubAuthorityCount
		);



PSID_IDENTIFIER_AUTHORITY
 
GetSidIdentifierAuthority (
			   PSID pSid
			    );



PDWORD
 
GetSidSubAuthority (
		    PSID pSid,
		    DWORD nSubAuthority
		     );



PUCHAR
 
GetSidSubAuthorityCount (
			 PSID pSid
			  );



DWORD
 
GetLengthSid (
	      PSID pSid
	       );



WINBOOL
 
CopySid (
	 DWORD nDestinationSidLength,
	 PSID pDestinationSid,
	 PSID pSourceSid
	  );



WINBOOL
 
AreAllAccessesGranted (
		       DWORD GrantedAccess,
		       DWORD DesiredAccess
			);



WINBOOL
 
AreAnyAccessesGranted (
		       DWORD GrantedAccess,
		       DWORD DesiredAccess
			);



void 
 
MapGenericMask (
		PDWORD AccessMask,
		PGENERIC_MAPPING GenericMapping
		 );



WINBOOL
 
IsValidAcl (
	    PACL pAcl
	     );



WINBOOL
 
InitializeAcl (
	       PACL pAcl,
	       DWORD nAclLength,
	       DWORD dwAclRevision
		);



WINBOOL
 
GetAclInformation (
		   PACL pAcl,
		   LPVOID pAclInformation,
		   DWORD nAclInformationLength,
		   ACL_INFORMATION_CLASS dwAclInformationClass
		    );



WINBOOL
 
SetAclInformation (
		   PACL pAcl,
		   LPVOID pAclInformation,
		   DWORD nAclInformationLength,
		   ACL_INFORMATION_CLASS dwAclInformationClass
		    );



WINBOOL
 
AddAce (
	PACL pAcl,
	DWORD dwAceRevision,
	DWORD dwStartingAceIndex,
	LPVOID pAceList,
	DWORD nAceListLength
	 );



WINBOOL
 
DeleteAce (
	   PACL pAcl,
	   DWORD dwAceIndex
	    );



WINBOOL
 
GetAce (
	PACL pAcl,
	DWORD dwAceIndex,
	LPVOID *pAce
	 );



WINBOOL
 
AddAccessAllowedAce (
		     PACL pAcl,
		     DWORD dwAceRevision,
		     DWORD AccessMask,
		     PSID pSid
		      );



WINBOOL
 
AddAccessDeniedAce (
		    PACL pAcl,
		    DWORD dwAceRevision,
		    DWORD AccessMask,
		    PSID pSid
		     );



WINBOOL
 
AddAuditAccessAce(
		  PACL pAcl,
		  DWORD dwAceRevision,
		  DWORD dwAccessMask,
		  PSID pSid,
		  WINBOOL bAuditSuccess,
		  WINBOOL bAuditFailure
		  );



WINBOOL
 
FindFirstFreeAce (
		  PACL pAcl,
		  LPVOID *pAce
		   );



WINBOOL
 
InitializeSecurityDescriptor (
			      PSECURITY_DESCRIPTOR pSecurityDescriptor,
			      DWORD dwRevision
			       );



WINBOOL
 
IsValidSecurityDescriptor (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor
			    );



DWORD
 
GetSecurityDescriptorLength (
			     PSECURITY_DESCRIPTOR pSecurityDescriptor
			      );



WINBOOL
 
GetSecurityDescriptorControl (
			      PSECURITY_DESCRIPTOR pSecurityDescriptor,
			      PSECURITY_DESCRIPTOR_CONTROL pControl,
			      LPDWORD lpdwRevision
			       );



WINBOOL
 
SetSecurityDescriptorDacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   WINBOOL bDaclPresent,
			   PACL pDacl,
			   WINBOOL bDaclDefaulted
			    );



WINBOOL
 
GetSecurityDescriptorDacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   LPBOOL lpbDaclPresent,
			   PACL *pDacl,
			   LPBOOL lpbDaclDefaulted
			    );



WINBOOL
 
SetSecurityDescriptorSacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   WINBOOL bSaclPresent,
			   PACL pSacl,
			   WINBOOL bSaclDefaulted
			    );



WINBOOL
 
GetSecurityDescriptorSacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   LPBOOL lpbSaclPresent,
			   PACL *pSacl,
			   LPBOOL lpbSaclDefaulted
			    );



WINBOOL
 
SetSecurityDescriptorOwner (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID pOwner,
			    WINBOOL bOwnerDefaulted
			     );



WINBOOL
 
GetSecurityDescriptorOwner (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID *pOwner,
			    LPBOOL lpbOwnerDefaulted
			     );



WINBOOL
 
SetSecurityDescriptorGroup (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID pGroup,
			    WINBOOL bGroupDefaulted
			     );



WINBOOL
 
GetSecurityDescriptorGroup (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID *pGroup,
			    LPBOOL lpbGroupDefaulted
			     );



WINBOOL
 
CreatePrivateObjectSecurity (
			     PSECURITY_DESCRIPTOR ParentDescriptor,
			     PSECURITY_DESCRIPTOR CreatorDescriptor,
			     PSECURITY_DESCRIPTOR * NewDescriptor,
			     WINBOOL IsDirectoryObject,
			     HANDLE Token,
			     PGENERIC_MAPPING GenericMapping
			      );



WINBOOL
 
SetPrivateObjectSecurity (
			  SECURITY_INFORMATION SecurityInformation,
			  PSECURITY_DESCRIPTOR ModificationDescriptor,
			  PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
			  PGENERIC_MAPPING GenericMapping,
			  HANDLE Token
			   );



WINBOOL
 
GetPrivateObjectSecurity (
			  PSECURITY_DESCRIPTOR ObjectDescriptor,
			  SECURITY_INFORMATION SecurityInformation,
			  PSECURITY_DESCRIPTOR ResultantDescriptor,
			  DWORD DescriptorLength,
			  PDWORD ReturnLength
			   );



WINBOOL
 
DestroyPrivateObjectSecurity (
			      PSECURITY_DESCRIPTOR * ObjectDescriptor
			       );



WINBOOL
 
MakeSelfRelativeSD (
		    PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor,
		    PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,
		    LPDWORD lpdwBufferLength
		     );



WINBOOL
 
MakeAbsoluteSD (
		PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,
		PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor,
		LPDWORD lpdwAbsoluteSecurityDescriptorSize,
		PACL pDacl,
		LPDWORD lpdwDaclSize,
		PACL pSacl,
		LPDWORD lpdwSaclSize,
		PSID pOwner,
		LPDWORD lpdwOwnerSize,
		PSID pPrimaryGroup,
		LPDWORD lpdwPrimaryGroupSize
		 );



WINBOOL
 
SetKernelObjectSecurity (
			 HANDLE Handle,
			 SECURITY_INFORMATION SecurityInformation,
			 PSECURITY_DESCRIPTOR SecurityDescriptor
			  );


WINBOOL
 
FindNextChangeNotification(
			   HANDLE hChangeHandle
			   );


WINBOOL
 
FindCloseChangeNotification(
			    HANDLE hChangeHandle
			    );


WINBOOL
 
VirtualLock(
	    LPVOID lpAddress,
	    DWORD dwSize
	    );


WINBOOL
 
VirtualUnlock(
	      LPVOID lpAddress,
	      DWORD dwSize
	      );


LPVOID
 
MapViewOfFileEx(
		HANDLE hFileMappingObject,
		DWORD dwDesiredAccess,
		DWORD dwFileOffsetHigh,
		DWORD dwFileOffsetLow,
		DWORD dwNumberOfBytesToMap,
		LPVOID lpBaseAddress
		);


WINBOOL
 
SetPriorityClass(
		 HANDLE hProcess,
		 DWORD dwPriorityClass
		 );


DWORD
 
GetPriorityClass(
		 HANDLE hProcess
		 );


WINBOOL
 
IsBadReadPtr(
	     const  void  *lp,
	     UINT ucb
	     );


WINBOOL
 
IsBadWritePtr(
	      LPVOID lp,
	      UINT ucb
	      );


WINBOOL
 
IsBadHugeReadPtr(
		 const  void  *lp,
		 UINT ucb
		 );


WINBOOL
 
IsBadHugeWritePtr(
		  LPVOID lp,
		  UINT ucb
		  );


WINBOOL
 
IsBadCodePtr(
	     FARPROC lpfn
	     );

WINBOOL
 
AllocateLocallyUniqueId(
			PLUID Luid
			);


WINBOOL
 
QueryPerformanceCounter(
			LARGE_INTEGER *lpPerformanceCount
			);


WINBOOL
 
QueryPerformanceFrequency(
			  LARGE_INTEGER *lpFrequency
			  );

void 
 
MoveMemory (
	    PVOID Destination,
	    const  void  *Source,
	    DWORD Length
	     );

void 
 
FillMemory (
	    PVOID Destination,
	    DWORD Length,
	    BYTE  Fill
	     );

void 
 
ZeroMemory (
	    PVOID Destination,
	    DWORD Length
	     );

 












WINBOOL
 
ActivateKeyboardLayout(
		       HKL hkl,
		       UINT Flags);


 
int
 
ToUnicodeEx(
	    UINT wVirtKey,
	    UINT wScanCode,
	    PBYTE lpKeyState,
	    LPWSTR pwszBuff,
	    int cchBuff,
	    UINT wFlags,
	    HKL dwhkl);

 
WINBOOL
 
UnloadKeyboardLayout(
		     HKL hkl);

 
int
 
GetKeyboardLayoutList(
		      int nBuff,
		      HKL *lpList);

 
HKL
 
GetKeyboardLayout(
		  DWORD dwLayout
		  );

 
HDESK
 
OpenInputDesktop(
		 DWORD dwFlags,
		 WINBOOL fInherit,
		 DWORD dwDesiredAccess);

WINBOOL
 
EnumDesktopWindows(
		   HDESK hDesktop,
		   ENUMWINDOWSPROC lpfn,
		   LPARAM lParam);

 
WINBOOL
 
SwitchDesktop(
	      HDESK hDesktop);

 
WINBOOL
 
SetThreadDesktop(
		 HDESK hDesktop);

 
WINBOOL
 
CloseDesktop(
	     HDESK hDesktop);

 
HDESK
 
GetThreadDesktop(
		 DWORD dwThreadId);

 
WINBOOL
 
CloseWindowStation(
		   HWINSTA hWinSta);

 
WINBOOL
 
SetProcessWindowStation(
			HWINSTA hWinSta);

 
HWINSTA
 
GetProcessWindowStation(
			void );

 
WINBOOL
 
SetUserObjectSecurity(
		      HANDLE hObj,
		      PSECURITY_INFORMATION pSIRequested,
		      PSECURITY_DESCRIPTOR pSID);

 
WINBOOL
 
GetUserObjectSecurity(
		      HANDLE hObj,
		      PSECURITY_INFORMATION pSIRequested,
		      PSECURITY_DESCRIPTOR pSID,
		      DWORD nLength,
		      LPDWORD lpnLengthNeeded);

 
WINBOOL
 
TranslateMessage(
		 const  MSG *lpMsg);

WINBOOL
 
SetMessageQueue(
		int cMessagesMax);

WINBOOL
 
RegisterHotKey(
	       HWND hWnd ,
	       int anID,
	       UINT fsModifiers,
	       UINT vk);

 
WINBOOL
 
UnregisterHotKey(
		 HWND hWnd,
		 int anID);

 
WINBOOL
 
ExitWindowsEx(
	      UINT uFlags,
	      DWORD dwReserved);

 
WINBOOL
 
SwapMouseButton(
		WINBOOL fSwap);

 
DWORD
 
GetMessagePos(
	      void );

 
LONG
 
GetMessageTime(
	       void );

 
LONG
 
GetMessageExtraInfo(
		    void );

 
LPARAM
 
SetMessageExtraInfo(
		    LPARAM lParam);

 
long  
   
BroadcastSystemMessage(
		       DWORD, 
		       LPDWORD, 
		       UINT, 
		       WPARAM, 
		       LPARAM);

WINBOOL
 
AttachThreadInput(
		  DWORD idAttach,
		  DWORD idAttachTo,
		  WINBOOL fAttach);

 
WINBOOL
 
ReplyMessage(
	     LRESULT lResult);

 
WINBOOL
 
WaitMessage(
	    void );

 
DWORD
 
WaitForInputIdle(
		 HANDLE hProcess,
		 DWORD dwMilliseconds);

 
void 
 
PostQuitMessage(
		int nExitCode);

WINBOOL
 
InSendMessage(
	      void );

 
UINT
 
GetDoubleClickTime(
		   void );

 
WINBOOL
 
SetDoubleClickTime(
		   UINT);

 
WINBOOL
 
IsWindow(
	 HWND hWnd);

 
WINBOOL
 
IsMenu(
       HMENU hMenu);

 
WINBOOL
 
IsChild(
	HWND hWndParent,
	HWND hWnd);

 
WINBOOL
 
DestroyWindow(
	      HWND hWnd);

 
WINBOOL
 
ShowWindow(
	   HWND hWnd,
	   int nCmdShow);

 
WINBOOL
 
ShowWindowAsync(
		HWND hWnd,
		int nCmdShow);

 
WINBOOL
 
FlashWindow(
	    HWND hWnd,
	    WINBOOL bInvert);

 
WINBOOL
 
ShowOwnedPopups(
		HWND hWnd,
		WINBOOL fShow);

 
WINBOOL
 
OpenIcon(
	 HWND hWnd);

 
WINBOOL
 
CloseWindow(
	    HWND hWnd);

 
WINBOOL
 
MoveWindow(
	   HWND hWnd,
	   int X,
	   int Y,
	   int nWidth,
	   int nHeight,
	   WINBOOL bRepaint);

 
WINBOOL
 
SetWindowPos(
	     HWND hWnd,
	     HWND hWndInsertAfter ,
	     int X,
	     int Y,
	     int cx,
	     int cy,
	     UINT uFlags);

 
WINBOOL
 
GetWindowPlacement(
		   HWND hWnd,
		   WINDOWPLACEMENT *lpwndpl);

 
WINBOOL
 
SetWindowPlacement(
		   HWND hWnd,
		   const  WINDOWPLACEMENT *lpwndpl);

 
HDWP
 
BeginDeferWindowPos(
		    int nNumWindows);

 
HDWP
 
DeferWindowPos(
	       HDWP hWinPosInfo,
	       HWND hWnd,
	       HWND hWndInsertAfter,
	       int x,
	       int y,
	       int cx,
	       int cy,
	       UINT uFlags);

 
WINBOOL
 
EndDeferWindowPos(
		  HDWP hWinPosInfo);

 
WINBOOL
 
IsWindowVisible(
		HWND hWnd);

 
WINBOOL
 
IsIconic(
	 HWND hWnd);

 
WINBOOL
 
AnyPopup(
	 void );

 
WINBOOL
 
BringWindowToTop(
		 HWND hWnd);

 
WINBOOL
 
IsZoomed(
	 HWND hWnd);

 
WINBOOL
 
EndDialog(
	  HWND hDlg,
	  int nResult);

 
HWND
 
GetDlgItem(
	   HWND hDlg,
	   int nIDDlgItem);

 
WINBOOL
 
SetDlgItemInt(
	      HWND hDlg,
	      int nIDDlgItem,
	      UINT uValue,
	      WINBOOL bSigned);

 
UINT
 
GetDlgItemInt(
	      HWND hDlg,
	      int nIDDlgItem,
	      WINBOOL *lpTranslated,
	      WINBOOL bSigned);

 
WINBOOL
 
CheckDlgButton(
	       HWND hDlg,
	       int nIDButton,
	       UINT uCheck);

 
WINBOOL
 
CheckRadioButton(
		 HWND hDlg,
		 int nIDFirstButton,
		 int nIDLastButton,
		 int nIDCheckButton);

 
UINT
 
IsDlgButtonChecked(
		   HWND hDlg,
		   int nIDButton);

 
HWND
 
GetNextDlgGroupItem(
		    HWND hDlg,
		    HWND hCtl,
		    WINBOOL bPrevious);

 
HWND
 
GetNextDlgTabItem(
		  HWND hDlg,
		  HWND hCtl,
		  WINBOOL bPrevious);

 
int
 
GetDlgCtrlID(
	     HWND hWnd);

 
long
 
GetDialogBaseUnits(void );

WINBOOL
 
OpenClipboard(
	      HWND hWndNewOwner);

 
WINBOOL
 
CloseClipboard(
	       void );

 
HWND
 
GetClipboardOwner(
		  void );

 
HWND
 
SetClipboardViewer(
		   HWND hWndNewViewer);

 
HWND
 
GetClipboardViewer(
		   void );

 
WINBOOL
 
ChangeClipboardChain(
		     HWND hWndRemove,
		     HWND hWndNewNext);

 
HANDLE
 
SetClipboardData(
		 UINT uFormat,
		 HANDLE hMem);

 
HANDLE
 
GetClipboardData(
		 UINT uFormat);

 
 
int
 
CountClipboardFormats(
		      void );

 
UINT
 
EnumClipboardFormats(
		     UINT format);

 
WINBOOL
 
EmptyClipboard(
	       void );

 
WINBOOL
 
IsClipboardFormatAvailable(
			   UINT format);

 
int
 
GetPriorityClipboardFormat(
			   UINT *paFormatPriorityList,
			   int cFormats);

 
HWND
 
GetOpenClipboardWindow(
		       void );

 
 
LPSTR
 
CharNextExA(
	    WORD CodePage,
	    LPCSTR lpCurrentChar,
	    DWORD dwFlags);

 
LPSTR
 
CharPrevExA(
	    WORD CodePage,
	    LPCSTR lpStart,
	    LPCSTR lpCurrentChar,
	    DWORD dwFlags);

 
HWND
 
SetFocus(
	 HWND hWnd);

 
HWND
 
GetActiveWindow(
		void );

 
HWND
 
GetFocus(
	 void );

 
UINT
 
GetKBCodePage(
	      void );

 
SHORT
 
GetKeyState(
	    int nVirtKey);

 
SHORT
 
GetAsyncKeyState(
		 int vKey);

 
WINBOOL
 
GetKeyboardState(
		 PBYTE lpKeyState);

 
WINBOOL
 
SetKeyboardState(
		 LPBYTE lpKeyState);

 
int
 
GetKeyboardType(
		int nTypeFlag);

 
int
 
ToAscii(
	UINT uVirtKey,
	UINT uScanCode,
	PBYTE lpKeyState,
	LPWORD lpChar,
	UINT uFlags);

 
int
 
ToAsciiEx(
	  UINT uVirtKey,
	  UINT uScanCode,
	  PBYTE lpKeyState,
	  LPWORD lpChar,
	  UINT uFlags,
	  HKL dwhkl);

 
int
 
ToUnicode(
	  UINT wVirtKey,
	  UINT wScanCode,
	  PBYTE lpKeyState,
	  LPWSTR pwszBuff,
	  int cchBuff,
	  UINT wFlags);

 
DWORD
 
OemKeyScan(
	   WORD wOemChar);

 
void 
 
keybd_event(
	    BYTE bVk,
	    BYTE bScan,
	    DWORD dwFlags,
	    DWORD dwExtraInfo);

 
void 
 
mouse_event(
	    DWORD dwFlags,
	    DWORD dx,
	    DWORD dy,
	    DWORD cButtons,
	    DWORD dwExtraInfo);

WINBOOL
 
GetInputState(
	      void );

 
DWORD
 
GetQueueStatus(
	       UINT flags);

 
HWND
 
GetCapture(
	   void );

 
HWND
 
SetCapture(
	   HWND hWnd);

 
WINBOOL
 
ReleaseCapture(
	       void );

 
DWORD
 
MsgWaitForMultipleObjects(
			  DWORD nCount,
			  LPHANDLE pHandles,
			  WINBOOL fWaitAll,
			  DWORD dwMilliseconds,
			  DWORD dwWakeMask);

 
UINT
 
SetTimer(
	 HWND hWnd ,
	 UINT nIDEvent,
	 UINT uElapse,
	 TIMERPROC lpTimerFunc);

 
WINBOOL
 
KillTimer(
	  HWND hWnd,
	  UINT uIDEvent);

 
WINBOOL
 
IsWindowUnicode(
		HWND hWnd);

 
WINBOOL
 
EnableWindow(
	     HWND hWnd,
	     WINBOOL bEnable);

 
WINBOOL
 
IsWindowEnabled(
		HWND hWnd);

 
WINBOOL
 
DestroyAcceleratorTable(
			HACCEL hAccel);

int
 
GetSystemMetrics(
		 int nIndex);

HMENU
 
GetMenu(
	HWND hWnd);

 
WINBOOL
 
SetMenu(
	HWND hWnd,
	HMENU hMenu);

 
WINBOOL
 
HiliteMenuItem(
	       HWND hWnd,
	       HMENU hMenu,
	       UINT uIDHiliteItem,
	       UINT uHilite);

 
UINT
 
GetMenuState(
	     HMENU hMenu,
	     UINT uId,
	     UINT uFlags);

 
WINBOOL
 
DrawMenuBar(
	    HWND hWnd);

 
HMENU
 
GetSystemMenu(
	      HWND hWnd,
	      WINBOOL bRevert);

 
HMENU
 
CreateMenu(
	   void );

 
HMENU
 
CreatePopupMenu(
		void );

 
WINBOOL
 
DestroyMenu(
	    HMENU hMenu);

 
DWORD
 
CheckMenuItem(
	      HMENU hMenu,
	      UINT uIDCheckItem,
	      UINT uCheck);

 
WINBOOL
 
EnableMenuItem(
	       HMENU hMenu,
	       UINT uIDEnableItem,
	       UINT uEnable);

 
HMENU
 
GetSubMenu(
	   HMENU hMenu,
	   int nPos);

 
UINT
 
GetMenuItemID(
	      HMENU hMenu,
	      int nPos);

 
int
 
GetMenuItemCount(
		 HMENU hMenu);

WINBOOL
  RemoveMenu(
		   HMENU hMenu,
		   UINT uPosition,
		   UINT uFlags);

 
WINBOOL
 
DeleteMenu(
	   HMENU hMenu,
	   UINT uPosition,
	   UINT uFlags);

 
WINBOOL
 
SetMenuItemBitmaps(
		   HMENU hMenu,
		   UINT uPosition,
		   UINT uFlags,
		   HBITMAP hBitmapUnchecked,
		   HBITMAP hBitmapChecked);

 
LONG
 
GetMenuCheckMarkDimensions(
			   void );

 
WINBOOL
 
TrackPopupMenu(
	       HMENU hMenu,
	       UINT uFlags,
	       int x,
	       int y,
	       int nReserved,
	       HWND hWnd,
	       const  RECT *prcRect);

UINT
 
GetMenuDefaultItem(
		   HMENU hMenu, 
		   UINT fByPos, 
		   UINT gmdiFlags);

WINBOOL
 
SetMenuDefaultItem(
		   HMENU hMenu, 
		   UINT uItem, 
		   UINT fByPos);

WINBOOL
 
GetMenuItemRect(HWND hWnd, 
		HMENU hMenu, 
		UINT uItem, 
		LPRECT lprcItem);

int
 
MenuItemFromPoint(HWND hWnd, 
		  HMENU hMenu, 
		  POINT ptScreen);

 
DWORD
 
DragObject(HWND, HWND, UINT, DWORD, HCURSOR);

 
WINBOOL
 
DragDetect(HWND hwnd, 
	   POINT pt);

 
WINBOOL
 
DrawIcon(
	 HDC hDC,
	 int X,
	 int Y,
	 HICON hIcon);

WINBOOL
 
UpdateWindow(
	     HWND hWnd);

 
HWND
 
SetActiveWindow(
		HWND hWnd);

 
HWND
 
GetForegroundWindow(
		    void );

WINBOOL
 
PaintDesktop(HDC hdc);

 
WINBOOL
 
SetForegroundWindow(
		    HWND hWnd);

 
HWND
 
WindowFromDC(
	     HDC hDC);

 
HDC
 
GetDC(
      HWND hWnd);

 
HDC
 
GetDCEx(
	HWND hWnd ,
	HRGN hrgnClip,
	DWORD flags);

 
HDC
 
GetWindowDC(
	    HWND hWnd);

 
int
 
ReleaseDC(
	  HWND hWnd,
	  HDC hDC);

 
HDC
 
BeginPaint(
	   HWND hWnd,
	   LPPAINTSTRUCT lpPaint);

 
WINBOOL
 
EndPaint(
	 HWND hWnd,
	 const  PAINTSTRUCT *lpPaint);

 
WINBOOL
 
GetUpdateRect(
	      HWND hWnd,
	      LPRECT lpRect,
	      WINBOOL bErase);

 
int
 
GetUpdateRgn(
	     HWND hWnd,
	     HRGN hRgn,
	     WINBOOL bErase);

 
int
 
SetWindowRgn(
	     HWND hWnd,
	     HRGN hRgn,
	     WINBOOL bRedraw);

 
int
 
GetWindowRgn(
	     HWND hWnd,
	     HRGN hRgn);

 
int
 
ExcludeUpdateRgn(
		 HDC hDC,
		 HWND hWnd);

 
WINBOOL
 
InvalidateRect(
	       HWND hWnd ,
	       const  RECT *lpRect,
	       WINBOOL bErase);

 
WINBOOL
 
ValidateRect(
	     HWND hWnd ,
	     const  RECT *lpRect);

 
WINBOOL
 
InvalidateRgn(
	      HWND hWnd,
	      HRGN hRgn,
	      WINBOOL bErase);

 
WINBOOL
 
ValidateRgn(
	    HWND hWnd,
	    HRGN hRgn);

 
WINBOOL
 
RedrawWindow(
	     HWND hWnd,
	     const  RECT *lprcUpdate,
	     HRGN hrgnUpdate,
	     UINT flags);

 
WINBOOL
 
LockWindowUpdate(
		 HWND hWndLock);

 
WINBOOL
 
ScrollWindow(
	     HWND hWnd,
	     int XAmount,
	     int YAmount,
	     const  RECT *lpRect,
	     const  RECT *lpClipRect);

 
WINBOOL
 
ScrollDC(
	 HDC hDC,
	 int dx,
	 int dy,
	 const  RECT *lprcScroll,
	 const  RECT *lprcClip ,
	 HRGN hrgnUpdate,
	 LPRECT lprcUpdate);

 
int
 
ScrollWindowEx(
	       HWND hWnd,
	       int dx,
	       int dy,
	       const  RECT *prcScroll,
	       const  RECT *prcClip ,
	       HRGN hrgnUpdate,
	       LPRECT prcUpdate,
	       UINT flags);

 
int
 
SetScrollPos(
	     HWND hWnd,
	     int nBar,
	     int nPos,
	     WINBOOL bRedraw);

 
int
 
GetScrollPos(
	     HWND hWnd,
	     int nBar);

 
WINBOOL
 
SetScrollRange(
	       HWND hWnd,
	       int nBar,
	       int nMinPos,
	       int nMaxPos,
	       WINBOOL bRedraw);

 
WINBOOL
 
GetScrollRange(
	       HWND hWnd,
	       int nBar,
	       LPINT lpMinPos,
	       LPINT lpMaxPos);

 
WINBOOL
 
ShowScrollBar(
	      HWND hWnd,
	      int wBar,
	      WINBOOL bShow);

 
WINBOOL
 
EnableScrollBar(
		HWND hWnd,
		UINT wSBflags,
		UINT wArrows);

 
WINBOOL
 
GetClientRect(
	      HWND hWnd,
	      LPRECT lpRect);

 
WINBOOL
 
GetWindowRect(
	      HWND hWnd,
	      LPRECT lpRect);

 
WINBOOL
 
AdjustWindowRect(
		 LPRECT lpRect,
		 DWORD dwStyle,
		 WINBOOL bMenu);

 
WINBOOL
 
AdjustWindowRectEx(
		   LPRECT lpRect,
		   DWORD dwStyle,
		   WINBOOL bMenu,
		   DWORD dwExStyle);

WINBOOL
 
SetWindowContextHelpId(HWND, DWORD);

DWORD
 
GetWindowContextHelpId(HWND);

WINBOOL
 
SetMenuContextHelpId(HMENU, DWORD);

DWORD
 
GetMenuContextHelpId(HMENU);

 
WINBOOL
 
MessageBeep(
	    UINT uType);

 
int
 
ShowCursor(
	   WINBOOL bShow);

 
WINBOOL
 
SetCursorPos(
	     int X,
	     int Y);

 
HCURSOR
 
SetCursor(
	  HCURSOR hCursor);

 
WINBOOL
 
GetCursorPos(
	     LPPOINT lpPoint);

 
WINBOOL
 
ClipCursor(
	   const  RECT *lpRect);

 
WINBOOL
 
GetClipCursor(
	      LPRECT lpRect);

 
HCURSOR
 
GetCursor(
	  void );

 
WINBOOL
 
CreateCaret(
	    HWND hWnd,
	    HBITMAP hBitmap ,
	    int nWidth,
	    int nHeight);

 
UINT
 
GetCaretBlinkTime(
		  void );

 
WINBOOL
 
SetCaretBlinkTime(
		  UINT uMSeconds);

 
WINBOOL
 
DestroyCaret(
	     void );

 
WINBOOL
 
HideCaret(
	  HWND hWnd);

 
WINBOOL
 
ShowCaret(
	  HWND hWnd);

 
WINBOOL
 
SetCaretPos(
	    int X,
	    int Y);

 
WINBOOL
 
GetCaretPos(
	    LPPOINT lpPoint);

 
WINBOOL
 
ClientToScreen(
	       HWND hWnd,
	       LPPOINT lpPoint);

 
WINBOOL
 
ScreenToClient(
	       HWND hWnd,
	       LPPOINT lpPoint);

 
int
 
MapWindowPoints(
		HWND hWndFrom,
		HWND hWndTo,
		LPPOINT lpPoints,
		UINT cPoints);

 
HWND
 
WindowFromPoint(
		POINT Point);

 
HWND
 
ChildWindowFromPoint(
		     HWND hWndParent,
		     POINT Point);

 
DWORD
 
GetSysColor(
	    int nIndex);

 
HBRUSH
 
GetSysColorBrush(
		 int nIndex);

 
WINBOOL
 
SetSysColors(
	     int cElements,
	     const  INT * lpaElements,
	     const  COLORREF * lpaRgbValues);

 
WINBOOL
 
DrawFocusRect(
	      HDC hDC,
	      const  RECT * lprc);

 
int
 
FillRect(
	 HDC hDC,
	 const  RECT *lprc,
	 HBRUSH hbr);

 
int
 
FrameRect(
	  HDC hDC,
	  const  RECT *lprc,
	  HBRUSH hbr);

 
WINBOOL
 
InvertRect(
	   HDC hDC,
	   const  RECT *lprc);

 
WINBOOL
 
SetRect(
	LPRECT lprc,
	int xLeft,
	int yTop,
	int xRight,
	int yBottom);

 
WINBOOL
 
SetRectEmpty(
	     LPRECT lprc);

 
WINBOOL
 
CopyRect(
	 LPRECT lprcDst,
	 const  RECT *lprcSrc);

 
WINBOOL
 
InflateRect(
	    LPRECT lprc,
	    int dx,
	    int dy);

 
WINBOOL
 
IntersectRect(
	      LPRECT lprcDst,
	      const  RECT *lprcSrc1,
	      const  RECT *lprcSrc2);

 
WINBOOL
 
UnionRect(
	  LPRECT lprcDst,
	  const  RECT *lprcSrc1,
	  const  RECT *lprcSrc2);

 
WINBOOL
 
SubtractRect(
	     LPRECT lprcDst,
	     const  RECT *lprcSrc1,
	     const  RECT *lprcSrc2);

 
WINBOOL
 
OffsetRect(
	   LPRECT lprc,
	   int dx,
	   int dy);

 
WINBOOL
 
IsRectEmpty(
	    const  RECT *lprc);

 
WINBOOL
 
EqualRect(
	  const  RECT *lprc1,
	  const  RECT *lprc2);

 
WINBOOL
 
PtInRect(
	 const  RECT *lprc,
	 POINT pt);

 
WORD
 
GetWindowWord(
	      HWND hWnd,
	      int nIndex);

 
WORD
 
SetWindowWord(
	      HWND hWnd,
	      int nIndex,
	      WORD wNewWord);

 
WORD
 
GetClassWord(
	     HWND hWnd,
	     int nIndex);

 
WORD
 
SetClassWord(
	     HWND hWnd,
	     int nIndex,
	     WORD wNewWord);

HWND
 
GetDesktopWindow(
		 void );

 
HWND
 
GetParent(
	  HWND hWnd);

 
HWND
 
SetParent(
	  HWND hWndChild,
	  HWND hWndNewParent);

 
WINBOOL
 
EnumChildWindows(
		 HWND hWndParent,
		 ENUMWINDOWSPROC lpEnumFunc,
		 LPARAM lParam);

 
WINBOOL
 
EnumWindows(
	    ENUMWINDOWSPROC lpEnumFunc,
	    LPARAM lParam);

 
WINBOOL
 
EnumThreadWindows(
		  DWORD dwThreadId,
		  ENUMWINDOWSPROC lpfn,
		  LPARAM lParam);

HWND
 
GetTopWindow(
	     HWND hWnd);

 
DWORD
 
GetWindowThreadProcessId(
			 HWND hWnd,
			 LPDWORD lpdwProcessId);

 
HWND
 
GetLastActivePopup(
		   HWND hWnd);

 
HWND
 
GetWindow(
	  HWND hWnd,
	  UINT uCmd);

WINBOOL
 
UnhookWindowsHook(
		  int nCode,
		  HOOKPROC pfnFilterProc);

WINBOOL
 
UnhookWindowsHookEx(
		    HHOOK hhk);

 
LRESULT
 
CallNextHookEx(
	       HHOOK hhk,
	       int nCode,
	       WPARAM wParam,
	       LPARAM lParam);

 
WINBOOL
 
CheckMenuRadioItem(HMENU, UINT, UINT, UINT, UINT);

HCURSOR
 
CreateCursor(
	     HINSTANCE hInst,
	     int xHotSpot,
	     int yHotSpot,
	     int nWidth,
	     int nHeight,
	     const  void  *pvANDPlane,
	     const  void  *pvXORPlane);

 
WINBOOL
 
DestroyCursor(
	      HCURSOR hCursor);

 
WINBOOL
 
SetSystemCursor(
		HCURSOR hcur,
		DWORD   anID);

 
HICON
 
CreateIcon(
	   HINSTANCE hInstance,
	   int nWidth,
	   int nHeight,
	   BYTE cPlanes,
	   BYTE cBitsPixel,
	   const  BYTE *lpbANDbits,
	   const  BYTE *lpbXORbits);

 
WINBOOL
 
DestroyIcon(
	    HICON hIcon);

 
int
 
LookupIconIdFromDirectory(
			  PBYTE presbits,
			  WINBOOL fIcon);

 
int
 
LookupIconIdFromDirectoryEx(
			    PBYTE presbits,
			    WINBOOL  fIcon,
			    int   cxDesired,
			    int   cyDesired,
			    UINT  Flags);

 
HICON
 
CreateIconFromResource(
		       PBYTE presbits,
		       DWORD dwResSize,
		       WINBOOL fIcon,
		       DWORD dwVer);

 
HICON
 
CreateIconFromResourceEx(
			 PBYTE presbits,
			 DWORD dwResSize,
			 WINBOOL  fIcon,
			 DWORD dwVer,
			 int   cxDesired,
			 int   cyDesired,
			 UINT  Flags);

 
HICON
 
CopyImage(
	  HANDLE,
	  UINT,
	  int,
	  int,
	  UINT);

 
HICON
 
CreateIconIndirect(
		   PICONINFO piconinfo);

 
HICON
 
CopyIcon(
	 HICON hIcon);

 
WINBOOL
 
GetIconInfo(
	    HICON hIcon,
	    PICONINFO piconinfo);

 
WINBOOL
 
MapDialogRect(
	      HWND hDlg,
	      LPRECT lpRect);

int
 
SetScrollInfo(HWND, int, LPCSCROLLINFO, WINBOOL);

WINBOOL
 
GetScrollInfo(HWND, int, LPSCROLLINFO);

WINBOOL
 
TranslateMDISysAccel(
		     HWND hWndClient,
		     LPMSG lpMsg);

 
UINT
 
ArrangeIconicWindows(
		     HWND hWnd);

WORD
 
TileWindows(HWND hwndParent, UINT wHow, const  RECT * lpRect, UINT cKids, const HWND *lpKids);

WORD
 
CascadeWindows(HWND hwndParent, UINT wHow, const  RECT * lpRect, UINT cKids,  const HWND *lpKids);

 
void 
 
SetLastErrorEx(
	       DWORD dwErrCode,
	       DWORD dwType
	       );

 
void 
 
SetDebugErrorLevel(
		   DWORD dwLevel
		   );

WINBOOL
 
DrawEdge(HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags);

WINBOOL
 
DrawFrameControl(HDC, LPRECT, UINT, UINT);

WINBOOL
 
DrawCaption(HWND, HDC, const  RECT *, UINT);

WINBOOL
 
DrawAnimatedRects(HWND hwnd, int idAni, const  RECT * lprcFrom, const  RECT * lprcTo);

WINBOOL
 
TrackPopupMenuEx(HMENU, UINT, int, int, HWND, LPTPMPARAMS);

HWND
 
ChildWindowFromPointEx(HWND, POINT, UINT);

WINBOOL
 
DrawIconEx(HDC hdc, int xLeft, int yTop,
	   HICON hIcon, int cxWidth, int cyWidth,
	   UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);

WINBOOL
 
AnimatePalette(HPALETTE, UINT, UINT, const  PALETTEENTRY *);

WINBOOL
 
Arc(HDC, int, int, int, int, int, int, int, int);

WINBOOL
 
BitBlt(HDC, int, int, int, int, HDC, int, int, DWORD);

WINBOOL
 
CancelDC(HDC);

WINBOOL
 
Chord(HDC, int, int, int, int, int, int, int, int);

HMETAFILE
 
CloseMetaFile(HDC);

int
 
CombineRgn(HRGN, HRGN, HRGN, int);

HBITMAP
 
CreateBitmap(int, int, UINT, UINT, const  void  *);

HBITMAP
 
CreateBitmapIndirect(const  BITMAP *);

HBRUSH
 
CreateBrushIndirect(const  LOGBRUSH *);

HBITMAP
 
CreateCompatibleBitmap(HDC, int, int);

HBITMAP
 
CreateDiscardableBitmap(HDC, int, int);

HDC
 
CreateCompatibleDC(HDC);

HBITMAP
 
CreateDIBitmap(HDC, const  BITMAPINFOHEADER *, DWORD, const  void  *, const  BITMAPINFO *, UINT);

HBRUSH
 
CreateDIBPatternBrush(HGLOBAL, UINT);

HBRUSH
 
CreateDIBPatternBrushPt(const  void  *, UINT);

HRGN
 
CreateEllipticRgn(int, int, int, int);

HRGN
 
CreateEllipticRgnIndirect(const  RECT *);

HBRUSH
 
CreateHatchBrush(int, COLORREF);

HPALETTE
 
CreatePalette(const  LOGPALETTE *);

HPEN
 
CreatePen(int, int, COLORREF);

HPEN
 
CreatePenIndirect(const  LOGPEN *);

HRGN
 
CreatePolyPolygonRgn(const  POINT *, const  INT *, int, int);

HBRUSH
 
CreatePatternBrush(HBITMAP);

HRGN
 
CreateRectRgn(int, int, int, int);

HRGN
 
CreateRectRgnIndirect(const  RECT *);

HRGN
 
CreateRoundRectRgn(int, int, int, int, int, int);

HBRUSH
 
CreateSolidBrush(COLORREF);

WINBOOL
 
DeleteDC(HDC);

WINBOOL
 
DeleteMetaFile(HMETAFILE);

WINBOOL
 
DeleteObject(HGDIOBJ);

int
 
DrawEscape(HDC, int, int, LPCSTR);

WINBOOL
 
Ellipse(HDC, int, int, int, int);

int
 
EnumObjects(HDC, int, ENUMOBJECTSPROC, LPARAM);

WINBOOL
 
EqualRgn(HRGN, HRGN);

int
 
Escape(HDC, int, int, LPCSTR, LPVOID);

int
 
ExtEscape(HDC, int, int, LPCSTR, int, LPSTR);

int
 
ExcludeClipRect(HDC, int, int, int, int);

HRGN
 
ExtCreateRegion(const  XFORM *, DWORD, const  RGNDATA *);

WINBOOL
 
ExtFloodFill(HDC, int, int, COLORREF, UINT);

WINBOOL
 
FillRgn(HDC, HRGN, HBRUSH);

WINBOOL
 
FloodFill(HDC, int, int, COLORREF);

WINBOOL
 
FrameRgn(HDC, HRGN, HBRUSH, int, int);

int
 
GetROP2(HDC);

WINBOOL
 
GetAspectRatioFilterEx(HDC, LPSIZE);

COLORREF
 
GetBkColor(HDC);

int
 
GetBkMode(HDC);

LONG
 
GetBitmapBits(HBITMAP, LONG, LPVOID);

WINBOOL
 
GetBitmapDimensionEx(HBITMAP, LPSIZE);

UINT
 
GetBoundsRect(HDC, LPRECT, UINT);

WINBOOL
 
GetBrushOrgEx(HDC, LPPOINT);

int
 
GetClipBox(HDC, LPRECT);

int
 
GetClipRgn(HDC, HRGN);

int
 
GetMetaRgn(HDC, HRGN);

HGDIOBJ
 
GetCurrentObject(HDC, UINT);

WINBOOL
 
GetCurrentPositionEx(HDC, LPPOINT);

int
 
GetDeviceCaps(HDC, int);

int
 
GetDIBits(HDC, HBITMAP, UINT, UINT, LPVOID, LPBITMAPINFO, UINT);

DWORD
 
GetFontData(HDC, DWORD, DWORD, LPVOID, DWORD);

int
 
GetGraphicsMode(HDC);

int
 
GetMapMode(HDC);

UINT
 
GetMetaFileBitsEx(HMETAFILE, UINT, LPVOID);

COLORREF
 
GetNearestColor(HDC, COLORREF);

UINT
 
GetNearestPaletteIndex(HPALETTE, COLORREF);

DWORD
 
GetObjectType(HGDIOBJ h);

UINT
 
GetPaletteEntries(HPALETTE, UINT, UINT, LPPALETTEENTRY);

COLORREF
 
GetPixel(HDC, int, int);

int
 
GetPixelFormat(HDC);

int
 
GetPolyFillMode(HDC);

WINBOOL
 
GetRasterizerCaps(LPRASTERIZER_STATUS, UINT);

DWORD
 
GetRegionData(HRGN, DWORD, LPRGNDATA);

int
 
GetRgnBox(HRGN, LPRECT);

HGDIOBJ
 
GetStockObject(int);

int
 
GetStretchBltMode(HDC);

UINT
 
GetSystemPaletteEntries(HDC, UINT, UINT, LPPALETTEENTRY);

UINT
 
GetSystemPaletteUse(HDC);

int
 
GetTextCharacterExtra(HDC);

UINT
 
GetTextAlign(HDC);

COLORREF
 
GetTextColor(HDC);

int
 
GetTextCharset(HDC hdc);

int
 
GetTextCharsetInfo(HDC hdc, LPFONTSIGNATURE lpSig, DWORD dwFlags);

WINBOOL
 
TranslateCharsetInfo( DWORD *lpSrc, LPCHARSETINFO lpCs, DWORD dwFlags);

DWORD
 
GetFontLanguageInfo( HDC );

WINBOOL
 
GetViewportExtEx(HDC, LPSIZE);

WINBOOL
 
GetViewportOrgEx(HDC, LPPOINT);

WINBOOL
 
GetWindowExtEx(HDC, LPSIZE);

WINBOOL
 
GetWindowOrgEx(HDC, LPPOINT);

int
 
IntersectClipRect(HDC, int, int, int, int);

WINBOOL
 
InvertRgn(HDC, HRGN);

WINBOOL
 
LineDDA(int, int, int, int, LINEDDAPROC, LPARAM);

WINBOOL
 
LineTo(HDC, int, int);

WINBOOL
 
MaskBlt(HDC, int, int, int, int,
	HDC, int, int, HBITMAP, int, int, DWORD);

WINBOOL
 
PlgBlt(HDC, const  POINT *, HDC, int, int, int,
       int, HBITMAP, int, int);

int
 
OffsetClipRgn(HDC, int, int);

int
 
OffsetRgn(HRGN, int, int);

WINBOOL
  
PatBlt(HDC, int, int, int, int, DWORD);

WINBOOL
 
Pie(HDC, int, int, int, int, int, int, int, int);

WINBOOL
 
PlayMetaFile(HDC, HMETAFILE);

WINBOOL
 
PaintRgn(HDC, HRGN);

WINBOOL
 
PolyPolygon(HDC, const  POINT *, const  INT *, int);

WINBOOL
 
PtInRegion(HRGN, int, int);

WINBOOL
 
PtVisible(HDC, int, int);

WINBOOL
 
RectInRegion(HRGN, const  RECT *);

WINBOOL
 
RectVisible(HDC, const  RECT *);

WINBOOL
 
Rectangle(HDC, int, int, int, int);

WINBOOL
 
RestoreDC(HDC, int);

UINT
 
RealizePalette(HDC);

WINBOOL
 
RoundRect(HDC, int, int, int, int, int, int);

WINBOOL
 
ResizePalette(HPALETTE, UINT);

int
 
SaveDC(HDC);

int
 
SelectClipRgn(HDC, HRGN);

int
 
ExtSelectClipRgn(HDC, HRGN, int);

int
 
SetMetaRgn(HDC);

HGDIOBJ
 
SelectObject(HDC, HGDIOBJ);

HPALETTE
 
SelectPalette(HDC, HPALETTE, WINBOOL);

COLORREF
 
SetBkColor(HDC, COLORREF);

int
 
SetBkMode(HDC, int);

LONG
 
SetBitmapBits(HBITMAP, DWORD, const  void  *);

UINT
 
SetBoundsRect(HDC, const  RECT *, UINT);

int
 
SetDIBits(HDC, HBITMAP, UINT, UINT, const  void  *, const  BITMAPINFO *, UINT);

int
 
SetDIBitsToDevice(HDC, int, int, DWORD, DWORD, int,
		  int, UINT, UINT, const  void  *, const  BITMAPINFO *, UINT);

DWORD
 
SetMapperFlags(HDC, DWORD);

int
 
SetGraphicsMode(HDC hdc, int iMode);

int
 
SetMapMode(HDC, int);

HMETAFILE
 
SetMetaFileBitsEx(UINT, const  BYTE *);

UINT
 
SetPaletteEntries(HPALETTE, UINT, UINT, const  PALETTEENTRY *);

COLORREF
 
SetPixel(HDC, int, int, COLORREF);

WINBOOL
 
SetPixelV(HDC, int, int, COLORREF);

int
 
SetPolyFillMode(HDC, int);

WINBOOL
 
StretchBlt(HDC, int, int, int, int, HDC, int, int, int, int, DWORD);

WINBOOL
 
SetRectRgn(HRGN, int, int, int, int);
int
 
StretchDIBits(HDC, int, int, int, int, int, int, int, int, const 
	      void  *, const  BITMAPINFO *, UINT, DWORD);

int
 
SetROP2(HDC, int);

int
 
SetStretchBltMode(HDC, int);

UINT
 
SetSystemPaletteUse(HDC, UINT);

int
 
SetTextCharacterExtra(HDC, int);

COLORREF
 
SetTextColor(HDC, COLORREF);

UINT
 
SetTextAlign(HDC, UINT);

WINBOOL
 
SetTextJustification(HDC, int, int);

WINBOOL
 
UpdateColors(HDC);

WINBOOL
 
PlayMetaFileRecord(HDC, LPHANDLETABLE, LPMETARECORD, UINT);

WINBOOL
 
EnumMetaFile(HDC, HMETAFILE, ENUMMETAFILEPROC, LPARAM);

HENHMETAFILE
 
CloseEnhMetaFile(HDC);

WINBOOL
 
DeleteEnhMetaFile(HENHMETAFILE);

WINBOOL
 
EnumEnhMetaFile(HDC, HENHMETAFILE, ENHMETAFILEPROC,
		LPVOID, const  RECT *);

UINT
 
GetEnhMetaFileHeader(HENHMETAFILE, UINT, LPENHMETAHEADER );

UINT
 
GetEnhMetaFilePaletteEntries(HENHMETAFILE, UINT, LPPALETTEENTRY );

UINT
 
GetWinMetaFileBits(HENHMETAFILE, UINT, LPBYTE, INT, HDC);

WINBOOL
 
PlayEnhMetaFile(HDC, HENHMETAFILE, const  RECT *);

WINBOOL
 
PlayEnhMetaFileRecord(HDC, LPHANDLETABLE, const  ENHMETARECORD *, UINT);

HENHMETAFILE
 
SetEnhMetaFileBits(UINT, const  BYTE *);

HENHMETAFILE
 
SetWinMetaFileBits(UINT, const  BYTE *, HDC, const  METAFILEPICT *);

WINBOOL
 
GdiComment(HDC, UINT, const  BYTE *);

WINBOOL
 
AngleArc(HDC, int, int, DWORD, FLOAT, FLOAT);

WINBOOL
 
PolyPolyline(HDC, const  POINT *, const  DWORD *, DWORD);

WINBOOL
 
GetWorldTransform(HDC, LPXFORM);

WINBOOL
 
SetWorldTransform(HDC, const  XFORM *);

WINBOOL
 
ModifyWorldTransform(HDC, const  XFORM *, DWORD);

WINBOOL
 
CombineTransform(LPXFORM, const  XFORM *, const  XFORM *);

HBITMAP
 
CreateDIBSection(HDC, const  BITMAPINFO *, UINT, void  **, HANDLE, DWORD);

UINT
 
GetDIBColorTable(HDC, UINT, UINT, RGBQUAD *);

UINT
 
SetDIBColorTable(HDC, UINT, UINT, const  RGBQUAD *);

WINBOOL
 
SetColorAdjustment(HDC, const  COLORADJUSTMENT *);

WINBOOL
 
GetColorAdjustment(HDC, LPCOLORADJUSTMENT);

HPALETTE
  
CreateHalftonePalette(HDC);

int
 
EndDoc(HDC);

int
 
StartPage(HDC);

int
 
EndPage(HDC);

int
 
AbortDoc(HDC);

int
 
SetAbortProc(HDC, ABORTPROC);

WINBOOL
 
AbortPath(HDC);

WINBOOL
 
ArcTo(HDC, int, int, int, int, int, int,int, int);

WINBOOL
 
BeginPath(HDC);

WINBOOL
 
CloseFigure(HDC);

WINBOOL
 
EndPath(HDC);

WINBOOL
 
FillPath(HDC);

WINBOOL
 
FlattenPath(HDC);

int
 
GetPath(HDC, LPPOINT, LPBYTE, int);

HRGN
 
PathToRegion(HDC);

WINBOOL
 
PolyDraw(HDC, const  POINT *, const  BYTE *, int);

WINBOOL
 
SelectClipPath(HDC, int);

int
 
SetArcDirection(HDC, int);

WINBOOL
 
SetMiterLimit(HDC, FLOAT, PFLOAT);

WINBOOL
 
StrokeAndFillPath(HDC);

WINBOOL
 
StrokePath(HDC);

WINBOOL
 
WidenPath(HDC);

HPEN
 
ExtCreatePen(DWORD, DWORD, const  LOGBRUSH *, DWORD, const  DWORD *);

WINBOOL
 
GetMiterLimit(HDC, PFLOAT);

int
 
GetArcDirection(HDC);

WINBOOL
 
MoveToEx(HDC, int, int, LPPOINT);

HRGN
 
CreatePolygonRgn(const  POINT *, int, int);

WINBOOL
 
DPtoLP(HDC, LPPOINT, int);

WINBOOL
 
LPtoDP(HDC, LPPOINT, int);
 
WINBOOL
 
Polygon(HDC, const  POINT *, int);

WINBOOL
 
Polyline(HDC, const  POINT *, int);

WINBOOL
 
PolyBezier(HDC, const  POINT *, DWORD);

WINBOOL
 
PolyBezierTo(HDC, const  POINT *, DWORD);

WINBOOL
 
PolylineTo(HDC, const  POINT *, DWORD);

WINBOOL
 
SetViewportExtEx(HDC, int, int, LPSIZE);

WINBOOL
 
SetViewportOrgEx(HDC, int, int, LPPOINT);

WINBOOL
 
SetWindowExtEx(HDC, int, int, LPSIZE);

WINBOOL
 
SetWindowOrgEx(HDC, int, int, LPPOINT);

WINBOOL
 
OffsetViewportOrgEx(HDC, int, int, LPPOINT);

WINBOOL
 
OffsetWindowOrgEx(HDC, int, int, LPPOINT);

WINBOOL
 
ScaleViewportExtEx(HDC, int, int, int, int, LPSIZE);

WINBOOL
 
ScaleWindowExtEx(HDC, int, int, int, int, LPSIZE);

WINBOOL
 
SetBitmapDimensionEx(HBITMAP, int, int, LPSIZE);

WINBOOL
 
SetBrushOrgEx(HDC, int, int, LPPOINT);

WINBOOL
 
GetDCOrgEx(HDC,LPPOINT);

WINBOOL
 
FixBrushOrgEx(HDC,int,int,LPPOINT);

WINBOOL
 
UnrealizeObject(HGDIOBJ);

WINBOOL
 
GdiFlush();

DWORD
 
GdiSetBatchLimit(DWORD);

DWORD
 
GdiGetBatchLimit();

int
 
SetICMMode(HDC, int);

WINBOOL
 
CheckColorsInGamut(HDC,LPVOID,LPVOID,DWORD);

HANDLE
 
GetColorSpace(HDC);

WINBOOL
 
SetColorSpace(HDC,HCOLORSPACE);

WINBOOL
 
DeleteColorSpace(HCOLORSPACE);

WINBOOL
 
GetDeviceGammaRamp(HDC,LPVOID);

WINBOOL
 
SetDeviceGammaRamp(HDC,LPVOID);

WINBOOL
 
ColorMatchToTarget(HDC,HDC,DWORD);

HPROPSHEETPAGE
 
CreatePropertySheetPageA(LPCPROPSHEETPAGE lppsp);

WINBOOL
 
DestroyPropertySheetPage(HPROPSHEETPAGE hPSPage);

void
 
InitCommonControls();



HIMAGELIST
 
ImageList_Create(int cx, int cy, UINT flags, 
		 int cInitial, int cGrow);

WINBOOL
 
ImageList_Destroy(HIMAGELIST himl);

int
 
ImageList_GetImageCount(HIMAGELIST himl);

int
 
ImageList_Add(HIMAGELIST himl, HBITMAP hbmImage, 
	      HBITMAP hbmMask);

int
 
ImageList_ReplaceIcon(HIMAGELIST himl, int i, HICON hicon);

COLORREF
 
ImageList_SetBkColor(HIMAGELIST himl, COLORREF clrBk);

COLORREF
 
ImageList_GetBkColor(HIMAGELIST himl);

WINBOOL
 
ImageList_SetOverlayImage(HIMAGELIST himl, int iImage, 
			  int iOverlay);

WINBOOL
 
ImageList_Draw(HIMAGELIST himl, int i, HDC hdcDst, int x, int y, UINT fStyle);

WINBOOL
 
ImageList_Replace(HIMAGELIST himl, int i, HBITMAP hbmImage, HBITMAP hbmMask);

int
 
ImageList_AddMasked(HIMAGELIST himl, HBITMAP hbmImage, COLORREF crMask);

WINBOOL
 
ImageList_DrawEx(HIMAGELIST himl, int i, HDC hdcDst, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);

WINBOOL
 
ImageList_Remove(HIMAGELIST himl, int i);

HICON
 
ImageList_GetIcon(HIMAGELIST himl, int i, UINT flags);

WINBOOL
 
ImageList_BeginDrag(HIMAGELIST himlTrack, int iTrack, int dxHotspot, int dyHotspot);

void
 
ImageList_EndDrag();

WINBOOL
 
ImageList_DragEnter(HWND hwndLock, int x, int y);

WINBOOL
 
ImageList_DragLeave(HWND hwndLock);

WINBOOL
 
ImageList_DragMove(int x, int y);

WINBOOL
 
ImageList_SetDragCursorImage(HIMAGELIST himlDrag, int iDrag, int dxHotspot, int dyHotspot);

WINBOOL
 
ImageList_DragShowNolock(WINBOOL fShow);

HIMAGELIST
 
ImageList_GetDragImage(POINT * ppt,POINT * pptHotspot);

WINBOOL
 
ImageList_GetIconSize(HIMAGELIST himl, int *cx, int *cy);

WINBOOL
 
ImageList_SetIconSize(HIMAGELIST himl, int cx, int cy);

WINBOOL
 
ImageList_GetImageInfo(HIMAGELIST himl, int i, IMAGEINFO * pImageInfo);

HIMAGELIST
 
ImageList_Merge(HIMAGELIST himl1, int i1, HIMAGELIST himl2, int i2, int dx, int dy);

HWND
 
CreateToolbarEx(HWND hwnd, DWORD ws, UINT wID, int nBitmaps,
		HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons,
		int iNumButtons, int dxButton, int dyButton,
		int dxBitmap, int dyBitmap, UINT uStructSize);

HBITMAP
 
CreateMappedBitmap(HINSTANCE hInstance, int idBitmap,
		   UINT wFlags, LPCOLORMAP lpColorMap,
		   int iNumMaps);


void
 
MenuHelp(UINT uMsg, WPARAM wParam, LPARAM lParam, HMENU hMainMenu, HINSTANCE hInst, HWND hwndStatus, UINT *lpwIDs);

WINBOOL
 
ShowHideMenuCtl(HWND hWnd, UINT uFlags, LPINT lpInfo);

void
 
GetEffectiveClientRect(HWND hWnd, LPRECT lprc, LPINT lpInfo);

WINBOOL
 
MakeDragList(HWND hLB);

void
 
DrawInsert(HWND handParent, HWND hLB, int nItem);

int
 
LBItemFromPt(HWND hLB, POINT pt, WINBOOL bAutoScroll);

HWND
 
CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy,
		    HWND hParent, int nID, HINSTANCE hInst,
		    HWND hBuddy,
		    int nUpper, int nLower, int nPos);

DWORD
 
CommDlgExtendedError(void );

 




















 


























































 






 






  



  




 


























































































































































































 



















































































































 






















































































































LONG
 
RegCloseKey (
    HKEY hKey
    );

LONG
 
RegSetKeySecurity (
    HKEY hKey,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor
    );

LONG
 
RegFlushKey (
    HKEY hKey
    );

LONG
 
RegGetKeySecurity (
    HKEY hKey,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    LPDWORD lpcbSecurityDescriptor
    );

LONG
 
RegNotifyChangeKeyValue (
    HKEY hKey,
    WINBOOL bWatchSubtree,
    DWORD dwNotifyFilter,
    HANDLE hEvent,
    WINBOOL fAsynchronus
    );

WINBOOL
 
IsValidCodePage(
    UINT  CodePage);


UINT
 
GetACP(void);


UINT
 
GetOEMCP(void);


WINBOOL
 
GetCPInfo(UINT, LPCPINFO);


WINBOOL
 
IsDBCSLeadByte(
    BYTE  TestChar);


WINBOOL
 
IsDBCSLeadByteEx(
    UINT  CodePage,
    BYTE  TestChar);


int
 
MultiByteToWideChar(
    UINT     CodePage,
    DWORD    dwFlags,
    LPCSTR   lpMultiByteStr,
    int      cchMultiByte,
    LPWSTR   lpWideCharStr,
    int      cchWideChar);


int
 
WideCharToMultiByte(
    UINT     CodePage,
    DWORD    dwFlags,
    LPCWSTR  lpWideCharStr,
    int      cchWideChar,
    LPSTR    lpMultiByteStr,
    int      cchMultiByte,
    LPCSTR   lpDefaultChar,
    LPBOOL   lpUsedDefaultChar);

WINBOOL
 
IsValidLocale(
    LCID   Locale,
    DWORD  dwFlags);


LCID
 
ConvertDefaultLocale(
    LCID   Locale);


LCID
 
GetThreadLocale(void);


WINBOOL
 
SetThreadLocale(
    LCID  Locale
    );


LANGID
 
GetSystemDefaultLangID(void);


LANGID
 
GetUserDefaultLangID(void);


LCID
 
GetSystemDefaultLCID(void);


LCID
 
GetUserDefaultLCID(void);


WINBOOL
 
ReadConsoleOutputAttribute(
    HANDLE hConsoleOutput,
    LPWORD lpAttribute,
    DWORD nLength,
    COORD dwReadCoord,
    LPDWORD lpNumberOfAttrsRead
    );


WINBOOL
 
WriteConsoleOutputAttribute(
    HANDLE hConsoleOutput,
    const  WORD *lpAttribute,
    DWORD nLength,
    COORD dwWriteCoord,
    LPDWORD lpNumberOfAttrsWritten
    );


WINBOOL
 
FillConsoleOutputAttribute(
    HANDLE hConsoleOutput,
    WORD   wAttribute,
    DWORD  nLength,
    COORD  dwWriteCoord,
    LPDWORD lpNumberOfAttrsWritten
    );


WINBOOL
 
GetConsoleMode(
    HANDLE hConsoleHandle,
    LPDWORD lpMode
    );


WINBOOL
 
GetNumberOfConsoleInputEvents(
    HANDLE hConsoleInput,
    LPDWORD lpNumberOfEvents
    );


WINBOOL
 
GetConsoleScreenBufferInfo(
    HANDLE hConsoleOutput,
    PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo
    );


COORD
 
GetLargestConsoleWindowSize(
    HANDLE hConsoleOutput
    );


WINBOOL
 
GetConsoleCursorInfo(
    HANDLE hConsoleOutput,
    PCONSOLE_CURSOR_INFO lpConsoleCursorInfo
    );


WINBOOL
 
GetNumberOfConsoleMouseButtons(
    LPDWORD lpNumberOfMouseButtons
    );


WINBOOL
 
SetConsoleMode(
    HANDLE hConsoleHandle,
    DWORD dwMode
    );


WINBOOL
 
SetConsoleActiveScreenBuffer(
    HANDLE hConsoleOutput
    );


WINBOOL
 
FlushConsoleInputBuffer(
    HANDLE hConsoleInput
    );


WINBOOL
 
SetConsoleScreenBufferSize(
    HANDLE hConsoleOutput,
    COORD dwSize
    );


WINBOOL
 
SetConsoleCursorPosition(
    HANDLE hConsoleOutput,
    COORD dwCursorPosition
    );


WINBOOL
 
SetConsoleCursorInfo(
    HANDLE hConsoleOutput,
    const  CONSOLE_CURSOR_INFO *lpConsoleCursorInfo
    );

WINBOOL
 
SetConsoleWindowInfo(
    HANDLE hConsoleOutput,
    WINBOOL bAbsolute,
    const  SMALL_RECT *lpConsoleWindow
    );


WINBOOL
 
SetConsoleTextAttribute(
    HANDLE hConsoleOutput,
    WORD wAttributes
    );


WINBOOL
 
SetConsoleCtrlHandler(
    PHANDLER_ROUTINE HandlerRoutine,
    WINBOOL Add
    );


WINBOOL
 
GenerateConsoleCtrlEvent(
    DWORD dwCtrlEvent,
    DWORD dwProcessGroupId
    );


WINBOOL
 
AllocConsole( void  );


WINBOOL
 
FreeConsole( void  );



HANDLE
 
CreateConsoleScreenBuffer(
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    const  SECURITY_ATTRIBUTES *lpSecurityAttributes,
    DWORD dwFlags,
    LPVOID lpScreenBufferData
    );


UINT
 
GetConsoleCP( void  );


WINBOOL
 
SetConsoleCP(
    UINT wCodePageID
    );


UINT
 
GetConsoleOutputCP( void  );


WINBOOL
 
SetConsoleOutputCP(
    UINT wCodePageID
    );

DWORD  
WNetConnectionDialog(
    HWND  hwnd,
    DWORD dwType
    );

DWORD  
WNetDisconnectDialog(
    HWND  hwnd,
    DWORD dwType
    );

DWORD  
WNetCloseEnum(
    HANDLE   hEnum
    );

WINBOOL
 
CloseServiceHandle(
    SC_HANDLE   hSCObject
    );


WINBOOL
 
ControlService(
    SC_HANDLE           hService,
    DWORD               dwControl,
    LPSERVICE_STATUS    lpServiceStatus
    );

WINBOOL
 
DeleteService(
    SC_HANDLE   hService
    );

SC_LOCK
 
LockServiceDatabase(
    SC_HANDLE   hSCManager
    );


WINBOOL
 
NotifyBootConfigStatus(
    WINBOOL     BootAcceptable
    );

WINBOOL
 
QueryServiceObjectSecurity(
    SC_HANDLE               hService,
    SECURITY_INFORMATION    dwSecurityInformation,
    PSECURITY_DESCRIPTOR    lpSecurityDescriptor,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded
    );


WINBOOL
 
QueryServiceStatus(
    SC_HANDLE           hService,
    LPSERVICE_STATUS    lpServiceStatus
    );

WINBOOL
 
SetServiceObjectSecurity(
    SC_HANDLE               hService,
    SECURITY_INFORMATION    dwSecurityInformation,
    PSECURITY_DESCRIPTOR    lpSecurityDescriptor
    );


WINBOOL
 
SetServiceStatus(
    SERVICE_STATUS_HANDLE   hServiceStatus,
    LPSERVICE_STATUS        lpServiceStatus
    );

WINBOOL
 
UnlockServiceDatabase(
    SC_LOCK     ScLock
    );

 

int  
ChoosePixelFormat(HDC, const  PIXELFORMATDESCRIPTOR *);	

int  
DescribePixelFormat(HDC, int, UINT, LPPIXELFORMATDESCRIPTOR);

UINT  
GetEnhMetaFilePixelFormat(HENHMETAFILE, DWORD,
			  const  PIXELFORMATDESCRIPTOR *);

int  
GetPixelFormat(HDC);

WINBOOL  
SetPixelFormat(HDC, int, const  PIXELFORMATDESCRIPTOR *);

WINBOOL  
SwapBuffers(HDC);

HGLRC  
wglCreateContext(HDC);

HGLRC  
wglCreateLayerContext(HDC, int);

WINBOOL  
wglCopyContext(HGLRC, HGLRC, UINT);

WINBOOL  
wglDeleteContext(HGLRC);

WINBOOL  
wglDescribeLayerPlane(HDC, int, int, UINT, LPLAYERPLANEDESCRIPTOR);

HGLRC  
wglGetCurrentContext(void );

HDC  
wglGetCurrentDC(void );

int  
wglGetLayerPaletteEntries(HDC, int, int, int, const  COLORREF *);

PROC  
wglGetProcAddress(LPCSTR);

WINBOOL  
wglMakeCurrent(HDC, HGLRC);

WINBOOL  
wglRealizeLayerPalette(HDC, int, WINBOOL);

int  
wglSetLayerPaletteEntries(HDC, int, int, int, const  COLORREF *);

WINBOOL  
wglShareLists(HGLRC, HGLRC);

WINBOOL  
wglSwapLayerBuffers(HDC, UINT);

 












 
 

WINBOOL   
DragQueryPoint (HDROP, LPPOINT);

void   
DragFinish (HDROP);

void   
DragAcceptFiles (HWND, WINBOOL);

HICON   
DuplicateIcon (HINSTANCE, HICON);

 
 
 

HCONV   	DdeConnect (DWORD, HSZ, HSZ, CONVCONTEXT *);
WINBOOL   	DdeDisconnect (HCONV);
WINBOOL   	DdeFreeDataHandle (HDDEDATA);
DWORD   	DdeGetData (HDDEDATA, BYTE *, DWORD, DWORD);
UINT   	DdeGetLastError (DWORD);
HDDEDATA   	DdeNameService (DWORD, HSZ, HSZ, UINT);
WINBOOL   	DdePostAdvise (DWORD, HSZ, HSZ);
HCONV   	DdeReconnect (HCONV);
WINBOOL   	DdeUninitialize (DWORD);
int   	DdeCmpStringHandles (HSZ, HSZ);
HDDEDATA   	DdeCreateDataHandle (DWORD, LPBYTE, DWORD, DWORD, HSZ,
				UINT, UINT);

 
 

DWORD   NetUserEnum (LPWSTR, DWORD, DWORD, LPBYTE*, DWORD, LPDWORD,
				LPDWORD, LPDWORD);
DWORD   NetApiBufferFree (LPVOID);
DWORD   NetUserGetInfo (LPWSTR, LPWSTR, DWORD, LPBYTE);
DWORD   NetGetDCName (LPWSTR, LPWSTR, LPBYTE*);
DWORD   NetGroupEnum (LPWSTR, DWORD, LPBYTE*, DWORD, LPDWORD,
				LPDWORD, LPDWORD);
DWORD   NetLocalGroupEnum (LPWSTR, DWORD, LPBYTE*, DWORD, LPDWORD,
				LPDWORD, LPDWORD);

void   
SHAddToRecentDocs (UINT, LPCVOID);

LPITEMIDLIST   
SHBrowseForFolder (LPBROWSEINFO);

void   
SHChangeNotify (LONG, UINT, LPCVOID, LPCVOID);

int   
SHFileOperation (LPSHFILEOPSTRUCT);

void   
SHFreeNameMappings (HANDLE);

 







DWORD   
SHGetFileInfo (LPCTSTR, DWORD, SHFILEINFO   *, UINT, UINT);

 




 




WINBOOL   
SHGetPathFromIDList (LPCITEMIDLIST, LPTSTR);

HRESULT   
SHGetSpecialFolderLocation (HWND, int, LPITEMIDLIST *);

 





}



# 55 "include/windows.h" 2




 
# 1 "include/Windows32/Errors.h" 1
 



























 





extern "C" {


 































































































































































































































































































































































































































































































































































































































































































}



# 60 "include/windows.h" 2




 




 






typedef WINBOOL BOOL;


 







# 11 "winsup.h" 2


# 1 "../newlib/libc/include/sys/types.h" 1
 

























# 1 "E:\\gcc-ms\\BIN\\include/stddef.h" 1 3






 







 

 




 


 





 


# 61 "E:\\gcc-ms\\BIN\\include/stddef.h" 3


 





 


















 





 

 





















typedef long int ptrdiff_t;









 




 

 
































typedef unsigned int size_t;


















 




 



























 














































typedef unsigned int  wint_t;




 

# 302 "E:\\gcc-ms\\BIN\\include/stddef.h" 3




 













 







# 27 "../newlib/libc/include/sys/types.h" 2

# 1 "../newlib/libc/include/machine/types.h" 1









# 28 "../newlib/libc/include/sys/types.h" 2


 


















typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;


typedef	unsigned short	ushort;		 
typedef	unsigned int	uint;		 



typedef long  time_t;



typedef	long	daddr_t;
typedef	char *	caddr_t;







typedef	unsigned short	ino_t;



 






typedef	short	dev_t;

typedef	long	off_t;

typedef	unsigned short	uid_t;
typedef	unsigned short	gid_t;
typedef int pid_t;
typedef	long key_t;
typedef long ssize_t;












typedef unsigned int mode_t __attribute__ ((__mode__ (__SI__))) ;



typedef unsigned short nlink_t;

 







 









typedef	long	fd_mask;





 

typedef	struct _types_fd_set {
	fd_mask	fds_bits[((( 64  )+((  (sizeof (fd_mask) * 8 )  )-1))/(  (sizeof (fd_mask) * 8 )  )) ];
} _types_fd_set;














# 13 "winsup.h" 2

# 1 "include/sys/strace.h" 1
 

 



















extern "C" {


 

















 
int strace (void);

 
void strace_dump (void);

 
void strace_printf (const char *, ...);

void _strace_wm (int message, int word, int lon);















}



# 14 "winsup.h" 2

# 1 "include/sys/resource.h" 1



# 1 "../newlib/libc/include/sys/time.h" 1
 

 

 














extern "C" {




struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};


 





struct  itimerval {
  struct  timeval it_interval;
  struct  timeval it_value;
};



}


# 4 "include/sys/resource.h" 2





struct rusage {
  	struct timeval ru_utime;	 
	struct timeval ru_stime;	 
	long ru_maxrss;
	long ru_ixrss;                
	long ru_idrss;                
	long ru_isrss;                
        long ru_minflt;               
        long ru_majflt;               
        long ru_nswap;                
        long ru_inblock;              
        long ru_oublock;              
        long ru_msgsnd;               
        long ru_msgrcv;               
        long ru_nsignals;             
        long ru_nvcsw;                
        long ru_nivcsw;               

};


extern "C" int getrusage(int who, struct rusage *rusage);






# 15 "winsup.h" 2

# 1 "../newlib/libc/include/setjmp.h" 1
 






extern "C" {



# 1 "../newlib/libc/include/_ansi.h" 1
 

 











# 1 "../newlib/libc/include/sys/config.h" 1



 
 
# 14 "../newlib/libc/include/sys/config.h"


# 25 "../newlib/libc/include/sys/config.h"


 








# 44 "../newlib/libc/include/sys/config.h"






































 








typedef int __int32_t;
typedef unsigned int __uint32_t;







# 15 "../newlib/libc/include/_ansi.h" 2


 
 

























# 61 "../newlib/libc/include/_ansi.h"


 








# 12 "../newlib/libc/include/setjmp.h" 2

# 1 "../newlib/libc/include/machine/setjmp.h" 1












 























# 45 "../newlib/libc/include/machine/setjmp.h"




















































































typedef	double  jmp_buf[24 ];





# 1 "../newlib/libc/include/signal.h" 1


extern "C" {




# 1 "../newlib/libc/include/sys/signal.h" 1
 







typedef unsigned long sigset_t;
struct sigaction 
{
	void (*sa_handler)(int);
	sigset_t sa_mask;
	int sa_flags;
};





 





int sigprocmask (int how, const sigset_t *a, sigset_t *b);

 

 



int  kill    (int, int)  ;
int  sigaction    (int, const struct sigaction *, struct sigaction *)  ;
 
int  sigdelset    (sigset_t *, const int)  ;
int  sigismember    (const sigset_t *, int)  ;
int  sigfillset    (sigset_t *)  ;
 
int  sigpending    (sigset_t *)  ;
int  sigsuspend    (const sigset_t *)  ;
int  sigpause    (int)  ;




# 83 "../newlib/libc/include/sys/signal.h"



































# 171 "../newlib/libc/include/sys/signal.h"


# 8 "../newlib/libc/include/signal.h" 2


typedef int	sig_atomic_t;		 





typedef void (*_sig_func_ptr) (int);

struct _reent;

_sig_func_ptr  _signal_r    (struct _reent *, int, _sig_func_ptr)  ;
int	 _raise_r    (struct _reent *, int)  ;


_sig_func_ptr  signal    (int, _sig_func_ptr)  ;
int	 raise    (int)  ;



}


# 135 "../newlib/libc/include/machine/setjmp.h" 2


 
typedef int sigjmp_buf[24 +2];













# 13 "../newlib/libc/include/setjmp.h" 2


void	 longjmp   (jmp_buf __jmpb, int __retval)  ;
int	 setjmp   (jmp_buf __jmpb)  ;


}



# 16 "winsup.h" 2






# 1 "../newlib/libc/include/string.h" 1
 









extern "C" {





# 1 "E:\\gcc-ms\\BIN\\include/stddef.h" 1 3






 


# 19 "E:\\gcc-ms\\BIN\\include/stddef.h" 3



 


 





 


# 61 "E:\\gcc-ms\\BIN\\include/stddef.h" 3


 





 


















 





 

 


# 126 "E:\\gcc-ms\\BIN\\include/stddef.h" 3


 




 

 


# 182 "E:\\gcc-ms\\BIN\\include/stddef.h" 3





 




 


# 256 "E:\\gcc-ms\\BIN\\include/stddef.h" 3
















 

# 302 "E:\\gcc-ms\\BIN\\include/stddef.h" 3




 













 







# 17 "../newlib/libc/include/string.h" 2






void *  	  memchr   (const void * , int, size_t)  ;
int 	  memcmp   (const void * , const void * , size_t)  ;
void *  	  memcpy   (void * , const void * , size_t)  ;
void * 	  memmove   (void * , const void * , size_t)  ;
void * 	  memset   (void * , int, size_t)  ;
char 	*  strcat   (char *, const char *)  ;
char 	*  strchr   (const char *, int)  ;
int	  strcmp   (const char *, const char *)  ;
int	  strcoll   (const char *, const char *)  ;
char 	*  strcpy   (char *, const char *)  ;
size_t	  strcspn   (const char *, const char *)  ;
char 	*  strerror   (int)  ;
size_t	  strlen   (const char *)  ;
char 	*  strncat   (char *, const char *, size_t)  ;
int	  strncmp   (const char *, const char *, size_t)  ;
char 	*  strncpy   (char *, const char *, size_t)  ;
char 	*  strpbrk   (const char *, const char *)  ;
char 	*  strrchr   (const char *, int)  ;
size_t	  strspn   (const char *, const char *)  ;
char 	*  strstr   (const char *, const char *)  ;


char 	*  strtok   (char *, const char *)  ;


size_t	  strxfrm   (char *, const char *, size_t)  ;


char 	*  strtok_r   (char *, const char *, char **)  ;

int	  bcmp   (const char *, const char *, size_t)  ;
void	  bcopy   (const char *, char *, size_t)  ;
void	  bzero   (char *, size_t)  ;
int	  ffs   (int)  ;
char 	*  index   (const char *, int)  ;
void * 	  memccpy   (void * , const void * , int, size_t)  ;
char 	*  rindex   (const char *, int)  ;
int	  strcasecmp   (const char *, const char *)  ;
char 	*  strdup   (const char *)  ;
int	  strncasecmp   (const char *, const char *, size_t)  ;
char 	*  strsep   (char **, const char *)  ;
char	*  strlwr   (char *)  ;
char	*  strupr   (char *)  ;

char    *  strsignal    (int signo)  ;
int      strtosigno    (const char *name)  ;


 
















}


# 22 "winsup.h" 2


# 1 "syscalls.h" 1
 










extern "C" {


# 1 "../newlib/libc/include/sys/stat.h" 1




extern "C" {



# 1 "../newlib/libc/include/time.h" 1
 







extern "C" {












# 1 "E:\\gcc-ms\\BIN\\include/stddef.h" 1 3






 


# 19 "E:\\gcc-ms\\BIN\\include/stddef.h" 3



 


 





 


# 61 "E:\\gcc-ms\\BIN\\include/stddef.h" 3


 





 


















 





 

 


# 126 "E:\\gcc-ms\\BIN\\include/stddef.h" 3


 




 

 


# 182 "E:\\gcc-ms\\BIN\\include/stddef.h" 3





 




 


# 256 "E:\\gcc-ms\\BIN\\include/stddef.h" 3
















 

# 302 "E:\\gcc-ms\\BIN\\include/stddef.h" 3




 













 







# 22 "../newlib/libc/include/time.h" 2


 



typedef unsigned long  clock_t;








struct tm
{
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
};

clock_t	    clock       (void)  ;
double	    difftime    (time_t _time2, time_t _time1)  ;
time_t	    mktime      (struct tm *_timeptr)  ;
time_t	    time        (time_t *_timer)  ;

char	  *  asctime     (const struct tm *_tblock)  ;
char	  *  ctime       (const time_t *_time)  ;
struct tm *  gmtime      (const time_t *_timer)  ;
struct tm *  localtime   (const time_t *_timer)  ;

size_t	    strftime    (char *_s, size_t _maxsize, const char *_fmt, const struct tm *_t)  ;

char	  *  asctime_r   	(const struct tm *, char *)  ;
char	  *  ctime_r   	(const time_t *, char *)  ;
struct tm *  gmtime_r   	(const time_t *, struct tm *)  ;
struct tm *  localtime_r   	(const time_t *, struct tm *)  ;



extern void tzset  (void)  ;
extern time_t *__imp__timezone;

extern int *__imp__daylight;

extern char *((*__imp__tzname)[2]);





}


# 9 "../newlib/libc/include/sys/stat.h" 2









 


 



struct	stat 
{
  dev_t		st_dev;
  ino_t		st_ino;
  mode_t	st_mode;
  nlink_t	st_nlink;
  uid_t		st_uid;
  gid_t		st_gid;
  dev_t		st_rdev;
  off_t		st_size;
   





  time_t	st_atime;
  long		st_spare1;
  time_t	st_mtime;
  long		st_spare2;
  time_t	st_ctime;
  long		st_spare3;
  long		st_blksize;
  long		st_blocks;
  long	st_spare4[2];

};

































 

































int	 chmod   ( const char *_path, mode_t _mode )  ;
int      fchmod   (int _fd, mode_t _mode)  ;
int	 fstat   ( int _fd, struct stat *_sbuf )  ;
int	 mkdir   ( const char *_path, mode_t _mode )  ;
int	 mkfifo   ( char *_path, mode_t _mode )  ;
int	 stat   ( const char *_path, struct stat *_sbuf )  ;
mode_t	 umask   ( mode_t _mask )  ;



}


# 15 "syscalls.h" 2

# 1 "include/sys/param.h" 1



 
 



 


 
 


 
 


 



 







 


 



# 16 "syscalls.h" 2



# 1 "../newlib/libc/include/sys/times.h" 1


extern "C" {











struct tms {
	clock_t	tms_utime;		 
	clock_t	tms_stime;		 
	clock_t	tms_cutime;		 
	clock_t	tms_cstime;		 
};

clock_t  times   (struct tms *)  ;


}


# 19 "syscalls.h" 2

# 1 "include/sys/uio.h" 1




extern "C" {


 
# 1 "E:\\gcc-ms\\BIN\\include/stddef.h" 1 3
# 327 "E:\\gcc-ms\\BIN\\include/stddef.h" 3

# 9 "include/sys/uio.h" 2

 


 



struct iovec {
	caddr_t iov_base;
	int iov_len;
};


};


# 20 "syscalls.h" 2

# 1 "../newlib/libc/include/errno.h" 1
# 1 "../newlib/libc/include/sys/errno.h" 1
 





extern "C" {



# 1 "../newlib/libc/include/sys/reent.h" 1
 

 





extern "C" {





struct _glue 
{
  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};

struct _Bigint 
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  unsigned long _x[1];
};

 





struct _atexit {
	struct	_atexit *_next;			 
	int	_ind;				 
	void	(*_fns[32 ])();	 
};

 






struct __sbuf {
	unsigned char *_base;
	int	_size;
};

 




typedef long _fpos_t;		 
				 

 
























struct __sFILE {
  unsigned char *_p;	 
  int	_r;		 
  int	_w;		 
  short	_flags;		 
  short	_file;		 
  struct __sbuf _bf;	 
  int	_lbfsize;	 

   
  void * 	_cookie;	 

  int	 (*_read)   (void *  _cookie, char *_buf, int _n)  ;
  int	 (*_write)   (void *  _cookie, const char *_buf, int _n)  ;
  _fpos_t  (*_seek)   (void *  _cookie, _fpos_t _offset, int _whence)  ;
  int	 (*_close)   (void *  _cookie)  ;

   
  struct __sbuf _ub;	 
  unsigned char *_up;	 
  int	_ur;		 

   
  unsigned char _ubuf[3];	 
  unsigned char _nbuf[1];	 

   
  struct __sbuf _lb;	 

   
  int	_blksize;	 
  int	_offset;	 

  struct _reent *_data;
};

 







struct _reent
{
   
  int _errno;

   


  struct __sFILE *_stdin, *_stdout, *_stderr;

  int  _inc;			 
  char _emergency[25];
 
  int _current_category;	 
  const  char *_current_locale;

  int __sdidinit;		 

  void  (*__cleanup)   (struct _reent *)  ;

   
  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;

   
  int _cvtlen;			 
  char *_cvtbuf;

   

  unsigned char * _nextf[30 ];
  unsigned int _nmalloc[30 ];

   
  struct _atexit *_atexit;	 
  struct _atexit _atexit0;	 

   
  void (**(_sig_func))();

   


  struct _glue __sglue;			 
  struct __sFILE __sf[3];		 
};




 








extern struct _reent *_impure_ptr  ;

void _reclaim_reent  (struct _reent *)  ;

 






}


# 11 "../newlib/libc/include/sys/errno.h" 2




extern int *__errno  (void)  ;

























































































































 





}


# 1 "../newlib/libc/include/errno.h" 2

# 21 "syscalls.h" 2


 

 

clock_t times (struct tms * buf);
clock_t _times (struct tms * buf);
int utimes (const char *path, struct timeval *tvp);
int settimeofday (const struct timeval * ,  const  struct timezone *);
int gettimeofday (struct timeval *p, struct timezone *z);
int _gettimeofday (struct timeval *p, struct timezone *z);
char * timezone ();
char *getwd (char *);
int _open (const char *path, int flags, mode_t mode);
int _close (int id);
off_t _lseek (int fd, off_t pos, int dir);
int ioctl (int id, int cmd , void *);
ssize_t _read (int fd, void *ptr, size_t len);
ssize_t _write (int fd, const void *ptr, size_t len);
ssize_t readv (int fd, const struct iovec *, int);
ssize_t writev (int fd, const struct iovec *, int);
void * _sbrk (size_t incr);
int _stat (const char *name, struct stat *buf);
int _fstat (int fd, struct stat *buf);
int fsync (int);
int getdtablesize();
struct passwd *getpwent (void);
void endpwent (void);
struct passwd * getpwuid (uid_t uid);
size_t getpagesize ();
int _setmode (int, int);
int setmode (int, int);
int ftruncate (int, off_t);
int truncate (const char *, off_t);
int symlink (const char *oldpath, const char *newpath);
int readlink (const char *, char *, int);
int gettimeofday (struct timeval *p, struct timezone *z);
char *cuserid (char *src);
struct tm * localtime (const time_t * tim_p);
void export_free (void *p);
void *export_malloc (int size);
void *export_realloc (void *p, int size);
void *export_calloc (size_t nmemb, size_t size);

 
pid_t sexecl(HANDLE, const char *path, const char *argv0, ...);
pid_t sexecle(HANDLE, const char *path, const char *argv0, ...  );
pid_t sexeclp(HANDLE, const char *path, const char *argv0, ...);
pid_t sexeclpe(HANDLE, const char *path, const char *argv0, ...  );

pid_t sexecv(HANDLE, const char *path, const char * const *argv);
pid_t sexecve(HANDLE, const char *path, const char * const *argv, const char * const *envp);
pid_t sexecvp(HANDLE, const char *path, const char * const *argv);
pid_t sexecvpe(HANDLE, const char *path, const char * const *argv, const char * const *envp);


}

# 24 "winsup.h" 2

# 1 "fhandler.h" 1
 












 






















class fhandler_base
{
  int access_;
  HANDLE handle_;

   
  char w_binary_;

   
  char r_binary_;
  char close_exec_p_;		 

   
  char readahead_valid_;
  char readahead_;

  char append_p_;  
  char async_;     

  int rpos_;  
  int rsize_; 

  char had_eof_;
  unsigned long namehash_;	  

   
  char *unix_path_name_;
   
  int openflags_;

  void set_name (const char *);

protected:

  char symlink_p_;
   

  char execable_p_;		

public:

  fhandler_base (const char *name = 0);
  ~fhandler_base(void);

   
  void set_handle (HANDLE);

  int  get_access (void) { return access_; }
  void set_access (int x) { access_ = x; }

  int  get_async (void) { return async_; }
  void set_async (int x) { async_ = x; }
  int  get_flags (void) { return openflags_; }
  void set_flags (int x) { openflags_ = x; }

  int get_w_binary (void) { return w_binary_; }
  int get_r_binary (void) { return r_binary_; }

  void set_w_binary (int b) { w_binary_ = b; }
  void set_r_binary (int b) { r_binary_ = b; }

  void set_close_on_exec (char val) { close_exec_p_ = val; }
  char get_close_on_exec (void) { return close_exec_p_; }

  const char *get_name (void) { return unix_path_name_; }
  unsigned long get_namehash(void) { return namehash_; }

   
  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual int close (void);
  virtual int fstat (struct stat *buf);
  virtual int ioctl (int cmd, void *);
  virtual char const * ttyname (void) { return get_name(); }
  virtual int read (void *ptr, size_t len);
  virtual int write (const void *ptr, size_t len);
  virtual off_t lseek (off_t offset, int whence);
  virtual int lock(int, struct flock *);
  virtual void dump (void);
  virtual int dup (fhandler_base *child);

  void *operator new (size_t, void *);

  virtual void init (HANDLE, int, int, const char *);

  virtual int tcflush (int);
  virtual int tcsendbreak (int);
  virtual int tcdrain (void);
  virtual int tcflow (int);
  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int tcsetpgrp (const pid_t pid);
  virtual int tcgetpgrp (void);
  virtual int is_tty (void) { return 0; }
  virtual char *ptsname (void) { return __null ;}
  virtual class fhandler_socket *is_socket (void) { return 0; }
  virtual class fhandler_console *is_console (void) { return 0; }

  virtual int raw_read (void *ptr, size_t ulen);
  virtual int raw_write (const void *ptr, size_t ulen);

   
  virtual const int always_read_ready (void) { return 1; } ;
   
  virtual const int always_write_ready (void) { return 1; } ;
   
  virtual const int always_except_ready (void) { return 1; } ;

   
  virtual int linearize(unsigned char *);
   
  virtual int de_linearize(const unsigned char *);

   

  virtual HANDLE get_handle (void) const { return handle_; }
  virtual HANDLE get_input_handle (void) const { return handle_; }
  virtual HANDLE get_output_handle (void) const { return handle_; }
  virtual void dup_for_fork (void) { return; }
};

class fhandler_socket: public fhandler_base
{
public:
  fhandler_socket (unsigned int, const char *name = 0);
  ~fhandler_socket (void);
  int get_socket (void) const { return (int) get_handle(); }
  fhandler_socket * is_socket (void) { return this; }
  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int ioctl (int cmd, void *);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int fstat (struct stat *buf);
  virtual int close (void);

  virtual const int always_read_ready (void) { return 0; }
  virtual const int always_write_ready (void) { return 0; }
  virtual const int always_except_ready (void) { return 0; }
};

class fhandler_pipe: public fhandler_base
{
public:
  fhandler_pipe (const char *name = 0);
  virtual off_t lseek (off_t offset, int whence);

  virtual const int always_read_ready (void) { return 0; }
};

class fhandler_dev_floppy: public fhandler_base
{
public:
  fhandler_dev_floppy (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode = 0);
};

class fhandler_dev_tape: public fhandler_base
{
public:
  fhandler_dev_tape (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode = 0);
};

 

class fhandler_disk_file: public fhandler_base
{
private:
  int check_execable_p (const char *path);

public:
  fhandler_disk_file (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode = 0);
  virtual int lock (int, struct flock *);
};

class fhandler_tty: public fhandler_base
{
private:
  unsigned int vmin_;			 
  unsigned int vtime_;			 
  pid_t pgrp_;

public:
   
  fhandler_tty (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode);
  virtual int raw_read (void *ptr, size_t ulen);
  virtual int tcsendbreak (int);
  virtual int tcdrain (void);
  virtual int tcflow (int);
  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int fstat (struct stat *buf);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int tcflush (int);
  virtual void dump (void);
  virtual int is_tty (void) { return 1; }

   


  virtual int tcgetpgrp (void) { return pgrp_; }
  virtual int tcsetpgrp (const pid_t pid) { pgrp_ = pid; return 0; }

   
  virtual int linearize (unsigned char *);
   
  virtual int de_linearize (const unsigned char *);
};

 
class fhandler_console: public fhandler_tty
{
private:

 

   









  int state_;
  int args_[10 ];
  int nargs_;

 
  HANDLE output_handle_;
  DWORD default_color;

 

  BOOL fillin_info (void);
  void clear_screen (int, int, int, int);
  void scroll_screen (int, int, int, int, int, int);
  void cursor_set (BOOL, int, int);
  void cursor_get (int *, int *);
  void cursor_rel (int, int);
  void get_info (void);
  const unsigned char * write_normal (unsigned const char*, unsigned const char *);
  void char_command (char);
  int output_tcsetattr (int a, const struct termios *t);

 
   








  int iflag_;
  int lflag_;

 
  int igncr_enabled (void);
  int input_tcsetattr (int a, const struct termios *t);

public:
  fhandler_console (const char *name = 0);

  fhandler_console* is_console (void) { return this; }

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);

  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int close (void);

  virtual int tcflush (int);
  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);

   
  virtual int dup (fhandler_base *child);

  virtual int ioctl (int cmd, void *);
  virtual void init (HANDLE, int, int, const char *);

  virtual const int always_read_ready (void) { return 0;}

   
  virtual int linearize (unsigned char *);
   
  virtual int de_linearize (const unsigned char *);

  virtual HANDLE get_output_handle(void) const { return output_handle_; }
};

class fhandler_tty_slave: public fhandler_base
{
private:
  HANDLE output_done_event;	 
				 
  HANDLE ioctl_request_event;	 
				 
  HANDLE ioctl_done_event;	 
				 
  HANDLE output_mutex;
  int ttynum;			 
 
  HANDLE output_handle_;
  void send_ioctl_request (void);
public:
   
  fhandler_tty_slave (int, const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int close (void);
  virtual void init (HANDLE, int, int, const char *);

  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int tcsetpgrp (const pid_t pid);
  virtual int tcgetpgrp (void);
  virtual int tcflush (int);
  virtual int ioctl (int cmd, void *);

  virtual int fstat (struct stat *buf);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int is_tty (void) { return 1; }
  virtual const int always_read_ready (void) { return 0;}

   
  virtual int linearize(unsigned char *);
   
  virtual int de_linearize (const unsigned char *);

   
  virtual int dup (fhandler_base *child);
  virtual HANDLE get_output_handle(void) const { return output_handle_; }
  virtual void dup_for_fork (void);
};

class fhandler_pty_master: public fhandler_base
{
  int pktmode;			 
public:
  HANDLE output_done_event;	 
				 
  HANDLE ioctl_request_event;	 
				 
  HANDLE ioctl_done_event;	 
				 
  HANDLE restart_output_event;
  HANDLE output_mutex;
  int ttynum;			 
  HANDLE output_handle_;	 
  int neednl_;			 

   
  fhandler_pty_master (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual int write (const void *ptr, size_t len);
  virtual int read (void *ptr, size_t len);
  virtual int close (void);

  virtual int tcsetattr (int a, const struct termios *t);
  virtual int tcgetattr (struct termios *t);
  virtual int tcflush (int);
  virtual int ioctl (int cmd, void *);

  virtual int fstat (struct stat *buf);
  virtual off_t lseek (off_t offset, int whence) { return 0; }
  virtual int is_tty (void) { return 1; }
  virtual char *ptsname (void);
  virtual const int always_read_ready (void) { return 0;}

  virtual HANDLE get_output_handle(void) const { return output_handle_; }
   
  virtual int linearize(unsigned char *);
   
  virtual int de_linearize (const unsigned char *);
  virtual void dup_for_fork (void);
};


class fhandler_dev_null: public fhandler_base
{
public:
  fhandler_dev_null (const char *name = 0);

  virtual fhandler_base *open (const char *path, int flags, mode_t mode=0);
  virtual void dump (void);
};

# 446 "fhandler.h"




class fhandler_tty_master: public fhandler_pty_master
{
public:
   
  fhandler_tty_master (const char *name = 0);
  fhandler_base *f;		 
  char item[sizeof(fhandler_console )];	
  HANDLE hThread;		 

  virtual int init (int);
};


uid_t get_file_owner (char *);
gid_t get_file_group (char *);


# 25 "winsup.h" 2

# 1 "path.h" 1
 









class path_conv 
{
  char path[(260) ];
 public:

  char binary_p;
  char silent_p;
  int  symlink_p;
  int  exec_p;

  int error;

  path_conv (const char * const, int follow_mode = 1);
  inline char *get_win32 () { return path; }
};

 


 


 

class mount_item
{
public:
   


   

  char device[(260) ];
  int devicelen;

   
  char path[(260) ];
  int pathlen;

  char binary;
  char silent;

  void init (const char *dev, const char *path, int flags);

  struct mntent *getmntent ();
};

 

 





class mount_info
{
 public:
  int nmounts;
  mount_item mount[30 ];

  void init ();
  int add_item (const char *dev, const char *path, int flags);
  int del_item (const char *path);
  void sort ();
  void to_registry ();
  void from_registry ();
  int posix_path_p ();
  int binary_win32_path_p (const char *path);
  int conv_to_win32_path (const char *src_path, char *win32_path,
			  char *full_win32_path);
  int conv_to_posix_path (const char *src_path, char *posix_path,
			  int keep_rel_p);
  struct mntent *getmntent (int x);
};

 
extern "C" {
  void conv_to_win32_path (const char *src_path, char *win32_path);
  void conv_to_full_win32_path (const char *src_path, char *win32_path);
  void conv_to_posix_path (const char *src_path, char *posix_path);
  void conv_to_full_posix_path (const char *src_path, char *posix_path);
  int posix_path_list_p (const char *path);
  int win32_to_posix_path_list_buf_size (const char *path_list);
  int posix_to_win32_path_list_buf_size (const char *path_list);
  void win32_to_posix_path_list (char *win32, char *posix);
  void posix_to_win32_path_list (char *posix, char *win32);
  void split_path (const char *path, char *dir, char *file);
}
# 26 "winsup.h" 2

# 1 "version.h" 1
 









 

 


























 









# 27 "winsup.h" 2

# 1 "tty.h" 1
 












# 1 "include/sys/termios.h" 1
 




























































 















 

































 















 

































 





















typedef unsigned char cc_t;
typedef unsigned short tcflag_t;
typedef unsigned char speed_t;

struct termios {
	tcflag_t	c_iflag;
	tcflag_t	c_oflag;
	tcflag_t	c_cflag;
	tcflag_t	c_lflag;
	char		c_line;
	cc_t		c_cc[18 ];
	speed_t		c_ispeed;
	speed_t		c_ospeed;
};









extern "C" {


int tcgetattr (int, struct termios *);
int tcsetattr (int, int, const struct termios *);
int tcsendbreak (int, int);
int tcdrain (int);
int tcflush (int, int);
int tcflow (int, int);


}


 
struct winsize
{
  unsigned short ws_row, ws_col;
  unsigned short ws_xpixel, ws_ypixel;
};





# 14 "tty.h" 2






 







class tty {
public:
  struct termios termios;
  struct winsize winsize;

   
  int cmd;
  union {
    struct termios termios;
    struct winsize winsize;
    int value;
    pid_t pid;
  } arg;
   


  int ioctl_retval;

  int read_retval;

  BOOL OutputStopped;
  int write_retval;

  pid_t pgid;	 
  pid_t sid;	 
  HWND  hwnd;	 

  DWORD master_pid;	 
  int slave_opened;
  HANDLE input_handle;	 
  HANDLE output_handle;

  void init ();
  int getsid () {return sid;}
  void setsid (pid_t tsid) {sid = tsid;}
  pid_t getpgid () {return pgid;}
  void setpgid (pid_t gid) {pgid = gid;}
  HWND gethwnd () {return hwnd;}
  void sethwnd (HWND wnd) {hwnd = wnd;}
};

class tty_list {
  tty ttys[16 ];
  int volatile count[16 ];  

public:
  int allocate_tty (int n);  
  int connect_tty (int);
  void free_tty (int);
  tty *gettty(int n) {return &ttys[n];}
  int getcount (int n) { return count[n]; }
  void terminate ();
  void init ();
};

void tty_init ();
void tty_terminate ();
int attach_tty (int);
void detach_tty (int);
void create_tty_master (int);
extern "C" ttyslot (void);


# 28 "winsup.h" 2

# 1 "delqueue.h" 1
 









 







   



class delqueue_item 
{
public:
  char name[(260 - 1  ) ];
  int inuse;
  void init ();
  int add (const char *dosname);
  void process ();
};

class delqueue_list 
{
public:
  delqueue_item dqueue[100 ];
  void init ();  
  void queue_file (const char *dosname);
  void process_queue ();
};
# 29 "winsup.h" 2


 
class pinfo;
class shared_info;

 
# 1 "sigproc.h" 1
 













enum procstuff
{
  PROC_ADDCHILD		= 1,	 
  PROC_CHILDSTOPPED	= 2,	 
  PROC_CHILDTERMINATED	= 3,	 
  PROC_CLEARWAIT	= 4,	 
  PROC_WAIT		= 5	 
};

typedef struct struct_waitq
{
  int pid;
  int options;
  int status;
  HANDLE ev;
  void *rusage;			 
  struct struct_waitq *next;
  HANDLE thread_ev;
} waitq;

enum
{
  __SIGSTRACE	    = -2,
  __SIGSUSPEND	    = -1,
  __SIGCHILDSTOPPED =  0,
  __SIGOFFSET	    =  2
};

extern HANDLE sig_dispatch;
extern DWORD waitq_storage;

extern void block_sig_dispatch (void);
extern void allow_sig_dispatch (void);

BOOL alive_parent (pinfo *);
void sig_dispatch_pending (void);
extern "C" void set_process_mask (sigset_t);
int sig_handle (int);
void sig_clear (int);
void sig_set_pending (int);
int handle_sigsuspend (sigset_t);

void proc_terminate (void);
void sigproc_init (void);
void subproc_init (void);
void sigproc_terminate (void);
BOOL proc_exists (pinfo *);
int proc_subproc (DWORD, DWORD);
int sig_send (pinfo *, int);


# 36 "winsup.h" 2


 

 















class per_process
{
 public:
  char *initial_sp;

   
   
  int magic_biscuit;
  int version_major;
  int version_minor;

  struct _reent **impure_ptr_ptr;
  char ***envptr;

   

  void *(*malloc)(size_t);
  void (*free)(void *);
  void *(*realloc)(void *, size_t);

  int *fmode_ptr;

  int (*main)(int, char **, char **);
  void (**ctors)(void);
  void (**dtors)(void);

   
  void *data_start;
  void *data_end;
  void *bss_start;
  void *bss_end;

  void *(*calloc)(size_t, size_t);
   
  void *public_reserved[4];

   



   
  int run_ctors_p;

   

   
  int __imp_malloc;
  int __imp_free;
  int __imp_realloc;

   
  void *base;			 
  void *ptr;			 
  int  size;			 

  HANDLE strace_file;		 


   

  int forkee;

  void *hmodule;

   

  void *internal_reserved[10];
};

extern per_process *u;  

 




 

class hinfo
{
 public:
  fhandler_base *h;
  char item[sizeof (fhandler_console )];
  int is_open (void) const { return h != 0; }
  void clearout (void);
};

class hinfo_vec
{
 public:
  hinfo *vec;

  int not_open (int fd);
  hinfo & operator [] (int arg);
  int find_unused_handle (int start);
  void release (int fd);
  void lookup_fhandler (int fd, const char *path, int flags);
  void clearout (void);
  void init_std_file_from_handle (int fd, HANDLE handle, int bin,
					int access, const char *name);
  fhandler_base * build_fhandler (const char *name, int n, HANDLE h);
  void dup_for_exec (void);
  void dup_for_fork (hinfo_vec *child);
  int dup2 (int oldfd, int newfd);

  int linearize_fd_array (unsigned char *, int);
  LPBYTE de_linearize_fd_array (LPBYTE);
};

 

class pinfo
{
 public:

   



  HANDLE hProcess;

   

  HANDLE subproc_ready;
  HANDLE forker_finished;
  HANDLE parent_alive;

   








  DWORD dwProcessId, dwSpawnedProcessId;

   





  uid_t uid;	 
  gid_t gid;	 
  pid_t pgid;	 
  pid_t sid;	 
  int ctty;	 
  mode_t umask;

   
  char stopsig;

  struct sigaction sigs[32 ];
  sigset_t sig_mask;		 
  LONG _sigtodo[32  + __SIGOFFSET];
  

   
  long start_time;
  struct rusage rusage_self;
  struct rusage rusage_children;

   
  char progname[(260) ];

  

   

   
  pid_t pid;
   
  pid_t ppid;

   
  DWORD strace_mask;
 
   
  jmp_buf restore;

   

  DWORD process_state;

   
  hinfo_vec hmap;
  struct _reent reent_save;

   
  void *mmap_ptr;

  void record_death (void);
  void record_death_nolock (void);
  void init_from_exec (void);
};




 
enum
{
  PID_NOT_IN_USE       = 0x0000,  
  PID_IN_USE 	       = 0x0001,  
  PID_ZOMBIE	       = 0x0002,  
  PID_STOPPED	       = 0x0004,  
  PID_TTYIN	       = 0x0008,  
  PID_TTYOU	       = 0x0010,  
  PID_ORPHANED	       = 0x0020,  
  PID_ACTIVE	       = 0x0040,  
  PID_CYGPARENT	       = 0x0080,  
  PID_SPLIT_HEAP       = 0x0100,  
				  
  PID_EXECED	       = 0x0200,  
  PID_SOCKETS_USED     = 0x0400,  
  PID_INITIALIZING     = 0x0800,  
  PID_USETTY	       = 0x1000,  
				  
				  
};




class pinfo_list
{
 private:
  pinfo *get_empty_pinfo (void);

 public:
  int next_pid_index;
  pinfo vec[128 ];
  char lock_info[(260)  + 1];
  pinfo *operator[] (pid_t x);
  int size (void) { return 128 ; }
  pinfo *lookup_by_handle (HANDLE *);
  pinfo *allocate_pid (void);
  void init (void);
};

void pinfo_init (void);
pinfo *procinfo (int n);

 
 




class host_dependent_constants
{
 public:
  void init (void);
  
   

  DWORD win32_upper;

   

  int shared;
};

extern host_dependent_constants host_dependent;

 
 


class shared_info
{
  int inited;

public:
  pinfo_list p;

   
  mount_info mount;

  int heap_chunk_in_mb;
  int heap_chunk_size (void);

  tty_list t;
  delqueue_list delqueue;
  void initialize (void);
};

extern shared_info *s;

void shared_init (void);
void shared_terminate (void);

 
extern "C" class shared_info *cygwin32_getshared (void);

 

 










 
 







 


 



 
void fork_init (void);
void fork_terminate (void);
void dump_jmp_buf (jmp_buf buf);

int spawn_guts (HANDLE hToken, const char *prog_arg,
                   const char *const *argv, const char *const envp[],
                   int pid, int mode);
const char * find_exec (const char *name, char *buf);

 
void strace_init (char *);

 

void heap_init (void);
void malloc_init (void);

void hmap_init (void);
void uinfo_init (void);

 
extern "C" int recreate_mmaps_after_fork (void *);
extern "C" void set_child_mmap_ptr (pinfo *);

extern "C" void close_all_files (void);


extern "C" {



 
extern "C" void seterrno (const char *, int line);


















}


void mark (const char *s, int i);


extern "C" int __small_sprintf (char *dst, const char *fmt, ...);




void system_printf (const char *fmt, ...);
void small_printf (const char *fmt, ...);

void dll_crt0 (per_process *);
extern "C" int dll_dllcrt0 (HMODULE,per_process*);

extern "C" unsigned long hash_path_name (unsigned long hash, const char *name);

long totime_t (FILETIME * ptr);

 
void totimeval (struct timeval *dst, FILETIME * src, int sub, int flag);
long to_time_t (FILETIME * ptr);
int fhandler_make_pipe (int fildes[2]);









void api_fatal (const char *);

void events_init (void);
void events_terminate (void);
int lock_pinfo_for_update (DWORD timeout);
void unlock_pinfo (void);
extern "C" void	do_exit (int) __attribute__ ((noreturn));

 
extern pinfo *myself;

 
extern HANDLE pinfo_mutex;
extern HANDLE signal_arrived;
extern HANDLE title_mutex;

 
 
SECURITY_DESCRIPTOR *get_null_sd (void);

int get_id_from_sid (PSID);

BOOL get_file_attribute (const char *, int *);
BOOL set_file_attribute (const char *, int);

int NTReadEA (const char *file, const char *attrname, char *buf, int len);
BOOL NTWriteEA (const char *file, const char *attrname, char *buf, int len);

HANDLE gethwnd (void);
void window_terminate (void);

char *cygname (char *, int);
void set_console_title (char *);

void fill_rusage (struct rusage *, HANDLE);
void add_rusage (struct rusage *, struct rusage *);

void environ_init (void);
char *winenv (const char * const *);
extern char **__cygwin_environ;

 

extern char *old_title;
extern BOOL display_title;

enum os_type {winNT, win95, win32s, unknown};

extern "C" os_type get_os_type (void);

 
extern int number_of_sockets;
void winsock_init (void);
extern "C" int cygwin32_select (int , _types_fd_set  *, _types_fd_set  *, _types_fd_set  *,
		     struct timeval *to);

 

extern "C" void setdtablesize (int);

 
extern "C" void login (struct utmp *);
extern "C" int logout (char *);






 

extern "C" {
pid_t _execve (const char *path, const char *const argv[],
                                          const char *const envp[]);
void __main (void);
void __do_global_ctors (void);
void __do_global_dtors (void);
int _rename (const char *oldpath, const char *newpath);
int lstat (const char *name, struct stat *buf);
int access (const char *fn, int flags);
int _stat (const char *name, struct stat *buf);
int  chmod (const char *a, mode_t x);
int _unlink (const char *name);
pid_t _getpid (void);
pid_t  setsid (void);
time_t time (time_t * ptr);
int _fcntl (int fd, int cmd, ...);
int dup2 (int fd, int fd2);
int dup (int fd);
int pipe (int fildes[2]);
int setpgid (int f, int p);
int tcsetpgrp (int f, int p);
int tcgetpgrp (int f);
int tcgetattr (int fd, struct termios *t);
int sigaddset (sigset_t *, const int);
int sigemptyset (sigset_t *);
int gethostname (char *name, size_t len);
int tcsetattr (int fd, int actions, const struct termios *t);
int tcdrain (int fd);
int tcdrain (int fd);
int tcsendbreak (int fd, int duration);
int tcflow (int fd, int action);

int _link (const char *, const char *);
int vfork (void);
int _kill (int, int);
int kill_pgrp (pid_t, int);
int _raise (int sig);
pid_t cwait (int *status, pid_t intpid, int flags);
pid_t waitpid (pid_t intpid, int *status, int options);
pid_t _wait (int *status);
int tcflush (int fd, int queue);
int system (const char *);

unsigned int sleep (unsigned int seconds);
unsigned int usleep (unsigned int useconds);
unsigned int alarm (unsigned int seconds);

int _gettimeofday ();

int getdtablesize (void);

extern unsigned long int htonl (unsigned long int);
extern unsigned short int htons (unsigned short int);
};

# 15 "net.cc" 2

# 1 "include/netdb.h" 1
 

 



























































extern "C" {


 





   
struct	hostent {
	const char	*h_name;	 
	char	**h_aliases;	 
	short	h_addrtype;	 
	short	h_length;	 
	char	**h_addr_list;	 

};

 




struct	netent {
	char		*n_name;	 
	char		**n_aliases;	 
	short		n_addrtype;	 
	unsigned long	n_net;		 
};

struct	servent {
	char	*s_name;	 
	char	**s_aliases;	 
	short   s_port;		 
	char	*s_proto;	 
};

struct	protoent 
{
  char	*p_name;	 
  char	**p_aliases;	 
  short	p_proto;	 
};

struct rpcent {
	char	*r_name;	 
	char	**r_aliases;	 
	int	r_number;	 
};

 





extern int h_errno;













# 161 "include/netdb.h"



};




# 16 "net.cc" 2

# 1 "include/sys/socket.h" 1



# 1 "include/features.h" 1
 
# 4 "include/sys/socket.h" 2

# 1 "include/cygwin32/socket.h" 1




extern "C" {


struct sockaddr {
  unsigned short	sa_family;	 
  char			sa_data[14];	 
};

# 1 "include/asm/socket.h" 1



# 1 "include/cygwin32/if.h" 1




extern "C" {



# 1 "include/sys/socket.h" 1
# 37 "include/sys/socket.h"

# 9 "include/cygwin32/if.h" 2


 








 






struct ifreq 
{

        union
        {
                char    ifrn_name[16 ];             
        } ifr_ifrn;

        union {
                struct  sockaddr ifru_addr;
                struct  sockaddr ifru_broadaddr;
                struct  sockaddr ifru_netmask;
                short   ifru_flags;
                int     ifru_metric;
                int     ifru_mtu;
        } ifr_ifru;
};







 






struct ifconf
{
        int     ifc_len;                         
        union
        {
                caddr_t ifcu_buf;
                struct  ifreq *ifcu_req;
        } ifc_ifcu;
};




};



# 4 "include/asm/socket.h" 2





















 
















 

                                                                       











# 13 "include/cygwin32/socket.h" 2

# 1 "include/cygwin32/sockios.h" 1
 
# 14 "include/cygwin32/socket.h" 2

# 1 "include/cygwin32/uio.h" 1
 
# 15 "include/cygwin32/socket.h" 2



struct linger {
  unsigned short 			l_onoff;	 
 unsigned short			l_linger;	 
};

struct msghdr 
{
	void	*	msg_name;	 
	int		msg_namelen;	 
	struct iovec *	msg_iov;	 
	int 		msg_iovlen;	 
	void 	*	msg_accrights;	 
	int		msg_accrightslen;	 
};

 






					 
					 
					 
					 

 
 























 























 


 




 








 




 




 










 
 


 



 





};



# 5 "include/sys/socket.h" 2




extern "C"
{


# 31 "include/sys/socket.h"



};



# 17 "net.cc" 2

# 1 "registry.h" 1
 









class reg_key
{
  HKEY key_;

public:

  int fillone_string (char *dst, const char *name, const char *def, int max);
  int setone_string (const char *src, const char *name);
  int setone_int (const char *key, int val);
  int getone_string (char *dst, const char *name, int len);

  void init (const char *name, HKEY r, REGSAM access);
  int open(const char *name, HKEY r, REGSAM access);

  void close();

  reg_key (reg_key &parent, const char *name, REGSAM access = (0xf003fL) );
  reg_key ();
  HKEY get_key ();

  int get_int (const char *,int def);
  int get_string (const char *, char *buf, size_t len, const char *def);
  int set_string (const char *,const char *);
  int set_int (const char *,int val);
  void kill (const char *child);

  ~reg_key ();
};

class reg_session
{
  reg_key majorkey_;
  reg_key minorkey_;
  reg_key versionkey_;
  reg_key vminorkey_;

public:
  reg_session (HKEY key = ((HKEY)0x80000001) , REGSAM access = (0xf003fL) );
  ~reg_session ();
  reg_key &get_key ();
};
# 18 "net.cc" 2




# 1 "include/mywinsock.h" 1
 














# 155 "include/mywinsock.h"


 


typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

 



typedef u_int           SOCKET;

 











 









 










 














                                         



 


 





 




# 247 "include/mywinsock.h"

 



# 260 "include/mywinsock.h"


# 270 "include/mywinsock.h"










 




 














 















 








 







 





                                         

 





 






 


struct in_addr {
        union {
                struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { u_short s_w1,s_w2; } S_un_w;
                u_long S_addr;
        } S_un;

                                 

                                 

                                 

                                 

                                 

                                 
};

 


























 


struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};




typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
        char                    szDescription[256 +1];
        char                    szSystemStatus[128 +1];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char   *              lpVendorInfo;
} WSADATA;

typedef WSADATA   *LPWSADATA;

 




 






 








 




 
























 











 



struct sockproto {
        u_short sp_family;               
        u_short sp_protocol;             
};

 























 










 




 









 




 









 




 









 








































 






 


 


 


 


 


 


extern "C" {










int     shutdown (SOCKET s, int how);

# 702 "include/mywinsock.h"



}


 
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr *PSOCKADDR;
typedef struct sockaddr   *LPSOCKADDR;

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in   *LPSOCKADDR_IN;

typedef struct linger LINGER;
typedef struct linger *PLINGER;
typedef struct linger   *LPLINGER;

typedef struct in_addr IN_ADDR;
typedef struct in_addr *PIN_ADDR;
typedef struct in_addr   *LPIN_ADDR;

typedef struct _types_fd_set  FD_SET;
typedef struct _types_fd_set  *PFD_SET;
typedef struct _types_fd_set    *LPFD_SET;

typedef struct hostent HOSTENT;
typedef struct hostent *PHOSTENT;
typedef struct hostent   *LPHOSTENT;

typedef struct servent SERVENT;
typedef struct servent *PSERVENT;
typedef struct servent   *LPSERVENT;

typedef struct protoent PROTOENT;
typedef struct protoent *PPROTOENT;
typedef struct protoent   *LPPROTOENT;

typedef struct timeval TIMEVAL;
typedef struct timeval *PTIMEVAL;
typedef struct timeval   *LPTIMEVAL;

 







 




 





 





 





 








extern "C" 
{
  int    WSAStartup(int wVersionRequired, LPWSADATA lpWSAData);
  int    WSAGetLastError(void);
    struct protoent  *  getprotobyname(const char  * name);
    struct protoent  *  getprotobynumber(int number);
     char  *  inet_ntoa (struct in_addr in);
  unsigned long   inet_addr (const char   * cp);

  int    sendto (SOCKET s, const char  * buf, int len, int flags,
		      const struct sockaddr  *to, int tolen);

  SOCKET     socket (int af, int type, int protocol);
  int   recvfrom (SOCKET s, char * buf, int len, int flags,
		       struct sockaddr  *from, int * fromlen);

  int   setsockopt (SOCKET s, int level, int optname,
			 const char * optval, int optlen);

    struct servent *  getservbyname(const char * name,
					const char * proto);

    struct servent *  getservbyport(int port,
					const char * proto);

  struct hostent  *   gethostbyname(const char  * name);
  struct hostent  *   gethostbyaddr(const char  * addr, int, int);
int    connect (SOCKET s, const struct sockaddr  *name, int namelen);
int    recv (SOCKET s, char  * buf, int len, int flags);
int    send (SOCKET s, const char * buf, int len, int flags);
int     bind (SOCKET s, const struct sockaddr   *addr, int namelen);
int     listen (SOCKET s, int backlog);
int     getsockname (SOCKET s, struct sockaddr   *name, int   * namelen);
SOCKET     accept (SOCKET s, struct sockaddr   *addr,int   *addrlen);
int     closesocket (SOCKET s);
int     getpeername (SOCKET s, struct sockaddr   *name, int   * namelen);
int     WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg, long lEvent);
extern int     __WSAFDIsSet(SOCKET, _types_fd_set    *);

int     select (int nfds, _types_fd_set    *readfds, _types_fd_set    *writefds,
                       _types_fd_set    *exceptfds, const struct timeval   *timeout);

int     WSACleanup (void);
int     WSACancelBlockingCall(void);
int     ioctlsocket (SOCKET s, long cmd, u_long   *argp);
int     getsockopt (SOCKET s, int level, int optname,
                           char   * optval, int   *optlen);
SOCKET     rcmd (char **ahost, unsigned short inport, char *locuser,
			   char *remuser, char *cmd, SOCKET *fd2p);
SOCKET     rresvport (int *port);
SOCKET     rexec(char **host, unsigned short port, char *user,
			   char *passwd, char *cmd, SOCKET *fd2p);
};
# 22 "net.cc" 2


 

int number_of_sockets = 0;

extern "C" {
int h_errno;
};

 

HANDLE wsock32;

 
int (*i_WSAAsyncSelect) (SOCKET s, HWND hWnd, u_int wMsg, long lEvent)  ;
int (*i_WSACleanup) (void)  ;
int (*i_WSAGetLastError) (void)  ;
int (*i_WSAStartup) (int wVersionRequired, LPWSADATA lpWSAData)  ;
int (*i___WSAFDIsSet) (SOCKET, _types_fd_set  *)  ;
SOCKET (*i_accept) (SOCKET s, struct sockaddr *addr,int *addrlen)  ;
int (*i_bind) (SOCKET s, const struct sockaddr *addr, int namelen)  ;
int (*i_closesocket) (SOCKET s)  ;
int (*i_connect) (SOCKET s, const struct sockaddr *name, int namelen)  ;
struct hostent * (*i_gethostbyaddr) (const char * addr, int, int)  ;
struct hostent * (*i_gethostbyname) (const char * name)  ;
int (*i_getpeername) (SOCKET s, struct sockaddr *name, int * namelen)  ;
struct protoent * (*i_getprotobyname) (const char * name)  ;
struct protoent * (*i_getprotobynumber) (int number)  ;
struct servent * (*i_getservbyname) (const char * name,	const char * proto)  ;
struct servent * (*i_getservbyport) (int port, const char * proto)  ;
int (*i_getsockname) (SOCKET s, struct sockaddr *name, int * namelen)  ;
int (*i_getsockopt) (SOCKET s, int level, int optname,
                     char * optval, int *optlen)  ;
unsigned long (*i_inet_addr) (const char * cp)  ;
char * (*i_inet_ntoa) (struct in_addr in)  ;
int (*i_ioctlsocket) (SOCKET s, long cmd, u_long *argp)  ;
int (*i_listen) (SOCKET s, int backlog)  ;
int (*i_recv) (SOCKET s, char * buf, int len, int flags)  ;
int (*i_recvfrom) (SOCKET s, char * buf, int len, int flags,
		   struct sockaddr  *from, int * fromlen)  ;
int (*i_select) (int nfds, _types_fd_set  *readfds, _types_fd_set  *writefds,
                 _types_fd_set  *exceptfds, const struct timeval *timeout)  ;
int (*i_send) (SOCKET s, const char * buf, int len, int flags)  ;
int (*i_sendto) (SOCKET s, const char  * buf, int len, int flags,
		 const struct sockaddr  *to, int tolen)  ;
int (*i_setsockopt) (SOCKET s, int level, int optname,
		     const char * optval, int optlen)  ;
int (*i_shutdown) (SOCKET s, int how)  ;
SOCKET (*i_socket) (int af, int type, int protocol)  ;

 
SOCKET (*i_rcmd) (char **ahost, unsigned short inport, char *locuser,
		  char *remuser, char *cmd, SOCKET *fd2p)  ;
SOCKET (*i_rexec) (char **host, unsigned short port, char *user,
		   char *passwd, char *cmd, SOCKET *fd2p)  ;
SOCKET (*i_rresvport) (int *port)  ;

 
 
void
winsock_init ()
{
  WSADATA p;
  int res;

  if ((wsock32 = LoadLibraryA  ("wsock32.dll")) == __null )
    api_fatal ("Can't load wsock32.dll! Have you installed TCP/IP?\n");





  if (((int (*)())i_WSAAsyncSelect  = GetProcAddress (wsock32, "WSAAsyncSelect")) == __null ) {	small_printf ("Can't link to %s\n", "WSAAsyncSelect");	ExitProcess (1);	} 
  if (((int (*)())i_WSACleanup  = GetProcAddress (wsock32, "WSACleanup")) == __null ) {	small_printf ("Can't link to %s\n", "WSACleanup");	ExitProcess (1);	} 
  if (((int (*)())i_WSAGetLastError  = GetProcAddress (wsock32, "WSAGetLastError")) == __null ) {	small_printf ("Can't link to %s\n", "WSAGetLastError");	ExitProcess (1);	} 
  if (((int (*)())i_WSAStartup  = GetProcAddress (wsock32, "WSAStartup")) == __null ) {	small_printf ("Can't link to %s\n", "WSAStartup");	ExitProcess (1);	} 
  if (((int (*)())i___WSAFDIsSet  = GetProcAddress (wsock32, "__WSAFDIsSet")) == __null ) {	small_printf ("Can't link to %s\n", "__WSAFDIsSet");	ExitProcess (1);	} 
  if (((int (*)())i_accept  = GetProcAddress (wsock32, "accept")) == __null ) {	small_printf ("Can't link to %s\n", "accept");	ExitProcess (1);	} 
  if (((int (*)())i_bind  = GetProcAddress (wsock32, "bind")) == __null ) {	small_printf ("Can't link to %s\n", "bind");	ExitProcess (1);	} 
  if (((int (*)())i_closesocket  = GetProcAddress (wsock32, "closesocket")) == __null ) {	small_printf ("Can't link to %s\n", "closesocket");	ExitProcess (1);	} 
  if (((int (*)())i_connect  = GetProcAddress (wsock32, "connect")) == __null ) {	small_printf ("Can't link to %s\n", "connect");	ExitProcess (1);	} 
  if (((int (*)())i_gethostbyaddr  = GetProcAddress (wsock32, "gethostbyaddr")) == __null ) {	small_printf ("Can't link to %s\n", "gethostbyaddr");	ExitProcess (1);	} 
  if (((int (*)())i_gethostbyname  = GetProcAddress (wsock32, "gethostbyname")) == __null ) {	small_printf ("Can't link to %s\n", "gethostbyname");	ExitProcess (1);	} 
  if (((int (*)())i_getpeername  = GetProcAddress (wsock32, "getpeername")) == __null ) {	small_printf ("Can't link to %s\n", "getpeername");	ExitProcess (1);	} 
  if (((int (*)())i_getprotobyname  = GetProcAddress (wsock32, "getprotobyname")) == __null ) {	small_printf ("Can't link to %s\n", "getprotobyname");	ExitProcess (1);	} 
  if (((int (*)())i_getprotobynumber  = GetProcAddress (wsock32, "getprotobynumber")) == __null ) {	small_printf ("Can't link to %s\n", "getprotobynumber");	ExitProcess (1);	} 
  if (((int (*)())i_getservbyname  = GetProcAddress (wsock32, "getservbyname")) == __null ) {	small_printf ("Can't link to %s\n", "getservbyname");	ExitProcess (1);	} 
  if (((int (*)())i_getservbyport  = GetProcAddress (wsock32, "getservbyport")) == __null ) {	small_printf ("Can't link to %s\n", "getservbyport");	ExitProcess (1);	} 
  if (((int (*)())i_getsockname  = GetProcAddress (wsock32, "getsockname")) == __null ) {	small_printf ("Can't link to %s\n", "getsockname");	ExitProcess (1);	} 
  if (((int (*)())i_getsockopt  = GetProcAddress (wsock32, "getsockopt")) == __null ) {	small_printf ("Can't link to %s\n", "getsockopt");	ExitProcess (1);	} 
  if (((int (*)())i_inet_addr  = GetProcAddress (wsock32, "inet_addr")) == __null ) {	small_printf ("Can't link to %s\n", "inet_addr");	ExitProcess (1);	} 
  if (((int (*)())i_inet_ntoa  = GetProcAddress (wsock32, "inet_ntoa")) == __null ) {	small_printf ("Can't link to %s\n", "inet_ntoa");	ExitProcess (1);	} 
  if (((int (*)())i_ioctlsocket  = GetProcAddress (wsock32, "ioctlsocket")) == __null ) {	small_printf ("Can't link to %s\n", "ioctlsocket");	ExitProcess (1);	} 
  if (((int (*)())i_listen  = GetProcAddress (wsock32, "listen")) == __null ) {	small_printf ("Can't link to %s\n", "listen");	ExitProcess (1);	} 
  if (((int (*)())i_recv  = GetProcAddress (wsock32, "recv")) == __null ) {	small_printf ("Can't link to %s\n", "recv");	ExitProcess (1);	} 
  if (((int (*)())i_recvfrom  = GetProcAddress (wsock32, "recvfrom")) == __null ) {	small_printf ("Can't link to %s\n", "recvfrom");	ExitProcess (1);	} 
  if (((int (*)())i_select  = GetProcAddress (wsock32, "select")) == __null ) {	small_printf ("Can't link to %s\n", "select");	ExitProcess (1);	} 
  if (((int (*)())i_send  = GetProcAddress (wsock32, "send")) == __null ) {	small_printf ("Can't link to %s\n", "send");	ExitProcess (1);	} 
  if (((int (*)())i_sendto  = GetProcAddress (wsock32, "sendto")) == __null ) {	small_printf ("Can't link to %s\n", "sendto");	ExitProcess (1);	} 
  if (((int (*)())i_setsockopt  = GetProcAddress (wsock32, "setsockopt")) == __null ) {	small_printf ("Can't link to %s\n", "setsockopt");	ExitProcess (1);	} 
  if (((int (*)())i_shutdown  = GetProcAddress (wsock32, "shutdown")) == __null ) {	small_printf ("Can't link to %s\n", "shutdown");	ExitProcess (1);	} 
  if (((int (*)())i_socket  = GetProcAddress (wsock32, "socket")) == __null ) {	small_printf ("Can't link to %s\n", "socket");	ExitProcess (1);	} 

  res = (*i_WSAStartup) ((2<<8) |2, &p);

  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "res %d\n"   , __PRETTY_FUNCTION__ ,res  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "wVersion %d\n"   , __PRETTY_FUNCTION__ ,p.wVersion  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "wHighVersion %d\n"   , __PRETTY_FUNCTION__ ,p.wHighVersion  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "szDescription %s\n"   , __PRETTY_FUNCTION__ ,p.szDescription  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "szSystemStatus %s\n"   , __PRETTY_FUNCTION__ ,p.szSystemStatus  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "iMaxSockets %d\n"   , __PRETTY_FUNCTION__ ,p.iMaxSockets  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "iMaxUdpDg %d\n"   , __PRETTY_FUNCTION__ ,p.iMaxUdpDg  ); })  ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "lpVendorInfo %d\n"   , __PRETTY_FUNCTION__ ,p.lpVendorInfo  ); })  ;

  if (0x8004667e   != (0x80000000 |(((long)sizeof(  u_long )& 0x7f )<<16)|( 'f' <<8)|  126 )  )
    ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "****************  FIONBIO  != REAL_FIONBIO\n"    , __PRETTY_FUNCTION__  ); })  ;

  myself->process_state |= PID_SOCKETS_USED;

  return;
  mark ("net.cc",143) ;
}

 
extern "C"
unsigned long int
htonl (unsigned long int x)
{
  mark ("net.cc",151) ;
  return   ((((x & 0x000000ffU) << 24) | 
	     ((x & 0x0000ff00U) <<  8) | 
	     ((x & 0x00ff0000U) >>  8) | 
	     ((x & 0xff000000U) >> 24)));
}

 
extern "C"
unsigned long int
ntohl (unsigned long int x)
{
  return htonl (x);
}

 
extern "C"
unsigned short
htons (unsigned short x)
{
  mark ("net.cc",171) ;
  return   ((((x & 0x000000ffU) << 8) | 
	     ((x & 0x0000ff00U) >> 8)));
}

 
extern "C"
unsigned short
ntohs (unsigned short x)
{
  return htons (x);
}

 
static void
dump_protoent (struct protoent *p)
{
  if (p)
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "protoent %s %x %x\n"   , __PRETTY_FUNCTION__ ,p->p_name, p->p_aliases, p->p_proto  ); })  ;
    }
}

 
extern "C"
char *
cygwin32_inet_ntoa (struct in_addr in) 
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  char *res = (*i_inet_ntoa) (in);
   ;
  return res;
}

 
extern "C"
unsigned long
cygwin32_inet_addr (const char *cp) 
{ 
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  unsigned long res = (*i_inet_addr) (cp);
   ;
  return res;
}

 



extern "C"
unsigned long
inet_netof (struct in_addr in)
{
  unsigned long i, res;

   ;

  i = ntohl (in.S_un.S_addr );
  if ((((long)( i ) & 0x80000000) == 0) )
    res = (i & 0xff000000 ) >> 24 ;
  else if ((((long)( i ) & 0xc0000000) == 0x80000000) )
    res = (i & 0xffff0000 ) >> 16 ;
  else
    res = (i & 0xffffff00 ) >> 8 ;

   ;

  return res;
}

 



extern "C"
struct in_addr
inet_makeaddr (int net, int lna)
{
  unsigned long i;
  struct in_addr in;

   ;

  if (net < 128 )
    i = (net << 24 ) | (lna & 0x00ffffff );
  else if (net < 65536 )
    i = (net << 16 ) | (lna & 0x0000ffff );
  else if (net < 0x1000000)
    i = (net << 8 ) | (lna & 0x000000ff );
  else
    i = net | lna;

  in.S_un.S_addr  = htonl (i);

   ;

  return in;
}

struct tl 
{
  int w;
  const char *s;
  int e;
};

static struct tl errmap[] =
{
 {(10000 +35) , "WSAEWOULDBLOCK", 11  },
 {(10000 +36) , "WSAEINPROGRESS", 119 },
 {(10000 +37) , "WSAEALREADY", 120 },
 {(10000 +38) , "WSAENOTSOCK", 108 },
 {(10000 +39) , "WSAEDESTADDRREQ", 121 },
 {(10000 +40) , "WSAEMSGSIZE", 122 },
 {(10000 +41) , "WSAEPROTOTYPE", 107 },
 {(10000 +42) , "WSAENOPROTOOPT", 109 },
 {(10000 +43) , "WSAEPROTONOSUPPORT", 123 },
 {(10000 +44) , "WSAESOCKTNOSUPPORT", 124 },
 {(10000 +45) , "WSAEOPNOTSUPP", 95 },
 {(10000 +46) , "WSAEPFNOSUPPORT", 96 },
 {(10000 +47) , "WSAEAFNOSUPPORT", 106 },
 {(10000 +48) , "WSAEADDRINUSE", 112 },
 {(10000 +49) , "WSAEADDRNOTAVAIL", 125 },
 {(10000 +50) , "WSAENETDOWN", 115 },
 {(10000 +51) , "WSAENETUNREACH", 114 },
 {(10000 +52) , "WSAENETRESET", 126 },
 {(10000 +53) , "WSAECONNABORTED", 113 },
 {(10000 +54) , "WSAECONNRESET", 104 },
 {(10000 +55) , "WSAENOBUFS", 105 },
 {(10000 +56) , "WSAEISCONN", 127 },
 {(10000 +57) , "WSAENOTCONN", 128 },
 {(10000 +58) , "WSAESHUTDOWN", 110 },
 {(10000 +59) , "WSAETOOMANYREFS", 129 },
 {(10000 +60) , "WSAETIMEDOUT", 116 },
 {(10000 +61) , "WSAECONNREFUSED", 111 },
 {(10000 +62) , "WSAELOOP", 92 },
 {(10000 +63) , "WSAENAMETOOLONG", 91 },
 {(10000 +64) , "WSAEHOSTDOWN", 117 },
 {(10000 +65) , "WSAEHOSTUNREACH", 118 },
 {(10000 +66) , "WSAENOTEMPTY", 90 },
 {(10000 +67) , "WSAEPROCLIM", 130 },
 {(10000 +68) , "WSAEUSERS", 131 },
 {(10000 +69) , "WSAEDQUOT", 132 },
 {(10000 +70) , "WSAESTALE", 133 },
 {(10000 +71) , "WSAEREMOTE", 66 },
 {(10000 +22) , "WSAEINVAL", 22 },
 {(10000 +14) , "WSAEFAULT", 14 },
 { 0}
};

 
static void
set_winsock_errno ()
{
  int i;
  int why  = (*i_WSAGetLastError) ();
  for (i = 0; errmap[i].w != 0; ++i)
    if (why == errmap[i].w)
      break;

  if (errmap[i].w != 0)
    {
      ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d (%s) -> %d\n"   , __PRETTY_FUNCTION__ ,why, errmap[i].s, errmap[i].e  ); })  ;

      (_impure_ptr->_errno = ( errmap[i].e )) ;
    }
  else
    {
      ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "unknown error %d!!\n"   , __PRETTY_FUNCTION__ ,why  ); })  ;
      (_impure_ptr->_errno = ( 1  )) ;
    }
}

static struct tl host_errmap[] =
{
  {(10000 +1001) , "WSAHOST_NOT_FOUND", 1 },
  {(10000 +1002) , "WSATRY_AGAIN", 2 },
  {(10000 +1003) , "WSANO_RECOVERY", 3 },
  {(10000 +1004) , "WSANO_DATA", 4 },
  { 0}
};

 
static void
set_host_errno ()
{
  int i;

  int why = (*i_WSAGetLastError) ();
  for (i = 0; i < host_errmap[i].w != 0; ++i)
    if (why == host_errmap[i].w)
      break;

  if (host_errmap[i].w != 0)
    h_errno = host_errmap[i].e;
  else
    h_errno = -1 ;
}

 
extern "C"
struct protoent *
cygwin32_getprotobyname (const char *p)
{
  mark ("net.cc",381) ;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  struct protoent *res = (*i_getprotobyname) (p);
  if (!res)
    set_winsock_errno ();

  dump_protoent (res);
   ;
  return res;
}

 
extern "C"
struct protoent *
cygwin32_getprotobynumber (int number)
{
  mark ("net.cc",401) ;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  struct protoent *res = (*i_getprotobynumber) (number);
  if (!res)
    set_winsock_errno ();

  dump_protoent (res);
   ;
  return res;
}

 
extern "C"
int
cygwin32_socket (int af, int type, int protocol)
{
  int res = -1;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  pinfo *p = myself;
  SOCKET soc, newsock;

  int fd = p->hmap.find_unused_handle (0);

  if (fd < 0)
    {
      (_impure_ptr->_errno = ( 89  )) ;
      goto done;
    }

  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "socket (%d, %d, %d);\n"   , __PRETTY_FUNCTION__ ,af, type, protocol  ); })  ;

  soc = (*i_socket) (af, type, protocol);

  if (soc == (SOCKET)(~0) )
    {
      set_winsock_errno ();
      goto done;
    }

  if (DuplicateHandle (GetCurrentProcess(), (HANDLE) soc,
			 GetCurrentProcess(), (HANDLE *) &newsock,
			 0, 1 , (2) ))
    {
      (*i_closesocket) (soc);
      soc = newsock;
    }
  else
    small_printf ("cygwin32_socket: DuplicateHandle failed %d\n", GetLastError ());

  fhandler_socket *h;
  char *name;
  if(af == 2 )
      name = ( type == 1  ? "/dev/tcp" : "/dev/udp");
  else
      name = ( type == 1  ? "/dev/streamsocket" : "/dev/dgsocket");
    
  p->hmap.vec[fd].h =h = new (&p->hmap.vec[fd].item) fhandler_socket(soc, name);
  res = fd;

done:
   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = socket (%d, %d, %d);\n"   , __PRETTY_FUNCTION__ ,res, af, type, protocol  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_sendto (int fd, 
		 const void *buf,
		 int len,
		 unsigned int flags,
		 const struct sockaddr *to, 
		 int tolen)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  int res = (*i_sendto) (h->get_socket(), (const char *)buf, len, flags, to, tolen);
  if (res == (-1) ) {
    set_winsock_errno ();
    res = -1;
  }
   ;
  return res;
}

 
extern "C"
int
cygwin32_recvfrom (int fd, 
		   char *buf,
		   int len, 
		   int flags, 
		   struct sockaddr *from,
		   int *fromlen)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "recvfrom %d\n"   , __PRETTY_FUNCTION__ ,h->get_socket ()  ); })  ;
  int res = (*i_recvfrom) (h->get_socket (), buf, len, flags, from, fromlen);
  if (res == (-1) ) {
    set_winsock_errno ();
    res = -1;
  }

   ;
  return res;
}

 
fhandler_socket *
get (int fd)
{
  if (myself->hmap.not_open ( fd ) )
    {
      (_impure_ptr->_errno = ( 22  )) ;
      return 0;
    }
  
  return myself->hmap.vec[fd].h->is_socket ();
}

 
extern "C"
int
cygwin32_setsockopt (int fd, 
		     int level,
		     int optname,
		     const void *optval, 
		     int optlen)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  fhandler_socket *h = get (fd);
  int res = -1;
  const char *name = "error";
  if (h) 
    {
      switch (optname)
	{
	case 0x0001       :name="SO_DEBUG";
	case 0x0002  :name="SO_ACCEPTCONN";
	case 0x0004   :name="SO_REUSEADDR";
	case 0x0008   :name="SO_KEEPALIVE";
	case 0x0010   :name="SO_DONTROUTE";
	case 0x0020   :name="SO_BROADCAST";
	case 0x0040 :name="SO_USELOOPBACK";
	case 0x0080     :name="SO_LINGER";
	case 0x0100  :name="SO_OOBINLINE";
	}
      
      res = (*i_setsockopt) (h->get_socket (), level, optname, (const char *)optval, optlen);
      
      if (optlen == 4)
	{
	  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "setsockopt optval=%x\n"   , __PRETTY_FUNCTION__ ,*(long *)optval  ); })  ;
	}
      if (res)
	set_winsock_errno ();
    }

   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = setsockopt (%d, %d, %x (%s), %x, %d);\n"   , __PRETTY_FUNCTION__ ,res,
		 fd, 
		 level, optname,name, optval, optlen  ); })  ;

  return res;
}

 
extern "C"
int
cygwin32_getsockopt (int fd, 
		     int level,
		     int optname,
		     void *optval, 
		     int *optlen)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  fhandler_socket *h = get (fd);
  int res = -1;
  const char *name = "error";
  if (h) 
    {
      switch (optname)
	{
	case 0x0001       :name="SO_DEBUG";
	case 0x0002  :name="SO_ACCEPTCONN";
	case 0x0004   :name="SO_REUSEADDR";
	case 0x0008   :name="SO_KEEPALIVE";
	case 0x0010   :name="SO_DONTROUTE";
	case 0x0020   :name="SO_BROADCAST";
	case 0x0040 :name="SO_USELOOPBACK";
	case 0x0080     :name="SO_LINGER";
	case 0x0100  :name="SO_OOBINLINE";
	}
      
      res = (*i_getsockopt) (h->get_socket (), level, optname, ( char *)optval, (int *)optlen);
      
      if (res)
	set_winsock_errno ();
    }

   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = getsockopt (%d, %d, %x (%s), %x, %d);\n"   , __PRETTY_FUNCTION__ ,res,
		  fd, 
		  level, optname,name, optval, optlen  ); })  ;

  return res;
}

 
extern "C"
int
cygwin32_connect (int fd,
		  const struct sockaddr * name,
		  int namelen)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  int res;
  fhandler_socket *s = get (fd);
  if (!s)
    {
      res = -1;
    }
  else
    {
      res = (*i_connect) (s->get_socket (), name, namelen);
      if (res)
        set_winsock_errno ();
       ;
    }
  return res;
}

 
extern "C"
struct servent *
cygwin32_getservbyname (const char *name, const char *proto)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  struct servent *p = (*i_getservbyname) (name, proto);
  if (!p)
    set_winsock_errno ();

  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%x = getservbyname (%s, %s);\n"   , __PRETTY_FUNCTION__ ,p, name, proto  ); })  ;

   ;
  return p;
}

 
extern "C"
struct servent *
cygwin32_getservbyport (int port, const char *proto)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  struct servent *p = (*i_getservbyport) (port, proto);
  if (!p)
    set_winsock_errno ();

  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%x = getservbyport (%d, %s);\n"   , __PRETTY_FUNCTION__ ,p, port, proto  ); })  ;

   ;
  return p;
}

 
extern "C"
struct hostent *
cygwin32_gethostbyname (const char *name)
{
  mark ("net.cc",704) ;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  struct hostent *ptr = (*i_gethostbyname) (name);
  if (!ptr)
    {
      set_winsock_errno ();
      set_host_errno ();
    }
  else
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "h_name %s\n"   , __PRETTY_FUNCTION__ ,ptr->h_name  ); })  ;
      h_errno = 0;
    }
   ;
  return ptr;
}

 
extern "C" 
struct hostent *
cygwin32_gethostbyaddr (const char *addr, int len, int type)
{
  mark ("net.cc",729) ;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  struct hostent *ptr = (*i_gethostbyaddr) (addr, len, type);
  if (!ptr)
    {
      set_winsock_errno ();
      set_host_errno ();
    }
  else
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "h_name %s\n"   , __PRETTY_FUNCTION__ ,ptr->h_name  ); })  ;
      h_errno = 0;
    }
   ;
  return ptr;
}

 

 
 

fhandler_socket::fhandler_socket (unsigned int s, const char *name) : fhandler_base (name)
{
  set_handle ((HANDLE) s);
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "socket id %d\n"   , __PRETTY_FUNCTION__ ,s  ); })  ;
  number_of_sockets++;
}

fhandler_socket::~fhandler_socket ()
{
  if (--number_of_sockets < 0)
    {
      number_of_sockets = 0;
      small_printf("socket count < 0!\n");
    }
}


int
fhandler_socket::write (const void *ptr, size_t len)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  int res = (*i_send) (get_socket (), (const char *) ptr, len, 0);
  if (res == (-1) )
    {
      set_winsock_errno ();
      if ((_impure_ptr->_errno)  == 113  || (_impure_ptr->_errno)  == 104 )
	_raise (13 );
    }
  return res;
}

 
int
fhandler_socket::read (void *ptr, size_t len)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  int res = (*i_recv) (get_socket (), (char *) ptr, len, 0);
  if (res == (-1) )
    {
      set_winsock_errno ();
    }
   ;
  return res;
}

 
extern "C"
int
cygwin32_accept (int fd, struct sockaddr *peer, int *len)
{
  int res = -1;
  SOCKET newsock;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  fhandler_socket *s = get (fd);
  if (s)
    {
      pinfo *p = myself;
      int res_fd = p->hmap.find_unused_handle (0);
      if (res_fd == -1)
	{
	   
	  (_impure_ptr->_errno = ( 24  )) ;
	  goto done;
	}
      res = (*i_accept) (s->get_socket (), peer, len);
      if ((SOCKET)res == (SOCKET)(SOCKET)(~0) )
	set_winsock_errno ();
      else
	{
	  if (DuplicateHandle (GetCurrentProcess(), (HANDLE) res,
			 GetCurrentProcess(), (HANDLE *) &newsock,
			 0, 1 , (2) ))
	    {
	      (*i_closesocket) (res);
	      res = newsock;
	    }
	  else
	    small_printf ("cygwin32_socket: DuplicateHandle failed %d\n", GetLastError ());

	  fhandler_socket *h;
	  p->hmap.vec[res_fd].h = h = 
               new (&p->hmap.vec[res_fd].item) fhandler_socket(res, s->get_name());
	  res = res_fd;
	}
    }
done:
   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = accept (%d, %x, %x);\n"   , __PRETTY_FUNCTION__ ,res, fd, peer, len  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_bind (int fd, struct sockaddr *my_addr, int addrlen)
{
  int res = -1;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_bind) (s->get_socket (), my_addr, addrlen);
      if (res)
	set_winsock_errno ();
    }
   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = bind (%d, %x, %d);\n"   , __PRETTY_FUNCTION__ ,res, fd, my_addr, addrlen  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_getsockname (int fd, struct sockaddr *addr, int *namelen)
{
  int res = -1;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;
  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_getsockname) (s->get_socket (), addr, namelen);
      if (res)
	set_winsock_errno ();

    }
   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = getsockname (%d, %x, %d);\n"   , __PRETTY_FUNCTION__ ,res, fd, addr, namelen  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_listen (int fd, int backlog)
{
  int res = -1;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_listen) (s->get_socket (), backlog);
      if (res)
	set_winsock_errno ();
    }
   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = listen (%d, %d);\n"   , __PRETTY_FUNCTION__ ,res, fd, backlog  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_shutdown (int fd, int how)
{
  int res = -1;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_shutdown) (s->get_socket (), how);
      if (res)
	set_winsock_errno ();
    }
   ;
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = shutdown (%d, %d);\n"   , __PRETTY_FUNCTION__ ,res, fd, how  ); })  ;
  return res;
}

 
extern "C"
void
cygwin32_herror (const char *p)
{
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "********%d*************\n"   , __PRETTY_FUNCTION__ ,950  ); })  ;
}

 
extern "C"
int
cygwin32_send (int fd, const void *buf, int len, unsigned int flags)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  int res = (*i_send) (h->get_socket (),(const char *) buf, len, flags);
  if (res == (-1) ) {
    set_winsock_errno ();
    res = -1;
  }








  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = send (%d, %x, %d, %x);\n"   , __PRETTY_FUNCTION__ ,res, fd, buf, len, flags  ); })  ;

   ;
  return res;
}

 
int
fhandler_socket::close ()
{
  int res = 0;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  if ((*i_closesocket) (get_socket ())) 
    {
      set_winsock_errno ();
      res = -1;
    }

  return res;
}

 
extern "C"
int
cygwin32_recv (int fd, void *buf, int len, unsigned int flags)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  int res = (*i_recv) (h->get_socket (), (char *)buf, len, flags);
  if (res == (-1) )
    {
      set_winsock_errno ();
      res = -1;
    }

# 1026 "net.cc"


  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = recv (%d, %x, %x, %x)\n"   , __PRETTY_FUNCTION__ ,res, fd, buf,len,flags  ); })  ;

   ;
  return res;
}

 
extern "C"
int
cygwin32_getpeername (int fd, struct sockaddr *name, int *len)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

   ;

  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "getpeername %d\n"   , __PRETTY_FUNCTION__ ,h->get_socket ()  ); })  ;
  int res = (*i_getpeername) (h->get_socket (), name, len);
  if (res)
    set_winsock_errno ();

   ;
  ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "%d = getpeername %d\n"   , __PRETTY_FUNCTION__ ,res, h->get_socket ()  ); })  ;
  return res;
}

 
extern "C"
int
getdomainname (char *domain, int len)
{
  reg_key sys;
  reg_key controlset;
  reg_key services;
  reg_key tcp;
  reg_key params;

   

  if (sys.open ((get_os_type () == win95) ? "System" : "SYSTEM",
                         ((HKEY)0x80000002) , (0x20019L) ) != 0L )
    {
      seterrno ("net.cc", 1071) ;
      return -1;
    }
  if (controlset.open ("CurrentControlSet", sys.get_key (),
                                           (0x20019L) ) != 0L )
    {
      seterrno ("net.cc", 1077) ;
      return -1;
    }
  if (services.open ("Services", controlset.get_key (),
                                            (0x20019L) ) != 0L )
    {
      seterrno ("net.cc", 1083) ;
      return -1;
    }
   






  if (tcp.open ((get_os_type () == win95) ? "MSTCP" : "Tcpip",
                       services.get_key (), (0x20019L) ) != 0L )
    {
      seterrno ("net.cc", 1096) ;
      return -1;
    }
  if (params.open ("Parameters", tcp.get_key (), (0x20019L) ) != 0L )
    {
      seterrno ("net.cc", 1101) ;
      return -1;
    }
  if (params.get_string ("Domain", domain, len, "") != 0L )
    {
      seterrno ("net.cc", 1106) ;
      return -1;
    }

  return 0;
}

 
 





static int
get_win95_ifconf (struct ifconf *ifc)
{
   
  char name[256];

   
  if (ifc->ifc_len < (2 * sizeof (struct ifreq)))
    {
      (_impure_ptr->_errno = ( 14  )) ;
      return -1;
    }

  if (gethostname (name, sizeof (name)) == (-1) )
    {
      set_winsock_errno ();
      return -1;
    }
   
  struct hostent *he = (*i_gethostbyname) (name);
  if (he == 0)
    {
      set_winsock_errno ();
      return -1;
    }

  struct sockaddr_in *sa;
  struct ifreq *ifr = ifc-> ifc_ifcu.ifcu_req ;  
   
  ifr++;
  strcpy (ifr-> ifr_ifrn.ifrn_name , "lo0");
  memset (&ifr-> ifr_ifru.ifru_addr , '\0', sizeof (ifr-> ifr_ifru.ifru_addr ));
  sa = (struct sockaddr_in *) &ifr-> ifr_ifru.ifru_addr ;
  sa->sin_family = 2 ;
  sa->sin_port = 0;
  sa->sin_addr.S_un.S_addr  = 0x7f000001 ;

   
  strcpy (ifr-> ifr_ifrn.ifrn_name , "eth0");
  memset (&ifr-> ifr_ifru.ifru_addr , '\0', sizeof (ifr-> ifr_ifru.ifru_addr ));
  sa = (struct sockaddr_in *)&ifr-> ifr_ifru.ifru_addr ;
  sa->sin_family = 2 ;
  sa->sin_port = 0;
  sa->sin_addr = *(struct in_addr *) he-> h_addr_list[0] ;

   
  ifc->ifc_len = 2 * sizeof (struct ifreq);
  return 0;
}

 
 















static int
get_winnt_ifconf (struct ifconf *ifc)
{
  return get_win95_ifconf (ifc);
}

 
 






static int
get_if_flags (struct ifreq *ifr)
{
  short flags = 0x1  | 0x20  | 0x40 ;
  struct sockaddr_in *sa = (struct sockaddr_in *) &ifr-> ifr_ifru.ifru_addr ;
  if (sa->sin_addr.S_un.S_addr  == 0x7f000001 )
      flags |= 0x8 ;
  else
      flags |= 0x2 ;
  ifr-> ifr_ifru.ifru_flags  = flags;
  return 0;
}

 
int
fhandler_socket::ioctl (int cmd, void *p)
{
  int res;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  switch (cmd)
    {
    case (0x80000000 |(((long)sizeof(  struct ifconf )& 0x7f )<<16)|( 's' <<8)|  100 )  :
      {
        struct ifconf *ifc = (struct ifconf *) p;
        if (ifc == 0)
          {
            (_impure_ptr->_errno = ( 22  )) ;
            return -1;
          }
        if (get_os_type () == winNT)
          res = get_winnt_ifconf (ifc);
        else
          res = get_win95_ifconf (ifc);
        break;
      }
    case (0x80000000 |(((long)sizeof(  struct ifreq )& 0x7f )<<16)|( 's' <<8)|  101 )  :
      {
        struct ifreq *ifr = (struct ifreq *) p;
        if (ifr == 0)
          {
            (_impure_ptr->_errno = ( 22  )) ;
            return -1;
          }
        res = get_if_flags (ifr);
        break;
      }
    case (0x80000000 |(((long)sizeof(  u_long )& 0x7f )<<16)|( 'f' <<8)|  125 )  :
      {

        res = (*i_WSAAsyncSelect) (get_socket (), gethwnd (), 0x8000 ,
		*(int *) p ? (0x01 | 0x02 | 0x04 | 0x08 | 0x10 )  : 0);
        ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "Async I/O on socket %s\n"   , __PRETTY_FUNCTION__ ,*(int *) p ? "started" : "cancelled"  ); })  ;

        set_async (*(int *) p);
        break;
      }
    default:
      {
       


        if (cmd == 0x8004667e  && *(int *)p == 0)
          (*i_WSAAsyncSelect) (get_socket (), gethwnd (), 0, 0);
        res = (*i_ioctlsocket) (get_socket (), cmd, (unsigned long *) p);
        if (res == (-1) )
            set_winsock_errno ();
        if (cmd == (int) 0x8004667e )
          {
            ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "socket is now %sblocking\n"   , __PRETTY_FUNCTION__ ,*(int *) p ? "un" : ""  ); })  ;

    	     
	    if (*(int *) p && get_async ())
	      (*i_WSAAsyncSelect) (get_socket (), gethwnd (), 0x8000 ,
		(0x01 | 0x02 | 0x04 | 0x08 | 0x10 ) );
	  }
        break;
      }
    }
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = ioctl_socket (%x, %x);\n"   , __PRETTY_FUNCTION__ ,res, cmd, p  ); })  ;
  return res;
}

 
int
fhandler_socket::fstat (struct stat *buf)
{
  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "fhandler_socket::fstat unsupported!\n"    , __PRETTY_FUNCTION__  ); })  ;
  (_impure_ptr->_errno = ( 88  )) ;
  return -1;
}

 
extern "C"
int
cygwin32_rcmd (char **ahost, unsigned short inport, char *locuser,
               char *remuser, char *cmd, int *fd2p)
{
  int res = -1;
  SOCKET newsock;
  SOCKET fd2s;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  if (!i_rcmd)
    if (((int (*)())i_rcmd  = GetProcAddress (wsock32, "rcmd")) == __null ) {	small_printf ("Can't link to %s\n", "rcmd");	ExitProcess (1);	} 

  pinfo *p = myself;
  int res_fd = p->hmap.find_unused_handle (0);
  if (res_fd == -1)
    goto done;
  if (fd2p)
    {
      *fd2p = p->hmap.find_unused_handle (res_fd + 1);
      if (*fd2p == -1)
        goto done;
    }
  res = (*i_rcmd) (ahost, inport, locuser, remuser, cmd, fd2p? &fd2s: __null );
  if (res == (SOCKET)(~0) )
    goto done;
  else
    {
      if (DuplicateHandle (GetCurrentProcess(), (HANDLE) res,
                           GetCurrentProcess(), (HANDLE *) &newsock,
                           0, 1 , (2) ))
        {
          (*i_closesocket) (res);
          res = newsock;
        }
      else
        small_printf ("DuplicateHandle failed %d\n", GetLastError ());

      fhandler_socket *h;
      p->hmap.vec[res_fd].h = h = 
          new (&p->hmap.vec[res_fd].item) fhandler_socket(res, "/dev/tcp");
      res = res_fd;
    }
  if (fd2p)
    {
      if (DuplicateHandle (GetCurrentProcess(), (HANDLE) fd2s,
                           GetCurrentProcess(), (HANDLE *) &newsock,
                           0, 1 , (2) ))
        {
          (*i_closesocket) (fd2s);
          fd2s = newsock;
        }
      else
        small_printf ("DuplicateHandle failed %d\n", GetLastError ());

      fhandler_socket *h;
      p->hmap.vec[*fd2p].h = h = 
          new (&p->hmap.vec[*fd2p].item) fhandler_socket(fd2s, "/dev/tcp");
    }
done:
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = rcmd (...);\n"   , __PRETTY_FUNCTION__ ,res  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_rresvport (int *port)
{
  int res = -1;
  SOCKET newsock;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  if (!i_rresvport)
    if (((int (*)())i_rresvport  = GetProcAddress (wsock32, "rresvport")) == __null ) {	small_printf ("Can't link to %s\n", "rresvport");	ExitProcess (1);	} 

  pinfo *p = myself;
  int res_fd = p->hmap.find_unused_handle (0);
  if (res_fd == -1)
    goto done;
  res = (*i_rresvport) (port);
  if (res == (SOCKET)(~0) )
    goto done;
  else
    {
      if (DuplicateHandle (GetCurrentProcess(), (HANDLE) res,
                           GetCurrentProcess(), (HANDLE *) &newsock,
                           0, 1 , (2) ))
        {
          (*i_closesocket) (res);
          res = newsock;
        }
      else
        small_printf ("DuplicateHandle failed %d\n", GetLastError ());

      fhandler_socket *h;
      p->hmap.vec[res_fd].h = h = 
          new (&p->hmap.vec[res_fd].item) fhandler_socket(res, "/dev/tcp");
      res = res_fd;
    }
done:
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = rresvport (%d);\n"   , __PRETTY_FUNCTION__ ,res, port? *port: 0  ); })  ;
  return res;
}

 
extern "C"
int
cygwin32_rexec (char **ahost, unsigned short inport, char *locuser,
               char *passwd, char *cmd, int *fd2p)
{
  int res = -1;
  SOCKET newsock;
  SOCKET fd2s;

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  if (!i_rexec)
    if (((int (*)())i_rexec  = GetProcAddress (wsock32, "rexec")) == __null ) {	small_printf ("Can't link to %s\n", "rexec");	ExitProcess (1);	} 

  pinfo *p = myself;
  int res_fd = p->hmap.find_unused_handle (0);
  if (res_fd == -1)
    goto done;
  if (fd2p)
    {
      *fd2p = p->hmap.find_unused_handle (res_fd + 1);
      if (*fd2p == -1)
        goto done;
    }
  res = (*i_rexec) (ahost, inport, locuser, passwd, cmd, fd2p? &fd2s: __null );
  if (res == (SOCKET)(~0) )
    goto done;
  else
    {
      if (DuplicateHandle (GetCurrentProcess(), (HANDLE) res,
                           GetCurrentProcess(), (HANDLE *) &newsock,
                           0, 1 , (2) ))
        {
          (*i_closesocket) (res);
          res = newsock;
        }
      else
        small_printf ("DuplicateHandle failed %d\n", GetLastError ());

      fhandler_socket *h;
      p->hmap.vec[res_fd].h = h = 
          new (&p->hmap.vec[res_fd].item) fhandler_socket(res, "/dev/tcp");
      res = res_fd;
    }
  if (fd2p)
    {
      if (DuplicateHandle (GetCurrentProcess(), (HANDLE) fd2s,
                           GetCurrentProcess(), (HANDLE *) &newsock,
                           0, 1 , (2) ))
        {
          (*i_closesocket) (fd2s);
          fd2s = newsock;
        }
      else
        small_printf ("DuplicateHandle failed %d\n", GetLastError ());

      fhandler_socket *h;
      p->hmap.vec[*fd2p].h = h = 
          new (&p->hmap.vec[*fd2p].item) fhandler_socket(fd2s, "/dev/tcp");
    }
done:
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = rexec (...);\n"   , __PRETTY_FUNCTION__ ,res  ); })  ;
  return res;
}

 
 
extern "C"
int
socketpair (int, int type, int, int *sb)
{
  int res = -1;
  SOCKET insock, outsock, newsock;
  pinfo *p = myself;
  struct sockaddr_in sin;
  int len = sizeof (sin);

  if ((!(( myself )->process_state &   PID_SOCKETS_USED )) )
    winsock_init ();

  sb[0] = p->hmap.find_unused_handle (0);
  if (sb[0] == -1)
    {
      (_impure_ptr->_errno = ( 24  )) ;
      goto done;
    }
  sb[1] = p->hmap.find_unused_handle (sb[0] + 1);
  if (sb[1] == -1)
    {
      (_impure_ptr->_errno = ( 24  )) ;
      goto done;
    }

   
  newsock = (*i_socket) (2 , type, 0);
  if (newsock == (SOCKET)(~0) )
    {
      set_winsock_errno ();
      goto done;
    }

   
  sin.sin_family = 2 ;
  sin.sin_port = 0;
  sin.sin_addr.S_un.S_addr  = (u_long)0x00000000 ;
  if ((*i_bind) (newsock, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      goto done;
    }

  if ((*i_getsockname) (newsock, (struct sockaddr *) &sin, &len) < 0)
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "getsockname error\n"    , __PRETTY_FUNCTION__  ); })  ;
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      goto done;
    }
  (*i_listen) (newsock, 2);

   
  outsock = (*i_socket) (2 , type, 0);
  if (outsock == (SOCKET)(~0) )
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "can't create outsock\n"    , __PRETTY_FUNCTION__  ); })  ;
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      goto done;
    }
  sin.sin_addr.S_un.S_addr  = htonl (0x7f000001 );

   
  if ((*i_connect) (outsock, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "connect error\n"    , __PRETTY_FUNCTION__  ); })  ;
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      (*i_closesocket) (outsock);
      goto done;
    }
  insock = (*i_accept) (newsock, (struct sockaddr *) &sin, &len);
  if (insock == (SOCKET)(~0) )
    {
      ({	if (strace() &((0x0040  )|1)) strace_printf("%F: "    "accept error\n"    , __PRETTY_FUNCTION__  ); })  ;
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      (*i_closesocket) (outsock);
      goto done;
    }

  (*i_closesocket) (newsock);
  res = 0;

  if (DuplicateHandle (GetCurrentProcess(), (HANDLE) insock,
                       GetCurrentProcess(), (HANDLE *) &newsock,
                       0, 1 , (2) ))
    {
      (*i_closesocket) (insock);
      insock = newsock;
    }
  else
    small_printf ("DuplicateHandle failed %d\n", GetLastError ());

  p->hmap.vec[sb[0]].h = 
          new (&p->hmap.vec[sb[0]].item) fhandler_socket(insock, "/dev/tcp");

  if (DuplicateHandle (GetCurrentProcess(), (HANDLE) outsock,
                       GetCurrentProcess(), (HANDLE *) &newsock,
                       0, 1 , (2) ))
    {
      (*i_closesocket) (outsock);
      outsock = newsock;
    }
  else
    small_printf ("DuplicateHandle failed %d\n", GetLastError ());

  p->hmap.vec[sb[1]].h = 
          new (&p->hmap.vec[sb[1]].item) fhandler_socket(outsock, "/dev/tcp");

done:
  ({	if (strace() &((0x0010  )|1)) strace_printf("%F: "    "%d = socketpair (...);\n"   , __PRETTY_FUNCTION__ ,res  ); })  ;
  return res;
}
