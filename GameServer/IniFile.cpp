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

#include "IniFile.h"

CIniFile::CIniFile(string sFileName)
{
	IniFileName = sFileName;
}

CIniFile::~CIniFile()
{

}

void triml(string & str)
{
	while ((str.length() > 0) && (str[0] <= 32))
		str.erase(str.begin());
}
void trimr(string & str)
{
	while ((str.length() > 0) && ((str[str.length() - 1]) <= 32))
		str.erase(str.length() - 1, 1);
}

string trim(string str)
{
	string newstr(str);
	triml(str);
	trimr(str);
	return str;
}
bool CIniFile::LoadIni()
{
	FILE *fin;

	string line = "";
	fin = fopen(IniFileName.c_str(), "r");

	if (fin == NULL)
		return false;

	while (!feof(fin))
	{
		char c = fgetc(fin);
		if ((c == '\n') && (line != ""))
		{
			Lines.push_back(line);
			line = "";
		}
		else
		{
			if (c >= 32)
				line.push_back(c);
		}
	}
	if (line != "")
		Lines.push_back(line);
	fclose(fin);
	return true;
}

bool is_number(string & str)
{
	if (str.length() == 0)
		return false;

	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

int CIniFile::iGetValue(string sSectionName, string sKeyName, int iDefaultValue)
{
	string sVal = sGetValue(sSectionName, sKeyName, "");
	return is_number(sVal) ? atoi(sVal.c_str()) : iDefaultValue;
}

string CIniFile::sGetValue(string sSectionName, string sKeyName, string sDefaultValue)
{
	v_string vals = GetValuesByName(sSectionName, sKeyName);
	return vals.size() > 0 ? vals[0] : sDefaultValue;
}

v_string CIniFile::GetValuesByName(string sSectionName, string sKeyName)
{
	string sKey = "";
	string sVal = "";
	size_t index;
	v_string values;

	for (unsigned i = 0; i < Lines.size(); ++i)
		if (Lines[i] == string("[" + sSectionName + "]"))
		{
			for (unsigned j = i + 1; j < Lines.size(); j++)
			{
				index = Lines[j].find('=');
				if (index != string::npos)
				{
					sKey = trim(Lines[j].substr(0, index));
					if (sKey == sKeyName)
					{
						sVal = trim(Lines[j].substr(index + 1, Lines[j].length() - index));
						values.push_back(sVal);
					}
				}
				if ((Lines[j].find('[') == 0) && (Lines[j].find(']') == Lines[j].length() - 1))
					break;
			}
			break;
		}
	return values;
}
