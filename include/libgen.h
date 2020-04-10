/*
 * libgen.h compatibility shim
 * Public domain
 */

#include_next <libgen.h>

#ifndef LIBCOMPAT_LIBGEN_H
#define LIBCOMPAT_LIBGEN_H

#ifndef HAVE_BASENAME
char *basename(const char *path);
#endif


#endif
