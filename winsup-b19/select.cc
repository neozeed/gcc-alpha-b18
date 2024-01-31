/* select.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

   Written by Jeremy Allison of Cygnus Support.
   jra@cygnus.com

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

/*
 * The following line means that the BSD socket
 * definitions for fd_set, FD_ISSET etc. are used in this
 * file.
 */

#define  __INSIDE_CYGWIN_NET__

#include "winsup.h"
#include <sys/socket.h>
#include <netdb.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

/*
 * The following line means that the Win32 Winsock
 * definitions for fd_set, FD_ISSET etc. are *NOT *used in this
 * file.
 */

#define __INSIDE_CYGWIN32__
#include <mywinsock.h>

extern int (*i___WSAFDIsSet) (SOCKET, fd_set *) PASCAL;
extern int (*i_WSAGetLastError) (void) PASCAL;
extern int (*i_select) (int nfds, fd_set *readfds, fd_set *writefds,
                 fd_set *exceptfds, const struct timeval *timeout) PASCAL;
extern SOCKET (*i_socket) (int af, int type, int protocol) PASCAL;
extern int (*i_closesocket) (SOCKET s) PASCAL;

/*
 * Use this struct to interface to
 * the system provided select.
 */

typedef struct winsock_fd_set
{
  unsigned short fd_count;
  HANDLE fd_array[1]; /* Dynamically allocated. */
} winsock_fd_set;

/*
 * Define the Win32 winsock definitions to have a prefix WINSOCK_
 * so we can be explicit when we are using them.
 */

#define WINSOCK_FD_ISSET(fd, set) (*i___WSAFDIsSet) ((SOCKET)fd, (fd_set *)set)
#define WINSOCK_FD_SET(fd, set) do { \
               (set)->fd_array[(set)->fd_count++]=fd;\
} while(0)
#define WINSOCK_FD_ZERO(set) ((set)->fd_count=0)
#define WINSOCK_FD_CLR(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < (set)->fd_count ; __i++) { \
        if ((set)->fd_array[__i] == fd) { \
            while (__i < (set)->fd_count-1) { \
                (set)->fd_array[__i] = \
                    (set)->fd_array[__i+1]; \
                __i++; \
            } \
            (set)->fd_count--; \
            break; \
        } \
    } \
} while(0)

/*
 * All these defines below should be in sys/types.h
 * but because of the includes above, they may not have
 * been included. We create special UNIX_xxxx versions here.
 */

#ifndef NBBY
#define NBBY 8    /* number of bits in a byte */
#endif /* NBBY */

/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */

typedef long fd_mask;
#define UNIX_NFDBITS (sizeof (fd_mask) * NBBY)       /* bits per mask */
#ifndef unix_howmany
#define unix_howmany(x,y) (((x)+((y)-1))/(y))
#endif

#define unix_fd_set fd_set

#define UNIX_FD_SET(n, p) \
         ((p)->fds_bits[(n)/UNIX_NFDBITS] |= (1L << ((n) % UNIX_NFDBITS)))
#define UNIX_FD_CLR(n, p) \
         ((p)->fds_bits[(n)/UNIX_NFDBITS] &= ~(1L << ((n) % UNIX_NFDBITS)))
#define UNIX_FD_ISSET(n, p) \
         ((p)->fds_bits[(n)/UNIX_NFDBITS] & (1L << ((n) % UNIX_NFDBITS)))
#define UNIX_FD_ZERO(p)      bzero((caddr_t)(p), sizeof (*(p)))

/*
 * Abstract Class to handle mapping cygwin32 fd's to SOCKETS/HANDLES.
 */

class fd_set_map
{
  private:
    fd_set_map (const fd_set_map&);
    fd_set_map operator = (const fd_set_map&);

  protected:
    int size_;
    int used_;

    unsigned short *unix_fd_array_;
    HANDLE *handle_array_;

    void add_pair (int fd, HANDLE h, int pos);
    void get_pair (int pos, HANDLE *h, int *fd) const
      { 
        *h = handle_array_[pos];
        *fd = unix_fd_array_[pos];
      }
    int get_fd (int pos) const { return unix_fd_array_[pos]; }
    HANDLE get_handle (int pos) const { return handle_array_[pos]; }
    int init_failed () const 
      {
        return ((unix_fd_array_ == 0) || (handle_array_ == 0));
      }

    virtual int create_arrays ();

public:
  fd_set_map (int size);
  virtual ~fd_set_map ();

  HANDLE *get_handle_array () { return handle_array_; }
  int get_fd_by_handle (HANDLE h) const;
  void remove_pair_by_handle (HANDLE);
  virtual int add (int fd, int is_write_handle);
  virtual int convert_to_unix_fdset (unix_fd_set *) = 0;
};

fd_set_map::fd_set_map (int size)
{
  size_ = size;
  used_ = 0;
  unix_fd_array_ = 0;
  handle_array_ = 0;
}

fd_set_map::~fd_set_map ()
{
  if (unix_fd_array_)
    delete [] unix_fd_array_;
  if (handle_array_)
    delete [] handle_array_;
}

/*
 * Add an fd/HANDLE mapping.
 * Create arrays must have been called.
 */

void fd_set_map::add_pair (int fd, HANDLE h, int pos)
{
  unix_fd_array_[pos] = fd;
  handle_array_[pos] = h;
}

int fd_set_map::get_fd_by_handle (HANDLE h) const
{
  for (int i = 0; i < used_; i++)
    if (h == handle_array_[i])
      return unix_fd_array_[i];

  return -1;
}
 
void fd_set_map::remove_pair_by_handle(HANDLE h)
{
  for (int i = 0; i < used_; i++)
    if (h == handle_array_[i])
      {
        if (i < (used_ - 1))
          {
            memcpy ((char *) &handle_array_[i], 
                   (char *) &handle_array_[i + 1], 
                   (used_ - i - 1) * sizeof (HANDLE));
            memcpy ((char *) &unix_fd_array_[i], 
                   (char *) &unix_fd_array_[i + 1], 
                   (used_ - i - 1) * sizeof (unsigned short));
          }
        --used_;
      }
}

/* 
 * Lazy array creation.
 */

int fd_set_map::create_arrays ()
{
  unix_fd_array_ = new unsigned short[size_];
  handle_array_ = new HANDLE[size_];

  if (unix_fd_array_ == 0 || handle_array_ == 0)
    {
      set_errno (ENOMEM);
      return -1;
    }
  return 0;
}

/*
 * Add a cygwin32 fd to the set.
 */

int fd_set_map::add (int fd, int is_write_handle)
{
  /* Make sure fd is open */
  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      return -1;
    }

  /* Lazy array creation */
  if (unix_fd_array_ == 0 || handle_array_ == 0)
    {
      if (create_arrays ())
        return -1;
    }

  hinfo_vec *hvec = &myself->hmap;
  HANDLE h = is_write_handle ? (*hvec) [fd].h->get_output_handle () : 
                           (*hvec) [fd].h->get_input_handle ();

  add_pair (fd, h, used_);

  select_printf ("fd %d, handle %d at pos %d\n",
                fd, h, used_);
  ++used_;

  return 0;
}

/*
 * Concrete classes for sockets, handles, read/write and except
 * always readies.
 */

class fd_socket_map : public fd_set_map
{
  private:

    winsock_fd_set *win_fd_set_;
    int handle_is_in_set (HANDLE) const;

  protected:

    virtual int create_arrays ();

  public:

    fd_socket_map (int size) : fd_set_map (size) { win_fd_set_ = 0; }
    virtual ~fd_socket_map () { delete win_fd_set_; }
    virtual int convert_to_unix_fdset (unix_fd_set *unix_set);
    virtual int add (int fd, int is_write_handle);
    winsock_fd_set *get_winsock_fd_set ()
      {
        return (winsock_fd_set *) win_fd_set_;
      }
  };

int fd_socket_map::create_arrays ()
{
  win_fd_set_ = (winsock_fd_set *)
        new char[sizeof (winsock_fd_set) + ((size_ - 1) * sizeof (HANDLE))];

  if (win_fd_set_ == 0)
    {
      set_errno (ENOMEM);
      return -1;
    }
  win_fd_set_->fd_count = 0;

  fd_set_map::create_arrays ();
}
  
int fd_socket_map::add (int fd, int is_write_handle)
{
  /* Make sure fd is open */
  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      return -1;
    }

  /* Lazy array creation */
  if (win_fd_set_ == 0)
    {
      if (create_arrays ())
        return -1;
    }

  hinfo_vec *hvec = &myself->hmap;
  HANDLE h = is_write_handle ? (*hvec) [fd].h->get_output_handle () :
                               (*hvec) [fd].h->get_input_handle ();

  win_fd_set_->fd_array[win_fd_set_->fd_count++] = h;

  fd_set_map::add (fd, is_write_handle);
}

/*
 * Routine to check if a given handle is in the winsock fd_set.
 */

int
fd_socket_map::handle_is_in_set (HANDLE h) const
{
  int i;

  for (i = 0; i < win_fd_set_->fd_count; i++)
    if (h == win_fd_set_->fd_array[i])
      return 1;

  return 0;
}

/*
 * Convert to a unix fd_set from a set of sockets.
 * Returns the number of unix fd's set.
 * This is complicated by the fact the the winsock select actually
 * changes the contents of the win_fd_set_ array. Thus we must
 * set only the fd's corresponding to the handles in the
 * win_fd_set_ array, and clear all others.
 */

int
fd_socket_map::convert_to_unix_fdset (unix_fd_set *unix_set)
{
  if (unix_set == 0)
    return 0;

  int i;
  int ret = 0;

  if (used_)
    select_printf ("fd_count = %d\n",
                win_fd_set_->fd_count);
  else
    select_printf ("!used_\n");

  for (i = 0; i < used_; i++)
    {
      HANDLE h;
      int fd;

      get_pair (i, &h, &fd);

      select_printf ("checking handle %d\
fd %d\n", h, fd);

      if (handle_is_in_set (h) && WINSOCK_FD_ISSET (h, win_fd_set_))
        {
          select_printf ("\
entry %d was winsock set, setting %d into unix_set\n", i, fd); 

          UNIX_FD_SET (fd, unix_set);
          ++ret;
        }
      else
        {
          select_printf ("\
entry %d was winsock clear, clearing %d from unix_set\n", i, fd); 

          UNIX_FD_CLR (fd, unix_set);
        }
    }

  return ret;
}

class fd_handler_map : public fd_set_map
{
  public:
    fd_handler_map (int size) : fd_set_map (size) { }
    virtual int convert_to_unix_fdset (unix_fd_set *unix_set);
};

/*
 * Convert to a unix fd_set from a set of handles.
 * Returns the number of unix fd's set.
 * WaitForMultipleObjects doesn't change
 * the array passed to it.
 */

int fd_handler_map::convert_to_unix_fdset (unix_fd_set *unix_set)
{
  if (unix_set == 0)
    return 0;

  int i;
  int ret = 0;

  for (i = 0; i < used_; i++)
    {
      /* Poll on the handle - nowait */
      switch (WaitForSingleObject (get_handle (i), 0))
        {
        case WAIT_OBJECT_0:
        case WAIT_ABANDONED:
          UNIX_FD_SET (get_fd (i), unix_set);
          ++ret;
          break;
        default:
          UNIX_FD_CLR (get_fd (i), unix_set);
          break;
        }
    }
  return ret;
}

class fd_pipe_map : public fd_set_map
{
  public:
    fd_pipe_map (int size) : fd_set_map (size) { }
    virtual int convert_to_unix_fdset (unix_fd_set *unix_set);
};

/*
 * Convert to a unix fd_set from a set of pipe handles.
 * Returns the number of unix fd's set.
 */

int fd_pipe_map::convert_to_unix_fdset (unix_fd_set *unix_set)
{
  if (unix_set == 0)
    return 0;

  int i;
  int ret = 0;

  for (i = 0; i < used_; i++)
    {
      unsigned n = 0;
      BOOL success;
      /* Poll on the handle - nowait */
      success = PeekNamedPipe (get_handle (i), NULL, 0, NULL, &n, NULL);
      if (n || !success)
        {
          UNIX_FD_SET (get_fd (i), unix_set);
          ++ret;
	}
      else
	{
          UNIX_FD_CLR (get_fd (i), unix_set);
        }
    }
  return ret;
}

/*
 * Special class to take care of console read events. Only
 * returns true when set event is true.
 */

class fd_read_console_map : public fd_set_map
{
  public:
    fd_read_console_map (int size) : fd_set_map (size) { }
    virtual int convert_to_unix_fdset (unix_fd_set *unix_set);
    int keydown_event_pending (HANDLE h);
};

int fd_read_console_map::keydown_event_pending (HANDLE h)
{
  DWORD num_events;

  /* Fail if can't read */
  if (GetNumberOfConsoleInputEvents (h, &num_events) == 0)
    return 0;

  DWORD i;
  for (i = 0; i < num_events; i++)
    {
      INPUT_RECORD input_rec;
      DWORD events_read;

      PeekConsoleInput (h, &input_rec, 1, &events_read);
      if ((input_rec.EventType == KEY_EVENT) &&
                    (input_rec.Event.KeyEvent.bKeyDown == TRUE))
        return 1;

      /* Read and discard the event */
      ReadConsoleInput (h, &input_rec, 1, &events_read);
    }
  return 0;
}

int fd_read_console_map::convert_to_unix_fdset (unix_fd_set *unix_set)
{
  if (unix_set == 0)
    return 0;

  int i;
  int ret = 0;

  /* Only return true if a keydown event is pending
     on the handle. */
  for (i = 0; i < used_; i++)
    {
      if (keydown_event_pending (get_handle (i))) 
        {
          UNIX_FD_SET (get_fd (i), unix_set);
          ++ret;
        }
      else
        UNIX_FD_CLR (get_fd (i), unix_set);
    }
  return ret;
}

/*
 * Class to deal with always ready fds.
 */

class fd_always_map : public fd_set_map
{
  public:
    fd_always_map (int size) : fd_set_map (size) { }
    virtual int convert_to_unix_fdset (unix_fd_set *unix_set);
};

int fd_always_map::convert_to_unix_fdset (unix_fd_set *unix_set)
{
  if (unix_set == 0)
    return 0;

  int i;

  for (i = 0; i < used_; i++)
    UNIX_FD_SET (get_fd (i), unix_set);

  return used_;
}

/*
 * Auto delete class for created fd_set_map classes.
 */

class auto_del_fd_set_map
{
  private:
    fd_set_map **to_del_;
    int next_;

  public:
    auto_del_fd_set_map (int size);
    int add (fd_set_map *map) { to_del_[next_++] = map; }
    ~auto_del_fd_set_map ();
    int ok () { return to_del_ != 0; }
};

auto_del_fd_set_map::auto_del_fd_set_map (int size)
{
  next_ = 0;
  to_del_ = new (fd_set_map *) [ size ];
}

auto_del_fd_set_map::~auto_del_fd_set_map ()
{
  int i;
  for (i = 0; i < next_; i++)
    delete to_del_[i];
  delete [] to_del_;
}

static fd_socket_map *read_socket_map;
static fd_socket_map *write_socket_map;
static fd_socket_map *except_socket_map;
static fd_pipe_map *read_pipe_map;

static int volatile stop_pipe_thread;
int number_of_read_pipes;
HANDLE pipe_select;
HANDLE pipe_done;
HANDLE pth = NULL;

DWORD
pipethread (DWORD *arg)
{
  while (1)
    {
      WaitForSingleObject (pipe_select, INFINITE);
      while (1)
	{
          unsigned n;

          for (int i = 0; i < number_of_read_pipes; i++)
	    {
	      BOOL success;
	      success = PeekNamedPipe (read_pipe_map->get_handle_array ()[i],
					 NULL, 0, NULL, &n, NULL);
	      if (stop_pipe_thread || n || !success)
	        goto done;
	    }
          Sleep (10);
	}
done:
      select_printf ("pipe event\n");
      SetEvent (pipe_done);
    }
}

SOCKET sock;
HANDLE start_select;
HANDLE select_done;
HANDLE sth = NULL;
int select_ret;

DWORD
selectthread (DWORD *arg)
{
  winsock_fd_set except, *e;
    
  while (1)
   {
     WaitForSingleObject (start_select, INFINITE);

        WINSOCK_FD_ZERO (&except);

        if (except_socket_map->get_winsock_fd_set ())
	  e = except_socket_map->get_winsock_fd_set ();
        else
	  e = &except;
        WINSOCK_FD_SET ((void *) sock, e);
        select_printf ("doing Win32 select\n");
        select_ret = (*i_select) (0,
                       (fd_set *) read_socket_map->get_winsock_fd_set (), 
                       (fd_set *) write_socket_map->get_winsock_fd_set (),
                       (fd_set *) e, 
                       NULL);

        select_printf ("Win32 select returned %d\n", select_ret);
        if (select_ret == -1)
          {
            select_printf ("error %d\n", (*i_WSAGetLastError) ());
          }
        SetEvent (select_done);
      }
}

/* 
 * The main select code. The fd_set pointers here are not taken as
 * given as we are not sure how large the fd_set arrays are in the client code.
 * We only look as far as the largest value of the n parameter.
 */

extern "C"
int
cygwin32_select (int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		     struct timeval *to)
{

  select_printf ("In cygwin32_select, n = %d, to = %x\n", n, to);
  if (to)
    select_printf ("cygwin32_select to->tv_sec = %d, to->tv_usec = %d\n",
        to->tv_sec, to->tv_usec);

  if (n == 0)
    {
degenerate:
      /*
       * Degenerate case - we are being used as a high
       * precision wait.
       */
      if (to == 0)
        {
          set_errno (EINVAL);
          return -1; /* Else we block forever... */
        }
      DWORD waittime = (to->tv_sec * 1000) + (to->tv_usec / 1000);

      select_printf ("degenerate case - wait = %d\n",
								waittime);
      Sleep (waittime);
      return 0;
    }

  /*
   * Iterate through the arrays, count how many fd's are set
   * in each of the read/write/except arrays.
   */

  int i;
  int total_read_number = 0;
  int total_write_number = 0;
  int total_except_number = 0;

  for (i = 0; i < n; i++)
    {
      if (readfds != 0)
        {
          if (UNIX_FD_ISSET (i, readfds))
            ++total_read_number;
        }
      if (writefds != 0)
        {
          if (UNIX_FD_ISSET (i, writefds))
            ++total_write_number;
        }
      if (exceptfds != 0)
        {
          if (UNIX_FD_ISSET (i, exceptfds))
            ++total_except_number;
        }
    }

  select_printf ("total_read_number = %d, total_write_number = %d, total_except_number = %d\n", total_read_number, total_write_number, total_except_number);

  if ((total_read_number == 0) && (total_write_number == 0) && 
                  (total_except_number == 0))
    {
       /* Degenerate case - just sleep. */
       goto degenerate;
    }

  int number_of_read_sockets = 0;
  int number_of_write_sockets = 0;
  int number_of_except_sockets = 0;

  /* We only treat read console and pipe handles differently than handles. */
  int number_of_read_consoles = 0;

  int number_of_read_handles = 0;
  int number_of_write_handles = 0;
  int number_of_except_handles = 0;

  int number_of_read_always_ready = 0;
  int number_of_write_always_ready = 0;
  int number_of_except_always_ready = 0;

  number_of_read_pipes = 0;

  /*
   * Create the fd_set_maps for the read/write/except sockets
   * handles, and always readies.
   * As we do no allocation until we actually add a fd
   * to this class then this doesn't waste much space.
   */

  read_socket_map = new fd_socket_map (total_read_number);
  write_socket_map = new fd_socket_map (total_write_number);
  except_socket_map = new fd_socket_map (total_except_number);

  fd_read_console_map *read_console_map = new fd_read_console_map (total_read_number);
  read_pipe_map = new fd_pipe_map (total_read_number);

  fd_set_map *read_handle_map = new fd_handler_map (total_read_number);
  fd_set_map *write_handle_map = new fd_handler_map (total_write_number);
  fd_set_map *except_handle_map = new fd_handler_map (total_except_number);

  fd_set_map *read_always_map = new fd_always_map (total_read_number);
  fd_set_map *write_always_map = new fd_always_map (total_write_number);
  fd_set_map *except_always_map = new fd_always_map (total_except_number);

  if (read_socket_map == 0 || write_socket_map == 0 ||
      except_socket_map == 0 || read_handle_map == 0 ||
      write_handle_map == 0 || except_handle_map == 0 ||
      read_always_map == 0 || write_always_map == 0 ||
      except_always_map == 0 || read_console_map == 0 ||
      read_pipe_map == 0)
    {
      set_errno (ENOMEM);
      return -1;
    }

  auto_del_fd_set_map adm (11);
  if (!adm.ok ())
    {
      set_errno (ENOMEM);
      return -1;
    }
  adm.add (read_socket_map);
  adm.add (write_socket_map);
  adm.add (except_socket_map);
  adm.add (read_handle_map);
  adm.add (read_console_map);
  adm.add (read_pipe_map);
  adm.add (write_handle_map);
  adm.add (except_handle_map);
  adm.add (read_always_map);
  adm.add (write_always_map);
  adm.add (except_always_map);

  hinfo_vec *hvec = &myself->hmap;

  for (i = 0; i < n; i++)
    {
      fhandler_base *fbp = (*hvec) [i].h;

      select_printf ("examining fd %d\n", i);

      if (readfds != 0)
        {
          if (UNIX_FD_ISSET (i, readfds))
            {
              if (NOT_OPEN_FD (i))
                {
                  set_errno (EBADF);
                  return -1;
                }
              /* Determine if we are socket, always ready, console, or handle. */
              if (fbp->is_socket ())
                {
                  if (read_socket_map->add (i, 0))
                    return -1;
                  ++number_of_read_sockets;
                  select_printf ("added fd %d to socket_read\n", i);
                }
              else if (fbp->always_read_ready ())
                {
                  if (read_always_map->add (i, 0))
                    return -1;
                  ++number_of_read_always_ready;
                  select_printf ("added fd %d to always_read\n", i);
                }
              /* We only check consoles on read */
              else if (fbp->is_console ())
                {
                  if (read_console_map->add (i, 0))
                    return -1;
                  ++number_of_read_consoles;
                  select_printf ("added fd %d to console_read\n", i);
                }
              else if (GetFileType (fbp->get_handle ()) == FILE_TYPE_PIPE)
                {
                  if (read_pipe_map->add (i, 0))
                    return -1;
                  ++number_of_read_pipes;
                  select_printf ("added fd %d to pipe_read\n", i);
                }
	      else
                {
                  if (read_handle_map->add (i, 0))
                    return -1;
                  ++number_of_read_handles;
                  select_printf ("added fd %d to handle_read\n", i);
                }
             }
         }
      if (writefds != 0)
        {
          if (UNIX_FD_ISSET (i, writefds))
            {
              if (NOT_OPEN_FD (i))
                {
                  set_errno (EBADF);
                  return -1;
                }
              /* Determine if we are socket, always ready, or handle. */
              if (fbp->is_socket ())
                {
                  if(write_socket_map->add (i,1))
                    return -1;
                  ++number_of_write_sockets;
                  select_printf ("added fd %d to socket_write\n", i);
                }
              else if (fbp->always_write_ready ())
                {
                  if (write_always_map->add (i,1))
                    return -1;
                  ++number_of_write_always_ready;
                  select_printf ("added fd %d to always_write\n", i);
                }
              else
                {
                  if (write_handle_map->add (i,1))
                    return -1;
                  ++number_of_write_handles;
                  select_printf ("added fd %d to handle_write\n", i);
                }
             }
         }
      if (exceptfds != 0)
        {
          if (UNIX_FD_ISSET (i, exceptfds))
            {
              if (NOT_OPEN_FD (i))
                {
                  set_errno (EBADF);
                  return -1;
                }
              /* Determine if we are socket, always ready, or handle. */
              if (fbp->is_socket ())
                {
                  if (except_socket_map->add (i,0))
                    return -1;
                  ++number_of_except_sockets;
                  select_printf ("added fd %d to socket_except\n", i);
                }
              else if (fbp->always_except_ready ())
                {
                  if (except_always_map->add (i,0))
                    return -1;
                  ++number_of_except_always_ready;
                  select_printf ("added fd %d to always_except\n", i);
                }
              else
                {
                  if (except_handle_map->add (i,0))
                    return -1;
                  ++number_of_except_handles;
                  select_printf ("added fd %d to handle_except\n", i);
                }
             }
         }
    }

  int socket_used = ((number_of_read_sockets != 0) || 
                     (number_of_write_sockets != 0) ||
                     (number_of_except_sockets != 0));
  int handle_used = ((number_of_read_handles != 0) ||
                     (number_of_write_handles != 0) ||
                     (number_of_except_handles != 0));
  int console_used = (number_of_read_consoles != 0);
  int pipe_used = (number_of_read_pipes != 0);
  int always_ready_used = ((number_of_read_always_ready != 0) ||
                           (number_of_write_always_ready != 0) ||
                           (number_of_except_always_ready != 0));

#if 0
  /* Look for easy to handle cases. One is where all
   * given fd's are sockets. In this case create the Win32 fd_set
   * and call win32 select. This should be the most common case.
   */

  if ((socket_used != 0) && (handle_used == 0) && (console_used == 0) &&
				(always_ready_used == 0) && (pipe_used == 0))
    {
      /* FIXME: The following casts to fd_set are bogus, because what we
         are actually returning is a winsock_fd_set *. However, as
         the prototype for select insists on fd_set, and they are
         pointers anyway, it won't hurt. GAG!
      */

      select_printf ("doing Win32 select\n");
    
      int ret = select (0, (fd_set *) read_socket_map->get_winsock_fd_set (),
                       (fd_set *) write_socket_map->get_winsock_fd_set (),
                       (fd_set *) except_socket_map->get_winsock_fd_set (),
                       to);

      select_printf ("Win32 select returned %d\n", ret);
    
      if (ret == SOCKET_ERROR)
        {
          return -1;
        }

      /* Now translate the winsock fd_set changes back into unix_fd_set
         values and return. */
      int myret = 0;

      myret += read_socket_map->convert_to_unix_fdset (readfds);
      myret += write_socket_map->convert_to_unix_fdset (writefds);
      myret += except_socket_map->convert_to_unix_fdset (exceptfds);

      /* Assert that myret == ret */
      if (ret != myret)
        {
          small_printf ("cygwin32_select: ERROR fd counts fail to match !\n");
          small_printf ("cygwin32_select: ret = %d, my_ret = %d\n",
							ret, myret);
        }
      return myret;
    }
#endif

  /* 
   * Next special case. If any of the always_ready fd's are set then
   * we must just poll all the handles and sockets as we know we will
   * be returning without a timeout.
   */

  if (always_ready_used || (to && to->tv_sec == 0 && to->tv_usec == 0))
    {
      int myret = 0;

      if (socket_used)
        {
          struct timeval myto = {0, 0};

	  if (NOTSTATE(myself, PID_SOCKETS_USED))
	    winsock_init ();

          int ret = (*i_select) (0,
                       (fd_set *) read_socket_map->get_winsock_fd_set (),
                       (fd_set *) write_socket_map->get_winsock_fd_set (),
                       (fd_set *) except_socket_map->get_winsock_fd_set (),
                       &myto);

          if (ret == SOCKET_ERROR)
            return -1;

          /* Now translate the winsock fd_set changes back 
             into unix_fd_set values. */

          myret += read_socket_map->convert_to_unix_fdset (readfds);
          myret += write_socket_map->convert_to_unix_fdset (writefds);
          myret += except_socket_map->convert_to_unix_fdset (exceptfds);
      
          if (ret != myret)
            {
              small_printf (
                  "cygwin32_select:case 2: ERROR fd counts fail to match !\n");
              small_printf ("cygwin32_select: ret = %d, my_ret = %d\n", 
                            ret, myret);
            }
         }

      /* Poll the console handles */
      myret += read_console_map->convert_to_unix_fdset (readfds);

      /* Poll the pipe handles */
      myret += read_pipe_map->convert_to_unix_fdset (readfds);

      /* Now poll all the read/write/except handles */
      myret += read_handle_map->convert_to_unix_fdset (readfds);
      myret += write_handle_map->convert_to_unix_fdset (writefds);
      myret += except_handle_map->convert_to_unix_fdset (exceptfds);
      
      /* And add in all the always ready handles */
      myret += read_always_map->convert_to_unix_fdset (readfds);
      myret += write_always_map->convert_to_unix_fdset (writefds);
      myret += except_always_map->convert_to_unix_fdset (exceptfds);

      return myret;
    }

  /*
   * Third case - handles and sockets set.
   */

  if ((socket_used !=0 || handle_used != 0 || console_used != 0 || pipe_used != 0) &&
	 (always_ready_used == 0))
    {
      /*
       * Clear out the descriptor sets in case we
       * return with timeout (thanks to Sergey Okhapkin for
       * fixing this one). Restore sets if select was interrupted by a signal.
       */
      fd_set save_readfds, save_writefds, save_exceptfds;

      if (readfds)
       {
         save_readfds = *readfds;
          UNIX_FD_ZERO (readfds);
       }
      if (writefds)
       {
         save_writefds = *writefds;
          UNIX_FD_ZERO (writefds);
       }
      if (exceptfds)
       {
         save_exceptfds = *exceptfds;
          UNIX_FD_ZERO (exceptfds);
       }

      /*
       * Win32 has no concept of differing handle states,
       * read/write/except. Just do a wait on all of them.
       * Currently we don't expect there to be more than MAXIMUM_WAIT_OBJECTS
       * handles to be set over all the read/write and except fd sets.
       * If there are we currently fail. We could cope by using a similar
       * technique as the handle and socket method below, but I think
       * this will be so rare as to not warrent the extra code.
       */
      int num_handles = number_of_read_handles + number_of_write_handles +
                        number_of_except_handles + number_of_read_consoles + 
					socket_used + pipe_used + 1;

      if (num_handles > MAXIMUM_WAIT_OBJECTS)
        {
          /* Oops - punt. */
          set_errno (EINVAL);
          return -1;
        }

      HANDLE *harray = new HANDLE[num_handles];
      if (harray == 0)
        {
          set_errno (ENOMEM);
          return -1;
        }
      /* Copy the handle arrays from console_handle_map, read_handle_map, write_handle_map and
         except_handle_map. */

      if (number_of_read_consoles)
        memcpy ((char *) harray,
                   read_console_map->get_handle_array (),
                   number_of_read_consoles * sizeof (HANDLE));
      if (number_of_read_handles)
        memcpy ((char *) &harray[number_of_read_consoles], 
                   read_handle_map->get_handle_array (),
                   number_of_read_handles * sizeof (HANDLE));
      if (number_of_write_handles)
        memcpy ((char *) &harray[number_of_read_consoles + number_of_read_handles],
                   write_handle_map->get_handle_array (),
                   number_of_write_handles * sizeof (HANDLE));
      if (number_of_except_handles)
        memcpy ((char *) &harray[number_of_read_consoles + number_of_read_handles+number_of_write_handles],
                   except_handle_map->get_handle_array (),
                   number_of_except_handles * sizeof (HANDLE));

      if (pipe_used)
        {
          DWORD ptid;

	  if (pth == NULL)	/* First select call */
            {
	      pth = CreateThread (NULL, 0, pipethread, &pipe_used, 0, &ptid);
	      if (pth == NULL)
                {
                  __seterrno ();
                  delete [] harray;
	          select_printf ("cannot create pipe thread\n");
                  return -1;
	        }
              CloseHandle (pth);

	      pipe_select = CreateEventA (NULL, FALSE, FALSE, NULL);

	      if (pipe_select == NULL)
                {
                  __seterrno ();
                  delete [] harray;
	          select_printf ("cannot create pipe_select\n");
	          pth = NULL;
                  return -1;
	        }
	      pipe_done = CreateEventA (NULL, TRUE, FALSE, NULL);

	      if (pipe_done == NULL)
                {
                  __seterrno ();
                  delete [] harray;
	          select_printf("cannot create pipe_done\n");
	          pth = NULL;
	          CloseHandle (pipe_select);
                  return -1;
	        }
            }
	  stop_pipe_thread = 0;

          harray[number_of_read_consoles + number_of_read_handles +
	      number_of_write_handles + number_of_except_handles] =
							pipe_done;
	  SetEvent (pipe_select);
	}

      if (socket_used)
        {
	  DWORD stid;

	  if (sth == NULL)	/* First select call */
            {
	      sth = CreateThread (NULL, 0, selectthread, &socket_used,
								0, &stid);
	      if (sth == NULL)
                {
                  __seterrno ();
                  delete [] harray;
	          select_printf ("cannot create socket thread\n");
                  return -1;
	        }
              CloseHandle (sth);

	      start_select = CreateEventA (NULL, FALSE, FALSE, NULL);

	      if (start_select == NULL)
                {
                  __seterrno ();
                  delete [] harray;
	          select_printf ("cannot create start_select\n");
	          sth = NULL;
                  return -1;
	        }
	      select_done = CreateEventA (NULL, TRUE, FALSE, NULL);

	      if (select_done == NULL)
                {
                  __seterrno ();
                  delete [] harray;
	          select_printf("cannot create select_done\n");
	          sth = NULL;
	          CloseHandle (start_select);
                  return -1;
	        }
            }
	  if ((sock = (*i_socket) (PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
            {
              __seterrno ();
              delete [] harray;
	      select_printf ("cannot create socket\n");
              return -1;
	    }
          harray[number_of_read_consoles + number_of_read_handles +
	      number_of_write_handles + number_of_except_handles + 
					pipe_used] = select_done;
	  SetEvent (start_select);
        }

      harray[number_of_read_consoles + number_of_read_handles +
	  number_of_write_handles + number_of_except_handles +
			socket_used + pipe_used] = signal_arrived;

      DWORD waittime;

      if (to == 0)
        waittime = INFINITE;
      else
        waittime = (to->tv_sec * 1000) + (to->tv_usec / 1000);

      int myret = 1;

      /* May need this if we have a console read handle that fires bogusly */
      DWORD tickcount = 0;

      if (number_of_read_consoles != 0)
        tickcount = GetTickCount ();

      /* Label we may have to use if a console read handle is fired but
         no keydown event was found */
wait_again:

      DWORD wait_ret;
      switch ((wait_ret = WaitForMultipleObjects (num_handles, harray, 
                                              0, waittime)))
      {
        case WAIT_FAILED:
          __seterrno ();
          delete [] harray;
	  if (socket_used)
            {
              (*i_closesocket) (sock);
	      WaitForSingleObject (select_done, INFINITE);
	      ResetEvent (select_done);
	    }
	  if (pipe_used)
	    {
	      stop_pipe_thread++;
	      WaitForSingleObject (pipe_done, INFINITE);
	      ResetEvent (pipe_done);
	    }
	  select_printf ("wait failed\n");
          return -1;

        case WAIT_TIMEOUT:
          delete [] harray;
	  if (socket_used)
            {
	      (*i_closesocket) (sock);
	      WaitForSingleObject (select_done, INFINITE);
	      ResetEvent (select_done);
	    }
	  if (pipe_used)
	    {
	      stop_pipe_thread++;
	      WaitForSingleObject (pipe_done, INFINITE);
	      ResetEvent (pipe_done);
	    }
	  select_printf ("wait timeout\n");
          return 0;

        default:
          /*
           * If we have a WAIT_ABANDONED, map it to a 
           * WAIT_OBJECT + x.
           */
          if ((wait_ret >= WAIT_ABANDONED_0) && 
                         (wait_ret < WAIT_ABANDONED_0 + num_handles))
            wait_ret = WAIT_OBJECT_0 + (wait_ret - WAIT_ABANDONED_0);

          /* Convert into an index into the harray */

          wait_ret -= WAIT_OBJECT_0;
	  select_printf ("after WMF: wait_ret=%d\n", wait_ret);

          /*
           * Determine if the handle that was signalled was within
           * the console_read/read/write or except set and set it in that set.
           * Handle console read ready as a special case as it may be bogus.
           * Remove the handle that became signalled, as we aren't
           * sure if it will remain so when we poll it.
           */

          HANDLE h = harray[wait_ret];

          /*
           * Special case console handling. Only return true if
           * a keydown event was pending, else reduce the timeout
           * and wait again.
           */

          if (wait_ret < number_of_read_consoles)
            {
              if (read_console_map->keydown_event_pending (h))
                {
                  /* A real event, set the unix fd as true and remove the
                     handle from the array we are going to poll. */
                  UNIX_FD_SET (read_console_map->get_fd_by_handle (h),
					readfds);
                  read_console_map->remove_pair_by_handle (h);
                }
              else
                {
	          select_printf ("nrc=%d\n", number_of_read_consoles);
                  /* Bogus event: check if we need to reduce timeout
                     and then wait again. */
                  if (waittime == INFINITE)
                    goto wait_again;

                  DWORD ticknow = GetTickCount ();
                  DWORD tickdelta;
                  /* This next part depends on DWORD being an unsigned
                     32 bit int */
                  if (ticknow < tickcount)
                    tickdelta = (((unsigned long) 0xFFFFFFFF) - tickcount) +
				ticknow;
                  else
                    tickdelta = ticknow - tickcount;

                  /* Make sure we don't make waittime wrap */
                  tickdelta = waittime < tickdelta ? waittime : tickdelta;
                  waittime -= tickdelta;
                  tickcount = ticknow; /* Reset the tickcount */
                  goto wait_again;
                }
            }
          else if (wait_ret < number_of_read_consoles + number_of_read_handles)
            {
              UNIX_FD_SET (read_handle_map->get_fd_by_handle (h), readfds);
              read_handle_map->remove_pair_by_handle (h);
            }
          else if (wait_ret < (number_of_read_consoles +
                         number_of_read_handles + number_of_write_handles))
            {
              UNIX_FD_SET (write_handle_map->get_fd_by_handle (h), writefds);
              write_handle_map->remove_pair_by_handle (h);
            }
          else if (wait_ret < (number_of_read_consoles +
			number_of_read_handles + number_of_write_handles +
			number_of_except_handles))
            {
              UNIX_FD_SET (except_handle_map->get_fd_by_handle (h), exceptfds);
              except_handle_map->remove_pair_by_handle (h);
            }
	  else if (pipe_used && wait_ret == (number_of_read_consoles +
			number_of_read_handles + number_of_write_handles +
			number_of_except_handles))
	    {
	      myret = 0;
	    }
	  else if (socket_used && wait_ret == (number_of_read_consoles +
			number_of_read_handles + number_of_write_handles +
			number_of_except_handles + pipe_used))
	    {
	      myret = select_ret;
	      (*i_closesocket) (sock);
	      if (myret == SOCKET_ERROR)
                {
	          delete [] harray;
		  if (pipe_used)
		    {
		      stop_pipe_thread++;
		      WaitForSingleObject (pipe_done, INFINITE);
		      ResetEvent (pipe_done);
		    }
		  select_printf ("Win32 select error\n");
                  return -1;
                }
      	      read_socket_map->convert_to_unix_fdset (readfds);
              write_socket_map->convert_to_unix_fdset (writefds);
              except_socket_map->convert_to_unix_fdset (exceptfds);
	    }
	  else	/* signal */
	    {
	      if (socket_used)
                {
                  (*i_closesocket) (sock);
	          WaitForSingleObject (select_done,INFINITE);
		  ResetEvent (select_done);
	        }
	      if (pipe_used)
	        {
	          stop_pipe_thread++;
		  WaitForSingleObject (pipe_done, INFINITE);
		  ResetEvent (pipe_done);
	        }
	      delete [] harray;
	      if (readfds)
                *readfds = save_readfds;
              if (writefds)
                *writefds = save_writefds;
              if (exceptfds)
                *exceptfds = save_exceptfds;
	      set_errno (EINTR);
	      select_printf ("signal\n");
	      return -1;
	    }
	  if (socket_used)
            {
	      (*i_closesocket) (sock);
	      WaitForSingleObject (select_done, INFINITE);
	      ResetEvent (select_done);
	    }
	  if (pipe_used)
	    {
	      stop_pipe_thread++;
	      WaitForSingleObject (pipe_done, INFINITE);
	      ResetEvent (pipe_done);
	    }

          /* Now poll all the console_read/read/write/except handles */
          myret += read_console_map->convert_to_unix_fdset (readfds);
          myret += read_pipe_map->convert_to_unix_fdset (readfds);
          myret += read_handle_map->convert_to_unix_fdset (readfds);
          myret += write_handle_map->convert_to_unix_fdset (writefds);
          myret += except_handle_map->convert_to_unix_fdset (exceptfds);

          delete [] harray;
	  select_printf ("returning %d\n", myret);
          return myret;
      }
    }
  /*
   * We should NEVER come here!
   */
  select_printf ("we shouldn't come here!\n");
  set_errno (EINVAL);
  return -1;
}
