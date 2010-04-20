/*
 This file is part of OpenHelbreath.
 OpenHelbreath is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenHelbreath is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenHelbreath.  If not, see <http://www.gnu.org/licenses/>.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>

#include "GameServer.h"

bool GameServer::Initialize()
{
	if (!ReadMainConfig())
		return false;

#ifdef WIN32
	WSADATA wsdat;
	memset(&wsdat, 0, sizeof(wsdat));
	if (WSAStartup(0x0101, &wsdat))
	{
		PutLog("WSAStartup() failed.");
		return false;
	}
#endif

	GateConnector = new CGateConnector();
	GateConnector->Start();
	return true;
}

bool GameServer::ReadMainConfig()
{
	CIniFile * cfg;
	cfg = new CIniFile(DEF_MAINCONFIGFILE);

	if (!cfg->LoadIni())
	{
		PutLog("(!) Cannot open configuration file.");
		return false;
	}

	ServerName = cfg->sGetValue("CONFIG", "game-server-name", "");
	if (ServerName == "")
		return false;

	if (ServerName.length() > 10)
	{
		PutLog("(!!!) Game server name(" + ServerName + ") must within 10 chars!");
		return false;
	}

	PutLog("(*) Game server name : " + ServerName);

	GameServerAddr = cfg->sGetValue("CONFIG", "game-server-address", "");
	if (GameServerAddr == "")
	{
		PutLog("(*) You must specify game server bind address!");
		return false;
	}

	GameServerPort = cfg->iGetValue("CONFIG", "game-server-port", -1);
	if ((GameServerPort < 0) || (GameServerPort > 65535))
		return false;

	PutLog("(*) Game server port : " + toString<int> (GameServerPort));

	GateServerAddr = cfg->sGetValue("CONFIG", "gate-server-address", "");
	if (GateServerAddr == "")
		return false;

	PutLog("(*) Gate server address : " + GateServerAddr);

	GateServerPort = cfg->iGetValue("CONFIG", "gate-server-port", -1);
	if ((GateServerPort < 0) || (GateServerPort > 65535))
		return false;

	PutLog("(*) Gate server port : " + toString<int> (GateServerPort));

	vector<string> sMapList = cfg->GetValuesByName("MAPS", "game-server-map");

	for (unsigned int i = 0; i < sMapList.size(); i++)
	{
		PutLog("(*) Add map (" + sMapList[i] + ") - Loading map info files...");
		if (!RegisterMap(sMapList[i]))
		{
			PutLog("(!!!) Data file loading fail!");
			return false;
		}
		const CMap & pLoaded = MapList[GetMapIndex(sMapList[i])];
		PutLog("(*) Data file loading success. Map:" + pLoaded.m_sMapName + " Width:" + toString<int> (pLoaded.m_iSizeX) + " Height:"
				+ toString<int> (pLoaded.m_iSizeY));
	}

	delete cfg;
	return true;
}

bool GameServer::RegisterMap(string sMapName)
{
	CMap pMapFile(sMapName);
	if (!pMapFile.bReadMapFile())
		return false;
	MapList.push_back(pMapFile);
	return true;
}

int GameServer::GetMapIndex(string sMapName)
{
	int idx = -1;
	for (unsigned int i = 0; i < MapList.size(); i++)
		if (MapList[i].m_sMapName == sMapName)
		{
			idx = i;
			break;
		}
	return idx;
}

void GameServer::Execute()
{
	int iRegisterTimeout = 0;
	while (true)
	{
		if (GateConnector && GateConnector->IsConnected)
		{
			PutLog("(***) Game Server activated!");
			break;
		}
		if (!GateConnector->IsConnected)
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

void GameServer::TimerLoop()
{
	while (true)
	{
		//TODO: Reimplement
		sleep(3);
		if (!GateConnector->IsConnected)
		{
			PutLog("(!!!) No connection to Gate Server!");
			DeadCount++;
			if (DeadCount > 10)
				break;
		}
		Packet p(MSGID_GAMESERVERALIVE, DEF_MSGTYPE_CONFIRM);
		p.push<short> (0); //Total Players
		p.send(GateConnector->GetSock());
	}
}

void GameServer::PutLog(string sMessage, int iLogType)
{
	if (iLogType == LOGTYPE_LOCAL)
	{
		time_t rawtime;
		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
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

	if (!GateConnector->IsConnected && (iLogType == LOGTYPE_GAMEMASTER || iLogType == LOGTYPE_ITEM || iLogType == LOGTYPE_CRUSADE))
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
	p->push<char> (sMessage.c_str(), sMessage.length());
	p->send(GateConnector->GetSock());
	delete p;
}
