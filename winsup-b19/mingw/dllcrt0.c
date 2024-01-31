/*
 * dllcrt0.c
 *
 * Initialization code for DLLs.
 *
 * This code was written to interface with CRTDLL.DLL as supplied with
 * Windows NT and Windows 95, although it could, conceivably, be useful
 * under other circumstances.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *  Pedro A. Aranda gave me a clue about how to get the standard file
 *    handles, which he in turn was told by Jacob Navia.
 *  DLL support adapted from Gunther Ebert <gunther.ebert@ixos-leipzig.de>
 *
 *
 *  THIS SOFTWARE IS NOT COPYRIGHTED
 *
 *  This source code is offered for use in the public domain. You may
 *  use, modify or distribute it freely.
 *
 *  This code is distributed in the hope that it will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRENTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAMED. This includes but is not limited to warrenties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <stdio.h>
#include <io.h>
#include <process.h>
#include <windows.h>

/* NOTE: The code for initializing, as well as referencing, the standard
 * file handles and the __argv, __argc, and _environ variables has been
 * moved to a separate .c file which is included in both crt0.c and
 * dllcrt0.c. This means changes in the code doesn't have to be manually
 * synchronized, but it does lead to this not-generally-a-good-idea use
 * of include. */
#include "init.c"

/* Unlike normal crt0, I don't initialize the FPU, because the process
 * should have done that already. */


extern BOOL WINAPI DllMain(HANDLE, DWORD, LPVOID);

BOOL WINAPI
DllMainCRTStartup (HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
	BOOL bRet;
 
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        	_mingw32_init_stdhandles();
        	_mingw32_init_mainargs();

		/* From libgcc.a, calls global class constructors. */
		__main();
	}

	/*
	 * Call the user-supplied DllMain subroutine
	 * NOTE: DllMain is optional, so libmingw32.a includes a stub
	 *       which will be used if the user does not supply one.
	 */
	bRet = DllMain(hDll, dwReason, lpReserved);

	if (dwReason == DLL_PROCESS_DETACH)
	{
		/* From libgcc.a, calls global class destructors. */
		__do_global_dtors();
	}

	return bRet;
}

#ifdef	__GNUC__
/*
 * This section terminates the list of imports under GCC. If you do not
 * include this then you will have problems when linking with DLLs.
 */
asm (".section .idata$3\n" ".long 0,0,0,0,0,0,0,0");
#endif

