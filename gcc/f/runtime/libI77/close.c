#include "f2c.h"
#include "fio.h"
#ifdef KR_headers
integer f_clos(a) cllist *a;
#else
#undef abs
#undef min
#undef max
#include <stdlib.h>
#ifdef NON_UNIX_STDIO
#ifndef unlink
#define unlink remove
#endif
#else
#if defined (MSDOS) && !defined (GO32)
#include "io.h"
#else
#ifdef __cplusplus
extern "C" int unlink(const char*);
#else
extern int unlink(const char*);
#endif
#endif
#endif

integer f_clos(cllist *a)
#endif
{	unit *b;

	if (f__init & 2)
		f__fatal (131, "I/O recursion");
	if(a->cunit >= MXUNIT) return(0);
	b= &f__units[a->cunit];
	if(b->ufd==NULL)
		goto done;
	if (!a->csta)
		if (b->uscrtch == 1)
			goto Delete;
		else
			goto Keep;
	switch(*a->csta) {
		default:
	 	Keep:
		case 'k':
		case 'K':
			if(b->uwrt == 1)
				t_runc((alist *)a);
			if(b->ufnm) {
				fclose(b->ufd);
				free(b->ufnm);
				}
			break;
		case 'd':
		case 'D':
		Delete:
			if(b->ufnm) {
				fclose(b->ufd);
				unlink(b->ufnm); /*SYSDEP*/
				free(b->ufnm);
				}
		}
	b->ufd=NULL;
 done:
	b->uend=0;
	b->ufnm=NULL;
	return(0);
	}
 void
#ifdef KR_headers
f_exit()
#else
f_exit(void)
#endif
{	int i;
	static cllist xx;
	if (! (f__init & 1))
		return;		/* Not initialized, so no open units. */
	if (!xx.cerr) {
		xx.cerr=1;
		xx.csta=NULL;
		for(i=0;i<MXUNIT;i++)
		{
			xx.cunit=i;
			(void) f_clos(&xx);
		}
	}
}
 int
#ifdef KR_headers
G77_flush_0 ()
#else
G77_flush_0 (void)
#endif
{	int i;
	for(i=0;i<MXUNIT;i++)
		if(f__units[i].ufd != NULL && f__units[i].uwrt)
			fflush(f__units[i].ufd);
return 0;
}
