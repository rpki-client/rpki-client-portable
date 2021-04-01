/*
 * Public domain
 * poll.h compatibility shim
 */

#include_next <poll.h>

#ifndef LIBCOMPAT_POLL_H
#define LIBCOMPAT_POLL_H

#ifndef INFTIM
#define INFTIM          (-1)
#endif

#ifndef HAVE_PPOLL
#include <signal.h>
struct timespec;

int	ppoll(struct pollfd *, nfds_t, const struct timespec *,
	    const sigset_t *);
#endif

#endif
