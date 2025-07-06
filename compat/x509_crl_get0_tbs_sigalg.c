/*
 * X509_CRL get0_tbs_sigalg() compatibility shim. Public domain.
 */

#include <openssl/x509.h>

const X509_ALGOR *
X509_CRL_get0_tbs_sigalg(const X509_CRL *crl)
{
	const X509_ALGOR *alg = NULL;

	X509_CRL_get0_signature(crl, NULL, &alg);
	return alg;
}
