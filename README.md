This is a port of OpenBSD's rpki-client to other operating systems. It
is based on portability code from the OpenBGPD, OpenNTPD, OpenSSH, and
LibreSSL portable projects.

The current portable tree can be found at
https://github.com/rpki-client/rpki-client-portable

[![Build CI](https://github.com/rpki-client/rpki-client-portable/workflows/Build%20CI/badge.svg)](https://github.com/rpki-client/rpki-client-portable/actions?query=workflow%3A%22Build+CI%22)
[![Docker Pulls](https://img.shields.io/docker/pulls/rpki/rpki-client.svg)](https://hub.docker.com/r/rpki/rpki-client)

Platform Requirements
---------------------

At the time of writing the portable version is known to build and work on:

 - OpenBSD
 - Alpine 3.13
 - Debian 9, 10
 - Fedora 32, 33, 34
 - macOS Catalina
 - CentOS/RHEL/Rocky 7, 8
 - Windows Subsystem for Linux 2

Building
--------

The offical release location is https://ftp.openbsd.org/pub/OpenBSD/rpki-client/
Make sure you have an official release tarball!
Use a previously fetched copy of the Signify key or GPG key to confirm authenticity.

    $ ./configure
    $ make

rpki-client may work on other operating systems, newer and older, but the above
ones are tested regularly by the developer.

Reports (success or otherwise) are welcome. You may report bugs or submit pull
requests at the GitHub project: https://github.com/rpki-client/rpki-client-portable

Thanks,
  Sebastian Benoit <benno at openbsd.org>,
  Job Snijders <job @ openbsd.org>
