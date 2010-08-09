#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
{
	public:
		Config();
		virtual ~Config();
		bool load(const std::string& fileName);

	private:
		// game settings
		bool enableSound;
		int soundVolume;
		bool enableMusic;
		int musicVolume;
		int detalis;
		bool transparency;
		int transparencyLevel;
		bool ekScreenShot;
};

#endif // CONFIG_H
