/*
 * Public domain
 * arpa/inet.h compatibility shim
 */

#include_next <arpa/inet.h>

#ifndef LIBCOMPAT_ARPA_INET_H
#define LIBCOMPAT_ARPA_INET_H

#ifndef HAVE_INET_NET_PTON
int inet_net_pton(int, const char *, void *, size_t);
#endif

#endif
