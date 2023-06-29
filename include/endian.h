/*
 * Public domain
 * endian.h compatibility shim
 */
#ifndef LIBCOMPAT_ENDIAN_H
#define LIBCOMPAT_ENDIAN_H

#ifdef HAVE_ENDIAN_H
#include_next <endian.h>
#else

#if defined(__APPLE__) && !defined(HAVE_ENDIAN_H)
#include <libkern/OSByteOrder.h>
#define be16toh(x) OSSwapBigToHostInt16((x))
#define htobe16(x) OSSwapHostToBigInt16((x))
#define be32toh(x) OSSwapBigToHostInt32((x))
#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define htobe64(x) OSSwapHostToBigInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#endif /* __APPLE__ && !HAVE_ENDIAN_H */

#endif
#endif
