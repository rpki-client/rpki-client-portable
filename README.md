This is a port of OpenBSDs rpki-client to other operating systems. It
is based on portability code from the OpenNTPD, OpenSSH, and LibreSSL
portable projects.

The current portable tree can be found at
XXX https://github.com/openbgpd-portable/openbgpd-portable XXX

[![Build Status](https://travis-ci.org/openbgpd-portable/openbgpd-portable.svg?branch=master)](https://travis-ci.org/openbgpd-portable/openbgpd-portable)

Platform Requirements
---------------------

At the time of writing the Portable version is known to build and work on:

 - OpenBSD-current
 - OpenBSD (6.6)
 - Linux (Debian 9)
 - FreeBSD (12.x)

rpki-client may work on other operating systems, newer and older, but the above
ones are tested regularly by the developer.

Reports (success or otherwise) are welcome. You may report bugs or submit pull
requests at the GitHub project: https://github.com/openbgpd-portable

Thanks,
  Sebastian Benoit <benno at openbsd.org>,
  Claudio Jeker <claudio at openbsd.org> and
  Brent Cook <bcook at openbsd.org>.
