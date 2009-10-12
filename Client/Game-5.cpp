void CGame::CommandProcessor(short msX, short msY, short indexX, short indexY, char cLB, char cRB)
{
 char   cDir, absX, absY, cName[12];
 short  sX, sY, sObjectType, tX, tY;
 int iObjectStatus;
 int    iRet;
 DWORD  dwTime = timeGetTime();
 WORD   wType = 0;
 int i;//, iFOE;
 char   cTxt[120];

 char  pDstName[21];
 short sDstOwnerType;
 int iDstOwnerStatus;

 BOOL  bGORet;
 // Fixed by Snoopy
	if ((m_bIsObserverCommanded == FALSE) && (m_bIsObserverMode == TRUE))
	{	if ((msX == 0) && (msY == 0) && (m_sViewDstX > 32*21) && (m_sViewDstY > 32*16)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 8, NULL, NULL, NULL, NULL);
		else
		if ((msX == 639) && (msY == 0) && (m_sViewDstX < 32*m_pMapData->m_sMapSizeX - 32*21) && (m_sViewDstY > 32*16)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 2, NULL, NULL, NULL, NULL);
		else
		if ((msX == 639) && (msY == 479) && (m_sViewDstX < 32*m_pMapData->m_sMapSizeX - 32*21) && (m_sViewDstY < 32*m_pMapData->m_sMapSizeY - 32*16)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 4, NULL, NULL, NULL, NULL);
		else
		if ((msX == 0) && (msY == 479)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 6, NULL, NULL, NULL, NULL);
		else
		if ((msX == 0) && (m_sViewDstX > 32*21)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 7, NULL, NULL, NULL, NULL);
		else
		if ((msX == 639) && (m_sViewDstX < 32*m_pMapData->m_sMapSizeX - 32*21)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 3, NULL, NULL, NULL, NULL);
		else
		if ((msY == 0) && (m_sViewDstY > 32*16)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 1, NULL, NULL, NULL, NULL);
		else
		if ((msY == 479) && (m_sViewDstY < 32*m_pMapData->m_sMapSizeY - 32*16)) bSendCommand(MSGID_REQUEST_PANNING, NULL, 5, NULL, NULL, NULL, NULL);
		else return;

		m_bIsObserverCommanded = TRUE;
		m_cArrowPressed = 0;
		return;
	}

	if (m_bIsObserverMode == TRUE) return;

	if (GetAsyncKeyState(VK_MENU)>>15) // [ALT]
		 m_bSuperAttackMode = TRUE;
	else m_bSuperAttackMode = FALSE;

	switch (m_stMCursor.cPrevStatus) {
	case DEF_CURSORSTATUS_NULL:
		if (cLB != 0)
		{	iRet = _iCheckDlgBoxFocus(msX, msY, 1);
			if (iRet == 1)
			{	m_stMCursor.cPrevStatus	= DEF_CURSORSTATUS_SELECTED;
				return;
			}else if (iRet == 0)
			{	m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_PRESSED;
				// Snoopy: Added Golden LevelUp
				if (   (msX >560) && (msX <620) && (msY>390) && (msY<405)
					&& (m_iLU_Point >0))
				{	if (m_bIsDialogEnabled[12] != TRUE)
					{	EnableDialogBox(12, NULL, NULL, NULL);
						PlaySound('E', 14, 5);
					}
					m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
					return;
				}
			}else if (iRet == -1)
			{	return;
			}
		}else if (cRB != 0)
		{	iRet = _iCheckDlgBoxFocus(msX, msY, 2);
			if (iRet == 1) return;
		}
		break;
	case DEF_CURSORSTATUS_PRESSED:
		if (cLB == 0) // Normal Click
		{	m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
		}
		break;
	case DEF_CURSORSTATUS_SELECTED:
		if (cLB == 0)
		{	if (   ((dwTime - m_stMCursor.dwSelectClickTime) < DEF_DOUBLECLICKTIME) 	// Double Click
				&& (msX == m_stMCursor.sClickX) && (msY == m_stMCursor.sClickY) )
			{	m_stMCursor.dwSelectClickTime = m_stMCursor.dwSelectClickTime;
				_bCheckDlgBoxDoubleClick(msX, msY);
			}else // Click
			{	_bCheckDlgBoxClick(msX, msY);
				m_stMCursor.sClickX = msX;
				m_stMCursor.sClickY = msY;
			}
			m_stMCursor.dwSelectClickTime = dwTime;
			m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
			if (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM)
			{	_bCheckDraggingItemRelease(msX, msY);
				m_stMCursor.cSelectedObjectType = NULL;
				m_stMCursor.sSelectedObjectID   = NULL;
			}
			return;
		}
		if (cLB != 0) 			// v2.05 01-11-30
		{	if ((m_pMapData->bIsTeleportLoc(m_sPlayerX, m_sPlayerY) == TRUE) && (m_cCommandCount == 0)) goto CP_SKIPMOUSEBUTTONSTATUS;

			if ((m_stMCursor.sPrevX != msX)	|| (m_stMCursor.sPrevY != msY))
			{	m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_DRAGGING;
				m_stMCursor.sPrevX = msX;
				m_stMCursor.sPrevY = msY;
				if ( (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
					 ((m_stMCursor.sSelectedObjectID == 30) || (m_stMCursor.sSelectedObjectID == 29)) )
				{	m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
				}
				if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
					(m_stMCursor.sSelectedObjectID == 7) && (m_stDialogBoxInfo[7].cMode == 1))
				{	EndInputString();
					m_stDialogBoxInfo[7].cMode = 20;
				}
				// Query Drop Item Amount
				if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
					(m_stMCursor.sSelectedObjectID == 17) && (m_stDialogBoxInfo[17].cMode == 1))
					// Guild Menu
				{	EndInputString();
					m_stDialogBoxInfo[17].cMode = 20;
				}
				return;
			}
			if ((m_cCommand == DEF_OBJECTMOVE) || (m_cCommand == DEF_OBJECTRUN)) goto MOTION_COMMAND_PROCESS;
			return;
		}
		break;
	case DEF_CURSORSTATUS_DRAGGING:
		if (cLB != 0)
		{	if ((m_pMapData->bIsTeleportLoc(m_sPlayerX, m_sPlayerY) == TRUE) && (m_cCommandCount == 0)) goto CP_SKIPMOUSEBUTTONSTATUS;
			if (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX)
			{	m_stDialogBoxInfo[m_stMCursor.sSelectedObjectID].sX = msX - m_stMCursor.sDistX;
				m_stDialogBoxInfo[m_stMCursor.sSelectedObjectID].sY = msY - m_stMCursor.sDistY;
			}
			m_stMCursor.sPrevX = msX;
			m_stMCursor.sPrevY = msY;

			if ((m_cCommand == DEF_OBJECTMOVE) || (m_cCommand == DEF_OBJECTRUN)) goto MOTION_COMMAND_PROCESS;
			return;
		}
		if (cLB == 0) {
			switch (m_stMCursor.cSelectedObjectType) {
			case DEF_SELECTEDOBJTYPE_DLGBOX:
				if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
					(m_stMCursor.sSelectedObjectID == 7) && (m_stDialogBoxInfo[7].cMode == 20))
				{	sX = m_stDialogBoxInfo[7].sX;
					sY = m_stDialogBoxInfo[7].sY;
					StartInputString(sX + 75, sY + 140, 21, m_cGuildName);
					m_stDialogBoxInfo[7].cMode = 1;
				}

				if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
					(m_stMCursor.sSelectedObjectID == 17) && (m_stDialogBoxInfo[17].cMode == 20))
				{	// Query Drop Item Amount
					sX = m_stDialogBoxInfo[17].sX;
					sY = m_stDialogBoxInfo[17].sY;
					StartInputString(sX + 40, sY + 57, 11, m_cAmountString);
					m_stDialogBoxInfo[17].cMode = 1;
				}

				if ( m_stMCursor.sSelectedObjectID == 9 )
				{	if( msX < 320 ) m_stDialogBoxInfo[9].sX = 0;
					else m_stDialogBoxInfo[9].sX = 640 - m_stDialogBoxInfo[9].sSizeX;
					if( msY < 213 ) m_stDialogBoxInfo[9].sY = 0;
					else m_stDialogBoxInfo[9].sY = 427 - m_stDialogBoxInfo[9].sSizeY;
				}

				m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
				m_stMCursor.cSelectedObjectType = NULL;
				m_stMCursor.sSelectedObjectID   = NULL;
				break;

			case DEF_SELECTEDOBJTYPE_ITEM:
				_bCheckDraggingItemRelease(msX, msY);
				m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
				m_stMCursor.cSelectedObjectType = NULL;
				m_stMCursor.sSelectedObjectID   = NULL;
				break;

			default:
				m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_NULL;
				m_stMCursor.cSelectedObjectType = NULL;
				m_stMCursor.sSelectedObjectID   = NULL;
				break;
			}
			return;
		}
		break;
	}

CP_SKIPMOUSEBUTTONSTATUS:;
	if (m_bCommandAvailable == FALSE) return;
	if ( (dwTime - m_dwCommandTime) < 300 )
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
	if (m_iHP <= 0) return;

	if (m_sDamageMove != 0)
	{	m_cCommand = DEF_OBJECTDAMAGEMOVE;
		goto MOTION_COMMAND_PROCESS;
	}

	if ((m_pMapData->bIsTeleportLoc(m_sPlayerX, m_sPlayerY) == TRUE) && (m_cCommandCount == 0))
		RequestTeleportAndWaitData();

	// indexX, indexY
	if (cLB != 0) // Mouse Left button
	{	if (m_bIsGetPointingMode == TRUE)
		{	if ((m_sMCX != 0) || (m_sMCY != 0))
				 PointCommandHandler(m_sMCX, m_sMCY);
			else PointCommandHandler(indexX, indexY);

			m_bCommandAvailable  = FALSE;
			m_dwCommandTime = timeGetTime();
			m_bIsGetPointingMode = FALSE;
			return;
		}

		m_pMapData->bGetOwner(m_sMCX, m_sMCY-1, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID); // v1.4
		//m_pMapData->m_pData[dX][dY].m_sItemSprite
		if (memcmp(m_cMCName, m_cPlayerName, 10) == 0 && ( sObjectType <= 6 || m_pMapData->m_pData[m_sPlayerX-m_pMapData->m_sPivotX][m_sPlayerY-m_pMapData->m_sPivotY].m_sItemSprite != 0 ))
		{//if (memcmp(m_cMCName, m_cPlayerName, 10) == 0 && ( sObjectType <= 6 || m_pMapData->m_pData[15][15].m_sItemSprite != 0 )) {
		 //if (memcmp(m_cMCName, m_cPlayerName, 10) == 0 && sObjectType <= 6){
			if ((m_sPlayerType >= 1) && (m_sPlayerType <= 6)/* && ((m_sPlayerAppr2 & 0xF000) == 0)*/)
			{	m_cCommand = DEF_OBJECTGETITEM;
				m_sCommX = m_sPlayerX;
				m_sCommY = m_sPlayerY;
			}
		}else
		{	if( memcmp(m_cMCName, m_cPlayerName, 10) == 0 ) m_sMCY -= 1;
			if ((m_sMCX != 0) && (m_sMCY != 0)) // m_sMCX, m_sMCY
			{	if (m_bCtrlPressed == TRUE)
				{	m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
					if ( (iObjectStatus & 0x10) != 0) return;
					if ((sObjectType == 15) || (sObjectType == 20) || (sObjectType == 24)) return;
					m_stMCursor.sCursorFrame = 3;
					absX = abs(m_sPlayerX - m_sMCX);
					absY = abs(m_sPlayerY - m_sMCY);
					if ((absX <= 1) && (absY <= 1))
					{	wType = _iGetAttackType();
						m_cCommand = DEF_OBJECTATTACK;
						m_sCommX = m_sMCX;
						m_sCommY = m_sMCY;
					}else if ( (absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
							&& ((sObjectType == 66)||(sObjectType == 73)||(sObjectType == 81)||(sObjectType == 91)))
					{	wType = _iGetAttackType();
						m_cCommand = DEF_OBJECTATTACK;
						m_sCommX = m_sMCX;
						m_sCommY = m_sMCY;
					}else // Pas au corp à corp
					{	switch (_iGetWeaponSkillType()) {
						case 6: // Bow
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
							wType = _iGetAttackType();
							break;

						case 5: // OpenHand
						case 7: // SS
							if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
							{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
								{	if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
									{	m_cCommand = DEF_OBJECTATTACKMOVE;
										wType = _iGetAttackType();
									}else
									{	m_cCommand = DEF_OBJECTRUN;
										GetPlayerTurn();
									}
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
								}else
								{	m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
								}
							}else
							{	if (   (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)
									&& (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
									 m_cCommand = DEF_OBJECTRUN;	// Staminar
								else m_cCommand = DEF_OBJECTMOVE;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
								GetPlayerTurn();
							}
							break;

						case 8: // LS
							if (   (absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
								&& (_iGetAttackType() != 30)) // Crit without StormBlade
							{	wType = _iGetAttackType();
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
							}else if ( (absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
								&& (_iGetAttackType() == 30))  // Crit with StormBlade (by Snoopy)
							{	wType = _iGetAttackType();
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
							}else if ( (absX <= 3) && (absY <= 3)
								&& (_iGetAttackType() == 5))  // Normal hit with StormBlade (by Snoopy)
							{	wType = _iGetAttackType();
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
							}else // Swing
							{	if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0))
									&& (_iGetAttackType() != 5)) // no Dash possible with StormBlade
								{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
									{	if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
										{	m_cCommand = DEF_OBJECTATTACKMOVE;
											wType = _iGetAttackType();
										}else
										{	m_cCommand = DEF_OBJECTRUN;
											GetPlayerTurn();
										}
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
									}else
									{	m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
								}else
								{	if (   (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)
										&& (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
										 m_cCommand = DEF_OBJECTRUN;
									else m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
							}	}
							break;

						case 9: // Fencing
							if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE))
							{	m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
								wType = _iGetAttackType();
							}
							else {
								if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0))) {
									if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)) {
										if (m_cSkillMastery[_iGetWeaponSkillType()] == 100) {
											m_cCommand = DEF_OBJECTATTACKMOVE;
											wType = _iGetAttackType();
										}
										else {
											m_cCommand = DEF_OBJECTRUN;
											GetPlayerTurn();
										}
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
									}
									else {
										m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
								}
								else {
									if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
										(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
										 m_cCommand = DEF_OBJECTRUN;
									else m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
								}
							}
							break;

						case 10: // Axe
							if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE))
							{	m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
								wType = _iGetAttackType();
							}else
							{	if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
								{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
									{	if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
										{	m_cCommand = DEF_OBJECTATTACKMOVE;
											wType = _iGetAttackType();
										}else
										{	m_cCommand = DEF_OBJECTRUN;
											GetPlayerTurn();
										}
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
									}else
									{	m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
								}else
								{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
										(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
										 m_cCommand = DEF_OBJECTRUN;
									else m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
							}	}
							break;
						case 14: // Hammer
							if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
								wType = _iGetAttackType();
							}
							else {
								if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0))) {
									if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)) {
										if (m_cSkillMastery[_iGetWeaponSkillType()] == 100) {
											m_cCommand = DEF_OBJECTATTACKMOVE;
											wType = _iGetAttackType();
										}
										else {
											m_cCommand = DEF_OBJECTRUN;
											GetPlayerTurn();
										}
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
									}
									else {
										m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
								}
								else {
									if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
										(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
										 m_cCommand = DEF_OBJECTRUN;
									else m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
							}	}
							break;
						case 21: // Wand
							if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
								wType = _iGetAttackType();
							}
							else {
								if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0))) {
									if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)) {
										if (m_cSkillMastery[_iGetWeaponSkillType()] == 100) {
											m_cCommand = DEF_OBJECTATTACKMOVE;
											wType = _iGetAttackType();
										}
										else {
											m_cCommand = DEF_OBJECTRUN;
											GetPlayerTurn();
										}
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
									}
									else {
										m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
								}
								else {
									if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
										(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
										 m_cCommand = DEF_OBJECTRUN;
									else m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
								}
							}
							break;
						}
					}
				}else // CTRL not pressed
				{	m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
					if (sObjectType >= 10 || ((sObjectType >= 1) && (sObjectType <= 6)))
					{	switch (sObjectType) { 	// CLEROTH - NPC TALK
						case 15: // ShopKeeper-W°
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 5, 11, 1);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 15;
							/*	break;
							}*/
							break;

						case 19: // Gandlf
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 0, 16, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 19;
							/*	break;
						 	}*/
							break;

						case 20: // Howard
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 0, 14, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 20;
								m_stDialogBoxInfo[39].sV3 = 20;
								m_stDialogBoxInfo[39].sV4 = m_wCommObjectID;
								m_stDialogBoxInfo[39].sV5 = m_sMCX;
								m_stDialogBoxInfo[39].sV6 = m_sMCY;
							/*	break;
						 	}*/
							break;

						case 24: // Tom
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 5, 11, 2);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 24;
								m_stDialogBoxInfo[39].sV3 = 24;
								m_stDialogBoxInfo[39].sV4 = m_wCommObjectID;
								m_stDialogBoxInfo[39].sV5 = m_sMCX;
								m_stDialogBoxInfo[39].sV6 = m_sMCY;
							/*	break;
						 	}*/
							break;

						case 25: // William
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 0, 13, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 25;
							/*	break;
						 	}*/
							break;

						case 26: // Kennedy
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 0, 7, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 26;
							/*	break;
						 	}*/
							break;

						case 21: // Guard
							if ((_iGetFOE(iObjectStatus)>=0) && (!m_bIsCombatMode))
							{	EnableDialogBox(20, 4, NULL, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 21;
							}
							break;
						case 67: // McGaffin
						case 68: // Perry
						case 69: // Devlin
							if (!m_bIsCombatMode)
							{	EnableDialogBox(20, 4, NULL, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = sObjectType;
							}
							break;

						case 32: // Unicorn
							if (!m_bIsCombatMode)
							{	EnableDialogBox(20, 4, NULL, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 32;
							}
							break;

						case 90: // Snoopy: Gail
							/*switch (cName[0]) {
							case '1':*/
								EnableDialogBox(20, 6, 0, NULL);
								tX = msX - 117;
								tY = msY - 50;
								if (tX < 0) tX = 0;
								if ((tX + 235) > 639) tX = 639 - 235;
								if (tY < 0) tY = 0;
								if ((tY + 100) > 479) tY = 479 - 100;
								m_stDialogBoxInfo[20].sX  = tX;
								m_stDialogBoxInfo[20].sY  = tY;
								m_stDialogBoxInfo[20].sV3 = 90;
								/*break;
						 	}*/
							break;

						default: // Other mobs
							if ( _iGetFOE(iObjectStatus) >= 0 ) break;
							if ( (sObjectType>=1) && (sObjectType<=6) && (m_bForceAttack==FALSE) ) break;
							absX = abs(m_sPlayerX - m_sMCX);
							absY = abs(m_sPlayerY - m_sMCY);
							if ((absX <= 1) && (absY <= 1))
							{	wType = _iGetAttackType();
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
							}else if ( (absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
							&& ((sObjectType == 66)||(sObjectType == 73)||(sObjectType == 81)||(sObjectType == 91)))
							{	wType = _iGetAttackType();
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
							}else // Normal hit from a range.
							{	switch (_iGetWeaponSkillType()) {
								case 6: // Bow
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									wType = _iGetAttackType();
									break;

								case 5: // Boxe
								case 7: // SS
									if (   (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)
										&& (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
										m_cCommand = DEF_OBJECTRUN;
									else m_cCommand = DEF_OBJECTMOVE;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									GetPlayerTurn();
									break;

								case 8: // LS
									if (   (absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
										&& (_iGetAttackType() != 30)) // Crit without StormBlade by Snoopy
									{	if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
											 m_cCommand = DEF_OBJECTATTACKMOVE;
										else m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}else if ((absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
										   && (_iGetAttackType() == 30)) // Crit with StormBlade by Snoopy
									{	if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
											 m_cCommand = DEF_OBJECTATTACKMOVE;
										else m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}else if ((absX <= 3) && (absY <= 3)
										   && (_iGetAttackType() == 5)) // Normal hit with StormBlade by Snoopy
									{	m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}else
									{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
											(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
											m_cCommand = DEF_OBJECTRUN;
										else m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
									break;

								case 9: // Fencing
									if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE))
									{	if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
											 m_cCommand = DEF_OBJECTATTACKMOVE;
										else m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}else
									{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
											(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
											m_cCommand = DEF_OBJECTRUN;
										else m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
									break;

								case 10: //
									if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
										if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
											 m_cCommand = DEF_OBJECTATTACKMOVE;
										else m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}
									else {
										if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
											(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
											m_cCommand = DEF_OBJECTRUN;
										else m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
									break;
								case 14: //
									if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
										if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
											 m_cCommand = DEF_OBJECTATTACKMOVE;
										else m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}
									else {
										if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
											(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
											m_cCommand = DEF_OBJECTRUN;
										else m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
									break;
								case 21: //
									if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
										if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
											 m_cCommand = DEF_OBJECTATTACKMOVE;
										else m_cCommand = DEF_OBJECTATTACK;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										wType = _iGetAttackType();
									}
									else {
										if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
											(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
											m_cCommand = DEF_OBJECTRUN;
										else m_cCommand = DEF_OBJECTMOVE;
										m_sCommX = m_sMCX;
										m_sCommY = m_sMCY;
										GetPlayerTurn();
									}
									break;
								}
							}
							break;
						}
					}
					else {
						if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
							(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
							 m_cCommand = DEF_OBJECTRUN;
						else m_cCommand = DEF_OBJECTMOVE;
						m_sCommX = m_sMCX;
						m_sCommY = m_sMCY;
						GetPlayerTurn();
					}
				}
			}else
			{	if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
					(m_sPlayerType >= 1) && (m_sPlayerType <= 6))
					 m_cCommand = DEF_OBJECTRUN;
				else m_cCommand = DEF_OBJECTMOVE;
				m_sCommX = indexX;
				m_sCommY = indexY;
				GetPlayerTurn();
			}
		}
	}else if (cRB != 0) // Mouse Right button
	{	m_cCommand = DEF_OBJECTSTOP;
		if (m_bIsGetPointingMode == TRUE)
		{	m_bIsGetPointingMode = FALSE;
			AddEventList(COMMAND_PROCESSOR1, 10);
		}
		if (m_bCommandAvailable == FALSE) return;
		if (m_cCommandCount >= 6) return;

		if ((m_sMCX != 0) && (m_sMCY != 0))
		{	absX = abs(m_sPlayerX - m_sMCX);
			absY = abs(m_sPlayerY - m_sMCY);
			if( absX==0 && absY==0 ) return;

			if (m_bCtrlPressed == TRUE)
			{	m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
				if ( (iObjectStatus & 0x10) != 0) return;
				if ((sObjectType == 15) || (sObjectType == 20) || (sObjectType == 24)) return;

				if ((absX <= 1) && (absY <= 1))
				{	wType = _iGetAttackType();
					m_cCommand = DEF_OBJECTATTACK;
					m_sCommX = m_sMCX;
					m_sCommY = m_sMCY;
				}else if ( (absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
							&& ((sObjectType == 66)||(sObjectType == 73)||(sObjectType == 81)||(sObjectType == 91)))
				{	wType = _iGetAttackType();
					m_cCommand = DEF_OBJECTATTACK;
					m_sCommX = m_sMCX;
					m_sCommY = m_sMCY;
				}else
				{	switch (_iGetWeaponSkillType()) {
					case 6: // Bow
						m_cCommand = DEF_OBJECTATTACK;
						m_sCommX = m_sMCX;
						m_sCommY = m_sMCY;
						wType = _iGetAttackType();
						break;

					case 5: // Boxe
					case 7: // SS
						break;

					case 8: // LS
						if (   (absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
							&& (_iGetAttackType() != 30)) // without StormBlade by Snoopy
						{	wType = _iGetAttackType();
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
						}else if (   (absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
							&& (_iGetAttackType() == 30)) // with stormBlade crit by Snoopy
						{	wType = _iGetAttackType();
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
						}else if (   (absX <= 3) && (absY <= 3)
							&& (_iGetAttackType() == 5)) // with stormBlade no crit by Snoopy
						{	wType = _iGetAttackType();
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
						}
						break;

					case 9: // Fencing
						if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
							wType = _iGetAttackType();
						}
						break;

					case 10: //
						if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
							wType = _iGetAttackType();
						}
						break;

					case 14: //
						if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
							wType = _iGetAttackType();
						}
						break;
					case 21: //
						if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
							wType = _iGetAttackType();
						}
						break;
					}
				}
			}else // CTRL not pressed
			{	absX = abs(m_sPlayerX - m_sMCX);
				absY = abs(m_sPlayerY - m_sMCY);
				m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
				if (sObjectType >= 10 || ((sObjectType >= 1) && (sObjectType <= 6))) {
					switch (sObjectType) {
					case 15:
					case 19:
					case 20:
					case 24:
					case 25:
					case 26: // npcs
						break;

					default: // All "normal mobs"
						if ( _iGetFOE(iObjectStatus) >= 0 ) break;
						if ( (sObjectType>=1) && (sObjectType<=6) && (m_bForceAttack==FALSE) ) break;
						if ((absX <= 1) && (absY <= 1))
						{	wType = _iGetAttackType();
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
						}else if ( (absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
							&& ((sObjectType == 66)||(sObjectType == 73)||(sObjectType == 81)||(sObjectType == 91)))
						{	wType = _iGetAttackType();
							m_cCommand = DEF_OBJECTATTACK;
							m_sCommX = m_sMCX;
							m_sCommY = m_sMCY;
						}else //
						{	switch (_iGetWeaponSkillType()) {
							case 6: // Bow
								m_cCommand = DEF_OBJECTATTACK;
								m_sCommX = m_sMCX;
								m_sCommY = m_sMCY;
								wType = _iGetAttackType();
								break;

							case 5: // Boxe
							case 7: // SS
								break;

							case 8: // LS
								if (   (absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
									&& (_iGetAttackType() != 30)) // crit without StormBlade by Snoopy
								{	wType = _iGetAttackType();
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
								}else if (   (absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)
									&& (_iGetAttackType() == 30)) // with stormBlade crit by Snoopy
								{	wType = _iGetAttackType();
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
								}else if (   (absX <= 3) && (absY <= 3)
									&& (_iGetAttackType() == 5)) // with stormBlade no crit by Snoopy
								{	wType = _iGetAttackType();
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
								}
								break;

							case 9: // fencing
								if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									wType = _iGetAttackType();
								}
								break;

							case 10: //
								if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									wType = _iGetAttackType();
								}
								break;
							case 14: // hammer
								if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									wType = _iGetAttackType();
								}
								break;
							case 21: // wand
								if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE)) {
									m_cCommand = DEF_OBJECTATTACK;
									m_sCommX = m_sMCX;
									m_sCommY = m_sMCY;
									wType = _iGetAttackType();
								}
								break;
						}	}
						break;
			}	}	}
		}else
		{	cDir = m_Misc.cGetNextMoveDir(m_sPlayerX, m_sPlayerY, indexX, indexY);
			if (m_iHP <= 0) return;
			if (cDir == 0) return;
			if (m_cPlayerDir  == cDir) return;
			ClearSkillUsingStatus();
			m_cPlayerDir = cDir;
			bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTSTOP, m_cPlayerDir, NULL, NULL, NULL, NULL);

			m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
							                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
											  m_iPlayerStatus, m_cPlayerName,
											  m_cCommand, NULL, NULL, NULL, 0,
											  10);
			m_bCommandAvailable = FALSE;
			m_dwCommandTime = timeGetTime();
			return;
	}	}

MOTION_COMMAND_PROCESS:;

	if (m_cCommand != DEF_OBJECTSTOP)
	{	if (m_iHP <= 0) return;
		if (m_cCommandCount == 5) AddEventList(COMMAND_PROCESSOR2, 10, FALSE);
		if (m_bCommandAvailable == FALSE) return;
		if (m_cCommandCount >= 6) return;

		if ((m_sPlayerType >= 0) && (m_sPlayerType > 6))
		{	switch (m_cCommand) {
			case DEF_OBJECTRUN:
			case DEF_OBJECTMAGIC:
			case DEF_OBJECTGETITEM:
				m_cCommand = DEF_OBJECTSTOP;
				break;
		}	}

		ClearSkillUsingStatus();

		if (m_sDamageMove != 0)
		{	m_cCommand = DEF_OBJECTDAMAGEMOVE;
			m_sCommX = m_sPlayerX;
			m_sCommY = m_sPlayerY;

			switch (m_sDamageMove) {
			case 1: m_sCommY--; break;
			case 2: m_sCommX++; m_sCommY--; break;
			case 3: m_sCommX++; break;
			case 4: m_sCommX++; m_sCommY++; break;
			case 5: m_sCommY++; break;
			case 6: m_sCommX--; m_sCommY++; break;
			case 7: m_sCommX--; break;
			case 8: m_sCommX--; m_sCommY--; break;
			}

			for (i = 1; i < DEF_MAXCHATMSGS; i++)
			if (m_pChatMsgList[i] == NULL)
			{	ZeroMemory(cTxt, sizeof(cTxt));
				if (m_sDamageMoveAmount > 0)
					wsprintf(cTxt, "-%dPts", m_sDamageMoveAmount); //pts
				else strcpy(cTxt, "Critical!");

				int iFontType;
				if ((m_sDamageMoveAmount >= 0) && (m_sDamageMoveAmount < 12))		iFontType = 21;
				else if ((m_sDamageMoveAmount >= 12) && (m_sDamageMoveAmount < 40)) iFontType = 22;
				else if ((m_sDamageMoveAmount >= 40) || (m_sDamageMoveAmount < 0))	iFontType = 23;

				m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
				m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;

				if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == FALSE) {
					delete m_pChatMsgList[i];
					m_pChatMsgList[i] = NULL;
				}
				break;
			}
			m_sDamageMove = 0;
		}

		switch (m_cCommand) {
		case DEF_OBJECTRUN:
		case DEF_OBJECTMOVE:
		case DEF_OBJECTDAMAGEMOVE: // v1.43

			if( m_bParalyze ) return;
			bGORet = m_pMapData->bGetOwner(m_sCommX, m_sCommY, pDstName, &sDstOwnerType, &iDstOwnerStatus, &m_wCommObjectID); // v1.4

			if ((m_sPlayerX == m_sCommX) && (m_sPlayerY == m_sCommY))
				m_cCommand = DEF_OBJECTSTOP;
			else if ( (abs(m_sPlayerX - m_sCommX) <= 1) && (abs(m_sPlayerY - m_sCommY) <= 1) &&
				      (bGORet == TRUE) && (sDstOwnerType != NULL) )
				m_cCommand = DEF_OBJECTSTOP;
			else if((abs(m_sPlayerX - m_sCommX) <= 2) && (abs(m_sPlayerY - m_sCommY) <= 2) &&
				(m_pMapData->m_tile[m_sCommX][m_sCommY].m_bIsMoveAllowed == FALSE))
				m_cCommand = DEF_OBJECTSTOP;
			else
			{	if( m_cCommand == DEF_OBJECTMOVE )
				{	if(m_bRunningMode || m_bShiftPressed) m_cCommand = DEF_OBJECTRUN;
				}
				if( m_cCommand == DEF_OBJECTRUN )
				{	if( (m_bRunningMode == FALSE) && (m_bShiftPressed == FALSE) ) m_cCommand = DEF_OBJECTMOVE;
					if( m_iSP < 1 ) m_cCommand = DEF_OBJECTMOVE;
				}


				// Snoopy: Illusion Movement
				if ((m_bIllusionMVT == TRUE)&&(m_cCommand != DEF_OBJECTDAMAGEMOVE))
				{	cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, TRUE, TRUE);
				}
				if (cDir != 0)
				{	m_cPlayerDir = cDir;
					bSendCommand(MSGID_COMMAND_MOTION, m_cCommand, cDir, NULL, NULL, NULL, NULL);
					switch (cDir) {
					case 1:	m_sPlayerY--; break;
					case 2:	m_sPlayerY--; m_sPlayerX++;	break;
					case 3:	m_sPlayerX++; break;
					case 4:	m_sPlayerX++; m_sPlayerY++;	break;
					case 5:	m_sPlayerY++; break;
					case 6:	m_sPlayerX--; m_sPlayerY++;	break;
					case 7:	m_sPlayerX--; break;
					case 8:	m_sPlayerX--; m_sPlayerY--;	break;
					}
					m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
						                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, // v1.4
										  m_iPlayerStatus, m_cPlayerName,
										  m_cCommand, NULL, NULL, NULL);
					m_bCommandAvailable = FALSE;
					m_dwCommandTime = timeGetTime();
					m_iPrevMoveX = m_sPlayerX;
					m_iPrevMoveY = m_sPlayerY;
			}	}

			if (m_cCommand == DEF_OBJECTDAMAGEMOVE)
			{	m_bIsGetPointingMode = FALSE;
				m_iPointCommandType	 = -1;
				m_stMCursor.sCursorFrame = 0;
				ClearSkillUsingStatus();
				m_cCommand = DEF_OBJECTSTOP;
			}
			break;

		case DEF_OBJECTATTACK:
			cDir = m_Misc.cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY);
			// Snoopy: Illusion movement
			if (m_bIllusionMVT == TRUE)
			{	cDir +=4;
				if (cDir >8) cDir -=8;
			}
			if (cDir != 0)
			{	if ((wType == 2) || (wType == 25))
				{	if (_bCheckItemByType(DEF_ITEMTYPE_ARROW) == FALSE)
						wType = 0;
				}
				if (wType >= 20)
				{	m_iSuperAttackLeft--;
					if (m_iSuperAttackLeft < 0) m_iSuperAttackLeft = 0;
				}
				m_cPlayerDir = cDir;
				bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTATTACK, cDir, m_sCommX, m_sCommY, wType, NULL, m_wCommObjectID);
				m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
					                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
									  m_iPlayerStatus, m_cPlayerName,
									  DEF_OBJECTATTACK,
									  m_sCommX - m_sPlayerX, m_sCommY - m_sPlayerY, wType);
				m_bCommandAvailable = FALSE;
				m_dwCommandTime = timeGetTime();
			}
			m_cCommand = DEF_OBJECTSTOP;
			break;

		case DEF_OBJECTATTACKMOVE:
			if( m_bParalyze ) return;
			bGORet = m_pMapData->bGetOwner(m_sCommX, m_sCommY, pDstName, &sDstOwnerType, &iDstOwnerStatus, &m_wCommObjectID);
			if ((m_sPlayerX == m_sCommX) && (m_sPlayerY == m_sCommY))
				m_cCommand = DEF_OBJECTSTOP;
			else if ( (abs(m_sPlayerX - m_sCommX) <= 1) && (abs(m_sPlayerY - m_sCommY) <= 1) &&
				      (bGORet == TRUE) && (sDstOwnerType != NULL) )
				m_cCommand = DEF_OBJECTSTOP;
			else
			{	cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, TRUE);
				// Snoopy: Illusion mvt
				if (m_bIllusionMVT == TRUE)
				{	cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, TRUE, TRUE);
				}
				if (cDir != 0)
				{	m_cPlayerDir = cDir;
					bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTATTACKMOVE, cDir, m_sCommX, m_sCommY, wType, NULL, m_wCommObjectID);
					switch (cDir) {
					case 1:	m_sPlayerY--; break;
					case 2:	m_sPlayerY--; m_sPlayerX++;	break;
					case 3:	m_sPlayerX++; break;
					case 4:	m_sPlayerX++; m_sPlayerY++;	break;
					case 5:	m_sPlayerY++; break;
					case 6:	m_sPlayerX--; m_sPlayerY++;	break;
					case 7:	m_sPlayerX--; break;
					case 8:	m_sPlayerX--; m_sPlayerY--;	break;
					}

					m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
						                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
										  m_iPlayerStatus, m_cPlayerName,
										  m_cCommand, m_sCommX - m_sPlayerX, m_sCommY - m_sPlayerY, wType);
					m_bCommandAvailable = FALSE;
					m_dwCommandTime = timeGetTime();
					m_iPrevMoveX = m_sPlayerX;
					m_iPrevMoveY = m_sPlayerY;
			}	}
			m_cCommand = DEF_OBJECTSTOP;
			break;

		case DEF_OBJECTGETITEM:
			bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTGETITEM, m_cPlayerDir, NULL, NULL, NULL, NULL);
			m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
				                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
								  m_iPlayerStatus, m_cPlayerName,
								  DEF_OBJECTGETITEM, NULL, NULL, NULL);
			m_bCommandAvailable = FALSE;
			m_cCommand = DEF_OBJECTSTOP;
			break;

		case DEF_OBJECTMAGIC:
			bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTMAGIC, m_cPlayerDir, m_iCastingMagicType, NULL, NULL, NULL);
			m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
				                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
								  m_iPlayerStatus, m_cPlayerName,
								  DEF_OBJECTMAGIC, m_iCastingMagicType, NULL, NULL);
			m_bCommandAvailable = FALSE;
			m_dwCommandTime = timeGetTime();
			m_bIsGetPointingMode = TRUE;
			m_cCommand = DEF_OBJECTSTOP;
			_RemoveChatMsgListByObjectID(m_sPlayerObjectID);
			for (i = 1; i < DEF_MAXCHATMSGS; i++)
			if (m_pChatMsgList[i] == NULL)
			{	ZeroMemory(cTxt, sizeof(cTxt));
				wsprintf(cTxt, "%s!", m_pMagicCfgList[m_iCastingMagicType]->m_cName);
				m_pChatMsgList[i] = new class CMsg(41, cTxt, timeGetTime());
				m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;
				m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i);
				return;
			}
			break;

		default:
			break;
	}	}
}

void CGame::DrawDialogBox_Bank(short msX, short msY, short msZ, char cLB)
{	short sX, sY, szX;
	int  i, iTotalLines, iPointerLoc, iLoc;
	double d1, d2, d3;
	char cItemColor, cStr1[64], cStr2[64], cStr3[64];
	BOOL bFlag = FALSE;

	sX = m_stDialogBoxInfo[14].sX;
	sY = m_stDialogBoxInfo[14].sY;
	szX = m_stDialogBoxInfo[14].sSizeX - 5;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 21);
	ZeroMemory( cStr1, sizeof(cStr1) );
	ZeroMemory( cStr2, sizeof(cStr2) );
	ZeroMemory( cStr3, sizeof(cStr3) );
	iLoc = 45;

	switch (m_stDialogBoxInfo[14].cMode) {
	case -1:
		PutString(sX + 30 + 15, sY + 70, DRAW_DIALOGBOX_BANK1, RGB(0,0,0));//"
		PutString(sX + 30 + 15, sY + 85, DRAW_DIALOGBOX_BANK2, RGB(0,0,0));//"
		break;

	case 0:
		for (i = 0; i < m_stDialogBoxInfo[14].sV1; i++)
		if ((m_pBankList[i + m_stDialogBoxInfo[14].sView] != NULL) && ((i + m_stDialogBoxInfo[14].sView) < DEF_MAXBANKITEMS)) {
			GetItemName(m_pBankList[i + m_stDialogBoxInfo[14].sView], cStr1, cStr2, cStr3);
			if ((msX > sX + 30) && (msX < sX + 210) && (msY >= sY + 110 + i*15) && (msY <= sY + 124 + i*15))
			{
				bFlag = TRUE;

				PutAlignedString(sX, sX+szX, sY + 110 + i*15, cStr1, 255, 255, 255 );
				if(m_bIsSpecial)
					PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr1, 0, 255, 50 );
				else
					PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr1, 255, 255, 255 );

				if( strlen(cStr2) > 0 )
				{
					iLoc += 15;
					PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr2, 150, 150, 150 );
				}
				if( strlen(cStr3) > 0 )
				{
					iLoc += 15;
					PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr3, 150, 150, 150 );
				}
				if( m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sLevelLimit != 0 && m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_dwAttribute & 0x00000001 )
				{
					iLoc += 15;
					wsprintf( G_cTxt, "%s: %d", DRAW_DIALOGBOX_SHOP24, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sLevelLimit );
					PutAlignedString(sX + 70, sX + szX, sY + iLoc, G_cTxt, 150, 150, 150 );
				}

				if( (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos != DEF_EQUIPPOS_NONE) && (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_wWeight>=1100) )
				{
					iLoc += 15;
					int		_wWeight = 0;
					if(m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_wWeight%100)				_wWeight = 1;
					wsprintf( G_cTxt, DRAW_DIALOGBOX_SHOP15, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_wWeight/100 + _wWeight);

					PutAlignedString(sX + 70, sX + szX, sY + iLoc, G_cTxt, 150, 150, 150 );
				}

				cItemColor = m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cItemColor;
				if( cItemColor == 0 )
				{	 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSprite]->PutSpriteFast(sX+60, sY+68, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSpriteFrame, m_dwCurTime);
				}else
				{	if (   (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
						|| (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
						|| (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
					{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSprite]->PutSpriteRGB(sX+60, sY+68, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSpriteFrame,
																			m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
					}else m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSprite]->PutSpriteRGB(sX+60, sY+68, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSpriteFrame,
																			m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
				}
			}else
			{	if (m_bIsSpecial)
					PutAlignedString(sX, sX+szX, sY + 110 + i*15, cStr1, 0, 255, 50 );
				else
					PutAlignedString(sX, sX+szX, sY + 110 + i*15, cStr1, 0, 0, 0 );
		}	}

		iTotalLines = 0;
		for (i = 0; i < DEF_MAXBANKITEMS; i++)
		if (m_pBankList[i] != NULL) iTotalLines++;
		if (iTotalLines > m_stDialogBoxInfo[14].sV1)
		{	d1 = (double)m_stDialogBoxInfo[14].sView;
			d2 = (double)(iTotalLines-m_stDialogBoxInfo[14].sV1);
			d3 = (274.0f * d1)/d2;
			iPointerLoc = (int)d3;
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX+242, sY + iPointerLoc + 35, 7);
		}
		else iPointerLoc = 0;
		if (cLB != 0 && (iGetTopDialogBoxIndex() == 14) && iTotalLines > m_stDialogBoxInfo[14].sV1) {
			if ((msX >= sX + 230) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
				d1 = (double)(msY -(sY+35));
				d2 = (double)(iTotalLines-m_stDialogBoxInfo[14].sV1);
				d3 = (d1 * d2)/274.0f;
				m_stDialogBoxInfo[14].sView = (int)(d3+0.5);
			}
			else if ((msX >= sX + 230) && (msX <= sX + 260) && (msY > sY + 10) && (msY < sY + 40)) m_stDialogBoxInfo[14].sView = 0;
		}
		else m_stDialogBoxInfo[14].bIsScrollSelected = FALSE;
		if( iGetTopDialogBoxIndex() == 14 && msZ != 0 )
		{
			if( iTotalLines > 50 ) m_stDialogBoxInfo[14].sView = m_stDialogBoxInfo[14].sView - msZ/30;
			else {//
				if( msZ > 0 ) m_stDialogBoxInfo[14].sView--;
				if( msZ < 0 ) m_stDialogBoxInfo[14].sView++;
			}
			m_DInput.m_sZ = 0;
		}
		if( iTotalLines > m_stDialogBoxInfo[14].sV1 && m_stDialogBoxInfo[14].sView > iTotalLines-m_stDialogBoxInfo[14].sV1 ) m_stDialogBoxInfo[14].sView = iTotalLines-m_stDialogBoxInfo[14].sV1;
		if( iTotalLines <= m_stDialogBoxInfo[14].sV1 ) m_stDialogBoxInfo[14].sView = 0;
		if( m_stDialogBoxInfo[14].sView < 0 ) m_stDialogBoxInfo[14].sView = 0;
		if( bFlag == FALSE )
		{
			PutAlignedString(sX, sX+szX, sY + 45, DRAW_DIALOGBOX_BANK3);
			PutAlignedString(sX, sX+szX, sY + 60, DRAW_DIALOGBOX_BANK4);
			PutAlignedString(sX, sX+szX, sY + 75, DRAW_DIALOGBOX_BANK5);
		}
		break;
	}
}

void CGame::DrawDialogBox_FeedBackCard(short msX, short msY)
{}

void CGame::DrawDialogBox_Character(short msX, short msY)
{short sX, sY, sSprH, sFrame;
 int i, iR, iG, iB, iSkirtDraw = 0;
 char cTxt2[120], cEquipPoiStatus[DEF_MAXITEMEQUIPPOS];
 char  cItemColor, cCollison;

	sX = m_stDialogBoxInfo[1].sX;
	sY = m_stDialogBoxInfo[1].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 0, FALSE, m_bDialogTrans);

	ZeroMemory(G_cTxt, sizeof(G_cTxt));
	strcpy(G_cTxt, m_cPlayerName);
	strcat(G_cTxt, " : ");

	if (m_iPKCount > 0) {
		ZeroMemory(cTxt2, sizeof(cTxt2));
		wsprintf(cTxt2, DRAW_DIALOGBOX_CHARACTER1, m_iPKCount);
		strcat(G_cTxt, cTxt2);
	}

	ZeroMemory(cTxt2, sizeof(cTxt2));
	wsprintf(cTxt2, DRAW_DIALOGBOX_CHARACTER2, m_iContribution);
	strcat(G_cTxt, cTxt2);
	PutAlignedString(sX +24, sX +252, sY+52, G_cTxt, 45,20,20);
	ZeroMemory(G_cTxt, sizeof(G_cTxt));

	if( m_bCitizen == FALSE )
	{	strcpy( G_cTxt, DRAW_DIALOGBOX_CHARACTER7); // "Traveller"
	}else
	{	if(m_bHunter)
		{	if (m_bAresden)
				 strcat(G_cTxt, DEF_MSG_ARECIVIL); //
			else strcat(G_cTxt, DEF_MSG_ELVCIVIL); // "Elvine Civilian"
		}else
		{	if (m_bAresden)
				 strcat(G_cTxt, DEF_MSG_ARESOLDIER); //
			else strcat(G_cTxt, DEF_MSG_ELVSOLDIER); //
		}
		if( m_iGuildRank >= 0 )
		{	strcat( G_cTxt, "(" );
			strcat( G_cTxt, m_cGuildName );
			if( m_iGuildRank == 0 ) strcat( G_cTxt, DEF_MSG_GUILDMASTER1 );
			else strcat( G_cTxt, DEF_MSG_GUILDSMAN1 ); // " Guildsman)"
	}	}

	PutAlignedString(sX, sX+275, sY+69, G_cTxt, 45,25,25);

	int iTemp;
	// Level
	wsprintf(G_cTxt, "%d", m_iLevel);
	PutAlignedString(sX+180, sX+250, sY + 106, G_cTxt, 45,25,25);
	// Exp
	wsprintf(G_cTxt, "%d", m_iExp);
	PutAlignedString(sX+180, sX+250, sY + 125, G_cTxt, 45,25,25);
	// Next.Exp
	wsprintf(G_cTxt, "%d", iGetLevelExp(m_iLevel+1));
	PutAlignedString(sX+180, sX+250, sY + 142, G_cTxt, 45,25,25);

	// Hp
	iTemp = m_iHP;
	wsprintf(G_cTxt, "%d/%d", iTemp, m_iVit*3 + m_iLevel*2 + (m_iStr + m_iAngelicStr)/2);
	PutAlignedString(sX+180, sX+250, sY + 173, G_cTxt, 45,25,25);

	// Mp
	iTemp = m_iMP;
	wsprintf(G_cTxt, "%d/%d", iTemp, (m_iMag + m_iAngelicMag)*2 + m_iLevel*2 + (m_iInt + m_iAngelicInt)/2);
	PutAlignedString(sX+180, sX+250, sY + 191, G_cTxt, 45,25,25);

	// Sp
	iTemp = m_iSP;
	wsprintf(G_cTxt, "%d/%d", iTemp, m_iLevel*2 + (m_iStr + m_iAngelicStr)*2);
	PutAlignedString(sX+180, sX+250, sY + 208, G_cTxt, 45,25,25);

	// Max.Load
	wsprintf(G_cTxt, "%d/%d", (_iCalcTotalWeight()/100), ((m_iStr + m_iAngelicStr)*5 + m_iLevel*5));
	PutAlignedString(sX+180, sX+250, sY + 240, G_cTxt, 45,25,25);

	// Enemy Kills
	wsprintf(G_cTxt, "%d", m_iEnemyKillCount);
	PutAlignedString(sX+180, sX+250, sY + 257, G_cTxt, 45,25,25);

	// Str
	if (m_iAngelicStr == 0)
	{	wsprintf(G_cTxt, "%d", m_iStr);
		PutAlignedString(sX+48, sX+82, sY + 285, G_cTxt, 45,25,25);
	}else
	{	wsprintf(G_cTxt, "%d", m_iStr + m_iAngelicStr);
		PutAlignedString(sX+48, sX+82, sY + 285, G_cTxt, 0,0,192);
	}

	// Vit
	wsprintf(G_cTxt, "%d", m_iVit);
	PutAlignedString(sX+218, sX+251, sY + 285, G_cTxt, 45,25,25);

	// Dex
	if (m_iAngelicDex == 0)
	{	wsprintf(G_cTxt, "%d", m_iDex);
		PutAlignedString(sX+48, sX+82, sY +302, G_cTxt, 45,25,25);
	}else
	{	wsprintf(G_cTxt, "%d", m_iDex + m_iAngelicDex);
		PutAlignedString(sX+48, sX+82, sY +302, G_cTxt, 0,0,192);
	}

	// Int
	if (m_iAngelicInt == 0)
	{	wsprintf(G_cTxt, "%d", m_iInt);
		PutAlignedString(sX+135, sX+167, sY +285, G_cTxt, 45,25,25);
	}else
	{	wsprintf(G_cTxt, "%d", m_iInt + m_iAngelicInt);
		PutAlignedString(sX+135, sX+167, sY +285, G_cTxt, 0,0,192);
	}

	// Mag
	if (m_iAngelicMag == 0)
	{	wsprintf(G_cTxt, "%d", m_iMag);
		PutAlignedString(sX+135, sX+167, sY +302, G_cTxt, 45,25,25);
	}else
	{	wsprintf(G_cTxt, "%d", m_iMag + m_iAngelicMag);
		PutAlignedString(sX+135, sX+167, sY +302, G_cTxt, 0,0,192);
	}

	// Chr
	wsprintf(G_cTxt, "%d", m_iCharisma);
	PutAlignedString(sX+218, sX+251, sY +302, G_cTxt, 45,25,25);

	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
		cEquipPoiStatus[i] = -1;

	for (i = 0; i < DEF_MAXITEMS; i++)
	{	if ((m_pItemList[i] != NULL) && (m_bIsItemEquipped[i] == TRUE))	cEquipPoiStatus[ m_pItemList[i]->m_cEquipPos ] = i;
	}
	if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
	{	cCollison = -1;
		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 0]->PutSpriteFast(sX + 171, sY + 290, m_sPlayerType-1, m_dwCurTime);
		if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] == -1)
		{	_GetHairColorRGB(((m_sPlayerAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18]->PutSpriteRGB(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x0F00) >> 8, iR, iG, iB, m_dwCurTime);
		}

		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19]->PutSpriteFast(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x000F), m_dwCurTime);

		if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BACK] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 41, sY + 137, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 41, sY + 137, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 41, sY + 137, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 41, sY + 137, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison( sX + 41, sY + 137, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BACK;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_PANTS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_PANTS;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_ARMS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_ARMS;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BOOTS;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BODY] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BODY;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_FULLBODY;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_LHAND] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 90, sY + 170, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 90, sY + 170, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 90, sY + 170, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 90, sY + 170, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 90, sY + 170, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_LHAND;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_RHAND] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 57, sY + 186, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 57, sY + 186, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_RHAND;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 57, sY + 186, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 57, sY + 186, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_TWOHAND;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_NECK] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 35, sY + 120, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 35, sY + 120, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_NECK;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 32, sY + 193, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 32, sY + 193, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_RFINGER;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 98, sY + 182, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 98, sY + 182, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_LFINGER;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_HEAD] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 72, sY + 135, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 72, sY + 135, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 72, sY + 135, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 72, sY + 135, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 72, sY + 135, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_HEAD;
		}
		if( cCollison != -1 )
		{
			sSprH      = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSpriteFrame;
			if( cCollison == DEF_EQUIPPOS_HEAD )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 72, sY + 135, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_RFINGER )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 32, sY + 193, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_LFINGER )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 98, sY + 182, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_NECK )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 35, sY + 120, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_TWOHAND )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 57, sY + 186, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_RHAND )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 57, sY + 186, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_LHAND )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 90, sY + 170, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_BODY )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_FULLBODY )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_BOOTS )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_ARMS )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_PANTS )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_BACK )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 41, sY + 137, sFrame, m_dwCurTime);
		}
	}else if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6))
	{	cCollison = -1;
		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 40]->PutSpriteFast(sX + 171, sY + 290, m_sPlayerType-4, m_dwCurTime);

		if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] == -1)
		{	_GetHairColorRGB(((m_sPlayerAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18 +40]->PutSpriteRGB(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x0F00) >> 8, iR, iG, iB, m_dwCurTime);
		}

		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19 +40]->PutSpriteFast(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x000F), m_dwCurTime);

		if ((cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1))
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			if ((sSprH == 12) && (sFrame == 0)) iSkirtDraw = 1;
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BACK] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 45, sY + 143, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 45, sY + 143, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 45, sY + 143, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 45, sY + 143, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 45, sY + 143, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BACK;
		}

		if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) && (iSkirtDraw == 1))
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BOOTS;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_PANTS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_PANTS;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_ARMS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_ARMS;
		}

		if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) && (iSkirtDraw == 0))
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BOOTS;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_BODY] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_BODY;
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_FULLBODY;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_LHAND] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 84, sY + 175, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 84, sY + 175, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 84, sY + 175, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 84, sY + 175, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 84, sY + 175, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_LHAND;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_cItemColor;
			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_RHAND] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 60, sY + 191, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 60, sY + 191, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_RHAND;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_cItemColor;
			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 60, sY + 191, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 60, sY + 191, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_TWOHAND;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_NECK] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 35, sY + 120, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 35, sY + 120, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_NECK;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 32, sY + 193, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 32, sY + 193, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_RFINGER;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] ] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 98, sY + 182, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 98, sY + 182, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_LFINGER;
		}

		if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
			cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_cItemColor;

			if (m_bIsItemDisabled[ cEquipPoiStatus[DEF_EQUIPPOS_HEAD]] == FALSE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteFast(sX + 72, sY +139, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutSpriteRGB(sX + 72, sY +139, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite2(sX + 72, sY +139, sFrame, m_dwCurTime);
				else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSpriteRGB(sX + 72, sY +139, sFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], m_dwCurTime);
			}
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 72, sY + 139, sFrame, msX, msY ) )
				cCollison = DEF_EQUIPPOS_HEAD;
		}
		if( cCollison != -1 )
		{	sSprH      = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSpriteFrame;
			if( cCollison == DEF_EQUIPPOS_HEAD )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 72, sY + 139, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_RFINGER )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 32, sY + 193, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_LFINGER )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 98, sY + 182, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_NECK )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 35, sY + 120, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_TWOHAND )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 60, sY + 191, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_RHAND )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 60, sY + 191, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_LHAND )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 84, sY + 175, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_BODY )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_FULLBODY )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_BOOTS )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_ARMS )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_PANTS )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
			else if( cCollison == DEF_EQUIPPOS_BACK )
				m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->PutTransSprite(sX + 45, sY + 143, sFrame, m_dwCurTime);
		}
	}

	// v2.05
	if ((msX >= sX + 15) && (msX <= sX + 15 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 15, sY +340, 5, FALSE, m_bDialogTrans);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 15, sY +340, 4, FALSE, m_bDialogTrans);

	if ((msX >= sX + 98) && (msX <= sX + 98 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 98, sY +340, 45, FALSE, m_bDialogTrans);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 98, sY +340, 44, FALSE, m_bDialogTrans);

	if ((msX >= sX + 180) && (msX <= sX + 180 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 180, sY +340, 11, FALSE, m_bDialogTrans);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 180, sY +340, 10, FALSE, m_bDialogTrans);
}

// 3.51 Level Up Dialog - Diuuude
void CGame::DrawDialogBox_LevelUpSetting(short msX, short msY)
{
 short sX, sY, szX;
 DWORD dwTime = m_dwCurTime;
 char cTxt[120];
 int iStats;
	sX = m_stDialogBoxInfo[12].sX;
	sY = m_stDialogBoxInfo[12].sY;
	szX = m_stDialogBoxInfo[12].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX+16, sY+100, 4);

	PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_LEVELUP_SETTING1);
	PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_LEVELUP_SETTING2);

	// Points Left - Display in green if > 0
	PutString(sX + 20,  sY + 85, DRAW_DIALOGBOX_LEVELUP_SETTING3, RGB(0,0,0));
	wsprintf(cTxt, "%d", m_iLU_Point);
	if (m_iLU_Point > 0)
	{	PutString(sX + 73,  sY + 102, cTxt, RGB(0,255,0));
	}else
	{	PutString(sX + 73,  sY + 102, cTxt, RGB(0,0,0));
	}
	// Strength
	PutString(sX + 24, sY + 125, DRAW_DIALOGBOX_LEVELUP_SETTING4, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iStr);
	PutString(sX + 109, sY + 125, cTxt, RGB(25,35,25));
	iStats = m_iStr + m_cLU_Str;
	wsprintf(cTxt, "%d", iStats);
	if (iStats != m_iStr)
	{	PutString(sX + 162, sY + 125, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 125, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_iStr < 200))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 127, 5, dwTime);
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_cLU_Str > 0))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 127, 6, dwTime);

	// Vitality
	PutString(sX + 24, sY + 144, DRAW_DIALOGBOX_LEVELUP_SETTING5, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iVit);
	PutString(sX + 109, sY + 144, cTxt, RGB(25,35,25));
	iStats = m_iVit + m_cLU_Vit;
	wsprintf(cTxt, "%d", iStats);
	if (iStats != m_iVit)
	{	PutString(sX + 162, sY + 144, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 144, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_iVit < 200))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 146, 5, dwTime);
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_cLU_Vit > 0))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 146, 6, dwTime);

	// Dexterity
	PutString(sX + 24, sY + 163, DRAW_DIALOGBOX_LEVELUP_SETTING6, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iDex);
	PutString(sX + 109, sY + 163, cTxt, RGB(25,35,25));
	iStats = m_iDex + m_cLU_Dex;
	wsprintf(cTxt, "%d", iStats);
	if (iStats != m_iDex)
	{	PutString(sX + 162, sY + 163, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 163, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_iDex < 200))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 165, 5, dwTime);
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_cLU_Dex > 0))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 165, 6, dwTime);

	// Intelligence
	PutString(sX + 24, sY + 182, DRAW_DIALOGBOX_LEVELUP_SETTING7, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iInt);
	PutString(sX + 109, sY + 182, cTxt, RGB(25,35,25));
	iStats = m_iInt + m_cLU_Int;
	wsprintf(cTxt, "%d", iStats);
	if (iStats != m_iInt)
	{	PutString(sX + 162, sY + 182, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 182, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_iInt < 200))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 184, 5, dwTime);
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_cLU_Int > 0))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 184, 6, dwTime);

	// Magic
	PutString(sX + 24, sY + 201, DRAW_DIALOGBOX_LEVELUP_SETTING8, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iMag);
	PutString(sX + 109, sY + 201, cTxt, RGB(25,35,25));
	iStats = m_iMag + m_cLU_Mag;
	wsprintf(cTxt, "%d", iStats);
	if (iStats != m_iMag)
	{	PutString(sX + 162, sY + 201, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 201, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_iMag < 200))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 203, 5, dwTime);
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_cLU_Mag > 0))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 203, 6, dwTime);

	// Charisma
	PutString(sX + 24, sY + 220, DRAW_DIALOGBOX_LEVELUP_SETTING9, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iCharisma);
	PutString(sX + 109, sY + 220, cTxt, RGB(25,35,25));
	iStats = m_iCharisma + m_cLU_Char;
	wsprintf(cTxt, "%d", iStats);
	if (iStats != m_iCharisma)
	{	PutString(sX + 162, sY + 220, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 220, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_iCharisma < 200))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 222, 5, dwTime);
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_cLU_Char > 0))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 222, 6, dwTime);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
	if ((m_cLU_Str == 0)&&(m_cLU_Vit == 0)&&(m_cLU_Dex == 0)&&(m_cLU_Int == 0)&&(m_cLU_Mag == 0)&&(m_cLU_Char == 0))
	{	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	if (m_iLU_Point <= 0) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 21);
		}else
		{	if (m_iLU_Point <= 0) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 20);
	}	}
}

void CGame::DrawDialogBox_CityHallMenu(short msX, short msY)
{
 short sX, sY, szX;
 char cTxt[120];

	sX = m_stDialogBoxInfo[13].sX;
	sY = m_stDialogBoxInfo[13].sY;
	szX = m_stDialogBoxInfo[13].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 18);//CityHall Menu Text

	switch (m_stDialogBoxInfo[13].cMode) {
	case 0:
		// citizenship req
		if (m_bCitizen == FALSE)
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
				 PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 255,255,255);	//"
			else PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 4,0,50);		//"
		}else    PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 65,65,65);			//"

		if (m_iRewardGold > 0)
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
				 PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 255,255,255);	//"
			else PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 4,0,50);		//"
		}else    PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 65,65,65);			//"

		// 3.51 Cityhall Menu - Request Hero's Items - Diuuude
		if ((m_iEnemyKillCount >= 100) && (m_iContribution >= 10))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
				 PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 4,0,50);
		}else    PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 65,65,65);

		// Cancel quest
		if (m_stQuest.sQuestType != NULL)
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
				 PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 4,0,50);//"
		}else    PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 65,65,65);//"

		// change playmode
		if ( (m_bIsCrusadeMode==FALSE) && m_bCitizen && (m_iPKCount==0))
		{	if (m_bHunter==TRUE)
			{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
					PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 255,255,255);
				else
					PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 4,0,50);
			}else if(m_iLevel < 100)
			{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
					 PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 255,255,255);
				else
					PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 4,0,50);
			}else // Disable...
					PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 65,65,65);
		}else       PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 65,65,65);

		// Teleport menu
		if ( (m_bIsCrusadeMode==FALSE) && m_bCitizen && (m_iPKCount==0))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
				 PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 255,255,255);//"Teleporting to dungeon level 2."
			else PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 4,0,50);
		}else    PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 65,65,65);

		//Change crusade role
		if ( m_bIsCrusadeMode && m_bCitizen )
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 220) && (msY < sY + 220))
				 PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 255,255,255);//"Change the crusade assignment."
			else PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 4,0,50);//"
		}else    PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 65,65,65);//"

		PutAlignedString(sX, sX + szX, sY + 270, DRAW_DIALOGBOX_CITYHALL_MENU17);//"Select an Item you want."

		break;

	case 1: // become citizen warning
		PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU18, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU19, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU20, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU21, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 140,DRAW_DIALOGBOX_CITYHALL_MENU22, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 155,DRAW_DIALOGBOX_CITYHALL_MENU23, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 170,DRAW_DIALOGBOX_CITYHALL_MENU24, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 200,DRAW_DIALOGBOX_CITYHALL_MENU25, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 215,DRAW_DIALOGBOX_CITYHALL_MENU26, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 230,DRAW_DIALOGBOX_CITYHALL_MENU27, 55,25,25);//"

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;

	case 2: // Offering Citizenship.
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU28, 55,25,25);//"
		break;

	case 3: //Congratulations!! You acquired Citizenship"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU29, 55,25,25);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 4: //Failed on acquiring citizenship!"
		PutAlignedString(sX, sX + szX, sY + 80,  DRAW_DIALOGBOX_CITYHALL_MENU30, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 100, DRAW_DIALOGBOX_CITYHALL_MENU31, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 115, DRAW_DIALOGBOX_CITYHALL_MENU32, 55,25,25);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 5: //The prize gold for your"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU33, 55,25,25);//"
		wsprintf(cTxt, DRAW_DIALOGBOX_CITYHALL_MENU34, m_iRewardGold);//"
		PutAlignedString(sX, sX + szX, sY + 140, cTxt, 55,25,25);
		PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU35, 55,25,25);//"

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;

	case 7:// 3.51 Cityhall Menu - Request Hero's Items - Diuuude
		PutAlignedString(sX, sX + szX, sY + 60,  DRAW_DIALOGBOX_CITYHALL_MENU46, 255,255,255);// Here are the Hero's Item aivable :
		// Hero's Cape (EK 300)
		if (m_iEnemyKillCount >= 300)
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 110))
				 PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 65,65,65);// Disabled Mode
		// Hero's Helm (EK 150 - Contrib 20)
		if ((m_iEnemyKillCount >= 150) && (m_iContribution >= 20))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 125) && (msY < sY + 140))
				 PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 65,65,65);// Disabled Mode
		// Hero's Cap (EK 100 - Contrib 20)
		if ((m_iEnemyKillCount >= 100) && (m_iContribution >= 20))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 155) && (msY < sY + 170))
				 PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 65,65,65);// Disabled Mode
		// Hero's Armor (EK 300 - Contrib 30)
		if ((m_iEnemyKillCount >= 300) && (m_iContribution >= 30))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 185) && (msY < sY + 200))
				 PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 65,65,65);// Disabled Mode
		// Hero's Robe (EK 200 - Contrib 20)
		if ((m_iEnemyKillCount >= 200) && (m_iContribution >= 20))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 215) && (msY < sY + 230))
				 PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 65,65,65);// Disabled Mode
		// Hero's Hauberk (EK 100 - Contrib 10)
		if ((m_iEnemyKillCount >= 100) && (m_iContribution >= 10))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 245) && (msY < sY + 260))
				 PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 65,65,65);// Disabled Mode
		// Hero's Leggings (EK 150 - Contrib 15)
		if ((m_iEnemyKillCount >= 150) && (m_iContribution >= 15))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 275) && (msY < sY + 290))
				 PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 255,255,255);// On mouse over Mode
			else PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 4,0,50);// Normal Mode
		}
		else PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 65,65,65);// Disabled Mode
		break;

	case 8: // cancel current quest?
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU54, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU55, 55,25,25);//"

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;

	case 9: // You are civilian/ combatant now
		if( m_bHunter )
		{	PutAlignedString(sX, sX + szX, sY +  53, DRAW_DIALOGBOX_CITYHALL_MENU57, 200,200,25);//"
		}else
		{	PutAlignedString(sX, sX + szX, sY +  53, DRAW_DIALOGBOX_CITYHALL_MENU58, 200,200,25);//"
		}
		PutAlignedString(sX, sX + szX, sY +  78, DRAW_DIALOGBOX_CITYHALL_MENU59, 55,25,25);//"

		PutString(sX + 35, sY + 108, DRAW_DIALOGBOX_CITYHALL_MENU60, RGB(220,130,45));//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU61, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU62, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU63, 55,25,25);//"
		PutString(sX + 35, sY +  177, DRAW_DIALOGBOX_CITYHALL_MENU64, RGB(220,130,45));//"
		PutAlignedString(sX, sX + szX, sY + 194, DRAW_DIALOGBOX_CITYHALL_MENU65, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 209, DRAW_DIALOGBOX_CITYHALL_MENU66, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 224, DRAW_DIALOGBOX_CITYHALL_MENU67, 55,25,25);//"

		PutAlignedString(sX, sX + szX, sY + 252, DRAW_DIALOGBOX_CITYHALL_MENU68, 55,25,25);//"
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;

	case 10: // TP 2nd screen
		if( m_iTeleportMapCount > 0 )
		{	PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_CITYHALL_MENU69, 55,25,25);//"Teleporting to dungeon level 2."
			PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU70, 55,25,25);//"5000Gold is required"
			PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU71, 55,25,25);//"to teleport to dungeon level 2."
			PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU72, 55,25,25);//"Would you like to teleport?"
			PutString2(sX + 35, sY + 250, DRAW_DIALOGBOX_CITYHALL_MENU72_1, 55,25,25);//"Civilians cannot go some area."
			for( int i=0 ; i<m_iTeleportMapCount ; i++ )
			{	ZeroMemory( cTxt, sizeof(cTxt) );
				GetOfficialMapName( m_stTeleportList[i].mapname, cTxt );
				wsprintf( G_cTxt, DRAW_DIALOGBOX_CITYHALL_MENU77, cTxt, m_stTeleportList[i].iCost );
				if( (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i*15) && (msY <= sY + 144 + i*15) )
					 PutAlignedString(sX, sX + szX, sY + 130 + i*15, G_cTxt, 255, 255, 255);
				else PutAlignedString(sX, sX + szX, sY + 130 + i*15, G_cTxt,  250,  250,  0);
			}
		}else if( m_iTeleportMapCount == -1 )
		{	PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU73, 55,25,25);//"Now it's searching for possible area"
			PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_CITYHALL_MENU74, 55,25,25);//"to teleport."
			PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU75, 55,25,25);//"Please wait for a moment."
		}else
		{	PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU76, 55,25,25);//"There is no area that you can teleport."
		}
		break;

	case 11: //drajwer - ask for tooking hero mantle
		PutAlignedString(sX,sX+szX-1,sY+125,m_cTakeHeroItemName, 55,25,25);
		PutAlignedString(sX+1,sX+szX,sY+125,m_cTakeHeroItemName, 55,25,25);
		PutAlignedString(sX,sX+szX,sY+260,DRAW_DIALOGBOX_CITYHALL_MENU46A, 55,25,25); // would you like..
		if (   (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX)
			&& (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		   DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);
		if (   (msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX)
			&& (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		   DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
 	break;
	}
}
/*********************************************************************************************************************
**  void CGame::DrawDialogBox_ConfirmExchange(short msX, short msY)	(snoopy)										**
**  description			:: paints the trade windows	Added confirmation window in v3.51								**
**********************************************************************************************************************/
void CGame::DrawDialogBox_ConfirmExchange(short msX, short msY)
{short sX, sY;
	sX = m_stDialogBoxInfo[41].sX;
	sY = m_stDialogBoxInfo[41].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);
	switch (m_stDialogBoxInfo[41].cMode) {
	case 1: // Question
		PutString(sX + 35, sY + 30, "Do you really want to exchange?", RGB(4,0,50));
		PutString(sX + 36, sY + 30, "Do you really want to exchange?", RGB(4,0,50));

		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55 , 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55 , 18);

		if ((msX >= sX + 170 ) && (msX <= sX + 170 + DEF_BTNSZX ) && (msY >= sY + 55 ) && (msY <= sY + 55 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55 , 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55 , 2);
		break;

	case 2: // Waiting for response
		PutString(sX + 45, sY + 36, "Waiting for response...", RGB(4,0,50));
		PutString(sX + 46, sY + 36, "Waiting for response...", RGB(4,0,50));
		break;
	}
}

/*********************************************************************************************************************
**  void CGame::DrawDialogBox_Exchange(short msX, short msY)	(snoopy)											**
**  description			:: paints the trade windows																	**
**********************************************************************************************************************/
void CGame::DrawDialogBox_Exchange(short msX, short msY)
{
 short sX, sY, szX, sXadd;
 DWORD dwTime = m_dwCurTime;
 char cItemColor, cTxt[120], cTxt2[128];
 char cNameStr[120], cSubStr1[120], cSubStr2[120];
 int iLoc, i;

	sX = m_stDialogBoxInfo[27].sX;
	sY = m_stDialogBoxInfo[27].sY ;
	szX = m_stDialogBoxInfo[27].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWEXCHANGE, sX, sY, 0);
	switch (m_stDialogBoxInfo[27].cMode) {
	case 1: // Not yet confirmed exchange
		PutAlignedString(sX + 80, sX + 180, sY + 38, m_cPlayerName, 35,55,35); // my name
		if (m_stDialogBoxExchangeInfo[4].sV1 != -1) // Other name if applicable
			PutAlignedString(sX + 250, sX + 540, sY + 38, m_stDialogBoxExchangeInfo[4].cStr2, 35,55,35);
		for (i=0; i<8; i++) // draw items
		{	sXadd = (58 * i) + 48; if (i>3) sXadd += 20;
			if ( m_stDialogBoxExchangeInfo[i].sV1 != -1)
			{	cItemColor = m_stDialogBoxExchangeInfo[i].sV4;
				if (cItemColor == 0)
				{	 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteFast(sX + sXadd, sY + 130, m_stDialogBoxExchangeInfo[i].sV2, dwTime);
				}else
				{	switch (m_stDialogBoxExchangeInfo[i].sV1) {//sV1 : Sprite
					case 1: //  Swds
					case 2: //  Bows
					case 3: //  Shields
					case 15: // Axes hammers
					case 17: // Wands
							m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
								, m_stDialogBoxExchangeInfo[i].sV2,	 m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
							break;
					default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
								 , m_stDialogBoxExchangeInfo[i].sV2,  m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
						break;
				}	}
				GetItemName(m_stDialogBoxExchangeInfo[i].cStr1, m_stDialogBoxExchangeInfo[i].dwV1, cNameStr, cSubStr1, cSubStr2);
				// If pointer over item then show this item data
				if ( (msX >= sX + sXadd - 6) && (msX <= sX + sXadd + 42)
					&& (msY >= sY + 61) && (msY <= sY + 200) )
				{	wsprintf(cTxt, "%s", cNameStr);
					if (m_bIsSpecial)
					{	PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 0,255,50);
						PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 0,255,50);
					}else
					{	PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 35,35,35);
						PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 35,35,35);
					}
					iLoc = 0;
					if (strlen(cSubStr1) != 0)
					{	PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cSubStr1, 0,0,0);
						iLoc += 15;
					}
					if (strlen(cSubStr2) != 0)
					{	PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cSubStr2, 0,0,0);
						iLoc += 15;
					}
					if (m_stDialogBoxExchangeInfo[i].sV3 != 1) // Item avec Quantity
					{	if(m_stDialogBoxExchangeInfo[i].sV3 > 1)
						{	DisplayCommaNumber_G_cTxt(m_stDialogBoxExchangeInfo[i].sV3);
							strcpy(cTxt2, G_cTxt);
						}else wsprintf(cTxt2, DRAW_DIALOGBOX_EXCHANGE2, m_stDialogBoxExchangeInfo[i].sV3);
						PutAlignedString(sX + 16, sX + 155, sY +235 +iLoc, cTxt2, 35,35,35);
						iLoc += 15;
					}
					if (m_stDialogBoxExchangeInfo[i].sV5 != -1) // completion
					{	// Crafting Magins completion fix
						if (m_stDialogBoxExchangeInfo[i].sV1 == 22)
						{	if (   (m_stDialogBoxExchangeInfo[i].sV2 > 5)
								&& (m_stDialogBoxExchangeInfo[i].sV2 < 10))
							{	wsprintf(cTxt, GET_ITEM_NAME2, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Completion - 100
							}
						}else if (m_stDialogBoxExchangeInfo[i].sV1 == 6)
						{	wsprintf(cTxt, GET_ITEM_NAME1, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Purity
						}else
						{	wsprintf(cTxt, GET_ITEM_NAME2, m_stDialogBoxExchangeInfo[i].sV7); //Completion
						}
						PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cTxt, 35,35,35);
						iLoc += 15;
					}
					if (iLoc < 45) // Endurance
					{	wsprintf(cTxt, DRAW_DIALOGBOX_EXCHANGE3, m_stDialogBoxExchangeInfo[i].sV5, m_stDialogBoxExchangeInfo[i].sV6);
						PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cTxt, 35,35,35);
						iLoc += 15;
		}	}	}	}
		if ((m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 == -1))
		{	PutAlignedString(sX, sX + szX, sY + 235 +10, DRAW_DIALOGBOX_EXCHANGE9, 55,25,25); // Please wait until other player decides
			PutAlignedString(sX, sX + szX, sY + 250 +10, DRAW_DIALOGBOX_EXCHANGE10, 55,25,25);// to exchange. If you want to cancel the
			PutAlignedString(sX, sX + szX, sY + 265 +10, DRAW_DIALOGBOX_EXCHANGE11, 55,25,25);// exchange press the CANCEL button now.
			PutString_SprFont(sX + 220,  sY + 310, "Exchange", 15,15,15);
		}else if ((m_stDialogBoxExchangeInfo[0].sV1 == -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
		{	PutAlignedString(sX, sX + szX, sY + 205 +10, DRAW_DIALOGBOX_EXCHANGE12, 55,25,25);// Other player offered an item exchange
			PutAlignedString(sX, sX + szX, sY + 220 +10, DRAW_DIALOGBOX_EXCHANGE13, 55,25,25);// Select an item which you want to exc-
			PutAlignedString(sX, sX + szX, sY + 235 +10, DRAW_DIALOGBOX_EXCHANGE14, 55,25,25);// hange with above item, drag it to the
			PutAlignedString(sX, sX + szX, sY + 250 +10, DRAW_DIALOGBOX_EXCHANGE15, 55,25,25);// blank and press the EXCHANGE button.
			PutAlignedString(sX, sX + szX, sY + 265 +10, DRAW_DIALOGBOX_EXCHANGE16, 55,25,25);// And you can also reject an offer by
			PutAlignedString(sX, sX + szX, sY + 280 +10, DRAW_DIALOGBOX_EXCHANGE17, 55,25,25);// pressing the CANCEL button.
			PutString_SprFont(sX + 220,  sY + 310, "Exchange", 15,15,15);
		}else if ((m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
		{	PutAlignedString(sX, sX + szX, sY + 205 +10, DRAW_DIALOGBOX_EXCHANGE18, 55,25,25);// The preparation for item exchange
			PutAlignedString(sX, sX + szX, sY + 220 +10, DRAW_DIALOGBOX_EXCHANGE19, 55,25,25);// has been finished. Press the EXCHANGE
			PutAlignedString(sX, sX + szX, sY + 235 +10, DRAW_DIALOGBOX_EXCHANGE20, 55,25,25);// button to exchange as above. Press the
			PutAlignedString(sX, sX + szX, sY + 250 +10, DRAW_DIALOGBOX_EXCHANGE21, 55,25,25);// CANCEL button to cancel. Occasionally
			PutAlignedString(sX, sX + szX, sY + 265 +10, DRAW_DIALOGBOX_EXCHANGE22, 55,25,25);// when you press the EXCHANGE button, you
			PutAlignedString(sX, sX + szX, sY + 280 +10, DRAW_DIALOGBOX_EXCHANGE23, 55,25,25);// will not be able to cancel the exchange.
			if ( (msX >= sX + 200) && (msX <= sX + 200 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY) )
				 PutString_SprFont(sX + 220,  sY + 310, "Exchange", 6,6,20);
			else PutString_SprFont(sX + 220,  sY + 310, "Exchange", 0,0,7);
		}
		if (   (msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)
			&& (m_bIsDialogEnabled[41] == FALSE))
			 PutString_SprFont(sX + 450, sY + 310, "Cancel", 6,6,20);
		else PutString_SprFont(sX + 450, sY + 310, "Cancel", 0,0,7);
		break;

	case 2: // You have confirmed the exchange
		PutAlignedString(sX + 80, sX + 180, sY + 38, m_cPlayerName, 35,55,35); // my name
		if (m_stDialogBoxExchangeInfo[4].sV1 != -1) // Other name if applicable
			PutAlignedString(sX + 250, sX + 540, sY + 38, m_stDialogBoxExchangeInfo[4].cStr2, 35,55,35);
		for (i=0; i<8; i++) // draw items
		{	sXadd = (58 * i) + 48; if (i>3) sXadd += 20;
			if ( m_stDialogBoxExchangeInfo[i].sV1 != -1)
			{	cItemColor = m_stDialogBoxExchangeInfo[i].sV4;
				if (cItemColor == 0)
				{	 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteFast(sX + sXadd, sY + 130, m_stDialogBoxExchangeInfo[i].sV2, dwTime);
				}else
				{	switch (m_stDialogBoxExchangeInfo[i].sV1) {
					case 1: // Swds
					case 2: // Bows
					case 3: // Shields
					case 15: // Axes hammers
					case 17: // Wands
					m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
						, m_stDialogBoxExchangeInfo[i].sV2, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
						break;
					default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
								 , m_stDialogBoxExchangeInfo[i].sV2, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
						break;
				}	}
				GetItemName(m_stDialogBoxExchangeInfo[i].cStr1, m_stDialogBoxExchangeInfo[i].dwV1, cNameStr, cSubStr1, cSubStr2);
				// If pointer over item then show this item data
				if ( (msX >= sX + sXadd - 6) && (msX <= sX + sXadd + 42)
					&& (msY >= sY + 61) && (msY <= sY + 200) )
				{	wsprintf(cTxt, "%s", cNameStr);
					if (m_bIsSpecial)
					{	PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 0,255,50);
						PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 0,255,50);
					}else
					{	PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 35,35,35);
						PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 35,35,35);
					}
					iLoc = 0;
					if (strlen(cSubStr1) != 0)
					{	PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cSubStr1, 0,0,0);
						iLoc += 15;
					}
					if (strlen(cSubStr2) != 0)
					{	PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cSubStr2, 0,0,0);
						iLoc += 15;
					}
					if (m_stDialogBoxExchangeInfo[i].sV3 != 1) // Item avec Quantity
					{	if(m_stDialogBoxExchangeInfo[i].sV3 > 1)
						{	DisplayCommaNumber_G_cTxt(m_stDialogBoxExchangeInfo[i].sV3);
							strcpy(cTxt2, G_cTxt);
						}else wsprintf(cTxt2, DRAW_DIALOGBOX_EXCHANGE2, m_stDialogBoxExchangeInfo[i].sV3);
						PutAlignedString(sX + 16, sX + 155, sY +235 +iLoc, cTxt2, 35,35,35);
						iLoc += 15;
					}
					if (m_stDialogBoxExchangeInfo[i].sV5 != -1) // completion
					{	// Crafting Magins completion fix
						if (m_stDialogBoxExchangeInfo[i].sV1 == 22)
						{	if (   (m_stDialogBoxExchangeInfo[i].sV2 > 5)
								&& (m_stDialogBoxExchangeInfo[i].sV2 < 10))
							{	wsprintf(cTxt, GET_ITEM_NAME2, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Completion - 100
							}
						}else if (m_stDialogBoxExchangeInfo[i].sV1 == 6)
						{	wsprintf(cTxt, GET_ITEM_NAME1, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Purity
						}else
						{	wsprintf(cTxt, GET_ITEM_NAME2, m_stDialogBoxExchangeInfo[i].sV7); //Completion
						}
						PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cTxt, 35,35,35);
						iLoc += 15;
					}
					if (iLoc < 45) // Endurance
					{	wsprintf(cTxt, DRAW_DIALOGBOX_EXCHANGE3, m_stDialogBoxExchangeInfo[i].sV5, m_stDialogBoxExchangeInfo[i].sV6);
						PutAlignedString(sX + 16, sX + 155, sY + 235 +iLoc, cTxt, 35,35,35);
						iLoc += 15;
		}	}	}	}
		wsprintf(cTxt, DRAW_DIALOGBOX_EXCHANGE33, m_stDialogBoxExchangeInfo[4].cStr2);
		PutAlignedString(sX, sX + szX, sY + 205 +10, cTxt, 55,25,25);                     // Please wait until %s agrees to
		PutAlignedString(sX, sX + szX, sY + 220 +10, DRAW_DIALOGBOX_EXCHANGE34, 55,25,25);// exchange. The exchange can't be achieved
		PutAlignedString(sX, sX + szX, sY + 235 +10, DRAW_DIALOGBOX_EXCHANGE35, 55,25,25);// unless both people agree.
		PutAlignedString(sX, sX + szX, sY + 250 +10, DRAW_DIALOGBOX_EXCHANGE36, 55,25,25);//  If other player does not decide to exchange
		PutAlignedString(sX, sX + szX, sY + 265 +10, DRAW_DIALOGBOX_EXCHANGE37, 55,25,25);// you can cancel the exchange by pressing the
		PutAlignedString(sX, sX + szX, sY + 280 +10, DRAW_DIALOGBOX_EXCHANGE38, 55,25,25);// CANCEL button. But if other player already
		PutAlignedString(sX, sX + szX, sY + 295 +10, DRAW_DIALOGBOX_EXCHANGE39, 55,25,25);// decided to exchange, you can't cancel anymore

	/*	if ( (msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY) )
			 PutString_SprFont(sX + 450, sY + 310, "Cancel", 6,6,20);
		else PutString_SprFont(sX + 450, sY + 310, "Cancel", 0,0,7);*/
		break;
	}
}

void CGame::DrawDialogBox_Fishing(short msX, short msY)
{

 short sX, sY;
 DWORD dwTime = m_dwCurTime;
 char  cTxt[120];

	sX = m_stDialogBoxInfo[24].sX;
	sY = m_stDialogBoxInfo[24].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_stDialogBoxInfo[24].cStr, NULL, cStr1, cStr2, cStr3);

	switch (m_stDialogBoxInfo[24].cMode) {
	case 0:
		m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxInfo[24].sV3]->PutSpriteFast(sX + 18 + 35, sY + 18 + 17, m_stDialogBoxInfo[24].sV4, dwTime);
		wsprintf(cTxt, "%s", cStr1);
		PutString(sX + 98, sY + 14, cTxt, RGB(255,255,255));
		wsprintf(cTxt, DRAW_DIALOGBOX_FISHING1, m_stDialogBoxInfo[24].sV2);
		PutString(sX + 98, sY + 28, cTxt, RGB(0,0,0));
		PutString(sX + 97, sY + 43, DRAW_DIALOGBOX_FISHING2, RGB(0,0,0));
		wsprintf(cTxt, "%d %%", m_stDialogBoxInfo[24].sV1);
		PutString_SprFont(sX + 157,  sY + 40, cTxt, 10,0,0);
		if ((msX >= sX + 160) && (msX <= sX + 253) && (msY >= sY + 70) && (msY <= sY + 90))
			 PutString_SprFont(sX + 160, sY + 70, "Try Now!", 6,6,20);
		else PutString_SprFont(sX + 160, sY + 70, "Try Now!", 0, 0, 7);
		break;
	}

}

void CGame::DrawDialogBox_GuildMenu(short msX, short msY)
{
 short sX, sY, szX;
 int iAdjX, iAdjY ;

	sX = m_stDialogBoxInfo[7].sX;
	sY = m_stDialogBoxInfo[7].sY;
	szX = m_stDialogBoxInfo[7].sSizeX;

	iAdjX = - 13 ;
	iAdjY =  30 ;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 19);

	switch (m_stDialogBoxInfo[7].cMode) {
	case 0:
		if ( (m_iGuildRank == -1) && (m_iCharisma >= 20) && (m_iLevel >= 20) ) {
			if ((msX > sX + iAdjX +80) && (msX < sX + iAdjX +210) && (msY > sY + iAdjY + 63) && (msY < sY + iAdjY + 78))
				 PutAlignedString(sX, sX + szX, sY + iAdjY + 65, DRAW_DIALOGBOX_GUILDMENU1, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + iAdjY + 65, DRAW_DIALOGBOX_GUILDMENU1, 4,0,50);//"
		}
		else PutAlignedString(sX, sX + szX, sY + iAdjY + 65, DRAW_DIALOGBOX_GUILDMENU1, 65,65,65);//"

		if (m_iGuildRank == 0) {
			if ((msX > sX + iAdjX +72) && (msX < sX + iAdjX +222) && (msY > sY + iAdjY + 82) && (msY < sY + iAdjY + 99))
				 PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU4, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU4, 4,0,50);//"
		}
		else PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU4, 65,65,65);//"

		if ((msX > sX + iAdjX +61) && (msX < sX + iAdjX +226) && (msY > sY + iAdjY + 103) && (msY < sY + iAdjY + 120))
			 PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU7, 255,255,255);//"
		else PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU7, 4,0,50);//"

		if ((msX > sX + iAdjX +60) && (msX < sX + iAdjX +227) && (msY > sY + iAdjY + 123) && (msY < sY + iAdjY + 139))
			 PutAlignedString(sX, sX + szX, sY + iAdjY + 125, DRAW_DIALOGBOX_GUILDMENU9, 255,255,255);//"
		else PutAlignedString(sX, sX + szX, sY + iAdjY + 125, DRAW_DIALOGBOX_GUILDMENU9, 4,0,50);//"

		if (m_iGuildRank == 0 && m_iFightzoneNumber == 0) {
			if ((msX > sX + iAdjX +72) && (msX < sX + iAdjX +228) && (msY > sY + iAdjY + 143) && (msY < sY + iAdjY + 169))
				 PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU11, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU11, 4,0,50);//"

		} else if (m_iGuildRank == 0 && m_iFightzoneNumber > 0) {
			if ((msX > sX + iAdjX +72) && (msX < sX + iAdjX +216) && (msY > sY + iAdjY + 143) && (msY < sY + iAdjY + 169))
				 PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU13, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU13, 4,0,50);//"

		} else if (m_iFightzoneNumber < 0) {
			PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU13, 65,65,65);//"
		} else PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU11, 65,65,65);//"

		PutAlignedString(sX, sX + szX, sY + iAdjY + 205, DRAW_DIALOGBOX_GUILDMENU17);//"
		break;

	case 1:
		PutAlignedString(sX + 24, sX + 239, sY + 125, DRAW_DIALOGBOX_GUILDMENU18, 55,25,25);//"
		PutString(sX + 75, sY + 144, "____________________", RGB(25,35,25));

		if (iGetTopDialogBoxIndex() != 7)
			PutString(sX + 75, sY + 140, m_cGuildName, RGB(255,255,255), 16, FALSE, 2);

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			if ((strcmp(m_cGuildName, "NONE") == 0) || (strlen(m_cGuildName) == 0)) {
				 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);//Create Gray Button
			}
			else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 25);//Create Highlight Button
		}
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);//Create Gray Button

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);//Red Cancel Button
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);//Gray Cancel Button
	   	break;

	case 2:
		PutAlignedString(sX, sX + szX, sY +140, DRAW_DIALOGBOX_GUILDMENU19, 55,25,25);//"
		break;
	case 3:
		PutAlignedString(sX, sX + szX,  sY + 125, DRAW_DIALOGBOX_GUILDMENU20, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 140, m_cGuildName, 55,25,25);
		PutAlignedString(sX, sX + szX, sY + 144, "____________________", 25,35,25);
		PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU21, 55,25,25);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 4:
		PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU22, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU23, 55,25,25);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 5:
		PutAlignedString(sX, sX + szX, sY + 90, DRAW_DIALOGBOX_GUILDMENU24);
		PutAlignedString(sX, sX + szX, sY + 105, m_cGuildName, 35,35,35);
		PutAlignedString(sX, sX + szX, sY + 109, "____________________", 0,0,0);
		PutAlignedString(sX, sX + szX, sY + 130, DRAW_DIALOGBOX_GUILDMENU25);//"
		PutAlignedString(sX, sX + szX, sY + 145,DRAW_DIALOGBOX_GUILDMENU26);//"
		PutAlignedString(sX, sX + szX, sY + 160,DRAW_DIALOGBOX_GUILDMENU27);//"
		PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_GUILDMENU28, 55,25,25);//"

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;
	case 6:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU29, 55,25,25);//"
		break;
	case 7:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU30, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 8:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU31, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 9:
		PutAlignedString(sX, sX + szX, sY + iAdjY + 60,  DRAW_DIALOGBOX_GUILDMENU32);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 75,  DRAW_DIALOGBOX_GUILDMENU33);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 90,  DRAW_DIALOGBOX_GUILDMENU34);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU35);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 130, DRAW_DIALOGBOX_GUILDMENU36);//"
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;
	case 10:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU37, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	case 11:
		PutAlignedString(sX, sX + szX, sY + iAdjY + 60,  DRAW_DIALOGBOX_GUILDMENU38);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 75,  DRAW_DIALOGBOX_GUILDMENU39);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 90, DRAW_DIALOGBOX_GUILDMENU40);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU41);//
		PutAlignedString(sX, sX + szX, sY + iAdjY + 130, DRAW_DIALOGBOX_GUILDMENU42);//"
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;
	case 12:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU43, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 13:
		PutAlignedString(sX, sX + szX, sY + iAdjY + 40,  DRAW_DIALOGBOX_GUILDMENU44);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 55,  DRAW_DIALOGBOX_GUILDMENU45);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 70,  DRAW_DIALOGBOX_GUILDMENU46);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU47);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 100, DRAW_DIALOGBOX_GUILDMENU48);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 115, DRAW_DIALOGBOX_GUILDMENU49);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 130, DRAW_DIALOGBOX_GUILDMENU50);//"

		if ((msX > sX + iAdjX +65) && (msX < sX + iAdjX +137) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
			 PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU51, RGB(255,255,255));
		else PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU51, RGB(4,0,50));

		if ((msX > sX + iAdjX +150) && (msX < sX + iAdjX +222) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
			 PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU53, RGB(255,255,255));
		else PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU53, RGB(4,0,50));

		if ((msX > sX + iAdjX +65) && (msX < sX + iAdjX +137) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
			 PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU55, RGB(255,255,255));
		else PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU55, RGB(4,0,50));

		if ((msX > sX + iAdjX +150) && (msX < sX + iAdjX +222) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
			 PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU57, RGB(255,255,255));
		else PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU57, RGB(4,0,50));

		if ((msX > sX + iAdjX +65) && (msX < sX + iAdjX +137) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
			 PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU59, RGB(255,255,255));
		else PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU59, RGB(4,0,50));

		if ((msX > sX + iAdjX +150) && (msX < sX + iAdjX +222) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
			 PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU61, RGB(255,255,255));
		else PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU61, RGB(4,0,50));

		if ((msX > sX + iAdjX +65) && (msX < sX + iAdjX +137) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
			 PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU63, RGB(255,255,255));
		else PutString(sX + iAdjX +65 + 25 -23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU63, RGB(4,0,50));

		if ((msX > sX + iAdjX +150) && (msX < sX + iAdjX +222) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
			 PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU65, RGB(255,255,255));
		else PutString(sX + iAdjX +150 + 25 -23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU65, RGB(4,0,50));

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 14:
		PutAlignedString(sX, sX + szX, sY + 130, DRAW_DIALOGBOX_GUILDMENU66, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_GUILDMENU67, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU68, 55,25,25);//
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 15:
		PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU69, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU70, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 16:
		PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU71, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU72, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 17:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU73, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 18:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU74, 55,25,25);//"
		break;

	case 19:
		if( m_iFightzoneNumber >0 )
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETOCCUPYFIGHTZONETICKET, NULL, NULL, NULL, NULL, NULL);
		m_stDialogBoxInfo[7].cMode = 0;
		break;

	case 20:
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_GUILDMENU75, 55,25,25);//"
		PutString(sX + 75, sY + 144, "____________________", RGB(25,35,25));
		PutString(sX + 75, sY + 140, m_cGuildName, RGB(255,255,255), FALSE, 2);
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 25);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 21:
		PutAlignedString(sX, sX + szX, sY + iAdjY + 95,  DRAW_DIALOGBOX_GUILDMENU76, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 110, DRAW_DIALOGBOX_GUILDMENU77, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 135, DRAW_DIALOGBOX_GUILDMENU78, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 150, DRAW_DIALOGBOX_GUILDMENU79, 55,25,25);//"
		PutAlignedString(sX, sX + szX, sY + iAdjY + 165, DRAW_DIALOGBOX_GUILDMENU80, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 22:
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU81, 55,25,25);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	}
}

void CGame::DrawDialogBox_GuildOperation(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[8].sX;
	sY = m_stDialogBoxInfo[8].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 19);

	switch (m_stGuildOpList[0].cOpMode) {
	case 1:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION1);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35,35,35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0,0,0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION2);
		PutAlignedString(sX + 24, sX + 248, sY + 105,DRAW_DIALOGBOX_GUILD_OPERATION3);
		PutAlignedString(sX + 24, sX + 248, sY + 120,DRAW_DIALOGBOX_GUILD_OPERATION4);
		PutAlignedString(sX + 24, sX + 248, sY + 160, DRAW_DIALOGBOX_GUILD_OPERATION5, 55,25,25);

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 35);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 34);
		break;

	case 2:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION6);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35,35,35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0,0,0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION7);
		PutAlignedString(sX + 24, sX + 248, sY + 105,DRAW_DIALOGBOX_GUILD_OPERATION8);
		PutAlignedString(sX + 24, sX + 248, sY + 120,DRAW_DIALOGBOX_GUILD_OPERATION9);
		PutAlignedString(sX + 24, sX + 248, sY + 160, DRAW_DIALOGBOX_GUILD_OPERATION10, 55,25,25);

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 35);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 34);
		break;

	case 3:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION11);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35,35,35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0,0,0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION12);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION13);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 4:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION14);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35,35,35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0,0,0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION15);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION16);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 5:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION17);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35,35,35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0,0,0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION18);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION19);
		PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION20);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 6:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION21);
		PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35,35,35);
		PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0,0,0);
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION22);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION23);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 7:
		PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION24);
		//PutString(sX + 60, sY + 65, m_stGuildOpList[0].cName, RGB(35,35,35));
		//PutString(sX + 60, sY + 69, "____________________", RGB(0,0,0));
		PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION25);
		PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION26);
		PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION27);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	}
}

int  _tmp_iMCProb[]        = {0, 300, 250, 200, 150, 100, 80, 70, 60, 50, 40};
int  _tmp_iMLevelPenalty[] = {0,   5,   5,   8,   8,   10, 14, 28, 32, 36, 40};

void CGame::DrawDialogBox_Magic(short msX, short msY, short msZ)
{
	short sX, sY, sMagicCircle, sLevelMagic;
	int  iCPivot, i, iYloc, iResult, iManaCost;
	char cTxt[120], cMana[10];
	DWORD dwTime = m_dwCurTime;
	double dV1, dV2, dV3, dV4;

	sX = m_stDialogBoxInfo[3].sX;
	sY = m_stDialogBoxInfo[3].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 1, FALSE, m_bDialogTrans);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 7, FALSE, m_bDialogTrans);

	if( iGetTopDialogBoxIndex() == 3 && msZ != 0 )
	{
		if( msZ > 0 ) m_stDialogBoxInfo[3].sView--;
		if( msZ < 0 ) m_stDialogBoxInfo[3].sView++;
		m_DInput.m_sZ = 0;
	}
	if( m_stDialogBoxInfo[3].sView < 0 ) m_stDialogBoxInfo[3].sView = 9;
	if( m_stDialogBoxInfo[3].sView > 9 ) m_stDialogBoxInfo[3].sView = 0;

	//Circle
	ZeroMemory(cTxt, sizeof(cTxt));
	switch (m_stDialogBoxInfo[3].sView) {
	case 0: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC1);  break;//"Circle One"
	case 1: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC2);  break;//"Circle Two"
	case 2: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC3);  break;//"Circle Three"
	case 3: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC4);  break;//"Circle Four"
	case 4: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC5);  break;//"Circle Five"
	case 5: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC6);  break;//"Circle Six"
	case 6: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC7);  break;//"Circle Seven"
	case 7: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC8);  break;//"Circle Eight"
	case 8: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC9);  break;//"Circle Nine"
	case 9: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC10); break;//"Circle Ten"
	}
	PutAlignedString(sX + 3, sX + 256, sY + 50, cTxt);
	PutAlignedString(sX + 4, sX + 257, sY + 50, cTxt);
	iCPivot = m_stDialogBoxInfo[3].sView*10;
	iYloc = 0;

	for (i = 0; i < 9; i++) {
		if ((m_cMagicMastery[iCPivot + i] != NULL) && (m_pMagicCfgList[iCPivot + i] != NULL)) {
			wsprintf(cTxt, "%s", m_pMagicCfgList[iCPivot + i]->m_cName);

			m_Misc.ReplaceString(cTxt, '-', ' ');
			iManaCost = iGetManaCost(iCPivot+i);
			if (iManaCost > m_iMP)
			{
				if( m_Misc.bCheckIMEString( cTxt ) == FALSE )
				{
					PutString(sX + 30, sY + 73 + iYloc, cTxt, RGB(41, 16, 41));
					PutString(sX + 31, sY + 73 + iYloc, cTxt, RGB(41, 16, 41));
				}
				else PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 5, 5, 5);
				wsprintf(cMana, "%3d", iManaCost);
				PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 5, 5, 5);
			}
			else
			if ((msX >= sX + 30) && (msX <= sX + 240) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 14 + iYloc))
			{
				if( m_Misc.bCheckIMEString( cTxt ) == FALSE )
				{
					PutString(sX + 30, sY + 73 + iYloc, cTxt, RGB(255,255,255));
					PutString(sX + 31, sY + 73 + iYloc, cTxt, RGB(255,255,255));
				}
				else PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 250, 250, 250);
				wsprintf(cMana, "%3d", iManaCost);
				PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 250, 250, 250);
			}
			else
			{
				if( m_Misc.bCheckIMEString( cTxt ) == FALSE )
				{
					PutString(sX + 30, sY + 73 + iYloc, cTxt, RGB(8,0,66));
					PutString(sX + 31, sY + 73 + iYloc, cTxt, RGB(8,0,66));
				}
				else PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 1, 1, 8);
				wsprintf(cMana, "%3d", iManaCost);
				PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 1, 1, 8);
			}

			iYloc += 18;
		}

	}

	if (iYloc == 0) {
		PutAlignedString(sX + 3, sX +256, sY + 100, DRAW_DIALOGBOX_MAGIC11);//"
		PutAlignedString(sX + 3, sX +256, sY + 115, DRAW_DIALOGBOX_MAGIC12);//"
		PutAlignedString(sX + 3, sX +256, sY + 130, DRAW_DIALOGBOX_MAGIC13);//"
		PutAlignedString(sX + 3, sX +256, sY + 145, DRAW_DIALOGBOX_MAGIC14);//"
		PutAlignedString(sX + 3, sX +256, sY + 160, DRAW_DIALOGBOX_MAGIC15);//"
	}

	m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 30, sY + 250, 19, dwTime);

	switch (m_stDialogBoxInfo[3].sView) {
	case 0: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 30, sY + 250, 20, dwTime); break;
	case 1: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 43, sY + 250, 21, dwTime); break;
	case 2: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 61, sY + 250, 22, dwTime); break;
	case 3: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 86, sY + 250, 23, dwTime); break;
	case 4: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 106, sY + 250, 24, dwTime); break;
	case 5: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 121, sY + 250, 25, dwTime); break;
	case 6: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 142, sY + 250, 26, dwTime); break;
	case 7: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 169, sY + 250, 27, dwTime); break;
	case 8: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 202, sY + 250, 28, dwTime); break;
	case 9: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 222, sY + 250, 29, dwTime); break;
	}

	sMagicCircle = m_stDialogBoxInfo[3].sView + 1;
	if (m_cSkillMastery[4] == 0)
		 dV1 = 1.0f;
	else dV1 = (double)m_cSkillMastery[4];
	dV2 = (double)(dV1 / 100.0f);
	dV3 = (double)_tmp_iMCProb[sMagicCircle];
	dV1 = dV2 * dV3;
	iResult = (int)dV1;
	if ((m_iInt + m_iAngelicInt) > 50) iResult += ((m_iInt + m_iAngelicInt) - 50)/2;
	sLevelMagic = (m_iLevel / 10);
	if (sMagicCircle != sLevelMagic)
	{	if (sMagicCircle > sLevelMagic)
		{	dV1 = (double)(m_iLevel - sLevelMagic*10);
			dV2 = (double)abs(sMagicCircle - sLevelMagic)*_tmp_iMLevelPenalty[sMagicCircle];
			dV3 = (double)abs(sMagicCircle - sLevelMagic)*10;
			dV4 = (dV1 / dV3)*dV2;
			iResult -= abs(abs(sMagicCircle - sLevelMagic)*_tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
		}else
		{	iResult += 5*abs(sMagicCircle - sLevelMagic);
	}	}

	switch (m_cWhetherStatus) {
	case 0: break;
	case 1: iResult = iResult - (iResult / 24); break;
	case 2:	iResult = iResult - (iResult / 12); break;
	case 3: iResult = iResult - (iResult / 5);  break;
	}
	for( i=0; i<DEF_MAXITEMS ; i++ )
	{	if( m_pItemList[i] == NULL ) continue;
		if( m_bIsItemEquipped[i] == TRUE )
		{	if( ((m_pItemList[i]->m_dwAttribute & 0x00F00000) >> 20) == 10 )
			{	dV1 = (double)iResult;
				dV2 = (double)(( (m_pItemList[i]->m_dwAttribute & 0x000F0000) >> 16) * 3 );
				dV3 = dV1 + dV2;
				iResult = (int)dV3;
				break;
	}	}	}

	if (iResult > 100) iResult = 100;
	if (m_iSP < 1) iResult = iResult*9/10;
	if (iResult < 1 ) iResult = 1;

	ZeroMemory(cTxt, sizeof(cTxt));
	wsprintf(cTxt, DRAW_DIALOGBOX_MAGIC16, iResult);//"
	PutAlignedString(sX, sX + 256, sY + 267, cTxt);
	PutAlignedString(sX+1, sX + 257, sY + 267, cTxt);

	// v2.15
	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 285) && (msY <= sY + 285 + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 285, 49, FALSE, m_bDialogTrans);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 285, 48, FALSE, m_bDialogTrans);
}

void CGame::DrawDialogBox_MagicShop(short msX, short msY, short msZ)
{
 short sX, sY;
 DWORD dwTime = m_dwCurTime;
 int  i;

 int  iCPivot, iYloc;
 char cTxt[120], cMana[10];

	sX = m_stDialogBoxInfo[16].sX;
	sY = m_stDialogBoxInfo[16].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 1);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 14);

	if( iGetTopDialogBoxIndex() == 16 && msZ != 0 )
	{
		if( msZ > 0 ) m_stDialogBoxInfo[16].sView--;
		if( msZ < 0 ) m_stDialogBoxInfo[16].sView++;
		m_DInput.m_sZ = 0;
	}
	if( m_stDialogBoxInfo[16].sView < 0 ) m_stDialogBoxInfo[16].sView = 9;
	if( m_stDialogBoxInfo[16].sView > 9 ) m_stDialogBoxInfo[16].sView = 0;

	PutString(sX -20 + 60 -17, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP11, RGB(45,25,25));//"Spell Name"
	PutString(sX -20 + 232 -20, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP12, RGB(45,25,25));//"Req.Int"
	PutString(sX -20 + 270, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP13, RGB(45,25,25));//"Cost"

	iCPivot = m_stDialogBoxInfo[16].sView*10;

	iYloc = 0;
	for (i = 0; i < 9; i++) {
		if ((m_pMagicCfgList[iCPivot + i] != NULL) && (m_pMagicCfgList[iCPivot + i]->m_bIsVisible)) {
			wsprintf(cTxt, "%s", m_pMagicCfgList[iCPivot + i]->m_cName);

			m_Misc.ReplaceString(cTxt, '-', ' ');
			if (m_cMagicMastery[iCPivot + i] != 0) {
				if( m_Misc.bCheckIMEString( cTxt ) == FALSE )
				{
					PutString(sX + 24, sY + 73 + iYloc, cTxt, RGB(41,16,41));
					PutString(sX + 25, sY + 73 + iYloc, cTxt, RGB(41,16,41));
				}
				else PutString_SprFont(sX + 24, sY + 70 + iYloc, cTxt, 5, 5, 5);
				wsprintf(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue2);
				PutString_SprFont(sX + 200, sY + 70 + iYloc, cMana, 5, 5, 5);
				wsprintf(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue3);
				PutString_SprFont(sX + 241, sY + 70 + iYloc, cMana, 5, 5, 5);
			}
			else
			if ((msX >= sX + 24) && (msX <= sX + 24 + 135) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 14 + iYloc)) {
				if( m_Misc.bCheckIMEString( cTxt ) == FALSE )
				{
					PutString(sX + 24, sY + 73 + iYloc, cTxt, RGB(255,255,255));
					PutString(sX + 25, sY + 73 + iYloc, cTxt, RGB(255,255,255));
				}
				else PutString_SprFont(sX -20 + 44, sY + 70 + iYloc, cTxt, 250, 250, 250);
				wsprintf(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue2);
				PutString_SprFont(sX -20 + 220, sY + 70 + iYloc, cMana, 250, 250, 250);
				wsprintf(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue3);
				PutString_SprFont(sX -20 + 261, sY + 70 + iYloc, cMana, 250, 250, 250);
			}
			else {
				if( m_Misc.bCheckIMEString( cTxt ) == FALSE )
				{
					PutString(sX + 24, sY + 73 + iYloc, cTxt, RGB(8,0,66));
					PutString(sX + 25, sY + 73 + iYloc, cTxt, RGB(8,0,66));
				}
				else PutString_SprFont(sX -20 + 44, sY + 70 + iYloc, cTxt, 1, 1, 8);
				wsprintf(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue2);
				PutString_SprFont(sX -20 + 220, sY + 70 + iYloc, cMana, 1, 1, 8);
				wsprintf(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue3);
				PutString_SprFont(sX -20 + 261, sY + 70 + iYloc, cMana, 1, 1, 8);
			}
			iYloc += 18;
		}
	}

	m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 55, sY + 250, 19, dwTime);

	switch (m_stDialogBoxInfo[16].sView) {
	case 0: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 44  +31, sY + 250, 20, dwTime); break;
	case 1: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 57  +31, sY + 250, 21, dwTime); break;
	case 2: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 75  +31, sY + 250, 22, dwTime); break;
	case 3: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 100 +31, sY + 250, 23, dwTime); break;
	case 4: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 120 +31, sY + 250, 24, dwTime); break;
	case 5: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 135 +31, sY + 250, 25, dwTime); break;
	case 6: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 156 +31, sY + 250, 26, dwTime); break;
	case 7: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 183 +31, sY + 250, 27, dwTime); break;
	case 8: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 216 +31, sY + 250, 28, dwTime); break;
	case 9: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX -20 + 236 +31, sY + 250, 29, dwTime); break;
	}

	PutAlignedString(sX, sX+m_stDialogBoxInfo[16].sSizeX, sY + 275, DRAW_DIALOGBOX_MAGICSHOP14, 45,25,25);
}

void CGame::DrawDialogBox_ShutDownMsg(short msX, short msY)
{
 short sX, sY, szX;

	sX = m_stDialogBoxInfo[25].sX;
	sY = m_stDialogBoxInfo[25].sY;
	szX = m_stDialogBoxInfo[25].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY,2);

	switch (m_stDialogBoxInfo[25].cMode) {
	case 1:
		ZeroMemory(G_cTxt, sizeof(G_cTxt));
		if (m_stDialogBoxInfo[25].sV1 != 0) wsprintf(G_cTxt, DRAW_DIALOGBOX_NOTICEMSG1, m_stDialogBoxInfo[25].sV1);
		else strcpy(G_cTxt, DRAW_DIALOGBOX_NOTICEMSG2);
		PutAlignedString(sX, sX + szX, sY + 31, G_cTxt, 100,10,10);
		PutAlignedString(sX, sX + szX, sY + 48, DRAW_DIALOGBOX_NOTICEMSG3);
		PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_NOTICEMSG4);
		PutAlignedString(sX, sX + szX, sY + 82, DRAW_DIALOGBOX_NOTICEMSG5);
		PutAlignedString(sX, sX + szX, sY + 99, DRAW_DIALOGBOX_NOTICEMSG6);
		if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 0);
		break;

	case 2:
		PutAlignedString(sX, sX + szX, sY + 31, DRAW_DIALOGBOX_NOTICEMSG7, 100,10,10);
		PutAlignedString(sX, sX + szX, sY + 48, DRAW_DIALOGBOX_NOTICEMSG8);
		PutAlignedString(sX, sX + szX, sY + 65,  DRAW_DIALOGBOX_NOTICEMSG9);
		PutAlignedString(sX, sX + szX, sY + 82, DRAW_DIALOGBOX_NOTICEMSG10);
		PutAlignedString(sX, sX + szX, sY + 99, DRAW_DIALOGBOX_NOTICEMSG11);
		if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 0);
		break;
	}
}

void CGame::DrawDialogBox_NpcActionQuery(short msX, short msY)
{
 short sX, sY, szX;

 char cTxt[120], cTxt2[120],  cStr1[64], cStr2[64], cStr3[64];

	ZeroMemory(cStr1, sizeof(cStr1));
	ZeroMemory(cStr2, sizeof(cStr2));
	ZeroMemory(cStr3, sizeof(cStr3));

	sX = m_stDialogBoxInfo[20].sX;
	sY = m_stDialogBoxInfo[20].sY;
	szX = m_stDialogBoxInfo[20].sSizeX;

	//DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5); //5
	//DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6); //6

	switch (m_stDialogBoxInfo[20].cMode) {
	case 0: // npc
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
		switch (m_stDialogBoxInfo[20].sV3) {
		case 15:
			PutString(sX +33, sY +23, NPC_NAME_SHOP_KEEPER, RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_SHOP_KEEPER, RGB(255,255,255));
			break;
		case 19:
			PutString(sX +33, sY +23, NPC_NAME_MAGICIAN, RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_MAGICIAN, RGB(255,255,255));
			break;
		case 20:
			PutString(sX +33, sY +23, NPC_NAME_WAREHOUSE_KEEPER, RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_WAREHOUSE_KEEPER, RGB(255,255,255));
			break;
		case 24:
			PutString(sX +33, sY +23, NPC_NAME_BLACKSMITH_KEEPER, RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_BLACKSMITH_KEEPER, RGB(255,255,255));
			break;
		case 25:
			PutString(sX +33, sY +23, NPC_NAME_CITYHALL_OFFICER, RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_CITYHALL_OFFICER, RGB(255,255,255));
			break;
		case 26: // "Guildhall Officer"
			PutString(sX +33, sY +23, NPC_NAME_GUILDHALL_OFFICER, RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_GUILDHALL_OFFICER, RGB(255,255,255));
			break;
		case 90: //Gail
			PutString(sX +33, sY +23, "Heldenian staff officer", RGB(45,25,25));
			PutString(sX +33 -1, sY +23 -1, "Heldenian staff officer", RGB(255,255,255));
			break;
		}

		if ( m_stDialogBoxInfo[20].sV3 == 25 )
		{   // OFFER
			if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, RGB(255,255,255)); // "Offer"
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, RGB(255,255,255));
			}
			else {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, RGB(4,0,50));
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, RGB(4,0,50));
			}
		}else if ( m_stDialogBoxInfo[20].sV3 == 20 )
		{   // WITHDRAW
			if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, RGB(255,255,255)); // "Withdraw"
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, RGB(255,255,255));
			}
			else {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, RGB(4,0,50));
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, RGB(4,0,50));
			}
		}else if ( m_stDialogBoxInfo[20].sV3 == 19 ) // CLEROTH: MAGICIAN
		{   // LEARN
			if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, RGB(255,255,255)); // "Learn"
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, RGB(255,255,255));
			}
			else {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, RGB(4,0,50));
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, RGB(4,0,50));
			}
		}else
		{   // TRADE
			if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(255,255,255)); // "Trade"
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(255,255,255));
			}
			else {
				PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(4,0,50));
				PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(4,0,50));
		}	}

		if (m_bIsDialogEnabled[21] == FALSE)
		{	if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70)) {
				PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(255,255,255)); // "Talk"
				PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(255,255,255));
			}
			else {
				PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(4,0,50));
				PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(4,0,50));
			}
		}
		break;

	case 1: // Other char
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
		GetItemName(m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_dwAttribute, cStr1, cStr2, cStr3);
		wsprintf(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, m_stDialogBoxInfo[20].sV3, cStr1); //"%d %s to"
		wsprintf(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, m_stDialogBoxInfo[20].cStr); // "%s"

		PutString(sX+24, sY+25, cTxt, RGB(45,25,25));
		PutString(sX+24, sY+40, cTxt2, RGB(45,25,25));

		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, RGB(255,255,255));//"Give"
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, RGB(255,255,255));
		}
		else {
			PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, RGB(4,0,50));
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, RGB(4,0,50));
		}

		if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70)) {
			PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, RGB(255,255,255));//"Exchange"
			PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, RGB(255,255,255));
		}
		else {
			PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, RGB(4,0,50));
			PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, RGB(4,0,50));
		}
		break;

	case 2: // Shop / BS
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
		GetItemName(m_pItemList[ m_stDialogBoxInfo[20].sV1 ]->m_cName, m_pItemList[ m_stDialogBoxInfo[20].sV1 ]->m_dwAttribute, cStr1, cStr2, cStr3);

		wsprintf(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, m_stDialogBoxInfo[20].sV3, cStr1);//"%d %s to"
		wsprintf(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, m_stDialogBoxInfo[20].cStr);//"%s"

		PutString(sX+24, sY+20, cTxt, RGB(45,25,25));
		PutString(sX+24, sY+35, cTxt2, RGB(45,25,25));

		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(255,255,255));//"Sell"
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(255,255,255));
		}else
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(4,0,50));
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(4,0,50));
		}

		if ((m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
			(m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cItemType == DEF_ITEMTYPE_ARROW))
		{}else
		{	if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
			{	PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, RGB(255,255,255));//"Repair"
				PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, RGB(255,255,255));
			}else
			{	PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, RGB(4,0,50));
				PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, RGB(4,0,50));
		}	}
		break;

	case 3: // WH
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
		GetItemName(m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_dwAttribute, cStr1, cStr2, cStr3);

		wsprintf(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, m_stDialogBoxInfo[20].sV3, cStr1);//"%d %s to"
		wsprintf(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, m_stDialogBoxInfo[20].cStr);//"%s"

		PutAlignedString(sX, sX+240, sY+20, cTxt, 45,25,25);
		PutAlignedString(sX, sX+240, sY+35, cTxt2, 45,25,25);

		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70)) {
			PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, RGB(255,255,255));//"Deposit"
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, RGB(255,255,255));
		}else
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, RGB(4,0,50));
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, RGB(4,0,50));
		}
		break;

	case 4: // talk to npc or unicorn
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
		switch (m_stDialogBoxInfo[20].sV3) {
		case 21:
			PutString(sX +35, sY + 25, NPC_NAME_GUARD, RGB(45,25,25));//
			PutString(sX +35 -1, sY + 25 -1, NPC_NAME_GUARD, RGB(255,255,255));
			break;
		case 32:
			PutString(sX +35, sY + 25, NPC_NAME_UNICORN, RGB(45,25,25));//"
			PutString(sX +35 -1, sY + 25 -1, NPC_NAME_UNICORN, RGB(255,255,255));//"
			break;
		case 67:
			PutString(sX +35, sY + 25, NPC_NAME_MCGAFFIN, RGB(45,25,25));
			PutString(sX +35 -1, sY + 25 -1, NPC_NAME_MCGAFFIN, RGB(255,255,255));
			break;
		case 68:
			PutString(sX +35, sY + 25, NPC_NAME_PERRY, RGB(45,25,25));
			PutString(sX +35 -1, sY + 25 -1, NPC_NAME_PERRY, RGB(255,255,255));
			break;
		case 69:
			PutString(sX +35, sY + 25, NPC_NAME_DEVLIN, RGB(45,25,25));
			PutString(sX +35 -1, sY + 25 -1, NPC_NAME_DEVLIN, RGB(255,255,255));
			break;

		}

		if (m_bIsDialogEnabled[21] == FALSE) {
			if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70)) {
				PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(255,255,255));
				PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(255,255,255));
			}
			else {
				PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(4,0,50));
				PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(4,0,50));
			}
		}
		break;

	case 5: // Shop / BS
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
		switch (m_stDialogBoxInfo[20].sV3) {
		case 15:
			PutString(sX +33, sY +23, NPC_NAME_SHOP_KEEPER, RGB(45,25,25));//Shop Keeper"
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_SHOP_KEEPER, RGB(255,255,255));
			break;
		case 24:
			PutString(sX +33, sY +23, NPC_NAME_BLACKSMITH_KEEPER, RGB(45,25,25));//"BlackSmith Keeper"
			PutString(sX +33 -1, sY +23 -1, NPC_NAME_BLACKSMITH_KEEPER, RGB(255,255,255));//"
			break;
		}

		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(255,255,255));//"Trade"
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(255,255,255));
		}else
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(4,0,50));
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(4,0,50));
		}

		if ((msX > sX + 25 +79) && (msX < sX + 80 +75) && (msY > sY + 55) && (msY < sY + 70))
		{	PutString(sX + 28 +75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(255,255,255));//"Sell"
			PutString(sX + 29 +75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(255,255,255));
		}else
		{	PutString(sX + 28 +75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(4,0,50));
			PutString(sX + 29 +75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, RGB(4,0,50));
		}
		if (m_bIsDialogEnabled[21] == FALSE)
		{	if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
			{	PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(255,255,255));//"Talk"
				PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(255,255,255));
			}else
			{	PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(4,0,50));
				PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, RGB(4,0,50));
		}	}
		break;

	case 6: //Gail
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(255,255,255)); // "Trade"
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(255,255,255));
		}else
		{	PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(4,0,50));
			PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, RGB(4,0,50));
		}
		PutString(sX +33, sY +23, "Heldenian staff officer", RGB(45,25,25));
		PutString(sX +33 -1, sY +23 -1, "Heldenian staff officer", RGB(255,255,255));
		break;
	}
}

void CGame::DrawDialogBox_Party(short msX, short msY)
{short sX, sY, szX;
 int  i, iNth;
	sX = m_stDialogBoxInfo[32].sX;
	sY = m_stDialogBoxInfo[32].sY;
	szX = m_stDialogBoxInfo[32].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 3);

	switch (m_stDialogBoxInfo[32].cMode) {
	case 0:
		if (m_iPartyStatus == 0) {
			if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 80) && (msY < sY + 100))
				 PutAlignedString(sX, sX + szX, sY + 85, DRAW_DIALOGBOX_PARTY1, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + 85, DRAW_DIALOGBOX_PARTY1, 4,0,50);//"
		}
		else PutAlignedString(sX, sX + szX, sY + 85, DRAW_DIALOGBOX_PARTY1, 65,65,65);//"

		if (m_iPartyStatus != 0) {
			if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 100) && (msY < sY + 120))
				 PutAlignedString(sX, sX + szX, sY + 105, DRAW_DIALOGBOX_PARTY4, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + 105, DRAW_DIALOGBOX_PARTY4, 4,0,50);//"
		}
		else PutAlignedString(sX, sX + szX, sY + 105, DRAW_DIALOGBOX_PARTY4, 65,65,65);//"

		if (m_iPartyStatus != 0) {
			if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 120) && (msY < sY + 140))
				 PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY7, 255,255,255);//"
			else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY7, 4,0,50);//"
		}
		else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY7, 65,65,65);//"


		switch (m_iPartyStatus) {
		case 0:
			PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY10);//"
			PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY11);//"
			PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_PARTY12);//"
			break;

		case 1:
		case 2:
			PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY13);//"
			PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY14);//"
			PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_PARTY15);//"
			break;
		}

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
		break;

	case 1: //
		wsprintf(G_cTxt, DRAW_DIALOGBOX_PARTY16,  m_stDialogBoxInfo[32].cStr);
		PutAlignedString(sX, sX + szX, sY + 95, G_cTxt);
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY17);//"join the party. You can"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY18);//"share the experience by"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY19);//"the ratio of level if"
		PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY20);//"you join the party."
		PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_PARTY21);//"Would you like to join party?"

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;

	case 2:
		PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY22);//"Click the character which"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY23);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY24);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY25);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 3:
		wsprintf(G_cTxt, DRAW_DIALOGBOX_PARTY26, m_stDialogBoxInfo[32].cStr);//"
		PutAlignedString(sX, sX + szX, sY + 95, G_cTxt);
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY27);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY28);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY29);//"
		PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY30);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 4:
		PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY31);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY32);//"

		iNth = 0;
		for (i = 0; i <= DEF_MAXPARTYMEMBERS; i++)
		if (strlen(m_stPartyMemberNameList[i].cName) != 0) {
			wsprintf(G_cTxt, "%s", m_stPartyMemberNameList[i].cName);
			PutAlignedString(sX +17, sX +270, sY + 140 +15*(iNth), G_cTxt);
			iNth++;
		}

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 5:
		PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY33);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY34);//"
		break;

	case 6:
		PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY35);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 7:
		PutAlignedString(sX, sX + szX, sY + 95,  DRAW_DIALOGBOX_PARTY36);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY37);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY38);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY39);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 8:
		PutAlignedString(sX, sX + szX, sY + 95,  DRAW_DIALOGBOX_PARTY40);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY41);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY42);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY43);//"
		PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY44);//"
		PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY45);//"


		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 9:
		PutAlignedString(sX, sX + szX, sY + 95,  DRAW_DIALOGBOX_PARTY46);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY47);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY48);//"
		PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY49);//"
		PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY50);//"
		PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY51);//"

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 10:
		PutAlignedString(sX, sX + szX, sY + 95,  DRAW_DIALOGBOX_PARTY52);//"
		PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY53);//"
		PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY54);//"
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 11: //
		PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY55);//"
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
		break;
	}
}

void CGame::DrawDialogBox_QueryDropItemAmount()
{
 short sX, sY;
 char cTxt[120], cStr1[64], cStr2[64], cStr3[64];

	sX = m_stDialogBoxInfo[17].sX;
	sY = m_stDialogBoxInfo[17].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);

	switch (m_stDialogBoxInfo[17].cMode) {
	case 1:
		GetItemName( m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName, m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwAttribute, cStr1, cStr2, cStr3 );
		if (strlen(m_stDialogBoxInfo[17].cStr) == 0)
			 wsprintf(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT1, cStr1);
		else wsprintf(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT2, cStr1, m_stDialogBoxInfo[17].cStr);//"%s:

		if (m_stDialogBoxInfo[17].sV3 < 1000)
			PutString(sX + 30, sY + 20, cTxt, RGB(55,25,25));

		PutString(sX + 30, sY + 35, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT3, RGB(55,25,25));//"
		if (iGetTopDialogBoxIndex() != 17)
			PutString(sX + 40, sY + 57, m_cAmountString, RGB(255,255,255), FALSE, 2);
		wsprintf(cTxt, "__________ (0 ~ %d)", m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount);
		PutString(sX + 38, sY + 62, cTxt, RGB(25,35,25));
		break;

	case 20:
		GetItemName( m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName, m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwAttribute, cStr1, cStr2, cStr3 );
		if (strlen(m_stDialogBoxInfo[17].cStr) == 0) // v1.4
			 wsprintf(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT1, cStr1);//"%s:
		else wsprintf(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT2, cStr1, m_stDialogBoxInfo[17].cStr);//"%s:

		if (m_stDialogBoxInfo[17].sV3 < 1000) // v1.4
			PutString(sX + 30, sY + 20, cTxt, RGB(55,25,25));

		PutString(sX + 30, sY + 35, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT3, RGB(55,25,25));//"
		PutString(sX + 40, sY + 57, m_cAmountString, RGB(255,255,255), FALSE, 2);
		wsprintf(cTxt, "__________ (0 ~ %d)", m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount);
		PutString(sX + 38, sY + 62, cTxt, RGB(25,35,25));
		break;
	}
}


void CGame::DrawDialogBox_Quest(int msX, int msY)
{
 short sX, sY, szX;
 char cTxt[120], cTemp[21];

	sX = m_stDialogBoxInfo[28].sX;
	sY = m_stDialogBoxInfo[28].sY;
	szX = m_stDialogBoxInfo[28].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT , sX, sY, 4);

	switch (m_stDialogBoxInfo[28].cMode) {
	case 1:
		switch (m_stQuest.sQuestType) {
		case NULL:
			PutAlignedString(sX, sX + szX, sY + 50 +115 -30, DRAW_DIALOGBOX_QUEST1, 55,25,25); // " You are not on a quest."
			break;

		case 1:	//  Hunt
			if (m_stQuest.bIsQuestCompleted == FALSE)
				 PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST2, 55,25,25); // "You are on a monster conquering quest."
			else PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST3, 55,25,25); // "You accomplished the monster conquering quest."

			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, "Rest Monster : %d", m_stQuest.sCurrentCount); // Snoopy: "Rest Monster : %s"
			PutAlignedString(sX, sX + szX, sY + 50 +20, cTxt, 55,25,25);  // m_stQuest.sCurrentCount

			ZeroMemory(cTemp, sizeof(cTemp));
			switch (m_stQuest.sWho) {
			case 1:
			case 2:
			case 3: break;
			case 4: strcpy(cTemp, NPC_NAME_CITYHALL_OFFICER); break;
			case 5:
			case 6:
			case 7: break;
			}
			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt,  DRAW_DIALOGBOX_QUEST5, cTemp); // "Client: %s"
			PutAlignedString(sX, sX + szX, sY + 50 +45, cTxt, 55,25,25);

			ZeroMemory(cTemp, sizeof(cTemp));
			GetNpcName(m_stQuest.sTargetType, cTemp);
			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, NPC_TALK_HANDLER16, m_stQuest.sTargetCount, cTemp);
			PutAlignedString(sX, sX + szX, sY + 50 +60, cTxt, 55,25,25);

			ZeroMemory(cTxt, sizeof(cTxt));
			if (memcmp(m_stQuest.cTargetName, "NONE", 4) == 0)
			{	strcpy(cTxt, DRAW_DIALOGBOX_QUEST31); // "Location : Anywhere"
				PutAlignedString(sX, sX + szX, sY + 50 +75, cTxt, 55,25,25);
			}else
			{	ZeroMemory(cTemp, sizeof(cTemp));
				GetOfficialMapName(m_stQuest.cTargetName, cTemp);
				wsprintf(cTxt,  DRAW_DIALOGBOX_QUEST32, cTemp); // "Map : %s"
				PutAlignedString(sX, sX + szX, sY + 50 +75, cTxt, 55,25,25);

				if (m_stQuest.sX != 0) {
					ZeroMemory(cTxt, sizeof(cTxt));
					wsprintf(cTxt, DRAW_DIALOGBOX_QUEST33, m_stQuest.sX, m_stQuest.sY, m_stQuest.sRange); // "Position: %d, %d Range: %d block"
					PutAlignedString(sX, sX + szX, sY + 50 +90, cTxt, 55,25,25);
				}
			}

			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST34, m_stQuest.sContribution); // "Contribution: %d"
			PutAlignedString(sX, sX + szX, sY + 50 +105, cTxt, 55,25,25);
			break;

		case 7: //
			if (m_stQuest.bIsQuestCompleted == FALSE)
				 PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST26, 55,25,25);
			else PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST27, 55,25,25);

			ZeroMemory(cTemp, sizeof(cTemp));
			switch (m_stQuest.sWho) {
			case 1:
			case 2:
			case 3: break;
			case 4: strcpy(cTemp, NPC_NAME_CITYHALL_OFFICER); break;
			case 5:
			case 6:
			case 7: break;
			}
			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST29, cTemp);
			PutAlignedString(sX, sX + szX, sY + 50 +45, cTxt, 55,25,25);

			PutAlignedString(sX, sX + szX, sY + 50 +60, DRAW_DIALOGBOX_QUEST30, 55,25,25);

			ZeroMemory(cTxt, sizeof(cTxt));
			if (memcmp(m_stQuest.cTargetName, "NONE", 4) == 0) {
				strcpy(cTxt, DRAW_DIALOGBOX_QUEST31);
				PutAlignedString(sX, sX + szX, sY + 50 +75, cTxt, 55,25,25);
			}
			else {
				ZeroMemory(cTemp, sizeof(cTemp));
				GetOfficialMapName(m_stQuest.cTargetName, cTemp);
				wsprintf(cTxt, DRAW_DIALOGBOX_QUEST32, cTemp);
				PutAlignedString(sX, sX + szX, sY + 50 +75, cTxt, 55,25,25);

				if (m_stQuest.sX != 0) {
					ZeroMemory(cTxt, sizeof(cTxt));
					wsprintf(cTxt, DRAW_DIALOGBOX_QUEST33, m_stQuest.sX, m_stQuest.sY, m_stQuest.sRange);
					PutAlignedString(sX, sX + szX, sY + 50 +90, cTxt, 55,25,25);
				}
			}

			ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, DRAW_DIALOGBOX_QUEST34, m_stQuest.sContribution);//" %dPoint"
			PutAlignedString(sX, sX + szX, sY + 50 +105, cTxt, 55,25,25);
			break;
		}
		break;

	case 2:
		PutAlignedString(sX, sX + szX, sY + 50 +115 -30, DRAW_DIALOGBOX_QUEST35, 55,25,25);
		break;
	}

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void CGame::DrawDialogBox_SellList(short msX, short msY)
{
 short sX, sY, szX;
 int  i, iItem;
 char cTemp[255], cStr1[64], cStr2[64], cStr3[64];

	sX = m_stDialogBoxInfo[31].sX;
	sY = m_stDialogBoxInfo[31].sY;
	szX = m_stDialogBoxInfo[31].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

	iItem = 0;
	for (i = 0; i < DEF_MAXSELLLIST; i++)
	if (m_stSellItemList[i].iIndex != -1)
	{
		ZeroMemory(cTemp, sizeof(cTemp));
		GetItemName(m_pItemList[m_stSellItemList[i].iIndex]->m_cName, m_pItemList[m_stSellItemList[i].iIndex]->m_dwAttribute, cStr1, cStr2, cStr3);
		if (m_stSellItemList[i].iAmount > 1 )
		{	wsprintf(cTemp, DRAW_DIALOGBOX_SELL_LIST1, m_stSellItemList[i].iAmount, cStr1);
			if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i*15) && (msY <= sY + 55 + 14 + i*15))
				 PutAlignedString(sX, sX+szX, sY + 55 + i*15, cTemp, 255,255,255);
			else
			{
				if(m_bIsSpecial)
					PutAlignedString(sX, sX+szX, sY + 55 + i*15, cTemp, 0,255,50);
				else
					PutAlignedString(sX, sX+szX, sY + 55 + i*15, cTemp, 45,25,25);
			}
		}
		else
		{
			if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i*15) && (msY <= sY + 55 + 14 + i*15))
			{
				if( (strlen(cStr2)==0) && (strlen(cStr3)==0) ) PutAlignedString(sX, sX+szX, sY + 55 + i*15, cStr1, 255,255,255);
				else
				{
					ZeroMemory( G_cTxt, sizeof(G_cTxt) );
					if( (strlen(cStr1)+strlen(cStr2)+strlen(cStr3)) < 36 )
					{
						if( (strlen(cStr2)>0) && (strlen(cStr3)>0) ) wsprintf( G_cTxt, "%s(%s, %s)", cStr1, cStr2, cStr3 );
						else wsprintf( G_cTxt, "%s(%s%s)", cStr1, cStr2, cStr3 );
						PutAlignedString(sX, sX+szX, sY + 55 + i*15, G_cTxt, 255,255,255);

					}
					else
					{
						if( (strlen(cStr2)>0) && (strlen(cStr3)>0) ) wsprintf( G_cTxt, "(%s, %s)", cStr2, cStr3 );
						else wsprintf( G_cTxt, "(%s%s)", cStr2, cStr3 );
						PutAlignedString(sX, sX+szX, sY + 55 + i*15, cStr1, 255,255,255);
						PutAlignedString(sX, sX+szX, sY + 55 + i*15 + 15, G_cTxt, 200,200,200);
						i++;
					}
				}
			}else
			{	if( (strlen(cStr2)==0) && (strlen(cStr3)==0) )
				{	if(m_bIsSpecial)
						PutAlignedString(sX, sX+szX, sY + 55 + i*15, cStr1, 0,255,50);
					else
						PutAlignedString(sX, sX+szX, sY + 55 + i*15, cStr1, 45,25,25);
				}else
				{	ZeroMemory( G_cTxt, sizeof(G_cTxt) );
					if( (strlen(cStr1)+strlen(cStr2)+strlen(cStr3)) < 36 )
					{
						if( (strlen(cStr2)>0) && (strlen(cStr3)>0) ) wsprintf( G_cTxt, "%s(%s, %s)", cStr1, cStr2, cStr3 );
						else wsprintf( G_cTxt, "%s(%s%s)", cStr1, cStr2, cStr3 );

						if(m_bIsSpecial)
							PutAlignedString(sX, sX+szX, sY + 55 + i*15, G_cTxt, 0,255,50);
						else
							PutAlignedString(sX, sX+szX, sY + 55 + i*15, G_cTxt, 45,25,25);

					}
					else
					{	if(m_bIsSpecial)
							PutAlignedString(sX, sX+szX, sY + 55 + i*15, cStr1, 0,255,50);
						else
							PutAlignedString(sX, sX+szX, sY + 55 + i*15, cStr1, 45,25,25);
					}
				}
			}
		}
	}
	else iItem++;

	if (iItem == DEF_MAXSELLLIST) {
		PutAlignedString(sX, sX+szX, sY + 55 + 30 + 282 -117 -170, DRAW_DIALOGBOX_SELL_LIST2);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 45 + 282 -117 -170, DRAW_DIALOGBOX_SELL_LIST3);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 60 + 282 -117 -170, DRAW_DIALOGBOX_SELL_LIST4);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 75 + 282 -117 -170, DRAW_DIALOGBOX_SELL_LIST5);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 95 + 282 -117 -170, DRAW_DIALOGBOX_SELL_LIST6);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 110 + 282 -117 -170,DRAW_DIALOGBOX_SELL_LIST7);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 125 + 282 -117 -170,DRAW_DIALOGBOX_SELL_LIST8);//"
		PutAlignedString(sX, sX+szX, sY + 55 + 155 + 282 -117 -170,DRAW_DIALOGBOX_SELL_LIST9);//"

	}

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY) && (iItem < DEF_MAXSELLLIST) )
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 39);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 38);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void CGame::DrawDialogBox_SellorRepairItem(short msX, short msY)
{
 short sX, sY;
 DWORD dwTime = m_dwCurTime;
 char cItemID, cItemColor, cTxt[120], cTemp[120], cStr2[120], cStr3[120];

	sX = m_stDialogBoxInfo[23].sX;
	sY = m_stDialogBoxInfo[23].sY;

	switch (m_stDialogBoxInfo[23].cMode) {
	case 1:
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

		cItemID = m_stDialogBoxInfo[23].sV1;

		cItemColor = m_pItemList[cItemID]->m_cItemColor;
		if (cItemColor == 0)
			 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteFast(sX + 62 + 15, sY + 84 + 30,
	                                                                                                   m_pItemList[cItemID]->m_sSpriteFrame, dwTime);
		else
		{	switch (m_pItemList[cItemID]->m_sSprite) {
			case 1: // Swds
			case 2: // Bows
			case 3: // Shields
			case 15: // Axes hammers
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
						, m_pItemList[cItemID]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
				break;
			default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
					 	, m_pItemList[cItemID]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
				break;
			}
		}
		ZeroMemory(cTemp, sizeof(cTemp));
		ZeroMemory(cStr2, sizeof(cStr2));
		ZeroMemory(cStr3, sizeof(cStr3));

		GetItemName(m_pItemList[cItemID]->m_cName, m_pItemList[cItemID]->m_dwAttribute, cTemp, cStr2, cStr3);
		if( m_stDialogBoxInfo[23].sV4 == 1 ) strcpy( cTxt, cTemp );
		else wsprintf(cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM1, m_stDialogBoxInfo[23].sV4, cTemp);

		if(m_bIsSpecial)
		{
			PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 0,255,50);
			PutAlignedString(sX + 25 +1, sX + 240 +1, sY + 60, cTxt, 0,255,50);
		}
		else
		{
			PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 45,25,25);
			PutAlignedString(sX + 25 +1, sX + 240 +1, sY + 60, cTxt, 45,25,25);
		}

		wsprintf(cTxt,  DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM2, m_stDialogBoxInfo[23].sV2);
		PutString(sX + 95 + 15, sY + 53 + 60, cTxt, RGB(45,25,25));
		wsprintf(cTxt,  DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM3, m_stDialogBoxInfo[23].sV3);
		PutString(sX + 95 + 15, sY + 53 + 75, cTxt, RGB(45,25,25));
		PutString(sX + 55, sY + 190, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM4, RGB(45,25,25));

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX +DEF_LBTNPOSX, sY + DEF_BTNPOSY, 39);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX +DEF_LBTNPOSX, sY + DEF_BTNPOSY, 38);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX +DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX +DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 2:
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 10);
		cItemID = m_stDialogBoxInfo[23].sV1;
		cItemColor = m_pItemList[cItemID]->m_cItemColor; // v1.4
		if (cItemColor == 0)
			 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteFast(sX + 62 + 15, sY + 84 + 30,
			                                                                                           m_pItemList[cItemID]->m_sSpriteFrame, dwTime);
		else
		{	switch (m_pItemList[cItemID]->m_sSprite) {
			case 1: // Swds
			case 2: // Bows
			case 3: // Shields
			case 15: // Axes hammers
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
					, m_pItemList[cItemID]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
				break;

			default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
						 , m_pItemList[cItemID]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
				break;
			}
		}
		ZeroMemory(cTemp, sizeof(cTemp));
		ZeroMemory(cStr2, sizeof(cStr2));
		ZeroMemory(cStr3, sizeof(cStr3));
		GetItemName(m_pItemList[cItemID], cTemp, cStr2, cStr3);
		wsprintf(cTxt, "%s", cTemp);
//		PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 45,25,25);
//		PutAlignedString(sX + 25 +1, sX + 240 +1, sY + 60, cTxt, 45,25,25);
		if(m_bIsSpecial)
		{	PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 0,255,50);
			PutAlignedString(sX + 25 +1, sX + 240 +1, sY + 60, cTxt, 0,255,50);
		}else
		{	PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 45,25,25);
			PutAlignedString(sX + 25 +1, sX + 240 +1, sY + 60, cTxt, 45,25,25);
		}
		wsprintf(cTxt,  DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM2, m_stDialogBoxInfo[23].sV2);
		PutString(sX + 95 + 15, sY + 53 + 60, cTxt, RGB(45,25,25));
		wsprintf(cTxt,  DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM6, m_stDialogBoxInfo[23].sV3);
		PutString(sX + 95 + 15, sY + 53 + 75, cTxt, RGB(45,25,25));
		PutString(sX + 55, sY + 190, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM7, RGB(45,25,25));

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 43);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 42);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 3:
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

		PutString(sX + 55, sY + 100, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM8, RGB(45,25,25));//"
		PutString(sX + 55, sY + 120, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM9, RGB(45,25,25));//"
		PutString(sX + 55, sY + 135, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM10, RGB(45,25,25));//"
		break;

	case 4:
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 10);

		PutString(sX + 55, sY + 100, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM11, RGB(45,25,25));//"
		PutString(sX + 55, sY + 120, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM9, RGB(45,25,25));//"
		PutString(sX + 55, sY + 135, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM10, RGB(45,25,25));//"
		break;
	}
}

void CGame::DrawDialogBox_Shop(short msX, short msY, short msZ, char cLB)
{short sX, sY;
 DWORD dwTime = m_dwCurTime;
 int  i, iTemp;
 char cTemp[255], cStr2[255], cStr3[255];

 int  iCost, iDiscountCost, iDiscountRatio;

 double dTmp1, dTmp2, dTmp3;
 int  iTotalLines, iPointerLoc;
 BOOL bFlagStatLow = FALSE;
 BOOL bFlagRedShown = FALSE;
 double d1, d2, d3;

	sX = m_stDialogBoxInfo[11].sX;
	sY = m_stDialogBoxInfo[11].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

	switch (m_stDialogBoxInfo[11].cMode) {
	case 0:
		iTotalLines = 0;
		for (i = 0; i < DEF_MAXMENUITEMS; i++)
		if (m_pItemForSaleList[i] != NULL) iTotalLines++;
		if (iTotalLines > 13) {
			d1 = (double)m_stDialogBoxInfo[11].sView;
			d2 = (double)(iTotalLines-13);
			d3 = (274.0f * d1)/d2;
			iPointerLoc = (int)(d3);
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX+242, sY + iPointerLoc + 35, 7);
		}else iPointerLoc = 0;

		if (cLB != 0 && iTotalLines > 13)
		{	if ((iGetTopDialogBoxIndex() == 11))
			{	if ((msX >= sX + 235) && (msX <= sX + 260) && (msY >= sY + 10) && (msY <= sY + 330))
				{ 	d1 = (double)(msY -(sY+35));
					d2 = (double)(iTotalLines-13);
					d3 = (d1 * d2)/274.0f;
					m_stDialogBoxInfo[11].sView = (int)(d3+0.5);
			}	}
		}else m_stDialogBoxInfo[11].bIsScrollSelected = FALSE;
		if( iGetTopDialogBoxIndex() == 11 && msZ != 0 )
		{	m_stDialogBoxInfo[11].sView = m_stDialogBoxInfo[11].sView - msZ/60;
			m_DInput.m_sZ = 0;
		}
		if( iTotalLines > 13 && m_stDialogBoxInfo[11].sView > iTotalLines-13 ) m_stDialogBoxInfo[11].sView = iTotalLines-13;
		if( m_stDialogBoxInfo[11].sView < 0 || iTotalLines < 13 ) m_stDialogBoxInfo[11].sView = 0;
		PutAlignedString(sX + 22, sX +165, sY + 45, DRAW_DIALOGBOX_SHOP1); // "ITEM"
		PutAlignedString(sX + 23, sX +166, sY + 45, DRAW_DIALOGBOX_SHOP1);
		PutAlignedString(sX +153, sX +250, sY + 45, DRAW_DIALOGBOX_SHOP3);
		PutAlignedString(sX +154, sX +251, sY + 45, DRAW_DIALOGBOX_SHOP3);

		for (i = 0; i < 13; i++)
		if (((i+ m_stDialogBoxInfo[11].sView) < DEF_MAXMENUITEMS) && (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView] != NULL))
		{	ZeroMemory(cTemp, sizeof(cTemp));
			GetItemName(m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView], cTemp, cStr2, cStr3);
			if ((msX >= sX + 20) && (msX <= sX + 220) && (msY >= sY + i*18 + 65) && (msY <= sY + i*18 + 79))
			{	  PutAlignedString(sX +10, sX +190, sY + i*18 + 65, cTemp, 255, 255, 255);
			}else PutAlignedString(sX +10, sX +190, sY + i*18 + 65, cTemp, 4,0,50);
		}

		for (i = 0; i < 13; i++)
		if (((i+ m_stDialogBoxInfo[11].sView) < DEF_MAXMENUITEMS) && (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView] != NULL))
		{
			iDiscountRatio = ((m_iCharisma - 10)  / 4) ;
			dTmp1 = (double)iDiscountRatio;
			dTmp2 = dTmp1 / 100.0f;
			dTmp1 = (double)m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice;
			dTmp3 = dTmp1 * dTmp2;
			iDiscountCost = (int)dTmp3;
			iCost = (int)(m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice * ((100 + m_cDiscount)/100.) );
			iCost = iCost - iDiscountCost;

			if (iCost < (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice/2))
				iCost = (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice/2) - 1;
			ZeroMemory(cTemp, sizeof(cTemp));
			wsprintf(cTemp, "%6d", iCost);
			if ((msX >= sX+20) && (msX <= sX+220) && (msY >= sY+i*18+65) && (msY <= sY+i*18+79))
					PutAlignedString(sX+148, sX+260, sY+i*18+65, cTemp, 255, 255, 255);
			else	PutAlignedString(sX+148, sX+260, sY+i*18+65, cTemp, 4,0,50);
		}
		break;

	default:
		m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sSprite]->PutSpriteFast(sX + 62 + 30 -35, sY + 84 + 30 -10,
		          m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sSpriteFrame, dwTime);

		ZeroMemory(cTemp, sizeof(cTemp));
		GetItemName(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode-1], cTemp, cStr2, cStr3);

		PutAlignedString(sX +25, sX+240, sY+50, cTemp, 255,255,255);
		PutAlignedString(sX +26, sX+241, sY+50, cTemp, 255,255,255);

		strcpy(cTemp, DRAW_DIALOGBOX_SHOP3); //"PRICE"
		PutString(sX + 90, sY + 78 + 30 -10, cTemp, RGB(40,10,10));
		PutString(sX + 91, sY + 78 + 30 -10, cTemp, RGB(40,10,10));
		strcpy(cTemp, DRAW_DIALOGBOX_SHOP6); // "Weight"
		PutString(sX + 90, sY + 93 + 30 -10, cTemp, RGB(40,10,10));
		PutString(sX + 91, sY + 93 + 30 -10, cTemp, RGB(40,10,10));

		iDiscountRatio = ((m_iCharisma -10) / 4) ;
		dTmp1 = (double)iDiscountRatio;
		dTmp2 = dTmp1 / 100.0f;
		dTmp1 = (double)m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice;
		dTmp3 = dTmp1 * dTmp2;
		iDiscountCost = (int)dTmp3;
		iCost = (int)(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice * ((100 +m_cDiscount)/100.) );
		iCost = iCost - iDiscountCost;

		if (iCost < (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice/2))
				iCost = (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice/2) - 1;

		wsprintf(cTemp, DRAW_DIALOGBOX_SHOP7, iCost );
		                //": %d Gold"
		PutString(sX + 140, sY + 98, cTemp, RGB(45,25,25));

		iTemp = m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100;
		wsprintf(cTemp, DRAW_DIALOGBOX_SHOP8, iTemp);
		               //": %d Stone"
		PutString(sX + 140, sY + 113, cTemp, RGB(45,25,25));

		switch (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cEquipPos) {
		case DEF_EQUIPPOS_RHAND:
		case DEF_EQUIPPOS_TWOHAND:
			strcpy(cTemp, DRAW_DIALOGBOX_SHOP9);  // Damage
			PutString(sX + 90, sY + 145, cTemp, RGB(40,10,10));
			PutString(sX + 91, sY + 145, cTemp, RGB(40,10,10));
			strcpy(cTemp, DRAW_DIALOGBOX_SHOP10); //"Speed(Min.~Max.)"
			PutString(sX + 40, sY + 175, cTemp, RGB(40,10,10));
			PutString(sX + 41, sY + 175, cTemp, RGB(40,10,10));

			if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue3 != 0)
			{	wsprintf(cTemp, ": %dD%d+%d (S-M)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1,
					                                m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue2,
								                    m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue3);
			}else
			{	wsprintf(cTemp, ": %dD%d (S-M)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1,
					                             m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue2);
			}
			PutString(sX + 140, sY + 145, cTemp, RGB(45,25,25));
			if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue6 != 0)
			{	wsprintf(cTemp, ": %dD%d+%d (L)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue4,
					                              m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5,
								                  m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue6);
			}else
			{	wsprintf(cTemp, ": %dD%d (L)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue4,
					                           m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
			}
			PutString(sX + 140, sY + 160, cTemp, RGB(45,25,25));
			if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cSpeed == 0)   wsprintf(cTemp, ": 0(10~10)");
			else wsprintf(cTemp, ": %d(%d ~ %d)",m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cSpeed, iTemp,m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cSpeed*13);
			PutString(sX + 140, sY + 175, cTemp, RGB(45,25,25));

			if ((m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100) > m_iStr)
			{	wsprintf(cTemp,DRAW_DIALOGBOX_SHOP11, (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100)) ;
				PutAlignedString(sX +25, sX+240, sY + 258, cTemp, 195,25,25);
				PutAlignedString(sX +26, sX+241, sY + 258, cTemp, 195,25,25); // *Your STR should be at least %d to use this item."
				bFlagRedShown = TRUE;
			}
			break;

		case DEF_EQUIPPOS_LHAND:
			strcpy(cTemp, DRAW_DIALOGBOX_SHOP12); // "Defence"
			PutString(sX + 90, sY + 145, cTemp, RGB(40,10,10));
			PutString(sX + 91, sY + 145, cTemp, RGB(40,10,10));
			wsprintf(cTemp, ": +%d%", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1);
			PutString(sX + 140, sY + 145, cTemp, RGB(45,25,25));
			if ((m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100) > m_iStr)
			{	wsprintf(cTemp,DRAW_DIALOGBOX_SHOP11, (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100)) ;
				PutAlignedString(sX +25, sX+240, sY + 258, cTemp, 195,25,25); // "*Your STR should be at least %d to use this item."
				PutAlignedString(sX +26, sX+241, sY + 258, cTemp, 195,25,25);
				bFlagRedShown = TRUE;
			}
			break;

		case DEF_EQUIPPOS_HEAD:
		case DEF_EQUIPPOS_BODY:
		case DEF_EQUIPPOS_BOOTS:
		case DEF_EQUIPPOS_ARMS:
		case DEF_EQUIPPOS_PANTS:
			strcpy(cTemp, DRAW_DIALOGBOX_SHOP12); // "Defence"
			PutString(sX + 90, sY + 145, cTemp, RGB(40,10,10));
			PutString(sX + 91, sY + 145, cTemp, RGB(40,10,10));
			wsprintf(cTemp, ": +%d%", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1);
			PutString(sX + 140, sY + 145, cTemp, RGB(45,25,25));
			bFlagStatLow = FALSE;
			switch(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue4) {
			case 10://"Available for above Str %d"
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP15, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
				if (m_iStr >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 45,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 45,25,25);
				}else
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 125,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 125,25,25);
					bFlagStatLow = TRUE; // Means some red msg need to be shown at the bottom
				}
				break;
			case 11: // "Available for above Dex %d"
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP16, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
				if (m_iDex >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 45,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 45,25,25);
				}else
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 125,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 125,25,25);
					bFlagStatLow = TRUE; // Means some red msg need to be shown at the bottom
				}
				break;
			case 12: // "Available for above Vit %d"
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP17, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
				if (m_iVit >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 45,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 45,25,25);
				}else
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 125,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 125,25,25);
					bFlagStatLow = TRUE; // Means some red msg need to be shown at the bottom
				}
				break;
			case 13: // "Available for above Int %d"
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP18, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
				if (m_iInt >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 45,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 45,25,25);
				}else
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 125,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 125,25,25);
					bFlagStatLow = TRUE; // Means some red msg need to be shown at the bottom
				}
				break;
			case 14: // "Available for above Mag %d"
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP19, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
				if (m_iMag >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 45,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 45,25,25);
				}else
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 125,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 125,25,25);
					bFlagStatLow = TRUE; // Means some red msg need to be shown at the bottom
				}
				break;
			case 15: // "Available for above Chr %d"
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP20, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
				if (m_iCharisma >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 45,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 45,25,25);
				}else
				{	PutAlignedString(sX +25, sX+240, sY + 160, cTemp, 125,25,25);
					PutAlignedString(sX +26, sX+241, sY + 160, cTemp, 125,25,25);
					bFlagStatLow = TRUE; // Means some red msg need to be shown at the bottom
				}
				break;

			default:
				break;
			}
			if ((m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100) > m_iStr)
			{	wsprintf(cTemp,DRAW_DIALOGBOX_SHOP11, (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight/100)) ;
				PutAlignedString(sX +25, sX+240, sY + 288, cTemp, 195,25,25);
				PutAlignedString(sX +26, sX+241, sY + 288, cTemp, 195,25,25); // "*Your STR should be at least %d to use this item."
				bFlagRedShown = TRUE;
			}else if (bFlagStatLow == TRUE) // Means some stat is too low
			{	strcpy(cTemp, DRAW_DIALOGBOX_SHOP21); // "(Warning!) Your stat is too low for this item."
				PutAlignedString(sX +25, sX+240, sY + 258, cTemp, 195,25,25);
				PutAlignedString(sX +26, sX+241, sY + 258, cTemp, 195,25,25);
				bFlagRedShown = TRUE;
			}else if ( (strstr(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cName, "(M)") != NULL)
					&& (m_sPlayerType > 3))
			{	strcpy(cTemp, DRAW_DIALOGBOX_SHOP22); // "(Warning!) only for male."
				PutAlignedString(sX +25, sX+240, sY + 258, cTemp, 195,25,25);
				PutAlignedString(sX +26, sX+241, sY + 258, cTemp, 195,25,25);
				bFlagRedShown = TRUE;
			}else if ( (strstr(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cName, "(W)") != NULL)
					&& (m_sPlayerType <= 3))
			{	strcpy(cTemp, DRAW_DIALOGBOX_SHOP23); // "(Warning!) only for female."
				PutAlignedString(sX +25, sX+240, sY + 258, cTemp, 195,25,25);
				PutAlignedString(sX +26, sX+241, sY + 258, cTemp, 195,25,25);
				bFlagRedShown = TRUE;
			}
			break;

		case DEF_EQUIPPOS_NONE:
			break;
		}

		if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit != 0)
		{	strcpy(cTemp, DRAW_DIALOGBOX_SHOP24); // "Level"
			if (m_iLevel >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit)
			{	PutString(sX + 90, sY + 190, cTemp, RGB(40,10,10));
				PutString(sX + 91, sY + 190, cTemp, RGB(40,10,10));
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP25, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit);
				PutString(sX + 140, sY + 190, cTemp, RGB(45,25,25));// ": above %d"
			}else
			{	PutString(sX + 90, sY + 190, cTemp, RGB(40,10,10));
				PutString(sX + 91, sY + 190, cTemp, RGB(40,10,10));
				wsprintf(cTemp, DRAW_DIALOGBOX_SHOP25, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit);
				PutString(sX + 140, sY + 190, cTemp, RGB(125,25,25));// ": above %d"
				if (bFlagRedShown == FALSE)
				{	strcpy(cTemp, DRAW_DIALOGBOX_SHOP26); // "(Warning!) Your level is too low for this item."
					PutAlignedString(sX +25	  , sX+240   , sY + 258, cTemp, 195,25,25);
					PutAlignedString(sX +25 +1, sX+240 +1, sY + 258, cTemp, 195,25,25);
					bFlagRedShown = TRUE;
		}	}	}

		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + 156, sY + 219, 19, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + 170, sY + 219, 19, dwTime);
		PutString(sX + 123 -35, sY + 237 -10, DRAW_DIALOGBOX_SHOP27, RGB(40,10,10)); // "Quantity:"
		PutString(sX + 124 -35, sY + 237 -10, DRAW_DIALOGBOX_SHOP27, RGB(40,10,10));
		if( iGetTopDialogBoxIndex() == 11 && msZ != 0 )
		{	m_stDialogBoxInfo[11].sV3 = m_stDialogBoxInfo[11].sV3 + msZ/60;
			m_DInput.m_sZ = 0;
		}
		if (m_stDialogBoxInfo[11].sV3 > (50 - _iGetTotalItemNum())) m_stDialogBoxInfo[11].sV3 = (50 - _iGetTotalItemNum());
		if (m_stDialogBoxInfo[11].sV3 < 1) m_stDialogBoxInfo[11].sV3 = 1;

		if (m_stDialogBoxInfo[11].sV3 >= 10)
		{	ZeroMemory(cTemp, sizeof(cTemp));
			_itoa(m_stDialogBoxInfo[11].sV3, cTemp, 10);
			cTemp[1] = NULL;
			PutString(sX -35 + 186, sY -10 + 237, cTemp, RGB(40,10,10));
			PutString(sX -35 + 187, sY -10 + 237, cTemp, RGB(40,10,10));
			ZeroMemory(cTemp, sizeof(cTemp));
			_itoa(m_stDialogBoxInfo[11].sV3, cTemp, 10);
			PutString(sX -35 + 200, sY -10 + 237, (cTemp+1), RGB(40,10,10));
			PutString(sX -35 + 201, sY -10 + 237, (cTemp+1), RGB(40,10,10));
		}else
		{	PutString(sX -35 + 186, sY -10 + 237, "0", RGB(40,10,10));
			PutString(sX -35 + 187, sY -10 + 237, "0", RGB(40,10,10));
			ZeroMemory(cTemp, sizeof(cTemp));
			_itoa(m_stDialogBoxInfo[11].sV3, cTemp, 10);
			PutString(sX -35 + 200, sY -10 + 237, (cTemp), RGB(40,10,10));
			PutString(sX -35 + 201, sY -10 + 237, (cTemp), RGB(40,10,10));
		}
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX +156, sY + 244, 20, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX +170, sY + 244, 20, dwTime);

		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;
	}
}

void CGame::DrawDialogBox_Skill(short msX, short msY, short msZ, char cLB)
{
 short sX, sY;
 int  i, iTotalLines, iPointerLoc;
 char cTemp[255], cTemp2[255];
 double d1,d2,d3;

	sX = m_stDialogBoxInfo[15].sX;
	sY = m_stDialogBoxInfo[15].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0); // Normal Dialog
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 1); // Skill Dialog Title Bar

	switch (m_stDialogBoxInfo[15].cMode) {
	case 0:
		for (i = 0; i < 17; i++)
		if ((i < DEF_MAXSKILLTYPE) && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView] != NULL))
		{	ZeroMemory(cTemp, sizeof(cTemp));
			wsprintf(cTemp, "%s", m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_cName);
			m_Misc.ReplaceString(cTemp, '-', ' ');
			ZeroMemory(cTemp2, sizeof(cTemp2));
			wsprintf(cTemp2, "%3d%%", m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel);
			if ((msX >= sX + 25) && (msX <= sX + 166) && (msY >= sY + 45 + i*15) && (msY <= sY + 59 + i*15))
			{	if (   (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_bIsUseable == TRUE)
					&& (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel != 0) )
				{	PutString(sX + 30,  sY + 45 + i*15, cTemp, RGB(255,255,255));
					PutString(sX + 183, sY + 45 + i*15, cTemp2, RGB(255,255,255));
				}else
				{	PutString(sX + 30,  sY + 45 + i*15, cTemp, RGB(5,5,5));
					PutString(sX + 183, sY + 45 + i*15, cTemp2, RGB(5,5,5));
				}
			}else
			{	if (   (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_bIsUseable == TRUE)
					&& (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel != 0) )
				{	PutString(sX + 30, sY + 45 + i*15, cTemp, RGB(34,30,120));
					PutString(sX + 183, sY + 45 + i*15, cTemp2, RGB(34,30,120));
			   	}else
				{	PutString(sX + 30, sY + 45 + i*15, cTemp, RGB(5,5,5));
					PutString(sX + 183, sY + 45 + i*15, cTemp2, RGB(5,5,5));
			}	}

			if (m_iDownSkillIndex == (i + m_stDialogBoxInfo[15].sView))
				 m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(sX + 215, sY + 47 + i*15, 21, 50,50,50, m_dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + 215, sY + 47 + i*15, 20, m_dwTime);
		}

		iTotalLines = 0;
		for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		if (m_pSkillCfgList[i] != NULL) iTotalLines++;

		if (iTotalLines > 17)
		{	d1 = (double)m_stDialogBoxInfo[15].sView;
			d2 = (double)(iTotalLines-17);
			d3 = (274.0f * d1)/d2;
			iPointerLoc = (int)d3;
		}
		else iPointerLoc = 0;
		if( iTotalLines > 17 )
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX+242, sY+iPointerLoc + 35, 7);
		}

		if (cLB != 0 && iTotalLines > 17)
		{	if ((iGetTopDialogBoxIndex() == 15))
			{	if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 30) && (msY <= sY + 320))
				{	d1 = (double)(msY -(sY+35));
					d2 = (double)(iTotalLines-17);
					d3 = (d1 * d2)/274.0f;
					iPointerLoc = (int)(d3+0.5);
					if (iPointerLoc > iTotalLines - 17) iPointerLoc = iTotalLines -17;
					m_stDialogBoxInfo[15].sView = iPointerLoc;
			}	}
		}else m_stDialogBoxInfo[15].bIsScrollSelected = FALSE;
		if( iGetTopDialogBoxIndex() == 15 && msZ != 0 )
		{	if( msZ > 0 ) m_stDialogBoxInfo[15].sView--;
			if( msZ < 0 ) m_stDialogBoxInfo[15].sView++;
			m_DInput.m_sZ = 0;
		}
		if( m_stDialogBoxInfo[15].sView < 0 ) m_stDialogBoxInfo[15].sView = 0;
		if( iTotalLines > 17 && m_stDialogBoxInfo[15].sView > iTotalLines-17 ) m_stDialogBoxInfo[15].sView = iTotalLines-17;
	   	break;
	}
}

void CGame::DrawDialogBox_SkillDlg(short msX, short msY, short msZ, char cLB)
{
 int i, iLoc ,iAdjX, iAdjY;
 char cTemp[120], cTemp2[120];
 short sX, sY, szX;
 char cStr1[64], cStr2[64], cStr3[64];
 DWORD dwTime = m_dwCurTime;

	iAdjX = 5 ;
	iAdjY = 8 ;

	switch (m_stDialogBoxInfo[26].cMode) {
	case 1: // Alchemy waiting incredients
		if (m_stDialogBoxInfo[26].cStr[0] != 0)
		{	sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
			sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
		}else
		{	sX = m_stDialogBoxInfo[26].sX;
			sY = m_stDialogBoxInfo[26].sY;
		}

		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX, sY, 1, dwTime);

		if (m_stDialogBoxInfo[26].sV1 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV2 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +45*1 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV3 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +45*2 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV4 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV5 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55+45*1 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV6 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55+45*2 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

		if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
			 PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 16,16,30);
		else PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 6, 6, 20);

		break;

	case 2: // Alchemy, creating a potion
		if (m_stDialogBoxInfo[26].cStr[0] != 0) {
			sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
			sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
		}else
		{	sX = m_stDialogBoxInfo[26].sX;
			sY = m_stDialogBoxInfo[26].sY;
		}
		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX, sY, 1, dwTime);

		if (m_stDialogBoxInfo[26].sV1 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV2 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +45*1 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV3 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +45*2 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV4 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV5 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55+45*1 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV6 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55+45*2 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

		PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Creating...", 20,6,6);


		if ((dwTime - m_stDialogBoxInfo[26].dwT1) > 1000)
		{	m_stDialogBoxInfo[26].dwT1 = dwTime;
			m_stDialogBoxInfo[26].cStr[0]++;
		}

		if (m_stDialogBoxInfo[26].cStr[0] >= 5)
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_CREATEPORTION, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(26);
			PlaySound('E', 42, 0);
		}
		break;

	case 3: // Manuf: Choose what you want to create
		sX = m_stDialogBoxInfo[26].sX;
		sY = m_stDialogBoxInfo[26].sY;
		szX = m_stDialogBoxInfo[26].sSizeX;
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
		PutString(sX + iAdjX + 44, sY + iAdjY + 38, "Name", RGB(0,0,0));
		PutString(sX + iAdjX +171, sY + iAdjY + 38, "Max.Skill", RGB(0,0,0));

		iLoc = 0;
		for (i = 0; i < 13; i++)
		if (m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView] != NULL) {

			ZeroMemory(cTemp, sizeof(cTemp));
			GetItemName( m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView]->m_cName, NULL, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			ZeroMemory(cTemp2, sizeof(cTemp2));
			wsprintf(cTemp2, "%d%%", m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView]->m_iMaxSkill);

			if ((msX >= sX + 30) && (msX <= sX + 180) && (msY >= sY + iAdjY + 55 + iLoc*15) && (msY <= sY + iAdjY + 69 + iLoc*15))
			{	PutString(sX + 30, sY + iAdjY + 55 + iLoc*15, cTemp, RGB(255,255,255));
				PutString(sX + 190, sY + iAdjY + 55 + iLoc*15, cTemp2, RGB(255,255,255));
			}else
			{	if (m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView]->m_bBuildEnabled == TRUE)
				{	 PutString(sX + 30, sY + iAdjY + 55 + iLoc*15, cTemp, RGB(34,30,120));
					 PutString(sX + 190, sY + iAdjY + 55 + iLoc*15, cTemp2, RGB(34,30,120));
				}else
				{	PutString(sX + 30, sY + iAdjY + 55 + iLoc*15, cTemp, RGB(45,25,25));
					PutString(sX + 190, sY + iAdjY + 55 + iLoc*15, cTemp2, RGB(45,25,25));
				}
			}

			iLoc++;
		}
		if ((m_stDialogBoxInfo[26].sView >= 1) && (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView - 1] != NULL))
			 m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + iAdjX + 225, sY + iAdjY + 210, 23, dwTime);
		else m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSpriteRGB(sX + iAdjX + 225, sY + iAdjY + 210, 23, 5,5,5, dwTime);

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView+13] != NULL)
			 m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + iAdjX + 225, sY + iAdjY + 230, 24, dwTime);
		else m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSpriteRGB(sX + iAdjX + 225, sY + iAdjY + 230, 24, 5,5,5, dwTime);

		if ((cLB != 0) && (iGetTopDialogBoxIndex() == 26)) {
			if ((msX >= sX + iAdjX + 225) && (msX <= sX + iAdjX + 245) && (msY >= sY + iAdjY + 210) && (msY <= sY + iAdjY + 230)) {
				m_stDialogBoxInfo[26].sView--;
			}

			if ((msX >= sX + iAdjX + 225) && (msX <= sX + iAdjX + 245) && (msY >= sY + iAdjY + 230) && (msY <= sY + iAdjY + 250)) {
				if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView + 13] != NULL)
					m_stDialogBoxInfo[26].sView++;
			}
		}
		if (( msZ != 0) && (iGetTopDialogBoxIndex() == 26)) {
			m_stDialogBoxInfo[26].sView = m_stDialogBoxInfo[26].sView - msZ/60;
			m_DInput.m_sZ = 0;
		}
		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView + 12] == NULL)
		{
			while(1)
			{
				m_stDialogBoxInfo[26].sView --;
				if( m_stDialogBoxInfo[26].sView < 1 ) break;
				if( m_pDispBuildItemList[m_stDialogBoxInfo[26].sView+12] != NULL ) break;
			}
		}
		if (m_stDialogBoxInfo[26].sView < 0) m_stDialogBoxInfo[26].sView = 0;

		PutAlignedString(sX, sX+m_stDialogBoxInfo[26].sSizeX, sY + 265, DRAW_DIALOGBOX_SKILLDLG2, 55,25,25);//" List of items which you can make with"
		PutAlignedString(sX, sX+m_stDialogBoxInfo[26].sSizeX, sY + 280, DRAW_DIALOGBOX_SKILLDLG3, 55,25,25);//"your current skill. The items you can"
		PutAlignedString(sX, sX+m_stDialogBoxInfo[26].sSizeX, sY + 295, DRAW_DIALOGBOX_SKILLDLG4, 55,25,25);//"make now with your current stuff will"
		PutAlignedString(sX, sX+m_stDialogBoxInfo[26].sSizeX, sY + 310, DRAW_DIALOGBOX_SKILLDLG5, 55,25,25);//"be displayed in blue. "
		PutAlignedString(sX, sX+m_stDialogBoxInfo[26].sSizeX, sY + 340, DRAW_DIALOGBOX_SKILLDLG6, 55,25,25);//"Select an item you want to manufacture."
		break;

	case 4: // Manuf: Waiting for incredients
		sX = m_stDialogBoxInfo[26].sX;
		sY = m_stDialogBoxInfo[26].sY;
		szX = m_stDialogBoxInfo[26].sSizeX;
		iAdjX = -1;
		iAdjY = -7;
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
		m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
		          m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprFrame, dwTime);

		ZeroMemory(cTemp, sizeof(cTemp));
		GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName, 0, cStr1, cStr2, cStr3 );
		wsprintf(cTemp, "%s", cStr1);
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55, cTemp, RGB(255,255,255));

		wsprintf(cTemp,  DRAW_DIALOGBOX_SKILLDLG7 // "Skill level: %d/%d"
			, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSkillLimit
			, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iMaxSkill);
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55 +2*15, cTemp, RGB(45,25,25));
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55 +3*15 +5, DRAW_DIALOGBOX_SKILLDLG8, RGB(45,25,25));//"Ingredients Needed:"

		iLoc = 4;
		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[1] != 0) {
			GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName1, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[1] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(150,150,150));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[2] != 0) {
			GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName2, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[2] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(150,150,150));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[3] != 0) {
			GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName3, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[3] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(150,150,150));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[4] != 0) {
			GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName4, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[4] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(150,150,150));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[5] != 0) {
			GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName5, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[5] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(150,150,150));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[6] != 0) {
			GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName6, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[6] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(150,150,150));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bBuildEnabled == TRUE)
		{	m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +13, sY + iAdjY +55 +180 , 2, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*1 +13, sY + iAdjY +55 +180, 2, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*2 +13, sY + iAdjY +55 +180, 2, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +13, sY + iAdjY +100 +180, 2, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*1 +13, sY + iAdjY +100 +180, 2, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*2 +13, sY + iAdjY +100 +180, 2, dwTime);

			if (m_stDialogBoxInfo[26].sV1 != -1)
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
				m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +30 +13, sY + iAdjY + 55 +180,
				m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

			if (m_stDialogBoxInfo[26].sV2 != -1)
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
				m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +45*1 +30 +13, sY + iAdjY + 55 +180,
				m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

			if (m_stDialogBoxInfo[26].sV3 != -1)
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
				m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +45*2 +30 +13, sY + iAdjY + 55 +180,
				m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

			if (m_stDialogBoxInfo[26].sV4 != -1)
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
				m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +30 +13, sY + iAdjY + 100 +180,
				m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

			if (m_stDialogBoxInfo[26].sV5 != -1)
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
				m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55+45*1 +30 +13, sY + iAdjY + 100 +180,
				m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

			if (m_stDialogBoxInfo[26].sV6 != -1)
				m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
				m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55+45*2 +30 +13, sY + iAdjY + 100 +180,
				m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

			PutAlignedString(sX, sX + szX, sY + iAdjY + 230 +75, DRAW_DIALOGBOX_SKILLDLG15, 55,25,25);//" Click MANUFACTURE button after"
			PutAlignedString(sX, sX + szX, sY + iAdjY + 245 +75, DRAW_DIALOGBOX_SKILLDLG16, 55,25,25);//"dragging ingredients in the blanks"
			PutAlignedString(sX, sX + szX, sY + iAdjY + 260 +75, DRAW_DIALOGBOX_SKILLDLG17, 55,25,25);//"to manufacture above item."

			if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
				 PutString_SprFont(sX + iAdjX + 25,  sY + iAdjY + 330 +23, "Back", 6,6,20);
			else PutString_SprFont(sX + iAdjX + 25,  sY + iAdjY + 330 +23, "Back", 0,0,7);


			if ((msX >= sX + iAdjX + 160) && (msX <= sX + iAdjX + 255) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) {
				if (m_stDialogBoxInfo[26].cStr[4] == 1)
					 PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 +23, "Manufacture", 6,6,20);
				else PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 +23, "Manufacture", 10,10,10);
			}
			else {
				if (m_stDialogBoxInfo[26].cStr[4] == 1)
					 PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 +23, "Manufacture", 0, 0, 7);
				else PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 +23, "Manufacture", 10,10,10);
			}
		}
		else {
			PutAlignedString(sX, sX + szX, sY + iAdjY + 200 +75, DRAW_DIALOGBOX_SKILLDLG18, 55,25,25);//"There are not enough ingredients to"
			PutAlignedString(sX, sX + szX, sY + iAdjY + 215 +75, DRAW_DIALOGBOX_SKILLDLG19, 55,25,25);//"manufacture. Needed materials are"
			PutAlignedString(sX, sX + szX, sY + iAdjY + 230 +75, DRAW_DIALOGBOX_SKILLDLG20, 55,25,25);//"displayed in grey."
			if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
				 PutString_SprFont(sX + iAdjX + 25,  sY + iAdjY + 330 +23, "Back", 6,6,20);
			else PutString_SprFont(sX + iAdjX + 25,  sY + iAdjY + 330 +23, "Back", 0,0,7);
		}
		break;

	case 5: // Manuf: in progress
		sX = m_stDialogBoxInfo[26].sX;
		sY = m_stDialogBoxInfo[26].sY;
		iAdjX = -1;
		iAdjY = -7;

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
		m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
		          m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprFrame, dwTime);

		ZeroMemory(cTemp, sizeof(cTemp));
		GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName, 0, cStr1, cStr2, cStr3 );
		wsprintf(cTemp, "%s", cStr1);
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55, cTemp, RGB(255,255,255));

		wsprintf(cTemp,  DRAW_DIALOGBOX_SKILLDLG7 // "Skill level: %d/%d"
			, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSkillLimit, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iMaxSkill);//"½ºÅ³ ¼öÁØ: %d/%d"
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55 +2*15, cTemp, RGB(45,25,25));
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55 +3*15 +5, DRAW_DIALOGBOX_SKILLDLG8, RGB(45,25,25));//"Ingredients Needed:"

		iLoc = 4;
		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[1] != 0)
		{	GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName1, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[1] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(120,120,120));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[2] != 0)
		{	GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName2, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[2] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(120,120,120));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[3] != 0)
		{	GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName3, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[3] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(120,120,120));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[4] != 0)
		{	GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName4, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[4] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(120,120,120));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[5] != 0)
		{	GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName5, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[5] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(120,120,120));
			iLoc++;
		}

		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[6] != 0)
		{	GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName6, 0, cStr1, cStr2, cStr3 );
			wsprintf(cTemp, "%s", cStr1);
			if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[6] == TRUE)
				 PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(45,25,25));
			else PutString(sX + iAdjX + 44 +20 +60, sY + iAdjY + 55 +iLoc*15 +5, cTemp, RGB(120,120,120));
			iLoc++;
		}

		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +13, sY + iAdjY +55 +180 , 2, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*1 +13, sY + iAdjY +55 +180, 2, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*2 +13, sY + iAdjY +55 +180, 2, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +13, sY + iAdjY +100 +180, 2, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*1 +13, sY + iAdjY +100 +180, 2, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX +55 +30 +45*2 +13, sY + iAdjY +100 +180, 2, dwTime);

		if (m_stDialogBoxInfo[26].sV1 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +30 +13, sY + iAdjY + 55 +180,
					  m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV2 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +45*1 +30 +13, sY + iAdjY + 55 +180,
					  m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV3 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +45*2 +30 +13, sY + iAdjY + 55 +180,
					  m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV4 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +30 +13, sY + iAdjY + 100 +180,
					  m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV5 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55+45*1 +30 +13, sY + iAdjY + 100 +180,
					  m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV6 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55+45*2 +30 +13, sY + iAdjY + 100 +180,
					  m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

		PutString(sX + iAdjX + 33, sY + iAdjY + 230 +75, DRAW_DIALOGBOX_SKILLDLG29, RGB(55,25,25));//" Manufacturing the items...."
		PutString(sX + iAdjX + 33, sY + iAdjY + 245 +75, DRAW_DIALOGBOX_SKILLDLG30, RGB(55,25,25));//"Please wait until manufacture finishes."

		if ((dwTime - m_stDialogBoxInfo[26].dwT1) > 1000)
		{	m_stDialogBoxInfo[26].dwT1 = dwTime;
			m_stDialogBoxInfo[26].cStr[1]++;
			if (m_stDialogBoxInfo[26].cStr[1] >= 7) m_stDialogBoxInfo[26].cStr[1] = 7;
		}

		if (m_stDialogBoxInfo[26].cStr[1] == 4)
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_BUILDITEM, NULL, NULL, NULL, NULL, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName);
			m_stDialogBoxInfo[26].cStr[1]++;
		}
		break;

	case 6: // Manuf: Done
		sX = m_stDialogBoxInfo[26].sX;
		sY = m_stDialogBoxInfo[26].sY;
		iAdjX = -1;
		iAdjY = -7;

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
		m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
		          m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprFrame, dwTime);

		ZeroMemory(cTemp, sizeof(cTemp));
		GetItemName( m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName, 0, cStr1, cStr2, cStr3 );

		wsprintf(cTemp, "%s", cStr1);
		PutString(sX + iAdjX + 44 +10 +60, sY + iAdjY + 55, cTemp, RGB(255,255,255));

		if (m_stDialogBoxInfo[26].cStr[2] == 1) {
			PutString(sX + iAdjX + 33 +11, sY + iAdjY + 200 -45, DRAW_DIALOGBOX_SKILLDLG31, RGB(55,25,25));//" Success in manufacture!"

			if (m_stDialogBoxInfo[26].sV1 == DEF_ITEMTYPE_MATERIAL) {
				wsprintf(G_cTxt, DRAW_DIALOGBOX_SKILLDLG32, m_stDialogBoxInfo[26].cStr[3]);//"The purity of product is %d%%."
				PutString(sX + iAdjX + 33 +11, sY + iAdjY + 215 -45, G_cTxt, RGB(55,25,25));
			}
			else {
				wsprintf(G_cTxt, DRAW_DIALOGBOX_SKILLDLG33, (int)m_stDialogBoxInfo[26].cStr[3] +100);//"The completion of product is %d%%."
				PutString(sX + iAdjX + 33, sY + iAdjY + 215 -45, G_cTxt, RGB(55,25,25));
			}
		}
		else {
			PutString(sX + iAdjX + 33+11, sY + iAdjY + 200, DRAW_DIALOGBOX_SKILLDLG34, RGB(55,25,25));//"Failed on manufacture."
		}

		if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
			 PutString_SprFont(sX + iAdjX + 35,  sY + iAdjY + 330 +23, "Back", 6,6,20);
		else PutString_SprFont(sX + iAdjX + 35,  sY + iAdjY + 330 +23, "Back", 0,0,7);
		break;


	case 7: // Crafting, wait for incredients
		if (m_stDialogBoxInfo[26].cStr[0] != 0)
		{	sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
			sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
		}else
		{	sX = m_stDialogBoxInfo[26].sX;
			sY = m_stDialogBoxInfo[26].sY;
		}
		m_pSprite[DEF_SPRID_INTERFACE_CRAFTING]->PutSpriteFast(sX, sY, 0, dwTime);

		if (m_stDialogBoxInfo[26].sV1 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV2 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 +45*1 +(1-(rand()%3)), sY + iAdjY + 40 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV3 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 +45*2 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV4 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV5 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65+45*1 +(1-(rand()%3)), sY + iAdjY + 115 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

		if (m_stDialogBoxInfo[26].sV6 != -1)
			m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 75+45*2 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);
		if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
			 PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 16,16,30);
		else PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 6, 6, 20);
		break;

	case 8: // Crafting in progress
		if (m_stDialogBoxInfo[26].cStr[0] != 0)
		{	sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
			sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0]*2)));
		}else
		{	sX = m_stDialogBoxInfo[26].sX;
			sY = m_stDialogBoxInfo[26].sY;
		}
		m_pSprite[DEF_SPRID_INTERFACE_CRAFTING]->PutSpriteFast(sX, sY, 0, dwTime);

		if (m_stDialogBoxInfo[26].sV1 != -1)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 +(1-(rand()%3)) +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);
			if (   (m_pItemList[m_stDialogBoxInfo[26].sV1]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				&& (m_pItemList[m_stDialogBoxInfo[26].sV1]->m_cEquipPos == DEF_EQUIPPOS_NECK))
				m_iContributionPrice = 10;
		}
		if (m_stDialogBoxInfo[26].sV2 != -1)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 +45*1 +(1-(rand()%3)), sY + iAdjY + 40 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);
			if (   (m_pItemList[m_stDialogBoxInfo[26].sV2]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				&& (m_pItemList[m_stDialogBoxInfo[26].sV2]->m_cEquipPos == DEF_EQUIPPOS_NECK))
				m_iContributionPrice = 10;
		}
		if (m_stDialogBoxInfo[26].sV3 != -1)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 +45*2 +(1-(rand()%3)), sY + iAdjY + 55 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);
			if (   (m_pItemList[m_stDialogBoxInfo[26].sV3]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				&& (m_pItemList[m_stDialogBoxInfo[26].sV3]->m_cEquipPos == DEF_EQUIPPOS_NECK))
				m_iContributionPrice = 10;
		}
		if (m_stDialogBoxInfo[26].sV4 != -1)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);
			if (   (m_pItemList[m_stDialogBoxInfo[26].sV4]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				&& (m_pItemList[m_stDialogBoxInfo[26].sV4]->m_cEquipPos == DEF_EQUIPPOS_NECK))
				m_iContributionPrice = 10;
		}
		if (m_stDialogBoxInfo[26].sV5 != -1)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65+45*1 +(1-(rand()%3)), sY + iAdjY + 115 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);
			if (   (m_pItemList[m_stDialogBoxInfo[26].sV5]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				&& (m_pItemList[m_stDialogBoxInfo[26].sV5]->m_cEquipPos == DEF_EQUIPPOS_NECK))
				m_iContributionPrice = 10;
		}
		if (m_stDialogBoxInfo[26].sV6 != -1)
		{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
			          m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 75+45*2 +(1-(rand()%3)), sY + iAdjY + 100 +(1-(rand()%3)),
					  m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);
			if (   (m_pItemList[m_stDialogBoxInfo[26].sV6]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				&& (m_pItemList[m_stDialogBoxInfo[26].sV6]->m_cEquipPos == DEF_EQUIPPOS_NECK))
				m_iContributionPrice = 10;
		}
		PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Creating...", 20,6,6);

		if ((dwTime - m_stDialogBoxInfo[26].dwT1) > 1000)
		{	m_stDialogBoxInfo[26].dwT1 = dwTime;
			m_stDialogBoxInfo[26].cStr[1]++;
		}
		if (m_stDialogBoxInfo[26].cStr[1] >= 5)//m_pDispCraftItemList
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CRAFTITEM, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(26);
			PlaySound('E', 42, 0);
		}
		break;
	}
}

void CGame::DrawDialogBox_SysMenu(short msX, short msY, char cLB)
{short sX, sY;

	sX = m_stDialogBoxInfo[19].sX;
	sY = m_stDialogBoxInfo[19].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 6);
	PutString(sX + 23, sY + 63, DRAW_DIALOGBOX_SYSMENU_DETAILLEVEL, RGB(45,25,25));
	PutString(sX + 24, sY + 63, DRAW_DIALOGBOX_SYSMENU_DETAILLEVEL, RGB(45,25,25));
	if (m_cDetailLevel == 0)
		 PutString(sX + 121, sY + 63, DRAW_DIALOGBOX_SYSMENU_LOW, RGB(255,255,255));
	else PutString(sX + 121, sY + 63, DRAW_DIALOGBOX_SYSMENU_LOW, RGB(45,25,25));
	if (m_cDetailLevel == 1)
		 PutString(sX + 153, sY + 63, DRAW_DIALOGBOX_SYSMENU_NORMAL, RGB(255,255,255));
	else PutString(sX + 153, sY + 63, DRAW_DIALOGBOX_SYSMENU_NORMAL, RGB(45,25,25));
	if (m_cDetailLevel == 2)
		 PutString(sX + 205, sY + 63, DRAW_DIALOGBOX_SYSMENU_HIGH, RGB(255,255,255));
	else PutString(sX + 205, sY + 63, DRAW_DIALOGBOX_SYSMENU_HIGH, RGB(45,25,25));

	PutString(sX + 23, sY + 84, DRAW_DIALOGBOX_SYSMENU_SOUND, RGB(45,25,25));
	PutString(sX + 24, sY + 84, DRAW_DIALOGBOX_SYSMENU_SOUND, RGB(45,25,25));
	if (m_bSoundFlag) {
		if (m_bSoundStat) PutString(sX + 85, sY + 85, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255,255,255));
		else PutString(sX + 83, sY + 85, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200,200,200));
  	}
	else PutString(sX + 68, sY + 85, DRAW_DIALOGBOX_SYSMENU_DISABLED, RGB(100,100,100));

	PutString(sX + 123, sY + 84, DRAW_DIALOGBOX_SYSMENU_MUSIC, RGB(45,25,25));
	PutString(sX + 124, sY + 84, DRAW_DIALOGBOX_SYSMENU_MUSIC, RGB(45,25,25));
	if (m_bSoundFlag) {
		if (m_bMusicStat) PutString(sX + 180, sY + 85, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255,255,255));
		else PutString(sX + 178, sY + 85, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200,200,200));
  	}
	else PutString(sX + 163, sY + 85, DRAW_DIALOGBOX_SYSMENU_DISABLED, RGB(100,100,100));

	PutString(sX + 23,  sY + 106, DRAW_DIALOGBOX_SYSMENU_WHISPER, RGB(45,25,25));
	PutString(sX + 24, sY + 106, DRAW_DIALOGBOX_SYSMENU_WHISPER, RGB(45,25,25));
	if (m_bWhisper) PutString(sX + 85, sY + 106, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255,255,255));
	else PutString(sX + 82, sY + 106, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200,200,200));

	PutString(sX + 123, sY + 106, DRAW_DIALOGBOX_SYSMENU_SHOUT, RGB(45,25,25));
	PutString(sX + 124, sY + 106, DRAW_DIALOGBOX_SYSMENU_SHOUT, RGB(45,25,25));
	if (m_bShout) PutString(sX + 180, sY + 106, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255,255,255));
	else PutString(sX + 177, sY + 106, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200,200,200));

	PutString(sX + 23, sY + 124, DRAW_DIALOGBOX_SYSMENU_SOUNDVOLUME, RGB(45,25,25));
	PutString(sX + 24, sY + 124, DRAW_DIALOGBOX_SYSMENU_SOUNDVOLUME, RGB(45,25,25));
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 130 + m_cSoundVolume, sY + 129, 8);

	PutString(sX + 23, sY + 141, DRAW_DIALOGBOX_SYSMENU_MUSICVOLUME, RGB(45,25,25));
	PutString(sX + 24, sY + 141, DRAW_DIALOGBOX_SYSMENU_MUSICVOLUME, RGB(45,25,25));
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 130 + m_cMusicVolume, sY + 145, 8);

	PutString(sX + 23, sY + 158, DRAW_DIALOGBOX_SYSMENU_TRANSPARENCY, RGB(45,25,25));
	PutString(sX + 24, sY + 158, DRAW_DIALOGBOX_SYSMENU_TRANSPARENCY, RGB(45,25,25));
	if (m_bDialogTrans) PutString(sX + 208, sY + 158, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255,255,255));
	else PutString(sX + 207, sY + 158, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200,200,200));

	PutString(sX + 23, sY + 180, DRAW_DIALOGBOX_SYSMENU_GUIDEMAP, RGB(45,25,25));
	PutString(sX + 24, sY + 180, DRAW_DIALOGBOX_SYSMENU_GUIDEMAP, RGB(45,25,25));
	if (m_bIsDialogEnabled[9]) PutString(sX + 99, sY + 180, DRAW_DIALOGBOX_SYSMENU_ON, RGB(255,255,255));
	else PutString(sX + 98, sY + 180, DRAW_DIALOGBOX_SYSMENU_OFF, RGB(200,200,200));

	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	ZeroMemory(G_cTxt, sizeof(G_cTxt));
	wsprintf(G_cTxt, "%d:%d:%d:%d:%d", SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	PutString(sX + 23, sY + 204, G_cTxt, RGB(45,25,25));
	PutString(sX + 24, sY + 204, G_cTxt, RGB(45,25,25));

//v2.172
#ifdef _DEBUG
	PutString(sX + 23, sY + 41, UPDATE_SCREEN_ON_SELECT_CHARACTER36, RGB(45,25,25)); // "Test server"
	PutString(sX + 24, sY + 41, UPDATE_SCREEN_ON_SELECT_CHARACTER36, RGB(45,25,25)); // "Test server"
#else

	if (strcmp(m_cWorldServerName, NAME_WORLDNAME1) == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME1, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME1, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS2") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME2, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME2, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS3") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME3, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME3, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS4") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME4, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME4, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS5") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME5, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME5, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS6") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME6, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME6, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS7") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME7, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME7, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS8") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME8, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME8, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS9") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME9, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME9, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS10") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME10, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME10, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS11") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME11, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME11, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS12") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME12, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME12, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS13") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME13, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME13, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS14") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME14, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME14, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS15") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME15, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME15, RGB(45,25,25));
	}
	else if (strcmp(m_cWorldServerName, "WS16") == 0) {
		PutString(sX + 23, sY + 41, MSG_WORLDNAME16, RGB(45,25,25));
		PutString(sX + 24, sY + 41, MSG_WORLDNAME16, RGB(45,25,25));
	}
#endif

	if ( (cLB != 0) && (iGetTopDialogBoxIndex() == 19) )
	//  (msX >= sX + 120) && (msX <= sX + 242) && (msY >= sY +122) && (msY <= sY +138)
	{	if ((msX >= sX + 127) && (msX <= sX + 238) && (msY >= sY +122) && (msY <= sY +138))
		{	m_cSoundVolume = msX - (sX + 127);
			if( m_cSoundVolume > 100 ) m_cSoundVolume = 100;
			if( m_cSoundVolume < 0 ) m_cSoundVolume = 0;
		}
		if ((msX >= sX + 127) && (msX <= sX + 238) && (msY >= sY +139) && (msY <= sY +155))
		{	m_cMusicVolume = msX - (sX + 127);
			if( m_cMusicVolume > 100 ) m_cMusicVolume = 100;
			if( m_cMusicVolume < 0 ) m_cMusicVolume = 0;
			if (m_bSoundFlag)
			{
				int iVol;
				iVol = (m_cMusicVolume - 100)*20;
				if (iVol > 0) iVol = 0;
				if (iVol < -10000) iVol = -10000;
				if (m_pBGM != NULL)
				{	m_pBGM->bStop(TRUE);
					m_pBGM->Play(FALSE, 0, iVol);
		}	}	}
	}
	else m_stDialogBoxInfo[19].bIsScrollSelected = FALSE;

	// Log-Out
	if (m_cLogOutCount == -1)
	{	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY +225, 9);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY +225, 8);
	}else  //Continue
	{	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY +225, 7);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY +225, 6);
	}
	// Restart
	if ((m_iHP <= 0) && (m_cRestartCount == -1))
	{	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY +225, 37);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY +225, 36);
	}else if (m_cRestartCount == -1)
	{	// Of course it's easy to remove or change this...
		PutString(sX + 133, sY + 214, "Coded by Cleroth,", RGB(45,25,25));
		PutString(sX + 134, sY + 214, "Coded by Cleroth,", RGB(45,25,25));
		PutString(sX + 125, sY + 229, "Diuuude & Snoopy81", RGB(45,25,25));
		PutString(sX + 126, sY + 229, "Diuuude & Snoopy81", RGB(45,25,25));
	}
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

void CGame::bItemDrop_Character()
{	ItemEquipHandler((char)m_stMCursor.sSelectedObjectID);
}

void CGame::bItemDrop_Inventory(short msX, short msY)
{ short sX, sY, dX, dY;
 char  cTxt[120];
	if (m_cCommand < 0) return;
	if (m_pItemList[m_stMCursor.sSelectedObjectID] == NULL) return;
	if ((m_bSkillUsingStatus == TRUE) && (m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] == TRUE))
	{	AddEventList(BITEMDROP_INVENTORY1, 10);
		return;
	}
	if (m_bIsItemDisabled[m_stMCursor.sSelectedObjectID] == TRUE) return;
	sY = m_stDialogBoxInfo[2].sY;
	sX = m_stDialogBoxInfo[2].sX;
	dX = msX - sX - 32 - m_stMCursor.sDistX;
	dY = msY - sY - 44 - m_stMCursor.sDistY;
	if (dY < -10) dY = -10;
	if (dX < 0)   dX = 0;
	if (dX > 170) dX = 170;
	if (dY > 95) dY = 95;

	m_pItemList[m_stMCursor.sSelectedObjectID]->m_sX = dX;
	m_pItemList[m_stMCursor.sSelectedObjectID]->m_sY = dY;

	short sTmpSpr, sTmpSprFrm;
	sTmpSpr = m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite;
	sTmpSprFrm = m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame;

	char cItemID;
	if (m_bShiftPressed)
	{	for (int i = 0; i < DEF_MAXITEMS; i++)
		{	if (m_cItemOrder[DEF_MAXITEMS - 1 - i] != -1)
			{	cItemID = m_cItemOrder[DEF_MAXITEMS - 1 - i];
				if (m_pItemList[cItemID] != NULL && memcmp(m_pItemList[cItemID]->m_cName, m_pItemList[m_stMCursor.sSelectedObjectID]->m_cName, 20) == 0 )
				{	m_pItemList[cItemID]->m_sX = dX;
					m_pItemList[cItemID]->m_sY = dY;
					bSendCommand(MSGID_REQUEST_SETITEMPOS, NULL, cItemID, dX, dY, NULL, NULL);
		}	}	}
    }else bSendCommand(MSGID_REQUEST_SETITEMPOS, NULL, (char)(m_stMCursor.sSelectedObjectID), dX, dY, NULL, NULL);

	if (m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] == TRUE)
	{	char cStr1[64], cStr2[64], cStr3[64];
		GetItemName(m_pItemList[m_stMCursor.sSelectedObjectID], cStr1, cStr2, cStr3);
		wsprintf(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
		AddEventList(cTxt, 10);

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
	}
}

void CGame::bItemDrop_SellList(short msX, short msY)
{
 int i;
 char cItemID;

	cItemID = (char)m_stMCursor.sSelectedObjectID;

	if (m_pItemList[cItemID] == NULL) return;
	if (m_bIsItemDisabled[cItemID] == TRUE) return;
	if (m_cCommand < 0) return;
		for (i = 0; i < DEF_MAXSELLLIST; i++)
	if (m_stSellItemList[i].iIndex == cItemID)
	{	AddEventList(BITEMDROP_SELLLIST1, 10);
		return;
	}
	if (strcmp(m_pItemList[cItemID]->m_cName, "Gold") == 0) {
		AddEventList(BITEMDROP_SELLLIST2, 10);
		return;
	}
	if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
	{
		ZeroMemory( G_cTxt, sizeof(G_cTxt) );
		char cStr1[64], cStr2[64], cStr3[64];
		GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);
		wsprintf( G_cTxt, NOTIFYMSG_CANNOT_SELL_ITEM2, cStr1 );
		AddEventList( G_cTxt, 10 );
		return;
	}

	if ( ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW)) &&
		 (m_pItemList[cItemID]->m_dwCount > 1) )
	{	m_stDialogBoxInfo[17].sX  = msX - 140;
		m_stDialogBoxInfo[17].sY  = msY - 70;
		if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;
		m_stDialogBoxInfo[17].sV1 = m_sPlayerX+1;
		m_stDialogBoxInfo[17].sV2 = m_sPlayerY+1;
		m_stDialogBoxInfo[17].sV3 = 1001;
		m_stDialogBoxInfo[17].sV4 = cItemID;
		ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
		EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, NULL);
		m_bIsItemDisabled[cItemID] = TRUE;
	}else
	{	for (i = 0; i < DEF_MAXSELLLIST; i++)
		if (m_stSellItemList[i].iIndex == -1)
		{	m_stSellItemList[i].iIndex = cItemID;
			m_stSellItemList[i].iAmount = 1;
			m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}
		AddEventList(BITEMDROP_SELLLIST3, 10);
	}
}

void CGame::bItemDrop_ItemUpgrade()
{
 char cItemID;
	cItemID = (char)m_stMCursor.sSelectedObjectID;
	if (m_bIsItemDisabled[cItemID] == TRUE) return;
	if (m_cCommand < 0) return;
	if (m_pItemList[cItemID]->m_cEquipPos == DEF_EQUIPPOS_NONE) return;

	switch (m_stDialogBoxInfo[34].cMode) {
	case 1:
		m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = FALSE;
		m_stDialogBoxInfo[34].sV1 = cItemID;
		m_bIsItemDisabled[cItemID] = TRUE;
		PlaySound('E', 29, 0);
		break;

	case 6:
		m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = FALSE;
		m_stDialogBoxInfo[34].sV1 = cItemID;
		m_bIsItemDisabled[cItemID] = TRUE;
		PlaySound('E', 29, 0);
		break;
	}
}

void CGame::bItemDrop_Bank(short msX, short msY)
{	m_stDialogBoxInfo[39].sV1 = m_stMCursor.sSelectedObjectID;
	if (m_cCommand < 0) return;
	if (m_pItemList[m_stDialogBoxInfo[39].sV1] == NULL) return;
	if (m_bIsItemDisabled[m_stDialogBoxInfo[39].sV1] == TRUE) return;
	if ( m_bIsDialogEnabled[17] == TRUE )
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}
	if ( (m_bIsDialogEnabled[20] == TRUE) && ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)) )
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}
	if (m_bIsDialogEnabled[23] == TRUE)
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}
	if (m_bIsDialogEnabled[4] == TRUE)
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}
	if ( ((m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cItemType == DEF_ITEMTYPE_ARROW)) && (m_pItemList[m_stDialogBoxInfo[39].sV1]->m_dwCount > 1) )
	{	m_stDialogBoxInfo[17].sX  = msX - 140;
		m_stDialogBoxInfo[17].sY  = msY - 70;
		if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;

		m_stDialogBoxInfo[17].sV1 = m_sPlayerX+1;
		m_stDialogBoxInfo[17].sV2 = m_sPlayerY+1;
		m_stDialogBoxInfo[17].sV3 = 1002;// NPC
		m_stDialogBoxInfo[17].sV4 = m_stDialogBoxInfo[39].sV1;

		ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
		EnableDialogBox(17, m_stDialogBoxInfo[39].sV1, m_pItemList[m_stDialogBoxInfo[39].sV1]->m_dwCount, NULL);
	}else
	{	if (_iGetBankItemCount() >= (DEF_MAXBANKITEMS-1)) AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);
		else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[39].sV1, 1, m_stDialogBoxInfo[39].sV5, m_stDialogBoxInfo[39].sV6, m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cName, m_stDialogBoxInfo[39].sV4); //v1.4
	}
}

void CGame::bItemDrop_SkillDialog()
{
 int iConsumeNum;
 char cItemID;

	if (m_cCommand < 0) return;
	cItemID = (char)m_stMCursor.sSelectedObjectID;
	if (m_pItemList[cItemID] == NULL) return;
	if (m_bIsItemDisabled[cItemID] == TRUE) return;

	if ( m_bIsDialogEnabled[17] == TRUE )
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}

	if (   (m_bIsDialogEnabled[20] == TRUE)
		&& ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)) )
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}

	if (m_bIsDialogEnabled[23] == TRUE)
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}

	switch (m_stDialogBoxInfo[26].cMode) {
	case 1:
		if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)
		{	iConsumeNum = 0;
			if (m_stDialogBoxInfo[26].sV1 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV2 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV3 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV4 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV5 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV6 == cItemID) iConsumeNum++;
			if (iConsumeNum >= (int)(m_pItemList[cItemID]->m_dwCount)) return;
		}
		if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT) ||
			(m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
			(m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_NONE))
		{}else return;

		if (m_stDialogBoxInfo[26].sV1 == -1)
		{	m_stDialogBoxInfo[26].sV1 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV2 == -1)
		{	m_stDialogBoxInfo[26].sV2 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV3 == -1)
		{	m_stDialogBoxInfo[26].sV3 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV4 == -1)
		{	m_stDialogBoxInfo[26].sV4 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV5 == -1)
		{	m_stDialogBoxInfo[26].sV5 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV6 == -1)
		{	m_stDialogBoxInfo[26].sV6 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}
		AddEventList(BITEMDROP_SKILLDIALOG4, 10);
		break;

	case 4:
		if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)
		{	iConsumeNum = 0;
			if (m_stDialogBoxInfo[26].sV1 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV2 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV3 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV4 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV5 == cItemID) iConsumeNum++;
			if (m_stDialogBoxInfo[26].sV6 == cItemID) iConsumeNum++;
			if (iConsumeNum >= (int)(m_pItemList[cItemID]->m_dwCount)) return;
		}

		if (m_stDialogBoxInfo[26].sV1 == -1)
		{	m_stDialogBoxInfo[26].sV1 = cItemID;
			m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV2 == -1)
		{	m_stDialogBoxInfo[26].sV2 = cItemID;
			m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV3 == -1)
		{	m_stDialogBoxInfo[26].sV3 = cItemID;
			m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV4 == -1)
		{	m_stDialogBoxInfo[26].sV4 = cItemID;
			m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV5 == -1)
		{
			m_stDialogBoxInfo[26].sV5 = cItemID;
			m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV6 == -1)
		{	m_stDialogBoxInfo[26].sV6 = cItemID;
			m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}
		AddEventList(BITEMDROP_SKILLDIALOG4, 10); // "There is no more space for ingredients."
		break;

	// Crafting
	case 7:
		if (   (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_NONE)			// Merien Stone
			|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EQUIP)		// Necks XXXMagins
			|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)		// stones
			|| (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_MATERIAL))	// XXXwares
		{}else return;

		if (m_stDialogBoxInfo[26].sV1 == -1)
		{	m_stDialogBoxInfo[26].sV1 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV2 == -1)
		{	m_stDialogBoxInfo[26].sV2 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV3 == -1)
		{	m_stDialogBoxInfo[26].sV3 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV4 == -1)
		{	m_stDialogBoxInfo[26].sV4 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV5 == -1)
		{	m_stDialogBoxInfo[26].sV5 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}else if (m_stDialogBoxInfo[26].sV6 == -1)
		{	m_stDialogBoxInfo[26].sV6 = cItemID;
			if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
			{}else m_bIsItemDisabled[cItemID] = TRUE;
			return;
		}
		AddEventList(BITEMDROP_SKILLDIALOG4, 10); // "There is no more space for ingredients."
		break;

	default:
		break;
	}
}

// Slates Item Drag&Drop - Diuuude
void CGame::bItemDrop_Slates()
{
 char cItemID;
	if (m_cCommand < 0) return;
	cItemID = (char)m_stMCursor.sSelectedObjectID;
	if (m_pItemList[cItemID] == NULL) return;
	if (m_bIsItemDisabled[cItemID] == TRUE) return;
	if ( m_bIsDialogEnabled[17] == TRUE ) {
		AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}

	if ( (m_bIsDialogEnabled[20] == TRUE) &&
		 ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)) ) {
		AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}

	if (m_bIsDialogEnabled[23] == TRUE) {
		AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}

	switch (m_stDialogBoxInfo[40].cMode) {
	case 1:
		if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) && (m_pItemList[cItemID]->m_sSpriteFrame >= 151) && (m_pItemList[cItemID]->m_sSpriteFrame <= 154)) {
			char cItemIDText[20];
			switch(m_pItemList[cItemID]->m_sSpriteFrame){
				case 151:
					if (m_stDialogBoxInfo[40].sV1 == -1){
						m_bIsItemDisabled[cItemID] = TRUE;
						m_stDialogBoxInfo[40].sV1 = cItemID;
						wsprintf(cItemIDText, "Item ID : %d", cItemID);
						AddEventList(cItemIDText, 10);
					}
					break;
				case 152:
					if (m_stDialogBoxInfo[40].sV2 == -1){
						m_bIsItemDisabled[cItemID] = TRUE;
						m_stDialogBoxInfo[40].sV2 = cItemID;
						wsprintf(cItemIDText, "Item ID : %d", cItemID);
						AddEventList(cItemIDText, 10);
					}
					break;
				case 153:
					if (m_stDialogBoxInfo[40].sV3 == -1){
						m_bIsItemDisabled[cItemID] = TRUE;
						m_stDialogBoxInfo[40].sV3 = cItemID;
						wsprintf(cItemIDText, "Item ID : %d", cItemID);
						AddEventList(cItemIDText, 10);
					}
					break;
				case 154:
					if (m_stDialogBoxInfo[40].sV4 == -1){
						m_bIsItemDisabled[cItemID] = TRUE;
						m_stDialogBoxInfo[40].sV4 = cItemID;
						wsprintf(cItemIDText, "Item ID : %d", cItemID);
						AddEventList(cItemIDText, 10);
					}
					break;
			}
		}
		break;

	default:
		break;
	}
}

void CGame::DlgBoxClick_Bank(short msX, short msY)
{
 int i;
 short sX, sY;


	sX = m_stDialogBoxInfo[14].sX;
	sY = m_stDialogBoxInfo[14].sY;

	switch ( m_stDialogBoxInfo[14].cMode ) {
	case -1:
		break;

	case 0:
		for (i = 0; i < m_stDialogBoxInfo[14].sV1; i++)
		if ((msX > sX + 30) && (msX < sX + 210) && (msY >= sY + 110 + i*15) && (msY <= sY + 124 + i*15)) {
			if ((m_pBankList[m_stDialogBoxInfo[14].sView + i] != NULL) && ((m_stDialogBoxInfo[14].sView + i) < DEF_MAXBANKITEMS)) {
				if (_iGetTotalItemNum() >= 50) {
					AddEventList(DLGBOX_CLICK_BANK1, 10);
					return;
				}
				bSendCommand(MSGID_REQUEST_RETRIEVEITEM, NULL, NULL, (m_stDialogBoxInfo[14].sView + i), NULL, NULL, NULL);
				m_stDialogBoxInfo[14].cMode = -1;
				PlaySound('E', 14, 5);
			}
			return;
		}

		break;
	}
}

void CGame::DlgBoxClick_Fish(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[24].sX;
	sY = m_stDialogBoxInfo[24].sY;

	switch (m_stDialogBoxInfo[24].cMode) {
	case 0:
		if ((msX >= sX + 160) && (msX <= sX + 253) && (msY >= sY + 70) && (msY <= sY + 90)) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETFISHTHISTIME, NULL, NULL, NULL, NULL, NULL);
			AddEventList(DLGBOX_CLICK_FISH1, 10);
			DisableDialogBox(24);

			PlaySound('E', 14, 5);
		}
		break;
	}
}

void CGame::DlgBoxClick_Magic(short msX, short msY)
{
 int i, iCPivot, iYloc;
 short sX, sY;

	sX = m_stDialogBoxInfo[3].sX;
	sY = m_stDialogBoxInfo[3].sY;
	iCPivot = m_stDialogBoxInfo[3].sView*10;
	iYloc = 0;
	for (i = 0; i < 9; i++)
	{	if ((m_cMagicMastery[iCPivot + i] != NULL) && (m_pMagicCfgList[iCPivot + i] != NULL))
		{	if ((msX >= sX + 30) && (msX <= sX + 240) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 18 + iYloc))
			{	UseMagic(iCPivot + i);
				PlaySound('E', 14, 5);
		 		return;
			}
			iYloc += 18;
	}	}
	if ((msX >= sX + 16) && (msX <= sX + 38) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 0;
	if ((msX >= sX + 39) && (msX <= sX + 56) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 1;
	if ((msX >= sX + 57) && (msX <= sX + 81) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 2;
	if ((msX >= sX + 82) && (msX <= sX + 101) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 3;
	if ((msX >= sX + 102) && (msX <= sX + 116) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 4;
	if ((msX >= sX + 117) && (msX <= sX + 137) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 5;
	if ((msX >= sX + 138) && (msX <= sX + 165) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 6;
	if ((msX >= sX + 166) && (msX <= sX + 197) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 7;
	if ((msX >= sX + 198) && (msX <= sX + 217) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 8;
	if ((msX >= sX + 218) && (msX <= sX + 239) && (msY >= sY + 240) && (msY <= sY + 268))
		m_stDialogBoxInfo[3].sView = 9;

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 285) && (msY <= sY + 285 + DEF_BTNSZY))
	{	if (m_cSkillMastery[12] == 0) AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY16, 10);
		else
		{	for (i = 0; i < DEF_MAXITEMS; i++)
			if ((m_pItemList[i] != NULL) && (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) &&
				(m_pItemList[i]->m_sSpriteFrame == 55))
			{	EnableDialogBox(26, 1, NULL, NULL, NULL);
				AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY10, 10);
				PlaySound('E', 14, 5);
				return;
			}
			AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY15, 10);
		}
		PlaySound('E', 14, 5);
	}
}