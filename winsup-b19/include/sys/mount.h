#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Once upon a time, MOUNT_MIXED was 1 */
#define MOUNT_BINARY 2
#define MOUNT_SILENT 4

int mount (const char *, const char *, int flags);
int umount (const char *);
#ifdef __cplusplus
};
#endif

#endif /* _SYS_MOUNT_H */
