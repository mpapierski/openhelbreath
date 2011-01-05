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

import warnings
from threading import Thread
warnings.filterwarnings("ignore")

import sys
from LoginServer import CLoginServer

Server = None

def CLIThread():
	global Server
	while Server:
		cmd = raw_input()
		if not cmd:
			continue
		if cmd.upper() == 'exit':
			break
		Server.CommandHandler(cmd)

def main():
	print "OpenHelbreath Login Server experimental" # Last stable revision
	print "Copyright (C) 2009-2011 by openhelbreath team"
	print "This program comes with ABSOLUTELY NO WARRANTY."
	print "This is free software, and you are welcome to redistribute it under certain conditions."
	print
	
	global Server	
	Server = CLoginServer()
	
	if not Server.DoInitialSetup():
		print "(!) Stopped!"
		del Server
		return False
	
	if not Server.InitServer():
		del Server
		return False
	
	clithread = Thread(target = CLIThread)
	clithread.start()
	
	while Server:
		try:
			Server.MainLoop()
		except KeyboardInterrupt as e:
			del Server
			Server = None
	
if __name__ == '__main__':
	main()
