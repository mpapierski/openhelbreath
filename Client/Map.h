#ifndef MAP_H
#define MAP_H

#include <string>
#include <exception>
#include <vector>
#include <map>
#include <algorithm>

#include "Logger.h"

class BadMapFormat: public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Bad map file format.";
		}
};

typedef struct
{
		short TileSprite;
		short TileSpriteFrame;
		short ObjectSprite;
		short ObjectSpriteFrame;

		bool IsMoveAllowed;
		bool IsTeleport;
		bool IsWater;
		bool IsFarm;
		bool IsTempMoveAllowed;
		int Attribute;
} Tile;

class Map
{
	private:
		std::vector< std::vector<Tile> > m_Tiles;
		int m_iSizeX, m_iSizeY;
		int m_iTileDataSize;
	public:
		Map(const std::string& fileName) throw(BadMapFormat);
		virtual ~Map();
		inline const Tile & getTileAt(int X, int Y) const
		{
			return m_Tiles[X][Y];
		}
		inline int getSizeX() const
		{
			return m_iSizeX;
		}
		inline int getSizeY() const
		{
			return m_iSizeY;
		}
};

class MapBank
{
	private:
		std::map<std::string, Map> m_Maps;
	public:

		MapBank();
		virtual ~MapBank();
		bool loadMap(const std::string& mapName);

		inline std::map<std::string, Map> getMaps() const
		{
			return m_Maps;
		}
		inline Map & getMap(std::string mapName)
		{
			return m_Maps.find(mapName)->second;
		}
};
#endif
