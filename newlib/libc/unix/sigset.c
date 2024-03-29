#include <signal.h>
#include <errno.h>

#ifdef SIG_SETMASK	/* easier than trying to remove from Makefile */

#undef sigemptyset
int
sigemptyset (sigset_t * set)
{
  *set = (sigset_t) 0;
  return 0;
}

int
sigfillset (sigset_t * set)
{
  *set = ~((sigset_t) 0);
  return 0;
}

#undef sigaddset
int
sigaddset (sigset_t * set, int signo)
{
  if (signo >= NSIG || signo <= 0)
    {
      errno = EINVAL;
      return -1;
    }
  *set |= 1 << (signo - 1);
  return 0;
}

int
sigdelset (sigset_t * set, int signo)
{
  if (signo >= NSIG || signo <= 0)
    {
      errno = EINVAL;
      return -1;
    }
  *set &= ~(1 << (signo - 1));
  return 0;
}

int
sigismember (const sigset_t * set, int signo)
{
  if (signo >= NSIG || signo <= 0)
    {
      errno = EINVAL;
      return -1;
    }

  if (*set & (1 << (signo - 1)))
    return 1;
  else
    return 0;
}

#endif /* SIG_SETMASK */
