#include "Threading.h"

int Thread::ThreadCount = 0;
Semaphore Thread::ThreadCounter;

Thread::Thread()
{
	Th = 0;
	Thread::ThreadCounter.Acquire();
	ID = Thread::ThreadCount++;
	Thread::ThreadCounter.Release();
	Running = false;
}

Thread::~Thread()
{
	Thread::ThreadCounter.Acquire();
	Thread::ThreadCount--;
	Thread::ThreadCounter.Release();
	if (Running)
		SDL_KillThread(Th);
}

void Thread::Join()
{
	SDL_WaitThread(Th, NULL);
}

int Thread::ThreadID()
{
	return ID;
}

int Thread::ThreadWrapper(void *Param)
{
#ifdef DEBUG
	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = SDL_THREAD_START;
	Ev.user.data1 = Param;
	Ev.user.data2 = reinterpret_cast<int*>((static_cast<Thread*>(Param))->ThreadID());
	SDL_PushEvent(&Ev);
#endif
	(static_cast<Thread*>(Param))->Running = true;
	(static_cast<Thread*>(Param))->Run();
	(static_cast<Thread*>(Param))->Running = false;
#ifdef DEBUG
	Ev.user.code = SDL_THREAD_FINISHED;
	SDL_PushEvent(&Ev);
#endif
	return 0;
}

void Thread::Start()
{
	Th = SDL_CreateThread(ThreadWrapper, this);
}

Semaphore::Semaphore(int Value)
{
	S = SDL_CreateSemaphore(Value);
	if (S == NULL)
		printf("SDL_CreateSemaphore(%d) returns NULL.\n", Value);
}

Semaphore::~Semaphore()
{
	if (S != NULL)
	{
		SDL_DestroySemaphore(S);
		S = 0;
	}
}

void Semaphore::Release()
{
	if (SDL_SemPost(S) == -1)
		printf("SDL_SemPost() returns -1.\n");
}

void Semaphore::Acquire()
{
	if (SDL_SemWait(S) == -1)
		printf("SDL_SemWait() returns -1.\n");
}

Mutex::Mutex()
{
	M = SDL_CreateMutex();
}

void Mutex::Release()
{
	if (SDL_mutexV(M) == -1)
		printf("SDL_mutexV() returns -1.\n");
}

Mutex::~Mutex()
{
	SDL_DestroyMutex(M);
}

void Mutex::Acquire()
{
	if (SDL_mutexP(M) == -1)
		printf("SDL_mutexP() returns -1.\n");
}

