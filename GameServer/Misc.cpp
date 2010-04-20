/*
 This file is part of OpenHelbreath.
 OpenHelbreath is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenHelbreath is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenHelbreath.  If not, see <http://www.gnu.org/licenses/>.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Misc.h"

#ifdef WIN32

int usleep(long usec)
{
	struct timeval tv;
	tv.tv_sec = usec / 1000000L;
	tv.tv_usec = usec % 1000000L;
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

