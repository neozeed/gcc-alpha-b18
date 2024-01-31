/*
 * dirent.c
 *
 * Derived from DIRLIB.C by Matt J. Weinstein 
 * This note appears in the DIRLIB.H
 * DIRLIB.H by M. J. Weinstein   Released to public domain 1-Jan-89
 *
 * Updated by Jeremy Bettis <jeremy@hksys.com>
 *
 */

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <dir.h>
#include <direct.h>

#include <dirent.h>

#define MAXPATHLEN 1024

/*
 * opendir
 */

#define SUFFIX	"*"
#define	SLASH	"\\"
#define streq(a,b)	(strcmp(a,b)==0)

DIR * opendir(const char *name)
{
   DIR *nd;

   if (!(nd = (DIR *)malloc( sizeof(DIR) + strlen(name) + strlen(SLASH) +
        strlen(SUFFIX))))
	  return (DIR *) 0;
   strcpy(nd->dd_name, name);
   if (!nd->dd_name[0] || (nd->dd_name[ strlen(nd->dd_name)-1 ] != '/' &&
        nd->dd_name[ strlen(nd->dd_name)-1 ] != '\\')) 
      strcat(nd->dd_name, SLASH);
   strcat(nd->dd_name, SUFFIX);

   /* search */
   nd->dd_handle = _findfirst(&nd->dd_name[0], &nd->dd_dta);
   if (nd->dd_handle == -1) {
      free((char *)nd);
      return (DIR *) 0;
   }
   nd->dd_stat = 0;
   return nd;
}


struct dirent *
readdir( DIR *dirp )
{
   if (!dirp) {
      errno = EFAULT;
      return (struct dirent *) 0;
   }
   if (dirp->dd_stat)
      return (struct dirent *) 0;

   /* format structure */
   dirp->dd_dir.d_ino = 0; /* not valid for DOS */
   dirp->dd_dir.d_reclen = 0;
   strcpy(dirp->dd_dir.d_name, dirp->dd_dta.name);
   dirp->dd_dir.d_namlen = strlen(dirp->dd_dir.d_name);
   /* strlwr(dir.d_name);  DOSism */

   /* read ahead */
   if (!_findnext(dirp->dd_handle, &(dirp->dd_dta)))
      dirp->dd_stat = 0;
   else		
      dirp->dd_stat = 1;

   return &dirp->dd_dir;
}


int closedir( DIR *dirp )
{
   int rc;
   if (!dirp) {
       errno = EFAULT;
       return -1;
   }

   rc = _findclose(dirp->dd_handle);
   free((char *)dirp);
   return rc;
}


