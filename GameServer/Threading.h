#ifndef THREADING_H
#define THREADING_H

#ifdef WIN32
#	include <windows.h>
#	include <process.h>
#else
#	include <pthread.h>
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

#ifdef WIN32
class CThread
{
public:
	CThread();
	virtual ~CThread();

	bool create(unsigned int stackSize = 0);
	unsigned int threadId() const;
	void start();
	void join();

	void resume();
	void suspend();
	void shutdown();

protected:
	bool canRun();
	virtual void run() = 0;

private:
	static unsigned int __stdcall threadFunc(void *args);

	HANDLE m_hThread;
	unsigned int m_threadId;
	volatile bool m_canRun;
	volatile bool m_suspended;
	Mutex m_mutex;
};
#else
//POSIX implementation


class CThread {
	private:
		pthread_t tid;
		static void* execute(void*p);
	public:
		CThread();
		~CThread();
		void virtual run() = 0;
		void start();
		void shutdown();
		void * join();
};

#endif

class Lock
{
public:
	Lock(Mutex &mutex);
	~Lock();
private:
	Mutex m_mutex;
};

class Semaphore
{
	private:
		int m_iValue;
	public:
		Semaphore(const int iValue = 1);
		~Semaphore() {};
		void acquire();
		void release();
};
#endif

