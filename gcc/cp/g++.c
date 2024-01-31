/* G++ preliminary semantic processing for the compiler driver.
   Copyright (C) 1993, 1994, 1995, 1996 Free Software Foundation, Inc.
   Contributed by Brendan Kehoe (brendan@cygnus.com).

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* This program is a wrapper to the main `gcc' driver.  For GNU C++,
   we need to do two special things: a) append `-lstdc++' in situations
   where it's appropriate, to link in libstdc++, and b) add `-xc++'..`-xnone'
   around file arguments named `foo.c' or `foo.i'.  So, we do all of
   this semantic processing then just exec gcc with the new argument
   list.

   We used to do all of this in a small shell script, but many users
   found the performance of this as a shell script to be unacceptable.
   In situations where your PATH has a lot of NFS-mounted directories,
   using a script that runs sed and other things would be a nasty
   performance hit.  With this program, we never search the PATH at all.  */

#include "config.h"
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include <stdio.h>
#include <sys/types.h>
#if !defined(__OPENNT)
#if (! defined (_WIN32) || defined (__CYGWIN32__))
#include <sys/file.h>   /* May get R_OK, etc. on some systems.  */
#else
#include <process.h>
#endif
#endif  /* !__OPENNT */
#include <errno.h>

#include "gansidecl.h"

/* Defined to the name of the compiler; if using a cross compiler, the
   Makefile should compile this file with the proper name
   (e.g., "i386-aout-gcc").  */
#ifndef GCC_NAME
#define GCC_NAME "gcc"
#endif

/* This bit is set if we saw a `-xfoo' language specification.  */
#define LANGSPEC	(1<<1)
/* This bit is set if they did `-lm' or `-lmath'.  */
#define MATHLIB		(1<<2)
/* This bit is set if they did `-lc'.  */
#define WITHLIBC	(1<<3)

#ifndef MATH_LIBRARY
#define MATH_LIBRARY "-lm"
#endif

#ifndef errno
extern int errno;
#endif

#ifndef HAVE_STRERROR
extern int sys_nerr;
#if defined(bsd4_4)
extern const char *const sys_errlist[];
#else
extern char *sys_errlist[];
#endif
#else
extern char *strerror();
#endif

/* If a stage of compilation returns an exit status >= 1,
   compilation of that file ceases.  */

#define MIN_FATAL_STATUS 1

/* Name with which this program was invoked.  */
static char *programname;

/* The number of errors that have occurred; the link phase will not be
   run if this is non-zero.  */
static int error_count = 0;

/* Number of commands that exited with a signal.  */

static int signal_count;

extern char *choose_temp_base PROTO((void));

/* Execute a program.  */
extern int pexecute PROTO ((const char *, char * const *, const char *,
			    const char *, char **, char **, int));

/* Cover function for wait.  */
extern int pwait PROTO ((int, int *, int));

/* Flag arguments to pexecute.  */
#define PEXECUTE_FIRST   1
#define PEXECUTE_LAST    2
#define PEXECUTE_SEARCH  4
#define PEXECUTE_VERBOSE 8
/* CYGNUS LOCAL mpw */
#ifdef MPW
#define PEXECUTE_PFINISH
#endif
/* END CYGNUS LOCAL */

#ifndef WIFSIGNALED
#define WIFSIGNALED(S) (((S) & 0xff) != 0 && ((S) & 0xff) != 0x7f)
#endif
#ifndef WTERMSIG
#define WTERMSIG(S) ((S) & 0x7f)
#endif
#ifndef WIFEXITED
#define WIFEXITED(S) (((S) & 0xff) == 0)
#endif
#ifndef WEXITSTATUS
#define WEXITSTATUS(S) (((S) & 0xff00) >> 8)
#endif

char *
my_strerror(e)
     int e;
{

#ifdef HAVE_STRERROR
  return strerror(e);

#else

  static char buffer[30];
  if (!e)
    return "cannot access";

  if (e > 0 && e < sys_nerr)
    return sys_errlist[e];

  sprintf (buffer, "Unknown error %d", e);
  return buffer;
#endif
}

#ifdef HAVE_VPRINTF
/* Output an error message and exit */

static void
fatal VPROTO((char *format, ...))
{
#ifndef __STDC__
  char *format;
#endif
  va_list ap;

  VA_START (ap, format);

#ifndef __STDC__
  format = va_arg (ap, char*);
#endif

  fprintf (stderr, "%s: ", programname);
  vfprintf (stderr, format, ap);
  va_end (ap);
  fprintf (stderr, "\n");
#if 0
  /* XXX Not needed for g++ driver.  */
  delete_temp_files ();
#endif
  exit (1);
}

#else /* not HAVE_VPRINTF */

static void
error (msg, arg1, arg2)
     char *msg, *arg1, *arg2;
{
  fprintf (stderr, "%s: ", programname);
  fprintf (stderr, msg, arg1, arg2);
  fprintf (stderr, "\n");
}

static void
fatal (msg, arg1, arg2)
     char *msg, *arg1, *arg2;
{
  error (msg, arg1, arg2);
#if 0
  /* XXX Not needed for g++ driver.  */
  delete_temp_files ();
#endif
  exit (1);
}

#endif /* not HAVE_VPRINTF */

/* More 'friendly' abort that prints the line and file.
   config.h can #define abort fancy_abort if you like that sort of thing.  */

void
fancy_abort ()
{
  fatal ("Internal g++ abort.");
}

char *
xmalloc (size)
     unsigned size;
{
  register char *value = (char *) malloc (size);
  if (value == 0)
    fatal ("virtual memory exhausted");
  return value;
}

static void
pfatal_pexecute (errmsg_fmt, errmsg_arg)
     char *errmsg_fmt;
     char *errmsg_arg;
{
  if (errmsg_arg)
    {
      /* Space for trailing '\0' is in %s.  */
      char *msg = xmalloc (strlen (errmsg_fmt) + strlen (errmsg_arg));
      sprintf (msg, errmsg_fmt, errmsg_arg);
      errmsg_fmt = msg;
    }

  fatal ("%s: %s", errmsg_fmt, my_strerror (errno));
}

/* This is the common prefix we use to make temp file names.
   It is chosen once for each run of this program.
   It is substituted into a spec by %g.
   Thus, all temp file names contain this prefix.
   In practice, all temp file names start with this prefix.

   This prefix comes from the envvar TMPDIR if it is defined;
   otherwise, from the P_tmpdir macro if that is defined;
   otherwise, in /usr/tmp or /tmp;
   or finally the current directory if all else fails.  */

static char *temp_filename;

int
main (argc, argv)
     int argc;
     char **argv;
{
  register int i, j = 0;
  register char *p;
  int verbose_flag = 0;

  /* This will be 0 if we encounter a situation where we should not
     link in libstdc++.  */
  int library = 1;

  /* Used to track options that take arguments, so we don't go wrapping
     those with -xc++/-xnone.  */
  char *quote = NULL;

  /* The new argument list will be contained in this.  */
  char **arglist;

  /* The name of the compiler we will want to run---by default, it
     will be the definition of `GCC_NAME', e.g., `gcc'.  */
  char *gcc = GCC_NAME;

  /* Non-zero if we saw a `-xfoo' language specification on the
     command line.  Used to avoid adding our own -xc++ if the user
     already gave a language for the file.  */
  int saw_speclang = 0;

  /* "-lm" or "-lmath" if it appears on the command line.  */
  char *saw_math = 0;

  /* "-lc" if it appears on the command line.  */
  char *saw_libc = 0;

  /* The number of arguments being added to what's in argv, other than
     libraries.  We use this to track the number of times we've inserted
     -xc++/-xnone.  */
  int added = 0;

  /* An array used to flag each argument that needs a bit set for
     LANGSPEC, MATHLIB, or WITHLIBC.  */
  int *args;

  /* Used by pexecute.  */
  char *errmsg_fmt, *errmsg_arg;
  int child_pid, pid, status;

  p = argv[0] + strlen (argv[0]);

  while (p != argv[0] && p[-1] != '/')
    --p;
  programname = p;

  if (argc == 1)
    fatal ("No input files specified.\n");

#ifndef __MSDOS__
  /* We do a little magic to find out where the main gcc executable
     is.  If they ran us as /usr/local/bin/g++, then we will look
     for /usr/local/bin/gcc; similarly, if they just ran us as `g++',
     we'll just look for `gcc'.  */
  if (p != argv[0])
    {
      *--p = '\0';
      gcc = (char *) malloc ((strlen (argv[0]) + 1 + strlen (GCC_NAME) + 1)
			     * sizeof (char));
      sprintf (gcc, "%s/%s", argv[0], GCC_NAME);
    }
#endif

  args = (int *) malloc (argc * sizeof (int));
  bzero ((char *) args, argc * sizeof (int));

  for (i = 1; i < argc; i++)
    {
      /* If the previous option took an argument, we swallow it here.  */
      if (quote)
	{
	  quote = NULL;
	  continue;
	}

      if (argv[i][0] == '\0' || argv[i][1] == '\0')
	continue;

      if (argv[i][0] == '-')
	{
	  if (library != 0 && (strcmp (argv[i], "-nostdlib") == 0
			       || strcmp (argv[i], "-nodefaultlibs") == 0))
	    {
	      library = 0;
	    }
	  else if (strcmp (argv[i], "-lm") == 0
		   || strcmp (argv[i], "-lmath") == 0
#ifdef ALT_LIBM
		   || strcmp (argv[i], ALT_LIBM) == 0
#endif
		  )
	    args[i] |= MATHLIB;
	  else if (strcmp (argv[i], "-lc") == 0)
	    args[i] |= WITHLIBC;
	  else if (strcmp (argv[i], "-v") == 0)
	    {
	      verbose_flag = 1;
	      if (argc == 2)
		{
		  /* If they only gave us `-v', don't try to link
		     in libg++.  */ 
		  library = 0;
		}
	    }
	  else if (strncmp (argv[i], "-x", 2) == 0)
	    saw_speclang = 1;
	  else if (((argv[i][2] == '\0'
		     && (char *)strchr ("bBVDUoeTuIYmLiA", argv[i][1]) != NULL)
		    || strcmp (argv[i], "-Tdata") == 0))
	    quote = argv[i];
	  else if (library != 0 && ((argv[i][2] == '\0'
		     && (char *) strchr ("cSEM", argv[i][1]) != NULL)
		    || strcmp (argv[i], "-MM") == 0))
	    {
	      /* Don't specify libraries if we won't link, since that would
		 cause a warning.  */
	      library = 0;
	    }
	  else
	    /* Pass other options through.  */
	    continue;
	}
      else
	{
	  int len; 

	  if (saw_speclang)
	    {
	      saw_speclang = 0;
	      continue;
	    }

	  /* If the filename ends in .c or .i, put options around it.
	     But not if a specified -x option is currently active.  */
	  len = strlen (argv[i]);
	  if (len > 2
	      && (argv[i][len - 1] == 'c' || argv[i][len - 1] == 'i')
	      && argv[i][len - 2] == '.')
	    {
	      args[i] |= LANGSPEC;
	      added += 2;
	    }
	}
    }

  if (quote)
    fatal ("argument to `%s' missing\n", quote);

  if (added || library)
    {
      arglist = (char **) malloc ((argc + added + 4) * sizeof (char *));

      for (i = 1, j = 1; i < argc; i++, j++)
	{
	  arglist[j] = argv[i];

	  /* Make sure -lstdc++ is before the math library, since libstdc++
	     itself uses those math routines.  */
	  if (!saw_math && (args[i] & MATHLIB) && library)
	    {
	      --j;
	      saw_math = argv[i];
	    }

	  if (!saw_libc && (args[i] & WITHLIBC) && library)
	    {
	      --j;
	      saw_libc = argv[i];
	    }

	  /* Wrap foo.c and foo.i files in a language specification to
	     force the gcc compiler driver to run cc1plus on them.  */
	  if (args[i] & LANGSPEC)
	    {
	      int len = strlen (argv[i]);
	      if (argv[i][len - 1] == 'i')
		arglist[j++] = "-xc++-cpp-output";
	      else
		arglist[j++] = "-xc++";
	      arglist[j++] = argv[i];
	      arglist[j] = "-xnone";
	    }
	}

      /* Add `-lstdc++' if we haven't already done so.  */
      if (library)
	arglist[j++] = "-lstdc++";
      if (saw_math)
	arglist[j++] = saw_math;
      else if (library)
	arglist[j++] = MATH_LIBRARY;
      if (saw_libc)
	arglist[j++] = saw_libc;

      arglist[j] = NULL;
    }
  else
    /* No need to copy 'em all.  */
    arglist = argv;

  arglist[0] = gcc;

  if (verbose_flag)
    {
      if (j == 0)
	j = argc;

      for (i = 0; i < j; i++)
	fprintf (stderr, " %s", arglist[i]);
      fprintf (stderr, "\n");
      arglist[i] = NULL;
    }

  temp_filename = choose_temp_base ();

  child_pid = pexecute (gcc, arglist, programname, temp_filename,
			&errmsg_fmt, &errmsg_arg,
			PEXECUTE_LAST | PEXECUTE_SEARCH | (verbose_flag ? PEXECUTE_VERBOSE : 0));
  if (child_pid == -1)
    pfatal_pexecute (errmsg_fmt, errmsg_arg);

  pid = pwait (child_pid, &status, 0);
  if (pid < 0)
    abort ();

  if (status != 0)
    {
      if (WIFSIGNALED (status))
	{
	  fatal ("Internal compiler error: program %s got fatal signal %d",
		 GCC_NAME, WTERMSIG (status));
	  error_count = 1;
	  signal_count++;
	}
      else if (WIFEXITED (status)
	       && WEXITSTATUS (status) >= MIN_FATAL_STATUS)
	error_count = 1;
    }

/* CYGNUS LOCAL mpw */
#ifdef PEXECUTE_PFINISH
  pfinish ();
#endif
/* END CYGNUS LOCAL */

  exit (error_count > 0 ? (signal_count ? 2 : 1) : 0);
}
