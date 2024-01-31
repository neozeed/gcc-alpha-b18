/* System-dependent stuff, for OpenNT systems */

#define HAVE_UNISTD_H
#ifdef __GNUC__
#define alloca __builtin_alloca
#else
extern char *alloca ();
#endif

#include <sys/types.h>			/* Needed by dirent.h */
#include <string.h>

#include <dirent.h>
typedef struct dirent dirent;
