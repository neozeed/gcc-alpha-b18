/*
 * crt0.c
 *
 * Source code for the startup proceedures used by all programs. This code
 * is compiled to make crt0.o, which should be located in the library path.
 *
 * This code was written to interface with CRTDLL.DLL as supplied with
 * Windows NT and Windows 95, although it could, conceivably, be useful
 * under other circumstances.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *  Pedro A. Aranda gave me a clue about how to get the standard file
 *    handles, which he in turn was told by Jacob Navia.
 *  Floating point initialization from <W.Derks@nl.cis.philips.com>
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
#include <float.h>
#include <windows.h>

/* NOTE: The code for initializing, as well as referencing, the standard
 * file handles and the __argv, __argc, and _environ variables has been
 * moved to a separate .c file which is included in both crt0.c and
 * dllcrt0.c. This means changes in the code doesn't have to be manually
 * synchronized, but it does lead to this not-generally-a-good-idea use
 * of include. */
#include "init.c"

/*
 * The function mainCRTStartup is the entry point for all console programs.
 */
int
mainCRTStartup ()
{
	int	nRet;

	/*
	 * Initialize floating point unit.
	 */
	_fpreset ();	/* Supplied by CRTDLL.DLL */

	/*
	 * Open stdin, stdout and stderr.
	 */
	_mingw32_init_stdhandles();

	/*
	 * Set up __argc, __argv and _environ.
	 */
	_mingw32_init_mainargs();

	/*
	 * Call the main function. If the user does not supply one
	 * the one in the 'libmingw32.a' library will be linked in, and
	 * that one calls WinMain. See main.c in the 'lib' dir
	 * for more details.
	 */
	nRet = main(__argc, __argv, _environ);

	/*
	 * Perform exit processing for the C library. This means
	 * flushing output and calling 'atexit' registered functions.
	 */
	_cexit();

	ExitProcess (nRet);
}

/*
 * For now the GUI startup function is the same as the console one.
 * This simply gets rid of the annoying warning about not being able
 * to find WinMainCRTStartup when linking GUI applications.
 */
int
WinMainCRTStartup ()
{
	return mainCRTStartup();
}

#ifdef	__GNUC__
/*
 * This section terminates the list of imports under GCC. If you do not
 * include this then you will have problems when linking with DLLs.
 */
asm (".section .idata$3\n" ".long 0,0,0,0,0,0,0,0");
#endif

