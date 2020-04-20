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

SUBDIRS = include compat src
ACLOCAL_AMFLAGS = -I m4

taldir = $(RPKI_TAL_DIR)
tal_DATA = afrinic.tal apnic.tal lacnic.tal ripe.tal

EXTRA_DIST = README.md VERSION $(tal_DATA)

install-data-hook:
	-@if [ ! -d "$(DESTDIR)$(RPKI_BASE_DIR)" ]; then \
		if [ "`id -u`" = "0" ]; then \
			$(INSTALL) -m 755 -o $(RPKI_USER) -d "$(DESTDIR)$(RPKI_BASE_DIR)"; \
		else \
			$(INSTALL) -m 755 -d "$(DESTDIR)$(RPKI_BASE_DIR)"; \
			echo "Warning: Unprivileged permissions, remember to run" \
				"'chown $(RPKI_USER) $(DESTDIR)$(RPKI_BASE_DIR)'"; \
		fi \
	fi
	-@if [ ! -d "$(DESTDIR)$(RPKI_OUT_DIR)" ]; then \
		if [ "`id -u`" = "0" ]; then \
			$(INSTALL) -m 755 -o $(RPKI_USER) -d "$(DESTDIR)$(RPKI_OUT_DIR)"; \
		else \
			$(INSTALL) -m 755 -d "$(DESTDIR)$(RPKI_OUT_DIR)"; \
			echo "Warning: Unprivileged permissions, remember to run" \
				"'chown $(RPKI_USER) $(DESTDIR)$(RPKI_OUT_DIR)'"; \
		fi \
	fi
