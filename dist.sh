#!/bin/sh
set -e
set -x

tree=`dirname $0`
cd $tree
version=`cat VERSION`

if [ -d "../rpki-client-$version" ]; then
	echo "error: directory ../rpki-client-portable-$version already exists."
	exit 1
fi

mkdir "../rpki-client-$version"
cp -a ./ "../rpki-client-$version/"

cd "../rpki-client-$version"

# cleanup
find ./ -name \*.orig -o -name \*.rej -o -name \*~ -delete

# remove git things
rm -fr .git .gitignore .travis.yml

# remove files created by configure
rm -fr	Makefile \
	compat/.deps/ \
	compat/Makefile \
	config.log \
	config.status \
	include/Makefile \
	libtool \
	src/rpki-client/.deps/ \
	src/rpki-client/Makefile


tar -C .. -czf ../rpki-client-$version.tar.gz rpki-client-$version

# remove files created by running autogen.sh
#rm -fr Makefile.in \
#	aclocal.m4 \
#	autom4te.cache/ \
#	compile \
#	config.guess \
#	config.sub \
#	configure \
#	depcomp \
#	install-sh \
#	ltmain.sh \
#	m4/ \
#	missing \
#	openbsd/ \
