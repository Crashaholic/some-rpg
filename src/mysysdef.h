#ifndef MY_SYSDEF_H
#define MY_SYSDEF_H

#ifdef __unix__
	#define PLATFORM_LINUX
#endif
#ifdef _WIN32
	#define PLATFORM_WINDOWS
#endif

#endif