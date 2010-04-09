#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#define DEF_FULLSCREEN
//#define DEF_FPSLIMIT 60

#define DEF_SELECTSERVER //Abaddon, Apocalypse server
#define DEF_SERVERADDR "localhost" //Abaddon address (Default address)
#define DEF_SERVERPORT 2848 //Abaddon port (Default port)
#ifdef DEF_SELECTSERVER
#	define DEF_SERVERADDR2 "localhost" //Apocalpyse address
#	define DEF_SERVERPORT2 2849 //Apocalypse port
#endif

#define DEF_MAKEACCOUNT // Enable account creation from Client
#define DEF_MAXSPRITES 20

#define DEBUG

#ifdef DEBUG
#	undef DEF_FULLSCREEN
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

#endif // GLOBALDEF_H
