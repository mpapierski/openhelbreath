#ifndef GAMESERVER_H_
#define GAMESERVER_H_
#include <string>
#include <vector>

#include "Map.h"

using namespace std;

class CGameServer
{
private:
	string m_sConfigFile; // stores main configuration file (default gserver.cfg, could be changed by command line)
	string m_sServerName; // server name, it is sent to gate server
	vector<string> m_sGameServerAddr; // bind address list
	int m_iGameServerPort; // bind address port (ports?)
	string m_sLogServerAddr; // login server address
	int m_iGateServerPort; // gate server port
	
public:
	CGameServer(string cConfigFile);
	virtual ~CGameServer();
	bool bInit();
	bool bReadProgramConfigFile(string sFileName);
	bool _bRegisterMap(string sMapName);
	
	vector<CMap> m_pMapList;
	CMap & pGetMapByName(string sMapName);
};

#endif /*GAMESERVER_H_*/
