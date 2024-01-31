#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <sys/types.h>

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4

#define MAP_FILE 0
#define MAP_SHARED 1
#define MAP_PRIVATE 2
#define MAP_TYPE 0xF
#define MAP_FIXED 0x10
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS

/*
 * Flags for msync.
 */
#define MS_ASYNC 1
#define MS_SYNC 2
#define MS_INVALIDATE 4

extern caddr_t mmap (caddr_t addr, size_t len, int prot, int flags, int fd, off_t off);
extern int munmap (caddr_t addr, size_t len);
extern int mprotect (caddr_t addr, size_t len, int prot);
extern int msync(caddr_t addr, size_t len, int flags);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /*  _SYS_MMAN_H_ */
