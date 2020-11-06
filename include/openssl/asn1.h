/*
 * Public domain
 * openssl/asn1.h compatibility shim
 */

#include_next <openssl/asn1.h>

#ifndef LIBCOMPAT_OPENSSL_ASN1_H
#define LIBCOMPAT_OPENSSL_ASN1_H

#ifndef HAVE_ASN1_TIME_PARSE
int ASN1_time_parse(const char *_bytes, size_t _len, struct tm *_tm, int _mode);
#endif

#ifndef HAVE_ASN1_TIME_TM_CMP
int ASN1_time_tm_cmp(struct tm *_tm1, struct tm *_tm2);
#endif

#endif
