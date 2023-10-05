/*
 * Copyright (c) 2020 Claudio Jeker <claudio@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <time.h>

static volatile sig_atomic_t signaled;
static void (*sigfunc)(int);
static int initalized;

static void
proc_child(int signal)
{
	signaled = 1;

	if (sigfunc)
		sigfunc(signal);
}

/*
 * Note: This compat code function only handles SIGCHLD
 */
int
ppoll(struct pollfd *fds, nfds_t nfds, const struct timespec *timeout,
    const sigset_t *mask)
{
	int rc, t = INFTIM;
	int saved_errno;
	sigset_t oldmask;

	if (timeout) {
		t = timeout->tv_sec * 1000;
		t += timeout->tv_nsec / 1000 / 1000;
	}

	signaled = 0;

	if (mask) {
		if (!initalized) {
			/* overload SIGCHLD handler */
			sigfunc = signal(SIGCHLD, proc_child);
			initalized = 1;
		}
		sigemptyset(&oldmask);
		sigprocmask(SIG_SETMASK, mask, &oldmask);
	}

	/* check if signal was pending and fired */
	if (signaled) {
		errno = EINTR;
		rc = -1;
	} else
		rc = poll(fds, nfds, t);

	saved_errno = errno;
	if (mask)
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
	errno = saved_errno;

	return rc;
}
