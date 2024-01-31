
/*
 * win-e7kpc.c
 * 
 * This code supports the reading and writing of physical memory 
 * for the Hitachi e7000-pc, by acting as a 32-bit interface to 
 * 16-bit functions defined in win-e7kpc16.c.  
 * 
 * sh.mak contains the makefile rules for building the e7000pc dlls.
 * If HOST=WIN95, _Win95 is defined, and w95e7kpc.dll is built.
 * If HOST=WIN31, _Win32s is defined, and w31e7kpc.dll is built.
 *  
 * 
 * This source is built into a 32-bit dll which handles the 32 <-> 16 bit 
 * thunks for a 16-bit dll which accesses the UMB memory used by the e7000 pc.
 * 
 * host             32-bit code       16-bit code
 * win95   gdb <--> w95e7kpc.dll <--> w95e7k16.dll
 * win32s  gdb <--> w31e7kpc.dll <--> w31e7k16.dll
 * winnt   -not supported-
 * 
 * When the e7000 pc target is selected, gdb dynamically loads the 32-bit dll 
 * (w??e7kpc.dll) based on the host's windows version.
 * The 32-bit dll intern dynamically loads the 16-bit dll (w??e7k16.dll)
 * and handles the 32<->16 bit thunks required to call the 16-bit functions.
 * 
 * Both win95 & win32s use 16-bit dlls to access the real physical 
 * memory via selectors and offsets.
 * Win95 uses "Flat thunks" to handle the 32<->16 bit translation,
 * while Win32s uses "Universal thunks".
 * WinNT does not allow access to real physical memory except through
 * virtual device drivers (VxD).  At this time, there isn't a requirement
 * to have support for NT, but this may change in the future.
 * 
 */


#include <stdio.h>
#include "win-e7kpc.h"
#include "gdbwin.h"

#define W32SUT_32
#include "windefs.h"
#include "w32sut.h"
#include "serdll32.h"
#include "serdll.h"

#define ERROR 1
#define OK 0

//#define DEBUGIFY
#define REDIRECT
#define TO_FILE
#include "debugify.h"


/* for calling kernel32 to get addresses of dll entry points */
typedef int (CALLBACK *PROC16_PFN)(int);


/* ====================== Win32s defs ================================ */
#ifdef _WIN32s
typedef BOOL (APIENTRY * PUTREGISTER) (HANDLE hModule,
				       LPCSTR lpsz16BitDLL,
				       LPCSTR lpszInitName,
				       LPCSTR lpszProcName,
				       UT32PROC * ppfn32Thunk,
				       FARPROC pfnUT32Callback,
				       LPVOID lpBuff
);
typedef VOID (APIENTRY * PUTUNREGISTER) (HANDLE hModule);

UT32PROC pfnUTProc = NULL;
PUTREGISTER pUTRegister = NULL;
PUTUNREGISTER pUTUnRegister = NULL;
int cProcessesAttached = 0;
BOOL fWin32s = FALSE;
HANDLE hKernel32 = 0;
static HANDLE hInstMe = 0;
#endif /* _WIN32s */


/* ====================== Win95 defs ================================ */
#ifdef _WIN95
// Prototype undocumented KERNEL32 functions
HINSTANCE WINAPI LoadLibrary16( PSTR );
void WINAPI FreeLibrary16( HINSTANCE );
FARPROC WINAPI GetProcAddress16( HINSTANCE, PSTR );
void __cdecl QT_Thunk(void);

PROC16_PFN pfn_set_mem = NULL;   // We don't want these as locals
PROC16_PFN pfn_get_mem = NULL;   
HINSTANCE hInstUser16=0;                  // since QT_THUNK could
static long save_sp=0;
static WORD set_mem_rc=0;                 // trash them...
static WORD mem=0;                 
static long mem_offset=0;
static long mem_parms=0;
#endif /* _WIN95 */


/* ====================== common defs ================================ */
/* we have our own versions of these inside the dll */

static int wine7k16_loaded = 0;
static int remote_debug = 0;
static int i;


/* ====================== loads & thunks ================================ */
/*
 * Set up thunking code for accessing the 16-bit dll from this 32-bit dll.
 * For Win32s, save away our instance handle in during dll initialization.
 * Load 16-bit dll in win_load_e7kpc.
 * Get addresses of dynamically loaded procesdures.
 * For Win32s, use UTRegister to load the 16-bit dll and handle the thunks.
 * For Win95, use QT_Thunk to call the 16-bit functions.
 */

/* Win32s: Dll initialization and termination */

#ifdef _WIN32s
int main(void) { return 0; }	/* bogus main to make libc happy */
/* If building the stand-alone test, don't create a dll */
#ifndef STAND_ALONE
BOOL APIENTRY 
DllMain (HANDLE hInst, DWORD dwReason, LPVOID lpReserved)
{
  hInstMe = hInst;
  DBG(("DllInit: hInstMe=x%x\n", hInstMe));

  fWin32s = (BOOL) (GetVersion () & 0x80000000);
  if (!fWin32s)
    return (FALSE);	/* this dll should only be loaded on Win32s systems */

  switch( dwReason ) 
  {
    case DLL_PROCESS_ATTACH:
      if (cProcessesAttached++)
	  return (TRUE);
      break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
       --cProcessesAttached;
       /* if (0 == cProcessesAttached)
	* then Windows is gunna unload us!!
	* Better do any last minute cleanup while we can!
	*/
      break;
  }
  return TRUE;
}
#endif /* !STAND_ALONE */
#endif /* _WIN32s */


/* Win95: Return address of 16-bit function within 16-bit dll */

#ifdef _WIN95
static PROC16_PFN getproc16(HANDLE hDll16,char* name)
{
    PROC16_PFN pfn=0;
    pfn = (PROC16_PFN) GetProcAddress16(hDll16, name);
    if (!pfn)
    {
	if (remote_debug) 
	    printf_unfiltered( "GetProcAddress16() failed!\n" );
	return 0;
    }
    return pfn;
}
#endif /* _WIN95 */


/* ============= win_load_e7kpc ============================ */

int win_load_e7kpc(void)
{

    if (wine7k16_loaded)	/* we've been here before */
       return OK;

    /* Win95: load 16-bit e7000pc dll w95e7k16.dll */
#ifdef _WIN95
    hInstUser16 = LoadLibrary16("w95e7k16.dll");
    if ( hInstUser16 < (HINSTANCE)32 )
    {
        if (remote_debug) 
	    printf_unfiltered( "LoadLibrary16() failed!\n" );
        return ERROR;
    }

    wine7k16_loaded = 1;

    pfn_set_mem = getproc16(hInstUser16, "set_mem");
    pfn_get_mem = getproc16(hInstUser16, "get_mem");
    if (!pfn_set_mem || !pfn_get_mem)
      {
	if (remote_debug) 
	    printf_unfiltered( "unable to get addrs for get_mem and get_mem!\n" );
	return ERROR;
      }
#endif /* _WIN95 */
    

      /* Win32s: set up for universal thunks; used in win31, win32s, and wfw */
#ifdef _WIN32s
      hKernel32 = LoadLibrary ("Kernel32.Dll");
      if (!hKernel32)
      {
	if (remote_debug) 
	    printf_unfiltered( "unable to load Kernel32.dll!\n" );
	return ERROR;
      }

      pUTRegister = (PUTREGISTER) GetProcAddress(hKernel32,"UTRegister");
      if (!pUTRegister)
      {
	if (remote_debug) 
	    printf_unfiltered( "GetProcAddress(..,UTRegister) failed!\n" );
	return ERROR;
      }
      pUTUnRegister = (PUTUNREGISTER) GetProcAddress(hKernel32,"UTUnRegister");
      if (!pUTUnRegister)
      {
	if (remote_debug) 
	    printf_unfiltered( "GetProcAddress(..,UTUnRegister) failed!\n" );
	return ERROR;
      }

      DBG(("Calling pUTRegister=x%x, hInstMe=x%x\n", pUTRegister, hInstMe));
      /* Win32s: load 16-bit e7000pc dll w31e7k16.dll */
      if ((*pUTRegister) (hInstMe,
	     "w31e7k16.DLL",
	     NULL,		// no init routine
	     "UTProc",		// name of 16bit dispatch routine
	     &pfnUTProc,	// Global variable to receive thunk address
	     NULL,		// no callback function
	     NULL) 		// no shared memroy
	 == FALSE)
      {
	DBG(("pfnUTProc=x%x, hInstMe=x%x\n", pfnUTProc, hInstMe));
	if (remote_debug) 
	    printf_unfiltered( "win_load_e7kpc: unable to load 16-bit dll or register UT!\n" );
	return ERROR;
      }

    wine7k16_loaded = 1;
#endif /* _WIN32s */
      

#ifdef _WINNT
    return ERROR;
#endif /* _WINNT */

    DBG(("win_load_e7kpc: Done! :-)\n"));
    return OK;
}

//============= cleanup ============================
void win_unload_e7kpc(void)
{
#ifdef _WIN95
    /* Win95: free 16-bit e7000pc dll w95e7k16.dll */
    if (hInstUser16 && wine7k16_loaded)
        FreeLibrary16 (hInstUser16);   
    hInstUser16=0;
#endif /* _WIN95 */
#ifdef _WIN32s
    /* Win32s: free 16-bit e7000pc dll w31e7k16.dll */
    if (hInstMe && pUTUnRegister && wine7k16_loaded)
	(*pUTUnRegister) (hInstMe);
    if (hKernel32)                  
	FreeLibrary (hKernel32);
    hKernel32=0;
#endif /* _WIN32s */
    wine7k16_loaded = 0;
}
    
//============= win_mem_put ============================
#ifdef _WIN95 /* Win95 uses flat thunks */
void win_mem_put (unsigned char* buf, int offset, int len)
{
    //============= trash space ==================
    char buffer[0x40];
    buffer[0] = 0;  // Make sure to use the local variable so that the
                    // compiler sets up an EBP frame
    offset-=UMB_ADR;	/* subtract off selector address */
    if (offset<0 || offset>=0x10000)
    {
	DBG(("selector offset 0x%x out of range!\n",offset));
	return;
    }
                  
    //============= write mem bytes from buf ==================
    for (i=0,mem_offset=offset; i<len; i++, mem_offset++) 
    {
#if 0	/* we only get 1 byte now :-( */
	if (len-i > 1)	
	{
	    mem=((buf[i]&0xff)<<8 | (buf[i+1]&0xff)); /* put 2 bytes */
	    i++;
	}
	else
#endif
	    mem=(buf[i]&0xff); /* put 1 byte */
	// push both 16-bit parms with one 32-bit push
	// stack should be sp->[offset mem]
	ASSERT(mem_offset>0 && mem_offset<0x10000);
	mem_parms=(mem&0xffff)|(mem_offset<<16)&0xffff0000;
	// thunk from 32 to 16-bit code in dll
	__asm 
	{
	    mov	save_sp, esp
	    mov     edx, [mem_parms]
	    push    edx
	    mov     edx, [pfn_set_mem]
	    call    QT_Thunk
	    mov	esp, save_sp
	    mov     [set_mem_rc], ax
        }
    }
}
#endif /* _WIN95 */

#ifdef _WIN32s
int APIENTRY
win_mem_put (unsigned char* buf, int offset, int len)
//FIXME! win_mem_put (LPCSTR buf, USHORT offset, USHORT len)
{
      DWORD args[3];
      PVOID translist[2];
      int rc=0;
      
      if (remote_debug) 
        printf_unfiltered( "win_mem_get: offset=x%x, len=x%x\n", offset, len);
      /* Address comes in "0xd300c", when the offset is "0x300c" */
      offset-=UMB_ADR;	/* subtract off selector address */
      DBG(("after subtract UBM_ADR=0x%x: offset=0x%x\n", UMB_ADR, offset));
      if (offset<0 || offset>=0x10000)
      {
	  DBG(("selector offset 0x%x out of range!\n",offset));
	  return -1;
      }
      args[2] = 0;
      translist[0] = &args[0];
      translist[1] = NULL;
      for (i=0; i<len; i++)
      {
        DBG(("top-o-loop: i=%d, ((DWORD)offset&oxffff=0x%x\n", i, ((DWORD)offset)&0xffff));
        args[0] = ((DWORD) (offset + i)) & 0xffff;
        args[1] = ((DWORD) buf[i]) & 0xff;
	if (remote_debug) 
	{
	    printf_unfiltered( "Calling thunk for set_mem; pfnUTProc=x%x\n",
		    pfnUTProc);
	    printf_unfiltered( "\targs: offset=x%x, data=x%x\n",
		    args[0],args[1]);
	}
      	rc = ((*pfnUTProc) (args, SETMEM, translist));
	if (rc!=0)
	    break;
      }
      return rc;
}
#endif /* _WIN32s */


//============= win_mem_get ============================
#ifdef _WIN95 /* Win95 uses flat thunks */
void win_mem_get (unsigned char* buf, int offset, int len)
{
    //============= trash space ==================
    unsigned char buffer[0x40];
    buffer[0] = 0;  // Make sure to use the local variable so that the
                    // compiler sets up an EBP frame
    offset-=UMB_ADR;	/* subtract off selector address */
    if (offset<0 || offset>=0x10000)
    {
	DBG(("selector offset 0x%x out of range!\n",offset));
	return;
    }

    //============= collect mem bytes into buf ==================
    for (i=0,mem_offset=offset; i<len; i++, mem_offset++) 
    {
	// thunk from 32 to 16-bit code in dll
	// stack should be sp->[offset]
	    //mov     edx, [mem_parms]//works as parms...
	ASSERT(mem_offset>0 && mem_offset<0x10000);
	mem_parms=(mem_offset)&0xffff;
	__asm 
	{
	    mov	save_sp, esp
	    mov     edx, [mem_parms]
	    push    edx
	    mov     edx, [pfn_get_mem]
	    call    QT_Thunk
	    mov	esp, save_sp
	    mov     [mem], ax
        }
#if 0	/* right now we only get 1 byte at a time, but may want this later.. */
	if (len-i > 1)	
	{
	    buf[i]=(unsigned char)(mem&0xff); /* get 2 bytes */
	    buf[++i]=(unsigned char)((mem>>8)&0xff);
	}
	else
#endif
	    buf[i]=(unsigned char)(mem&0xff); /* get 1 byte */
    }
}
#endif /* _WIN95 */

#ifdef _WIN32s
int APIENTRY
win_mem_get (unsigned char* buf, int offset, int len)
//FIXME! win_mem_get (LPSTR buf, USHORT offset, USHORT len)
{
      DWORD args[2];
      PVOID translist[2];
      int data=0;
      
      if (remote_debug) 
        printf_unfiltered( "win_mem_get: offset=x%x, len=x%x\n", offset, len);
      offset-=UMB_ADR;	/* subtract off selector address */
      if (offset<0 || offset>=0x10000)
      {
  	  DBG(("selector offset 0x%x out of range!\n",offset));
	  return -1;
      }
      args[1] = 0;
      translist[0] = &args[0];
      translist[1] = NULL;

      for (i=0; i<len; i++)
      {
        args[0] = ((DWORD) (offset + i)) & 0xffff;
	if (remote_debug) 
	{
	    printf_unfiltered( "Calling thunk for get_mem; pfnUTProc=x%x\n",
		    pfnUTProc);
	    printf_unfiltered( "\targs: offset=x%x\n", args[0]);
	}
      	data = ((*pfnUTProc) (args, GETMEM, translist));
	if (remote_debug) 
	    printf_unfiltered( "\tget_mem returned x%x\n",data);
        buf[i] = (unsigned char) (data & 0xff);
      }
      return 0;
}
#endif /* _WIN32s */


//============= debugging ============================
/* a way for gdb to turn on remote_debug */
void win_remote_debug(int val)
{
    remote_debug=val;
}

//============= stand-alone test code ==================
#ifdef STAND_ALONE
    static int len=20;
    static unsigned long offset=UMB_ADR+10;
    static unsigned char buf[512];
    static int j;
#ifndef _WIN32s
int main(void)

#else
int PASCAL WinMain (HINSTANCE   hinst,
			 HINSTANCE   hinstPrev,
			 LPSTR       lpszCmdLine,
			 int         cmdShow
			 )
#endif
{
    //============= trash space ==================
    unsigned char buffer[0x40];
    buffer[0] = 0;  // Make sure to use the local variable so that the
                    // compiler sets up an EBP frame
    remote_debug = 1;	/* turn on by default for testing */
#ifdef _WIN32s
    hInstMe = hinst;
#endif

    if (remote_debug) 
	printf_unfiltered("Testing memory at offset=%d, len=%d\n", offset,len);
    if (remote_debug) 
	printf_unfiltered("loading dll..\n"); 
    if (win_load_e7kpc() == ERROR)
    {
        if (remote_debug) 
	    printf_unfiltered("ERROR! win_load_e7kpc failed\n"); 
        win_unload_e7kpc();
        return ERROR;
    }
    
    //============= do test ============================
    if (remote_debug) 
	printf_unfiltered("Initializing memory to: \n"); 
    for (j=0; j<len; j++) 
    {
	buf[j] = 'a'+j;
        if (remote_debug) 
	    printf_unfiltered("%x",buf[j]); 
    }
    if (remote_debug) 
	printf_unfiltered("\n"); 

    if (remote_debug) 
	printf_unfiltered("Calling win_mem_put(x%x,%d,%d)...\n",buf,offset,len);
    win_mem_put(buf,offset,len);
    if (remote_debug) 
	printf_unfiltered("Calling win_mem_get(x%x,%d,%d)...\n",buf,offset,len);
    win_mem_get(buf,offset,len);

    if (remote_debug) 
	printf_unfiltered("Testing that we read what we wrote...\n"); 
    for (j=0; j<len; j++) 
    {
	if ('a'+j != buf[j])
	    if (remote_debug) 
		printf_unfiltered("ERROR! j=%d, expected=%x, read=%x\n", 
		    j,'a'+j,buf[j]);
    }

    if (remote_debug) 
	printf_unfiltered("unloading dll..\n"); 
    win_unload_e7kpc();

    if (remote_debug) 
	printf_unfiltered("Done!\n"); 

    return 0;
}
#endif /* STAND_ALONE */
