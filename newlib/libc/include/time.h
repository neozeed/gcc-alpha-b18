/*
 * time.h
 * 
 * Struct and function declarations for dealing with time.
 */

#ifndef _TIME_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _TIME_H_

#include "_ansi.h"

#ifndef NULL
#define	NULL	0L
#endif

#define CLOCKS_PER_SEC 1000		/* Machine dependent */
#define CLK_TCK CLOCKS_PER_SEC
#define __need_size_t
#include <stddef.h>

/* Get _CLOCK_T_ and _TIME_T_.  */
#include <machine/types.h>

#ifndef __clock_t_defined
typedef _CLOCK_T_ clock_t;
#define __clock_t_defined
#endif

#ifndef __time_t_defined
typedef _TIME_T_ time_t;
#define __time_t_defined
#endif

struct tm
{
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
};

clock_t	   _EXFUN(clock,    (void));
double	   _EXFUN(difftime, (time_t _time2, time_t _time1));
time_t	   _EXFUN(mktime,   (struct tm *_timeptr));
time_t	   _EXFUN(time,     (time_t *_timer));
#ifndef _REENT_ONLY
char	  *_EXFUN(asctime,  (const struct tm *_tblock));
char	  *_EXFUN(ctime,    (const time_t *_time));
struct tm *_EXFUN(gmtime,   (const time_t *_timer));
struct tm *_EXFUN(localtime,(const time_t *_timer));
#endif
size_t	   _EXFUN(strftime, (char *_s, size_t _maxsize, const char *_fmt, const struct tm *_t));

char	  *_EXFUN(asctime_r,	(const struct tm *, char *));
char	  *_EXFUN(ctime_r,	(const time_t *, char *));
struct tm *_EXFUN(gmtime_r,	(const time_t *, struct tm *));
struct tm *_EXFUN(localtime_r,	(const time_t *, struct tm *));

#ifdef __CYGWIN32__
#ifndef __STRICT_ANSI__
extern void tzset _PARAMS ((void));
extern time_t *__imp__timezone;
#define _timezone (*__imp__timezone)
extern int *__imp__daylight;
#define _daylight (*__imp__daylight)
extern char *((*__imp__tzname)[2]);
#define _tzname (*__imp__tzname)
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif /* _TIME_H_ */
