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

#include "Threading.h"

Mutex::Mutex()
{
#ifdef WIN32
	InitializeCriticalSection(&m_mutex);
#else
	pthread_mutex_init(&m_mutex,NULL);
#endif
}

Mutex::~Mutex()
{
#ifdef WIN32
	DeleteCriticalSection(&m_mutex);
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}

void Mutex::acquire()
{
#ifdef WIN32
	EnterCriticalSection(&m_mutex);
#else
	pthread_mutex_lock(&m_mutex);
#endif
}

void Mutex::release()
{
#ifdef WIN32
	LeaveCriticalSection(&m_mutex);
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}

Semaphore::Semaphore(const int iValue)
{
	m_iValue = iValue;
}

void Semaphore::acquire()
{
	do
	{
	} while (m_iValue > 0);
	m_iValue -= 1;
}

void Semaphore::release()
{
	m_iValue += 1;
}

void Thread::Join()
{
	if (getRunning())
	{
		WaitForSingleObject(HThread, INFINITE);
		Running = false;
	}
}

unsigned int __stdcall Thread::Wrapper(void *Args)
{
	Thread * Runner = static_cast<Thread*> (Args);
	Runner->setRunning(true);
	Runner->Run();
	Runner->setRunning(false);
	_endthreadex(0);
	return 0;
}

Thread::Thread()
{
	Running = false;
	HThread = 0;
	ThreadID = 0;
}

void Thread::Shutdown()
{
	if (!TerminateThread(&ThreadID, 0))
	{
		fprintf(stderr, "Could not terminate thread. #%d\n", GetLastError());
	}
}

Thread::~Thread()
{
	Join();
	CloseHandle(HThread);
}

void Thread::Start()
{
	HThread = reinterpret_cast<HANDLE> (_beginthreadex(0, 0, Thread::Wrapper, this, 0, &ThreadID));
}

