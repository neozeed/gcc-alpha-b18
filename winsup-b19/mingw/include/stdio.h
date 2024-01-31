/*
 * stdio.h
 *
 * Definitions of types and prototypes of functions for standard input and
 * output.
 *
 * NOTE: The file manipulation functions provided by CRTDLL.DLL seem to
 * work with either slash (/) or backslash (\) as the path separator.
 *
 * This header file is meant for use with CRTDLL.DLL as included with
 * Windows 95(tm) and Windows NT(tm). In conjunction with other versions
 * of the standard C library things may or may not work so well.
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
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAMED. This includes but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _STDIO_H_
#define	_STDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define __need_size_t
#define __need_NULL
#define __need_wchar_t
#include <stddef.h>

#include <stdarg.h>

/*
 * FILE is actually used as a pointer to an opaque data type.
 * Note: You (as a programmer using the standard library) may only use
 * this type as a pointer because the compiler does not know how much
 * storage to allocate for it. There is no reason I can think of to
 * use it in any other way (unless you were writing the standard
 * library yourself).
 *
 * Frankly it surprises me that this typedef works, but it does.
 */
typedef void	FILE;


/* Returned by various functions on end of file condition or error. */
#define	EOF	(-1)


/*
 * The three standard file pointers opened by the startup code before a
 * program begins. NOTE: These will go to the bit-bucket silently in
 * GUI applications!
 *
 * These are initialized by the code in crt0.c in an incredibly unportable
 * fashion.
 */
extern FILE*	stdin;
extern FILE*	stdout;
extern FILE*	stderr;


/*
 * The maximum length of a file name. You should use GetVolumeInformation
 * instead of this constant. But hey, this works.
 *
 * NOTE: This is used in the structure _finddata_t (see dir.h) so changing it
 *       is probably not a good idea.
 */
#define	FILENAME_MAX	(260)

/*
 * The maximum number of files that may be open at once.
 * This is from my system, it may or may not be a constant.
 */
#define FOPEN_MAX	(34)


/*
 * File Operations
 */

FILE*	fopen (const char* szFileName, const char* szMode);
FILE*	freopen (const char* szNewFileName, const char* szNewMode,
		 FILE* fileChangeAssociation);
int	fflush (FILE* fileFlush);
int	fclose (FILE* fileClose);
int	remove (const char* szFileName);
int	rename (const char* szOldFileName, const char* szNewFileName);
FILE*	tmpfile ();


/*
 * The maximum size of name (including NUL) that will be put in the user
 * supplied buffer caName.
 * NOTE: This has not been determined by experiment, but based on the
 * maximum file name length above it is probably reasonable. I could be
 * wrong...
 */
#define	L_tmpnam	(260)

char*	tmpnam (char caName[]);


/*
 * The three possible buffering mode (nMode) values for setvbuf.
 * NOTE: _IOFBF works, but _IOLBF seems to work like unbuffered...
 * maybe I'm testing it wrong?
 */
#define	_IOFBF	0	/* fully buffered */
#define	_IOLBF	1	/* line buffered */
#define	_IONBF	2	/* unbuffered */

int	setvbuf (FILE* fileSetBuffer, char* caBuffer, int nMode,
		 size_t sizeBuffer);


/*
 * The buffer size as used by setbuf such that it is equivalent to
 * (void) setvbuf(fileSetBuffer, caBuffer, _IOFBF, BUFSIZ).
 */
#define	BUFSIZ	512

void	setbuf (FILE* fileSetBuffer, char* caBuffer);


/*
 * Formatted Output
 */

int	fprintf (FILE* filePrintTo, const char* szFormat, ...);
int	printf (const char* szFormat, ...);
int	sprintf (char* caBuffer, const char* szFormat, ...);
int	vfprintf (FILE* filePrintTo, const char* szFormat, va_list varg);
int	vprintf (const char* szFormat, va_list varg);
int	vsprintf (char* caBuffer, const char* szFormat, va_list varg);

/* Wide character versions */
int	fwprintf (FILE* filePrintTo, const wchar_t* wsFormat, ...);
int	wprintf (const wchar_t* wsFormat, ...);
int	swprintf (wchar_t* wcaBuffer, const wchar_t* wsFormat, ...);
int	vfwprintf (FILE* filePrintTo, const wchar_t* wsFormat, va_list varg);
int	vwprintf (const wchar_t* wsFormat, va_list varg);
int	vswprintf (wchar_t* wcaBuffer, const wchar_t* wsFormat, va_list varg);

/*
 * Formatted Input
 */

int	fscanf (FILE* fileReadFrom, const char* szFormat, ...);
int	scanf (const char* szFormat, ...);
int	sscanf (const char* szReadFrom, const char* szFormat, ...);

/* Wide character versions */
int	fwscanf (FILE* fileReadFrom, const wchar_t* wsFormat, ...);
int	wscanf (const wchar_t* wsFormat, ...);
int	swscanf (wchar_t* wsReadFrom, const wchar_t* wsFormat, ...);

/*
 * Character Input and Output Functions
 */

int	fgetc (FILE* fileRead);
char*	fgets (char* caBuffer, int nBufferSize, FILE* fileRead);
int	fputc (int c, FILE* fileWrite);
int	fputs (const char* szOutput, FILE* fileWrite);
int	getc (FILE* fileRead);
int	getchar ();
char*	gets (char* caBuffer);	/* Unsafe: how does gets know how long the
				 * buffer is? */
int	putc (int c, FILE* fileWrite);
int	putchar (int c);
int	puts (const char* szOutput);
int	ungetc (int c, FILE* fileWasRead);

/* Wide character versions */
int	fgetwc (FILE* fileRead);
int	fputwc (wchar_t wc, FILE* fileWrite);
int	ungetwc (wchar_t wc, FILE* fileWasRead);

/*
 * Not exported by CRTDLL.DLL included for reference purposes.
 */
#if 0
wchar_t*	fgetws (wchar_t* wcaBuffer, int nBufferSize, FILE* fileRead);
int		fputws (const wchar_t* wsOutput, FILE* fileWrite);
int		getwc (FILE* fileRead);
int		getwchar ();
wchar_t*	getws (wchar_t* wcaBuffer);
int		putwc (wchar_t wc, FILE* fileWrite);
int		putws (const wchar_t* wsOutput);
#endif	/* 0 */

/* NOTE: putchar has no wide char equivalent even in tchar.h */


/*
 * Direct Input and Output Functions
 */

size_t	fread (void* pBuffer, size_t sizeObject, size_t sizeObjCount,
		FILE* fileRead);
size_t	fwrite (const void* pObjArray, size_t sizeObject, size_t sizeObjCount,
		FILE* fileWrite);


/*
 * File Positioning Functions
 */

/* Constants for nOrigin indicating the position relative to which fseek
 * sets the file position. Enclosed in ifdefs because io.h could also
 * define them. (Though not anymore since io.h includes this file now.) */
#ifndef	SEEK_SET
#define SEEK_SET	(0)
#endif

#ifndef	SEEK_CUR
#define	SEEK_CUR	(1)
#endif

#ifndef	SEEK_END
#define SEEK_END	(2)
#endif

int	fseek	(FILE* fileSetPosition, long lnOffset, int nOrigin);
long	ftell	(FILE* fileGetPosition);
void	rewind	(FILE* fileRewind);

/*
 * An opaque data type used for storing file positions... The contents of
 * this type are unknown, but we (the compiler) need to know the size
 * because the programmer using fgetpos and fsetpos will be setting aside
 * storage for fpos_t structres. Actually I tested using a byte array and
 * it is fairly evident that the fpos_t type is a long (in CRTDLL.DLL).
 * Perhaps an unsigned long? TODO?
 */
typedef long	fpos_t;

int	fgetpos	(FILE* fileGetPosition, fpos_t* pfpos);
int	fsetpos (FILE* fileSetPosition, fpos_t* pfpos);


/*
 * Error Functions
 */

void	clearerr (FILE* fileClearErrors);
int	feof (FILE* fileIsAtEnd);
int	ferror (FILE* fileIsError);
void	perror (const char* szErrorMessage);

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H_ */
