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

#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
using namespace std;

struct CTile
{
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
		vector<vector<CTile> > m_pTile;
		CMap(string sMapName);
		virtual ~CMap();
		bool bReadMapFile();
};

#endif
