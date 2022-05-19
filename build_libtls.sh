#!/bin/sh
#
# This script is only used to build a version of libtls on the CI systems.
# Once there are offical packages available it will be removed again.

V=3.5.3
SUM=3ab5e5eaef69ce20c6b170ee64d785b42235f48f2e62b095fca5d7b6672b8b28

set -e

cd /tmp
wget https://cdn.openbsd.org/pub/OpenBSD/LibreSSL/libressl-${V}.tar.gz

cat <<EOF | sha256sum -c -
SHA256 (libressl-${V}.tar.gz) = ${SUM}
EOF

tar xzf libressl-${V}.tar.gz 

cd libressl-${V}
./configure --prefix=/usr --sysconfdir=/etc --enable-libtls-only
make
# install libtls
sudo make install
