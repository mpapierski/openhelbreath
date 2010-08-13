#include "Map.h"

Map::Map(const std::string& mapName) throw (BadMapFormat)
{
	FILE* fin;

	std::string fileName = "MAPDATA/" + mapName + ".amd";

	fin = fopen(fileName.c_str(), "r");
	if (fin == NULL)
	{
		fileName = "MAPDATA/" + mapName + ".AMD";
		fin = fopen(fileName.c_str(), "r");
		if (fin == NULL)
		{
			throw BadMapFormat();
		}
	}
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
					m_iSizeX = static_cast<int>(std::strtol(token, NULL, 10));
					cReadMode = 0;
					break;
				case 2:
					m_iSizeY = static_cast<int>(std::strtol(token, NULL, 10));
					cReadMode = 0;
					break;
				case 3:
					m_iTileDataSize = static_cast<int>(std::strtol(token, NULL, 10));
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

	if (m_iSizeX == -1 || m_iSizeY == -1 || m_iTileDataSize == -1)
		throw BadMapFormat();

	m_Tiles = std::vector< std::vector<Tile> > (m_iSizeX, std::vector<Tile> (m_iSizeY, Tile()));
	for (int iy = 0; iy < m_iSizeY; iy++)
		for (int ix = 0; ix < m_iSizeX; ix++)
		{
			fread(cTemp, 1, m_iTileDataSize, fin);

			memcpy(&m_Tiles[ix][iy].TileSprite, cTemp, 2);
			memcpy(&m_Tiles[ix][iy].TileSpriteFrame, cTemp + 2, 2);
			memcpy(&m_Tiles[ix][iy].ObjectSprite, cTemp + 4, 2);
			memcpy(&m_Tiles[ix][iy].ObjectSpriteFrame, cTemp + 6, 2);

			m_Tiles[ix][iy].IsMoveAllowed = (cTemp[8] & 0x80) != 0;
			m_Tiles[ix][iy].IsTeleport = (cTemp[8] & 0x40) != 0;
			m_Tiles[ix][iy].IsFarm = (cTemp[8] & 0x20) != 0;
			m_Tiles[ix][iy].IsWater = (m_Tiles[ix][iy].TileSprite == 19);
		}
	fclose(fin);
}

Map::~Map()
{

}

MapBank::MapBank()
{

}

MapBank::~MapBank()
{

}

bool MapBank::loadMap(const std::string& mapName)
{
	std::string lowerMapName(mapName);
	std::transform(lowerMapName.begin(), lowerMapName.end(), lowerMapName.begin(), ::tolower);

	try
	{
		Map mapData(mapName);
		Debug() << "Loading map: " << lowerMapName;
		m_Maps.insert(std::pair<std::string, Map>(lowerMapName, mapData));
		return true;
	}
	catch(BadMapFormat& e)
	{
		Debug() << "Error while loading map: " << e.what();
		return false;
	}
}
