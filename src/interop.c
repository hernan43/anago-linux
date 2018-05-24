#include "interop.h"

#ifdef linux
#include <time.h>
#include <errno.h>
#else
#include <windows.h>
#endif//linux

#ifdef linux
void Sleep(long msec) {
	struct timespec delay, remaining;
	delay.tv_sec = msec / 1000;
	delay.tv_nsec = (msec % 1000) * 1000000;
	while(1) {
		int rc = nanosleep(&delay, &remaining);
		if(rc == 0 || errno != EINTR) {
			break;
		}
		delay.tv_sec = remaining.tv_sec;
		delay.tv_nsec = remaining.tv_nsec;
	}
}
#endif//linux

