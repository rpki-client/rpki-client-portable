/*
 * Public domain
 * sys/stat.h compatibility shim
 */

#include_next <sys/stat.h>

#ifndef LIBCOMPAT_SYS_STAT_H
#define LIBCOMPAT_SYS_STAT_H

#if defined(__APPLE__) || defined(__NetBSD__)
#define st_mtim st_mtimespec
#endif

#endif
