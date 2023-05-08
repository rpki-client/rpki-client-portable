
/*
 * Public domain
 * openssl/x509.h compatibility shim
 */

#include_next <openssl/crypto.h>

#ifndef LIBCOMPAT_OPENSSL_CRYPTO_H
#define LIBCOMPAT_OPENSSL_CRYPTO_H

#ifndef HAVE_OPENSSL_CLEANUP
void OPENSSL_cleanup(void);
#endif
#endif
