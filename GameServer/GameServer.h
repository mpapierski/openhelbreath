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
		int m_iAliveCount;
		GameServer() {
			m_pGateConnector = NULL;
			m_iAliveCount = 0;
		}
		~GameServer()
		{
			if (m_pGateConnector != NULL)
				delete m_pGateConnector;
		}

		GameServer(const GameServer &);
		GameServer& operator=(const GameServer&);
	public:
		static GameServer& getInstance()
		{
			static GameServer instance;
			return instance;
		}

		CGateConnector * m_pGateConnector;	
		string m_sServerName; // server name, it is sent to gate server
		string m_sGameServerAddr; // bind address list
		int m_iGameServerPort; // bind address port (ports?)
		string m_sGateServerAddr; // login server address
		int m_iGateServerPort; // gate server port

		vector<CMap> m_pMapList;
		map<int, CItem> m_pItemConfig;
		vector<CNpc> m_pNpcConfig;
		map<int, CMagic> m_pMagicConfig;
		map<int, CSkill> m_pSkillConfig;
		vector<CBuildItem> m_pBuildItemConfig;
		vector<CPotion> m_pPotionConfig;
		vector<CQuest> m_pQuestConfig;

		bool bInitialize();

		bool bReadMainConfig();
		bool bRegisterMap(string sMapName);
		int iGetMapIndex(string sMapName);
		void Execute();
		void TimerLoop();
		void PutLog(string sMessage, int iLogType = LOGTYPE_LOCAL);
};
#endif
