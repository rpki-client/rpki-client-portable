/*
 * Public domain
 * sys/socket.h compatibility shim
 */

#include_next <sys/socket.h>

#if !defined(SOCK_CLOEXEC) || !defined(SOCK_NONBLOCK)
#define NEED_SOCKET_FLAGS
int _socket(int domain, int type, int protocol);
int _socketpair(int domain, int type, int protocol, int socket_vector[2]);
#ifndef IN_SOCKET_COMPAT
#define socket(d, t, p) _socket(d, t, p)
#define socketpair(d, t, p, s) _socketpair(d, t, p, s)
#endif
#endif

#ifndef SOCK_NONBLOCK
#define SOCK_NONBLOCK  0x4000 /* set O_NONBLOCK */
#endif

#ifndef SOCK_CLOEXEC
#define SOCK_CLOEXEC  0x8000 /* set FD_CLOEXEC */
#endif
