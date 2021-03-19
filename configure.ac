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

# check functions that are expected to be in libc
AC_CHECK_FUNCS([explicit_bzero])
AC_CHECK_FUNCS([reallocarray recallocarray freezero])
AC_CHECK_FUNCS([setgroups])
AC_CHECK_FUNCS([setregid setresgid setreuid setresuid])
AC_CHECK_FUNCS([strlcat strlcpy strtonum])
AC_CHECK_FUNCS([pledge unveil])
AC_CHECK_FUNCS([getdtablecount])
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

# check functions that may be in different libs on other systems
AC_SEARCH_LIBS([fts_open],[fts])
AC_CHECK_FUNCS([fts_open])

# Share test results with automake
AM_CONDITIONAL([HAVE_EXPLICIT_BZERO], [test "x$ac_cv_func_explicit_bzero" = xyes])
AM_CONDITIONAL([HAVE_REALLOCARRAY], [test "x$ac_cv_func_reallocarray" = xyes])
AM_CONDITIONAL([HAVE_RECALLOCARRAY], [test "x$ac_cv_func_recallocarray" = xyes])
AM_CONDITIONAL([HAVE_FREEZERO], [test "x$ac_cv_func_freezero" = xyes])
AM_CONDITIONAL([HAVE_SETGROUPS], [test "x$ac_cv_func_setgroups" = xyes])
AM_CONDITIONAL([HAVE_SETRESGID], [test "x$ac_cv_func_setresgid" = xyes])
AM_CONDITIONAL([HAVE_SETRESUID], [test "x$ac_cv_func_setresuid" = xyes])
AM_CONDITIONAL([HAVE_STRLCAT], [test "x$ac_cv_func_strlcat" = xyes])
AM_CONDITIONAL([HAVE_STRLCPY], [test "x$ac_cv_func_strlcpy" = xyes])
AM_CONDITIONAL([HAVE_STRTONUM], [test "x$ac_cv_func_strtonum" = xyes])
AM_CONDITIONAL([HAVE_PLEDGE], [test "x$ac_cv_func_pledge" = xyes])
AM_CONDITIONAL([HAVE_UNVEIL], [test "x$ac_cv_func_unveil" = xyes])
AM_CONDITIONAL([HAVE_GETDTABLECOUNT], [test "x$ac_cv_func_getdtablecount" = xyes])
AM_CONDITIONAL([HAVE_STRNVIS], [test "x$ac_cv_func_strnvis" = xyes])
AM_CONDITIONAL([BROKEN_STRNVIS], [test "x$ac_cv_broken_strnvis" = xyes])
AM_CONDITIONAL([HAVE_IMSG], [test "x$ac_cv_func_ibuf_open" = xyes])

AC_CHECK_HEADERS([err.h sha2.h])

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

AC_CHECK_HEADERS([openssl/cms.h openssl/err.h openssl/evp.h openssl/ssl.h openssl/x509.h openssl/x509v3.h], [], [AC_MSG_ERROR([OpenSSL headers required])])
AC_CHECK_LIB([crypto], [ASN1_STRING_get0_data], [], [AC_MSG_ERROR([OpenSSL libraries required])])
AC_CHECK_FUNCS([X509_up_ref], [], [AC_MSG_ERROR([OpenSSL libraries required])])

AC_CHECK_FUNCS([ASN1_time_parse ASN1_time_tm_cmp])
AM_CONDITIONAL([HAVE_ASN1_TIME_PARSE], [test "x$ac_cv_func_ASN1_time_parse" = xyes])
AM_CONDITIONAL([HAVE_ASN1_TIME_TM_CMP], [test "x$ac_cv_func_ASN1_time_tm_cmp" = xyes])

AC_ARG_WITH([libtls],
	AS_HELP_STRING([--with-libtls=pkg-name],
		[Use pkg-config(1) pkg-name to find LibreSSL libtls files]),
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
		[Extra flags for linker to link with LibreSSL libtls libraries]),
	LIBTLS_LDFLAGS="$withval"
)
AC_SUBST(LIBTLS_CFLAGS)
AC_SUBST(LIBTLS_LDFLAGS)

CFLAGS="$CFLAGS $LIBTLS_CFLAGS"
CPPFLAGS="$CPPFLAGS $LIBTLS_CFLAGS"
LDFLAGS="$LDFLAGS $LIBTLS_LDFLAGS"

AC_CHECK_HEADERS([tls.h], [], [AC_MSG_ERROR([LibreSSL libtls headers required])])
AC_SEARCH_LIBS([tls_read],[tls-standalone tls retls], [], [AC_MSG_ERROR([LibreSSL libtls library required])], [-lssl -lcrypto])
AC_CHECK_FUNCS([tls_default_ca_cert_file tls_config_set_ca_mem], [], [AC_MSG_ERROR([LibreSSL libtls library required])])

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
