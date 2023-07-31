
/*
 * Public domain
 * openssl/cms.h compatibility shim
 */

#include_next <openssl/cms.h>

#ifndef LIBCOMPAT_OPENSSL_CMS_H
#define LIBCOMPAT_OPENSSL_CMS_H

#ifndef HAVE_CMS_GET_VERSION
int CMS_get_version(const CMS_ContentInfo *cms, long *version);
int CMS_SignerInfo_get_version(const CMS_SignerInfo *si, long *version);
#endif
#endif
