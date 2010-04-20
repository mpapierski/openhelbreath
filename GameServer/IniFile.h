/*
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
 */

#ifndef INIFILE_H_
#define INIFILE_H_
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef vector<string> v_string;
typedef map<string, string> v_section;

class CIniFile
{
	public:
		v_string Lines;
		string IniFileName;
		CIniFile(string sFileName);
		virtual ~CIniFile();
		bool LoadIni();
		string sGetValue(string sSectionName, string sKeyName, string sDefaultValue);
		int iGetValue(string sSectionName, string sKeyName, int iDefaultValue);
		bool bGetValue(string sSectionName, string sKeyName, bool bDefaultValue);
		v_string GetValuesByName(string sSectionName, string sKeyName);
};

#endif /*INIFILE_H_*/
