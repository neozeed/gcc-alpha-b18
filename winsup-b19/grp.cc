/* grp.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

   Original stubs by Jason Molenda of Cygnus Support, crash@cygnus.com
   First implementation by Gunther Ebert, gunther.ebert@ixos-leipzig.de

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include "winsup.h"

/* Read /etc/group only once for better performance.  This is done
   on the first call that needs information from it. */

static NO_COPY  char *etc_group = "/etc/group";
static char **group_buf = NULL;		/* group contents in memory */
static int curr_lines = 0;
static int max_lines = 0;

/* Position in the group cache */
static int grp_pos = 0;

/* Default values used if accessing /etc/group isn't possible */
static char *def_group = "everyone";
static int def_group_id = 500;

/* Set to 1 when /etc/group has been read in by read_etc_group (). */
/* Functions in this file need to check the value of group_in_memory_p
   and read in the group file if it isn't set. */
/* FIXME: This should be static but this is called in uinfo_init outside
   this file */
int group_in_memory_p = 0;

/* Cygwin32 internal */
/* Read one line from /etc/group into the group cache */
static void
add_grp_line (char *line)
{
    if (curr_lines == max_lines)
    {
        max_lines += 10;
        char **new_grp_buf = (char **) malloc (max_lines * sizeof (char *));
        if (group_buf)
        {
            memcpy (new_grp_buf, group_buf, curr_lines * sizeof (char *));
            free (group_buf);
        }
        group_buf = new_grp_buf;
    }
    group_buf[curr_lines++] = strdup (line);
}

/* Cygwin32 internal */
/* Read in /etc/group and save contents in the group cache */
/* This sets group_in_memory_p to 1 so functions in this file can
   tell that /etc/group has been read in */
/* FIXME: should be static but this is called in uinfo_init outside this
   file */
void
read_etc_group ()
{
  FILE *f = fopen (etc_group, "r");

  if (f)
    {
      char linebuf[200];

      while (!feof (f))
        {
          fgets (linebuf, sizeof (linebuf), f);
	  if (strlen (linebuf))
            add_grp_line (linebuf);
        }

      fclose (f);
    }
  else /* /etc/group doesn't exist -- create default one in memory */
    {
      const char *default_line = "everyone::500:\n";
      add_grp_line (default_line);
    }

  group_in_memory_p = 1;
}

extern "C"
struct group *
getgrgid (gid_t gid)
{
  static NO_COPY struct group grp;
  static NO_COPY char *namearray[2];
  static NO_COPY char linebuf[100];

  if (!group_in_memory_p)
    read_etc_group();

  for (int i = 0; i < curr_lines; i++)
  {
    char *id_ptr;
    strcpy (linebuf, group_buf[i]);
    grp.gr_name = strtok (linebuf, ":");

    if (grp.gr_name)
      {
        id_ptr = strtok (NULL, ":");
   
        if (id_ptr && atoi (id_ptr) == gid)
          {
            grp.gr_gid = gid;
            namearray[0] = grp.gr_name;
            namearray[1] = NULL;
            grp.gr_mem = namearray;
            return &grp;
          }
      }
  }

  grp.gr_gid = def_group_id;
  grp.gr_name = def_group;
  namearray[0] = grp.gr_name;
  namearray[1] = NULL;
  grp.gr_mem = namearray;

  return (&grp);
}

extern "C"
struct group *
getgrnam (const char *name)
{
  static NO_COPY struct group grp;
  static NO_COPY char *namearray[2];
  static NO_COPY char linebuf[100];

  if (!group_in_memory_p)
    read_etc_group();

  for (int i = 0; i < curr_lines; i++)
  {
    char *id_ptr;
    strcpy (linebuf, group_buf[i]);
    grp.gr_name = strtok (linebuf, ":");

    if (grp.gr_name)
      {
        id_ptr = strtok (NULL, ":");
      
        if (id_ptr && !strcasecmp (grp.gr_name, name))
          {
              grp.gr_gid = atoi (id_ptr);
              namearray[0] = grp.gr_name;
              namearray[1] = NULL;
              grp.gr_mem = namearray;
              return &grp;
          }
      }
  }

  /* Didn't find requested group */
  return NULL;
}

extern "C"
void
endgrent()
{
  grp_pos = 0;
}

extern "C"
struct group *
getgrent()
{
  if (!group_in_memory_p)
    read_etc_group();

  if (grp_pos < curr_lines)
    {
      char *id_ptr;
      static NO_COPY char linebuf[100];
      static NO_COPY struct group grp;
      static NO_COPY char *namearray[2];
      strcpy (linebuf, group_buf[grp_pos++]);
      grp.gr_name = strtok (linebuf, ":");
  
      if (grp.gr_name)
        {
          id_ptr = strtok (NULL, ":");

          if (id_ptr)
            {
              grp.gr_gid = atoi (id_ptr);
              namearray[0] = grp.gr_name;
              namearray[1] = NULL;
              grp.gr_mem = namearray;
              return &grp;
            }
        }
    }
        
    return NULL;
}

extern "C"
void
setgrent ()
{
  grp_pos = 0;
}

/* Cygwin32 doesn't support supplementary groups so we
   return only the current gid */
extern "C"
int
getgroups (int gidsetsize, gid_t *grouplist)
{
  if (gidsetsize <= 0)
      return 0;
  grouplist[0] = myself->gid;
  return 1;
}

extern "C"
int
initgroups (const char *user, gid_t group)
{
  return 0;
}
