/*
 * Public domain.
 */

#include <openssl/cms.h>

int
CMS_get_version(const CMS_ContentInfo *cms, long *version)
{
	*version = 3;
	return 1;
}

int
CMS_SignerInfo_get_version(const CMS_SignerInfo *si, long *version)
{
	*version = 3;
	return 1;
}
