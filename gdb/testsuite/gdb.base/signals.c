/* Test GDB dealing with stuff like stepping into sigtramp.  */

#include <signal.h>

#ifdef __sh__
#define signal(a,b)	/* Signals not supported on this target - make them go away */
#define alarm(a)	/* Ditto for alarm() */
#endif

static int count = 0;
static int i;

static void
handler (sig)
     int sig;
{
  signal (sig, handler);
  ++count;
}

static void
handler2 (sig)
     int sig;
{
  signal (sig, handler2);
  i = -99;
}

static void
func1 ()
{
  ++count;
}

static void
func2 ()
{
  ++count;
}

int
main ()
{
#ifdef usestubs
  set_debug_traps();
  breakpoint();
#endif
#ifdef SIGALRM
  signal (SIGALRM, handler);
#endif
#ifdef SIGUSR1
  signal (SIGUSR1, handler);
#endif
  alarm (1);
  ++count; /* first */
  alarm (1);
  ++count; /* second */
  func1 ();
  alarm (1);
  func2 ();

  /* Now test strange unwind cases: make sure we can unwind over all
     these conditions */

#ifdef SIGALRM
  signal (SIGALRM, handler2);
#endif
  /* while computing */
  alarm (2);
  for (i=1;i>0;i++);

  /* while paused */
  alarm (2);
  pause();

  /* SIGINT while computing, paused; gdb will "see" the signal */
#ifdef SIGINT
  signal (SIGINT, handler2);
#endif

  for (i=1;i>0;i++);
  pause();

  return count;
}
