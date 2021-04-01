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
#define IN_SOCKET_COMPAT
#include <sys/socket.h>

#ifdef NEED_SOCKET_FLAGS

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static int
setflags(int fd, int type)
{
	int flags;

	if (type & SOCK_CLOEXEC) {
		flags = fcntl(fd, F_GETFD);
		if (flags == -1)
			return -1;
		if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1)
			return -1;
	}
	if (type & SOCK_NONBLOCK) {
		flags = fcntl(fd, F_GETFL);
		if (flags == -1)
			return -1;
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
			return -1;
	}
	return 0;
}

int
_socketpair(int domain, int type, int protocol, int sv[2])
{
	int mask = ~(SOCK_CLOEXEC | SOCK_NONBLOCK);

	if (socketpair(domain, type & mask, protocol, sv) == -1)
		return -1;
	if (setflags(sv[0], type) == -1 ||
	    setflags(sv[1], type) == -1) {
		int save_errno = errno;
		close(sv[0]);
		close(sv[1]);
		errno = save_errno;
		return -1;
	}
	return 0;
}

int
_socket(int domain, int type, int protocol)
{
	int fd, mask = ~(SOCK_CLOEXEC | SOCK_NONBLOCK);

	if ((fd = socket(domain, type & mask, protocol)) == -1)
		return -1;
	if (setflags(fd, type) == -1) {
		int save_errno = errno;
		close(fd);
		errno = save_errno;
		return -1;
	}
	return fd;
}

#endif
