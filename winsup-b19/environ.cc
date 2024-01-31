/* environ.cc: Cygwin.dll-adopted functions from newlib to manipulate with
   process's environment.

   Copyright 1997, 1998 Cygnus Solutions.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <fcntl.h>
#include "registry.h"

#define environ (*u->envptr)

extern BOOL allow_glob;
extern BOOL strip_title_path;

/* List of names which are converted from dos to unix
 * on the way in and back again on the way out.
 *
 * PATH needs to be here because CreateProcess uses it and gdb uses
 * CreateProcess.  HOME is here because most shells use it and would be
 * confused by Windows style path names.
 *
 */

static NO_COPY const char conv_path_names[] = { "=HOME=PATH=" };

/*
 * _findenv --
 *	Returns pointer to value associated with name, if any, else NULL.
 *	Sets offset to be the offset of the name/value combination in the
 *	environment array, for use by setenv(3) and unsetenv(3).
 *	Explicitly removes '=' in argument name.
 */

static
char *
_findenv (const char *name, int *offset)
{
  register int len;
  register char **p;
  const char *c;

  c = name;
  len = 0;
  while (*c && *c != '=')
    {
      c++;
      len++;
    }

  for (p = environ; *p; ++p)
    if (!strncmp (*p, name, len))
      if (*(c = *p + len) == '=')
	{
	  *offset = p - environ;
	  return (char *) (++c);
	}
  return NULL;
}

/*
 * getenv --
 *	Returns ptr to value associated with name, if any, else NULL.
 */

extern "C"
char *
getenv (const char *name)
{
  int offset;

  return _findenv (name, &offset);
}

/* putenv --
 *	Sets an environment variable
 */

extern "C"
int
putenv (const char *str)
{
  register char *p, *equal;
  int rval;

  if (!(p = strdup (str)))
    return 1;
  if (!(equal = index (p, '=')))
    {
      (void) free (p);
      return 1;
    }
  *equal = '\0';
  rval = setenv (p, equal + 1, 1);
  (void) free (p);
  return rval;
}

/*
 * setenv --
 *	Set the value of the environment variable "name" to be
 *	"value".  If rewrite is set, replace any current value.
 */

extern "C"
int
setenv (const char *name, const char *value, int rewrite)
{
  register char *C;
  int l_value, offset;

  if (*value == '=')		/* no `=' in value */
    ++value;
  l_value = strlen (value);
  if ((C = _findenv (name, &offset)))
    {				/* find if already exists */
      if (!rewrite)
	return 0;
      if (strlen (C) >= l_value)
	{			/* old larger; copy over */
	  while (*C++ = *value++);
	  return 0;
	}
    }
  else
    {				/* create new slot */
      register int cnt;
      register char **P;

      for (P = environ, cnt = 0; *P; ++P, ++cnt)
	;
      __cygwin_environ = environ = (char **) realloc ((char *) environ,
		      (size_t) (sizeof (char *) * (cnt + 2)));
      if (!environ)
        return -1;
      environ[cnt + 1] = NULL;
      offset = cnt;
    }
  for (C = (char *) name; *C && *C != '='; ++C);	/* no `=' in name */
  if (!(environ[offset] =	/* name + `=' + value */
	(char *) malloc ((size_t) ((int) (C - name) + l_value + 2))))
    return -1;
  for (C = environ[offset]; (*C = *name++) && *C != '='; ++C);
  for (*C++ = '='; *C++ = *value++;);
  return 0;
}

/*
 * unsetenv(name) --
 *	Delete environment variable "name".
 */

extern "C"
void
unsetenv (const char *name)
{
  register char **P;
  int offset;

  while (_findenv (name, &offset))	/* if set multiple times */
    for (P = &environ[offset];; ++P)
      if (!(*P = *(P + 1)))
	break;
}

/* Turn environment variable part of a=b string into uppercase. */

static void
ucenv (char *p, char *eq)
{
  /* Amazingly, NT has a case sensitive environment name list,
     but only sometimes.
     It's normal to have NT set your "Path" to something.
     Later, you set "PATH" to something else.  This alters "Path".
     But if you try and do a naive getenv on "PATH" you'll get nothing. 
     
     So we upper case the labels here to prevent confusion later but
     we only do it for the first process in a session group. */
  for (; p < eq; p++)
    if (islower (*p))
      *p = toupper (*p);
}

/* Parse CYGWIN32 options */

static NO_COPY BOOL export_settings = FALSE;

static char *
parse_options (char *buf)
{
  int i, istrue;
  char *p;
  static char *remember_title, *remember_strip_title_path, *remember_tty,
	      *remember_binmode, *remember_strace, *remember_glob;

  enum settings
    {
      justset,
      isfunc,
      setbit
    };

  struct
    {
      char *name;
      struct
	{
	  BOOL *b;
	  DWORD *x;
	  int *i;
	  void (*func)(char *);
	} setting;
	  
      enum settings disposition;
      char **remember;
      struct
	{
	  DWORD i;
	  char *s;
	} values[2];
    } known[8];

  known[0].name = (char *) malloc (6 + 1);
  known[0].name = "export";
  known[0].setting.b = &export_settings;
  known[0].disposition = justset;
  known[0].remember = NULL;
  known[0].values[0].i = FALSE;
  known[0].values[1].i = TRUE;

  known[1].name = (char *) malloc (5 + 1);
  known[1].name = "title";
  known[1].setting.b = &display_title;
  known[1].disposition = justset;
  known[1].remember = &remember_title;
  known[1].values[0].i = FALSE;
  known[1].values[1].i = TRUE;

  known[2].name = (char *) malloc (11 + 1);
  known[2].name = "strip_title";
  known[2].setting.b = &strip_title_path;
  known[2].disposition = justset;
  known[2].remember = &remember_strip_title_path;
  known[2].values[0].i = FALSE;
  known[2].values[1].i = TRUE;

  known[3].name = (char *) malloc (4 + 1);
  known[3].name = "glob";
  known[3].setting.b = &allow_glob;
  known[3].disposition = justset;
  known[3].remember = &remember_glob;
  known[3].values[0].i = FALSE;
  known[3].values[1].i = TRUE;

  known[4].name = (char *) malloc (3 + 1);
  known[4].name = "tty";
  known[4].setting.x = &myself->process_state;
  known[4].disposition = setbit;
  known[4].remember = &remember_tty;
  known[4].values[0].i = 0;
  known[4].values[1].i = PID_USETTY;

  known[5].name = (char *) malloc (7 + 1);
  known[5].name = "binmode";
  known[5].setting.i = u->fmode_ptr;
  known[5].disposition = justset;
  known[5].remember = &remember_binmode;
  known[5].values[0].i = 0;
  known[5].values[1].i = O_BINARY;

  known[6].name = (char *) malloc (6 + 1);
  known[6].name = "strace";
  known[6].setting.func = strace_init;
  known[6].disposition = isfunc;
  known[6].remember = &remember_strace;
  known[5].values[0].s = "0";
  known[5].values[1].s = "1";
  
  known[7].name = NULL;
  known[7].setting.b = 0;

#if 0
  /* FIXME: used to be statically initialized like this.  This doesn't
     seem to be valid ANSI C or C++ code (can't do this for more than
     first member of a union which caused problems for strace line). */
    } known[] =
    {
      {"export", {b: &export_settings}, justset, NULL, {FALSE, TRUE}},
      {"title", {b: &display_title}, justset, &remember_title, {FALSE, TRUE}},
      {"strip_title", {b: &strip_title_path}, justset,
       &remember_strip_title_path, {FALSE, TRUE}},
      {"glob", {b: &allow_glob}, justset, &remember_glob, {FALSE, TRUE}},
      {"tty", {x: &myself->process_state}, setbit, &remember_tty, {0, PID_USETTY}},
      {"binmode", {i: u->fmode_ptr}, justset, &remember_binmode, {0, O_BINARY}},
      {"strace", {func: strace_init}, isfunc, &remember_strace, {s: "0", s: "1"}},
      {NULL, 0}
    };
#endif

  if (buf == NULL)
    {
      char newbuf[MAX_PATH + 9] = "CYGWIN32";
      for (i = 0; known[i].name != NULL; i++)
	if (known[i].remember != NULL && *known[i].remember != NULL)
	  {
	    strcat (strcat (newbuf, " "), *known[i].remember);
	    free (*known[i].remember);
	  }
      if (!export_settings)
	return NULL;
      newbuf[sizeof ("CYGWIN32") - 1] = '=';
      debug_printf ("%s\n", newbuf);
      return strdup (newbuf);
    }

  buf = strcpy ((char *) alloca (strlen (buf) + 1), buf);
  for (p = strtok (buf, " \t"); p != NULL; p = strtok (NULL, " \t"))
    {
      if (!(istrue = strncasecmp (p, "no", 2) != 0))
	p += 2;
      else if (!(istrue = strncasecmp (p, "-", 1) != 0))
	p++;

      char ch, *eq;
      if ((eq = strchr (p, '=')) != NULL || (eq = strchr (p, ':')) != NULL)
	ch = *eq, *eq++ = '\0';
      else
	ch = 0;
      for (i = 0; known[i].name != NULL; i++)
	if (strcasecmp (p, known[i].name) == 0)
	  {
	    if (known[i].disposition == isfunc)
	      known[i].setting.func ((!eq || !istrue) ?
		known[i].values[istrue].s : eq);
	    else if (known[i].disposition == justset)
	      {
		if (!istrue || !eq)
		  *known[i].setting.x = known[i].values[istrue].i;
		else
		  *known[i].setting.x = strtol (eq, NULL, 0);
	      }
	    else // if (known[i].disposition == setbit)
	      {
		*known[i].setting.x &= ~known[i].values[istrue].i;
		if (istrue || (eq && strtol (eq, NULL, 0)))
		  *known[i].setting.x |= known[i].values[istrue].i;
	      }
		

	    if (!known[i].disposition == isfunc)
	      debug_printf ("%s=%d\n", known[i].name, *known[i].setting.x);

	    if (eq)
		*--eq = ch;
	    if (known[i].remember)
	      {
		int n = eq - p;
		p = strdup (p);
		if (n > 0)
		  p[n] = ':';
		*known[i].remember = p;
	      }
	    break;
	  }
      }
  debug_printf ("returning\n");
  return NULL;
}

#ifdef USE_REGISTRY
/* Set options from the registry. */

static void
regopt (char *name)
{
  reg_session r;
  char buf[MAX_PATH];
  strlwr (name);
  reg_key wrapper = reg_key (r.get_key (), "Program Options");
  if (wrapper.get_string (name, buf, sizeof (buf) - 1, "") == ERROR_SUCCESS)
    parse_options (buf);
}
#endif


/* If we're using posix paths, we do a special thing for the PATH
 * [and potentially others].  They might be in native format so we turn
 * them into their posix equivalent.  */

static void
posify (char **here, char *value)
{
  char *p, *src = *here;
  char ch = *value;

  *value = '\0';
  if ((p = strstr (conv_path_names, src)) == NULL || p[-1] != '=')
    {
      *value = ch;
      return;
    }

  /* Turn all the items from c:<foo>;<bar> into their 
     mounted equivalents - if there is one.  */
  
  *value = ch;
  int namelen = value - src;
  char *outenv = (char *) malloc (1 + namelen +
		    win32_to_posix_path_list_buf_size (value));
  memcpy (outenv, src, namelen);
  win32_to_posix_path_list (value, outenv + namelen);

  debug_printf ("env var converted to %s\n", outenv);
  *here = outenv;
  free (src);
}

/* Initialize the environ array.  Look for CYGWIN32 environment variable and
 * set appropriate options from it. */

void
environ_init (void)
{
  const char * const rawenv = GetEnvironmentStrings ();
  int envsize, i, cygix = -1;
  char *newp, **envp;
  const char *p;

  /* Allocate space for environment + trailing NULL + CYGWIN32 env. */
  envp = (char **) malloc ((1 + (envsize = 100)) * sizeof (char *));

#ifdef USE_REGISTRY
  {
    char module_name[MAX_PATH];

    regopt ("default");
    if (GetModuleFileName (NULL, module_name, MAX_PATH))
      regopt (module_name);
  }
#endif

  /* Current directory information is recorded as variables of the
     form "=X:=X:\foo\bar; these must be changed into something legal
     (we could just ignore them but maybe an application will
     eventually want to use them).  */
  for (i = 0, p = rawenv; *p != '\0'; p = strchr (p, '\0') + 1, i++)
    {
      newp = strdup (p);
      if (i >= envsize)
	envp = (char **) realloc (envp, (1 + (envsize += 100)) *
					    sizeof (char *));
      envp[i] = newp;
      if (*newp == '=')
	*newp = '!';
      char *eq;
      if ((eq = strchr (newp, '=')) == NULL)
	eq = strchr (newp, '\0');
      if (!myself->parent_alive)
	ucenv (newp, eq);
      if (strncmp (newp, "CYGWIN32=", 9) == 0)
	parse_options (newp + 9);
      if (*eq && s->mount.posix_path_p ())
	posify (envp + i, *++eq ? eq : --eq);
      debug_printf ("%s\n", envp[i]);
    }

  envp[i++] = NULL;
  __cygwin_environ = *u->envptr =
    (char **) realloc (envp, i * sizeof (char *));
  FreeEnvironmentStringsA ((char *) rawenv);
}

/* Function called by qsort to sort environment strings.  */

static int
env_sort (const void *a, const void *b)
{
  const char **p = (const char **) a;
  const char **q = (const char **) b;

  return strcmp (*p, *q);
}

/* Create a Windows-style environment block. */

char *
winenv (const char * const *envp)
{
  int len, n, tl;
  const char * const *srcp;
  char **dstp;

  for (n = 0; envp[n]; n++)
    continue;

  char *newenvp[n + 1];

  for (tl = 0, srcp = envp, dstp = newenvp; *srcp; srcp++, dstp++)
    {
      len = strcspn (*srcp, "=") + 1;

      const char *p;
      for (p = conv_path_names; p && *++p != '\0'; p = strchr (p, '='))
	if (strncmp (p, *srcp, len) == 0)
	  {
	    /* Turn unix style into win32 style.  */

	    debug_printf ("translating %s\n", *srcp);

	    *dstp = (char *) alloca (len + 1 +
				     posix_to_win32_path_list_buf_size (*srcp +
									len));
	    strncpy (*dstp, p, len);
	    posix_to_win32_path_list ((char *)*srcp + len, *dstp + len);

	    debug_printf ("setting %s\n", *dstp);
	    goto outer;
	  }

      /* Handle env var if not done yet.  */
      *dstp = (char *)*srcp;

    outer:
      tl += strlen (*dstp) + 1;
    }

  *dstp = NULL;		/* Terminate */

  int envlen = dstp - newenvp;
  debug_printf ("env count=%d bytes=%d\n", envlen, tl);

  /* Windows programs expect the environment block to be sorted.  */
  qsort (newenvp, envlen, sizeof (char *), env_sort);

  /* Create an environment block suitable for passing to CreateProcess.  */
  char *ptr, *envblock;
  envblock = (char *) malloc (tl + 2);
  for (srcp = newenvp, ptr = envblock; *srcp; srcp++)
    {
      len = strlen (*srcp);
      memcpy (ptr, *srcp, len + 1);
      ptr += len + 1;
    }
  *ptr = '\0';		/* Two null bytes at the end */

  return envblock;
}
