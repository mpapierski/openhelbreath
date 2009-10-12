#ifndef WEBCTRL_H
#define WEBCTRL_H

// #define WEBCTRL_AUTOINIT

#define WC_WEBCTRLA "WebCtrl32"
#define WC_WEBCTRLW L"WebCtrl32"

#ifdef UNICODE
#define WC_WEBCTRL WC_WEBCTRLW
#else
#define WC_WEBCTRL WC_WEBCTRLA 
#endif // UNICODE

class CWebCtrl
{
public:

   CWebCtrl( HWND );

private:

   friend LRESULT CALLBACK WebCtrlProc( HWND, UINT, WPARAM, LPARAM );

   LRESULT WebCtrlProc( UINT, WPARAM, LPARAM );

   void Navigate( LPTSTR );

   HWND m_hwnd;

   int  m_cxScroll;
   int  m_cyScroll;

   CWebContainer *m_pContainer;

   IWebBrowser2 *m_pweb;
};

bool WINAPI InitWebCtrl();
bool WINAPI UninitWebCtrl();

#ifdef WEBCTRL_AUTOINIT

HWND WINAPI CreateWebControl( LPCTSTR pszText, DWORD dwStyles, int x, int y, int cx, int cy, HWND hwndParent, UINT uId );

#endif // WEBCTRL_AUTOINIT

#endif // WEBCTRL_H
