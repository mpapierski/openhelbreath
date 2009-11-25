#include "IniFile.h"

CIniFile::CIniFile(string sFileName)
{
	m_sIniFileName = sFileName;
}

CIniFile::~CIniFile()
{
	
}

void triml(string & str) {
	while ( (str.length()>0) && (str[0] <= 32) )
			str.erase(str.begin());
}
void trimr(string & str) {
	while ( (str.length()>0) && ((str[str.length()-1]) <= 32) )
			str.erase(str.length()-1, 1);
}

string trim(string str) {
	string newstr(str);
	triml(str);
	trimr(str);
	return str;
}
bool CIniFile::bLoadIni()
{
	FILE *fin;

	string line = "";
	fin = fopen(m_sIniFileName.c_str(), "r");
	
	if (fin == NULL)
		return false;
		
	while (!feof(fin)) {
		char c = fgetc(fin);
		if ( (c == '\n') && (line != "") ) {
			lines.push_back(line);
			line = "";
		}
		else {
			if (c >= 32)
				line.push_back(c);
		}
	}
	fclose(fin);
	return true;
}

bool is_number(string & str)
{
	if (str.length() == 0)
		return false;
	for (unsigned int i = 0; i < str.length(); ++i)
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
	v_string vals = pGetValuesByName(sSectionName, sKeyName);
	return vals.size()>0 ? vals[0] : sDefaultValue;
}

v_string CIniFile::pGetValuesByName(string sSectionName, string sKeyName)
{
	string sKey = "";
	string sVal = "";
	size_t index;
	v_string values;
	
	for (unsigned i = 0; i < lines.size(); ++i)
		if (lines[i] == string("[" + sSectionName + "]"))
		{
			for (unsigned j = i+1; j < lines.size(); ++j)
			{
				index=lines[j].find('=');
				if (index != string::npos)
				{
					sKey = trim(lines[j].substr(0, index));
					if (sKey == sKeyName) {
						sVal = trim(lines[j].substr(index + 1, lines[j].length() - index));
						values.push_back(sVal);
					}
				}
				if ( (lines[j].find('[') == 0) && (lines[j].find(']') == lines[j].length()-1) )
					break;
			}
			break;
		}
	return values;
}