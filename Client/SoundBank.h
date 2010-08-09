#ifndef SOUNDBANK_H
#define SOUNDBANK_H

#include <string>
#include <map>

#include <SDL_mixer.h>

typedef std::map<std::string, Mix_Chunk*> SoundMap;

class SoundBank
{
	public:
		SoundBank();
		virtual ~SoundBank();
		void load(const std::string& fileName);
		void play(const std::string& fileName);
		void cleanUp();

		static SoundBank manager;

	private:
		SoundMap soundContainer;
};

#endif // SOUNDBANK_H
