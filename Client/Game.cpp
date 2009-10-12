// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////


#include "Game.h"
#include "lan_eng.h"
#include "SHA1.h"

extern char G_cSpriteAlphaDegree;

extern char G_cCmdLine[256], G_cCmdLineTokenA[120], G_cCmdLineTokenA_Lowercase[120], G_cCmdLineTokenB[120], G_cCmdLineTokenC[120], G_cCmdLineTokenD[120], G_cCmdLineTokenE[120];
extern class XSocket * G_pCalcSocket;
extern BOOL G_bIsCalcSocketConnected;
extern DWORD G_dwCalcSocketTime, G_dwCalcSocketSendTime;
extern HWND	G_hWnd, G_hEditWnd;
extern HINSTANCE G_hInstance;

char _cDrawingOrder[]            = {0, 1, 0, 0, 0, 0, 0, 1, 1};
char _cMantleDrawingOrder[]      = {0, 1, 1, 1, 0, 0, 0, 2, 2};
char _cMantleDrawingOrderOnRun[] = {0, 1, 1, 1, 1, 1, 1, 1, 1};


short _tmp_sOwnerType, _tmp_sAppr1, _tmp_sAppr2, _tmp_sAppr3, _tmp_sAppr4;//, _tmp_iStatus;
//CInt _tmp_iStatus;
int _tmp_iStatus;
char  _tmp_cAction, _tmp_cDir, _tmp_cFrame, _tmp_cName[12];
int   _tmp_iChatIndex, _tmp_dx, _tmp_dy, _tmp_iApprColor, _tmp_iEffectType, _tmp_iEffectFrame, _tmp_dX, _tmp_dY; // 21.171 2002-6-14
WORD  _tmp_wObjectID;
char cDynamicObjectData1, cDynamicObjectData2, cDynamicObjectData3, cDynamicObjectData4;
WORD  wFocusObjectID;
short sFocus_dX, sFocus_dY;
char  cFocusAction, cFocusFrame, cFocusDir, cFocusName[12];
short sFocusX, sFocusY, sFocusOwnerType, sFocusAppr1, sFocusAppr2, sFocusAppr3, sFocusAppr4;
int iFocuiStatus;
int   iFocusApprColor;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CGame::ReadSettings()
{	m_sMagicShortCut = -1;
	m_sRecentShortCut = -1;
	for( int i=0 ; i<6 ; i++ ) m_sShortCut[i] = -1;

	HKEY key;
	DWORD dwDisp;
	UINT Result;
	DWORD Size = sizeof(LONG);
	if( RegCreateKeyEx( HKEY_CURRENT_USER, "Software\\Siementech\\Helbreath\\Settings", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp ) != ERROR_SUCCESS ) return;

	if( RegQueryValueEx(key, "Magic", 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	if( Result > 0 && Result < 101 ) m_sMagicShortCut = Result - 1;
	else m_sMagicShortCut = -1;

	if( RegQueryValueEx(key, "ShortCut0", 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	if( Result > 0 && Result < 201 ) m_sShortCut[0] = Result - 1;
	else m_sShortCut[0] = -1;

	if( RegQueryValueEx(key, "ShortCut1", 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	if( Result > 0 && Result < 201 ) m_sShortCut[1] = Result - 1;
	else m_sShortCut[1] = -1;

	if( RegQueryValueEx(key, "ShortCut2", 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	if( Result > 0 && Result < 201 ) m_sShortCut[2] = Result - 1;
	else m_sShortCut[2] = -1;

	if( RegQueryValueEx(key, "ShortCut3", 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	if( Result > 0 && Result < 201 ) m_sShortCut[3] = Result - 1;
	else m_sShortCut[3] = -1;

	if( RegQueryValueEx(key, "ShortCut4", 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	if( Result > 0 && Result < 201 ) m_sShortCut[4] = Result - 1;
	else m_sShortCut[4] = -1;

	RegCloseKey(key);
}

void CGame::WriteSettings()
{HKEY key;
 DWORD dwDisp;
 UINT nData;
	if( RegCreateKeyEx( HKEY_CURRENT_USER, "Software\\Siementech\\Helbreath\\Settings", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp ) != ERROR_SUCCESS ) return;

	if( m_sMagicShortCut >= 0 && m_sMagicShortCut < 100 ) nData = m_sMagicShortCut + 1;
	else nData = 0;
	if( RegSetValueEx(key, "Magic", 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT) ) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}

	if( m_sShortCut[0] >= 0 && m_sShortCut[0] < 200 ) nData = m_sShortCut[0] + 1;
	else nData = 0;
	if( RegSetValueEx(key, "ShortCut0", 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT) ) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}

	if( m_sShortCut[1] >= 0 && m_sShortCut[1] < 200 ) nData = m_sShortCut[1] + 1;
	else nData = 0;
	if( RegSetValueEx(key, "ShortCut1", 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT) ) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}

	if( m_sShortCut[2] >= 0 && m_sShortCut[2] < 200 ) nData = m_sShortCut[2] + 1;
	else nData = 0;
	if( RegSetValueEx(key, "ShortCut2", 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT) ) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}

	if( m_sShortCut[3] >= 0 && m_sShortCut[3] < 200 ) nData = m_sShortCut[3] + 1;
	else nData = 0;
	if( RegSetValueEx(key, "ShortCut3", 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT) ) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}

	if( m_sShortCut[4] >= 0 && m_sShortCut[4] < 200 ) nData = m_sShortCut[4] + 1;
	else nData = 0;
	if( RegSetValueEx(key, "ShortCut4", 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT) ) != ERROR_SUCCESS )
	{	RegCloseKey(key);
		return;
	}
	RegCloseKey(key);
}

CGame::CGame()
{	int i;
	srand( (unsigned)time( NULL ) );
	ReadSettings();

#ifdef _DEBUG
	m_bToggleScreen = TRUE;
#else
	m_bToggleScreen = FALSE;
#endif

	m_bShowFPS = FALSE;
	m_cDetailLevel = 2;
	m_cLoading = 0;
	m_bZoomMap = TRUE;
	m_bIsFirstConn = TRUE;
	m_iItemDropCnt = 0;
	m_bItemDrop = FALSE;
	m_bIsSpecial = FALSE;
	m_cGameMode = DEF_GAMEMODE_ONLOADING;
	m_cWhisperIndex = DEF_MAXWHISPERMSG;
	m_cGameModeCount = 0;
	ZeroMemory(m_cMapName, sizeof(m_cMapName));
	m_pGSock   = NULL;
	m_pLSock   = NULL;
	m_pMapData = NULL;
	m_cCommandCount  = 0;
	m_dwCommandTime = 0; //v2.15 SpeedHack
	m_sPlayerX = NULL;
	m_sPlayerY = NULL;
	m_sViewDX  = NULL;
	m_sViewDY  = NULL;
	m_cCommand = DEF_OBJECTSTOP;
	m_bIsObserverMode = FALSE;
	for (i = 0; i < DEF_MAXSPRITES; i++) m_pSprite[i] = NULL;
	for (i = 0; i < DEF_MAXTILES; i++) m_pTileSpr[i] = NULL;
	for (i = 0; i < DEF_MAXEFFECTSPR; i++) m_pEffectSpr[i] = NULL;
	m_pBGM = NULL;
	for (i = 0; i < DEF_MAXSOUNDEFFECTS; i++)
	{	m_pCSound[i]  = NULL;
		m_pESound[i]  = NULL;
		m_pMSound[i]  = NULL;
	}

	for (i = 0; i < DEF_MAXCHATMSGS; i++) m_pChatMsgList[i] = NULL;

	for (i = 0; i < DEF_MAXEFFECTS; i++) m_pEffectList[i] = NULL;

	for (i = 0; i < DEF_MAXITEMS; i++) m_pItemList[i] = NULL;

	for (i = 0; i < DEF_MAXBANKITEMS; i++) m_pBankList[i] = NULL;

	for (i = 0; i < 4; i++) m_pCharList[i] = NULL;
	// Snoopy: Fixed here
	for (i = 0; i < 61; i++) m_cDialogBoxOrder[i] = NULL;

	for (i = 0; i < DEF_MAXMAGICTYPE; i++) m_pMagicCfgList[i] = NULL;

	for (i = 0; i < DEF_MAXSKILLTYPE; i++) m_pSkillCfgList[i] = NULL;

	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++) {
		m_pMsgTextList[i] = NULL;
		m_pMsgTextList2[i] = NULL;
		m_pAgreeMsgTextList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pBuildItemList[i] = NULL;

	for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pDispBuildItemList[i] = NULL;

	// Crafting:
	for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pCraftItemList[i] = NULL;
	for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pDispCraftItemList[i] = NULL;



	for (i = 0; i < DEF_MAXGAMEMSGS; i++) m_pGameMsgList[i] = NULL;

	m_pExID = NULL;

	for (i = 0; i < DEF_MAXITEMNAMES; i++) m_pItemNameList[i] = NULL;

	m_stMCursor.cPrevStatus       = DEF_CURSORSTATUS_NULL;
	m_stMCursor.dwSelectClickTime = NULL;

	ZeroMemory(m_cLogServerAddr, sizeof(m_cLogServerAddr));
	m_iGameServerMode = 2; // Snoopy: Default is INTERNET

	for (i = 0; i < DEF_MAXMENUITEMS; i++)
		m_pItemForSaleList[i] = NULL;

	// CLEROTh - INIT DIALOG BOXES

	//Character-Info Dialog(F5)
	m_stDialogBoxInfo[1].sX = 30;
	m_stDialogBoxInfo[1].sY = 30;
	m_stDialogBoxInfo[1].sSizeX = 270;
	m_stDialogBoxInfo[1].sSizeY = 376;

	//Inventory Dialog(F6)
	m_stDialogBoxInfo[2].sX = 380;
	m_stDialogBoxInfo[2].sY = 210;
	m_stDialogBoxInfo[2].sSizeX = 225;
	m_stDialogBoxInfo[2].sSizeY = 185;

	//Magic Circle Dialog(F7)
	m_stDialogBoxInfo[3].sX = 337;
	m_stDialogBoxInfo[3].sY = 57;
	m_stDialogBoxInfo[3].sSizeX = 258;//280;
	m_stDialogBoxInfo[3].sSizeY = 328;//346;

	// Item drop confirmation
	m_stDialogBoxInfo[4].sX = 0;
	m_stDialogBoxInfo[4].sY = 0;
	m_stDialogBoxInfo[4].sSizeX = 270;
	m_stDialogBoxInfo[4].sSizeY = 105;

	// Age <15 box !?!?!?
	m_stDialogBoxInfo[5].sX = 0;
	m_stDialogBoxInfo[5].sY = 0;
	m_stDialogBoxInfo[5].sSizeX = 310;
	m_stDialogBoxInfo[5].sSizeY = 170;

	// ** This is a battle area **
	m_stDialogBoxInfo[6].sX = 0;
	m_stDialogBoxInfo[6].sY = 0;
	m_stDialogBoxInfo[6].sSizeX = 310;
	m_stDialogBoxInfo[6].sSizeY = 170;

	//Guild Menu Dialog
	m_stDialogBoxInfo[7].sX = 337;
	m_stDialogBoxInfo[7].sY = 57;
	m_stDialogBoxInfo[7].sSizeX = 258;
	m_stDialogBoxInfo[7].sSizeY = 339;

	//Guild Operation Dialog
	m_stDialogBoxInfo[8].sX = 337;
	m_stDialogBoxInfo[8].sY = 57;
	m_stDialogBoxInfo[8].sSizeX = 295;
	m_stDialogBoxInfo[8].sSizeY = 346;

	//Guide Map Dialog
	m_stDialogBoxInfo[9].sX = 512;
	m_stDialogBoxInfo[9].sY = 0;
	m_stDialogBoxInfo[9].sSizeX = 128;
	m_stDialogBoxInfo[9].sSizeY = 128;

	//Chatting History Dialog(F9)
	m_stDialogBoxInfo[10].sX = 135;
	m_stDialogBoxInfo[10].sY = 273;
	m_stDialogBoxInfo[10].sSizeX = 364;
	m_stDialogBoxInfo[10].sSizeY = 162;

	//Sale Menu Dialog
	m_stDialogBoxInfo[11].sX = 70;
	m_stDialogBoxInfo[11].sY = 50;
	m_stDialogBoxInfo[11].sSizeX = 258;
	m_stDialogBoxInfo[11].sSizeY = 339;

	//Level-Up Setting Dialog
	m_stDialogBoxInfo[12].sX = 0;
	m_stDialogBoxInfo[12].sY = 0;
	m_stDialogBoxInfo[12].sSizeX = 258;
	m_stDialogBoxInfo[12].sSizeY = 339;

	//City Hall Menu Dialog
	m_stDialogBoxInfo[13].sX = 337;
	m_stDialogBoxInfo[13].sY = 57;
	m_stDialogBoxInfo[13].sSizeX = 258;
	m_stDialogBoxInfo[13].sSizeY = 339;

	//Bank Dialog
	m_stDialogBoxInfo[14].sX = 60; //337
	m_stDialogBoxInfo[14].sY = 50;
	m_stDialogBoxInfo[14].sSizeX = 258;
	m_stDialogBoxInfo[14].sSizeY = 339;
	m_stDialogBoxInfo[14].sV1 = 13;

	//Skill Menu(F8)
	m_stDialogBoxInfo[15].sX = 337;
	m_stDialogBoxInfo[15].sY = 57;
	m_stDialogBoxInfo[15].sSizeX = 258;
	m_stDialogBoxInfo[15].sSizeY = 339;

	//Magic Shop Menu
	m_stDialogBoxInfo[16].sX = 30;
	m_stDialogBoxInfo[16].sY = 30;
	m_stDialogBoxInfo[16].sSizeX = 304;
	m_stDialogBoxInfo[16].sSizeY = 328;

	//Dialog items drop external screen
	m_stDialogBoxInfo[17].sX = 0;
	m_stDialogBoxInfo[17].sY = 0;
	m_stDialogBoxInfo[17].sSizeX = 215;
	m_stDialogBoxInfo[17].sSizeY = 87;

	//Text Dialog
	m_stDialogBoxInfo[18].sX = 20;
	m_stDialogBoxInfo[18].sY = 65;
	m_stDialogBoxInfo[18].sSizeX = 258; // 238
	m_stDialogBoxInfo[18].sSizeY = 339; // 274

	//System Menu Dialog(F12)
	m_stDialogBoxInfo[19].sX = 337;
	m_stDialogBoxInfo[19].sY = 107;
	m_stDialogBoxInfo[19].sSizeX = 258;//270; //v2.18
	m_stDialogBoxInfo[19].sSizeY = 268;//346;

	//NpcActionQuery Dialog
	m_stDialogBoxInfo[20].sX = 237;
	m_stDialogBoxInfo[20].sY = 57;
	m_stDialogBoxInfo[20].sSizeX = 252;
	m_stDialogBoxInfo[20].sSizeY = 87;

	//NpcTalk Dialog
	m_stDialogBoxInfo[21].sX = 337;
	m_stDialogBoxInfo[21].sY = 57;
	m_stDialogBoxInfo[21].sSizeX = 258;
	m_stDialogBoxInfo[21].sSizeY = 339;

	//Map
	m_stDialogBoxInfo[22].sX = 336;
	m_stDialogBoxInfo[22].sY = 88;
	m_stDialogBoxInfo[22].sSizeX = 270;
	m_stDialogBoxInfo[22].sSizeY = 346;

	//ItemSellorRepair Dialog
	m_stDialogBoxInfo[23].sX = 337;
	m_stDialogBoxInfo[23].sY = 57;
	m_stDialogBoxInfo[23].sSizeX = 258;
	m_stDialogBoxInfo[23].sSizeY = 339;

	//Fishing Dialog
	m_stDialogBoxInfo[24].sX = 193;
	m_stDialogBoxInfo[24].sY = 241;
	m_stDialogBoxInfo[24].sSizeX = 263;
	m_stDialogBoxInfo[24].sSizeY = 100;

	//Noticement Dialog
	m_stDialogBoxInfo[25].sX = 162;
	m_stDialogBoxInfo[25].sY = 40;
	m_stDialogBoxInfo[25].sSizeX = 315;
	m_stDialogBoxInfo[25].sSizeY = 171;

	//Manufacture Dialog
	m_stDialogBoxInfo[26].sX = 100;
	m_stDialogBoxInfo[26].sY = 60;
	m_stDialogBoxInfo[26].sSizeX = 258;
	m_stDialogBoxInfo[26].sSizeY = 339;

	//Exchange Dialog
	m_stDialogBoxInfo[27].sX = 100;
	m_stDialogBoxInfo[27].sY = 30;
	m_stDialogBoxInfo[27].sSizeX = 520;
	m_stDialogBoxInfo[27].sSizeY = 357;

	//Quest Dialog
	m_stDialogBoxInfo[28].sX = 0;
	m_stDialogBoxInfo[28].sY = 0;
	m_stDialogBoxInfo[28].sSizeX = 258;
	m_stDialogBoxInfo[28].sSizeY = 339;

	//Gauge Pannel
	m_stDialogBoxInfo[29].sX = 0;
	m_stDialogBoxInfo[29].sY = 434;
	m_stDialogBoxInfo[29].sSizeX = 157;
	m_stDialogBoxInfo[29].sSizeY = 53;

	//Icon Pannel
	m_stDialogBoxInfo[30].sX = 0;
	m_stDialogBoxInfo[30].sY = 427;
	m_stDialogBoxInfo[30].sSizeX = 640;
	m_stDialogBoxInfo[30].sSizeY = 53;//47;

	//Sell List Dialog
	m_stDialogBoxInfo[31].sX = 170;
	m_stDialogBoxInfo[31].sY = 70;
	m_stDialogBoxInfo[31].sSizeX = 258;
	m_stDialogBoxInfo[31].sSizeY = 339;

	//Party Dialog
	m_stDialogBoxInfo[32].sX = 0;
	m_stDialogBoxInfo[32].sY = 0;
	m_stDialogBoxInfo[32].sSizeX = 258;
	m_stDialogBoxInfo[32].sSizeY = 339;

	//Crusade Job Dialog
	m_stDialogBoxInfo[33].sX = 360;
	m_stDialogBoxInfo[33].sY = 65;
	m_stDialogBoxInfo[33].sSizeX = 258;
	m_stDialogBoxInfo[33].sSizeY = 339;

	//Item Upgrade Dialog
	m_stDialogBoxInfo[34].sX = 60;
	m_stDialogBoxInfo[34].sY = 50;
	m_stDialogBoxInfo[34].sSizeX = 258;
	m_stDialogBoxInfo[34].sSizeY = 339;

	//Help Menu Dialog(F1)
	m_stDialogBoxInfo[35].sX = 358;
	m_stDialogBoxInfo[35].sY = 65;
	m_stDialogBoxInfo[35].sSizeX = 258;
	m_stDialogBoxInfo[35].sSizeY = 339;

	//Crusade Commander Dialog
	m_stDialogBoxInfo[36].sX = 20;
	m_stDialogBoxInfo[36].sY = 20;
	m_stDialogBoxInfo[36].sSizeX = 310;
	m_stDialogBoxInfo[36].sSizeY = 386;

	//Crusade Constructor Dialog
	m_stDialogBoxInfo[37].sX = 20;
	m_stDialogBoxInfo[37].sY = 20;
	m_stDialogBoxInfo[37].sSizeX = 310;
	m_stDialogBoxInfo[37].sSizeY = 386;

	//Crusade Soldier Dialog
	m_stDialogBoxInfo[38].sX = 20;
	m_stDialogBoxInfo[38].sY = 20;
	m_stDialogBoxInfo[38].sSizeX = 310;
	m_stDialogBoxInfo[38].sSizeY = 386;

	// Give item ???
	m_stDialogBoxInfo[39].sX = 0;
	m_stDialogBoxInfo[39].sY = 0;
	m_stDialogBoxInfo[39].sSizeX = 291;
	m_stDialogBoxInfo[39].sSizeY = 413;

	// 3.51 Slates Dialog - Diuuude
	m_stDialogBoxInfo[40].sX = 100;
	m_stDialogBoxInfo[40].sY = 60;
	m_stDialogBoxInfo[40].sSizeX = 258;
	m_stDialogBoxInfo[40].sSizeY = 339;

	// Snoopy: Item exchange confirmation
	m_stDialogBoxInfo[41].sX = 285;
	m_stDialogBoxInfo[41].sY = 200;
	m_stDialogBoxInfo[41].sSizeX = 270;
	m_stDialogBoxInfo[41].sSizeY = 105;

	// MJ Stats Change DialogBox - Diuuude
	m_stDialogBoxInfo[42].sX = 0;
	m_stDialogBoxInfo[42].sY = 0;
	m_stDialogBoxInfo[42].sSizeX = 258;
	m_stDialogBoxInfo[42].sSizeY = 339;

	// Snoopy: Resurection
	m_stDialogBoxInfo[50].sX = 185;
	m_stDialogBoxInfo[50].sY = 100;
	m_stDialogBoxInfo[50].sSizeX = 270;
	m_stDialogBoxInfo[50].sSizeY = 105;

	//Guild Hall Menu Dialog
	m_stDialogBoxInfo[51].sX = 337;
	m_stDialogBoxInfo[51].sY = 57;
	m_stDialogBoxInfo[51].sSizeX = 258;
	m_stDialogBoxInfo[51].sSizeY = 339;

	m_bCtrlPressed  = FALSE;
	m_bShiftPressed = FALSE;
	m_bEnterPressed = FALSE;
	m_bEscPressed	= FALSE;
	m_bSoundFlag = FALSE;
	m_dwDialogCloseTime = 0;
	m_iTimeLeftSecAccount = NULL;
	m_iTimeLeftSecIP      = NULL;
	m_bWhisper = TRUE;
	m_bShout   = TRUE;
}

CGame::~CGame()
{}

BOOL CGame::bInit(HWND hWnd, HINSTANCE hInst, char * pCmdLine)
{int iIndex;
 int i;
 class CStrTok * pStrTok;
 char seps[] = "&= ,\t\n";
 char * token;
 // CLEROTH - BUG
	for (i = 0; i < DEF_MAXSPRITES; i++)
		m_pSprite[i] = NULL;
	if (pCmdLine != NULL)
	{	ZeroMemory(G_cCmdLine, sizeof(G_cCmdLine));
		ZeroMemory(G_cCmdLineTokenA, sizeof(G_cCmdLineTokenA));
		ZeroMemory(G_cCmdLineTokenB, sizeof(G_cCmdLineTokenB));
		ZeroMemory(G_cCmdLineTokenC, sizeof(G_cCmdLineTokenC));
		ZeroMemory(G_cCmdLineTokenD, sizeof(G_cCmdLineTokenD));
		ZeroMemory(G_cCmdLineTokenE, sizeof(G_cCmdLineTokenE));

		strcpy(G_cCmdLine, pCmdLine);

		iIndex = 0;
		pStrTok = new class CStrTok(pCmdLine, seps);
		token = pStrTok->pGet();
		while( token != NULL )
		{	switch (iIndex) {
			case 0:	strcpy(G_cCmdLineTokenA, token); break;
			case 1: strcpy(G_cCmdLineTokenB, token); break;
			case 2: strcpy(G_cCmdLineTokenC, token); break;
			case 3: strcpy(G_cCmdLineTokenD, token); break;
			case 4: strcpy(G_cCmdLineTokenE, token); break;
			}
			token = pStrTok->pGet();
			iIndex++;
		}
		delete pStrTok;
	}

	ZeroMemory(G_cCmdLineTokenA_Lowercase, sizeof(G_cCmdLineTokenA_Lowercase));
	strcpy(G_cCmdLineTokenA_Lowercase, G_cCmdLineTokenA);
	_strlwr(G_cCmdLineTokenA_Lowercase);

	if (memcmp(G_cCmdLineTokenA_Lowercase, "/egparam", 8) == 0)
	{	ZeroMemory(G_cCmdLineTokenA, sizeof(G_cCmdLineTokenA));
		memcpy(G_cCmdLineTokenA,"dataq",5);
	}
	m_hWnd = hWnd;
	m_bCommandAvailable = TRUE;
	m_dwTime = G_dwGlobalTime;
	m_bSoundFlag = m_DSound.Create(m_hWnd);
	m_bMusicStat = m_bSoundStat = m_bSoundFlag;
	m_bIsHideLocalCursor = FALSE;
	m_cEnterCheck = m_cTabCheck = m_cLeftArrowCheck = NULL;

	if (bCheckImportantFile() == FALSE)
	{	MessageBox(m_hWnd, "File checksum error! Get Update again please!", "ERROR1", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if (_bDecodeBuildItemContents() == FALSE)
	{	MessageBox(m_hWnd, "File checksum error! Get Update again please!","ERROR2",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if(bReadLoginConfigFile("login.cfg") == FALSE)
	{	MessageBox(m_hWnd, "login.cfg file contains wrong infomation.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if(bReadItemNameConfigFile() == FALSE)
	{	MessageBox(m_hWnd, "ItemName.cfg file contains wrong infomation.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if (bInitMagicCfgList() == FALSE) {
		MessageBox(m_hWnd, "MAGICCFG.TXT file contains wrong infomation.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	// Skill
	if (bInitSkillCfgList() == FALSE)
	{	MessageBox(m_hWnd, "SKILLCFG.TXT file contains wrong infomation.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if (m_DDraw.bInit(m_hWnd) == FALSE)
	{	MessageBox(m_hWnd, "This program requires DirectX7.0a!","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if (m_DInput.bInit(hWnd, hInst) == FALSE) {
		MessageBox(m_hWnd, "This program requires DirectX7.0a!","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}


	m_hPakFile = CreateFile("sprites\\New-Dialog.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING] = new class CSprite(m_hPakFile, &m_DDraw, "New-Dialog", 0, FALSE);
	CloseHandle(m_hPakFile);

	m_hPakFile = CreateFile("sprites\\interface2.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE] = new class CSprite(m_hPakFile, &m_DDraw, "interface2", 0, FALSE);
	m_pSprite[DEF_SPRID_INTERFACE_CRAFTING] = new class CSprite(m_hPakFile, &m_DDraw, "interface2", 3, FALSE);
	CloseHandle(m_hPakFile);

	// CLEROTH - LOAD FONTS BEFORE MAIN LOADING
	m_hPakFile = CreateFile("sprites\\interface2.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( m_hPakFile != INVALID_HANDLE_VALUE )
	{	m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2] = new class CSprite(m_hPakFile, &m_DDraw, "interface2", 1, FALSE);
		m_pSprite[DEF_SPRID_INTERFACE_F1HELPWINDOWS] = new class CSprite(m_hPakFile, &m_DDraw, "interface2", 2, FALSE);
		CloseHandle(m_hPakFile);
	}

	m_hPakFile = CreateFile("sprites\\sprfonts.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( m_hPakFile != INVALID_HANDLE_VALUE )
	{	m_pSprite[DEF_SPRID_INTERFACE_FONT1] = new class CSprite(m_hPakFile, &m_DDraw, "sprfonts", 0, FALSE);
		m_pSprite[DEF_SPRID_INTERFACE_FONT2] = new class CSprite(m_hPakFile, &m_DDraw, "sprfonts", 1, FALSE);
		CloseHandle(m_hPakFile);
	}

	m_stMCursor.sX = 0;
	m_stMCursor.sY = 0;
	m_pMapData = new class CMapData(this);
	ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
	ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
	ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

	m_sPlayerType = 2;
	m_cPlayerTurn = 0;
// Snoopy: fixed here
	m_cDialogBoxOrder[60] = 29;
	m_cDialogBoxOrder[59] = 30; // 29π¯ GaugePannel

	m_cMenuDir    = 4;
	m_cMenuDirCnt = 0;
	m_cMenuFrame  = 0;

	m_cSoundVolume = 100;
	m_cMusicVolume = 100;

	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  70,  70,  80), &m_wWR[1], &m_wWG[1], &m_wWB[1]); // Light-blue
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  70,  70,  80), &m_wWR[2], &m_wWG[2], &m_wWB[2]); // light-blue
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  70,  70,  80), &m_wWR[3], &m_wWG[3], &m_wWB[3]); // light-blue
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  70, 100,  70), &m_wWR[4], &m_wWG[4], &m_wWB[4]); // Green
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB( 130,  90,  10), &m_wWR[5], &m_wWG[5], &m_wWB[5]); // Critical
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  42,  53, 111), &m_wWR[6], &m_wWG[6], &m_wWB[6]); // Heavy-blue
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB( 145, 145, 145), &m_wWR[7], &m_wWG[7], &m_wWB[7]); // White
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB( 120, 100, 120), &m_wWR[8], &m_wWG[8], &m_wWB[8]); // Violet
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  75,  10,  10), &m_wWR[9], &m_wWG[9], &m_wWB[9]); // Heavy-Red
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB( 135, 104,  30), &m_wR[10], &m_wG[10], &m_wB[10]);	// Gold, buggy

	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB( 200/2,  200/2,  200/2),  &m_wR[0], &m_wG[0], &m_wB[0]);
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0x50/2, 0x50/2, 0xC0/2),  &m_wR[1], &m_wG[1], &m_wB[1]); // Indigo Blue
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(    79,     79,     62),  &m_wR[2], &m_wG[2], &m_wB[2]); // Custom-Weapon Color
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(   135,    104,     30),  &m_wR[3], &m_wG[3], &m_wB[3]); // Gold
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB( 255/2,   36/2,      0),  &m_wR[4], &m_wG[4], &m_wB[4]); // Crimson
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(    10,     60,     10),  &m_wR[5], &m_wG[5], &m_wB[5]); // Green
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0x50/2, 0x50/2, 0x50/2),  &m_wR[6], &m_wG[6], &m_wB[6]); // Gray
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0x5F/2, 0x9E/2, 0xA0/2),  &m_wR[7], &m_wG[7], &m_wB[7]); // Aqua
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0xFF/2, 0x69/2, 0xB4/2),  &m_wR[8], &m_wG[8], &m_wB[8]); // Pink
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(    90,     60,     90),  &m_wR[9], &m_wG[9], &m_wB[9]); // Violet

	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(     0,     35,     60),  &m_wR[10], &m_wG[10], &m_wB[10]); // Blue
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0xD2/2, 0xB4/2, 0x8C/2),  &m_wR[11], &m_wG[11], &m_wB[11]); // Tan
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0xBD/2, 0xB7/2, 0x6B/2),  &m_wR[12], &m_wG[12], &m_wB[12]); // Khaki
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(    85,     85,      8),  &m_wR[13], &m_wG[13], &m_wB[13]); // Yellow
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(    75,     10,     10),  &m_wR[14], &m_wG[14], &m_wB[14]); // Red
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(  0x30,   0x30,   0x30),  &m_wR[15], &m_wG[15], &m_wB[15]); // Black


	m_pCGameMonitor = new class CGameMonitor;
#ifndef _DEBUG
	//===============================================
	// badword.txt
	if(!m_Misc._iConvertFileXor("contents\\badword.txt", "contents\\badword.tmp", 35))
	{	MessageBox(m_hWnd, "BADWORD.TXT file contains wrong infomation.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	m_pCGameMonitor->iReadBadWordFileList("contents\\badword.tmp");
	DeleteFile("contents\\badword.tmp");

	if(!m_Misc._iConvertFileXor("contents\\Curse.txt", "contents\\Curse.tmp", 35))
	{	MessageBox(m_hWnd, "CURSE.TXT file contains wrong infomation.","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	m_curse.LoadCurse( "contents\\Curse.tmp" );
	DeleteFile("contents\\Curse.tmp");
	//==============================================
#endif

	_LoadGameMsgTextContents();
	ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));

	return TRUE;
}

void CGame::Quit()
{int i;
	WriteSettings();
	ChangeGameMode(DEF_GAMEMODE_NULL);

	for (i = 0; i < DEF_MAXSPRITES; i++)
	if (m_pSprite[i] != NULL) delete m_pSprite[i];
	for (i = 0; i < DEF_MAXTILES; i++)
	if (m_pTileSpr[i] != NULL) delete m_pTileSpr[i];
	for (i = 0; i < DEF_MAXEFFECTSPR; i++)
	if (m_pEffectSpr[i] != NULL) delete m_pEffectSpr[i];

	for (i = 0; i < DEF_MAXSOUNDEFFECTS; i++) {
		if (m_pCSound[i] != NULL) delete m_pCSound[i];
		if (m_pMSound[i] != NULL) delete m_pMSound[i];
		if (m_pESound[i] != NULL) delete m_pESound[i];
	}

	if (m_pBGM != NULL) delete m_pBGM;

	for (i = 0; i < 4; i++)
	if (m_pCharList[i] != NULL) delete m_pCharList[i];

	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] != NULL)	delete m_pItemList[i];

	for (i = 0; i < DEF_MAXBANKITEMS; i++)
	if (m_pBankList[i] != NULL)	delete m_pBankList[i];

	for (i = 0; i < DEF_MAXEFFECTS; i++)
	if (m_pEffectList[i] != NULL) delete m_pEffectList[i];

	for (i = 0; i < DEF_MAXCHATMSGS; i++)
		if (m_pChatMsgList[i] != NULL) delete m_pChatMsgList[i];

	for (i = 0; i < DEF_MAXCHATSCROLLMSGS; i++)
		if (m_pChatScrollList[i] != NULL) delete m_pChatScrollList[i];

	for (i = 0; i < DEF_MAXWHISPERMSG; i++)
		if (m_pWhisperMsg[i] != NULL) delete m_pWhisperMsg[i];

	for (i = 0; i < DEF_MAXMENUITEMS; i++)
		if (m_pItemForSaleList[i] != NULL) delete m_pItemForSaleList[i];

	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		if (m_pMagicCfgList[i] != NULL) delete m_pMagicCfgList[i];

	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		if (m_pSkillCfgList[i] != NULL) delete m_pSkillCfgList[i];

	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++) {
		if (m_pMsgTextList[i] != NULL)  delete m_pMsgTextList[i];
		if (m_pMsgTextList2[i] != NULL) delete m_pMsgTextList2[i];
		if (m_pAgreeMsgTextList[i] != NULL) delete m_pAgreeMsgTextList[i];
	}

	if (m_pExID != NULL) delete m_pExID;

	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
		if (m_pBuildItemList[i] != NULL) delete m_pBuildItemList[i];

	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
		if (m_pDispBuildItemList[i] != NULL) delete m_pDispBuildItemList[i];

	// Crafting:
	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
		if (m_pCraftItemList[i] != NULL) delete m_pCraftItemList[i];
	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
		if (m_pDispCraftItemList[i] != NULL) delete m_pDispCraftItemList[i];


	for (i = 0; i < DEF_MAXGAMEMSGS; i++)
		if (m_pGameMsgList[i] != NULL) delete m_pGameMsgList[i];

	for (i = 0; i < DEF_MAXITEMNAMES; i++)
		if (m_pItemNameList[i] != NULL) delete m_pItemNameList[i];

	delete m_pMapData;

	if (m_pGSock != NULL) delete m_pGSock;
	if (m_pLSock != NULL) delete m_pLSock;
	if (G_pCalcSocket != NULL) delete G_pCalcSocket;
	if (m_pCGameMonitor != NULL) delete m_pCGameMonitor;
}


void CGame::UpdateScreen()
{ 	G_dwGlobalTime = timeGetTime();
	switch (m_cGameMode) {
#ifdef DEF_MAKE_ACCOUNT
	case DEF_GAMEMODE_ONAGREEMENT:
		// UpdateScreen_OnAgreement(); //unused by HBx server..
		break;

	case DEF_GAMEMODE_ONCREATENEWACCOUNT:
		UpdateScreen_OnCreateNewAccount();
		break;
#endif

	case DEF_GAMEMODE_ONVERSIONNOTMATCH:
		UpdateScreen_OnVersionNotMatch();
		break;

	case DEF_GAMEMODE_ONCONNECTING:
		UpdateScreen_OnConnecting();
		break;

	case DEF_GAMEMODE_ONMAINMENU:
		UpdateScreen_OnMainMenu();
		break;

	case DEF_GAMEMODE_ONLOADING:
		UpdateScreen_OnLoading(TRUE);
		break;

	case DEF_GAMEMODE_ONMAINGAME:
		UpdateScreen_OnGame();
		break;

	case DEF_GAMEMODE_ONWAITINGINITDATA:
		UpdateScreen_OnWaitInitData();
		break;

	case DEF_GAMEMODE_ONCONNECTIONLOST:
		UpdateScreen_OnConnectionLost();
		break;

	case DEF_GAMEMODE_ONMSG:
		UpdateScreen_OnMsg();
		break;

	case DEF_GAMEMODE_ONLOGIN:
		UpdateScreen_OnLogin();
		break;

	case DEF_GAMEMODE_ONSELECTSERVER:
		UpdateScreen_OnSelectServer();
		break;

	case DEF_GAMEMODE_ONQUIT:
		UpdateScreen_OnQuit();
		break;

	case DEF_GAMEMODE_ONQUERYFORCELOGIN:
		UpdateScreen_OnQueryForceLogin();
		break;

	case DEF_GAMEMODE_ONSELECTCHARACTER:
		UpdateScreen_OnSelectCharacter();
		break;

	case DEF_GAMEMODE_ONCREATENEWCHARACTER:
		UpdateScreen_OnCreateNewCharacter();
		break;

	case DEF_GAMEMODE_ONWAITINGRESPONSE:
		UpdateScreen_OnWaitingResponse();
		break;

	case DEF_GAMEMODE_ONQUERYDELETECHARACTER:
		UpdateScreen_OnQueryDeleteCharacter();
		break;

	case DEF_GAMEMODE_ONLOGRESMSG:
		UpdateScreen_OnLogResMsg();
		break;

	case DEF_GAMEMODE_ONCHANGEPASSWORD:
		UpdateScreen_OnChangePassword();
		break;
	}

#ifdef DEF_USING_WIN_IME

	if (GetAsyncKeyState(VK_RETURN) != NULL) m_cEnterCheck = 1;
	if ((m_cEnterCheck == 1) && (GetAsyncKeyState(VK_RETURN) == NULL))
	{	m_bEnterPressed = TRUE;
		m_cEnterCheck = NULL;
	}
	if (GetAsyncKeyState(VK_TAB) != NULL) m_cTabCheck = 1;
 	if ((m_cTabCheck == 1) && (GetAsyncKeyState(VK_TAB) == NULL))
	{	m_cCurFocus++;
		if( m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
		if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME) bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, NULL, NULL, NULL, NULL, NULL);
		m_cTabCheck = NULL;
	}
	if( m_bInputStatus )
	{	if (GetAsyncKeyState(VK_LEFT) != NULL) m_cLeftArrowCheck = 1;
		if ((m_cLeftArrowCheck == 1) && (GetAsyncKeyState(VK_LEFT) == NULL))
		{	m_cLeftArrowCheck = NULL;
			if( G_hEditWnd != NULL )
			{	int iStrLen = strlen(m_pInputBuffer);
				SendMessage( G_hEditWnd, EM_SETSEL, iStrLen, iStrLen );
	}	}	}
#endif
}


void CGame::CalcViewPoint()
{ short dX, dY;
	dX = m_sViewPointX - m_sViewDstX;
	dY = m_sViewPointY - m_sViewDstY;
	if (abs(dX) < abs(m_sViewDX))
	{	m_sViewPointX = m_sViewDstX;
		m_sViewDX = 0;
	}else
	{	if (dX > 0) m_sViewDX--;
		if (dX < 0) m_sViewDX++;
		if (dX == 0) m_sViewDX = 0;
		if (abs(dX) < 40) {
			if (m_sViewDX > 4)  m_sViewDX = 4;
			else if (m_sViewDX < -4) m_sViewDX = -4;
		}
		m_sViewPointX += m_sViewDX;
	}

	if (abs(dY) < abs(m_sViewDY))
	{	m_sViewPointY = m_sViewDstY;
		m_sViewDY = 0;
	}else
	{	if (dY > 0) m_sViewDY--;
		if (dY < 0) m_sViewDY++;
		if (dY == 0) m_sViewDY = 0;
		if (abs(dY) < 40) {
			if (m_sViewDY > 4)  m_sViewDY = 4;
			else if (m_sViewDY < -4) m_sViewDY = -4;
		}
		m_sViewPointY += m_sViewDY;
	}
}

void CGame::OnGameSocketEvent(WPARAM wParam, LPARAM lParam)
{int iRet;
 char * pData;
 DWORD  dwMsgSize;

	if (m_pGSock == NULL) return;

	iRet = m_pGSock->iOnSocketEvent(wParam, lParam);
	switch (iRet) {
	case DEF_XSOCKEVENT_CONNECTIONESTABLISH:
		ConnectionEstablishHandler(DEF_SERVERTYPE_GAME);
		break;

	case DEF_XSOCKEVENT_READCOMPLETE:
		pData = m_pGSock->pGetRcvDataPointer(&dwMsgSize);
		GameRecvMsgHandler(dwMsgSize, pData);
		m_dwTime = G_dwGlobalTime;
		break;

	case DEF_XSOCKEVENT_SOCKETCLOSED:
		ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
		delete m_pGSock;
		m_pGSock = NULL;
		break;

	case DEF_XSOCKEVENT_SOCKETERROR:
		ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
		delete m_pGSock;
		m_pGSock = NULL;
		break;

	case DEF_XSOCKEVENT_CRITICALERROR:
		delete m_pGSock;
		m_pGSock = NULL;
		if (G_pCalcSocket != NULL)
		{	delete G_pCalcSocket;
			G_pCalcSocket = NULL;
		}
		break;
	}
}

void CGame::RestoreSprites()
{
	for (int i = 0; i < DEF_MAXSPRITES; i++)
	if (m_pSprite[i] != NULL) m_pSprite[i]->iRestore();
}

char _tmp_cTmpDirX[9] = { 0,0,1,1,1,0,-1,-1,-1 };
char _tmp_cTmpDirY[9] = { 0,-1,-1,0,1,1,1,0,-1 };
char CGame::cGetNextMoveDir(short sX, short sY, short dstX, short dstY, BOOL bMoveCheck, BOOL bMIM)
{
 char  cDir, cTmpDir;
 //int   aX, aY, aX2, aY2, dX, dY;
 int   aX, aY, dX, dY;
 int   i;
	if ((sX == dstX) && (sY == dstY)) return 0;
	dX = sX;
	dY = sY;

	if (bMIM == FALSE) // MIM Fix
		 cDir = m_Misc.cGetNextMoveDir(dX, dY, dstX, dstY);
	else cDir = m_Misc.cGetNextMoveDir(dstX, dstY, dX, dY);

	if (m_cPlayerTurn == 0)
	for (i = cDir; i <= cDir + 2;i++)
	{	cTmpDir = i;
		if (cTmpDir > 8) cTmpDir -= 8;
		aX = _tmp_cTmpDirX[cTmpDir];
		aY = _tmp_cTmpDirY[cTmpDir];
		if (((dX + aX) == m_iPrevMoveX) && ((dY + aY) == m_iPrevMoveY) && (m_bIsPrevMoveBlocked == TRUE) && (bMoveCheck == TRUE))
		{	m_bIsPrevMoveBlocked = FALSE;
		}else if (m_pMapData->bGetIsLocateable(dX + aX, dY + aY) == TRUE)
		{	if( m_pMapData->bIsTeleportLoc(dX + aX, dY + aY) == TRUE )
			{	if( _bCheckMoveable(dX + aX, dY + aY) == TRUE ) return cTmpDir;
				else
				{	SetTopMsg( DEF_MSG_GETNEXTMOVEDIR, 5 );
				}
			}else return cTmpDir;
	}	}

	if (m_cPlayerTurn == 1)
	for (i = cDir; i >= cDir - 2;i--)
	{	cTmpDir = i;
		if (cTmpDir < 1) cTmpDir += 8;
		aX = _tmp_cTmpDirX[cTmpDir];
		aY = _tmp_cTmpDirY[cTmpDir];
		if (((dX + aX) == m_iPrevMoveX) && ((dY + aY) == m_iPrevMoveY) && (m_bIsPrevMoveBlocked == TRUE) && (bMoveCheck == TRUE))
		{	m_bIsPrevMoveBlocked = FALSE;
		}else if (m_pMapData->bGetIsLocateable(dX + aX, dY + aY) == TRUE)
		{	if( m_pMapData->bIsTeleportLoc(dX + aX, dY + aY) == TRUE )
			{	if( _bCheckMoveable(dX + aX, dY + aY) == TRUE ) return cTmpDir;
				else
				{	SetTopMsg( DEF_MSG_GETNEXTMOVEDIR, 5 );
				}
			}else return cTmpDir;
	}	}
	return 0;
}

BOOL CGame::_bCheckMoveable( short sx, short sy )
{	// Snoopy: This function prevents the client from asking at TP from some maps to
	// ML or PL if not citizen
	// Incomplete function and useless (the server will handle such cases)
/*	if( m_bIsCrusadeMode ) return TRUE;
	if( m_bHunter == FALSE ) return TRUE;
	if( m_bCitizen == FALSE ) return TRUE;
	if( m_bAresden == TRUE && m_cMapIndex == 11 )
	{	if( sy == 20 )
		{	if( (sx>=39) && (sx<=47) ) return FALSE;
			if( (sx>=360) && (sx<=368) ) return FALSE;
		}
	}
	if( m_bAresden == FALSE && m_cMapIndex == 3 )
	{
		if( sy == 373 )
		{	if( (sx>=27) && (sx<=32) ) return FALSE;
		}
		if( sy == 374 )
		{	if( (sx>=298) && (sx<=305) ) return FALSE;
		}
	}*/
	return TRUE;
}

BOOL CGame::bSendCommand(DWORD dwMsgID, WORD wCommand, char cDir, int iV1, int iV2, int iV3, char * pString, int iV4)
{char  * cp, cMsg[300], cTxt[256], cKey;
 WORD  * wp;
 DWORD * dwp, dwTime;
 short * sp;
 int   * ip, iRet, i, * fightzonenum ;
 CSHA1 sha1;
 char szReport[1024];

	if ((m_pGSock == NULL) && (m_pLSock == NULL)) return FALSE;
	dwTime = timeGetTime();
	ZeroMemory(cMsg, sizeof(cMsg));
	cKey = (char)(rand() % 255) +1;

	switch (dwMsgID) {

	case DEF_REQUEST_ANGEL:	// to Game Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char*)(cMsg + 6);
		memset( cp, 0, 20 );
		memcpy((char *)cp, pString, strlen(pString) + 1);
		cp += 20;
		ip = (int *)cp;
		*ip = iV1; // Angel ID
		iRet = m_pGSock->iSendMsg(cMsg, 30, cKey);
		break;

	case DEF_REQUEST_RESURRECTPLAYER_YES: // By snoopy
	case DEF_REQUEST_RESURRECTPLAYER_NO:  // By snoopy
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		iRet = m_pGSock->iSendMsg(cMsg, 6, cKey);
		break;

	case MSGID_REQUEST_HELDENIAN_SCROLL:// By snoopy
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char*)(cMsg + 6);
		memset( cp, 0, 20 );
		memcpy((char *)cp, pString, strlen(pString) + 1);
		cp += 20;
		wp = (WORD *)cp;
		*wp = wCommand; // Item ID
		iRet = m_pGSock->iSendMsg(cMsg, 28, cKey);
		break;

	case MSGID_REQUEST_TELEPORT_LIST:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char*)(cMsg + 6);
		memset( cp, 0, 20 );
		memcpy( cp, "William", 20 );
		iRet = m_pGSock->iSendMsg(cMsg, 26, cKey);
		break;

	case MSGID_REQUEST_HELDENIAN_TP_LIST: // Snoopy: Heldenian TP
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char*)(cMsg + 6);
		memset( cp, 0, 20 );
		memcpy( cp, "Gail", 20 );
		iRet = m_pGSock->iSendMsg(cMsg, 26, cKey);
		break;

	case MSGID_REQUEST_HELDENIAN_TP: // Snoopy: Heldenian TP
	case MSGID_REQUEST_CHARGED_TELEPORT:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		ip  = (int *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		*ip = iV1;
		iRet = m_pGSock->iSendMsg(cMsg, 10, cKey);
		break;

	case MSGID_REQUEST_SELLITEMLIST:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		for (i = 0; i < DEF_MAXSELLLIST; i++)
		{	*cp = m_stSellItemList[i].iIndex;
			cp++;
			ip = (int *)cp;
			*ip = m_stSellItemList[i].iAmount;
			cp += 4;
		}

		iRet = m_pGSock->iSendMsg(cMsg, 70, cKey);
		break;

	case MSGID_REQUEST_RESTART:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		iRet = m_pGSock->iSendMsg(cMsg, 6, cKey);
		break;

	case MSGID_REQUEST_PANNING:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		*cp = cDir;
		cp++;

		iRet = m_pGSock->iSendMsg(cMsg, 7, cKey);
		break;

	case MSGID_REQUEST_CHANGEPASSWORD:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, m_cAccountName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cNewPassword, strlen(m_cNewPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cNewPassConfirm, strlen(m_cNewPassConfirm));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		iRet = m_pLSock->iSendMsg(cMsg, 136, cKey);
		break;

	case MSGID_REQUEST_CREATENEWACCOUNT:
		// to Log Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, m_cAccountName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		memcpy(cp, m_cEmailAddr, 50);
		cp += 50;

		ZeroMemory(cTxt, sizeof(cTxt));
		strcpy(cTxt, " "); // gender
		memcpy(cp, cTxt, 10);
		cp += 10;

		memcpy(cp, m_cAccountAge, 10);
		cp += 10;

		memcpy(cp, " ", 4);
		cp += 4;

		memcpy(cp, " ", 2);
		cp += 2;

		memcpy(cp, " ", 2);
		cp += 2;

		memcpy(cp, m_cAccountCountry, 17);
		cp += 17;

		memcpy(cp, m_cAccountSSN, 28);
		cp += 28;

 		memcpy(cp, m_cAccountQuiz, 45);
		cp += 45;

		memcpy(cp, m_cAccountAnswer, 20);
		cp += 20;

		memcpy(cp, G_cCmdLineTokenA_Lowercase, 50);

		iRet = m_pLSock->iSendMsg(cMsg, 244	+50, cKey);
		break;

	case MSGID_GETMINIMUMLOADGATEWAY:
	case MSGID_REQUEST_LOGIN:
		// to Log Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, m_cAccountName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		memcpy(cp, m_cWorldServerName, 30);
		cp += 30;

		iRet = m_pLSock->iSendMsg(cMsg, 86, cKey);
		break;

	case MSGID_REQUEST_CREATENEWCHARACTER:
		// to Log Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = (WORD)NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		memcpy(cp, m_cPlayerName, 10);
		cp += 10;

		memcpy(cp, m_cAccountName, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		memcpy(cp, m_cWorldServerName, 30);
		cp += 30;

		*cp = m_cGender;
		cp++;

		*cp = m_cSkinCol;
		cp++;

		*cp = m_cHairStyle;
		cp++;

		*cp = m_cHairCol;
		cp++;

		*cp = m_cUnderCol;
		cp++;

		*cp = m_ccStr;
		cp++;

		*cp = m_ccVit;
		cp++;

		*cp = m_ccDex;
		cp++;

		*cp = m_ccInt;
		cp++;

		*cp = m_ccMag;
		cp++;

		*cp = m_ccChr;
		cp++;

		iRet = m_pLSock->iSendMsg(cMsg, 107, cKey);
		break;

	case MSGID_REQUEST_ENTERGAME:
		// to Log Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = (WORD)m_wEnterGameType;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, m_cPlayerName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.43
		memcpy(cTxt, m_cMapName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, m_cAccountName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		ip = (int *)cp;
		*ip = m_iLevel;
		cp += 4;

		memcpy(cp, m_cWorldServerName, 30);
		cp += 30;

		memcpy(cp, G_cCmdLineTokenA, 120);
		cp += 120;

		iRet = m_pLSock->iSendMsg(cMsg, 230, cKey);
		break;

	case MSGID_REQUEST_DELETECHARACTER:
		// to Log Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = (WORD)m_wEnterGameType;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		memcpy(cp, m_pCharList[m_wEnterGameType - 1]->m_cName, 10);
		cp += 10;

		memcpy(cp, m_cAccountName, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		memcpy(cp, m_cWorldServerName, 30);
		cp += 30;

		iRet = m_pLSock->iSendMsg(cMsg, 96, cKey);
		break;

	case MSGID_REQUEST_SETITEMPOS:
		// to Game Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		*cp = cDir;

		cp++;

		sp = (short *)cp;
		*sp = (short)iV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)iV2;
		cp += 2;

		iRet = m_pGSock->iSendMsg(cMsg, 11);
		break;

	case MSGID_COMMAND_CHECKCONNECTION:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		dwp = (DWORD *)cp;
		*dwp = dwTime;
		cp += 4;
		iRet = m_pGSock->iSendMsg(cMsg, 10, cKey);

		break;

	case MSGID_REQUEST_INITDATA:
	case MSGID_REQUEST_INITPLAYER:
		// to Game Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, m_cPlayerName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, m_cAccountName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		*cp = (char)m_bIsObserverMode;
		cp++;

		// v2.04 Gateway
		memcpy(cp, m_cGameServerName, 20);
		cp += 20;

		iRet = m_pGSock->iSendMsg(cMsg, 67 +21, cKey);

		//m_bIsObserverMode = FALSE;
		break;
	case MSGID_LEVELUPSETTINGS:
		// CLEROTH
		//if ((m_cLU_Str + m_cLU_Vit + m_cLU_Dex + m_cLU_Int + m_cLU_Mag + m_cLU_Char) > 3) return FALSE;

		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		*cp = m_cLU_Str;
		cp++;

		*cp = m_cLU_Vit;
		cp++;

		*cp = m_cLU_Dex;
		cp++;

		*cp = m_cLU_Int;
		cp++;

		*cp = m_cLU_Mag;
		cp++;

		*cp = m_cLU_Char;
		cp++;

		iRet = m_pGSock->iSendMsg(cMsg, 12);
		break;

	case MSGID_COMMAND_CHATMSG:
		if (m_bIsTeleportRequested == TRUE) return FALSE;

		// to Game Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		sp = (short *)cp;
		*sp = m_sPlayerX;
		cp += 2;

		sp = (short *)cp;
		*sp = m_sPlayerY;
		cp += 2;

		memcpy(cp, m_cPlayerName, 10);
		cp += 10;

		*cp = (char)iV1;
		cp++;

		if (bCheckLocalChatCommand(pString) == TRUE) return FALSE;
		memcpy((char *)cp, pString, strlen(pString) + 1);

		iRet = m_pGSock->iSendMsg(cMsg, 22 + strlen(pString));
		break;

	case MSGID_COMMAND_COMMON:
		if (m_bIsTeleportRequested == TRUE) return FALSE;
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = wCommand;
		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		*sp = m_sPlayerX;
		cp += 2;
		sp = (short *)cp;
		*sp = m_sPlayerY;
		cp += 2;
		*cp = cDir;
		cp++;
		switch (wCommand) {
		case DEF_COMMONTYPE_BUILDITEM:
			memcpy(cp, pString, 20);
			cp += 20;
			*cp = (char)m_stDialogBoxInfo[26].sV1;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV2;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV3;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV4;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV5;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV6;
			cp++;
			iRet = m_pGSock->iSendMsg(cMsg, 37);
			break;

		case DEF_COMMONTYPE_REQ_CREATEPORTION:
			*cp = (char)m_stDialogBoxInfo[26].sV1;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV2;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV3;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV4;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV5;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV6;
			cp++;
			iRet = m_pGSock->iSendMsg(cMsg, 18);
			break;

		//Crafting
		case DEF_COMMONTYPE_CRAFTITEM:
			memcpy(cp, "                    ", 20);
			cp += 20;
			*cp = (char)m_stDialogBoxInfo[26].sV1;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV2;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV3;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV4;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV5;
			cp++;
			*cp = (char)m_stDialogBoxInfo[26].sV6;
			cp++;
			iRet = m_pGSock->iSendMsg(cMsg, 37);
			break;

		// Create Slate Request - Diuuude
		case DEF_COMMONTYPE_REQ_CREATESLATE:
			*cp = (char)m_stDialogBoxInfo[40].sV1;
			cp++;
			*cp = (char)m_stDialogBoxInfo[40].sV2;
			cp++;
			*cp = (char)m_stDialogBoxInfo[40].sV3;
			cp++;
			*cp = (char)m_stDialogBoxInfo[40].sV4;
			cp++;
			*cp = (char)m_stDialogBoxInfo[40].sV5;
			cp++;
			*cp = (char)m_stDialogBoxInfo[40].sV6;
			cp++;
			iRet = m_pGSock->iSendMsg(cMsg, 18);
			break;

		default:
			if (pString == NULL)
			{	ip = (int *)cp;
				*ip = iV1;
				cp += 4;
				ip = (int *)cp;
				*ip = iV2;
				cp += 4;
				ip = (int *)cp;
				*ip = iV3;
				cp += 4;
				dwp = (DWORD *)cp;
				*dwp = dwTime;
				cp += 4;
				iRet = m_pGSock->iSendMsg(cMsg, 23 +4);
			}else
			{	ip = (int *)cp;
				*ip = iV1;
				cp += 4;
				ip = (int *)cp;
				*ip = iV2;
				cp += 4;
				ip = (int *)cp;
				*ip = iV3;
				cp += 4;
				memcpy(cp, pString, 30);
				cp += 30;
				ip = (int *)cp;
				*ip = iV4;
				cp += 4;
				iRet = m_pGSock->iSendMsg(cMsg, 23 + 34);
			}
			break;
		}

		break;

	case MSGID_REQUEST_CREATENEWGUILD:
	case MSGID_REQUEST_DISBANDGUILD:
		// to Game Server
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = DEF_MSGTYPE_CONFIRM;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, m_cPlayerName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, m_cAccountName, 10);
		memcpy(cp, cTxt, 10);
		cp += 10;

		ZeroMemory(szReport, sizeof(szReport));
		sha1.Reset();
		sha1.Update((unsigned char *)m_cAccountPassword, strlen(m_cAccountPassword));
		sha1.Final();
		sha1.ReportHash(szReport, CSHA1::REPORT_HEX_SHORT);
		ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
		memcpy(cTxt, szReport, 40);
		memcpy(cp, cTxt, 40); 
		cp += 40;

		char cTemp[21];
		ZeroMemory(cTemp, sizeof(cTemp));
		memcpy(cTemp, m_cGuildName, 20);
		m_Misc.ReplaceString(cTemp, ' ', '_');
		memcpy(cp, cTemp, 20);
		cp += 20;

		iRet = m_pGSock->iSendMsg(cMsg, 86, cKey);
		break;

	case MSGID_REQUEST_TELEPORT:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = DEF_MSGTYPE_CONFIRM;

		iRet = m_pGSock->iSendMsg(cMsg, 6);

		m_bIsTeleportRequested = TRUE;
		break;

	case MSGID_REQUEST_CIVILRIGHT:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = DEF_MSGTYPE_CONFIRM;

		iRet = m_pGSock->iSendMsg(cMsg, 6);
		break;

	case MSGID_REQUEST_RETRIEVEITEM:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = DEF_MSGTYPE_CONFIRM;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		*cp = (char)iV1;

		iRet = m_pGSock->iSendMsg(cMsg, 7);
		break;

	case MSGID_REQUEST_NOTICEMENT:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		*ip = iV1;
		cp += 4;

		iRet = m_pGSock->iSendMsg(cMsg, 10, cKey);
		break;

	case  MSGID_REQUEST_FIGHTZONE_RESERVE:
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		fightzonenum = (int *)cp;
		*fightzonenum = iV1;
		cp += 4;

		iRet = m_pGSock->iSendMsg(cMsg, 10);
		break;

	case MSGID_STATECHANGEPOINT:
		// Diuuude
		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = NULL;
		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
		*cp = cStateChange1;
		cp++;
		*cp = cStateChange2;
		cp++;
		*cp = cStateChange3;
		cp++;
		iRet = m_pGSock->iSendMsg(cMsg, 12);
		break;

	default:
		if (m_bIsTeleportRequested == TRUE) return FALSE;

		dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
		*dwp = dwMsgID;
		wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
		*wp = wCommand;

		cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

		sp = (short *)cp;
		*sp = m_sPlayerX;
		cp += 2;

		sp = (short *)cp;
		*sp = m_sPlayerY;
		cp += 2;

		*cp = cDir;
		cp++;

		sp  = (short *)cp;
		*sp = (short)iV1;
		cp += 2;

		sp  = (short *)cp;
		*sp = (short)iV2;
		cp += 2;

		sp  = (short *)cp;
		*sp = (short)iV3;
		cp += 2;
		if ((wCommand == DEF_OBJECTATTACK) || (wCommand == DEF_OBJECTATTACKMOVE))
		{	sp  = (short *)cp;
			*sp = (short)iV4;
			cp += 2;
			dwp = (DWORD *)cp;
			*dwp = dwTime;
			cp += 4;
			iRet = m_pGSock->iSendMsg(cMsg, 19 +4);
		}else
		{	dwp = (DWORD *)cp;
			*dwp = dwTime;
			cp += 4;

			iRet = m_pGSock->iSendMsg(cMsg, 17 +4); //v2.171
		}
		m_cCommandCount++;
		break;
	}
	switch (iRet) {
	case DEF_XSOCKEVENT_SOCKETCLOSED:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_QUENEFULL:
		ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
		delete m_pGSock;
		m_pGSock = NULL;
		break;

	case DEF_XSOCKEVENT_CRITICALERROR:
		delete m_pGSock;
		m_pGSock = NULL;
		if (G_pCalcSocket != NULL) {
			delete G_pCalcSocket;
			G_pCalcSocket = NULL;
		}
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
		break;
	}
	return TRUE;
}


void CGame::DrawObjects(short sPivotX, short sPivotY, short sDivX, short sDivY, short sModX, short sModY, short msX, short msY)
{int ix, iy, indexX, indexY, dX, dY, iDvalue;
 char cItemColor;
 BOOL bIsPlayerDrawed = FALSE;
 BOOL bContact = FALSE;
 BOOL bRet = FALSE;
 short sItemSprite, sItemSpriteFrame, sObjSpr, sObjSprFrame, sDynamicObject, sDynamicObjectFrame;
 static DWORD dwMCAnimTime = G_dwGlobalTime;
 static short sMCAnimFrame = 1;
// Xmas
 static int ix1[100];
 static int iy2[100];
 static int iXmasTreeBulbDelay = 76;
 int idelay = 75;

	if( sDivY < 0 || sDivX < 0) return ;
	m_sMCX = NULL;
	m_sMCY = NULL;
	ZeroMemory(m_cMCName, sizeof(m_cMCName));

	//dwTime = G_dwGlobalTime;
	DWORD dwTime = m_dwCurTime;
	m_stMCursor.sCursorFrame = 0;

	indexY = sDivY + sPivotY - 7;
	for (iy = -sModY-224; iy <= 427+352; iy += 32)
	{	indexX = sDivX + sPivotX-4;
		for (ix = -sModX-128 ; ix <= 640 + 128; ix += 32)
		{	sDynamicObject = NULL;
			bRet = FALSE;
			if ((ix >= -sModX) && (ix <= 640+16) && (iy >= -sModY) && (iy <= 427+32+16))
			{	_tmp_wObjectID = _tmp_sOwnerType = _tmp_sAppr1 = _tmp_sAppr2 = _tmp_sAppr3 = _tmp_sAppr4 = _tmp_iStatus = NULL;
				_tmp_cDir = _tmp_cFrame = 0;
				_tmp_iEffectType = _tmp_iEffectFrame = _tmp_iChatIndex = 0;
				ZeroMemory(_tmp_cName, sizeof(_tmp_cName));
				if ((indexX < m_pMapData->m_sPivotX) || (indexX > m_pMapData->m_sPivotX + MAPDATASIZEX) ||
					(indexY < m_pMapData->m_sPivotY) || (indexY > m_pMapData->m_sPivotY + MAPDATASIZEY))
				{	sItemSprite = NULL;
					sItemSpriteFrame = NULL;
					bRet = FALSE;
					cItemColor = NULL;
				}else
				{	_tmp_dX = dX = indexX - m_pMapData->m_sPivotX;
					_tmp_dY = dY = indexY - m_pMapData->m_sPivotY;
					_tmp_wObjectID  = m_pMapData->m_pData[dX][dY].m_wDeadObjectID;
					_tmp_sOwnerType = m_pMapData->m_pData[dX][dY].m_sDeadOwnerType;
					_tmp_cDir       = m_pMapData->m_pData[dX][dY].m_cDeadDir;
					_tmp_sAppr1     = m_pMapData->m_pData[dX][dY].m_sDeadAppr1;
					_tmp_sAppr2     = m_pMapData->m_pData[dX][dY].m_sDeadAppr2;
					_tmp_sAppr3     = m_pMapData->m_pData[dX][dY].m_sDeadAppr3;
					_tmp_sAppr4     = m_pMapData->m_pData[dX][dY].m_sDeadAppr4;
					_tmp_iApprColor = m_pMapData->m_pData[dX][dY].m_iDeadApprColor;
					_tmp_cFrame     = m_pMapData->m_pData[dX][dY].m_cDeadOwnerFrame;
					_tmp_iChatIndex = m_pMapData->m_pData[dX][dY].m_iDeadChatMsg;
					_tmp_iStatus    = m_pMapData->m_pData[dX][dY].m_iDeadStatus;
					strcpy(_tmp_cName, m_pMapData->m_pData[dX][dY].m_cDeadOwnerName);
					sItemSprite      = m_pMapData->m_pData[dX][dY].m_sItemSprite;
					sItemSpriteFrame = m_pMapData->m_pData[dX][dY].m_sItemSpriteFrame;
					cItemColor       = m_pMapData->m_pData[dX][dY].m_cItemColor;
					sDynamicObject      = m_pMapData->m_pData[dX][dY].m_sDynamicObjectType;
					sDynamicObjectFrame = (short)m_pMapData->m_pData[dX][dY].m_cDynamicObjectFrame;
					cDynamicObjectData1 = m_pMapData->m_pData[dX][dY].m_cDynamicObjectData1;
					cDynamicObjectData2 = m_pMapData->m_pData[dX][dY].m_cDynamicObjectData2;
					cDynamicObjectData3 = m_pMapData->m_pData[dX][dY].m_cDynamicObjectData3;
					cDynamicObjectData4 = m_pMapData->m_pData[dX][dY].m_cDynamicObjectData4;
					bRet = TRUE;
			 	}

				if ((bRet == TRUE) && (sItemSprite != 0))
				{	if (cItemColor == 0)
						 m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT + sItemSprite]->PutSpriteFast(ix, iy, sItemSpriteFrame, dwTime);
					else
					{	switch (sItemSprite) {
						case 1: // Swds
						case 2: // Bows
						case 3: // Shields
						case 15: // Axes hammers
							m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT + sItemSprite]->PutSpriteRGB(ix, iy
								, sItemSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
							break;
						default:
							m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT + sItemSprite]->PutSpriteRGB(ix, iy
								, sItemSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
							break;
					}	}

					if ((ix - 13 < msX)	&& (ix + 13 > msX) && (iy - 13 < msY) && (iy + 13 > msY))
					{	if ((dwTime - dwMCAnimTime)	> 200)
						{	dwMCAnimTime = dwTime;
							if (sMCAnimFrame == 1)
								 sMCAnimFrame = 2;
							else sMCAnimFrame = 1;
						}
						m_stMCursor.sCursorFrame  = sMCAnimFrame;
				}	}

				if ((bRet == TRUE) && (_tmp_wObjectID != NULL))
				{	bContact = DrawObject_OnDead(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
				}

				if ((bContact == TRUE) && (msY <= 431))
				{	m_sMCX = indexX;
					m_sMCY = indexY;
					sFocusX = ix;
					sFocusY = iy;
					sFocusOwnerType = _tmp_sOwnerType;
					cFocusAction = DEF_OBJECTDEAD;
					wFocusObjectID = _tmp_wObjectID;
					cFocusFrame  = _tmp_cFrame;
					cFocusDir    = _tmp_cDir;
					sFocusAppr1  = _tmp_sAppr1;
					sFocusAppr2  = _tmp_sAppr2;
					sFocusAppr3  = _tmp_sAppr3;
					sFocusAppr4  = _tmp_sAppr4;
					iFocusApprColor = _tmp_iApprColor;
					iFocuiStatus = _tmp_iStatus;
					ZeroMemory(cFocusName, sizeof(cFocusName));
					strcpy(cFocusName, _tmp_cName);
					ZeroMemory(m_cMCName, sizeof(m_cMCName));
					strcpy(m_cMCName,  _tmp_cName);
					sFocus_dX = _tmp_dX;
					sFocus_dY = _tmp_dY;
					bContact = FALSE;
				}

				_tmp_wObjectID = _tmp_sOwnerType = _tmp_sAppr1 = _tmp_sAppr2 = _tmp_sAppr3 = _tmp_sAppr4 = _tmp_iStatus = NULL;
				_tmp_cFrame = _tmp_cDir = 0;
				_tmp_iEffectType = _tmp_iEffectFrame = _tmp_iApprColor = _tmp_iChatIndex = 0;
				ZeroMemory(_tmp_cName, sizeof(_tmp_cName));

				if ((indexX < m_pMapData->m_sPivotX) || (indexX > m_pMapData->m_sPivotX + MAPDATASIZEX) ||
					(indexY < m_pMapData->m_sPivotY) || (indexY > m_pMapData->m_sPivotY + MAPDATASIZEY))
				{	sItemSprite = NULL;
					bRet = FALSE;
				}else
				{	_tmp_dX = dX = indexX - m_pMapData->m_sPivotX; // v2.171 2002-6-14
					_tmp_dY = dY = indexY - m_pMapData->m_sPivotY; // v2.171 2002-6-14
					_tmp_wObjectID  = m_pMapData->m_pData[dX][dY].m_wObjectID;
					_tmp_sOwnerType = m_pMapData->m_pData[dX][dY].m_sOwnerType;
					_tmp_cAction    = m_pMapData->m_pData[dX][dY].m_cOwnerAction;
					_tmp_iStatus    = m_pMapData->m_pData[dX][dY].m_iStatus;
					_tmp_cDir       = m_pMapData->m_pData[dX][dY].m_cDir;
					_tmp_sAppr1     = m_pMapData->m_pData[dX][dY].m_sAppr1;
					_tmp_sAppr2     = m_pMapData->m_pData[dX][dY].m_sAppr2;
					_tmp_sAppr3     = m_pMapData->m_pData[dX][dY].m_sAppr3;
					_tmp_sAppr4     = m_pMapData->m_pData[dX][dY].m_sAppr4;
					_tmp_iApprColor = m_pMapData->m_pData[dX][dY].m_iApprColor; // v1.4
					_tmp_cFrame     = m_pMapData->m_pData[dX][dY].m_cOwnerFrame;
					_tmp_iChatIndex = m_pMapData->m_pData[dX][dY].m_iChatMsg;
					_tmp_iEffectType  = m_pMapData->m_pData[dX][dY].m_iEffectType;
					_tmp_iEffectFrame = m_pMapData->m_pData[dX][dY].m_iEffectFrame;

					strcpy(_tmp_cName, m_pMapData->m_pData[dX][dY].m_cOwnerName);
					bRet = TRUE;

					if (m_iIlusionOwnerH != NULL)
					{	if ((strcmp(_tmp_cName, m_cPlayerName) != 0) && (_tmp_sOwnerType < 10))
						{	_tmp_sOwnerType = m_cIlusionOwnerType;
							_tmp_iStatus    = m_iStatus_IE;
							_tmp_sAppr1     = m_sAppr1_IE;
							_tmp_sAppr2     = m_sAppr2_IE;
							_tmp_sAppr3     = m_sAppr3_IE;
							_tmp_sAppr4     = m_sAppr4_IE;
							_tmp_iApprColor = m_iApprColor_IE;
			 	}	}	}

				if ((bRet == TRUE) && (strlen(_tmp_cName) > 0))
				{	_tmp_dx = 0;
					_tmp_dy = 0;
					switch (_tmp_cAction) {
					case DEF_OBJECTSTOP:
						bContact = DrawObject_OnStop(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTMOVE:
						bContact = DrawObject_OnMove(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTDAMAGEMOVE:
						bContact = DrawObject_OnDamageMove(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTRUN:
						bContact = DrawObject_OnRun(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTATTACK:
						bContact = DrawObject_OnAttack(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTATTACKMOVE:
						bContact = DrawObject_OnAttackMove(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTMAGIC:
						bContact = DrawObject_OnMagic(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTGETITEM:
						bContact = DrawObject_OnGetItem(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTDAMAGE:
						bContact = DrawObject_OnDamage(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;

					case DEF_OBJECTDYING:
						bContact = DrawObject_OnDying(indexX, indexY, ix, iy, FALSE, dwTime, msX, msY);
						break;
					}

					if ((bContact == TRUE) && (msY <= 431))
					{	m_sMCX = indexX;
						m_sMCY = indexY;
						sFocusX = ix;
						sFocusY = iy;
						wFocusObjectID = _tmp_wObjectID;
						sFocusOwnerType = _tmp_sOwnerType;
						cFocusAction = _tmp_cAction;
						cFocusFrame  = _tmp_cFrame;
						cFocusDir    = _tmp_cDir;
						sFocusAppr1  = _tmp_sAppr1;
						sFocusAppr2  = _tmp_sAppr2;
						sFocusAppr3  = _tmp_sAppr3;
						sFocusAppr4  = _tmp_sAppr4;
						iFocusApprColor = _tmp_iApprColor; // v1.4
						iFocuiStatus = _tmp_iStatus;
						ZeroMemory(cFocusName, sizeof(cFocusName));
						strcpy(cFocusName, _tmp_cName);
						ZeroMemory(m_cMCName, sizeof(m_cMCName));
						strcpy(m_cMCName,  _tmp_cName);
						sFocus_dX = _tmp_dX; // v2.171
						sFocus_dY = _tmp_dY; // v2.171
						bContact = FALSE;
					}

					if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0)
					{	if (m_bIsObserverMode == FALSE)
						{	m_sViewDstX = (indexX*32) - 288 - 32;
							m_sViewDstY = (indexY*32) - 224;
						}
						SetRect(&m_rcPlayerRect, m_rcBodyRect.left, m_rcBodyRect.top, m_rcBodyRect.right, m_rcBodyRect.bottom);
						bIsPlayerDrawed = TRUE;
		   	}	}	}

			// CLEROTH
			sObjSpr      = m_pMapData->m_tile[indexX][indexY].m_sObjectSprite;
			sObjSprFrame = m_pMapData->m_tile[indexX][indexY].m_sObjectSpriteFrame;

			if (sObjSpr != 0)
			{	if ((sObjSpr < 100) || (sObjSpr >= 200))
				{	switch (sObjSpr) {
					case 200:
					case 223:
						m_pTileSpr[sObjSpr]->PutShadowSprite(ix - 16, iy - 16, sObjSprFrame, dwTime);
						break;

					case 224:
						switch (sObjSprFrame) {
						case 24:
						case 34:
						case 35:
						case 36:
						case 37:
						case 38:
							break;
						default:
							m_pTileSpr[sObjSpr]->PutShadowSprite(ix - 16, iy - 16, sObjSprFrame, dwTime);
							break;
					}	}
					if (m_cDetailLevel == 0) // Special Grass & Flowers
					{	if ((sObjSpr != 6) && (sObjSpr != 9))
							m_pTileSpr[sObjSpr]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
					}else
					{	m_pTileSpr[sObjSpr]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
					}

					switch (sObjSpr) {
					case 223:
						if (sObjSprFrame == 4)
						{	if (G_cSpriteAlphaDegree == 2) //nuit
							{	int iDvalue1 = -1*(rand() % 5);
								int iDvalue2 = -1*(rand() % 5);
								int iDvalue3 = -1*(rand() % 5);
								m_pEffectSpr[0]->PutTransSpriteRGB(ix+2 -17,  iy - 147 -15, 1, iDvalue1, iDvalue1, iDvalue1, dwTime);
								m_pEffectSpr[0]->PutTransSpriteRGB(ix+16 -17, iy - 96 -15,  1, iDvalue2, iDvalue2, iDvalue2, dwTime);
								m_pEffectSpr[0]->PutTransSpriteRGB(ix-19 -17, iy - 126 -15, 1, iDvalue3, iDvalue3, iDvalue3, dwTime);
						}	}
						break;

					case 370: // nuit
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 9) && (G_cSpriteAlphaDegree == 2)) bAddNewEffect(65, m_sViewPointX + ix -16 +30, m_sViewPointY + iy -16 -334, NULL, NULL, NULL, 0);
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 11) && (G_cSpriteAlphaDegree == 2)) bAddNewEffect(65, m_sViewPointX +ix -16 +17, m_sViewPointY + iy -16 -300, NULL, NULL, NULL, 0);
						break;

					case 374: // nuit
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 2) && (G_cSpriteAlphaDegree == 2)) bAddNewEffect(65, m_sViewPointX + ix -7, m_sViewPointY + iy -122, NULL, NULL, NULL, 0);
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 6) && (G_cSpriteAlphaDegree == 2)) bAddNewEffect(65, m_sViewPointX + ix -14, m_sViewPointY + iy -321, NULL, NULL, NULL, 0);
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 7) && (G_cSpriteAlphaDegree == 2)) bAddNewEffect(65, m_sViewPointX +ix +7, m_sViewPointY + iy -356, NULL, NULL, NULL, 0);
						break;

					case 376: // nuit
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 12) && (G_cSpriteAlphaDegree == 2)) {
							bAddNewEffect(65, m_sViewPointX + ix -16, m_sViewPointY + iy -346, NULL, NULL, NULL, 0);
							bAddNewEffect(65, m_sViewPointX + ix +11, m_sViewPointY + iy -308, NULL, NULL, NULL, 0);
						}
						break;

					case 378: // nuit
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 11) && (G_cSpriteAlphaDegree == 2)) bAddNewEffect(65, m_sViewPointX + ix, m_sViewPointY + iy -91, NULL, NULL, NULL, 0);
						break;

					case 382: // nuit
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 9) && (G_cSpriteAlphaDegree == 2)) {
							bAddNewEffect(65, m_sViewPointX + ix +73, m_sViewPointY + iy -264, NULL, NULL, NULL, 0);
							bAddNewEffect(65, m_sViewPointX + ix +23, m_sViewPointY + iy -228, NULL, NULL, NULL, 0);
						}
						break;

					case 429:
						if ( ((dwTime - m_dwEnvEffectTime) > 400) && (sObjSprFrame == 2)) bAddNewEffect(65, m_sViewPointX + ix -15, m_sViewPointY + iy -224, NULL, NULL, NULL, 0);
						break;
					}
				}else // sprites 100..199: Trees and tree shadows
				{	m_pTileSpr[sObjSpr]->_GetSpriteRect(ix - 16, iy - 16, sObjSprFrame);
					if (m_cDetailLevel==0)
					{	if( sObjSpr < 100 + 11 ) m_pTileSpr[100 + 4]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
						else if( sObjSpr < 100 + 23 ) m_pTileSpr[100 + 9]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
						else if( sObjSpr < 100 + 32 ) m_pTileSpr[100 + 23]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
						else m_pTileSpr[100 + 32]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
					}else
					{	if ((bIsPlayerDrawed == TRUE) && (m_pTileSpr[sObjSpr]->m_rcBound.top <= m_rcPlayerRect.top) && (m_pTileSpr[sObjSpr]->m_rcBound.bottom >= m_rcPlayerRect.bottom) &&
							(m_cDetailLevel >= 2) && (m_pTileSpr[sObjSpr]->m_rcBound.left <= m_rcPlayerRect.left) && (m_pTileSpr[sObjSpr]->m_rcBound.right >= m_rcPlayerRect.right))
						{	m_pTileSpr[sObjSpr + 50]->PutFadeSprite(ix , iy , sObjSprFrame, dwTime);
							m_pTileSpr[sObjSpr]->PutTransSprite2(ix - 16, iy - 16, sObjSprFrame, dwTime);
						}else
						{	m_pTileSpr[sObjSpr + 50]->PutSpriteFast(ix , iy , sObjSprFrame, dwTime);
							m_pTileSpr[sObjSpr]->PutSpriteFast(ix - 16, iy - 16, sObjSprFrame, dwTime);
						}
						if (m_bIsXmas == TRUE)
						{	if (G_cSpriteAlphaDegree == 2) // nuit
							{	if( iXmasTreeBulbDelay < 0 || iXmasTreeBulbDelay > idelay + 1) iXmasTreeBulbDelay = 0;
								if( iXmasTreeBulbDelay > idelay )
								{	for (int i = 0; i < 100; i++) {
										ix1[i] = 1*(rand() % 400)-200;
										iy2[i] = -1*(rand() % 300);
									}
									iXmasTreeBulbDelay = 0;
								}	else iXmasTreeBulbDelay++;

								for (int j = 0; j < 100; j++)
								{	if( m_pTileSpr[sObjSpr]->_bCheckCollison(ix-16, iy-16, sObjSprFrame, ix + ix1[j], iy + iy2[j]) )
									{	m_pEffectSpr[66+(j%6)]->PutTransSprite(ix + ix1[j], iy + iy2[j], (iXmasTreeBulbDelay>>2), dwTime);
			}	}	}	}	}	}	}

			// Dynamic Object
			if ( (bRet == TRUE) && (sDynamicObject != NULL) )
			{	switch (sDynamicObject) {
				case DEF_DYNAMICOBJECT_PCLOUD_BEGIN:	// 10
					if (sDynamicObjectFrame >= 0)
						m_pEffectSpr[23]->PutTransSprite50_NoColorKey(ix+(rand() % 2), iy+(rand() % 2), sDynamicObjectFrame, dwTime);
					break;

				case DEF_DYNAMICOBJECT_PCLOUD_LOOP:		// 11
					m_pEffectSpr[23]->PutTransSprite50_NoColorKey(ix+(rand() % 2), iy+(rand() % 2), sDynamicObjectFrame+8, dwTime);
					break;

				case DEF_DYNAMICOBJECT_PCLOUD_END:		// 12
					m_pEffectSpr[23]->PutTransSprite50_NoColorKey(ix+(rand() % 2), iy+(rand() % 2), sDynamicObjectFrame+16, dwTime);
					break;

				case DEF_DYNAMICOBJECT_ICESTORM:		// 8
					iDvalue = (rand() % 5)*(-1);
					m_pEffectSpr[0]->PutTransSpriteRGB(ix, iy, 1, iDvalue, iDvalue, iDvalue, dwTime);
					m_pEffectSpr[13]->PutTransSprite70_NoColorKey(ix, iy, sDynamicObjectFrame, dwTime);
					break;

				case DEF_DYNAMICOBJECT_FIRE:			// 1
				case DEF_DYNAMICOBJECT_FIRE3:			// 14
					switch (rand() % 3) {
					case 0: m_pEffectSpr[0]->PutTransSprite25_NoColorKey(ix, iy, 1, dwTime); break;
					case 1: m_pEffectSpr[0]->PutTransSprite50_NoColorKey(ix, iy, 1, dwTime); break;
					case 2: m_pEffectSpr[0]->PutTransSprite70_NoColorKey(ix, iy, 1, dwTime); break;
					}
					m_pEffectSpr[9]->PutTransSprite70_NoColorKey(ix, iy, sDynamicObjectFrame/3, dwTime);
					break;

				case DEF_DYNAMICOBJECT_FIRE2:			// 13
					switch (rand() % 3) {
					case 0: m_pEffectSpr[0]->PutTransSprite25_NoColorKey(ix, iy, 1, dwTime); break;
					case 1: m_pEffectSpr[0]->PutTransSprite50_NoColorKey(ix, iy, 1, dwTime); break;
					case 2: m_pEffectSpr[0]->PutTransSprite70_NoColorKey(ix, iy, 1, dwTime); break;
					}
					break;

				case DEF_DYNAMICOBJECT_FISH:			// 2
					{	char cTmpDOdir, cTmpDOframe;
						cTmpDOdir   = m_Misc.cCalcDirection(cDynamicObjectData1, cDynamicObjectData2, cDynamicObjectData1 + cDynamicObjectData3, cDynamicObjectData2 + cDynamicObjectData4);
						cTmpDOframe = ((cTmpDOdir-1) * 4) + (rand() % 4);
						m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+0]->PutTransSprite2(ix + cDynamicObjectData1, iy + cDynamicObjectData2, cTmpDOframe, dwTime);
					}
					break;

				case DEF_DYNAMICOBJECT_MINERAL1:		// 4
					if (m_cDetailLevel != 0) m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->PutShadowSprite(ix, iy, 0, dwTime);
					m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->PutSpriteFast(ix, iy, 0, dwTime);
					if (    (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.top != -1)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.top < msY)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.bottom > msY)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.left < msX)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.right > msX) )
					{	m_sMCX = indexX;
						m_sMCY = indexY;
						iFocuiStatus = NULL;
						ZeroMemory(cFocusName, sizeof(cFocusName));
						ZeroMemory(m_cMCName, sizeof(m_cMCName));
					}
					break;

				case DEF_DYNAMICOBJECT_MINERAL2:		// 5
					if (m_cDetailLevel != 0) m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->PutShadowSprite(ix, iy, 1, dwTime);
					m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->PutSpriteFast(ix, iy, 1, dwTime);
					if (   (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.top != -1)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.top < msY)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.bottom > msY)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.left < msX)
						&& (m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+1]->m_rcBound.right > msX) )
					{	m_sMCX = indexX;
						m_sMCY = indexY;
						iFocuiStatus = NULL;
						ZeroMemory(cFocusName, sizeof(cFocusName));
						ZeroMemory(m_cMCName, sizeof(m_cMCName));
					}
					break;

				case DEF_DYNAMICOBJECT_SPIKE:			// 9
					m_pEffectSpr[17]->PutTransSprite70_NoColorKey(ix, iy, sDynamicObjectFrame, dwTime);
					break;

				case DEF_DYNAMICOBJECT_ARESDENFLAG1:  // 6
					m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+2]->PutSpriteFast(ix, iy, sDynamicObjectFrame, dwTime);
					break;

				case DEF_DYNAMICOBJECT_ELVINEFLAG1: // 7
					m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT+2]->PutSpriteFast(ix, iy, sDynamicObjectFrame, dwTime);
					break;
			}	}
			indexX++;
		}
		indexY++;
	}

	if ((dwTime - m_dwEnvEffectTime) > 400) m_dwEnvEffectTime = dwTime;

	if (m_sMCX != NULL)	// CLEROTH - STATUS
	{	if( _iGetFOE(iFocuiStatus) < 0 ) m_stMCursor.sCursorFrame = 3;
		else m_stMCursor.sCursorFrame = 6;

		_tmp_wObjectID  = wFocusObjectID;
		_tmp_sOwnerType = sFocusOwnerType;
		_tmp_cAction    = cFocusAction;
		_tmp_cFrame     = cFocusFrame;
		_tmp_cDir       = cFocusDir;
		_tmp_sAppr1     = sFocusAppr1;
		_tmp_sAppr2     = sFocusAppr2;
		_tmp_sAppr3     = sFocusAppr3;
		_tmp_sAppr4     = sFocusAppr4;
		_tmp_iApprColor = iFocusApprColor; // v1.4
		_tmp_iStatus    = iFocuiStatus;
		strcpy(_tmp_cName, cFocusName);
		_tmp_dX = sFocus_dX; // v2.171
		_tmp_dY = sFocus_dY; // v2.171

		if ( (_tmp_cAction != DEF_OBJECTDEAD) && (_tmp_cFrame < 0) ) return;
		switch (_tmp_cAction) {
		case DEF_OBJECTSTOP:
			DrawObject_OnStop(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;
		case DEF_OBJECTMOVE:
			switch (_tmp_sOwnerType) {
			case 1:
			case 2:
			case 3: // Human M
			case 4:
			case 5:
			case 6: // Human F

			case 28: // Troll.
			case 29: // Ogre
			case 30: // Liche
			case 31: // DD
			case 32: // Uni
			case 33: // WW
			case 43: // LWB
			case 44: // GHK
			case 45: // GHKABS
			case 46: // TK
			case 47: // BG
			case 48: // SK
			case 49: // HC
			case 50: // TW
			case 51: // CP
			case 52: // GG
			case 53: // BB
			case 54: // DE
			case 55: // Rabbit
			case 56: // Cat
			case 57: // Frog
			case 58: // MG
			case 59: // Ettin
			case 60: // Plant
			case 61: // Rudolph
			case 62: // DireBoar
			case 63: // Frost
			case 65: // Ice-Golem
			case 66: // Wyvern
			case 70: // Dragon..........Ajouts par Snoopy
			case 71: // Centaur
			case 72: // ClawTurtle
			case 73: // FireWyvern
			case 74: // GiantCrayfish
			case 75: // Gi Lizard
			case 76: // Gi Tree
			case 77: // Master Orc
			case 78: // Minaus
			case 79: // Nizie
			case 80: // Tentocle
			case 81: // Abaddon
			case 82: // Sorceress
			case 83: // ATK
			case 84: // MasterElf
			case 85: // DSK
			case 86: // HBT
			case 87: // CT
			case 88: // Barbarian
			case 89: // AGC
			case 91: // Gate

		/*	case 15: // ShopKeeper // Ils ont 8 sprites Stop
			case 19: // Gandalf
			case 20: // Howard
			case 24: // Tom
			case 25: // William
			case 26: // Kenedy
			case 90: // Gail*/
				break;

			default: // 10..27
				_tmp_cFrame = _tmp_cFrame * 2; //
				break;
			}

			DrawObject_OnMove(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTDAMAGEMOVE:
			DrawObject_OnDamageMove(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTRUN:
			DrawObject_OnRun(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTATTACK:
			DrawObject_OnAttack(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTATTACKMOVE:
			DrawObject_OnAttackMove(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTMAGIC:
			DrawObject_OnMagic(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTDAMAGE:
			DrawObject_OnDamage(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTDYING: //10
			DrawObject_OnDying(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;

		case DEF_OBJECTDEAD: //101
			DrawObject_OnDead(m_sMCX, m_sMCY, sFocusX, sFocusY, TRUE, dwTime, msX, msY);
			break;
	}	}

	if (m_bIsGetPointingMode == TRUE)
	{	if ( (m_iPointCommandType >= 100) && (m_iPointCommandType < 200) ) // spell
		{	if (m_bCommandAvailable == TRUE)
			{	if( m_sMCX != NULL )
				{	if( _iGetFOE(iFocuiStatus) < 0 )
						m_stMCursor.sCursorFrame = 5;   // Red enemi for spell
					else m_stMCursor.sCursorFrame = 4;  // Blue friend for spell
				}else m_stMCursor.sCursorFrame = 4;     // Blue friend for spell
			}else m_stMCursor.sCursorFrame = 8;
		}else if ( (m_iPointCommandType >= 0) && (m_iPointCommandType < 50) ) // item
		{	m_stMCursor.sCursorFrame = 10;				// hand to grap item
	}	}
}


void CGame::GameRecvMsgHandler(DWORD dwMsgSize, char * pData)
{ DWORD * dwpMsgID;
	dwpMsgID = (DWORD *)(pData + DEF_INDEX4_MSGID);
	switch (*dwpMsgID) {
	case MSGID_RESPONSE_CHARGED_TELEPORT:
		ResponseChargedTeleport(pData);
		break;

	case MSGID_RESPONSE_TELEPORT_LIST:
		ResponseTeleportList(pData);
		break;

	case MSGID_RESPONSE_HELDENIAN_TP_LIST: // Snoopy Heldenian TP
		ResponseHeldenianTeleportList(pData);
		break;

	case MSGID_RESPONSE_NOTICEMENT:
		NoticementHandler(pData);
		break;

	case MSGID_DYNAMICOBJECT:
		DynamicObjectHandler(pData);
		break;

	case MSGID_RESPONSE_INITPLAYER:
		InitPlayerResponseHandler(pData);
		break;

	case MSGID_RESPONSE_INITDATA:
		InitDataResponseHandler(pData);
		break;

	case MSGID_RESPONSE_MOTION:
		MotionResponseHandler(pData);
		break;

	case MSGID_EVENT_COMMON:
		CommonEventHandler(pData);
		break;

	case MSGID_EVENT_MOTION:
		MotionEventHandler(pData);
		break;

	case MSGID_EVENT_LOG:
		LogEventHandler(pData);
		break;

	case MSGID_COMMAND_CHATMSG:
		ChatMsgHandler(pData);
		break;

	case MSGID_PLAYERITEMLISTCONTENTS:
		InitItemList(pData);
		break;

	case MSGID_NOTIFY:
		NotifyMsgHandler(pData);
		break;

	case MSGID_RESPONSE_CREATENEWGUILD:
		CreateNewGuildResponseHandler(pData);
		break;

	case MSGID_RESPONSE_DISBANDGUILD:
		DisbandGuildResponseHandler(pData);
		break;

	case MSGID_PLAYERCHARACTERCONTENTS:
		InitPlayerCharacteristics(pData);
		break;

	case MSGID_RESPONSE_CIVILRIGHT:
		CivilRightAdmissionHandler(pData);
		break;

	case MSGID_RESPONSE_RETRIEVEITEM:
		RetrieveItemHandler(pData);
		break;

	case MSGID_RESPONSE_PANNING:
		ResponsePanningHandler(pData);
		break;

	case MSGID_RESPONSE_FIGHTZONE_RESERVE:
		ReserveFightzoneResponseHandler(pData);
		break;
	}
}


void CGame::ConnectionEstablishHandler(char cWhere)
{
	ChangeGameMode(DEF_GAMEMODE_ONWAITINGRESPONSE);

	switch (cWhere) {
	case DEF_SERVERTYPE_GAME:
		bSendCommand(MSGID_REQUEST_INITPLAYER, NULL, NULL, NULL, NULL, NULL, NULL);
		break;

	case DEF_SERVERTYPE_LOG:
		switch (m_dwConnectMode) {
		case MSGID_REQUEST_LOGIN:
			bSendCommand(MSGID_REQUEST_LOGIN, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		case MSGID_REQUEST_CREATENEWACCOUNT:
			bSendCommand(MSGID_REQUEST_CREATENEWACCOUNT, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		case MSGID_REQUEST_CREATENEWCHARACTER:
			bSendCommand(MSGID_REQUEST_CREATENEWCHARACTER, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		case MSGID_REQUEST_ENTERGAME:
			bSendCommand(MSGID_REQUEST_ENTERGAME, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		case MSGID_REQUEST_DELETECHARACTER:
			bSendCommand(MSGID_REQUEST_DELETECHARACTER, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		case MSGID_REQUEST_CHANGEPASSWORD:
			bSendCommand(MSGID_REQUEST_CHANGEPASSWORD, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		case MSGID_REQUEST_INPUTKEYCODE:
			bSendCommand(MSGID_REQUEST_INPUTKEYCODE, NULL, NULL, NULL, NULL, NULL, NULL);
			break;
		}
		break;
	}
}

void CGame::InitPlayerResponseHandler(char * pData)
{WORD * wp;
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	switch (*wp) {
	case DEF_MSGTYPE_CONFIRM:
		bSendCommand(MSGID_REQUEST_INITDATA, NULL, NULL, NULL, NULL, NULL, NULL);
		ChangeGameMode(DEF_GAMEMODE_ONWAITINGINITDATA);
		break;

	case DEF_MSGTYPE_REJECT:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "3J");
		break;
	}
}

void CGame::UpdateScreen_OnMainMenu()
{ short msX, msY, msZ;
 char cLB, cRB, cMIresult;
 int  iMIbuttonNum;
 static class CMouseInterface * pMI;
 DWORD dwTime = G_dwGlobalTime;

 m_iItemDropCnt = 0;
 m_bItemDrop = FALSE;

	if (m_cGameModeCount == 0)
	{	if (G_pCalcSocket != NULL)
		{	delete G_pCalcSocket;
			G_pCalcSocket = NULL;
		}
		if ( m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING] != NULL )
		{	delete m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING];
			m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING] = NULL;
		}
		EndInputString();
		pMI = new class CMouseInterface;

		// CLEROTH - INTERFACE
		pMI->AddRect(384,177,548,198);
		pMI->AddRect(384,215,548,236);
		pMI->AddRect(384,254,548,275);
		m_DInput.m_sX = 400;
		m_DInput.m_sY = 240;

		m_cCurFocus = 1;
		m_cMaxFocus = 3;

		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	m_DDraw.ClearBackB4();

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_MAINMENU, -1, -1, 0, TRUE);

	// CLEROTH
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);

	if ((msX >= 384) && (msY >= 177) && (msX <= 548) && (msY <= 198)) m_cCurFocus = 1;
	if ((msX >= 384) && (msY >= 215) && (msX <= 548) && (msY <= 236)) m_cCurFocus = 2;
	if ((msX >= 384) && (msY >= 254) && (msX <= 548) && (msY <= 275)) m_cCurFocus = 3;

	switch (m_cCurFocus) {

	case 1:
		m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->PutSpriteFast(384 , 177, 1, dwTime);
		break;
	case 2:
		m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->PutSpriteFast(384, 215, 2, dwTime);
		break;

	case 3:
		m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->PutSpriteFast(384, 254, 3, dwTime);
		break;
	}

	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	//m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(msX, msY, 1, 0, 0, 0, dwTime);

	if (m_cArrowPressed != 0) {
	   	switch (m_cArrowPressed) {
		case 1:
			m_cCurFocus--;
			if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
			break;
		case 3:
			m_cCurFocus++;
			if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;
		}
		m_cArrowPressed = 0;
	}

	if (m_bEnterPressed == TRUE) {
		// Enter
		PlaySound('E', 14, 5);
		m_bEnterPressed = FALSE;
		switch (m_cCurFocus) {
		case 1:
			delete pMI;
			ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER);
			return;
		case 2:
	#ifdef DEF_MAKE_ACCOUNT
			ClearContents_OnSelectCharacter();
			delete pMI;
			//ChangeGameMode(DEF_GAMEMODE_ONAGREEMENT);
			ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
	#else
			GoHomepage();
	#endif
			return;
		case 3:
			delete pMI;
			ChangeGameMode(DEF_GAMEMODE_ONQUIT);
			return;
		}
	}

	DrawVersion(TRUE);

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK) {
		PlaySound('E', 14, 5);
		m_cCurFocus = iMIbuttonNum;
		switch (iMIbuttonNum)
		{
		case 1:
			ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER);
			delete pMI;
			break;

		case 2:
	#ifdef DEF_MAKE_ACCOUNT
			ClearContents_OnSelectCharacter();
			delete pMI;
			//ChangeGameMode(DEF_GAMEMODE_ONAGREEMENT);
			ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
	#else
			GoHomepage();
	#endif
			return;
		case 3:
			delete pMI;
			ChangeGameMode(DEF_GAMEMODE_ONQUIT);
			return;
		}
	}
//	if ((msX >= 112) && (msY >= 150) && (msX <= 247) && (msY <= 191)) m_cCurFocus = 1;
//	if ((msX >= 73) && (msY >= 192) && (msX <= 281) && (msY <= 230)) m_cCurFocus = 2;
//	if ((msX >= 120) && (msY >= 231) && (msX <= 239) && (msY <= 262)) m_cCurFocus = 3;

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::MakeSprite( char* FileName, short sStart, short sCount, bool bAlphaEffect )
{int iTotalimage;
 DWORD nCount;
 char PathName[28];
	wsprintf( PathName, "sprites\\%s.pak", FileName );
	HANDLE m_hPakFile = CreateFile(PathName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( m_hPakFile == INVALID_HANDLE_VALUE ) return;
	SetFilePointer(m_hPakFile, 20, NULL, FILE_BEGIN);
	ReadFile(m_hPakFile, (char *)&iTotalimage, 4, &nCount, NULL);
	for( short i=0 ; i < sCount ; i++ )
	{	if( i < iTotalimage ) m_pSprite[i+sStart] = new class CSprite(m_hPakFile, &m_DDraw, FileName, i, bAlphaEffect);
	}
	CloseHandle(m_hPakFile);
}

void CGame::MakeTileSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect )
{int iTotalimage;
 DWORD nCount;
 char PathName[28];
	wsprintf( PathName, "sprites\\%s.pak", FileName );
	HANDLE m_hPakFile = CreateFile(PathName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( m_hPakFile == INVALID_HANDLE_VALUE ) return;
	SetFilePointer(m_hPakFile, 20, NULL, FILE_BEGIN);
	ReadFile(m_hPakFile, (char *)&iTotalimage, 4, &nCount, NULL);
	for( short i=0 ; i < sCount ; i++ )
	{	if( i < iTotalimage ) m_pTileSpr[i+sStart] = new class CSprite(m_hPakFile, &m_DDraw, FileName, i, bAlphaEffect);
	}
	CloseHandle(m_hPakFile);
}

void CGame::MakeEffectSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect )
{int iTotalimage;
 DWORD nCount;
 char PathName[28];
	wsprintf( PathName, "sprites\\%s.pak", FileName );
	HANDLE m_hPakFile = CreateFile(PathName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( m_hPakFile == INVALID_HANDLE_VALUE ) return;
	SetFilePointer(m_hPakFile, 20, NULL, FILE_BEGIN);
	ReadFile(m_hPakFile, (char *)&iTotalimage, 4, &nCount, NULL);
	for( short i=0 ; i < sCount ; i++ )
	{	if( i < iTotalimage ) m_pEffectSpr[i+sStart] = new class CSprite(m_hPakFile, &m_DDraw, FileName, i, bAlphaEffect);
	}
	CloseHandle(m_hPakFile);
}

void CGame::UpdateScreen_OnLoading(bool bActive)
{
	int i;
	if( bActive ) UpdateScreen_OnLoading_Progress();

	switch( m_cLoading ) {
	case 0:
		{	m_hPakFile = CreateFile("sprites\\interface.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_MOUSECURSOR] = new class CSprite(m_hPakFile, &m_DDraw, "interface", 0, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS] = new class CSprite(m_hPakFile, &m_DDraw, "interface", 1, FALSE);
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\Newmaps.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1] = new class CSprite(m_hPakFile, &m_DDraw, "Newmaps", 0, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2] = new class CSprite(m_hPakFile, &m_DDraw, "Newmaps", 1, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3] = new class CSprite(m_hPakFile, &m_DDraw, "Newmaps", 2, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4] = new class CSprite(m_hPakFile, &m_DDraw, "Newmaps", 3, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5] = new class CSprite(m_hPakFile, &m_DDraw, "Newmaps", 4, FALSE);
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\LoginDialog.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN] = new class CSprite(m_hPakFile, &m_DDraw, "LoginDialog", 0, FALSE);
#ifdef DEF_MAKE_ACCOUNT
				m_pSprite[DEF_SPRID_INTERFACE_ND_NEWACCOUNT] = new class CSprite(m_hPakFile, &m_DDraw, "LoginDialog", 1, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_AGREEMENT] = new class CSprite(m_hPakFile, &m_DDraw, "LoginDialog", 2, FALSE);
#endif
				CloseHandle(m_hPakFile);
			}
#ifdef DEF_MAKE_ACCOUNT			// CLEROTH - ACC - Snoopy: fixed to use without special pak
			m_hPakFile = CreateFile("sprites\\CreateNewAcc.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_INTERFACE_ND_NEWACCOUNT] = new class CSprite(m_hPakFile, &m_DDraw, "CreateNewAcc", 0, FALSE);
				CloseHandle(m_hPakFile);
			}else
			{	m_hPakFile = CreateFile("sprites\\New-Dialog.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
				m_pSprite[DEF_SPRID_INTERFACE_ND_NEWACCOUNT] = new class CSprite(m_hPakFile, &m_DDraw, "New-Dialog", 2, FALSE);
				CloseHandle(m_hPakFile);
			}
#endif
			m_hPakFile = CreateFile("sprites\\New-Dialog.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU] = new class CSprite(m_hPakFile, &m_DDraw, "New-Dialog", 1, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_QUIT] = new class CSprite(m_hPakFile, &m_DDraw, "New-Dialog", 2, FALSE);
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\GameDialog.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_INTERFACE_ND_GAME1] =      new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 0, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2] =      new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 1, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_GAME3] =      new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 2, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4] =      new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 3, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE] =    new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 4, FALSE);
				//m_pSprite[DEF_SPRID_INTERFACE_GUIDEMAP] =      new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 5, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL] = new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 6, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY] =  new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 7, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_SELECTCHAR] = new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 8, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_NEWCHAR] =    new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 9, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_NEWEXCHANGE] = new class CSprite(m_hPakFile, &m_DDraw, "GameDialog", 10, FALSE);
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\DialogText.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_INTERFACE_ND_TEXT] = new class CSprite(m_hPakFile, &m_DDraw, "DialogText", 0, FALSE);
				m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON] = new class CSprite(m_hPakFile, &m_DDraw, "DialogText", 1, FALSE);
				CloseHandle(m_hPakFile);
			}
			MakeSprite( "Telescope", DEF_SPRID_INTERFACE_GUIDEMAP    , 32, FALSE);	  // Snoopy: 20->32
			MakeSprite( "Telescope2", DEF_SPRID_INTERFACE_GUIDEMAP+35, 4 , FALSE); // Snoopy: Ajout.351 (heldenian maps)
			MakeSprite( "monster", DEF_SPRID_INTERFACE_MONSTER, 1, FALSE);
			m_cLoading = 4;
		}
		break;
	case 4:
		{	MakeTileSpr( "maptiles1", 0, 32, TRUE);
			m_hPakFile = CreateFile("sprites\\structures1.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL); //æ»æ≤¥¬ ≈∏¿œ ∑Œµ˘ æ»«—¥Ÿ.2002.09.06ªÛ«œ
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pTileSpr[1 + 50] = new class CSprite(m_hPakFile, &m_DDraw, "structures1",  1, TRUE);
				m_pTileSpr[5 + 50] = new class CSprite(m_hPakFile, &m_DDraw, "structures1",  5, TRUE);
				CloseHandle(m_hPakFile);
			}
			MakeTileSpr( "Sinside1", 70, 27, FALSE);
			MakeTileSpr( "Trees1", 100, 46, TRUE);
			MakeTileSpr( "TreeShadows", 150, 46, TRUE);
			MakeTileSpr( "objects1", 200, 10, TRUE); // snoopy: 8->10
			MakeTileSpr( "objects2", 211, 5, TRUE);
			MakeTileSpr( "objects3", 216, 4, TRUE);
			MakeTileSpr( "objects4", 220, 2, TRUE); //snoopy: 1->2
			m_cLoading = 8;
		}
		break;
	case 8:
		{	MakeTileSpr( "Tile223-225", 223, 3, TRUE);
			MakeTileSpr( "Tile226-229", 226, 4, TRUE);
			MakeTileSpr( "objects5", 230, 9, TRUE);	// Snoopy
			MakeTileSpr( "objects6", 238, 4, TRUE);	// Snoopy
			MakeTileSpr( "objects7", 242, 7, TRUE);	// Snoopy
			MakeTileSpr( "maptiles2", 300, 15, TRUE);//- Index 300
			MakeTileSpr( "maptiles4", 320, 10, TRUE);
			MakeTileSpr( "maptiles5", 330, 19, TRUE);
			MakeTileSpr( "maptiles6", 349, 4, TRUE);
			MakeTileSpr( "maptiles353-361", 353, 9, TRUE);
			MakeTileSpr( "Tile363-366", 363, 4, TRUE);
			MakeTileSpr( "Tile367-367", 367, 1, TRUE); // Add by Snoopy (fountains)
			MakeTileSpr( "Tile370-381", 370, 12, TRUE);// Tile370~381
			MakeTileSpr( "Tile382-387", 382, 6, TRUE);
			MakeTileSpr( "Tile388-402", 388, 15, TRUE);
			m_cLoading = 12;
		}
		break;
	case 12:
		{
			MakeTileSpr( "Tile403-405", 403, 3, TRUE);
			MakeTileSpr( "Tile406-421", 406, 16, TRUE);
			MakeTileSpr( "Tile422-429", 422, 8, TRUE);
			MakeTileSpr( "Tile430-443", 430, 14, TRUE);
			MakeTileSpr( "Tile444-444", 444, 1, TRUE);
			MakeTileSpr( "Tile445-461",	445, 17, TRUE);
			MakeTileSpr( "Tile462-473",	462, 12, TRUE);	// Diuuude
			MakeTileSpr( "Tile474-478",	474, 5, TRUE);	// Diuuude
			MakeTileSpr( "Tile479-488",	479, 10, TRUE);	// Diuuude
			MakeTileSpr( "Tile489-522",	489, 34, TRUE);	// Diuuude Drunken City
			MakeTileSpr( "Tile523-530",	523, 8, TRUE);	// Diuuude Rampart
			MakeTileSpr( "Tile531-540",	531, 10, TRUE);	// Diuuude GodH + Pont
			MakeTileSpr( "Tile541-545",	541, 5, TRUE);	// Diuuude GodH

			// DEF_SPRID_ITEMPACK_PIVOTPOINT+0
			MakeSprite( "item-pack", DEF_SPRID_ITEMPACK_PIVOTPOINT+1, 27, FALSE);
			m_hPakFile = CreateFile("sprites\\item-pack.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT+20] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 17, FALSE); //
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT+21] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 18, FALSE); //
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT+22] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 19, FALSE); // Angels
				CloseHandle(m_hPakFile);
			}

			// DEF_SPRID_ITEMGROUND_PIVOTPOINT+1
			MakeSprite( "item-ground", DEF_SPRID_ITEMGROUND_PIVOTPOINT+1, 19, FALSE);
			m_hPakFile = CreateFile("sprites\\item-ground.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT+20] = new class CSprite(m_hPakFile, &m_DDraw, "item-ground", 17, FALSE);
				m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT+21] = new class CSprite(m_hPakFile, &m_DDraw, "item-ground", 18, FALSE);
				m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT+22] = new class CSprite(m_hPakFile, &m_DDraw, "item-ground", 19, FALSE);//Angels
				CloseHandle(m_hPakFile);
			}
			MakeSprite( "item-dynamic", DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT, 3, FALSE);// Snoopy 2-> 3 (flags)
			m_cLoading = 16;
		}
		break;
	case 16:
		{
			m_hPakFile = CreateFile("sprites\\item-equipM.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 0] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 0, FALSE);	// body
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 1] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 1, FALSE);	// 1-swords
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 2] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 2, FALSE);	// 2-bows
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 3] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 3, FALSE);	// 3-shields
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 4] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 4, FALSE);	// 4-tunics
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 5] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 5, FALSE);	// 5-shoes
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 7] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 6, FALSE);	// 6-berk
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 8] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 7, FALSE);	// 7-hoses
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 9] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 8, FALSE);	// 8-bodyarmor
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 15] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 11, FALSE); // Axe hammer
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 17] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 12, FALSE); // Wands
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 9, FALSE);  // hair
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 10, FALSE); // undies
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 20] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 13, FALSE); // capes
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 21] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipM", 14, FALSE); // helm
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\item-pack.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 16] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 15); // Necks
				//Snoopy: Angels pandents
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 22] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 19); // Angels
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\item-equipW.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 40] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 0, FALSE); // body
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 41] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 1, FALSE); // 1-swords
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 42] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 2, FALSE); // 2-bows
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 43] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 3, FALSE); // 3-shields
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 45] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 4, FALSE); // 4-shoes
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 50] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 5, FALSE); // 5-Soustif
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 51] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 6, FALSE); // 6 berk
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 52] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 7, FALSE); // 7 hose
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 53] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 8, FALSE); // 8-hoses
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 55] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 11, FALSE); // Axe hammer
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 57] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 12, FALSE); // Wands
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 58] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 9, FALSE); // hair
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 59] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 10, FALSE);// undies
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 60] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 13, FALSE);// capes
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 61] = new class CSprite(m_hPakFile, &m_DDraw, "item-equipW", 14, FALSE);// helm
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\item-pack.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 56] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 15);// necks
				//Snoopy: Angels pandents
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 62] = new class CSprite(m_hPakFile, &m_DDraw, "item-pack", 19); // Angels
				CloseHandle(m_hPakFile);
			}
			MakeSprite( "Bm", 500 + 15*8*0, 96, TRUE);// Black Man (Type: 1)
			MakeSprite( "Wm", 500 + 15*8*1, 96, TRUE);// White Man (Type: 2)
			MakeSprite( "Ym", 500 + 15*8*2, 96, TRUE);// Yellow Man (Type: 3)
			m_cLoading = 20;
		}
		break;
	case 20:
		{	MakeSprite( "TutelarAngel1", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50*0, 48, FALSE);//(STR)
			MakeSprite( "TutelarAngel2", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50*1, 48, FALSE);//(DEX)
			MakeSprite( "TutelarAngel3", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50*2, 48, FALSE);//(INT)
			MakeSprite( "TutelarAngel4", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50*3, 48, FALSE);//(MAG)
			MakeSprite( "Bw", 500 + 15*8*3, 96, TRUE);// Black Woman (Type: 4)
			MakeSprite( "Ww", 500 + 15*8*4, 96, TRUE);// White Woman (Type: 5)
			MakeSprite( "Yw", 500 + 15*8*5, 96, TRUE);// Yellow Woman (Type: 6)
			m_cLoading = 24;
		}
		break;
	case 24:
		{	MakeSprite( "slm",		  DEF_SPRID_MOB   + 7*8*0, 40, TRUE);// Slime (Type: 10)
			MakeSprite( "ske",		  DEF_SPRID_MOB   + 7*8*1, 40, TRUE);// Skeleton (Type: 11)
			MakeSprite( "Gol",		  DEF_SPRID_MOB   + 7*8*2, 40, TRUE);// Stone-Golem (Type: 12)
			MakeSprite( "Cyc",		  DEF_SPRID_MOB   + 7*8*3, 40, TRUE);// Cyclops (Type: 13)
			MakeSprite( "Orc",		  DEF_SPRID_MOB   + 7*8*4, 40, TRUE);// Orc (Type: 14)
			MakeSprite( "Shopkpr",	  DEF_SPRID_MOB   + 7*8*5,  8);		// ShopKeeper-Woman (Type: 15)
			MakeSprite( "Ant",		  DEF_SPRID_MOB   + 7*8*6, 40, TRUE);//  Giant-Ant (Type: 16)
			MakeSprite( "Scp",		  DEF_SPRID_MOB   + 7*8*7, 40, TRUE);//  Scorpion (Type: 17)
			MakeSprite( "Zom",		  DEF_SPRID_MOB   + 7*8*8, 40, TRUE);//  Zombie (Type: 18)
			MakeSprite( "Gandlf",	  DEF_SPRID_MOB   + 7*8*9,  8, TRUE);// Gandalf ∏ (Type: 19)
			MakeSprite( "Howard",	  DEF_SPRID_MOB   + 7*8*10, 8, TRUE);// Howard ∫∏∞¸º“ ¡÷¿Œ (Type: 20)
			MakeSprite( "Guard",	  DEF_SPRID_MOB   + 7*8*11, 40, TRUE);// Guard (Type: 21)
			MakeSprite( "Amp",		  DEF_SPRID_MOB   + 7*8*12, 40, TRUE);// Amphis (Type: 22)
			MakeSprite( "Cla",		  DEF_SPRID_MOB   + 7*8*13, 40, TRUE);// Clay-Golem (Type: 23)
			MakeSprite( "tom",		  DEF_SPRID_MOB   + 7*8*14,  8, TRUE);// Tom (Type: 24)
			MakeSprite( "William",	  DEF_SPRID_MOB   + 7*8*15,  8, TRUE);// William (Type: 25)
			m_cLoading = 28;
		}
		break;
	case 28:
		{	MakeSprite( "Kennedy",	  DEF_SPRID_MOB   + 7*8*16,  8, TRUE);// Kennedy (Type: 26)
			MakeSprite( "Helb",		  DEF_SPRID_MOB   + 7*8*17, 40, TRUE);// Hellbound (Type: 27)
			MakeSprite( "Troll",	  DEF_SPRID_MOB   + 7*8*18, 40, TRUE);// Troll (Type: 28)
			MakeSprite( "Orge",		  DEF_SPRID_MOB   + 7*8*19, 40, TRUE);// Orge (Type: 29)
			MakeSprite( "Liche",	  DEF_SPRID_MOB   + 7*8*20, 40, TRUE);// Liche (Type: 30)
			MakeSprite( "Demon",	  DEF_SPRID_MOB   + 7*8*21, 40, TRUE);// Demon (Type: 31)
			MakeSprite( "Unicorn",	  DEF_SPRID_MOB   + 7*8*22, 40, TRUE);// Unicorn (Type: 32)
			MakeSprite( "WereWolf",	  DEF_SPRID_MOB   + 7*8*23, 40, TRUE);// WereWolf (Type: 33)
			MakeSprite( "Dummy",	  DEF_SPRID_MOB   + 7*8*24, 40, TRUE);// Dummy (Type: 34)
			m_hPakFile = CreateFile("sprites\\Effect5.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL); // Energy-Ball (Type: 35)
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i < 40; i++)
					m_pSprite[  DEF_SPRID_MOB + i + 7*8*25] = new class CSprite(m_hPakFile, &m_DDraw, "Effect5", 0, TRUE);

				CloseHandle(m_hPakFile);
			}
			m_cLoading = 32;
		}
		break;
	case 32:
		{MakeSprite( "GT-Arrow",		  DEF_SPRID_MOB   + 7*8*26, 40, TRUE);// Arrow-GuardTower (Type: 36)
			MakeSprite( "GT-Cannon",	  DEF_SPRID_MOB   + 7*8*27, 40, TRUE);// Cannon-GuardTower (Type: 37)
			MakeSprite( "ManaCollector",  DEF_SPRID_MOB   + 7*8*28, 40, TRUE);// Mana Collector (Type: 38)
			MakeSprite( "Detector",		  DEF_SPRID_MOB   + 7*8*29, 40, TRUE);// Detector (Type: 39)
			MakeSprite( "ESG",			  DEF_SPRID_MOB   + 7*8*30, 40, TRUE);// ESG (Type: 40)
			MakeSprite( "GMG",			  DEF_SPRID_MOB   + 7*8*31, 40, TRUE);// GMG (Type: 41)
			MakeSprite( "ManaStone",	  DEF_SPRID_MOB   + 7*8*32, 40, TRUE);// ManaStone (Type: 42)
			MakeSprite( "LWB",			  DEF_SPRID_MOB   + 7*8*33, 40, TRUE);// Light War Beetle (Type: 43)
			MakeSprite( "GHK",		  DEF_SPRID_MOB   + 7*8*34, 40, TRUE);// God's Hand Knight (Type: 44)
			MakeSprite( "GHKABS",	  DEF_SPRID_MOB   + 7*8*35, 40, TRUE);// God's Hand Knight with Armored Battle Steed (Type: 45)
			MakeSprite( "TK",		  DEF_SPRID_MOB   + 7*8*36, 40, TRUE);// Temple Knight (Type: 46)
			MakeSprite( "BG",		  DEF_SPRID_MOB   + 7*8*37, 40, TRUE);// Battle Golem (Type: 47)
			m_cLoading = 36;
		}
		break;
	case 36:
		{
			MakeSprite( "Stalker",	  DEF_SPRID_MOB   + 7*8*38, 40, TRUE);// Stalker (Type: 48)
			MakeSprite( "Hellclaw",	  DEF_SPRID_MOB   + 7*8*39, 40, TRUE);// Hellclaw (Type: 49)
			MakeSprite( "Tigerworm",  DEF_SPRID_MOB   + 7*8*40, 40, TRUE);// Tigerworm (Type: 50)
			MakeSprite( "Catapult",	  DEF_SPRID_MOB   + 7*8*41, 40, TRUE);// Catapult (Type: 51)
			MakeSprite( "Gagoyle",	  DEF_SPRID_MOB   + 7*8*42, 40, TRUE);// Gargoyle (Type: 52)
			MakeSprite( "Beholder",	  DEF_SPRID_MOB   + 7*8*43, 40, TRUE);// Beholder (Type: 53)
			MakeSprite( "DarkElf",	  DEF_SPRID_MOB   + 7*8*44, 40, TRUE);// Dark-Elf (Type: 54)
			MakeSprite( "Bunny",	  DEF_SPRID_MOB   + 7*8*45, 40, TRUE);// Bunny (Type: 55)
			MakeSprite( "Cat",		  DEF_SPRID_MOB   + 7*8*46, 40, TRUE);// Cat (Type: 56)
			MakeSprite( "GiantFrog",  DEF_SPRID_MOB   + 7*8*47, 40, TRUE);// GiantFrog (Type: 57)
			MakeSprite( "MTGiant",	  DEF_SPRID_MOB   + 7*8*48, 40, TRUE);// Mountain Giant (Type: 58)
			m_cLoading = 40;
		}
		break;
	case 40:
		{	MakeSprite( "Ettin",	  DEF_SPRID_MOB   + 7*8*49, 40, TRUE);// Ettin (Type: 59)
			MakeSprite( "CanPlant",	  DEF_SPRID_MOB   + 7*8*50, 40, TRUE);// Cannibal Plant (Type: 60)
			MakeSprite( "Rudolph",	  DEF_SPRID_MOB   + 7*8*51, 40, TRUE);// Rudolph (Type: 61)
			MakeSprite( "DireBoar",	  DEF_SPRID_MOB   + 7*8*52, 40, TRUE);// Boar (Type: 62)
			MakeSprite( "frost",	  DEF_SPRID_MOB   + 7*8*53, 40, TRUE);// Frost (Type: 63)
			MakeSprite( "Crop",		  DEF_SPRID_MOB   + 7*8*54, 40, TRUE);// Crop(Type: 64)
			MakeSprite( "IceGolem",	  DEF_SPRID_MOB   + 7*8*55, 40, TRUE);// IceGolem (Type: 65)
			MakeSprite( "Wyvern",	  DEF_SPRID_MOB   + 7*8*56, 24, TRUE);// Wyvern (Type: 66)
			MakeSprite( "McGaffin",	  DEF_SPRID_MOB   + 7*8*57, 16, TRUE);// McGaffin (Type: 67)
			MakeSprite( "Perry",	  DEF_SPRID_MOB   + 7*8*58, 16, TRUE);// Perry (Type: 68)
			MakeSprite( "Devlin",	  DEF_SPRID_MOB   + 7*8*59, 16, TRUE);// Devlin (Type: 69)
			MakeSprite( "Barlog",		  DEF_SPRID_MOB   + 7*8*60, 40, TRUE);// Barlog (Type: 70)
			MakeSprite( "Centaurus",	  DEF_SPRID_MOB   + 7*8*61, 40, TRUE);// Centaurus (Type: 71)
			MakeSprite( "ClawTurtle",	  DEF_SPRID_MOB   + 7*8*62, 40, TRUE);// Claw-Turtle (Type: 72)
			MakeSprite( "FireWyvern",	  DEF_SPRID_MOB   + 7*8*63, 24, TRUE);// Fire-Wyvern (Type: 73)
			MakeSprite( "GiantCrayfish",  DEF_SPRID_MOB   + 7*8*64, 40, TRUE);// Giant-Crayfish (Type: 74)
			MakeSprite( "GiantLizard",	  DEF_SPRID_MOB   + 7*8*65, 40, TRUE);// Giant-Lizard (Type: 75)
			m_cLoading = 44;
		}
		break;
	case 44:
		{	// New NPCs - Diuuude - fixed by Snoopy
			MakeSprite( "GiantPlant",	  DEF_SPRID_MOB   + 7*8*66, 40, TRUE);// Giant-Plant (Type: 76)
			MakeSprite( "MasterMageOrc",  DEF_SPRID_MOB   + 7*8*67, 40, TRUE);// MasterMage-Orc (Type: 77)
			MakeSprite( "Minotaurs",	  DEF_SPRID_MOB   + 7*8*68, 40, TRUE);// Minotaurs (Type: 78)
			MakeSprite( "Nizie",		  DEF_SPRID_MOB   + 7*8*69, 40, TRUE);// Nizie (Type: 79)
			MakeSprite( "Tentocle",		  DEF_SPRID_MOB   + 7*8*70, 40, TRUE);// Tentocle (Type: 80)
			MakeSprite( "yspro",		  DEF_SPRID_MOB   + 7*8*71, 32, TRUE);// Abaddon (Type: 81)
			MakeSprite( "Sorceress",	  DEF_SPRID_MOB   + 7*8*72, 40, TRUE);// Sorceress (Type: 82)
			MakeSprite( "TPKnight",		  DEF_SPRID_MOB   + 7*8*73, 40, TRUE);// TPKnight (Type: 83)
			MakeSprite( "ElfMaster",	  DEF_SPRID_MOB   + 7*8*74, 40, TRUE);// ElfMaster (Type: 84)
			MakeSprite( "DarkKnight",	  DEF_SPRID_MOB   + 7*8*75, 40, TRUE);// DarkKnight (Type: 85)
			MakeSprite( "HBTank",		  DEF_SPRID_MOB   + 7*8*76, 32, TRUE);// HeavyBattleTank (Type: 86)
			MakeSprite( "CBTurret",		  DEF_SPRID_MOB   + 7*8*77, 32, TRUE);// CBTurret (Type: 87)
			MakeSprite( "Babarian",		  DEF_SPRID_MOB   + 7*8*78, 40, TRUE);// Babarian (Type: 88)
			MakeSprite( "ACannon",		  DEF_SPRID_MOB   + 7*8*79, 32, TRUE);// ACannon (Type: 89)
			m_cLoading = 48;
		}
		break;
	case 48:
		{	MakeSprite( "Gail",			  DEF_SPRID_MOB   + 7*8*80, 8, TRUE); // Gail (Type: 90)
			MakeSprite( "Gate",			  DEF_SPRID_MOB   + 7*8*81, 24, TRUE);// Heldenian Gate (Type: 91)/**/
			m_hPakFile = CreateFile("sprites\\Mpt.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*0] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*0, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*1] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*1, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*2] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*2, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*3] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*3, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*4] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*4, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*5] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*5, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*6] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*6, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15*7] = new class CSprite(m_hPakFile, &m_DDraw, "Mpt", i + 12*7, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_cLoading = 52;
		}
		break;

	case 52:
		{	m_hPakFile = CreateFile("sprites\\Mhr.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*0] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*0, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*1] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*1, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*2] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*2, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*3] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*3, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*4] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*4, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*5] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*5, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*6] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*6, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15*7] = new class CSprite(m_hPakFile, &m_DDraw, "Mhr", i + 12*7, TRUE);
				CloseHandle(m_hPakFile);
			}
			MakeSprite( "MLArmor",	DEF_SPRID_BODYARMOR_M + 15*1, 12, TRUE);
			MakeSprite( "MCMail",	DEF_SPRID_BODYARMOR_M + 15*2, 12, TRUE);
			MakeSprite( "MSMail",	DEF_SPRID_BODYARMOR_M + 15*3, 12, TRUE);
			MakeSprite( "MPMail",	DEF_SPRID_BODYARMOR_M + 15*4, 12, TRUE);
			MakeSprite( "Mtunic",	DEF_SPRID_BODYARMOR_M + 15*5, 12, TRUE);
			MakeSprite( "MRobe1",	DEF_SPRID_BODYARMOR_M + 15*6, 12, TRUE);
			MakeSprite( "MSanta",	DEF_SPRID_BODYARMOR_M + 15*7, 12, TRUE);
			MakeSprite( "MHRobe1",	DEF_SPRID_BODYARMOR_M + 15*10, 12, TRUE); //hero
			MakeSprite( "MHRobe2",	DEF_SPRID_BODYARMOR_M + 15*11, 12, TRUE); //hero
			MakeSprite( "MHPMail1",	DEF_SPRID_BODYARMOR_M + 15*8, 12, TRUE); //hero
			MakeSprite( "MHPMail2",	DEF_SPRID_BODYARMOR_M + 15*9, 12, TRUE); //hero
			MakeSprite( "MShirt",	  DEF_SPRID_BERK_M + 15*1, 12, TRUE);
			MakeSprite( "MHauberk",	  DEF_SPRID_BERK_M + 15*2, 12, TRUE);
			MakeSprite( "MHHauberk1", DEF_SPRID_BERK_M + 15*3, 12, TRUE);
			MakeSprite( "MHHauberk2", DEF_SPRID_BERK_M + 15*4, 12, TRUE);
			m_cLoading = 56;
		}
		break;
	case 56:
		{	MakeSprite( "MTrouser",	DEF_SPRID_LEGG_M + 15*1, 12, TRUE);
			MakeSprite( "MHTrouser",DEF_SPRID_LEGG_M + 15*2, 12, TRUE);
			MakeSprite( "MCHoses",	DEF_SPRID_LEGG_M + 15*3, 12, TRUE);
			MakeSprite( "MLeggings",DEF_SPRID_LEGG_M + 15*4, 12, TRUE);
			MakeSprite( "MHLeggings1",	DEF_SPRID_LEGG_M + 15*5, 12, TRUE); // hero
			MakeSprite( "MHLeggings2",DEF_SPRID_LEGG_M + 15*6, 12, TRUE); // hero
			MakeSprite( "MShoes",	DEF_SPRID_BOOT_M + 15*1, 12, TRUE);
			MakeSprite( "MLBoots",	DEF_SPRID_BOOT_M + 15*2, 12, TRUE);
			m_hPakFile = CreateFile("sprites\\Msw.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*1] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*0, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*2] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*1, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*3] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*2, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*4] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*3, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*6] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*5, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*7] = new class CSprite(m_hPakFile, &m_DDraw,  "Msw", i + 56*6, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*8] = new class CSprite(m_hPakFile, &m_DDraw,  "Msw", i + 56*7, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*9] = new class CSprite(m_hPakFile, &m_DDraw,  "Msw", i + 56*8, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*10] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*9, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*11] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*10, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*12] = new class CSprite(m_hPakFile, &m_DDraw, "Msw", i + 56*11, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_cLoading = 60;
		}
		break;
	case 60:
		{	MakeSprite( "Mswx",			DEF_SPRID_WEAPON_M + 64*5, 56, TRUE);
			MakeSprite( "Msw2",			DEF_SPRID_WEAPON_M + 64*13, 56, TRUE);
            MakeSprite( "Msw3",			DEF_SPRID_WEAPON_M + 64*14, 56, TRUE);
			MakeSprite( "MStormBringer",DEF_SPRID_WEAPON_M + 64*15, 56, TRUE);
			MakeSprite( "MDarkExec",	DEF_SPRID_WEAPON_M + 64*16, 56, TRUE);
			MakeSprite( "MKlonessBlade",DEF_SPRID_WEAPON_M + 64*17, 56, TRUE);
			MakeSprite( "MKlonessAstock",DEF_SPRID_WEAPON_M + 64*18, 56, TRUE);
			MakeSprite( "MDebastator",	DEF_SPRID_WEAPON_M + 64*19, 56, TRUE);
			MakeSprite( "MAxe1",		DEF_SPRID_WEAPON_M + 64*20, 56, TRUE);// Axe
			MakeSprite( "MAxe2",		DEF_SPRID_WEAPON_M + 64*21, 56, TRUE);
			MakeSprite( "MAxe3",		DEF_SPRID_WEAPON_M + 64*22, 56, TRUE);
			MakeSprite( "MAxe4",		DEF_SPRID_WEAPON_M + 64*23, 56, TRUE);
			MakeSprite( "MAxe5",		DEF_SPRID_WEAPON_M + 64*24, 56, TRUE);
			MakeSprite( "MPickAxe1",	DEF_SPRID_WEAPON_M + 64*25, 56, TRUE);
			MakeSprite( "MAxe6",		DEF_SPRID_WEAPON_M + 64*26, 56, TRUE);
			MakeSprite( "Mhoe",			DEF_SPRID_WEAPON_M + 64*27, 56, TRUE);
			MakeSprite( "MKlonessAxe",	DEF_SPRID_WEAPON_M + 64*28, 56, TRUE);
			MakeSprite( "MLightBlade",	DEF_SPRID_WEAPON_M + 64*29, 56, TRUE);
			m_cLoading = 64;
		}
		break;
	case 64:
		{	MakeSprite( "MHammer",		DEF_SPRID_WEAPON_M + 64*30, 56, TRUE);
			MakeSprite( "MBHammer",		DEF_SPRID_WEAPON_M + 64*31, 56, TRUE);
			MakeSprite( "MBabHammer",	DEF_SPRID_WEAPON_M + 64*32, 56, TRUE);
			MakeSprite( "MBShadowSword",DEF_SPRID_WEAPON_M + 64*33, 56, TRUE);
			MakeSprite( "MBerserkWand", DEF_SPRID_WEAPON_M + 64*34, 56, TRUE);
			MakeSprite( "Mstaff1",		DEF_SPRID_WEAPON_M + 64*35, 56, TRUE);// Staff
			MakeSprite( "Mstaff2",		DEF_SPRID_WEAPON_M + 64*36, 56, TRUE);
			MakeSprite( "MStaff3",		DEF_SPRID_WEAPON_M + 64*37, 56, TRUE);
			MakeSprite( "MReMagicWand", DEF_SPRID_WEAPON_M + 64*38, 56, TRUE);
			MakeSprite( "MKlonessWand", DEF_SPRID_WEAPON_M + 64*39, 56, TRUE);
			// Bows 40 41 below
			MakeSprite( "MDirectBow",	DEF_SPRID_WEAPON_M + 64*42, 56, TRUE);
			MakeSprite( "MFireBow",		DEF_SPRID_WEAPON_M + 64*43, 56, TRUE);
			m_cLoading = 68;
		}
		break;
	case 68:
		{	MakeSprite( "Mbo", DEF_SPRID_WEAPON_M + 64*40, 56, TRUE);
			m_hPakFile = CreateFile("sprites\\Mbo.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64*41] = new class CSprite(m_hPakFile, &m_DDraw, "Mbo", i + 56*1, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_hPakFile = CreateFile("sprites\\Msh.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*1] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*0, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*2] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*1, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*3] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*2, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*4] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*3, TRUE);
				for (i = 0; i < 7; i++)	m_pSprite[DEF_SPRID_SHIELD_M + i + 8*5] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*4, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*6] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*5, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*7] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*6, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*8] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*7, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8*9] = new class CSprite(m_hPakFile, &m_DDraw, "Msh", i + 7*8, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_cLoading = 72;
		}
		break;
	case 72:
		{	MakeSprite( "Mmantle01", DEF_SPRID_MANTLE_M + 15*1, 12, TRUE);
			MakeSprite( "Mmantle02", DEF_SPRID_MANTLE_M + 15*2, 12, TRUE);
			MakeSprite( "Mmantle03", DEF_SPRID_MANTLE_M + 15*3, 12, TRUE);
			MakeSprite( "Mmantle04", DEF_SPRID_MANTLE_M + 15*4, 12, TRUE);
			MakeSprite( "Mmantle05", DEF_SPRID_MANTLE_M + 15*5, 12, TRUE);
			MakeSprite( "Mmantle06", DEF_SPRID_MANTLE_M + 15*6, 12, TRUE);
			MakeSprite( "MHelm1", DEF_SPRID_HEAD_M + 15*1, 12, TRUE);
			MakeSprite( "MHelm2", DEF_SPRID_HEAD_M + 15*2, 12, TRUE);
			MakeSprite( "MHelm3", DEF_SPRID_HEAD_M + 15*3, 12, TRUE);
			MakeSprite( "MHelm4", DEF_SPRID_HEAD_M + 15*4, 12, TRUE);
			MakeSprite( "MHCap1", DEF_SPRID_HEAD_M + 15*11, 12, TRUE);
			MakeSprite( "MHCap2", DEF_SPRID_HEAD_M + 15*12, 12, TRUE);
			MakeSprite( "MHHelm1", DEF_SPRID_HEAD_M + 15*9, 12, TRUE);
			MakeSprite( "MHHelm2", DEF_SPRID_HEAD_M + 15*10, 12, TRUE);
			MakeSprite( "NMHelm1", DEF_SPRID_HEAD_M + 15*5, 12, TRUE);
			MakeSprite( "NMHelm2", DEF_SPRID_HEAD_M + 15*6, 12, TRUE);
			MakeSprite( "NMHelm3", DEF_SPRID_HEAD_M + 15*7, 12, TRUE);
			MakeSprite( "NMHelm4", DEF_SPRID_HEAD_M + 15*8, 12, TRUE);
			m_cLoading = 76;
		}
		break;
	case 76:
		{	m_hPakFile = CreateFile("sprites\\Wpt.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*0] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*1] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*2] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12*2, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*3] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12*3, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*4] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12*4, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*5] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12*5, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*6] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12*6, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15*7] = new class CSprite(m_hPakFile, &m_DDraw, "Wpt", i + 12*7, TRUE);
				CloseHandle(m_hPakFile);
			}

			m_hPakFile = CreateFile("sprites\\Whr.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*0] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 0, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*1] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*2] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12*2, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*3] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12*3, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*4] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12*4, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*5] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12*5, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*6] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12*6, TRUE);
				for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15*7] = new class CSprite(m_hPakFile, &m_DDraw, "Whr", i + 12*7, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_cLoading = 80;
		}
		break;
	case 80:
		{
			MakeSprite( "WBodice1", DEF_SPRID_BODYARMOR_W + 15*1, 12, TRUE);
			MakeSprite( "WBodice2", DEF_SPRID_BODYARMOR_W + 15*2, 12, TRUE);
			MakeSprite( "WLArmor",	DEF_SPRID_BODYARMOR_W + 15*3, 12, TRUE);
			MakeSprite( "WCMail",	DEF_SPRID_BODYARMOR_W + 15*4, 12, TRUE);
			MakeSprite( "WSMail",	DEF_SPRID_BODYARMOR_W + 15*5, 12, TRUE);
			MakeSprite( "WPMail",	DEF_SPRID_BODYARMOR_W + 15*6, 12, TRUE);
			MakeSprite( "WRobe1",	DEF_SPRID_BODYARMOR_W + 15*7, 12, TRUE);
			MakeSprite( "WSanta",	DEF_SPRID_BODYARMOR_W + 15*8, 12, TRUE);
			MakeSprite( "WHRobe1",	DEF_SPRID_BODYARMOR_W + 15*11, 12, TRUE); // hero
			MakeSprite( "WHRobe2",	DEF_SPRID_BODYARMOR_W + 15*12, 12, TRUE); // hero
			MakeSprite( "WHPMail1",	DEF_SPRID_BODYARMOR_W + 15*9, 12, TRUE); //hero
			MakeSprite( "WHPMail2",	DEF_SPRID_BODYARMOR_W + 15*10, 12, TRUE); //hero
			MakeSprite( "WChemiss",  DEF_SPRID_BERK_W + 15*1, 12, TRUE);
			MakeSprite( "WShirt",	 DEF_SPRID_BERK_W + 15*2, 12, TRUE);
			MakeSprite( "WHauberk",	 DEF_SPRID_BERK_W + 15*3, 12, TRUE);
			MakeSprite( "WHHauberk1",DEF_SPRID_BERK_W + 15*4, 12, TRUE);
			MakeSprite( "WHHauberk2",DEF_SPRID_BERK_W + 15*5, 12, TRUE);
			MakeSprite( "WSkirt",		DEF_SPRID_LEGG_W + 15*1, 12, TRUE);
			MakeSprite( "WTrouser",		DEF_SPRID_LEGG_W + 15*2, 12, TRUE);
			MakeSprite( "WHTrouser",	DEF_SPRID_LEGG_W + 15*3, 12, TRUE);
			MakeSprite( "WHLeggings1",	DEF_SPRID_LEGG_W + 15*6, 12, TRUE);
			MakeSprite( "WHLeggings2",	DEF_SPRID_LEGG_W + 15*7, 12, TRUE);
			MakeSprite( "WCHoses",		DEF_SPRID_LEGG_W + 15*4, 12, TRUE);
			MakeSprite( "WLeggings",	DEF_SPRID_LEGG_W + 15*5, 12, TRUE);
			MakeSprite( "WShoes",	DEF_SPRID_BOOT_W + 15*1, 12, TRUE);
			MakeSprite( "WLBoots",  DEF_SPRID_BOOT_W + 15*2, 12, TRUE);
			m_cLoading = 84;
		}
		break;
	case 84:
		{	m_hPakFile = CreateFile("sprites\\Wsw.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*1] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*0, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*2] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*1, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*3] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*2, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*4] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*3, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*6] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*5, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*7] = new class CSprite(m_hPakFile, &m_DDraw,  "Wsw", i + 56*6, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*8] = new class CSprite(m_hPakFile, &m_DDraw,  "Wsw", i + 56*7, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*9] = new class CSprite(m_hPakFile, &m_DDraw,  "Wsw", i + 56*8, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*10] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*9, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*11] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*10, TRUE);
				for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*12] = new class CSprite(m_hPakFile, &m_DDraw, "Wsw", i + 56*11, TRUE);
				CloseHandle(m_hPakFile);
			}
			MakeSprite( "Wswx",			DEF_SPRID_WEAPON_W + 64*5, 56, TRUE);
			MakeSprite( "Wsw2",			DEF_SPRID_WEAPON_W + 64*13, 56, TRUE);
            MakeSprite( "Wsw3",			DEF_SPRID_WEAPON_W + 64*14, 56, TRUE); // TheVampire
			MakeSprite( "WStormBringer",DEF_SPRID_WEAPON_W + 64*15, 56, TRUE);
			MakeSprite( "WDarkExec",	DEF_SPRID_WEAPON_W + 64*16, 56, TRUE);
			MakeSprite( "WKlonessBlade",DEF_SPRID_WEAPON_W + 64*17, 56, TRUE);
			MakeSprite( "WKlonessAstock",DEF_SPRID_WEAPON_W + 64*18, 56, TRUE);
			MakeSprite( "WDebastator",	DEF_SPRID_WEAPON_W + 64*19, 56, TRUE);
			m_cLoading = 88;
		}
		break;
	case 88:
		{	MakeSprite( "WAxe1",		DEF_SPRID_WEAPON_W + 64*20, 56, TRUE);// Axe
			MakeSprite( "WAxe2",		DEF_SPRID_WEAPON_W + 64*21, 56, TRUE);
			MakeSprite( "WAxe3",		DEF_SPRID_WEAPON_W + 64*22, 56, TRUE);
			MakeSprite( "WAxe4",		DEF_SPRID_WEAPON_W + 64*23, 56, TRUE);
			MakeSprite( "WAxe5",		DEF_SPRID_WEAPON_W + 64*24, 56, TRUE);
			MakeSprite( "WpickAxe1",	DEF_SPRID_WEAPON_W + 64*25, 56, TRUE);
			MakeSprite( "WAxe6",		DEF_SPRID_WEAPON_W + 64*26, 56, TRUE);
			MakeSprite( "Whoe",			DEF_SPRID_WEAPON_W + 64*27, 56, TRUE);
			MakeSprite( "WKlonessAxe",	DEF_SPRID_WEAPON_W + 64*28, 56, TRUE);
			MakeSprite( "WLightBlade",  DEF_SPRID_WEAPON_W + 64*29, 56, TRUE);
			MakeSprite( "WHammer",		DEF_SPRID_WEAPON_W + 64*30, 56, TRUE);
			MakeSprite( "WBHammer",		DEF_SPRID_WEAPON_W + 64*31, 56, TRUE);
			MakeSprite( "WBabHammer",	DEF_SPRID_WEAPON_W + 64*32, 56, TRUE);
			MakeSprite( "WBShadowSword",DEF_SPRID_WEAPON_W + 64*33, 56, TRUE);
			MakeSprite( "WBerserkWand", DEF_SPRID_WEAPON_W + 64*34, 56, TRUE);
			MakeSprite( "Wstaff1",		DEF_SPRID_WEAPON_W + 64*35, 56, TRUE);// Staff
			MakeSprite( "Wstaff2",		DEF_SPRID_WEAPON_W + 64*36, 56, TRUE);
			MakeSprite( "WStaff3",		DEF_SPRID_WEAPON_W + 64*37, 56, TRUE);
			MakeSprite( "WKlonessWand", DEF_SPRID_WEAPON_W + 64*39, 56, TRUE);
			MakeSprite( "WReMagicWand", DEF_SPRID_WEAPON_W + 64*38, 56, TRUE);
			// bows 40 41 below
			MakeSprite( "WDirectBow",	DEF_SPRID_WEAPON_W + 64*42, 56, TRUE);
			MakeSprite( "WFireBow",		DEF_SPRID_WEAPON_W + 64*43, 56, TRUE);
			m_cLoading = 92;
		}
		break;
	case 92:
		{	MakeSprite( "Wmantle01", DEF_SPRID_MANTLE_W + 15*1, 12, TRUE);
			MakeSprite( "Wmantle02", DEF_SPRID_MANTLE_W + 15*2, 12, TRUE);
			MakeSprite( "Wmantle03", DEF_SPRID_MANTLE_W + 15*3, 12, TRUE);
			MakeSprite( "Wmantle04", DEF_SPRID_MANTLE_W + 15*4, 12, TRUE);
			MakeSprite( "Wmantle05", DEF_SPRID_MANTLE_W + 15*5, 12, TRUE);
			MakeSprite( "Wmantle06", DEF_SPRID_MANTLE_W + 15*6, 12, TRUE);
			MakeSprite( "WHelm1",	 DEF_SPRID_HEAD_W + 15*1, 12, TRUE);
			MakeSprite( "WHelm4",	 DEF_SPRID_HEAD_W + 15*4, 12, TRUE);
			MakeSprite( "WHHelm1",	 DEF_SPRID_HEAD_W + 15*9, 12, TRUE);
			MakeSprite( "WHHelm2",	 DEF_SPRID_HEAD_W + 15*10, 12, TRUE);
			MakeSprite( "WHCap1",	 DEF_SPRID_HEAD_W + 15*11, 12, TRUE);
			MakeSprite( "WHCap2",	 DEF_SPRID_HEAD_W + 15*12, 12, TRUE);
			MakeSprite( "NWHelm1",	 DEF_SPRID_HEAD_W + 15*5, 12, TRUE);
			MakeSprite( "NWHelm2",	 DEF_SPRID_HEAD_W + 15*6, 12, TRUE);
			MakeSprite( "NWHelm3",	 DEF_SPRID_HEAD_W + 15*7, 12, TRUE);
			MakeSprite( "NWHelm4",	 DEF_SPRID_HEAD_W + 15*8, 12, TRUE);
			m_cLoading = 96;
		}
		break;
	case 96:
		{	MakeSprite( "Wbo", DEF_SPRID_WEAPON_W + 64*40, 56, TRUE);// Bow
			m_hPakFile = CreateFile("sprites\\Wbo.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64*41] = new class CSprite(m_hPakFile, &m_DDraw, "Wbo", i + 56*1, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_hPakFile = CreateFile("sprites\\Wsh.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE ) {
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*1] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*0, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*2] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*1, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*3] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*2, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*4] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*3, TRUE);
				for (i = 0; i < 7; i++)	m_pSprite[DEF_SPRID_SHIELD_W + i + 8*5] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*4, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*6] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*5, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*7] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*6, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*8] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*7, TRUE);
				for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8*9] = new class CSprite(m_hPakFile, &m_DDraw, "Wsh", i + 7*8, TRUE);
				CloseHandle(m_hPakFile);
			}
			m_cLoading = 100;
		}
		break;
	case 100:
		{	MakeEffectSpr( "effect", 0, 10, FALSE);
			MakeEffectSpr( "effect2", 10, 3, FALSE);
			MakeEffectSpr( "effect3", 13, 6, FALSE);
			MakeEffectSpr( "effect4", 19, 5, FALSE);
			m_hPakFile = CreateFile("sprites\\effect5.pak", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			if( m_hPakFile != INVALID_HANDLE_VALUE )
			{	for (i = 0; i <= 6; i++) // Because effectn∞0 is EnergySphere
					m_pEffectSpr[i+ 24] = new class CSprite(m_hPakFile, &m_DDraw, "effect5", i+1, FALSE);
				CloseHandle(m_hPakFile);
			}
			MakeEffectSpr( "CruEffect1", 31, 9, FALSE);
			MakeEffectSpr( "effect6", 40, 5, FALSE);
			MakeEffectSpr( "effect7", 45, 12, FALSE);
			MakeEffectSpr( "effect8", 57, 9, FALSE);
			MakeEffectSpr( "effect9", 66, 21, FALSE);

			MakeEffectSpr( "effect10",  87,  2, FALSE); // Effets Hero items
			MakeEffectSpr( "effect11",  89, 14, FALSE); // Cancel, stormBlade, resu, GateHeldenian....etc
			//NB: Charge 15 du client 3.51, mais il n'y a que 14 ds le PAK
			MakeEffectSpr( "effect11s", 104, 1, FALSE); // effet sort mais je ne sais pas lequel
			// Manque des effets ici .....
			// MakeEffectSpr( "effect13", 108, 2, FALSE); // not loaded by client 351 (Heldenian gates death)
			//MakeEffectSpr( "yseffect2", 141, 8, FALSE); // Wrong in 351 client...
			MakeEffectSpr( "yseffect2", 140, 8, FALSE); // Abaddon's death
			MakeEffectSpr( "effect12",  148, 4, FALSE); // Slates auras
			MakeEffectSpr( "yseffect3", 152,16, FALSE); // Fumerolles ou ame qui s'envole
			//MakeEffectSpr( "yseffect4", 167, 7, FALSE); // Wrong in 351 client
			MakeEffectSpr( "yseffect4", 133, 7, FALSE); // Abaddon's map thunder.


			if (m_bSoundFlag) // Attention il y a un autre systeme de chargement ds la v351
			{	for (i = 1; i <= 24; i++)
				{	wsprintf(G_cTxt, "sounds\\C%d.wav", i);
					m_pCSound[i] = new class CSoundBuffer(m_DSound.m_lpDS, m_DSound.m_DSCaps, G_cTxt);
				}

				for (i = 1; i <= 156; i++)
				{	wsprintf(G_cTxt, "sounds\\M%d.wav", i);
					m_pMSound[i] = new class CSoundBuffer(m_DSound.m_lpDS, m_DSound.m_DSCaps, G_cTxt);
				}
				for (i = 1; i <= 53; i++)
				{	wsprintf(G_cTxt, "sounds\\E%d.wav", i);
					m_pESound[i] = new class CSoundBuffer(m_DSound.m_lpDS, m_DSound.m_DSCaps, G_cTxt);
			}	}
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		}
		break;
	}
}
/*********************************************************************************************************************
** 	void CGame::UpdateScreen_OnLoading_Progress()																	**
**  description			:: loading becomes progressbar																**
**********************************************************************************************************************/
void CGame::UpdateScreen_OnLoading_Progress()
{
	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOADING, 0,0,0, TRUE);
	DrawVersion(TRUE);
	int iBarWidth;
	iBarWidth= (int)m_cLoading;
	m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING]->PutSpriteFastWidth(472,442, 1, iBarWidth, G_dwGlobalTime);
	m_DDraw.iFlip();
}

void CGame::OnTimer()
{
	if( m_cGameMode < 0 ) return;
	DWORD dwTime = timeGetTime();

	if (m_cGameMode != DEF_GAMEMODE_ONLOADING) {
		if ((dwTime - m_dwCheckSprTime) > 8000 )
		{	m_dwCheckSprTime = dwTime;
			if( m_bIsProgramActive ) ReleaseUnusedSprites();
			if ((m_pGSock != NULL) && (m_pGSock->m_bIsAvailable == TRUE))
				bSendCommand(MSGID_COMMAND_CHECKCONNECTION, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL, NULL, NULL);
	}	}

	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
	{	if ((dwTime - m_dwCheckConnTime) > 5000)
		{	m_dwCheckConnTime = dwTime;
			if ((m_bIsCrusadeMode) && (m_iCrusadeDuty == NULL)) EnableDialogBox(33, 1, NULL, NULL);
		}

		if ((dwTime - m_dwCheckChatTime) > 2000)
		{	m_dwCheckChatTime = m_dwTime;
			ReleaseTimeoverChatMsg();
			if (m_cCommandCount >= 6)
			{	m_iNetLagCount++;
				if (m_iNetLagCount >= 7)
				{	ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
					delete m_pGSock;
					m_pGSock = NULL;
					return;
				}
			}else m_iNetLagCount = NULL;
		}

		if ((G_bIsCalcSocketConnected == FALSE) && ((dwTime - G_dwCalcSocketTime) > 5000))
		{	delete m_pGSock;
			m_pGSock = NULL;
			ChangeGameMode(DEF_GAMEMODE_ONQUIT);
			m_bEscPressed = FALSE;
			PlaySound('E', 14, 5);
			if (m_bSoundFlag) m_pESound[38]->bStop();
			if ((m_bSoundFlag) && (m_bMusicStat == TRUE))
			{
				if (m_pBGM != NULL) m_pBGM->bStop();
			}
			return;
		}

		if ((G_pCalcSocket != NULL) && (G_bIsCalcSocketConnected == TRUE)) {
			if ((dwTime - G_dwCalcSocketSendTime) > 1000*5) {
				if (memcmp(G_cCmdLineTokenA_Lowercase, "wisetop", 7) == 0)
				{}else
				{	char cPacket[120];
					int  iSended;
					WORD * wp;
					ZeroMemory(cPacket, sizeof(cPacket));
					cPacket[0] = 0;					// Key
					wp  = (WORD *)(cPacket +1);
					*wp = 5;
					iSended = G_pCalcSocket->iSendMsgBlockingMode(cPacket, 5);
				}
				G_dwCalcSocketSendTime = dwTime;
	}	}	}
}


BOOL CGame::_bCheckDlgBoxClick(short msX, short msY)
{int i;
 char         cDlgID;
	m_DInput.m_sZ = 0;
	// Snoopy: 41->61
	for (i = 0; i < 61; i++)
	// Snoopy: 40->60
	if (m_cDialogBoxOrder[60 - i] != NULL) {
	// Snoopy: 40->60
		cDlgID = m_cDialogBoxOrder[60 - i];
		if ((m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX) &&
			(m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY) )
		{	switch (cDlgID) {
			case 1:
				DlgBoxClick_Character(msX, msY);
				break;
			case 2:
				DlgBoxClick_Inventory(msX, msY);
				break;
			case 3:
				DlgBoxClick_Magic(msX, msY);
				break;
			case 4:
				DlgBoxClick_ItemDrop(msX, msY);
				break;
			case 5:
				DlgBoxClick_15AgeMsg(msX, msY);
				break;
			case 6:
				DlgBoxClick_WarningMsg(msX, msY);
				break;
			case 7:
				DlgBoxClick_GuildMenu(msX, msY);
				break;
			case 8:
				DlgBoxClick_GuildOp(msX, msY);
				break;
			case 9:
				break;
			case 11:
				DlgBoxClick_Shop(msX, msY);
				break;
			case 12:
				DlgBoxClick_LevelUpSettings(msX, msY);
				break;
			case 13:
				DlgBoxClick_CityhallMenu(msX, msY);
				break;
			case 14:
				DlgBoxClick_Bank(msX, msY);
				break;
			case 15:
				DlgBoxClick_Skill(msX, msY);
				break;
			case 16:
				DlgBoxClick_MagicShop(msX, msY);
				break;
			case 18:
				DlgBoxClick_Text(msX, msY);
				break;
			case 19:
				DlgBoxClick_SysMenu(msX, msY);
				break;
			case 20:
				DlgBoxClick_NpcActionQuery(msX, msY);
				break;
			case 21:
				DlgBoxClick_NpcTalk(msX, msY);
				break;
			case 23:
				DlgBoxClick_ItemSellorRepair(msX, msY);
				break;
			case 24:
				DlgBoxClick_Fish(msX, msY);
				break;
			case 25:
				DlgBoxClick_ShutDownMsg(msX, msY);
				break;
			case 26:
				DlgBoxClick_SkillDlg(msX, msY);
				break;
			case 27:
				DlgBoxClick_Exchange(msX, msY);
				break;
			case 28:
				DlgBoxClick_Quest(msX, msY);
				break;
			case 30:
				DlgBoxClick_IconPannel(msX, msY);
				break;
			case 31:
				DlgBoxClick_SellList(msX, msY);
				break;
			case 32:
				DlgBoxClick_Party(msX, msY);
				break;
			case 33:
				DlgBoxClick_CrusadeJob(msX, msY);
				break;
			case 34:
				DlgBoxClick_ItemUpgrade(msX, msY);
     			break;
			case 35:
				DlgBoxClick_Help(msX, msY);
				break;

			case 36:
				DlgBoxClick_Commander(msX, msY);
				break;

			case 37:
				DlgBoxClick_Constructor(msX, msY);
				break;

			case 38:
				DlgBoxClick_Soldier(msX, msY);
				break;

			case 40:
				DlgBoxClick_Slates(msX, msY);
				break;
// Snoopy: Boite de dialogue de confirmation d'Èchange
			case 41:
				DlgBoxClick_ConfirmExchange(msX, msY);
				break;
			case 42:
				DlgBoxClick_ChangeStatsMajestic(msX, msY);
				break;
			case 50:
				DlgBoxClick_Resurect(msX, msY);
				break;
			case 51:
				DlgBoxClick_CMDHallMenu(msX, msY);
				break;
			}

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGame::_bCheckDlgBoxDoubleClick(short msX, short msY)
{
	int i;
	char cDlgID;
//	if (m_iHP <= 0) return FALSE;
	//Snoopy: 41->61
	for (i = 0; i < 61; i++)
	//Snoopy: 40->60
	if (m_cDialogBoxOrder[60 - i] != NULL) {
	//Snoopy: 40->60
		cDlgID = m_cDialogBoxOrder[60 - i];
		if ((m_stDialogBoxInfo[cDlgID].sX < msX)	&& ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX) &&
			(m_stDialogBoxInfo[cDlgID].sY < msY)	&& ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY) ) {
			switch (cDlgID) {
			case 1:
				DlbBoxDoubleClick_Character(msX, msY);
				break;
			case 2:
				DlbBoxDoubleClick_Inventory(msX, msY);
				break;
			case 9:
				DlbBoxDoubleClick_GuideMap(msX, msY);
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CGame::bDlgBoxPress_Inventory(short msX, short msY)
{int i;
 char  cItemID;
 short sX, sY, x1, x2, y1, y2;

#ifdef _DEBUG
 AddEventList("Press Inventory", 10);
#endif

	if (m_bIsDialogEnabled[2] == FALSE) return FALSE;
	if (m_bIsDialogEnabled[17] == TRUE) return FALSE;
	if (m_bIsDialogEnabled[4] == TRUE) return FALSE;

	sX = m_stDialogBoxInfo[2].sX;
	sY = m_stDialogBoxInfo[2].sY;

	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_cItemOrder[DEF_MAXITEMS - 1 - i] != -1) {
		cItemID = m_cItemOrder[DEF_MAXITEMS - 1 - i];

		if (m_pItemList[cItemID] != NULL)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + 32 + m_pItemList[cItemID]->m_sX,
			                                                   sY + 44 + m_pItemList[cItemID]->m_sY, m_pItemList[cItemID]->m_sSpriteFrame);
			x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
			y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
			x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
			y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;
			if ( (m_bIsItemDisabled[cItemID] == FALSE) && (m_bIsItemEquipped[cItemID] == FALSE) && (msX > x1) && (msX < x2) && (msY > y1) && (msY < y2) ) {

				if (m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_bCheckCollison(sX + 32 + m_pItemList[cItemID]->m_sX, sY + 44 + m_pItemList[cItemID]->m_sY, m_pItemList[cItemID]->m_sSpriteFrame, msX, msY) == TRUE)
				{	_SetItemOrder(0, cItemID);
					if (   (m_bIsGetPointingMode == TRUE) && (m_iPointCommandType < 100) && (m_iPointCommandType >= 0 )
						&& (m_pItemList[m_iPointCommandType] != NULL)
						&& (m_pItemList[m_iPointCommandType]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE_DEST)
						&& (m_iPointCommandType != cItemID) )
					{	PointCommandHandler(NULL, NULL, cItemID);
						//m_bCommandAvailable  = FALSE;
						m_bIsGetPointingMode = FALSE;
					}else
					{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
						m_stMCursor.sSelectedObjectID   = cItemID;
						m_stMCursor.sDistX = msX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
						m_stMCursor.sDistY = msY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
					}
					return TRUE;
	}	}	}	}
	return FALSE;
}

void CGame::_SetItemOrder(char cWhere, char cItemID)
{
 int i;

	switch (cWhere) {
	case 0:
		for (i = 0; i < DEF_MAXITEMS; i++)
		if (m_cItemOrder[i] == cItemID)
			m_cItemOrder[i] = -1;

		for (i = 1; i < DEF_MAXITEMS; i++)
		if ((m_cItemOrder[i-1] == -1) && (m_cItemOrder[i] != -1)) {
			m_cItemOrder[i-1] = m_cItemOrder[i];
			m_cItemOrder[i]   = -1;
		}

		for (i = 0; i < DEF_MAXITEMS; i++)
		if (m_cItemOrder[i] == -1) {
			m_cItemOrder[i] = cItemID;
			return;
		}
		break;
	}
}

BOOL CGame::_bCheckDraggingItemRelease(short msX, short msY)
{int i;
 char         cDlgID;
	//Snoopy: 41->61
	for (i = 0; i < 61; i++)
	//Snoopy: 40->60
	if (m_cDialogBoxOrder[60 - i] != NULL) {
	//Snoopy: 40->60
		cDlgID = m_cDialogBoxOrder[60 - i];
		if (   (m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX)
			&& (m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY) )
		{	EnableDialogBox(cDlgID, NULL, NULL, NULL);
			switch (cDlgID) {
			case 1:
				bItemDrop_Character();
				break;

			case 2:
				bItemDrop_Inventory(msX, msY);
				break;

			case 14:
				bItemDrop_Bank(msX, msY);
				break;

			case 26: // Alchim / Manuf
				bItemDrop_SkillDialog();
				break;

			case 27:
				bItemDrop_ExchangeDialog(msX, msY);
				break;

			case 30:
				bItemDrop_IconPannel(msX, msY);
				break;

			case 31:
				bItemDrop_SellList(msX, msY);
				break;

			case 34:
				bItemDrop_ItemUpgrade();
				break;

			case 40:
				bItemDrop_Slates();
				break;
			}
			return TRUE;
	}	}
	bItemDrop_ExternalScreen((char)m_stMCursor.sSelectedObjectID, msX, msY);
	return FALSE;
}



void CGame::bItemDrop_ExternalScreen(char cItemID, short msX, short msY)
{char  cName[21];
 short sType, tX, tY;
 int iStatus;

	if (bCheckItemOperationEnabled(cItemID) == FALSE) return;

	if ((m_sMCX != 0) && (m_sMCY != 0) && (abs(m_sPlayerX - m_sMCX) <= 8) && (abs(m_sPlayerY - m_sMCY) <= 8))
	{	ZeroMemory(cName, sizeof(cName));
		m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sType, &iStatus, &m_wCommObjectID);
		if (memcmp(m_cPlayerName, cName, 10) == 0)
		{}else
		{	if (   ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW))
				&& (m_pItemList[cItemID]->m_dwCount > 1))
			{	m_stDialogBoxInfo[17].sX  = msX - 140;
				m_stDialogBoxInfo[17].sY  = msY - 70;
				if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;
				m_stDialogBoxInfo[17].sV1 = m_sMCX;
				m_stDialogBoxInfo[17].sV2 = m_sMCY;
				m_stDialogBoxInfo[17].sV3 = sType;
				m_stDialogBoxInfo[17].sV4 = m_wCommObjectID;
				ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
				if (sType < 10)
					memcpy(m_stDialogBoxInfo[17].cStr, cName, 10);
				else
				{	GetNpcName(sType, m_stDialogBoxInfo[17].cStr);
				}
				EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, NULL);
			}else
			{	switch (sType) {
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					EnableDialogBox(20, 1, cItemID, sType);
					m_stDialogBoxInfo[20].sV3 = 1;
					m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;
					m_stDialogBoxInfo[20].sV5 = m_sMCX;
					m_stDialogBoxInfo[20].sV6 = m_sMCY;

					tX = msX - 117;
					tY = msY - 50;
					if (tX < 0) tX = 0;
					if ((tX + 235) > 639) tX = 639 - 235;
					if (tY < 0) tY = 0;
					if ((tY + 100) > 479) tY = 479 - 100;
					m_stDialogBoxInfo[20].sX  = tX;
					m_stDialogBoxInfo[20].sY  = tY;

					ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
					strcpy(m_stDialogBoxInfo[20].cStr, cName);
					//bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, cItemID, 1, m_sMCX, m_sMCY, m_pItemList[cItemID]->m_cName); //v1.4
					break;

				case 20: // Howard
					EnableDialogBox(20, 3, cItemID, sType);
					m_stDialogBoxInfo[20].sV3 = 1;
					m_stDialogBoxInfo[20].sV4 = m_wCommObjectID; // v1.4
					m_stDialogBoxInfo[20].sV5 = m_sMCX;
					m_stDialogBoxInfo[20].sV6 = m_sMCY;

					tX = msX - 117;
					tY = msY - 50;
					if (tX < 0) tX = 0;
					if ((tX + 235) > 639) tX = 639 - 235;
					if (tY < 0) tY = 0;
					if ((tY + 100) > 479) tY = 479 - 100;
					m_stDialogBoxInfo[20].sX  = tX;
					m_stDialogBoxInfo[20].sY  = tY;

					ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
					GetNpcName(sType, m_stDialogBoxInfo[20].cStr);
					//bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, cItemID, 1, m_sMCX, m_sMCY, m_pItemList[cItemID]->m_cName);
					break;

				case 15: // ShopKeeper-W
		  		case 24: // Tom
					EnableDialogBox(20, 2, cItemID, sType);
					m_stDialogBoxInfo[20].sV3 = 1;
					m_stDialogBoxInfo[20].sV4 = m_wCommObjectID; // v1.4
					m_stDialogBoxInfo[20].sV5 = m_sMCX;
					m_stDialogBoxInfo[20].sV6 = m_sMCY;

					tX = msX - 117;
					tY = msY - 50;
					if (tX < 0) tX = 0;
					if ((tX + 235) > 639) tX = 639 - 235;
					if (tY < 0) tY = 0;
					if ((tY + 100) > 479) tY = 479 - 100;
					m_stDialogBoxInfo[20].sX  = tX;
					m_stDialogBoxInfo[20].sY  = tY;

					ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
					GetNpcName(sType, m_stDialogBoxInfo[20].cStr);
					break;

				default:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, cItemID, 1, m_sMCX, m_sMCY, m_pItemList[cItemID]->m_cName);
					break;
				}
				//m_bIsItemDisabled[cItemID] = TRUE;
			}
			m_bIsItemDisabled[cItemID] = TRUE;
		}
	}else
	{	if (   ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW))
			&& (m_pItemList[cItemID]->m_dwCount > 1))
		{	m_stDialogBoxInfo[17].sX  = msX - 140;
			m_stDialogBoxInfo[17].sY  = msY - 70;
			if (m_stDialogBoxInfo[17].sY < 0)		m_stDialogBoxInfo[17].sY = 0;
			m_stDialogBoxInfo[17].sV1 = NULL;
			m_stDialogBoxInfo[17].sV2 = NULL;
			m_stDialogBoxInfo[17].sV3 = NULL;
			m_stDialogBoxInfo[17].sV4 = NULL;
			ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
			EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, NULL);
		}else
		{	if(_ItemDropHistory(m_pItemList[cItemID]->m_cName))
			{	m_stDialogBoxInfo[4].sX  = msX - 140;
				m_stDialogBoxInfo[4].sY  = msY - 70;
				if (m_stDialogBoxInfo[4].sY < 0)	m_stDialogBoxInfo[4].sY = 0;
    			m_stDialogBoxInfo[4].sV1 = NULL;
				m_stDialogBoxInfo[4].sV2 = NULL;
				m_stDialogBoxInfo[4].sV3 = 1;
				m_stDialogBoxInfo[4].sV4 = NULL;
				m_stDialogBoxInfo[4].sV5 = cItemID;
				ZeroMemory(m_stDialogBoxInfo[4].cStr, sizeof(m_stDialogBoxInfo[4].cStr));
				EnableDialogBox(4, cItemID, m_pItemList[cItemID]->m_dwCount, NULL);
			}else
			{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_ITEMDROP, NULL, cItemID, 1, NULL, m_pItemList[cItemID]->m_cName);
		}	}
		m_bIsItemDisabled[cItemID] = TRUE;
	}
}


void CGame::CommonEventHandler(char * pData)
{
 WORD * wp, wEventType;
 short * sp, sX, sY, sV1, sV2, sV3, sV4;
 char * cp;

	wp   = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wEventType = *wp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	sp  = (short *)cp;
	sX  = *sp;
	cp += 2;

	sp  = (short *)cp;
	sY  = *sp;
	cp += 2;

	sp  = (short *)cp;
	sV1 = *sp;
	cp += 2;

	sp  = (short *)cp;
	sV2 = *sp;
	cp += 2;

	sp  = (short *)cp;
	sV3 = *sp;
	cp += 2;

	sp  = (short *)cp;
	sV4 = *sp;
	cp += 2;

	switch (wEventType) {
	case DEF_COMMONTYPE_ITEMDROP:
		if ((sV1 == 6) && (sV2 == 0)) {
			bAddNewEffect(4, sX, sY, NULL, NULL, 0);
		}
		m_pMapData->bSetItem(sX, sY, sV1, sV2, (char)sV3);
		break;

	case DEF_COMMONTYPE_SETITEM:
		m_pMapData->bSetItem(sX, sY, sV1, sV2, (char)sV3, FALSE); // v1.4 color
		break;

	case DEF_COMMONTYPE_MAGIC:
		bAddNewEffect(sV3, sX, sY, sV1, sV2, 0, sV4);
		break;

	case DEF_COMMONTYPE_CLEARGUILDNAME:
		ClearGuildNameList();
		break;
	}
}

void CGame::ClearGuildNameList()
{
	for (int i = 0; i < DEF_MAXGUILDNAMES; i++) {
		m_stGuildName[i].dwRefTime = 0;
		m_stGuildName[i].iGuildRank = -1;
		ZeroMemory(m_stGuildName[i].cCharName, sizeof(m_stGuildName[i].cCharName));
		ZeroMemory(m_stGuildName[i].cGuildName, sizeof(m_stGuildName[i].cGuildName));
	}
}

void CGame::InitGameSettings()
{
 int i;

	m_bForceAttack = FALSE;
	m_dwCommandTime = 0;

	m_bInputStatus = FALSE;
	m_pInputBuffer = NULL;

	m_iPDBGSdivX = 0;
	m_iPDBGSdivY = 0;
	m_bIsRedrawPDBGS = TRUE;

	m_iCameraShakingDegree = 0;

	m_cCommand = DEF_OBJECTSTOP;
	m_cCommandCount = 0;

	m_bIsGetPointingMode = FALSE;
	m_iPointCommandType  = -1; //v2.15 NULL -> -1

	m_bIsCombatMode = FALSE;
	m_bRunningMode = FALSE;

	m_stMCursor.cPrevStatus       = DEF_CURSORSTATUS_NULL;
	m_stMCursor.dwSelectClickTime = NULL;

	m_bSkillUsingStatus = FALSE;
	m_bItemUsingStatus  = FALSE;
	m_bUsingSlate = FALSE;

	m_bIsWhetherEffect   = FALSE;
	m_cWhetherEffectType = NULL;

	m_iDownSkillIndex = -1;
	m_stDialogBoxInfo[15].bFlag = FALSE;

	m_bIsConfusion = FALSE;

	m_iIlusionOwnerH = NULL;
	m_cIlusionOwnerType = NULL;

	m_iDrawFlag = 0;
	m_bDrawFlagDir = FALSE;
	m_bIsCrusadeMode = FALSE;
	m_iCrusadeDuty = NULL;
	m_bIsAvatarMode  = FALSE;
	m_bIsAvatarMessenger = FALSE;

	m_iNetLagCount = NULL;

	m_dwEnvEffectTime = timeGetTime();

	for (i = 0; i < DEF_MAXGUILDNAMES; i++) {
		m_stGuildName[i].dwRefTime = 0;
		m_stGuildName[i].iGuildRank = -1;
		ZeroMemory(m_stGuildName[i].cCharName, sizeof(m_stGuildName[i].cCharName));
		ZeroMemory(m_stGuildName[i].cGuildName, sizeof(m_stGuildName[i].cGuildName));
	}
	//Snoopy: 61
	for (i = 0; i < 61; i++)
		m_bIsDialogEnabled[i] = FALSE;

	//Snoopy: 58 because 2 last ones alreaddy defined
	for (i = 0; i < 58; i++)
		m_cDialogBoxOrder[i] = NULL;

	for (i = 0; i < DEF_MAXEFFECTS; i++) {
		if (m_pEffectList[i] != NULL) delete m_pEffectList[i];
		m_pEffectList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXCHATMSGS; i++) {
		if (m_pChatMsgList[i] != NULL) delete m_pChatMsgList[i];
		m_pChatMsgList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXCHATSCROLLMSGS; i++) {
		if (m_pChatScrollList[i] != NULL) delete m_pChatScrollList[i];
		m_pChatScrollList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXWHISPERMSG; i++) {
		if (m_pWhisperMsg[i] != NULL) delete m_pWhisperMsg[i];
		m_pWhisperMsg[i] = NULL;
	}

	ZeroMemory(m_cLocation, sizeof(m_cLocation));

	ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
	m_iGuildRank = -1;
	m_iTotalGuildsMan = 0;

	for (i = 0; i < 100; i++) {
		m_stGuildOpList[i].cOpMode = NULL;
		ZeroMemory(m_stGuildOpList[i].cName, sizeof(m_stGuildOpList[i].cName));
	}

	for (i = 0; i < 6; i++) {
		ZeroMemory(m_stEventHistory[i].cTxt, sizeof(m_stEventHistory[i].cTxt));
		m_stEventHistory[i].dwTime = G_dwGlobalTime;

		ZeroMemory(m_stEventHistory2[i].cTxt, sizeof(m_stEventHistory2[i].cTxt));
		m_stEventHistory2[i].dwTime = G_dwGlobalTime;
	}

    for (i = 0; i < DEF_MAXMENUITEMS; i++) {
		if (m_pItemForSaleList[i] != NULL) delete m_pItemForSaleList[i];
		m_pItemForSaleList[i] = NULL;
	}

	for (i = 0; i < 41; i++) {
		m_stDialogBoxInfo[i].bFlag = FALSE;
		m_stDialogBoxInfo[i].sView = 0;
		m_stDialogBoxInfo[i].bIsScrollSelected = FALSE;
	}

	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] != NULL) {
		delete m_pItemList[i];
		m_pItemList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXSELLLIST; i++) {
		m_stSellItemList[i].iIndex = -1;
		m_stSellItemList[i].iAmount = 0;
	}

	for (i = 0; i < DEF_MAXBANKITEMS; i++)
	if (m_pBankList[i] != NULL) {
		delete m_pBankList[i];
		m_pBankList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		m_cMagicMastery[i] = NULL;

	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		m_cSkillMastery[i] = NULL;

	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++) {
		if (m_pMsgTextList[i] != NULL)
			delete m_pMsgTextList[i];
		m_pMsgTextList[i] = NULL;

		if (m_pMsgTextList2[i] != NULL)
			delete m_pMsgTextList2[i];
		m_pMsgTextList2[i] = NULL;

		if (m_pAgreeMsgTextList[i] != NULL)
			delete m_pAgreeMsgTextList[i];
		m_pAgreeMsgTextList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
		m_stPartyMember[i].cStatus = 0;
		ZeroMemory(m_stPartyMember[i].cName, sizeof(m_stPartyMember[i].cName));
	}

	m_iLU_Point = 0;
	m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
	m_bDialogTrans   = FALSE;
	m_cWhetherStatus = NULL;
	m_cLogOutCount = -1;
	m_dwLogOutCountTime = NULL;
	m_iSuperAttackLeft = 0;
	m_bSuperAttackMode = FALSE;
	m_iFightzoneNumber = 0 ;
	ZeroMemory(m_cBGMmapName, sizeof(m_cBGMmapName));
	m_dwWOFtime = 0;
	m_stQuest.sWho          = NULL;
	m_stQuest.sQuestType    = NULL;
	m_stQuest.sContribution = NULL;
	m_stQuest.sTargetType   = NULL;
	m_stQuest.sTargetCount  = NULL;
	m_stQuest.sCurrentCount = NULL;
	m_stQuest.sX            = NULL;
	m_stQuest.sY            = NULL;
	m_stQuest.sRange        = NULL;
	m_stQuest.bIsQuestCompleted = FALSE;
	ZeroMemory(m_stQuest.cTargetName, sizeof(m_stQuest.cTargetName));
	m_bIsObserverMode = FALSE;
	m_bIsObserverCommanded = FALSE;
	m_bIsPoisoned = FALSE;
	m_bIsPrevMoveBlocked = FALSE;
	m_iPrevMoveX = m_iPrevMoveY = -1;
	m_sDamageMove = 0;
	m_sDamageMoveAmount = 0;
	m_bForceDisconn = FALSE;
	m_bIsSpecialAbilityEnabled = FALSE;
	m_iSpecialAbilityType = 0;
	m_dwSpecialAbilitySettingTime = NULL;
	m_iSpecialAbilityTimeLeftSec = NULL;
	m_stMCursor.cSelectedObjectType = NULL;
	m_bIsF1HelpWindowEnabled = FALSE;
	m_bIsTeleportRequested = FALSE;
	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
	{	m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}
	ZeroMemory(m_cStatusMapName, sizeof(m_cStatusMapName));
	m_dwCommanderCommandRequestedTime = NULL;
	ZeroMemory(m_cTopMsg, sizeof(m_cTopMsg));
	m_iTopMsgLastSec = NULL;
	m_dwTopMsgTime   = NULL;
	m_iConstructionPoint = NULL;
	m_iWarContribution   = NULL;
	ZeroMemory(m_cTeleportMapName, sizeof(m_cTeleportMapName));
	m_iTeleportLocX = m_iTeleportLocY = -1;
	ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
	m_iConstructLocX = m_iConstructLocY = -1;

	//Snoopy: Apocalypse Gate
	ZeroMemory(m_cGateMapName, sizeof(m_cGateMapName));
	m_iGatePositX = m_iGatePositY = -1;
	m_iHeldenianAresdenLeftTower	= -1;
	m_iHeldenianElvineLeftTower		= -1;
	m_iHeldenianAresdenFlags		= -1;
	m_iHeldenianElvineFlags			= -1;
	m_bIsXmas = FALSE;
	m_iTotalPartyMember = 0;
	m_iPartyStatus = 0;
	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
	m_iGizonItemUpgradeLeft = 0;
	cStateChange1 = 0;
	cStateChange2 = 0;
	cStateChange3 = 0;
	EnableDialogBox(9, 0, 0, 0 );
}

void CGame::_GetHairColorRGB(int iColorType, int * pR, int * pG, int * pB)
{	switch (iColorType) {
	case 0: // rouge foncÈ
		*pR = 14; *pG = -5; *pB = -5; break;
	case 1: // Orange
		*pR = 20; *pG = 0; *pB = 0; break;
	case 2: // marron tres clair
		*pR = 22; *pG = 13; *pB = -10; break;
	case 3: // vert
		*pR = 0; *pG = 10; *pB = 0; break;
	case 4: // Bleu flashy
		*pR = 0; *pG = 0; *pB = 22; break;
	case 5: // Bleu foncÈ
		*pR = -5; *pG = -5; *pB = 15; break;
	case 6: //Mauve
		*pR = 15; *pG = -5; *pB = 16; break;
	case 7: // Noir
		*pR = -6; *pG = -6; *pB = -6; break;
	case 8:
		*pR = 10; *pG = 3; *pB = 10; break;
	case 9:
		*pR = 10; *pG = 3; *pB = -10; break;
	case 10:
		*pR = -10; *pG = 3; *pB = 10; break;
	case 11:
		*pR = 10; *pG = 3; *pB = 20; break;
	case 12:
		*pR = 21; *pG = 3; *pB = 3; break;
	case 13:
		*pR = 3; *pG = 3; *pB = 25; break;
	case 14:
		*pR = 3; *pG = 11; *pB = 3; break;
	case 15:
		*pR = 6; *pG = 8; *pB = 0; break;
	}
}

void CGame::DlgBoxClick_GuildMenu(short msX, short msY)
{short sX, sY;
 char cTemp[21];
 int iAdjX , iAdjY ;
	sX = m_stDialogBoxInfo[7].sX;
	sY = m_stDialogBoxInfo[7].sY ;

	iAdjX = -13;
	iAdjY = 30;

	switch (m_stDialogBoxInfo[7].cMode) {
	case 0:
		if ((msX > sX + iAdjX + 80) && (msX < sX + iAdjX + 210) && (msY > sY + iAdjY + 63) && (msY < sY + iAdjY + 78))
		{	if (m_iGuildRank != -1) return;
			if (m_iCharisma < 20) return;
			if (m_iLevel < 20) return;
			if (m_bIsCrusadeMode) return;
			EndInputString();
			StartInputString(sX + 75, sY + 140, 21, m_cGuildName);
			m_stDialogBoxInfo[7].cMode = 1;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 82) && (msY < sY + iAdjY + 99))
		{	if (m_iGuildRank != 0) return;
			if (m_bIsCrusadeMode) return;
			m_stDialogBoxInfo[7].cMode = 5;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 61) && (msX < sX + iAdjX + 226) && (msY > sY + iAdjY + 103) && (msY < sY + iAdjY + 120))
		{	m_stDialogBoxInfo[7].cMode = 9;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 60) && (msX < sX + iAdjX + 227) && (msY > sY + iAdjY + 123) && (msY < sY + iAdjY + 139))
		{	m_stDialogBoxInfo[7].cMode = 11;
			PlaySound('E', 14, 5);
		}
		if( m_iFightzoneNumber < 0 ) break ;
		if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 228) && (msY > sY + iAdjY + 143) && (msY < sY + iAdjY + 169))
		{	if (m_iGuildRank != 0) return;
			if (m_iFightzoneNumber == 0 )	m_stDialogBoxInfo[7].cMode = 13;
			else  m_stDialogBoxInfo[7].cMode = 19;
			PlaySound('E', 14, 5);
		}
		break;
	case 1:
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Submit
			if (strcmp(m_cGuildName, "NONE") == 0) return;
			if (strlen(m_cGuildName) == 0) return;
			bSendCommand(MSGID_REQUEST_CREATENEWGUILD, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 2;
			EndInputString();
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			m_stDialogBoxInfo[7].cMode = 0;
			EndInputString();
			PlaySound('E', 14, 5);
		}
		break;

	case 3:
	case 4:
	case 7:
	case 8:
	case 10:
	case 12:
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 9:
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Purchaseπ
			ZeroMemory(cTemp, sizeof(cTemp));
			strcpy(cTemp,"GuildAdmissionTicket");
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, NULL, 1, NULL, NULL, cTemp);
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 11:
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Purchase
			ZeroMemory(cTemp, sizeof(cTemp));
			strcpy(cTemp,"GuildSecessionTicket");
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, NULL, 1, NULL, NULL, cTemp);
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 5:
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Confirm
			bSendCommand(MSGID_REQUEST_DISBANDGUILD, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 6;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Cancel
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 13:
		if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 1, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 1;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 2, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 2;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 3, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 3;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 4, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 4;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 5, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 5;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 6, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 6;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
		{	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 7, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 7;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
		{ 	bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, NULL, NULL, 8, NULL, NULL, NULL);
			m_stDialogBoxInfo[7].cMode = 18;
			m_iFightzoneNumberTemp = 8;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break ;

	case 14://
	case 15://
	case 16://
	case 17://
	case 21://
	case 22://
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// OK
			m_stDialogBoxInfo[7].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break ;
	}
}

void CGame::CreateNewGuildResponseHandler(char * pData)
{WORD * wpResult;
 	wpResult = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	switch (*wpResult) {
	case DEF_MSGTYPE_CONFIRM:
		m_iGuildRank = 0;
		m_stDialogBoxInfo[7].cMode = 3;
		break;
	case DEF_MSGTYPE_REJECT:
		m_iGuildRank = -1;
		m_stDialogBoxInfo[7].cMode = 4;
		break;
	}
}

void CGame::InitPlayerCharacteristics(char * pData)
{int  * ip;
 char * cp;
 WORD * wp;
	// Snoopy: Angels
	m_iAngelicStr = 0;
	m_iAngelicDex = 0;
	m_iAngelicInt = 0;
	m_iAngelicMag = 0;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ip   = (int *)cp;
	m_iHP = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iMP = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iSP = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iAC = *ip;		//‚ m_iDefenseRatio
	cp += 4;
	ip   = (int *)cp;
	m_iTHAC0 = *ip;    //ª m_iHitRatio
	cp += 4;
	ip   = (int *)cp;
	m_iLevel = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iStr = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iInt = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iVit = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iDex = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iMag = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iCharisma = *ip;
	cp += 4;

	// CLEROTH - LU
	wp = (WORD *)cp;
	m_iLU_Point = *wp - 3;
	cp += 7; // 2 + 5

	/* ORIGINAL
	m_cLU_Str = *cp;
	cp++;
	m_cLU_Vit = *cp;
	cp++;
	m_cLU_Dex = *cp;
	cp++;
	m_cLU_Int = *cp;
	cp++;
	m_cLU_Mag = *cp;
	cp++;
	m_cLU_Char = *cp;
	cp++;

	m_iLU_Point = 3 - (m_cLU_Str + m_cLU_Vit + m_cLU_Dex + m_cLU_Int + m_cLU_Mag + m_cLU_Char);
*/

	ip   = (int *)cp;
	m_iExp = *ip;
	cp += 4;

	ip   = (int *)cp;
	m_iEnemyKillCount = *ip;
	cp += 4;

	ip   = (int *)cp;
	m_iPKCount = *ip;
	cp += 4;

	ip   = (int *)cp;
	m_iRewardGold = *ip;
	cp += 4;

	memcpy(m_cLocation, cp, 10);
	cp += 10;
	if (memcmp(m_cLocation, "aresden", 7) == 0)
	{	m_bAresden = TRUE;
		m_bCitizen = TRUE;
		m_bHunter  = FALSE;
	}else if (memcmp(m_cLocation, "arehunter", 9) == 0)
	{	m_bAresden = TRUE;
		m_bCitizen = TRUE;
		m_bHunter  = TRUE;
	}else if (memcmp(m_cLocation, "elvine", 6) == 0)
	{	m_bAresden = FALSE;
		m_bCitizen = TRUE;
		m_bHunter  = FALSE;
	}else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
	{	m_bAresden = FALSE;
		m_bCitizen = TRUE;
		m_bHunter  = TRUE;
	}else
	{	m_bAresden = TRUE;
		m_bCitizen = FALSE;
		m_bHunter  = TRUE;
	}

	cp = (char *)cp;
	memcpy(m_cGuildName, cp, 20);
	cp += 20;

	if (strcmp(m_cGuildName, "NONE") == 0)
		ZeroMemory(m_cGuildName, sizeof(m_cGuildName));

	m_Misc.ReplaceString(m_cGuildName, '_', ' ');
	ip   = (int *)cp;
	m_iGuildRank = *ip;
	cp += 4;
	m_iSuperAttackLeft = (int)*cp;
	cp++;
	ip   = (int *)cp;
	m_iFightzoneNumber = *ip;
	cp += 4;
}


void CGame::DisbandGuildResponseHandler(char * pData)
{WORD * wpResult;
 	wpResult = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	switch (*wpResult) {
	case DEF_MSGTYPE_CONFIRM:
		ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
		m_iGuildRank = -1;
		m_stDialogBoxInfo[7].cMode = 7;
		break;
	case DEF_MSGTYPE_REJECT:
		m_stDialogBoxInfo[7].cMode = 8;
		break;
	}
}

void CGame::NotifyMsg_BanGuildMan(char * pData)
{ char * cp, cName[24], cLocation[12];
	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cLocation, sizeof(cLocation));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 20);
	cp += 20;
	cp += 2;
	memcpy(cLocation, cp, 10);
	cp += 10;
	ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
	m_iGuildRank = -1;
	ZeroMemory(m_cLocation, sizeof(m_cLocation));
	memcpy(m_cLocation, cLocation, 10);
	if (memcmp(m_cLocation, "aresden", 7) == 0)
	{	m_bAresden = TRUE;
		m_bCitizen = TRUE;
		m_bHunter  = FALSE;
	}else if (memcmp(m_cLocation, "arehunter", 9) == 0)
	{	m_bAresden = TRUE;
		m_bCitizen = TRUE;
		m_bHunter  = TRUE;
	}else if (memcmp(m_cLocation, "elvine", 6) == 0)
	{	m_bAresden = FALSE;
		m_bCitizen = TRUE;
		m_bHunter  = FALSE;
	}else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
	{	m_bAresden = FALSE;
		m_bCitizen = TRUE;
		m_bHunter  = TRUE;
	}else
	{	m_bAresden = TRUE;
		m_bCitizen = FALSE;
		m_bHunter  = TRUE;
	}
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 8);
}

void CGame::_PutGuildOperationList(char * pName, char cOpMode)
{int i;
	for (i = 0; i < 100; i++)
	if (m_stGuildOpList[i].cOpMode == NULL)
	{	m_stGuildOpList[i].cOpMode = cOpMode;
		ZeroMemory(m_stGuildOpList[i].cName, sizeof(m_stGuildOpList[i].cName));
		memcpy(m_stGuildOpList[i].cName, pName, 20);
		return;
	}
}

void CGame::_ShiftGuildOperationList()
{int i;
	ZeroMemory(m_stGuildOpList[0].cName ,sizeof(m_stGuildOpList[0].cName));
	m_stGuildOpList[0].cOpMode = NULL;

	for (i = 1; i < 100; i++)
	if ((m_stGuildOpList[i-1].cOpMode == NULL) && (m_stGuildOpList[i].cOpMode != NULL)) {
		m_stGuildOpList[i-1].cOpMode = m_stGuildOpList[i].cOpMode;
		ZeroMemory(m_stGuildOpList[i-1].cName, sizeof(m_stGuildOpList[i-1].cName));
		memcpy(m_stGuildOpList[i-1].cName, m_stGuildOpList[i].cName, 20);

		ZeroMemory(m_stGuildOpList[i].cName ,sizeof(m_stGuildOpList[i].cName));
		m_stGuildOpList[i].cOpMode = NULL;
	}
}



void CGame::DlgBoxClick_GuildOp(short msX, short msY)
{
 short sX, sY;
 char cName[12], cName20[24];

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cName20, sizeof(cName20));
	sX = m_stDialogBoxInfo[8].sX;
	sY = m_stDialogBoxInfo[8].sY;

	switch (m_stGuildOpList[0].cOpMode) {
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			_ShiftGuildOperationList();
			if (m_stGuildOpList[0].cOpMode == NULL) DisableDialogBox(8);
		}
		return;
	}

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		// Approve
		PlaySound('E', 14, 5);

		switch (m_stGuildOpList[0].cOpMode) {
		case 1:
			strcpy(cName20, m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_JOINGUILDAPPROVE, NULL, NULL, NULL, NULL, cName20);
			break;

		case 2:
			strcpy(cName20, m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_DISMISSGUILDAPPROVE, NULL, NULL, NULL, NULL, cName20);
			break;
		}
		_ShiftGuildOperationList();
		if (m_stGuildOpList[0].cOpMode == NULL) DisableDialogBox(8);
	}

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		// Reject
		PlaySound('E', 14, 5);

		switch (m_stGuildOpList[0].cOpMode) {
		case 1:
			strcpy(cName20, m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_JOINGUILDREJECT, NULL, NULL, NULL, NULL, cName20);
			break;

		case 2:
			strcpy(cName20, m_stGuildOpList[0].cName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_DISMISSGUILDREJECT, NULL, NULL, NULL, NULL, cName20);
			break;
		}

		_ShiftGuildOperationList();
		if (m_stGuildOpList[0].cOpMode == NULL) DisableDialogBox(8);
	}
}

void CGame::SetItemCount(char * pItemName, DWORD dwCount)
{int i;
 char cTmpName[21];
	ZeroMemory(cTmpName, sizeof(cTmpName));
	strcpy(cTmpName, pItemName);
	for (i = 0; i < DEF_MAXITEMS; i++)
	if ((m_pItemList[i] != NULL) && (memcmp(m_pItemList[i]->m_cName, cTmpName, 20) == 0))
	{	m_pItemList[i]->m_dwCount = dwCount;
		return;
	}
}


void CGame::AddEventList(char * pTxt, char cColor, BOOL bDupAllow)
{int i;
	if ((bDupAllow == FALSE) && (strcmp(m_stEventHistory[5].cTxt, pTxt) == 0)) return;
	if (cColor == 10)
	{	for (i = 1; i < 6; i++)
		{	strcpy(m_stEventHistory2[i-1].cTxt, m_stEventHistory2[i].cTxt);
			m_stEventHistory2[i-1].cColor = m_stEventHistory2[i].cColor;
			m_stEventHistory2[i-1].dwTime = m_stEventHistory2[i].dwTime;
		}
		ZeroMemory(m_stEventHistory2[5].cTxt, sizeof(m_stEventHistory2[5].cTxt));
		strcpy(m_stEventHistory2[5].cTxt, pTxt);
		m_stEventHistory2[5].cColor = cColor;
		m_stEventHistory2[5].dwTime = m_dwCurTime;
	}else
	{	for (i = 1; i < 6; i++)
		{	strcpy(m_stEventHistory[i-1].cTxt, m_stEventHistory[i].cTxt);
			m_stEventHistory[i-1].cColor = m_stEventHistory[i].cColor;
			m_stEventHistory[i-1].dwTime = m_stEventHistory[i].dwTime;
		}
		ZeroMemory(m_stEventHistory[5].cTxt, sizeof(m_stEventHistory[5].cTxt));
		strcpy(m_stEventHistory[5].cTxt, pTxt);
		m_stEventHistory[5].cColor = cColor;
		m_stEventHistory[5].dwTime = m_dwCurTime;
	}
}

int _iAttackerHeight[] = {0, 35, 35,35,35,35,35, 0,0,0,
5,  // Slime
35, // Skeleton
40, // Stone-Golem
45, // Cyclops
35,// OrcMage
35,// ShopKeeper
5, // GiantAnt
8, // Scorpion
35,// Zombie
35,// Gandalf
35,// Howard
35,// Guard
10,// Amphis
38,// Clay-Golem
35,// Tom
35,// William
35,// Kennedy
35,// Hellhound
50,// Troll
45,// Orge
55,// Liche
65,// Demon
46,// Unicorn
49,// WereWolf
55,// Dummy
35,// Energysphere
75,// Arrow Guard Tower
75,// Cannon Guard Tower
50,// Mana Collector
50,// Detector
50,// Energy Shield Generator
50,// Grand Magic Generator
50,// ManaStone 42
40,// Light War Beetle
35,// GHK
40,// GHKABS
35,// TK
60,// BG
40,// Stalker
70,// HellClaw
85,// Tigerworm
50,// Catapult
85,// Gargoyle
70,// Beholder
40,// Dark-Elf
20,// Bunny
20,// Cat
40,// Giant-Frog
80,// Mountain-Giant
85,// Ettin
50,// Cannibal-Plant
50, // Rudolph 61 //Snoopy....
80, // Direboar 62
90, // Frost 63
40, // Crops 64
80, // IceGolem 65
190, // Wyvern 66
35, // npc 67
35, // npc 68
35, // npc 69
100, // Dragon 70
90, // Centaur 71
75, // ClawTurtle 72
200, // FireWyvern 73
80, // GiantCrayfish 74
120, // Gi Lizard 75
100, // Gi Tree 76
100, // Master Orc 77
80, // Minaus 78
100, // Nizie 79
25,  // Tentocle 80
200, // Abaddon	 81
60, // Sorceress 82
60, // ATK 83
70, // MasterElf 84
60, // DSK 85
50, // HBT 86
60, // CT 87
60, // Barbarian 88
60, // AGC 89
35, // ncp 90 Gail
35  // Gate 91
};

void CGame::bAddNewEffect(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1)
{int i;
 short sAbsX, sAbsY, sDist;
 long lPan;
 int  iV2 = 0;
	if (m_cDetailLevel == 0) // Detail Level Low
	{	switch (sType) {
		case 8:
		case 9:
		case 11:
		case 12:
		case 14:
		case 15:
			return;
	}	}
	if( m_bIsProgramActive == FALSE ) return;
  	sAbsX = abs(((m_sViewPointX / 32) + 10) - dX);
	sAbsY = abs(((m_sViewPointY / 32) + 7) - dY);
	if (sAbsX > sAbsY) sDist = sAbsX;
	else sDist = sAbsY;

	for (i = 0; i < DEF_MAXEFFECTS; i++)
	if (m_pEffectList[i] == NULL)
	{	m_pEffectList[i] = new class CEffect;
		m_pEffectList[i]->m_sType  = sType;
		m_pEffectList[i]->m_sX     = sX;
		m_pEffectList[i]->m_sY     = sY;
		m_pEffectList[i]->m_dX     = dX;
		m_pEffectList[i]->m_dY     = dY;
		m_pEffectList[i]->m_iV1    = iV1;
		m_pEffectList[i]->m_cFrame = cStartFrame;
		m_pEffectList[i]->m_dwTime = m_dwCurTime;

		switch (sType) {
		case 1: // coup normal
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - _iAttackerHeight[iV1];
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = 2;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 2:	// FlÍche qui vole
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - _iAttackerHeight[iV1];
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = 0;
			m_pEffectList[i]->m_dwFrameTime = 10;
			m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
			PlaySound('C', 4, sDist);
			break;

		case 4: // Gold
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32;
			m_pEffectList[i]->m_cMaxFrame   = 12;
			m_pEffectList[i]->m_dwFrameTime = 100;
			sAbsX = abs(((m_sViewPointX / 32) + 10) - sX);
			sAbsY = abs(((m_sViewPointY / 32) + 7)  - sY);
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			lPan = -(((m_sViewPointX / 32) + 10) - sX)*1000;
			PlaySound('E', 12, sDist, lPan);
			break;

		case 5: // FireBall Fire Explosion
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 11;
			m_pEffectList[i]->m_dwFrameTime = 10;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - sX)*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist);
			break;

		case 6:	 // Energy Bolt
		case 10: // Lightning Arrow
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 14;
			m_pEffectList[i]->m_dwFrameTime = 10;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(320 - (sX - m_sViewPointX))*1000;
			PlaySound('E', 2, sDist, lPan);
			SetCameraShakingEffect(sDist);
			break;

		case 7: // Magic Missile Explosion
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 5;
			m_pEffectList[i]->m_dwFrameTime = 50;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(320 - (sX - m_sViewPointX))*1000;
			PlaySound('E', 3, sDist, lPan);
			break;

		case 8: // Burst
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 4;
			m_pEffectList[i]->m_dwFrameTime = 30;
			break;

		case 9: // Burst
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_rX     =  6 - (rand() % 12);
			m_pEffectList[i]->m_rY     = -8 - (rand() % 6);
			m_pEffectList[i]->m_cMaxFrame   = 14;
			m_pEffectList[i]->m_dwFrameTime = 30;
			break;

		case 11:
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_rX     =  6 - (rand() % 12);
			if (iV2 == 0)
				 m_pEffectList[i]->m_rY     = -2 - (rand() % 4);
			else m_pEffectList[i]->m_rY     = -2 - (rand() % 10);
			m_pEffectList[i]->m_cMaxFrame   = 8;
			m_pEffectList[i]->m_dwFrameTime = 30;
			break;

		case 12: // Burst
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_rX    =  8 - (rand() % 16);
			m_pEffectList[i]->m_rY    =  4 - (rand() % 12);
			m_pEffectList[i]->m_cMaxFrame   = 10;
			m_pEffectList[i]->m_dwFrameTime = 30;
			break;

		case 13: // Bulles druncncity
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 18;
			m_pEffectList[i]->m_dwFrameTime = 20;
			break;

		case 14: // Traces de pas ou Tremor (pas en low detail)
			m_pEffectList[i]->m_mX    = sX;
			if (m_pEffectList[i]->m_iV1 > 0) // Case if hit by an arrow
			{	m_pEffectList[i]->m_mY = sY - (_iAttackerHeight[m_pEffectList[i]->m_iV1]/4 + rand()%(_iAttackerHeight[m_pEffectList[i]->m_iV1]/2) );
				m_pEffectList[i]->m_mX = sX + (rand()%5) -2;
			}else m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 4;
			m_pEffectList[i]->m_dwFrameTime = 100;
			m_pEffectList[i]->m_iV1 = iV1;
			break;

		case 15: //
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		case 16: //
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			break;

		case 17:
			m_pEffectList[i]->m_mX     = sX + (rand() % 20) - 40;
			m_pEffectList[i]->m_mY     = sY + (rand() % 20) - 40;
			m_pEffectList[i]->m_rX     =  8 - (rand() % 16);
			m_pEffectList[i]->m_rY     =  4 - (rand() % 12);
			m_pEffectList[i]->m_mX3    = sX;
			m_pEffectList[i]->m_mY3    = sY;
			m_pEffectList[i]->m_iV1    = 0;
			m_pEffectList[i]->m_dwFrameTime = 20;
			break;

		case 18:
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 10;
			m_pEffectList[i]->m_dwFrameTime = 50;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			SetCameraShakingEffect(sDist);
			break;

		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27: // Critical strike with a weapon
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = 0;
			m_pEffectList[i]->m_dwFrameTime = 10;
			m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
			break;

		case 30: // Mass-Fire-Strike (called 1 time)
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 9;
			m_pEffectList[i]->m_dwFrameTime = 40;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(320 - (sX - m_sViewPointX))*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist*2);
			break;

		case 31: // Mass-Fire-Strike (called 3 times)
		case 252: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 8;
			m_pEffectList[i]->m_dwFrameTime = 40;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(320 - (sX - m_sViewPointX))*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist);
			break;

		case 32: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = 4;
			m_pEffectList[i]->m_dwFrameTime = 100;
			break;

		case 33: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 34: //
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			SetCameraShakingEffect(sDist);
			break;

		case 35: // Snoopy: rajout (pour Mass Magic-Missile)
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 18;
			m_pEffectList[i]->m_dwFrameTime = 40;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(320 - (sX - m_sViewPointX))*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist*2);
			break;

		case 36: // Snoopy: Rajout (pour Mass Magic-Missile)
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 40;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(320 - (sX - m_sViewPointX))*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist);
			break;

		case 40: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 30;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			PlaySound('E', 45, sDist, lPan);
			break;

		case 41: // Large Type 1, 2, 3, 4
		case 42:
		case 43:
		case 44:
		case 45: // Small Type 1, 2
		case 46:
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY -220;
			m_pEffectList[i]->m_cMaxFrame   = 14;
			m_pEffectList[i]->m_dwFrameTime = 20;
			m_pEffectList[i]->m_iV1 = 20;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			PlaySound('E', 46, sDist, lPan);
			break;

		case 47: // Blizzard
		case 48: // Blizzard
		case 49: // Blizzard
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY -220;
			m_pEffectList[i]->m_cMaxFrame   = 12;
			m_pEffectList[i]->m_dwFrameTime = 20;
			m_pEffectList[i]->m_iV1 = 20;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			PlaySound('E', 46, sDist, lPan);
			break;

		case 50: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 12;
			m_pEffectList[i]->m_dwFrameTime = 50;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			if ((rand()%4) == 1) SetCameraShakingEffect(sDist);
			PlaySound('E', 47, sDist, lPan);
			break;

		case 51:
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 9; //15;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		case 52: // Protect ring
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 80;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 53: // Hold twist
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 80;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 54: // star twingkling (effect armes brillantes)
		case 55: // Unused
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 10;
			m_pEffectList[i]->m_dwFrameTime = 15;
			break;

		case 56: //  Mass-Chill-Wind
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 14;
			m_pEffectList[i]->m_dwFrameTime = 30;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			PlaySound('E', 45, sDist, lPan);
			break;

		case 57: //
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		case 60: //
			m_pEffectList[i]->m_mX    = sX +300;
			m_pEffectList[i]->m_mY    = sY -460;
			m_pEffectList[i]->m_cMaxFrame   = 10;
			m_pEffectList[i]->m_dwFrameTime = 50;
			break;

		case 61: //
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 10;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - sX)*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist, 2);
			break;

		case 62: //
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 6;
			m_pEffectList[i]->m_dwFrameTime = 100;
			break;

		case 63: //
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 20;
			break;

		case 64: //
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 20;
			break;

		case 65: // Crusade's MS
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 30;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		case 66: // Crusade MS explosion
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 14;
			m_pEffectList[i]->m_dwFrameTime = 30;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - sX)*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist, 2);
			break;

		case 67: // Crusade's MS fire + smoke ?
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 27;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 68: // worm-bite
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 17;
			m_pEffectList[i]->m_dwFrameTime = 30;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - sX)*1000;
			PlaySound('E', 4, sDist, lPan);
			m_pEffectList[i]->m_iV1 = sDist;
			//SetCameraShakingEffect(sDist, 2);
			break;

		case 69: // identique au cas 70
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 11;
			m_pEffectList[i]->m_dwFrameTime = 30;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - (sX/32))*1000;
			PlaySound('E', 42, sDist, lPan);
			break;

		case 70: // identtique au cas 69
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			m_pEffectList[i]->m_cMaxFrame   = 11;
			m_pEffectList[i]->m_dwFrameTime = 30;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - (sX/32))*1000;
			PlaySound('E', 42, sDist, lPan);
			break;

		case 71: //
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			SetCameraShakingEffect(sDist);
			break;

		case 72: // Blizzard
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 20;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			lPan = ((sX - m_sViewPointX)-320)*30;
			if ((rand()%4) == 1) SetCameraShakingEffect(sDist);
			PlaySound('E', 47, sDist, lPan);
			break;

		case 73:
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 60;
			break;

		case 74:
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 19;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 75: //ice golem
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_dX = dX;
			m_pEffectList[i]->m_dY = dY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 76: //ice golem
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_dX = dX;
			m_pEffectList[i]->m_dY = dY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 77: //ice golem
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_dX = dX;
			m_pEffectList[i]->m_dY = dY;
			m_pEffectList[i]->m_cMaxFrame   = 16;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 80: // Snoopy: rajouÈ, implÈmentÈ en dernier ds la v351
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_iV1    = 20;
			m_pEffectList[i]->m_cMaxFrame   = 30;
			m_pEffectList[i]->m_dwFrameTime = 25;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			SetCameraShakingEffect(sDist);
			break;

		case 81: //  Snoopy: Rajout (StormBlade)
			m_pEffectList[i]->m_mX		= sX*32;
			m_pEffectList[i]->m_mY		= sY*32;
			m_pEffectList[i]->m_iErr	= 0;
			m_pEffectList[i]->m_cMaxFrame   = 27;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 82: //  Snoopy: Rajout (Gate Apocalypse)
			m_pEffectList[i]->m_cMaxFrame   = 30;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 100: // MagicMissile is Flying
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 1, sDist, lPan);
			break;

		case 101: // Heal
		case 111: // Staminar-Drain
		case 121: // Great Heal
		case 123: // Staminar-Recovery
		case 128: // Great-Staminar-Recovery
			m_pEffectList[i]->m_cMaxFrame   = 14;
			m_pEffectList[i]->m_dwFrameTime = 80;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 102: // CreateFood
		case 122: // Recall
		case 126: // Possession
		case 127: // Poison
		case 134: // DetectInvi
		case 136: // Cure
		case 142: // Confuse language
		case 152: // Polymorph
		case 153: // Mass-Poison
		case 162: // Confusion
		case 171: // Mass-Confusion
			m_pEffectList[i]->m_cMaxFrame   = 13;
			m_pEffectList[i]->m_dwFrameTime = 120;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 110: // Energy-Bolt
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 1, sDist, lPan);
			break;

		case 112: // Recall
		case 131: // Summon
		case 132: // Invi
			m_pEffectList[i]->m_cMaxFrame   = 12;
			m_pEffectList[i]->m_dwFrameTime = 80;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 113: // Defense-Shield
		case 144: // Great-Defense-Shield
			m_pEffectList[i]->m_cMaxFrame   = 12;
			m_pEffectList[i]->m_dwFrameTime = 120;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 114: // Celebrating Light
			bAddNewEffect(69 +(rand()%2), dX*32 +20 - (rand() % 40), dY*32 +20 - (rand() % 40), NULL, NULL, -12);
			bAddNewEffect(69 +(rand()%2), dX*32 +20 - (rand() % 40), dY*32 +20 - (rand() % 40), NULL, NULL, -9);
			bAddNewEffect(69 +(rand()%2), dX*32 +20 - (rand() % 40), dY*32 +20 - (rand() % 40), NULL, NULL, -6);
			bAddNewEffect(69 +(rand()%2), dX*32 +20 - (rand() % 40), dY*32 +20 - (rand() % 40), NULL, NULL, -3);
			bAddNewEffect(69 +(rand()%2), dX*32 +20 - (rand() % 40), dY*32 +20 - (rand() % 40), NULL, NULL, 0);
			delete m_pEffectList[i];
			m_pEffectList[i] = NULL;
			break;

		case 120: // Fire Ball
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 1, sDist, lPan);
			break;

		case 124: // Protect form N.M
		case 133: // Protection from Magic
 			bAddNewEffect(52, dX*32, dY*32, NULL, NULL, 0, 0);
			delete m_pEffectList[i];
			m_pEffectList[i] = NULL;
			break;

		case 125: // Hold Person
		case 135: // Paralyze
			bAddNewEffect(53, dX*32, dY*32, NULL, NULL, 0, 0);
			delete m_pEffectList[i];
			m_pEffectList[i] = NULL;
			break;

		case 130: // Fire Strike
		case 137: // Lightning Arrow
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 1, sDist, lPan);
			break;

		case 138: // Tremor.
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 4, sDist, lPan);
			SetCameraShakingEffect(sDist, 2);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);

			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			m_pEffectList[i]->m_cMaxFrame   = 2;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 143: // Lightning
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 50;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_rX     = 5 - (rand() % 10);
			m_pEffectList[i]->m_rY	   = 5 - (rand() % 10);
			m_pEffectList[i]->m_cMaxFrame   = 7;
			m_pEffectList[i]->m_dwFrameTime = 10;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 40, sDist, lPan);
			break;

		case 145: // ChillWind
			m_pEffectList[i]->m_cMaxFrame   = 2;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 147: // Triple-Energy-Bolt
			m_pEffectList[i]->m_cMaxFrame   = NULL ;
			m_pEffectList[i]->m_dwFrameTime = 20;
			break;

		case 150: // Berserk : Cirlcle 6 magic
		case 177: // Illusion-Movement
		case 180: // Illusion
		case 183: // Inhibition-Casting
		case 190: // Mass-Illusion
		case 195: // Mass-Illusion-Movement
			m_pEffectList[i]->m_cMaxFrame   = 11;
			m_pEffectList[i]->m_dwFrameTime = 100;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 151: // LightningBolt
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 50;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_rX     = 5 - (rand() % 10);
			m_pEffectList[i]->m_rY	   = 5 - (rand() % 10);
			m_pEffectList[i]->m_cMaxFrame   = 10;
			m_pEffectList[i]->m_dwFrameTime = 10;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 40, sDist, lPan);
			break;

		case 156: // Mass-Ligtning-Arrow
			m_pEffectList[i]->m_cMaxFrame   = 3;
			m_pEffectList[i]->m_dwFrameTime = 130;
			break;

		case 157: // Ice-Strike
			m_pEffectList[i]->m_cMaxFrame   = 2;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 160: // Energy-Strike
			m_pEffectList[i]->m_cMaxFrame   = 7;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		case 161: // Mass-Fire-Strike
		case 251: //
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 1, sDist, lPan);
			break;

		case 163: // Mass-Chill-Wind
			m_pEffectList[i]->m_cMaxFrame   = 2;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 164: // worm-bite
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 4, sDist, lPan);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);

			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			bAddNewEffect(14, dX*32 + (rand() % 120) - 60, dY*32 + (rand() % 80) - 40, NULL, NULL, 0, 0);
			m_pEffectList[i]->m_cMaxFrame   = 1;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 165: // Absolute-Magic-Protection
			m_pEffectList[i]->m_cMaxFrame   = 21;
			m_pEffectList[i]->m_dwFrameTime = 70;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 166: // Armor Break
			m_pEffectList[i]->m_cMaxFrame   = 13;
			m_pEffectList[i]->m_dwFrameTime = 80;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 170: // Bloody-Shock-Wave
			m_pEffectList[i]->m_cMaxFrame   = 7;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		case 172: // Mass-Ice-Strike
			m_pEffectList[i]->m_cMaxFrame   = 2;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		case 174: // Lightning-Strike
			m_pEffectList[i]->m_cMaxFrame   = 5;
			m_pEffectList[i]->m_dwFrameTime = 120;
			break;

		case 176: // Snoopy: Ajout Cancellation
			m_pEffectList[i]->m_cMaxFrame   = 23;
			m_pEffectList[i]->m_dwFrameTime = 60;
			sDist = sDist / 32;
			lPan = -(((m_sViewPointX / 32) + 10) - sX)*1000;
			PlaySound('E', 5, sDist, lPan);
			break;

		case 181: // MS
			m_pEffectList[i]->m_mX    = dX*32 +300;
			m_pEffectList[i]->m_mY    = dY*32 -460;
			m_pEffectList[i]->m_cMaxFrame   = 10;
			m_pEffectList[i]->m_dwFrameTime = 25;
			break;

		case 182: // Snoopy: Ajout Mass-Magic-Missile
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32 - 40;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = NULL;
			m_pEffectList[i]->m_dwFrameTime = 20;
			lPan = -(((m_sViewPointX / 32) + 10) - dX)*1000;
			PlaySound('E', 1, sDist, lPan);
			break;

		case 244: // Snoopy: dÈplacÈ pour nvx sorts: Aura du casteur de Mass MagicMissile
		//case 184: // effet sur le caster pour MassMM
			m_pEffectList[i]->m_cMaxFrame   = 29;
			m_pEffectList[i]->m_dwFrameTime = 80;
			m_pEffectList[i]->m_mX    = sX;
			m_pEffectList[i]->m_mY    = sY;
			break;

		case 191: // Blizzard
			m_pEffectList[i]->m_cMaxFrame   = 7;
			m_pEffectList[i]->m_dwFrameTime = 80;
			break;

		//case 192: // Hero set Effect
		case 242: // Hero set Effect
			m_pEffectList[i]->m_cMaxFrame   = 30;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		//case 193: // Hero set Effect
		case 243: // Hero set Effect
			m_pEffectList[i]->m_cMaxFrame   = 19;
			m_pEffectList[i]->m_dwFrameTime = 18;
			break;

		case 194: // Resurrection
			m_pEffectList[i]->m_cMaxFrame   = 30;
			m_pEffectList[i]->m_dwFrameTime = 40;
			break;

		case 196: // Snoopy: Ajout de Earth-Shock-Wave
			m_pEffectList[i]->m_mX     = sX*32;
			m_pEffectList[i]->m_mY     = sY*32;
			m_pEffectList[i]->m_iErr   = 0;
			m_pEffectList[i]->m_cMaxFrame   = 30;
			m_pEffectList[i]->m_dwFrameTime = 25;
			sAbsX = abs(320 - (sX - m_sViewPointX));
			sAbsY = abs(240 - (sY - m_sViewPointY));
			if (sAbsX > sAbsY) sDist = sAbsX;
			else sDist = sAbsY;
			sDist = sDist / 32;
			SetCameraShakingEffect(sDist);
			break;
		case 200: //
		case 201: //
		case 202: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 15;
			m_pEffectList[i]->m_dwFrameTime = 25;
			break;

		case 203: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 18;
			m_pEffectList[i]->m_dwFrameTime = 70;
			break;

		case 204: //
		case 205: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 12;
			m_pEffectList[i]->m_dwFrameTime = 70;
			break;

		case 206: //
			m_pEffectList[i]->m_mX     = sX;
			m_pEffectList[i]->m_mY     = sY;
			m_pEffectList[i]->m_cMaxFrame   = 3;
			m_pEffectList[i]->m_dwFrameTime = 70;
			break;

		case 250: //
			m_pEffectList[i]->m_mX     = sX * 32;
			m_pEffectList[i]->m_mY     = sY * 32 -40;
			m_pEffectList[i]->m_iErr = 0;
			m_pEffectList[i]->m_cMaxFrame   = 0;
			m_pEffectList[i]->m_dwFrameTime = 10;
			break;

		default:
			delete m_pEffectList[i];
			m_pEffectList[i] = NULL;
			break;
		}
		if (m_pEffectList[i] != NULL)
		{	m_pEffectList[i]->m_mX2 = m_pEffectList[i]->m_mX;
			m_pEffectList[i]->m_mY2 = m_pEffectList[i]->m_mY;
		}
		return;
	}
}

void CGame::DrawEffects()
{int i, dX, dY, iDvalue,  tX, tY, rX, rY, rX2, rY2, rX3, rY3, rX4, rY4, rX5, rY5, iErr;
 char  cTempFrame;
 DWORD dwTime = m_dwCurTime;

 	for (i = 0;	i < DEF_MAXEFFECTS; i++)
	if ((m_pEffectList[i] != NULL) && (m_pEffectList[i]->m_cFrame >= 0))
	{	switch (m_pEffectList[i]->m_sType) {
		case 1: // Normal hit
			if (m_pEffectList[i]->m_cFrame < 0) break;
			dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			m_pEffectSpr[8]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 2: // Arrow flying
			dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*2;
			if (cTempFrame < 0) break;
			m_pEffectSpr[7]->PutSpriteFast(dX, dY, cTempFrame, dwTime);
			break;

		case 4: // gold
			/* 1.5
			if (m_pEffectList[i]->m_cFrame < 9) break;
			cTempFrame = m_pEffectList[i]->m_cFrame - 9;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[1]->PutSpriteFast(dX, dY-40, cTempFrame, dwTime);
			*/
			break;

		case 5: // FireBall Fire Explosion
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			iDvalue = (cTempFrame - 8)*(-5);
			if (cTempFrame < 7)
				 m_pEffectSpr[3]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			else m_pEffectSpr[3]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);
			break;

		case 6:	 // Energy Bolt
		case 10: // Lightning Arrow
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			iDvalue = (cTempFrame - 7)*(-6);
			if (cTempFrame < 6)
				 m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			else m_pEffectSpr[6]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 7: // Magic Missile Explosion
			cTempFrame = m_pEffectList[i]->m_cFrame;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			iDvalue = (cTempFrame - 4)*(-3);
			if (cTempFrame < 4)
				 m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			else m_pEffectSpr[6]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 8: // Burst
			cTempFrame = m_pEffectList[i]->m_cFrame;
			cTempFrame = 4 - cTempFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 9: // Burst
			cTempFrame = (rand() % 5);
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 11: // pt grenat
			cTempFrame = (rand() % 5) + 5;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			m_pEffectSpr[11]->PutTransSprite2(dX, dY, cTempFrame, dwTime);
			break;

		case 12: // Burst
			cTempFrame = (rand() % 6) + 10;
			if (cTempFrame < 0) break;
			iDvalue = (m_pEffectList[i]->m_cFrame - 4)*(-3);
			dX  = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			if (cTempFrame < 4)
				 m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			else //m_pEffectSpr[11]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			//
			m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);
			break;

		case 13:
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			if (cTempFrame < 13)
			{	m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, 25 + (cTempFrame / 5), dwTime);
			}else
			{	m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, (8 + cTempFrame), dwTime);
			}
			break;

		case 14: // Traces de pas (terrain sec)
			if (m_pEffectList[i]->m_cFrame < 0) break;
			dX  = m_pEffectList[i]->m_mX - m_sViewPointX;
			dY  = m_pEffectList[i]->m_mY - m_sViewPointY;
			m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, (28 + m_pEffectList[i]->m_cFrame), dwTime);
			break;

		case 15: // petits nuages rouges
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = m_pEffectList[i]->m_mX - m_sViewPointX;
			dY  = m_pEffectList[i]->m_mY - m_sViewPointY;
			m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, (33 + cTempFrame), dwTime);
			break;

		case 16: //
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 0, dwTime);
			break;

		case 17: //test
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = 39 + (rand() % 3)*3 + (rand() % 3);
			if (cTempFrame < 0) break;
			m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			dX  = (m_pEffectList[i]->m_mX2)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY2)  - m_sViewPointY;
			m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 18: //
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			m_pEffectSpr[18]->PutTransSprite70_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 20: // critical hit
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27: // Critical strike with a weapon
			dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
			dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
			m_pEffectSpr[8]->PutTransSprite_NoColorKey(dX, dY, 1, dwTime);
			break;

		case 30: // Mass-Fire-Strike
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			m_pEffectSpr[14]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 31: // Mass-Fire-Strike
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			m_pEffectSpr[15]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 32: // Trace de pas  (raining weather)
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame + 20;
			if (cTempFrame < 0) break;
			m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 33: //
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			iDvalue = 0;
			m_pEffectSpr[19]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 34: // absent (220 et 351)
			break;

		case 35: // Snoopy: Ajout
			if (m_pEffectList[i]->m_cFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX-30, dY-18, cTempFrame, dwTime);
			break;

		case 36: // Snoopy: Ajout
			if (m_pEffectList[i]->m_cFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			m_pEffectSpr[97]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 40:
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[20]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime); // 20
			break;

		case 41: // Large Type 1, 2, 3, 4
		case 42:
		case 43:
		case 44:
		case 45: // Small Type 1, 2
		case 46:
			dX  = (m_pEffectList[i]->m_sX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_sY)  - m_sViewPointY;
			m_pEffectSpr[21]->PutFadeSprite(dX, dY, 48, dwTime);
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			if ((8*(m_pEffectList[i]->m_sType-41) +cTempFrame) < (8*(m_pEffectList[i]->m_sType-41) +7))
			{	iDvalue = -8*(6 - cTempFrame);
				m_pEffectSpr[21]->PutTransSpriteRGB(dX, dY, 8*(m_pEffectList[i]->m_sType-41) +cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			}else
			{	if ((cTempFrame - 5) >= 8) cTempFrame = ((cTempFrame - 5) - 8) + 5;
				m_pEffectSpr[21]->PutSpriteFast(dX, dY, 8*(m_pEffectList[i]->m_sType-41) + (cTempFrame - 5), dwTime);
			}
			break;

		case 47:
		case 48:
		case 49: // Blizzard
			dX  = (m_pEffectList[i]->m_sX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_sY)  - m_sViewPointY;
			m_pEffectSpr[m_pEffectList[i]->m_sType-1]->PutRevTransSprite(dX, dY, 0, dwTime);
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			//PutString(dX, dY, "*", RGB(255,255,255));
			if (cTempFrame < 7) {
				iDvalue = -8*(6 - cTempFrame);
				m_pEffectSpr[m_pEffectList[i]->m_sType-1]->PutTransSpriteRGB(dX, dY, cTempFrame+1, iDvalue, iDvalue, iDvalue, dwTime);
			}
			else {
				if (cTempFrame >= 8) cTempFrame = cTempFrame % 8;
				m_pEffectSpr[m_pEffectList[i]->m_sType-1]->PutSpriteFast(dX, dY, cTempFrame+1, dwTime);
			}
			break;

		case 50:
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;

			if (cTempFrame <= 6) {
				iDvalue = 0;
				m_pEffectSpr[22]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);	// RGB2
			}
			else {
				iDvalue = -5*(cTempFrame - 6);
				m_pEffectSpr[22]->PutTransSpriteRGB(dX, dY, 6, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			}
			break;

		case 51: //
			cTempFrame = m_pEffectList[i]->m_cFrame + 11; //15
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[28]->PutTransSprite25(dX, dY, cTempFrame, dwTime); //20
			break;


		case 52: // Protection Ring commente par siementec, a voir
		/*			cTempFrame = m_pEffectList[i]->m_cFrame;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[24]->PutTransSprite(dX, dY, cTempFrame, dwTime);
		*/
			break;


		case 53: // Hold Twist
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			if (cTempFrame < 0) cTempFrame = 0;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[25]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime); //25
			break;

		case 54: //  star twingkling (effect armes brillantes)
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) cTempFrame = 0;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[28]->PutTransSprite(dX, dY, cTempFrame, dwTime);
			break;

		case 55: //
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) cTempFrame = 0;
			dX  = (m_pEffectList[i]->m_mX);
			dY  = (m_pEffectList[i]->m_mY);
			m_pEffectSpr[28]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 56: // Mass-Chill-Wind
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) cTempFrame = 0;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[29]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 57:  // absent (220 et 351)
			break;

		case 60:  //
		case 181: // MS
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			if (cTempFrame > 4)
			{	cTempFrame = cTempFrame / 4;
			}
			if (cTempFrame >= 0)
			{	dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				m_pEffectSpr[31]->PutSpriteFast(dX, dY, 15 + cTempFrame, dwTime);
				m_pEffectSpr[31]->PutTransSprite(dX, dY, cTempFrame, dwTime);
			}
			break;

		case 61: // Fire aura on ground (crueffect1, 1)
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[32]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 62: // MS strike
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			if (cTempFrame > 0)
			{	cTempFrame = cTempFrame - 1;
				dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				m_pEffectSpr[31]->PutRevTransSprite(dX, dY, 20 + cTempFrame, dwTime, cTempFrame/3);
			}
			break;

		case 63: // Fire explosion (crueffect1, 2)
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[33]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 64: // effet halo blancchatre
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[34]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 65: // MS from crusade striking
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			cTempFrame = cTempFrame / 6;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[31]->PutRevTransSprite(dX, dY, 20 + cTempFrame, dwTime, cTempFrame >> 2);
			break;

		case 66: // MS explodes on the ground
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[39]->PutRevTransSprite(dX, dY, cTempFrame, dwTime);
			m_pEffectSpr[39]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 67: // MS fire with smoke
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			switch (rand() % 3) {
			case 0: m_pEffectSpr[0]->PutTransSprite25_NoColorKey(dX, dY +20, 1, dwTime); break;
			case 1: m_pEffectSpr[0]->PutTransSprite50_NoColorKey(dX, dY +20, 1, dwTime); break;
			case 2: m_pEffectSpr[0]->PutTransSprite70_NoColorKey(dX, dY +20, 1, dwTime); break;
			}
			m_pEffectSpr[35]->PutTransSprite70_NoColorKey(dX, dY, cTempFrame/3, dwTime);
			break;

		case 68: // worm-bite
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			if (cTempFrame <= 11)
			{	m_pEffectSpr[40]->PutSpriteFast(dX, dY, cTempFrame, dwTime);
				m_pEffectSpr[41]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
				m_pEffectSpr[44]->PutRevTransSprite(dX-2, dY-3, cTempFrame, dwTime);
				m_pEffectSpr[44]->PutTransSprite_NoColorKey(dX-4, dY-3, cTempFrame, dwTime);
			}else
			{	switch (cTempFrame) {
				case 12:
				case 13:
				case 14: m_pEffectSpr[40]->PutSpriteFast(dX, dY, 11, dwTime); break;
				case 15: m_pEffectSpr[40]->PutTransSprite70_NoColorKey(dX, dY, 11, dwTime); break;
				case 16: m_pEffectSpr[40]->PutTransSprite50_NoColorKey(dX, dY, 11, dwTime); break;
				case 17: m_pEffectSpr[40]->PutTransSprite25_NoColorKey(dX, dY, 11, dwTime); break;
			}	}
			break;

		case 69: // identique au cas 70
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[42]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 70: // identique au cas 69
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[43]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 71: // absent v220 et v351
			break;

		case 72: // Blizzard
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			if (cTempFrame <= 8)
			{	iDvalue = 0;
				m_pEffectSpr[51]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);
			}else
			{	iDvalue = -1*(cTempFrame - 8);
				m_pEffectSpr[51]->PutTransSpriteRGB(dX, dY, 8, iDvalue, iDvalue, iDvalue, dwTime);	// RGB2
			}
			break;

		case 73: // absent v220 et v351
		case 74: // absent v220 et v351
		case 75: // absent v220 et v351
		case 76: // absent v220 et v351
		case 77: // absent v220 et v351
			break;

		case 80:
		case 196: // Earth-Shock-Wave
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[91]->PutSpriteFast(dX, dY, cTempFrame, dwTime); //Nbe d'arguments modifiÈs ds la 351....
			m_pEffectSpr[92]->PutTransSprite(dX, dY, cTempFrame, dwTime);
			break;

		case 81: // Snoopy: Ajout StormBlade
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = m_pEffectList[i]->m_cFrame;
			m_pEffectSpr[100]->PutTransSprite_NoColorKey(dX+70, dY+70, cTempFrame, dwTime);
			break;

		case 82: // Gate (apocalypse)
			cTempFrame = m_pEffectList[i]->m_cFrame;
			m_pEffectSpr[101]->PutTransSprite_NoColorKey(320, 480, cTempFrame, dwTime);
			break;

		case 100: // Magic Missile
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 0, dwTime);
			break;

		case 101: // Heal
		case 121: // Great-Heal
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			m_pEffectSpr[50]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 102: // Create Food
		case 124: // Protection from N.M
		case 125: // Hold-Person
		case 126: // Possession
		case 127: // Poison
		case 133: // Protect-From-Magic
		case 134: // Detect-Invisibility
		case 135: // Paralyze
		case 136: // Cure
		case 142: // Confuse Language
		case 152: // Polymorph
		case 153: // Mass-Poison
		case 162: // Confusion
		case 171: // Mass-Confusion
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			if (cTempFrame < 5)
				 m_pEffectSpr[4]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			else m_pEffectSpr[4]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 110: // Energy-Bolt
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 2 + (rand() % 4), dwTime);
			break;

		case 111: // Staminar Drain
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			m_pEffectSpr[49]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 112: // Recall
		case 131: // Summon-Creature
		case 132: // Invisibility
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			m_pEffectSpr[52]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 113: // Defense Shield
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			if (cTempFrame < 6)
				 m_pEffectSpr[62]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			else m_pEffectSpr[62]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 120: // Fire Ball
		case 130: // Fire Strike
		case 161: // Mass-Fire-Strike
		case 251: //
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[5]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			break;

		case 122: // Absent v220 et 351
			break;

		case 123: // Staminar-Recovery
		case 128: // Great-Staminar-Recovery
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			m_pEffectSpr[56]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 137: // Lightning Arrow
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			tX  = (m_pEffectList[i]->m_mX2)  - m_sViewPointX;
			tY  = (m_pEffectList[i]->m_mY2)  - m_sViewPointY;
			iErr = 0;
			m_Misc.GetPoint(dX, dY, tX, tY, &rX, &rY, &iErr, 15);
			m_Misc.GetPoint(dX, dY, tX, tY, &rX2, &rY2, &iErr, 30);
			m_Misc.GetPoint(dX, dY, tX, tY, &rX3, &rY3, &iErr, 45);
			m_Misc.GetPoint(dX, dY, tX, tY, &rX4, &rY4, &iErr, 60);
			m_Misc.GetPoint(dX, dY, tX, tY, &rX5, &rY5, &iErr, 75);
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[10]->PutTransSprite25_NoColorKey(rX5, rY5, cTempFrame, dwTime);
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[10]->PutTransSprite25_NoColorKey(rX4, rY4, cTempFrame, dwTime);
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[10]->PutTransSprite50_NoColorKey(rX3, rY3, cTempFrame, dwTime);
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[10]->PutTransSprite50_NoColorKey(rX2, rY2, cTempFrame, dwTime);
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[10]->PutTransSprite70_NoColorKey(rX,  rY, cTempFrame, dwTime);
			cTempFrame = (m_pEffectList[i]->m_cDir-1)*4 + (rand() % 4);
			if (cTempFrame < 0) break;
			m_pEffectSpr[10]->PutTransSprite(dX, dY, cTempFrame, dwTime);
			break;

		case 143: // Lightning
			_DrawThunderEffect(m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY - 800,
				                m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY,
								m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);
			_DrawThunderEffect(m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY - 800,
				                m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY,
								m_pEffectList[i]->m_rX+4, m_pEffectList[i]->m_rY+2, 2);
			_DrawThunderEffect(m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY - 800,
				                m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY,
								m_pEffectList[i]->m_rX-2, m_pEffectList[i]->m_rY-2, 2);
			break;

		case 144: // Great-Defense-Shield
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-5);
			if (cTempFrame < 9)
				 m_pEffectSpr[63]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			else m_pEffectSpr[63]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 151: // Lightning Bolt
			_DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
				                m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY,
								m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);

			_DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
				                m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY,
								m_pEffectList[i]->m_rX+2, m_pEffectList[i]->m_rY-2, 2);

			_DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
				                m_pEffectList[i]->m_dX*32 - m_sViewPointX, m_pEffectList[i]->m_dY*32 - m_sViewPointY,
								m_pEffectList[i]->m_rX-2, m_pEffectList[i]->m_rY-2, 2);
			break;

		case 165: // Absolute-Magic-Protect
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY; // 53 = APFM buble
			m_pEffectSpr[53]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 166: // Armor-Break
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[55]->PutRevTransSprite(dX, dY+35, m_pEffectList[i]->m_cFrame, dwTime);
			m_pEffectSpr[54]->PutTransSprite50(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 176: // Cancellation
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[90]->PutTransSprite_NoColorKey(dX+50, dY+85, cTempFrame, dwTime);
			break;

		case 177: // Illusion-Movement
		case 180: // Illusion
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-3);
			if (cTempFrame < 9)	m_pEffectSpr[60]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			else m_pEffectSpr[60]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		case 182: //Mass-Magic-Missile
			cTempFrame = m_pEffectList[i]->m_cFrame;
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[98]->PutTransSprite(dX, dY, cTempFrame, dwTime, 0);
		break;

		case 183: // Inhibition-Casting
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-3);
			if (cTempFrame < 9) m_pEffectSpr[94]->PutTransSprite_NoColorKey(dX, dY + 40, m_pEffectList[i]->m_cFrame, dwTime);
			else m_pEffectSpr[94]->PutTransSpriteRGB(dX, dY + 40, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime);
			break;

		case 244: // Snoopy: dÈplacÈ pour nvx sorts: Aura du casteur de Mass MagicMissile
		//case 184: // Aura du casteur de Mass MagicMissile
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = m_pEffectList[i]->m_mX - m_sViewPointX;
			dY  = m_pEffectList[i]->m_mY - m_sViewPointY;
			m_pEffectSpr[96]->PutTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime, 0);
			break;

		case 190: // Mass-Illusion
		case 195: // Mass-Illusion-Movement
			cTempFrame = m_pEffectList[i]->m_cFrame;
			if (cTempFrame < 0) break;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			iDvalue = (cTempFrame - 5)*(-3);
			if (cTempFrame < 9) m_pEffectSpr[61]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			else m_pEffectSpr[61]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
			break;

		//case 192: // Mage Hero set effect
		case 242:
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[87]->PutTransSprite_NoColorKey(dX+50, dY+57, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		//case 193: // War Hero set effect
		case 243:
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[88]->PutTransSprite_NoColorKey(dX+65, dY+80, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 194: // Resurrection
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[99]->PutTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime, 0);
			break;

		case 200: // shotstar fall on ground
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[133]->PutTransSprite_NoColorKey(dX, dY, (rand() %15), dwTime);
			break;

		case 201: // shotstar fall on ground
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[134]->PutTransSprite_NoColorKey(dX, dY, (rand() %15), dwTime);
			break;

		case 202: // shotstar fall on ground
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[135]->PutTransSprite_NoColorKey(dX, dY, (rand() %15), dwTime);
			break;

		case 203: // explosion feu apoc
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[136]->PutTransSprite_NoColorKey(dX, dY, (rand() %18), dwTime);
			break;

		case 204: // Faille oblique
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[137]->PutTransSprite_NoColorKey(dX, dY, (rand() %12), dwTime);
			break;

		case 205: // Faille horizontale
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[138]->PutTransSprite_NoColorKey(dX, dY, (rand() %12), dwTime);
			break;

		case 206: // steams
			dX  = m_pEffectList[i]->m_mX;
			dY  = m_pEffectList[i]->m_mY;
			m_pEffectSpr[139]->PutTransSprite_NoColorKey(dX, dY, (rand() %20), dwTime);
			break;

		case 250: // Gate (round one)
			dX  = m_pEffectList[i]->m_mX - m_sViewPointX;
			dY  = m_pEffectList[i]->m_mY - m_sViewPointY;
			m_pEffectSpr[103]->PutTransSprite_NoColorKey(dX, dY, (rand() %3), dwTime);
			break;

		case 252: // burst (lisgt salmon color)
			dX  = m_pEffectList[i]->m_mX - m_sViewPointX;
			dY  = m_pEffectList[i]->m_mY - m_sViewPointY;
			m_pEffectSpr[104]->PutTransSprite_NoColorKey(dX, dY, (rand() %3), dwTime);
			break;
		}
	}
}

#include "Game-2.cpp"
#include "Game-3.cpp"
#include "Game-4.cpp"
#include "Game-5.cpp"
#include "Game-6.cpp"