This is a port of OpenBSDs rpki-client to other operating systems. It
is based on portability code from the OpenNTPD, OpenSSH, and LibreSSL
portable projects.

The current portable tree can be found at
XXX https://github.com/sebastianbenoit/rpki-client-portable XXX

Platform Requirements
---------------------

At the time of writing the Portable version is known to build and work on:

 - OpenBSD-current
 - XXX

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
