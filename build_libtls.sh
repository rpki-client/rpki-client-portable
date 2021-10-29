#!/bin/sh
#
# This script is only used to build a version of libtls on the CI systems.
# Once there are offical packages available it will be removed again.

V=3.4.1
SUM=107ceae6ca800e81cb563584c16afa36d6c7138fade94a2b3e9da65456f7c61c

set -e

cd /tmp
wget https://cdn.openbsd.org/pub/OpenBSD/LibreSSL/libressl-${V}.tar.gz

cat <<EOF | sha256sum -c -
SHA256 (libressl-${V}.tar.gz) = ${SUM}
EOF

tar xzf libressl-${V}.tar.gz 

cd libressl-${V}
./configure --prefix=/usr --sysconfdir=/etc
make
# install libtls
cd tls
sudo make install
# tls.h include
cd ../include
sudo make install-includeHEADERS
# and cert.pem
cd ../apps/openssl
sudo make install-exec-hook
