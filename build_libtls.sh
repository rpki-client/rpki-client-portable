#!/bin/sh

V=3.2.5
SUM=798a65fd61d385e09d559810cdfa46512f8def5919264cfef241a7b086ce7cfe

set -e

cd /tmp
wget https://cdn.openbsd.org/pub/OpenBSD/LibreSSL/libressl-${V}.tar.gz

cat <<EOF | sha256sum -c -
SHA256 (libressl-${V}.tar.gz) = ${SUM}
EOF

wget https://www.zyd.ch/cert.pem
cat <<EOF | sha256sum -c -
SHA256 (cert.pem) = 2ea89861c7fb73506b6c74cc134952aa1fad4311b9b012f5e6d97e949868d045
EOF

sudo install -m 644 cert.pem /etc/ssl/cert.pem

tar xzf libressl-${V}.tar.gz 

cd libressl-${V}
./configure --prefix=/usr --sysconfdir=/etc
make
cd tls
sudo make install
cd ../include
sudo make install-includeHEADERS
