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

AC_INIT([rpki-client], m4_esyscmd([tr -d '\n' < VERSION]))

AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_PROG_CC([cc gcc])

case $host_os in
	*darwin*)
		HOST_OS=darwin
		AC_DEFINE([SPT_TYPE], [SPT_REUSEARGV])
		;;
	*freebsd*)
		HOST_OS=freebsd
		;;
	*linux*)
		HOST_OS=linux
		CFLAGS="$CFLAGS -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_GNU_SOURCE"
		AC_DEFINE([SPT_TYPE], [SPT_REUSEARGV])
		;;
	*netbsd*)
		HOST_OS=netbsd
		;;
	*openbsd*)
		HOST_OS=openbsd
		AC_DEFINE([HAVE_ATTRIBUTE__BOUNDED__], [1], [OpenBSD has __bounded__])
		AC_DEFINE([HAVE_ATTRIBUTE__DEAD], [1], [OpenBSD has __dead])
		;;
	*solaris*)
		HOST_OS=solaris
		CFLAGS="$CFLAGS -D__EXTENSIONS__ -D_XOPEN_SOURCE=600 -DBSD_COMP"
		;;
	*) ;;
esac

AM_CONDITIONAL([HOST_DARWIN],  [test x$HOST_OS = xdarwin])
AM_CONDITIONAL([HOST_FREEBSD], [test x$HOST_OS = xfreebsd])
AM_CONDITIONAL([HOST_LINUX],   [test x$HOST_OS = xlinux])
AM_CONDITIONAL([HOST_NETBSD],  [test x$HOST_OS = xnetbsd])
AM_CONDITIONAL([HOST_SOLARIS], [test x$HOST_OS = xsolaris])

AC_PROG_SED
AC_PROG_CC
AC_PROG_CC_STDC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL

AC_ARG_ENABLE(warnings,
	AS_HELP_STRING([--disable-warnings],
	[ enable compiler warnings [default=enabled]]),
    [case $enableval in
	    yes) enable_warnings=yes;;
	    no) enable_warnings=no;;
	    *) enable_warnings=yes;; esac],
    enable_warnings=yes)

if test "$enable_warnings" = yes; then
	AM_CFLAGS="$AM_CFLAGS -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wshadow -Wpointer-arith -Wsign-compare -Werror-implicit-function-declaration"
	#AC_SUBST(AM_CFLAGS, ["-Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wshadow -Wpointer-arith -Wsign-compare -Werror-implicit-function-declaration"])

	save_cflags="$CFLAGS"
	CFLAGS=-Wno-pointer-sign
	AC_MSG_CHECKING([whether CC supports -Wno-pointer-sign])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
	    [AC_MSG_RESULT([yes])]
	    [WARN_CFLAGS=-Wno-pointer-sign],
	    [AC_MSG_RESULT([no])]
	)
	AM_CFLAGS="$AM_CFLAGS $WARN_CFLAGS"
	CFLAGS="$save_cflags"
fi

AC_MSG_CHECKING([if compiling with clang])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [[
#ifndef __clang__
	not clang
#endif
	]])],
	[AC_MSG_RESULT([yes])]
	[CLANG_FLAGS=-Qunused-arguments],
	[AC_MSG_RESULT([no])]
)
AM_CFLAGS="$AM_CFLAGS $CLANG_FLAGS"
AM_LDFLAGS="$LDFLAGS $CLANG_FLAGS"
AC_SUBST(AM_CFLAGS)
AC_SUBST(AM_LDFLAGS)

AC_ARG_WITH([openssl],
	AS_HELP_STRING([--with-openssl=pkg-name],
		[Use pkg-config(1) pkg-name to find OpenSSL files]),
	PKG_NAME="$withval"
)
if test X"$PKG_NAME" != X; then
	OPENSSL_CFLAGS=`pkg-config --cflags-only-I $PKG_NAME 2>/dev/null`
	OPENSSL_LDFLAGS=`pkg-config --libs-only-L $PKG_NAME 2>/dev/null`
fi

AC_ARG_WITH([openssl-cflags],
	AS_HELP_STRING([--with-openssl-cflags=STRING],
		[Extra compiler flags to build with OpenSSL]),
	OPENSSL_CFLAGS="$withval"
)
AC_ARG_WITH([openssl-ldflags],
	AS_HELP_STRING([--with-openssl-ldflags=STRING],
		[Extra flags for linker to link with OpenSSL libraries]),
	OPENSSL_LDFLAGS="$withval"
)
AC_SUBST(OPENSSL_CFLAGS)
AC_SUBST(OPENSSL_LDFLAGS)

CFLAGS="$CFLAGS $OPENSSL_CFLAGS"
CPPFLAGS="$CPPFLAGS $OPENSSL_CFLAGS"
LDFLAGS="$LDFLAGS $OPENSSL_LDFLAGS"

AC_ARG_WITH([libtls],
	AS_HELP_STRING([--with-libtls=pkg-name],
		[Use pkg-config(1) pkg-name to find LibreSSL libtls]),
	PKG_NAME="$withval"
)
if test X"$PKG_NAME" != X; then
	LIBTLS_CFLAGS=`pkg-config --cflags-only-I $PKG_NAME 2>/dev/null`
	LIBTLS_LDFLAGS=`pkg-config --libs-only-L $PKG_NAME 2>/dev/null`
fi

AC_ARG_WITH([libtls-cflags],
	AS_HELP_STRING([--with-libtls-cflags=STRING],
		[Extra compiler flags to build with LibreSSL libtls]),
	LIBTLS_CFLAGS="$withval"
)
AC_ARG_WITH([libtls-ldflags],
	AS_HELP_STRING([--with-libtls-ldflags=STRING],
		[Extra flags for linker to link with libtls library]),
	LIBTLS_LDFLAGS="$withval"
)
AC_SUBST(LIBTLS_CFLAGS)
AC_SUBST(LIBTLS_LDFLAGS)

CFLAGS="$CFLAGS $LIBTLS_CFLAGS"
CPPFLAGS="$CPPFLAGS $LIBTLS_CFLAGS"
LDFLAGS="$LDFLAGS $LIBTLS_LDFLAGS"

AC_ARG_WITH([expat],
	AS_HELP_STRING([--with-expat=pkg-name],
		[Use pkg-config(1) pkg-name to find Expat]),
	PKG_NAME="$withval"
)
if test X"$PKG_NAME" != X; then
	LIBEXPAT_CFLAGS=`pkg-config --cflags-only-I $PKG_NAME 2>/dev/null`
	LIBEXPAT_LDFLAGS=`pkg-config --libs-only-L $PKG_NAME 2>/dev/null`
fi

AC_ARG_WITH([expat-cflags],
	AS_HELP_STRING([--with-expat-cflags=STRING],
		[Extra compiler flags to build with Expat]),
	LIBEXPAT_CFLAGS="$withval"
)
AC_ARG_WITH([expat-ldflags],
	AS_HELP_STRING([--with-libtls-ldflags=STRING],
		[Extra flags for linker to link with Expat library]),
	LIBEXPAT_LDFLAGS="$withval"
)
AC_SUBST(LIBEXPAT_CFLAGS)
AC_SUBST(LIBEXPAT_LDFLAGS)

CFLAGS="$CFLAGS $LIBEXPAT_CFLAGS"
CPPFLAGS="$CPPFLAGS $LIBEXPAT_CFLAGS"
LDFLAGS="$LDFLAGS $LIBEXPAT_LDFLAGS"

# check functions that are expected to be in libc
AC_CHECK_FUNCS([explicit_bzero])
AC_CHECK_FUNCS([reallocarray recallocarray freezero])
AC_CHECK_FUNCS([setproctitle setgroups])
AC_CHECK_FUNCS([setregid setresgid setreuid setresuid])
AC_CHECK_FUNCS([memrchr strlcat strlcpy strtonum])
AC_CHECK_FUNCS([pledge unveil])
AC_CHECK_FUNCS([getdtablecount pipe2 ppoll])
AC_CHECK_FUNCS([strnvis])

dnl NetBSD added an strnvis and unfortunately made it incompatible with the
dnl existing one in OpenBSD and Linux's libbsd (the former having existed
dnl for over ten years). Despite this incompatibility being reported during
dnl development (see http://gnats.netbsd.org/44977) they still shipped it.
dnl Even more unfortunately FreeBSD and later MacOS picked up this incompatible
dnl implementation.  Try to detect this mess, and assume the only safe option
dnl if we're cross compiling.
dnl
dnl OpenBSD, 2001: strnvis(char *dst, const char *src, size_t dlen, int flag);
dnl NetBSD: 2012,  strnvis(char *dst, size_t dlen, const char *src, int flag);
if test "x$ac_cv_func_strnvis" = "xyes"; then
 AC_MSG_CHECKING([for working strnvis])
 AC_RUN_IFELSE(
  [AC_LANG_PROGRAM([[
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vis.h>
static void sighandler(int sig) { _exit(1); }
  ]], [[
 char dst[16];

 signal(SIGSEGV, sighandler);
 if (strnvis(dst, "src", 4, 0) && strcmp(dst, "src") == 0)
  exit(0);
 exit(1)
  ]])],
  [AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])
   ac_cv_broken_strnvis="yes" ],
  [AC_MSG_WARN([cross compiling: assuming broken])
   ac_cv_broken_strnvis="yes" ]
 )
fi


# check functions that are expected to be in libutil
AC_SEARCH_LIBS([ibuf_open], [util])
AC_CHECK_FUNCS([ibuf_open])

# check functions that are expected to be in libresolv
AC_SEARCH_LIBS([inet_net_pton],[resolv])
AC_CHECK_FUNCS([inet_net_pton])
# check if inet_net_pton code can be used
if test "x$ac_cv_func_inet_net_pton" = "xyes"; then
  AC_MSG_CHECKING([for working inet_net_pton])
  AC_RUN_IFELSE(
  [AC_LANG_PROGRAM([[
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
  ]], [[
  struct in_addr ia;
  struct in6_addr ia6;

  if (inet_net_pton(AF_INET, "192.0.2.0/24", &ia, sizeof(ia)) != 24)
	  exit(1);
  if (inet_net_pton(AF_INET6, "2001:db8::/32", &ia6, sizeof(ia6)) != 32)
	  exit(1);
  exit(0);
  ]])],
  [AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])
    ac_cv_broken_inet_net_pton="yes" ],
  [AC_MSG_WARN([cross compiling: assuming broken])
    ac_cv_broken_inet_net_pton="yes" ]
  )
fi

# check if HOST_NAME_MAX is available
AC_MSG_CHECKING([for HOST_NAME_MAX])
AC_COMPILE_IFELSE(
 [AC_LANG_PROGRAM([[
#include <limits.h>
#include <unistd.h>
]], [[
  char buf[HOST_NAME_MAX + 1];
]])],
 [AC_MSG_RESULT([yes])
  AC_DEFINE(HAVE_HOST_NAME_MAX) ],
 [AC_MSG_RESULT([no])]
)

# check functions that may be in different libs on other systems
AC_CHECK_HEADERS([fts.h], [], [AC_MSG_ERROR([fts.h is required])])
AC_SEARCH_LIBS([fts_open],[fts])
AC_CHECK_FUNCS([fts_open])

# Share test results with automake
AM_CONDITIONAL([HAVE_EXPLICIT_BZERO], [test "x$ac_cv_func_explicit_bzero" = xyes])
AM_CONDITIONAL([HAVE_REALLOCARRAY], [test "x$ac_cv_func_reallocarray" = xyes])
AM_CONDITIONAL([HAVE_RECALLOCARRAY], [test "x$ac_cv_func_recallocarray" = xyes])
AM_CONDITIONAL([HAVE_FREEZERO], [test "x$ac_cv_func_freezero" = xyes])
AM_CONDITIONAL([HAVE_SETPROCTITLE], [test "x$ac_cv_func_setproctitle" = xyes])
AM_CONDITIONAL([HAVE_SETGROUPS], [test "x$ac_cv_func_setgroups" = xyes])
AM_CONDITIONAL([HAVE_SETRESGID], [test "x$ac_cv_func_setresgid" = xyes])
AM_CONDITIONAL([HAVE_SETRESUID], [test "x$ac_cv_func_setresuid" = xyes])
AM_CONDITIONAL([HAVE_MEMRCHR], [test "x$ac_cv_func_memrchr" = xyes])
AM_CONDITIONAL([HAVE_STRLCAT], [test "x$ac_cv_func_strlcat" = xyes])
AM_CONDITIONAL([HAVE_STRLCPY], [test "x$ac_cv_func_strlcpy" = xyes])
AM_CONDITIONAL([HAVE_STRTONUM], [test "x$ac_cv_func_strtonum" = xyes])
AM_CONDITIONAL([HAVE_PLEDGE], [test "x$ac_cv_func_pledge" = xyes])
AM_CONDITIONAL([HAVE_UNVEIL], [test "x$ac_cv_func_unveil" = xyes])
AM_CONDITIONAL([HAVE_GETDTABLECOUNT], [test "x$ac_cv_func_getdtablecount" = xyes])
AM_CONDITIONAL([HAVE_PIPE2], [test "x$ac_cv_func_pipe2" = xyes])
AM_CONDITIONAL([HAVE_PPOLL], [test "x$ac_cv_func_ppoll" = xyes])
AM_CONDITIONAL([HAVE_INET_NET_PTON], [test "x$ac_cv_func_inet_net_pton" = xyes])
AM_CONDITIONAL([BROKEN_INET_NET_PTON], [test "x$ac_cv_broken_inet_net_pton" = xyes])

AM_CONDITIONAL([HAVE_STRNVIS], [test "x$ac_cv_func_strnvis" = xyes])
AM_CONDITIONAL([BROKEN_STRNVIS], [test "x$ac_cv_broken_strnvis" = xyes])
AM_CONDITIONAL([HAVE_IMSG], [test "x$ac_cv_func_ibuf_open" = xyes])

AC_CHECK_HEADERS([err.h sha2.h])

AC_CHECK_HEADERS([openssl/cms.h openssl/err.h openssl/evp.h openssl/ssl.h openssl/x509.h openssl/x509v3.h], [], [AC_MSG_ERROR([OpenSSL headers required])])
AC_CHECK_LIB([crypto], [ASN1_STRING_get0_data], [], [AC_MSG_ERROR([OpenSSL libraries required])])
AC_CHECK_FUNCS([X509_up_ref], [], [AC_MSG_ERROR([OpenSSL libraries required])])
AC_CHECK_FUNCS([ASIdentifiers_free IPAddressRange_free X509v3_addr_is_canonical X509v3_asid_is_canonical], [], [AC_MSG_ERROR([libcrypto with RFC3779 support required])])

AC_CHECK_HEADERS([tls.h], [], [AC_MSG_ERROR([LibreSSL libtls headers required])])
AC_SEARCH_LIBS([tls_read],[tls-standalone tls retls], [], [AC_MSG_ERROR([LibreSSL libtls library required])], [-lssl -lcrypto])
AC_CHECK_FUNCS([tls_default_ca_cert_file tls_config_set_ca_mem], [], [AC_MSG_ERROR([LibreSSL libtls library required])])

# check for libressl special functions after including libtls in case
# these are present in that library
AC_CHECK_FUNCS([ASN1_time_parse ASN1_time_tm_cmp OPENSSL_cleanup X509_get0_uids])
# Needed for OpenSSL compat. May be replaceable once we require LibreSSL 3.6.0.
AM_CONDITIONAL([HAVE_ASN1_TIME_PARSE], [test "x$ac_cv_func_ASN1_time_parse" = xyes])
AM_CONDITIONAL([HAVE_ASN1_TIME_TM_CMP], [test "x$ac_cv_func_ASN1_time_tm_cmp" = xyes])
# available since LibreSSL 3.6.0
AM_CONDITIONAL([HAVE_OPENSSL_CLEANUP], [test "x$ac_cv_func_OPENSSL_cleanup" = xyes])
# available since LibreSSL 3.7.1
AM_CONDITIONAL([HAVE_X509_GET0_UIDS], [test "x$ac_cv_func_X509_get0_uids" = xyes])

AC_CHECK_HEADERS([expat.h], [], [AC_MSG_ERROR([Expat headers required])])
AC_CHECK_LIB([expat], [XML_Parse], [], [AC_MSG_ERROR([Expat library required])])
AC_CHECK_FUNCS([XML_Parse XML_SetUserData], [], [AC_MSG_ERROR([Expat library required])])

AC_ARG_ENABLE(landlock,
	AS_HELP_STRING([--disable-landlock],
		[ use landlock if available  [default=enabled]]),
	[case $enableval in
		yes) enable_landlock=yes;;
		no) enable_landlock=no;;
		*) enable_landlock=yes;; esac],
	enable_landlock=yes)


if test "x$enable_landlock" = "xyes"; then
	AC_CHECK_HEADERS([linux/landlock.h])
	if test "x$ac_cv_header_linux_landlock_h" = xyes; then
		AC_DEFINE([HAVE_LANDLOCK])
	fi
	AM_CONDITIONAL([HAVE_LANDLOCK], [test "x$ac_cv_header_linux_landlock_h" = xyes])
fi

AC_ARG_WITH([user],
	AS_HELP_STRING([--with-user=user],
		[User for rpki-client to use when run as root]),
	RPKI_USER="$withval",
	RPKI_USER="_rpki-client"
)
AC_DEFINE_UNQUOTED(RPKI_CLIENT_USER, "$RPKI_USER", [Unprivileged user])
AC_SUBST(RPKI_USER)

AC_ARG_WITH([rsync],
	AS_HELP_STRING([--with-rsync=command],
		[Rsync command to use]),
	RSYNC="$withval"
)
if test X"$RSYNC" = X; then
	AC_CHECK_PROGS([RSYNC], [openrsync rsync])
fi
if test X"$RSYNC" = X; then
   AC_MSG_ERROR([No rsync binary found in $PATH])
fi
AC_DEFINE_UNQUOTED(RPKI_RSYNC_CMD, "$RSYNC", [Rsync command])

AC_ARG_WITH([tal-dir],
	AS_HELP_STRING([--with-tal-dir=path],
		[Path to the default TAL directory]),
	RPKI_TAL_DIR="$withval",
	RPKI_TAL_DIR="$sysconfdir/rpki"
)
AC_SUBST(RPKI_TAL_DIR)

AC_ARG_WITH([base-dir],
	AS_HELP_STRING([--with-base-dir=path],
		[Location to store the RPKI cache repository]),
	RPKI_BASE_DIR="$withval",
	RPKI_BASE_DIR="$localstatedir/cache/rpki-client"
)
AC_SUBST(RPKI_BASE_DIR)

AC_ARG_WITH([output-dir],
	AS_HELP_STRING([--with-output-dir=path],
		[Path to the default output directory]),
	RPKI_OUT_DIR="$withval",
	RPKI_OUT_DIR="$localstatedir/db/rpki-client"
)
AC_SUBST(RPKI_OUT_DIR)

AC_CONFIG_FILES([
	Makefile
	include/Makefile
	compat/Makefile
	src/Makefile
])

AC_OUTPUT
