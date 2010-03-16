#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
    Timer();
    
    void Start();
    
    void Stop();
    
    void Pause();
    
    void Unpause();
    
    int GetTicks();
    
    bool IsStarted();
    
    bool IsPaused();

private:
    int StartTicks;
    
    int PausedTicks;
    
    bool Paused;
    
    bool Started;
};

#endif // TIMER_H
