#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "Misc.h"
#include "GameServer.h"

int main (int argc, char *argv[])
{
	if (!GameServer::getInstance().bInitialize())
	{
		puts("(!!!) Game Server initialization failed!");
		exit(EXIT_FAILURE);
	}
	GameServer::getInstance().Execute();
	return 0;
}
