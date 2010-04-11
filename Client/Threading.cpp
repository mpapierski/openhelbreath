#include "Threading.h"

Thread::Thread()
{
	Th = 0;
	ID = 0;
}

Thread::~Thread()
{
	SDL_KillThread(Th);
}

void Thread::Join()
{
	int status;
	SDL_WaitThread(Th, &status);
}

int Thread::ThreadID()
{
	return ID;
	//int ThId = SDL_GetThreadID(Th);
	//return ThId == 0 ? ID : (ID = ThId);
}

int Thread::ThreadWrapper(void *Param)
{
#ifdef DEBUG
	SDL_Event Ev;
	Ev.type = SDL_USEREVENT;
	Ev.user.code = SDL_THREAD_START;
	Ev.user.data1 = Param;
	Ev.user.data2 = (int*)SDL_ThreadID();
	SDL_PushEvent(&Ev);
#endif
	((Thread*) Param)->ID = SDL_ThreadID();
	((Thread*) Param)->Run();
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

