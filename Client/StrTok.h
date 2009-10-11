// StrTok.h: interface for the CStrTok class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRTOK_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_STRTOK_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

class CStrTok  
{
public:
	CStrTok(char * pData, char * pSeps);
	virtual ~CStrTok();
	char * pGet();
	bool _bIsSeperator(char cData, char cNextData);

	char * m_pData, * m_pSeps, m_cToken[256];
	int    m_iDataLength, m_iCurLoc;
};

#endif // !defined(AFX_STRTOK_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_)
