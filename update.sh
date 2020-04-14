#!/bin/sh
set -e

openbsd_branch=`cat OPENBSD_BRANCH`
openbgpd_version=`cat VERSION`

# pull in latest upstream code
echo "pulling upstream openbsd source"
if [ ! -d openbsd ]; then
	if [ -z "${OPENBGPD_GIT}" ]; then
		git clone https://github.com/openbgpd-portable/openbgpd-openbsd.git openbsd
	else
		git clone "${OPENBGPD_GIT}/openbsd"
	fi
fi
(cd openbsd/src
 git fetch
 git checkout "${openbsd_branch}"
 git pull --rebase)

# setup source paths
dir=`pwd`
patches="${dir}/patches"
etc_src="${dir}/openbsd/src/etc"
libc_inc="${dir}/openbsd/src/include"
libc_src="${dir}/openbsd/src/lib/libc"
arc4random_src="${dir}/openbsd/src/lib/libcrypto/arc4random"
libutil_src="${dir}/openbsd/src/lib/libutil"
sbin_src="${dir}/openbsd/src/usr.sbin"

do_cp_libc() {
	sed "/DEF_WEAK/d" < "${1}" > "${2}"/`basename "${1}"`
}
CP_LIBC='do_cp_libc'
CP='cp -p'
PATCH='patch -s'

echo "copying includes"
#${CP} "${etc_src}/rpki/*.tal" ./src/rpki-client/
sed '/DECLS/d' "${libc_inc}/sha2.h" > include/sha2_openbsd.h

for i in strlcpy.c strlcat.c; do
	${CP_LIBC} "${libc_src}/string/${i}" compat
done
${CP_LIBC} "${libc_src}/stdlib/reallocarray.c" compat
${CP_LIBC} "${libc_src}/stdlib/recallocarray.c" compat
${CP_LIBC} "${libc_src}/stdlib/strtonum.c" compat
${CP_LIBC} "${libc_src}/hash/md5.c" compat
${CP_LIBC} "${libc_src}/hash/sha2.c" compat

for j in rpki-client ; do
	for i in `awk '/SOURCES|HEADERS|MANS/ { print $3 }' src/$j/Makefile.am |grep -v top_srcdir` ; do
		src=$j
#		[ ! -f $sbin_src/$src/$i ] && src=bgpd
		[ ! -f $sbin_src/$src/$i ] && continue
		echo Copying $i
		$CP $sbin_src/$src/$i src/$j/$i
	done
done

if [ -n "$(ls -A patches/*.patch 2>/dev/null)" ]; then
	for i in patches/*.patch; do
		echo "Applying patch ${i}"
		(cd src && ${PATCH} -p2 < "${dir}/${i}")
	done
fi
