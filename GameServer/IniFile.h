#ifndef INIFILE_H_
#define INIFILE_H_
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef vector<string> v_string;
typedef map<string, string> v_section;

class CIniFile
{
public:
	
	v_string lines;
	
	string m_sIniFileName;
	CIniFile(string sFileName);
	virtual ~CIniFile();
	bool bLoadIni();
	string sGetValue(string sSectionName, string sKeyName, string sDefaultValue);
	int iGetValue(string sSectionName, string sKeyName, int iDefaultValue);
	bool bGetValue(string sSectionName, string sKeyName, bool bDefaultValue);
	v_string pGetValuesByName(string sSectionName, string sKeyName);
};

#endif /*INIFILE_H_*/
