#!/bin/sh
set -e

openbsd_branch=master
if [ -n "$1" ]; then
	openbsd_branch="$1"
fi

# pull in latest upstream code
echo "pulling upstream openbsd source"
if [ ! -d openbsd ]; then
	if [ -z "${RPKICLIENT_GIT}" ]; then
		git clone https://github.com/rpki-client/rpki-client-openbsd.git openbsd
	else
		git clone "${RPKICLIENT_GIT}/openbsd"
	fi
fi
if [ -d openbsd/.git ]; then
	(cd openbsd
	 git fetch
	 git checkout "${openbsd_branch}"
	 git pull --rebase)
fi

# setup source paths
dir=`pwd`
patches="${dir}/patches"
etc_src="${dir}/openbsd/src/etc/rpki"
libc_inc="${dir}/openbsd/src/include"
libc_src="${dir}/openbsd/src/lib/libc"
arc4random_src="${dir}/openbsd/src/lib/libcrypto/arc4random"
libutil_src="${dir}/openbsd/src/lib/libutil"
rpkiclient_src="${dir}/openbsd/src/usr.sbin/rpki-client"

do_cp_libc() {
	sed "/DEF_WEAK/d" < "${1}" > "${2}"/`basename "${1}"`
}
CP_LIBC='do_cp_libc'
CP='cp -p'
MV='mv -f'
PATCH='patch -s'

echo "copying tal and constraints"
${CP} ${etc_src}/*.tal "${dir}"
${CP} ${etc_src}/*.constraints "${dir}"

echo "copying includes"
sed '/DECLS/d' "${libc_inc}/sha2.h" > include/sha2_openbsd.h
sed '/DECLS/d ; /cdefs.h/d' "${libc_inc}/vis.h" > include/vis.h
sed '/DECLS/d' "${libutil_src}/imsg.h" > include/imsg.h

for i in explicit_bzero.c memrchr.c strlcpy.c strlcat.c; do
	${CP_LIBC} "${libc_src}/string/${i}" compat
done
for i in reallocarray.c recallocarray.c strtonum.c; do
	${CP_LIBC} "${libc_src}/stdlib/${i}" compat
done
${CP_LIBC} "${libc_src}/hash/sha2.c" compat
${CP_LIBC} "${libc_src}/gen/vis.c" compat
${CP_LIBC} "${libc_src}/net/inet_net_pton.c" compat
${CP_LIBC} "${libc_src}/crypt/arc4random.c" compat
${CP_LIBC} "${libc_src}/crypt/arc4random_uniform.c" compat
${CP_LIBC} "${libc_src}/crypt/chacha_private.h" compat
for i in "${arc4random_src}"/getentropy_*.c; do
	sed -e 's/openssl\/sha.h/sha2.h/' < "${i}" > compat/`basename "${i}"`
done
${CP} "${arc4random_src}"/arc4random_*.h compat

${CP} "${libutil_src}/imsg.c" compat/
${CP} "${libutil_src}/imsg-buffer.c" compat/

for i in as.c aspa.c cert.c cms.c constraints.c crl.c encoding.c extern.h \
	filemode.c gbr.c geofeed.c http.c io.c ip.c json.c json.h main.c \
	mft.c mkdir.c ometric.c ometric.h output-bgpd.c output-bird.c \
	output-csv.c output-json.c output-ometric.c output.c parser.c \
	print.c repo.c rfc3779.c roa.c rpki-asn1.h rpki-client.8 rrdp.c \
	rrdp.h rrdp_delta.c rrdp_notification.c rrdp_snapshot.c rrdp_util.c \
	rsc.c rsync.c spl.c tak.c tal.c validate.c version.h x509.c
do
	file=`basename ${i}`
	echo Copying ${file}
	${CP} "${rpkiclient_src}/${i}" src
done

grep RPKI_VERSION "${rpkiclient_src}/version.h" | cut -d '"' -f 2 > VERSION

if [ -n "$(ls -A patches/*.patch 2>/dev/null)" ]; then
	for i in patches/*.patch; do
		echo "Applying patch ${i}"
		(cd src && ${PATCH} -p3 < "${dir}/${i}")
	done
fi

# after patching rename man-page so that configure can adjust placeholders
(cd src && ${MV} rpki-client.8 rpki-client.8.in)
