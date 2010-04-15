#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL_mixer.h>
#include <string>
#include <map>

#include "GlobalDef.h"

#define AUDIO_MUSIC 1
#define AUDIO_SOUND 2

typedef std::map<std::string, Mix_Chunk*> SoundMap;
typedef std::pair<std::string, Mix_Chunk*> SoundPair;

class AudioManager
{
	public:
		AudioManager();
		virtual ~AudioManager();
		static void CallbackWrapper(void *userdata, Uint8 *stream, int len);
		void DeviceReady(Uint8 *stream, int len);
		void Add(std::string Source, int AudioType);
		void Play(std::string Key, bool Loop = false);

	private:
		SoundMap SoundBank;
};

#endif // AUDIOMANAGER_H
