
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "gdbwin.h"
#include "windefs.h"

const char *doing_something (const char *s)
{
    printf("doing_something: %s\n",s);
}

struct cleanup *
make_final_cleanup (void (*f) (void *), void *a) 
{
    return NULL;
}

char *safe_strerror (int l) 
{
    return strerror(l);
}

PTR xmalloc(long l) 
{
    return malloc(l);
} 

void fprintf_unfiltered (FILE *fp, const char *str, ...) 
{
    va_list ap;
    if (fp==0) fp=stderr;
    va_start(ap, str);
    vfprintf(fp,str,ap);
    va_end(ap);
}
void error(const char *str, ...) 
{
    va_list ap;
    va_start(ap, str);
    vprintf(str,ap);
    va_end(ap);
    exit(1);
}

int fputc_unfiltered (int c, FILE *fp) 
{
    if (fp==0) fp=stderr;
    return fputc(c,fp);
}

char * savestring (ptr, size)
         const char *ptr;
	      int size;
{
      register char *p = (char *) xmalloc (size + 1);
        memcpy (p, ptr, size);
	  p[size] = 0;
	    return p;
}
char * strsave (ptr)
         const char *ptr;
{
      return savestring (ptr, strlen (ptr));
}



void fputs_unfiltered(char* str, FILE* fp) 
{
    if (fp==0) fp=stderr;
fputs(str,fp);
} 

win_host_type
win_host(void)
{
    win_host_type host;
    int ver = GetVersion () ;

    if (ver < 0x80000000)
	host=winnt; /* windows NT */
    else if ((ver & 255) >= 4 )
	host=win95; /* windows 95 */
    else
	host=win32s; /* must be win32s */
    return host;
}


/* these don't need to do anything */
struct cmd_list_element *setlist=0;
struct cmd_list_element *showlist=0;

void perror_with_name() 
{ 
}

extern struct cmd_list_element *
add_set_cmd (char *c, enum command_class e, var_types t, char *d, char *q,
	                     struct cmd_list_element **s)
{
    return 0;
}

extern struct cmd_list_element *
add_set_enum_cmd (char *name, enum command_class e, char *list[],
		  char *var, char *doc, struct cmd_list_element **c)
{
    return 0;
}

extern struct cmd_list_element *
add_show_from_set (struct cmd_list_element *c,
			       struct cmd_list_element **pc)
{
    return 0;
}


