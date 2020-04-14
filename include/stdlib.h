/*
 * stdlib.h compatibility shim
 * Public domain
 */

#include_next <stdlib.h>

#ifndef LIBCOMPAT_STDLIB_H
#define LIBCOMPAT_STDLIB_H

#ifndef HAVE_REALLOCARRAY
void *reallocarray(void *, size_t, size_t);
#endif

#endif
