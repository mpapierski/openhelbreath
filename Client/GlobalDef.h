/****************************************************************
*		 This client was writen by Diuuude & Snoopy81.			*
*					Based on Cleroth work.						*
*																*
*			V3.51 compatibility by Cleroth						*
*			V3.51 dialogs by Diuuude							*
*			Effects, mobs, Apocalypse, Heldenian				*
*			& finalizing by Snoopy81							*
*			V3.82 Crafting & Angels by Snoopy81					*
*****************************************************************/

/****************************************************************
*	Find here all compilation options							*
*	I removed useless ones and tryed to add some explanations	*
*	( Snoopy81 06/2005 )										*
*****************************************************************/

/*** Put here global data for your server ***/
#define NAME_WORLDNAME1			"WS1" // Name for default (1st) server
#define MSG_WORLDNAME1			"ABADDON Server" // Long name for 1st server...
#define MSG_HOMEPAGE			"http://www.helbreath.com/"
#define DEF_UPPERVERSION		3
#define DEF_LOWERVERSION		82
#define DEF_SERVER_IP			"192.168.1.101"
#define DEF_SERVER_PORT			2848




/*** Some more compilation options ***/
//#define DEF_USING_WIN_IME		// Used for unicode characters (unchecked)
//#define DEF_MAKE_ACCOUNT		// Enable acc creation. Missing sprites, fixed!
//#define DEF_SELECTSERVER		// Show/Hides server selection screen.

// #define DEF_COMMA_GOLD		// Allows to show comma nbe as original HB (ie: 1,200,000)
// #define DEF_4XXP_PER_LVL		// limits xp niv 140, then 4 x XP per lvl (affects XP shown as % on status)


//#define  _DEBUG				// Multi-Client, Instant-logout, Version check, Badwords,
								// Mics debug msgs, CtrlQ for admins, Show status, Cursor position
//#define DEF_WINDOWED_MODE		// Shows HB in a windowed mode (for debug purpose only, sprite will bug....)



/*** Special conditions   ***/
#ifndef _DEBUG
	#undef DEF_WINDOWED_MODE
#endif
