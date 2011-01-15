import struct, re
from Helpers import Array2d

class Tile(object):
	def __init__(self, TS, TSF, OS, OSF, OPT):
		self.TileSprite = TS
		self.TileSpriteFrame = TSF
		self.ObjectSprite = OS
		self.ObjectSpriteFrame = OSF
		self.MoveAllowed = OPT & 0x80 != 0
		self.Teleport = OPT & 0x40 != 0
		self.Farming = OPT & 0x20 != 0
		self.Option = OPT
		
	def __str__(self):
		return "(%d, %d) (%d, %d) (%d, %d)" % (
			self.TileSprite,
			self.TileSpriteFrame,
			self.ObjectSprite,
			self.ObjectSpriteFrame,
			self.Option & 0x80 != 0,
			self.Option & 0x40 != 0
		)
		
class HBMap(Array2d):
	def __init__(self, filename):
		f = open(filename, "r+b")
		header = f.read(256)
		header, = re.findall("^MAPSIZEX =  (\d+) MAPSIZEY =  (\d+) TILESIZE = (\d+)", header)
		assert header != []
		(self.MAPSIZEX, self.MAPSIZEY, self.TILESIZE) = map(int, header)
		cpMapData = f.read(self.MAPSIZEX * self.MAPSIZEY * 10)
		Array2d.__init__(self, (self.MAPSIZEX, self.MAPSIZEY))
		pos = 0
		for y in range(self.MAPSIZEY):
			for x in range(self.MAPSIZEX):
				T = Tile(*struct.unpack('<hhhhh', cpMapData[pos:pos+10]))
				self[x,y] = T
				pos += 10	