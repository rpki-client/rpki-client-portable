<h1><img src="https://rpki-client.org/images/rpki-client.png"></h1>

[![Build CI](https://github.com/rpki-client/rpki-client-portable/workflows/Build%20CI/badge.svg)](https://github.com/rpki-client/rpki-client-portable/actions?query=workflow%3A%22Build+CI%22)
[![Docker Pulls](https://img.shields.io/docker/pulls/rpki/rpki-client.svg)](https://hub.docker.com/r/rpki/rpki-client)

<a href="https://repology.org/project/rpki-client/versions">
    <img src="https://repology.org/badge/vertical-allrepos/rpki-client.svg?exclude_unsupported=1" alt="Packaging status" align="right">
</a>

This is a port of OpenBSD's rpki-client to other operating systems. It
is based on portability code from the OpenBGPD, OpenNTPD, OpenSSH, and
LibreSSL portable projects.

The current portable tree can be found at
https://github.com/rpki-client/rpki-client-portable

Platform Requirements
---------------------

At the time of writing the portable version is known to build and work on:

 - OpenBSD
 - Alpine 3.21, edge
 - CentOS/RHEL/Rocky 8, 9, 10
 - Debian 11, 12, 13
 - Fedora 40, 41, Rawhide
 - Ubuntu 20.04 LTS, 22.04 LTS
 - FreeBSD 12, 13, 14
 - macOS Catalina

Building
--------

The offical release location is https://ftp.openbsd.org/pub/OpenBSD/rpki-client/

Make sure you have an official release tarball!
Use a previously fetched copy of the Signify key or GPG key to confirm authenticity.

    $ ./configure
    $ make

rpki-client may work on other operating systems, newer and older, but the above
ones are tested regularly by the developers.

If you install from a GitHub repository checkout please read the [INSTALL](./INSTALL) file instead.

Reports (success or otherwise) are welcome. You may report bugs or submit pull
requests at the GitHub project: https://github.com/rpki-client/rpki-client-portable

Thanks,
  Sebastian Benoit <benno at openbsd.org>,
  Job Snijders <job @ openbsd.org>
