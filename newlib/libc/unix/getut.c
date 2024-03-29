#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <_syslist.h>

static int utmp_fd = -2;
static char *utmp_file = UTMP_FILE;

static struct utmp utmp_data;

void
setutent ()
{
  if (utmp_fd == -2)
    {
      utmp_fd = _open (utmp_file, O_RDONLY);
    }
  _lseek (utmp_fd, 0, SEEK_SET);
}

void
endutent ()
{
  _close (utmp_fd);
  utmp_fd = -2;
}

void
utmpname (char *file)
{
  extern char *strdup (char *);

  utmp_file = strdup (file);
}

struct utmp *
getutent ()
{
  if (utmp_fd == -2)
    setutent ();
  if (_read (utmp_fd, &utmp_data, sizeof (utmp_data)) < sizeof (utmp_data))
    return 0;
  return &utmp_data;
}

struct utmp *
getutid (struct utmp *id)
{
  while (_read (utmp_fd, &utmp_data, sizeof (utmp_data)) == sizeof (utmp_data))
    {
      switch (id->ut_type)
	{
	case RUN_LVL:
	case BOOT_TIME:
	case OLD_TIME:
	case NEW_TIME:
	  if (id->ut_type == utmp_data.ut_type)
	    return &utmp_data;
	case INIT_PROCESS:
	case LOGIN_PROCESS:
	case USER_PROCESS:
	case DEAD_PROCESS:
	  if (id->ut_id == utmp_data.ut_id)
	    return &utmp_data;
	default:
	  abort ();
	}
    }
  return 0;
}

struct utmp *
getutline (struct utmp *line)
{
  while (_read (utmp_fd, &utmp_data, sizeof (utmp_data)) == sizeof (utmp_data))
    {
      if ((utmp_data.ut_type == LOGIN_PROCESS ||
	   utmp_data.ut_type == USER_PROCESS) &&
	  !strncmp (utmp_data.ut_line, line->ut_line,
		    sizeof (utmp_data.ut_line)))
	return &utmp_data;
    }

  return 0;
}
