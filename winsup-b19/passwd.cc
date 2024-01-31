/* passwd.cc: getpwnam () and friends 

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <termios.h>
#include "winsup.h"

/* Read /etc/passwd only once for better performance.  This is done
   on the first call that needs information from it. */

static char **passwd_buf = NULL;	/* passwd contents in memory */
static int curr_lines = 0;
static int max_lines = 0;

/* Set to 1 when /etc/passwd has been read in by read_etc_passwd (). */
/* Functions in this file need to check the value of passwd_in_memory_p
   and read in the password file if it isn't set. */
static int passwd_in_memory_p = 0;

/* Cache the last passwd query */
static struct passwd last_passwd = { 0, 0, 0, 0, 0, 0, 0, 0 };

/* Position in the passwd cache */
static int pw_pos = 0;

/* Cygwin32 internal */
/* Read one line from /etc/passwd into the password cache */
static void
add_pwd_line (char *line)
{
    if (curr_lines == max_lines)
    {
        max_lines += 10;
        char **new_pwd_buf = (char **) malloc (max_lines * sizeof (char *));
        if (passwd_buf)
        {
            memcpy (new_pwd_buf, passwd_buf, curr_lines * sizeof (char *));
            free (passwd_buf);
        }
        passwd_buf = new_pwd_buf;
    }
    passwd_buf[curr_lines++] = strdup (line);
}

/* Cygwin32 internal */
/* Read in /etc/passwd and save contents in the password cache */
/* This sets passwd_in_memory_p to 1 so functions in this file can
   tell that /etc/passwd has been read in */
static void
read_etc_passwd ()
{
    FILE *f = fopen ("/etc/passwd", "r");
    
    if (f)
    {
        char linebuf[200];

        while (!feof (f))
        {
            fgets (linebuf, sizeof (linebuf), f);
	    if (strlen (linebuf))
              add_pwd_line (linebuf);
        }

        fclose (f);
    }
    passwd_in_memory_p = 1;
}

/* Cygwin32 internal */
/* Remove a : teminated string from the buffer, and increment the pointer */
static char *
grab_string (char **p)
{
  char *src = *p;
  char *res = src;

  while (*src && *src != ':' && *src != '\n')
    src++;

  if (*src == ':')
    {
      *src = 0;
      src++;
    }
  *p = src;
  return res;
}

/* Cygwin32 internal */
/* same, for ints */
static int
grab_int (char **p)
{
  char *src = *p;
  int val = atoi (src);
  while (*src && *src != ':' && *src != '\n')
    src++;
  if (*src == ':')
    src++;
  *p = src;
  return val;
}

/* Cygwin32 internal */
static struct passwd *
parse (const char *buf)
{
  /* Allocate enough room for the passwd struct and all the strings
     in it in one go */
  static NO_COPY struct passwd res;
  static NO_COPY char stat[100];
  size_t len = strlen (buf);
  char *mybuf;

  if (len > sizeof (stat))
    {
      set_errno (ENOMEM);
      return 0;
    }
  mybuf = stat;
  strcpy (mybuf, buf);
  if (mybuf[len-1] == '\n')
    mybuf[len-1] = '\0';
  res.pw_name = grab_string (&mybuf);
  res.pw_passwd = grab_string (&mybuf);
  res.pw_uid = grab_int (&mybuf);
  res.pw_gid = grab_int (&mybuf);
  res.pw_gecos = grab_string (&mybuf);
  res.pw_dir =  grab_string (&mybuf);
  res.pw_shell = grab_string (&mybuf);
/* paranoid_printf ("passwd says %s:%d:%d\n",
		 res.pw_name,
		 res.pw_uid,
		 res.pw_gid); */
  return &res;
}

/* Cygwin32 internal */
static struct passwd *
search_for (uid_t uid, const char *name)
{
  struct passwd *res = 0;
  char buf[_PASSWORD_LEN];
  in ("search_for");
  char *got;

  for (int i = 0; i < curr_lines; i++)
    {
      got = strcpy (buf, passwd_buf[i]);
      paranoid_printf ("line from passwd file %s\n", got);
      res = parse (got);
      if (res) 
	{
	  if (name) 
            {
              /* on Windows NT user names are case-insensitive */
              if (strcasecmp (name, res->pw_name) == 0)
                {
                  // memcpy (&last_passwd, res, sizeof (last_passwd));
                  return res;
                }
            }
          else
            {
              if (uid == res->pw_uid)
                {
                  // memcpy (&last_passwd, res, sizeof (last_passwd));
                  return res;
		}
	    }
	}
    }

  out ("search_for");
  return NULL;
}

extern "C"
struct passwd *
getpwuid (uid_t uid)
{
  if (!passwd_in_memory_p)
    read_etc_passwd();

  return search_for (uid, 0);
}

extern "C"
struct passwd *
getpwnam (const char *name)
{
  if (!passwd_in_memory_p)
    read_etc_passwd();

  return search_for (0, name);
}

extern "C"
struct passwd *
getpwent (void)
{
  char buf[_PASSWORD_LEN];

  if (!passwd_in_memory_p)
    read_etc_passwd();

  if (pw_pos < curr_lines)
    {
      strcpy (buf, passwd_buf[pw_pos++]);
      return parse (buf);
    }

  return NULL;
}

extern "C" 
struct passwd * 
getpwduid (uid_t uid)
{
  if (!passwd_in_memory_p)
    read_etc_passwd();

  return NULL;
}

extern "C"
void
setpwent (void)
{
  if (!passwd_in_memory_p)
    read_etc_passwd();

  pw_pos = 0;
}

extern "C"
void
endpwent (void)
{
  if (!passwd_in_memory_p)
    read_etc_passwd();

  pw_pos = 0;
}

extern "C"
int
setpassent ()
{
  if (!passwd_in_memory_p)
    read_etc_passwd();

  return 0;
}

extern "C"
char *
getpass (const char * prompt)
{
  static NO_COPY char pass[_PASSWORD_LEN];
  struct termios ti, newti;

  if (!passwd_in_memory_p)
    read_etc_passwd();

  tcgetattr (0, &ti);
  newti = ti;
  newti.c_lflag &= ~ECHO;
  tcsetattr (0, TCSANOW, &newti);
  fprintf (stderr, prompt);
  fgets (pass, _PASSWORD_LEN, stdin);
  fprintf (stderr, "\n");
  for (int i=0; pass[i]; i++)
    if (pass[i] == '\r' || pass[i] == '\n')
      pass[i] = '\0';
  tcsetattr (0, TCSANOW, &ti);
  return pass;
}
