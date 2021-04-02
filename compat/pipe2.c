/*
 * Copyright (c) 2021 Claudio Jeker <claudio@openbsd.org>
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
#include <fcntl.h>
#include <unistd.h>

static int
setflags(int fd, int type)
{
	int flags;

	if (type & O_CLOEXEC) {
		flags = fcntl(fd, F_GETFD);
		if (flags == -1)
			return -1;
		if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1)
			return -1;
	}
	if (type & O_NONBLOCK) {
		flags = fcntl(fd, F_GETFL);
		if (flags == -1)
			return -1;
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
			return -1;
	}
	return 0;
}

int
pipe2(int filedes[2], int flags)
{
	if (pipe(filedes) == -1)
		return -1;
	if (setflags(filedes[0], flags) == -1 ||
	    setflags(filedes[1], flags) == -1) {
		int save_errno = errno;
		close(filedes[0]);
		close(filedes[1]);
		errno = save_errno;
		return -1;
	}
	return 0;
}
