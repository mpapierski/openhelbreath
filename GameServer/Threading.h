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

#ifndef THREADING_H
#define THREADING_H

#include <stdio.h>

#ifdef WIN32
#	include <windows.h>
#	include <process.h>
#else
#	include <pthread.h>
#	include <signal.h>
#endif

class Mutex
{
	public:
		Mutex();
		~Mutex();
		void acquire();
		void release();
	private:
#ifdef WIN32
		CRITICAL_SECTION m_mutex;
#else
		pthread_mutex_t m_mutex;
#endif
};

// FIXME : pthread support
class Thread
{
	private:
		HANDLE HThread;
		unsigned int ThreadID;
		bool Running;
	public:
		Thread();
		virtual ~Thread();
		void Start();
		void Join();
		void Shutdown();
		static unsigned int Wrapper(void *Args);
		virtual void Run() = 0;

		bool getRunning() const
		{
			return Running;
		}

		void setRunning(bool Val)
		{
			Running = Val;
		}

		inline unsigned int getThreadID() const
		{
			return ThreadID;
		}
};

class Semaphore
{
	private:
		int m_iValue;
	public:
		Semaphore(const int iValue = 1);
		void acquire();
		void release();
};
#endif

