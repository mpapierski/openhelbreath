#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <string>
#include <vector>
#include "GameServer.h"

using namespace std;

class CApplication
{
private:
	vector<string> m_vArg;
	string m_sMainConfig;
	string m_sExecutable;
	CGameServer * m_pGameServer;
public:
	CApplication(int argc, char * argv[]);
	virtual ~CApplication();
	bool ParseCommandLine();
	void Run();
};

#endif /*APPLICATION_H_*/
