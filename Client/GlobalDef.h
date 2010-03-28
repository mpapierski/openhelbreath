#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#define DEF_FULLSCREEN
#define DEF_FPSLIMIT 60

#define DEF_SELECTSERVER //Abaddon, Apocalypse server
#define DEF_SERVERADDR "localhost" //Abaddon address (Default address)
#define DEF_SERVERPORT 2848 //Abaddon port (Default port)

#ifdef DEF_SELECTSERVER
#	define DEF_SERVERADDR2 "localhost" //Apocalpyse address
#	define DEF_SERVERPORT2 2849 //Apocalypse port
#endif

#define DEF_MAXSPRITES 10

//#define DEBUG

#ifdef DEBUG
#	undef DEF_FULLSCREEN
#endif

#endif // GLOBALDEF_H
