/***********************************************************************
 *                                                                     *
 *                      openhelbreath GameServer                       *
 *                            26-11-2009                               *
 *                                                                     *
 *                 http://code.google.com/p/openhelbreath/             *
 ***********************************************************************/

#include "Application.h"
#include "GlobalDef.h"

int main (int argc, char *argv[])
{
	CApplication * App;
	App = new CApplication(argc, argv);
	App->Run();
	delete App;
	return 0;
}
