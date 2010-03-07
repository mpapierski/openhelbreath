#ifndef MISC_H
#	define MISC_H

#	ifdef WIN32
#		include "NetSock.h"
		int usleep(long usec);
		int sleep(long sec);
#	else
#		include <unistd.h>
#	endif

#include <string>
#include <sstream>

template <class TS>
inline string const toString(TS object)
{
	ostringstream os;
	os << object;
	return os.str();
}
#define itoa(x) (toString<int>(x))
#endif
