#
# Copyright (c) 2019 Brent Cook
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

AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/src/rpki-client

ACLOCAL_AMFLAGS = -Im4

sbin_PROGRAMS = rpki-client
dist_man_MANS = rpki-client.8

rpki_client_CFLAGS = $(CFLAGS)
rpki_client_CFLAGS += -DSYSCONFDIR=\"$(sysconfdir)\"
rpki_client_CFLAGS += -DLOCALSTATEDIR=\"$(localstatedir)\"

rpki_client_LDADD = $(PLATFORM_LDADD) $(PROG_LDADD) -lcrypto
rpki_client_LDADD += $(top_builddir)/compat/libcompat.la
rpki_client_LDADD += $(top_builddir)/compat/libcompatnoopt.la

rpki_client_SOURCES = as.c
rpki_client_SOURCES += cert.c
rpki_client_SOURCES += cms.c
rpki_client_SOURCES += crl.c
rpki_client_SOURCES += io.c
rpki_client_SOURCES += ip.c
rpki_client_SOURCES += log.c
rpki_client_SOURCES += main.c
rpki_client_SOURCES += mft.c
rpki_client_SOURCES += output.c
rpki_client_SOURCES += output-bgpd.c
rpki_client_SOURCES += output-bird.c
rpki_client_SOURCES += output-csv.c
rpki_client_SOURCES += output-json.c
rpki_client_SOURCES += roa.c
rpki_client_SOURCES += rsync.c
rpki_client_SOURCES += tal.c
rpki_client_SOURCES += validate.c
rpki_client_SOURCES += x509.c

noinst_HEADERS = extern.h
