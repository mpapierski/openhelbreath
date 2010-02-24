#include <stdlib.h>
#include <stdio.h>

#include "GameServer.h"

bool
GameServer::bInitialize()
{
	puts("openhelbreath Game Server beta");
	puts("");

	if (!bReadMainConfig())
		return false;

#ifdef WIN32
	WSADATA wsdat;
	memset(&wsdat,0,sizeof(wsdat));
	if(WSAStartup(0x0101,&wsdat))
	{
		puts("WSAStartup() failed.");
		return false;
	}
#endif

	m_pGateConnector = new CGateConnector();
	puts("(*) Gate connector thread start...");
	m_pGateConnector->start();
	return true;
}

bool
GameServer::bReadMainConfig()
{
	CIniFile * cfg;
	
	cfg = new CIniFile(DEF_MAINCONFIGFILE);
	if (!cfg->bLoadIni())
	{
		printf("(!) Cannot open configuration file.\n");
		return false;
	}

	m_sServerName = cfg->sGetValue("CONFIG", "game-server-name", "");
	if (m_sServerName == "")
		return false;
		
	if (m_sServerName.length() > 10)
	{
		printf("(!!!) Game server name(%s) must within 10 chars!\n", m_sServerName.c_str());
		return false;
	}
	
	printf("(*) Game server name : %s\n", m_sServerName.c_str());
	
	m_sGameServerAddr = cfg->sGetValue("CONFIG","game-server-address", "");
	if (m_sGameServerAddr == "")
	{
		printf("(*) You must specify game server bind address!\n");
		return false;
	}

	m_iGameServerPort = cfg->iGetValue("CONFIG", "game-server-port", -1);
	if ( (m_iGameServerPort < 0) || (m_iGameServerPort > 65535) )
		return false;
		
	printf("(*) Game server port : %d\n", m_iGameServerPort);
	
	
	m_sGateServerAddr = cfg->sGetValue("CONFIG", "gate-server-address", "");
	if (m_sGateServerAddr == "")
		return false;
		
	printf("(*) Gate server address : %s\n", m_sGateServerAddr.c_str());

	m_iGateServerPort = cfg->iGetValue("CONFIG", "gate-server-port", -1);
	if ( (m_iGateServerPort < 0) || (m_iGateServerPort > 65535) )
		return false;
	printf("(*) Gate server port : %d\n", m_iGateServerPort);
	
	vector<string> sMapList = cfg->pGetValuesByName("MAPS", "game-server-map");
	for (unsigned int i = 0; i < sMapList.size(); i++)
	{
		printf("(*) Add map (%s) - Loading map info files...\n", sMapList[i].c_str());
		if (!bRegisterMap(sMapList[i]))
		{
			printf("(!!!) Data file loading fail!\n");
			return false;
		}
		const CMap & pLoaded = m_pMapList[iGetMapIndex(sMapList[i])];
		printf("(*) Data file loading success. Map:%s Width:%d Height:%d\n", pLoaded.m_sMapName.c_str(), pLoaded.m_iSizeX, pLoaded.m_iSizeY);
	}
	
	delete cfg;
	return true;
}

bool
GameServer::bRegisterMap(string sMapName)
{
	CMap pMapFile(sMapName);
	if (!pMapFile.bReadMapFile())
		return false;
	m_pMapList.push_back(pMapFile);
	return true;
}

int
GameServer::iGetMapIndex(string sMapName)
{
	for (unsigned int i = 0; i < m_pMapList.size(); i++)
	{
		if (m_pMapList[i].m_sMapName == sMapName)
		{
			return i;
		}
	}
	return -1;
}

void
GameServer::Execute()
{
	int iRegisterTimeout = 0;
	while (true)
	{
		if (m_pGateConnector && m_pGateConnector->m_bIsConnected)
		{
			puts("(***) Game Server activated!");
			break;
		}
		if (iRegisterTimeout == DEF_REGISTERTIMEOUT)
		{
			puts("(!!!) Game Server is not activated!");
		}
		else if (iRegisterTimeout == DEF_REGISTERTIMEOUT + 1)
		{
			exit(EXIT_FAILURE);
		}
		sleep(1);
		iRegisterTimeout += 1;
	}
	TimerLoop();
}
	
void
GameServer::TimerLoop()
{
	while (true)
	{
		//TODO : Timer support
		sleep(1);
	}
}
