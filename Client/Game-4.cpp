
void CGame::NotifyMsg_QuestContents(char *pData)
{short * sp;
 char  * cp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	sp = (short *)cp;
	m_stQuest.sWho = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sQuestType = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sContribution = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sTargetType = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sTargetCount = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sX = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sY = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.sRange = *sp;
	cp += 2;
	sp = (short *)cp;
	m_stQuest.bIsQuestCompleted = (BOOL)*sp;
	cp += 2;
	ZeroMemory(m_stQuest.cTargetName, sizeof(m_stQuest.cTargetName));
	memcpy(m_stQuest.cTargetName, cp, 20);
	cp += 20;
	// v2.05
	//AddEventList(m_pGameMsgList[92]->m_pMsg, 10);
}

void CGame::NotifyMsg_PlayerProfile(char * pData)
{char * cp;
 char cTemp[500];
 int i;
	ZeroMemory(cTemp, sizeof(cTemp));
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	strcpy(cTemp, cp);
	for (i = 0; i < 500; i++)
	if (cTemp[i] == '_') cTemp[i] = ' ';
	AddEventList(cTemp, 10);
}

void CGame::NotifyMsg_NoticeMsg(char * pData)
{char * cp, cMsg[1000];
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	strcpy(cMsg, cp);
	AddEventList(cMsg, 10);
}
/*********************************************************************************************************************
**  void CGame::NotifyMsg_OpenExchageWindow(char *pData)		(snoopy)											**
**  description			:: Recieve a msg from gserver and sets the item	and opens trade windows						**
**********************************************************************************************************************/
void CGame::NotifyMsg_OpenExchageWindow(char *pData)
{short * sp, sDir, sSprite, sSpriteFrame, sCurLife, sMaxLife, sPerformance;
 int * ip, iAmount;
 char * cp, cColor, cItemName[24], cCharName[12];
 DWORD * dwp, dwAttribute;
	ZeroMemory(cItemName, sizeof(cItemName));
	ZeroMemory(cCharName, sizeof(cCharName));

	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	sp = (short *)cp;
	sDir = *sp;
	cp += 2;
	sp = (short *)cp;
	sSprite = *sp;
	cp += 2;
	sp = (short *)cp;
	sSpriteFrame = *sp;
	cp += 2;
	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;
	cColor = *cp;
	cp++;
	sp = (short *)cp;
	sCurLife = *sp;
	cp += 2;
	sp = (short *)cp;
	sMaxLife = *sp;
	cp += 2;
	sp = (short *)cp;
	sPerformance = *sp;
	cp += 2;
	memcpy(cItemName, cp, 20);
	cp += 20;
	memcpy(cCharName, cp, 10);
	cp += 10;
	dwp = (DWORD *)cp;
	dwAttribute = *dwp;
	cp += 4;

	EnableDialogBox(27, 1, 0, 0, NULL);
	int i;
	if (sDir >= 1000)  // Set the item I want to exchange
	{	i = 0;
		while (m_stDialogBoxExchangeInfo[i].sV1 !=-1)
		{	i++;
			if (i>=4) return; // Error situation
		}
		if ((sDir >1000) && (i == 0))
		{	m_bIsItemDisabled[sDir -1000] = TRUE;
			m_stDialogBoxExchangeInfo[0].sItemID = sDir -1000;
		}
	}else // Set the item he proposes me.
	{	i = 4;
		while (m_stDialogBoxExchangeInfo[i].sV1 !=-1)
		{	i++;
			if (i>=8) return; // Error situation
	}	}
	m_stDialogBoxExchangeInfo[i].sV1 = sSprite;
	m_stDialogBoxExchangeInfo[i].sV2 = sSpriteFrame;
	m_stDialogBoxExchangeInfo[i].sV3 = iAmount;
	m_stDialogBoxExchangeInfo[i].sV4 = cColor;
	m_stDialogBoxExchangeInfo[i].sV5 = (int)sCurLife;
	m_stDialogBoxExchangeInfo[i].sV6 = (int)sMaxLife;
	m_stDialogBoxExchangeInfo[i].sV7 = (int)sPerformance;
	memcpy(m_stDialogBoxExchangeInfo[i].cStr1, cItemName, 20);
	memcpy(m_stDialogBoxExchangeInfo[i].cStr2, cCharName, 10);
	m_stDialogBoxExchangeInfo[i].dwV1 = dwAttribute;
}

void CGame::NotifyMsg_JoinGuildApprove(char * pData)
{char * cp, cName[21];
 short * sp;
	ZeroMemory(cName, sizeof(cName));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 20);
	cp += 20;
	sp = (short *)cp;
	cp += 2;
	ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
	strcpy(m_cGuildName, cName);
	m_iGuildRank = *sp;
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 3);
}


void CGame::NotifyMsg_JoinGuildReject(char * pData)
{char * cp, cName[21];
	ZeroMemory(cName, sizeof(cName));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 20);
	cp += 20;
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 4);
}

void CGame::DlgBoxClick_Help(int msX, int msY)
{ short sX, sY;
	sX = m_stDialogBoxInfo[35].sX;
	sY = m_stDialogBoxInfo[35].sY;
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*0) && (msY < sY +50+15*1))
	{	DisableDialogBox(18);
		EnableDialogBox(18, 1000, NULL, NULL);
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*1) && (msY < sY +50+15*2)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 900, NULL, NULL);
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*2) && (msY < sY +50+15*3)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 901, NULL, NULL);
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*3) && (msY < sY +50+15*4)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 902, NULL, NULL);
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*4) && (msY < sY +50+15*5)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 903, NULL, NULL);
		m_bIsF1HelpWindowEnabled = TRUE;
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*5) && (msY < sY +50+15*6)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 904, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*6) && (msY < sY +50+15*7)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 905, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*7) && (msY < sY +50+15*8)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 906, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*8) && (msY < sY +50+15*9)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 907, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*9) && (msY < sY +50+15*10)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 908, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*10) && (msY < sY +50+15*11)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 909, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*11) && (msY < sY +50+15*12)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 910, NULL, NULL); //
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*12) && (msY < sY +50+15*13)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 911, NULL, NULL); // FAQ
	}

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*13) && (msY < sY +50+15*14)) {
		DisableDialogBox(18);
		EnableDialogBox(18, 912, NULL, NULL); //
	}
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		PlaySound('E', 14, 5);
		DisableDialogBox(35);
	}
}

/*********************************************************************************************************************
** void CGame::CreateScreenShot()										(snoopy)									**
**  description			:: Fixed Screen Shots																		**
**********************************************************************************************************************/
void CGame::CreateScreenShot()
{	//HelShot20060307_173003_Warehouse000.jpg
 int i;
 FILE * pFile;
 char cFn[256];
 char LongMapName[128];
 char SStime[32];
 SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	ZeroMemory(LongMapName, sizeof(LongMapName));
	GetOfficialMapName(m_cMapName, LongMapName);
	ZeroMemory(SStime, sizeof(SStime));
	wsprintf(SStime, "%02d:%02d - %02d:%02d:%02d"
		, SysTime.wMonth, SysTime.wDay
		, SysTime.wHour, SysTime.wMinute, SysTime.wSecond
		, LongMapName);
	PutAlignedString(500, 600, 30, SStime, 255, 255, 255); //ScreenShot time
	PutString_SprFont3(500, 390, " Client coded by", 20, 20, 0, TRUE, 2);
	PutString_SprFont3(500, 405, "Diuuude & Snoopy81", 0, 20, 20, TRUE, 2);

	if (strcmp(m_cWorldServerName, NAME_WORLDNAME1) == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME1,255,255,255);//"ABADDON Server"
	else if (strcmp(m_cWorldServerName, "WS2") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME2,255,255,255);//"APOCALYPSE Server"
	else if (strcmp(m_cWorldServerName, "WS3") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME3,255,255,255);//"3rd Server"
	else if (strcmp(m_cWorldServerName, "WS4") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME4,255,255,255);//"4th Server"
	else if (strcmp(m_cWorldServerName, "WS5") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME5,255,255,255);//"5th Server"
	else if (strcmp(m_cWorldServerName, "WS6") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME6,255,255,255);//"6th Server"
	else if (strcmp(m_cWorldServerName, "WS7") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME7,255,255,255);//"7th Server"
	else if (strcmp(m_cWorldServerName, "WS8") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME8,255,255,255);//"8th Server"
	else if (strcmp(m_cWorldServerName, "WS9") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME9,255,255,255);//"9th Server"
	else if (strcmp(m_cWorldServerName, "WS10") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME10,255,255,255);//"10th Server"
	else if (strcmp(m_cWorldServerName, "WS11") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME11,255,255,255);//"11th Server"
	else if (strcmp(m_cWorldServerName, "WS12") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME12,255,255,255);//"12th Server"
	else if (strcmp(m_cWorldServerName, "WS13") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME13,255,255,255);//"13th Server"
	else if (strcmp(m_cWorldServerName, "WS14") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME14,255,255,255);//"14th Server"
	else if (strcmp(m_cWorldServerName, "WS15") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME15,255,255,255);//"15th Server"
	else if (strcmp(m_cWorldServerName, "WS16") == 0)
		PutAlignedString(500, 600, 15, MSG_WORLDNAME16,255,255,255);//"16th Server"

	for (i = 0; i < 1000; i++)
	{	ZeroMemory(cFn, sizeof(cFn));
		wsprintf(cFn, "Save\\HelShot%04d%02d%02d_%02d%02d%02d_%s%03d.jpg"
			, SysTime.wYear, SysTime.wMonth, SysTime.wDay
			, SysTime.wHour, SysTime.wMinute, SysTime.wSecond
			, LongMapName
			,i);
		_mkdir("SAVE");
		pFile = fopen(cFn, "rb");
		if (pFile == NULL)
		{	m_DDraw.Screenshot(cFn, m_DDraw.m_lpBackB4);
			CxImage  image;
			image.Load(cFn, CXIMAGE_FORMAT_BMP);
			if (image.IsValid())
			{   image.SetJpegQuality(80);
			    image.Save(cFn,CXIMAGE_FORMAT_JPG);
			}
			wsprintf(G_cTxt, NOTIFYMSG_CREATE_SCREENSHOT1, cFn);
			AddEventList(G_cTxt, 10);
			return;
		}
		fclose(pFile);
	}
	AddEventList(NOTIFYMSG_CREATE_SCREENSHOT2, 10);
}

void CGame::UpdateScreen_OnConnecting()
{
 short sX, sY, msX, msY, msZ;
 char cLB, cRB;
 DWORD dwTime = timeGetTime();
 static class CMouseInterface * pMI;
 static DWORD dwMTime, dwCTime;

	if (m_cGameModeCount == 0) {
		m_bEnterPressed = FALSE;
		m_bEscPressed   = FALSE;
		dwCTime = dwMTime = timeGetTime();
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_bEscPressed == TRUE) {

		if ((dwTime - m_dwTime) > 1000)
		{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			if (m_pLSock != NULL)
			{	delete m_pLSock;
				m_pLSock = NULL;
			}
			if (m_pGSock != NULL)
			{	delete m_pGSock;
				m_pGSock = NULL;
		}	}
		m_bEscPressed = FALSE;
		return;
	}

	if ((dwTime - dwMTime) > 150) dwMTime = dwTime;

	if ((dwTime - dwCTime) > 100) {
		m_cMenuFrame++;
		dwCTime = dwTime;
	}
	if (m_cMenuFrame >= 8) {
		m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8) {
			m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;

	m_DDraw.ClearBackB4();

	m_bIsHideLocalCursor = TRUE;
	switch (m_cMsg[0]) {
	case '0':
		_Draw_UpdateScreen_OnCreateNewAccount();
		break;

	case '1':
		sX = 146;
		sY = 114;
		_Draw_OnLogin(m_cAccountName, m_cAccountPassword, 0, 0);
		break;

	case '2':
		_bDraw_OnCreateNewCharacter(m_cPlayerName, 0, 0, 0);
		break;

	case '3':
		UpdateScreen_OnSelectCharacter(0, 0, 0, 0);
		break;

	case '4':
		// Change Password
		UpdateScreen_OnSelectCharacter(0, 0, 0, 0, TRUE);
		break;

	case '5':
		m_DDraw.ClearBackB4();
		break;
	}
	m_bIsHideLocalCursor = FALSE;

	m_DDraw.DrawShadowBox(0,0,639,479);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);
	wsprintf(G_cTxt, "Connecting to Server... %3dSec", (dwTime - m_dwTime)/1000);
	PutString_SprFont(172 + 35, 190, G_cTxt, 7,0,0);

	if ((dwTime - m_dwTime) > 7000)
	{	PutAlignedString(180, 463, 195+30, UPDATE_SCREEN_ON_CONNECTING1);//"Press ESC key during long time of no"
		PutAlignedString(180, 463, 195+45, UPDATE_SCREEN_ON_CONNECTING2);//"connection and return to the main menu."
	}
	else PutAlignedString(180, 463, 195+30, UPDATE_SCREEN_ON_CONNECTING3);//"  Connecting to server. Please wait..."
	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 8, dwTime);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::UpdateScreen_OnWaitInitData()
{
 short msX, msY, msZ;
 char cLB, cRB;
 DWORD dwTime = timeGetTime();

	if (m_cGameModeCount == 0) {
		m_bEnterPressed = FALSE;
		m_bEscPressed   = FALSE;
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_bEscPressed == TRUE) {
		if ((dwTime - m_dwTime) > 7000)
		{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			if (m_pLSock != NULL)
			{	delete m_pLSock;
				m_pLSock = NULL;
			}
			if (m_pGSock != NULL)
			{	delete m_pGSock;
				m_pGSock = NULL;
		}	}
		m_bEscPressed = FALSE;
		return;
	}

	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);

	wsprintf(G_cTxt,"Waiting for response... %dsec", (dwTime - m_dwTime)/1000);
	PutString_SprFont(172+ 44, 190, G_cTxt, 7,0,0);
	if ((dwTime - m_dwTime) > 7000) {
		PutAlignedString(174, 467, 190+30, UPDATE_SCREEN_ON_WAIT_INIT_DATA1);//"Press ESC key during long time of no"
		PutAlignedString(174, 467, 190+45, UPDATE_SCREEN_ON_WAIT_INIT_DATA2);//"connection and return to the main menu."
	}
	else PutAlignedString(174, 467, 195+30, UPDATE_SCREEN_ON_WAIT_INIT_DATA3);//  Connecting to server. Please wait..."

	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 8, dwTime);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::UpdateScreen_OnConnectionLost()
{short msX, msY, msZ;
 char cLB, cRB;
 static DWORD dwTime;
	if (m_cGameModeCount == 0)
	{	dwTime = timeGetTime();
		if (m_bSoundFlag) m_pESound[38]->bStop();
		if ((m_bSoundFlag) && (m_bMusicStat == TRUE))
		{
			if (m_pBGM != NULL) m_pBGM->bStop();
	}	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;
	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);
	PutString_SprFont(172 + 54, 180, "Connection Lost!", 7,0,0);
	PutString(172+50, 180+30, UPDATE_SCREEN_ON_CONNECTION_LOST, RGB(0,0,0));//"
	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();

	if ((timeGetTime() - m_dwTime) > 5000)
	{	if (strlen(G_cCmdLineTokenA) != 0)
			 ChangeGameMode(DEF_GAMEMODE_ONQUIT);
		else
		{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
	}	}
}

BOOL CGame::_bDraw_OnCreateNewCharacter(char * pName, short msX, short msY, int iPoint)
{
 BOOL bFlag = TRUE;
 DWORD dwTime = timeGetTime();
 int i=0;

	m_DDraw.ClearBackB4();

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWCHAR, 0, 0, 0, TRUE);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 69, TRUE);
	PutAlignedString(64, 282, 90, _BDRAW_ON_CREATE_NEW_CHARACTER1, 5,5,5);//"
	PutAlignedString(57, 191, 110, DEF_MSG_CHARACTERNAME, 5,5,5);//"Character Name"
	if (m_cCurFocus != 1) PutString(197, 112, pName, RGB(25,35,25));
	PutAlignedString(64, 282, 140, _BDRAW_ON_CREATE_NEW_CHARACTER2, 5,5,5);//"
	PutString(100, 160, DEF_MSG_GENDER, RGB(5,5,5));//"Gender"
	PutString(100, 175, DEF_MSG_SKINCOLOR, RGB(5,5,5));//"Skin Color"
	PutString(100, 190, DEF_MSG_HAIRSTYLE, RGB(5,5,5));//"Hair Style"
	PutString(100, 205, DEF_MSG_HAIRCOLOR, RGB(5,5,5));//"Hair Color"
	PutString(100, 220, DEF_MSG_UNDERWEARCOLOR, RGB(5,5,5));//"Underwear Color"
	//PutAlignedString(64, 282, 245, _BDRAW_ON_CREATE_NEW_CHARACTER3, 5,5,5);
	//wsprintf(G_cTxt, _BDRAW_ON_CREATE_NEW_CHARACTER4,  iPoint);//" %d points"
	//PutAlignedString(64, 282, 260, G_cTxt, 15,10,10);
	PutString(100, 275, DEF_MSG_STRENGTH, RGB(5,5,5));//"Strength"
	PutString(100, 292, DEF_MSG_VITALITY, RGB(5,5,5));//"Vitality"
	PutString(100, 309, DEF_MSG_DEXTERITY, RGB(5,5,5));//"Dexterity"
	PutString(100, 326, DEF_MSG_INTELLIGENCE, RGB(5,5,5));//"Intelligence"
	PutString(100, 343, DEF_MSG_MAGIC, RGB(5,5,5));//"Magic"
	PutString(100, 360, DEF_MSG_CHARISMA, RGB(5,5,5));//"Charisma"

	wsprintf(G_cTxt, "%d", m_ccStr);
	PutString(204 , 277+ 16*i++ , G_cTxt, RGB(25,35,25));
	wsprintf(G_cTxt, "%d", m_ccVit);
	PutString(204 , 277+ 16*i++ , G_cTxt, RGB(25,35,25));
	wsprintf(G_cTxt, "%d", m_ccDex);
	PutString(204 , 277+ 16*i++ , G_cTxt, RGB(25,35,25));
	wsprintf(G_cTxt, "%d", m_ccInt);
	PutString(204 , 277+ 16*i++ , G_cTxt, RGB(25,35,25));
	wsprintf(G_cTxt, "%d", m_ccMag);
	PutString(204 , 277+ 16*i++ , G_cTxt, RGB(25,35,25));
	wsprintf(G_cTxt, "%d", m_ccChr);
	PutString(204 , 277+ 16*i++ , G_cTxt, RGB(25,35,25));

	if (strlen(pName) <= 0) bFlag = FALSE;
	if (iPoint > 0) bFlag = FALSE;
	if (m_Misc.bCheckValidName(pName) == FALSE) bFlag = FALSE;
	if (_bCheckBadWords(pName) == TRUE) bFlag = FALSE;

	if ( (bFlag == TRUE) && (m_cCurFocus == 2) ) m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(384, 445, 25, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(384, 445, 24, dwTime);
	if (m_cCurFocus == 3)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(500, 445, 17, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(500, 445, 16, dwTime);
	if (m_cCurFocus == 4)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 445, 68, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 445, 67, dwTime);
	if (m_cCurFocus == 5)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 445, 66, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 445, 65, dwTime);
	if (m_cCurFocus == 6)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 445, 64, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 445, 63, dwTime);
	/*if (m_cCurFocus == 4)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 245, 68, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 245, 67, dwTime);
	if (m_cCurFocus == 5)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 245, 66, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 245, 65, dwTime);
	if (m_cCurFocus == 6)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 245, 64, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 245, 63, dwTime);*/

	ShowReceivedString();

	switch (m_cGender) {
	case 1:	_tmp_sOwnerType = 1; break;
	case 2:	_tmp_sOwnerType = 4; break; //@@@@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!
	}
	_tmp_sOwnerType += m_cSkinCol - 1;
	_tmp_cDir   = m_cMenuDir;
	_tmp_sAppr1 = 0;
	_tmp_sAppr1 = _tmp_sAppr1 | (m_cUnderCol);
	_tmp_sAppr1 = _tmp_sAppr1 | (m_cHairStyle << 8);
	_tmp_sAppr1 = _tmp_sAppr1 | (m_cHairCol << 4);
	_tmp_sAppr2 = 0;
	_tmp_sAppr3 = 0;
	_tmp_sAppr4 = 0;
	ZeroMemory(_tmp_cName, sizeof(_tmp_cName));
	memcpy(_tmp_cName, m_cPlayerName,10);
	_tmp_cAction = DEF_OBJECTMOVE;
	_tmp_cFrame = m_cMenuFrame;

	_Draw_CharacterBody( 507 , 267, _tmp_sOwnerType);

	DrawObject_OnMove_ForMenu(0, 0, 500 , 174, FALSE, dwTime, msX, msY);

    i = 0 ;

	PutString(445, 192, DEF_MSG_HITPOINT, RGB(5,5,5));//"Hit Point"
	wsprintf(G_cTxt, "%d", m_ccVit*3 + 2 + m_ccStr/2);
	PutString(550, 192 + 16*i++, G_cTxt, RGB(25,35,25));

	PutString(445, 208, DEF_MSG_MANAPOINT, RGB(5,5,5));//"Mana Point"
	wsprintf(G_cTxt, "%d", m_ccMag*2 + 2 + m_ccInt/2);
	PutString(550, 192 + 16*i++, G_cTxt, RGB(25,35,25));

	PutString(445, 224, DEF_MSG_STAMINARPOINT, RGB(5,5,5));//"Staminar Point"
	wsprintf(G_cTxt, "%d", m_ccStr*2 + 2);
	PutString(550, 192 + 16*i++, G_cTxt, RGB(25,35,25));

	return bFlag;
}

void CGame::UpdateScreen_OnCreateNewCharacter()
{static class CMouseInterface * pMI;
 int i=0;
 int iMIbuttonNum;
 static int iPoint;
 char cLB, cRB, cMIresult;
 static char cName[12];
 static char cPrevFocus;
 short msX, msY, msZ;
 BOOL bFlag;
 static DWORD dwMTime;
 DWORD dwTime = timeGetTime();

	if (m_cGameModeCount == 0)
	{	pMI = new class CMouseInterface;
		pMI->AddRect(65+4, 65+45, 275+4, 82+45);

		pMI->AddRect(232+4, 111+45, 274+4 -21, 124+45);
		pMI->AddRect(255+4, 111+45, 289+4 -13, 124+45);

		pMI->AddRect(232+4, 126+45, 274+4 -21, 139+45);
		pMI->AddRect(255+4, 126+45, 289+4 -13, 139+45);

		pMI->AddRect(232+4, 141+45, 274+4 -21, 154+45);
		pMI->AddRect(255+4, 141+45, 289+4 -13, 154+45);

		pMI->AddRect(232+4, 156+45, 274+4 -21, 169+45);
		pMI->AddRect(255+4, 156+45, 289+4 -13, 169+45);

		pMI->AddRect(232+4, 171+45, 274+4 -21, 184+45);
		pMI->AddRect(255+4, 171+45, 289+4 -13, 184+45);


		pMI->AddRect(232+4, 231+45, 253+4, 244+45);
		pMI->AddRect(255+4, 231+45, 276+4, 244+45);

		pMI->AddRect(232+4, 246+45, 253+4, 259+45);
		pMI->AddRect(255+4, 246+45, 276+4, 259+45);

		pMI->AddRect(232+4, 261+45, 253+4, 274+45);
		pMI->AddRect(255+4, 261+45, 276+4, 274+45);

		pMI->AddRect(232+4, 276+45, 253+4, 289+45);
		pMI->AddRect(255+4, 276+45, 276+4, 289+45);

		pMI->AddRect(232+4, 291+45, 253+4, 304+45);
		pMI->AddRect(255+4, 291+45, 276+4, 304+45);

		pMI->AddRect(232+4, 306+45, 253+4, 319+45);
		pMI->AddRect(255+4, 306+45, 276+4, 319+45);

		pMI->AddRect(384, 445, 384+72, 445+15);
		pMI->AddRect(500, 445, 500+72, 445+15);

		pMI->AddRect(60, 445, 60+72, 445+15);
		pMI->AddRect(145, 445, 145+72, 445+15);
		pMI->AddRect(230, 445, 230+72, 445+15);

		iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
		iPoint  = 70 - iPoint;
		cPrevFocus  = 1;
		m_cCurFocus = 1;
		m_cMaxFocus = 6;
		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;
		dwMTime = timeGetTime();
		StartInputString(193+4, 65+45, 11, cName);
		ClearInputString();
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_cArrowPressed != 0)
	{	switch (m_cArrowPressed) {
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

	if (cPrevFocus != m_cCurFocus) {
		EndInputString();
		switch (m_cCurFocus) {
		case 1:
			StartInputString(193+4, 65+45, 11, cName);
			break;
		}
		cPrevFocus = m_cCurFocus;
	}

	if (m_bEscPressed == TRUE) {
		ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	bFlag = _bDraw_OnCreateNewCharacter(cName, msX, msY, iPoint);

	if ((dwTime - dwMTime) > 100)
	{	m_cMenuFrame++;
		dwMTime = dwTime;
	}
	if (m_cMenuFrame >= 8)
	{	m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8)
		{	m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;

	DrawVersion();
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK)
	{	PlaySound('E', 14, 5);
		switch (iMIbuttonNum) {
		case 1:
			m_cCurFocus = 1;
			break;
		case 2:
			m_cGender--;
			if (m_cGender < 1) m_cGender = 2;
			break;
		case 3:
			m_cGender++;
			if (m_cGender > 2) m_cGender = 1;
			break;
		case 4:
			m_cSkinCol--;
			if (m_cSkinCol < 1) m_cSkinCol = 3;
			break;
		case 5:
			m_cSkinCol++;
			if (m_cSkinCol > 3) m_cSkinCol = 1;
			break;
		case 6:
			m_cHairStyle--;
			if (m_cHairStyle < 0) m_cHairStyle = 7;
			break;
		case 7:
			m_cHairStyle++;
			if (m_cHairStyle > 7) m_cHairStyle = 0;
			break;
		case 8:
			m_cHairCol--;
			if (m_cHairCol < 0) m_cHairCol = 15;
			break;
		case 9:
			m_cHairCol++;
			if (m_cHairCol > 15) m_cHairCol = 0;
			break;
		case 10:
			m_cUnderCol--;
			if (m_cUnderCol < 0) m_cUnderCol = 7;
			break;
		case 11:
			m_cUnderCol++;
			if (m_cUnderCol > 7) m_cUnderCol = 0;
			break;
		case 12:
			if (iPoint > 0) {
				if (m_ccStr < 14) {
					m_ccStr++;
					iPoint--;
				}
			}
			break;
		case 13:
			if (m_ccStr > 10) {
				m_ccStr--;
				iPoint++;
			}
			break;
		case 14:
			if (iPoint > 0) {
				if (m_ccVit < 14) {
					m_ccVit++;
					iPoint--;
				}
			}
			break;
		case 15:
			if (m_ccVit > 10) {
				m_ccVit--;
				iPoint++;
			}
			break;
		case 16:
			if (iPoint > 0) {
				if (m_ccDex < 14) {
					m_ccDex++;
					iPoint--;
				}
			}
			break;
		case 17:
			if (m_ccDex > 10) {
				m_ccDex--;
				iPoint++;
			}
			break;
		case 18:
			if (iPoint > 0) {
				if (m_ccInt < 14) {
					m_ccInt++;
					iPoint--;
				}
			}
			break;
		case 19:
			if (m_ccInt > 10) {
				m_ccInt--;
				iPoint++;
			}
			break;
		case 20:
			if (iPoint > 0) {
				if (m_ccMag < 14) {
					m_ccMag++;
					iPoint--;
				}
			}
			break;
		case 21:
			if (m_ccMag > 10) {
				m_ccMag--;
				iPoint++;
			}
			break;
		case 22:
			if (iPoint > 0) {
				if (m_ccChr < 14) {
					m_ccChr++;
					iPoint--;
				}
			}
			break;
		case 23:
			if (m_ccChr > 10)
			{	m_ccChr--;
				iPoint++;
			}
			break;

		case 24:
			if (m_cCurFocus != 2)
			{	m_cCurFocus = 2;
				return;
			}
			if (bFlag == FALSE) return;
			//if (m_Misc.bCheckValidName(m_cPlayerName) == FALSE) break;
			if (m_Misc.bCheckValidName(cName) == FALSE) break;
			ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
			strcpy(m_cPlayerName, cName);
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_CREATENEWCHARACTER;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg,"22");
			delete pMI;
			return;


		case 25:
			if (m_cCurFocus != 3)
			{	m_cCurFocus = 3;
				return;
			}
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			delete pMI;
			return;


		case 26: // WARRIOR
			if (m_cCurFocus != 4)
			{	m_cCurFocus = 4;
				return;
			}

			m_ccMag = 10 ;
			m_ccInt = 10 ;
			m_ccChr = 10 ;
			m_ccStr = 14 ;
			m_ccVit = 12 ;
			m_ccDex = 14 ;
			iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
			iPoint  = 70 - iPoint;
			break;

		case 27: // MAGE
			if (m_cCurFocus != 5) {
				m_cCurFocus = 5;
				return;
			}

			m_ccMag = 14 ;
			m_ccInt = 14 ;
			m_ccChr = 10 ;
			m_ccStr = 10 ;
			m_ccVit = 12 ;
			m_ccDex = 10 ;
			iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
			iPoint  = 70 - iPoint;
			break;

		case 28: // PRIEST
			if (m_cCurFocus != 6) {
				m_cCurFocus = 6;
				return;
			}

			m_ccMag = 12 ;
			m_ccInt = 10 ;
			m_ccChr = 14 ;
			m_ccStr = 14 ;
			m_ccVit = 10 ;
			m_ccDex = 10 ;
			iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
			iPoint  = 70 - iPoint;
			break;
		}


	}

	if ((msX >= 65+4-127) && (msX <= 275+4) && (msY >= 65+45) && (msY <= 82+45)) {
		PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER1);
	}
	else
	if ((msX >= 261+4-212) && (msX <= 289+4) && (msY >= 111+45) && (msY <= 124+45)) {
		PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER2);
	}
	else
	if ((msX >= 261+4-212) && (msX <= 289+4) && (msY >= 126+45) && (msY <= 139+45)) {
		PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER3);
	}
	else
	if ((msX >= 261+4-212) && (msX <= 289+4) && (msY >= 141+45) && (msY <= 154+45)) {
		PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER4);
	}
	else
	if ((msX >= 261+4-212) && (msX <= 289+4) && (msY >= 156+45) && (msY <= 169+45)) {
		PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER5);
	}
	else
	if ((msX >= 261+4-212) && (msX <= 289+4) && (msY >= 171+45) && (msY <= 184+45)) {
		PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER6);
	}
	else
	if ((msX >= 240+4-175) && (msX <= 268+4) && (msY >= 231+45) && (msY <= 244+45)) {
		// Str
		i= 0 ;
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER7);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER8);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER9);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER10);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER11);
	}
	else if ((msX >= 240+4-175) && (msX <= 268+4) && (msY >= 246+45) && (msY <= 259+45)) {
			// Vit
		i= 0 ;
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER12);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER13);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER14);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER15);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER16);//"
	}
	else if ((msX >= 240+4-175) && (msX <= 268+4) && (msY >= 261+45) && (msY <= 274+45)) {
		// Dex
		i= 0 ;
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER17);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER18);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER19);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER20);//"
	}
	else if ((msX >= 240+4-175) && (msX <= 268+4) && (msY >= 276+45) && (msY <= 289+45)) {
		// Int
		i= 0 ;
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER21);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER22);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER23);//"
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER24);
	}
	else if ((msX >= 240+4-175) && (msX <= 268+4) && (msY >= 291+45) && (msY <= 304+45)) {
		// Mag
		i= 0 ;
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER25);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER26);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER27);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER28);
	}
	else if ((msX >= 240+4-175) && (msX <= 268+4) && (msY >= 306+45) && (msY <= 319+45)) {
		// Charisma
		i= 0 ;
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER29);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER30);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER31);
		PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER32);
	}
	else if ((msX >= 384) && (msX <= 384+72) && (msY >= 445) && (msY <= 445+15))  {
		m_cCurFocus = 2;
		if (strlen(cName) <= 0)
		{	i= 0 ;
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER35);//"Please enter a character name."
		}
		else if (iPoint > 0)
		{	i= 0 ;
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER36);//"You need to select your character class."
		}else if (m_Misc.bCheckValidName(cName) == FALSE)
		{	i= 0 ;
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER39);//"Cannot use special characters "
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER40);//"in your character's name. Please"
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER41);//"type another name."
		}else if (_bCheckBadWords(cName) == TRUE)
		{	i= 0 ;
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER42);//"The character's name is not appropriate."
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER43);//"Please retry with another name."
		}else
		{	i= 0 ;
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER44);//"
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER45);//"
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER46);//"
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER47);//"
			PutAlignedString(370, 580, 345 + 16*i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER48);//"
		}
	}else if ((msX >= 500) && (msX <= 500+72) && (msY >= 445) && (msY <= 445+15))
	{	m_cCurFocus = 3;
		PutAlignedString(370, 580, 345 , UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER49);
	}

	if ((msX >= 60) && (msX <= 60+72) && (msY >= 445) && (msY <= 445+15)) {
		m_cCurFocus = 4;
		PutAlignedString(370, 580, 345 , UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER50);
	}

	if ((msX >= 145) && (msX <= 145+72) && (msY >= 445) && (msY <= 445+15)) {
		m_cCurFocus = 5;
		PutAlignedString(370, 580, 345 , UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER51);
	}

	if ((msX >= 230) && (msX <= 230+72) && (msY >= 445) && (msY <= 445+15)) {
		m_cCurFocus = 6;
		PutAlignedString(370, 580, 345 , UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER52);
	}

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

#ifdef DEF_MAKE_ACCOUNT

void CGame::_LoadAgreementTextContents(char cType)
{
 char * pContents, * token, cTemp[120], cFileName[120];
 char   seps[] = "\n";
 int    iIndex = 0, i;
 class  CStrTok * pStrTok;
 DWORD  dwFileSize;
 HANDLE hFile;
 FILE * pFile;

	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++) {
		if (m_pAgreeMsgTextList[i] != NULL)
			delete m_pAgreeMsgTextList[i];
		m_pAgreeMsgTextList[i] = NULL;
	}

	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFileName, sizeof(cFileName));

	wsprintf(cTemp, "contents%d", cType);

	strcat(cFileName, "contents");
	strcat(cFileName, "\\");
	strcat(cFileName, "\\");
	strcat(cFileName, cTemp);
	strcat(cFileName, ".txt");

	hFile = CreateFile(cFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFileName, "rt");
	if (pFile == NULL) return;
	else {
		pContents = new char[dwFileSize+1];
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, dwFileSize, 1, pFile);
	}

	fclose(pFile);
	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL ) {
		m_pAgreeMsgTextList[iIndex] = new class CMsg(NULL, token, NULL);
		token = pStrTok->pGet();
		iIndex++;
	}
	delete pStrTok;
	delete[] pContents;
}

void CGame::UpdateScreen_OnAgreement()
{
 short sX, sY, msX, msY, msZ;
 char  cLB, cRB;
 char  cMIresult;
 static class CMouseInterface * pMI;
 int i, iTotalLines, iPointerLoc;
 DWORD dwTime = timeGetTime();
 double d1,d2,d3;
 int iMIbuttonNum;

	sX = 121;
	sY = 22;

	if (m_cGameModeCount == 0) {
		m_iAgreeView = 0;
		_LoadAgreementTextContents(0);

		pMI = new class CMouseInterface;
		pMI->AddRect(sX+82 -105, sY+355,sX+131 -105,sY+374);
		pMI->AddRect(sX+235 -105, sY+355,sX+303 -105,sY+375);
	}

	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;
	if (m_bEnterPressed == TRUE) {
		PlaySound('E', 14, 5);
		ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
		ClearContents_OnCreateNewAccount();
		delete pMI;
		return;
	}
	if (m_bEscPressed == TRUE) {
		PlaySound('E', 14, 5);
		ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK) {
		switch (iMIbuttonNum) {
		case 1: // Agree
			PlaySound('E', 14, 5);
			ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
			ClearContents_OnCreateNewAccount();
			delete pMI;
			return;

		case 2:	// Disagree
			PlaySound('E', 14, 5);
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			delete pMI;
			return;
		}
	}

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_AGREEMENT, 0,0,0, TRUE);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, 43, 38,12, FALSE);

	iTotalLines = 0;
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	if (m_pAgreeMsgTextList[i] != NULL) iTotalLines++;

	d1 = (double)m_iAgreeView;
	d2 = (double)(iTotalLines - 20);
	d3 = (double)d1 / d2;
	d1 = 338.0f * d3;
	iPointerLoc = (int)d1;
	m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX +361 -112, sY +37 +13 +iPointerLoc, 7, dwTime);

	for (i = 0; i < 20; i++)
	if (m_pAgreeMsgTextList[i + m_iAgreeView] != NULL) {
		PutAlignedString(60, 360, sY + 65 +i*13, m_pAgreeMsgTextList[i + m_iAgreeView]->m_pMsg, 45,25,25);
	}

	if( msZ != 0 )
	{
		m_iAgreeView = m_iAgreeView - msZ/60;
		m_DInput.m_sZ = 0;
	}
	if (cLB != 0 && iTotalLines > 20)
	{ 	if ((msX >= sX +345 -112) && (msX <= sX +380 -112) && (msY >= sY +50) && (msY <= sY +395))
		{	d1 = (double)(msY - (sY + 37 +13));
			d2 = (double)(iTotalLines - 17);
			d3 = (double)(d1 * d2)/(338.0f);
			m_iAgreeView = (int)d3;
			m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSprite(sX +361 -112, sY +37 +13 +iPointerLoc, 4, dwTime);
	}	}
	if( m_iAgreeView < 0 ) m_iAgreeView = 0;
	if( iTotalLines > 20 && m_iAgreeView > iTotalLines-20 ) m_iAgreeView = iTotalLines-20;

	if ((msX > sX + 82 -105) && (msX < sX + 131 -105) && (msY > sY + 355 -3) && (msY < sY + 374 +3))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 43 + 20 -23 +45 -105,  sY + 265 +90, 13);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 43 + 20 -23 +45 -105,  sY + 265 +90, 12);

	if ((msX > sX + 235 -105) && (msX < sX + 303 -105) && (msY > sY + 355 -3) && (msY < sY + 375 +3))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 158 + 57 -23 +45 -105, sY + 265 +90, 15);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 158 + 57 -23 +45 -105, sY + 265 +90, 14);

	DrawVersion();
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::UpdateScreen_OnCreateNewAccount()
{short msX, msY, msZ;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;
 static class CMouseInterface * pMI;
 static char cName[12], cPassword[12], cConfirm[12], cPrevFocus, cSSN_A[8], cSSN_B[8], cQuiz[44] ,cAnswer[20], cTempQuiz[44] ;
 DWORD dwTime = timeGetTime();
 int iFlag = 0;

	if (m_cGameModeCount == 0)
	{	pMI = new class CMouseInterface;
		pMI->AddRect(310, 80,560,100);
		pMI->AddRect(310,101,558,122);
		pMI->AddRect(310,123,558,145);
		//pMI->AddRect(310,146,558,167); // real name
		//pMI->AddRect(310,168,477,191); // ssn
		//pMI->AddRect(488,168,557,191); // ssn
		pMI->AddRect(300,192,560,231);
		pMI->AddRect(300,232,560,268);   // Quiz 8  // +41
		pMI->AddRect(300,269,560,306);   // Answer 9
		pMI->AddRect(297, 399, 367, 417);  // Create 10
		pMI->AddRect(392, 399, 462, 417);  // Clear  11
		pMI->AddRect(488, 399, 558, 417);  // Cancel  12   Size 73 x 15
		cPrevFocus  = 1;
		m_cCurFocus = 1;
		m_cMaxFocus = 9; //12
		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;
		ZeroMemory(m_cEmailAddr, sizeof(m_cEmailAddr));
		ZeroMemory(cName, sizeof(cName));
		ZeroMemory(cPassword, sizeof(cPassword));
		ZeroMemory(cConfirm, sizeof(cConfirm));
		ZeroMemory(cSSN_A, sizeof(cSSN_A));
		ZeroMemory(cSSN_B, sizeof(cSSN_B));
		ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
		ZeroMemory(cQuiz, sizeof(cQuiz));
		ZeroMemory(cTempQuiz, sizeof(cTempQuiz));
		ZeroMemory(cAnswer, sizeof(cAnswer));
		StartInputString(427, 84, 11, cName);
		ClearInputString();
	}

	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;
	if (m_cArrowPressed != 0)
	{	switch (m_cArrowPressed) {
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

	if (m_bEscPressed == TRUE)
	{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	if (cPrevFocus != m_cCurFocus)
	{	EndInputString();
		switch (m_cCurFocus) {
		case 1:
			StartInputString(427, 84, 11, cName);
			break;
		case 2:
			StartInputString(427, 106, 11, cPassword);
			break;
		case 3:
			StartInputString(427, 129, 11, cConfirm);
			break;
		case 4:
			StartInputString(311, 215, 31, m_cEmailAddr);
			break;
		case 5:
			StartInputString(311, 253, 44, cQuiz);
			break;
		case 6:
			StartInputString(311, 291 , 19, cAnswer);
			break;
		}
		cPrevFocus = m_cCurFocus;
	}

	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWACCOUNT, 0,0,0, TRUE);
	PutString(377, 84,  "Account:", RGB(100,100,200));
	PutString(372, 106, "Password:", RGB(100,100,200));
	PutString(372, 129, "(confirm)", RGB(100,100,200));
	PutString(271, 215, "eMail:", RGB(100,100,200));
	PutString(276, 253, "Quiz:", RGB(100,100,200));
	PutString(266, 291, "Answer:", RGB(100,100,200));

	if ((m_cCurFocus == 2) || (m_cCurFocus == 3))
		 ShowReceivedString(TRUE);
	else if ((m_cCurFocus == 1) || (m_cCurFocus == 4) || (m_cCurFocus == 5) || (m_cCurFocus == 6))
		ShowReceivedString();

	if (m_cCurFocus != 1) {
		if (m_Misc.bCheckValidName(cName) != FALSE)
			 PutString2(427, 84, cName, 100,200,100);
		else PutString2(427, 84, cName, 200,100,100);
	}
	if (m_cCurFocus != 2) {
		if (m_Misc.bCheckValidName(cPassword) != FALSE)
			 PutString(427, 106, cPassword, RGB(100,200,100), TRUE, 1);
		else PutString(427, 106, cPassword, RGB(200,100,100), TRUE, 1);
	}

	if (m_cCurFocus != 3) {
		if (memcmp(cPassword, cConfirm, 10) == 0)
			 PutString(427, 129, cConfirm, RGB(100,200,100), TRUE, 1);
		else PutString(427, 129, cConfirm, RGB(200,100,100), TRUE, 1);
	}
	if (memcmp(cPassword, cConfirm, 10) != 0) iFlag = 9;

	if (m_cCurFocus != 4) {
		if( m_Misc.bIsValidEmail(m_cEmailAddr) )
			PutString2(311, 48 + 190 -25 +2, m_cEmailAddr, 100,200,100);
		else PutString2(311, 48 + 190 -25 +2, m_cEmailAddr, 200,100,100);
	}

	wsprintf(cTempQuiz,"%s",cQuiz) ;
	m_Misc.ReplaceString(cTempQuiz, ' ', '_');

	if (m_cCurFocus != 5) {
		//if(m_Misc.bCheckValidName(cTempQuiz) != FALSE)
			PutString2(311, 48 + 226 -25 +4, cQuiz, 100,200,100);
		//else PutString2(311, 48 + 226 -25 +4, cQuiz, 200,100,100);
	}

	if (m_cCurFocus != 6) {
		//if (m_Misc.bCheckValidName(cAnswer) != FALSE)
			 PutString2(311, 291, cAnswer, 100,200,100);
		//else PutString2(311, 291, cAnswer, 200,100,100);
	}

	//if (m_Misc.bCheckValidName(cAnswer) == FALSE)		iFlag = 13;
	//if (m_Misc.bCheckValidName(cTempQuiz) == FALSE)		iFlag = 12;
	if (strlen(cAnswer) == 0)							iFlag = 11;
	if (strlen(cTempQuiz) == 0)							iFlag = 10;
	if (m_Misc.bCheckValidName(cPassword) == FALSE)		iFlag = 7;
	if (m_Misc.bCheckValidName(cName) == FALSE)			iFlag = 6;
	if (m_Misc.bIsValidEmail(m_cEmailAddr) == FALSE)	iFlag = 5;
	if (strlen(cConfirm) == 0)							iFlag = 3;
	if (strlen(cPassword) == 0)							iFlag = 2;
	if ((strlen(cName) == 0 ))							iFlag = 1;


	switch (m_cCurFocus) {
	case 1:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT1);
		PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT2);
		break;

	case 2:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT4);
		break;

	case 3:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT8);
		break;

	case 4:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT21);
		PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT22);
		PutAlignedString(290, 575, 360, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT23);
		break;

	case 5:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT25);
		PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT26);
		break;

	case 6:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT29);
		break;

	case 7:
		switch (iFlag) {
		case 0:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT33);
			break;

		case 1:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT35);
			break;

		case 2:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT38);
			break;

		case 3:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT42);
			break;

		case 5:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT50);
			break;

		case 6:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT52);
			PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT53);
			break;

		case 7:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT56);
			PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT57);
			break;

		case 9:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT63);
			PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT64);
			PutAlignedString(290, 575, 360, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT65);
			break;
		case 10:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT67);
			break;
		case 11:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT69);
			break;
		case 12:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT73);
			PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT74);
			break;

		case 13:
			PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT77);
			PutAlignedString(290, 575, 345, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT78);
			break;

		}
		break;

	case 8:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT80);
		break;

	case 9:
		PutAlignedString(290, 575, 330, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT81);
		break;
	}


	if ( (iFlag == 0) && (m_cCurFocus == 7) )
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(199+98, 398, 25, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(199+98, 398, 24, dwTime);

	if (m_cCurFocus == 8)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(294+98, 398, 27, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(294+98, 398, 26, dwTime);

	if (m_cCurFocus == 9)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(390+98, 398, 17, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(390+98, 398, 16, dwTime);

	DrawVersion(TRUE);
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	if (m_bEnterPressed == TRUE)
	{	PlaySound('E', 14, 5);
		switch (m_cCurFocus) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			m_cCurFocus++;
			if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;

		case 7:
			if (iFlag != 0) return;
			ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
			ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

			ZeroMemory(m_cAccountQuiz, sizeof(m_cAccountQuiz));
			ZeroMemory(m_cAccountAnswer, sizeof(m_cAccountAnswer));

			strcpy(m_cAccountName, cName);
			strcpy(m_cAccountPassword, cPassword);

			strcpy(m_cAccountQuiz, cTempQuiz);
			strcpy(m_cAccountAnswer, cAnswer);
			m_cAccountQuiz[45] = ' ' ;
			m_cAccountAnswer[20] = ' ' ;

			ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
			wsprintf(m_cAccountSSN, "%s-%s", cSSN_A, cSSN_B);

			if (memcmp(cPassword, cConfirm, 10) != 0)
			{	ChangeGameMode(DEF_GAMEMODE_ONMSG);
				ZeroMemory(m_cMsg, sizeof(m_cMsg));
				strcpy(m_cMsg, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT82);
				               //"Cannot create account! - password not match!"
				delete pMI;
				return;
			}
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);

			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_CREATENEWACCOUNT;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg, "00");
			delete pMI;
			return;

		case 8:
			ZeroMemory(cName, sizeof(cName));
			ZeroMemory(cPassword, sizeof(cPassword));
			ZeroMemory(cConfirm, sizeof(cConfirm));
			ZeroMemory(m_cAccountAge, sizeof(m_cAccountAge));
			ZeroMemory(m_cAccountCountry, sizeof(m_cAccountCountry));
			ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
			ZeroMemory(m_cEmailAddr, sizeof(m_cEmailAddr));
			ZeroMemory(cSSN_A, sizeof(cSSN_A));
			ZeroMemory(cSSN_B, sizeof(cSSN_B));
			ZeroMemory(cQuiz, sizeof(cQuiz));
			ZeroMemory(cTempQuiz, sizeof(cTempQuiz));
			ZeroMemory(cAnswer, sizeof(cAnswer));

			break;

		case 9:
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			delete pMI;
			return;
		}
		m_bEnterPressed = FALSE;
	}

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK) {
		PlaySound('E', 14, 5);

		switch (iMIbuttonNum) {
		default:
			m_cCurFocus = iMIbuttonNum;
			break;

		case 7:
			if (iFlag != 0) return;
			ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
			ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

			ZeroMemory(m_cAccountQuiz, sizeof(m_cAccountQuiz));
			ZeroMemory(m_cAccountAnswer, sizeof(m_cAccountAnswer));


			strcpy(m_cAccountName, cName);
			strcpy(m_cAccountPassword, cPassword);
			strcpy(m_cAccountQuiz, cTempQuiz);
			strcpy(m_cAccountAnswer, cAnswer);

			ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
			wsprintf(m_cAccountSSN, "%s-%s", cSSN_A, cSSN_B);

			if (memcmp(cPassword, cConfirm, 10) != 0)
			{	ChangeGameMode(DEF_GAMEMODE_ONMSG);
				ZeroMemory(m_cMsg, sizeof(m_cMsg));
				strcpy(m_cMsg, UPDATE_SCREEN_ON_CREATE_NEW_ACCOUNT82);
				               //"Cannot create account! - password not match!"
				delete pMI;
				return;
			}

			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_CREATENEWACCOUNT;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg, "00");
			delete pMI;
			return;

		case 8:
			ZeroMemory(cName, sizeof(cName));
			ZeroMemory(cPassword, sizeof(cPassword));
			ZeroMemory(cConfirm, sizeof(cConfirm));
			ZeroMemory(m_cAccountAge, sizeof(m_cAccountAge));
			ZeroMemory(m_cAccountCountry, sizeof(m_cAccountCountry));
			ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
			ZeroMemory(m_cEmailAddr, sizeof(m_cEmailAddr));
			ZeroMemory(cSSN_A, sizeof(cSSN_A));
			ZeroMemory(cSSN_B, sizeof(cSSN_B));
			ZeroMemory(cQuiz, sizeof(cQuiz));
			ZeroMemory(cTempQuiz, sizeof(cTempQuiz));
			ZeroMemory(cAnswer, sizeof(cAnswer));
			break;

		case 9:
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			delete pMI;
			return;
		}
	}

	if ((msX >= 297) && (msX <= 370) && (msY >= 396) && (msY <= 417))  m_cCurFocus = 7;  //12
	if ((msX >= 392) && (msX <= 465) && (msY >= 396) && (msY <= 417)) m_cCurFocus = 8;  //13
	if ((msX >= 488) && (msX <= 561) && (msY >= 396) && (msY <= 417)) m_cCurFocus = 9; //14

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}
#endif //endif from #ifdef DEF_MAKE_ACCOUNT

void CGame::UpdateScreen_OnLogin()
{
 short msX, msY, msZ, sX, sY;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;
 static class CMouseInterface * pMI;
 static char  cPassword[12], cPrevFocus;
 static char cName[12];
	sX = 146;
	sY = 114;
	if (m_cGameModeCount == 0)
	{	EndInputString();
		pMI = new class CMouseInterface;
		pMI->AddRect(80, 151, 337, 179);
		pMI->AddRect(80, 180, 337, 205);
		pMI->AddRect(80, 280, 163, 302);
		pMI->AddRect(258, 280, 327, 302);
		cPrevFocus  = 1;
		m_cCurFocus = 1;
		m_cMaxFocus = 4;
		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;
		ZeroMemory(cName, sizeof(cName));
		ZeroMemory(cPassword, sizeof(cPassword));
		StartInputString(180, 162, 11, cName);
		ClearInputString();
	}

	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_cArrowPressed != 0)
	{	switch (m_cArrowPressed) {
		case 1:
			m_cCurFocus--;
			if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
			break;

		case 2:
			if (m_cCurFocus == 3) m_cCurFocus = 4;
			else if (m_cCurFocus == 4) m_cCurFocus = 3;
			break;

		case 3:
			m_cCurFocus++;
			if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;

		case 4:
			if (m_cCurFocus == 3) m_cCurFocus = 4;
			else if (m_cCurFocus == 4) m_cCurFocus = 3;
			break;
		}
		m_cArrowPressed = 0;
	}

	if (m_bEnterPressed == TRUE)
	{	m_bEnterPressed = FALSE;
		PlaySound('E', 14, 5);

		switch (m_cCurFocus) {
		case 1:
			m_cCurFocus++;
			if( m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;
		case 2:
		case 3:
			if ((strlen(cName) == 0) || (strlen(cPassword) == 0)) break;
			ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
			ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
			strcpy(m_cAccountName, cName);
			strcpy(m_cAccountPassword, cPassword);
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort +(rand()%1), WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_LOGIN;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg, "11");
			delete pMI;
			return;
		case 4:	// Cancel
#ifdef DEF_SELECTSERVER
			ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER);
#else
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
#endif
			delete pMI;
			return;
	}	}

	if (m_bEscPressed == TRUE)
	{	EndInputString();
		ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	if (cPrevFocus != m_cCurFocus)
	{	EndInputString();
		switch (m_cCurFocus) {
		case 1:
			StartInputString(180, 162, 11, cName);
			break;
		case 2:
			StartInputString(180, 185, 11, cPassword, TRUE);
			break;
		case 3:
		case 4:
			break;
		}
		cPrevFocus = m_cCurFocus;
	}


	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK)
	{	PlaySound('E', 14, 5);
		switch (iMIbuttonNum) {
		case 1:
			m_cCurFocus = 1;
			break;

		case 2:
			m_cCurFocus = 2;
			break;

		case 3:
			if ((strlen(cName) == 0) || (strlen(cPassword) == 0)) break;
			EndInputString();
			ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
			ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
			strcpy(m_cAccountName, cName);
			strcpy(m_cAccountPassword, cPassword);
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort +(rand()%1), WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_LOGIN;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg, "11");
			delete pMI;
			return;

		case 4:
#ifdef DEF_SELECTSERVER
			ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER); // ONMAINMENU
#else
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
#endif
			delete pMI;
			return;
	}	}

	if ((msX >= 80) && (msX <= 163) && (msY >= 280) && (msY <= 302)) m_cCurFocus = 3;
	if ((msX >= 258) && (msX <= 327) && (msY >= 280) && (msY <= 302)) m_cCurFocus = 4;

	_Draw_OnLogin(cName, cPassword, msX, msY, m_cGameModeCount);
	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();

}

void CGame::UpdateScreen_OnSelectServer()
{
 short msX, msY, msZ, sX, sY;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;
 static class CMouseInterface * pMI;
 static char  cPrevFocus;
 DWORD dwTime = timeGetTime();
 BOOL bFlag = TRUE;

	sX = 146;
	sY = 114;
	if (m_cGameModeCount == 0) {
		EndInputString();

		pMI = new class CMouseInterface;
		pMI->AddRect(130,177,270,198);
		pMI->AddRect(130,199,270,225);
		pMI->AddRect(256,279,331,308);

		cPrevFocus  = 1;
		m_cCurFocus = 1;
		m_cMaxFocus = 3;

		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_cArrowPressed != 0)
	{	switch (m_cArrowPressed) {
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

	if (m_bEnterPressed == TRUE)
	{	m_bEnterPressed = FALSE;
		PlaySound('E', 14, 5);
		switch (m_cCurFocus) {
		case 1:
			if (strlen(m_cWorldServerName) ==0)
			ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
			strcpy(m_cWorldServerName, NAME_WORLDNAME1);
			ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
			delete pMI;
			return;

		case 2:
			ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
			strcpy(m_cWorldServerName, "WS2");
			ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
			delete pMI;
			return;

		case 3:	// Cancel
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			delete pMI;
			return;
	}	}

	if (m_bEscPressed == TRUE)
	{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}
	if (cPrevFocus != m_cCurFocus)
	{	cPrevFocus = m_cCurFocus;
	}
	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 0,0,0, TRUE);
	if (m_cGameModeCount > 20) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 40,121,1, TRUE);
	else if ((m_cGameModeCount >= 15) && (m_cGameModeCount <= 20)) m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->PutTransSprite25(40,121,1, TRUE);

	if (m_cGameModeCount > 20)
	{	if (m_cCurFocus == 1) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 138, 177, 5, TRUE);
		if (m_cCurFocus == 2) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 130, 205, 6, TRUE);
		if (m_cCurFocus == 3) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 256, 282, 4, TRUE);
	}
	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK) {
		PlaySound('E', 14, 5);

		switch (iMIbuttonNum) {
		case 1:
			if (m_cCurFocus == 1) {
				ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
				strcpy(m_cWorldServerName, NAME_WORLDNAME1);
				ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
				delete pMI;
				return;
			}
			else m_cCurFocus = 1;
			break;

		case 2:
			if (m_cCurFocus == 2) {
				ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
				strcpy(m_cWorldServerName, "WS2");
				ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
				delete pMI;
				return;
			}
			else m_cCurFocus = 2;
			break;

		case 3:
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			delete pMI;
			return;
		}
	}

	if ((msX >= 130) && (msX <= 295) && (msY >= 175) && (msY <= 198)) m_cCurFocus = 1;
	if ((msX >= 130) && (msX <= 295) && (msY >= 199) && (msY <= 225)) m_cCurFocus = 2;
	if ((msX >= 256) && (msX <= 331) && (msY >= 279) && (msY <= 308)) m_cCurFocus = 3;

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::OnSysKeyDown(WPARAM wParam)
{
	switch( wParam )
	{
	case VK_SHIFT:
		m_bShiftPressed = TRUE;
		break;
	case VK_CONTROL:
		m_bCtrlPressed = TRUE;
		break;
	case VK_RETURN:
		m_bEnterPressed = TRUE;
		break;
	}
}

void CGame::OnSysKeyUp(WPARAM wParam)
{
	switch( wParam )
	{
	case VK_SHIFT:
		m_bShiftPressed = FALSE;
		break;
	case VK_CONTROL:
		m_bCtrlPressed = FALSE;
		break;
	case VK_RETURN:
		m_bEnterPressed = FALSE;
		if( m_bToggleScreen == TRUE )
		{	m_bIsRedrawPDBGS = TRUE;
			m_DDraw.ChangeDisplayMode(G_hWnd);
		}
		break;
	case VK_ESCAPE:
		m_bEscPressed = FALSE;

	}
}

void CGame::OnKeyUp(WPARAM wParam)
{
 int i=0;
 DWORD dwTime = timeGetTime();

	switch (wParam) {
	case VK_SHIFT:
		m_bShiftPressed = FALSE;
		break;
	case VK_CONTROL:
		m_bCtrlPressed = FALSE;
		break;
	case 65://'A'
		if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	if( m_bForceAttack )
			{	m_bForceAttack = FALSE;
				AddEventList( DEF_MSG_FORCEATTACK_OFF, 10 );
			}else
			{	m_bForceAttack = TRUE;
				AddEventList( DEF_MSG_FORCEATTACK_ON, 10 );
		}	}
		break;

	case 68://'D'
		if (m_bCtrlPressed == TRUE && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	m_cDetailLevel++;
			if( m_cDetailLevel > 2 ) m_cDetailLevel = 0;
			switch( m_cDetailLevel ) {
			case 0:
				AddEventList( NOTIFY_MSG_DETAIL_LEVEL_LOW, 10 );
				break;
			case 1:
				AddEventList( NOTIFY_MSG_DETAIL_LEVEL_MEDIUM, 10 );
				break;
			case 2:
				AddEventList( NOTIFY_MSG_DETAIL_LEVEL_HIGH, 10 );
				break;
		}	}
		break;

	case 72: // 'H' // Snoopy: Mimics VK_F1
		if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	if (m_bIsDialogEnabled[35] == FALSE)
				EnableDialogBox(35, NULL, NULL, NULL);
			else
			{	DisableDialogBox(35);
				DisableDialogBox(18);
		}	}
		break;

	case 87: // 'W' // Snoopy: mimics VK_F11 Togles transparency
		if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	m_bDialogTrans = !m_bDialogTrans;
		}
		break;

	case 88: // 'X' // Snoopy: mimics VK_F12 Logout Window
		if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	if (m_bIsDialogEnabled[19] == FALSE)
				EnableDialogBox(19, NULL, NULL, NULL);
			else DisableDialogBox(19);
		}
		break;

	case 77://'M'
		if( m_cGameMode == DEF_GAMEMODE_ONMAINGAME )
		{	if( m_bCtrlPressed )
			{	if( m_bIsDialogEnabled[9] == TRUE ) DisableDialogBox(9);
				else EnableDialogBox(9, 0, 0, 0, NULL);
		}	}
		break;

#ifdef _DEBUG
	case 81://'Q'
		if( ( m_bCtrlPressed == TRUE ) && ( m_cGameMode == DEF_GAMEMODE_ONMAINGAME ) )
		{	ZeroMemory(m_cChatMsg, sizeof(m_cChatMsg) );
			strcpy(m_cChatMsg, "/enableadmincommand 147258 ");
			StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
			//ClearInputString();
		}
		break;
#endif

	case 82://'R'
		if (m_bCtrlPressed == TRUE && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	if( m_bRunningMode )
			{	m_bRunningMode = FALSE;
				AddEventList( NOTIFY_MSG_CONVERT_WALKING_MODE, 10 );
			}else
			{	m_bRunningMode = TRUE;
				AddEventList( NOTIFY_MSG_CONVERT_RUNNING_MODE, 10 );
		}	}
		break;

	case 83://'S'
		if (m_bCtrlPressed == TRUE && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	if (m_bMusicStat == TRUE) // Music Off
			{	m_bMusicStat = FALSE;
				if (m_bSoundFlag)
				{
					if (m_pBGM != NULL)
					{	m_pBGM->bStop();
						delete m_pBGM;
						m_pBGM = NULL;
				}	}
				AddEventList( NOTIFY_MSG_MUSIC_OFF, 10 );
				break;
			}else if( m_bSoundStat == TRUE )
			{	m_pESound[38]->bStop();
				m_bSoundStat = FALSE;
				AddEventList( NOTIFY_MSG_SOUND_OFF, 10 );
				break;
			}else 	// Music On
			{	if( m_bSoundFlag )
				{	m_bMusicStat = TRUE;
					AddEventList( NOTIFY_MSG_MUSIC_ON, 10 );
				}
				if( m_bSoundFlag )
				{	m_bSoundStat = TRUE;
					AddEventList( NOTIFY_MSG_SOUND_ON, 10 );
				}
				StartBGM();
		}	}
		break;

	case 84: //'T'
		if (m_bCtrlPressed == TRUE && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus) )
		{	char tempid[100], cLB, cRB;
			short sX, sY, msX, msY, msZ;
			sX = m_stDialogBoxInfo[10].sX;
			sY = m_stDialogBoxInfo[10].sY;
			ZeroMemory( tempid, sizeof( tempid ) );
			m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
			if( m_bIsDialogEnabled[10] == TRUE && (msX >= sX + 20) && (msX <= sX + 360) && (msY >= sY + 35) && (msY <= sY + 139) )
			{	CStrTok *pStrTok;
				char   * token, cBuff[64];
				char   seps[] = ":";
				int i = (139-msY+sY)/13;
				if( m_pChatScrollList[i + m_stDialogBoxInfo[10].sView] == NULL ) return;
				if( m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg[0] == ' ' ) i++;
				strcpy(cBuff, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg);
				pStrTok = new class CStrTok(cBuff, seps);
				token = pStrTok->pGet();
				wsprintf( tempid, "/to %s", token );
				bSendCommand(MSGID_COMMAND_CHATMSG, NULL, NULL, NULL, NULL, NULL, tempid);
				delete pStrTok;
			}else if( _tmp_sOwnerType < 7 && (strlen(_tmp_cName)>0) && (m_iIlusionOwnerH==NULL)
						&& ((m_bIsCrusadeMode == FALSE) || _iGetFOE(_tmp_iStatus) >= 0))
			{	wsprintf( tempid, "/to %s", _tmp_cName );
				bSendCommand(MSGID_COMMAND_CHATMSG, NULL, NULL, NULL, NULL, NULL, tempid);
			}else
			{	EndInputString();
				wsprintf( m_cChatMsg, "/to " );
				StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
		}	}
		break;
	case 107: //'+'
		if(m_bInputStatus == FALSE) m_bZoomMap = TRUE;
		break;
	case 109: //'-'
		if(m_bInputStatus == FALSE) m_bZoomMap = FALSE;
		break;

	case VK_F2:
		UseShortCut( 1 );
		break;

	case VK_F3:
		UseShortCut( 2 );
		break;

	case VK_INSERT:
		if (m_iHP <= 0) return;
		if (m_bItemUsingStatus == TRUE)
		{	AddEventList(USE_RED_POTION1, 10);
			return;
		}
		if (m_bIsDialogEnabled[27] == TRUE)
		{	AddEventList(USE_RED_POTION2, 10);
			return;
		}
		for (i = 0; i < DEF_MAXITEMS; i++)
		if ( (m_pItemList[i] != NULL) && (m_bIsItemDisabled[i] != TRUE) &&
			 (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 1))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, NULL, i, NULL, NULL, NULL);
			m_bIsItemDisabled[i] = TRUE;
			m_bItemUsingStatus = TRUE;
			return;
		}

		for (i = 0; i < DEF_MAXITEMS; i++)
		if ( (m_pItemList[i] != NULL) && (m_bIsItemDisabled[i] != TRUE) &&
			 (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 2))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, NULL, i, NULL, NULL, NULL);
			m_bIsItemDisabled[i] = TRUE;
			m_bItemUsingStatus = TRUE;
			return;
		}
		break;

	case VK_DELETE:
		if (m_iHP <= 0) return;
		if (m_bItemUsingStatus == TRUE)
		{	AddEventList(USE_BLUE_POTION1, 10);
			return;
		}
		if (m_bIsDialogEnabled[27] == TRUE)
		{	AddEventList(USE_BLUE_POTION2, 10);
			return;
		}

		for (i = 0; i < DEF_MAXITEMS; i++)
		if ( (m_pItemList[i] != NULL) && (m_bIsItemDisabled[i] != TRUE) &&
			 (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 3))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, NULL, i, NULL, NULL, NULL);
			m_bIsItemDisabled[i] = TRUE;
			m_bItemUsingStatus = TRUE;
			return;
		}

		for (i = 0; i < DEF_MAXITEMS; i++)
		if ( (m_pItemList[i] != NULL) && (m_bIsItemDisabled[i] != TRUE) &&
			 (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 4))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, NULL, i, NULL, NULL, NULL);
			m_bIsItemDisabled[i] = TRUE;
			m_bItemUsingStatus = TRUE;
			return;
		}
		break;

	case VK_END:
		if ( ((m_bIsDialogEnabled[7] == TRUE) && (m_stDialogBoxInfo[7].cMode == 1) && (iGetTopDialogBoxIndex() == 7)) ||
			((m_bIsDialogEnabled[17] == TRUE) && (m_stDialogBoxInfo[17].cMode == 1) && (iGetTopDialogBoxIndex() == 17)) )
		{}else if ((!m_bInputStatus) && (m_cBackupChatMsg[0] != '!') && (m_cBackupChatMsg[0] != '~') && (m_cBackupChatMsg[0] != '^') &&
				 (m_cBackupChatMsg[0] != '@'))
		{	ZeroMemory(m_cChatMsg, sizeof(m_cChatMsg));
			strcpy(m_cChatMsg, m_cBackupChatMsg);
			StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
		}
		break;

	case VK_F4:
		if(m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
		UseMagic(m_sMagicShortCut);
		break;

	case VK_F5:
		if (m_bIsDialogEnabled[1] == FALSE)
			EnableDialogBox(1, NULL, NULL, NULL);
		else DisableDialogBox(1);
		break;

	case VK_F6:
		if (m_bIsDialogEnabled[2] == FALSE)
			EnableDialogBox(2, NULL, NULL, NULL);
		else DisableDialogBox(2);
		break;

	case VK_F7:
		if (m_bIsDialogEnabled[3] == FALSE)
			EnableDialogBox(3, NULL, NULL, NULL);
		else DisableDialogBox(3);
		break;

	case VK_F8:
		if (m_bIsDialogEnabled[15] == FALSE)
			EnableDialogBox(15, NULL, NULL, NULL);
		else DisableDialogBox(15);
		break;

	case VK_F9:
		if (m_bIsDialogEnabled[10] == FALSE)
			EnableDialogBox(10, NULL, NULL, NULL);
		else DisableDialogBox(10);
		break;

	case VK_F11:
		m_bDialogTrans = !m_bDialogTrans;
		break;

	case VK_F12:
		if(m_bInputStatus) return;
		if (m_bIsDialogEnabled[19] == FALSE)
			EnableDialogBox(19, NULL, NULL, NULL);
		else DisableDialogBox(19);
		break;

	case VK_F1:
		if (m_bInputStatus) return;
		if (m_bIsDialogEnabled[35] == FALSE) // 35 CLEROTH
			EnableDialogBox(35, NULL, NULL, NULL);
		else
		{	DisableDialogBox(35);
			DisableDialogBox(18);
		}
		break;

	case VK_UP:
		m_cArrowPressed	= 1;
		if( m_cGameMode == DEF_GAMEMODE_ONMAINGAME )
		{	int iTotalMsg=0;
			for( int i=DEF_MAXWHISPERMSG-1 ; i>=0 ; i-- )
			{	if( m_pWhisperMsg[i] != NULL )
				{	iTotalMsg = i;
					break;
			}	}
			m_cWhisperIndex ++;
			if( m_cWhisperIndex > iTotalMsg ) m_cWhisperIndex = 0;
			if( m_cWhisperIndex < 0 ) m_cWhisperIndex = iTotalMsg;
			if( m_pWhisperMsg[m_cWhisperIndex] != NULL ) {
			EndInputString();
			wsprintf( m_cChatMsg, "/to %s", m_pWhisperMsg[m_cWhisperIndex]->m_pMsg );
			StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
		}	}
		break;

	case VK_RIGHT:
		m_cArrowPressed	= 2;
		break;

	case VK_DOWN:
		m_cArrowPressed	= 3;
		if( m_cGameMode == DEF_GAMEMODE_ONMAINGAME )
		{	int iTotalMsg=0;
			for( int i=DEF_MAXWHISPERMSG-1 ; i>=0 ; i-- )
			{	if( m_pWhisperMsg[i] != NULL )
				{	iTotalMsg = i;
					break;
			}	}
			m_cWhisperIndex --;
			if( m_cWhisperIndex < 0 ) m_cWhisperIndex = iTotalMsg;
			if( m_cWhisperIndex > iTotalMsg ) m_cWhisperIndex = 0;
			if( m_pWhisperMsg[m_cWhisperIndex] != NULL ) {
			EndInputString();
			wsprintf( m_cChatMsg, "/to %s", m_pWhisperMsg[m_cWhisperIndex]->m_pMsg );
			StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
		}	}
		break;

	case VK_LEFT:
		m_cArrowPressed	= 4;
		break;

	case VK_SNAPSHOT:
		CreateScreenShot();
		break;

#ifndef DEF_USING_WIN_IME
	case VK_TAB:
		if( m_bShiftPressed )
		{	m_cCurFocus--;
			if( m_cCurFocus < 1 ) m_cCurFocus = m_cMaxFocus;
		}else
		{	m_cCurFocus++;
			if( m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
		}
		if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, NULL, NULL, NULL, NULL, NULL);
		}
		break;

	case VK_RETURN:
		m_bEnterPressed = TRUE;
		break;
#endif

	case VK_HOME:
		if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLESAFEATTACKMODE, NULL, NULL, NULL, NULL, NULL);
		}
		break;

	case VK_ESCAPE:
		m_bEscPressed = TRUE;
		if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
		{	if ((m_bIsObserverMode == TRUE) && (m_bShiftPressed)) { //ObserverMode Shift+Esc
				// Log Out
				if (m_cLogOutCount == -1) m_cLogOutCount = 1;
				DisableDialogBox(19);
				PlaySound('E', 14, 5);
			}
			else if(m_cLogOutCount != -1) {
				if (m_bForceDisconn == FALSE) { //Esc
					m_cLogOutCount = -1;
					AddEventList(DLGBOX_CLICK_SYSMENU2, 10);
				}
			}
			if (m_bIsGetPointingMode == TRUE) {
				m_bIsGetPointingMode = FALSE;
				AddEventList(COMMAND_PROCESSOR1, 10);
			}
			m_bIsF1HelpWindowEnabled = FALSE;
		}
		break;

	case 33:
		if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
		if (m_bInputStatus) return;
		if (m_bIsSpecialAbilityEnabled == TRUE)
		{	if (m_iSpecialAbilityType != 0) {
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACTIVATESPECABLTY, NULL, NULL, NULL, NULL, NULL);
				m_bIsSpecialAbilityEnabled = FALSE;
			}
			else AddEventList(ON_KEY_UP26, 10);
		}
		else {
			if (m_iSpecialAbilityType == 0) AddEventList(ON_KEY_UP26, 10);
			else {
				if ((m_sPlayerAppr4 & 0x00F0) != 0) {
					AddEventList(ON_KEY_UP28, 10);
					return;
				}

				i = (dwTime - m_dwSpecialAbilitySettingTime)/1000;
				i = m_iSpecialAbilityTimeLeftSec - i;
				if (i < 0) i = 0;

				ZeroMemory(G_cTxt, sizeof(G_cTxt));
				if (i < 60) {
					switch (m_iSpecialAbilityType) {
					case 1: wsprintf(G_cTxt, ON_KEY_UP29, i); break;//"
					case 2: wsprintf(G_cTxt, ON_KEY_UP30, i); break;//"
					case 3: wsprintf(G_cTxt, ON_KEY_UP31, i); break;//"
					case 4: wsprintf(G_cTxt, ON_KEY_UP32, i); break;//"
					case 5: wsprintf(G_cTxt, ON_KEY_UP33, i); break;//"
					case 50:wsprintf(G_cTxt, ON_KEY_UP34, i); break;//"
					case 51:wsprintf(G_cTxt, ON_KEY_UP35, i); break;//"
					case 52:wsprintf(G_cTxt, ON_KEY_UP36, i); break;//"
					}
				}
				else {
					switch (m_iSpecialAbilityType) {
					case 1: wsprintf(G_cTxt, ON_KEY_UP37, i/60); break;//"
					case 2: wsprintf(G_cTxt, ON_KEY_UP38, i/60); break;//"
					case 3: wsprintf(G_cTxt, ON_KEY_UP39, i/60); break;//"
					case 4: wsprintf(G_cTxt, ON_KEY_UP40, i/60); break;//"
					case 5: wsprintf(G_cTxt, ON_KEY_UP41, i/60); break;//"
					case 50:wsprintf(G_cTxt, ON_KEY_UP42, i/60); break;//"
					case 51:wsprintf(G_cTxt, ON_KEY_UP43, i/60); break;//"
					case 52:wsprintf(G_cTxt, ON_KEY_UP44, i/60); break;//"
					}
				}
				AddEventList(G_cTxt, 10);
			}
		}
		break;
	}
}

void CGame::OnKeyDown(WPARAM wParam)
{
	switch (wParam) {
	case VK_CONTROL:
		m_bCtrlPressed = TRUE;
		break;
	case VK_SHIFT:
		m_bShiftPressed = TRUE;
		break;
	case VK_INSERT:
	case VK_DELETE:
	case VK_TAB:
	case VK_RETURN:
	case VK_ESCAPE:
	case VK_END:
	case VK_HOME:
	case VK_F1:
	case VK_F2:
	case VK_F3:
	case VK_F4:
	case VK_F5:
	case VK_F6:
	case VK_F7:
	case VK_F8:
	case VK_F9:
	case VK_F10:
	case VK_F11:
	case VK_F12:
	case VK_PRIOR: // Page-Up
	case VK_NEXT: // Page-Down
	case VK_LWIN:
	case VK_RWIN:
	case VK_MULTIPLY:
	case VK_ADD: //'+'
	case VK_SEPARATOR:
	case VK_SUBTRACT: //'-'
	case VK_DECIMAL:
	case VK_DIVIDE:
	case VK_NUMLOCK:
	case VK_SCROLL:
		break;

	default:
		if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
		{	if (m_bCtrlPressed)
			{	switch (wParam) {
				case 48: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 9; break; // 0
				case 49: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 0; break; // 1
				case 50: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 1; break; // 2
				case 51: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 2; break; // 3
				case 52: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 3; break; // 4
				case 53: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 4; break; // 5
				case 54: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 5; break; // 6
				case 55: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 6; break; // 7
				case 56: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 7; break; // 8
				case 57: EnableDialogBox(3, NULL, NULL, NULL); m_stDialogBoxInfo[3].sView = 8; break; // 9
				}
			}else if ((m_bInputStatus == FALSE) && (GetAsyncKeyState(VK_MENU)>>15 == FALSE))
			{	StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
				ClearInputString();
		}	}
		break;
	}
}

void CGame::UpdateScreen_OnQuit()
{
 short msX, msY, msZ;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;

 static class CMouseInterface * pMI;

 DWORD dwTime = timeGetTime();

	if (m_cGameModeCount == 0) {
		if (G_pCalcSocket != NULL)
		{	delete G_pCalcSocket;
			G_pCalcSocket = NULL;
		}
		if (m_pGSock != NULL)
		{	delete m_pGSock;
			m_pGSock = NULL;
		}
		m_bEscPressed = FALSE;
		m_bEnterPressed = FALSE;
		pMI = new class CMouseInterface;
		pMI->AddRect(0,0,640,480);
		m_bEnterPressed = FALSE;
	}

    m_cGameModeCount++;
	if (m_cGameModeCount > 120) m_cGameModeCount = 120;

	m_DDraw.ClearBackB4();

	if (m_bEscPressed == TRUE || m_bEnterPressed == TRUE) {
		m_bEscPressed = FALSE;
		m_bEnterPressed = FALSE;
		delete pMI;
		ChangeGameMode(DEF_GAMEMODE_NULL);
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
		return;
	}
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_QUIT, 0,0,0, TRUE);
	if (m_cGameModeCount > 20) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_QUIT, 255,123,1, TRUE);
	else if ((m_cGameModeCount >= 15) && (m_cGameModeCount <= 20)) m_pSprite[DEF_SPRID_INTERFACE_ND_QUIT]->PutTransSprite25(255,123,1, TRUE);
	DrawVersion(TRUE);
	if(m_cGameModeCount == 100)
	{	ChangeGameMode(DEF_GAMEMODE_NULL);
		delete pMI;
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
		return;
	}
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if ((cMIresult == DEF_MIRESULT_CLICK) && (iMIbuttonNum == 1)) {
		ChangeGameMode(DEF_GAMEMODE_NULL);
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
		delete pMI;
		return;
	}

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::UpdateScreen_OnQueryForceLogin()
{
 short msX, msY, msZ;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;

 static class CMouseInterface * pMI;
 static DWORD dwCTime;
 DWORD dwTime = timeGetTime();

	if (m_cGameModeCount == 0) {
		pMI = new class CMouseInterface;
		pMI->AddRect(200,244,200+DEF_BTNSZX,244+DEF_BTNSZY);
		pMI->AddRect(370,244,370+DEF_BTNSZX,244+DEF_BTNSZY);
		m_bEnterPressed = FALSE;
		m_bEscPressed   = FALSE;
		m_cArrowPressed = 0;

		dwCTime = timeGetTime();

		PlaySound('E', 25, 0);
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_bEscPressed == TRUE) {
		ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	UpdateScreen_OnSelectCharacter(0, 0, 0, 0);
	if ((m_cGameModeCount >= 0) && (m_cGameModeCount < 6)) {
		m_DDraw.DrawShadowBox(0,0,639,479);
	}
	else if (m_cGameModeCount >= 6) {
		m_DDraw.DrawShadowBox(0,0,639,479);
		m_DDraw.DrawShadowBox(0,0,639,479);
	}

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 130, 2);

	PutString_SprFont(172 + 86, 160, "Character on Use", 7,0,0);
	PutAlignedString(178, 453, 195, UPDATE_SCREEN_ON_QUERY_FORCE_LOGIN1);
	PutAlignedString(178, 453, 215, UPDATE_SCREEN_ON_QUERY_FORCE_LOGIN2);

	if ((msX >= 200) && (msX <= 200 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 19);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 18);

	if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 3);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 2);

	if ((dwTime - dwCTime) > 100) {
		m_cMenuFrame++;
		dwCTime = dwTime;
	}
	if (m_cMenuFrame >= 8) {
		m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8) {
			m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK)
	{	PlaySound('E', 14, 5);
		switch (iMIbuttonNum) {
		case 1:
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode  = MSGID_REQUEST_ENTERGAME;
			m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NOENTER_FORCEDISCONN;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg,"33");
			delete pMI;
			return;

		case 2:
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			delete pMI;
			break;
	}	}
	DrawVersion();
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::UpdateScreen_OnSelectCharacter(short sX, short sY, short msX, short msY, BOOL bIgnoreFocus)
{int i;
 int iYear, iMonth, iDay, iHour, iMinute;
 __int64 iTemp1, iTemp2;
 char cTotalChar = 0;
 DWORD dwTime = timeGetTime();
	sY = 10;
	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_SELECTCHAR, 0, 0, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 50);

	iTemp1 = 0;
	iTemp2 = 0;
	iYear = iMonth = iDay = iHour = iMinute = 0;
	for (i = 0; i < 4; i++)
	{	if ((m_cCurFocus - 1 == i) && (bIgnoreFocus == FALSE))
			 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(sX + 110 + i*109 -7, 63 -9, 62, dwTime);
		else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(sX + 110 + i*109 -7, 63 -9, 61, dwTime);

		if (m_pCharList[i] != NULL)
		{	cTotalChar++;
			switch (m_pCharList[i]->m_sSex) {
			case 1:	_tmp_sOwnerType = 1; break;
			case 2:	_tmp_sOwnerType = 4; break;
			}
			_tmp_sOwnerType += m_pCharList[i]->m_sSkinCol - 1;
			_tmp_cDir   = m_cMenuDir;
			_tmp_sAppr1 = m_pCharList[i]->m_sAppr1;
			_tmp_sAppr2 = m_pCharList[i]->m_sAppr2;
			_tmp_sAppr3 = m_pCharList[i]->m_sAppr3;
			_tmp_sAppr4 = m_pCharList[i]->m_sAppr4;
			_tmp_iApprColor = m_pCharList[i]->m_iApprColor; // v1.4

			ZeroMemory(_tmp_cName, sizeof(_tmp_cName));
			memcpy(_tmp_cName, m_pCharList[i]->m_cName, 10);
			// CLEROTH - NO USE
			_tmp_cAction = DEF_OBJECTMOVE;
			_tmp_cFrame = m_cMenuFrame;

			if (m_pCharList[i]->m_sSex != NULL)
			{	if (m_Misc.bCheckValidString(m_pCharList[i]->m_cName) == TRUE)
				{	m_pEffectSpr[0]->PutTransSprite(sX +157 +i*109, sY +138, 1, dwTime);
					DrawObject_OnMove_ForMenu(0, 0, sX +157 +i*109, sY +138, FALSE, dwTime, 0, 0);
					PutString(sX +112 +i*109, sY +179 -9, m_pCharList[i]->m_cName, RGB(51,0,51));//25,35,25);
					int	_sLevel = m_pCharList[i]->m_sLevel;
					wsprintf(G_cTxt, "%d", _sLevel);
					PutString(sX + 138 +i*109, sY +196 -10, G_cTxt, RGB(51,0,51)); //25,35,25);

					wsprintf(G_cTxt, "%d", m_pCharList[i]->m_iExp);
					PutString(sX + 138 +i*109, sY +211 -10, G_cTxt, RGB(51,0,51)); //25,35,25);
				}
				iTemp2 = m_pCharList[i]->m_iYear*1000000 + m_pCharList[i]->m_iMonth*60000 + m_pCharList[i]->m_iDay*1700 + m_pCharList[i]->m_iHour*70 + m_pCharList[i]->m_iMinute;
				if (iTemp1 < iTemp2)
				{	iYear   = m_pCharList[i]->m_iYear;
					iMonth  = m_pCharList[i]->m_iMonth;
					iDay    = m_pCharList[i]->m_iDay;
					iHour   = m_pCharList[i]->m_iHour;
					iMinute = m_pCharList[i]->m_iMinute;
					iTemp1 = iTemp2;
	}	}	}	}
    i = 0 ;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,51);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,52);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,53);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,54);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,55);

	if ((msX > 360) && (msY >= 283) && (msX < 545) & (msY <= 315)) {
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,56);
		PutAlignedString(98, 357, 290 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER1);//"
		PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER2);//"
		PutAlignedString(98, 357, 320 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER3);//"
		PutAlignedString(98, 357, 335 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER4);//"
	} else
	if ((msX > 360) && (msY >= 316) && (msX < 545) & (msY <= 345)) {
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,57);
		PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER5);//"

	} else
	if ((msX > 360) && (msY >= 346) && (msX < 545) & (msY <= 375)) {

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,58);
		PutAlignedString(98, 357, 275 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER6);//"
		PutAlignedString(98, 357, 290 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER7);//"
		PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER8);//"
		PutAlignedString(98, 357, 320 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER9);//"
		PutAlignedString(98, 357, 335 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER10);//"
		PutAlignedString(98, 357, 350 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER11);//"

	}else if ((msX > 360) && (msY >= 376) && (msX < 545) & (msY <= 405))
	{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,59);
		PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER12);//"
	}else if ((msX > 360) && (msY >= 406) && (msX < 545) & (msY <= 435)) {
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0,0,60);
		PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER13);//"
	}else
	{	if (cTotalChar == 0)
		{	PutAlignedString(98, 357, 275 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER14);//"
			PutAlignedString(98, 357, 290 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER15);//"
			PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER16);//"
			PutAlignedString(98, 357, 320 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER17);//"New Character
			PutAlignedString(98, 357, 335 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER18);//"
		}else if (cTotalChar < 4)
		{	PutAlignedString(98, 357, 275 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER19);//"
			PutAlignedString(98, 357, 290 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER20);//"Play¹
			PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER21);//"
			PutAlignedString(98, 357, 320 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER22);//"
			PutAlignedString(98, 357, 335 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER23);//"Delete Character
			PutAlignedString(98, 357, 350 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER24);//"
		}
		if (cTotalChar == 4)
		{	PutAlignedString(98, 357, 290 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER25);//"
			PutAlignedString(98, 357, 305 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER26);//"Play
			PutAlignedString(98, 357, 320 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER27);//"Delete Character
			PutAlignedString(98, 357, 335 +15,  UPDATE_SCREEN_ON_SELECT_CHARACTER28);//"
	}	}
	int iTempMon, iTempDay, iTempHour, iTempMin ;
	iTempMon = iTempDay = iTempHour =iTempMin = 0;

	if (m_iAccntYear != 0)
	{	 iTempMin =  (m_iTimeLeftSecAccount / 60 ) ;
		 wsprintf(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER37, m_iAccntYear, m_iAccntMonth, m_iAccntDay, iTempMin);
	}else
	{	if (m_iTimeLeftSecAccount > 0)
		{	iTempDay =   (m_iTimeLeftSecAccount /(60*60*24)) ;
			iTempHour =  (m_iTimeLeftSecAccount /(60*60)) % 24;
			iTempMin =   (m_iTimeLeftSecAccount / 60 ) % 60;
			wsprintf(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER38, iTempDay, iTempHour, iTempMin);
		}else strcpy(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER39);
	}
	PutAlignedString(98, 357, 385 +10, G_cTxt);

	if (m_iIpYear != 0)
	{	iTempHour =  (m_iTimeLeftSecIP / (60*60)) ;
		iTempMin =   (m_iTimeLeftSecIP / 60 ) % 60;
		wsprintf(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER40, m_iIpYear, m_iIpMonth, m_iIpDay, iTempHour, iTempMin) ;
	}else
	{	if (m_iTimeLeftSecIP > 0)
 		{	iTempDay =   (m_iTimeLeftSecIP / (60*60*24)) ;
			iTempHour =  (m_iTimeLeftSecIP / (60*60)) % 24;
			iTempMin =   (m_iTimeLeftSecIP / 60 ) % 60;
			wsprintf(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER41, iTempDay, iTempHour, iTempMin);
		} else strcpy(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER42);
	}
	PutAlignedString(98, 357, 400 +10, G_cTxt);
	if (iYear != 0)
	{	wsprintf(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER43, iYear, iMonth, iDay, iHour, iMinute);
		PutAlignedString(98, 357, 415 +10, G_cTxt);
	}

#ifdef _DEBUG
	PutAlignedString(122, 315, 456, UPDATE_SCREEN_ON_SELECT_CHARACTER36);//"Test Server"
#else
	if (strcmp(m_cWorldServerName, NAME_WORLDNAME1) == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME1);//"ABADDON Server"
	else if (strcmp(m_cWorldServerName, "WS2") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME2);//"APOCALYPSE Server"
	else if (strcmp(m_cWorldServerName, "WS3") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME3);//"3rd Server"
	else if (strcmp(m_cWorldServerName, "WS4") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME4);//"4th Server"
	else if (strcmp(m_cWorldServerName, "WS5") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME5);//"5th Server"
	else if (strcmp(m_cWorldServerName, "WS6") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME6);//"6th Server"
	else if (strcmp(m_cWorldServerName, "WS7") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME7);//"7th Server"
	else if (strcmp(m_cWorldServerName, "WS8") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME8);//"8th Server"
	else if (strcmp(m_cWorldServerName, "WS9") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME9);//"9th Server"
	else if (strcmp(m_cWorldServerName, "WS10") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME10);//"10th Server"
	else if (strcmp(m_cWorldServerName, "WS11") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME11);//"11th Server"
	else if (strcmp(m_cWorldServerName, "WS12") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME12);//"12th Server"
	else if (strcmp(m_cWorldServerName, "WS13") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME13);//"13th Server"
	else if (strcmp(m_cWorldServerName, "WS14") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME14);//"14th Server"
	else if (strcmp(m_cWorldServerName, "WS15") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME15);//"15th Server"
	else if (strcmp(m_cWorldServerName, "WS16") == 0)
		PutAlignedString(129, 321, 456, MSG_WORLDNAME16);//"16th Server"
#endif



}

void CGame::UpdateScreen_OnWaitingResponse()
{
 short sX, sY, msX, msY, msZ;
 char cLB, cRB;

 DWORD dwTime = timeGetTime();
 //static class CMouseInterface * pMI;
 static DWORD dwCTime;

	if (m_cGameModeCount == 0)
	{	m_bEnterPressed = FALSE;
		m_bEscPressed   = FALSE;
		dwCTime = timeGetTime();
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_bEscPressed == TRUE)
	{	if ((dwTime - m_dwTime) > 7000)
		{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			if (m_pLSock != NULL)
			{	delete m_pLSock;
				m_pLSock = NULL;
			}
			if (m_pGSock != NULL)
			{	delete m_pGSock;
				m_pGSock = NULL;
		}	}
		m_bEscPressed = FALSE;
		return;
	}

	if ((dwTime - dwCTime) > 100)
	{	m_cMenuFrame++;
		dwCTime = dwTime;
	}
	if (m_cMenuFrame >= 8)
	{	m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8)
		{	m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;

	m_bIsHideLocalCursor = TRUE;
	m_DDraw.ClearBackB4();
	switch (m_cMsg[0]) {
	case '0':
		_Draw_UpdateScreen_OnCreateNewAccount();
		break;
	case '1':
		sX = 146;
		sY = 114;
		_Draw_OnLogin(m_cAccountName, m_cAccountPassword, 0, 0);
		break;
	case '2':
		_bDraw_OnCreateNewCharacter(m_cPlayerName, 0, 0, 0);
		break;
	case '3':
		UpdateScreen_OnSelectCharacter(0, 0, 0, 0);
		break;
	case '4':// Change Password
		UpdateScreen_OnSelectCharacter(0, 0, 0, 0, TRUE);
		break;
	case '5':
		m_DDraw.ClearBackB4();
		break;
	}
	m_bIsHideLocalCursor = FALSE;

	m_DDraw.DrawShadowBox(0,0, 639,479);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);
	PutString_SprFont(172 + 44 -17, 190, "Connected. Waiting for response...", 7,0,0);

	if ((dwTime - m_dwTime) > 7000)
	{	PutAlignedString(180, 463, 195+30, UPDATE_SCREEN_ON_WATING_RESPONSE1);
		PutAlignedString(180, 463, 195+45, UPDATE_SCREEN_ON_WATING_RESPONSE2);
	}else PutAlignedString(180, 463, 195+30, UPDATE_SCREEN_ON_WATING_RESPONSE3);

	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 8, dwTime);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::UpdateScreen_OnQueryDeleteCharacter()
{
 short msX, msY, msZ;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;

 static class CMouseInterface * pMI;
 static DWORD dwCTime;
 DWORD dwTime = timeGetTime();

	if (m_cGameModeCount == 0)
	{	pMI = new class CMouseInterface;
		pMI->AddRect(200, 244, 200 + DEF_BTNSZX, 244 + DEF_BTNSZY);
		pMI->AddRect(370, 244, 370 + DEF_BTNSZX, 244 + DEF_BTNSZY);
		//m_cCurFocus = 1;
		//m_cMaxFocus = 2;
		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;

		dwCTime = timeGetTime();

		PlaySound('E', 25, 0);
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_bEscPressed == TRUE)
	{	ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	UpdateScreen_OnSelectCharacter(0, 0, 500, 70);
	if ((m_cGameModeCount >= 0) && (m_cGameModeCount < 6))
	{	m_DDraw.DrawShadowBox(0,0,639,479);
	}else if (m_cGameModeCount >= 6)
	{	m_DDraw.DrawShadowBox(0,0,639,479);
		m_DDraw.DrawShadowBox(0,0,639,479);
	}

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);

	PutString_SprFont(172 + 86, 160, "Delete Character", 7,0,0);
	PutString(215, 195, UPDATE_SCREEN_ON_QUERY_DELETE_CHARACTER1, RGB(5,5,5));//"Character Name"
	                   //"Character Name"
	PutString(335, 199, "__________", RGB(5,5,5));
	PutString(335, 195, m_pCharList[m_wEnterGameType - 1]->m_cName, RGB(25,35,25));
	PutAlignedString(178, 453, 220, UPDATE_SCREEN_ON_QUERY_DELETE_CHARACTER2);//"Do you want to delete the character above?"

	// v2.05
	if ((msX >= 200) && (msX <= 200 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 19);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 18);

	if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 3);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 2);

	if ((dwTime - dwCTime) > 100)
	{	m_cMenuFrame++;
		dwCTime = dwTime;
	}
	if (m_cMenuFrame >= 8)
	{	m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8)
		{	m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK)
	{	PlaySound('E', 14, 5);
		switch (iMIbuttonNum) {
		case 1:
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode  = MSGID_REQUEST_DELETECHARACTER;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg,"33");
			delete pMI;
			return;

		case 2:
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			delete pMI;
			break;
	}	}
	DrawVersion();
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::NotifyMsgHandler(char * pData)
{DWORD * dwp, dwTime, dwTemp;
 WORD  * wp, wEventType;
 char  * cp, cTemp[510], cTxt[120];
 short * sp, sX, sY, sV1, sV2, sV3, sV4, sV5, sV6, sV7, sV8, sV9;
 int   * ip, i, iV1, iV2, iV3, iV4;

	dwTime = timeGetTime();

	wp   = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wEventType = *wp;

	switch (wEventType) {

	case DEF_NOTIFY_SLATE_BERSERK:		// reversed by Snoopy: 0x0BED
		AddEventList( DEF_MSG_NOTIFY_SLATE_BERSERK, 10 );//"Berserk magic casted!"
		m_bUsingSlate = TRUE;
		break;

	case DEF_NOTIFY_LOTERY_LOST:		// reversed by Snoopy: 0x0BEE:
		AddEventList( DEF_MSG_NOTIFY_LOTERY_LOST, 10 );//"You draw a blank. Please try again next time.."
		break;

	case DEF_NOTIFY_0BEF:				// 0x0BEF: // Snoopy: Crash or closes the client? (Calls SE entry !)
		// I'm noot sure at all of this function's result, so let's quit game...

		break;

	case DEF_NOTIFY_CRAFTING_SUCCESS:	//reversed by Snoopy: 0x0BF0:
		m_iContribution -= m_iContributionPrice;
		m_iContributionPrice = 0;
		DisableDialogBox(25);
		AddEventList(NOTIFY_MSG_HANDLER42, 10);		// "Item manufacture success!"
		PlaySound('E', 23, 5);
		switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			PlaySound('C', 21, 0);
			break;
		case 4:
		case 5:
		case 6:
			PlaySound('C', 22, 0);
			break;
		}
		break;

	case DEF_NOTIFY_CRAFTING_FAIL:		//reversed by Snoopy: 0x0BF1:
		m_iContributionPrice = 0;
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		iV1 = *ip; // Error reason
		switch (iV1) {
		case 1:
			AddEventList(DEF_MSG_NOTIFY_CRAFTING_NO_PART, 10);		// "There is not enough material"
			PlaySound('E', 24, 5);
			break;
		case 2:
			AddEventList(DEF_MSG_NOTIFY_CRAFTING_NO_CONTRIB, 10);	// "There is not enough Contribution Point"
			PlaySound('E', 24, 5);
			break;
		default:
		case 3:
			AddEventList(DEF_MSG_NOTIFY_CRAFTING_FAILED, 10);		// "Crafting failed"
			PlaySound('E', 24, 5);
			break;
		}
		break;

	case DEF_NOTIFY_ANGELIC_STATS:		// reversed by Snoopy: 0x0BF2
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		m_iAngelicStr = *ip;  // m_iAngelicStr
		cp +=4;
		ip = (int *)cp;
		m_iAngelicInt = *ip;  // m_iAngelicInt
		cp +=4;
		ip = (int *)cp;
		m_iAngelicDex = *ip;  // m_iAngelicDex
		cp +=4;
		ip = (int *)cp;
		m_iAngelicMag = *ip;  // m_iAngelicMag
		break;

	case DEF_NOTIFY_ITEM_CANT_RELEASE:	// reversed by Snoopy: 0x0BF3
		AddEventList(DEF_MSG_NOTIFY_NOT_RELEASED , 10 );//"Item cannot be released"
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ItemEquipHandler(*cp);
		break;

	case DEF_NOTIFY_ANGEL_FAILED:		// reversed by Snoopy: 0x0BF4
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		iV1 = *ip; // Error reason
		switch (iV1) {
		case 1: // "BFB9BBF3C4A120BECAC0BA20B9F6B1D7C0D4B4CFB4D92E20A4D02E2EA4D0" (Stolen bytes ?)
			AddEventList(DEF_MSG_NOTIFY_ANGEL_FAILED , 10 ); //"Impossible to get a Tutelary Angel." // Invented by Snoopy.
			break;
		case 2: //
			AddEventList(DEF_MSG_NOTIFY_ANGEL_MAJESTIC , 10 );//"You need additional Majesty Points."
			break;
		case 3: //
			AddEventList(DEF_MSG_NOTIFY_ANGEL_LOW_LVL , 10 ); //"Only Majesty characters can receive Tutelary Angel"
			break;
		}
		break;

	case DEF_NOTIFY_ANGEL_RECEIVED:		// reversed by Snoopy: 0x0BF5:
		AddEventList(DEF_MSG_NOTIFY_ANGEL_RECEIVED, 10 );// "You have received the Tutelary Angel."
		break;

	case DEF_NOTIFY_SPELL_SKILL:		// reversed by Snoopy: 0x0BF6
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		{	m_cMagicMastery[i] = *cp;
			cp++;
		}
		for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		{	m_cSkillMastery[i] = (unsigned char)*cp;
			if (m_pSkillCfgList[i] != NULL)
				m_pSkillCfgList[i]->m_iLevel = (int)*cp;
			cp++;
		}
		break;

	case DEF_NOTIFY_NORECALL: // Snoopy 0x0BD1
		AddEventList( "You can not recall in this map.", 10 );
		break;

	case DEF_NOTIFY_APOCGATESTARTMSG: // Snoopy 0x0BD2
		SetTopMsg("The portal to the Apocalypse is opened.", 10);
		break;

	case DEF_NOTIFY_APOCGATEENDMSG: // Snoopy 0x0BD3
		SetTopMsg("The portal to the Apocalypse is closed.", 10);
		break;

	case DEF_NOTIFY_APOCGATEOPEN: // Snoopy ;  Case BD4 of switch 00454077
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ip  = (int *)cp;
		m_iGatePositX = *ip;
		cp += 4;
		ip  = (int *)cp;
		m_iGatePositY = *ip;
		cp += 4;
		ZeroMemory(m_cGateMapName, sizeof(m_cGateMapName));
		memcpy(m_cGateMapName, cp, 10);
		cp += 10;
		break;

	case DEF_NOTIFY_QUESTCOUNTER: // Snoopy;  Case BE2 of switch 00454077
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ip  = (int *)cp;
		m_stQuest.sCurrentCount = (short)*ip;
		cp += 4;
		break;

	case DEF_NOTIFY_MONSTERCOUNT: // Snoopy ;  Case BE3 of switch 00454077
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp+=2;
		wsprintf(cTxt,"Rest Monster :%d", sV1) ;
		AddEventList(cTxt, 10);
		break;

	case DEF_NOTIFY_APOCGATECLOSE: // Snoopy ;  Case BD5 of switch 00454077
		m_iGatePositX = m_iGatePositY = -1;
		ZeroMemory(m_cGateMapName, sizeof(m_cGateMapName));
		break;

	case DEF_NOTIFY_APOCFORCERECALLPLAYERS: // Snoopy ;  Case BD7 of switch 00454077
		AddEventList( "You are recalled by force, because the Apocalypse is started.", 10 );
		break;

	case DEF_NOTIFY_ABADDONKILLED: // Snoopy ;  Case BD6 of switch 00454077
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, cp, 10);
		cp += 10;
		wsprintf(G_cTxt, "Abaddon is destroyed by %s", cTxt);
		AddEventList(G_cTxt, 10);
		break;

	case DEF_NOTIFY_0BE5: // Snoopy Abaddon's related? Thunder?;  Case BE5 of switch 00454077
/*00454255  |> B8 01000000    MOV EAX,1         ;  Case BE5 of switch 00454077
0045425A  |. 5F             POP EDI
0045425B  |. 8985 D8380700  MOV DWORD PTR SS:[EBP+738D8],EAX
00454261  |. 8985 DC380700  MOV DWORD PTR SS:[EBP+738DC],EAX
00454267  |. 8B85 88250700  MOV EAX,DWORD PTR SS:[EBP+72588]
0045426D  |. 5E             POP ESI
0045426E  |. 8985 E0380700  MOV DWORD PTR SS:[EBP+738E0],EAX
00454274  |. 5D             POP EBP
00454275  |. 5B             POP EBX
00454276  |. 81C4 10080000  ADD ESP,810
0045427C  |. C2 0400        RETN 4*/

		break;

	case DEF_NOTIFY_RESURRECTPLAYER: // Case BE9 of switch 00454077
				EnableDialogBox(50, 0, NULL, NULL);
		break;

	case DEF_NOTIFY_HELDENIANTELEPORT: //;  Case BE6 of switch 00454077
		SetTopMsg("Teleport to Heldenian field is available from now. Magic casting is forbidden until real battle.", 10);
		break;

	case DEF_NOTIFY_HELDENIANEND: //    ;  Case BE7 of switch 00454077
		SetTopMsg("Heldenian holy war has been closed.", 10);
		break;

	case DEF_NOTIFY_0BE8: // ;  Case BE8 of switch 00454077
		SetTopMsg("Characters will be recalled by force as Heldenian begins.", 10);
		break;

	case DEF_NOTIFY_HELDENIANSTART: //  Case BEA of switch 00454077
		SetTopMsg("Heldenian real battle has been started form now on.", 10);
		break;

	case DEF_NOTIFY_HELDENIANVICTORY: // Case BEB of switch 00454077
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp+=2;
		ShowHeldenianVictory(sV1);
		m_iHeldenianAresdenLeftTower	= -1;
		m_iHeldenianElvineLeftTower		= -1;
		m_iHeldenianAresdenFlags		= -1;
		m_iHeldenianElvineFlags			= -1;
		break;

	case DEF_NOTIFY_HELDENIANCOUNT: // Case BEC of switch 00454077
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		m_iHeldenianAresdenLeftTower = (int)*sp;
		cp+=2;
		sp  = (short *)cp;
		m_iHeldenianElvineLeftTower = (int)*sp;
		cp+=2;
		sp  = (short *)cp;
		m_iHeldenianAresdenFlags = (int)*sp;
		cp+=2;
		sp  = (short *)cp;
		m_iHeldenianElvineFlags = (int)*sp;
		cp+=2;
		break;

	// Slates - Diuuude
	case DEF_NOTIFY_SLATE_CREATESUCCESS:	// 0x0BC1
		AddEventList( DEF_MSG_NOTIFY_SLATE_CREATESUCCESS, 10 );
		break;
	case DEF_NOTIFY_SLATE_CREATEFAIL:		// 0x0BC2
		AddEventList( DEF_MSG_NOTIFY_SLATE_CREATEFAIL, 10 );
		break;
	case DEF_NOTIFY_SLATE_INVINCIBLE:		// 0x0BD8
		AddEventList( DEF_MSG_NOTIFY_SLATE_INVINCIBLE, 10 );
		m_bUsingSlate = TRUE;
		break;
	case DEF_NOTIFY_SLATE_MANA:				// 0x0BD9
		AddEventList( DEF_MSG_NOTIFY_SLATE_MANA, 10 );
		m_bUsingSlate = TRUE;
		break;
	case DEF_NOTIFY_SLATE_EXP:				// 0x0BE0
		AddEventList( DEF_MSG_NOTIFY_SLATE_EXP, 10 );
		m_bUsingSlate = TRUE;
		break;
	case DEF_NOTIFY_SLATE_STATUS:			// 0x0BE1
		AddEventList( DEF_MSG_NOTIFY_SLATECLEAR, 10 ); // "The effect of the prophecy-slate is disappeared."
		m_bUsingSlate = FALSE;
		break;

	// MJ Stats Change - Diuuude: Erreur, ici il s'agit de sorts et skills, le serveur comme la v351 sont aussi bugués !
	case DEF_NOTIFY_STATECHANGE_SUCCESS:	// 0x0BB5
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		{	m_cMagicMastery[i] = *cp;
			cp++;
		}
		for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		{	m_cSkillMastery[i] = (unsigned char)*cp;
			if (m_pSkillCfgList[i] != NULL)
				m_pSkillCfgList[i]->m_iLevel = (int)*cp;
			//else m_pSkillCfgList[i]->m_iLevel = 0;
			cp++;
		}
		// MJ Stats Change - Diuuude
		m_iStr += m_cLU_Str;
		m_iVit += m_cLU_Vit;
		m_iDex += m_cLU_Dex;
		m_iInt += m_cLU_Int;
		m_iMag += m_cLU_Mag;
		m_iCharisma += m_cLU_Char;
		m_iLU_Point = m_iLevel*3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
		m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
		AddEventList( "Your stat has been changed.", 10 ); // "Your stat has been changed."
		break;

	case DEF_NOTIFY_LEVELUP: // 0x0B16
		NotifyMsg_LevelUp(pData);
		break;

	case DEF_NOTIFY_STATECHANGE_FAILED:		// 0x0BB6
		m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
		m_iLU_Point = m_iLevel*3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
		AddEventList( "Your stat has not been changed.", 10 );
		break;

	case DEF_NOTIFY_SETTING_FAILED: // 0x0BB4 -  Case BB4 of switch 00454077
		AddEventList( "Your stat has not been changed.", 10 );
		m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
		m_iLU_Point = m_iLevel*3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
		break;

	// CLEROTH - LU
	case DEF_NOTIFY_SETTING_SUCCESS: // 0x0BB3 - envoie le niv et les stats
		NotifyMsg_SettingSuccess(pData);
		break;

	case DEF_NOTIFY_AGRICULTURENOAREA:		// 0x0BB2
		AddEventList( DEF_MSG_NOTIFY_AGRICULTURENOAREA, 10 );
		break;
	case DEF_NOTIFY_AGRICULTURESKILLLIMIT:	// 0x0BB1
		AddEventList( DEF_MSG_NOTIFY_AGRICULTURESKILLLIMIT, 10 );
		break;

	case DEF_NOTIFY_NOMOREAGRICULTURE:		// 0x0BB0
		AddEventList( DEF_MSG_NOTIFY_NOMOREAGRICULTURE, 10 );
		break;
	case DEF_NOTIFY_SPAWNEVENT:				// 0x0BAA
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		m_sMonsterID = (short)(*cp);
		cp++;
		sp  = (short *)cp;
		m_sEventX = *sp;
		cp+=2;
		sp  = (short *)cp;
		m_sEventY = *sp;
		cp+=2;
		m_dwMonsterEventTime = dwTime;
		break;

	case DEF_NOTIFY_CHANGEPLAYMODE:			// 0x0BA9
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		memcpy(m_cLocation, cp, 10);
		cp += 10;
		if (memcmp(m_cLocation, "aresden", 7) == 0)
		{	m_bAresden = TRUE;
			m_bCitizen = TRUE;
			m_bHunter = FALSE;
		}else if (memcmp(m_cLocation, "arehunter", 9) == 0)
		{	m_bAresden = TRUE;
			m_bCitizen = TRUE;
			m_bHunter = TRUE;
		}else if (memcmp(m_cLocation, "elvine", 6) == 0)
		{	m_bAresden = FALSE;
			m_bCitizen = TRUE;
			m_bHunter = FALSE;
		}else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
		{	m_bAresden = FALSE;
			m_bCitizen = TRUE;
			m_bHunter = TRUE;
		}else
		{	m_bAresden = TRUE;
			m_bCitizen = FALSE;
			m_bHunter = TRUE;
		}
		AddEventList( DEF_MSG_GAMEMODE_CHANGED, 10 );
		break;

	case DEF_NOTIFY_REQGUILDNAMEANSWER:	 //   0x0BA6
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		sp  = (short *)cp;
		sV2 = *sp;
		cp += 2;
		ZeroMemory(cTemp, sizeof(cTemp));
		memcpy(cTemp, cp, 20);
		cp += 20;

		ZeroMemory( m_stGuildName[sV2].cGuildName, sizeof(m_stGuildName[sV2].cGuildName) );
		strcpy(m_stGuildName[sV2].cGuildName, cTemp);
		m_stGuildName[sV2].iGuildRank = sV1;
		for (i = 0; i < 20; i++) if (m_stGuildName[sV2].cGuildName[i] == '_') m_stGuildName[sV2].cGuildName[i] = ' ';
		break;

	case DEF_NOTIFY_FORCERECALLTIME: // 0x0BA7
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		if ( (int)(sV1/20) > 0)
			wsprintf(G_cTxt,NOTIFY_MSG_FORCERECALLTIME1,(int) (sV1/20)) ;
		else
			wsprintf(G_cTxt,NOTIFY_MSG_FORCERECALLTIME2) ;
		AddEventList(G_cTxt, 10);
		break;

	case DEF_NOTIFY_GIZONITEMUPGRADELEFT: // 0x0BA4// Item upgrade is possible.
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		m_iGizonItemUpgradeLeft = sV1;
		dwp = (DWORD *)cp;
		switch (*dwp) {
		case 1: //
			AddEventList(NOTIFY_MSG_HANDLER_GIZONITEMUPGRADELEFT1, 10);
			break;
		}
		//wsprintf(G_cTxt,"majesty: %d", m_iGizonItemUpgradeLeft);
		//DebugLog(G_cTxt);
		cp += 4;
		break;

	case DEF_NOTIFY_GIZONEITEMCHANGE: // 0x0BA5
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		m_pItemList[sV1]->m_cItemType = *cp ;
		cp++ ;
		wp  = (WORD *)cp;
		m_pItemList[sV1]->m_wCurLifeSpan = *wp;
		cp += 2;
		sp  = (short *)cp;
		m_pItemList[sV1]->m_sSprite = *sp;
		cp += 2;
		sp  = (short *)cp;
		m_pItemList[sV1]->m_sSpriteFrame = *sp;
		cp += 2;
		m_pItemList[sV1]->m_cItemColor = *cp ;
		cp++ ;
		m_pItemList[sV1]->m_sItemSpecEffectValue2 = *cp ;
		cp++ ;
		dwp = (DWORD *) cp ;
		m_pItemList[sV1]->m_dwAttribute =  *dwp ;
		cp +=4 ;
		ZeroMemory( m_pItemList[sV1]->m_cName, sizeof(m_pItemList[sV1]->m_cName) );
		memcpy(m_pItemList[sV1]->m_cName,cp,20) ;
		cp += 20 ;
		if (m_bIsDialogEnabled[34] == TRUE)
		{	m_stDialogBoxInfo[34].cMode = 3; // succes
		}
		PlaySound('E', 23, 5);
		switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			PlaySound('C', 21, 0);
			break;

		case 4:
		case 5:
		case 6:
			PlaySound('C', 22, 0);
			break;
		}
		break;

	case DEF_NOTIFY_ITEMATTRIBUTECHANGE: // 0x0BA3
	case 0x0BC0: // 0x0BC0 Unknown msg, but real in client v3.51
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		dwTemp = m_pItemList[sV1]->m_dwAttribute;
		dwp  = (DWORD *)cp;
		m_pItemList[sV1]->m_dwAttribute = *dwp;
		cp += 4;
		dwp  = (DWORD *)cp;
		if (*dwp != 0) m_pItemList[sV1]->m_sItemSpecEffectValue1 = (short)*dwp;
		cp += 4;
		dwp  = (DWORD *)cp;
		if (*dwp != 0) m_pItemList[sV1]->m_sItemSpecEffectValue2 = (short)*dwp;
		cp += 4;
		if (dwTemp == m_pItemList[sV1]->m_dwAttribute)
		{	if (m_bIsDialogEnabled[34] == TRUE)
			{	m_stDialogBoxInfo[34].cMode = 4;// Failed
			}
			PlaySound('E', 24, 5);
		}else
		{	if (m_bIsDialogEnabled[34] == TRUE)
			{	m_stDialogBoxInfo[34].cMode = 3; // Success
			}
			PlaySound('E', 23, 5);
			switch (m_sPlayerType) {
			case 1:
			case 2:
			case 3:
				PlaySound('C', 21, 0);
				break;
			case 4:
			case 5:
			case 6:
				PlaySound('C', 22, 0);
				break;
		}	}
		break;

	case DEF_NOTIFY_ITEMUPGRADEFAIL:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		if (m_bIsDialogEnabled[34] == FALSE) return ;
		PlaySound('E', 24, 5);
		switch(sV1){
		case 1:
			m_stDialogBoxInfo[34].cMode = 8 ; // Failed
			break ;
		case 2:
			m_stDialogBoxInfo[34].cMode = 9 ; // Failed
			break ;
		case 3:
			m_stDialogBoxInfo[34].cMode = 10 ; // Failed
			break ;
		}
		break;

	case DEF_NOTIFY_PARTY:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;
		sp  = (short *)cp;
		sV2 = *sp;
		cp += 2;
		sp  = (short *)cp;
		sV3 = *sp;
		cp += 2;
		switch (sV1) {
		case 1: //
			switch (sV2) {
			case 0:
				EnableDialogBox(32, NULL, NULL, NULL);
				m_stDialogBoxInfo[32].cMode = 9;
				break;

			case 1:
				m_iPartyStatus = 1;
				m_iTotalPartyMember = NULL;
				EnableDialogBox(32, NULL, NULL, NULL);
				m_stDialogBoxInfo[32].cMode = 8;
				for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, NULL, 2, NULL, NULL, m_cMCName);
				break;
			}
			break;

		case 2: //
			m_iPartyStatus = 0;
			m_iTotalPartyMember = NULL;
			EnableDialogBox(32, NULL, NULL, NULL);
			m_stDialogBoxInfo[32].cMode = 10;
			for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
			break;

		case 4:
			ZeroMemory(cTxt, sizeof(cTxt));
			memcpy(cTxt, cp, 10);
			cp += 10;

			switch (sV2) {
			case 0: //
				EnableDialogBox(32, NULL, NULL, NULL);
				m_stDialogBoxInfo[32].cMode = 9;
				break;

			case 1: //
				if (strcmp(cTxt, m_cPlayerName) == 0) {
					m_iPartyStatus = 2;
					EnableDialogBox(32, NULL, NULL, NULL);
					m_stDialogBoxInfo[32].cMode = 8;
				}
				else {
					wsprintf(G_cTxt, NOTIFY_MSG_HANDLER1, cTxt);
					AddEventList(G_cTxt, 10);
				}

				m_iTotalPartyMember++;
				for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
				if (strlen(m_stPartyMemberNameList[i].cName) == 0) {
					ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
					memcpy(m_stPartyMemberNameList[i].cName, cTxt, 10);
					goto NMH_LOOPBREAK1;
				}
NMH_LOOPBREAK1:;
				break;

			case 2: //
				break;
			}
			break;

		case 5: //
			m_iTotalPartyMember = NULL;
			for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));

			m_iTotalPartyMember = sV3;
			for (i = 1; i <= sV3; i++) {
				ZeroMemory(m_stPartyMemberNameList[i-1].cName, sizeof(m_stPartyMemberNameList[i-1].cName));
				memcpy(m_stPartyMemberNameList[i-1].cName, cp, 10);
				cp += 11;
			}
			break;

		default:
			sp  = (short *)cp;
			sV4 = *sp;
			cp += 2;
			break;

		case 6:
			ZeroMemory(cTxt, sizeof(cTxt));
			memcpy(cTxt, cp, 10);
			cp += 10;

			switch (sV2) {
			case 0: //
				EnableDialogBox(32, NULL, NULL, NULL);
				m_stDialogBoxInfo[32].cMode = 7;
				break;

			case 1: //
				if (strcmp(cTxt, m_cPlayerName) == 0) {
					m_iPartyStatus = 0;
					EnableDialogBox(32, NULL, NULL, NULL);
					m_stDialogBoxInfo[32].cMode = 6;
				}
				else {
					wsprintf(G_cTxt, NOTIFY_MSG_HANDLER2 , cTxt);
					AddEventList(G_cTxt, 10);
				}
				for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
				if (strcmp(m_stPartyMemberNameList[i].cName, cTxt) == 0) {
					ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
					m_iTotalPartyMember--;
					goto NMH_LOOPBREAK2;
				}
NMH_LOOPBREAK2:;
				break;
			}
			break;

		case 7: //
			EnableDialogBox(32, NULL, NULL, NULL);
			m_stDialogBoxInfo[32].cMode = 9;
			break;

		case 8: //
			m_iPartyStatus = 0;
			m_iTotalPartyMember = NULL;
			for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
			break;
		}
		break;

	case DEF_NOTIFY_CANNOTCONSTRUCT:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;

		CannotConstruct(sV1);
		PlaySound('E', 25, 0, 0);
		break;

	case DEF_NOTIFY_TCLOC:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

		sp  = (short *)cp;
		m_iTeleportLocX = *sp;
		cp += 2;

		sp  = (short *)cp;
		m_iTeleportLocY = *sp;
		cp += 2;

		ZeroMemory(m_cTeleportMapName, sizeof(m_cTeleportMapName));
		memcpy(m_cTeleportMapName, cp, 10);
		cp += 10;

		sp  = (short *)cp;
		m_iConstructLocX = *sp;
		cp += 2;

		sp  = (short *)cp;
		m_iConstructLocY = *sp;
		cp += 2;

		ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
		memcpy(m_cConstructMapName, cp, 10);
		cp += 10;
		break;

	case DEF_NOTIFY_CONSTRUCTIONPOINT:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

		sp  = (short *)cp;
		sV1 = *sp;
		cp += 2;

		sp  = (short *)cp;
		sV2 = *sp;
		cp += 2;

		sp  = (short *)cp;
		sV3 = *sp;
		cp += 2;

		if (sV3 == 0) {
			if ((sV1 > m_iConstructionPoint) && (sV2 > m_iWarContribution)) {
				wsprintf(G_cTxt, "%s +%d, %s +%d", m_pGameMsgList[13]->m_pMsg, (sV1 - m_iConstructionPoint), m_pGameMsgList[21]->m_pMsg, (sV2 - m_iWarContribution));
				SetTopMsg(G_cTxt, 5);
				PlaySound('E', 23, 0, 0);
			}

			if ((sV1 > m_iConstructionPoint) && (sV2 == m_iWarContribution)) {
				if (m_iCrusadeDuty == 3) {
					wsprintf(G_cTxt, "%s +%d", m_pGameMsgList[13]->m_pMsg, sV1 - m_iConstructionPoint);
					SetTopMsg(G_cTxt, 5);
					PlaySound('E', 23, 0, 0);
				}
			}

			if ((sV1 == m_iConstructionPoint) && (sV2 > m_iWarContribution)) {
				wsprintf(G_cTxt, "%s +%d", m_pGameMsgList[21]->m_pMsg, sV2 - m_iWarContribution);
				SetTopMsg(G_cTxt, 5);
				PlaySound('E', 23, 0, 0);
			}

			if (sV1 < m_iConstructionPoint) {
				if (m_iCrusadeDuty == 3) {
					wsprintf(G_cTxt, "%s -%d", m_pGameMsgList[13]->m_pMsg, m_iConstructionPoint - sV1);
					SetTopMsg(G_cTxt, 5);
					PlaySound('E', 25, 0, 0);
				}
			}

			if (sV2 < m_iWarContribution) {
				wsprintf(G_cTxt, "%s -%d", m_pGameMsgList[21]->m_pMsg, m_iWarContribution - sV2);
				SetTopMsg(G_cTxt, 5);
				PlaySound('E', 24, 0, 0);
			}
		}

		m_iConstructionPoint = sV1;
		m_iWarContribution   = sV2;
		break;

	case DEF_NOTIFY_NOMORECRUSADESTRUCTURE:
		SetTopMsg(m_pGameMsgList[12]->m_pMsg, 5);
		PlaySound('E', 25, 0, 0);
		break;

	case DEF_NOTIFY_GRANDMAGICRESULT:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

		wp  = (WORD *)cp;
		sV1 = *wp;
		cp += 2;

		wp  = (WORD *)cp;
		sV2 = *wp;
		cp += 2;

		wp  = (WORD *)cp;
		sV3 = *wp;
		cp += 2;

		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, cp, 10);
		cp += 10;

		wp  = (WORD *)cp;
		sV4 = *wp;
		cp += 2;

		wp  = (WORD *)cp;
		sV5 = *wp;  //
		cp += 2;

		if (sV5  > 0 ) {
			wp  = (WORD *)cp;
			sV6 = *wp;
			cp += 2;
			sV5-- ;
		}
		else sV6 = 0 ;

		if ( sV5  > 0 ) {
			wp  = (WORD *)cp;
			sV7 = *wp;
			cp += 2;
			sV5-- ;
		}
		else sV7 = 0 ;

		if ( sV5  > 0 ) {
			wp  = (WORD *)cp;
			sV8 = *wp;
			cp += 2;
			sV5-- ;
		}
		else sV8 = 0 ;

		if ( sV5  > 0 ) {
			wp  = (WORD *)cp;
			sV9 = *wp;
			cp += 2;
			sV5-- ;
		}
		else sV9 = 0 ;

		GrandMagicResult(cTxt, sV1, sV2, sV3, sV4, sV6, sV7, sV8, sV9);
		break;

	case DEF_NOTIFY_METEORSTRIKECOMING:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		wp  = (WORD *)cp;
		sV1 = *wp;
		cp += 2;
		MeteorStrikeComing(sV1);
		PlaySound('E', 25, 0, 0);
		break;

	case DEF_NOTIFY_METEORSTRIKEHIT:
		SetTopMsg(m_pGameMsgList[17]->m_pMsg, 5);
		//StartMeteorStrikeEffect
		for( i=0 ; i<36 ; i++ ) bAddNewEffect(60, m_sViewPointX +(rand() % 640), m_sViewPointY +(rand() % 480), NULL, NULL, -(rand() % 80));
		break;

	case DEF_NOTIFY_MAPSTATUSNEXT:
		AddMapStatusInfo(pData, FALSE);
		break;

	case DEF_NOTIFY_MAPSTATUSLAST:
		AddMapStatusInfo(pData, TRUE);
		break;

	case DEF_NOTIFY_LOCKEDMAP:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		sV1 = *sp;
		cp += 2;

		ZeroMemory(cTemp, sizeof(cTemp));
		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, cp, 10);
		cp += 10;

		GetOfficialMapName(cTxt, cTemp);
		wsprintf( G_cTxt, NOTIFY_MSG_HANDLER3, sV1, cTemp );
		SetTopMsg(G_cTxt, 10);
		PlaySound('E', 25, 0, 0);
		break;

	case DEF_NOTIFY_CRUSADE: // Crusade msg
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		iV1 = *ip; // Crusademode
		cp += 4;
		ip = (int *)cp;
		iV2 = *ip; // crusade duty
		cp += 4;
		ip = (int *)cp;
		iV3 = *ip;
		cp += 4;
		ip = (int *)cp;
		iV4 = *ip;
		cp += 4;
		if (m_bIsCrusadeMode == FALSE)
		{	if (iV1 != 0) // begin crusade
			{	m_bIsCrusadeMode = TRUE;
				m_iCrusadeDuty = iV2;
				if( (m_iCrusadeDuty != 3) && (m_bCitizen==TRUE) )
					_RequestMapStatus("middleland", 3);
				if (m_iCrusadeDuty != NULL)
					 EnableDialogBox(33, 2, iV2, NULL);
				else EnableDialogBox(33, 1, NULL, NULL);
				if( m_bCitizen == FALSE ) EnableDialogBox(18, 800, NULL, NULL);
				else if( m_bAresden == TRUE ) EnableDialogBox(18, 801, NULL, NULL);
				else if( m_bAresden == FALSE ) EnableDialogBox(18, 802, NULL, NULL);
				if (m_bCitizen == FALSE) SetTopMsg(NOTIFY_MSG_CRUSADESTART_NONE, 10);
				else SetTopMsg(m_pGameMsgList[9]->m_pMsg, 10);
				PlaySound('E', 25, 0, 0);
			}
			if (iV3 != 0) // Crusade finished, show XP result screen
			{	CrusadeContributionResult(iV3);
			}
			if (iV4 == -1) // The crusade you played in was finished.
			{	CrusadeContributionResult(0); // You connect in this crusade, but did not connect after previous one => no XP....
			}
		}else
		{	if (iV1 == 0) // crusade finished show result (1st result: winner)
			{	m_bIsCrusadeMode = FALSE;
				m_iCrusadeDuty   = NULL;
				CrusadeWarResult(iV4);
				SetTopMsg(m_pGameMsgList[57]->m_pMsg, 8);
			}else
			{	if (m_iCrusadeDuty != iV2)
				{	m_iCrusadeDuty = iV2;
					EnableDialogBox(33, 2, iV2, NULL);
					PlaySound('E', 25, 0, 0);
			}	}
			if (iV4 == -1)
			{	CrusadeContributionResult(0); // You connect in this crusade, but did not connect after previous one => no XP....
		}	}
		break;

	case DEF_NOTIFY_SPECIALABILITYSTATUS:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		sV1 = *sp;
		cp += 2;
		sp = (short *)cp;
		sV2 = *sp;
		cp += 2;
		sp = (short *)cp;
		sV3 = *sp;
		cp += 2;
		if (sV1 == 1) // Use SA
		{	PlaySound('E', 35, 0);
			AddEventList(NOTIFY_MSG_HANDLER4, 10); // "Use special ability!"
			switch (sV2) {
			case 1: wsprintf(G_cTxt, NOTIFY_MSG_HANDLER5,sV3); break;//"You are untouchable for %d seconds!"
			case 2: wsprintf(G_cTxt, NOTIFY_MSG_HANDLER6, sV3); break;//"
			case 3: wsprintf(G_cTxt, NOTIFY_MSG_HANDLER7, sV3); break;//"
			case 4: wsprintf(G_cTxt, NOTIFY_MSG_HANDLER8, sV3); break;//"
			case 5: wsprintf(G_cTxt, NOTIFY_MSG_HANDLER9, sV3); break;//"
			case 50:wsprintf(G_cTxt, NOTIFY_MSG_HANDLER10, sV3); break;//"
			case 51:wsprintf(G_cTxt, NOTIFY_MSG_HANDLER11, sV3); break;//"
			case 52:wsprintf(G_cTxt, NOTIFY_MSG_HANDLER12, sV3); break;//"
			case 55: // Spell effect
				if (sV3 >90)
					wsprintf(G_cTxt, "You cast a powerfull incantation, you can't use it again before %d minutes.", sV3/60);
				else
					wsprintf(G_cTxt, "You cast a powerfull incantation, you can't use it again before %d seconds.", sV3);
				break;
			}
			AddEventList(G_cTxt, 10);
		}else if (sV1 == 2) // Finished using
		{	if (m_iSpecialAbilityType != (int)sV2)
			{	PlaySound('E', 34, 0);
				AddEventList(NOTIFY_MSG_HANDLER13, 10);//"Special ability has been set!"
				if (sV3 >= 60)
				{	switch (sV2) {
					case 1: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER14, sV3/60); AddEventList(G_cTxt, 10); break;//"Ability that decreases enemy's HP by 50%: Can use after %dMin"
					case 2: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER15, sV3/60); AddEventList(G_cTxt, 10); break;//"
					case 3: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER16, sV3/60); AddEventList(G_cTxt, 10); break;//"
					case 4: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER17, sV3/60); AddEventList(G_cTxt, 10); break;//"
					case 5: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER18, sV3/60); AddEventList(G_cTxt, 10); break;//"
					case 50:wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER19, sV3/60); AddEventList(G_cTxt, 10); break;//"
					case 51:wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER20, sV3/60); AddEventList(G_cTxt, 10); break;//"
					case 52:wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER21, sV3/60); AddEventList(G_cTxt, 10); break;//"
					}
				}else
				{	switch (sV2) {
					case 1: wsprintf(G_cTxt, NOTIFY_MSG_HANDLER22, sV3); AddEventList(G_cTxt, 10); break;//"
					case 2: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER23, sV3); AddEventList(G_cTxt, 10); break;//"
					case 3: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER24, sV3); AddEventList(G_cTxt, 10); break;//"
					case 4: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER25, sV3); AddEventList(G_cTxt, 10); break;//"
					case 5: wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER26, sV3); AddEventList(G_cTxt, 10); break;//"
					case 50:wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER27, sV3); AddEventList(G_cTxt, 10); break;//"
					case 51:wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER28, sV3); AddEventList(G_cTxt, 10); break;//"
					case 52:wsprintf(G_cTxt,  NOTIFY_MSG_HANDLER29, sV3); AddEventList(G_cTxt, 10); break;//""Ability that makes character untouchable: Can use after %dSec"
			}	}	}
			m_iSpecialAbilityType = (int)sV2;
			m_dwSpecialAbilitySettingTime = dwTime;
			m_iSpecialAbilityTimeLeftSec  = (int)sV3;
		}else if (sV1 == 3)  // End of using time
		{	m_bIsSpecialAbilityEnabled = FALSE;
			m_dwSpecialAbilitySettingTime = dwTime;
			if (sV3 == 0)
			{	m_iSpecialAbilityTimeLeftSec  = 1200;
				AddEventList(NOTIFY_MSG_HANDLER30, 10);//"Special ability has run out! Will be available in 20 minutes."
			}else
			{	m_iSpecialAbilityTimeLeftSec  = (int)sV3;
				if (sV3 >90)
					 wsprintf(G_cTxt, "Special ability has run out! Will be available in %d minutes." , sV3/60);
				else wsprintf(G_cTxt, "Special ability has run out! Will be available in %d seconds." , sV3);
				AddEventList(G_cTxt, 10);
			}
		}else if (sV1 == 4) // Unequiped the SA item
		{	AddEventList(NOTIFY_MSG_HANDLER31, 10);//"Special ability has been released."
			m_iSpecialAbilityType = 0;
		}else if (sV1 == 5) // Angel
		{	PlaySound('E', 52, 0); // Angel
		}
		break;

	case DEF_NOTIFY_SPECIALABILITYENABLED:
		if (m_bIsSpecialAbilityEnabled == FALSE) {
			PlaySound('E', 30, 5);
			AddEventList(NOTIFY_MSG_HANDLER32, 10);//"
		}
		m_bIsSpecialAbilityEnabled = TRUE;
		break;

	case DEF_NOTIFY_ENERGYSPHEREGOALIN:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		sV1 = *sp;
		cp += 2;
		sp = (short *)cp;
		sV2 = *sp;
		cp += 2;
		sp = (short *)cp;
		sV3 = *sp;
		cp += 2;
		ZeroMemory(cTxt, sizeof(cTxt));
		memcpy(cTxt, cp, 20);

		if (sV2 == sV3)
		{	PlaySound('E', 24, 0);
			if (strcmp(cTxt, m_cPlayerName) == 0)
			{	AddEventList(NOTIFY_MSG_HANDLER33, 10);//You pushed energy sphere to enemy's energy portal! Contribution point will be decreased by 10 points."
				m_iContribution += sV1; // fixed, server must match...
				m_iContributionPrice = 0;
				if (m_iContribution < 0) m_iContribution = 0;
			}
			else {
				ZeroMemory(G_cTxt, sizeof(G_cTxt));
				if( m_bAresden == TRUE ) wsprintf(G_cTxt, NOTIFY_MSG_HANDLER34, cTxt);//"%s(Aresden) pushed energy sphere to enemy's portal!!..."
				else if (m_bAresden == FALSE) wsprintf(G_cTxt, NOTIFY_MSG_HANDLER34_ELV, cTxt);//"%s(Elvine) pushed energy sphere to enemy's portal!!..."
				AddEventList(G_cTxt, 10);
			}
		}else
		{	PlaySound('E', 23, 0);
			if (strcmp(cTxt, m_cPlayerName) == 0)
			{	switch (m_sPlayerType) {
				case 1:
				case 2:
				case 3:	PlaySound('C', 21, 0); break;
				case 4:
				case 5:
				case 6:	PlaySound('C', 22, 0); break;
				}
				AddEventList(NOTIFY_MSG_HANDLER35, 10);//"Congulaturations! You brought energy sphere to energy portal and earned experience and prize gold!"

				m_iContribution += 5;
				if (m_iContribution < 0) m_iContribution = 0;
			}else
			{	ZeroMemory(G_cTxt, sizeof(G_cTxt));
				if (sV3 == 1)
				{	wsprintf(G_cTxt, NOTIFY_MSG_HANDLER36, cTxt);//"Elvine %s : Goal in!"
					AddEventList(G_cTxt, 10);
				}else if (sV3 == 2)
				{	wsprintf(G_cTxt, NOTIFY_MSG_HANDLER37, cTxt);//"Aresden %s : Goal in!"
					AddEventList(G_cTxt, 10);
		}	}	}
		break;

	case DEF_NOTIFY_ENERGYSPHERECREATED:
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		sV1 = *sp;
		cp += 2;
		sp = (short *)cp;
		sV2 = *sp;
		cp += 2;
		ZeroMemory(G_cTxt, sizeof(G_cTxt));
		wsprintf(G_cTxt, NOTIFY_MSG_HANDLER38, sV1, sV2);//"Energy sphere was dropped in (%d, %d) of middleland!"
		AddEventList(G_cTxt, 10);
		AddEventList(NOTIFY_MSG_HANDLER39, 10);//"A player who pushed energy sphere to the energy portal of his city will earn many Exp and Contribution."
		break;

	case DEF_NOTIFY_QUERY_JOINPARTY:
		EnableDialogBox(32, NULL, NULL, NULL);
		m_stDialogBoxInfo[32].cMode = 1;
		ZeroMemory(m_stDialogBoxInfo[32].cStr, sizeof(m_stDialogBoxInfo[32].cStr));
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		strcpy(m_stDialogBoxInfo[32].cStr, cp);
		break;

	case DEF_NOTIFY_RESPONSE_CREATENEWPARTY:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;

		if ((BOOL)*sp == TRUE)
		{	m_stDialogBoxInfo[32].cMode = 2;
		}else
		{	m_stDialogBoxInfo[32].cMode = 3;
		}
		break;

	case DEF_NOTIFY_DAMAGEMOVE:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		m_sDamageMove = *sp;
		cp += 2;
		sp = (short *)cp;
		m_sDamageMoveAmount = *sp;
		cp += 2;
		break;

	case DEF_NOTIFY_OBSERVERMODE:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		if (*sp == 1)
		{	AddEventList(NOTIFY_MSG_HANDLER40);//"Observer Mode On. Press 'SHIFT + ESC' to Log Out..."
			m_bIsObserverMode = TRUE;
			m_dwObserverCamTime = timeGetTime();
			char cName[12];
			ZeroMemory(cName, sizeof(cName));
			memcpy(cName, m_cPlayerName, 10);
			m_pMapData->bSetOwner(m_sPlayerObjectID, -1, -1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, cName, NULL, NULL, NULL, NULL);
		}else
		{	AddEventList(NOTIFY_MSG_HANDLER41);//"Observer Mode Off"
			m_bIsObserverMode = FALSE;
			m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir, m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, m_iPlayerStatus, m_cPlayerName, DEF_OBJECTSTOP, NULL, NULL, NULL);
		}
		break;

	case DEF_NOTIFY_BUILDITEMSUCCESS:
		DisableDialogBox(26);
		cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
		sp = (short *)cp;
		sV1 = *sp;
		cp += 2;
		sp = (short *)cp;
		sV2 = *sp;
		cp += 2;
		if (sV1 < 10000)
		{	EnableDialogBox(26, 6, 1, sV1, NULL);
			m_stDialogBoxInfo[26].sV1 = sV2;
		}else
		{	EnableDialogBox(26, 6, 1, -1*(sV1 - 10000), NULL);
			m_stDialogBoxInfo[26].sV1 = sV2;
		}
		AddEventList(NOTIFY_MSG_HANDLER42, 10);
		PlaySound('E', 23, 5);
		switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			PlaySound('C', 21, 0);
			break;

		case 4:
		case 5:
		case 6:
			PlaySound('C', 22, 0);
			break;
		}
		break;

	case DEF_NOTIFY_BUILDITEMFAIL:
		DisableDialogBox(26);
		EnableDialogBox(26, 6, 0, NULL);
		AddEventList(NOTIFY_MSG_HANDLER43, 10);
		PlaySound('E', 24, 5);
		break;

	case DEF_NOTIFY_QUESTREWARD:
		NotifyMsg_QuestReward(pData);
		break;

	case DEF_NOTIFY_QUESTCOMPLETED:
		m_stQuest.bIsQuestCompleted = TRUE;
		DisableDialogBox(28);
		EnableDialogBox(28, 1, NULL, NULL);
		switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:	PlaySound('C', 21, 0); break;
		case 4:
		case 5:
		case 6:	PlaySound('C', 22, 0); break;
		}
		PlaySound('E', 23, 0);
		AddEventList(NOTIFY_MSG_HANDLER44, 10);
		break;

	case DEF_NOTIFY_QUESTABORTED:
		m_stQuest.sQuestType = NULL;
		DisableDialogBox(28);
		EnableDialogBox(28, 2, NULL, NULL);
		break;

	case DEF_NOTIFY_QUESTCONTENTS:
		NotifyMsg_QuestContents(pData);
		break;

	case DEF_NOTIFY_ITEMCOLORCHANGE:
		NotifyMsg_ItemColorChange(pData);
		break;

	case DEF_NOTIFY_DROPITEMFIN_COUNTCHANGED:
		NotifyMsg_DropItemFin_CountChanged(pData);
		break;

	case DEF_NOTIFY_CANNOTGIVEITEM:
		NotifyMsg_CannotGiveItem(pData);
		break;

	case DEF_NOTIFY_GIVEITEMFIN_COUNTCHANGED:
		NotifyMsg_GiveItemFin_CountChanged(pData);
		break;

	case DEF_NOTIFY_EXCHANGEITEMCOMPLETE:
		AddEventList(NOTIFYMSG_EXCHANGEITEM_COMPLETE1, 10);
		DisableDialogBox(27);
		//Snoopy: MultiTrade
		DisableDialogBox(41);
		PlaySound('E', 23, 5);
		break;

	case DEF_NOTIFY_CANCELEXCHANGEITEM:
		PlaySound('E', 24, 5);
		AddEventList(NOTIFYMSG_CANCEL_EXCHANGEITEM1, 10);
		AddEventList(NOTIFYMSG_CANCEL_EXCHANGEITEM2, 10);
		//Snoopy: MultiTrade
		DisableDialogBox(41);
		DisableDialogBox(27);
		break;

	case DEF_NOTIFY_SETEXCHANGEITEM:
		NotifyMsg_SetExchangeItem(pData);
		break;

	case DEF_NOTIFY_OPENEXCHANGEWINDOW:
		NotifyMsg_OpenExchageWindow(pData);
		break;

	case DEF_NOTIFY_NOTFLAGSPOT:
		AddEventList(NOTIFY_MSG_HANDLER45, 10);
		break;

	case DEF_NOTIFY_ITEMPOSLIST:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		for (i = 0; i < DEF_MAXITEMS; i++) {
			sp = (short *)cp;
			sX = *sp;
			cp += 2;
			sp = (short *)cp;
			sY = *sp;
			cp += 2;
			if (m_pItemList[i] != NULL) {
				if (sY < -10) sY = -10;
				if (sX < 0)   sX = 0;
				if (sX > 170) sX = 170;
				if (sY > 95)  sY = 95;

				m_pItemList[i]->m_sX = sX;
				m_pItemList[i]->m_sY = sY;
			}
		}
		break;

	case DEF_NOTIFY_ENEMYKILLS:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		m_iEnemyKillCount = *ip;
		break;

	case DEF_NOTIFY_DOWNSKILLINDEXSET:
		NotifyMsg_DownSkillIndexSet(pData);
		break;

	case DEF_NOTIFY_ADMINIFO:
		NotifyMsg_AdminInfo(pData);
		break;

	case DEF_NOTIFY_NPCTALK:
		NpcTalkHandler(pData);
		break;

	case DEF_NOTIFY_PORTIONSUCCESS:
		AddEventList(NOTIFY_MSG_HANDLER46, 10);
		break;

	case DEF_NOTIFY_PORTIONFAIL:
		AddEventList(NOTIFY_MSG_HANDLER47, 10);
		break;

	case DEF_NOTIFY_LOWPORTIONSKILL:
		AddEventList(NOTIFY_MSG_HANDLER48, 10);
		break;

	case DEF_NOTIFY_NOMATCHINGPORTION:
		AddEventList(NOTIFY_MSG_HANDLER49, 10);
		break;

	case DEF_NOTIFY_SUPERATTACKLEFT:
		sp = (short *)(pData + DEF_INDEX2_MSGTYPE + 2);
		m_iSuperAttackLeft = (int)*sp;
		break;

	case DEF_NOTIFY_SAFEATTACKMODE:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		switch (*cp) {
		case 1:
			if(!m_bIsSafeAttackMode) AddEventList(NOTIFY_MSG_HANDLER50, 10);//"
			m_bIsSafeAttackMode = TRUE;
			break;
		case 0:
			if(m_bIsSafeAttackMode) AddEventList(NOTIFY_MSG_HANDLER51, 10);//"
			m_bIsSafeAttackMode = FALSE;
			break;
		}
		break;

	case DEF_NOTIFY_IPACCOUNTINFO:
		ZeroMemory(cTemp, sizeof(cTemp));
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		strcpy(cTemp, cp);
		AddEventList(cTemp);
		break;

	case DEF_NOTIFY_REWARDGOLD:
		dwp = (DWORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
		m_iRewardGold = *dwp;
		break;

	case DEF_NOTIFY_SERVERSHUTDOWN:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		if (m_bIsDialogEnabled[25] == FALSE)
			 EnableDialogBox(25, *cp, NULL, NULL);
		else m_stDialogBoxInfo[25].cMode = *cp;
		PlaySound('E', 27, NULL);
		break;

	case DEF_NOTIFY_GLOBALATTACKMODE:
		NotifyMsg_GlobalAttackMode(pData);
		break;

	case DEF_NOTIFY_WHETHERCHANGE:
		NotifyMsg_WhetherChange(pData);
		break;

	case DEF_NOTIFY_FISHCANCELED:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		wp = (WORD *)cp;
		switch (*wp) {
		case NULL:
			AddEventList(NOTIFY_MSG_HANDLER52, 10);
			DisableDialogBox(24);
			break;

		case 1:
			AddEventList(NOTIFY_MSG_HANDLER53, 10);
			DisableDialogBox(24);
			break;

		case 2:
			AddEventList(NOTIFY_MSG_HANDLER54, 10);
			DisableDialogBox(24);
			break;
		}
		break;

	case DEF_NOTIFY_FISHSUCCESS:
		AddEventList(NOTIFY_MSG_HANDLER55, 10);
		PlaySound('E', 23, 5);
		PlaySound('E', 17, 5);
		switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			PlaySound('C', 21, 0);
			break;

		case 4:
		case 5:
		case 6:
			PlaySound('C', 22, 0);
			break;
		}
		break;

	case DEF_NOTIFY_FISHFAIL:
		AddEventList(NOTIFY_MSG_HANDLER56, 10);
		PlaySound('E', 24, 5);
		break;

	case DEF_NOTIFY_FISHCHANCE:
		NotifyMsg_FishChance(pData);
		break;

	case DEF_NOTIFY_EVENTFISHMODE:
		NotifyMsg_EventFishMode(pData);
		break;

	case DEF_NOTIFY_NOTICEMSG:
		NotifyMsg_NoticeMsg(pData);
		break;

	case DEF_NOTIFY_RATINGPLAYER:
		NotifyMsg_RatingPlayer(pData);
		break;

	case DEF_NOTIFY_CANNOTRATING:
		NotifyMsg_CannotRating(pData);
		break;

	case DEF_NOTIFY_ADMINUSERLEVELLOW:
		AddEventList(NOTIFY_MSG_HANDLER58, 10);
		break;

	case DEF_NOTIFY_NOGUILDMASTERLEVEL:
		AddEventList(NOTIFY_MSG_HANDLER59, 10);
		break;
	case DEF_NOTIFY_SUCCESSBANGUILDMAN:
		AddEventList(NOTIFY_MSG_HANDLER60, 10);
		break;
	case DEF_NOTIFY_CANNOTBANGUILDMAN:
		AddEventList(NOTIFY_MSG_HANDLER61, 10);
		break;

	case DEF_NOTIFY_PLAYERSHUTUP:
		NotifyMsg_PlayerShutUp(pData);
		break;

	case DEF_NOTIFY_TIMECHANGE:
		NotifyMsg_TimeChange(pData);
		break;

	case DEF_NOTIFY_TOBERECALLED:
		AddEventList(NOTIFY_MSG_HANDLER62, 10);
		break;

	case DEF_NOTIFY_HUNGER:
		NotifyMsg_Hunger(pData);
		break;

	case DEF_NOTIFY_PLAYERPROFILE:
		NotifyMsg_PlayerProfile(pData);
		break;

	case DEF_NOTIFY_WHISPERMODEON:
		NotifyMsg_WhisperMode(TRUE, pData);
		break;

	case DEF_NOTIFY_WHISPERMODEOFF:
		NotifyMsg_WhisperMode(FALSE, pData);
		break;

	case DEF_NOTIFY_PLAYERONGAME:
		NotifyMsg_PlayerStatus(TRUE, pData);
		break;

	case DEF_NOTIFY_PLAYERNOTONGAME:
		NotifyMsg_PlayerStatus(FALSE, pData);
		break;

	case DEF_NOTIFY_CHARISMA:
		NotifyMsg_Charisma(pData);
		break;

	case DEF_NOTIFY_ITEMSOLD:
		DisableDialogBox(23);
		break;

	case DEF_NOTIFY_ITEMREPAIRED:
		DisableDialogBox(23);
		NotifyMsg_ItemRepaired(pData);
		break;

	case DEF_NOTIFY_CANNOTREPAIRITEM:
		NotifyMsg_CannotRepairItem(pData);
		break;

	case DEF_NOTIFY_CANNOTSELLITEM:
		NotifyMsg_CannotSellItem(pData);
		break;

	case DEF_NOTIFY_REPAIRITEMPRICE:
		NotifyMsg_RepairItemPrice(pData);
		break;

	case DEF_NOTIFY_SELLITEMPRICE:
		NotifyMsg_SellItemPrice(pData);
		break;

	case DEF_NOTIFY_SHOWMAP:
		NotifyMsg_ShowMap(pData);
		break;

	case DEF_NOTIFY_SKILLUSINGEND:
		NotifyMsg_SkillUsingEnd(pData);
		break;

	case DEF_NOTIFY_TOTALUSERS:
		NotifyMsg_TotalUsers(pData);
		break;

	case DEF_NOTIFY_MAGICEFFECTOFF:
		NotifyMsg_MagicEffectOff(pData);
		break;

	case DEF_NOTIFY_MAGICEFFECTON:
		NotifyMsg_MagicEffectOn(pData);
		break;

	case DEF_NOTIFY_CANNOTITEMTOBANK:
		AddEventList(NOTIFY_MSG_HANDLER63, 10);
		break;

	case DEF_NOTIFY_SERVERCHANGE:
		NotifyMsg_ServerChange(pData);
		break;

	case DEF_NOTIFY_SKILL:
		NotifyMsg_Skill(pData);
		break;

	case DEF_NOTIFY_SETITEMCOUNT:
		NotifyMsg_SetItemCount(pData);
		break;

	case DEF_NOTIFY_ITEMDEPLETED_ERASEITEM:
		NotifyMsg_ItemDepleted_EraseItem(pData);
		break;

	case DEF_NOTIFY_DROPITEMFIN_ERASEITEM:
		NotifyMsg_DropItemFin_EraseItem(pData);
		break;

	case DEF_NOTIFY_GIVEITEMFIN_ERASEITEM:
		NotifyMsg_GiveItemFin_EraseItem(pData);
		break;

	case DEF_NOTIFY_ENEMYKILLREWARD:
		NotifyMsg_EnemyKillReward(pData);
		break;

	case DEF_NOTIFY_PKCAPTURED:
		NotifyMsg_PKcaptured(pData);
		break;

	case DEF_NOTIFY_PKPENALTY:
		NotifyMsg_PKpenalty(pData);
		break;

	case DEF_NOTIFY_ITEMTOBANK:
		NotifyMsg_ItemToBank(pData);
		break;

	case DEF_NOTIFY_TRAVELERLIMITEDLEVEL:
		AddEventList(NOTIFY_MSG_HANDLER64, 10);
		break;

	case DEF_NOTIFY_LIMITEDLEVEL:
		AddEventList(NOTIFYMSG_LIMITED_LEVEL1, 10);
		break;

	case DEF_NOTIFY_ITEMLIFESPANEND:
		NotifyMsg_ItemLifeSpanEnd(pData);
		break;

	case DEF_NOTIFY_ITEMRELEASED:
		NotifyMsg_ItemReleased(pData);
		break;

	case DEF_NOTIFY_ITEMOBTAINED:
		NotifyMsg_ItemObtained(pData);
		break;

	case DEF_NOTIFY_ITEMPURCHASED:
		NotifyMsg_ItemPurchased(pData);
		break;

	case DEF_NOTIFY_QUERY_JOINGUILDREQPERMISSION:
		NotifyMsg_QueryJoinGuildPermission(pData);
		break;

	case DEF_NOTIFY_QUERY_DISMISSGUILDREQPERMISSION:
		NotifyMsg_QueryDismissGuildPermission(pData);
		break;

	case DEF_COMMONTYPE_JOINGUILDAPPROVE:
		NotifyMsg_JoinGuildApprove(pData);
		break;

	case DEF_COMMONTYPE_JOINGUILDREJECT:
		NotifyMsg_JoinGuildReject(pData);
		break;

	case DEF_COMMONTYPE_DISMISSGUILDAPPROVE:
		NotifyMsg_DismissGuildApprove(pData);
		break;

	case DEF_COMMONTYPE_DISMISSGUILDREJECT:
		NotifyMsg_DismissGuildReject(pData);
		break;

	case DEF_NOTIFY_CANNOTCARRYMOREITEM:
		AddEventList(NOTIFY_MSG_HANDLER65, 10);//"
		AddEventList(NOTIFY_MSG_HANDLER66, 10);//"
		// Bank dialog Box
		m_stDialogBoxInfo[14].cMode = 0;
		break;

	case DEF_NOTIFY_NOTENOUGHGOLD:
		DisableDialogBox(23);
		AddEventList(NOTIFY_MSG_HANDLER67, 10);//"Gold
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		if (*cp >= 0) {
			m_bIsItemDisabled[*cp] = FALSE;
		}
		break;

	case DEF_NOTIFY_HP:
		NotifyMsg_HP(pData);
		break;
	case DEF_NOTIFY_MP:
		NotifyMsg_MP(pData);
		break;
	case DEF_NOTIFY_SP:
		NotifyMsg_SP(pData);
		break;
	case DEF_NOTIFY_KILLED:
		NotifyMsg_Killed(pData);
		break;
	case DEF_NOTIFY_EXP:
		NotifyMsg_Exp(pData);
		break;
	case DEF_NOTIFY_GUILDDISBANDED:
		NotifyMsg_GuildDisbanded(pData);
		break;
	case DEF_NOTIFY_CANNOTJOINMOREGUILDSMAN:
		NotifyMsg_CannotJoinMoreGuildsMan(pData);
		break;
	case DEF_NOTIFY_NEWGUILDSMAN:
		NotifyMsg_NewGuildsMan(pData);
		break;
	case DEF_NOTIFY_DISMISSGUILDSMAN:
		NotifyMsg_DismissGuildsMan(pData);
		break;
	case DEF_NOTIFY_MAGICSTUDYSUCCESS:
		NotifyMsg_MagicStudySuccess(pData);
		break;
	case DEF_NOTIFY_MAGICSTUDYFAIL:
		NotifyMsg_MagicStudyFail(pData);
		break;
	case DEF_NOTIFY_SKILLTRAINSUCCESS:
		NotifyMsg_SkillTrainSuccess(pData);
		break;
	case DEF_NOTIFY_SKILLTRAINFAIL:
		break;
	case DEF_NOTIFY_FORCEDISCONN:
		NotifyMsg_ForceDisconn(pData);
		break;
	case DEF_NOTIFY_FIGHTZONERESERVE:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		switch (*ip) {
		case -5:
			AddEventList(NOTIFY_MSG_HANDLER68, 10);
			break;
		case -4:
			AddEventList(NOTIFY_MSG_HANDLER69, 10);
			break;
		case -3:
			AddEventList(NOTIFY_MSG_HANDLER70, 10);
			break;
		case -2:
			m_iFightzoneNumber = 0;
			AddEventList(NOTIFY_MSG_HANDLER71, 10);
			break;
		case -1:
			m_iFightzoneNumber = m_iFightzoneNumber * -1 ;
			AddEventList(NOTIFY_MSG_HANDLER72, 10);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			wsprintf(cTxt, NOTIFY_MSG_HANDLER73, *ip);//"
			AddEventList(cTxt, 10);
			break;
		}
		break;
	}
}

void CGame::ReserveFightzoneResponseHandler(char * pData)
{
 	WORD * wpResult;
	char * cp ;
	int * ip ;
 	wpResult = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	switch (*wpResult) {
	case DEF_MSGTYPE_CONFIRM:
		AddEventList(RESERVE_FIGHTZONE_RESPONSE_HANDLER1, 10);
		m_stDialogBoxInfo[7].cMode = 14;
		m_iFightzoneNumber = m_iFightzoneNumberTemp ;
		break;

	case DEF_MSGTYPE_REJECT:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		ip   = (int *)cp;
		cp += 4;
		AddEventList(RESERVE_FIGHTZONE_RESPONSE_HANDLER2, 10);
		m_iFightzoneNumberTemp = 0 ;

		if (*ip == 0) {
		 	m_stDialogBoxInfo[7].cMode = 15;
		}else if (*ip == -1){
			m_stDialogBoxInfo[7].cMode = 16;
		} else if (*ip == -2) {
			m_stDialogBoxInfo[7].cMode = 17;
		}else if (*ip == -3) {
			m_stDialogBoxInfo[7].cMode = 21;
		}else if (*ip == -4) {
			m_stDialogBoxInfo[7].cMode = 22;
		}
		break;
	}
}

void CGame::UpdateScreen_OnLogResMsg()
{
 short msX, msY, msZ, sX, sY;
 char  cLB, cRB;
 DWORD dwTime = timeGetTime();
 static DWORD dwCTime;
 static class CMouseInterface * pMI;
 int   iMIbuttonNum;
 char  cMIresult;


	if (m_cGameModeCount == 0)
	{	pMI = new class CMouseInterface;
		pMI->AddRect(370, 240, 370 + DEF_BTNSZX, 240 + DEF_BTNSZY);
		m_bEnterPressed = FALSE;
		m_bEscPressed   = FALSE;
		m_cArrowPressed = 0;
		dwCTime = timeGetTime();
		if (m_bSoundFlag) m_pESound[38]->bStop();
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_bEscPressed == TRUE || m_bEnterPressed) {
		switch (m_cMsg[0]) {
		case '0':
			ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
			break;
		case '1':
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			break;
		case '2':
			ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
			break;
		case '3':
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			break;
		case '4':
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			break;
		case '5':
				ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			break;
		case '6':
			switch (m_cMsg[1]) {
			case 'B':
				ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
				break;
			case 'C': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
			case 'M': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
			}
			break;
		case '7':
		case '8':
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			break;
		}

		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);

	m_DDraw.ClearBackB4();

	switch (m_cMsg[0]) {
	case '0':
	case '5':
		_Draw_UpdateScreen_OnCreateNewAccount();
		break;

	case '1':
	case '7':
		sX = 146;
		sY = 114;

		_Draw_OnLogin(m_cAccountName, m_cAccountPassword, 0, 0);
		break;

	case '2':
	case '4':
		_bDraw_OnCreateNewCharacter(m_cPlayerName, 0, 0, 0);
		break;

	case '3':
		sX = 0;
		sY = 0;
		UpdateScreen_OnSelectCharacter(sX, sY, 0, 0);
		break;

	case '6':
		sX = 146;
		sY = 114;

		UpdateScreen_OnSelectCharacter(0, 0, 0, 0, TRUE);
		break;
	case '8':
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_MAINMENU, -1, -1, 0, TRUE);
		break;
	}

	m_DDraw.DrawShadowBox(0,0,639,479);

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);

	if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 0);

	switch (m_cMsg[1]) {
	case '1':
		PutString_SprFont(172 + 70, 165, "Password is not correct!", 7,0,0);
		PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG5);//"
		break;

	case '2':
		PutString_SprFont(172 + 70, 165, "Not existing account!", 7,0,0);
		PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG6);//"
		PutAlignedString(198, 453, 215, UPDATE_SCREEN_ON_LOG_MSG7);//"
		break;

	case '3':
		PutString_SprFont(172 + 10 +34, 165, "Can not connect to game server!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG8);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG9);//"
		PutAlignedString(198, 453, 225,  UPDATE_SCREEN_ON_LOG_MSG10);//"
		break;

	case '4':
		PutString_SprFont(172 + 58, 165, "New account created.", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG11);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG12);//"
		break;

	case '5':
		PutString_SprFont(172 + 58, 165, "Can not create new account!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG13);//"
		break;

	case '6':
		PutString_SprFont(172 + 36, 165, "Can not create new account!", 7,0,0);
		PutString_SprFont(172 + 24, 180, "Already existing account name.", 7,0,0);
		PutAlignedString(198, 453, 205,  UPDATE_SCREEN_ON_LOG_MSG14);//"
		PutAlignedString(198, 453, 220,  UPDATE_SCREEN_ON_LOG_MSG15);//"
		break;

	case '7':
		PutString_SprFont(172 + 58, 165, "New character created.", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG16);//"
		break;

	case '8':
		PutString_SprFont(172 + 58, 165, "Can not create new character!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG17);//"
		break;

	case '9':
		PutString_SprFont(172 + 36, 165, "Can not create new character!", 7,0,0);
		PutString_SprFont(172 + 24, 180, "Already existing character name.", 7,0,0);
		PutAlignedString(198, 453, 205,  UPDATE_SCREEN_ON_LOG_MSG18);//"
		PutAlignedString(198, 453, 220,  UPDATE_SCREEN_ON_LOG_MSG19);//"
		break;

	case 'A':
		PutString_SprFont(172 + 36 +45, 165, "Character deleted.", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG20);//"

		break;
	case 'B':
		PutString_SprFont(172 + 36 +45, 165, "Password changed.", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG21);//"
		break;
	case 'C':
		PutString_SprFont(172 + 36, 165, "Can not change password!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG22);//"
		break;

	case 'D':
		PutString_SprFont(172 + 10 +34, 165, "Can not connect to game server!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG23);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG24);//"
		break;

	case 'E':
		PutString_SprFont(172 + 10 +34, 165, "Can not connect to game server!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG25);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG26);//"
		PutAlignedString(198, 453, 225,  UPDATE_SCREEN_ON_LOG_MSG27);//"
		break;

	case 'F':
		PutString_SprFont(172 + 10 +34, 165, "Can not connect to game server!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG28);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG29);//"
		break;

	case 'G':
		PutString_SprFont(172 + 10 +34, 165, "Can not connect to game server!", 7,0,0);
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG30);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG31);//"
		break;

	case 'H':
		PutString_SprFont(172 + 68, 165, "Connection Rejected!", 7,0,0);
		if (m_iBlockYear == 0) {
			PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG32);//"
			PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG33);//"
		}
		else {
			PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG34);//"
			wsprintf(G_cTxt, UPDATE_SCREEN_ON_LOG_MSG35, m_iBlockYear, m_iBlockMonth, m_iBlockDay);//"
			PutAlignedString(198, 453, 210,  G_cTxt);
		}
		break;

	case 'I': //
		PutString_SprFont(172 + 68, 165, "Not Enough Point!", 7,0,0);
		PutAlignedString(198, 453, 210,  "ÂI¼Æ¨Ï¥Î´Á­­¤wµ²§ô, ½Ð¦ÜGD2S.gamania.com©µªø¨Ï¥Î´Á­­");

		break;

	case 'J': // v2.15 2002-5-21
		PutString_SprFont(172 + 68, 165, "World Server Full", 7,0,0);
		PutAlignedString(198, 453, 210,  "Please ! Try Other World Server");
		break;

	case 'M': 	// v2.18
		PutString_SprFont(172 + 68, 165, "Your password expired", 7,0,0);
		PutAlignedString(198, 453, 210,  "Please! Change password");
		break;


	case 'U': // v2.15
		PutString_SprFont(172 + 68, 165, "Keycode input Success!", 7,0,0);
		PutAlignedString(198, 453, 210,  "Keycode Registration successed.");

		break;

	case 'X':
		PutAlignedString(198, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG38);//"
		PutAlignedString(198, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG39);//"
		break;

	case 'Y':
		PutAlignedString(178, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG40);//"
		PutAlignedString(178, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG41);//"
		break;

	case 'Z':
		PutAlignedString(178, 453, 195,  UPDATE_SCREEN_ON_LOG_MSG42);//"
		PutAlignedString(178, 453, 210,  UPDATE_SCREEN_ON_LOG_MSG41);//"
		break;
	}

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK) {
		switch (iMIbuttonNum) {
		case 1:
			switch (m_cMsg[0]) {
			case '0':
				ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
				break;
			case '1':
				ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
				break;
			case '2':
				ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
				break;
			case '3':
				ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
				break;
			case '4':
				ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
				break;
			case '5':
				ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
				break;
			case '6':
				switch (m_cMsg[1]) {
					case 'B':
						ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
						break;
					case 'C': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
					case 'M': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
				}
				break;
			case '7':
			case '8':
				ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
				break;
			}
			delete pMI;
			return;
		}
	}

	if ((dwTime - dwCTime) > 100)
	{	m_cMenuFrame++;
		dwCTime = dwTime;
	}
	if (m_cMenuFrame >= 8)
	{	m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8)
		{	m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;
	DrawVersion();
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::RetrieveItemHandler(char *pData)
{char * cp, cBankItemIndex, cItemIndex, cTxt[120];
 WORD * wp;
 int j;
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	if (*wp != DEF_MSGTYPE_REJECT)
	{	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		cBankItemIndex = *cp;
		cp++;
		cItemIndex = *cp;
		cp++;

		if (m_pBankList[cBankItemIndex] != NULL) {
			// v1.42
			char cStr1[64], cStr2[64], cStr3[64];
			GetItemName(m_pBankList[cBankItemIndex], cStr1, cStr2, cStr3);

			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, RETIEVE_ITEM_HANDLER4, cStr1);//""You took out %s."
			AddEventList(cTxt, 10);

			if ( (m_pBankList[cBankItemIndex]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
				 (m_pBankList[cBankItemIndex]->m_cItemType == DEF_ITEMTYPE_ARROW) )
			{	if (m_pItemList[cItemIndex]	== NULL) goto RIH_STEP2;
				delete m_pBankList[cBankItemIndex];
				m_pBankList[cBankItemIndex] = NULL;
				for ( j = 0; j <= DEF_MAXBANKITEMS - 2; j++)
				{	if ((m_pBankList[j+1] != NULL) && (m_pBankList[j] == NULL))
					{	m_pBankList[j] = m_pBankList[j+1];
						m_pBankList[j+1] = NULL;
				}	}
			}else
			{
RIH_STEP2:;
				if (m_pItemList[cItemIndex] != NULL) return;
				short nX, nY;
				nX = 40;
				nY = 30;
				for (j = 0; j < DEF_MAXITEMS; j++)
				{	if ( ( m_pItemList[j] != NULL) && (memcmp(m_pItemList[j]->m_cName, cStr1, 20) == 0))
					{	nX = m_pItemList[j]->m_sX+1;
						nY = m_pItemList[j]->m_sY+1;
						break;
				}	}
				m_pItemList[cItemIndex] = m_pBankList[cBankItemIndex];
				m_pItemList[cItemIndex]->m_sX =	nX;
				m_pItemList[cItemIndex]->m_sY =	nY;
                bSendCommand(MSGID_REQUEST_SETITEMPOS, NULL, cItemIndex, nX, nY, NULL, NULL);

				for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_cItemOrder[j] == -1)
				{	m_cItemOrder[j] = cItemIndex;
					break;
				}
				m_bIsItemEquipped[cItemIndex] = FALSE;
				m_bIsItemDisabled[cItemIndex] = FALSE;
				m_pBankList[cBankItemIndex] = NULL;
				for ( j = 0; j <= DEF_MAXBANKITEMS - 2; j++)
				{	if ((m_pBankList[j+1] != NULL) && (m_pBankList[j] == NULL))
					{	m_pBankList[j] = m_pBankList[j+1];
						m_pBankList[j+1] = NULL;
	}	}	}	}	}
	m_stDialogBoxInfo[14].cMode = 0;
}

void CGame::EraseItem(char cItemID)
{int i;
 char cStr1[64], cStr2[64], cStr3[64];
	ZeroMemory(cStr1, sizeof(cStr1));
	ZeroMemory(cStr2, sizeof(cStr2));
	ZeroMemory(cStr3, sizeof(cStr3));
	for( i=0 ; i<6 ; i++ )
	{	if (m_sShortCut[i] == cItemID)
		{	GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);
			if( i < 3 ) wsprintf(G_cTxt, ERASE_ITEM, cStr1, cStr2, cStr3, i+1);
			else wsprintf(G_cTxt, ERASE_ITEM, cStr1, cStr2, cStr3, i+7);
			AddEventList(G_cTxt, 10);
			m_sShortCut[i] = -1;
	}	}

	if (cItemID == m_sRecentShortCut)
		m_sRecentShortCut = -1;
	// ItemOrder
	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_cItemOrder[i] == cItemID)
			m_cItemOrder[i] = -1;
	for (i = 1; i < DEF_MAXITEMS; i++)
	if ((m_cItemOrder[i-1] == -1) && (m_cItemOrder[i] != -1))
	{	m_cItemOrder[i-1] = m_cItemOrder[i];
		m_cItemOrder[i]   = -1;
	}
	// ItemList
	delete m_pItemList[cItemID];
	m_pItemList[cItemID] = NULL;
	m_bIsItemEquipped[cItemID] = FALSE;
	m_bIsItemDisabled[cItemID] = FALSE;
}

void CGame::DlbBoxDoubleClick_Character(short msX, short msY)
{
	char cEquipPoiStatus[DEF_MAXITEMEQUIPPOS], cItemID = -1;
	short sX, sY, sSprH, sFrame;
	int i;
	if (m_bIsDialogEnabled[17] == TRUE) return;
	sX = m_stDialogBoxInfo[1].sX;
	sY = m_stDialogBoxInfo[1].sY;

	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
		cEquipPoiStatus[i] = -1;

	for (i = 0; i < DEF_MAXITEMS; i++) {
		if ((m_pItemList[i] != NULL) && (m_bIsItemEquipped[i] == TRUE))	cEquipPoiStatus[ m_pItemList[i]->m_cEquipPos ] = i;
	}
	if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
	{
		if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison( sX + 41, sY + 137, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BACK];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_PANTS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_ARMS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BOOTS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BODY];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 90, sY + 170, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LHAND];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RHAND];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_NECK];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RFINGER];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LFINGER];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 72, sY + 135, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_HEAD];
		}
	}
	else if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6)) {
		if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 45, sY + 143, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BACK];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BOOTS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_PANTS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_ARMS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BOOTS];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BODY];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 84, sY + 175, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LHAND];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RHAND];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_NECK];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RFINGER];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LFINGER];
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1) {
			sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 72, sY + 139, sFrame, msX, msY ) )
				cItemID = cEquipPoiStatus[DEF_EQUIPPOS_HEAD];
		}
	}

	if( cItemID == -1 || m_pItemList[cItemID] == NULL ) return;
	if ( (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW) || (m_pItemList[cItemID]->m_dwCount > 1) ) return;
	if ( (m_bIsDialogEnabled[11]==TRUE) && (m_bIsDialogEnabled[23] == FALSE) && (m_stDialogBoxInfo[39].sV3 == 24))
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, NULL, cItemID, m_stDialogBoxInfo[39].sV3, NULL, m_pItemList[cItemID]->m_cName, m_stDialogBoxInfo[39].sV4); // v1.4
	else {
		if (m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] == TRUE)
		{	char cStr1[64], cStr2[64], cStr3[64];
			GetItemName(m_pItemList[m_stMCursor.sSelectedObjectID], cStr1, cStr2, cStr3);
			ZeroMemory(G_cTxt, sizeof(G_cTxt) );
			wsprintf(G_cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);//"
			AddEventList(G_cTxt, 10);
			if(memcmp(m_pItemList[m_stMCursor.sSelectedObjectID]->m_cName, "AngelicPendant", 14) == 0) PlaySound('E', 53, 0);
			else PlaySound('E', 29, 0);

			// Remove Angelic Stats
			if (   (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos >= 11)
				&& (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cItemType == 1))
			{	char cItemID = m_stMCursor.sSelectedObjectID;
				if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(STR)", 19) == 0)
				{	m_iAngelicStr = 0;
				}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(DEX)", 19) == 0)
				{	m_iAngelicDex = 0;
				}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(INT)", 19) == 0)
				{	m_iAngelicInt = 0;
				}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(MAG)", 19) == 0)
				{	m_iAngelicMag = 0;
			}	}
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_RELEASEITEM, NULL, m_stMCursor.sSelectedObjectID, NULL, NULL, NULL);
			m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] = FALSE;
			m_sItemEquipmentStatus[	m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos ] = -1;
			m_stMCursor.cSelectedObjectType	= NULL;
			m_stMCursor.sSelectedObjectID   = NULL;
	}	}
}

void CGame::DlbBoxDoubleClick_GuideMap(short msX, short msY)
{short si = m_stMCursor.sCursorFrame;
	if( si != 0 ) return;
	if( m_cMapIndex < 0 ) return;

	short sX, sY, shX, shY, szX, szY;
	sX = m_stDialogBoxInfo[9].sX;
	sY = m_stDialogBoxInfo[9].sY;
	szX = m_stDialogBoxInfo[9].sSizeX;
	szY = m_stDialogBoxInfo[9].sSizeY;
	if( sX < 20 ) sX = 0;
	if( sY < 20 ) sY = 0;
	if( sX > 640-128-20 ) sX = 640-128;
	if( sY > 427-128-20 ) sY = 427-128;
	if( m_bZoomMap )
	{	shX = m_sPlayerX-64;
		shY = m_sPlayerY-64;
		if( shX < 0 ) shX = 0;
		if( shY < 0 ) shY = 0;
		if( shX > m_pMapData->m_sMapSizeX-128 ) shX = m_pMapData->m_sMapSizeX-128;
		if( shY > m_pMapData->m_sMapSizeY-128 ) shY = m_pMapData->m_sMapSizeY-128;
		shX = shX + msX - sX;
		shY = shY + msY - sY;
	}else
	{	shX = (m_pMapData->m_sMapSizeX*(msX-sX))/128;
		shY = (m_pMapData->m_sMapSizeX*(msY-sY))/128;
	}
	if( shX < 30 || shY < 30 ) return;
	if( shX > m_pMapData->m_sMapSizeX-30 || shY > m_pMapData->m_sMapSizeY-30 ) return;
	if( (m_bRunningMode==TRUE) && (m_iSP>0) )
		m_cCommand = DEF_OBJECTRUN;
	else m_cCommand = DEF_OBJECTMOVE;
	m_sCommX = shX;
	m_sCommY = shY;
	GetPlayerTurn();
}

void CGame::DlbBoxDoubleClick_Inventory(short msX, short msY)
{
 register int i;
 char  cItemID, cTxt[120];
 short sX, sY, x1, x2, y1, y2;
 char cStr1[64], cStr2[64], cStr3[64];
	//if (m_iHP <= 0) return;
	if (m_bItemUsingStatus == TRUE)
	{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY1, 10);
		return;
	}
	sX = m_stDialogBoxInfo[2].sX;
	sY = m_stDialogBoxInfo[2].sY;
	for (i = 0; i < DEF_MAXITEMS; i++)
	{	if (m_cItemOrder[DEF_MAXITEMS - 1 - i] == -1) continue;
		cItemID = m_cItemOrder[DEF_MAXITEMS - 1 - i];
		if (m_pItemList[cItemID] == NULL) continue;

		m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + 32 + m_pItemList[cItemID]->m_sX, sY + 44 + m_pItemList[cItemID]->m_sY, m_pItemList[cItemID]->m_sSpriteFrame);
		// Order
		x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
		y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
		x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
		y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;

		if ((m_bIsItemDisabled[cItemID] == FALSE) && (m_bIsItemEquipped[cItemID] == FALSE) && (msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
		{	// Order
			_SetItemOrder(0, cItemID);
			GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);

			if ( m_bIsDialogEnabled[11] && (m_bIsDialogEnabled[23] == FALSE) && (m_bIsDialogEnabled[23] == FALSE) && (m_stDialogBoxInfo[39].sV3 == 24) )
			{	if (m_pItemList[cItemID]->m_cEquipPos != DEF_EQUIPPOS_NONE)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, NULL, cItemID, m_stDialogBoxInfo[39].sV3, NULL, m_pItemList[cItemID]->m_cName, m_stDialogBoxInfo[39].sV4); // v1.4
					return;
			}	}

			if (   (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE)
				|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_PERM)
				|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW)
				|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT) )
			{	if (bCheckItemOperationEnabled(cItemID) == FALSE) return;
				if ((timeGetTime() - m_dwDamagedTime) < 10000)
				{	if ((m_pItemList[cItemID]->m_sSprite == 6) && (m_pItemList[cItemID]->m_sSpriteFrame == 9))
					{	wsprintf(G_cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY3, cStr1);//"Item %s: Scrolls cannot be used until 10 seconds after taking damage."
						AddEventList(G_cTxt, 10);
						return;
					}
					if ((m_pItemList[cItemID]->m_sSprite == 6) && (m_pItemList[cItemID]->m_sSpriteFrame == 89))
					{	wsprintf(G_cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY3, cStr1);//"Item %s: Scrolls cannot be used until 10 seconds after taking damage."
						AddEventList(G_cTxt, 10);
						return;
				}	}
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, NULL, cItemID, NULL, NULL, NULL);

				if (   (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE)
					|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT) )
				{	m_bIsItemDisabled[cItemID] = TRUE;
					m_bItemUsingStatus = TRUE;
			}	}

			if ( m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_SKILL )
			{	if (_bIsItemOnHand() == TRUE)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//"Your hands should be free to use this item."
					return;
				}
				if (m_bSkillUsingStatus == TRUE)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);//"You are already using another skill."
					return;
				}
				if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY6, 10);//"You can't use this item because it is exhausted."
				}else
				{	m_bIsGetPointingMode = TRUE;
					m_iPointCommandType  = cItemID;
					wsprintf(cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY7, cStr1);//"Item %s: Select a position which you want to use."
					AddEventList(cTxt, 10);
			}	}

			if ( m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE_DEST )
			{	if (_bIsItemOnHand() == TRUE)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//"Your hands should be free to use this item."
					return;
				}
				if (m_bSkillUsingStatus == TRUE)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY13, 10);//"You are already using another skill."
					return;
				}
				if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY6, 10);//"You can't use this item because it is exhausted."
				}else
				{	m_bIsGetPointingMode = TRUE;
					m_iPointCommandType  = cItemID;
					wsprintf(cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY8, cStr1);//"Item %s: Select an item which you want to use."
					AddEventList(cTxt, 10);
			}	}

			if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX)
			{	if (_bIsItemOnHand() == TRUE)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//"Your hands should be free to use this item."
					return;
				}

				if (m_bSkillUsingStatus == TRUE) {
					AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);//"You are already using another skill."
					return;
				}

				if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
				{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY6, 10);//"You can't use this item because it is exhausted."
				}else
				{	switch (m_pItemList[cItemID]->m_sSpriteFrame) {
					case 55: // Alchemy pot
						if (m_cSkillMastery[12] == 0)
						{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY9, 10);//"You should learn alchemy skill to use this item."
						}else
						{	EnableDialogBox(26, 1, NULL, NULL, NULL);
							AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY10, 10);//"Using alchemy skill..."
						}
						break;
					case 113: // Smith's Anvil
						if (m_cSkillMastery[13] == 0)
						{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY11, 10);//"You should learn manufacturing skill to use this item.."
						}else
						{	EnableDialogBox(26, 3, NULL, NULL, NULL);
							AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY12, 10);//"Using a manufacturing skill..."
						}
						break;

					// Crafting
					case 0:
						//if (m_pItemList[i]->m_sSprite == 22)
						{	EnableDialogBox(26, 7, NULL, NULL, NULL);
							AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY17, 10);	//  "Initiating item Crafting..."
						}
						break;

					case 151:
					case 152:
					case 153:
					case 154:
							EnableDialogBox(40, 1, NULL, NULL, NULL);
						break;
			}	}	}
			// Dblclick Alchemy bowl
			if (( m_bIsDialogEnabled[26] == TRUE) && (m_stDialogBoxInfo[26].cMode == 1))
			{	bItemDrop_SkillDialog();
				//bItemDrop_ExternalScreen(cItemID, m_stDialogBoxInfo[26].sX+50, m_stDialogBoxInfo[26].sY+50);
			}
			// Dblclick Manuf box
			if (( m_bIsDialogEnabled[26] == TRUE) && (m_stDialogBoxInfo[26].cMode == 4))
			{	bItemDrop_SkillDialog();
				//bItemDrop_ExternalScreen(cItemID, m_stDialogBoxInfo[26].sX+50, m_stDialogBoxInfo[26].sY+50);
			}
			// Crafting
			// Dblclick Crafting box
			if (( m_bIsDialogEnabled[26] == TRUE) && (m_stDialogBoxInfo[26].cMode == 7))
			{	bItemDrop_SkillDialog();
				//bItemDrop_ExternalScreen(cItemID, m_stDialogBoxInfo[26].sX+50, m_stDialogBoxInfo[26].sY+50);
			}
			if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EQUIP)
			{	m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID = (short)cItemID;
				bItemDrop_Character();
				m_stMCursor.cSelectedObjectType = NULL;
				m_stMCursor.sSelectedObjectID   = NULL;
			}
			return;
	}	}
}


void CGame::UpdateScreen_OnChangePassword()
{
 short msX, msY, msZ;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;
 static class CMouseInterface * pMI;
 static char  cName[12], cPassword[12], cNewPassword[12], cNewPassConfirm[12], cPrevFocus;
 static DWORD dwCTime;
 DWORD dwTime = timeGetTime();
 BOOL bFlag = TRUE;

	if (m_cGameModeCount == 0) {
		EndInputString();

		pMI = new class CMouseInterface;
		pMI->AddRect(300, 148, 425, 170);
		pMI->AddRect(300, 172, 425, 194);
		pMI->AddRect(300, 196, 425, 218);
		pMI->AddRect(300, 220, 425, 242);

		pMI->AddRect(197, 320, 197 + DEF_BTNSZX, 320 + DEF_BTNSZY);
		pMI->AddRect(370, 320, 370 + DEF_BTNSZX, 320 + DEF_BTNSZY);

		cPrevFocus  = 2; //1
		m_cCurFocus = 2; //1
		m_cMaxFocus = 6;
		m_bEnterPressed = FALSE;
		m_cArrowPressed = 0;

		ZeroMemory(cName, sizeof(cName));
		ZeroMemory(cPassword, sizeof(cPassword));
		ZeroMemory(cNewPassword, sizeof(cNewPassword));
		ZeroMemory(cNewPassConfirm, sizeof(cNewPassConfirm));

		strcpy( cName, m_cAccountName );
		//StartInputString(314, 155, 11, cName);
		StartInputString(314, 179, 11, cPassword);
		ClearInputString();
		dwCTime = dwTime;
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if ((dwTime - dwCTime) > 100) {
		m_cMenuFrame++;
		dwCTime = dwTime;
	}
	if (m_cMenuFrame >= 8)
	{	m_cMenuDirCnt++;
		if (m_cMenuDirCnt > 8)
		{	m_cMenuDir++;
			m_cMenuDirCnt = 1;
		}
		m_cMenuFrame = 0;
	}
	if (m_cMenuDir > 8) m_cMenuDir = 1;

	if (m_cArrowPressed != 0)
	{	switch (m_cArrowPressed) {
		case 1:
			m_cCurFocus--;
			if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
			break;

		case 2:
			if (m_cCurFocus == 3) m_cCurFocus = 4;
			else if (m_cCurFocus == 4) m_cCurFocus = 3;
			break;

		case 3:
			m_cCurFocus++;
			if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;

		case 4:
			if (m_cCurFocus == 3) m_cCurFocus = 4;
			else if (m_cCurFocus == 4) m_cCurFocus = 3;
			break;
		}
		m_cArrowPressed = 0;
	}

	if (m_bEnterPressed == TRUE)
	{	PlaySound('E', 14, 5);
		switch (m_cCurFocus) {
		case 1:
		case 2:
		case 3:
		case 4:
			m_cCurFocus++;
			if( m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;

		case 5:	// Connect
			if ( (m_Misc.bCheckValidString(cPassword) == FALSE) || (strlen(cPassword) == 0) ||
				 (m_Misc.bCheckValidName(cNewPassword) == FALSE) || (m_Misc.bCheckValidName(cNewPassConfirm) == FALSE) ||
				 (strlen(cNewPassword) == 0) || (memcmp(cNewPassword, cNewPassConfirm, 10) != 0) ) break;

			ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
			ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
			ZeroMemory(m_cNewPassword, sizeof(m_cNewPassword));
			ZeroMemory(m_cNewPassConfirm, sizeof(m_cNewPassConfirm));
			strcpy(m_cAccountName, cName);
			strcpy(m_cAccountPassword, cPassword);
			strcpy(m_cNewPassword, cNewPassword);
			strcpy(m_cNewPassConfirm, cNewPassConfirm);
			m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_CHANGEPASSWORD;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg, "41");
			delete pMI;
			return;

		case 6:	// Cancel
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			//m_dwLoginMode = MSGID_REQUEST_LOGIN;
			delete pMI;
			return;
		}
		m_bEnterPressed = FALSE;
	}

	if (m_bEscPressed == TRUE)
	{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		delete pMI;
		m_bEscPressed = FALSE;
		return;
	}

	if (cPrevFocus != m_cCurFocus)
	{	EndInputString();
		switch (m_cCurFocus) {
		case 1:
			StartInputString(314, 155, 11, cName);
			break;
		case 2:
			StartInputString(314, 179, 11, cPassword);
			break;
		case 3:
			StartInputString(314, 203, 11, cNewPassword);
			break;
		case 4:
			StartInputString(314, 227, 11, cNewPassConfirm);
			break;
		}
		cPrevFocus = m_cCurFocus;
	}

	m_DDraw.ClearBackB4();

	UpdateScreen_OnSelectCharacter(0, 0, 0, 0, TRUE);
	m_DDraw.DrawShadowBox(0,0,639,479);//SelectCharacter

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 153, 112, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT , 153, 112, 13);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 153 + 157, 112 + 109, 7);//

	PutString(206, 155, UPDATE_SCREEN_ON_CHANGE_PASSWORD1, RGB(25,35,25));
	PutString(206, 179, UPDATE_SCREEN_ON_CHANGE_PASSWORD2, RGB(25,35,25));
	PutString(206, 203, UPDATE_SCREEN_ON_CHANGE_PASSWORD3, RGB(25,35,25));
	PutString(206, 227, UPDATE_SCREEN_ON_CHANGE_PASSWORD4, RGB(25,35,25));

	if (m_cCurFocus != 1) {
		if (m_Misc.bCheckValidString(cName) != FALSE)
			 PutString(314, 155, cName, RGB(25,35,25));
		else PutString(314, 155, cName, RGB(55,18,13));
	}
	if ((m_Misc.bCheckValidString(cName) == FALSE) || (strlen(cName) == 0)) bFlag = FALSE;

	if (m_cCurFocus != 2) {
		if ((m_Misc.bCheckValidString(cPassword) != FALSE))
			 PutString(314, 179, cPassword, RGB(25,35,25), TRUE, 3);
		else PutString(314, 179, cPassword, RGB(55,18,13), TRUE, 3);
	}

	if (m_cCurFocus != 3) {
		if ((m_Misc.bCheckValidName(cNewPassword) != FALSE))
			 PutString(314, 203, cNewPassword, RGB(25,35,25), TRUE, 3);
		else PutString(314, 203, cNewPassword, RGB(55,18,13), TRUE, 3);
	}

	if (m_cCurFocus != 4) {
		if ((m_Misc.bCheckValidName(cNewPassConfirm) != FALSE))
			 PutString(314, 227, cNewPassConfirm, RGB(25,35,25), TRUE, 3);
		else PutString(314, 227, cNewPassConfirm, RGB(55,18,13), TRUE, 3);
	}

	if ( (m_Misc.bCheckValidString(cPassword) == FALSE) || (strlen(cPassword) == 0) ||
		 (strlen(cNewPassword) < 8) || (memcmp(cNewPassword, cNewPassConfirm, 10) != 0) ||
		 ( memcmp(cPassword, cNewPassword, 10) == 0 ) ) bFlag = FALSE;


	if (m_cCurFocus == 1) ShowReceivedString();
	else if ((m_cCurFocus == 2) || (m_cCurFocus == 3) || (m_cCurFocus == 4)) ShowReceivedString(TRUE);

	PutAlignedString(153, 487, 258, UPDATE_SCREEN_ON_CHANGE_PASSWORD5);//"
	PutAlignedString(153, 487, 273, UPDATE_SCREEN_ON_CHANGE_PASSWORD6);//"
	PutAlignedString(153, 487, 288, UPDATE_SCREEN_ON_CHANGE_PASSWORD7);//"

	if ( (bFlag == TRUE) && (m_cCurFocus == 5) )
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(197, 320, 21, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(197, 320, 20, dwTime);

	if (m_cCurFocus == 6)
		 m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(370, 320, 17, dwTime);
	else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(370, 320, 16, dwTime);

	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK)
	{	PlaySound('E', 14, 5);

		switch (iMIbuttonNum) {
		case 1:
		case 2:
		case 3:
		case 4:
			m_cCurFocus = iMIbuttonNum;
			break;

		case 5:
			if ( (m_Misc.bCheckValidString(cPassword) == FALSE) || (strlen(cPassword) == 0) ||
				 (m_Misc.bCheckValidName(cNewPassword) == FALSE) || (m_Misc.bCheckValidName(cNewPassConfirm) == FALSE) ||
				 (strlen(cNewPassword) == 0) || (memcmp(cNewPassword, cNewPassConfirm, 10) != 0) ) break;

			EndInputString();
			ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
			ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
			ZeroMemory(m_cNewPassword, sizeof(m_cNewPassword));
			ZeroMemory(m_cNewPassConfirm, sizeof(m_cNewPassConfirm));
			strcpy(m_cAccountName, cName);
			strcpy(m_cAccountPassword, cPassword);
			strcpy(m_cNewPassword, cNewPassword);
			strcpy(m_cNewPassConfirm, cNewPassConfirm);
						m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_USER_LOGSOCKETEVENT);
			m_pLSock->bInitBufferSize(30000);
			ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
			m_dwConnectMode = MSGID_REQUEST_CHANGEPASSWORD;
			ZeroMemory(m_cMsg, sizeof(m_cMsg));
			strcpy(m_cMsg, "41");
			delete pMI;
			return;

		case 6:
			// Cancel
			ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
			delete pMI;
			return;
		}
	}

	if ((msX >= 197) && (msX <= 197 + DEF_BTNSZX) && (msY >= 320) && (msY <= 320 + DEF_BTNSZY)) m_cCurFocus = 5;
	if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 320) && (msY <= 320 + DEF_BTNSZY)) m_cCurFocus = 6;

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::DlgBoxClick_SysMenu(short msX, short msY)
{ short sX, sY;
	sX = m_stDialogBoxInfo[19].sX;
	sY = m_stDialogBoxInfo[19].sY;
	if ((msX >= sX + 120) && (msX <= sX + 150) && (msY >= sY + 63) && (msY <= sY + 74))
	{	m_cDetailLevel = 0; // v1.41
		AddEventList( NOTIFY_MSG_DETAIL_LEVEL_LOW, 10 );
		PlaySound('E', 14, 5);
   	}

	if ((msX >= sX + 151) && (msX <= sX + 200) && (msY >= sY + 63) && (msY <= sY + 74))
	{	m_cDetailLevel = 1;
		AddEventList( NOTIFY_MSG_DETAIL_LEVEL_MEDIUM, 10 );
		PlaySound('E', 14, 5);
	}

	if ((msX >= sX + 201) && (msX <= sX + 234) && (msY >= sY + 63) && (msY <= sY + 74))
	{	m_cDetailLevel = 2;
		AddEventList( NOTIFY_MSG_DETAIL_LEVEL_HIGH, 10 );
		PlaySound('E', 14, 5);
	}

	if ((msX >= sX + 24) && (msX <= sX + 115) && (msY >= sY + 81) && (msY <= sY + 100))
	{	if( m_bSoundFlag )
		{	if (m_bSoundStat == TRUE)
			{	m_pESound[38]->bStop();
				m_bSoundStat = FALSE;
				AddEventList( NOTIFY_MSG_SOUND_OFF, 10 );
			}else
			{	m_bSoundStat = TRUE;
				AddEventList( NOTIFY_MSG_SOUND_ON, 10 );
	}	}	}

	if ((msX >= sX + 116) && (msX <= sX + 202) && (msY >= sY + 81) && (msY <= sY + 100))
	{	if( m_bSoundFlag )
		{	if (m_bMusicStat == TRUE) 	// Music Off
			{	m_bMusicStat = FALSE;
				AddEventList( NOTIFY_MSG_MUSIC_OFF, 10 );
				if (m_bSoundFlag)
				{
					if (m_pBGM != NULL)
					{	m_pBGM->bStop();
						delete m_pBGM;
						m_pBGM = NULL;
				}	}
			}else // Music On
			{	if (m_bSoundFlag)
				{	m_bMusicStat = TRUE;
					AddEventList( NOTIFY_MSG_MUSIC_ON, 10 );
					StartBGM();
	}	}	}	}


	if ((msX >= sX + 23) && (msX <= sX + 108) && (msY >= sY + 108) && (msY <= sY + 119))
	{	if (m_bWhisper == TRUE)
		{	m_bWhisper = FALSE;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND7, 10 );
		}else
		{	m_bWhisper = TRUE;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND6, 10 );
	}	}

	if ((msX >= sX + 123) && (msX <= sX + 203) && (msY >= sY + 108) && (msY <= sY + 119))
	{	if (m_bShout == TRUE)
		{	m_bShout = FALSE;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND9, 10 );
		}else
		{	m_bShout = TRUE;
			AddEventList(BCHECK_LOCAL_CHAT_COMMAND8, 10 );
	}	}

	//Transparency Change
	if ((msX >= sX + 28) && (msX <= sX + 235) && (msY >= sY + 156) && (msY <= sY + 171)) m_bDialogTrans = !m_bDialogTrans;

	//Guide Map Toggle
	if ((msX >= sX + 28) && (msX <= sX + 127) && (msY >= sY + 178) && (msY <= sY + 193))
	{	if( m_bIsDialogEnabled[9] ) DisableDialogBox(9);
		else EnableDialogBox(9, 0, 0, 0, NULL);
	}

	if (m_bForceDisconn) return;
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY)) {
		if( m_cLogOutCount == -1 )

#ifdef _DEBUG
			m_cLogOutCount = 1;
#else
			m_cLogOutCount = 11;
#endif
		else {
			m_cLogOutCount = -1;
			AddEventList(DLGBOX_CLICK_SYSMENU2, 10);
			DisableDialogBox(19);
		}
		PlaySound('E', 14, 5);
	}

	if ((m_iHP <= 0) && (m_cRestartCount == -1))
	{	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
		{	m_cRestartCount = 5;
			m_dwRestartCountTime = timeGetTime();
			DisableDialogBox(19);
			wsprintf(G_cTxt, DLGBOX_CLICK_SYSMENU1, m_cRestartCount); // "Restarting game....%d"
			AddEventList(G_cTxt, 10);
			PlaySound('E', 14, 5);
	}	}
}

void CGame::DrawNpcName(short sX, short sY, short sOwnerType, int iStatus)
{	char cTxt[32], cTxt2[64];
	ZeroMemory(cTxt, sizeof(cTxt));
	ZeroMemory(cTxt2, sizeof(cTxt2));
	GetNpcName(sOwnerType, cTxt);
	if ((iStatus & 0x20) != 0) strcat(cTxt, DRAW_OBJECT_NAME50);//" Berserk"
	if ((iStatus & 0x40) != 0) strcat(cTxt, DRAW_OBJECT_NAME51);//" Frozen"
	PutString2(sX, sY, cTxt, 255,255,255);
	if (m_bIsObserverMode == TRUE) PutString2(sX, sY+14, cTxt, 50,50,255);
	else if (m_bIsConfusion || (m_iIlusionOwnerH != NULL))
	{	ZeroMemory(cTxt, sizeof(cTxt));
		strcpy(cTxt, DRAW_OBJECT_NAME87);//"(Unknown)"
		PutString2(sX, sY+14, cTxt, 150,150,150); // v2.171
	}else
	{	switch( _iGetFOE(iStatus) ){
		case -2:
			PutString2(sX, sY+14, DRAW_OBJECT_NAME90, 255, 0, 0); // "(Enemy)"
			break;
		case -1:
			PutString2(sX, sY+14, DRAW_OBJECT_NAME90, 255, 0, 0); // "(Enemy)"
			break;
		case 0:
			PutString2(sX, sY+14, DRAW_OBJECT_NAME88, 50,50,255); // "Neutral"
			break;
		case 1:
			PutString2(sX, sY+14, DRAW_OBJECT_NAME89, 30,255,30); // "(Friendly)"
			break;
	}	}
#ifdef _DEBUG
	wsprintf(cTxt2,"Status: 0x%.8X ",iStatus);
	PutString2(sX, sY+42, cTxt2, 30,255,30);
	ZeroMemory(cTxt2, sizeof(cTxt2));
#endif

	switch ((iStatus & 0x0F00) >> 8) {
	case 0: break;
	case 1: strcpy(cTxt2, DRAW_OBJECT_NAME52); break;//"Clairvoyant"
	case 2: strcpy(cTxt2, DRAW_OBJECT_NAME53); break;//"Destruction of Magic Protection"
	case 3: strcpy(cTxt2, DRAW_OBJECT_NAME54); break;//"Anti-Physical Damage"
	case 4: strcpy(cTxt2, DRAW_OBJECT_NAME55); break;//"Anti-Magic Damage"
	case 5: strcpy(cTxt2, DRAW_OBJECT_NAME56); break;//"Poisonous"
	case 6: strcpy(cTxt2, DRAW_OBJECT_NAME57); break;//"Critical Poisonous"
	case 7: strcpy(cTxt2, DRAW_OBJECT_NAME58); break;//"Explosive"
	case 8: strcpy(cTxt2, DRAW_OBJECT_NAME59); break;//"Critical Explosive"
	}
	if( m_Misc.bCheckIMEString(cTxt2) ) PutString_SprFont3(sX, sY + 28, cTxt2, m_wR[13]*4, m_wG[13]*4, m_wB[13]*4, FALSE, 2);
	else PutString2(sX, sY + 28, cTxt2, 240,240,70);

}

void CGame::DrawObjectName(short sX, short sY, char * pName, int iStatus)
{	char cTxt[64], cTxt2[64];
	short sR, sG, sB;
	int i, iGuildIndex, iFOE, iAddY=0;
	BOOL bPK, bCitizen, bAresden, bHunter;
	iFOE = _iGetFOE(iStatus);
	if( iFOE < 0 )
	{	sR = 255; sG = 0; sB = 0;
	}else if( iFOE == 0 )
	{	sR = 50; sG = 50; sB = 255;
	}else
	{	sR = 30; sG = 200; sB = 30;
	}
	ZeroMemory(cTxt, sizeof(cTxt));
	ZeroMemory(cTxt2, sizeof(cTxt2));

	if (m_iIlusionOwnerH == NULL)
	{	if (m_bIsCrusadeMode == FALSE) wsprintf(cTxt, "%s", pName);
		else
		{	if (_tmp_wObjectID >= 10000) strcpy(cTxt, NPC_NAME_MERCENARY); //"Mercenary"
			else
			{	if( iFOE == -1 ) wsprintf(cTxt, "%d", _tmp_wObjectID);
				else strcpy(cTxt, pName);
		}	}
		if (m_iPartyStatus != NULL)
		{	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
			{	if (strcmp(m_stPartyMemberNameList[i].cName, pName) == 0)
				{	strcat(cTxt, BGET_NPC_NAME23); // ", Party Member"
					break;
		}	}	}
	}else strcpy(cTxt, "?????");

	if ((iStatus & 0x20) != 0) strcat(cTxt, DRAW_OBJECT_NAME50);//" Berserk"
	if ((iStatus & 0x40) != 0) strcat(cTxt, DRAW_OBJECT_NAME51);//" Frozen"

	PutString2(sX, sY, cTxt, 255,255,255);
	ZeroMemory(cTxt, sizeof(cTxt));

	if( memcmp(m_cPlayerName, pName, 10) == 0 )
	{	if( m_iGuildRank == 0 )
		{	wsprintf( G_cTxt, DEF_MSG_GUILDMASTER, m_cGuildName );//" Guildmaster)"
			PutString2(sX, sY+14, G_cTxt, 180,180,180);
			iAddY = 14;
		}
		if( m_iGuildRank > 0 )
		{	wsprintf( G_cTxt, DEF_MSG_GUILDSMAN, m_cGuildName );//" Guildsman)"
			PutString2(sX, sY+14, G_cTxt, 180,180,180);
			iAddY = 14;
		}
		if( m_iPKCount != 0 )
		{	bPK = TRUE;
			sR = 255; sG = 0; sB = 0;
		}else
		{	bPK = FALSE;
			sR = 30; sG = 200; sB = 30;
		}
		bCitizen = m_bCitizen;
		bAresden = m_bAresden;
		bHunter = m_bHunter;
	}else
	{	// CLEROTH - CRASH BUG ( STATUS )
		if( iStatus & 0x80000000 ) bPK = TRUE;
		else bPK = FALSE;
		if( iStatus & 0x40000000 ) bCitizen = TRUE;
		else bCitizen = FALSE;
		if( iStatus & 0x20000000 ) bAresden = TRUE;
		else bAresden = FALSE;
		if( iStatus & 0x10000000 ) bHunter = TRUE;
		else bHunter = FALSE;
		if( m_bIsCrusadeMode==FALSE || iFOE>=0 )
		{	if( FindGuildName(pName, &iGuildIndex) == TRUE )
			{	if (m_stGuildName[iGuildIndex].cGuildName[0] != NULL)
				{	if( strcmp(m_stGuildName[iGuildIndex].cGuildName, "NONE" )!=0 )
					{	if( m_stGuildName[iGuildIndex].iGuildRank == 0 )
						{	wsprintf( G_cTxt, DEF_MSG_GUILDMASTER, m_stGuildName[iGuildIndex].cGuildName );//
							PutString2(sX, sY+14, G_cTxt, 180,180,180);
							m_stGuildName[iGuildIndex].dwRefTime = m_dwCurTime;
							iAddY = 14;
						}else if( m_stGuildName[iGuildIndex].iGuildRank > 0 )
						{	wsprintf( G_cTxt, DEF_MSG_GUILDSMAN, m_stGuildName[iGuildIndex].cGuildName );//"
							PutString2(sX, sY+14, G_cTxt, 180,180,180);
							m_stGuildName[iGuildIndex].dwRefTime = m_dwCurTime;
							iAddY = 14;
						}
					}else
					{	m_stGuildName[iGuildIndex].dwRefTime = 0;
				}	}
			}else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQGUILDNAME, NULL, _tmp_wObjectID, iGuildIndex, NULL, NULL);
	}	}

	if( bCitizen == FALSE )	strcpy(cTxt, DRAW_OBJECT_NAME60);// "Traveller"
	else
	{	if( bAresden )
		{	if( bHunter == TRUE ) strcpy(cTxt, DEF_MSG_ARECIVIL); // "Aresden Civilian"
			else strcpy(cTxt, DEF_MSG_ARESOLDIER); // "Aresden Combatant"
		}else
		{	if( bHunter == TRUE ) strcpy(cTxt, DEF_MSG_ELVCIVIL);// "Elvine Civilian"
			else strcpy(cTxt, DEF_MSG_ELVSOLDIER);	// "Elvine Combatant"
	}	}
	if( bPK == TRUE )
	{	if( bCitizen == FALSE ) strcpy( cTxt, DEF_MSG_PK );	//"Criminal"
		else
		{	if( bAresden ) strcpy( cTxt, DEF_MSG_AREPK );// "Aresden Criminal"
			else strcpy( cTxt, DEF_MSG_ELVPK );  // "Elvine Criminal"
	}	}
	PutString2(sX, sY+14 +iAddY, cTxt, sR, sG, sB);

#ifdef _DEBUG
	wsprintf(cTxt2,"Status: 0x%.8X ",iStatus);
	PutString2(sX, sY+42, cTxt2, 30,255,30);
	ZeroMemory(cTxt2, sizeof(cTxt2));
#endif
}

BOOL CGame::FindGuildName(char* pName, int* ipIndex)
{
	int i, iRet = 0;
	DWORD dwTmpTime;
	for( i=0 ; i < DEF_MAXGUILDNAMES ; i++ )
	{
		if( memcmp(m_stGuildName[i].cCharName, pName, 10) == 0 )
		{
			m_stGuildName[i].dwRefTime = m_dwCurTime;
			*ipIndex = i;
			return TRUE;
		}
	}
	dwTmpTime = m_stGuildName[0].dwRefTime;
	for( i=0 ; i < DEF_MAXGUILDNAMES ; i++ )
	{
		if( m_stGuildName[i].dwRefTime < dwTmpTime )
		{
			iRet = i;
			dwTmpTime = m_stGuildName[i].dwRefTime;
		}
	}
	ZeroMemory( m_stGuildName[iRet].cGuildName, sizeof(m_stGuildName[iRet].cGuildName) );
	memcpy( m_stGuildName[iRet].cCharName, pName, 10 );
	m_stGuildName[iRet].dwRefTime = m_dwCurTime;
	m_stGuildName[iRet].iGuildRank = -1;
	*ipIndex = iRet;
	return FALSE;
}

void CGame::UpdateScreen_OnVersionNotMatch()
{short msX, msY, msZ;
 char cLB, cRB;
 char cMIresult;
 int  iMIbuttonNum;
 static class CMouseInterface * pMI;
 DWORD dwTime = timeGetTime();
	if (m_cGameModeCount == 0)
	{	if (G_pCalcSocket != NULL)
		{	delete G_pCalcSocket;
			G_pCalcSocket = NULL;
		}
		if (m_pGSock != NULL)
		{	delete m_pGSock;
			m_pGSock = NULL;
		}
		pMI = new class CMouseInterface;
		pMI->AddRect(0,0,640,480);
		m_bEnterPressed = FALSE;
	}
	m_cGameModeCount++;
	if (m_cGameModeCount > 120) m_cGameModeCount = 120;
	m_DDraw.ClearBackB4();
	if (m_bEscPressed == TRUE || m_bEnterPressed == TRUE)
	{	m_bEscPressed = FALSE;
		m_bEnterPressed = FALSE;
		delete pMI;
		ChangeGameMode(DEF_GAMEMODE_NULL);
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
		return;
	}
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_QUIT, 0,0,0, TRUE);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162,125,2);
	PutAlignedString(168, 474, 160, UPDATE_SCREEN_ON_VERSION_NO_MATCH1);
	PutAlignedString(168, 474, 180, UPDATE_SCREEN_ON_VERSION_NO_MATCH2);
	PutAlignedString(168, 474, 250, MSG_HOMEPAGE);
	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if ((cMIresult == DEF_MIRESULT_CLICK) && (iMIbuttonNum == 1))
	{	ChangeGameMode(DEF_GAMEMODE_NULL);
		delete pMI;
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
		return;
	}
	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

void CGame::DrawVersion(BOOL bAuthor)
{DWORD dwTime = timeGetTime();
 WORD  wR, wG, wB;
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(140, 140, 140), &wR, &wG, &wB);
	// Ver
	m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(14, 463, 19, wR, wG, wB, dwTime);
	// Upper Version
	wsprintf(G_cTxt, "%d", DEF_UPPERVERSION);
	PutString_SprNum(36, 463, G_cTxt, 140, 140, 140);
	// .
	m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(42, 463, 18, wR, wG, wB, dwTime);
	// Lower Version
	wsprintf(G_cTxt, "%d", DEF_LOWERVERSION);
	PutString_SprNum(46, 463, G_cTxt, 140, 140, 140);
	if (bAuthor == FALSE) return;
	// Of course it's easy to remove those lines, but those people deserve some credit
	// at least for releasing their work....
	PutString2(14, 375, "V3.51 compatibility by Cleroth", 220, 200, 200);
	PutString2(14, 390, "V3.51 dialogs by Diuuude", 220, 200, 200);
	PutString2(14, 405, "Effects, mobs, Apocalypse, Heldenian,", 220, 200, 200);
	PutString2(14, 420, "& finalizing by Snoopy81", 220, 200, 200);
	PutString2(14, 435, "Angels & Crafting by Snoopy81", 220, 200, 200);

}

char CGame::GetOfficialMapName(char * pMapName, char * pName)
{	// MapIndex
	if (strcmp(pMapName, "middleland") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME28);	// Middleland
		return 4;
	}else if (strcmp(pMapName, "huntzone3") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME31);	// Death Valley
		return 0;
	}else if (strcmp(pMapName, "huntzone1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME29);	// Rocky Highland
		return 1;
	}else if (strcmp(pMapName, "elvuni") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME57);	// Eldiniel Garden
		return 2;
	}else if (strcmp(pMapName, "elvine") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME24);	// Elvine City
		return 3;
	}else if (strcmp(pMapName, "elvfarm") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME2);	// Elvine Farm
		return 5;
	}else if (strcmp(pMapName, "arefarm") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME1);	// Aresden Farm
		return 6;
	}else if (strcmp(pMapName, "default") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME3);	// Beginner Zone
		return 7;
	}else if (strcmp(pMapName, "huntzone4") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME32);	// Silent Wood
		return 8;
	}else if (strcmp(pMapName, "huntzone2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME30);	// Eternal Field
		return 9;
	}else if (strcmp(pMapName, "areuni") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME56);	// Aresien Garden
		return 10;
	}else if (strcmp(pMapName, "aresden") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME22);	// Aresden City
		return 11;
	}else if (strcmp(pMapName, "dglv2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME25);	// Dungeon L2
		return 12;
	}else if (strcmp(pMapName, "dglv3") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME26);	// Dungeon L3
		return 13;
	}else if (strcmp(pMapName, "dglv4") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME53);	// Dungeon L4
		return 14;
	}else if (strcmp(pMapName, "elvined1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME23);	// Elvine Dungeon
		return 15;
	}else if (strcmp(pMapName, "aresdend1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME21);	// Aresden Dungeon
		return 16;
	}else if (strcmp(pMapName, "bisle") == 0) {
		strcpy(pName, GET_OFFICIAL_MAP_NAME27);	// Bleeding Island
		return 17;
	}else if (strcmp(pMapName, "toh1") == 0) {
		strcpy(pName, GET_OFFICIAL_MAP_NAME60);	// Tower of Hell 1
		return 18;
	}else if (strcmp(pMapName, "toh2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME61);	// Tower of Hell 2
		return 19;
	}else if (strcmp(pMapName, "toh3") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME62);	// Tower of Hell 3
		return 20;
	}else if (strcmp(pMapName, "middled1x") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME58);	// Middleland Mine
		return 21;
	}else if (strcmp(pMapName, "middled1n") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME59);	// Middleland Dungeon
		return 22;
	}else if (strcmp(pMapName, "2ndmiddle") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME65);	// Promiseland
		return 23;
	}else if (strcmp(pMapName, "icebound") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME66);	// Ice Map
		return 24;
	// Snoopy:
	}else if (strcmp(pMapName, "druncncity") == 0) // Snoopy: Apocalypse maps
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME70);
		return 25;
	}else if (strcmp(pMapName, "inferniaA") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME71);
		return 26;
	}else if (strcmp(pMapName, "inferniaB") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME72);
		return 27;
	}else if (strcmp(pMapName, "maze") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME73);
		return 28;
	}else if (strcmp(pMapName, "procella") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME74);
		return 29;
	}else if (strcmp(pMapName, "abaddon") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME75);
		return 30;
	}else if (strcmp(pMapName, "BtField") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME76);
		return 35;
	}else if (strcmp(pMapName, "GodH") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME77);
		return 36;
	}else if (strcmp(pMapName, "HRampart") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME78);
		return 37;
	}else if (strcmp(pMapName, "cityhall_1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME35);	// Aresden Cityhall
		return -1;
	}else if (strcmp(pMapName, "cityhall_2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME36);	// Elvine Cityhall
		return -1;
	}else if (strcmp(pMapName, "gldhall_1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME37);	// Aresden Guildhall
		return -1;
	}else if (strcmp(pMapName, "gldhall_2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME38);	// Elvine Guildhall
		return -1;
	}else if (memcmp(pMapName, "bsmith_1", 8) == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME33);	// Aresden Blacksmith
		return -1;
	}else if (memcmp(pMapName, "bsmith_2", 8) == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME34);	// Elvine Blacksmith
		return -1;
	}else if (memcmp(pMapName, "gshop_1", 7) == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME39);	// Aresden Shop
		return -1;
	}else if (memcmp(pMapName, "gshop_2", 7) == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME40);	// Elvine Shop
		return -1;
	}else if (memcmp(pMapName, "wrhus_1", 7) == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME43);	// Aresden Warehouse
		return -1;
	}else if (memcmp(pMapName, "wrhus_2", 7) == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME44);	// Elvine Warehouse
		return -1;
	}else if (strcmp(pMapName, "arewrhus") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME45);	// Aresden Warehouse
		return -1;
	}else if (strcmp(pMapName, "elvwrhus") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME46);	// Elvine Warehouse
		return -1;
	}else if (strcmp(pMapName, "wzdtwr_1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME41);	// Magic Tower
		return -1;
	}else if (strcmp(pMapName, "wzdtwr_2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME42);	// Magic Tower
		return -1;
	}else if (strcmp(pMapName, "cath_1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME47);	// Aresien Church
		return -1;
	}else if (strcmp(pMapName, "cath_2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME48);	// Eldiniel Church
		return -1;
	}else if (strcmp(pMapName, "resurr1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME54);	// Revival Zone
		return -1;
	}else if (strcmp(pMapName, "resurr2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME55);	// Revival Zone
		return -1;
	}else if (strcmp(pMapName, "arebrk11") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME4);	// Aresden Barrack 1
		return -1;
	}else if (strcmp(pMapName, "arebrk12") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME5);	// Aresden Barrack 1
		return -1;
	}else if (strcmp(pMapName, "arebrk21") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME6);	// Aresden Barrack 2
		return -1;
	}else if (strcmp(pMapName, "arebrk22") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME7);	// Aresden Barrack 2
		return -1;
	}else if (strcmp(pMapName, "elvbrk11") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME8);	// Elvine Barrack 1
		return -1;
	}else if (strcmp(pMapName, "elvbrk12") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME9);	// Elvine Barrack 1
		return -1;
	}else if (strcmp(pMapName, "elvbrk21") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME10);	// Elvine Barrack 2
		return -1;
	}else if (strcmp(pMapName, "elvbrk22") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME11);	// Elvine Barrack 2
		return -1;
	}else if (strcmp(pMapName, "fightzone1") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME12);	// Arena 1
		return -1;
	}else if (strcmp(pMapName, "fightzone2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME13);	// Arena 2
		return -1;
	}else if (strcmp(pMapName, "fightzone3") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME14);	// Arena 3
		return -1;
	}else if (strcmp(pMapName, "fightzone4") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME15);	// Arena 4
		return -1;
	}else if (strcmp(pMapName, "fightzone5") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME16);	// Arena 5
		return -1;
	}else if (strcmp(pMapName, "fightzone6") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME17);	// Arena 6
		return -1;
	}else if (strcmp(pMapName, "fightzone7") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME18);	// Arena 7
		return -1;
	}else if (strcmp(pMapName, "fightzone8") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME19);	// Arena 8
		return -1;
	}else if (strcmp(pMapName, "fightzone9") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME20);	// Arena 9
		return -1;
	}else if (strcmp(pMapName, "arejail") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME63);	// Aresden Jail
		return -1;
	}else if (strcmp(pMapName, "elvjail") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME64);	// Elvine Jail
		return -1;
	}else if (strcmp(pMapName, "CmdHall_1") == 0) // Snoopy: Commander Halls
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME79);
		return -1;
	}else if (strcmp(pMapName, "CmdHall_2") == 0)
	{	strcpy(pName, GET_OFFICIAL_MAP_NAME79);
		return -1;
	}
	else
	{	strcpy(pName, pMapName);
		return -1;
	}
}

BOOL CGame::bCheckLocalChatCommand(char * pMsg)
{class  CStrTok * pStrTok = NULL;
 char   * token, cBuff[256], cTxt[120], cName[12], cTemp[120];
 char   seps[] = " \t\n";
	ZeroMemory(cBuff, sizeof(cBuff));
	ZeroMemory(cName, sizeof(cName));
	strcpy(cBuff, pMsg);
	if (memcmp(cBuff, "/showframe", 10)==0)
	{	if(m_bShowFPS) m_bShowFPS = FALSE;
		else m_bShowFPS = TRUE;
		return TRUE;
	}
	if (memcmp(cBuff, "/enabletogglescreen", 19)==0)
	{	m_bToggleScreen = TRUE;
		return TRUE;
	}
	if (memcmp(cBuff, "/whon", 5) == 0)
	{	m_bWhisper = TRUE;
	    AddEventList(BCHECK_LOCAL_CHAT_COMMAND6, 10);// Enable to listen to whispers."
		return TRUE;
	}else if (memcmp(cBuff, "/whoff", 6) == 0)
	{	m_bWhisper = FALSE;
	    AddEventList(BCHECK_LOCAL_CHAT_COMMAND7, 10);//
		return TRUE;
	}else if (memcmp(cBuff, "/shon", 5) == 0)
	{	m_bShout = TRUE;
	    AddEventList(BCHECK_LOCAL_CHAT_COMMAND8, 10); //Enalbe to chat in public."
		return TRUE;
	}else if (memcmp(cBuff, "/shoff", 6) == 0)
	{	m_bShout = FALSE;
	    AddEventList(BCHECK_LOCAL_CHAT_COMMAND9, 10); //Unable to chat in public."
		return TRUE;
	}
	if (memcmp(cBuff, "/tooff", 6) == 0)
	{	pStrTok = new class CStrTok(cBuff, seps);
		token = pStrTok->pGet();
		token = pStrTok->pGet();
		if (token != NULL)
		{	if (strlen(token) <= 10)
			{	strcpy(cName, token);
				if (memcmp(m_cPlayerName, cName, 10) == 0)
				{	AddEventList(BCHECK_LOCAL_CHAT_COMMAND2, 10);
					if (pStrTok != NULL) delete pStrTok;
					return TRUE;
				}
				if( m_pExID != NULL ) delete m_pExID;
				wsprintf(cTxt, BCHECK_LOCAL_CHAT_COMMAND3, token);
				AddEventList(cTxt, 10);
				m_pExID = new class CMsg(NULL, token, NULL);
				if (pStrTok != NULL) delete pStrTok;
				return TRUE;
   			}
			else AddEventList(BCHECK_LOCAL_CHAT_COMMAND5, 10);
		}
		if (pStrTok != NULL) delete pStrTok;
		return TRUE;
	}else if (memcmp(cBuff, "/toon", 5) == 0)
	{	pStrTok = new class CStrTok(cBuff, seps);
		token = pStrTok->pGet();
		token = pStrTok->pGet();
		if (token != NULL)
		{	if (strlen(token) <= 10)
			{	strcpy(cName, token);
				if (m_pExID != NULL)
				{	ZeroMemory(cTemp, sizeof(cTemp));
					strcpy(cTemp, m_pExID->m_pMsg);
					if (memcmp(cTemp, cName, 10) == 0)
					{	wsprintf(cTxt, BCHECK_LOCAL_CHAT_COMMAND1, token);
						AddEventList(cTxt, 10);
						delete m_pExID;
						m_pExID = NULL;
						if (pStrTok != NULL) delete pStrTok;
						return TRUE;
				}	}
   			}else AddEventList(BCHECK_LOCAL_CHAT_COMMAND5, 10);
		}
		if (pStrTok != NULL) delete pStrTok;
		return TRUE;
	}
	if (pStrTok != NULL) delete pStrTok;
	return FALSE;
}

BOOL CGame::bCheckItemOperationEnabled(char cItemID)
{
	if (m_pItemList[cItemID] == NULL) return FALSE;
	if (m_cCommand < 0) return FALSE;
	if (m_bIsTeleportRequested == TRUE) return FALSE;
	if (m_bIsItemDisabled[cItemID] == TRUE) return FALSE;

	if ((m_pItemList[cItemID]->m_sSpriteFrame == 155) && (m_bUsingSlate == TRUE))
	{	if ((m_cMapIndex==35)||(m_cMapIndex==36)||(m_cMapIndex==37))
		{	AddEventList(DEF_MSG_NOTIFY_SLATE_WRONG_MAP, 10); // "You cannot use it right here."
			return FALSE;
		}
		AddEventList(DEF_MSG_NOTIFY_SLATE_ALREADYUSING, 10); // Already Using Another Slate
		return FALSE;
	}

	if ( m_bIsDialogEnabled[17] == TRUE )
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	if (m_bIsDialogEnabled[20] == TRUE)
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	if (m_bIsDialogEnabled[23] == TRUE)
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	if (m_bIsDialogEnabled[26] == TRUE)
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	if (m_bIsDialogEnabled[27] == TRUE)
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	if (m_bIsDialogEnabled[31] == TRUE)
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	if (m_bIsDialogEnabled[4] == TRUE)
	{	AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
		return FALSE;
	}

	return TRUE;
}

void CGame::ClearSkillUsingStatus()
{
	if (m_bSkillUsingStatus == TRUE)
	{	AddEventList(CLEAR_SKILL_USING_STATUS1, 10);//"
		DisableDialogBox(24);
		DisableDialogBox(26);
		if ((m_sPlayerType >= 1) && (m_sPlayerType <= 6)/* && ((m_sPlayerAppr2 & 0xF000) == 0)*/) {
			m_cCommand = DEF_OBJECTSTOP;
			m_sCommX = m_sPlayerX;
			m_sCommY = m_sPlayerY;
		}
	}
	m_bSkillUsingStatus = FALSE;
}


void CGame::NpcTalkHandler(char *pData)
{
 char  * cp, cRewardName[21], cTargetName[21], cTemp[21], cTxt[250];
 short * sp, sType, sResponse;
 int     iAmount, iIndex, iContribution, iX, iY, iRange;
 int     iTargetType, iTargetCount, iQuestionType;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	sp = (short *)cp;
	sType = *sp;
	cp += 2;
	sp = (short *)cp;
	sResponse = *sp;
	cp += 2;
	sp = (short *)cp;
	iAmount = *sp;
	cp += 2;
	sp = (short *)cp;
	iContribution = *sp;
	cp += 2;
	sp = (short *)cp;
	iTargetType = *sp;
	cp += 2;
	sp = (short *)cp;
	iTargetCount = *sp;
	cp += 2;
	sp = (short *)cp;
	iX = *sp;
	cp += 2;
	sp = (short *)cp;
	iY = *sp;
	cp += 2;
	sp = (short *)cp;
	iRange = *sp;
	cp += 2;
	ZeroMemory(cRewardName, sizeof(cRewardName));
	memcpy(cRewardName, cp, 20);
	cp += 20;
	ZeroMemory(cTargetName, sizeof(cTargetName));
	memcpy(cTargetName, cp, 20);
	cp += 20;
	EnableDialogBox(21, sResponse, sType, 0);

	if ((sType >= 1) && (sType <= 100))
	{	iIndex = m_stDialogBoxInfo[21].sV1;
		m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
		iIndex++;
		iQuestionType = NULL;
		switch (sType) {
		case 1: //Monster Hunt
			ZeroMemory(cTemp, sizeof(cTemp));
			GetNpcName(iTargetType, cTemp);
			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, NPC_TALK_HANDLER16, iTargetCount, cTemp);
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
			if (memcmp(cTargetName, "NONE", 4) == 0) {
				strcpy(cTxt, NPC_TALK_HANDLER17);//"
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;
			}
			else {
				ZeroMemory(cTemp, sizeof(cTemp));
				GetOfficialMapName(cTargetName, cTemp);
				wsprintf(cTxt, NPC_TALK_HANDLER18, cTemp);//"Map : %s"
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;

				if (iX != 0) {
					ZeroMemory(cTxt, sizeof(cTxt));
					wsprintf(cTxt, NPC_TALK_HANDLER19, iX, iY, iRange);//"Position: %d,%d within %d blocks"
					m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
					iIndex++;
				}

				ZeroMemory(cTxt, sizeof(cTxt));
				wsprintf(cTxt, NPC_TALK_HANDLER20, iContribution);//"
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;
			}
			iQuestionType = 1;
			break;

		case 7: //
			ZeroMemory(cTxt, sizeof(cTxt));
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, NPC_TALK_HANDLER21, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
			if (memcmp(cTargetName, "NONE", 4) == 0) {
				strcpy(cTxt, NPC_TALK_HANDLER22);
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;
			}
			else {
				ZeroMemory(cTemp, sizeof(cTemp));
				GetOfficialMapName(cTargetName, cTemp);
				wsprintf(cTxt, NPC_TALK_HANDLER23, cTemp);
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;

				if (iX != 0) {
					ZeroMemory(cTxt, sizeof(cTxt));
					wsprintf(cTxt, NPC_TALK_HANDLER24, iX, iY, iRange);
					m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
					iIndex++;
				}

				ZeroMemory(cTxt, sizeof(cTxt));
				wsprintf(cTxt, NPC_TALK_HANDLER25, iContribution);
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;
			}
			iQuestionType = 1;
			break;

		case 10: // Crusade
			ZeroMemory(cTxt, sizeof(cTxt));
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, NPC_TALK_HANDLER26, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
            strcpy(cTxt, NPC_TALK_HANDLER27);//"
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
            strcpy(cTxt, NPC_TALK_HANDLER28);//"
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
            strcpy(cTxt, NPC_TALK_HANDLER29);//"
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
            strcpy(cTxt, NPC_TALK_HANDLER30);//"
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
			strcpy(cTxt, " ");
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
			iIndex++;

			ZeroMemory(cTxt, sizeof(cTxt));
			if (memcmp(cTargetName, "NONE", 4) == 0) {
				strcpy(cTxt, NPC_TALK_HANDLER31);//"
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;
			}
			else {
				ZeroMemory(cTemp, sizeof(cTemp));
				GetOfficialMapName(cTargetName, cTemp);
				wsprintf(cTxt, NPC_TALK_HANDLER32, cTemp);//"
				m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
				iIndex++;
			}
			iQuestionType = 2;
			break;
		}

		switch (iQuestionType) {
		case 1:
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
			iIndex++;
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, NPC_TALK_HANDLER33, NULL);//"
			iIndex++;
			m_pMsgTextList2[iIndex]  = new class CMsg(NULL, NPC_TALK_HANDLER34, NULL);//"
			iIndex++;
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
			iIndex++;
			break;

		case 2:
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
			iIndex++;
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, NPC_TALK_HANDLER35, NULL);//"
			iIndex++;
			m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
			iIndex++;
			break;

		default: break;
		}
	}
}

void CGame::GetNpcName(short sType, char *pName)
{
	switch (sType)
	{
	case 10: strcpy(pName, NPC_NAME_SLIME); break;
	case 11: strcpy(pName, NPC_NAME_SKELETON); break;
	case 12: strcpy(pName, NPC_NAME_STONEGOLEM); break;
	case 13: strcpy(pName, NPC_NAME_CYCLOPS); break;
	case 14: strcpy(pName, NPC_NAME_ORC); break;
	case 15: strcpy(pName, NPC_NAME_SHOP_KEEPER); break;
	case 16: strcpy(pName, NPC_NAME_GIANTANT); break;
	case 17: strcpy(pName, NPC_NAME_GIANTSCORPION); break;
	case 18: strcpy(pName, NPC_NAME_ZOMBIE); break;
	case 19: strcpy(pName, NPC_NAME_MAGICIAN); break;
	case 20: strcpy(pName, NPC_NAME_WAREHOUSE_KEEPER); break;
	case 21: strcpy(pName, NPC_NAME_GUARD); break;
	case 22: strcpy(pName, NPC_NAME_SNAKE); break;
	case 23: strcpy(pName, NPC_NAME_CLAYGOLEM); break;
	case 24: strcpy(pName, NPC_NAME_BLACKSMITH_KEEPER); break;
	case 25: strcpy(pName, NPC_NAME_CITYHALL_OFFICER); break;
	case 26: strcpy(pName, NPC_NAME_GUILDHALL_OFFICER); break;
	case 27: strcpy(pName, NPC_NAME_HELHOUND); break;
	case 28: strcpy(pName, NPC_NAME_TROLL); break;
	case 29: strcpy(pName, NPC_NAME_OGRE); break;
	case 30: strcpy(pName, NPC_NAME_LICHE); break;
	case 31: strcpy(pName, NPC_NAME_DEMON); break;
	case 32: strcpy(pName, NPC_NAME_UNICORN); break;
	case 33: strcpy(pName, NPC_NAME_WEREWOLF); break;
	case 34: strcpy(pName, NPC_NAME_DUMMY); break;
	case 35: strcpy(pName, NPC_NAME_ENERGYSPHERE); break;
	case 36:
		if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_ARROWGUARDTOWER_CK);
		else strcpy(pName, NPC_NAME_ARROWGUARDTOWER);
		break;
	case 37:
		if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_CANNONGUARDTOWER_CK);
		else strcpy(pName, NPC_NAME_CANNONGUARDTOWER);
		break;
	case 38:
		if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_MANACOLLECTOR_CK);
		else strcpy(pName, NPC_NAME_MANACOLLECTOR);
		break;
	case 39:
		if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_DETECTOR_CK);
		else strcpy(pName, NPC_NAME_DETECTOR);
		break;
	case 40: strcpy(pName, NPC_NAME_ENERGYSHIELD); break;
	case 41: strcpy(pName, NPC_NAME_GRANDMAGICGENERATOR); break;
	case 42: strcpy(pName, NPC_NAME_MANASTONE); break;
	case 43: strcpy(pName, NPC_NAME_LIGHTWARBEETLE); break;
	case 44: strcpy(pName, NPC_NAME_GODSHANDKNIGHT); break;
	case 45: strcpy(pName, NPC_NAME_GODSHANDKNIGHT_CK); break;
	case 46: strcpy(pName, NPC_NAME_TEMPLEKNIGHT); break;
	case 47: strcpy(pName, NPC_NAME_BATTLEGOLEM); break;
	case 48: strcpy(pName, NPC_NAME_STALKER); break;
	case 49: strcpy(pName, NPC_NAME_HELLCLAW); break;
	case 50: strcpy(pName, NPC_NAME_TIGERWORM); break;
	case 51: strcpy(pName, NPC_NAME_CATAPULT); break;
	case 52: strcpy(pName, NPC_NAME_GARGOYLE); break;
	case 53: strcpy(pName, NPC_NAME_BEHOLDER); break;
	case 54: strcpy(pName, NPC_NAME_DARKELF); break;
	case 55: strcpy(pName, NPC_NAME_RABBIT); break;
	case 56: strcpy(pName, NPC_NAME_CAT); break;
	case 57: strcpy(pName, NPC_NAME_FROG); break;
	case 58: strcpy(pName, NPC_NAME_MOUNTAIN_GIANT); break;
	case 59: strcpy(pName, NPC_NAME_ETTIN); break;
	case 60: strcpy(pName, NPC_NAME_CANNIBAL); break;
	case 61: strcpy(pName, NPC_NAME_RUDOLPH); break;
	case 62: strcpy(pName, NPC_NAME_DIREBOAR); break;
	case 63: strcpy(pName, NPC_NAME_FROST); break;
	case 64:
		{	switch((_tmp_sAppr2 & 0xFF00)>>8)	{
			case 1:	strcpy(pName, NPC_NAME_WATERMELON);	break;
			case 2: strcpy(pName, NPC_NAME_PUMPKIN); break;
			case 3: strcpy(pName, NPC_NAME_GARLIC); break;
			case 4: strcpy(pName, NPC_NAME_BARLEY); break;
			case 5:	strcpy(pName, NPC_NAME_CARROT); break;
			case 6: strcpy(pName, NPC_NAME_RADISH); break;
			case 7: strcpy(pName, NPC_NAME_CORN); break;
			case 8: strcpy(pName, NPC_NAME_BFLOWER); break;
			case 9: strcpy(pName, NPC_NAME_MELON); break;
			case 10: strcpy(pName, NPC_NAME_TOMATO); break;
			case 11: strcpy(pName, NPC_NAME_GRAPPE); break;
			case 12: strcpy(pName, NPC_NAME_BLUEGRAPPE); break;
			case 13: strcpy(pName, NPC_NAME_MUSHROM); break;
			case 14: strcpy(pName, NPC_NAME_GINSENG); break;
			default: strcpy(pName, NPC_NAME_CROP); break;
			}
		}
		break;
	case 65: strcpy(pName, NPC_NAME_ICEGOLEM); break;
	case 66: strcpy(pName, NPC_NAME_WYVERN); break;
	case 67: strcpy(pName, NPC_NAME_MCGAFFIN); break;
	case 68: strcpy(pName, NPC_NAME_PERRY); break;
	case 69: strcpy(pName, NPC_NAME_DEVLIN); break;

	case 70: strcpy(pName, NPC_NAME_DRAGON); break;
	case 71: strcpy(pName, NPC_NAME_CENTAUR); break;
	case 72: strcpy(pName, NPC_NAME_CLAWTUR); break;
	case 73: strcpy(pName, NPC_NAME_FIREWYV); break;
	case 74: strcpy(pName, NPC_NAME_GICRAYF); break;
	case 75: strcpy(pName, NPC_NAME_GILIZAR); break;
	case 76: strcpy(pName, NPC_NAME_GITREE); break;
	case 77: strcpy(pName, NPC_NAME_MASTORC); break;
	case 78: strcpy(pName, NPC_NAME_MINAUS); break;
	case 79: strcpy(pName, NPC_NAME_NIZIE); break;

	case 80: strcpy(pName, NPC_NAME_TENTOCL); break;
	case 81: strcpy(pName, NPC_NAME_ABADDON); break;
	case 82: strcpy(pName, NPC_NAME_SORCERS); break;
	case 83: strcpy(pName, NPC_NAME_ATK); break;
	case 84: strcpy(pName, NPC_NAME_MASTELF); break;
	case 85: strcpy(pName, NPC_NAME_DSK); break;
	case 86: strcpy(pName, NPC_NAME_HBT); break;
	case 87: strcpy(pName, NPC_NAME_CT); break;
	case 88: strcpy(pName, NPC_NAME_BARBAR); break;
	case 89: strcpy(pName, NPC_NAME_AGC); break;
	case 90: strcpy(pName, NPC_NAME_GAIL); break;
	case 91: strcpy(pName, NPC_NAME_GATE); break;

	// CLEROTH - NEW MONSTERS
	case 110: strcpy(pName, NPC_NAME_AIRLEMENTAL); break;
	}
}

void CGame::GetItemName(CItem *pItem, char *pStr1, char *pStr2, char *pStr3)
{int i;
 char cTxt[256], cTxt2[256], cName[51];
 DWORD dwType1, dwType2, dwValue1, dwValue2, dwValue3;

	m_bIsSpecial = FALSE;
	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(pStr1, sizeof(pStr1));
	ZeroMemory(pStr2, sizeof(pStr2));
	ZeroMemory(pStr3, sizeof(pStr3));

	strcpy(cName, pItem->m_cName);
	for (i = 0; i < DEF_MAXITEMNAMES; i++)
	if ((m_pItemNameList[i] != NULL) && (strcmp(m_pItemNameList[i]->m_cOriginName, pItem->m_cName) == 0))
	{	strcpy(cName, m_pItemNameList[i]->m_cName);
		break;
	}

     	 if (0 == memcmp(pItem->m_cName,"AcientTablet", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"NecklaceOf", 10)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"DarkElfBow", 10)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"DarkExecutor", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"The_Devastator", 14)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"DemonSlayer", 10)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"LightingBlade", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"5thAnniversary", 13)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"RubyRing", 8)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"SapphireRing", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Ringof", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"MagicNecklace", 13)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"MagicWand(M.Shield)", 19)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"MagicWand(MS30-LLF)", 19)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Merien", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"BerserkWand", 11)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"ResurWand", 9)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Blood", 5)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Swordof", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"StoneOf", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"ZemstoneofSacrifice", 19)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"StormBringer", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Aresden", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Elvine", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"EmeraldRing", 11)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Excaliber", 9)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Xelima", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"Kloness", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"aHeroOf", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(pItem->m_cName,"eHeroOf", 7)) m_bIsSpecial = TRUE;
	if ((pItem->m_dwAttribute & 0x00000001) != 0)
	{	m_bIsSpecial = TRUE;
		strcpy(pStr1, cName);
		if (pItem->m_cItemType == DEF_ITEMTYPE_MATERIAL)
			wsprintf(pStr2, GET_ITEM_NAME1, pItem->m_sItemSpecEffectValue2);		//"Purity: %d%%"
		else
		{	// Crafting Magins completion fix
			if (pItem->m_cEquipPos == DEF_EQUIPPOS_LFINGER)
			{	wsprintf(pStr2, GET_ITEM_NAME2, pItem->m_sItemSpecEffectValue2);	//"Completion:
			}else
			{	wsprintf(pStr2, GET_ITEM_NAME2, pItem->m_sItemSpecEffectValue2 +100);	//"Completion: +100
		}	}
	}else
	{	if (pItem->m_dwCount == 1)
			wsprintf(G_cTxt, "%s", cName);
		else wsprintf(G_cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM1, pItem->m_dwCount, cName);//"%d %s"
		strcpy(pStr1, G_cTxt);
	}

	if ((pItem->m_dwAttribute & 0x00F0F000) != 0)
	{	m_bIsSpecial = TRUE;
		dwType1  = (pItem->m_dwAttribute & 0x00F00000) >> 20;
		dwValue1 = (pItem->m_dwAttribute & 0x000F0000) >> 16;
		dwType2  = (pItem->m_dwAttribute & 0x0000F000) >> 12;
		dwValue2 = (pItem->m_dwAttribute & 0x00000F00) >> 8;
		if (dwType1 != 0)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			switch (dwType1) {
			case 1: strcpy(cTxt, GET_ITEM_NAME3);   break;
			case 2: strcpy(cTxt, GET_ITEM_NAME4);   break; // "Poisoning "
			case 3: strcpy(cTxt, GET_ITEM_NAME5);   break; // "Righteous "
			case 4: break;
			case 5: strcpy(cTxt, GET_ITEM_NAME6);   break; // "Agile "
			case 6: strcpy(cTxt, GET_ITEM_NAME7);   break;
			case 7: strcpy(cTxt, GET_ITEM_NAME8);   break;
			case 8: strcpy(cTxt, GET_ITEM_NAME9);   break;
			case 9: strcpy(cTxt, GET_ITEM_NAME10);  break;
			case 10: strcpy(cTxt, GET_ITEM_NAME11); break;
			case 11: strcpy(cTxt, GET_ITEM_NAME12); break;
			case 12: strcpy(cTxt, GET_ITEM_NAME13); break;
			}
			strcat(cTxt, pStr1);
			ZeroMemory(pStr1, sizeof(pStr1));
			strcpy(pStr1, cTxt);

			ZeroMemory(cTxt, sizeof(cTxt));
			switch (dwType1) {
			case 1: wsprintf(cTxt, GET_ITEM_NAME14, dwValue1); break; // "Critical Hit Damage+%d"
			case 2: wsprintf(cTxt, GET_ITEM_NAME15, dwValue1*5); break; // "Poison Damage+%d"
			case 3: break;
			case 4: break;
			case 5: strcpy(cTxt, GET_ITEM_NAME16); break; // "Attack Speed -1"
			case 6: wsprintf(cTxt, GET_ITEM_NAME17, dwValue1*4); break;
			case 7: strcpy(cTxt, GET_ITEM_NAME18); break;
			case 8: wsprintf(cTxt, GET_ITEM_NAME19, dwValue1*7); break;
			case 9: strcpy(cTxt, GET_ITEM_NAME20); break;
			case 10: wsprintf(cTxt, GET_ITEM_NAME21, dwValue1*3); break;
			case 11: wsprintf(cTxt, GET_ITEM_NAME22, dwValue1); break;
			case 12: wsprintf(cTxt, GET_ITEM_NAME23, dwValue1); break;
			}
			strcat(pStr2, cTxt);

			if (dwType2 != 0) {
				ZeroMemory(cTxt, sizeof(cTxt));
				switch (dwType2) {
				case 1:  wsprintf(cTxt, GET_ITEM_NAME24, dwValue2*7); break;
				case 2:  wsprintf(cTxt, GET_ITEM_NAME25, dwValue2*7); break;
				case 3:  wsprintf(cTxt, GET_ITEM_NAME26, dwValue2*7); break;
				case 4:  wsprintf(cTxt, GET_ITEM_NAME27, dwValue2*7); break;
				case 5:  wsprintf(cTxt, GET_ITEM_NAME28, dwValue2*7); break;//"SPrec
				case 6:  wsprintf(cTxt, GET_ITEM_NAME29, dwValue2*7); break;//"MPrec
				case 7:  wsprintf(cTxt, GET_ITEM_NAME30, dwValue2*7); break;
				case 8:  wsprintf(cTxt, GET_ITEM_NAME31, dwValue2*3); break;
				case 9:  wsprintf(cTxt, GET_ITEM_NAME32, dwValue2*3); break;
				case 10: wsprintf(cTxt, GET_ITEM_NAME33, dwValue2);   break;
				case 11: wsprintf(cTxt, GET_ITEM_NAME34, dwValue2*10); break;
				case 12: wsprintf(cTxt, GET_ITEM_NAME35, dwValue2*10); break;//"Gold +%
				}
				strcpy(pStr3, cTxt);
	}	}	}

	dwValue3 = (pItem->m_dwAttribute & 0xF0000000) >> 28;
	if (dwValue3 > 0)
	{	if (pStr1[strlen(pStr1)-2] == '+')
		{	dwValue3 = atoi((char *)(pStr1 + strlen(pStr1)-1)) + dwValue3;
			ZeroMemory(cTxt, sizeof(cTxt));
			memcpy(cTxt, pStr1, strlen(pStr1)-2);
			ZeroMemory(cTxt2, sizeof(cTxt2));
			wsprintf(cTxt2, "%s+%d", cTxt, dwValue3);
			ZeroMemory(pStr1, sizeof(pStr1));
			strcpy(pStr1, cTxt2);
		}else
		{	ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, "+%d", dwValue3);
			strcat(pStr1, cTxt);
	}	}
}

void CGame::GetItemName(char * cItemName, DWORD dwAttribute, char *pStr1, char *pStr2, char *pStr3)
{
 int i;
 char cTxt[256], cTxt2[256], cName[51];
 DWORD dwType1, dwType2, dwValue1, dwValue2, dwValue3;

 m_bIsSpecial = FALSE;
	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(pStr1, sizeof(pStr1));
	ZeroMemory(pStr2, sizeof(pStr2));
	ZeroMemory(pStr3, sizeof(pStr3));

	strcpy(cName, cItemName);
	for (i = 0; i < DEF_MAXITEMNAMES; i++)
	if ((m_pItemNameList[i] != NULL) && (strcmp(m_pItemNameList[i]->m_cOriginName, cItemName) == 0)) {
		strcpy(cName, m_pItemNameList[i]->m_cName);
		break;
	}

     	 if (0 == memcmp(cItemName,"AcientTablet", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"NecklaceOf", 10)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"DarkElfBow", 10)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"DarkExecutor", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"The_Devastator", 14)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"DemonSlayer", 10)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"LightingBlade", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"5thAnniversary", 13)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"RubyRing", 8)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"SapphireRing", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Ringof", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"MagicNecklace", 13)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"MagicWand(M.Shield)", 19)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"MagicWand(MS30-LLF)", 19)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Merien", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"BerserkWand", 11)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"ResurWand", 9)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Blood", 5)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Swordof", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"StoneOf", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"ZemstoneofSacrifice", 19)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"StormBringer", 12)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Aresden", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Elvine", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"EmeraldRing", 11)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Excaliber", 9)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Xelima", 6)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"Kloness", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"aHeroOf", 7)) m_bIsSpecial = TRUE;
	else if (0 == memcmp(cItemName,"eHeroOf", 7)) m_bIsSpecial = TRUE;
	strcpy(pStr1, cName);

	if ((dwAttribute & 0x00F0F000) != 0)
	{	m_bIsSpecial = TRUE;
		dwType1  = (dwAttribute & 0x00F00000) >> 20;
		dwValue1 = (dwAttribute & 0x000F0000) >> 16;
		dwType2  = (dwAttribute & 0x0000F000) >> 12;
		dwValue2 = (dwAttribute & 0x00000F00) >> 8;
		if (dwType1 != 0)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			switch (dwType1) {
			case 1: strcpy(cTxt, GET_ITEM_NAME3); break;
			case 2: strcpy(cTxt, GET_ITEM_NAME4); break;
			case 3: strcpy(cTxt, GET_ITEM_NAME5); break;
			case 4: break;
			case 5: strcpy(cTxt, GET_ITEM_NAME6); break;
			case 6: strcpy(cTxt, GET_ITEM_NAME7); break;
			case 7: strcpy(cTxt, GET_ITEM_NAME8); break;
			case 8: strcpy(cTxt, GET_ITEM_NAME9); break;
			case 9: strcpy(cTxt, GET_ITEM_NAME10); break;
			case 10: strcpy(cTxt, GET_ITEM_NAME11); break;
			case 11: strcpy(cTxt, GET_ITEM_NAME12); break;
			case 12: strcpy(cTxt, GET_ITEM_NAME13); break;
			}
			strcat(cTxt, pStr1);
			ZeroMemory(pStr1, sizeof(pStr1));
			strcpy(pStr1, cTxt);

			ZeroMemory(cTxt, sizeof(cTxt));
			switch (dwType1) {
			case 1: wsprintf(cTxt, GET_ITEM_NAME14, dwValue1); break;
			case 2: wsprintf(cTxt, GET_ITEM_NAME15, dwValue1*5); break;
			case 3: break;
			case 4: break;
			case 5: strcpy(cTxt, GET_ITEM_NAME16); break;
			case 6: wsprintf(cTxt, GET_ITEM_NAME17, dwValue1*4); break;
			case 7: strcpy(cTxt, GET_ITEM_NAME18); break;
			case 8: wsprintf(cTxt, GET_ITEM_NAME19, dwValue1*7); break;
			case 9: strcpy(cTxt, GET_ITEM_NAME20); break;
			case 10: wsprintf(cTxt, GET_ITEM_NAME21, dwValue1*3); break;
			case 11: wsprintf(cTxt, GET_ITEM_NAME22, dwValue1); break;
			case 12: wsprintf(cTxt, GET_ITEM_NAME23, dwValue1); break;
			}
			strcat(pStr2, cTxt);

			if (dwType2 != 0)
			{	ZeroMemory(cTxt, sizeof(cTxt));
				switch (dwType2) {
				case 1:  wsprintf(cTxt, GET_ITEM_NAME24, dwValue2*7);  break;
				case 2:  wsprintf(cTxt, GET_ITEM_NAME25, dwValue2*7);  break;
				case 3:  wsprintf(cTxt, GET_ITEM_NAME26, dwValue2*7);  break;
				case 4:  wsprintf(cTxt, GET_ITEM_NAME27, dwValue2*7);  break;
				case 5:  wsprintf(cTxt, GET_ITEM_NAME28, dwValue2*7);  break;
				case 6:  wsprintf(cTxt, GET_ITEM_NAME29, dwValue2*7);  break;
				case 7:  wsprintf(cTxt, GET_ITEM_NAME30, dwValue2*7);  break;
				case 8:  wsprintf(cTxt, GET_ITEM_NAME31, dwValue2*3);  break;
				case 9:  wsprintf(cTxt, GET_ITEM_NAME32, dwValue2*3);  break;
				case 10: wsprintf(cTxt, GET_ITEM_NAME33, dwValue2);    break;
				case 11: wsprintf(cTxt, GET_ITEM_NAME34, dwValue2*10); break;
				case 12: wsprintf(cTxt, GET_ITEM_NAME35, dwValue2*10); break;
				}
				strcpy(pStr3, cTxt);
	}	}	}

	dwValue3 = (dwAttribute & 0xF0000000) >> 28;
	if (dwValue3 > 0)
	{	if (pStr1[strlen(pStr1)-2] == '+')
		{	dwValue3 = atoi((char *)(pStr1 + strlen(pStr1)-1)) + dwValue3;
			ZeroMemory(cTxt, sizeof(cTxt));
			memcpy(cTxt, pStr1, strlen(pStr1)-2);
			ZeroMemory(cTxt2, sizeof(cTxt2));
			wsprintf(cTxt2, "%s+%d", cTxt, dwValue3);
			ZeroMemory(pStr1, sizeof(pStr1));
			strcpy(pStr1, cTxt2);
		}else
		{	ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, "+%d", dwValue3);
			strcat(pStr1, cTxt);
	}	}
}

void CGame::_CalcSocketClosed()
{	if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
	{	delete m_pGSock;
		m_pGSock = NULL;
		m_bEscPressed = FALSE;
		PlaySound('E', 14, 5);
		if (m_bSoundFlag) m_pESound[38]->bStop();
		if ((m_bSoundFlag) && (m_bMusicStat == TRUE))
		{
			if (m_pBGM != NULL) m_pBGM->bStop();
		}
		ChangeGameMode(DEF_GAMEMODE_ONQUIT);
	}
}

void CGame::PointCommandHandler(int indexX, int indexY, char cItemID)
{char cTemp[31];
	if ((m_iPointCommandType >= 100) && (m_iPointCommandType < 200))
	{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_MAGIC, NULL, indexX, indexY, m_iPointCommandType, NULL);
	}else if ((m_iPointCommandType >= 0) && (m_iPointCommandType < 50))
	{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, NULL, m_iPointCommandType, indexX, indexY, cTemp, cItemID); // v1.4

		if (m_pItemList[m_iPointCommandType]->m_cItemType == DEF_ITEMTYPE_USE_SKILL)
			m_bSkillUsingStatus = TRUE;
	}else if (m_iPointCommandType == 200) // Normal Hand
	{	if ((strlen(m_cMCName) == 0) || (strcmp(m_cMCName, m_cPlayerName) == 0) || (m_cMCName[0] == '_'))
		{	m_stDialogBoxInfo[32].cMode = 0;
			PlaySound('E', 14, 5);
			AddEventList(POINT_COMMAND_HANDLER1, 10);
		}else
		{	m_stDialogBoxInfo[32].cMode = 3;
			PlaySound('E', 14, 5);
			ZeroMemory(m_stDialogBoxInfo[32].cStr, sizeof(m_stDialogBoxInfo[32].cStr));
			strcpy(m_stDialogBoxInfo[32].cStr, m_cMCName);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, NULL, 1, NULL, NULL, m_cMCName);
			return;
	}	}
}

void CGame::UpdateScreen_OnGame()
{
 short sVal, sDivX, sModX, sDivY, sModY, sPivotX, sPivotY, sVPXsave, sVPYsave;
 static int  iUpdateRet = -1;
 short msX, msY, msZ, absX, absY, tX, tY;
 char cLB, cRB;
 char cItemColor;
 int  i, iAmount;
 DWORD dwTime = timeGetTime();
 static DWORD dwPrevChatTime = 0;
 static int   imX = 0, imY = 0;

	if (m_cGameModeCount == 0)
	{	m_DDraw.ClearBackB4();
		m_dwFPStime = m_dwCheckConnTime = m_dwCheckSprTime = m_dwCheckChatTime = dwTime;
		m_sFrameCount = 0;
		if( m_bMusicStat ) StartBGM();
		//if(m_iLevel < 40) AddEventList(UPDATE_SCREEN_ONGAME12, 10);
	}

	m_cGameModeCount++;
	if (m_cGameModeCount > 20) m_cGameModeCount = 20;
	// ----------------------------------------------------

	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_dwCurTime = timeGetTime();

	if (m_bEnterPressed == TRUE)
	{
		m_bEnterPressed = FALSE;

		if ((m_bIsDialogEnabled[7] == TRUE) && (m_stDialogBoxInfo[7].cMode == 1) && (iGetTopDialogBoxIndex() == 7)) {

			EndInputString();

			m_bEnterPressed = FALSE;
			if (strlen(m_cGuildName) == 0) return;
			if (strcmp(m_cGuildName, "NONE") != 0) {
				bSendCommand(MSGID_REQUEST_CREATENEWGUILD, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL, NULL, NULL);
				m_stDialogBoxInfo[7].cMode = 2;
				//
			}
		}
		else if ((m_bIsDialogEnabled[17] == TRUE) && (m_stDialogBoxInfo[17].cMode == 1) && (iGetTopDialogBoxIndex() == 17)) {
			// Drop Item Query

			EndInputString();

			if (m_bSkillUsingStatus == TRUE)
			{	AddEventList(UPDATE_SCREEN_ONGAME1, 10);
				return;
			}

			if (   (m_bIsDialogEnabled[20] == TRUE)
				&& ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)) )
			{	AddEventList(UPDATE_SCREEN_ONGAME1, 10);//"You can not give or drop before the actual Item transaction."
				return;
			}

			if ( (m_bIsDialogEnabled[4] == TRUE) || (m_bIsDialogEnabled[23] == TRUE) || (m_bIsDialogEnabled[26] == TRUE))
			{	AddEventList(UPDATE_SCREEN_ONGAME1, 10);
				return;
			}

			if (strlen(m_cAmountString) == 0) return;
			iAmount = atoi(m_cAmountString);

			if ((int)(m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount) < iAmount){
				iAmount = m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount ;
			}

			if (iAmount != 0) {
				if ((int)(m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount) >= iAmount) {
					if (m_stDialogBoxInfo[17].sV1 != NULL) {
						absX = abs(m_stDialogBoxInfo[17].sV1 - m_sPlayerX);
						absY = abs(m_stDialogBoxInfo[17].sV2 - m_sPlayerY);

						if ((absX == 0)	&& (absY ==0))
							AddEventList(UPDATE_SCREEN_ONGAME5, 10);
						else if ((absX <= 8) && (absY <= 8)) {
							switch (m_stDialogBoxInfo[17].sV3) {
							case 1:
							case 2:
							case 3:
							case 4:
							case 5:
							case 6:
								EnableDialogBox(20, 1, m_stDialogBoxInfo[17].sView, m_stDialogBoxInfo[17].sV3);
								m_stDialogBoxInfo[20].sV3 = iAmount;
								m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;	// v1.4
								m_stDialogBoxInfo[20].sV5 = m_stDialogBoxInfo[17].sV1;
								m_stDialogBoxInfo[20].sV6 = m_stDialogBoxInfo[17].sV2;

								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;

								ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
								strcpy(m_stDialogBoxInfo[20].cStr, m_stDialogBoxInfo[17].cStr);
								break;

							case 20:
								EnableDialogBox(20, 3, m_stDialogBoxInfo[17].sView, m_stDialogBoxInfo[17].sV3);
								m_stDialogBoxInfo[20].sV3 = iAmount;
								m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;
								m_stDialogBoxInfo[20].sV5 = m_stDialogBoxInfo[17].sV1;
								m_stDialogBoxInfo[20].sV6 = m_stDialogBoxInfo[17].sV2;

								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;

								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;

								ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
								GetNpcName(m_stDialogBoxInfo[17].sV3, m_stDialogBoxInfo[20].cStr);
								break;

							case 15:
		  					case 24:
								EnableDialogBox(20, 2, m_stDialogBoxInfo[17].sView, m_stDialogBoxInfo[17].sV3);
								m_stDialogBoxInfo[20].sV3 = iAmount;
								m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;

								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;

								ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
								GetNpcName(m_stDialogBoxInfo[17].sV3, m_stDialogBoxInfo[20].cStr);
								break;

							case 1000: // Trade stackable items
								// hum, déjà affiché? , j'attends le retour et je désactive!
								/*m_stDialogBoxInfo[27].sV1 = m_pItemList[m_stDialogBoxInfo[17].sV4]->m_sSprite;
								m_stDialogBoxInfo[27].sV2 = m_pItemList[m_stDialogBoxInfo[17].sV4]->m_sSpriteFrame;
								m_stDialogBoxInfo[27].sV3 = iAmount;
								m_stDialogBoxInfo[27].sV4 = m_pItemList[m_stDialogBoxInfo[17].sV4]->m_cItemColor;*/

								if (m_stDialogBoxExchangeInfo[0].sV1 == -1)			m_stDialogBoxExchangeInfo[0].sItemID = m_stDialogBoxInfo[17].sV4;
								else if (m_stDialogBoxExchangeInfo[1].sV1 == -1)	m_stDialogBoxExchangeInfo[1].sItemID = m_stDialogBoxInfo[17].sV4;
								else if (m_stDialogBoxExchangeInfo[2].sV1 == -1)	m_stDialogBoxExchangeInfo[2].sItemID = m_stDialogBoxInfo[17].sV4;
								else if (m_stDialogBoxExchangeInfo[3].sV1 == -1)	m_stDialogBoxExchangeInfo[3].sItemID = m_stDialogBoxInfo[17].sV4;
								else return; // Impossible case, tested at function beginning

								bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETEXCHANGEITEM, NULL, m_stDialogBoxInfo[17].sV4, iAmount, NULL, NULL);
								break;

							case 1001:
								// Sell List
								for (i = 0; i < DEF_MAXSELLLIST; i++)
								if (m_stSellItemList[i].iIndex == -1) {
									m_stSellItemList[i].iIndex = m_stDialogBoxInfo[17].sV4;
									m_stSellItemList[i].iAmount = iAmount;
									m_bIsItemDisabled[m_stDialogBoxInfo[17].sV4] = TRUE;
									break;
								}
								if( i == DEF_MAXSELLLIST ) AddEventList(UPDATE_SCREEN_ONGAME6, 10);
								break;

							case 1002:
								if (_iGetBankItemCount() >= (DEF_MAXBANKITEMS-1)) AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);
								else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[39].sV1, iAmount, m_stDialogBoxInfo[39].sV5, m_stDialogBoxInfo[39].sV6, m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cName, m_stDialogBoxInfo[39].sV4); //v1.4
								break;

							default:
								bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, (char)(m_stDialogBoxInfo[17].sView), iAmount, m_stDialogBoxInfo[17].sV1, m_stDialogBoxInfo[17].sV2, m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName);
								break;
							}
							m_bIsItemDisabled[m_stDialogBoxInfo[17].sView] = TRUE;
		   				}else AddEventList(UPDATE_SCREEN_ONGAME7, 10);
					}else {
						if (iAmount <= 0)
						{	AddEventList(UPDATE_SCREEN_ONGAME8, 10);
						}else
						{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_ITEMDROP, NULL, m_stDialogBoxInfo[17].sView, iAmount, NULL, m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName);
							m_bIsItemDisabled[m_stDialogBoxInfo[17].sView] = TRUE;
					}	}
				}else
				{	AddEventList(UPDATE_SCREEN_ONGAME9, 10);//"You entered more quantity that you can carry."
				}
			}
			DisableDialogBox(17);
		}else
		{	if (!m_bInputStatus)
			{	switch( m_cBackupChatMsg[0] ){
				case '!':
				case '@':
				case '#':
				case '$':
				case '^':
					ZeroMemory(m_cChatMsg, sizeof(m_cChatMsg));
					m_cChatMsg[0] = m_cBackupChatMsg[0];
					StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
					break;
				default:
					StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
					ClearInputString();
					break;
				}
			}else
			{	EndInputString();
				ZeroMemory(G_cTxt, sizeof(G_cTxt));
				ReceiveString((char *)G_cTxt);
				ZeroMemory(m_cBackupChatMsg, sizeof(m_cBackupChatMsg));
				strcpy(m_cBackupChatMsg, G_cTxt);
				if ((m_dwCurTime - dwPrevChatTime) < 700)
				{}else
				{	dwPrevChatTime = m_dwCurTime;
					m_curse.ConvertString( G_cTxt, strlen(G_cTxt) );
					if ( strlen(G_cTxt) > 0 )
					{	if( (G_cTxt[0]=='!') || (G_cTxt[0]=='~'))
						{	if( m_Misc.bCheckIMEString(G_cTxt) == FALSE ) return;
						}
						bSendCommand(MSGID_COMMAND_CHATMSG, NULL, NULL, NULL, NULL, NULL, G_cTxt);
	}	}	}	}	}

	sVPXsave = m_sViewPointX;
	sVPYsave = m_sViewPointY;

	if ((m_iCameraShakingDegree > 0) && (iUpdateRet != 0))
	{	m_sViewPointX += m_iCameraShakingDegree - (rand() % m_iCameraShakingDegree*2);
		m_sViewPointY += m_iCameraShakingDegree - (rand() % m_iCameraShakingDegree*2);
		m_iCameraShakingDegree--;
		if (m_iCameraShakingDegree <= 0) m_iCameraShakingDegree = 0;
	}
	sPivotX = m_pMapData->m_sPivotX;
	sPivotY = m_pMapData->m_sPivotY;
	sVal = m_sViewPointX - (sPivotX*32);
	sDivX = sVal / 32;
	sModX = sVal % 32;
	sVal = m_sViewPointY - (sPivotY*32);
	sDivY = sVal / 32;
	sModY = sVal % 32;
	if (iUpdateRet != 0)
		DrawBackground(sDivX, sModX, sDivY, sModY);

	if (iUpdateRet != 0)
		DrawEffectLights();
	if (iUpdateRet != 0)
		DrawObjects(sPivotX, sPivotY, sDivX, sDivY, sModX, sModY, msX, msY);

	if (iUpdateRet != 0)
	{	DrawEffects();
		DrawWhetherEffects();
		DrawChatMsgs(-100, 0, 800, 600);
		WhetherObjectFrameCounter();
	}

	if (m_cMapIndex == 26)	//Snoopy: Add Apocalypse map effect (fires in inferniaA)
	{	m_pEffectSpr[89]->PutTransSprite(1296 - m_sViewPointX, 1283 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[89]->PutTransSprite(1520 - m_sViewPointX, 1123 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[89]->PutTransSprite(1488 - m_sViewPointX, 3971 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[93]->PutTransSprite(2574 - m_sViewPointX, 3677 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[93]->PutTransSprite(3018 - m_sViewPointX, 3973 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
	}else if (m_cMapIndex == 27)	//Add Apocalypse map effect (fires in inferniaB)
	{	m_pEffectSpr[89]->PutTransSprite(1293 - m_sViewPointX, 3657 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[89]->PutTransSprite(944  - m_sViewPointX, 3881 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[89]->PutTransSprite(1325 - m_sViewPointX, 4137 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
		m_pEffectSpr[89]->PutTransSprite(1648 - m_sViewPointX, 3913 - m_sViewPointY, _tmp_iEffectFrame %12, 0);
	}
	//Snoopy: Add Apocalypse Gate and apocalypse map effects (if no Gate, m_iGatePositX will be -1...
	if (   (m_iGatePositX >= m_sViewPointX/32) && (m_iGatePositX <= m_sViewPointX/32 + 20)
		&& (m_iGatePositY >= m_sViewPointY/32) && (m_iGatePositY <= m_sViewPointY/32 + 15))
	{	m_pEffectSpr[101]->PutTransSprite(m_iGatePositX*32 - m_sViewPointX - 96, m_iGatePositY*32 - m_sViewPointY - 69, _tmp_iEffectFrame%30, dwTime);
	}
	if (iUpdateRet != 0)
		DrawDialogBoxs(msX, msY, msZ, cLB);

	if ((iUpdateRet != 0) && m_bInputStatus)
	{	if (((m_bIsDialogEnabled[7] == TRUE) && (m_stDialogBoxInfo[7].cMode == 1)) ||
			((m_bIsDialogEnabled[17] == TRUE) && (m_stDialogBoxInfo[17].cMode == 1)) )
		{}else m_DDraw.DrawShadowBox(0, 413, 639, 429);
		ShowReceivedString();
	}

	if (iUpdateRet != 0)
		ShowEventList(m_dwCurTime);

	if ( (iUpdateRet != 0) && (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM) &&
		 (m_pItemList[m_stMCursor.sSelectedObjectID] != NULL) )
	{	cItemColor = m_pItemList[m_stMCursor.sSelectedObjectID]->m_cItemColor;
		if (cItemColor != 0) {
			if ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos == DEF_EQUIPPOS_LHAND) ||
				(m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos == DEF_EQUIPPOS_RHAND) ||
				(m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite]->PutSpriteRGB(msX - m_stMCursor.sDistX, msY - m_stMCursor.sDistY,
					                                                  m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame,
																	  m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0],
																	  dwTime);
			}else
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite]->PutSpriteRGB(msX - m_stMCursor.sDistX, msY - m_stMCursor.sDistY,
					                                                  m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame,
																	  m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0],
																	  dwTime);
			}
		}else m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite]->PutSpriteFast(msX - m_stMCursor.sDistX, msY - m_stMCursor.sDistY,
					                                                  m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame, dwTime);

		char cStr1[64], cStr2[64], cStr3[64];
		int  iLoc;
		GetItemName(m_pItemList[m_stMCursor.sSelectedObjectID], cStr1, cStr2, cStr3);

		iLoc = 0;
		if (strlen(cStr1) != 0)
		{	if(m_bIsSpecial)
				PutString(msX, msY +25, cStr1, RGB(0,255,50), FALSE, 1);
			else
				PutString(msX, msY +25, cStr1, RGB(255,255,255), FALSE, 1);
			iLoc += 15;
		}
		if (strlen(cStr2) != 0)
		{	PutString(msX, msY +25 +iLoc, cStr2, RGB(150,150,150), FALSE, 1);
			iLoc += 15;
		}
		if (strlen(cStr3) != 0)
		{	PutString(msX, msY +25 +iLoc, cStr3, RGB(150,150,150), FALSE, 1);
			iLoc += 15;
		}
		if ( (m_pItemList[m_stMCursor.sSelectedObjectID]->m_sLevelLimit != 0) && ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_dwAttribute & 0x00000001) == 0) )
		{	wsprintf(G_cTxt, "%s: %d", DRAW_DIALOGBOX_SHOP24, m_pItemList[m_stMCursor.sSelectedObjectID]->m_sLevelLimit);//"·¹º§ Á¦ÇÑ: %d"
			PutString(msX, msY +25 +iLoc, G_cTxt, RGB(150,150,150), FALSE, 1);
			iLoc += 15;
		}
		if( (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos != DEF_EQUIPPOS_NONE) && (m_pItemList[m_stMCursor.sSelectedObjectID]->m_wWeight>=1100) )
		{	int	_wWeight = 0;
			if(m_pItemList[m_stMCursor.sSelectedObjectID]->m_wWeight%100) _wWeight = 1;
			wsprintf( G_cTxt, DRAW_DIALOGBOX_SHOP15, m_pItemList[m_stMCursor.sSelectedObjectID]->m_wWeight/100 + _wWeight);
			PutString(msX, msY +25 +iLoc, G_cTxt, RGB(150,150,150), FALSE, 1);
			iLoc += 15;
		}
		if (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos != DEF_EQUIPPOS_NONE)
		{	wsprintf(G_cTxt, UPDATE_SCREEN_ONGAME10, m_pItemList[m_stMCursor.sSelectedObjectID]->m_wCurLifeSpan);
			PutString(msX, msY +25 +iLoc, G_cTxt, RGB(150,150,150), FALSE, 1);
			iLoc += 15;
		}
		if ( iLoc == 15 )
		{	iLoc = 0;
			for ( int iTmp = 0 ; iTmp < DEF_MAXITEMS ; iTmp++ )
			{	if( m_pItemList[iTmp] != NULL )
				{	if( strcmp(m_pItemList[iTmp]->m_cName, m_pItemList[m_stMCursor.sSelectedObjectID]->m_cName ) == 0 ) iLoc++;
				}
			}
			if( iLoc > 1 )
			{	wsprintf(G_cTxt, DEF_MSG_TOTAL_NUMBER, iLoc);
				PutString(msX, msY + 40, G_cTxt, RGB(150,150,150), FALSE, 1);
	}	}	}

	//Snoopy: Add Apocalypse map effect (druncncity bubbles)
	if (m_cMapIndex == 25)
	{	bAddNewEffect(13, m_sViewPointX + rand() %640, m_sViewPointY + rand() %480, 0, 0, -1*(rand() %80), 1);
		DrawDruncncity();
	}

	//Snoopy adding Heldenian turret count:
	if (   (iUpdateRet != 0 ) && (m_iHeldenianAresdenLeftTower != -1)
		&& (memcmp(m_cCurLocation, "BtField", 7) == 0))
	{	wsprintf( G_cTxt, "Aresden Flags : %d",  m_iHeldenianAresdenFlags);
		PutString( 10, 140, G_cTxt, RGB(255,255,255) );
		wsprintf( G_cTxt, "Aresden Flags : %d",  m_iHeldenianElvineFlags);
		PutString( 10, 160, G_cTxt, RGB(255,255,255) );
		wsprintf( G_cTxt, "Aresden's rest building number : %d",  m_iHeldenianAresdenLeftTower);
		PutString( 10, 180, G_cTxt, RGB(255,255,255) );
		wsprintf( G_cTxt, "Elvine's rest building number : %d",  m_iHeldenianElvineLeftTower);
		PutString( 10, 200, G_cTxt, RGB(255,255,255) );
	}
	DrawTopMsg();

#ifdef _DEBUG
	wsprintf(G_cTxt, "M(%d,%d) T(%d,%d)", msX, msY, (m_sViewPointX + msX)/32, (m_sViewPointY + msY)/32);
	PutString(msX, msY +30, G_cTxt, RGB(255,255,255));
#endif

	// LogOut process
	if (m_cLogOutCount > 0)
	{	if ((dwTime - m_dwLogOutCountTime) > 1000)
		{	m_cLogOutCount--;
			m_dwLogOutCountTime = dwTime;
			wsprintf(G_cTxt, UPDATE_SCREEN_ONGAME13, m_cLogOutCount);
			AddEventList(G_cTxt, 10);
	}	}
	// Logout
	if (m_cLogOutCount == 0)
	{	delete m_pGSock;
		m_pGSock = NULL;
		m_bEscPressed = FALSE;

		PlaySound('E', 14, 5);
		if (m_bSoundFlag) m_pESound[38]->bStop();
		if ((m_bSoundFlag) && (m_bMusicStat == TRUE))
		{
			if (m_pBGM != NULL) m_pBGM->bStop();
		}
		if (strlen(G_cCmdLineTokenA) != 0)
			 ChangeGameMode(DEF_GAMEMODE_ONQUIT);
		else ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
		return;
	}

	// Restart Process
	if (m_cRestartCount > 0)
	{	if ((dwTime - m_dwRestartCountTime) > 1000)
		{	m_cRestartCount--;
			m_dwRestartCountTime = dwTime;
			wsprintf(G_cTxt, UPDATE_SCREEN_ONGAME14, m_cRestartCount); // "Restarting game...%d"
			AddEventList(G_cTxt, 10);
	}	}
	// Restart
	if (m_cRestartCount == 0)
	{	m_cRestartCount = -1;
		bSendCommand(MSGID_REQUEST_RESTART, NULL, NULL, NULL, NULL, NULL, NULL);
		return;
	}

	//Snoopy: Added diag "LEVEL UP" right down
	if (m_iLU_Point >0) PutString_SprFont(560, 390, "Level Up", 250, 250, 0);

	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_bIsObserverMode == TRUE)
	{	m_DDraw.PutPixel(msX, msY,   255,255,255);
		m_DDraw.PutPixel(msX+1, msY, 255,255,255);
		m_DDraw.PutPixel(msX-1, msY, 255,255,255);
		m_DDraw.PutPixel(msX, msY+1, 255,255,255);
		m_DDraw.PutPixel(msX, msY-1, 255,255,255);
	}
	else m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, m_stMCursor.sCursorFrame, dwTime);

	if( iUpdateRet == 0 ) m_sFrameCount++;
	else m_sFrameCount+=256;

	if( dwTime - m_dwFPStime > 500 )
	{	m_dwFPStime = dwTime;
		m_sFPS = m_sFrameCount>>7;
		if( m_sFPS < 10 ) m_sFPS += 6;
		m_sFrameCount = 0;
	}

	if( iUpdateRet != 0 )
	{	if( m_bShowFPS )
		{	wsprintf( G_cTxt, "fps : %d", m_sFPS );
			PutString( 10, 100, G_cTxt, RGB(255,255,255) );
		}
		if( m_DDraw.iFlip() == DDERR_SURFACELOST ) RestoreSprites();
	}

	// m_iPlayerStatus 0x000F
	iUpdateRet = m_pMapData->iObjectFrameCounter(m_cPlayerName, m_sViewPointX, m_sViewPointY);

	if ((bEffectFrameCounter() == TRUE) && (iUpdateRet == 0)) iUpdateRet = -1;
	if (iUpdateRet == 2)
	{	m_bCommandAvailable = TRUE;
		m_dwCommandTime = 0;
	}
	CommandProcessor( msX, msY, ((sDivX + sPivotX)*32 + sModX + msX - 17)/32 + 1, ((sDivY + sPivotY)*32 + sModY + msY - 17)/32 + 1, cLB, cRB);

	m_sViewPointX = sVPXsave;
	m_sViewPointY = sVPYsave;

	if (iUpdateRet > 0) CalcViewPoint();

	if (m_bIsObserverMode)
	{	if ((dwTime - m_dwObserverCamTime) > 25)
		{	m_dwObserverCamTime = dwTime;
			CalcViewPoint();
			iUpdateRet = -1;
	}	}

	if (iUpdateRet > 0)
	{	if (m_bDrawFlagDir == FALSE)
		{	m_iDrawFlag++;
			if (m_iDrawFlag >= 25)
			{	m_iDrawFlag = 25;
				m_bDrawFlagDir = TRUE;
			}
		}else
		{	m_iDrawFlag--;
			if (m_iDrawFlag < 0)
			{	m_iDrawFlag = 0;
				m_bDrawFlagDir = FALSE;
	}	}	}
	// iUpdateRet
}

void CGame::StartBGM()
{	if( m_bSoundFlag == FALSE )
	{
		if (m_pBGM != NULL)
		{	m_pBGM->bStop();
			delete m_pBGM;
			m_pBGM = NULL;
		}
		return;
	}
	char cWavFileName[32];
	ZeroMemory( cWavFileName, sizeof(cWavFileName) );
	if ((m_bIsXmas == TRUE) && (m_cWhetherEffectType >= 4)) strcpy( cWavFileName, "music\\Carol.wav" );
	else
	{	if (memcmp(m_cCurLocation, "aresden", 7) == 0) strcpy( cWavFileName, "music\\aresden.wav" );
		else if (memcmp(m_cCurLocation, "elvine", 6) == 0) strcpy( cWavFileName, "music\\elvine.wav" );
		else if (memcmp(m_cCurLocation, "dglv", 4) == 0) strcpy( cWavFileName, "music\\dungeon.wav" );
		else if (memcmp(m_cCurLocation, "middled1", 8) == 0) strcpy( cWavFileName, "music\\dungeon.wav" );
		else if (memcmp(m_cCurLocation, "middleland", 10) == 0) strcpy( cWavFileName, "music\\middleland.wav" );
		// Snoopy: new musics
		else if (memcmp(m_cCurLocation, "druncncity", 10) == 0) strcpy( cWavFileName, "music\\druncncity.wav" );
		else if (memcmp(m_cCurLocation, "inferniaA", 9) == 0) strcpy( cWavFileName, "music\\middleland.wav" );
		else if (memcmp(m_cCurLocation, "inferniaB", 9) == 0) strcpy( cWavFileName, "music\\middleland.wav" );
		else if (memcmp(m_cCurLocation, "maze", 4) == 0) strcpy( cWavFileName, "music\\dungeon.wav" );
		else if (memcmp(m_cCurLocation, "abaddon", 7) == 0) strcpy( cWavFileName, "music\\abaddon.wav" );
		else strcpy( cWavFileName, "music\\MainTm.wav" );
	}

	if (m_pBGM != NULL)
	{	if( strcmp( m_pBGM->m_cWavFileName, cWavFileName ) == 0 ) return;
		m_pBGM->bStop();
		delete m_pBGM;
		m_pBGM = NULL;
	}
	int iVolume = (m_cMusicVolume - 100)*20;
	if (iVolume > 0) iVolume = 0;
	if (iVolume < -10000) iVolume = -10000; //iVolume == Volume
	m_pBGM = new class CSoundBuffer(m_DSound.m_lpDS, m_DSound.m_DSCaps, cWavFileName, TRUE);
	m_pBGM->Play(TRUE, 0, iVolume);
}

void CGame::MotionResponseHandler(char * pData)
{
 WORD  * wp, wResponse;
 short * sp, sX, sY;
 char  * cp, cDir;
 int   * ip, iPreHP;
	//						          0 3        4 5						 6 7		8 9		   10	    11
	// Confirm Code(4) | MsgSize(4) | MsgID(4) | DEF_OBJECTMOVE_CONFIRM(2) | Loc-X(2) | Loc-Y(2) | Dir(1) | MapData ...
	// Confirm Code(4) | MsgSize(4) | MsgID(4) | DEF_OBJECTMOVE_REJECT(2)  | Loc-X(2) | Loc-Y(2)
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wResponse = *wp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	switch (wResponse) {
	case DEF_OBJECTMOTION_CONFIRM:
		m_cCommandCount--;
		break;

	case DEF_OBJECTMOTION_ATTACK_CONFIRM:
		m_cCommandCount--;
		break;

	case DEF_OBJECTMOTION_REJECT:

		if (m_iHP <= 0) return;

		sp = (short *)cp;
		m_sPlayerX = *sp;
		cp += 2;

		sp = (short *)cp;
		m_sPlayerY = *sp;
		cp += 2;

		m_cCommand = DEF_OBJECTSTOP;
		m_sCommX = m_sPlayerX;
		m_sCommY = m_sPlayerY;

		m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
						                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
										  m_iPlayerStatus, m_cPlayerName,
										  DEF_OBJECTSTOP, NULL, NULL, NULL);
		m_cCommandCount = 0;
		m_bIsGetPointingMode = FALSE;
		m_sViewDstX = m_sViewPointX = (m_sPlayerX-10)*32;
		m_sViewDstY = m_sViewPointY = (m_sPlayerY-7)*32;

		m_bIsRedrawPDBGS = TRUE;
		break;

	case DEF_OBJECTMOVE_CONFIRM:
		sp = (short *)cp;
		sX = *sp;
		cp += 2;
		sp = (short *)cp;
		sY = *sp;
		cp += 2;
		cDir = *cp;
		cp++;
		m_iSP = m_iSP - *cp;
		cp++;
		if( m_iSP < 0 ) m_iSP = 0;
		// v1.3
		//m_iOccupyStatus = (int)*cp;
		cp++;
		// v1.4
		iPreHP = m_iHP;
		ip = (int *)cp;
		m_iHP = *ip;
		cp += 4;

		if (m_iHP != iPreHP)
		{	if (m_iHP < iPreHP)
			{	wsprintf(G_cTxt, NOTIFYMSG_HP_DOWN, iPreHP - m_iHP);
				AddEventList(G_cTxt, 10);
				m_dwDamagedTime = timeGetTime();
				if ((m_cLogOutCount>0) && (m_bForceDisconn==FALSE))
				{	m_cLogOutCount = -1;
					AddEventList(MOTION_RESPONSE_HANDLER2, 10);
				}
			}else
			{	wsprintf(G_cTxt, NOTIFYMSG_HP_UP, m_iHP - iPreHP);
				AddEventList(G_cTxt, 10);
		}	}
		m_pMapData->ShiftMapData(cDir);
		_ReadMapData(sX, sY, cp);
		m_bIsRedrawPDBGS = TRUE;
		m_cCommandCount--;
		break;

	case DEF_OBJECTMOVE_REJECT:
		if (m_iHP <= 0) return;
		wp = (WORD *)cp;
		if (m_sPlayerObjectID != *wp) return;
		cp += 2;
		sp  = (short *)cp;
		m_sPlayerX = *sp;
		cp += 2;
		sp  = (short *)cp;
		m_sPlayerY = *sp;
		cp += 2;
		sp  = (short *)cp;
		m_sPlayerType = *sp;
		cp += 2;
		m_cPlayerDir = *cp;
		cp++;
		//memcpy(cName, cp, 10);
		cp += 10;
		sp = (short *)cp;
		m_sPlayerAppr1 = *sp;
		cp += 2;
		sp = (short *)cp;
		m_sPlayerAppr2 = *sp;
		cp += 2;
		sp = (short *)cp;
		m_sPlayerAppr3 = *sp;
		cp += 2;
		sp = (short *)cp;
		m_sPlayerAppr4 = *sp;
		cp += 2;
		ip = (int *)cp;
		m_iPlayerApprColor = *ip;
		cp += 4;
		ip = (int *)cp;
		m_iPlayerStatus = *ip;
		cp += 4;
		m_cCommand = DEF_OBJECTSTOP;
		m_sCommX = m_sPlayerX;
		m_sCommY = m_sPlayerY;
		m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
						                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, // v1.4
										  m_iPlayerStatus, m_cPlayerName,
										  DEF_OBJECTSTOP, NULL, NULL, NULL,
										  0, 7);
		m_cCommandCount = 0;
		m_bIsGetPointingMode = FALSE;
		m_sViewDstX = m_sViewPointX = (m_sPlayerX-10)*32;
		m_sViewDstY = m_sViewPointY = (m_sPlayerY-7)*32;
		m_bIsPrevMoveBlocked = TRUE;
		switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			PlaySound('C', 12, 0);
			break;
		case 4:
		case 5:
		case 6:
			PlaySound('C', 13, 0);
			break;
		}
		//m_bCommandAvailable = TRUE;
		break;
	}
}