/*
 * init.c
 *
 * Code to initialize standard file handles and command line arguments.
 * This file is #included in both crt0.c and dllcrt0.c.
 *
 * This code was written to interface with CRTDLL.DLL as supplied with
 * Windows NT and Windows 95, although it could, conceivably, be useful
 * under other circumstances.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
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

/*
 * NOTE: Even though this code initializes the standard file
 * handles, and nothing will break terribly if you use them, unless
 * you compile a console application they will go to the bit bucket.
 */
FILE*	stdin = 0;
FILE*	stdout = 0;
FILE*	stderr = 0;

/*
 * The structure pointed to by _iob is 32 bytes long. This was determined
 * by experiment. I don't even *want* to know what's inside.
 */
#define SIZEOF_IOB	32

/*
 * This is provided as a DLL symbol. Unfortunately that means we have to
 * dance around the thunk created by dlltool to get at the real address.
 * __imp__iob is a symbol created by dlltool containing a real pointer
 * to _iob. If we used _iob directly we'd get a pointer to the thunk.
 */
extern	FILE*	__imp__iob;


/*
 * Access to a standard 'main'-like argument count and list. Also included
 * is a table of environment variables.
 */
int	__argc = 0;
char**	__argv = 0;
char**	_environ = 0;

/* NOTE: Thanks to Pedro A. Aranda Gutiirrez <paag@tid.es> for pointing
 * this out to me. GetMainArgs (used below) takes a fourth argument
 * which is an int that controls the globbing of the command line. If
 * _CRT_glob is non-zero the command line will be globbed (e.g. *.*
 * expanded to be all files in the startup directory). In the mingw32
 * library a _CRT_glob variable is defined as being -1, enabling
 * this command line globbing by default. To turn it off and do all
 * command line processing yourself (and possibly escape bogons in
 * MS's globbing code) include a line in one of your source modules
 * defining _CRT_glob and setting it to zero, like this:
 *  int _CRT_glob = 0;
 */
extern int	_CRT_glob;

/*
 * Initialize the __argc, __argv and _environ variables.
 */
static void
_mingw32_init_mainargs ()
{
	/*
	 * CRTDLL provides a nice little function for doing just that.
	 * Convenient isn't it?
	 * NOTE: The last 
	 */
	(void) __GetMainArgs(&__argc, &__argv, &_environ, _CRT_glob);
}


/*
 * Open the standard file handles stdin, stdout and stderr so that
 * the user's code can use them and get more or less what they expected.
 */
static void
_mingw32_init_stdhandles ()
{
	/* __imp__iob points to the actual iob array. So the standard file
	 * handles can be obtained as the first second and third members
	 * of this array. NOTE: This depends on the current definition of
	 * FILE* as a void*, so that SIZEOF_IOB is in bytes. If you went
	 * and defined FILE as a real structure of the appropriate size
	 * then SIZEOF_IOB should be set to one. */

	stdin = (FILE*) __imp__iob;
	stdout = stdin + SIZEOF_IOB;
	stderr = stdout + SIZEOF_IOB;
}

