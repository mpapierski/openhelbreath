#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H

#include "Font.h"

//#include "Threading.h"
#include "SDL_thread.h"

class Socket
{
	private:
		bool Connected;
		void KillSocket();
	public:
		Socket(std::string Addr, int Port);
		~Socket();
		void run();
		inline bool IsConnected() const;
		bool Connect();
		void OnDataPresent();
		void Readable(int SizeHeader);
		void Disconnect();
		static int Wrapper(void* param);
		void Start();
		void Join();
		std::string Address;
		int Port;

		fd_set Reader;
		struct timeval Timeout;

		NetSock * Connection;
		Buffer * Data;

		SDL_Thread * Th;
};

class DebugScene : public Scene
{
public:
	DebugScene();
	~DebugScene();

	void Draw(SDL_Surface *Dest);

	void OnLoop();
	void OnEvent(SDL_Event *EventSource);
	void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

	inline void Print(std::string txt);

	std::vector<std::string> backlog;

private:
	SDL_Surface *rect;

	SDL_Surface *TextSurface;

	int state;

	bool _connected;
	Socket * MLSocket;
};

#endif
