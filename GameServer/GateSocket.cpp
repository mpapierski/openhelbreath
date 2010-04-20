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

#include "GameServer.h"
#include "GateSocket.h"

CGateConnector::CGateConnector()
{
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
	{
		Buffers[i] = new Buffer(DEF_BUFFERSIZE);
		Sockets[i] = NULL;
	}
	IsConnected = false;
	CurrentSocket = 0;
}

CGateConnector::~CGateConnector()
{
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
	{
		if (Sockets[i] != NULL)
		{
			delete Sockets[i];
			Sockets[i] = NULL;
		}
		delete Buffers[i];
		Buffers[i] = NULL;
	}
}

int CGateConnector::BuildList()
{
	FD_ZERO(&SocksSet);
	HighSock = 0;
	int c = 0;
	for (unsigned int i = 0; i < DEF_MAXGATESOCKET; i++)
		if (Sockets[i] != NULL)
		{
			FD_SET((unsigned int)Sockets[i]->socket, &SocksSet);
			c++;
			if (Sockets[i]->socket > HighSock)
				HighSock = Sockets[i]->socket;
		}
	return c;
}

bool CGateConnector::Connect()
{
	int iRet = 0;
	for (int i = 0; i < DEF_MAXGATESOCKET; i++)
	{
		Sockets[i] = new NetSock;
		if (Sockets[i]->Connect(GameServer::getInstance().GateServerAddr.c_str(), GameServer::getInstance().GateServerPort))
		{
			GameServer::getInstance().PutLog("(*) Connection-" + toString<int> (i) + " established!");
			iRet += 1;
			OnConnected(i);
		}
		else
		{
			GameServer::getInstance().PutLog("(!) Failed on connection-" + toString<int> (i));
			delete Sockets[i];
			Sockets[i] = NULL;
		}
	}
	return iRet == DEF_MAXGATESOCKET;
}

void CGateConnector::OnConnected(int iSockIndex)
{
	if (iSockIndex > 0)
		return;
	GameServer::getInstance().PutLog("(!) Try to register game server(" + GameServer::getInstance().ServerName + ")");
	Packet p(MSGID_REQUEST_REGISTERGAMESERVER, DEF_MSGTYPE_CONFIRM);
	p.push<char> (GameServer::getInstance().ServerName.c_str(), 10);
	p.push<char> (GameServer::getInstance().GameServerAddr.c_str(), 16);
	p.push<unsigned short> (GameServer::getInstance().GameServerPort);
	p.push<bool> (false); //Do I have configs?
	int iTotalMaps = GameServer::getInstance().MapList.size();
	p.push<unsigned char> (iTotalMaps);
	p.push<unsigned short> (getpid()); //Server ID
	for (int i = 0; i < iTotalMaps; i++)
		p.push<char> (GameServer::getInstance().MapList[i].m_sMapName.c_str(), 11);
	p.send(Sockets[iSockIndex]);
}

void CGateConnector::Run()
{
	IsConnected = false;

	if (!Connect())
	{
		GameServer::getInstance().PutLog("(!!!) Could not connect to gate server.");
		return;
	}

	while (true)
	{
		Timeout.tv_sec = 1;
		Timeout.tv_usec = 0;

		if (BuildList() == 0)
		{
			GameServer::getInstance().PutLog("(!!!) Lost connection to Login Server!");
			IsConnected = false;
			break;
		}
		ReadSocks = select(HighSock + 1, &SocksSet, (fd_set*) 0, (fd_set*) 0, &Timeout);
		if (ReadSocks == -1)
		{
			int error_no = errno;
			GameServer::getInstance().PutLog("(!!!) Critical error! select() error: #" + toString<int> (error_no) + " (" + strerror(error_no) + ")");
			break;
		}
		else
		{

			for (int i = 0; i < DEF_MAXGATESOCKET; i++)
			{
				if ((Sockets[i] != NULL) && (FD_ISSET(Sockets[i]->socket, &SocksSet)))
				{
					OnDataAvailable(i);
				}
			}
		}
	}
}
void CGateConnector::RegisterSockets()
{
	Packet p(MSGID_REQUEST_REGISTERGAMESERVERSOCKET, GSID);
	for (int i = 1; i < DEF_MAXGATESOCKET; i++)
	{
		GameServer::getInstance().PutLog("(!) Try to register game server socket(" + toString<int> (i) + ") on ID[" + toString<int> (GSID) + "]");
		Sockets[i]->Write((unsigned char*) p.data(), p.size());
	}
	IsConnected = true;
}
void CGateConnector::__Reader(int iSockIndex)
{
	unsigned int dwMsgID = Buffers[iSockIndex]->next<int> ();
	unsigned short wMsgType = Buffers[iSockIndex]->next<unsigned short> ();
	switch (dwMsgID)
	{
		case MSGID_RESPONSE_REGISTERGAMESERVER:
			switch (wMsgType)
			{
				case DEF_MSGTYPE_CONFIRM:
					GSID = Buffers[iSockIndex]->next<unsigned short> ();
					GameServer::getInstance().PutLog("(!) Game Server registration to Log Server - Success! GSID[" + toString<int> (GSID) + "]");
					RegisterSockets();
					break;
				case DEF_MSGTYPE_REJECT:
					GameServer::getInstance().PutLog("(!) Game Server registration to Log Server - Fail!");
					break;
			}
			break;
		case MSGID_ITEMCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) ITEM configuration contents received. Now decoding...");
			int iItemCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iItemCount; i++)
			{
				// Get CItem from buffer
				CItem _item = Buffers[iSockIndex]->next<CItem> ();
				// Insert item into m_pItemConfig list
				GameServer::getInstance().ItemConfig.insert(pair<int, CItem> (_item.m_sIDnum, _item));
			}
			GameServer::getInstance().PutLog("(!) ITEM(Total:" + toString<int> (iItemCount) + " configuration - success!");
			break;
		case MSGID_NPCCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) NPC configuration contents received. Now decoding...");
			int iNpcCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iNpcCount; i++)
			{
				CNpc _npc = Buffers[iSockIndex]->next<CNpc> ();
				GameServer::getInstance().NpcConfig.push_back(_npc);
			}
			GameServer::getInstance().PutLog("(!) NPC(Total:" + toString<int> (iNpcCount) + ") configuration - success!");
			break;
		case MSGID_MAGICCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) MAGIC configuration contents received. Now decoding...");
			int iMagicCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iMagicCount; i++)
			{
				CMagic _magic = Buffers[iSockIndex]->next<CMagic> ();
				GameServer::getInstance().MagicConfig.insert(pair<int, CMagic> (_magic.m_iNum, _magic));
			}
			GameServer::getInstance().PutLog("(!) MAGIC(Total:" + toString<int> (iMagicCount) + ") configuration - success!");
			break;
		case MSGID_SKILLCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) SKILL configuration contents received. Now decoding...");
			int iSkillCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iSkillCount; i++)
			{
				CSkill _skill = Buffers[iSockIndex]->next<CSkill> ();
				GameServer::getInstance().SkillConfig.insert(pair<int, CSkill> (_skill.m_iSkillID, _skill));
			}
			GameServer::getInstance().PutLog("(!) SKILL(Total:" + toString<int> (iSkillCount) + ") configuration - success!");
			break;
		case MSGID_BUILDITEMCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) BUILDITEM configuration contents received. Now decoding...");
			int iBuildItemCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iBuildItemCount; i++)
				GameServer::getInstance().BuildItemConfig.push_back(Buffers[iSockIndex]->next<CBuildItem> ());
			GameServer::getInstance().PutLog("(!) BUILDITEM(Total:" + toString<int> (iBuildItemCount) + ") configuration - success!");
			break;
		case MSGID_PORTIONCONFIGURATIONCONTENTS: //silly koreans...
			GameServer::getInstance().PutLog("(!) PORTION configuration contents received. Now decoding..."); //but lets stick to the original
			int iPortionCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iPortionCount; i++)
				GameServer::getInstance().PotionConfig.push_back(Buffers[iSockIndex]->next<CPotion> ());
			GameServer::getInstance().PutLog("(!) PORTION(Total:" + toString<int> (iPortionCount) + ") configuration - success!");
			break;
		case MSGID_QUESTCONFIGURATIONCONTENTS:
			GameServer::getInstance().PutLog("(!) QUEST configuration contents received. Now decoding...");
			int iQuestCount = Buffers[iSockIndex]->next<int> ();
			for (int i = 0; i < iQuestCount; i++)
				GameServer::getInstance().QuestConfig.push_back(Buffers[iSockIndex]->next<CQuest> ());
			GameServer::getInstance().PutLog("(!) QUEST(Total:" + toString<int> (iQuestCount) + ") configuration - success!");
			break;
	}
}

void CGateConnector::OnDisconnected(int iSockIndex)
{
	//Reconnecting
	GameServer::getInstance().PutLog("(!!!) Lost connection to login server on socket-" + toString<int> (iSockIndex) + ".");
}

void CGateConnector::OnDataAvailable(int iSockIdx)
{

	if (!Buffers[iSockIdx]->receive(Sockets[iSockIdx]))
	{
		OnDisconnected(iSockIdx);
		delete Sockets[iSockIdx];
		Sockets[iSockIdx] = NULL;
		return;
	}

	unsigned short packetSize;

	while (true)
	{
		memcpy(&packetSize, Buffers[iSockIdx]->data() + 1, 2);
		if (packetSize <= Buffers[iSockIdx]->size())
		{
			int _before = Buffers[iSockIdx]->pos();
			unsigned char cKey = Buffers[iSockIdx]->next<unsigned char> ();
			unsigned short dwSize = Buffers[iSockIdx]->next<unsigned short> ();

			if (cKey > 0)
			{
				char * buf = Buffers[iSockIdx]->data();
				for (int i = 0; i < dwSize - 3; i++)
				{
					buf[i] ^= (cKey ^ (dwSize - i - 3));
					buf[i] -= i ^ cKey;
				}
			}

			__Reader(iSockIdx);
			int _readcount = _before - Buffers[iSockIdx]->pos();
			Buffers[iSockIdx]->seek(dwSize - _readcount);
		}
		else
			break;
	}
}

NetSock* CGateConnector::GetSock()
{
	int idx = CurrentSocket;
	CurrentSocket = (CurrentSocket + 1) % DEF_MAXGATESOCKET;
	return Sockets[idx];
}
