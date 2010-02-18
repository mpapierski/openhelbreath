#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
using namespace std;

struct CTile {
	bool m_bIsMoveAllowed;
	bool m_bIsTeleport;
	bool m_bIsWater;
	bool m_bIsFarm;
	bool m_bIsTempMoveAllowed;
	int m_iAttribute;
};

class CMap
{
private:
	string m_sFileName;
public:
	int m_iSizeX, m_iSizeY;
	int m_iTileDataSize;
	string m_sMapName;
	//vector< vector<CTile> > m_pTile;
	vector< vector<CTile> > m_pTile;
 	CMap(string sMapName);
	virtual ~CMap();
	bool bReadMapFile();
};

#endif
