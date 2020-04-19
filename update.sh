#!/bin/sh
set -e

openbsd_branch=`cat OPENBSD_BRANCH`
openbgpd_version=`cat VERSION`

# pull in latest upstream code
echo "pulling upstream openbsd source"
if [ ! -d openbsd ]; then
	if [ -z "${RPKICLIENT_GIT}" ]; then
		git clone https://github.com/rpki-client/rpki-client-openbsd.git openbsd
	else
		git clone "${RPKICLIENT_GIT}/openbsd"
	fi
fi
(cd openbsd/src
 git fetch
 git checkout "${openbsd_branch}"
 git pull --rebase)

# setup source paths
dir=`pwd`
patches="${dir}/patches"
etc_src="${dir}/openbsd/src/etc/rpki"
libc_inc="${dir}/openbsd/src/include"
libc_src="${dir}/openbsd/src/lib/libc"
rpkiclient_src="${dir}/openbsd/src/usr.sbin/rpki-client"

do_cp_libc() {
	sed "/DEF_WEAK/d" < "${1}" > "${2}"/`basename "${1}"`
}
CP_LIBC='do_cp_libc'
CP='cp -p'
MV='mv -f'
PATCH='patch -s'

echo "copying tal"
${CP} ${etc_src}/*.tal "${dir}"

echo "copying includes"
sed '/DECLS/d' "${libc_inc}/sha2.h" > include/sha2_openbsd.h

for i in explicit_bzero.c strlcpy.c strlcat.c; do
	${CP_LIBC} "${libc_src}/string/${i}" compat
done
for i in reallocarray.c recallocarray.c; do
	${CP_LIBC} "${libc_src}/stdlib/${i}" compat
done
${CP_LIBC} "${libc_src}/hash/sha2.c" compat

for i in as.c cert.c cms.c crl.c extern.h io.c ip.c log.c main.c \
	mft.c output-bgpd.c output-bird.c output-csv.c output-json.c \
	output.c roa.c rpki-client.8 rsync.c tal.c validate.c x509.c; do
	file=`basename ${i}`
	echo Copying ${file}
	${CP} "${rpkiclient_src}/${i}" src
done

if [ -n "$(ls -A patches/*.patch 2>/dev/null)" ]; then
	for i in patches/*.patch; do
		echo "Applying patch ${i}"
		(cd src && ${PATCH} -p3 < "${dir}/${i}")
	done
	${MV} src/rpki-client.8 src/rpki-client.8.in 
fi
