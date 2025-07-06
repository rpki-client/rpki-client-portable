#
# Copyright (c) 2014 Brent Cook
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -DSHA2_SMALL

noinst_LTLIBRARIES = libcompat.la libcompatnoopt.la

# compatibility functions that need to be built without optimizations
libcompatnoopt_la_CFLAGS = -O0
libcompatnoopt_la_SOURCES =

if !HAVE_EXPLICIT_BZERO
libcompatnoopt_la_SOURCES += explicit_bzero.c
endif

# other compatibility functions
libcompat_la_SOURCES =
libcompat_la_LIBADD = $(PLATFORM_LDADD)

libcompat_la_SOURCES += socket.c

if !HAVE_REALLOCARRAY
libcompat_la_SOURCES += reallocarray.c
endif

if !HAVE_RECALLOCARRAY
libcompat_la_SOURCES += recallocarray.c
endif

if !HAVE_FREEZERO
libcompat_la_SOURCES += freezero.c
endif

if !HAVE_INET_NET_PTON
libcompat_la_SOURCES += inet_net_pton.c
endif
if BROKEN_INET_NET_PTON
libcompat_la_SOURCES += inet_net_pton.c
endif

if !HAVE_PIPE2
libcompat_la_SOURCES += pipe2.c
endif

if !HAVE_PPOLL
libcompat_la_SOURCES += ppoll.c
endif

if !HAVE_MEMRCHR
libcompat_la_SOURCES += memrchr.c
endif

if !HAVE_STRLCAT
libcompat_la_SOURCES += strlcat.c
endif

if !HAVE_STRLCPY
libcompat_la_SOURCES += strlcpy.c
endif

if !HAVE_STRTONUM
libcompat_la_SOURCES += strtonum.c
endif

if !HAVE_SETPROCTITLE
libcompat_la_SOURCES += setproctitle.c
endif

if !HAVE_SETRESGID
libcompat_la_SOURCES += bsd-setresgid.c
endif

if !HAVE_SETRESUID
libcompat_la_SOURCES += bsd-setresuid.c
endif

if !HAVE_STRNVIS
libcompat_la_SOURCES += vis.c
endif
if BROKEN_STRNVIS
libcompat_la_SOURCES += vis.c
endif

if !HAVE_IMSG
libcompat_la_SOURCES += imsg.c
libcompat_la_SOURCES += imsg-buffer.c
endif

if !HAVE_CMS_GET_VERSION
libcompat_la_SOURCES += cms_lib.c
endif

if !HAVE_X509_GET0_UIDS
libcompat_la_SOURCES += x509_get0_uids.c
endif

if !HAVE_X509_CRL_GET0_TBS_SIGALG
libcompat_la_SOURCES += x509_crl_get0_tbs_sigalg.c
endif

if !HAVE_PLEDGE
libcompat_la_SOURCES += pledge.c
endif

if !HAVE_UNVEIL
if HAVE_LANDLOCK
libcompat_la_SOURCES += unveil_landlock.c
else
libcompat_la_SOURCES += unveil.c
endif
endif

if !HAVE_ARC4RANDOM
libcompat_la_SOURCES += arc4random.c
libcompat_la_SOURCES += arc4random_uniform.c

if !HAVE_GETENTROPY
if HOST_FREEBSD
libcompat_la_SOURCES += getentropy_freebsd.c
endif
if HOST_LINUX
libcompat_la_SOURCES += getentropy_linux.c
libcompat_la_SOURCES += sha2.c
endif
if HOST_NETBSD
libcompat_la_SOURCES += getentropy_netbsd.c
endif
if HOST_DARWIN
libcompat_la_SOURCES += getentropy_osx.c
libcompat_la_SOURCES += sha2.c
endif
if HOST_SOLARIS
libcompat_la_SOURCES += getentropy_solaris.c
libcompat_la_SOURCES += sha2.c
endif
endif
endif

noinst_HEADERS = arc4random.h
noinst_HEADERS += arc4random_freebsd.h
noinst_HEADERS += arc4random_linux.h
noinst_HEADERS += arc4random_netbsd.h
noinst_HEADERS += arc4random_osx.h
noinst_HEADERS += arc4random_solaris.h
noinst_HEADERS += arc4random_win.h
noinst_HEADERS += chacha_private.h
