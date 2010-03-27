#define DEF_FULLSCREEN
#define DEF_SELECTSERVER //Abaddon, Apocalypse server
#define DEF_SERVERADDR "localhost" //Abaddon (default if DEF_SELECTSERVER is not defined)
#define DEF_SERVERPORT 2848 // Default server port

#ifdef DEF_SELECTSERVER
#	define DEF_SERVERADDR2 "localhost" //Apocalypse
#	define DEF_SERVERPORT2 2849 //Abaddon
#endif


//#define DEBUG

#ifdef DEBUG
#	undef	DEF_FULLSCREEN
#endif

