#ifndef GLOBALDEF_H_
#define GLOBALDEF_H_

//Compilator independent code configuration. Propably useless.

#ifdef __WIN32__
	#define WINDOWS
	#undef __WIN32__
#endif

#ifdef __WIN32
	#define WINDOWS
	#undef __WIN32
#endif

#ifdef _WIN32
	#define WINDOWS
	#undef _WIN32
#endif

#ifndef linux 
	#ifdef __linux
		#define linux
		#undef __linux
	#endif
	#ifdef __linux__
		#define linux
		#undef __linux__
	#endif
#endif

#ifdef linux
	#undef linux
	#define LINUX
#endif

#define DEBUG //DEBUG VERSION

#define DEF_HB_LOWERVERSION 3
#define DEF_HB_UPPERVERSION 82

#define DEF_LOWERVERSION 0
#define DEF_UPPERVERSION 1

#define RELEASE_NOTES "beta"

#define DEF_MAINCONFIG "gserver.cfg"
#endif /*GLOBALDEF_H_*/
