#ifndef _CYGWIN32_IF_H_
#define _CYGWIN32_IF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <sys/socket.h>

/* Standard interface flags. */
#define IFF_UP          0x1             /* interface is up              */
#define IFF_BROADCAST   0x2             /* broadcast address valid      */
#define IFF_LOOPBACK    0x8             /* is a loopback net            */
#define IFF_NOTRAILERS  0x20            /* avoid use of trailers        */
#define IFF_RUNNING     0x40            /* resources allocated          */
#define IFF_PROMISC     0x100           /* receive all packets          */
#define IFF_MULTICAST   0x1000          /* Supports multicast           */

/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with ifr_name.  The
 * remainder may be interface specific.
 */

struct ifreq 
{
#define IFNAMSIZ        16
        union
        {
                char    ifrn_name[IFNAMSIZ];            /* if name, e.g. "en0" */
        } ifr_ifrn;

        union {
                struct  sockaddr ifru_addr;
                struct  sockaddr ifru_broadaddr;
                struct  sockaddr ifru_netmask;
                short   ifru_flags;
                int     ifru_metric;
                int     ifru_mtu;
        } ifr_ifru;
};

#define ifr_name        ifr_ifrn.ifrn_name      /* interface name       */
#define ifr_addr        ifr_ifru.ifru_addr      /* address              */
#define ifr_broadaddr   ifr_ifru.ifru_broadaddr /* broadcast address    */
#define ifr_netmask     ifr_ifru.ifru_netmask   /* interface net mask   */
#define ifr_flags       ifr_ifru.ifru_flags     /* flags                */

/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve interface configuration
 * for machine (useful for programs which
 * must know all networks accessible).
 */

struct ifconf
{
        int     ifc_len;                        /* size of buffer       */
        union
        {
                caddr_t ifcu_buf;
                struct  ifreq *ifcu_req;
        } ifc_ifcu;
};
#define ifc_buf ifc_ifcu.ifcu_buf               /* buffer address       */
#define ifc_req ifc_ifcu.ifcu_req               /* array of structures  */

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* _CYGWIN32_IF_H_ */
