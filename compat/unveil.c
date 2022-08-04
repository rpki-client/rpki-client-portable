/*
 * Public domain
 * unveil dummy function
 */

#include <unistd.h>

int
unveil(const char *path, const char *permissions)
{
	return 0;
}
