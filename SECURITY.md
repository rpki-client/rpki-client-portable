# Security Policy

This security policy for [rpki-client][1] applies to
the [rpki-client-portable][2] repository and
the version of [rpki-client][3] in [OpenBSD][4].

## Security and reliability fixes

Backports for security and reliability fixes are only provided for [OpenBSD][4].
They usually result in a new portable [release][5] at the same time.

### Reporting vulnerabilities

Please send a mail to [security@rpki-client.org][6].

- Include OS version and the rpki-client version number: `rpki-client -V`.
- Please strive for brevity and focus on the bug itself.
- A short summary written by a human with a modicum of understanding
  is strongly preferred over any generated output.
- If you refer to line numbers, please mention the RCS tag
  (`/* $OpenBSD: ... $ */`) at the top of the relevant source files.

[1]: https://www.rpki-client.org/
[2]: https://github.com/rpki-client/rpki-client-portable/
[3]: https://man.openbsd.org/rpki-client.8
[4]: https://www.openbsd.org/
[5]: https://github.com/rpki-client/rpki-client-portable/releases
[6]: mailto:security@rpki-client.org
