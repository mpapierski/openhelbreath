#include <stdlib.h>
#include <vector>
#include "GameServer.h"
#include "IniFile.h"
#include "GlobalDef.h"

CGameServer::CGameServer(string cConfigFile)
{
	m_sConfigFile = DEF_MAINCONFIG;
}

CGameServer::~CGameServer()
{
	//CGameServer destructor
}

bool CGameServer::bInit()
{
	printf("(!) INITIALIZING GAME SERVER...\n");
	if (!bReadProgramConfigFile(m_sConfigFile)) {
		printf("\n");
		printf("(!!!) CRITICAL ERROR! Cannot execute server! %s file contents error!\n", m_sConfigFile.c_str());
		return false;	
	}
	return true;
}


bool CGameServer::bReadProgramConfigFile(string sFileName)
{
	
	CIniFile * cfg;
	
	cfg = new CIniFile(sFileName);
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
	
	m_sGameServerAddr = cfg->pGetValuesByName("CONFIG","game-server-address");
	if (m_sGameServerAddr.size() == 0)
	{
		printf("(*) You must specify at least one bind address for game server!\n");
		return false;
	}
	for (unsigned int i = 0;i<m_sGameServerAddr.size(); ++i)
		printf("(*) Game server bind address : %s\n", m_sGameServerAddr[i].c_str());
	
	m_iGameServerPort = cfg->iGetValue("CONFIG", "game-server-port", -1);
	if ( (m_iGameServerPort < 0) || (m_iGameServerPort > 65535) )
		return false;
		
	printf("(*) Game server port : %d\n", m_iGameServerPort);
	
	
	m_sLogServerAddr = cfg->sGetValue("CONFIG", "log-server-address", "");
	if (m_sLogServerAddr == "")
		return false;
		
	printf("(*) Log server address : %s\n", m_sLogServerAddr.c_str());

	m_iGateServerPort = cfg->iGetValue("CONFIG", "gate-server-port", -1);
	if ( (m_iGateServerPort < 0) || (m_iGateServerPort > 65535) )
		return false;
	printf("(*) Gate server port : %d\n", m_iGateServerPort);
	
	vector<string> sMapList = cfg->pGetValuesByName("MAPS", "game-server-map");
	for (unsigned int i = 0; i < sMapList.size(); i++)
	{
		printf("(*) Add map (%s) - Loading map info files...\n", sMapList[i].c_str());
		if (!_bRegisterMap(sMapList[i]))
		{
			printf("(!!!) Data file loading fail!\n");
			return false;
		}
		const CMap & pLoaded = pGetMapByName(sMapList[i]);
		printf("(*) Data file loading success. Map:%s Width:%d Height:%d\n", pLoaded.m_sMapName.c_str(), pLoaded.m_iSizeX, pLoaded.m_iSizeY);
	}
	
	delete cfg;
	return true;
}


bool CGameServer::_bRegisterMap(string sMapName)
{
	CMap pMapFile(sMapName);
	if (!pMapFile.bReadMapFile())
		return false;
		
	m_pMapList.push_back(pMapFile);
	return true;
}

CMap & CGameServer::pGetMapByName(string sMapName)
{
	for (unsigned int i = 0; i < m_pMapList.size(); ++i)
		if (m_pMapList[i].m_sMapName == sMapName)
			return m_pMapList[i];		
}
