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
import re, time
from threading import Thread

class TimerManager(object):
	"""
		Usage:
		tm = TimerManager()
		tm.register_timer(lambda: sys.stdout.write("tactical facepalm"), 'tactical', 0.1, True)
		
		register_timer(proc_addr, 'timer_name', interval, autostart)
		1.0 = 1s
		0.5 = 0.5s
		minimum interval = 0.1s
		etc
	"""	
	def __init__(self):
		self.timer_list = []

	def register_timer(self, proc, name, tick_time, auto_start = False):
		self.timer_list += [{'Name': name, 'Time': tick_time, 'Active': auto_start, 'Addr': proc, 'Tick': time.time()}]

	def timers(self, proc_name): #Accepting wildcars
		return filter(lambda x: True if re.match(proc_name, x['Name']) else False, self.timer_list)

	def enable(self, proc_name):
		for i in self.timers(proc_name):
			i['Tick'] = time.time()
			i['Active'] = True
			
	def disable(self, proc_name):
		for i in self.timers(proc_name):
			i['Active'] = False
	
	def run(self):
		self.running = True
		start = time.time()
		for i in self.timer_list:
			if i['Active'] and start - i['Tick']  > i['Time']:
				ret = i['Addr']()
				i['Tick'] = start
				if ret == False:
					self.timer_list.remove(i)