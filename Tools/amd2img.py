""" 
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
"""

from hb_pak import HBPak
import re, struct, sys, os
from PIL import Image, ImageDraw, ImageMath
from optparse import OptionParser

TileCfg = [("maptiles1", 0, 32, True),	#Reversed from HelGame 4.10 (HBUsa)
			("structures1", 50, 15, False),
			("Sinside1", 70, 27, False),
			("Trees1", 100, 46, True),
			("TreeShadows", 150, 46, True),
			("objects1", 200, 10, True),
			("objects2", 211, 5, True),
			("objects3", 216, 4, True),
			("objects4", 220, 2, True),
			("Tile223-225", 223, 3, True),
			("Tile226-229", 226, 4, True),
			("objects5", 230, 9, True),
			("objects6", 238, 4, True),
			("objects7", 242, 7, True),
			("maptiles2", 300, 15, True),
			("maptiles4", 320, 10, True),
			("maptiles5", 330, 19, True),
			("maptiles6", 349, 4, True),
			("maptiles353-361", 353, 9, True),
			("Tile363-366", 363, 4, True),
			("Tile367-367", 367, 1, True),
			("Tile370-381", 370, 12, True),
			("Tile382-387", 382, 6, True),
			("Tile388-402", 388, 15, True),
			("Tile403-405", 403, 3, True),
			("Tile406-421", 406, 16, True),
			("Tile422-429", 422, 8, True),
			("Tile430-443", 430, 14, True),
			("Tile444-444", 444, 1, True),
			("Tile445-461", 445, 17, True),
			("Tile462-473", 462, 12, True),
			("Tile474-478", 474, 5, True),
			("Tile479-488", 479, 10, True),
			("Tile489-522", 489, 34, True),
			("Tile523-530", 523, 8, True),
			("Tile531-540", 531, 10, True),
			("Tile541-545", 541, 5, True)]

class Array2d():
	def __init__(self, (w, h)):
		self.a={}
		self.w = w
		self.h = h
		
	def __getitem__(self, v):
		assert isinstance(v, tuple)
		(x,y) = v
		return self.a[x][y]
		
	def __setitem__(self, key, v):
		assert isinstance(key, tuple)
		(x,y) = key
		if x not in self.a:
			self.a[x]={}
		self.a[x][y]=v
		

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
		return "(%d, %d) (%d, %d) (%d, %d)" % (self.TileSprite, self.TileSpriteFrame, self.ObjectSprite, self.ObjectSpriteFrame, self.Option & 0x80 != 0, self.Option & 0x40 != 0)

class HBMap(Array2d):
	def __init__(self, filename):
		f = open(filename, "r+b")
		header = f.read(256)
		r = re.compile("^MAPSIZEX =  (\d+) MAPSIZEY =  (\d+) TILESIZE = (\d+)")
		header, = r.findall(header)
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

def color2alpha(img, color):
	img = img.convert("RGBA")
	datas = img.getdata()
	newData = list()
	for item in datas:
		if item == color:
			newData.append((255, 255, 255, 0))
		else:
			newData.append(item)
	img.putdata(newData)
	return img
	
if __name__ == "__main__":
	print "OpenHelbreath amd2img v1.1"
	print "Copyright (C) 2010 by openhelbreath team"
	print "This program comes with ABSOLUTELY NO WARRANTY."
	print "This is free software, and you are welcome to redistribute it under certain conditions."
	print
	parser = OptionParser()
	parser.add_option("-a", "--amd", 
					dest = "mapname",
					help="Input map name",
					metavar="MAPNAME")
	parser.add_option("-p", "--path",
					dest="path",
					help="Path to Helbreath install directory",
					metavar="PATH",
					default="")
	parser.add_option("-o", "--output",
					dest = "output",
					help = "Image file name",
					metavar="OUTPUT")
	parser.add_option("-s", "--scale",
					dest ="scale",
					help = "Scale output",
					metavar="ASPECT",
					default="1")
	(options, args) = parser.parse_args()
	options.scale = float(options.scale)
	
	if not options.mapname or not options.path or \
			options.scale > 1 or options.scale < 0:
		parser.print_help()
		sys.exit(1)
		
	if not options.output:
		(file, ext) = os.path.splitext(options.mapname)
		options.output = file + ".png"
		
	mapname = options.mapname
	path = options.path
	print "Loading map file %s..." % mapname
	m = HBMap(path + "\\mapdata\\" + mapname)
	print "OK. %dx%dx%d" % (m.w, m.h, m.TILESIZE)
	need = set([])
	print "Generating necessary pak list..."
	for y in range(m.h):
		for x in range(m.w):
			tile = m[x,y]
			name = filter(lambda x: 
							(tile.TileSprite >= x[1] and tile.TileSprite <= x[1]+x[2]) or
							(tile.ObjectSprite >= x[1] and tile.ObjectSprite <= x[1]+x[2])
						, TileCfg)
			for n in name:
				need |= set([n])
	print "Need %d pak files." % len(need)
	Tiles = {}
	for (i, (name, start, count, alpha)) in enumerate(need):
		print " Loading %s..." % name
		pakpath = path + "\\sprites\\" + name + ".pak"
		pak = HBPak(pakpath)
		assert pak.load()
		for (i, spr) in enumerate(pak.sprites):
			Tiles[start+i] = spr
		print " Done... %d" % len(pak.sprites)
	print "Total tiles: %d" % len(Tiles)
	print "New image (%dx%d)" % (m.w << 5, m.h << 5)
	Output = Image.new("RGB", (m.w << 5, m.h << 5))
	print "Rendering background..."
	for y in range(m.h):
		for x in range(m.w):
			tile = m[x,y]
			(spr, sprf, obj, objf) = (tile.TileSprite, tile.TileSpriteFrame, tile.ObjectSprite, tile.ObjectSpriteFrame)
			if spr in Tiles.keys():
				fr = Tiles[spr].frames[sprf]
				img = Tiles[spr].image.crop((fr.X, fr.Y, fr.X + min(fr.W, 640), fr.Y + min(fr.H, 480)))
				Output.paste(img, (x << 5, y << 5))
	print "Rendering objects..."
	objects = 0
	for y in range(m.h):
		for x in range(m.w):
			tile = m[x,y]
			(spr, sprf, obj, objf) = (tile.TileSprite, tile.TileSpriteFrame, tile.ObjectSprite, tile.ObjectSpriteFrame)
			if obj <= 0:
				continue
			if obj not in Tiles.keys():
				print "Object (%d) not found" % obj
				continue
			try:
				fr = Tiles[obj].frames[objf]
			except:
				print "Object (%d) frame (%d) not found" % (obj, objf)
				continue
			img = Tiles[obj].image.crop((fr.X, fr.Y, fr.X + fr.W, fr.Y +fr.H))
			img = color2alpha(img, Tiles[obj].image.getpixel((0,0)))
			Output.paste(img, ((x << 5) + fr.FX, (y << 5) + fr.FY), img)
			if img.size[0] > 32 or img.size[1] > 32:
				objects+=1
	print "Done (objects=%d)." % objects
	if options.scale != 1:
		print "Rescale by %.2f..." % (options.scale)
		Output.thumbnail(map(lambda v: int(v * options.scale), Output.size), Image.ANTIALIAS)
		print "... %dx%d" % Output.size
	print "Saving..."
	file, ext = os.path.splitext(mapname)
	Output.save(options.output)
	print "Saved to %s." % (options.output)
