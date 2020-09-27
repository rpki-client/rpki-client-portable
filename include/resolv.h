/*
 * Public domain
 * resolv.h compatibility shim
 */

#include_next <resolv.h>

#ifndef LIBCOMPAT_RESOLV_H
#define LIBCOMPAT_RESOLV_H

#ifndef HAVE___B64_PTON
int b64_pton(char const *, unsigned char *, size_t);
#endif

#endif
