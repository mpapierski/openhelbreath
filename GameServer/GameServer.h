#ifndef GAMESERVER_H_
#define GAMESERVER_H_
#include <string>
#include <vector>
#include <stdio.h>
#include "GlobalDef.h"
#include "Map.h"
#include "Socket.h"

//#include "Callback.h"

using namespace std;

class CGameServer : public SocketCallbacks
{
private:
	string m_sConfigFile; // stores main configuration file (default gserver.cfg, could be changed by command line)
	string m_sServerName; // server name, it is sent to gate server
	vector<string> m_sGameServerAddr; // bind address list
	int m_iGameServerPort; // bind address port (ports?)
	string m_sLogServerAddr; // login server address
	int m_iGateServerPort; // gate server port
	TcpClient * m_pSubLogSocket[DEF_MAXSUBLOGSOCK]; //array of gate server sockets
	
 //current sub log socket which is trying to register
public:
	int m_iSubLogSockIndex;
	CGameServer(string cConfigFile);
	virtual ~CGameServer();
	bool bInit();
	bool bReadProgramConfigFile(string sFileName);
	bool _bRegisterMap(string sMapName);
	
	vector<CMap> m_pMapList;

	int iGetMapIndex(string sMapName);
	
	bool bRegisterGameServer();
	void SubLogSockInit(int iIndex);
	
	void Wait();

	void Connected(void*);
	void Disconnected(void*);
	void Received(void*, char*) {};
	
	
};

#endif /*GAMESERVER_H_*/
