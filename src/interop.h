#ifndef __INTEROP_H__
#define __INTEROP_H__

// Platform-dependant abstractions

#ifdef linux
void Sleep(long msec);
#else
#include <windows.h>
#endif//linux

#endif//__INTEROP_H__

