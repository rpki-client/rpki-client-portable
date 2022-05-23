/*
 * Public domain
 * openssl/safestack.h compatibility shim
 */

#include_next <openssl/safestack.h>

#ifndef LIBCOMPAT_OPENSSL_SAFESTACK_H
#define LIBCOMPAT_OPENSSL_SAFESTACK_H

#ifndef DECLARE_STACK_OF
#define DECLARE_STACK_OF	DEFINE_STACK_OF
#endif

#endif

