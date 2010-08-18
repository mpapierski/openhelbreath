#include "SoundBank.h"

SoundBank SoundBank::manager;

SoundBank::SoundBank()
{

}

SoundBank::~SoundBank()
{

}

void SoundBank::load(const std::string& fileName)
{
	std::string path;

	Mix_Chunk* tempSound = NULL;

	path = "SOUNDS/" + fileName + ".WAV";

	tempSound = Mix_LoadWAV(path.c_str());
	if(tempSound == NULL)
	{
		fprintf(stderr, "Unable to load: %s. %s\n", path.c_str(), Mix_GetError());
	}
	else
	{
		soundContainer[fileName] = tempSound;
		fprintf(stdout, "Sound: %s loaded.\n", path.c_str());
	}
}

void SoundBank::play(const std::string& fileName)
{
	SoundMap::iterator p = soundContainer.find(fileName);
	if (p == soundContainer.end())
	{
		fprintf(stderr, "Can not play sound: \"%s\" !\n", fileName.c_str());
		return;
	}
	Mix_PlayChannel(-1, soundContainer[fileName], 0);
}

void SoundBank::cleanUp()
{
	SoundMap::iterator p;
	for (p = soundContainer.begin(); p != soundContainer.end(); ++p)
	{
		Mix_Chunk* val = p->second;
		Mix_FreeChunk(val);
	}
}
