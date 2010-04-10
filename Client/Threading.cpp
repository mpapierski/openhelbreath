#include "Threading.h"

Thread::Thread()
{
	Th = 0;
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

int Thread::ThreadWrapper(void *Param)
{
	((Thread*) Param)->Run();
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

