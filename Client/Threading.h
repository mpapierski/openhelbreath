#ifndef THREADING_H_
#define THREADING_H_

#include "SDL_thread.h"

class Thread
{
	private:
		SDL_Thread * Th;
	public:
		Thread();
		virtual ~Thread();
		void Start();
		void Join();
		static int ThreadWrapper(void* Param);
		virtual void Run() = 0;
};

class Locker
{
	public:
		virtual void Acquire() = 0;
		virtual void Release() = 0;
};

class Semaphore : public Locker
{
	private:
		SDL_sem * S;
	public:
		Semaphore(int Value = 1);
		virtual ~Semaphore();
		void Acquire();
		void Release();
};

class Mutex : public Locker
{
	private:
		SDL_mutex * M;
	public:
		Mutex();
		virtual ~Mutex();
		void Acquire();
		void Release();
};
#endif /* THREADING_H_ */
