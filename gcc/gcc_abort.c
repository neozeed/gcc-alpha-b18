#include <stdio.h>
/* gcc_abort: Print a friendly message saying how totally hosed we are,
   and exit without producing a core file.  */
void
gcc_abort (file, line, fn)
     const char *file, *fn;
     int line;
{
  fprintf (stderr, "Internal error, aborting at %s line %d", file, line);
  if (fn)
    fprintf (stderr, " in %s", fn);
  fprintf (stderr, "\nPlease report this bug.\n");
  exit (1);
}
