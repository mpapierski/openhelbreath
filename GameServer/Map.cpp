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
#include <string.h>

#include "Map.h"
CMap::CMap(string sMapName)
{
	m_sFileName = "MAPDATA//" + sMapName + ".amd";
	m_sMapName = sMapName;
}

CMap::~CMap()
{
}

bool CMap::bReadMapFile()
{
	FILE *fin;
	fin = fopen(m_sFileName.c_str(), "r");
	if (fin == NULL)
		return false;
	char cHeader[256];
	char * token;
	char seps[] = "= \t\n";
	char cReadMode = 0;
	char cTemp[100];
	fread(cHeader, 1, 256, fin);
	token = strtok(cHeader, seps);
	m_iSizeX = m_iSizeY = m_iTileDataSize = -1;
	while (token != NULL)
	{

		if (cReadMode != 0)
		{
			switch (cReadMode)
			{
				case 1:
					m_iSizeX = atoi(token);
					cReadMode = 0;
					break;
				case 2:
					m_iSizeY = atoi(token);
					cReadMode = 0;
					break;
				case 3:
					m_iTileDataSize = atoi(token);
					cReadMode = 0;
					break;
			}
		}
		else
		{
			if (strcmp(token, "MAPSIZEX") == 0)
				cReadMode = 1;
			if (strcmp(token, "MAPSIZEY") == 0)
				cReadMode = 2;
			if (strcmp(token, "TILESIZE") == 0)
				cReadMode = 3;

		}
		token = strtok(NULL, seps);
	}
	m_pTile = vector<vector<CTile> > (m_iSizeX, vector<CTile> (m_iSizeY, CTile()));
	for (int iy = 0; iy < m_iSizeY; iy++)
		for (int ix = 0; ix < m_iSizeX; ix++)
		{
			fread(cTemp, 1, m_iTileDataSize, fin);
			m_pTile[ix][iy].m_bIsMoveAllowed = (cTemp[8] & 0x80) != 0;
			m_pTile[ix][iy].m_bIsTeleport = (cTemp[8] & 0x40) != 0;
			m_pTile[ix][iy].m_bIsFarm = (cTemp[8] & 0x20) != 0;
			short * sp = (short *) &cTemp[0];
			m_pTile[ix][iy].m_bIsWater = *sp == 19;
		}
	fclose(fin);
	return true;
}
