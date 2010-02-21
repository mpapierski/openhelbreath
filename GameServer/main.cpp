#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "Misc.h"
#include "GameServer.h"

int main (int argc, char *argv[])
{
	
	GameServer::getInstance().Initialize();
	
	while (true)
	{
		for (int i = 0; i < DEF_MAXGATESOCKET; i++)
		{
			printf("Sock-%d buffer size: %d.\n", i, GameServer::getInstance().m_pGateConnector->m_pBuffer[i]->size());
		}
		sleep(5);
	}
	return 0;
}
