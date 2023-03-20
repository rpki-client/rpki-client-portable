/*
 * Public domain
 * unistd.h compatibility shim
 */

#include_next <unistd.h>

#ifndef LIBCOMPAT_UNISTD_H
#define LIBCOMPAT_UNISTD_H

#ifndef HAVE_PIPE2
int pipe2(int [2], int);
#endif

#ifndef HAVE_PLEDGE
int pledge(const char *, const char *);

#ifdef HAVE_LANDLOCK
void pledge_landlock(const char *);
#endif
#endif

#ifndef HAVE_UNVEIL
int unveil(const char *, const char *);
#endif

#include <grp.h>

#ifndef HAVE_SETGROUPS
int setgroups(int ngroups, const gid_t *gidset);
#endif

#ifndef HAVE_SETRESGID
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);
#endif

#ifndef HAVE_SETRESUID
int setresuid(uid_t ruid, uid_t euid, uid_t suid);
#endif

#ifndef HAVE_HOST_NAME_MAX
#include <limits.h>
#define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#endif

#endif
