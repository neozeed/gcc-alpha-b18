/* hinfo.cc: file descriptor support.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#define  __INSIDE_CYGWIN_NET__

#include "winsup.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define __INSIDE_CYGWIN32__

#include <mywinsock.h>

#include <sys/socket.h>

extern int (*i_getpeername) (SOCKET s, struct sockaddr *name, int * namelen) PASCAL;

/* Initialize the file descriptor/handle mapping table.
   We only initialize the parent table here.  The child table is
   initialized at each fork () call.  */

void
hmap_init (void)
{
  /* Set these before trying to output anything from strace.
     Also, always set them even if we're to pick up our parent's fds
     in case they're missed.  */

  if (!myself->parent_alive && NOTSTATE(myself, PID_CYGPARENT))
    {
      MARK();

      myself->hmap.init_std_file_from_handle (0,
					      GetStdHandle (STD_INPUT_HANDLE),
					      1,
					      GENERIC_READ,
					      "{stdin}");

      /* STD_ERROR_HANDLE has been observed to be the same as
	 STD_OUTPUT_HANDLE.  We need separate handles (e.g. using pipes
	 to pass data from child to parent).  */
      HANDLE out = GetStdHandle (STD_OUTPUT_HANDLE);
      HANDLE err = GetStdHandle (STD_ERROR_HANDLE);
#ifndef __alpha
      const HANDLE proc = GetCurrentProcess ();
#else
      HANDLE proc = GetCurrentProcess ();
#endif
      if (out == err)
	{
	  /* Since this code is not invoked for fork'd tasks, we don't have
	     to worry about the close-on-exec flag here.  */
	  if (! DuplicateHandle (proc, out, proc, &err, 0,
				 1, DUPLICATE_SAME_ACCESS))
	    {
	      /* If that fails, do this as a fall back.  */
	      err = out;
	      small_printf ("Couldn't make stderr distinct from stdout!\n");
	    }
	}

      myself->hmap.init_std_file_from_handle (1, out, 1, GENERIC_WRITE,
					      "{stdout}");
      myself->hmap.init_std_file_from_handle (2, err, 1, GENERIC_WRITE,
					      "{stderr}");
    }
}

int
hinfo_vec::not_open (int fd)
{
  int res = fd < 0 || fd >= getdtablesize() || vec[fd].h == 0;
  return res;
}

hinfo &
hinfo_vec::operator [] (int arg)
{
  return vec[arg];
}

int
hinfo_vec::find_unused_handle (int start)
{
  if (start >= getdtablesize ())
    return -1;

  while (1)
    {
      for (int i = start; i < getdtablesize (); i++)
        if (vec[i].h == 0)
          return i;

      /* Try to allocate more space for fd table. We can't call realloc()
         here to preserve old table if memory allocation fails */
      int new_size = getdtablesize () + NOFILE_INCR;
      void *p;
      if ((p = calloc (new_size, sizeof (vec[0]))) == NULL)
        break;
      memcpy (p, vec, getdtablesize () * sizeof (vec[0]));
      setdtablesize (new_size);
      free (vec);
      vec = (hinfo *) p;

      /* Fix vec[i].h pointers */
      int j;
      for (j = 0; j < getdtablesize (); j++)
        if (vec[j].h)
          vec[j].h = (fhandler_base *) &vec[j].item;
    } 
  return -1;
}

void
hinfo_vec::release (int fd)
{
  vec[fd].h = 0;
}

void
hinfo_vec::clearout (void)
{
  for (int i = 0; i < getdtablesize(); i++)
    {
      release (i);
    }
}

void 
hinfo_vec::init_std_file_from_handle (int fd, HANDLE handle, int bin,
					int access, const char *name)
{
  /* Check to see if we're being redirected - if not then
     we open then as consoles */
  if (fd == 0 || fd == 1 || fd == 2)
    {
      /* See if we can consoleify it  - if it is a console,
       don't open it in binary.  That will screw up our crlfs*/
      CONSOLE_SCREEN_BUFFER_INFO buf;
      if (GetConsoleScreenBufferInfo (handle, &buf))
	{
	  bin = 0;
	  if (ISSTATE(myself, PID_USETTY))
	    name = "/dev/tty";
	  else
	    name = "/dev/conout";
	}
      if (FlushConsoleInputBuffer (handle))
	{
	  bin = 0;
	  if (ISSTATE(myself, PID_USETTY))
	    name = "/dev/tty";
	  else
	    name = "/dev/conin";
	}
    }
  MARK();

  fhandler_base *res = build_fhandler (name, fd, handle);
  res->init (handle, bin, access, name);
  paranoid_printf ("init_std_file_from %d\n", handle);
}

static inline int
digits (const char *s)
{
  for (; *s != '\0'; s++)
    if (! isdigit ((unsigned char) *s))
      return 0;
  return 1;
}

fhandler_base *
hinfo_vec::build_fhandler (const char *name, int fd, HANDLE handle)
{
  CONSOLE_SCREEN_BUFFER_INFO buf;
  DCB dcb;
  struct sockaddr sa;
  int sal;

  sal = sizeof(sa);
  if (strcmp (name, "/dev/tty") == 0)
    {
      if (NOTSTATE(myself, PID_USETTY))
	vec[fd].h = new (&vec[fd].item) fhandler_console (name);
      else
	{
	  int ttynum = myself->ctty;
	  char buf[20];
	  sprintf (buf, "/dev/tty%d", ttynum);
	  vec[fd].h = new (&vec[fd].item) fhandler_tty_slave (ttynum, buf);
	}
    }
  else if (strncmp (name, "/dev/tty", 8) == 0 && digits (name + 8))
    {
      int ttynum = atoi (name + 8);
      vec[fd].h = new (&vec[fd].item) fhandler_tty_slave (ttynum, name);
    }
  else if (strcmp (name, "/dev/ptmx") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_pty_master (name);
    }
  else if (GetNumberOfConsoleInputEvents (handle, (DWORD *) &buf)
	   || strcmp (name, "/dev/conin") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_console (name);
    }
  else if (GetConsoleScreenBufferInfo (handle, &buf)
	   || strcmp (name, "/dev/conout") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_console (name);
    }
  else if (strcmp (name, "/dev/null") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_dev_null ();
    }
  else if (strcmp (name, "/dev/fd0") == 0
	   || strcmp (name, "/dev/fd1") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_dev_floppy (name);
    }
  else if (strcmp (name, "/dev/st0") == 0
	   || strcmp (name, "/dev/st1") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_dev_tape (name);
    }
  else if (GetCommState (handle, &dcb) || strncmp (name,"com1", 4)  == 0
	   || strncmp (name,"com2",4)  == 0
	   || strncmp (name,"com3",4)  == 0
	   || strncmp (name,"com4",4)  == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_tty (name);
    }
  else if (i_getpeername && !(*i_getpeername) ((SOCKET) handle, &sa, &sal)
	   || strcmp (name, "/dev/tcp") == 0
	   || strcmp (name, "/dev/udp") == 0
	   || strcmp (name, "/dev/streamsocket") == 0
	   || strcmp (name, "/dev/dgsocket") == 0)

    {
      vec[fd].h = new (&vec[fd].item) fhandler_socket
					((unsigned int) handle, name);
    }
  else if ((GetFileType (handle) == FILE_TYPE_PIPE)
	   || strcmp (name, "piper") == 0
	   || strcmp (name, "pipew") == 0)
    {
      vec[fd].h = new (&vec[fd].item) fhandler_pipe (name);
    }
  else
    {
      vec[fd].h = new (&vec[fd].item) fhandler_disk_file (name);
    }
out:
  return vec[fd].h;
}

/* We're about to turn this process into another one.  */

void
hinfo_vec::dup_for_exec (void)
{
  for (int i = 0; i < getdtablesize(); i++) 
    {
      if (vec[i].is_open ())
	{
	  if (vec[i].h->get_close_on_exec())
	    _close (i);
	}
    }
}

/* We're copying the state from this process to another one,
   Duplicate all the handles we have open into the space
   of the new child.

   The vec is that of the parents's, and we're passed the child's vec. */

void
hinfo_vec::dup_for_fork (hinfo_vec *child)
{
  /* Copy the hmap info from the parent. */
  debug_printf ("dup_for_fork\n");

  for (int i = 0; i < getdtablesize(); i++) 
    {
      /* Do a bitwise copy */
      if (vec[i].h) 
	{
	  child->vec[i].h = (fhandler_base *)&child->vec[i].item;
	  memcpy (child->vec[i].h, vec[i].h,  sizeof (vec[i].item));
	  child->vec[i].h->dup_for_fork ();
	}
      else 
	{
	  child->vec[i].h = 0;
	}
    }
}

int
hinfo_vec::dup2 (int oldfd, int newfd)
{
  int res = -1;

  debug_printf ("dup2 (%d, %d);\n", oldfd, newfd);
  
  if (not_open (oldfd) || newfd < 0 || newfd >= getdtablesize())
    {
      set_errno (EBADF);
      goto done;
    }
  
  if (newfd == oldfd)
    {
      res = newfd;
      goto done;
    }
  
  if (vec[newfd].h)
    {
      _close (newfd);
    }
  
  vec[newfd].h = (fhandler_base *)&vec[newfd].item;
  vec[newfd].item = vec[oldfd].item;
  if(vec[oldfd].h->dup (vec[newfd].h) != 0)
    return -1;
  
  res = newfd;

 done:
  if (res >= 0)
    {
      syscall_printf ("%d = dup2 (%d, %d) (%d:%d)\n",
		     res, oldfd, newfd, res,
		     vec[res].h->get_handle ());
    }
  else
    {
      syscall_printf ("%d = dup2 (%d, %d)\n", res, oldfd, newfd);
    }

  MARK();
  return res;
}

void *
fhandler_base::operator new (size_t size, void *p)
{
  if (size > sizeof (fhandler_union)) 
    {
      small_printf ("fhandler_union too small!\n");
    }
  return p;
}

/*
 * Function to take an existant hinfo array
 * and linearize it into a memory buffer.
 * If memory buffer is NULL, it returns the size
 * of memory buffer needed to do the linearization.
 * On error returns -1.
 */

int
hinfo_vec::linearize_fd_array (unsigned char *buf, int buflen)
{
  int total_size = 0;
  int len, i;
  int number_of_fds = getdtablesize();

   debug_printf ("buf = %x, buflen = %d\n",
                      buf, buflen);

  /* Linearize int of number of fd's. */
  if((buf != 0) && (buflen < sizeof(int)))
    {
      small_printf("FATAL: linearize_fd_array exceeded buffer size on initial int\n");
      return -1;
    }
  if(buf != 0)
    {
      memcpy(buf, (char *)&number_of_fds, sizeof(int));
      buf += sizeof(int);
    }
  total_size += sizeof(int);

  /*
   * Now linearize each open fd (write a 0xff byte for a closed fd).
   * Write the name of the open fd first (null terminated). This
   * allows the de_linearizeing code to determine what kind of fhandler_xxx
   * to create.
   */

  for(i = 0; i < getdtablesize(); i++)
    {
      if(vec[i].is_open())
        {
          debug_printf ("linearizing open fd %d:%s\n" ,i, vec[i].h->get_name());

          /* Write the internal name of the fd */
          char *name = (char *)vec[i].h->get_name();
          len = strlen(name) + 1;
          total_size += len;
          if(buf != 0)
            {
              strcpy((char *)buf, name);
              buf += len;
            }
          len = vec[i].h->linearize(buf);
          debug_printf ("len was %d\n", len);
          if(len < 0)
            {
              small_printf("linearize_fd_array failed on fd %d\n", i);
              return -1;
            }
        }
      else
        {
        debug_printf ("linearizing closed fd %d\n",i);
        /* To linearize a closed fd just write a byte of 0xff */
        if(buf != 0)
          *buf = 0xff;
        len = 1;
        }
      total_size += len;
      if(buf != 0)
        buf += len;
      if((buflen != 0 ) && (total_size > buflen))
        {
          small_printf("FATAL: linearize_fd_array exceeded buffer size on fd %d\n", i);
          return -1;
        }
    }
  return total_size;
}

/*
 * Function to take a linearized hinfo array in a memory buffer and
 * re-create the original hinfo array.
 */

LPBYTE
hinfo_vec::de_linearize_fd_array(LPBYTE buf)
{
  int len, i;

  debug_printf ("buf = %x\n", buf); 

  /* First get the number of fd's - use this to set the dtablesize.
     NB. This is the only place in the code this should be done !! 
  */
  int number_of_fds = 0;

  memcpy((char *)&number_of_fds, buf, sizeof(int));
  buf += sizeof(int);

  setdtablesize(number_of_fds);

  /* First create the hinfo's we are de-linearizing into. */ 
  vec = new hinfo [ number_of_fds ];

  if(vec == 0)
    {
      small_printf("de_linearize_fd_array: out of memory !\n");
      return NULL;
    } 

  debug_printf ("number_of_fds = %d, vec = %x\n", 
                     number_of_fds, vec); 

  for(i = 0; i < number_of_fds; i++)
    {
      /* 0xFF means closed */
      if(*buf == 0xff)
        {
          vec[i].clearout();
          ++buf;
          debug_printf ("closed fd = %d\n", i); 
          continue;
        }
      /* fd was open - de_linearize it ! */
      /* First get the type - this is a null terminated char array used to
         pass to build_fhandler. */
      int str_len = strlen((char *)buf) + 1;

      debug_printf ("open fd = %d, %s\n", 
                     i, buf); 

      fhandler_base *new_fh = build_fhandler((const char *)buf, i, NULL);
      buf += str_len;
      len = new_fh->de_linearize(buf);

      debug_printf ("len = %d\n", len + str_len); 

      buf += len;
    }
  return buf;
}
