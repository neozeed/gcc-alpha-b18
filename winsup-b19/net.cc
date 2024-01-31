/* net.cc: network-related routines.  

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

/*#define DEBUG_NEST_ON 1*/

#define  __INSIDE_CYGWIN_NET__

#include "winsup.h"
#include <netdb.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "registry.h"

#define __INSIDE_CYGWIN32__

#include <mywinsock.h>

/* We only want to initialize WinSock in a child process if socket handles are
inheritted. This global allows us to know whether this should be done or not */
int number_of_sockets = 0;

extern "C" {
int h_errno;
};

/* Handle of wsock32.dll */

HANDLE wsock32;

/* Pointers to wsock32.dll exports */
int (*i_WSAAsyncSelect) (SOCKET s, HWND hWnd, u_int wMsg, long lEvent) NO_COPY PASCAL;
int (*i_WSACleanup) (void) NO_COPY PASCAL;
int (*i_WSAGetLastError) (void) NO_COPY PASCAL;
int (*i_WSAStartup) (int wVersionRequired, LPWSADATA lpWSAData) NO_COPY PASCAL;
int (*i___WSAFDIsSet) (SOCKET, fd_set *) NO_COPY PASCAL;
SOCKET (*i_accept) (SOCKET s, struct sockaddr *addr,int *addrlen) NO_COPY PASCAL;
int (*i_bind) (SOCKET s, const struct sockaddr *addr, int namelen) NO_COPY PASCAL;
int (*i_closesocket) (SOCKET s) NO_COPY PASCAL;
int (*i_connect) (SOCKET s, const struct sockaddr *name, int namelen) NO_COPY PASCAL;
struct hostent * (*i_gethostbyaddr) (const char * addr, int, int) NO_COPY PASCAL;
struct hostent * (*i_gethostbyname) (const char * name) NO_COPY PASCAL;
int (*i_getpeername) (SOCKET s, struct sockaddr *name, int * namelen) NO_COPY PASCAL;
struct protoent * (*i_getprotobyname) (const char * name) NO_COPY PASCAL;
struct protoent * (*i_getprotobynumber) (int number) NO_COPY PASCAL;
struct servent * (*i_getservbyname) (const char * name, const char * proto) NO_COPY PASCAL;
struct servent * (*i_getservbyport) (int port, const char * proto) NO_COPY PASCAL;
int (*i_getsockname) (SOCKET s, struct sockaddr *name, int * namelen) NO_COPY PASCAL;
int (*i_getsockopt) (SOCKET s, int level, int optname,
		     char * optval, int *optlen) NO_COPY PASCAL;
unsigned long (*i_inet_addr) (const char * cp) NO_COPY PASCAL;
char * (*i_inet_ntoa) (struct in_addr in) NO_COPY PASCAL;
int (*i_ioctlsocket) (SOCKET s, long cmd, u_long *argp) NO_COPY PASCAL;
int (*i_listen) (SOCKET s, int backlog) NO_COPY PASCAL;
int (*i_recv) (SOCKET s, char * buf, int len, int flags) NO_COPY PASCAL;
int (*i_recvfrom) (SOCKET s, char * buf, int len, int flags,
		   struct sockaddr  *from, int * fromlen) NO_COPY PASCAL;
int (*i_select) (int nfds, fd_set *readfds, fd_set *writefds,
		 fd_set *exceptfds, const struct timeval *timeout) NO_COPY PASCAL;
int (*i_send) (SOCKET s, const char * buf, int len, int flags) NO_COPY PASCAL;
int (*i_sendto) (SOCKET s, const char  * buf, int len, int flags,
		 const struct sockaddr  *to, int tolen) NO_COPY PASCAL;
int (*i_setsockopt) (SOCKET s, int level, int optname,
		     const char * optval, int optlen) NO_COPY PASCAL;
int (*i_shutdown) (SOCKET s, int how) NO_COPY PASCAL;
SOCKET (*i_socket) (int af, int type, int protocol) NO_COPY PASCAL;

/* These calls are non-standard, and may not present in non-MS IP stacks */
SOCKET (*i_rcmd) (char **ahost, unsigned short inport, char *locuser,
		  char *remuser, char *cmd, SOCKET *fd2p) NO_COPY PASCAL;
SOCKET (*i_rexec) (char **host, unsigned short port, char *user,
		   char *passwd, char *cmd, SOCKET *fd2p) NO_COPY PASCAL;
SOCKET (*i_rresvport) (int *port) NO_COPY PASCAL;

/* Cygwin32 internal */
/* Initialize WinSock */
void
winsock_init ()
{
  WSADATA p;
  int res;

  if ((wsock32 = LoadLibrary ("wsock32.dll")) == NULL)
    api_fatal ("Can't load wsock32.dll! Have you installed TCP/IP?\n");
#define LOAD(name) if (((int (*)())i_##name = GetProcAddress (wsock32, #name)) == NULL) \
		     {                                                        \
			small_printf ("Can't link to %s\n", #name);           \
			ExitProcess (1);                                      \
		     }
#ifdef __alpha
#define LOADVoid(name) if ((i_##name = GetProcAddress (wsock32, #name)) == NULL) \
		     {                                                        \
			small_printf ("Can't link to %s\n", #name);           \
			ExitProcess (1);                                      \
		     }
#endif
  LOAD (WSAAsyncSelect)
#ifndef __alpha
  LOAD (WSACleanup)
  LOAD (WSAGetLastError)
#else
  LOADVoid (WSACleanup)
  LOADVoid (WSAGetLastError)
#endif
  LOAD (WSAStartup)
  LOAD (__WSAFDIsSet)
  LOAD (accept)
  LOAD (bind)
  LOAD (closesocket)
  LOAD (connect)
  LOAD (gethostbyaddr)
  LOAD (gethostbyname)
  LOAD (getpeername)
  LOAD (getprotobyname)
  LOAD (getprotobynumber)
  LOAD (getservbyname)
  LOAD (getservbyport)
  LOAD (getsockname)
  LOAD (getsockopt)
  LOAD (inet_addr)
  LOAD (inet_ntoa)
  LOAD (ioctlsocket)
  LOAD (listen)
  LOAD (recv)
  LOAD (recvfrom)
  LOAD (select)
  LOAD (send)
  LOAD (sendto)
  LOAD (setsockopt)
  LOAD (shutdown)
  LOAD (socket)

  res = (*i_WSAStartup) ((2<<8) |2, &p);

  debug_printf ("res %d\n", res);
  debug_printf ("wVersion %d\n", p.wVersion);
  debug_printf ("wHighVersion %d\n", p.wHighVersion);
  debug_printf ("szDescription %s\n",p.szDescription);
  debug_printf ("szSystemStatus %s\n",p.szSystemStatus);
  debug_printf ("iMaxSockets %d\n", p.iMaxSockets);
  debug_printf ("iMaxUdpDg %d\n", p.iMaxUdpDg);
  debug_printf ("lpVendorInfo %d\n", p.lpVendorInfo);

  if (FIONBIO  != REAL_FIONBIO)
    debug_printf ("****************  FIONBIO  != REAL_FIONBIO\n");

  myself->process_state |= PID_SOCKETS_USED;

  return;
  MARK();
}

static SOCKET DuplicateSocket (SOCKET s)
{
  /* Do not duplicate socket on Windows NT because of problems with
     MS winsock proxy server.
  */
  if (get_os_type () == winNT)
    return s;

  SOCKET newsock;
  if (DuplicateHandle (GetCurrentProcess(), (HANDLE) s,
			 GetCurrentProcess(), (HANDLE *) &newsock,
			 0, TRUE, DUPLICATE_SAME_ACCESS))
    {
      (*i_closesocket) (s);
      s = newsock;
    }
  else
    small_printf ("DuplicateHandle failed %d\n", GetLastError ());
  return s;
}

/* htonl: standards? */
extern "C"
unsigned long int
htonl (unsigned long int x)
{
  MARK();
  return   ((((x & 0x000000ffU) << 24) | 
	     ((x & 0x0000ff00U) <<  8) | 
	     ((x & 0x00ff0000U) >>  8) | 
	     ((x & 0xff000000U) >> 24)));
}

/* ntohl: standards? */
extern "C"
unsigned long int
ntohl (unsigned long int x)
{
  return htonl (x);
}

/* htons: standards? */
extern "C"
unsigned short
htons (unsigned short x)
{
  MARK();
  return   ((((x & 0x000000ffU) << 8) | 
	     ((x & 0x0000ff00U) >> 8)));
}

/* ntohs: standards? */
extern "C"
unsigned short
ntohs (unsigned short x)
{
  return htons (x);
}

/* Cygwin32 internal */
static void
dump_protoent (struct protoent *p)
{
  if (p)
    {
      debug_printf ("protoent %s %x %x\n", p->p_name, p->p_aliases, p->p_proto);
    }
}

/* exported as inet_ntoa: standards? */
extern "C"
char *
cygwin32_inet_ntoa (struct in_addr in) 
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("inet_ntoa");
  char *res = (*i_inet_ntoa) (in);
  out ("inet_ntoa");
  return res;
}

/* exported as inet_addr: standards? */
extern "C"
unsigned long
cygwin32_inet_addr (const char *cp) 
{ 
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("inet_addr");
  unsigned long res = (*i_inet_addr) (cp);
  out ("inet_addr");
  return res;
}

/* inet_netof is in the standard BSD sockets library.  It are useless
   for modern networks, since it assumes network values which are no
   longer meaningful, but some existing code calls it.  */

extern "C"
unsigned long
inet_netof (struct in_addr in)
{
  unsigned long i, res;

  in ("inet_netof");

  i = ntohl (in.s_addr);
  if (IN_CLASSA (i))
    res = (i & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT;
  else if (IN_CLASSB (i))
    res = (i & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT;
  else
    res = (i & IN_CLASSC_NET) >> IN_CLASSC_NSHIFT;

  out ("inet_netof");

  return res;
}

/* inet_makeaddr is in the standard BSD sockets library.  It are
   useless for modern networks, since it assumes network values which
   are no longer meaningful, but some existing code calls it.  */

extern "C"
struct in_addr
inet_makeaddr (int net, int lna)
{
  unsigned long i;
  struct in_addr in;

  in ("inet_makeaddr");

  if (net < IN_CLASSA_MAX)
    i = (net << IN_CLASSA_NSHIFT) | (lna & IN_CLASSA_HOST);
  else if (net < IN_CLASSB_MAX)
    i = (net << IN_CLASSB_NSHIFT) | (lna & IN_CLASSB_HOST);
  else if (net < 0x1000000)
    i = (net << IN_CLASSC_NSHIFT) | (lna & IN_CLASSC_HOST);
  else
    i = net | lna;

  in.s_addr = htonl (i);

  out ("inet_makeaddr");

  return in;
}

struct tl 
{
  int w;
  const char *s;
  int e;
};

static struct tl errmap[] =
{
 {WSAEWOULDBLOCK, "WSAEWOULDBLOCK", EWOULDBLOCK},
 {WSAEINPROGRESS, "WSAEINPROGRESS", EINPROGRESS},
 {WSAEALREADY, "WSAEALREADY", EALREADY},
 {WSAENOTSOCK, "WSAENOTSOCK", ENOTSOCK},
 {WSAEDESTADDRREQ, "WSAEDESTADDRREQ", EDESTADDRREQ},
 {WSAEMSGSIZE, "WSAEMSGSIZE", EMSGSIZE},
 {WSAEPROTOTYPE, "WSAEPROTOTYPE", EPROTOTYPE},
 {WSAENOPROTOOPT, "WSAENOPROTOOPT", ENOPROTOOPT},
 {WSAEPROTONOSUPPORT, "WSAEPROTONOSUPPORT", EPROTONOSUPPORT},
 {WSAESOCKTNOSUPPORT, "WSAESOCKTNOSUPPORT", ESOCKTNOSUPPORT},
 {WSAEOPNOTSUPP, "WSAEOPNOTSUPP", EOPNOTSUPP},
 {WSAEPFNOSUPPORT, "WSAEPFNOSUPPORT", EPFNOSUPPORT},
 {WSAEAFNOSUPPORT, "WSAEAFNOSUPPORT", EAFNOSUPPORT},
 {WSAEADDRINUSE, "WSAEADDRINUSE", EADDRINUSE},
 {WSAEADDRNOTAVAIL, "WSAEADDRNOTAVAIL", EADDRNOTAVAIL},
 {WSAENETDOWN, "WSAENETDOWN", ENETDOWN},
 {WSAENETUNREACH, "WSAENETUNREACH", ENETUNREACH},
 {WSAENETRESET, "WSAENETRESET", ENETRESET},
 {WSAECONNABORTED, "WSAECONNABORTED", ECONNABORTED},
 {WSAECONNRESET, "WSAECONNRESET", ECONNRESET},
 {WSAENOBUFS, "WSAENOBUFS", ENOBUFS},
 {WSAEISCONN, "WSAEISCONN", EISCONN},
 {WSAENOTCONN, "WSAENOTCONN", ENOTCONN},
 {WSAESHUTDOWN, "WSAESHUTDOWN", ESHUTDOWN},
 {WSAETOOMANYREFS, "WSAETOOMANYREFS", ETOOMANYREFS},
 {WSAETIMEDOUT, "WSAETIMEDOUT", ETIMEDOUT},
 {WSAECONNREFUSED, "WSAECONNREFUSED", ECONNREFUSED},
 {WSAELOOP, "WSAELOOP", ELOOP},
 {WSAENAMETOOLONG, "WSAENAMETOOLONG", ENAMETOOLONG},
 {WSAEHOSTDOWN, "WSAEHOSTDOWN", EHOSTDOWN},
 {WSAEHOSTUNREACH, "WSAEHOSTUNREACH", EHOSTUNREACH},
 {WSAENOTEMPTY, "WSAENOTEMPTY", ENOTEMPTY},
 {WSAEPROCLIM, "WSAEPROCLIM", EPROCLIM},
 {WSAEUSERS, "WSAEUSERS", EUSERS},
 {WSAEDQUOT, "WSAEDQUOT", EDQUOT},
 {WSAESTALE, "WSAESTALE", ESTALE},
 {WSAEREMOTE, "WSAEREMOTE", EREMOTE},
 {WSAEINVAL, "WSAEINVAL", EINVAL},
 {WSAEFAULT, "WSAEFAULT", EFAULT},
 { 0}
};

/* Cygwin32 internal */
static void
set_winsock_errno ()
{
  int i;
  int why  = (*i_WSAGetLastError) ();
  for (i = 0; errmap[i].w != 0; ++i)
    if (why == errmap[i].w)
      break;

  if (errmap[i].w != 0)
    {
      syscall_printf ("%d (%s) -> %d\n", 
		      why, errmap[i].s, errmap[i].e);
      set_errno (errmap[i].e);
    }
  else
    {
      syscall_printf ("unknown error %d!!\n",why);
      set_errno (EPERM);
    }
}

static struct tl host_errmap[] =
{
  {WSAHOST_NOT_FOUND, "WSAHOST_NOT_FOUND", HOST_NOT_FOUND},
  {WSATRY_AGAIN, "WSATRY_AGAIN", TRY_AGAIN},
  {WSANO_RECOVERY, "WSANO_RECOVERY", NO_RECOVERY},
  {WSANO_DATA, "WSANO_DATA", NO_DATA},
  { 0}
};

/* Cygwin32 internal */
static void
set_host_errno ()
{
  int i;

  int why = (*i_WSAGetLastError) ();
  for (i = 0; i < host_errmap[i].w != 0; ++i)
    if (why == host_errmap[i].w)
      break;

  if (host_errmap[i].w != 0)
    h_errno = host_errmap[i].e;
  else
    h_errno = NETDB_INTERNAL;
}

/* exported as getprotobyname: standards? */
extern "C"
struct protoent *
cygwin32_getprotobyname (const char *p)
{
  MARK();
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getprotobyname");

  struct protoent *res = (*i_getprotobyname) (p);
  if (!res)
    set_winsock_errno ();

  dump_protoent (res);
  out ("getprotobyname");
  return res;
}

/* exported as getprotobynumber: standards? */
extern "C"
struct protoent *
cygwin32_getprotobynumber (int number)
{
  MARK ();
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getprotobynumber");

  struct protoent *res = (*i_getprotobynumber) (number);
  if (!res)
    set_winsock_errno ();

  dump_protoent (res);
  out ("getprotobynumber");
  return res;
}

/* exported as socket: standards? */
extern "C"
int
cygwin32_socket (int af, int type, int protocol)
{
  int res = -1;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("socket");
  pinfo *p = myself;
  SOCKET soc;

  int fd = p->hmap.find_unused_handle (0);

  if (fd < 0)
    {
      set_errno (ENMFILE);
      goto done;
    }

  debug_printf ("socket (%d, %d, %d);\n", af, type, protocol);

  soc = (*i_socket) (af, type, protocol);

  if (soc == INVALID_SOCKET)
    {
      set_winsock_errno ();
      goto done;
    }

  soc = DuplicateSocket (soc);

  fhandler_socket *h;
  char *name;
  if(af == AF_INET)
      name = ( type == SOCK_STREAM ? "/dev/tcp" : "/dev/udp");
  else
      name = ( type == SOCK_STREAM ? "/dev/streamsocket" : "/dev/dgsocket");
    
  p->hmap.vec[fd].h =h = new (&p->hmap.vec[fd].item) fhandler_socket(soc, name);
  res = fd;

done:
  out ("socket");
  syscall_printf ("%d = socket (%d, %d, %d);\n", res, af, type, protocol);
  return res;
}

/* exported as sendto: standards? */
extern "C"
int
cygwin32_sendto (int fd, 
		 const void *buf,
		 int len,
		 unsigned int flags,
		 const struct sockaddr *to, 
		 int tolen)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("sendto");
  int res = (*i_sendto) (h->get_socket(), (const char *)buf, len, flags, to, tolen);
  if (res == SOCKET_ERROR) {
    set_winsock_errno ();
    res = -1;
  }
  out ("sendto");
  return res;
}

/* exported as recvfrom: standards? */
extern "C"
int
cygwin32_recvfrom (int fd, 
		   char *buf,
		   int len, 
		   int flags, 
		   struct sockaddr *from,
		   int *fromlen)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("recvfrom");

  debug_printf ("recvfrom %d\n", h->get_socket ());
  int res = (*i_recvfrom) (h->get_socket (), buf, len, flags, from, fromlen);
  if (res == SOCKET_ERROR) {
    set_winsock_errno ();
    res = -1;
  }

  out ("recvfrom");
  return res;
}

/* Cygwin32 internal */
fhandler_socket *
get (int fd)
{
  if (NOT_OPEN_FD (fd))
    {
      set_errno (EINVAL);
      return 0;
    }
  
  return myself->hmap.vec[fd].h->is_socket ();
}

/* exported as setsockopt: standards? */
extern "C"
int
cygwin32_setsockopt (int fd, 
		     int level,
		     int optname,
		     const void *optval, 
		     int optlen)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("setsockopt");
  fhandler_socket *h = get (fd);
  int res = -1;
  const char *name = "error";
  if (h) 
    {
      switch (optname)
	{
	case SO_DEBUG      :name="SO_DEBUG";
	case SO_ACCEPTCONN :name="SO_ACCEPTCONN";
	case SO_REUSEADDR  :name="SO_REUSEADDR";
	case SO_KEEPALIVE  :name="SO_KEEPALIVE";
	case SO_DONTROUTE  :name="SO_DONTROUTE";
	case SO_BROADCAST  :name="SO_BROADCAST";
	case SO_USELOOPBACK:name="SO_USELOOPBACK";
	case SO_LINGER    :name="SO_LINGER";
	case SO_OOBINLINE :name="SO_OOBINLINE";
	}
      
      res = (*i_setsockopt) (h->get_socket (), level, optname, (const char *)optval, optlen);
      
      if (optlen == 4)
	{
	  syscall_printf ("setsockopt optval=%x\n", *(long *)optval);
	}
      if (res)
	set_winsock_errno ();
    }

  out ("setsockopt");
  syscall_printf ("%d = setsockopt (%d, %d, %x (%s), %x, %d);\n",
		 res,
		 fd, 
		 level, optname,name, optval, optlen);
  return res;
}

/* exported as getsockopt: standards? */
extern "C"
int
cygwin32_getsockopt (int fd, 
		     int level,
		     int optname,
		     void *optval, 
		     int *optlen)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getsockopt");
  fhandler_socket *h = get (fd);
  int res = -1;
  const char *name = "error";
  if (h) 
    {
      switch (optname)
	{
	case SO_DEBUG      :name="SO_DEBUG";
	case SO_ACCEPTCONN :name="SO_ACCEPTCONN";
	case SO_REUSEADDR  :name="SO_REUSEADDR";
	case SO_KEEPALIVE  :name="SO_KEEPALIVE";
	case SO_DONTROUTE  :name="SO_DONTROUTE";
	case SO_BROADCAST  :name="SO_BROADCAST";
	case SO_USELOOPBACK:name="SO_USELOOPBACK";
	case SO_LINGER    :name="SO_LINGER";
	case SO_OOBINLINE :name="SO_OOBINLINE";
	}
      
      res = (*i_getsockopt) (h->get_socket (), level, optname, ( char *)optval, (int *)optlen);
      
      if (res)
	set_winsock_errno ();
    }

  out ("getsockopt");
  syscall_printf ("%d = getsockopt (%d, %d, %x (%s), %x, %d);\n",
		  res,
		  fd, 
		  level, optname,name, optval, optlen);
  return res;
}

/* exported as connect: standards? */
extern "C"
int
cygwin32_connect (int fd,
		  const struct sockaddr * name,
		  int namelen)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("connect");
  int res;
  fhandler_socket *s = get (fd);
  if (!s)
    {
      res = -1;
    }
  else
    {
      res = (*i_connect) (s->get_socket (), name, namelen);
      if (res)
	set_winsock_errno ();
      out ("connect");
    }
  return res;
}

/* exported as getservbyname: standards? */
extern "C"
struct servent *
cygwin32_getservbyname (const char *name, const char *proto)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getservbyname");
  struct servent *p = (*i_getservbyname) (name, proto);
  if (!p)
    set_winsock_errno ();

  syscall_printf ("%x = getservbyname (%s, %s);\n",
		 p, name, proto);
  out ("getservbyname");
  return p;
}

/* exported as getservbyport: standards? */
extern "C"
struct servent *
cygwin32_getservbyport (int port, const char *proto)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getservbyport");
  struct servent *p = (*i_getservbyport) (port, proto);
  if (!p)
    set_winsock_errno ();

  syscall_printf ("%x = getservbyport (%d, %s);\n",
		 p, port, proto);
  out ("getservbyport");
  return p;
}

/* exported as gethostbyname: standards? */
extern "C"
struct hostent *
cygwin32_gethostbyname (const char *name)
{
  MARK ();
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("gethostbyname");
  struct hostent *ptr = (*i_gethostbyname) (name);
  if (!ptr)
    {
      set_winsock_errno ();
      set_host_errno ();
    }
  else
    {
      debug_printf ("h_name %s\n", ptr->h_name);
      h_errno = 0;
    }
  out ("gethostbyname");
  return ptr;
}

/* exported as gethostbyaddr: standards? */
extern "C" 
struct hostent *
cygwin32_gethostbyaddr (const char *addr, int len, int type)
{
  MARK();
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("gethostbyaddr");
  struct hostent *ptr = (*i_gethostbyaddr) (addr, len, type);
  if (!ptr)
    {
      set_winsock_errno ();
      set_host_errno ();
    }
  else
    {
      debug_printf ("h_name %s\n", ptr->h_name);
      h_errno = 0;
    }
  out ("gethostbyaddr");
  return ptr;
}

/* Cygwin32 internal */

/**********************************************************************/
/* fhandler_socket */

fhandler_socket::fhandler_socket (unsigned int s, const char *name) : fhandler_base (name)
{
  set_handle ((HANDLE) s);
  debug_printf ("socket id %d\n", s);
  number_of_sockets++;
  set_flags (O_RDWR);
}

fhandler_socket::~fhandler_socket ()
{
  if (--number_of_sockets < 0)
    {
      number_of_sockets = 0;
      small_printf("socket count < 0!\n");
    }
}


int
fhandler_socket::write (const void *ptr, size_t len)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  int res = (*i_send) (get_socket (), (const char *) ptr, len, 0);
  if (res == SOCKET_ERROR)
    {
      set_winsock_errno ();
      if (get_errno () == ECONNABORTED || get_errno () == ECONNRESET)
	_raise (SIGPIPE);
    }
  return res;
}

/* Cygwin32 internal */
int
fhandler_socket::read (void *ptr, size_t len)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("read");
  int res = (*i_recv) (get_socket (), (char *) ptr, len, 0);
  if (res == SOCKET_ERROR)
    {
      set_winsock_errno ();
    }
  out ("read");
  return res;
}

/* exported as accept: standards? */
extern "C"
int
cygwin32_accept (int fd, struct sockaddr *peer, int *len)
{
  int res = -1;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("accept");
  fhandler_socket *s = get (fd);
  if (s)
    {
      pinfo *p = myself;
      int res_fd = p->hmap.find_unused_handle (0);
      if (res_fd == -1)
	{
	  /* FIXME: what is correct errno? */
	  set_errno (EMFILE);
	  goto done;
	}
      res = (*i_accept) (s->get_socket (), peer, len);
      if ((SOCKET)res == (SOCKET)INVALID_SOCKET)
	set_winsock_errno ();
      else
	{
	  res = DuplicateSocket (res);

	  fhandler_socket *h;
	  p->hmap.vec[res_fd].h = h = 
	       new (&p->hmap.vec[res_fd].item) fhandler_socket(res, s->get_name());
	  res = res_fd;
	}
    }
done:
  out ("accept");
  syscall_printf ("%d = accept (%d, %x, %x);\n", res, fd, peer, len);
  return res;
}

/* exported as bind: standards? */
extern "C"
int
cygwin32_bind (int fd, struct sockaddr *my_addr, int addrlen)
{
  int res = -1;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("bind");
  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_bind) (s->get_socket (), my_addr, addrlen);
      if (res)
	set_winsock_errno ();
    }
  out ("bind");
  syscall_printf ("%d = bind (%d, %x, %d);\n", res, fd, my_addr, addrlen);
  return res;
}

/* exported as getsockname: standards? */
extern "C"
int
cygwin32_getsockname (int fd, struct sockaddr *addr, int *namelen)
{
  int res = -1;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getsockname");
  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_getsockname) (s->get_socket (), addr, namelen);
      if (res)
	set_winsock_errno ();

    }
  out ("getsockname");
  syscall_printf ("%d = getsockname (%d, %x, %d);\n", res, fd, addr, namelen);
  return res;
}

/* exported as listen: standards? */
extern "C"
int
cygwin32_listen (int fd, int backlog)
{
  int res = -1;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("listen");

  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_listen) (s->get_socket (), backlog);
      if (res)
	set_winsock_errno ();
    }
  out ("listen");
  syscall_printf ("%d = listen (%d, %d);\n", res, fd, backlog);
  return res;
}

/* exported as shutdown: standards? */
extern "C"
int
cygwin32_shutdown (int fd, int how)
{
  int res = -1;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("shutdown");

  fhandler_socket *s = get (fd);
  if (s)
    {
      res = (*i_shutdown) (s->get_socket (), how);
      if (res)
	set_winsock_errno ();
    }
  out ("shutdown");
  syscall_printf ("%d = shutdown (%d, %d);\n", res, fd, how);
  return res;
}

/* exported as herror: standards? */
extern "C"
void
cygwin32_herror (const char *p)
{
  debug_printf ("********%d*************\n", __LINE__);
}

/* exported as send: standards? */
extern "C"
int
cygwin32_send (int fd, const void *buf, int len, unsigned int flags)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("send");

  int res = (*i_send) (h->get_socket (),(const char *) buf, len, flags);
  if (res == SOCKET_ERROR) {
    set_winsock_errno ();
    res = -1;
  }

#if 0
  for (int i =0; i < len; i++)
    {
      small_printf ("send %d %x %c\n", i, ((char *)buf)[i], ((char *)buf)[i]);
    }
#endif

  syscall_printf ("%d = send (%d, %x, %d, %x);\n", res, fd, buf, len, flags);

  out ("send");
  return res;
}

/* Cygwin32 internal */
int
fhandler_socket::close ()
{
  int res = 0;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  if ((*i_closesocket) (get_socket ())) 
    {
      set_winsock_errno ();
      res = -1;
    }

  return res;
}

/* exported as recv: standards? */
extern "C"
int
cygwin32_recv (int fd, void *buf, int len, unsigned int flags)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("recv");

  int res = (*i_recv) (h->get_socket (), (char *)buf, len, flags);
  if (res == SOCKET_ERROR)
    {
      set_winsock_errno ();
      res = -1;
    }

#if 0
  if (res > 0 && res < 200)
    {
      for (int i =0; i < res; i++)
	{
	  small_printf ("%d %x %c\n", i, ((char *)buf)[i], ((char *)buf)[i]);
	}
    }
#endif

  syscall_printf ("%d = recv (%d, %x, %x, %x)\n",res, fd, buf,len,flags);

  out ("recv");
  return res;
}

/* exported as getpeername: standards? */
extern "C"
int
cygwin32_getpeername (int fd, struct sockaddr *name, int *len)
{
  fhandler_socket *h = (fhandler_socket *) myself->hmap.vec[fd].h;
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  in ("getpeername");

  debug_printf ("getpeername %d\n", h->get_socket ());
  int res = (*i_getpeername) (h->get_socket (), name, len);
  if (res)
    set_winsock_errno ();

  out ("getpeername");
  debug_printf ("%d = getpeername %d\n", res, h->get_socket ());
  return res;
}

/* getdomainname: standards? */
extern "C"
int
getdomainname (char *domain, int len)
{
  reg_key sys;
  reg_key controlset;
  reg_key services;
  reg_key tcp;
  reg_key params;

  /* Are registry keys case sensitive? */

  if (sys.open ((get_os_type () == win95) ? "System" : "SYSTEM",
			 HKEY_LOCAL_MACHINE, KEY_READ) != ERROR_SUCCESS)
    {
      __seterrno ();
      return -1;
    }
  if (controlset.open ("CurrentControlSet", sys.get_key (),
					   KEY_READ) != ERROR_SUCCESS)
    {
      __seterrno ();
      return -1;
    }
  if (services.open ("Services", controlset.get_key (),
					    KEY_READ) != ERROR_SUCCESS)
    {
      __seterrno ();
      return -1;
    }
  /*
   * This next line only works for Win95 if the machine is configured
   * to use MS-TCP. If a third-party TCP is being used this will fail.
   * Question : On Win95, is there a way to portably check the TCP stack in use
   * and include paths for the Domain name in each ?
   * Punt for now and assume MS-TCP on Win95.
   */
  if (tcp.open ((get_os_type () == win95) ? "MSTCP" : "Tcpip",
		       services.get_key (), KEY_READ) != ERROR_SUCCESS)
    {
      __seterrno ();
      return -1;
    }
  if (params.open ("Parameters", tcp.get_key (), KEY_READ) != ERROR_SUCCESS)
    {
      __seterrno ();
      return -1;
    }
  if (params.get_string ("Domain", domain, len, "") != ERROR_SUCCESS)
    {
      __seterrno ();
      return -1;
    }

  return 0;
}

/* Cygwin32 internal */
/* Routines to get a struct ifconf for Windows 95 and NT.
 * 
 * It is unlikely Win95 will ever have more than one netcard, so
 * just do a gethostbyname.  If this succeeds, then we have this
 * interface plus a loopback.
 */
static int
get_win95_ifconf (struct ifconf *ifc)
{
  /* Assume machinename will fit in 255 bytes, we will fail if not.*/
  char name[256];

  /* Ensure we have space for two struct ifreqs, fail if not. */
  if (ifc->ifc_len < (2 * sizeof (struct ifreq)))
    {
      set_errno (EFAULT);
      return -1;
    }

  if (gethostname (name, sizeof (name)) == SOCKET_ERROR)
    {
      set_winsock_errno ();
      return -1;
    }
  /* Now do the gethostbyname call */
  struct hostent *he = (*i_gethostbyname) (name);
  if (he == 0)
    {
      set_winsock_errno ();
      return -1;
    }

  struct sockaddr_in *sa;
  struct ifreq *ifr = ifc->ifc_req; /* Union maps buffer to correct struct */
  /* Set up interface lo0 first */
  ifr++;
  strcpy (ifr->ifr_name, "lo0");
  memset (&ifr->ifr_addr, '\0', sizeof (ifr->ifr_addr));
  sa = (struct sockaddr_in *) &ifr->ifr_addr;
  sa->sin_family = AF_INET;
  sa->sin_port = 0;
  sa->sin_addr.s_addr = INADDR_LOOPBACK;

  /* Increment and set up the eth0 struct */
  strcpy (ifr->ifr_name, "eth0");
  memset (&ifr->ifr_addr, '\0', sizeof (ifr->ifr_addr));
  sa = (struct sockaddr_in *)&ifr->ifr_addr;
  sa->sin_family = AF_INET;
  sa->sin_port = 0;
  sa->sin_addr = *(struct in_addr *) he->h_addr;

  /* Set the correct length */
  ifc->ifc_len = 2 * sizeof (struct ifreq);
  return 0;
}

/* Cygwin32 internal */
/*
 * The same for Windows NT.
 *
 * FIXME: need to do this properly for NT but it is a pain.
 * Need to look at the Bind value in:
 * HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Linkage\
 * This is a REG_MULTI_SZ with strings of the form:
 * \Device\<Netcard>, where netcard is the name of the net device.
 * Then look under:
 * HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\<NetCard>\Parameters\Tcpip
 * at the IPAddress, Subnetmask and DefaultGateway values for the
 * required values.  We will eventually do this as NT is much more
 * likely than 95 to be multi-homed.
 *
 * For now, though, just punt and do the same as on 95.
 */
static int
get_winnt_ifconf (struct ifconf *ifc)
{
  return get_win95_ifconf (ifc);
}

/* Cygwin32 internal */
/*
 * Return the flags settings for an interface.
 * This is broken at the moment as it doesn't check
 * if the interfaces are really up or down, but can
 * Windows net interfaces really be down?  (Ignore the
 * Wan interfaces for now).
 */
static int
get_if_flags (struct ifreq *ifr)
{
  short flags = IFF_UP | IFF_NOTRAILERS | IFF_RUNNING;
  struct sockaddr_in *sa = (struct sockaddr_in *) &ifr->ifr_addr;
  if (sa->sin_addr.s_addr == INADDR_LOOPBACK)
      flags |= IFF_LOOPBACK;
  else
      flags |= IFF_BROADCAST;
  ifr->ifr_flags = flags;
  return 0;
}

/* Cygwin32 internal */
int
fhandler_socket::ioctl (int cmd, void *p)
{
  int res;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  switch (cmd)
    {
    case SIOCGIFCONF:
      {
	struct ifconf *ifc = (struct ifconf *) p;
	if (ifc == 0)
	  {
	    set_errno (EINVAL);
	    return -1;
	  }
	if (get_os_type () == winNT)
	  res = get_winnt_ifconf (ifc);
	else
	  res = get_win95_ifconf (ifc);
	break;
      }
    case SIOCGIFFLAGS:
      {
	struct ifreq *ifr = (struct ifreq *) p;
	if (ifr == 0)
	  {
	    set_errno (EINVAL);
	    return -1;
	  }
	res = get_if_flags (ifr);
	break;
      }
    case FIOASYNC:
      {
#define ASYNC_MASK      (FD_READ|FD_WRITE|FD_OOB|FD_ACCEPT|FD_CONNECT)
	res = (*i_WSAAsyncSelect) (get_socket (), gethwnd (), WM_ASYNCIO,
		*(int *) p ? ASYNC_MASK : 0);
	syscall_printf ("Async I/O on socket %s\n",
		*(int *) p ? "started" : "cancelled");
	set_async (*(int *) p);
	break;
      }
    default:
      {
      /* We must cancel WSAAsyncSelect (if any) before settting socket to
       * blocking mode
       */
	if (cmd == FIONBIO && *(int *)p == 0)
	  (*i_WSAAsyncSelect) (get_socket (), gethwnd (), 0, 0);
	res = (*i_ioctlsocket) (get_socket (), cmd, (unsigned long *) p);
	if (res == SOCKET_ERROR)
	    set_winsock_errno ();
	if (cmd == (int) FIONBIO)
	  {
	    syscall_printf ("socket is now %sblocking\n",
			      *(int *) p ? "un" : "");
	    /* Start AsyncSelect if async socket unblocked */
	    if (*(int *) p && get_async ())
	      (*i_WSAAsyncSelect) (get_socket (), gethwnd (), WM_ASYNCIO,
		ASYNC_MASK);
	  }
	break;
      }
    }
  syscall_printf ("%d = ioctl_socket (%x, %x);\n", res, cmd, p);
  return res;
}

/* Cygwin32 internal */
int
fhandler_socket::fstat (struct stat *buf)
{
  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  syscall_printf ("fhandler_socket::fstat unsupported!\n");
  set_errno (ENOSYS);
  return -1;
}

/* exported as rcmd: standards? */
extern "C"
int
cygwin32_rcmd (char **ahost, unsigned short inport, char *locuser,
	       char *remuser, char *cmd, int *fd2p)
{
  int res = -1;
  SOCKET fd2s;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  if (!i_rcmd)
    LOAD (rcmd)

  pinfo *p = myself;
  int res_fd = p->hmap.find_unused_handle (0);
  if (res_fd == -1)
    goto done;
  if (fd2p)
    {
      *fd2p = p->hmap.find_unused_handle (res_fd + 1);
      if (*fd2p == -1)
	goto done;
    }
  res = (*i_rcmd) (ahost, inport, locuser, remuser, cmd, fd2p? &fd2s: NULL);
  if (res == INVALID_SOCKET)
    goto done;
  else
    {
      res = DuplicateSocket (res);

      fhandler_socket *h;
      p->hmap.vec[res_fd].h = h = 
	  new (&p->hmap.vec[res_fd].item) fhandler_socket(res, "/dev/tcp");
      res = res_fd;
    }
  if (fd2p)
    {
      fd2s = DuplicateSocket (fd2s);

      fhandler_socket *h;
      p->hmap.vec[*fd2p].h = h = 
	  new (&p->hmap.vec[*fd2p].item) fhandler_socket(fd2s, "/dev/tcp");
    }
done:
  syscall_printf ("%d = rcmd (...);\n", res);
  return res;
}

/* exported as rresvport: standards? */
extern "C"
int
cygwin32_rresvport (int *port)
{
  int res = -1;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  if (!i_rresvport)
    LOAD (rresvport)

  pinfo *p = myself;
  int res_fd = p->hmap.find_unused_handle (0);
  if (res_fd == -1)
    goto done;
  res = (*i_rresvport) (port);
  if (res == INVALID_SOCKET)
    goto done;
  else
    {
      res = DuplicateSocket (res);

      fhandler_socket *h;
      p->hmap.vec[res_fd].h = h = 
	  new (&p->hmap.vec[res_fd].item) fhandler_socket(res, "/dev/tcp");
      res = res_fd;
    }
done:
  syscall_printf ("%d = rresvport (%d);\n", res, port? *port: 0);
  return res;
}

/* exported as rexec: standards? */
extern "C"
int
cygwin32_rexec (char **ahost, unsigned short inport, char *locuser,
	       char *passwd, char *cmd, int *fd2p)
{
  int res = -1;
  SOCKET fd2s;

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  if (!i_rexec)
    LOAD (rexec)

  pinfo *p = myself;
  int res_fd = p->hmap.find_unused_handle (0);
  if (res_fd == -1)
    goto done;
  if (fd2p)
    {
      *fd2p = p->hmap.find_unused_handle (res_fd + 1);
      if (*fd2p == -1)
	goto done;
    }
  res = (*i_rexec) (ahost, inport, locuser, passwd, cmd, fd2p? &fd2s: NULL);
  if (res == INVALID_SOCKET)
    goto done;
  else
    {
      res = DuplicateSocket (res);

      fhandler_socket *h;
      p->hmap.vec[res_fd].h = h = 
	  new (&p->hmap.vec[res_fd].item) fhandler_socket(res, "/dev/tcp");
      res = res_fd;
    }
  if (fd2p)
    {
      fd2s = DuplicateSocket (fd2s);

      fhandler_socket *h;
      p->hmap.vec[*fd2p].h = h = 
	  new (&p->hmap.vec[*fd2p].item) fhandler_socket(fd2s, "/dev/tcp");
    }
done:
  syscall_printf ("%d = rexec (...);\n", res);
  return res;
}

/* socketpair: standards? */
/* Win32 supports AF_INET only, so ignore domain and protocol arguments */
extern "C"
int
socketpair (int, int type, int, int *sb)
{
  int res = -1;
  SOCKET insock, outsock, newsock;
  pinfo *p = myself;
  struct sockaddr_in sin;
  int len = sizeof (sin);

  if (NOTSTATE(myself, PID_SOCKETS_USED))
    winsock_init ();

  sb[0] = p->hmap.find_unused_handle (0);
  if (sb[0] == -1)
    {
      set_errno (EMFILE);
      goto done;
    }
  sb[1] = p->hmap.find_unused_handle (sb[0] + 1);
  if (sb[1] == -1)
    {
      set_errno (EMFILE);
      goto done;
    }

  /* create a listening socket */
  newsock = (*i_socket) (AF_INET, type, 0);
  if (newsock == INVALID_SOCKET)
    {
      set_winsock_errno ();
      goto done;
    }

  /* bind the socket to any unused port */
  sin.sin_family = AF_INET;
  sin.sin_port = 0;
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((*i_bind) (newsock, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      goto done;
    }

  if ((*i_getsockname) (newsock, (struct sockaddr *) &sin, &len) < 0)
    {
      debug_printf ("getsockname error\n");
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      goto done;
    }
  (*i_listen) (newsock, 2);

  /* create a connecting socket */
  outsock = (*i_socket) (AF_INET, type, 0);
  if (outsock == INVALID_SOCKET)
    {
      debug_printf ("can't create outsock\n");
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      goto done;
    }
  sin.sin_addr.s_addr = htonl (INADDR_LOOPBACK);

  /* Do a connect and accept the connection */
  if ((*i_connect) (outsock, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      debug_printf ("connect error\n");
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      (*i_closesocket) (outsock);
      goto done;
    }
  insock = (*i_accept) (newsock, (struct sockaddr *) &sin, &len);
  if (insock == INVALID_SOCKET)
    {
      debug_printf ("accept error\n");
      set_winsock_errno ();
      (*i_closesocket) (newsock);
      (*i_closesocket) (outsock);
      goto done;
    }

  (*i_closesocket) (newsock);
  res = 0;

  insock = DuplicateSocket (insock);

  p->hmap.vec[sb[0]].h = 
	  new (&p->hmap.vec[sb[0]].item) fhandler_socket(insock, "/dev/tcp");

  outsock = DuplicateSocket (outsock);

  p->hmap.vec[sb[1]].h = 
	  new (&p->hmap.vec[sb[1]].item) fhandler_socket(outsock, "/dev/tcp");

done:
  syscall_printf ("%d = socketpair (...);\n", res);
  return res;
}
