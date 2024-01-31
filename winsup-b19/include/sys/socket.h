#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#include <features.h>
#include <cygwin32/socket.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __INSIDE_CYGWIN_NET__
  int accept (int, struct sockaddr *peer, int *);
  int bind (int, struct sockaddr *my_addr, int addrlen);
  int connect (int,const struct sockaddr *, int);
  int getpeername (int, struct sockaddr *peer, int *);
  int getsockname (int, struct sockaddr *addr, int *);
  int listen (int, int n);
  int recv (int, void *buff, int len, unsigned int flags);
  int recvfrom (int, char *buff, int len, int flags, 
			 struct sockaddr *from, int *fromlen);
  int send (int, const void *buff, int len, unsigned int flags);
  int sendto (int, const void *, int, unsigned int, const struct sockaddr *, int);
  int setsockopt (int s, int level, int optname, const void *optval, int optlen);
  int getsockopt (int s, int level, int optname, void *optval, int *optlen);
  int shutdown (int, int);
  int socket (int family, int type, int protocol);
  struct servent *getservbyname (const char *name, const char *proto);
  int select (int, fd_set * , fd_set *, fd_set * , struct timeval *);
#endif

#ifdef __cplusplus
};
#endif

#endif /* _SYS_SOCKET_H */
