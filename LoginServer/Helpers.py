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
class Callbacks(object):
	def __init__(self, fr):
		"""
			Initialize from fr, either dict or list [('asdf': func/lambda), ...] or tuple
			Usage:
			CB = Callbacks({'asdf': A,'zxcv': B})
			CB['A'] += [C]
			CB('A', 1,2,3)
			This calls (in order):
			* A(1,2,3)
			* C(1,2,3)
		"""
		if type(fr) == dict:
			self.__cb = fr
		elif type(fr) in [list, tuple]:
			self.__cb = dict(fr)
		for i,j in self.__cb.items():
			if type(j) != list:
				self.__cb[i] = [j]
				
	def __setitem__(self, k, v):
		self.__cb.__setitem__(k, v)
		
	def __getitem__(self, k):
		return self.__cb.__getitem__(k)

	def __contains__(self, k):
		return k in self.__cb
		
	def __call__(self, vname, *arg):
		"""
			Calling callback chain
		"""
		assert vname in self.__cb, 'Method %s not found !' % vname
		for i in self.__cb[vname]:
			i(*arg)
	def items(self):
		return self.__cb.items()
