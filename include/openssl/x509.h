
/*
 * Public domain
 * openssl/x509.h compatibility shim
 */

#include_next <openssl/x509.h>

#ifndef LIBCOMPAT_OPENSSL_X509_H
#define LIBCOMPAT_OPENSSL_X509_H

#ifndef HAVE_X509_GET0_UIDS
void X509_get0_uids(const X509 *x, const ASN1_BIT_STRING **issuerUID,
    const ASN1_BIT_STRING **subjectUID);
#endif
#endif
