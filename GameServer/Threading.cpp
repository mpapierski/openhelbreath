#include "Threading.h"

#ifdef WIN32
Mutex::Mutex()
{
	InitializeCriticalSection(&m_mutex);
}
Mutex::~Mutex()
{
	DeleteCriticalSection(&m_mutex);
}
void Mutex::acquire()
{
	EnterCriticalSection(&m_mutex);
}
void Mutex::release() {
	LeaveCriticalSection(&m_mutex);
}

#else

Mutex::Mutex() {
	pthread_mutex_init(&m_mutex,NULL);
}
Mutex::~Mutex() {
	pthread_mutex_destroy(&m_mutex);
}

void Mutex::acquire() {
	pthread_mutex_lock(&m_mutex);
}
void Mutex::release() {
	pthread_mutex_unlock(&m_mutex);
}
#endif

#ifdef WIN32

CThread::CThread()

{
	m_hThread = 0;
	m_threadId = 0;
	m_canRun = true;
	m_suspended = true;
	m_bRunning = false;
	create();
}

CThread::~CThread()
{
	if (m_hThread)
	{
		if (m_bRunning)
		{
			kill();
		}
		CloseHandle(m_hThread);
	}
}

bool CThread::canRun()
{
	Lock guard(m_mutex);
	return m_canRun;
}

bool CThread::create(unsigned int stackSize)
{
	m_hThread = reinterpret_cast<HANDLE>(_beginthreadex(0, stackSize,
		threadFunc, this, CREATE_SUSPENDED, &m_threadId));

	if (m_hThread)
		return true;

	return false;
}

void CThread::join()
{
	WaitForSingleObject(m_hThread, INFINITE);
}

void CThread::resume()
{
	if (m_suspended)
	{
		Lock guard(m_mutex);

		if (m_suspended)
		{
			ResumeThread(m_hThread);
			m_suspended = false;
		}
	}
}

void CThread::shutdown()
{
	if (m_canRun)
	{
		Lock guard(m_mutex);

		if (m_canRun)
			m_canRun = false;

		resume();
	}
}

void CThread::start()
{
	resume();
}

void CThread::suspend()
{
	if (!m_suspended)
	{
		Lock guard(m_mutex);

		if (!m_suspended)
		{
			SuspendThread(m_hThread);
			m_suspended = true;
		}
	}
}

unsigned int CThread::threadId() const
{
	return m_threadId;
}

unsigned int __stdcall CThread::threadFunc(void *args)
{
	CThread *pThread = reinterpret_cast<CThread*>(args);

	if (pThread)
	{
		pThread->run();
		pThread->m_suspended = true;
	}

	_endthreadex(0);
	return 0;
}

void CThread::kill()
{
	TerminateThread(&m_threadId, 0);
	CloseHandle(m_hThread);
}

#else

//POSIX
void* CThread::execute(void*p)
{
	static_cast<CThread*>(p)->run();
	return NULL;
}

CThread::CThread() {}
CThread::~CThread() { kill(); }

void CThread::start()
{
	pthread_create(&tid, NULL, CThread::execute, this);
}
void CThread::shutdown()
{
	pthread_exit((void*)0);
}
void * CThread::join()
{
	void* ret;
	if (pthread_join(tid, &ret))
		return NULL;
	return ret;
}
void CThread::kill()
{
	pthread_cancel(tid);	
}
#endif

Lock::Lock(Mutex &mutex) : m_mutex(mutex) {
	m_mutex.acquire();
}

Lock::~Lock()
{
	m_mutex.release();
}

Semaphore::Semaphore(const int iValue)
{
	m_iValue = iValue;
}

void
Semaphore::acquire()
{
	do
	{}
	while (m_iValue > 0);
	m_iValue -= 1;
}

void
Semaphore::release()
{
	m_iValue += 1;
}
