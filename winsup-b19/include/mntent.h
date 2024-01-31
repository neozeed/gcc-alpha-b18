#ifndef _MNTENT_H
#define _MNTENT_H

#ifdef __cplusplus
extern "C" {
#endif

struct mntent
  {
	char *mnt_fsname;
	char *mnt_dir;
	char *mnt_type;
	char *mnt_opts;
	int  mnt_freq;
	int  mnt_passno;
};

FILE *setmntent(const char *filep, const char *type);
struct mntent *getmntent(FILE *filep);
int addmntent(FILE *filep, const struct mntent *mnt);
int endmntent(FILE *filep);
char *hasmntopt(const struct mntent *mnt, const char *opt);

/* This next file doesn't exist, it is in the registry,
   however applications need the define to pass to
   the above calls.
*/
#ifndef MOUNTED
#define MOUNTED "/etc/mtab"
#endif
#ifdef __cplusplus
};
#endif

#endif /* _MNTENT_H */
