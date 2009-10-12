// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1B00D5FB_7CF3_457D_83C2_1C440598B4BB__INCLUDED_)
#define AFX_STDAFX_H__1B00D5FB_7CF3_457D_83C2_1C440598B4BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifdef DEF_HTMLCOMMOM
//	//	이하 전부다... 웹 관련으로 변환..^^;
//#endif


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Local Header Files
#include <windows.h>
#include <windowsx.h>
#include <ocidl.h>
#include <shlobj.h>
#include <tchar.h>
#include "CntrEvnt.h"
#include "WebCtrl.h"	//	mando..
#include "resource.h"


#define NUMCHARS(x) (sizeof(x)/sizeof(x[0]))
#define THIS_PROP   _T("this")

BOOL AboutDlgProc( HWND, UINT, WPARAM, LPARAM );

//	HWND m_hwndWebCtrl;

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

////#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
////
////#include <afxwin.h>         // MFC core and standard components
////#include <afxext.h>         // MFC extensions
////#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
////#ifndef _AFX_NO_AFXCMN_SUPPORT
////#include <afxcmn.h>			// MFC support for Windows Common Controls
////#endif // _AFX_NO_AFXCMN_SUPPORT
////
////
//////{{AFX_INSERT_LOCATION}}
////// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1B00D5FB_7CF3_457D_83C2_1C440598B4BB__INCLUDED_)