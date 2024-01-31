#ifndef _SYS_SMALLPRINT_H
#define _SYS_SMALLPRINT_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int __small_sprintf (char *dst, const char*fmt, ...);
int __small_vsprintf (char *dst, const char *fmt, va_list ap);

#ifdef __cplusplus
};
#endif

#endif /* _SYS_SMALLPRINT_H */
