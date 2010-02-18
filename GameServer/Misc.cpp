#include "Misc.h"

#ifdef WIN32

int usleep(long usec)
{
	struct timeval tv;
	tv.tv_sec = usec/1000000L;
	tv.tv_usec = usec%1000000L;
	fd_set dummy;
	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	FD_ZERO(&dummy);
	FD_SET(s, &dummy);
	return select(1, 0, 0, &dummy, &tv);
}

int sleep(long sec)
{
	return usleep(sec * 1000000L);
}

#endif

