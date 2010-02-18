#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "Misc.h"
#include "GameServer.h"

int main (int argc, char *argv[])
{
	
	GameServer::getInstance().Initialize();
	GameServer::getInstance().m_pGateConnector->join();
	puts("Bye.");	
	return 0;
}
