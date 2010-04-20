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

#ifndef GAMESERVER_H
#define GAMESERVER_H
#include <time.h>

#include "GateSocket.h"
#include "Threading.h"
#include "IniFile.h"
#include "Map.h"
#include "GlobalDef.h"
#include "Misc.h"
#include "Item.h"
#include "Npc.h"
#include "Magic.h"
#include "Skill.h"
#include "BuildItem.h"
#include "Potion.h"
#include "Quest.h"

class GameServer
{
	private:
		int AliveCount;
		int DeadCount;

		GameServer() :
			AliveCount(0), DeadCount(0), GateConnector(0)
		{

		}
		~GameServer()
		{
			if (GateConnector != 0)
				delete GateConnector;
		}

		GameServer(const GameServer &);
		GameServer& operator=(const GameServer&);
	public:
		static GameServer& getInstance()
		{
			static GameServer instance;
			return instance;
		}

		CGateConnector * GateConnector;
		string ServerName; // server name, it is sent to gate server
		string GameServerAddr; // bind address list
		int GameServerPort; // bind address port (ports?)
		string GateServerAddr; // login server address
		int GateServerPort; // gate server port

		vector<CMap> MapList;
		map<int, CItem> ItemConfig;
		vector<CNpc> NpcConfig;
		map<int, CMagic> MagicConfig;
		map<int, CSkill> SkillConfig;
		vector<CBuildItem> BuildItemConfig;
		vector<CPotion> PotionConfig;
		vector<CQuest> QuestConfig;

		bool Initialize();

		bool ReadMainConfig();
		bool RegisterMap(string sMapName);
		int GetMapIndex(string sMapName);
		void Execute();
		void TimerLoop();
		void PutLog(string sMessage, int iLogType = LOGTYPE_LOCAL);
};
#endif
