#include "Sound.h"

CSound CSound::SoundControl;

CSound::CSound()
{
    //ctor
}

int CSound::OnLoad(const std::string &FileName)
{
    Mix_Chunk* TempSound = NULL;

    if((TempSound = Mix_LoadWAV(FileName.c_str())) == NULL)
    {
        printf("Unable to load: %s", FileName.c_str());
        return -1;
    }

    SoundList.push_back(TempSound);

    int ret (SoundList.size() - 1);
    return ret;
}

void CSound::OnCleanup()
{
    for(unsigned int i = 0; i < SoundList.size(); i++)
    {
        Mix_FreeChunk(SoundList[i]);
    }

    SoundList.clear();
}

void CSound::Play(unsigned int ID)
{
    if(ID < 0 || ID >= SoundList.size()) return;
    if(SoundList[ID] == NULL) return;

    Mix_PlayChannel(-1, SoundList[ID], 0);
}

void CSound::Volume(int level)
{
    printf("Average volume is %d\n",Mix_Volume(-1, level));
}
