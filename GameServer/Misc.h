#ifndef MISC_H
#	define MISC_H

#	ifdef WIN32
#		include "NetSock.h"
		int usleep(long usec);
		int sleep(long sec);
#	else
#		include <unistd.h>
#	endif

#endif
