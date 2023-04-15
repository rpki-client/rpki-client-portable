/*
 * X509_get0_uids compatibility shim. Public domain.
 */

#include <openssl/asn1.h>
#include <openssl/x509.h>

void
X509_get0_uids(const X509 *x, const ASN1_BIT_STRING **issuerUID,
    const ASN1_BIT_STRING **subjectUID)
{
	if (issuerUID != NULL)
		*issuerUID = NULL;
	if (subjectUID != NULL)
		*subjectUID = NULL;
}
