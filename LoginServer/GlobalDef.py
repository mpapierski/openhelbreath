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
from Enum import Enum

DEF = Enum({ 
'MAXGAMESERVERS'      : 100,
'MAXSOCKETSPERSERVER' : 4,
'MAXSKILLS'           : 24,
'MAXITEMS'            : 50,
'MAXBANKITEMS'        : 120,
'MAXPARTYMEMBERS'     : 8,
'MAXPARTYNUMBER'      : 200
})

Account = Enum({
'NOTEXISTS' : 0,
'WRONGPASS' : 1,
'OK'        : 2,
'BLOCKED'   : 3,
'EXISTS'    : 4,
'FAIL'      : 5
})

Version = Enum({
'UPPER' : 3,
'LOWER' : 82
})
