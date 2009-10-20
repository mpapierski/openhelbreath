import re, time
from threading import Thread

class TimerManager(Thread):
	"""
		Usage:
		tm = TimerManager()
		tm.register_timer(lambda: sys.stdout.write("tactical facepalm"), 'tactical', 0.1, True)
		
		register_timer(proc_addr, 'timer_name', interval, autostart)
		1.0 = 1s
		0.5 = 0.5s
		etc
	"""	
	def __init__(self):
		Thread.__init__(self)
		self.timer_list = []

	def register_timer(self, proc, name, tick_time, auto_start = False):
		self.timer_list += [{'Name': name, 'Time': tick_time, 'Active': auto_start, 'Addr': proc, 'Tick': time.time()}]
		if len(self.timer_list)>0 and not self.isAlive():
			self.start()

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
		while self.running:
			start = time.time()
			for i in self.timer_list:
				if i['Active'] and start - i['Tick']  > i['Time']:
					ret = i['Addr']()
					i['Tick'] = start
					if ret == False:
						self.timer_list.remove(i)
