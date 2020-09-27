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

if !HAVE_REALLOCARRAY
libcompat_la_SOURCES += reallocarray.c
endif

if !HAVE_RECALLOCARRAY
libcompat_la_SOURCES += recallocarray.c
endif

if !HAVE_STRLCAT
libcompat_la_SOURCES += strlcat.c
endif

if !HAVE_STRLCPY
libcompat_la_SOURCES += strlcpy.c
endif

if !HAVE_SETRESGID
libcompat_la_SOURCES += bsd-setresgid.c
endif

if !HAVE_SETRESUID
libcompat_la_SOURCES += bsd-setresuid.c
endif

if !HAVE___B64_PTON
libcompat_la_SOURCES += bsd-b64_pton.c
endif
