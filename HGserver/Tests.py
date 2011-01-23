import unittest

from Helpers import *

class TestHelpers(unittest.TestCase):
	'''
		Testing some functions from Helpers.py
	'''
	
	def setUp(self):
		pass

	def test_stripzeros(self):
		# make sure the shuffled sequence does not lose any elements
		self.assertEqual(strip_zeros('test\x00\x00\x00\x00'), 'test')
		self.assertEqual(strip_zeros(69), 69)
		self.assertEqual(strip_zeros(69L), 69L)
		self.assertEqual(strip_zeros(u'test'), u'test')
		
	def test_array2d(self):
		w, h = 100, 100
		t = Array2d((w, h))
		self.assertRaises(IndexError, t.__setitem__, (-1, -1), 100)
		self.assertRaises(IndexError, t.__setitem__, (w, h), 100)
		t[w - 1, h - 1] = 100
		self.assertEqual(t[w - 1, h - 1], 100)
		t[w - 1, h - 1] += 1
		self.assertEqual(t[w - 1, h - 1], 101)

class TestStruct(unittest.TestCase):
	'''
		Testing Struct class
	'''
	
	def setUp(self):
		self.item_format = (
			('id', 'I'),
			('item_name', '25s'),
			('padding1', '5x'),
			('type1', 'L'), # 4/8
			('type1', 'I'), # 4
			('type1', 'H'), # 2
		)
		
		self.skill_format = (
			('percent', 'B'),
			('progress', 'L')
		)
		
		self.char_gen = lambda: Struct((
			('char_name', '10s'),
			('level', 'I'),
			('item_count', 'B'),
			('items', Struct(self.item_format), 'item_count'),
			('padding', '69x'),
			('skills', Struct(self.skill_format), 5),
			('profile', '100s'),
		))
		
		self.char = self.char_gen()
		
	def test_simple(self):
		header = Struct(
			(('key', 'B'),
			('size', 'H'),
			('msgid', 'I'),
			('msgtype', 'H')),
		)
		
		header.update(
			key = 38,
			size = 6,
			msgid = 31337,
			msgtype = 69			
		)
		
		self.assertRaises(AttributeError, header.update, padding = 1)
		
		serialized = header.pack()
		
		header.unpack(serialized)
		
		self.assertEqual(header.key, 38)
		self.assertEqual(header.size, 6)
		self.assertEqual(header.msgid, 31337)
		self.assertEqual(header.msgtype, 69)
		
	def test_simple(self):
		el = Struct(
			(('v1', '20s'),
			('i', 'I'))
		)
		
		header = Struct(
			(('key', 'B'),
			('size', 'H'),
			('padding1', '2x'),
			('count', 'L'),
			('padding2', '2x'),
			('array', el, 'count'),
			('padding3', '2x'),
			('msgid', 'I'),
			('msgtype', 'H')),
		)
		
		header.update(
			key = 1,
			size = 2,
			msgid = 3,
			msgtype = 4,
			count = 0,
			array = []			
		)
		
		serialized = header.pack()
		
		new_header = header.unpack(serialized)
		
		self.assertEqual(header.count, 0)
		self.assertEqual(header.key, 1)
		self.assertEqual(header.size, 2)
		self.assertEqual(header.msgid, 3)
		self.assertEqual(header.msgtype, 4)
		
		self.assertEqual(header.get_dict(), dict(
			key = 1,
			size = 2,
			msgid = 3,
			msgtype = 4,
			count = 0,
			array = []								
		))
		
	def test_complex(self):
		self.char.char_name = 'test'
		self.char.level = 69
		self.char.item_count = 4
		self.char.items = [
			[1, 'test xxx', 1234, 567, 89],
			[2, 'test yyy', 666, 777, 888],
			[3, 'test zzz', 31337, 31337, 31337],
			[4, '', 0, 1, 2]
		]
		self.char.skills = [
			[1, 101],
			[2, 102],
			[3, 103],
			[4, 104],
			[5, 105]
		]
		
		self.char.profile = 'openhelbreath'
		
		serialized = self.char.pack()
		
		char = self.char_gen()
		
		char = char.unpack(serialized)
		
		self.assertEqual(self.char.profile, char.profile)
		self.assertEqual(self.char.level, char.level)
		self.assertEqual(self.char.item_count, char.item_count)
		self.assertEqual(self.char.items, char.items)
		self.assertEqual(self.char.skills, char.skills)
		
		self.assertEqual(len(char.items), self.char.item_count)
		self.assertEqual(len(char.skills), 5)
		
if __name__ == '__main__':
	unittest.main()