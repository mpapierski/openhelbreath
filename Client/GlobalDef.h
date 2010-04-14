#ifndef GLOBALDEF_H
#define GLOBALDEF_H

///////////////////////////////////////////////////////////////////////////////
#define DEBUG // Debug messages
#define DEF_FPSLIMIT 60
#define DEF_SELECTSERVER //Abaddon, Apocalypse server
#define DEF_FULLSCREEN // Run game in full screen
#define DEF_MAKEACCOUNT // Enable account creation from Client
#define DEF_CONSOLE  // Relocate stdout to console Window (Win32)
#define DEF_CHECKVERSION // Server version check
///////////////////////////////////////////////////////////////////////////////

#define DEF_SERVER_ADDR "localhost" // Server address (Default address)
#define DEF_SERVER_PORT 2848 // Server port (Default port)
#define DEF_SERVER_NAME1 "WS1" // Abaddon server name (Default)
#define DEF_SERVER_NAME2 "WS2" // Apocalypse server name (Apocalypse)
#define MSG_HOMEPAGE "http://code.google.com/p/openhelbreath"

#define DEF_LOWERVERSION 3
#define DEF_UPPERVERSION 82

#define DEF_MAXSPRITES 30

#ifdef DEBUG
#	if !defined(WIN32)
#		undef DEF_CONSOLE
#	endif
#	undef DEF_FULLSCREEN // No full screen while debug mode
#	undef DEF_CHECKVERSION // No version checking in Debug
#else
#	undef DEF_CONSOLE
#endif

#define DEF_BUFFERSIZE 128 * 1024 // Max buffer size (128Kb)

// Custom SDL events used by networking
#define SDL_NETWORK_INIT		0x00000001
#define SDL_NETWORK_CONNECTED	0x00000002
#define SDL_NETWORK_CLOSED		0x00000003
#define SDL_NETWORK_ERROR		0x00000004
#define SDL_NETWORK_RECEIVE		0x00000005
#define SDL_NETWORK_FINISH		0x00000006
#define SDL_NETWORK_BUSY		0x00000007

// Thread debugging
#define SDL_THREAD_START		0x00000008
#define SDL_THREAD_FINISHED		0x00000009

// Dialog button result...
#define SDL_CLICKED_LEFT		0x0000000A
#define SDL_CLICKED_RIGHT		0x0000000B

#endif // GLOBALDEF_H
