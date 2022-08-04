/*
 * Public domain
 * pledge dummy function
 */

#include <unistd.h>

int
pledge(const char *promises, const char *execpromises)
{
#ifdef HAVE_LANDLOCK
	pledge_landlock(promises);
#endif
	return 0;
}
