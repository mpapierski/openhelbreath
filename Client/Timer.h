#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
	public:
		Timer();
		void start();
		void stop();
		void pause();
		void unPause();
		int getTicks();
		bool isStarted();
		bool isPaused();

	private:
		int startTicks;
		int pausedTicks;
		bool paused;
		bool started;
};

#endif // TIMER_H
