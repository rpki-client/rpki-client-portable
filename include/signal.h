/*
 * signal.h compatibility shim
 * Public domain
 */

#include_next <signal.h>

#ifndef LIBCOMPAT_SIGNAL_H
#define LIBCOMPAT_SIGNAL_H

#ifndef SIGINFO
#define SIGINFO SIGUSR1
#endif

#endif
