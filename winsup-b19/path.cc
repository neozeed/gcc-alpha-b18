/* path.cc: path support.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

/* This module's job is to
   - convert between posix and dos style filenames,
   - support the `mount' functionality,
   - support symlinks [for files only, directories not currently supported]

   Pathnames are handled as follows:

   - / is equivalent to \
   - Paths beginning with //<letter> (or \\<letter>) are translated to
   <letter>:  (i.e. This is how drives are specified.  According to
   xxx this is how Microsoft does it in the NT Posix subsystem).
   - Paths beginning with // (or \\) are otherwise not translated
   (i.e. looked up in the mount table or treated as drive specifiers).
   - Paths containing a : are not translated
   (paths like /foo/bar/har:har: don't make much sense but having the rule
   written this way allows one to use strchr).

   The goal in the above set of rules is to allow both posix and win32 flavors
   without either interfering.  The rules are intended to be as close to a
   superset of both as possible.

   A possible future enhancement would be to allow people to disable/enable
   the mount table and //<letter> handling to support pure win32 pathnames.
   Hopefully this won't be needed.  The suggested way to do this would be
   an env var because
   a) we need something that is inherited from parent to child,
   b) environment variables can be passed from the DOS shell to a cygwin32 app,
   c) it allows disabling the feature on an app by app basis within the
   same session (whereas playing about with the registry wouldn't - without
   getting too complicated).  Example: CYGWIN=pathrules[=@]{win32,posix}.
   If CYGWIN=pathrules=win32, mount table and //<letter> handling are
   disabled.  [The intent is to have CYGWIN be a catchall for tweaking
   various cygwin.dll features].

   Note that you can have more than one path to a file.  The mount table is
   always prefered when translating win32 paths to posix paths.  Mount table
   entries may not begin with //.

   Text vs Binary issues are not considered here in path style descisions.

   / and \ are treated as equivalent.  One or the other is prefered in certain
   situations (e.g. / is preferred in result of getcwd, \ is preferred in
   arguments to win32 api calls), but this code will translate as necessary.

   Apps wishing to translate to/from pure win32 and posix-like pathnames
   can use cygwin32_foo.

   Removing mounted filesystem support would simplify things greatly, but
   having it gives us a mechanism of treating disk that lives on a unix machine
   as having unix semantics [it allows one to edit a text file on that disk
   and not have cr's magically appear and perhaps break apps running on unix
   boxes].  It also useful to be able to layout a hierarchy without changing
   the underlying directories.

   The semantics of mounting file systems is not intended to precisely follow
   normal unix systems.

   Each DOS drive is defined to have a current directory.
   Supporting this would complicate things so for now things are defined so
   that c: means c:\.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <mntent.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include "winsup.h"
#include "registry.h"

static int symlink_check_one (const char *path, char *buf, int buflen,
			      int *syml, int *exec);
static int normalize_win32_path (const char *cwd, const char *src, char *dst);
static int normalize_posix_path (const char *cwd, const char *src, char *dst);
static char *getcwd_inner (char *buf, size_t ulen, int posix_p);
static void slashify (const char *src, char *dst, int trailing_slash_p);
static void backslashify (const char *src, char *dst, int trailing_slash_p);
static void nofinalslash (const char *src, char *dst);
static int path_prefix_p (const char *path1, const char *path2, int len1);
static int slash_drive_prefix_p (const char *path);
static int slash_unc_prefix_p (const char *path);
static char *build_slash_drive_prefix (const char *path, char *buf);
static void slash_drive_to_win32_path (const char *path, char *buf,
				       int trailing_slash_p);
#if 0
static NO_COPY const char escape_char = '^';
#endif

/* Return non-zero if paths should be interpreted as Posix paths.
   Otherwise return zero (WIN32 Rules).

   This is a hold-over from the time we had two incompatible styles:
   win32 and posix.  Today there's one "unified" style.  This function
   is still used in case we ever want to implement the suggestion above
   of allowing the user[/app] to disable the posix enhancements (specifically
   the mount table and //<letter>).  For now we always return 1.  */

int
mount_info::posix_path_p ()
{
  return 1;
}

/* Return non-zero if P, a pure WIN32 path, points to a directory mounted
   with -b [binary mode].  */

int
mount_info::binary_win32_path_p (const char *p)
{
  for (int i = 0; i < nmounts; i++)
    {
      if (path_prefix_p (mount[i].device, p, mount[i].devicelen))
	return mount[i].binary;
    }
  return 0;
}

/* Return non-zero if PATH1 is a prefix of PATH2.
   Both are assumed to be of the same path style and / vs \ usage.
   Neither may be "".
   LEN1 = strlen (PATH1).  It's passed because often it's already known.

   Examples:
   /foo/ is a prefix of /foo  <-- may seem odd, but desired
   /foo is a prefix of /foo/
   / is a prefix of /foo/bar
   / is not a prefix of foo/bar
   foo/ is a prefix foo/bar
   /foo is not a prefix of /foobar
*/

static int
path_prefix_p (const char *path1, const char *path2, int len1)
{
  /* Handle case where PATH1 has trailing '/' and when it doesn't.  */
  if (SLASH_P (path1[len1 - 1]))
    --len1;

  if (len1 > 0
      && strncasecmp (path1, path2, len1) != 0)
    return 0;

  return SLASH_P (path2[len1]) || path2[len1] == 0;
}

/* Convert an arbitrary path SRC to a pure WIN32 path, suitable for passing to
   Win32 API routines.

   Whether PATH is interpreted using WIN32 or Posix Rules is specified by a
   call to posix_path_p.

   If an error occurs, `error' is set to the errno value.
   Otherwise it is set to 0.

   follow_mode values:
	> 0	    - convert to PATH symlink points to;
	= 0	    - convert to PATH of symlink itself;
	< 0	    - do not check PATH for symlinks.
*/

path_conv::path_conv (const char *src, int follow_mode)
{
  /* This array is used when expanding symlinks.  It is MAX_PATH * 2
     in length so that we can hold the expanded symlink plus a
     trailer.  */
  char copy[MAX_PATH * 2];

  /* This loop handles symlink expansion.  */
  int loop = 0;
  int expand_again = 1;
  while (expand_again)
    {
      char buf[MAX_PATH];

      expand_again = 0;

      silent_p = 0;
      binary_p = 0;
      error = 0;
      symlink_p = 0;
      exec_p = 0;

      if (! s->mount.posix_path_p ())
	{
	  if (strlen (src) >= MAX_PATH)
	    {
	      error = ENAMETOOLONG;
	      /* Set `path' in case caller doesn't check `error'.
		 Hopefully this is something that the Win32 API will
		 choke on.  */
	      strcpy (path, "::ENAMETOOLONG::");
	      return;
	    }

	  if (slash_drive_prefix_p (src))
	    slash_drive_to_win32_path (src, path, 0);
	  else
	    backslashify (src, path, 0);
	}
      else
	{
	  /* Must look up path in mount table, etc.  */

	  char full_path[MAX_PATH];
	  error = s->mount.conv_to_win32_path (src, path, full_path);
	  if (error != 0)
	    return;
	  binary_p = s->mount.binary_win32_path_p (full_path);
	}

      if (follow_mode < 0)
	return;

      /* Check for symlinks on the win32 path in PATH.  */

      debug_printf ("path_conv: expanding symlinks in %s\n", path);

      char *prev_str = path;
      char *str = path;
      if (str[1] == ':')
	str += 2;
      while (*str == '\\')
	++str;
      str += strcspn (str, "\\");
      while (1)
	{
	  if (*str != '\0')
	    {
	      while (str[1] == '\\')
		++str;
	    }

	  int ele_symlink_p = 0;
	  int ele_exec_p = 0;

	  char ch = *str;
	  *str = '\0';

	  int len = symlink_check_one (path, buf, sizeof buf - 1,
				       &ele_symlink_p, &ele_exec_p);

	  *str = ch;

	  if (ch == '\0')
	    {
	      symlink_p = ele_symlink_p;
	      exec_p = ele_exec_p;

	      /* If we've reached the end of the string, and we only
		 want to expand symlinks along the path, break out of
		 the loop.  We have to call symlink_check_one on the
		 last element of the path in order to set symlink_p
		 correctly.  */
	      if (follow_mode == 0)
		break;
	    }

	  if (len < 0)
	    {
	      error = get_errno ();
	      return;
	    }

	  if (len == 0)
	    {
	      /* We didn't find a symlink.  Move on to the next
                 element of PATH.  If we've reached the end of the
                 string, we're done.  */

	      if (ch == '\0')
		break;

	      ++str;
	      prev_str = str;
	      str += strcspn (str, "\\");
	      continue;
	    }

	  /* We found a symlink.  */

	  ++loop;
	  if (loop > MAX_LINK_DEPTH)
	    {
	      error = ELOOP;
	      return;
	    }

	  /* We assume that an absolute symlink starts with '/', so we
	     can easily determine whether it is an absolute path.  */

	  if (buf[0] == '/')
	    {
	      memcpy (copy, buf, len);
	      /* Note that this mixes forward and backward slashes in
		 COPY, but we should be able to get away with it.  */
	      strcpy (copy + len, str);
	      src = copy;
	      debug_printf ("path_conv: following symlink to %s\n", src);
	      expand_again = 1;
	      break;
	    }

	  if (strlen (path) + len >= MAX_PATH)
	    {
	      error = ENAMETOOLONG;
	      strcpy (path, "::ENAMETOOLONG::");
	      return;
	    }

	  char tmp[MAX_PATH];
	  strcpy (tmp, str);
	  buf[len] = '\0';
	  backslashify (buf, prev_str, 0);
	  strcpy (prev_str + len, tmp);

	  debug_printf ("path_conv: expanded symlink gives %s\n", path);

	  /* BUF may contain /../ sequences.  In principle we should
	     be able to sometimes handle them without searching the
	     entire path again.  Since these cases are likely to be
	     relatively rare, for simplicity we don't try.  */
	  if (strstr (prev_str, "..") != NULL)
	    {
	      if (! s->mount.posix_path_p ())
		strcpy (copy, path);
	      else
		{
		  /* We need to convert back to a posix path, because
		     moving up to the parent may move us to a
		     different mount entry.  */
		  error = s->mount.conv_to_posix_path (path, copy, 1);
		  if (error != 0)
		    return;
		}

	      src = copy;
	      expand_again = 1;
	      debug_printf ("path_conv: following parent symlink to %s\n",
			    src);
	      break;
	    }

	  /* Loop around and check the first element of the expanded
             symlink for another symlink.  */

	  str = prev_str;
	  str += strcspn (str, "\\");
	}
    }
}

/* Ensure SRC_PATH is a pure WIN32 path and store the result in WIN32_PATH.

   If WIN32_PATH != NULL, the relative path, if possible to keep, is
   stored in WIN32_PATH.  If the relative path isn't possible to keep,
   the full path is stored.

   If FULL_WIN32_PATH != NULL, the full path is stored there.

   The result is zero for success, or an errno value.

   {,FULL_}WIN32_PATH must have sufficient space (i.e. MAX_PATH bytes).  */

int
mount_info::conv_to_win32_path (const char *src_path,
				char *win32_path,
				char *full_win32_path)
{
  int src_path_len = strlen (src_path);
  int trailing_slash_p = (src_path_len > 0
			  && SLASH_P (src_path[src_path_len - 1]));

  debug_printf ("conv_to_win32_path (%s)\n", src_path);

  if (src_path_len >= MAX_PATH)
    {
      debug_printf ("ENAMETOOLONG = conv_to_win32_path (%s)\n", src_path);
      return ENAMETOOLONG;
    }

  /* The rule is :'s can't appear in [our] posix path names so this is a safe
     test; if ':' is present it already be in win32 form.  */
  if (strchr (src_path, ':') != NULL)
    {
      debug_printf ("%s already win32\n", src_path);
      if (win32_path != NULL)
        backslashify (src_path, win32_path, trailing_slash_p); 
      if (full_win32_path != NULL)
        backslashify (src_path, full_win32_path, trailing_slash_p);
      return 0;
    }

  /* Normalize the path, taking out ../../ stuff, we need to do this
     so that we can move from one mounted directory to another with relative 
     stuff.

     eg mounting c:/foo /foo
     d:/bar /bar

     cd /bar
     ls ../foo
   
     should look in c:/foo, not d:/foo.

     We do this by first getting an absolute Unix-style path and then 
     converting it to a DOS-style path, looking up the appropriate drive
     in the mount table.  */

  char pathbuf[MAX_PATH];
  char cwd[MAX_PATH];

  /* No need to fetch cwd if path is absolute.  */
  if (! SLASH_P (*src_path))
    getcwd_inner (cwd, MAX_PATH, 1); /* FIXME: check rc */
  else
    strcpy (cwd, "/"); /* some innocuous value */
  int rc = normalize_posix_path (cwd, src_path, pathbuf);
  if (rc != 0)
    {
      debug_printf ("%d = conv_to_win32_path (%s)\n", rc, src_path);
      return rc;
    }
  nofinalslash (pathbuf, pathbuf);

  for (int i = 0; i < nmounts; ++i)
    {
      if (! path_prefix_p (mount[i].path, pathbuf, mount[i].pathlen))
	continue;

      /* SRC_PATH is in the mount table.  */

      /* Compute relative path if asked to and able to.  */
      int got_rel_p = 0;
      if (win32_path != NULL
	  && ! SLASH_P (*src_path)
	  /* Ensure the path didn't ../ out of cwd.
	     There are times when we could keep ../foo as is, but
	     normalize_posix_path strips all ../'s and it's [currently] too
	     much work to deal with them.  */
	  && path_prefix_p (cwd, pathbuf, strlen (cwd)))
	{
	  if (path_prefix_p (cwd, mount[i].path, strlen (cwd)))
	    {
	      if (strcmp (pathbuf, mount[i].path) == 0)
		strcpy (win32_path, ".");
	      else
		strcpy (win32_path, pathbuf + strlen (cwd) + 1);
	    }
	  else
	    {
	      /* must be path_prefix_p (mount[i].path, cwd,
                                                  mount[i].pathlen) */
	      if (strcmp (pathbuf, cwd) == 0)
		strcpy (win32_path, ".");
	      else
		strcpy (win32_path, pathbuf + strlen (cwd) + 1);
	    }
	  backslashify (win32_path, win32_path, trailing_slash_p);
	  got_rel_p = 1;
	}

      /* If we've matched / and the path begins with the slash drive prefix,
	 or the UNC path prefix, break out.  If the slash drive path was
	 mounted, it would have matched already.  */
      if (! got_rel_p
	  && strcmp (mount[i].path, "/") == 0
	  && (slash_drive_prefix_p (pathbuf) || slash_unc_prefix_p(pathbuf)))
	break;

      /* Compute the full win32 path.
	 We go to some lengths to avoid unnecessary copying.  */
      char *p = NULL;
      if (full_win32_path != NULL)
	p = full_win32_path;
      else if (win32_path != NULL && ! got_rel_p)
	p = win32_path;
      if (p != NULL)
	{
	  int j = mount[i].devicelen;
	  memcpy (p, mount[i].device, j);
	  /* Do not add trailing \ to UNC device names like \\.\a: */
	  if (pathbuf[mount[i].pathlen] != '/' &&
	        !(strncmp (mount[i].device, "\\\\.\\", 4) == 0 &&
		mount[i].device[mount[i].devicelen-1] == ':'))
	    p[j++] = '\\';
	  strcpy (p + j, pathbuf + mount[i].pathlen);
	  backslashify (p, p, trailing_slash_p);
	}
      if (win32_path != NULL && ! got_rel_p && win32_path != p)
	strcpy (win32_path, p);

      debug_printf ("%s = conv_to_win32_path (%s)\n",
		    win32_path != NULL ? win32_path : full_win32_path,
		    src_path);
      return 0;
    }

  char *p;
  if (full_win32_path != NULL)
    p = full_win32_path;
  else
    p = win32_path;

  /* Not in the database.  Is it a //<letter> path?  */
  if (slash_drive_prefix_p (pathbuf))
    {
      slash_drive_to_win32_path (pathbuf, p, trailing_slash_p);
    }
  else
    {
      /* Can't translate it.  Just ensure no /'s are present.
	 Note that this should [theoretically] only happen if / isn't in
	 the data base, but that's ok [I think].
	 The use of posix_path and not pathbuf here is intentional.
	 We couldn't translate the path, so just ensure no \'s are present. */
      backslashify (src_path, p, trailing_slash_p);
    }
  if (win32_path != NULL && win32_path != p)
    strcpy (win32_path, p);

  debug_printf ("%s = conv_to_win32_path (%s)\n",
		win32_path != NULL ? win32_path : full_win32_path,
		src_path);
  return 0;
}

/* Ensure SRC_PATH is a POSIX_PATH.
   The result is zero for success, or an errno value.
   POSIX_PATH must have sufficient space (i.e. MAX_PATH bytes).
   If KEEP_REL_P is non-zero, relative paths stay that way.  */

int
mount_info::conv_to_posix_path (const char *src_path, char *posix_path,
				int keep_rel_p)
{
  int src_path_len = strlen (src_path);
  int trailing_slash_p = (src_path_len > 0
			  && SLASH_P (src_path[src_path_len - 1]));
  int relative_path_p = (! SLASH_P (*src_path)
			 && strchr (src_path, ':') == NULL);

  debug_printf ("conv_to_posix_path (%s, %s)\n", src_path,
		keep_rel_p ? "keep-rel" : "no-keep-rel");

  if (src_path_len >= MAX_PATH)
    {
      debug_printf ("ENAMETOOLONG\n");
      return ENAMETOOLONG;
    }

  /* FIXME: For now, if the path is relative and it's supposed to stay
     that way, skip mount table processing.  */
  if (keep_rel_p
      && relative_path_p)
    {
      slashify (src_path, posix_path, 0);
      debug_printf ("%s = conv_to_posix_path (%s)\n", posix_path, src_path);
      return 0;
    }

  char pathbuf[MAX_PATH];
  char cwd[MAX_PATH];

  /* No need to fetch cwd if path is absolute.  */
  if (relative_path_p)
    getcwd_inner (cwd, MAX_PATH, 0); /* FIXME: check rc */
  else
    strcpy (cwd, "/"); /* some innocuous value */
  int rc = normalize_win32_path (cwd, src_path, pathbuf);
  if (rc != 0)
    {
      debug_printf ("%d = conv_to_posix_path (%s)\n", rc, src_path);
      return rc;
    }
  nofinalslash (pathbuf, pathbuf);

  for (int i = 0; i < nmounts; ++i)
    {
      if (! path_prefix_p (mount[i].device, pathbuf, mount[i].devicelen))
	continue;

      /* SRC_PATH is in the mount table.  */

      if (mount[i].pathlen + strlen (pathbuf) - mount[i].devicelen >= MAX_PATH)
	return ENAMETOOLONG;
      strcpy (posix_path, mount[i].path);
      if (pathbuf[mount[i].devicelen])
        slashify (pathbuf + mount[i].devicelen,
		posix_path + (mount[i].pathlen == 1 ? 0 : mount[i].pathlen),
		trailing_slash_p);
      debug_printf ("%s = conv_to_posix_path (%s)\n", posix_path, src_path);
      return 0;
    }

  /* Not in the database.  This should [theoretically] only happen if either
     the path begins with //, or / isn't mounted, or the path has a drive
     letter not covered by the mount table.  If it's a relative path then the
     caller must want an absolute path (otherwise we would have returned
     above).  So we always return an absolute path at this point.  */
  if (isalpha (pathbuf[0]) && pathbuf[1] == ':')
    {
      slashify (pathbuf + 2,
		build_slash_drive_prefix (pathbuf, posix_path),
		trailing_slash_p);
    }
  else
    {
      /* The use of src_path and not pathbuf here is intentional.
	 We couldn't translate the path, so just ensure no \'s are present.  */
      slashify (src_path, posix_path, trailing_slash_p);
    }

  debug_printf ("%s = conv_to_posix_path (%s)\n", posix_path, src_path);
  return 0;
}

/* Normalize a posix path.
   \'s are converted to /'s in the process.
   All duplicate /'s, except for 2 leading /'s, are deleted.
   The result is 0 for success, or an errno error value.  */

static int
normalize_posix_path (const char *cwd, const char *src, char *dst)
{
  const char *src_start = src;
  char *dst_start = dst;

  if (! SLASH_P (src[0]))
    {
      if (strlen (cwd) + 1 + strlen (src) >= MAX_PATH)
	{
	  debug_printf ("ENAMETOOLONG = normalize_posix_path (%s)\n", src);
	  return ENAMETOOLONG;
	}
      strcpy (dst, cwd);
      dst += strlen (dst);
      *dst++ = '/';
    }
  /* Two leading /'s?  If so, preserve them.  */
  else if (SLASH_P (src[1]))
    {
      *dst++ = '/';
      *dst++ = '/';
      src += 2;
      if(SLASH_P(*src))
        { /* Starts with three or more slashes - reset. */
          dst = dst_start;
          *dst++ = '/';
          src = src_start + 1;
        }
    }

  while (*src)
    {
      /* Strip runs of /'s.  */
      if (SLASH_P (*src)) 
        {
          *dst++ = '/';
          src++;
          while(SLASH_P(*src))
            src++;
        }
      /* Ignore "./".  */
      else if (src[0] == '.' && SLASH_P (src[1])
	       && (src == src_start || SLASH_P (src[-1])))
	{
	  src += 2;
          while(SLASH_P(src[0]))
            src++;
	}
      /* Strip trailing "/.".  */
      else if (src[0] == '.' && src[1] == 0
	       /* dst must be greater than dst_start */
	       && dst[-1] == '/')
	{
	  /* Only strip ".", not "/.", if path is only "/.".  */
	  if (dst - 1 > dst_start)
	    dst--;
	  src++;
	}
      /* Backup if "..".  */
      else if (src[0] == '.' && src[1] == '.'
	       /* dst must be greater than dst_start */
	       && dst[-1] == '/'
	       && (SLASH_P (src[2]) || src[2] == 0))
	{
	  /* Back up over /, but not if it's the first one.  */
	  if (dst > dst_start + 1)
	    dst--;
	  /* Now back up to the next /.  */
	  while (dst > dst_start + 1 && dst[-1] != '/')
	    dst--;
	  src += 2;
	  while (SLASH_P (*src))
	    src++;
	}
      /* Otherwise, add char to result.  */
      else 
	{
	  if (*src == '\\')
	    *dst++ = '/';
	  else
	    *dst++ = *src;
	  ++src;
	}
    }
  *dst = 0;
  debug_printf ("%s = normalize_posix_path (%s)\n", dst_start, src_start);
  return 0;
}

/* Normalize a win32 path.
   /'s are converted to \'s in the process.
   All duplicate \'s, except for 2 leading \'s, are deleted.

   The result is 0 for success, or an errno error value.
   FIXME: A lot of this should be mergeable with the posix critter.  */

static int
normalize_win32_path (const char *cwd, const char *src, char *dst)
{
  const char *src_start = src;
  char *dst_start = dst;

  if (! SLASH_P (src[0])
      && strchr (src, ':') == NULL)
    {
      if (strlen (cwd) + 1 + strlen (src) >= MAX_PATH)
	{
	  debug_printf ("ENAMETOOLONG = normalize_win32_path (%s)\n", src);
	  return ENAMETOOLONG;
	}
      strcpy (dst, cwd);
      dst += strlen (dst);
      *dst++ = '\\';
    }
  /* Two leading \'s?  If so, preserve them.  */
  else if (SLASH_P (src[0]) && SLASH_P (src[1]))
    {
      *dst++ = '\\';
      ++src;
    }

  while (*src)
    {
      /* Strip duplicate /'s.  */
      if (SLASH_P (src[0]) && SLASH_P (src[1]))
	src++;
      /* Ignore "./".  */
      else if (src[0] == '.' && SLASH_P (src[1])
	       && (src == src_start || SLASH_P (src[-1])))
	{
	  src += 2;
	}
      /* Strip trailing "/.".  */
      else if (src[0] == '.' && src[1] == 0
	       /* dst must be greater than dst_start */
	       && dst[-1] == '\\')
	{
	  /* Only strip ".", not "\.", if path is only "\.".  */
	  if (dst - 1 > dst_start)
	    dst--;
	  src++;
	}
      /* Backup if "..".  */
      else if (src[0] == '.' && src[1] == '.'
	       /* dst must be greater than dst_start */
	       && dst[-1] == '\\'
	       && (SLASH_P (src[2]) || src[2] == 0))
	{
	  /* Back up over /, but not if it's the first one.  */
	  if (dst > dst_start + 1)
	    dst--;
	  /* Now back up to the next /.  */
	  while (dst > dst_start + 1 && dst[-1] != '\\' && dst[-2] != ':')
	    dst--;
	  src += 2;
	  if (SLASH_P (*src))
	    src++;
	}
      /* Otherwise, add char to result.  */
      else 
	{
	  if (*src == '/')
	    *dst++ = '\\';
	  else
	    *dst++ = *src;
	  ++src;
	}
    }
  *dst = 0;
  debug_printf ("%s = normalize_win32_path (%s)\n", dst_start, src_start);
  return 0;
}

/* Build the entire mount table from the registry.  */

static
void
read_mounts (reg_key& key, REGSAM access)
{
  for (int i = 0; i < MAX_MOUNTS; i++)
    {
      char key_name[10];
      char win32path[MAX_PATH];
      char unixpath[MAX_PATH];

      __small_sprintf (key_name, "%02x", i);

      reg_key k = reg_key (key, key_name, access);

      /* The registry names are historical but useful so are left alone.  */
      k.get_string ("native", win32path, sizeof (win32path), "");
      k.get_string ("unix", unixpath, sizeof (unixpath), "");

      /* Does this entry contain something?  */
      if (*win32path != 0)
	{
	  int flags = 0;
	  if (k.get_int ("fbinary", 0))
	    flags |= MOUNT_BINARY;
	  if (k.get_int ("fsilent", 0))
	    flags |= MOUNT_SILENT;

	  s->mount.add_item (win32path, unixpath, flags);
	}
    }
}

void
mount_info::from_registry ()
{
  reg_session r;
  reg_key wrapper = reg_key (r.get_key (), "mounts");

  nmounts = 0;

  read_mounts (wrapper, KEY_ALL_ACCESS);

  reg_session r_common (HKEY_LOCAL_MACHINE, KEY_READ);
  reg_key wrapper1 = reg_key (r_common.get_key (), "mounts", KEY_READ);
  read_mounts (wrapper1, KEY_READ);

  sort ();
}

/* Store the mount table in the registry.  */
/* ??? We always read/write the mount table en masse, rather than only
   the entries that changed.  One benefit of doing things this way is that the
   registry will get cleaned up on a regular basis (say if someone deletes
   entry 02), but we may need to reassess the cost.  */
/* FIXME: Need a mutex to avoid collisions with other tasks.  */

void
mount_info::to_registry ()
{
  reg_session r;

  reg_key wrapper = reg_key (r.get_key (), "mounts");

  for (int i = 0; i < MAX_MOUNTS; i++)
    {
      char key_name[10];

      __small_sprintf (key_name, "%02x", i);

      if (i < nmounts) 
	{
	  mount_item *p = mount + i;
	  debug_printf ("%02x: %s, %s, %d, %d\n",
			i, p->device, p->path, p->binary, p->silent);
	  reg_key k = reg_key (wrapper, key_name);
	  k.set_string ("native", p->device);
	  k.set_string ("unix", p->path);
	  k.set_int ("fbinary", p->binary);
	  k.set_int ("fsilent", p->silent);
	}
      else 
	{
	  /* Mount entry doesn't exist.  Ensure it doesn't in the
	     registry either.  */
	  wrapper.kill (key_name);
	}
    }
}

/* Initialize the mount table.  */

void
mount_info::init ()
{
  nmounts = 0;

  /* Fetch the mount table from the registry.  */
  from_registry ();

  /* Add on defaults.  If the registry overrides these, these will fail
     with "already mounted".  */

  /* Slash defaults to the drive letter containing the system directory */
  char drivestring[MAX_PATH];
  GetSystemDirectory (drivestring, MAX_PATH);
  drivestring[2] = 0;   /* truncate drivestring path to "<drive>:" */
  add_item (drivestring, "/", 0);

#if 0
  /* Mount all drive letters to /mnt/<letter> */
  /* FIXME: Is this right or should these be magic translations in
     the path code, inaccessible to users? */
  add_item ("a:", "/mnt/a", 0);  
  add_item ("b:", "/mnt/b", 0);  
  add_item ("c:", "/mnt/c", 0);  
  add_item ("d:", "/mnt/d", 0);  
  add_item ("e:", "/mnt/e", 0);  
  add_item ("f:", "/mnt/f", 0);  
  add_item ("g:", "/mnt/g", 0);  
  add_item ("h:", "/mnt/h", 0);  
  add_item ("i:", "/mnt/i", 0);  
  add_item ("j:", "/mnt/j", 0);  
  add_item ("k:", "/mnt/k", 0);  
  add_item ("l:", "/mnt/l", 0);  
  add_item ("m:", "/mnt/m", 0);  
  add_item ("n:", "/mnt/n", 0);  
  add_item ("o:", "/mnt/o", 0);  
  add_item ("p:", "/mnt/p", 0);  
  add_item ("q:", "/mnt/q", 0);  
  add_item ("r:", "/mnt/r", 0);  
  add_item ("s:", "/mnt/s", 0);  
  add_item ("t:", "/mnt/t", 0);  
  add_item ("u:", "/mnt/u", 0);  
  add_item ("v:", "/mnt/v", 0);  
  add_item ("w:", "/mnt/w", 0);  
  add_item ("x:", "/mnt/x", 0);  
  add_item ("y:", "/mnt/y", 0);  
  add_item ("z:", "/mnt/z", 0);  
#endif

  /* Floppies and tape raw devices */
  add_item ("//./a:", "/dev/fd0", MOUNT_SILENT);
  add_item ("//./b:", "/dev/fd1", MOUNT_SILENT);
  add_item ("//./tape0:", "/dev/st0", MOUNT_SILENT);
  add_item ("//./tape1:", "/dev/st1", MOUNT_SILENT);

  /* Reinitialize the registry.  */
  to_registry ();
}

struct mntent *
mount_item::getmntent ()
{
  static NO_COPY struct mntent ret;

  ret.mnt_fsname = device;
  ret.mnt_dir = path;
  ret.mnt_type = "native";

  /* We don't print `silent' here.  It's some magical internal thing.  */
  /* FIXME: The wording of mnt_opts needs to be more user friendly.  */
  if (binary)
    ret.mnt_opts = "text=binary";
  else
    ret.mnt_opts = "text!=binary";

  ret.mnt_freq = 1;
  ret.mnt_passno = 1;
  return &ret;
}

struct mntent *
mount_info::getmntent (int x)
{
  if (x < 0 || x >= nmounts)
    return NULL;

  return mount[x].getmntent ();
}

/* Fill in the fields of a mount table entry.  */

void
mount_item::init (const char *dev, const char *mountpoint, int flags)
{
  strcpy ((char *) device, dev);
  strcpy ((char *) path, mountpoint);

  devicelen = strlen (device);
  pathlen = strlen (path);
  binary = (flags & MOUNT_BINARY) != 0;
  silent = (flags & MOUNT_SILENT) != 0;

}

/* qsort callback to sort the mount entries */

static int
sort_by_name (const void *a, const void *b)
{
  mount_item *ap = (mount_item *) a;
  mount_item *bp = (mount_item *) b;

  return strcmp (bp->path, ap->path);
}

void
mount_info::sort ()
{
  /* Sort them into reverse length order, otherwise we won't
     be able to look for /foo in /.  */
  
  qsort (mount, nmounts, sizeof (mount[0]), sort_by_name);
}

/* Add an entry to the mount table.
   Returns 0 on success, -1 on failure and errno is set.

   This is where all argument validation is done.  It may not make sense to
   do this when called internally, but it's cleaner to keep it all here.  */

int
mount_info::add_item (const char *dev, const char *path, int flags)
{
  if (nmounts == MAX_MOUNTS)
    {
      set_errno (EMFILE);
      return -1;
    }

  /* Some argument validation.  */
  if (*path == 0)
    {
      set_errno (EINVAL);
      return -1;
    }

  /* Make sure both paths do not end in /.  */

  char devtmp[MAX_PATH];
  char pathtmp[MAX_PATH];

  backslashify (dev, devtmp, 0);
  nofinalslash (devtmp, devtmp);

  slashify (path, pathtmp, 0);
  nofinalslash (pathtmp, pathtmp);

  debug_printf ("%s[%s], %s[%s], 0x%x\n",
		dev, devtmp, path, pathtmp, flags);

  /* Duplicate /'s in PATH are an error.  */
  for (char *p = pathtmp + 1; *p; ++p)
    {
      if (p[-1] == '/' && p[0] == '/')
	{
	  set_errno (EINVAL);
	  return -1;
	}
    }

  /* Is the path already mounted?  */
  for (int i = 0; i < nmounts; i++)  
    {
      if (strcmp (mount[i].path, pathtmp) == 0)
	{
	  set_errno (EBUSY);
	  return -1;
	}
    }

  mount[nmounts++].init (devtmp, pathtmp, flags);
  sort ();
  return 0;
}

/* Delete a mount table entry where path is either a DOS or Unix name.
   Since the mount table is really just a table of aliases, deleting /
   is ok (although running without a slash mount is strongly discouraged
   because some programs may run erratically without one).  */

int
mount_info::del_item (const char *path)
{
  char pathtmp[MAX_PATH];

  slashify (path, pathtmp, 0);
  nofinalslash (pathtmp, pathtmp);

  for (int i = 0; i < nmounts; i++)
    {
      if (strcmp (mount[i].path, pathtmp) == 0
	  || strcmp (mount[i].device, pathtmp) == 0)
	{
	  /* Sort the names, which will put the new empty one to the end.
	     This is rather inefficient, but it's simple.  */
	  mount[i].init ("", "", 0);
	  sort ();
	  --nmounts;
	  return 0;
	}
    }
  set_errno (EINVAL);
  return -1;
}

/* Cache getcwd value.  FIXME: We need a lock for these in order to
   support multiple threads.  */

static char *current_directory_name=NULL;
static char *current_directory_posix_name=NULL;

/* getcwd */

static char *
getcwd_inner (char *buf, size_t ulen, int posix_p)
{
  char *resbuf = 0;
  int len = ulen;

  if (posix_p)
    {
      if (current_directory_posix_name != NULL)
	{
	  if (strlen (current_directory_posix_name) >= len)
	    set_errno (ERANGE);
	  else
	    {
	      strcpy (buf, current_directory_posix_name);
	      resbuf = buf;
	    }

	  syscall_printf ("%p (%s) = getcwd_inner (%p, %d, posix) (cached)\n",
			  resbuf, resbuf ? resbuf : "", buf, len);
	  return resbuf;
	}
    }
  else
    {
      if (current_directory_name != NULL)
	{
	  if (strlen (current_directory_name) >= len)
	    set_errno (ERANGE);
	  else
	    {
	      strcpy (buf, current_directory_name);
	      resbuf = buf;
	    }

	  syscall_printf ("%p (%s) = getcwd_inner (%p, %d, win32) (cached)\n",
			  resbuf, resbuf ? resbuf : "", buf, len);
	  return resbuf;
	}
    }

  int ok = 0;
  if (current_directory_name != NULL)
    {
      if (strlen (current_directory_name) >= len)
	set_errno (ERANGE);
      else
	{
	  strcpy (buf, current_directory_name);
	  ok = 1;
	}
    }
  else
    {
      DWORD dlen = GetCurrentDirectoryA (len, buf);

      if (dlen == 0)
	__seterrno ();
      else if (dlen >= len)
	set_errno (ERANGE);
      else
	{
	  current_directory_name = (char *) malloc (dlen + 1);
	  if (current_directory_name != NULL)
	    strcpy (current_directory_name, buf);
	  ok = 1;
	}
    }
  if (ok)
    {
      if (posix_p
	  && s->mount.posix_path_p ())
	{
	  char temp[MAX_PATH];

	  /* Turn from win32 style to our style.  */
	  s->mount.conv_to_posix_path (buf, temp, 0);

	  size_t tlen = strlen (temp);

	  current_directory_posix_name = (char *) malloc (tlen + 1);
	  if (current_directory_posix_name != NULL)
	    strcpy (current_directory_posix_name, temp);

	  if (tlen >= ulen)
	    {
	      /* len was too small */
	      set_errno (ERANGE);
	    }
	  else
	    {
	      strcpy (buf, temp);
	      resbuf = buf;
	    }
	}
      else
	resbuf = buf;
    }  
  syscall_printf ("%p (%s) = getcwd_inner (%p, %d, %s)\n",
		  resbuf, resbuf ? resbuf : "",
		  buf, len, posix_p ? "posix" : "win32");
  return resbuf;
}

char *
getcwd (char *buf, size_t ulen)
{
  char *res;

  if (buf == NULL || ulen == 0)
    {
      buf = (char *) alloca (MAX_PATH);
      res = getcwd_inner (buf, MAX_PATH, 1);
      res = strdup (buf);
    }
  else
    {
      res = getcwd_inner (buf, ulen, 1);
    }

  return res;
}

char *
getwd (char *buf)
{
  return getcwd (buf, MAX_PATH);
}

/* chdir: POSIX 5.2.1.1 */
extern "C"
int
chdir (const char *dir)
{
  path_conv path (dir);

  if (path.error)
    {
      set_errno (path.error);
      syscall_printf ("-1 = chdir (%s)\n", dir);
      return -1;
    }

  const char *native_dir = path.get_win32 ();

  int res = SetCurrentDirectoryA (native_dir);
  if (!res)
    __seterrno ();

  /* Clear the cache until we need to retrieve the directory again.  */
  if (current_directory_name != NULL)
    {
      free (current_directory_name);
      current_directory_name = NULL;
    }
  if (current_directory_posix_name != NULL)
    {
      free (current_directory_posix_name);
      current_directory_posix_name = NULL;
    }

  syscall_printf ("%d = chdir (%s) (dos %s)\n", res ? 0 : -1, dir, native_dir);
  return res ? 0 : -1;
}

/* symbolic link support

   Symbolic links to directories are not supported.  Only files.
*/

/* Create a symlink from FROMPATH to TOPATH.  */

int
symlink (const char *topath, const char *frompath)
{
  int fd;
  int res = -1;

  syscall_printf ("symlink (%s, %s)\n", topath, frompath);

  if (topath[0] == 0)
    {
      set_errno (EINVAL);
      goto done;
    }
  if (strlen (topath) >= MAX_PATH)
    {
      set_errno (ENAMETOOLONG);
      goto done;
    }

  fd = _open (frompath, O_WRONLY | O_CREAT | O_BINARY, 0);
  if (fd >= 0)
    {
      char buf[sizeof (SYMLINK_COOKIE) + MAX_PATH + 10];

      sprintf (buf, "%s%s", SYMLINK_COOKIE, topath);
      int len = strlen (buf) + 1;

      /* Note that the terminating nul is written.  */
      if (_write (fd, buf, len) != len)
	{
	  int save_errno = get_errno ();
	  _close (fd);
	  _unlink (frompath);
	  set_errno (save_errno);
	}
      else
	{
	  _close (fd);
          chmod (frompath, S_IFLNK | (STD_RBITS) | (STD_WBITS) | (STD_XBITS));
	  res = 0;
	}
    }

done:
  syscall_printf ("%d = symlink (%s, %s)\n", res, topath, frompath);
  return res;
}

/* Check if PATH is a symlink.  PATH must be a valid win32 path name.

   If PATH is a symlink, put the value of the symlink--the file to
   which it points--into BUF.  The value stored in BUF is not
   necessarily null terminated.  BUFLEN is the length of BUF; only up
   to BUFLEN characters will be stored in BUF.  BUF may be NULL, in
   which case nothing will be stored.

   Set *SYML if PATH is a symlink.

   Set *EXEC if PATH appears to be executable.  This is an efficiency
   hack because we sometimes have to open the file anyhow.  *EXEC will
   not be set for every executable file.

   Return -1 on error, 0 if PATH is not a symlink, or the length
   stored into BUF if PATH is a symlink.  */

static int
symlink_check_one (const char *path, char *buf, int buflen, int *syml,
		   int *exec)
{
  *syml = 0;

  DWORD fileattr = GetFileAttributesA (path);
  if (fileattr == (DWORD) -1)
    {
      /* The GetFileAttributesA call can fail for reasons that don't
	 matter, so we just return 0.  For example, getting the
	 attributes of \\HOST will typically fail.  */
      debug_printf ("symlink_check_one: GetFileAttributesA (%s) failed\n",
		    path);
      return 0;
    }

  /* A symlink will have the `system' file attribute. */
  /* Directories cannot be symlinks. */
  if ((fileattr & (FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_DIRECTORY)) !=
        FILE_ATTRIBUTE_SYSTEM)
    return 0;

  /* Check the file's extended attributes, if it has any.  */
  int unixattr;
  if (get_file_attribute (path, &unixattr) > 0)
    {
      if ((unixattr & STD_XBITS) != 0)
        *exec = 1;
      if (! S_ISLNK (unixattr))
        return 0;
    }

  /* Open the file.  */

  SECURITY_ATTRIBUTES sa;
  sa.nLength = sizeof (sa);
  sa.lpSecurityDescriptor = 0;
  sa.bInheritHandle = 0;

  HANDLE h = CreateFileA (path,
			  GENERIC_READ,
			  FILE_SHARE_READ,
			  &sa, 
			  OPEN_EXISTING,
			  FILE_ATTRIBUTE_NORMAL,
			  0);

  int res = -1;

  if (h == INVALID_HANDLE_VALUE)
    __seterrno ();
  else
    {
      char cookie_buf[sizeof (SYMLINK_COOKIE) - 1];
      DWORD got;

      if (! ReadFile (h, cookie_buf, sizeof (cookie_buf), &got, 0))
	set_errno (EIO);
      else if (got == sizeof (cookie_buf)
	       && memcmp (cookie_buf, SYMLINK_COOKIE,
			  sizeof (cookie_buf)) == 0)
	{
	  /* It's a symlink.  */
	  *syml = 1;
	  *exec = 0;

	  if (buf != NULL)
	    {
	      if (! ReadFile (h, buf, buflen, &got, 0))
		set_errno (EIO);
	      else
		{
		  /* Versions prior to b16 stored several trailing
		     NULs with the path (to fill the path out to 1024
		     chars).  Current versions only store one trailing
		     NUL.  The length returned is the path without
		     *any* trailing NULs.  We also have to handle (or
		     at least not die from) corrupted paths.  */
		  if (memchr (buf, 0, got) != NULL)
		    res = strlen (buf);
		  else
		    res = got;
		}
	    }
	  else
	    res = 0;
	}
      else
	{
	  /* Not a symlink, see if executable.  */
	  *syml = 0;
	  *exec = (got >= 2
		   && cookie_buf[0] == '#'
		   && cookie_buf[1] == '!');
	  res = 0;
	}
      CloseHandle (h);
    }

  if (res >= 0)
    syscall_printf ("%d = symlink_check_one (%s, %p, %d) (%s)\n",
		    res, path, buf, buflen,
		    *syml ? "symlink"
		    : *exec ? "executable"
		    : "normal file");
  else
    syscall_printf ("%d = symlink_check_one (%s, %p, %d)\n",
		    res, path, buf, buflen);

  return res;
}

/* readlink system call */

int
readlink (const char *path, char *buf, int buflen)
{
  path_conv pathbuf (path, 0);
  if (pathbuf.error)
    {
      set_errno (pathbuf.error);
      syscall_printf ("-1 = readlink (%s, %p, %d)\n", path, buf, buflen);
      return -1;
    }

  int syml_p, exec_p;

  int res = symlink_check_one (pathbuf.get_win32 (), buf, buflen,
			       &syml_p, &exec_p);

  if (res < 0)
    return -1;

  if (syml_p)
    return res;

  /* PATH isn't a symlink.  */
  set_errno (EINVAL);
  return -1;
}

/* Mount table system calls.
   Note that these are exported to the application.  */

int
mount (const char *dev, const char *path, int flags)
{
  int res;

  syscall_printf ("mount (%s, %s, 0x%x)\n", dev, path, flags);

  res = s->mount.add_item (dev, path, flags);
  if (res == 0)
    s->mount.to_registry ();

  syscall_printf ("%d = mount (%s, %s, 0x%x)\n", res, dev, path, flags);
  return res;
}

int
umount (const char *path)
{
  int res;

  syscall_printf ("umount (%s)\n",  path);

  res = s->mount.del_item (path);
  if (res == 0)
    s->mount.to_registry ();

  syscall_printf ("%d = umount (%s)\n", res,  path);
  return res;
}

#ifndef __alpha
static int iteration ;
#else
static int iteration=0;
#endif

FILE *
setmntent (const char *filep, const char *)
{
  iteration = 0;
  return (FILE *) filep;
}

struct mntent *
getmntent (FILE *)
{
  return s->mount.getmntent (iteration++);
}

int
endmntent (FILE *)
{
  return 1;
}

/* Cover functions to the path conversion routines.
   These are exported to the world as cygwin32_foo by cygwin.din.  */

extern "C" void
conv_to_win32_path (const char *path, char *win32_path)
{
  s->mount.conv_to_win32_path (path, win32_path, NULL);
}

extern "C" void
conv_to_full_win32_path (const char *path, char *win32_path)
{
  s->mount.conv_to_win32_path (path, NULL, win32_path);
}

/* This is exported to the world as cygwin32_foo by cygwin.din.  */

extern "C" void
conv_to_posix_path (const char *path, char *posix_path)
{
  s->mount.conv_to_posix_path (path, posix_path, 1);
}

extern "C" void
conv_to_full_posix_path (const char *path, char *posix_path)
{
  s->mount.conv_to_posix_path (path, posix_path, 0);
}

/* The realpath function is supported on some Unix systems.  */

extern "C" char *
realpath (const char *path, char *resolved)
{
  int err;
  path_conv real_path (path);

  if (real_path.error)
    err = real_path.error;
  else
    {
      err = s->mount.conv_to_posix_path (real_path.get_win32 (), resolved, 0);
      if (err == 0)
	return resolved;
    }

  /* FIXME: on error, we are supposed to put the name of the path
     component which could not be resolved into RESOLVED.  */
  resolved[0] = '\0';

  set_errno (err);
  return NULL;
}

/* Return non-zero if PATH is a Posix path list.
   This is exported to the world as cygwin32_foo by cygwin.din.

  Rather than use a mode to say what the "proper" path list format is,
  we allow any, and give apps the tools they need to convert between the two.
  If a ';' is present in the path list it's a win32 path list.  Otherwise,
  if the first path begins with <letter>: (in which case it can be the
  only element since if it wasn't a ';' would be present) it's a win32 path
  list.  Otherwise, it's a posix path list.  */

extern "C" int
posix_path_list_p (const char *path)
{
  int posix_p = ! (strchr (path, ';')
		   || (isalpha (path[0]) && path[1] == ':'));
  return posix_p;
}

/* These are used for apps that need to convert env vars like PATH back and
   forth.  The conversion is a two step process.  First, an upper bound on the
   size of the buffer needed is computed.  Then the conversion is done.  This
   allows the caller to use alloca if it wants.  */

static int
conv_path_list_buf_size (const char *path_list, int to_posix_p)
{
  int i, num_elms, max_mount_path_len, size;
  const char *p;

  /* The theory is that an upper bound is
     current_size + (num_elms * max_mount_path_len)  */

  char delim = to_posix_p ? ';' : ':';
  p = path_list;
  for (num_elms = 1; (p = strchr (p, delim)) != NULL; ++num_elms)
    ++p;

  /* 7: strlen ("//c") + slop, a conservative initial value */
  for (max_mount_path_len = 7, i = 0; i < s->mount.nmounts; ++i)
    {
      int mount_len = (to_posix_p
		       ? s->mount.mount[i].pathlen
		       : s->mount.mount[i].devicelen);
      if (max_mount_path_len < mount_len)
	max_mount_path_len = mount_len;
    }

  /* 100: slop */
  size = strlen (path_list) + (num_elms * max_mount_path_len) + 100;
  return size;
}

extern "C" int
win32_to_posix_path_list_buf_size (const char *path_list)
{
  return conv_path_list_buf_size (path_list, 1);
}

extern "C" int
posix_to_win32_path_list_buf_size (const char *path_list)
{
  return conv_path_list_buf_size (path_list, 0);
}

/* Convert a list of path names to/from win32/posix.

   SRC is not a const char * because we temporarily modify it to ease
   the implementation.

   I believe win32 always has '.' in $PATH.   Posix obviously doesn't.
   We certainly don't want to handle that here, but it is something for the
   caller to think about.  */

static void
conv_path_list (char *src, char *dst, int to_posix_p)
{
  char *s;
  char *d = dst;
  char src_delim = to_posix_p ? ';' : ':';
  char dst_delim = to_posix_p ? ':' : ';';
  void (*conv_fn) (const char *, char *) = (to_posix_p
					    ? conv_to_posix_path
					    : conv_to_win32_path);

  do
    {
      s = strchr (src, src_delim);
      if (s)
	{
	  *s = 0;
	  (*conv_fn) (src[0] != 0 ? src : ".", d);
	  d += strlen (d);
	  *d++ = dst_delim;
	  *s = src_delim;
	  src = s + 1;
	}
      else
	{
	  /* Last one.  */
	  (*conv_fn) (src[0] != 0 ? src : ".", d);
	}
    }
  while (s != NULL);
}

extern "C" void
win32_to_posix_path_list (char *win32, char *posix)
{
  conv_path_list (win32, posix, 1);
}

extern "C" void
posix_to_win32_path_list (char *posix, char *win32)
{
  conv_path_list (posix, win32, 0);
}

/* Various utilities.  */
static void
slashify (const char *src, char *dst, int trailing_slash_p)
{
  const char *start = src;

  while (*src)
    {
      if (*src == '\\')
	*dst++ = '/';
      else
	*dst++ = *src;
      ++src;
    }
  if (trailing_slash_p
      && src > start
      && src[-1] != '/')
    *dst++ = '/';
  *dst++ = 0;
}

static void
backslashify (const char *src, char *dst, int trailing_slash_p)
{
  const char *start = src;

  while (*src)
    {
      if (*src == '/')
	*dst++ = '\\';
      else
	*dst++ = *src;
      ++src;
    }
  if (trailing_slash_p
      && src > start
      && src[-1] != '\\'
      && src[-1] != '/')
    *dst++ = '\\';
  *dst++ = 0;
}

/* Remove trailing / and \ from SRC (except for the first one).
   It is ok for src == dst.  */

static void
nofinalslash (const char *src, char *dst)
{
  int l = strlen (src);
  if (src != dst)
    memcpy (dst, src, l+1);
  while (l > 1 && SLASH_P (dst[l-1]))
    {
      dst[l-1] = 0;
      --l;
    }
}

/* Return non-zero if PATH begins with //<letter>.  */

static int
slash_drive_prefix_p (const char *path)
{
  return (path[0] == '/'
	  && path[1] == '/'
	  && isalpha (path[2])
	  && (path[3] == 0 || path[3] == '/'));
}

/* Return non-zero if PATH begins with //UNC/SHARE */

static int
slash_unc_prefix_p (const char *path)
{
  char *p = NULL;
  int ret = (path[0] == '/'
	     && path[1] == '/'
	     && isalpha (path[2])
	     && path[3] != 0
	     && path[3] != '/'
	     && ((p = strchr(&path[3], '/')) != NULL));
  if (!ret || p == NULL)
    return ret;
  return ret && isalnum (p[1]);
}

/* Build "slash drive prefix" in BUF from PATH, which begins with <letter>:.
   The result is a pointer to the end of the string.  */

static char *
build_slash_drive_prefix (const char *path, char *buf)
{
  buf[0] = '/';
  buf[1] = '/';
  buf[2] = path[0];
  return buf + 3;
}

/* Convert PATH (for which slash_drive_prefix_p returns 1) to WIN32 form.  */

static void
slash_drive_to_win32_path (const char *path, char *buf, int trailing_slash_p)
{
  buf[0] = path[2];
  buf[1] = ':';
  if (path[3] == '0')
    strcpy (buf + 2, "\\");
  else
    backslashify (path + 3, buf + 2, trailing_slash_p);
}

/* Split a path into directory and file name parts.
   Buffers DIR and FILE are assumed to be big enough.

   Examples (path -> `dir' / `file'):
   / -> `/' / `'
   "" -> `.' / `'
   . -> `.' / `.' (FIXME: should be `.' / `')
   .. -> `.' / `..' (FIXME: should be `..' / `')
   foo -> `.' / `foo'
   foo/bar -> `foo' / `bar'
   foo/bar/ -> `foo' / `bar'
   /foo -> `/' / `foo'
   /foo/bar -> `/foo' / `bar'
   c: -> `c:/' / `'
   c:/ -> `c:/' / `'
   c:foo -> `c:/' / `foo'
   c:/foo -> `c:/' / `foo'
 */

extern "C" void
split_path (const char *path, char *dir, char *file)
{
  int dir_started_p = 0;

  /* Deal with drives.
     Remember that c:foo <==> c:/foo.  */
  if (isalpha (path[0]) && path[1] == ':')
    {
      *dir++ = *path++;
      *dir++ = *path++;
      *dir++ = '/';
      if (! *path)
	{
	  *dir = 0;
	  *file = 0;
	  return;
	}
      if (SLASH_P (*path))
	++path;
      dir_started_p = 1;
    }

  /* Determine if there are trailing slashes and "delete" them if present.
     We pretend as if they don't exist.  */
  const char *end = path + strlen (path);
  /* path + 1: keep leading slash.  */
  while (end > path + 1 && SLASH_P (end[-1]))
    --end;

  /* At this point, END points to one beyond the last character
     (with trailing slashes "deleted").  */

  /* Point LAST_SLASH at the last slash (duh...).  */
  const char *last_slash;
  for (last_slash = end - 1; last_slash >= path; --last_slash)
    if (SLASH_P (*last_slash))
      break;

  if (last_slash == path)
    {
      *dir++ = '/';
      *dir = 0;
    }
  else if (last_slash > path)
    {
      memcpy (dir, path, last_slash - path);
      dir[last_slash - path] = 0;
    }
  else
    {
      if (dir_started_p)
	; /* nothing to do */
      else
	*dir++ = '.';
      *dir = 0;
    }

  memcpy (file, last_slash + 1, end - last_slash - 1);
  file[end - last_slash - 1] = 0;
}
