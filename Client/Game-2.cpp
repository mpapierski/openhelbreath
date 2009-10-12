void CGame::bItemDrop_IconPannel(short msX, short msY)
{short sX, sY, sItemIndex;
	sX = m_stDialogBoxInfo[30].sX;	sY = m_stDialogBoxInfo[30].sY;

	sItemIndex = m_stMCursor.sSelectedObjectID;
	if (m_bIsItemDisabled[sItemIndex] == TRUE) return;
	if (m_cCommand < 0) return;
	if ((453 < msX) && (486 > msX) && (440 < msY) && (475 > msY))
	{	bItemDrop_Inventory(m_stDialogBoxInfo[2].sX + (rand() % 148), m_stDialogBoxInfo[2].sY + (rand() % 55));
		return;
	}
	if ((425 < msX)	&& (448 > msX) && (440 < msY) && (475 > msY))
	{	bItemDrop_Character();
		return;
	}
}



void CGame::DrawEffectLights()
{int i, dX, dY, iDvalue;
 DWORD dwTime = m_dwCurTime;
 char  cTempFrame;
	for (i = 0;	i < DEF_MAXEFFECTS; i++)
	if (m_pEffectList[i] != NULL) {
		switch (m_pEffectList[i]->m_sType) {
		case 1:
			break;

		case 2:
			break;

		case 4:
			break;

		case 5:	// Fire Explosion
			if (m_pEffectList[i]->m_cFrame >= 0)
			{	dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				iDvalue = (m_pEffectList[i]->m_cFrame - 7)*(-1);
				if (m_pEffectList[i]->m_cFrame < 6)
					 m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY+30, 1, dwTime);
				else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY+30, 1, iDvalue, iDvalue, iDvalue, dwTime);
			}
			break;

		case 6:	 // Energy Bolt
		case 10: // Lightning Arrow
			if (m_pEffectList[i]->m_cFrame >= 0)
			{	dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				iDvalue = (m_pEffectList[i]->m_cFrame - 9)*(-1);
				if (m_pEffectList[i]->m_cFrame < 8)
					 m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY+30, 1, dwTime);
				else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY+30, 1, iDvalue, iDvalue, iDvalue, dwTime);
			}
			break;
		case 7: // Magic Missile Explosion
			if (m_pEffectList[i]->m_cFrame >= 0)
			{	dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				iDvalue = (m_pEffectList[i]->m_cFrame - 2)*(-1);
				if (m_pEffectList[i]->m_cFrame < 2)
					 m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY+30, 1, dwTime);
				else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY+30, 1, iDvalue, iDvalue, iDvalue, dwTime);
			}
			break;

		case 16:
		case 61:
		case 66:
		case 100:
		case 110:
		case 120:
		case 130:
		case 137: // Lightning arrow
		//case 165: // APFM fixed green light
			// Light on ground below the flying effect
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			iDvalue = -5;
			m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY+30, 1, iDvalue, iDvalue, iDvalue, dwTime);
			break;

		case 69:
		case 70:
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[0]->PutTransSprite25(dX, dY+30, 1, dwTime);
			break;

		case 33: //
			/*
			if (m_pEffectList[i]->m_cFrame >= 0) {
				dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				iDvalue = (m_pEffectList[i]->m_cFrame - 9)*(-1);
				if (m_pEffectList[i]->m_cFrame < 8)
					 m_pEffectSpr[0]->PutTransSprite(dX, dY, 1, dwTime);
				else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY, 1, iDvalue, iDvalue, iDvalue, dwTime);
			}
			*/
			break;

		case 40: //
		case 56:
			if (m_pEffectList[i]->m_cFrame >= 0)
			{	dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				iDvalue = (m_pEffectList[i]->m_cFrame - 7)*(-1);
				if (m_pEffectList[i]->m_cFrame < 6)
					 m_pEffectSpr[0]->PutTransSprite(dX, dY, 1, dwTime);
				else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY, 1, iDvalue, iDvalue, iDvalue, dwTime);
			}
			break;

		case 52: // Protection Ring
			if (m_pEffectList[i]->m_cFrame >= 0)
			{				dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				m_pEffectSpr[24]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			}
			break;

		case 57:
			if (m_pEffectList[i]->m_cFrame >= 0) {
				dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
				dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
				m_pEffectSpr[30]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			}
			break;

		case 73:
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[74]->PutTransSprite(dX, dY-34, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 74:
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[75]->PutTransSprite(dX, dY+35, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 75: // Icegolem
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[76]->PutTransSprite25(dX+m_pEffectList[i]->m_dX*m_pEffectList[i]->m_cFrame, dY+m_pEffectList[i]->m_dY*m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 76:// Icegolem
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[77]->PutTransSprite25(dX+m_pEffectList[i]->m_dX*m_pEffectList[i]->m_cFrame, dY+m_pEffectList[i]->m_dY*m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 77:// Icegolem
			dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
			m_pEffectSpr[78]->PutTransSprite25(dX+m_pEffectList[i]->m_dX*m_pEffectList[i]->m_cFrame, dY+m_pEffectList[i]->m_dY*m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 150: // Berserk : Cirlcle 6 magic
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[58]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
			break;

		case 180: // Ilusion
		case 190: // Mass Illusion
			cTempFrame = m_pEffectList[i]->m_cFrame;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[59]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
			//if( cTempFrame < 9 ) m_pEffectSpr[59]->PutTransSprite_NoColorKey( dX, dY, cTempFrame, dwTime );
			//else m_pEffectSpr[59]->PutSpriteFast( dX, dY, cTempFrame, dwTime );
			break;

		case 177: // Illusion mvt
		case 195: // Mass Illusion mvt
			cTempFrame = m_pEffectList[i]->m_cFrame;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[102]->PutTransSprite_NoColorKey(dX, dY+30, cTempFrame, dwTime);
			break;

		case 183: // Inhibition casting
			cTempFrame = m_pEffectList[i]->m_cFrame;
			dX  = (m_pEffectList[i]->m_dX*32)  - m_sViewPointX;
			dY  = (m_pEffectList[i]->m_dY*32)  - m_sViewPointY;
			m_pEffectSpr[95]->PutTransSprite_NoColorKey(dX, dY+40, cTempFrame, dwTime);
			break;
		}
	}
}

void CGame::_LoadShopMenuContents(char cType)
{
 char cFileName[255], cTemp[255];
 HANDLE hFile;
 FILE * pFile;
 DWORD  dwFileSize;
 char * pBuffer;

	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFileName, sizeof(cFileName));
	wsprintf(cTemp, "contents%d", cType);
	strcat(cFileName, "contents" );
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
		pBuffer = new char[dwFileSize+1];
		ZeroMemory(pBuffer, dwFileSize+1);
		fread(pBuffer, dwFileSize, 1, pFile);

		__bDecodeContentsAndBuildItemForSaleList(pBuffer);
		delete[] pBuffer;
	}
	fclose(pFile);
}

BOOL CGame::__bDecodeContentsAndBuildItemForSaleList(char * pBuffer)
{
 char * pContents, * token;
 char seps[] = "= ,\t\n";
 char cReadModeA = 0;
 char cReadModeB = 0;
 int  iItemForSaleListIndex = 0;
 class CStrTok * pStrTok;

	pContents = pBuffer;

	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL ) {
		if (cReadModeA != 0) {
			//
			switch (cReadModeA) {
			case 1:
				switch (cReadModeB) {
				case 1:
					ZeroMemory(m_pItemForSaleList[iItemForSaleListIndex]->m_cName, sizeof(m_pItemForSaleList[iItemForSaleListIndex]->m_cName));
					memcpy(m_pItemForSaleList[iItemForSaleListIndex]->m_cName, token, strlen(token));
					cReadModeB = 2;
					break;
				case 2:	// m_cItemType
					m_pItemForSaleList[iItemForSaleListIndex]->m_cItemType = atoi(token);
					cReadModeB = 3;
					break;
				case 3: // m_cEquipPos
					m_pItemForSaleList[iItemForSaleListIndex]->m_cEquipPos = atoi(token);
					cReadModeB = 4;
					break;
				case 4: // m_sItemEffectType
					//m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectType = atoi(token);
					cReadModeB = 5;
					break;
				case 5:	// m_sItemEffectValue1
					m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue1 = atoi(token);
					cReadModeB = 6;
					break;
				case 6: // m_sItemEffectValue2
					m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue2 = atoi(token);
					cReadModeB = 7;
					break;
				case 7: // m_sItemEffectValue3
					m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue3 = atoi(token);
					cReadModeB = 8;
					break;
				case 8: // m_sItemEffectValue4
					m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue4 = atoi(token);
					cReadModeB = 9;
					break;
				case 9: // m_sItemEffectValue5
					m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue5 = atoi(token);
					cReadModeB = 10;
					break;
				case 10: // m_sItemEffectValue6
					m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue6 = atoi(token);
					cReadModeB = 11;
					break;
				case 11: // m_wMaxLifeSpan
					m_pItemForSaleList[iItemForSaleListIndex]->m_wMaxLifeSpan = (WORD)atoi(token);
					cReadModeB = 12;
					break;
				case 12: // m_sMaxFixCount
					//m_pItemForSaleList[iItemForSaleListIndex]->m_sMaxFixCount = atoi(token);
					cReadModeB = 13;
					break;
				case 13: // m_sSprite
					m_pItemForSaleList[iItemForSaleListIndex]->m_sSprite = atoi(token);
					cReadModeB = 14;
					break;
				case 14: // m_sSpriteFrame
					m_pItemForSaleList[iItemForSaleListIndex]->m_sSpriteFrame = atoi(token);
					cReadModeB = 15;
					break;
				case 15: // m_wPrice
					m_pItemForSaleList[iItemForSaleListIndex]->m_wPrice = atoi(token);
					cReadModeB = 16;
					break;
				case 16: // m_wWeight
					m_pItemForSaleList[iItemForSaleListIndex]->m_wWeight = atoi(token);
					cReadModeB = 17;
					break;
				case 17: // Appr Value
					//m_pItemForSaleList[iItemForSaleListIndex]->m_cApprValue = atoi(token);
					cReadModeB = 18;
					break;
				case 18: // m_cSpeed
					m_pItemForSaleList[iItemForSaleListIndex]->m_cSpeed = atoi(token);
					cReadModeB = 19;
					break;
				case 19: // Level Limit
					m_pItemForSaleList[iItemForSaleListIndex]->m_sLevelLimit = atoi(token);
					m_pItemForSaleList[iItemForSaleListIndex]->m_dwCount = 1;
					cReadModeA = 0;
					cReadModeB = 0;
					iItemForSaleListIndex++;
					break;
				}
				break;

			default:
				break;
			}
		}else
		{	if (memcmp(token, "ItemForSale", 4) == 0)
			{	if (iItemForSaleListIndex >= DEF_MAXMENUITEMS)
				{	delete pStrTok;
					return FALSE;
				}
				cReadModeA = 1;
				cReadModeB = 1;
				m_pItemForSaleList[iItemForSaleListIndex] = new class CItem;
		}	}
		token = pStrTok->pGet();
	}
	delete pStrTok;
	if ((cReadModeA != 0) || (cReadModeB != 0)) return FALSE;
	return TRUE;
}


static char __cSpace[] = {8,8,8,8,8,8,8,8,8,8, 8,8,8,8,8, 8,6,8,7,8,8,9,10,9,7, 8,8,8,8,8, 8,8,
                          15,16,12,17,14,15,14,16,10,13, 19,10,17,17,15,14,15,16,13,17, 16,16,20,17,16,14,
	       			      8,8,8,8,8,8,	8,6,7,8,7,7,7,7,4,7,7,  4,11,7,8,8,7,8,6,5,8,9,14,8,9,8, 8,8,8,8,
				          8,8,8,8,8,8,8};
void CGame::PutString_SprFont(int iX, int iY, char * pStr, short sR, short sG, short sB)
{
 int iXpos;
 DWORD iCnt;
 DWORD dwTime = G_dwGlobalTime;
 char  cTmpStr[100];

	ZeroMemory(cTmpStr, sizeof(cTmpStr));
	strcpy(cTmpStr, pStr);
	iXpos = iX;
	for (iCnt = 0; iCnt < strlen(cTmpStr); iCnt++) {
		if ((cTmpStr[iCnt] >= 33) && (cTmpStr[iCnt] <= 122)) {
			m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteRGB(iXpos+1, iY, cTmpStr[iCnt] - 33, sR+11, sG+7, sB+6, dwTime);
			if ((sR == 0) && (sG == 0) && (sB == 0))
				 m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos, iY, cTmpStr[iCnt] - 33, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 33, sR, sG, sB, dwTime);
			 iXpos += __cSpace[cTmpStr[iCnt] - 33];
		}
		else iXpos += 5;
	}
}

void CGame::PutString_SprFont2(int iX, int iY, char * pStr, short sR, short sG, short sB)
{
 int iXpos, iR, iG, iB;
 DWORD iCnt;
 DWORD dwTime = G_dwGlobalTime;
 char  cTmpStr[200];

	m_DDraw.ColorTransferRGB(RGB(sR, sG, sB), &iR, &iG, &iB);

	ZeroMemory(cTmpStr, sizeof(cTmpStr));
	strcpy(cTmpStr, pStr);

	iXpos = iX;
	for (iCnt = 0; iCnt < strlen(cTmpStr); iCnt++) {
		if ((cTmpStr[iCnt] >= 33) && (cTmpStr[iCnt] <= 122)) {
			m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos+1, iY, cTmpStr[iCnt] - 33, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos+1, iY+1, cTmpStr[iCnt] - 33, dwTime);
			if ((sR == 0) && (sG == 0) && (sB == 0))
				 m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos, iY, cTmpStr[iCnt] - 33, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 33, iR, iG, iB, dwTime);
			 iXpos += __cSpace[cTmpStr[iCnt] - 33];
		}
		else iXpos += 5;
	}
}

void CGame::PutString_SprFont3(int iX, int iY, char * pStr, short sR, short sG, short sB, BOOL bTrans, int iType)
{
 int iXpos, iAdd;
 DWORD iCnt;
 DWORD dwTime = G_dwGlobalTime;
 char  cTmpStr[128];

	ZeroMemory(cTmpStr, sizeof(cTmpStr));
	strcpy(cTmpStr, pStr);

	if (iType != -1) {
		iAdd = 95*iType;
		iXpos = iX;
		for (iCnt = 0; iCnt < strlen(cTmpStr); iCnt++) {
			if ((cTmpStr[iCnt] >= 32) && (cTmpStr[iCnt] <= 126)) {

				if (bTrans == FALSE) {
					m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteFast(iXpos, iY+1, cTmpStr[iCnt] - 32 +iAdd, dwTime);
					m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteFast(iXpos+1, iY+1, cTmpStr[iCnt] - 32 +iAdd, dwTime);
					if ((sR == 0) && (sG == 0) && (sB == 0))
						 m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteFast(iXpos, iY, cTmpStr[iCnt] - 32 +iAdd, dwTime);
					else m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 32 +iAdd, sR, sG, sB, dwTime);

				}
				else m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutTransSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 32 +iAdd, sR, sG, sB, dwTime);

				iXpos += (m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->m_stBrush[cTmpStr[iCnt] - 32 +iAdd].szx);
			}
			else iXpos += 5;
		}
	}
	else {
		iAdd = 0;
		iXpos = iX;
		for (iCnt = 0; iCnt < strlen(cTmpStr); iCnt++) {
			if ((cTmpStr[iCnt] >= 32) && (cTmpStr[iCnt] <= 126)) {

				if (bTrans == FALSE) {
					m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteFast(iXpos, iY+1, cTmpStr[iCnt] - 32 +iAdd, dwTime);
					m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteFast(iXpos+1, iY+1, cTmpStr[iCnt] - 32 +iAdd, dwTime);
					if ((sR == 0) && (sG == 0) && (sB == 0))
						 m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteFast(iXpos, iY, cTmpStr[iCnt] - 32 +iAdd, dwTime);
					else m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 32 +iAdd, sR, sG, sB, dwTime);

				}
				else m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutTransSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 32 +iAdd, sR, sG, sB, dwTime);

				iXpos += (m_pSprite[DEF_SPRID_INTERFACE_FONT2]->m_stBrush[cTmpStr[iCnt] - 32 +iAdd].szx);
			}
			else iXpos += 5;
		}
	}
}

static char __cSpace2[] = {6,4,6,6,6,6,6,6,6,6,6}; //{8,6,9,8,8,9,8,8,8,8};
void CGame::PutString_SprNum(int iX, int iY, char * pStr, short sR, short sG, short sB)
{int iXpos;
 unsigned char iCnt;
 DWORD dwTime = G_dwGlobalTime;
 char  cTmpStr[200];
 WORD  wR, wG, wB;
	ZeroMemory(cTmpStr, sizeof(cTmpStr));
	strcpy(cTmpStr, pStr);
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(sR, sG, sB), &wR, &wG, &wB);
	iXpos = iX;
	for (iCnt = 0; iCnt < strlen(cTmpStr); iCnt++)
	{	if ((cTmpStr[iCnt] >= 0x30) && (cTmpStr[iCnt] <= 0x39))
		{	m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSprite(iXpos+2, iY, cTmpStr[iCnt] - 0x30 +6, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSprite(iXpos+1, iY+1, cTmpStr[iCnt] - 0x30 +6, dwTime);
			if ((sR == 0) && (sG == 0) && (sB == 0))
				 m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSprite(iXpos, iY, cTmpStr[iCnt] - 0x30 +6, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(iXpos, iY, cTmpStr[iCnt] - 0x30 +6, wR, wG, wB, dwTime);
			iXpos += __cSpace2[cTmpStr[iCnt] - 0x30];
	}	}
}

void CGame::PutString(int iX, int iY, char * pString, COLORREF color, BOOL bHide, char cBGtype, BOOL bIsPreDC)
{char * pTmp;
 int i;
	if (strlen(pString) == 0) return;
	if (bIsPreDC == FALSE) m_DDraw._GetBackBufferDC();
	if (bHide == FALSE)
	{	switch (cBGtype) {
		case 0:
			m_DDraw.TextOut(iX+1, iY, pString, color);
			break;
		case 1:
			m_DDraw.TextOut(iX, iY+1, pString, RGB(5,5,5));
			m_DDraw.TextOut(iX+1, iY+1, pString, RGB(5,5,5));
			m_DDraw.TextOut(iX+1, iY, pString, RGB(5,5,5));
			break;
		}
		m_DDraw.TextOut(iX, iY, pString, color);
	}else
	{ 	pTmp = new char[strlen(pString)+2];
		ZeroMemory(pTmp, strlen(pString)+2);
		strcpy(pTmp, pString);
		for (i = 0; i < (int)strlen(pString); i++)
			if (pTmp[i] != NULL) pTmp[i] = '*';

		switch (cBGtype) {
		case 0:
			m_DDraw.TextOut(iX+1, iY, pTmp, color);
			break;
		case 1:
			m_DDraw.TextOut(iX, iY+1, pTmp, RGB(5,5,5));
			m_DDraw.TextOut(iX+1, iY+1, pTmp, RGB(5,5,5));
			m_DDraw.TextOut(iX+1, iY, pTmp, RGB(5,5,5));
			break;
		}
		m_DDraw.TextOut(iX, iY, pTmp, color);
		delete[] pTmp;
	}
	if (bIsPreDC == FALSE) m_DDraw._ReleaseBackBufferDC();
}


void CGame::PutString(int iX, int iY, char * pString, COLORREF color)
{
	m_DDraw._GetBackBufferDC();
	m_DDraw.TextOut(iX, iY, pString, color);
	m_DDraw._ReleaseBackBufferDC();
}

void CGame::PutString2(int iX, int iY, char * pString, short sR, short sG, short sB)
{
	m_DDraw._GetBackBufferDC();
	m_DDraw.TextOut(iX+1, iY, pString, RGB(0, 0, 0));
	m_DDraw.TextOut(iX, iY+1, pString, RGB(0, 0, 0));
	m_DDraw.TextOut(iX+1, iY+1, pString, RGB(0, 0, 0));
	m_DDraw.TextOut(iX, iY, pString, RGB(sR, sG, sB));
	m_DDraw._ReleaseBackBufferDC();
}

void CGame::PutAlignedString(int iX1, int iX2, int iY, char * pString, short sR, short sG, short sB)
{
	RECT rt;
	m_DDraw._GetBackBufferDC();
	SetRect(&rt, iX1, iY, iX2, iY+15);
	m_DDraw.DrawText(&rt, pString, RGB(sR, sG, sB));
	m_DDraw._ReleaseBackBufferDC();
}

BOOL CGame::bInitMagicCfgList()
{
 char cFn[255], cTemp[255];
 char * pContents, * token;
 char seps[] = "= ,\t\n";
 char cReadModeA = 0;
 char cReadModeB = 0;
 int  iMagicCfgListIndex = 0;
 class CStrTok * pStrTok;
 HANDLE hFile;
 FILE * pFile;
 DWORD  dwFileSize;

	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFn, sizeof(cFn));

	// CLEROTH - MAGIC CFG
	strcpy(cTemp, "magiccfg.txt");

	strcat(cFn, "contents");
	strcat(cFn, "\\");
	strcat(cFn, "\\");
	strcat(cFn, cTemp);

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFn, "rt");
	if (pFile == NULL) return FALSE;
	else {
		pContents = new char[dwFileSize+1];
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, dwFileSize, 1, pFile);
		fclose(pFile);
	}

	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL ) {
		if (cReadModeA != 0) {
			switch (cReadModeA) {
			case 1:
				switch (cReadModeB) {
				case 1:
					if (_bGetIsStringIsNumber(token) == FALSE)
					{	delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					if (m_pMagicCfgList[atoi(token)] != NULL)
					{	delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pMagicCfgList[atoi(token)] = new class CMagic;
					iMagicCfgListIndex = atoi(token);

					cReadModeB = 2;
					break;

				case 2:
					ZeroMemory(m_pMagicCfgList[iMagicCfgListIndex]->m_cName, sizeof(m_pMagicCfgList[iMagicCfgListIndex]->m_cName));
					memcpy(m_pMagicCfgList[iMagicCfgListIndex]->m_cName, token, strlen(token));
					cReadModeB = 3;
					break;

				case 3: // m_sValue1
					if (_bGetIsStringIsNumber(token) == FALSE) {
						delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pMagicCfgList[iMagicCfgListIndex]->m_sValue1 = atoi(token);
					cReadModeB = 4;
					break;

				case 4: // m_sValue2	// INT
					if (_bGetIsStringIsNumber(token) == FALSE) {
						delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pMagicCfgList[iMagicCfgListIndex]->m_sValue2 = atoi(token);
					cReadModeB = 5;
					break;

				case 5: // m_sValue3	// COST
					if (_bGetIsStringIsNumber(token) == FALSE) {
						delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pMagicCfgList[iMagicCfgListIndex]->m_sValue3 = atoi(token);
					cReadModeB = 6;
					break;

				// CLEROTH MAGIC CFG
				case 6: // m_sValue4	// STR
					if (_bGetIsStringIsNumber(token) == FALSE)
					{	delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pMagicCfgList[iMagicCfgListIndex]->m_sValue4 = atoi(token);
					cReadModeB = 7;
					break;

				case 7: // m_sValue5
					cReadModeB = 8;
					break;

				case 8: // m_sValue6
					cReadModeB = 9;
					break;

				case 9: // m_bIsVisible
					if (_bGetIsStringIsNumber(token) == FALSE)
					{	delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					if( atoi(token) == 0 ) m_pMagicCfgList[iMagicCfgListIndex]->m_bIsVisible = FALSE;
					else m_pMagicCfgList[iMagicCfgListIndex]->m_bIsVisible = TRUE;
					cReadModeA = 0;
					cReadModeB = 0;
					break;
				}
				break;

			default:
				break;
			}
		}
		else {
			if (memcmp(token, "magic", 5) == 0) {
				cReadModeA = 1;
				cReadModeB = 1;
			}
		}
		token = pStrTok->pGet();
	}

	delete pStrTok;
	delete[] pContents;

	if ((cReadModeA != 0) || (cReadModeB != 0)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CGame::bCheckImportantFile()
{	HANDLE hFile;

#ifndef _DEBUG
	hFile = CreateFile("CONTENTS\\badword.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( hFile == INVALID_HANDLE_VALUE ) return FALSE;
	CloseHandle( hFile );
#endif

	hFile = CreateFile("SPRITES\\TREES1.PAK", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if( hFile == INVALID_HANDLE_VALUE ) return FALSE;

//	// FileSize : 1846406.... Anti Tree1.pak hack....inutile ca peut se modifier sans changer la taille!
//	if( GetFileSize( hFile, NULL ) != 2945524 )
//	{	CloseHandle( hFile );
//		return FALSE;
//	}

	CloseHandle( hFile );
	return TRUE;
}

BOOL CGame::bInitSkillCfgList()
{
 char cFn[255], cTemp[255];
 char * pContents, * token;
 char seps[] = "= ,\t\n";
 char cReadModeA = 0;
 char cReadModeB = 0;
 int  iSkillCfgListIndex = 0;
 class CStrTok * pStrTok;
 HANDLE hFile;
 FILE * pFile;
 DWORD  dwFileSize;

	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFn, sizeof(cFn));

	strcpy(cTemp, "Skillcfg.txt");
	strcat(cFn, "contents");
	strcat(cFn, "\\");
	strcat(cFn, "\\");
	strcat(cFn, cTemp);

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFn, "rt");
	if (pFile == NULL) return FALSE;
	else {
		pContents = new char[dwFileSize+1];
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, dwFileSize, 1, pFile);
		fclose(pFile);
	}

	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL ) {
		if (cReadModeA != 0) {
			switch (cReadModeA) {
			case 1:
				switch (cReadModeB) {
				case 1:
					if (_bGetIsStringIsNumber(token) == FALSE)
					{	delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					if (m_pSkillCfgList[atoi(token)] != NULL)
					{	delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pSkillCfgList[atoi(token)] = new class CSkill;
					iSkillCfgListIndex = atoi(token);
					cReadModeB = 2;
					break;

				case 2:
					ZeroMemory(m_pSkillCfgList[iSkillCfgListIndex]->m_cName, sizeof(m_pSkillCfgList[iSkillCfgListIndex]->m_cName));
					memcpy(m_pSkillCfgList[iSkillCfgListIndex]->m_cName, token, strlen(token));
					cReadModeB = 3;
					break;

				case 3: // m_bIsUseable
					if (_bGetIsStringIsNumber(token) == FALSE) {
						delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pSkillCfgList[iSkillCfgListIndex]->m_bIsUseable = (BOOL)atoi(token);
					cReadModeB = 4;
					break;

				case 4: // m_cUseMethod
					if (_bGetIsStringIsNumber(token) == FALSE) {
						delete[] pContents;
						delete pStrTok;
						return FALSE;
					}
					m_pSkillCfgList[iSkillCfgListIndex]->m_cUseMethod = atoi(token);
					cReadModeA = 0;
					cReadModeB = 0;
					break;
				}
				break;

			default:
				break;
			}
		}
		else {
			if (memcmp(token, "skill", 5) == 0) {
				cReadModeA = 1;
				cReadModeB = 1;
			}
		}
		token = pStrTok->pGet();
	}

	delete pStrTok;
	delete[] pContents;

	if ((cReadModeA != 0) || (cReadModeB != 0)) {
		return FALSE;
	}

	return TRUE;
}


BOOL CGame::_bGetIsStringIsNumber(char * pStr)
{
 int i;
	for (i = 0; i < (int)strlen(pStr); i++)
	if ((pStr[i] != '-') && ((pStr[i] < (char)'0') || (pStr[i] > (char)'9'))) return FALSE;

	return TRUE;
}


void CGame::RequestFullObjectData(WORD wObjectID)
{
 char    cMsg[256];
 int     iRet;
 DWORD * dwp;
 WORD  * wp;

	ZeroMemory(cMsg, sizeof(cMsg));

	dwp = (DWORD *)(cMsg + DEF_INDEX4_MSGID);
	*dwp = MSGID_REQUEST_FULLOBJECTDATA;
	wp  = (WORD *)(cMsg + DEF_INDEX2_MSGTYPE);
	*wp = wObjectID;

	iRet = m_pGSock->iSendMsg((char *)cMsg, 6);

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
}


BOOL   CGame::DrawObject_OnAttack(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iHelmIndex, iR, iG, iB;
 int iWeaponIndex, iWeapon, iAdd, iShieldIndex, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponGlare, iShieldGlare;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 81 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66) bInv = TRUE; //Energy-Ball,Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}
	iWeaponGlare = (_tmp_sAppr4 & 0x000C) >> 2;
	iShieldGlare = (_tmp_sAppr4 & 0x0003);
	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}
	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		if ((_tmp_sAppr2 & 0xF000) != 0) {
			iWeapon = ((_tmp_sAppr2 & 0x0FF0) >> 4);
			if (iWeapon == 0) iAdd = 6;
			if ((iWeapon >= 1)  && (iWeapon <= 39)) iAdd = 6;
			if ((iWeapon >= 40) && (iWeapon <= 59)) iAdd = 7;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*4 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 4;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (5 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 5;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 5;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 5;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 5;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 5;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 5;
			iWeaponIndex = -1;
			iShieldIndex = -1;
		}
		break;

	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iWeapon = ((_tmp_sAppr2 & 0x0FF0) >> 4);
			if (iWeapon == 0) iAdd = 6;
			if ((iWeapon >= 1)  && (iWeapon <= 39)) iAdd = 6;
			if ((iWeapon >= 40) && (iWeapon <= 59)) iAdd = 7;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*4 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 4;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (5 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 5;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 5;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 5;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 5;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 5;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 5;
			iWeaponIndex = -1;
			iShieldIndex = -1;
		}
		break;

	default:
		if (_tmp_sAppr2 != 0)
		{	 iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			 _tmp_cFrame = _tmp_sAppr2 -1;
		}
		else if (_tmp_sOwnerType == 66) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else if (_tmp_sOwnerType == 73) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else if (_tmp_sOwnerType == 86) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (1 * 8);
		else if (_tmp_sOwnerType == 87) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (1 * 8);
		else if (_tmp_sOwnerType == 89) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (1 * 8);
		else iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iBodyArmorIndex = -1;
		iArmArmorIndex  = -1;
		iBootsIndex     = -1;
		iPantsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	if (m_bIsCrusadeMode) DrawObjectFOE(sX, sY, _tmp_cFrame);
	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if (bTrans == FALSE)
	{	CheckActiveAura(sX, sY, dwTime, _tmp_sOwnerType);
		if (_cDrawingOrder[_tmp_cDir] == 1)
		{	if (iWeaponIndex != -1)
			{	if (iWeaponColor == 0)
				{	m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
				}else
				{	m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY,  _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				}
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}
				if (_tmp_cFrame == 3) m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY, _tmp_cFrame -1, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
			}
			switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
            case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // FireWyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

			if (_tmp_sOwnerType == 81) // Abaddon
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			}else if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				    m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

			if ((iHairIndex   != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1)
			{	if (iPantsColor == 0)
					 m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1)
			{	if (iArmColor == 0)
					 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1)
			{	if (iArmorColor == 0)
					 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1)
			{	if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (((_tmp_sAppr2 & 0x000F) == 8) && (iShieldGlare == 1))
			{	m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
			}else
			if (iShieldIndex != -1)
			{	if (iShieldColor == 0)
					 m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}
		}else
		{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
            case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

			if (_tmp_sOwnerType == 81) // Abaddon
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			}else if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
			}

			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				    m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);


			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

			if ((iHairIndex   != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1)) {
				if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1)
			{	if (iPantsColor == 0)
					 m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1)
			{	if (iArmColor == 0)
					 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1)
			{	if (iArmorColor == 0)
					 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1)
			{	if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iShieldIndex != -1)
			{	if (iShieldColor == 0)
					 m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iWeaponIndex != -1)
			{	if (iWeaponColor == 0)
					 m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
				else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}
				if (_tmp_cFrame == 3) m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY, _tmp_cFrame -1, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
		}	}

		if ((_tmp_iStatus & 0x20) != 0) // Berserk
			m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX, sY, _tmp_cFrame, 0, -5, -5, dwTime);
		DrawAngel((_tmp_cDir - 1), sX+20, sY-20, _tmp_cFrame%8, dwTime);
		CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}
	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}

	// Snoopy: Abaddon effects
	if (_tmp_sOwnerType == 81)
	{	int randFrame = _tmp_cFrame % 12;
		m_pEffectSpr[154]->PutTransSprite70(sX-50	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[155]->PutTransSprite70(sX-20	, sY-80		, randFrame, dwTime);
		m_pEffectSpr[156]->PutTransSprite70(sX+70	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[157]->PutTransSprite70(sX-30	, sY		, randFrame, dwTime);
		m_pEffectSpr[158]->PutTransSprite70(sX-60	, sY+90		, randFrame, dwTime);
		m_pEffectSpr[159]->PutTransSprite70(sX+65	, sY+85		, randFrame, dwTime);
		switch (_tmp_cDir) {
		case 1:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+108 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-50	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 2:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-70	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 3:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+105 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-90	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 4:
			m_pEffectSpr[153]->PutTransSprite70(sX-35	, sY+100 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-80	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 5:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-65	, sY-5	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 6:
			m_pEffectSpr[153]->PutTransSprite70(sX+45	, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-31	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 7:
			m_pEffectSpr[153]->PutTransSprite70(sX+40	, sY+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-30	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 8:
			m_pEffectSpr[153]->PutTransSprite70(sX+20	, sY+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-20	, sY+16	, _tmp_iEffectFrame %15, dwTime);
			break;
	}	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}


BOOL   CGame::DrawObject_OnAttackMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iHelmIndex, iR, iG, iB;
 int iWeaponIndex, iWeapon, iAdd, iShieldIndex, iMantleIndex, dx, dy, dsx, dsy;
 int cFrameMoveDots;
 BOOL bInv = FALSE, bDashDraw = FALSE;
 int iWeaponGlare, iShieldGlare;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 81 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66) bInv = TRUE; //Energy-Ball,Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}
	iWeaponGlare = (_tmp_sAppr4 & 0x000C) >> 2;
	iShieldGlare = (_tmp_sAppr4 & 0x0003);
	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}

	switch (_tmp_cFrame) {
	case 4:  _tmp_cFrame = 4; break;
	case 5:  _tmp_cFrame = 4; break;
	case 6:  _tmp_cFrame = 4; break;
	case 7:  _tmp_cFrame = 4; break;
	case 8:  _tmp_cFrame = 4; break;
	case 9:  _tmp_cFrame = 4; break;
	case 10: _tmp_cFrame = 5; break;
	case 11: _tmp_cFrame = 6; break;
	case 12: _tmp_cFrame = 7; break;
	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		if ((_tmp_sAppr2 & 0xF000) != 0) {
			iWeapon = ((_tmp_sAppr2 & 0x0FF0) >> 4);
			if (iWeapon == 0) iAdd = 6;
			if ((iWeapon >= 1)  && (iWeapon <= 39)) iAdd = 6;
			if ((iWeapon >= 40) && (iWeapon <= 59)) iAdd = 7;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*4 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 4;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{ 	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (5 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 5;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 5;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 5;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 5;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 5;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 5;
			iWeaponIndex = -1;
			iShieldIndex = -1;
		}
		break;

	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		if ((_tmp_sAppr2 & 0xF000) != 0) {
			iWeapon = ((_tmp_sAppr2 & 0x0FF0) >> 4);
			if (iWeapon == 0) iAdd = 6;
			if ((iWeapon >= 1)  && (iWeapon <= 39)) iAdd = 6;
			if ((iWeapon >= 40) && (iWeapon <= 59)) iAdd = 7;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*4 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 4;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (5 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 5;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 5;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 5;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 5;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 5;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 5;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 5;
			iWeaponIndex = -1;
			iShieldIndex = -1;
		}
		break;
	default:
		iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iBodyArmorIndex = -1;
		iArmArmorIndex  = -1;
		iBootsIndex     = -1;
		iPantsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	dx = 0;
	dy = 0;
	if ((_tmp_cFrame >= 1) && (_tmp_cFrame <= 3))
	{	switch (_tmp_cFrame) {
		case 1: cFrameMoveDots = 26; break;
		case 2: cFrameMoveDots = 16; break;
		case 3: cFrameMoveDots = 0;  break;
		}
		switch (_tmp_cDir) {
		case 1 : dy =  cFrameMoveDots; break;
		case 2 : dy =  cFrameMoveDots; dx = -cFrameMoveDots; break;
		case 3 : dx = -cFrameMoveDots; break;
		case 4 : dx = -cFrameMoveDots; dy = -cFrameMoveDots; break;
		case 5 : dy = -cFrameMoveDots; break;
		case 6 : dy = -cFrameMoveDots; dx =  cFrameMoveDots; break;
		case 7 : dx =  cFrameMoveDots; break;
		case 8 : dx =  cFrameMoveDots; dy =  cFrameMoveDots; break;
		}
		switch (_tmp_cFrame) {
		case 1: dy++;    break;
		case 2: dy += 2; break;
		case 3: dy++;    break;
		}
		switch (_tmp_cFrame) {
		case 2: bDashDraw = TRUE; cFrameMoveDots = 26; break;
		case 3: bDashDraw = TRUE; cFrameMoveDots = 16; break;
		}
		dsx = 0;
		dsy = 0;
		switch (_tmp_cDir) {
		case 1 : dsy =  cFrameMoveDots; break;
		case 2 : dsy =  cFrameMoveDots; dsx = -cFrameMoveDots; break;
		case 3 : dsx = -cFrameMoveDots; break;
		case 4 : dsx = -cFrameMoveDots; dsy = -cFrameMoveDots; break;
		case 5 : dsy = -cFrameMoveDots; break;
		case 6 : dsy = -cFrameMoveDots; dsx =  cFrameMoveDots; break;
		case 7 : dsx =  cFrameMoveDots; break;
		case 8 : dsx =  cFrameMoveDots; dsy =  cFrameMoveDots; break;
		}
	}else if (_tmp_cFrame > 3)
	{	dx = 0;
		dy = 0;
	}else
	{	switch (_tmp_cDir) {
		case 1: dy = 32; break;
		case 2: dy = 32; dx = -32; break;
		case 3: dx = -32; break;
		case 4: dx = -32; dy = -32; break;
		case 5: dy = -32; break;
		case 6: dy = -32; dx = 32; break;
		case 7: dx = 32; break;
		case 8: dx = 32; dy = 32; break;
	}	}

	if (m_bIsCrusadeMode) DrawObjectFOE(sX+dx, sY+dy, _tmp_cFrame);

	if (_tmp_iEffectType != 0) {
		switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
		}
	}

	if (bTrans == FALSE)
	{	CheckActiveAura(sX+dx, sY+dy, dwTime, _tmp_sOwnerType);
		if (_cDrawingOrder[_tmp_cDir] == 1)
		{	if (iWeaponIndex != -1)
			{	if (iWeaponColor == 0)
					 m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}
				if (_tmp_cFrame == 3) m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy, _tmp_cFrame -1, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
			}
			switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
            case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				}
				break;
			}

			if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else {
				if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				    m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);


			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0)) {
				if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

			if ((iHairIndex != -1) && (iHelmIndex == -1)) {
				_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1)) {
				if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1) {
				if (iPantsColor == 0)
					 m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1) {
				if (iArmColor == 0)
					 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0)) {
				if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1) {
				if (iArmorColor == 0)
					 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1) {
				if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2)) {
				if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iShieldIndex != -1)
			{	if (iShieldColor == 0)
					 m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

				else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1)) {
				if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}
		}else
		{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
            case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;

			default:
				if (m_cDetailLevel != 0) {
					if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				}
				break;
			}

			if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else {
				if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				    m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0)) {
				if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

			if ((iHairIndex != -1) && (iHelmIndex == -1)) {
				_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1)) {
				if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1) {
				if (iPantsColor == 0)
					 m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1) {
				if (iArmColor == 0)
					 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0)) {
				if (iBootsColor == 0)
					 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1) {
				if (iArmorColor == 0)
					 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1)
			{	if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}


			if (iShieldIndex != -1)
			{	if (iShieldColor == 0)
					 m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13+dx, sY -34+dy, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1)) {
				if (iMantleColor == 0)
					 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iWeaponIndex != -1)
			{	if (iWeaponColor == 0)
					 m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}
				if (_tmp_cFrame == 3) m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy, _tmp_cFrame -1, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
		}	}

		// Berserk
		if ((_tmp_iStatus & 0x20) != 0)
			m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, 0, -5, -5, dwTime);
		DrawAngel(8+(_tmp_cDir - 1), sX+dx+20, sY+dy-20, _tmp_cFrame%8, dwTime);
		CheckActiveAura2(sX+dx, sY+dy, dwTime,  _tmp_sOwnerType);

		if (bDashDraw == TRUE) {
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSpriteRGB(sX+dsx, sY+dsy, _tmp_cFrame, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
			if (iWeaponIndex != -1) m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dsx, sY+dsy, _tmp_cFrame, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
			if (iShieldIndex != -1) m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dsx, sY+dsy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[10] -(m_wR[0]/3), m_wG[10] -(m_wG[0]/3), m_wB[10] -(m_wB[0]/3), dwTime);
		}
	}
	else if( strlen(_tmp_cName) > 0 )
	{
		if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX+dx, sY+dy, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX+dx, sY+dy, _tmp_sOwnerType, _tmp_iStatus);
	}

	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID)) {
			m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX+dx;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY+dy;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	_tmp_dx = dx;
	_tmp_dy = dy;

	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;

	return FALSE;
}


BOOL   CGame::DrawObject_OnMagic(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iR, iG, iB, iHelmIndex, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66) bInv = TRUE; //Energy-Ball,Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}

	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0)
			bInv = TRUE;
		else
		{	if (_tmp_iChatIndex != NULL)
			{	if (m_pChatMsgList[_tmp_iChatIndex] != NULL)
				{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
					m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
				}else
				{	m_pMapData->ClearChatMsg(indexX, indexY);
			} 	}
			return FALSE;
	}	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
  		iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (8 * 8);
		iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 8;
		iHairIndex   = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 8;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 8;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 8;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 8;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 8;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 8;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 8;
		break;
	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;

		iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (8 * 8);
		iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 8;
		iHairIndex   = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 8;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 8;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 8;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 8;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 8;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 8;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 8;
		break;
	}

	/*
	switch (_tmp_cFrame) {
	case 15:
		_tmp_cFrame = 14;
		break;
	case 16:
		_tmp_cFrame = 14;
		break;
	case 17:
		_tmp_cFrame = 15;
		break;
	case 18:
		_tmp_cFrame = 15;
		break;
	case 19:
		_tmp_cFrame = 15;
		break;
	case 20:
		_tmp_cFrame = 15;
		break;
	case 21:
		_tmp_cFrame = 15;
		break;
	case 22:
		_tmp_cFrame = 15;
		break;
	case 23:
		_tmp_cFrame = 14;
		break;
	}
	*/
	if (m_bIsCrusadeMode) DrawObjectFOE(sX, sY, _tmp_cFrame);

	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if (bTrans == FALSE)
	{	CheckActiveAura(sX, sY, dwTime, _tmp_sOwnerType);
		switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
		case 10: // Slime
		case 35: // Energy Sphere
		case 50: // TW
		case 51: // CP
        case 60: // Plant
		case 65: // IceGolem
		case 66: // Wyvern
		case 73: // Fire Wyvern
		case 81: // Abaddon
		case 91: // Gate
			break;
		default:
			if (m_cDetailLevel != 0) {
				if (sX < 50)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
			}
			break;
		}

		if (bInv == TRUE)
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
		else {
			if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
		}
		SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

		if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);

		if ((iHairIndex != -1) && (iHelmIndex == -1))
		{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, iR, iG, iB, dwTime);
		}

		if ((iBootsIndex != -1) && (iSkirtDraw == 1))
		{	if (iBootsColor == 0)
				m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}

		if (iPantsIndex != -1)
		{	if (iPantsColor == 0)
				m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
		}

		if (iArmArmorIndex != -1)
		{	if (iArmColor == 0)
				m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
		}

		if ((iBootsIndex != -1) && (iSkirtDraw == 0))
		{	if (iBootsColor == 0)
				m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}

		if (iBodyArmorIndex != -1)
		{	if (iArmorColor == 0)
				m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
		}

		if (iHelmIndex != -1)
		{	if (iHelmColor == 0)
				 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
		}

		if (iMantleIndex != -1)
		{	if (iMantleColor == 0)
				m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 16 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}

		if ((_tmp_iStatus & 0x20) != 0) 	// Berserk
			m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX, sY, _tmp_cFrame, 0, -5, -5, dwTime);
		DrawAngel(32+(_tmp_cDir - 1), sX+20, sY-20, _tmp_cFrame%16, dwTime);
		CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}
	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}

BOOL   CGame::DrawObject_OnGetItem(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iR, iG, iB, iHelmIndex, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66) bInv = TRUE; //Energy-Ball,Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}

	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (9 * 8);
		iUndiesIndex    = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 9;
		iHairIndex      = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 9;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 9;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 9;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 9;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 9;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 9;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 9; 		break;

	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (9 * 8);
		iUndiesIndex    = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 9;
		iHairIndex      = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 9;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 9;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 9;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 9;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 9;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 9;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 9;
		break;
	default:
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iArmArmorIndex  = -1;
		iBodyArmorIndex = -1;
		iPantsIndex     = -1;
		iBootsIndex     = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	if (m_bIsCrusadeMode) DrawObjectFOE(sX, sY, _tmp_cFrame);

	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if (bTrans == FALSE)
	{	CheckActiveAura(sX, sY, dwTime, _tmp_sOwnerType);
		switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
		case 10: // Slime
		case 35: // Energy Sphere
		case 50: // TW
		case 51: // CP
        case 60: // Plant
		case 65: // IceGolem
		case 66: // Wyvern
		case 73: // Fire Wyvern
		case 81: // Abaddon
		case 91: // Gate
			break;
		default:
			if (m_cDetailLevel != 0)
			{	if (sX < 50)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
			}
			break;
		}

		if (bInv == TRUE)
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite2(sX, sY, _tmp_cFrame, dwTime);
		else {
			if ((_tmp_iStatus & 0x40) != 0)
				 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
			else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
		}
		SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
			     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

		if (iUndiesIndex != -1)
		{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
		}

		if ((iHairIndex != -1) && (iHelmIndex == -1))
		{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, iR, iG, iB, dwTime);
		}

		if ((iBootsIndex != -1) && (iSkirtDraw == 1))
		{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}	}

		if (iPantsIndex != -1)
		{	if(bInv) m_pSprite[iPantsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iPantsColor == 0)
					m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
		}	}

		if (iArmArmorIndex != -1)
		{	if(bInv) m_pSprite[iArmArmorIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iArmColor == 0)
					m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
		}	}

		if ((iBootsIndex != -1) && (iSkirtDraw == 0))
		{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}	}

		if (iBodyArmorIndex != -1)
		{	if(bInv) m_pSprite[iBodyArmorIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iArmorColor == 0)
					m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
		}	}

		if (iHelmIndex != -1)
		{	if(bInv) m_pSprite[iHelmIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
		}	}

		if (iMantleIndex != -1)
		{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
			else
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}	}

		if ((_tmp_iStatus & 0x20) != 0) // Berserk
			m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX, sY, _tmp_cFrame, 0, -5, -5, dwTime);
		DrawAngel(40+(_tmp_cDir - 1), sX+20, sY-20, _tmp_cFrame%4, dwTime);
		CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}
	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}

BOOL CGame::DrawObject_OnDamage(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iWeaponIndex, iShieldIndex, iHelmIndex, iR, iG, iB;
 int iAdd, iDrawMode, iMantleIndex;
 char cFrame;
 BOOL bInv = FALSE;
 int iWeaponGlare, iShieldGlare;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 81 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66) bInv = TRUE; //Energy-Ball,Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}
	iWeaponGlare = (_tmp_sAppr4 & 0x000C) >> 2;
	iShieldGlare = (_tmp_sAppr4 & 0x0003);
	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}
	cFrame = _tmp_cFrame;
	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		if (cFrame < 4)
		{	if ((_tmp_sAppr2 & 0xF000) != 0) iAdd = 1;
			else iAdd = 0;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*iAdd + (_tmp_cDir - 1);
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
			iDrawMode = 0;
		}else
		{	cFrame -= 4;
			iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (10 * 8);
			iUndiesIndex    = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 10;
			iHairIndex      = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 10;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 10;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 10;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 10;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 10;
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 5;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*5 + (_tmp_cDir - 1);
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 10;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 10;
			iDrawMode = 1;
		}
		break;
	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		if (cFrame < 4)
		{	if ((_tmp_sAppr2 & 0xF000) != 0) iAdd = 1;
			else iAdd = 0;
			iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex   = DEF_SPRID_HAIR_W	+ ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*iAdd + (_tmp_cDir - 1);
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
			iDrawMode = 0;
		}else
		{	cFrame -= 4;
			iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (10 * 8);
			iUndiesIndex    = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 10;
			iHairIndex      = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 10;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 10;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 10;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 10;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 10;
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 5;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*5 + (_tmp_cDir - 1);
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 10;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 10;
			iDrawMode = 1;
		}
		break;

	default:
		if (cFrame < 4)
		{	if (_tmp_sAppr2 != 0)
			{	iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
				 cFrame = _tmp_sAppr2 -1;
			}
			else if (_tmp_sOwnerType == 66) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 67) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 68) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 69) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 73) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 81) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 86) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 87) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 89) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 91) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		}else
		{	cFrame -= 4;
			if (_tmp_sAppr2 != 0)
			{	iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
				cFrame = _tmp_sAppr2 -1;
			}
			else if (_tmp_sOwnerType == 66) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 67) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 68) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 69) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 73) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			else if (_tmp_sOwnerType == 81) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 86) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 87) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 89) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 91) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (1 * 8);
			else iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
		}
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iArmArmorIndex  = -1;
		iBodyArmorIndex = -1;
		iPantsIndex     = -1;
		iBootsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		iDrawMode = 0;
		break;
	}
	if (m_bIsCrusadeMode) DrawObjectFOE(sX, sY, cFrame);

	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if (bTrans == FALSE)
	{	CheckActiveAura(sX, sY, dwTime, _tmp_sOwnerType);
		if (iDrawMode == 1) // Etrange, 1 semble impossible avec des mobs !
		{	if (_cDrawingOrder[_tmp_cDir] == 1)
			{	if (iWeaponIndex != -1)
				{	if (iWeaponColor == 0)
						m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY,  cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
					DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
					switch (iWeaponGlare) {
					case 0: break;
					case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}	}
				switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
				case 10: // Slime
				case 35: // Energy Sphere
				case 50: // TW
				case 51: // CP
		        case 60: // Plant
				case 65: // IceGolem
				case 66: // Wyvern
				case 73: // Fire Wyvern
				case 81: // Abaddon
				case 91: // Gate
					break;
				default:
					if (m_cDetailLevel != 0) {
						if (sX < 50)
							 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, cFrame, dwTime);
						else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, cFrame, dwTime);
					}
					break;
				}
				if (_tmp_sOwnerType == 35)
					m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

				if (_tmp_sOwnerType == 81) // Abaddon
				{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				}else if (bInv == TRUE)
					m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				else
				{	if ((_tmp_iStatus & 0x40) != 0)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, cFrame, dwTime);
				}
				SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
					     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);

				if ((iHairIndex != -1) && (iHelmIndex == -1))
				{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
					m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, iR, iG, iB, dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 1))
				{	if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iPantsIndex != -1)
				{	if (iPantsColor == 0)
						m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
				}

				if (iArmArmorIndex != -1)
				{	if (iArmColor == 0)
						m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 0))
				{	if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iBodyArmorIndex != -1)
				{	if (iArmorColor == 0)
						m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
				}

				if (iHelmIndex != -1)
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
				}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iShieldIndex != -1)
				{	if (iShieldColor == 0)
						m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
					switch (iShieldGlare) {
					case 0: break;
					//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
					case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 4 + cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 4 + cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}	}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}
			}else
			{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
				case 10: // Slime
				case 35: // Energy Sphere
				case 50: // TW
				case 51: // CP
				case 60: // Plant
				case 65: // IceGolem
				case 66: // Wyvern
				case 73: // Fire Wyvern
				case 81: // Abaddon
				case 91: // Gate
					break;
				default:
					if (m_cDetailLevel != 0) {
						if (sX < 50)
							 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, cFrame, dwTime);
						else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, cFrame, dwTime);
					}
					break;
				}
				if (_tmp_sOwnerType == 35)
					m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

				if (_tmp_sOwnerType == 81) // Abaddon
				{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				}else if (bInv == TRUE)
					m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				else
				{	if ((_tmp_iStatus & 0x40) != 0)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, cFrame, dwTime);
				}
				SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
					     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);

				if ((iHairIndex != -1) && (iHelmIndex == -1))
				{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
					m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, iR, iG, iB, dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 1))
				{	if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iPantsIndex != -1)
				{	if (iPantsColor == 0)
						m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
				}

				if (iArmArmorIndex != -1)
				{	if (iArmColor == 0)
						m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 0))
				{	if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iBodyArmorIndex != -1)
				{	if (iArmorColor == 0)
						m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
				}

				if (iHelmIndex != -1)
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
				}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iShieldIndex != -1)
				{	if (iShieldColor == 0)
						m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
					switch (iShieldGlare) {
					case 0: break;
					//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
					case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 4 + cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 4 + cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}	}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 4 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iWeaponIndex != -1)
				{	if (iWeaponColor == 0)
						m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY, cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
					DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
					switch (iWeaponGlare) {
					case 0: break;
					case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}	}

			if ((_tmp_iStatus & 0x20) != 0) 	// Berserk
				m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX, sY, cFrame, 0, -5, -5, dwTime);
			DrawAngel(16+(_tmp_cDir - 1), sX+20, sY-20, cFrame%4, dwTime);
			CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);

		}else // DrawMode != 1
		{	if (_cDrawingOrder[_tmp_cDir] == 1)
			{	if (iWeaponIndex != -1)
				{	if (iWeaponColor == 0)
						m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY,  cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
					DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
					switch (iWeaponGlare) {
					case 0: break;
					case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}	}
				switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
				case 10: // Slime
				case 35: // Energy Sphere
				case 50: // TW
				case 51: // CP
			    case 60: // Plant
				case 65: // IceGolem
				case 66: // Wyvern
				case 73: // Fire Wyvern
				case 81: // Abaddon
				case 91: // Gate
					break;
				default:
					if (m_cDetailLevel != 0)
					{	if (sX < 50)
							 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
						else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
					}
					break;
				}
				if (_tmp_sOwnerType == 35)
					m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

				if (_tmp_sOwnerType == 81) // Abaddon
				{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				}else if (bInv == TRUE)
					m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				else {
					if ((_tmp_iStatus & 0x40) != 0)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, cFrame, dwTime);
				}
				SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
					     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);

				if ((iHairIndex != -1) && (iHelmIndex == -1))
				{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
					m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, iR, iG, iB, dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 1)) {
					if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iPantsIndex != -1)
				{	if (iPantsColor == 0)
						m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
				}

				if (iArmArmorIndex != -1)
				{	if (iArmColor == 0)
						m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 0)) {
					if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iBodyArmorIndex != -1)
				{	if (iArmorColor == 0)
						m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
				}

				if (iHelmIndex != -1)
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
				}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iShieldIndex != -1)
				{	if (iShieldColor == 0)
						m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
					switch (iShieldGlare) {
					case 0: break;
					//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
					case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
					}
				}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}
			}else
			{	switch (_tmp_sOwnerType) {
				case 10: // Slime
				case 35: // Energy Sphere
				case 50: // TW
				case 51: // CP
			    case 60: // Plant
				case 65: // IceGolem
				case 66: // Wyvern
				case 73: // Fire Wyvern
				case 81: // Abaddon
				case 91: // Gate
					break;
				default:
					if (m_cDetailLevel != 0) {
						if (sX < 50)
							 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, cFrame, dwTime);
						else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, cFrame, dwTime);
					}
					break;
				}
				if (_tmp_sOwnerType == 35)
					m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

				if (_tmp_sOwnerType == 81) // Abaddon
				{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				}else if (bInv == TRUE)
					m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
				else {
					if ((_tmp_iStatus & 0x40) != 0)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, cFrame, dwTime);
				}

				SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
					     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);

				if ((iHairIndex != -1) && (iHelmIndex == -1))
				{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
					m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, iR, iG, iB, dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 1))
				{	if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iPantsIndex != -1)
				{	if (iPantsColor == 0)
						m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
				}

				if (iArmArmorIndex != -1)
				{	if (iArmColor == 0)
						m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
				}

				if ((iBootsIndex != -1) && (iSkirtDraw == 0))
				{	if (iBootsColor == 0)
						m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
				}

				if (iBodyArmorIndex != -1)
				{	if (iArmorColor == 0)
						m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
				}

				if (iHelmIndex != -1)
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
				}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iShieldIndex != -1)
				{	if (iShieldColor == 0)
						m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
					switch (iShieldGlare) {
					case 0: break;
					//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
					case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
				}	}

				if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
				{	if (iMantleColor == 0)
						m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
				}

				if (iWeaponIndex != -1)
				{	if (iWeaponColor == 0)
						m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY, cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
					DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
					switch (iWeaponGlare) {
					case 0: break;
					case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
					case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
					case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}	}

			if ((_tmp_iStatus & 0x20) != 0)	// Berserk
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSpriteRGB(sX, sY, cFrame, 0, -5, -5, dwTime);
			DrawAngel(16+(_tmp_cDir - 1), sX+20, sY-20, cFrame%4, dwTime);
			CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);
		}
	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}
	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}
		else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	// Snoopy: Abaddon effects
	if (_tmp_sOwnerType == 81)
	{	int randFrame = _tmp_cFrame % 12;
		m_pEffectSpr[154]->PutTransSprite70(sX-50	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[155]->PutTransSprite70(sX-20	, sY-80		, randFrame, dwTime);
		m_pEffectSpr[156]->PutTransSprite70(sX+70	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[157]->PutTransSprite70(sX-30	, sY		, randFrame, dwTime);
		m_pEffectSpr[158]->PutTransSprite70(sX-60	, sY+90		, randFrame, dwTime);
		m_pEffectSpr[159]->PutTransSprite70(sX+65	, sY+85		, randFrame, dwTime);
		switch (_tmp_cDir) {
		case 1:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+108 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-50	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 2:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-70	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 3:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+105 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-90	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 4:
			m_pEffectSpr[153]->PutTransSprite70(sX-35	, sY+100 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-80	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 5:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-65	, sY-5	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 6:
			m_pEffectSpr[153]->PutTransSprite70(sX+45	, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-31	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 7:
			m_pEffectSpr[153]->PutTransSprite70(sX+40	, sY+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-30	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 8:
			m_pEffectSpr[153]->PutTransSprite70(sX+20	, sY+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-20	, sY+16	, _tmp_iEffectFrame %15, dwTime);
			break;
	}	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;

	return FALSE;
}

BOOL CGame::DrawObject_OnDying(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iR, iG, iB,  iHelmIndex, iMantleIndex;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;
 char cFrame;

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}
	cFrame = _tmp_cFrame;

	 switch (_tmp_sOwnerType) {
	 case 1:
	 case 2:
	 case 3:
		if (cFrame < 6)
		{	iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (0 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15;
			iHairIndex   = DEF_SPRID_HAIR_M	+ ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 0;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 0;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 0;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 0;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 0;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 0;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 0;
		}else
		{	cFrame -= 6;
			iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (11 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 11;
			iHairIndex   = DEF_SPRID_HAIR_M	+ ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 11;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				     iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 11;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 11;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 11;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 11;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 11;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 11;
		}
		break;

	 case 4:
	 case 5:
	 case 6:
		 if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		 if (cFrame < 6)
		 {	iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (0 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15;
			iHairIndex   = DEF_SPRID_HAIR_W	+ ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 0;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 0;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 0;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 0;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 0;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 0;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 0;
		}else
		{ 	cFrame -= 6;
			iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (11 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 11;
			iHairIndex   = DEF_SPRID_HAIR_W	+ ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 11;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				     iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 11;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 11;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 11;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 11;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 11;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 11;
		}
		break;

	 default:
		if (cFrame < 4)
		{	if (_tmp_sAppr2 != 0)
			{	 iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
				 cFrame = _tmp_sAppr2 -1;
			}
			else if (_tmp_sOwnerType == 66) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 73) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 81) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 86) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 87) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 89) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 91) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
			iUndiesIndex = -1;
			iHairIndex   = -1;
			iArmArmorIndex = -1;
			iBodyArmorIndex = -1;
			iPantsIndex = -1;
			iBootsIndex = -1;
			iMantleIndex = -1;
			iHelmIndex      = -1;
			switch (_tmp_sOwnerType) {
			case 36: // AGT
			case 37: // CGT
			case 38: // MS
			case 39: // DT
			case 40: // ESG
			case 41: // GMG
			case 42: // ManaStone
				if (_tmp_sAppr2 == 0) cFrame = 0;
				break;
			case 51: cFrame = 0; break;
			}
		}else
		{	switch (_tmp_sOwnerType) {
			case 51: cFrame = 0; break;
			default: cFrame -= 4; break;
			}
			if (_tmp_sAppr2 != 0)
			{	 iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
				 cFrame = _tmp_sAppr2 -1;
			}
			else if (_tmp_sOwnerType == 66) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 73) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else if (_tmp_sOwnerType == 81) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 86) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 87) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 89) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			else if (_tmp_sOwnerType == 91) iBodyIndex =  DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			else iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			iUndiesIndex = -1;
			iHairIndex   = -1;
			iArmArmorIndex = -1;
			iBodyArmorIndex = -1;
			iPantsIndex = -1;
			iBootsIndex = -1;
			iMantleIndex = -1;
			iHelmIndex   = -1;
		}
		break;
	}
	if (m_bIsCrusadeMode) DrawObjectFOE(sX, sY, cFrame);

	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if (bTrans == FALSE)
	{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
		case 10: // Slime
		case 35: // Energy Sphere
		case 50: // TW
		case 51: // CP
        case 60: // Plant
		case 65: // IceGolem
		case 66: // Wyvern
		case 73: // Fire Wyvern
		case 81: // Abaddon
		case 91: // Gate
			break;
		default:
			if (m_cDetailLevel != 0)
			{	if (sX < 50)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, cFrame, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, cFrame, dwTime);
			}
			break;
		}
		if (_tmp_sOwnerType == 81)
		{	m_pEffectSpr[152]->PutTransSprite70(sX-80	, sY-15 , _tmp_iEffectFrame %27, dwTime); // Explosion Abaddon
			m_pEffectSpr[152]->PutTransSprite70(sX		, sY-15 , _tmp_iEffectFrame %27, dwTime);
			m_pEffectSpr[152]->PutTransSprite70(sX-40	, sY	, _tmp_iEffectFrame %27, dwTime);
			m_pEffectSpr[163]->PutTransSprite70(sX-90	, sY-80	, _tmp_iEffectFrame %12, dwTime); // Ames qui s'envolent
			m_pEffectSpr[160]->PutTransSprite70(sX-60	, sY-50	, _tmp_iEffectFrame %12, dwTime);
			m_pEffectSpr[161]->PutTransSprite70(sX-30	, sY-20	, _tmp_iEffectFrame %12, dwTime);
			m_pEffectSpr[162]->PutTransSprite70(sX		, sY-100, _tmp_iEffectFrame %12, dwTime);
			m_pEffectSpr[163]->PutTransSprite70(sX+30	, sY-30	, _tmp_iEffectFrame %12, dwTime);
			m_pEffectSpr[162]->PutTransSprite70(sX+60	, sY-90	, _tmp_iEffectFrame %12, dwTime);
			m_pEffectSpr[163]->PutTransSprite70(sX+90	, sY-50	, _tmp_iEffectFrame %12, dwTime);
			switch (_tmp_cDir) {
			case 1: m_pEffectSpr[140]->PutTransSprite70(sX, sY, cFrame, dwTime); break; // Abbadon dying
			case 2: m_pEffectSpr[141]->PutTransSprite70(sX, sY, cFrame, dwTime); break; // fixed sprit IDs
			case 3: m_pEffectSpr[142]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			case 4: m_pEffectSpr[143]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			case 5: m_pEffectSpr[144]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			case 6: m_pEffectSpr[145]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			case 7: m_pEffectSpr[146]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			case 8: m_pEffectSpr[147]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			}
		}else if( _tmp_sOwnerType == 66 ) m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
		else if( _tmp_sOwnerType == 73 )
		{	//m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, cFrame, dwTime);
			m_pSprite[33]->PutTransSprite(sX, sY, cFrame, dwTime);
			switch (_tmp_cDir) {
			case 1: m_pEffectSpr[141]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break; // Abbadon qui meurt
			case 2: m_pEffectSpr[142]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break;
			case 3: m_pEffectSpr[143]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break;
			case 4: m_pEffectSpr[144]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break;
			case 5: m_pEffectSpr[145]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break;
			case 6: m_pEffectSpr[146]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break;
			case 7: m_pEffectSpr[147]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break;
			//case 8: m_pEffectSpr[148]->PutTransSprite70(sX, sY, cFrame, dwTime); break;
			case 8: m_pEffectSpr[141]->PutTransSprite70(sX, sY, cFrame+8, dwTime); break; //due to buggy Sprite nb
			}
		}else
		{	if ((_tmp_iStatus & 0x40) != 0)
				 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
			else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, cFrame, dwTime);
		}

		SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
			     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

		if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);

		if ((iHairIndex != -1) && (iHelmIndex == -1))
		{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, iR, iG, iB, dwTime);
		}

		if ((iBootsIndex != -1) && (iSkirtDraw == 1))
		{	if (iBootsColor == 0)
				m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}

		if (iPantsIndex != -1)
		{	if (iPantsColor == 0)
				m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
		}

		if (iArmArmorIndex != -1)
		{	if (iArmColor == 0)
				m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
		}

		if ((iBootsIndex != -1) && (iSkirtDraw == 0))
		{	if (iBootsColor == 0)
				m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}

		if (iBodyArmorIndex != -1)
		{	if (iArmorColor == 0)
				m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
		}

		if (iHelmIndex != -1)
		{	if (iHelmColor == 0)
				 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
		}

		if (iMantleIndex != -1)
		{	if (iMantleColor == 0)
				m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}

		if ((_tmp_iStatus & 0x20) != 0) // Berserk
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSpriteRGB(sX, sY,  cFrame, 0, -5, -5, dwTime);
		DrawAngel(24+(_tmp_cDir - 1), sX+20, sY-20, _tmp_cFrame, dwTime);
		CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}
	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}

	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}

BOOL   CGame::DrawObject_OnDead(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iR, iG, iB, iFrame, iMantleIndex, iHelmIndex;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if( _tmp_sOwnerType == 66) return FALSE;

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		iFrame = 7;
		iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (11 * 8);
		iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 11;
		iHairIndex   = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 11;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 11;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 11;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 11;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 11;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 11;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 11;
		break;

	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		iFrame = 7;
		iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (11 * 8);
		iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 11;
		iHairIndex   = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 11;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 11;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 11;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 11;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 11;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 11;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 11;
		break;
	default:
		switch (_tmp_sOwnerType) {
		case 28: // Troll
		case 29: // Ogre
		case 30: // Liche
		case 31: // DD		// les 2 dernieres sont pas bonnes pour un mort !
		case 63: // Frost	// les 2 dernieres sont pas bonnes pour un mort !
			iFrame = 5;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			break;

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
		case 53: // BB
		case 54: // DE
		case 55: // Rabbit
		case 56: // Cat
		case 57: // Frog
		case 58: // MG
		case 59: // Ettin
		case 60: // Plant
		case 61: // Rudolph
		case 62: // Direboar
		case 64: // Crops  ----------- Crop ici! etonant, pourtant !
		case 65: // IceGolem
		case 70: // Dragon..........Ajouts par Snoopy
		case 71: // Centaur
		case 72: // ClawTurtle
		case 74: // GiantCrayfish
		case 75: // Gi Lizard
		case 76: // Gi Tree
		case 77: // Master Orc
		case 78: // Minaus
		case 79: // Nizie
		case 80: // Tentocle
		case 82: // Sorceress
		case 83: // ATK
		case 84: // MasterElf
		case 85: // DSK
		case 88: // Barbarian
			iFrame = 7;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			break;

		case 86: // HBT
		case 87: // CT
		case 89: // AGC
			iFrame = 7;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			break;

		case 66: // Wyvern
			iFrame = 15;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			break;

		case 73: // FireWyvern
			iFrame = 7;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			bTrans = TRUE; // Prevents showing hugly corpse
			break;

		case 81: // Abaddon
			iFrame = 0;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
			bTrans = TRUE; // Prevents showing hugly corpse
			break;

		case 51: // CP
			iFrame = 0;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			break;

		case 52: // GG
			iFrame = 11;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			break;

		case 91: // Gate
			iFrame = 5;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
			break;

		default: // 40*4 (10...27)
			iFrame = 3;
			iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			break;
		}
		iUndiesIndex = -1;
		iHairIndex   = -1;
		iArmArmorIndex = -1;
		iBodyArmorIndex = -1;
		iPantsIndex = -1;
		iBootsIndex = -1;
		iMantleIndex = -1;
		iHelmIndex      = -1;
		break;
	}
	if (bTrans == FALSE)
	{	if (_tmp_cFrame == -1)
		{	_tmp_cFrame = 7;
			if ((_tmp_iStatus & 0x40) != 0)
				 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, iFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
			else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, iFrame, dwTime);

			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1)
			{	if (iPantsColor == 0)
					m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1)
			{	if (iArmColor == 0)
					m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1)
			{	if (iArmorColor == 0)
					m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1)
			{	if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if (iMantleIndex != -1)
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}
		}else if ((_tmp_iStatus & 0x20) != 0)
				 m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX, sY, iFrame, -2*_tmp_cFrame +5, -2*_tmp_cFrame -5, -2*_tmp_cFrame -5, dwTime);
			else m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX, sY, iFrame, -2*_tmp_cFrame,-2*_tmp_cFrame,-2*_tmp_cFrame, dwTime);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}

	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}else
		{	m_pMapData->ClearDeadChatMsg(indexX, indexY);
	}	}
	// Snoopy: Abaddon effects
	if (_tmp_sOwnerType == 81)
	{	Abaddon_corpse(sX, sY); // By Snoopy....
	}else if (_tmp_sOwnerType == 73)
	{	//m_pEffectSpr[35]->PutTransSprite70(sX+120, sY+120, rand(), dwTime);
		m_pEffectSpr[35]->PutTransSprite70(sX+20, sY-15,  rand()%10, dwTime);
	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}



BOOL   CGame::DrawObject_OnMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int dx, dy;
 int iBodyIndex, iHairIndex, iUndiesIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iHelmIndex, iR, iG, iB;
 int iWeaponIndex, iShieldIndex, iAdd, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponGlare, iShieldGlare;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 66 || _tmp_sOwnerType == 73)	bInv = TRUE; //Energy-Ball, Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}
	iWeaponGlare = (_tmp_sAppr4 & 0x000C) >> 2;
	iShieldGlare = (_tmp_sAppr4 & 0x0003);
	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iAdd = 3;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*3 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 3;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (2 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 2;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 2;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 2;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 2;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 2;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else  iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*2 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 2;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 2;
		}
		break;

	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iAdd = 3;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*3 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 3;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (2 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 2;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 2;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 2;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 2;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 2;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*2 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 2;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 2;
		}
		break;

	default:
		if (_tmp_sOwnerType == 86) iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (1 * 8);
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iBodyArmorIndex = -1;
		iArmArmorIndex  = -1;
		iBootsIndex     = -1;
		iPantsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	dx = 0;
	dy = 0;
	switch (_tmp_cDir) {
	case 1 : dy = 28 - (_tmp_cFrame<<2); break;
	case 2 : dy = 28 - (_tmp_cFrame<<2); dx = (_tmp_cFrame<<2) - 28; break;
	case 3 : dx = (_tmp_cFrame<<2) - 28; break;
	case 4 : dx = (_tmp_cFrame<<2) - 28; dy = (_tmp_cFrame<<2) - 28; break;
	case 5 : dy = (_tmp_cFrame<<2) - 28; break;
	case 6 : dy = (_tmp_cFrame<<2) - 28; dx = 28 - (_tmp_cFrame<<2); break;
	case 7 : dx = 28 - (_tmp_cFrame<<2); break;
	case 8 : dx = 28 - (_tmp_cFrame<<2); dy = 28 - (_tmp_cFrame<<2); break;
	}
	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:

	case 28: // Troll.
	case 29: // Orge.
	case 30: // Liche
	case 31: // DD
	case 32: // Uni
	case 33: // ww

	case 43: // LWB
	case 44: // GHK
	case 45: // GHKABS
	case 46: // TK
	case 47: // BG
	case 48: // SK
	case 49: // HC
	case 50: // TW

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
	case 90: // Gail
		break;

	default:
		_tmp_cFrame = _tmp_cFrame / 2;
		break;
	}
	if (m_bIsCrusadeMode) DrawObjectFOE(sX+dx, sY+dy, _tmp_cFrame);

	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if( _tmp_sOwnerType == 65 ) // IceGolem
	{	/*m_pEffectSpr[77]->PutTransSprite70(sX+dx, sY+dy, _tmp_cFrame, dwTime);*/
		switch( rand()%3 ) {
		case 0:	m_pEffectSpr[76]->PutTransSprite70(sX+dx, sY+dy, _tmp_cFrame, dwTime); break;
		case 1:	m_pEffectSpr[77]->PutTransSprite70(sX+dx, sY+dy, _tmp_cFrame, dwTime); break;
		case 2:	m_pEffectSpr[78]->PutTransSprite70(sX+dx, sY+dy, _tmp_cFrame, dwTime); break;
		}
	}
	if (bTrans == FALSE)
	{	CheckActiveAura(sX+dx, sY+dy, dwTime, _tmp_sOwnerType);
		if (_cDrawingOrder[_tmp_cDir] == 1)
		{	if (iWeaponIndex != -1)
			{	if(bInv) m_pSprite[iWeaponIndex]->PutTransSprite25(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				else
				{	if (iWeaponColor == 0)
						 m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				}
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}
			switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
			case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
						default:
				if (m_cDetailLevel != 0) {
					if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX+dx, sY+dy, 1, dwTime);

			if (_tmp_sOwnerType == 81) // Abaddon
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}else if (bInv == TRUE)
				 //m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite2(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}

			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			}

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iPantsIndex != -1)
			{	if(bInv) m_pSprite[iPantsIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iPantsColor == 0)
						 m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}	}

			if (iArmArmorIndex != -1)
			{	if(bInv) m_pSprite[iArmArmorIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmColor == 0)
						 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}	}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iBodyArmorIndex != -1)
			{	if(bInv) m_pSprite[iBodyArmorIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmorColor == 0)
						 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}	}

			if (iHelmIndex != -1)
			{	if(bInv) m_pSprite[iHelmIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iShieldIndex != -1)
			{	if(bInv) m_pSprite[iShieldIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iShieldColor == 0)
						 m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				}
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13+dx, sY -34+dy, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}
		}else
		{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
			case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX+dx, sY+dy, 1, dwTime);

			if (_tmp_sOwnerType == 81) // Abaddon
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite70(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}else if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}

			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			}

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iPantsIndex != -1)
			{	if(bInv) m_pSprite[iPantsIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iPantsColor == 0)
						 m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}	}

			if (iArmArmorIndex != -1)
			{	if(bInv) m_pSprite[iArmArmorIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmColor == 0)
						 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}	}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iBodyArmorIndex != -1)
			{	if(bInv) m_pSprite[iBodyArmorIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmorColor == 0)
						 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}	}

			if (iHelmIndex != -1)
			{	if(bInv) m_pSprite[iHelmIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iShieldIndex != -1)
			{	if(bInv) m_pSprite[iShieldIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iShieldColor == 0)
						 m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				}
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13+dx, sY -34+dy, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iWeaponIndex != -1)
			{	if(bInv) m_pSprite[iWeaponIndex]->PutTransSprite25(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				else
				{	if (iWeaponColor == 0)
						 m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				}
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
		}	}	}

		// Berserk
		if ((_tmp_iStatus & 0x20) != 0)
			m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, 0, -5, -5, dwTime);
		DrawAngel(40+(_tmp_cDir - 1), sX+dx+20, sY+dy-20, _tmp_cFrame%4, dwTime);
		CheckActiveAura2(sX+dx, sY+dy, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX+dx, sY+dy, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX+dx, sY+dy, _tmp_sOwnerType, _tmp_iStatus);
	}

	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX+dx;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY+dy;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	_tmp_dx = dx;
	_tmp_dy = dy;
	// Snoopy: Abaddon effects
	if (_tmp_sOwnerType == 81)
	{	int randFrame = _tmp_iEffectFrame %12;
		m_pEffectSpr[154]->PutTransSprite70(sX-50	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[155]->PutTransSprite70(sX-20	, sY-80		, randFrame, dwTime);
		m_pEffectSpr[156]->PutTransSprite70(sX+70	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[157]->PutTransSprite70(sX-30	, sY		, randFrame, dwTime);
		m_pEffectSpr[158]->PutTransSprite70(sX-60	, sY+90		, randFrame, dwTime);
		m_pEffectSpr[159]->PutTransSprite70(sX+65	, sY+85		, randFrame, dwTime);
		switch (_tmp_cDir) {
		case 1:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx		, sY+dy+108 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-50	, sY+dy+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 2:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx		, sY+dy+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-70	, sY+dy+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 3:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx		, sY+dy+105 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-90	, sY+dy+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 4:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx-35	, sY+dy+100 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-80	, sY+dy+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 5:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx		, sY+dy+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-65	, sY+dy-5	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 6:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx+45	, sY+dy+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-31	, sY+dy+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 7:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx+40	, sY+dy+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-30	, sY+dy+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 8:
			m_pEffectSpr[153]->PutTransSprite70(sX+dx+20	, sY+dy+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX+dx-20	, sY+dy+16	, _tmp_iEffectFrame %15, dwTime);
			break;
	}	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}

BOOL CGame::DrawObject_OnDamageMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{
 int cFrame, cDir;
 int dx, dy;
 int iBodyIndex, iHairIndex, iUndiesIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iHelmIndex, iR, iG, iB;
 int iWeaponIndex, iShieldIndex, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponGlare, iShieldGlare;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 67 || _tmp_sOwnerType == 68 || _tmp_sOwnerType == 69 || _tmp_sOwnerType == 81) return FALSE;
	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66) bInv = TRUE; //Energy-Ball,Wyvern

	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}
	iWeaponGlare = (_tmp_sAppr4 & 0x000C) >> 2;
	iShieldGlare = (_tmp_sAppr4 & 0x0003);
	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}
	cDir = _tmp_cDir;
	switch (_tmp_cDir) {
	case 1: _tmp_cDir = 5; break;
	case 2: _tmp_cDir = 6; break;
	case 3: _tmp_cDir = 7; break;
	case 4: _tmp_cDir = 8; break;
	case 5: _tmp_cDir = 1; break;
	case 6: _tmp_cDir = 2; break;
	case 7: _tmp_cDir = 3; break;
	case 8: _tmp_cDir = 4; break;
	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (10 * 8);
		iUndiesIndex    = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 10;
		iHairIndex      = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 10;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 10;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 10;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 10;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 10;
		if ((_tmp_sAppr2 & 0x000F) == 0)
			iShieldIndex = -1;
		else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 5;
		if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
			iWeaponIndex = -1;
		else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*5 + (_tmp_cDir - 1);
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 10;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 10;
		break;
	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		iBodyIndex = 500 + (_tmp_sOwnerType - 1 )*8*15 + (10 * 8);
		iUndiesIndex    = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 10;
		iHairIndex      = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 10;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 10;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 10;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 10;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 10;
		if ((_tmp_sAppr2 & 0x000F) == 0)
			iShieldIndex = -1;
		else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 5;
		if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
			iWeaponIndex = -1;
		else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*5 + (_tmp_cDir - 1);
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 10;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 10;
		break;
	default:
		if (_tmp_sOwnerType == 66)      iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else if (_tmp_sOwnerType == 73) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else if (_tmp_sOwnerType == 86) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);
		else if (_tmp_sOwnerType == 87) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);// Ne devrait pas arriver!
		else if (_tmp_sOwnerType == 89) iBodyIndex = DEF_SPRID_MOB +  (_tmp_sOwnerType - 10 )*8*7 + (2 * 8);// Ne devrait pas arriver!
		else iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (3 * 8);
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iArmArmorIndex  = -1;
		iBodyArmorIndex = -1;
		iPantsIndex     = -1;
		iBootsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	dx = 0;
	dy = 0;
	switch (_tmp_cDir) {
	case 1 : dy = 28 - (_tmp_cFrame<<2); break;
	case 2 : dy = 28 - (_tmp_cFrame<<2); dx = (_tmp_cFrame<<2) - 28; break;
	case 3 : dx = (_tmp_cFrame<<2) - 28; break;
	case 4 : dx = (_tmp_cFrame<<2) - 28; dy = (_tmp_cFrame<<2) - 28; break;
	case 5 : dy = (_tmp_cFrame<<2) - 28; break;
	case 6 : dy = (_tmp_cFrame<<2) - 28; dx = 28 - (_tmp_cFrame<<2); break;
	case 7 : dx = 28 - (_tmp_cFrame<<2); break;
	case 8 : dx = 28 - (_tmp_cFrame<<2); dy = 28 - (_tmp_cFrame<<2); break;
	}
	cFrame = _tmp_cFrame;
	if (m_bIsCrusadeMode) DrawObjectFOE(sX+dx, sY+dy, cFrame);
	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX+dy, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

	if (bTrans == FALSE)
	{	CheckActiveAura(sX+dx, sY+dy, dwTime, _tmp_sOwnerType);
		if (_cDrawingOrder[_tmp_cDir] == 1)
		{	if (iWeaponIndex != -1)
			{	if (iWeaponColor == 0)
					m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, cFrame, dwTime);
				else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy,  cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}
			switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
			case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, cFrame, dwTime);
				}
				break;
			}

			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

			if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, cFrame, dwTime);
			else {
				if ((_tmp_iStatus & 0x40) != 0)
					m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
			}

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1)
			{	if (iPantsColor == 0)
					m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1)
			{	if (iArmColor == 0)
					m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1)
			{	if (iArmorColor == 0)
					m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1) {
				if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iShieldIndex != -1)
			{	if (iShieldColor == 0)
					m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13+dx, sY -34+dy, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 4 + cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 4 + cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}
		}else
		{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
			case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

			if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, cFrame, dwTime);
			else {
				if ((_tmp_iStatus & 0x40) != 0)
					m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
			}

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iPantsIndex != -1)
			{	if (iPantsColor == 0)
					m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}

			if (iArmArmorIndex != -1)
			{	if (iArmColor == 0)
					m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0)) {
				if (iBootsColor == 0)
					m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}

			if (iBodyArmorIndex != -1)
			{	if (iArmorColor == 0)
					m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}

			if (iHelmIndex != -1)
			{	if (iHelmColor == 0)
					 m_pSprite[iHelmIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iHelmIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iShieldIndex != -1)
			{	if (iShieldColor == 0)
					m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13+dx, sY -34+dy, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 4 + cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 4 + cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if (iMantleColor == 0)
					m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, dwTime);
				else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 4 + cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}

			if (iWeaponIndex != -1)
			{	if (iWeaponColor == 0)
					m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, cFrame, dwTime);
				else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy, cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
		}	}	}

		if ((_tmp_iStatus & 0x20) != 0) 	// Berserk
			m_pSprite[iBodyIndex + (_tmp_cDir -1)]->PutTransSpriteRGB(sX+dx, sY+dy, cFrame, 0, -5, -5, dwTime);
		DrawAngel(16+(_tmp_cDir - 1), sX+dx+20, sY+dy-20, cFrame%4, dwTime);
		CheckActiveAura2(sX+dx, sY+dy, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX+dx, sY+dy, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX+dx, sY+dy, _tmp_sOwnerType, _tmp_iStatus);
	}
	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID))
		{	m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX+dx;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY+dy;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	_tmp_dx = dx;
	_tmp_dy = dy;
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}

BOOL CGame::DrawObject_OnMove_ForMenu(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{short dx, dy;
 int iBodyIndex, iHairIndex, iUndiesIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iHelmIndex, iR, iG, iB;
 int iWeaponIndex, iShieldIndex, iAdd, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
	iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
	iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
	iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
	iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
	iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
	iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
	iHelmColor   = (_tmp_iApprColor & 0x0000000F);

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iAdd = 3;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else
				{	iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
				}
			}else iBodyArmorIndex = -1;
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;

			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*3 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 3;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (2 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 2;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 2;
			}else iBodyArmorIndex = -1;
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 2;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 2;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 2;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*2 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 2;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 2;
		}
		break;
	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iAdd = 3;
			iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (iAdd * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + iAdd;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + iAdd;
			}else  iBodyArmorIndex = -1;
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + iAdd;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + iAdd;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				 iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*3 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 3;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + iAdd;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + iAdd;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (2 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 2;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 2;
			}else iBodyArmorIndex = -1;
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 2;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 2;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 2;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*2 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 2;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 2;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 2;
		}
		break;
	default:
		iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (1 * 8);
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iBodyArmorIndex = -1;
		iArmArmorIndex  = -1;
		iBootsIndex     = -1;
		iPantsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	dx = 0;
	dy = 0;
	if (_cDrawingOrder[_tmp_cDir] == 1)
	{	if (iWeaponIndex != -1)
		{	if (iWeaponColor == 0)
				 m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy,  _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
		}
		switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
		case 10: // Slime
		case 35: // Energy Sphere
		case 50: // TW
		case 51: // CP
		case 60: // Plant
		case 65: // IceGolem
		case 66: // Wyvern
		case 73: // Fire Wyvern
		case 81: // Abaddon
		case 91: // Gate
			break;
		default:
			if (m_cDetailLevel != 0)
			{	if (sX < 50)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}
			break;
		}
		if (bInv == TRUE)
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
		else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);


		if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
		{	if (iMantleColor == 0)
				 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}
		if (iUndiesIndex != -1)
		{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
		}

		if ((iHairIndex != -1) && (iHelmIndex == -1))
		{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
		}
		if ((iBootsIndex != -1) && (iSkirtDraw == 1))
		{	if (iBootsColor == 0)
				 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}
		if (iPantsIndex != -1)
		{	if (iPantsColor == 0)
				 m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
		}
		if (iArmArmorIndex != -1)
		{	if (iArmColor == 0)
				 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
		}
		if ((iBootsIndex != -1) && (iSkirtDraw == 0))
		{	if (iBootsColor == 0)
				 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}
		if (iBodyArmorIndex != -1)
		{	if (iArmorColor == 0)
				 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
		}
		if (iHelmIndex != -1)
		{	if (iHelmColor == 0)
				 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
		}
		if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
		{	if (iMantleColor == 0)
				 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}

		if (iShieldIndex != -1)
		{	if (iShieldColor == 0)
				 m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
		}
		if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
		{	if (iMantleColor == 0)
				 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}
	}else
	{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
		case 10: // Slime
		case 35: // Energy Sphere
		case 50: // TW
		case 51: // CP
		case 60: // Plant
		case 65: // IceGolem
		case 66: // Wyvern
		case 73: // Fire Wyvern
		case 81: // Abaddon
		case 91: // Gate
			break;
		default:
			if (m_cDetailLevel != 0)
			{	if (sX < 50)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}
			break;
		}

		if (bInv == TRUE)
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
		else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);

		if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
		{	if (iMantleColor == 0)
				 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}
		if (iUndiesIndex != -1) m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);

		if ((iHairIndex != -1) && (iHelmIndex == -1))
		{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
			m_pSprite[iHairIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
		}
		if ((iBootsIndex != -1) && (iSkirtDraw == 1))
		{	if (iBootsColor == 0)
				 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}
		if (iPantsIndex != -1)
		{	if (iPantsColor == 0)
				 m_pSprite[iPantsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iPantsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
		}
		if (iArmArmorIndex != -1)
		{	if (iArmColor == 0)
				 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
		}
		if ((iBootsIndex != -1) && (iSkirtDraw == 0))
		{	if (iBootsColor == 0)
				 m_pSprite[iBootsIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iBootsIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
		}
		if (iBodyArmorIndex != -1)
		{	if (iArmorColor == 0)
				 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
		}
		if (iHelmIndex != -1)
		{	if (iHelmColor == 0)
				 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
		}
		if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
		{	if (iMantleColor == 0)
				 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}

		if (iShieldIndex != -1)
		{	if (iShieldColor == 0)
				 m_pSprite[iShieldIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iShieldIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
		}
		if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
		{	if (iMantleColor == 0)
				 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
		}
		if (iWeaponIndex != -1)
		{	if (iWeaponColor == 0)
				 m_pSprite[iWeaponIndex]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
	}	}

	if (_tmp_iChatIndex != NULL)
	{	if (m_pChatMsgList[_tmp_iChatIndex] != NULL)
		{	DrawChatMsgBox(sX+dx, sY+dy, _tmp_iChatIndex, FALSE);
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	_tmp_dx = dx;
	_tmp_dy = dy;
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}


BOOL   CGame::DrawObject_OnStop(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int iBodyIndex, iUndiesIndex, iHairIndex, iBodyArmorIndex, iArmArmorIndex, iPantsIndex, iBootsIndex, iHelmIndex, iR, iG, iB;
 int iWeaponIndex, iShieldIndex, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponGlare, iShieldGlare;
 int iWeaponColor, iShieldColor, iArmorColor, iMantleColor, iArmColor, iPantsColor, iBootsColor, iHelmColor;
 int iSkirtDraw = 0;

	if(_tmp_sOwnerType == 35 || _tmp_sOwnerType == 73 || _tmp_sOwnerType == 66 || _tmp_sOwnerType == 81) bInv = TRUE; //Energy-Ball, Wyvern
	if (m_cDetailLevel == 0)
	{	iWeaponColor = 0;
		iShieldColor = 0;
		iArmorColor  = 0;
		iMantleColor = 0;
		iArmColor    = 0;
		iPantsColor  = 0;
		iBootsColor  = 0;
		iHelmColor   = 0;
	}else
	{	iWeaponColor = (_tmp_iApprColor & 0xF0000000) >> 28;
		iShieldColor = (_tmp_iApprColor & 0x0F000000) >> 24;
		iArmorColor  = (_tmp_iApprColor & 0x00F00000) >> 20;
		iMantleColor = (_tmp_iApprColor & 0x000F0000) >> 16;
		iArmColor    = (_tmp_iApprColor & 0x0000F000) >> 12;
		iPantsColor  = (_tmp_iApprColor & 0x00000F00) >> 8;
		iBootsColor  = (_tmp_iApprColor & 0x000000F0) >> 4;
		iHelmColor   = (_tmp_iApprColor & 0x0000000F);
	}

	iWeaponGlare = (_tmp_sAppr4 & 0x000C) >> 2;
	iShieldGlare = (_tmp_sAppr4 & 0x0003);
	if ( (_tmp_iStatus & 0x10) != 0)
	{	if (memcmp(m_cPlayerName, _tmp_cName, 10) == 0) bInv = TRUE;
		else if( _iGetFOE(_tmp_iStatus) == 1 ) bInv = TRUE;
		else return FALSE;
	}

	// CLEROTH - Single-direction monsters
	switch(_tmp_sOwnerType){
	case 110: // Air Elemental
		_tmp_cDir = 1; // North
		break;
	case 91: // Snoopy: Gate
		if (_tmp_cDir <= 3) _tmp_cDir = 3;
		else  _tmp_cDir = 5;
		break;
	}

	switch (_tmp_sOwnerType) {
	case 1:
	case 2:
	case 3:
		_tmp_cFrame = _tmp_cFrame / 2;
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (1 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 1;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 1;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 1;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 1;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 1;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 1;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*1 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 1;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 1;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 1;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (0 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15;
			iHairIndex	 = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*0 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 0;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 0;
		}
		break;

	case 4:
	case 5:
	case 6:
		_tmp_cFrame = _tmp_cFrame / 2;
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		if ((_tmp_sAppr2 & 0xF000) != 0)
		{	iBodyIndex   = 500 + (_tmp_sOwnerType - 1 )*8*15 + (1 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 1;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 1;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 1;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 1;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 1;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 1;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*1 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 1;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 1;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 1;
		}else
		{	iBodyIndex   = 500  + (_tmp_sOwnerType - 1 )*8*15 + (0 * 8);
			iUndiesIndex = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15;
			iHairIndex	 = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15;
			if ((_tmp_sAppr4 & 0x80) == 0)
			{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
					 iBodyArmorIndex = -1;
				else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15;
			}
			if ((_tmp_sAppr3 & 0x000F) == 0)
				 iArmArmorIndex = -1;
			else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15;
			if ((_tmp_sAppr3 & 0x0F00) == 0)
				 iPantsIndex = -1;
			else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15;
			if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
				 iBootsIndex = -1;
			else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15;
			if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
				iWeaponIndex = -1;
			else iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*0 + (_tmp_cDir - 1);
			if ((_tmp_sAppr2 & 0x000F) == 0)
				iShieldIndex = -1;
			else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 0;
			if ((_tmp_sAppr4 & 0x0F00) == 0)
				 iMantleIndex = -1;
			else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15;
			if ((_tmp_sAppr3 & 0x00F0) == 0)
				 iHelmIndex = -1;
			else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 0;
		}
		break;
	default:
		if (_tmp_sAppr2 != 0)
		{	 iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (4 * 8);
			 _tmp_cFrame = (_tmp_sAppr2 & 0x00FF ) -1;
		}
	/*	else if (_tmp_sOwnerType == 66) iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else if (_tmp_sOwnerType == 73) iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		else if (_tmp_sOwnerType == 81) iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);*/
		else iBodyIndex =  DEF_SPRID_MOB  +  (_tmp_sOwnerType - 10 )*8*7 + (0 * 8);
		iUndiesIndex    = -1;
		iHairIndex      = -1;
		iBodyArmorIndex = -1;
		iArmArmorIndex  = -1;
		iBootsIndex     = -1;
		iPantsIndex     = -1;
		iWeaponIndex    = -1;
		iShieldIndex    = -1;
		iMantleIndex    = -1;
		iHelmIndex      = -1;
		break;
	}
	if (m_bIsCrusadeMode) DrawObjectFOE(sX, sY, _tmp_cFrame);
	switch (_tmp_sOwnerType) { // hum? la lumiere en dessous ?
	case 15: // ShopKeeper
	case 19: // Gandalf
	case 20: // Howard
	case 24: // Tom
	case 25: // William
	case 26: // Kenedy
	case 51: // CP
	case 86: // HBT
	case 90: // Gail
		m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);
		break;
	}
	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX, sY, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}
	if (bTrans == FALSE)
	{	CheckActiveAura(sX, sY, dwTime, _tmp_sOwnerType);
		if (_cDrawingOrder[_tmp_cDir] == 1)
		{	if (iWeaponIndex != -1)
			{	if(bInv) m_pSprite[iWeaponIndex]->PutTransSprite25(sX, sY, _tmp_cFrame, dwTime);
				else
				{	if (iWeaponColor == 0)
						 m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY,  _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				}
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
			case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);

			if (_tmp_sOwnerType == 81) // Abaddon
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);

			}else if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
			}

			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0)) {
				if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			}

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iPantsIndex != -1)
			{	if(bInv) m_pSprite[iPantsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iPantsColor == 0)
						 m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}	}

			if (iArmArmorIndex != -1)
			{	if(bInv) m_pSprite[iArmArmorIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmColor == 0)
						 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}	}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iBodyArmorIndex != -1)
			{	if(bInv) m_pSprite[iBodyArmorIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmorColor == 0)
						 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}	}

			if (iHelmIndex != -1)
			{	if(bInv) m_pSprite[iHelmIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iShieldIndex != -1)
			{	if(bInv) m_pSprite[iShieldIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iShieldColor == 0)
						 m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				}
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}
		}else
		{	switch (_tmp_sOwnerType) { // Pas d'ombre pour ces mobs
			case 10: // Slime
			case 35: // Energy Sphere
			case 50: // TW
			case 51: // CP
			case 60: // Plant
			case 65: // IceGolem
			case 66: // Wyvern
			case 73: // Fire Wyvern
			case 81: // Abaddon
			case 91: // Gate
				break;
			default:
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX, sY, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX, sY, _tmp_cFrame, dwTime);
				}
				break;
			}
			if (_tmp_sOwnerType == 35)
				m_pEffectSpr[0]->PutTransSprite(sX, sY, 1, dwTime);
			if (_tmp_sOwnerType == 81) // Abaddon
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			}else if (bInv == TRUE)
			{	m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX, sY, _tmp_cFrame, dwTime);
			}else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 0))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else m_pSprite[iUndiesIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
			}

			if ((iHairIndex != -1) && (iHelmIndex == -1))
			{	_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
				m_pSprite[iHairIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, iR, iG, iB, dwTime);
			}

			if ((iBootsIndex != -1) && (iSkirtDraw == 1))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iPantsIndex != -1)
			{	if(bInv) m_pSprite[iPantsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iPantsColor == 0)
						 m_pSprite[iPantsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iPantsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iPantsColor] -m_wR[0], m_wG[iPantsColor] -m_wG[0], m_wB[iPantsColor] -m_wB[0], dwTime);
			}	}

			if (iArmArmorIndex != -1)
			{	if(bInv) m_pSprite[iArmArmorIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmColor == 0)
						 m_pSprite[iArmArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iArmArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmColor] -m_wR[0], m_wG[iArmColor] -m_wG[0], m_wB[iArmColor] -m_wB[0], dwTime);
			}	}

			if ((iBootsIndex != -1) && (iSkirtDraw == 0))
			{	if(bInv) m_pSprite[iBootsIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iBootsColor == 0)
						 m_pSprite[iBootsIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBootsIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iBootsColor] -m_wR[0], m_wG[iBootsColor] -m_wG[0], m_wB[iBootsColor] -m_wB[0], dwTime);
			}	}

			if (iBodyArmorIndex != -1)
			{	if(bInv) m_pSprite[iBodyArmorIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iArmorColor == 0)
						 m_pSprite[iBodyArmorIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iBodyArmorIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iArmorColor] -m_wR[0], m_wG[iArmorColor] -m_wG[0], m_wB[iArmorColor] -m_wB[0], dwTime);
			}	}

			if (iHelmIndex != -1)
			{	if(bInv) m_pSprite[iHelmIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iHelmColor == 0)
						 m_pSprite[iHelmIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iHelmIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iHelmColor] -m_wR[0], m_wG[iHelmColor] -m_wG[0], m_wB[iHelmColor] -m_wB[0], dwTime);
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 2))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iShieldIndex != -1)
			{	if(bInv) m_pSprite[iShieldIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iShieldColor == 0)
						 m_pSprite[iShieldIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iShieldIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iShieldColor] -m_wR[0], m_wG[iShieldColor] -m_wG[0], m_wB[iShieldColor] -m_wB[0], dwTime);
				}
				switch (iShieldGlare) {
				case 0: break;
				//case 1: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13, sY -34, 0, dwTime);
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX, sY,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrder[_tmp_cDir] == 1))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX, sY, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iWeaponIndex != -1)
			{	if(bInv) m_pSprite[iWeaponIndex]->PutTransSprite25(sX, sY, _tmp_cFrame, dwTime);
				else
				{	if (iWeaponColor == 0)
						 m_pSprite[iWeaponIndex]->PutSpriteFast(sX, sY, _tmp_cFrame, dwTime);
					else m_pSprite[iWeaponIndex]->PutSpriteRGB(sX, sY, _tmp_cFrame, m_wWR[iWeaponColor] -m_wR[0], m_wWG[iWeaponColor] -m_wG[0], m_wWB[iWeaponColor] -m_wB[0], dwTime);
				}
				DKGlare(iWeaponColor, iWeaponIndex, &iWeaponGlare);
				switch (iWeaponGlare) {
				case 0: break;
				case 1: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, m_iDrawFlag, 0, 0, dwTime); break; // Red Glare
				case 2: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iWeaponIndex]->PutTransSpriteRGB(sX, sY,  _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
		}	}	}
		if (_tmp_sOwnerType == 64) // crop
		{	switch( _tmp_cFrame ) {
			case 0: // color effect for crop
				m_pEffectSpr[84]->PutTransSprite(sX+52, sY+54, (dwTime%3000)/120, dwTime );
				break;
			case 1: // color effect for crop
				m_pEffectSpr[83]->PutTransSprite(sX+53, sY+59, (dwTime%3000)/120, dwTime );
				break;
			case 2: // color effect for crop
				m_pEffectSpr[82]->PutTransSprite(sX+53, sY+65, (dwTime%3000)/120, dwTime );
				break;
		}	}
		// Berserk
		if ((_tmp_iStatus & 0x20) != 0)
			m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSpriteRGB(sX, sY, _tmp_cFrame, 0, -5, -5, dwTime);
		DrawAngel(40+(_tmp_cDir - 1), sX+20, sY-20, _tmp_cFrame%4, dwTime);
		CheckActiveAura2(sX, sY, dwTime,  _tmp_sOwnerType);

	}else if( strlen(_tmp_cName) > 0 )
	{	if( (_tmp_sOwnerType>=1) && (_tmp_sOwnerType<=6) ) DrawObjectName(sX, sY, _tmp_cName, _tmp_iStatus);
		else DrawNpcName(sX, sY, _tmp_sOwnerType, _tmp_iStatus);
	}

	if (_tmp_iChatIndex != NULL)
	{	if ((m_pChatMsgList[_tmp_iChatIndex] != NULL) && (m_pChatMsgList[_tmp_iChatIndex]->m_iObjectID == _tmp_wObjectID)) {
			m_pChatMsgList[_tmp_iChatIndex]->m_sX = sX;
			m_pChatMsgList[_tmp_iChatIndex]->m_sY = sY;
		}else
		{	m_pMapData->ClearChatMsg(indexX, indexY);
	}	}
	// Snoopy: Abaddon effects
	if (_tmp_sOwnerType == 81)
	{	int randFrame = _tmp_cFrame % 12;
		m_pEffectSpr[154]->PutTransSprite70(sX-50	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[155]->PutTransSprite70(sX-20	, sY-80		, randFrame, dwTime);
		m_pEffectSpr[156]->PutTransSprite70(sX+70	, sY-50		, randFrame, dwTime);
		m_pEffectSpr[157]->PutTransSprite70(sX-30	, sY		, randFrame, dwTime);
		m_pEffectSpr[158]->PutTransSprite70(sX-60	, sY+90		, randFrame, dwTime);
		m_pEffectSpr[159]->PutTransSprite70(sX+65	, sY+85		, randFrame, dwTime);
		switch (_tmp_cDir) {
		case 1:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+108 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-50	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 2:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-70	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 3:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+105 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-90	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 4:
			m_pEffectSpr[153]->PutTransSprite70(sX-35	, sY+100 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-80	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 5:
			m_pEffectSpr[153]->PutTransSprite70(sX		, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-65	, sY-5	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 6:
			m_pEffectSpr[153]->PutTransSprite70(sX+45	, sY+95	, _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-31	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 7:
			m_pEffectSpr[153]->PutTransSprite70(sX+40	, sY+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-30	, sY+10	, _tmp_iEffectFrame %15, dwTime);
			break;
		case 8:
			m_pEffectSpr[153]->PutTransSprite70(sX+20	, sY+110 , _tmp_iEffectFrame %28, dwTime);
			m_pEffectSpr[164]->PutTransSprite70(sX-20	, sY+16	, _tmp_iEffectFrame %15, dwTime);
			break;
	}	}
	if ( (m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top != -1) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top < msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom > msY) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left < msX) &&
		 (m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right > msX) ) return TRUE;
	return FALSE;
}

void CGame::_ReadMapData(short sPivotX, short sPivotY, char * pData)
{int i;
 char  * cp, ucHeader, cDir, cName[12], cItemColor;
 short * sp, sTotal, sX, sY, sType, sAppr1, sAppr2, sAppr3, sAppr4, sItemSpr, sItemSprFrame, sDynamicObjectType;
 int iStatus;
 int   * ip, iApprColor;
 WORD    wObjectID;
 WORD  * wp, wDynamicObjectID;
	cp = pData;
	m_sVDL_X = sPivotX; // Valid Data Loc-X
	m_sVDL_Y = sPivotY;
	sp = (short *)cp;
	sTotal = *sp;
	cp += 2;
	for (i = 1;	i <= sTotal; i++)
	{	sp = (short *)cp;
		sX = *sp;
		cp += 2;
		sp = (short *)cp;
		sY = *sp;
		cp += 2;
		ucHeader = *cp;
		cp++;
		if (ucHeader & 0x01) // object ID
		{	wp  = (WORD *)cp;
			wObjectID = *wp;
			cp += 2;
			sp  = (short *)cp;
			sType = *sp;// object type
			cp += 2;
			// dir
			cDir = *cp;
			cp++;
			if (wObjectID < 10000)
			{	sp  = (short *)cp;
				sAppr1 = *sp;// Appearance1
				cp += 2;
				sp  = (short *)cp;
				sAppr2 = *sp;// Appearance2
				cp += 2;
				sp  = (short *)cp;
				sAppr3 = *sp;// Appearance3
				cp += 2;
				sp  = (short *)cp;
				sAppr4 = *sp;// Appearance4
				cp += 2;
				ip = (int *)cp;
				iApprColor = *ip;// v1.4 ApprColor
				cp += 4;
				// CLEROTH - CRASH BUG ( STATUS )
				// Status
				ip  = (int *)cp;
				iStatus = *ip;
				cp += 4;
				// Name
				ZeroMemory(cName, sizeof(cName));
				memcpy(cName, cp, 10);
				cp    += 10;
			}else // NPC
			{	sAppr1 = sAppr3 = sAppr4 = 0;
				sp  = (short *)cp;
				sAppr2 = *sp;// Appearance2
				cp += 2;
				// CLEROTH - CRASH BUG ( STATUS )
				// Status
				ip  = (int *)cp;
				iStatus = *ip;
				cp += 4;
				// Name
				ZeroMemory(cName, sizeof(cName));
				memcpy(cName, cp, 5);
				cp    += 5;
			}
			m_pMapData->bSetOwner(wObjectID, sPivotX + sX, sPivotY + sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, DEF_OBJECTSTOP, NULL, NULL, NULL);
		}
		if (ucHeader & 0x02) // object ID
		{	wp  = (WORD *)cp;
			wObjectID = *wp;
			cp += 2;
			sp  = (short *)cp;
			sType = *sp;	// object type
			cp += 2;
			cDir = *cp;	// dir
			cp++;
			if (wObjectID < 10000)
			{	sp  = (short *)cp;
				sAppr1 = *sp;// Appearance1
				cp += 2;
				sp  = (short *)cp;
				sAppr2 = *sp;// Appearance2
				cp += 2;
				sp  = (short *)cp;
				sAppr3 = *sp;// Appearance3
				cp += 2;
				sp  = (short *)cp;
				sAppr4 = *sp;// Appearance4
				cp += 2;
				ip = (int *)cp;
				iApprColor = *ip;// v1.4 ApprColor
				cp += 4;
				// CLEROTH - CRASH BUG ( STATUS )
				// Status
				ip  = (int *)cp;
				iStatus = *ip;
				cp += 4;
				// Name
				ZeroMemory(cName, sizeof(cName));
				memcpy(cName, cp, 10);
				cp    += 10;
			}else 	// NPC
			{	sAppr1 = sAppr3 = sAppr4 = 0;
				sp  = (short *)cp;
				sAppr2 = *sp;// Appearance2
				cp += 2;
				ip  = (int *)cp;
				iStatus = *ip;// Status
				cp += 4;
				ZeroMemory(cName, sizeof(cName));	// Name
				memcpy(cName, cp, 5);
				cp    += 5;
			}
			m_pMapData->bSetDeadOwner(wObjectID, sPivotX + sX, sPivotY + sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName);
		}
		if (ucHeader & 0x04)
		{	sp  = (short *)cp;
			sItemSpr = *sp;
			cp += 2;
			sp  = (short *)cp;
			sItemSprFrame = *sp;
			cp += 2;
			cItemColor = *cp;
			cp++;
			m_pMapData->bSetItem(sPivotX + sX, sPivotY + sY, sItemSpr, sItemSprFrame, cItemColor, FALSE);
		}
		if (ucHeader & 0x08) // Dynamic object
		{	wp = (WORD *)cp;
			wDynamicObjectID = *wp;
			cp += 2;
			sp  = (short *)cp;
			sDynamicObjectType = *sp;
			cp += 2;
			m_pMapData->bSetDynamicObject(sPivotX + sX, sPivotY + sY, wDynamicObjectID, sDynamicObjectType, FALSE);
	}	}
}

void CGame::LogEventHandler(char * pData)
{WORD * wp, wEventType, wObjectID;
 short * sp, sX, sY, sType, sAppr1, sAppr2, sAppr3, sAppr4;
 int iStatus;
 char  * cp, cDir, cName[12];
 int   * ip, iApprColor;
	wp   = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wEventType = *wp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp  = (WORD *)cp;
	wObjectID  = *wp;
	cp += 2;
	sp  = (short *)cp;
	sX  = *sp;
	cp += 2;
	sp  = (short *)cp;
	sY  = *sp;
	cp += 2;
	sp  = (short *)cp;
	sType = *sp;
	cp += 2;
	cDir = *cp;
	cp++;
	ZeroMemory(cName, sizeof(cName));
	if (wObjectID < 10000)
	{	memcpy(cName, cp, 10);
		cp += 10;
		sp  = (short *)cp;
		sAppr1 = *sp;
		cp += 2;
		sp  = (short *)cp;
		sAppr2 = *sp;
		cp += 2;
		sp  = (short *)cp;
		sAppr3 = *sp;
		cp += 2;
		sp  = (short *)cp;
		sAppr4 = *sp;
		cp += 2;
		ip = (int *)cp;
		iApprColor = *ip;
		cp += 4;
		// CLEROTH - CRASH BUG ( STATUS )
		ip  = (int *)cp;
		iStatus = *ip;
		cp += 4;
	}else 	// NPC
	{	memcpy(cName, cp, 5);
		cp += 5;
		sAppr1 = sAppr3 = sAppr4 = 0;
		sp  = (short *)cp;
		sAppr2 = *sp;
		cp += 2;
		ip  = (int *)cp;
		iStatus = *ip;
		cp += 4;
	}

	switch (wEventType) {
	case DEF_MSGTYPE_CONFIRM:
		m_pMapData->bSetOwner(wObjectID, sX, sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, DEF_OBJECTSTOP, NULL, NULL, NULL);
		switch (sType) {
		case 43: // LWB
		case 44: // GHK
		case 45: // GHKABS
		case 46: // TK
		case 47: // BG
			bAddNewEffect(64, (sX)*32 ,(sY)*32, NULL, NULL, 0);
			break;
		}
		break;

	case DEF_MSGTYPE_REJECT:
		m_pMapData->bSetOwner(wObjectID, -1, -1, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, DEF_OBJECTSTOP, NULL, NULL, NULL);
		break;
	}

	_RemoveChatMsgListByObjectID(wObjectID);
}

void CGame::OnLogSocketEvent(WPARAM wParam, LPARAM lParam)
{int iRet;
 char * pData;
 DWORD  dwMsgSize;
	if (m_pLSock == NULL) return;

	iRet = m_pLSock->iOnSocketEvent(wParam, lParam);
	switch (iRet) {
	case DEF_XSOCKEVENT_CONNECTIONESTABLISH:
		ConnectionEstablishHandler(DEF_SERVERTYPE_LOG);
		break;

	case DEF_XSOCKEVENT_READCOMPLETE:
		pData = m_pLSock->pGetRcvDataPointer(&dwMsgSize);
		LogRecvMsgHandler(pData);
		m_dwTime = G_dwGlobalTime;
		break;

	case DEF_XSOCKEVENT_SOCKETCLOSED:
		ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
		delete m_pLSock;
		m_pLSock = NULL;
		break;

	case DEF_XSOCKEVENT_SOCKETERROR:
		ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
		delete m_pLSock;
		m_pLSock = NULL;
		break;

	case DEF_XSOCKEVENT_CRITICALERROR:
		delete m_pLSock;
		m_pLSock = NULL;
		break;
	}
}

void CGame::LogResponseHandler(char * pData)
{
 WORD  * wp, wResponse;
 WORD wServerUpperVersion, wServerLowerVersion;
 DWORD * dwp;
 char  * cp, cCharName[12];
 int   * ip, i;

	dwp = (DWORD *)(pData);
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wResponse = *wp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	switch (wResponse) {
	case DEF_LOGRESMSGTYPE_CHARACTERDELETED:
		cp = (pData + DEF_INDEX2_MSGTYPE + 2);
		//m_iAccountStatus = (int)*cp;
		cp++;
		m_iTotalChar = (int)*cp;
		cp++;
		for (i = 0; i < 4; i++)
		if (m_pCharList[i] != NULL)
		{	delete m_pCharList[i];
			m_pCharList[i] = NULL;
		}

		for (i = 0; i < m_iTotalChar; i++) {
			m_pCharList[i] = new class CCharInfo;
			memcpy(m_pCharList[i]->m_cName, cp, 10);
			cp += 10;
			if (*cp == 0)
			{	m_pCharList[i]->m_sSex = NULL; // Sex
				cp += 40;
			}else
			{	cp++;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr1 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr2 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr3 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr4 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sSex = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sSkinCol = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sLevel = *wp;
				cp += 2;
				dwp = (DWORD *)cp;
				m_pCharList[i]->m_iExp = *dwp;
				cp += 4;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sStr = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sVit = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sDex = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sInt = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sMag = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sChr = *wp;
				cp += 2;
				ip = (int *)cp; // v1.4
				m_pCharList[i]->m_iApprColor = *ip;
				cp += 4;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iYear = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iMonth = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iDay = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iHour = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iMinute = (int)*wp;
				cp += 2;
				ZeroMemory(m_pCharList[i]->m_cMapName, sizeof(m_pCharList[i]->m_cMapName));
				memcpy(m_pCharList[i]->m_cMapName, cp, 10);
				cp += 10;
		}	}
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "3A");
		break;

	case DEF_LOGRESMSGTYPE_CONFIRM:
		cp = (pData + DEF_INDEX2_MSGTYPE + 2);
		wp = (WORD *)cp;
		wServerUpperVersion = *wp;
		cp += 2;
		wp = (WORD *)cp;
		wServerLowerVersion = *wp;
		cp += 2;
//		m_iAccountStatus = (int)*cp;
		cp++;
		wp = (WORD *)cp;
		m_iAccntYear = *wp;
		cp += 2;
		wp = (WORD *)cp;
		m_iAccntMonth = *wp;
		cp += 2;
		wp = (WORD *)cp;
		m_iAccntDay = *wp;
		cp += 2;
		wp = (WORD *)cp;
		m_iIpYear = *wp;
		cp += 2;
		wp = (WORD *)cp;
		m_iIpMonth = *wp;
		cp += 2;
		wp = (WORD *)cp;
		m_iIpDay = *wp;
		cp += 2;
		m_iTotalChar = (int)*cp;
		cp++;
		for (i = 0; i < 4; i++)
		if (m_pCharList[i] != NULL)
		{	delete m_pCharList[i];
			m_pCharList[i] = NULL;
		}

		for (i = 0; i < m_iTotalChar; i++)
		{	m_pCharList[i] = new class CCharInfo;
			memcpy(m_pCharList[i]->m_cName, cp, 10);
			cp += 10;
			if (*cp == 0)
			{	m_pCharList[i]->m_sSex = NULL;
				cp += 40;
			}else
			{	cp++;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr1 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr2 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr3 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr4 = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sSex = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sSkinCol = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sLevel = *wp;
				cp += 2;
				dwp = (DWORD *)cp;
				m_pCharList[i]->m_iExp = *dwp;
				cp += 4;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sStr = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sVit = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sDex = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sInt = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sMag = *wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_sChr = *wp;
				cp += 2;
				ip = (int *)cp;
				m_pCharList[i]->m_iApprColor = *ip; // v1.4
				cp += 4;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iYear = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iMonth = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iDay = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iHour = (int)*wp;
				cp += 2;
				wp = (WORD *)cp;
				m_pCharList[i]->m_iMinute = (int)*wp;
				cp += 2;
				ZeroMemory(m_pCharList[i]->m_cMapName, sizeof(m_pCharList[i]->m_cMapName));
				memcpy(m_pCharList[i]->m_cMapName, cp, 10);
				cp += 10;
		}	}
		ip = (int *)cp;
		m_iTimeLeftSecAccount = *ip;
		cp += 4;
		ip = (int *)cp;
		m_iTimeLeftSecIP = *ip;
		cp += 4;
		ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
		ClearContents_OnSelectCharacter();

#ifndef _DEBUG
		if ( (wServerUpperVersion!=DEF_UPPERVERSION) || (wServerLowerVersion!=DEF_LOWERVERSION) )
			ChangeGameMode(DEF_GAMEMODE_ONVERSIONNOTMATCH);
#endif
		break;

	case DEF_LOGRESMSGTYPE_REJECT:
		cp = (pData + DEF_INDEX2_MSGTYPE + 2);
		ip = (int *)cp;
		m_iBlockYear = *ip;
		cp += 4;

		ip = (int *)cp;
		m_iBlockMonth = *ip;
		cp += 4;

		ip = (int *)cp;
		m_iBlockDay = *ip;
		cp += 4;

		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "7H");
		break;

	case DEF_LOGRESMSGTYPE_NOTENOUGHPOINT:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "7I");
		break;

	case DEF_LOGRESMSGTYPE_ACCOUNTLOCKED:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "7K");
		break;

	case DEF_LOGRESMSGTYPE_SERVICENOTAVAILABLE:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "7L");
		break;

	case DEF_LOGRESMSGTYPE_PASSWORDCHANGESUCCESS:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "6B");
		break;

	case DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "6C");
		break;

	case DEF_LOGRESMSGTYPE_PASSWORDMISMATCH:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "11");
		break;

	case DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "12");
		break;

	case DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "54");
		break;

	case DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "05");
		break;

	case DEF_LOGRESMSGTYPE_ALREADYEXISTINGACCOUNT:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "06");
		break;

	case DEF_LOGRESMSGTYPE_NOTEXISTINGCHARACTER:
		ChangeGameMode(DEF_GAMEMODE_ONMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "Not existing character!");
		break;

	case DEF_LOGRESMSGTYPE_NEWCHARACTERCREATED:
		ZeroMemory(cCharName, sizeof(cCharName));
		memcpy(cCharName, cp, 10);
		cp += 10;

		m_iTotalChar = (int)*cp;
		cp++;

		for (i = 0; i < 4; i++)
		if (m_pCharList[i] != NULL) delete m_pCharList[i];
		//
		for (i = 0; i < m_iTotalChar; i++) {
			m_pCharList[i] = new class CCharInfo;
			memcpy(m_pCharList[i]->m_cName, cp, 10);
			cp += 10;
			if (*cp == 0) {
				m_pCharList[i]->m_sSex = NULL; // Sex
				cp += 40;
			}
			else {
				cp++;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr1 = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr2 = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr3 = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sAppr4 = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sSex = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sSkinCol = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sLevel = *wp;
				cp += 2;

				dwp = (DWORD *)cp;
				m_pCharList[i]->m_iExp = *dwp;
				cp += 4;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sStr = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sVit = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sDex = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sInt = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sMag = *wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_sChr = *wp;
				cp += 2;

				ip = (int *)cp; // v1.4
				m_pCharList[i]->m_iApprColor = *ip;
				cp += 4;

				wp = (WORD *)cp;
				m_pCharList[i]->m_iYear = (int)*wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_iMonth = (int)*wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_iDay = (int)*wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_iHour = (int)*wp;
				cp += 2;

				wp = (WORD *)cp;
				m_pCharList[i]->m_iMinute = (int)*wp;
				cp += 2;

				ZeroMemory(m_pCharList[i]->m_cMapName, sizeof(m_pCharList[i]->m_cMapName));
				memcpy(m_pCharList[i]->m_cMapName, cp, 10);
				cp += 10;
			}
		}
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "47");
		break;

	case DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "28");
		break;

	case DEF_LOGRESMSGTYPE_ALREADYEXISTINGCHARACTER:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "29");
		break;

	case DEF_ENTERGAMERESTYPE_PLAYING:
		ChangeGameMode(DEF_GAMEMODE_ONQUERYFORCELOGIN);
		break;

	case DEF_ENTERGAMERESTYPE_CONFIRM:
		{	int iGameServerPort;
			char cGameServerAddr[16];
			ZeroMemory(cGameServerAddr, sizeof(cGameServerAddr));
			cp = (pData + DEF_INDEX2_MSGTYPE + 2);
			memcpy(cGameServerAddr, cp, 16);
			cp += 16;
			wp = (WORD *)cp;
			iGameServerPort = *wp;
			cp += 2;
			ZeroMemory(m_cGameServerName, sizeof(m_cGameServerName));
			memcpy(m_cGameServerName, cp, 20);
			cp += 20;
			m_pGSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
			if (m_iGameServerMode == 1)
			{	m_pGSock->bConnect(m_cLogServerAddr, iGameServerPort, WM_USER_GAMESOCKETEVENT);
			}else
			{	m_pGSock->bConnect(cGameServerAddr, iGameServerPort, WM_USER_GAMESOCKETEVENT);
			}
			m_pGSock->bInitBufferSize(30000);
		}
		break;

	case DEF_ENTERGAMERESTYPE_REJECT:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		switch (*cp) {
		case 1:	strcpy(m_cMsg, "3E"); break;
		case 2:	strcpy(m_cMsg, "3F"); break;
		case 3:	strcpy(m_cMsg, "33"); break;
		case 4: strcpy(m_cMsg, "3D"); break;
		case 5: strcpy(m_cMsg, "3G"); break;
		case 6: strcpy(m_cMsg, "3Z"); break;
		case 7: strcpy(m_cMsg, "3J"); break;
		}
		break;

	case DEF_ENTERGAMERESTYPE_FORCEDISCONN:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "3X");
		break;

	case DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "1Y");
		break;

	case DEF_LOGRESMSGTYPE_INPUTKEYCODE:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		switch (*cp) {
		case 1:	strcpy(m_cMsg, "8U"); break; //MainMenu, Keycode registration success
		case 2:	strcpy(m_cMsg, "82"); break; //MainMenu, Not existing Account
		case 3:	strcpy(m_cMsg, "81"); break; //MainMenu, Password wrong
		case 4: strcpy(m_cMsg, "8V"); break; //MainMenu, Invalid Keycode
		case 5: strcpy(m_cMsg, "8W"); break; //MainMenu, Already Used Keycode
		}
		break;


	case DEF_LOGRESMSGTYPE_FORCECHANGEPASSWORD:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "6M");
		break;

	case DEF_LOGRESMSGTYPE_INVALIDKOREANSSN:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "1a");
		break;

	case DEF_LOGRESMSGTYPE_LESSTHENFIFTEEN:
		ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
		ZeroMemory(m_cMsg, sizeof(m_cMsg));
		strcpy(m_cMsg, "1b");
		break;

	}
	delete m_pLSock;
	m_pLSock = NULL;
}

void CGame::LogRecvMsgHandler(char * pData)
{
	LogResponseHandler(pData);
}

void CGame::UpdateScreen_OnMsg()
{short msX, msY, msZ;
 char cLB, cRB;
 DWORD dwTime = G_dwGlobalTime;
	m_DDraw.ClearBackB4();
	PutString(10, 10, m_cMsg, RGB(255,155,155), FALSE, 1);
	DrawVersion();
	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
	if ((G_dwGlobalTime - m_dwTime) > 1500)
	{	ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
	}
}

void CGame::_InitOnCreateNewCharacter()
{	m_cGender    = rand() % 2 + 1;
	m_cSkinCol   = rand() % 3 + 1;
	m_cHairStyle = rand() % 8;
	m_cHairCol   = rand() % 16;
	m_cUnderCol  = rand() % 8;
	m_ccStr = 10;
	m_ccVit = 10;
	m_ccDex = 10;
	m_ccInt = 10;
	m_ccMag = 10;
	m_ccChr = 10;
}

void CGame::ClearContents_OnCreateNewAccount()
{
	ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
	ZeroMemory(m_cAccountAge, sizeof(m_cAccountAge));
	ZeroMemory(m_cAccountCountry, sizeof(m_cAccountCountry));
	ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
	ZeroMemory(m_cEmailAddr, sizeof(m_cEmailAddr));
	//v1.4334
	ZeroMemory(m_cAccountQuiz, sizeof(m_cAccountQuiz));
	ZeroMemory(m_cAccountAnswer, sizeof(m_cAccountAnswer));
}

void CGame::ChangeGameMode(char cMode)
{
	m_cGameMode = cMode;
	m_cGameModeCount = 0;
	m_dwTime = G_dwGlobalTime;

#ifndef DEF_SELECTSERVER
	if( cMode == DEF_GAMEMODE_ONSELECTSERVER )
	{	ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
		strcpy(m_cWorldServerName, NAME_WORLDNAME1);
		m_cGameMode = DEF_GAMEMODE_ONLOGIN;
	}
#endif
}

BOOL CGame::bReadIp()
{	ZeroMemory(m_cLogServerAddr, sizeof(m_cLogServerAddr));
	strcpy(m_cLogServerAddr, DEF_SERVER_IP);
	m_iLogServerPort = DEF_SERVER_PORT;
	return TRUE;
}

BOOL CGame::bReadLoginConfigFile(char * cFn)
{FILE * pFile;
 HANDLE hFile;
 DWORD  dwFileSize;
 char * cp, * token, cReadMode;
 char seps[] = "= ,\t\n";
 	cReadMode = 0;
	// Get file size only
	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
	pFile = fopen(cFn, "rt");
	if (pFile == NULL) goto DEFAULT_IP;
	cp = new char[dwFileSize+2];
	ZeroMemory(cp, dwFileSize+2);
	fread(cp, dwFileSize, 1, pFile);
	token = strtok( cp, seps );
	while( token != NULL )
	{	if (cReadMode != 0)
		{	switch (cReadMode) {
			case 1: // log-server-address
				if (strlen(token) > 15)
				{	delete[] cp;
					if (pFile != NULL) fclose(pFile);
					goto DEFAULT_IP;
				}
				ZeroMemory(m_cLogServerAddr, sizeof(m_cLogServerAddr));
				strcpy(m_cLogServerAddr, token);
				cReadMode = 0;
				break;
			case 2: // log-server-port
				m_iLogServerPort = atoi(token);
				if (m_iLogServerPort == 0)
				{	delete[] cp;
					if (pFile != NULL) fclose(pFile);
					goto DEFAULT_IP;
				}
				cReadMode = 0;
				break;
			case 3: // game-server-mode
				if ((memcmp(token, "lan", 3) == 0) || (memcmp(token, "LAN", 3) == 0))
				{	m_iGameServerMode = 1;  // Will no connect multi-hoster HB
											// but will connect from LAN even with bad router
				}
				if ((memcmp(token, "internet", 8) == 0) || (memcmp(token, "INTERNET", 8) == 0))
				{	m_iGameServerMode = 2; // Default HB mode
				}
				cReadMode = 0;
				break;
			}
		}else
		{	if (memcmp(token, "log-server-address",18) == 0) cReadMode = 1;
			if (memcmp(token, "log-server-port",15) == 0)    cReadMode = 2;
			if (memcmp(token, "game-server-mode",16) == 0)   cReadMode = 3;
		}
		token = strtok( NULL, seps );
	}
	delete[] cp;
	if (pFile != NULL) fclose(pFile);
	return TRUE;
DEFAULT_IP:
	ZeroMemory(m_cLogServerAddr, sizeof(m_cLogServerAddr));
	strcpy(m_cLogServerAddr, DEF_SERVER_IP);
	m_iLogServerPort = DEF_SERVER_PORT;
	return TRUE;
}

void CGame::ReleaseUnusedSprites()
{	int i;
	for (i = 0; i < DEF_MAXSPRITES; i++)
	if ((m_pSprite[i] != NULL))
	{	if( (m_pSprite[i]->m_bIsSurfaceEmpty == FALSE) && (m_pSprite[i]->m_bOnCriticalSection == FALSE) )
		{	if ((G_dwGlobalTime - m_pSprite[i]->m_dwRefTime) > 60000 ) m_pSprite[i]->_iCloseSprite();

	}	}
	for (i = 0; i < DEF_MAXTILES; i++)
	if ((m_pTileSpr[i] != NULL))
	{	if( (m_pTileSpr[i]->m_bIsSurfaceEmpty == FALSE) && (m_pTileSpr[i]->m_bOnCriticalSection == FALSE) )
		{	if ((G_dwGlobalTime - m_pTileSpr[i]->m_dwRefTime) > 60000 ) m_pTileSpr[i]->_iCloseSprite();
	}	}
	for (i = 0; i < DEF_MAXEFFECTSPR; i++)
	if ((m_pEffectSpr[i] != NULL))
	{	if( (m_pEffectSpr[i]->m_bIsSurfaceEmpty == FALSE) && (m_pEffectSpr[i]->m_bOnCriticalSection == FALSE) )
		{	if ((G_dwGlobalTime - m_pEffectSpr[i]->m_dwRefTime) > 60000 ) m_pEffectSpr[i]->_iCloseSprite();
	}	}

	for (i = 0; i < DEF_MAXSOUNDEFFECTS; i++)
	{	if (m_pCSound[i] != NULL)
		{	if (((G_dwGlobalTime - m_pCSound[i]->m_dwTime) > 30000) && (m_pCSound[i]->m_bIsLooping == FALSE)) m_pCSound[i]->_ReleaseSoundBuffer();
		}
		if (m_pMSound[i] != NULL)
		{	if (((G_dwGlobalTime - m_pMSound[i]->m_dwTime) > 30000) && (m_pMSound[i]->m_bIsLooping == FALSE)) m_pMSound[i]->_ReleaseSoundBuffer();
		}
		if (m_pESound[i] != NULL)
		{	if (((G_dwGlobalTime - m_pESound[i]->m_dwTime) > 30000) && (m_pESound[i]->m_bIsLooping == FALSE)) m_pESound[i]->_ReleaseSoundBuffer();
	}	}
}

void CGame::PutChatScrollList(char * pMsg, char cType)
{int i;
	if (m_pChatScrollList[DEF_MAXCHATSCROLLMSGS - 1] != NULL)
	{	delete m_pChatScrollList[DEF_MAXCHATSCROLLMSGS - 1];
		m_pChatScrollList[DEF_MAXCHATSCROLLMSGS - 1] = NULL;
	}
	for (i = DEF_MAXCHATSCROLLMSGS - 2; i >= 0; i--)
	{	m_pChatScrollList[i+1] = m_pChatScrollList[i];
		m_pChatScrollList[i] = NULL;
	}
	m_pChatScrollList[0] = new class CMsg(1, pMsg, cType);
}

void CGame::ChatMsgHandler(char * pData)
{
 int i, iObjectID, iLoc;
 short * sp, sX, sY;
 char * cp, cMsgType, cName[21], cTemp[100], cMsg[100], cTxt1[100], cTxt2[100];
 DWORD dwTime;
 WORD * wp;
 BOOL bFlag;

 char cHeadMsg[200];

	dwTime = m_dwCurTime;

	ZeroMemory(cTxt1, sizeof(cTxt1));
	ZeroMemory(cTxt2, sizeof(cTxt2));
	ZeroMemory(cMsg, sizeof(cMsg));

	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	iObjectID = (int)*wp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	sp = (short *)cp;
	sX = *sp;
	cp += 2;

	sp = (short *)cp;
	sY = *sp;
	cp += 2;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, (char *)cp, 10);
	cp += 10;

	cMsgType = *cp;
	cp++;

	if (bCheckExID(cName) == TRUE) return;

	ZeroMemory(cTemp, sizeof(cTemp));
	strcpy(cTemp, cp);

	if( (cMsgType==0) || (cMsgType==2) || (cMsgType==3) )
	{	if( m_Misc.bCheckIMEString(cTemp)==FALSE ) return;
	}
	if( !m_bWhisper )
	{	if( cMsgType == 20 ) return;
	}
	if( !m_bShout )
	{	if( cMsgType == 2 || cMsgType == 3 ) return;
	}

	ZeroMemory(cMsg, sizeof(cMsg));
	wsprintf(cMsg, "%s: %s", cName, cTemp);
	m_DDraw._GetBackBufferDC();
	bFlag = FALSE;
	short sCheckByte = 0;
	while (bFlag == FALSE)
	{	iLoc = m_Misc.iGetTextLengthLoc(m_DDraw.m_hDC, cMsg, 305);
		for( int i=0 ; i<iLoc ; i++ ) if( cMsg[i] < 0 ) sCheckByte ++;
		if (iLoc == 0)
		{	PutChatScrollList(cMsg, cMsgType);
			bFlag = TRUE;
		}else
		{	if ((sCheckByte%2)==0)
			{	ZeroMemory(cTemp, sizeof(cTemp));
				memcpy(cTemp, cMsg, iLoc);
				PutChatScrollList(cTemp, cMsgType);
				ZeroMemory(cTemp, sizeof(cTemp));
				strcpy(cTemp, cMsg +iLoc );
				ZeroMemory(cMsg, sizeof(cMsg));
				strcpy(cMsg, " ");
				strcat(cMsg, cTemp);
			}else
			{	ZeroMemory(cTemp, sizeof(cTemp));
				memcpy(cTemp, cMsg, iLoc+1);
				PutChatScrollList(cTemp, cMsgType);
				ZeroMemory(cTemp, sizeof(cTemp));
				strcpy(cTemp, cMsg +iLoc+1);
				ZeroMemory(cMsg, sizeof(cMsg));
				strcpy(cMsg, " ");
				strcat(cMsg, cTemp);
	}	}	}

	m_DDraw._ReleaseBackBufferDC();

	_RemoveChatMsgListByObjectID(iObjectID);

	for (i = 1; i < DEF_MAXCHATMSGS; i++)
	if (m_pChatMsgList[i] == NULL) {
		m_pChatMsgList[i] = new class CMsg(1, (char *)(cp), dwTime);
		m_pChatMsgList[i]->m_iObjectID = iObjectID;

		if (m_pMapData->bSetChatMsgOwner(iObjectID, sX, sY, i) == FALSE) {
			delete m_pChatMsgList[i];
			m_pChatMsgList[i] = NULL;
		}

		if ( (cMsgType != 0) && (m_bIsDialogEnabled[10] != TRUE) ) {
			ZeroMemory(cHeadMsg, sizeof(cHeadMsg));
			wsprintf(cHeadMsg, "%s:%s", cName, cp);
			AddEventList(cHeadMsg, cMsgType);
		}
		return;
	}
}

void CGame::ReleaseTimeoverChatMsg()
{int i;
 DWORD dwTime;
	dwTime = G_dwGlobalTime;
	for ( i = 1; i < DEF_MAXCHATMSGS; i++)
	if (m_pChatMsgList[i] != NULL) {

		if ((m_pChatMsgList[i]->m_cType >= 1) && (m_pChatMsgList[i]->m_cType <= 20)) {
			if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_A) {
				delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
		}
		else
		if ((m_pChatMsgList[i]->m_cType >= 21) && (m_pChatMsgList[i]->m_cType <= 40)) {
			if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_B) {
				delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
		}
		else
		if ((m_pChatMsgList[i]->m_cType >= 41) && (m_pChatMsgList[i]->m_cType <= 60)) {
			if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_C) {
				delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
		}
		else if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_A) {
			delete m_pChatMsgList[i];
			m_pChatMsgList[i] = NULL;
		}
	}
}

void CGame::DrawBackground(short sDivX, short sModX, short sDivY, short sModY)
{
 int indexX, indexY, ix, iy;
 short sSpr, sSprFrame;
 	if (sDivX < 0 || sDivY < 0) return ;
	if ((m_bIsRedrawPDBGS == TRUE) || (m_iPDBGSdivX != sDivX) || (m_iPDBGSdivY != sDivY)) {
		// Pre-Draw Background Surface
		m_bIsRedrawPDBGS = FALSE;
		m_iPDBGSdivX = sDivX;
		m_iPDBGSdivY = sDivY;
		SetRect(&m_DDraw.m_rcClipArea, 0,0, 640+32, 480+32);
		indexY = sDivY+m_pMapData->m_sPivotY;
		for (iy = -sModY; iy < 427+48 ; iy += 32)
		{
			indexX = sDivX+m_pMapData->m_sPivotX;
			for (ix = -sModX; ix < 640+48 ; ix += 32)
			{	sSpr      = m_pMapData->m_tile[indexX][indexY].m_sTileSprite;
				sSprFrame = m_pMapData->m_tile[indexX][indexY].m_sTileSpriteFrame;
				m_pTileSpr[sSpr]->PutSpriteFastNoColorKeyDst(m_DDraw.m_lpPDBGS, ix - 16 +sModX, iy - 16 +sModY, sSprFrame, m_dwCurTime);
				indexX++;
			}
			indexY++;
		}
		SetRect(&m_DDraw.m_rcClipArea, 0,0, 640, 480);
	}
	RECT rcRect;
	SetRect(&rcRect, sModX, sModY, 640+sModX, 480+sModY); // our fictitious sprite bitmap is
	m_DDraw.m_lpBackB4->BltFast( 0, 0, m_DDraw.m_lpPDBGS, &rcRect, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
	if( m_bIsCrusadeMode )
	{	if(m_iConstructLocX != -1) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, m_iConstructLocX*32 - m_sViewPointX, m_iConstructLocY*32 - m_sViewPointY, 41);
		if( m_iTeleportLocX != -1) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, m_iTeleportLocX*32 - m_sViewPointX, m_iTeleportLocY*32 - m_sViewPointY, 42);
	}
}