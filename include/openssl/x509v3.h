/*
 * Public domain
 * openssl/x509v3.h compatibility shim
 */

#include_next <openssl/x509v3.h>

#ifndef LIBCOMPAT_OPENSSL_X509V3_H
#define LIBCOMPAT_OPENSSL_X509V3_H

#ifndef HAVE_X509_GET_EXTENSION_FLAGS
uint32_t X509_get_extension_flags(X509 *x);
#endif

#endif
