#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Application.h"
#include "GameServer.h"
#include "GlobalDef.h"

CApplication::CApplication(int argc, char * argv[])
{
	m_sExecutable = argv[0];
	for (int i=1;i<argc;i++)
		m_vArg.push_back(string(argv[i]));
	
	m_sMainConfig = "gserver.cfg";
}

CApplication::~CApplication()
{
	if (m_pGameServer != NULL) {
		//m_pGameServer->Quit();
		delete m_pGameServer;
	}
}
bool CApplication::ParseCommandLine()
{
	int i;
	char pId = 0;
	bool bWas[255];
	bool bNext;
	
	for (i=0;i<(int)m_vArg.size();i++)
		bWas[i] = false;
		
	for (int i=0;i<(int)m_vArg.size();i++){
		if ( (m_vArg[i].length() == 2) && (m_vArg[i].substr(0, 1) == "-") ) {
			pId = m_vArg[i].substr(1,1).c_str()[0];
			bNext = (i+1 < (int)m_vArg.size());
			
			if (!bWas[(int)pId])
				bWas[(int)pId] = true;
			else
				continue;
				
			switch (pId) {
				case 'h':
					printf("openhelbreath v%d.%d (Server version: %d.%d %s)\n",
														DEF_LOWERVERSION,
														DEF_UPPERVERSION,
														DEF_HB_LOWERVERSION,
														DEF_HB_UPPERVERSION,
														RELEASE_NOTES);
					printf("by openhelbreath team\n");
					printf("http://code.google.com/p/openhelbreath/\n");
					printf("%s -h -v -c [config_name]\n", m_sExecutable.c_str());
					printf("-c [config_name]\n");
					printf(" forces server to load config_name, default is gserver.conf\n");
					printf("-h\n");
					printf(" display this help file\n");
					printf("-v\n");
					printf(" shows game server version\n");
					exit(0);
					return true;
					break; 
					
				case 'c':
					if (!bNext)
						continue;
					printf("* Config file set to : %s\n", m_vArg[i+1].c_str());
					m_sMainConfig = m_vArg[i+1];
					return true;
					break;
				case 'v':
					if (bWas[(int)'c'] == true)
						continue;
					printf("v%d.%d %s\n", 
									DEF_LOWERVERSION,
									DEF_UPPERVERSION,
									RELEASE_NOTES);
					exit(0);
					return true;
			}
		}
	}
	return false;
}

void CApplication::Run()
{
	if (!ParseCommandLine()) {
		printf("Main config file: %s\n", m_sMainConfig.c_str());
	}
	
	m_pGameServer = new CGameServer(m_sMainConfig);
	if (!m_pGameServer->bInit()) {
		printf("(!) STOPPED\n");
		return;
	}
	else
	{
		printf("(*) Game server initialization done.\n");
	}
	if (!m_pGameServer->bRegisterGameServer())
	{
		printf("(!) Game server registration error!\n");
		return;
	}
}
