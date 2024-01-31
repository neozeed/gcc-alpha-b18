#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#include <sys/time.h>

#define	RUSAGE_SELF	0		/* calling process */
#define	RUSAGE_CHILDREN	-1		/* terminated child processes */

struct rusage {
  	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long ru_maxrss;
	long ru_ixrss;               /* XXX: 0 */
	long ru_idrss;               /* XXX: sum of rm_asrss */
	long ru_isrss;               /* XXX: 0 */
        long ru_minflt;              /* any page faults not requiring I/O */
        long ru_majflt;              /* any page faults requiring I/O */
        long ru_nswap;               /* swaps */
        long ru_inblock;             /* block input operations */
        long ru_oublock;             /* block output operations */
        long ru_msgsnd;              /* messages sent */
        long ru_msgrcv;              /* messages received */
        long ru_nsignals;            /* signals received */
        long ru_nvcsw;               /* voluntary context switches */
        long ru_nivcsw;              /* involuntary " */
#define ru_last         ru_nivcsw
};

#ifdef __cplusplus
extern "C" int getrusage(int who, struct rusage *rusage);
#else
extern int getrusage(int who, struct rusage *rusage);
#endif

#endif

