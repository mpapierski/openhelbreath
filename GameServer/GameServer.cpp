#include <stdlib.h>
#include <stdio.h>

#include "GameServer.h"

bool
GameServer::bInitialize()
{

	PutLog("openhelbreath Game Server beta");
	
	if (!bReadMainConfig())
		return false;

#ifdef WIN32
	WSADATA wsdat;
	memset(&wsdat,0,sizeof(wsdat));
	if(WSAStartup(0x0101,&wsdat))
	{
		PutLog("WSAStartup() failed.");
		return false;
	}
#endif

	m_pGateConnector = new CGateConnector();
	m_pGateConnector->start();
	return true;
}

bool
GameServer::bReadMainConfig()
{
	CIniFile * cfg;
	cfg = new CIniFile(DEF_MAINCONFIGFILE);
	char _buf[100];

	if (!cfg->bLoadIni())
	{
		PutLog("(!) Cannot open configuration file.");
		return false;
	}

	m_sServerName = cfg->sGetValue("CONFIG", "game-server-name", "");
	if (m_sServerName == "")
		return false;
		
	if (m_sServerName.length() > 10)
	{
		PutLog("(!!!) Game server name(" + m_sServerName + ") must within 10 chars!");
		return false;
	}
	PutLog("(*) Game server name : "+ m_sServerName);

	m_sGameServerAddr = cfg->sGetValue("CONFIG","game-server-address", "");
	if (m_sGameServerAddr == "")
	{
		PutLog("(*) You must specify game server bind address!");
		return false;
	}

	m_iGameServerPort = cfg->iGetValue("CONFIG", "game-server-port", -1);
	if ( (m_iGameServerPort < 0) || (m_iGameServerPort > 65535) )
		return false;
		
	memset(_buf, 0, sizeof(_buf));
	sprintf(_buf, "(*) Game server port : %d", m_iGameServerPort);
	PutLog(_buf);
	
	m_sGateServerAddr = cfg->sGetValue("CONFIG", "gate-server-address", "");
	if (m_sGateServerAddr == "")
		return false;
		
	PutLog("(*) Gate server address : " + m_sGateServerAddr);
	
	m_iGateServerPort = cfg->iGetValue("CONFIG", "gate-server-port", -1);
	if ( (m_iGateServerPort < 0) || (m_iGateServerPort > 65535) )
		return false;

	memset(_buf, 0, sizeof(_buf));
	sprintf(_buf, "(*) Gate server port : %d", m_iGateServerPort);
	PutLog(_buf);

	vector<string> sMapList = cfg->pGetValuesByName("MAPS", "game-server-map");

	for (unsigned int i = 0; i < sMapList.size(); i++)
	{
		PutLog("(*) Add map (" + sMapList[i] + ") - Loading map info files...");
		if (!bRegisterMap(sMapList[i]))
		{
			PutLog("(!!!) Data file loading fail!");
			return false;
		}
		const CMap & pLoaded = m_pMapList[iGetMapIndex(sMapList[i])];
		memset(_buf, 0, sizeof(_buf));
		sprintf(_buf, "(*) Data file loading success. Map:%s Width:%d Height:%d", pLoaded.m_sMapName.c_str(), pLoaded.m_iSizeX, pLoaded.m_iSizeY);
		PutLog(_buf);
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
			PutLog("(***) Game Server activated!");
			break;
		}
		if (!m_pGateConnector->m_bIsConnected)
		{
			if (iRegisterTimeout == DEF_REGISTERTIMEOUT)
			{
				PutLog("(!!!) Game Server is not activated!");
			}
			else if (iRegisterTimeout == DEF_REGISTERTIMEOUT + 1)
			{
				exit(EXIT_FAILURE);
			}
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

void
GameServer::PutLog(string sMessage, int iLogType)
{
	if (iLogType == LOGTYPE_LOCAL)
	{
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime( &rawtime );
		char s_time[20];
		strftime(s_time, sizeof(s_time), "%Y:%m:%d %H:%M:%S", timeinfo);
		FILE * log = fopen("GameServer.log", "ab");
		fwrite(s_time, 1, sizeof(s_time) - 1, log);
		fputc('\t', log);
		fwrite(sMessage.c_str(), 1, sMessage.length(), log);
#ifdef WIN32
		fputs("\r\n", log);
#else
		fputc('\n', log);
#endif
		fclose(log);
		puts(sMessage.c_str());
		return;
	}

	if (!m_pGateConnector->m_bIsConnected && (iLogType == LOGTYPE_GAMEMASTER ||
				iLogType == LOGTYPE_ITEM ||
				iLogType == LOGTYPE_CRUSADE))
		return;

	Packet * p;

	switch (iLogType)
	{
		case LOGTYPE_GAMEMASTER:
			p = new Packet(MSGID_GAMEMASTERLOG, DEF_MSGTYPE_CONFIRM);
			break;
		case LOGTYPE_ITEM:
			p = new Packet(MSGID_GAMEITEMLOG, DEF_MSGTYPE_CONFIRM);
			break;
		case LOGTYPE_CRUSADE:
			p = new Packet(MSGID_GAMECRUSADELOG, DEF_MSGTYPE_CONFIRM);
			break;
	}
	p->push<char>(sMessage.c_str(), sMessage.length());
	m_pGateConnector->pGetSock()->Write((unsigned char*)p->data(), p->size());
	delete p;
}
