#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class CTimer
{
public:

    CTimer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();

private:

    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
};

#endif // TIMER_H
