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
import os, struct, mmap, StringIO
from PIL import Image, ImageDraw
from collections import namedtuple

exists = lambda fn : os.path.exists(fn) and os.path.isfile(fn)

DEF_PAKSIG = "<Pak file header>"
DEF_SPRSIG = "<Sprite File Header>"

class Frame:
	def __init__(self, *args):
		(self.X, self.Y, self.W, self.H, self.FX, self.FY) = args[0]

class Sprite:
	def __init__(self):
		self.frames = []
		self.image = None
		
	def add_frame(self, fr):
		self.frames += [Frame(fr)]
	
class HBPak(object):
	"""
		Usage:
		pak = HBPak("C:\Program Files\Helbreath USA\Sprites\Wyvern.pak")
		pak.load()
	"""
	def __init__(self, filename):
		assert exists(filename)		
		self.PakFileName = filename
		
	def load(self):
		f = open(self.PakFileName, "r+b")
		fs = mmap.mmap(f.fileno(), 0)
		try:
			CheckChar = fs[:len(DEF_PAKSIG)]
			if CheckChar != DEF_PAKSIG:
				return False
			fs.seek(20)
			SprOffsets = []
			(c1, ) = struct.unpack('<I', fs.read(4)) #SprCount
			self.sprites = []
			for i in range(c1):
				(off, size) = struct.unpack('<II', fs.read(8))
				SprOffsets += [(off, size)]
			for i in range(len(SprOffsets)):
				(offset, size) = SprOffsets[i]
				fs.seek(offset, 0)
				head = fs.read(100)
				assert head[:len(DEF_SPRSIG)] == DEF_SPRSIG
				(c2, ) = struct.unpack('<I', fs.read(4))
				Spr = Sprite()
				for j in range(c2):
					Spr.add_frame(struct.unpack('<6h', fs.read(12)))
				fs.seek(4, os.SEEK_CUR) #4 padding zeros
				# Obviously PIL tries to reset file stream so Image.open(fs) does not load image
				# so we need to trick it, calculate image size, copy it from fs to StringIO and pass it to Image.open
				# Happily this "hack" does not affect speed too much
				data = StringIO.StringIO(fs.read(size))
				Spr.image = Image.open(data).convert("RGBA")
				self.sprites += [Spr]
		finally:
			fs.close()
			f.close()
						
		return True
