

/* 
 * win-e7kpc.h 	
 * 	
 * 	Win32 support for e7000pc
 * 
 * The e7000pc reserves the upper memory block (UMB) D000-D3FF 
 * as it's memory.  This is done by adding the following to 
 * config.sys:
 * DEVICE=C:\WINDOWS\HIMEM.SYS
 * DEVICE=C:\WINDOWS\EMM386.EXE 1024 RAM X=D000-D3FF FRAME=E000
 * The values may differ if:
 * 1) the computer system uses this memory for another device
 * 	(in this case, change the dip switches on the e7000pc card
 * 	to use a different address, and modify the parameters to EMM386
 * 	accordingly)
 * 2) the e7000pc card may be set to use a different address.  Check
 * 	the dip switches on the card and read the e7000pc manual
 * 	to find out how to set these values.
 */

#ifndef _WINE7KPC_H_
#define _WINE7KPC_H_

#define KERNEL
#define STRICT

#include "windefs.h"

#ifdef _WIN32s
#define GETMEM 1
#define SETMEM 2
#endif /* _WIN32s */


 /* __D000h is an absolute value; by declaring it as a NEAR variable
  * in our data segment we can take its "address" and get the
  * 16-bit absolute value.
  */

#ifndef STAND_ALONE
#define UMB_ADR 0xd0000
#define UMB_SEL _D000h /* special MSVC identifier for selector D */
#else
#define UMB_ADR 0xa0000
#define UMB_SEL _A000h /* use this value to test the UMB access code 
			* separately (no e7000pc hardware or setup required).
			* This address is the selector for VGA and will test 
			* reading and writing to the upper left corner of 
			* the display.  If the code is working properly, 
		        * you should see a line of strange pixels accross
			* the top left corner of the display.
			*/
#endif /* !STAND_ALONE */

/* ====================== Win32 defs ================================ */

#if _WIN32
 #define DllExport __declspec(dllexport)
 /* 32-bit dll entry points for w31e7kpc.dll and w95e7kpc.dll: */

#ifdef _WIN95
 int win_load_e7kpc (void);
 void win_unload_e7kpc (void);
 void win_mem_put (unsigned char *buf, int offset, int len);
 void win_mem_get (unsigned char *buf, int offset, int len);
#endif /* _WIN95 */

#ifdef _WIN32s
 int win_load_e7kpc(void);
 void win_unload_e7kpc (void);
 //int APIENTRY win_mem_put (LPCSTR buf, USHORT offset, USHORT len);
 //int APIENTRY win_mem_get (LPSTR buf, USHORT offset, USHORT len);
 int APIENTRY win_mem_put (unsigned char *buf, int offset, int len);
 int APIENTRY win_mem_get (unsigned char *buf, int offset, int len);
#endif /* _WIN32s */


#ifdef _WIN95
 /* 16-bit dll entry points for w96e7k16.dll: */
 DllExport short CALLBACK set_mem (short offset, short data);
 DllExport short CALLBACK get_mem (short offset);
#endif /* _WIN95 */
 

/* ====================== Win16 defs ================================ */

#else /* _WIN32 */


 typedef WORD SELECTOR;
 extern BYTE NEAR CDECL UMB_SEL;
 SELECTOR selUMB = (SELECTOR) &UMB_SEL;

#ifdef _WIN95
 short CALLBACK set_mem (short offset, short mem);
 short CALLBACK get_mem (short offset);
#endif /* _WIN95 */

#endif /* _WIN32 */

#endif /* _WINE7KPC_H_ */
