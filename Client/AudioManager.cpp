#include "AudioManager.h"

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		fprintf(stderr, "Couldn't open audio: %s", SDL_GetError());
		exit(-1);
	}
#ifdef DEBUG
	puts("AudioManager::AudioManager();");
#endif
}

AudioManager::~AudioManager()
{
	SoundMap::iterator p;
	for (p = SoundBank.begin(); p != SoundBank.end(); ++p)
	{
		std::string key = p->first;
		Mix_Chunk* val = p->second;
#ifdef DEBUG
		printf("Free: %s\n", key.c_str());
#endif
		Mix_FreeChunk(val);
	}
#ifdef DEBUG
	puts("SDL_CloseAudio();");
#endif
	SDL_CloseAudio();
}

void AudioManager::CallbackWrapper(void *userdata, Uint8 *stream, int len)
{
	((AudioManager*) userdata)->DeviceReady(stream, len);
}

void AudioManager::DeviceReady(Uint8 *stream, int len)
{
#ifdef DEBUG
	puts("DeviceReady");
#endif
}

void AudioManager::Add(std::string Source, int AudioType)
{
	std::string Path;
	switch (AudioType)
	{
		case AUDIO_MUSIC:
			Path = "MUSIC/" + Source + ".WAV";
			break;
		case AUDIO_SOUND:
			Path = "SOUNDS/" + Source + ".WAV";
			break;
	}
#ifdef DEBUG
	printf("AudioManager::Add(\"%s\");\n", Path.c_str());
#endif

	Mix_Chunk * Temp;
	if ((Temp = Mix_LoadWAV(Path.c_str())) == NULL)
	{
		printf("*** Error: Mix_LoadWAV(\"%s\") == NULL\n", Path.c_str());
		return;
	}
	SoundBank[Source] = Temp;
}

void AudioManager::Play(std::string Key, bool Loop)
{
	SoundMap::iterator p = SoundBank.find(Key);
	if (p == SoundBank.end())
	{
		printf("AudioManager can not play sound named \"%s\" !\n", Key.c_str());
		return;
	}
	Mix_PlayChannel(-1, SoundBank[Key], Loop ? -1 : 0);
}

