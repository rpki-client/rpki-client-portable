/*
 * Copyright (c) 2022 Claudio Jeker <claudio@openbsd.org>
 * Copyright (c) 2021 Omar Polo <op@openbsd.org>
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

#include <linux/landlock.h>

#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/*
 * What's the deal with landlock?  While distro with linux >= 5.13
 * have the struct declarations, libc wrappers are missing.  The
 * sample landlock code provided by the authors includes these "shims"
 * in their example for the landlock API until libc provides them.
 */

#ifndef landlock_create_ruleset
static inline int
landlock_create_ruleset(const struct landlock_ruleset_attr *attr, size_t size,
    __u32 flags)
{
	return syscall(__NR_landlock_create_ruleset, attr, size, flags);
}
#endif

#ifndef landlock_add_rule
static inline int
landlock_add_rule(int ruleset_fd, enum landlock_rule_type type,
    const void *attr, __u32 flags)
{
	return syscall(__NR_landlock_add_rule, ruleset_fd, type, attr, flags);
}
#endif

#ifndef landlock_restrict_self
static inline int
landlock_restrict_self(int ruleset_fd, __u32 flags)
{
	return syscall(__NR_landlock_restrict_self, ruleset_fd, flags);
}
#endif

#ifndef LANDLOCK_ACCESS_FS_REFER
#define LANDLOCK_ACCESS_FS_REFER	(1ULL << 13)
#endif

static int landlock_state;
static int landlock_fd;
static int landlock_abi;

/*
 * initalize landlock, which is stupidly complicated.
 */
static int
landlock_init(const char *permissions)
{
	struct landlock_ruleset_attr rattr = {
		/*
		 * List all capabilities currently defined by landlock.
		 * Failure in doing so will implicitly allow those actions
		 * (i.e. omitting READ_FILE will allow to read _any_ file.)
		 */
		.handled_access_fs =
		    LANDLOCK_ACCESS_FS_EXECUTE |
		    LANDLOCK_ACCESS_FS_READ_DIR |
		    LANDLOCK_ACCESS_FS_READ_FILE |
		    LANDLOCK_ACCESS_FS_WRITE_FILE |
		    LANDLOCK_ACCESS_FS_REMOVE_DIR |
		    LANDLOCK_ACCESS_FS_REMOVE_FILE |
		    LANDLOCK_ACCESS_FS_MAKE_CHAR |
		    LANDLOCK_ACCESS_FS_MAKE_DIR |
		    LANDLOCK_ACCESS_FS_MAKE_REG |
		    LANDLOCK_ACCESS_FS_MAKE_SOCK |
		    LANDLOCK_ACCESS_FS_MAKE_FIFO |
		    LANDLOCK_ACCESS_FS_MAKE_BLOCK |
		    LANDLOCK_ACCESS_FS_MAKE_SYM |
		    LANDLOCK_ACCESS_FS_REFER,
	};

	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
		return -1;

	landlock_abi = landlock_create_ruleset(NULL, 0,
	    LANDLOCK_CREATE_RULESET_VERSION);
	if (landlock_abi == -1)
		return -1;
	if (landlock_abi < 2) {
		rattr.handled_access_fs &= ~LANDLOCK_ACCESS_FS_REFER;
		if (permissions != NULL && strcmp(permissions, "rwc") == 0) {
			landlock_state = -1;
			return 0;
		}
	}

	landlock_state = 1;
	return landlock_create_ruleset(&rattr, sizeof(rattr), 0);
}

static int
landlock_lock(void)
{
	int saved_errno;

	if (landlock_restrict_self(landlock_fd, 0)) {
		saved_errno = errno;
		close(landlock_fd);
		errno = saved_errno;
		landlock_state = -1;
		return -1;
	}

	landlock_state = 2;
	close(landlock_fd);
	return 0;
}

/*
 * Implement the bits from pledge we need to make landlock work.
 */
void
pledge_landlock(const char *promises)
{
	if (strstr(promises, "unveil") == NULL) {
		if (landlock_state == 1)
			landlock_lock();
		if (landlock_state == 0) {
			/* is IO allowed at all */
			if (strstr(promises, "rpath") == NULL &&
			    strstr(promises, "wpath") == NULL)
				unveil(NULL, NULL);
		}
	}
}

/*
 * This is by no means a proper implementation of unveil() but it is
 * good enough for rpki-client which uses only a few featrues.
 * rpki-client only uses 'r' and 'x' and for 'x' we need to do
 * some horrible hacks.
 */
int
unveil(const char *path, const char *permissions)
{
	struct landlock_path_beneath_attr lpba;
	int fd, saved_errno;

	if (landlock_state == 0) {
		if ((landlock_fd = landlock_init(permissions)) == -1) {
			landlock_state = -1;
			/* this kernel doesn't have landlock built in */
			if (errno == ENOSYS || errno == EOPNOTSUPP)
				return 0;
			return -1;
		}
	}

	/* no landlock available */
	if (landlock_state == -1)
		return 0;

	if (path == NULL && permissions == NULL) {
		return landlock_lock();
	}

	if (path == NULL || permissions == NULL || landlock_state != 1) {
		errno = EINVAL;
		return -1;
	}

	if (strcmp(permissions, "r") == 0) {
		fd = open(path, O_PATH | O_CLOEXEC);
		if (fd == -1)
			return -1;
		lpba = (struct landlock_path_beneath_attr) {
		    .allowed_access =
			LANDLOCK_ACCESS_FS_READ_FILE |
			LANDLOCK_ACCESS_FS_READ_DIR,
		    .parent_fd = fd,
		};
		if (landlock_add_rule(landlock_fd, LANDLOCK_RULE_PATH_BENEATH,
		    &lpba, 0) == -1) {
			saved_errno = errno;
			close(fd);
			errno = saved_errno;
			return -1;
		}
		close(fd);
	}
	if (strcmp(permissions, "rwc") == 0) {
		fd = open(path, O_PATH | O_CLOEXEC);
		if (fd == -1)
			return -1;
		lpba = (struct landlock_path_beneath_attr) {
		    .allowed_access =
			LANDLOCK_ACCESS_FS_READ_DIR |
			LANDLOCK_ACCESS_FS_READ_FILE |
			LANDLOCK_ACCESS_FS_WRITE_FILE |
			LANDLOCK_ACCESS_FS_REMOVE_DIR |
			LANDLOCK_ACCESS_FS_REMOVE_FILE |
			LANDLOCK_ACCESS_FS_MAKE_DIR |
			LANDLOCK_ACCESS_FS_MAKE_REG |
			LANDLOCK_ACCESS_FS_REFER,
		    .parent_fd = fd,
		};
		if (landlock_add_rule(landlock_fd, LANDLOCK_RULE_PATH_BENEATH,
		    &lpba, 0) == -1) {
			saved_errno = errno;
			close(fd);
			errno = saved_errno;
			return -1;
		}
		close(fd);
	}
	if (strcmp(permissions, "x") == 0) {
		/*
		 * GROSS HACK: landlock is inherited so one needs to give
		 * all the access for the child process to work. The hope
		 * is that rsync will not break when it only has read access
		 * to all of the system and gets most access to the repo.
		 * Also the execute access is extremely crippled because
		 * more than just the executable needs to be marked executable.
		 * It is unclear if it is just ld.so or also the shared libs
		 * but thanks to that the only viable solution is to give
		 * everything the execute right.
		 */
		fd = open("/", O_PATH | O_CLOEXEC);
		if (fd == -1)
			return -1;
		lpba = (struct landlock_path_beneath_attr) {
		    .allowed_access =
			LANDLOCK_ACCESS_FS_READ_FILE |
			LANDLOCK_ACCESS_FS_READ_DIR |
			LANDLOCK_ACCESS_FS_EXECUTE,
		    .parent_fd = fd,
		};
		if (landlock_add_rule(landlock_fd, LANDLOCK_RULE_PATH_BENEATH,
		    &lpba, 0) == -1) {
			saved_errno = errno;
			close(fd);
			errno = saved_errno;
			return -1;
		}
		close(fd);

		fd = open(".", O_PATH | O_CLOEXEC);
		if (fd == -1)
			return -1;
		lpba = (struct landlock_path_beneath_attr) {
		    .allowed_access =
			LANDLOCK_ACCESS_FS_READ_DIR |
			LANDLOCK_ACCESS_FS_READ_FILE |
			LANDLOCK_ACCESS_FS_WRITE_FILE |
			LANDLOCK_ACCESS_FS_REMOVE_DIR |
			LANDLOCK_ACCESS_FS_REMOVE_FILE |
			LANDLOCK_ACCESS_FS_MAKE_DIR |
			LANDLOCK_ACCESS_FS_MAKE_REG |
			LANDLOCK_ACCESS_FS_REFER,
		    .parent_fd = fd,
		};
		if (landlock_abi >= 2)
			lpba.allowed_access |= LANDLOCK_ACCESS_FS_REFER;
		if (landlock_add_rule(landlock_fd, LANDLOCK_RULE_PATH_BENEATH,
		    &lpba, 0) == -1) {
			saved_errno = errno;
			close(fd);
			errno = saved_errno;
			return -1;
		}
		close(fd);

	}

	return (0);
}
