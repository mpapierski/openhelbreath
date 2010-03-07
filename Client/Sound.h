#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <vector>

#include <SDL_mixer.h>

class CSound
{
public:
    static CSound SoundControl;

    CSound();

    std::vector<Mix_Chunk*> SoundList;

    int OnLoad(const std::string &FileName);

    void OnCleanup();

    void Play(unsigned int ID);

    void Volume(int level);
};

#endif // SOUND_H
