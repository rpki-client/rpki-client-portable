This is a port of OpenBSD's rpki-client to other operating systems. It
is based on portability code from the OpenBGPD, OpenNTPD, OpenSSH, and
LibreSSL portable projects.

The current portable tree can be found at
https://github.com/rpki-client/rpki-client-portable

[![Build CI](https://github.com/rpki-client/rpki-client-portable/workflows/Build%20CI/badge.svg)](https://github.com/rpki-client/rpki-client-portable/actions?query=workflow%3A%22Build+CI%22)
[![Build Status](https://travis-ci.org/rpki-client/rpki-client-portable.svg?branch=master)](https://travis-ci.org/github/rpki-client/rpki-client-portable)
[![Docker Pulls](https://img.shields.io/docker/pulls/rpki/rpki-client.svg)](https://hub.docker.com/r/rpki/rpki-client)

Platform Requirements
---------------------

At the time of writing the portable version is known to build and work on:

 - OpenBSD-current
 - Alpine 3.12
 - Debian 9, 10
 - Fedora 31, 32, 33
 - RHEL/CentOS 7, 8

Building
--------

    $ ./configure
    $ make

rpki-client may work on other operating systems, newer and older, but the above
ones are tested regularly by the developer.

Reports (success or otherwise) are welcome. You may report bugs or submit pull
requests at the GitHub project: https://github.com/rpki-client/rpki-client-portable

Thanks,
  Sebastian Benoit <benno at openbsd.org>,
  Job Snijders <job @ openbsd.org>
