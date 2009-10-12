
void CGame::DlgBoxClick_NpcActionQuery(short msX, short msY)
{short sX, sY;
 int   absX, absY;
	if (m_bIsDialogEnabled[27] == TRUE)
	{	AddEventList(BITEMDROP_SKILLDIALOG1, 10);
		return;
	}
	sX = m_stDialogBoxInfo[20].sX;
	sY = m_stDialogBoxInfo[20].sY;

	switch (m_stDialogBoxInfo[20].cMode) {
	case 0: // Talk to npc
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	EnableDialogBox(m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, NULL, NULL);
			DisableDialogBox(20);
		}
		if ((m_bIsDialogEnabled[21] == FALSE) && (msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
		{	switch (m_stDialogBoxInfo[20].sV1) {
			case 7:	// Guild
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 1, NULL, NULL, NULL);
				AddEventList(TALKING_TO_GUILDHALL_OFFICER, 10);
				break;
			case 11: // BS or Shop
				switch (m_stDialogBoxInfo[20].sV2) {
				case 1:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 2, NULL, NULL, NULL);
					AddEventList(TALKING_TO_SHOP_KEEPER, 10);
					break;
				case 2:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 3, NULL, NULL, NULL);
					AddEventList(TALKING_TO_BLACKSMITH_KEEPER, 10);
					break;
				}
				break;
			case 13: // CityHall officer
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 4, NULL, NULL, NULL);
				AddEventList(TALKING_TO_CITYHALL_OFFICER, 10);
				break;
			case 14: // WH keeper
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 5, NULL, NULL, NULL);
				AddEventList(TALKING_TO_WAREHOUSE_KEEPER, 10);
				break;
			case 16: // Magicmerchant
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 6, NULL, NULL, NULL);
				AddEventList(TALKING_TO_MAGICIAN, 10);
				break;
			}
			DisableDialogBox(20);
		}
		break;

	case 1: // On other player
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	absX = abs(m_stDialogBoxInfo[20].sV5 - m_sPlayerX);
			absY = abs(m_stDialogBoxInfo[20].sV6 - m_sPlayerY);
			if ((absX <= 4) && (absY <= 4))
				 bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV3, m_stDialogBoxInfo[20].sV5, m_stDialogBoxInfo[20].sV6, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); //v1.4
			else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY7, 10); //"Too far to give the item."
			DisableDialogBox(20);
		}else if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
		{	absX = abs(m_stDialogBoxInfo[20].sV5 - m_sPlayerX);
			absY = abs(m_stDialogBoxInfo[20].sV6 - m_sPlayerY);
			if ((absX <= 4) && (absY <= 4))
				 bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_EXCHANGEITEMTOCHAR, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV3, m_stDialogBoxInfo[20].sV5, m_stDialogBoxInfo[20].sV6, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); //v1.4
			else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY8, 10); //"Too far to exchange item."
			DisableDialogBox(20);
		}
		break;

	case 2: // Item on Shop/BS
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SELLITEM, NULL, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, m_stDialogBoxInfo[20].sV3, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); // v1.4
			DisableDialogBox(20);
		}else if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
		{	if (m_stDialogBoxInfo[20].sV3 == 1)
			{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, NULL, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, NULL, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); // v1.4
				DisableDialogBox(20);
		}	}
		break;

	case 3: // Put item in the WH
		if ((msX > sX + 25) && (msX < sX + 105) && (msY > sY + 55) && (msY < sY + 70))
		{	absX = abs(m_stDialogBoxInfo[20].sV5 - m_sPlayerX);
			absY = abs(m_stDialogBoxInfo[20].sV6 - m_sPlayerY);
			if ((absX <= 8) && (absY <= 8))
			{	if (_iGetBankItemCount() >= (DEF_MAXBANKITEMS-1))
				{	AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);//"here is no empty space left in warehouse."
				}else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV3, m_stDialogBoxInfo[20].sV5, m_stDialogBoxInfo[20].sV6, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); //v1.4
			}else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY7, 10);//"Too far to give the item."

			DisableDialogBox(20);
		}
		break;

	case 4: // talk to npc or Unicorn
		if ((m_bIsDialogEnabled[21] == FALSE) && (msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
		{	switch (m_stDialogBoxInfo[20].sV3) {
			case 21: // Guard
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 21, NULL, NULL, NULL);
				AddEventList(TALKING_TO_GUARD, 10);//"Talking to Guard..."
				break;

			case 32: // Unicorn
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 32, NULL, NULL, NULL);
				AddEventList(TALKING_TO_UNICORN, 10);//"Talking to Unicorn..."
				break;
			case 67:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 67, NULL, NULL, NULL);
				AddEventList(TALKING_TO_MCGAFFIN, 10);//"Talking to a town man..."
				break;
			case 68:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 68, NULL, NULL, NULL);
				AddEventList(TALKING_TO_PERRY, 10);//"Talking to a town maiden..."
				break;
			case 69:
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 69, NULL, NULL, NULL);
				AddEventList(TALKING_TO_DEVLIN, 10);//"Talking to a town magician..."
				break;
		}	}
		DisableDialogBox(20);
		break;


	case 5: // Talk
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	EnableDialogBox(m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, NULL, NULL);
			DisableDialogBox(20);
		}
		if ((msX > sX + 25 +75) && (msX < sX + 80 +75) && (msY > sY + 55) && (msY < sY + 70))
		{	EnableDialogBox(31, NULL, NULL, NULL);
			DisableDialogBox(20);
		}

		if ((m_bIsDialogEnabled[21] == FALSE) && (msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
		{	switch (m_stDialogBoxInfo[20].sV1) {
			case 7:	// Guild
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 1, NULL, NULL, NULL);
				AddEventList(TALKING_TO_GUILDHALL_OFFICER, 10);//"Talking to Guildhall Officer..."
				break;

			case 11: //
				switch (m_stDialogBoxInfo[20].sV2) {
				case 1:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 2, NULL, NULL, NULL);
					AddEventList(TALKING_TO_SHOP_KEEPER, 10);//"Talking to Shop Keeper..."
					break;
				case 2:
					bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 3, NULL, NULL, NULL);
					AddEventList(TALKING_TO_BLACKSMITH_KEEPER, 10);//"
					break;
				}
				break;

			case 13: //
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 4, NULL, NULL, NULL);
				AddEventList(TALKING_TO_CITYHALL_OFFICER, 10);//"
				break;

			case 14: //
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 5, NULL, NULL, NULL);
				AddEventList(TALKING_TO_WAREHOUSE_KEEPER, 10);//
				break;

			case 16: //
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, NULL, 6, NULL, NULL, NULL);
				AddEventList(TALKING_TO_MAGICIAN, 10);//"
				break;
			}
			DisableDialogBox(20);
		}
		break;

	case 6: // Snoopy: Added Gail
		if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
		{	EnableDialogBox(51, 0, NULL, NULL);
			DisableDialogBox(20);
		}
	}
}


void CGame::DlgBoxClick_Shop(short msX, short msY)
{
 int i;
 short sX, sY;
 char cTemp[21];
	sX = m_stDialogBoxInfo[11].sX;
	sY = m_stDialogBoxInfo[11].sY;

	switch ( m_stDialogBoxInfo[11].cMode ) {
	case 0:
		for (i = 0; i < 13; i++)
		if ((msX >= sX + 20) && (msX <= sX + 220) && (msY >= sY + i*18 + 65) && (msY <= sY + i*18 + 79)) {
			if (_iGetTotalItemNum() >= 50) {
				AddEventList(DLGBOX_CLICK_SHOP1, 10);//"You cannot buy anything because your bag is full."
				return;
			}

			PlaySound('E', 14, 5);
			if (m_pItemForSaleList[m_stDialogBoxInfo[11].sView + i] != NULL)
				m_stDialogBoxInfo[11].cMode = m_stDialogBoxInfo[11].sView + i + 1;
			return;
		}
		break;

	default:
		if ((msX >= sX + 145) && (msX <= sX + 162) && (msY >= sY + 209) && (msY <= sY + 230))
		{	m_stDialogBoxInfo[11].sV3 += 10;
			if (m_stDialogBoxInfo[11].sV3 >= (50 - _iGetTotalItemNum()))
				m_stDialogBoxInfo[11].sV3 = (50 - _iGetTotalItemNum());
		}

		if ((msX >= sX + 145) && (msX <= sX + 162) && (msY >= sY + 234) && (msY <= sY + 251))
		{	m_stDialogBoxInfo[11].sV3 -= 10;
			if (m_stDialogBoxInfo[11].sV3 <= 1)
				m_stDialogBoxInfo[11].sV3 = 1;
		}

		if ((msX >= sX + 163) && (msX <= sX + 180) && (msY >= sY + 209) && (msY <= sY + 230))
		{	m_stDialogBoxInfo[11].sV3++;
			if (m_stDialogBoxInfo[11].sV3 >= (50 - _iGetTotalItemNum()))
				m_stDialogBoxInfo[11].sV3 = (50 - _iGetTotalItemNum());
		}

		if ((msX >= sX + 163) && (msX <= sX + 180) && (msY >= sY + 234) && (msY <= sY + 251))
		{	m_stDialogBoxInfo[11].sV3--;
			if (m_stDialogBoxInfo[11].sV3 <= 1)
				m_stDialogBoxInfo[11].sV3 = 1;
		}

		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Purchase Click
			if ((50 - _iGetTotalItemNum()) < m_stDialogBoxInfo[11].sV3)
			{	AddEventList(DLGBOX_CLICK_SHOP1, 10);//"ou cannot buy anything because your bag is full."
			}else
			{	ZeroMemory(cTemp, sizeof(cTemp));
				strcpy(cTemp, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cName);
				bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, NULL, m_stDialogBoxInfo[11].sV3, NULL, NULL, cTemp);
			}
			m_stDialogBoxInfo[11].cMode = 0;
			m_stDialogBoxInfo[11].sV3   = 1;
			PlaySound('E', 14, 5);
		}

		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel Click
			m_stDialogBoxInfo[11].cMode = 0;
			m_stDialogBoxInfo[11].sV3   = 1;
			PlaySound('E', 14, 5);
		}
		break;
	}
}

void CGame::DlgBoxClick_Skill(short msX, short msY)
{int i;
 short sX, sY;
	sX = m_stDialogBoxInfo[15].sX;
	sY = m_stDialogBoxInfo[15].sY;
	switch ( m_stDialogBoxInfo[15].cMode ) {
	case -1:
		break;
	case 0:
		for (i = 0; i < 17; i++)
		if ((i < DEF_MAXSKILLTYPE) && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView] != NULL))
		{	if ((msX >= sX + 44) && (msX <= sX + 135 + 44) && (msY >= sY + 45 + i*15) && (msY <= sY + 59 + i*15))
			{	if (    (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_bIsUseable == TRUE)
					 && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel != 0) )
				{	if (m_bSkillUsingStatus == TRUE)
					{	AddEventList(DLGBOX_CLICK_SKILL1, 10); // "You are already using other skill."
						return;
					}
					if ((m_bCommandAvailable == FALSE) || (m_iHP <= 0))
					{	AddEventList(DLGBOX_CLICK_SKILL2, 10); // "You can't use a skill while you are moving."
						return;
					}
					if (m_bIsGetPointingMode == TRUE)
					{	return;
					}
					switch (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_cUseMethod) {
					case 0:
					case 2:
						bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USESKILL, NULL, (i + m_stDialogBoxInfo[15].sView), NULL, NULL, NULL);
						m_bSkillUsingStatus = TRUE;
						DisableDialogBox(15);
						PlaySound('E', 14, 5);
						break;
					}
				}
			}else if ((msX >= sX + 215) && (msX <= sX + 240) && (msY >= sY + 45 + i*15) && (msY <= sY + 59 + i*15))
			{	if (m_stDialogBoxInfo[15].bFlag == FALSE)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SETDOWNSKILLINDEX, NULL, i + m_stDialogBoxInfo[15].sView, NULL, NULL, NULL);
					PlaySound('E', 14, 5);
					m_stDialogBoxInfo[15].bFlag = TRUE;
		}	}	}
		break;
	}
}

void CGame::DlgBoxClick_SkillDlg(short msX, short msY)
{
 int i, iAdjX, iAdjY;
 short sX, sY;

	sX = m_stDialogBoxInfo[26].sX;
	sY = m_stDialogBoxInfo[26].sY;

	iAdjX = 5 ;
	iAdjY = 8 ;


	switch (m_stDialogBoxInfo[26].cMode) {
	case 1:
		if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
		{	m_stDialogBoxInfo[26].cMode = 2;
			m_stDialogBoxInfo[26].cStr[0] = 1;
			m_stDialogBoxInfo[26].dwT1 = m_dwCurTime;
			PlaySound('E', 14, 5);
			AddEventList(DLGBOX_CLICK_SKILLDLG1, 10); // "Mixing a potion..."
			PlaySound('E', 41, 0);
		}
		break;
	// Crafting
	case 7:
		if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
		{	DebugLog("Tag1 DlgBoxClick_SkillDlg");
			if (m_stDialogBoxInfo[26].sV1 == -1)
			{	AddEventList(DLGBOX_CLICK_SKILLDLG2, 10); // "There is not enough crafting materials. Please put in more materials."
				PlaySound('E', 14, 5);
			}else
			{	m_stDialogBoxInfo[26].cMode = 8;
				m_stDialogBoxInfo[26].dwT1 = m_dwCurTime;
				m_stDialogBoxInfo[26].cStr[1] = 1;
				PlaySound('E', 14, 5);
				AddEventList(DLGBOX_CLICK_SKILLDLG3, 10); // "Crafting the item in progress"
				PlaySound('E', 51, 0);
		}	}
		break;

	case 3:
		for (i = 0; i < 13; i++)
		if (m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView] != NULL)
		{	if ((msX >= sX + iAdjX + 44) && (msX <= sX + iAdjX + 135 + 44) && (msY >= sY + iAdjY + 55 + i*15) && (msY <= sY + iAdjY + 55 + 14 + i*15)) {
				m_stDialogBoxInfo[26].cMode = 4;
				m_stDialogBoxInfo[26].cStr[0] = i + m_stDialogBoxInfo[26].sView;
				PlaySound('E', 14, 5);
		}	}
		break;

	case 4:
		iAdjX = -1 ;
		iAdjY = -7 ;
		if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bBuildEnabled == TRUE)
		{	if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) {
				// Back
				m_stDialogBoxInfo[26].cMode = 3;
				PlaySound('E', 14, 5);

				if ((m_stDialogBoxInfo[26].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV1] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = FALSE;
				if ((m_stDialogBoxInfo[26].sV2 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV2] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = FALSE;
				if ((m_stDialogBoxInfo[26].sV3 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV3] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = FALSE;
				if ((m_stDialogBoxInfo[26].sV4 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV4] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = FALSE;
				if ((m_stDialogBoxInfo[26].sV5 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV5] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = FALSE;
				if ((m_stDialogBoxInfo[26].sV6 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV6] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = FALSE;

				m_stDialogBoxInfo[26].sV1   = -1;
				m_stDialogBoxInfo[26].sV2   = -1;
				m_stDialogBoxInfo[26].sV3   = -1;
				m_stDialogBoxInfo[26].sV4   = -1;
				m_stDialogBoxInfo[26].sV5   = -1;
				m_stDialogBoxInfo[26].sV6   = -1;
				m_stDialogBoxInfo[26].cStr[0] = 0;
				m_stDialogBoxInfo[26].cStr[1] = 0;
				m_stDialogBoxInfo[26].cStr[4] = 0;
			}

			if ((msX >= sX + iAdjX + 160) && (msX <= sX + iAdjX + 255) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
			{	// Manufacture
				if (m_stDialogBoxInfo[26].cStr[4] == 1)
				{	m_stDialogBoxInfo[26].cMode   = 5;
					m_stDialogBoxInfo[26].cStr[1] = 0;
					m_stDialogBoxInfo[26].dwT1    = m_dwCurTime;
					PlaySound('E', 14, 5);
					PlaySound('E', 44, 0);
			}	}
		}else
		{	if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) 	// Back
			{	m_stDialogBoxInfo[26].cMode = 3;
				PlaySound('E', 14, 5);

				if ((m_stDialogBoxInfo[26].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV1] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = FALSE;
				if ((m_stDialogBoxInfo[26].sV2 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV2] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = FALSE;
				if ((m_stDialogBoxInfo[26].sV3 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV3] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = FALSE;
				if ((m_stDialogBoxInfo[26].sV4 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV4] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = FALSE;
				if ((m_stDialogBoxInfo[26].sV5 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV5] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = FALSE;
				if ((m_stDialogBoxInfo[26].sV6 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV6] != NULL))
					m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = FALSE;

				m_stDialogBoxInfo[26].sV1   = -1;
				m_stDialogBoxInfo[26].sV2   = -1;
				m_stDialogBoxInfo[26].sV3   = -1;
				m_stDialogBoxInfo[26].sV4   = -1;
				m_stDialogBoxInfo[26].sV5   = -1;
				m_stDialogBoxInfo[26].sV6   = -1;
				m_stDialogBoxInfo[26].cStr[0] = 0;
				m_stDialogBoxInfo[26].cStr[1] = 0;
				m_stDialogBoxInfo[26].cStr[4] = 0;
			}
		}
		break;

	case 6:
		iAdjX = -1;
		iAdjY = -7;
		if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) {
			// Back
			m_stDialogBoxInfo[26].cMode = 3;
			PlaySound('E', 14, 5);

			if ((m_stDialogBoxInfo[26].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV1] != NULL))
				m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = FALSE;
			if ((m_stDialogBoxInfo[26].sV2 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV2] != NULL))
				m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = FALSE;
			if ((m_stDialogBoxInfo[26].sV3 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV3] != NULL))
				m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = FALSE;
			if ((m_stDialogBoxInfo[26].sV4 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV4] != NULL))
				m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = FALSE;
			if ((m_stDialogBoxInfo[26].sV5 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV5] != NULL))
				m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = FALSE;
			if ((m_stDialogBoxInfo[26].sV6 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV6] != NULL))
				m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = FALSE;

			m_stDialogBoxInfo[26].sV1   = -1;
			m_stDialogBoxInfo[26].sV2   = -1;
			m_stDialogBoxInfo[26].sV3   = -1;
			m_stDialogBoxInfo[26].sV4   = -1;
			m_stDialogBoxInfo[26].sV5   = -1;
			m_stDialogBoxInfo[26].sV6   = -1;
			m_stDialogBoxInfo[26].cStr[0] = 0;
			m_stDialogBoxInfo[26].cStr[1] = 0;
			m_stDialogBoxInfo[26].cStr[4] = 0;
		}
		break;
	}
}

void CGame::ResponseTeleportList(char *pData)
{	char *cp;
	int  *ip, i;
#ifdef _DEBUG
	AddEventList("Teleport ???", 10);
#endif
	cp = pData + 6;
	ip = (int*) cp;
	m_iTeleportMapCount = *ip;
	cp += 4;
	for ( i = 0 ; i < m_iTeleportMapCount ; i++)
	{	ip = (int*)cp;
		m_stTeleportList[i].iIndex = *ip;
		cp += 4;
		ZeroMemory(m_stTeleportList[i].mapname, sizeof(m_stTeleportList[i].mapname) );
		memcpy(m_stTeleportList[i].mapname, cp, 10);
		cp += 10;
		ip = (int*)cp;
		m_stTeleportList[i].iX = *ip;
		cp += 4;
		ip = (int*)cp;
		m_stTeleportList[i].iY = *ip;
		cp += 4;
		ip = (int*)cp;
		m_stTeleportList[i].iCost = *ip;
		cp += 4;
	}
}

void CGame::ResponseChargedTeleport(char *pData)
{	short *sp;
	char *cp;
	short sRejectReason = 0;
	cp = (char*)pData + DEF_INDEX2_MSGTYPE + 2;
	sp = (short*)cp;
	sRejectReason = *sp;

#ifdef _DEBUG
	AddEventList( "charged teleport ?", 10 );
#endif

	switch( sRejectReason )	{
	case 1:
		AddEventList( RESPONSE_CHARGED_TELEPORT1, 10 );
		break;
	case 2:
		AddEventList( RESPONSE_CHARGED_TELEPORT2, 10 );
		break;
	case 3:
		AddEventList( RESPONSE_CHARGED_TELEPORT3, 10 );
		break;
	case 4:
		AddEventList( RESPONSE_CHARGED_TELEPORT4, 10 );
		break;
	case 5:
		AddEventList( RESPONSE_CHARGED_TELEPORT5, 10 );
		break;
	case 6:
		AddEventList( RESPONSE_CHARGED_TELEPORT6, 10 );
		break;
	default:
		AddEventList( RESPONSE_CHARGED_TELEPORT7, 10 );
	}
}

void CGame::NotifyMsg_CannotGiveItem(char *pData)
{
 char * cp, cName[21], cTxt[256];
 WORD * wp, wItemIndex;
 int  * ip, iAmount;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wItemIndex = *wp;
	cp += 2;

	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[wItemIndex], cStr1, cStr2, cStr3);
	if( iAmount == 1 ) wsprintf(cTxt, NOTIFYMSG_CANNOT_GIVE_ITEM2, cStr1, cName);
	else wsprintf( cTxt, NOTIFYMSG_CANNOT_GIVE_ITEM1, iAmount, cStr1, cName);


	AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_DropItemFin_CountChanged(char *pData)
{
 char * cp, cTxt[256];
 WORD * wp, wItemIndex;
 int  * ip, iAmount;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wItemIndex = *wp;
	cp += 2;

	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[wItemIndex]->m_cName, m_pItemList[wItemIndex]->m_dwAttribute, cStr1, cStr2, cStr3);
	wsprintf(cTxt, NOTIFYMSG_THROW_ITEM1, iAmount, cStr1);

	AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_CannotJoinMoreGuildsMan(char * pData)
{
 char * cp, cName[12], cTxt[120];

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);

	wsprintf(cTxt, NOTIFYMSG_CANNOT_JOIN_MOREGUILDMAN1, cName);
	AddEventList(cTxt, 10);
	AddEventList(NOTIFYMSG_CANNOT_JOIN_MOREGUILDMAN2, 10);
}



void CGame::NotifyMsg_DismissGuildsMan(char * pData)
{
 char * cp, cName[12], cTxt[120];
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);

	if( memcmp( m_cPlayerName, cName, 10 ) != 0 ) {
		wsprintf(cTxt, NOTIFYMSG_DISMISS_GUILDMAN1, cName);
		AddEventList(cTxt, 10);
	}
	ClearGuildNameList();
}

void CGame::NotifyMsg_CannotRating(char * pData)
{
 char * cp, cTxt[120];
 WORD * wp, wTime;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wTime = *wp;
	cp += 2;

	if (wTime == 0) wsprintf(cTxt, NOTIFYMSG_CANNOT_RATING1, wTime*3);
	else wsprintf(cTxt, NOTIFYMSG_CANNOT_RATING2, wTime*3);
	AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_CannotRepairItem(char * pData)
{
 char * cp, cTxt[120], cStr1[64], cStr2[64], cStr3[64];
 WORD * wp, wV1, wV2;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
  	wV1 = *wp;
	cp += 2;
	wp = (WORD *)cp;
  	wV2 = *wp;
	cp += 2;
	ZeroMemory( cStr1, sizeof(cStr1) );
	ZeroMemory( cStr2, sizeof(cStr2) );
	ZeroMemory( cStr3, sizeof(cStr3) );
	GetItemName( m_pItemList[wV1], cStr1, cStr2, cStr3 );

	switch (wV2) {
	case 1:
		wsprintf(cTxt, NOTIFYMSG_CANNOT_REPAIR_ITEM1, cStr1 );
		AddEventList(cTxt, 10);
 		break;
	case 2:
		wsprintf(cTxt, NOTIFYMSG_CANNOT_REPAIR_ITEM2, cStr1 );
		AddEventList(cTxt, 10);
 		break;
	}
	m_bIsItemDisabled[wV1] = FALSE;
}

void CGame::NotifyMsg_CannotSellItem(char * pData)
{
 char * cp, cTxt[120], cStr1[64], cStr2[64], cStr3[64];
 WORD * wp, wV1, wV2;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	wp = (WORD *)cp;
  	wV1 = *wp;
	cp += 2;

	wp = (WORD *)cp;
  	wV2 = *wp;
	cp += 2;

	ZeroMemory( cStr1, sizeof(cStr1) );
	ZeroMemory( cStr2, sizeof(cStr2) );
	ZeroMemory( cStr3, sizeof(cStr3) );
	GetItemName( m_pItemList[wV1], cStr1, cStr2, cStr3 );

	switch (wV2) {
	case 1:
		wsprintf(cTxt, NOTIFYMSG_CANNOT_SELL_ITEM1, cStr1);//"
		AddEventList(cTxt, 10);
		break;

	case 2:
		wsprintf(cTxt, NOTIFYMSG_CANNOT_SELL_ITEM2, cStr1);//"
		AddEventList(cTxt, 10);
		break;

	case 3:
		wsprintf(cTxt, NOTIFYMSG_CANNOT_SELL_ITEM3, cStr1);//"
		AddEventList(cTxt, 10);
		AddEventList(NOTIFYMSG_CANNOT_SELL_ITEM4, 10);//"
		break;

	case 4:
		AddEventList(NOTIFYMSG_CANNOT_SELL_ITEM5, 10); // "
		AddEventList(NOTIFYMSG_CANNOT_SELL_ITEM6, 10); // "
		break;
	}
	m_bIsItemDisabled[wV1] = FALSE;
}

void CGame::NotifyMsg_Charisma(char * pData)
{
 DWORD * dwp;
 int  iPrevChar;
 char cTxt[120];

	iPrevChar = m_iCharisma;
	dwp = (DWORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
	m_iCharisma = (int)*dwp;

	if (m_iCharisma > iPrevChar)
	{	wsprintf(cTxt, NOTIFYMSG_CHARISMA_UP, m_iCharisma - iPrevChar);//"
		AddEventList(cTxt, 10);
		PlaySound('E', 21, 0);
	}else
	{	wsprintf(cTxt, NOTIFYMSG_CHARISMA_DOWN, iPrevChar - m_iCharisma);//"
		AddEventList(cTxt, 10);
	}
}

void CGame::NotifyMsg_DropItemFin_EraseItem(char *pData)
{
 char * cp;
 WORD * wp;
 int * ip, iAmount;
 short  sItemIndex;
 char   cTxt[120];

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	wp = (WORD *)cp;
	sItemIndex = *wp;
	cp += 2;

	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);

	ZeroMemory(cTxt, sizeof(cTxt));
	if (m_bIsItemEquipped[sItemIndex] == TRUE)
	{	wsprintf(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
		AddEventList(cTxt, 10);
		m_sItemEquipmentStatus[	m_pItemList[sItemIndex]->m_cEquipPos ] = -1;
		m_bIsItemEquipped[sItemIndex] = FALSE;
	}
	if (m_iHP > 0)
	{	wsprintf(cTxt, NOTIFYMSG_THROW_ITEM2, cStr1);
	}else
	{	if (iAmount < 2)
			wsprintf(cTxt, NOTIFYMSG_DROPITEMFIN_ERASEITEM3, cStr1); // "You dropped a %s."
		else // Snoopy fix
		{	wsprintf(cTxt, NOTIFYMSG_DROPITEMFIN_ERASEITEM5, cStr1); // "You dropped %s."
	}	}
	AddEventList(cTxt, 10);
	EraseItem((char)sItemIndex);
	_bCheckBuildItemStatus();
}


void CGame::NotifyMsg_EnemyKillReward(char *pData)
{
 DWORD * dwp;
 short * sp, sGuildRank;
 char  * cp, cName[12], cGuildName[24], cTxt[120];
 int   iExp, iEnemyKillCount, iWarContribution;

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cGuildName, sizeof(cGuildName));

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	dwp  = (DWORD *)cp;
	iExp = *dwp;
	cp += 4;
	dwp  = (DWORD *)cp;
	iEnemyKillCount = *dwp;
	cp += 4;
	memcpy(cName, cp, 10);
	cp += 10;
	memcpy(cGuildName, cp, 20);
	cp += 20;
	sp  = (short *)cp;
	sGuildRank = *sp;
	cp += 2;
	sp  = (short *)cp;
	iWarContribution = *sp;
	cp += 2;

	if (iWarContribution > m_iWarContribution)
	{	wsprintf(G_cTxt, "%s +%d!", m_pGameMsgList[21]->m_pMsg, iWarContribution - m_iWarContribution);
		SetTopMsg(G_cTxt, 5);
	}else if (iWarContribution < m_iWarContribution)
	{}
	m_iWarContribution = iWarContribution;

	if (sGuildRank == -1)
	{	wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD1, cName);
		AddEventList(cTxt, 10);
	}else
	{	wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD2, cName, cGuildName); // Fixed by Snoopy
		AddEventList(cTxt, 10);
	}

/*	if( m_iExp != iExp ) // removed by snoopy because too much msg hide victim's name
	{	if (m_iExp > iExp) wsprintf(cTxt, EXP_DECREASED,m_iExp - iExp);
		else wsprintf(cTxt, EXP_INCREASED,iExp - m_iExp);
		AddEventList(cTxt, 10);
	}*/

	if (m_iEnemyKillCount != iEnemyKillCount)
	{	if (m_iEnemyKillCount > iEnemyKillCount)
		{	wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD5,m_iEnemyKillCount - iEnemyKillCount);
			AddEventList(cTxt, 10);
		}else
		{	wsprintf(cTxt, NOTIFYMSG_ENEMYKILL_REWARD6, iEnemyKillCount - m_iEnemyKillCount);
			AddEventList(cTxt, 10);
		}
	}

	if( iExp >= 0 ) m_iExp = iExp;
	if( iEnemyKillCount >= 0 ) m_iEnemyKillCount = iEnemyKillCount;
	PlaySound('E', 23, 0);
}

void CGame::NotifyMsg_EventFishMode(char * pData)
{
 short sSprite, sSpriteFrame;
 char * cp, cName[21];
 WORD * wp, wPrice;
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

	wp = (WORD *)cp;
	wPrice = *wp;
	cp += 2;

	wp = (WORD *)cp;
	sSprite = (short)*wp;
	cp += 2;

	wp = (WORD *)cp;
	sSpriteFrame = (short)*wp;
	cp += 2;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	EnableDialogBox(24, 0, NULL, wPrice, cName);
	m_stDialogBoxInfo[24].sV3 = sSprite;
	m_stDialogBoxInfo[24].sV4 = sSpriteFrame;

	AddEventList(NOTIFYMSG_EVENTFISHMODE1, 10);
}

void CGame::NotifyMsg_Exp(char * pData)
{
 DWORD * dwp;
 int iPrevExp, * ip;
 char * cp, cTxt[120];

	iPrevExp = m_iExp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	dwp = (DWORD *)cp;
	m_iExp = (int)*dwp;
	cp += 4;

	ip = (int *)cp;
//	m_iRating = *ip;
	cp += 4;

	if (m_iExp > iPrevExp)
	{	wsprintf(cTxt, EXP_INCREASED, m_iExp - iPrevExp);
		AddEventList(cTxt, 10);
	}else
	{	wsprintf(cTxt, EXP_DECREASED, iPrevExp - m_iExp);
		AddEventList(cTxt, 10);
	}
}


void CGame::NotifyMsg_ForceDisconn(char *pData)
{WORD * wpCount;
	wpCount = (WORD *)(pData + 6);
	m_bForceDisconn = TRUE;
	//m_cLogOutCount = (char)*wpCount;
	if( m_bIsProgramActive )
	{	if( m_cLogOutCount < 0 || m_cLogOutCount > 5 ) m_cLogOutCount = 5;
		AddEventList(NOTIFYMSG_FORCE_DISCONN1, 10);
	}else
	{	delete m_pGSock;
		m_pGSock = NULL;
		m_bEscPressed = FALSE;
		if (m_bSoundFlag) m_pESound[38]->bStop();
		if ((m_bSoundFlag) && (m_bMusicStat == TRUE))
		{
			if (m_pBGM != NULL) m_pBGM->bStop();
		}
		if (strlen(G_cCmdLineTokenA) != 0)
			 ChangeGameMode(DEF_GAMEMODE_ONQUIT);
		else ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
	}
}

void CGame::NotifyMsg_GiveItemFin_CountChanged(char *pData)
{
 char * cp, cName[21], cTxt[256];
 WORD * wp, wItemIndex;
 int  * ip, iAmount;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wItemIndex = *wp;
	cp += 2;

	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[wItemIndex]->m_cName, m_pItemList[wItemIndex]->m_dwAttribute, cStr1, cStr2, cStr3);
	if( iAmount == 1 ) wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_COUNTCHANGED1, cStr1, cName);
	wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_COUNTCHANGED2, iAmount, cStr1, cName);
	AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_GiveItemFin_EraseItem(char *pData)
{
 char * cp;
 WORD * wp;
 int  * ip, iAmount;
 short  sItemIndex;
 char cName[21], cTxt[250];


	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	wp = (WORD *)cp;
	sItemIndex = *wp;
	cp += 2;

	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[sItemIndex]->m_cName, m_pItemList[sItemIndex]->m_dwAttribute, cStr1, cStr2, cStr3);

	if (m_bIsItemEquipped[sItemIndex] == TRUE) {
		wsprintf(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
		AddEventList(cTxt, 10);

		// v1.42
		m_sItemEquipmentStatus[	m_pItemList[sItemIndex]->m_cEquipPos ] = -1;
		m_bIsItemEquipped[sItemIndex] = FALSE;
	}
	if (strlen(cName) == 0) wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM2, iAmount, cStr1);
	else {
		if (strcmp(cName, "Howard") == 0)
			 wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM3, iAmount, cStr1);
		else if (strcmp(cName, "William") == 0)
			 wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM4, iAmount, cStr1);
		else if (strcmp(cName, "Kennedy") == 0)
			wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM5, iAmount, cStr1);
		else if (strcmp(cName, "Tom") == 0)
			wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM7, iAmount, cStr1);
		else wsprintf(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM8, iAmount, cStr1, cName);
	}
	AddEventList(cTxt, 10);
	EraseItem((char)sItemIndex);
	_bCheckBuildItemStatus();
}

void CGame::NotifyMsg_GlobalAttackMode(char *pData)
{
 char * cp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	switch (*cp) {
	case 0:
		AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE1, 10);
		AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE2, 10);
		break;

	case 1:
		AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE3, 10);
		break;
	}
	cp++;
}


void CGame::NotifyMsg_HP(char * pData)
{
 DWORD * dwp;
 int iPrevHP;
 char cTxt[120];
 int iPrevMP;

	iPrevHP = m_iHP;
	dwp = (DWORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
	m_iHP = (int)*dwp;

	iPrevMP = m_iMP;
	dwp = (DWORD *)(pData + DEF_INDEX2_MSGTYPE + 6);
	m_iMP = (int)*dwp;

	if (m_iHP > iPrevHP)
	{	if ((m_iHP - iPrevHP) < 10) return;
		wsprintf(cTxt, NOTIFYMSG_HP_UP, m_iHP - iPrevHP);
		AddEventList(cTxt, 10);
		PlaySound('E', 21, 0);
	}else
	{	if ( (m_cLogOutCount > 0) && (m_bForceDisconn==FALSE) )
		{	m_cLogOutCount = -1;
			AddEventList(NOTIFYMSG_HP2, 10);
		}
		m_dwDamagedTime = timeGetTime();
		if (m_iHP < 20) AddEventList(NOTIFYMSG_HP3, 10);
		if ((iPrevHP - m_iHP) < 10) return;
		wsprintf(cTxt, NOTIFYMSG_HP_DOWN, iPrevHP - m_iHP);
		AddEventList(cTxt, 10);
	}
}

void CGame::NotifyMsg_Hunger(char * pData)
{
 char * cp, cHLv;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	cHLv = *cp;

	if ((cHLv <= 40) && (cHLv > 30)) AddEventList(NOTIFYMSG_HUNGER1, 10);//"
	if ((cHLv <= 25) && (cHLv > 20)) AddEventList(NOTIFYMSG_HUNGER2, 10);//"
	if ((cHLv <= 20) && (cHLv > 15)) AddEventList(NOTIFYMSG_HUNGER3, 10);//"
	if ((cHLv <= 15) && (cHLv > 10)) AddEventList(NOTIFYMSG_HUNGER4, 10);//"
	if ((cHLv <= 10) && (cHLv >= 0)) AddEventList(NOTIFYMSG_HUNGER5, 10);//"
}

void CGame::NotifyMsg_ItemColorChange(char *pData)
{
 short * sp, sItemIndex, sItemColor;
 char * cp;
 char cTxt[120];

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	sp = (short *)cp;
	sItemIndex = *sp;
	cp += 2;

	sp = (short *)cp;
	sItemColor = (short)*sp;
	cp += 2;

	if (m_pItemList[sItemIndex] != NULL) {
		char cStr1[64], cStr2[64], cStr3[64];
		GetItemName( m_pItemList[sItemIndex], cStr1, cStr2, cStr3 );
		if (sItemColor != -1) {
			m_pItemList[sItemIndex]->m_cItemColor = (char)sItemColor;
			wsprintf(cTxt, NOTIFYMSG_ITEMCOLOR_CHANGE1, cStr1);
			AddEventList(cTxt, 10);
		}
		else {
			wsprintf(cTxt, NOTIFYMSG_ITEMCOLOR_CHANGE2, cStr1);
			AddEventList(cTxt, 10);
		}
	}
}

void CGame::NotifyMsg_ItemDepleted_EraseItem(char * pData)
{
 char * cp;
 WORD * wp;
 short  sItemIndex;
 BOOL   bIsUseItemResult;
 char   cTxt[120];

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	wp = (WORD *)cp;
	sItemIndex = *wp;
	cp += 2;

	bIsUseItemResult = (BOOL)*cp;
	cp += 2;

	ZeroMemory(cTxt, sizeof(cTxt));

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);

	if (m_bIsItemEquipped[sItemIndex] == TRUE) {
		wsprintf(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
		AddEventList(cTxt, 10);

		// v1.42
		m_sItemEquipmentStatus[	m_pItemList[sItemIndex]->m_cEquipPos ] = -1;
		m_bIsItemEquipped[sItemIndex] = FALSE;
	}

	ZeroMemory(cTxt, sizeof(cTxt));
	if ( (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
		 (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_ARROW) ) {
		wsprintf(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM2, cStr1);
	}
	else {
		if (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE) {
			if (bIsUseItemResult == TRUE) {
				wsprintf(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM3, cStr1);
			}
		}
		else if (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_EAT) {
			if (bIsUseItemResult == TRUE) {
				wsprintf(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM4, cStr1);
				if ( (m_sPlayerType >= 1) && (m_sPlayerType <= 3) )
					PlaySound('C', 19, 0);
				if ( (m_sPlayerType >= 4) && (m_sPlayerType <= 6) )
					PlaySound('C', 20, 0);
			}
		}
		else if (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE_DEST) {
			if (bIsUseItemResult == TRUE) {
				wsprintf(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM3, cStr1);
			}
		}
		else {
			if (bIsUseItemResult == TRUE) {
				wsprintf(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM6, cStr1);
				PlaySound('E', 10, 0);
			}
		}
	}
	AddEventList(cTxt, 10);

	if (bIsUseItemResult == TRUE) 	m_bItemUsingStatus = FALSE;
	EraseItem((char)sItemIndex);
	_bCheckBuildItemStatus();
}

void CGame::NotifyMsg_ItemLifeSpanEnd(char * pData)
{
 char * cp;
 short * sp, sEquipPos, sItemIndex;
 char cTxt[120];

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	sp = (short *)cp;
	sEquipPos = *sp;
	cp += 2;
	sp = (short *)cp;
	sItemIndex = *sp;
	cp += 2;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName( m_pItemList[sItemIndex], cStr1, cStr2, cStr3 );
	wsprintf(cTxt, NOTIFYMSG_ITEMLIFE_SPANEND1, cStr1);
	AddEventList(cTxt, 10);
	m_sItemEquipmentStatus[	m_pItemList[sItemIndex]->m_cEquipPos ] = -1;
	m_bIsItemEquipped[sItemIndex] = FALSE;
	m_pItemList[sItemIndex]->m_wCurLifeSpan = 0;

	PlaySound('E', 10, 0);
}

void CGame::NotifyMsg_ItemObtained(char * pData)
{
 char * cp;
 short * sp;
 DWORD * dwp;
 int i, j;

 DWORD dwCount, dwAttribute;
 char  cName[21], cItemType, cEquipPos;
 BOOL  bIsEquipped;
 short sSprite, sSpriteFrame, sLevelLimit, sSpecialEV2;
 char  cTxt[120], cGenderLimit, cItemColor;
 WORD  * wp, wWeight, wCurLifeSpan;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	cp++;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	dwp = (DWORD *)cp;
	dwCount = *dwp;
	cp += 4;

	cItemType = *cp;
	cp++;

	cEquipPos = *cp;
	cp++;

	bIsEquipped = (BOOL)*cp;
	cp++;

	sp = (short *)cp;
	sLevelLimit = *sp;
	cp += 2;

	cGenderLimit = *cp;
	cp++;

	wp = (WORD *)cp;
	wCurLifeSpan = *wp;
	cp += 2;

	wp = (WORD *)cp;
	wWeight = *wp;
	cp += 2;

	sp = (short *)cp;
	sSprite = *sp;
	cp += 2;

	sp = (short *)cp;
	sSpriteFrame = *sp;
	cp += 2;

	cItemColor = *cp;
	cp++;

	sSpecialEV2 = (short)*cp; // v1.41
	cp++;

	dwp = (DWORD *)cp;
	dwAttribute = *dwp;
	cp += 4;
	/*
	bIsCustomMade = (BOOL)*cp;
	cp++;
	*/

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(cName, dwAttribute, cStr1, cStr2, cStr3);

	ZeroMemory(cTxt, sizeof(cTxt));
	if( dwCount == 1 ) wsprintf(cTxt, NOTIFYMSG_ITEMOBTAINED2, cStr1);
	else wsprintf(cTxt, NOTIFYMSG_ITEMOBTAINED1, dwCount, cStr1);

	AddEventList(cTxt, 10);

	PlaySound('E', 20, 0);

	if ((cItemType == DEF_ITEMTYPE_CONSUME) || (cItemType == DEF_ITEMTYPE_ARROW))
	{	for (i = 0; i < DEF_MAXITEMS; i++)
		if ((m_pItemList[i] != NULL) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
		{	m_pItemList[i]->m_dwCount += dwCount;
			m_bIsItemDisabled[i] = FALSE;
			return;
	}	}

  	short nX, nY;
  	for (i = 0; i < DEF_MAXITEMS; i++)
  	{	if ( ( m_pItemList[i] != NULL) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
		{	nX = m_pItemList[i]->m_sX;
			nY = m_pItemList[i]->m_sY;
			break;
		}else
		{	nX = 40;
			nY = 30;
	}	}


	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] == NULL)
	{	m_pItemList[i] = new class CItem;
		memcpy(m_pItemList[i]->m_cName, cName, 20);
		m_pItemList[i]->m_dwCount = dwCount;
		//m_pItemList[i]->m_sX      =	40;
		//m_pItemList[i]->m_sY      =	30;
		m_pItemList[i]->m_sX      =	nX;
		m_pItemList[i]->m_sY      =	nY;
		bSendCommand(MSGID_REQUEST_SETITEMPOS, NULL, i, nX, nY, NULL, NULL);
		m_pItemList[i]->m_cItemType = cItemType;
		m_pItemList[i]->m_cEquipPos = cEquipPos;
		m_bIsItemDisabled[i]        = FALSE;

		m_bIsItemEquipped[i] = FALSE;
		m_pItemList[i]->m_sLevelLimit  = sLevelLimit;
		m_pItemList[i]->m_cGenderLimit = cGenderLimit;
		m_pItemList[i]->m_wCurLifeSpan = wCurLifeSpan;
		m_pItemList[i]->m_wWeight      = wWeight;
		m_pItemList[i]->m_sSprite      = sSprite;
		m_pItemList[i]->m_sSpriteFrame = sSpriteFrame;
		m_pItemList[i]->m_cItemColor   = cItemColor;
		m_pItemList[i]->m_sItemSpecEffectValue2 = sSpecialEV2; // v1.41
		m_pItemList[i]->m_dwAttribute = dwAttribute;
		//m_pItemList[i]->m_bIsCustomMade = bIsCustomMade;

		_bCheckBuildItemStatus();

		for (j = 0; j < DEF_MAXITEMS; j++)
		if (m_cItemOrder[j] == -1) {
			m_cItemOrder[j] = i;
			return;
		}
		return;
	}
}

void CGame::NotifyMsg_ItemPurchased(char * pData)
{
 char  * cp;
 short * sp;
 DWORD * dwp;
 WORD  * wp;
 int i, j;

 DWORD dwCount;
 char  cName[21], cItemType, cEquipPos, cGenderLimit;
 BOOL  bIsEquipped;
 short sSprite, sSpriteFrame, sLevelLimit;
 WORD  wCost, wWeight, wCurLifeSpan;
 char  cTxt[120], cItemColor;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	cp++;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	dwp = (DWORD *)cp;
	dwCount = *dwp;
	cp += 4;

	cItemType = *cp;
	cp++;

	cEquipPos = *cp;
	cp++;

	bIsEquipped = (BOOL)*cp;
	cp++;

	sp = (short *)cp;
	sLevelLimit = *sp;
	cp += 2;

	cGenderLimit = *cp;
	cp++;

 	wp = (WORD *)cp;
	wCurLifeSpan = *wp;
	cp += 2;

	wp = (WORD *)cp;
	wWeight = *wp;
	cp += 2;

	sp = (short *)cp;
	sSprite = *sp;
	cp += 2;

	sp = (short *)cp;
	sSpriteFrame = *sp;
	cp += 2;

	cItemColor = *cp; // v1.4
	cp++;

	wp = (WORD *)cp;
	wCost = *wp;
	ZeroMemory(cTxt, sizeof(cTxt));
	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName( cName, NULL, cStr1, cStr2, cStr3 );
	wsprintf(cTxt, NOTIFYMSG_ITEMPURCHASED, cStr1, wCost);
	AddEventList(cTxt, 10);

	if ( (cItemType == DEF_ITEMTYPE_CONSUME) || (cItemType == DEF_ITEMTYPE_ARROW))
	{	for (i = 0; i < DEF_MAXITEMS; i++)
		if ((m_pItemList[i] != NULL) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
		{	m_pItemList[i]->m_dwCount += dwCount;
			return;
	}	}

 short nX, nY;
 for (i = 0; i < DEF_MAXITEMS; i++)
  {	  if ( ( m_pItemList[i] != NULL) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
	  {	  nX = m_pItemList[i]->m_sX;
		  nY = m_pItemList[i]->m_sY;
		  break;
	  }else
	  {  nX = 40;
		  nY = 30;
  }  }

	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] == NULL)
	{	m_pItemList[i] = new class CItem;
		memcpy(m_pItemList[i]->m_cName, cName, 20);
		m_pItemList[i]->m_dwCount      = dwCount;
		//m_pItemList[i]->m_sX           = 40;
		//m_pItemList[i]->m_sY           = 30;
		m_pItemList[i]->m_sX           = nX;
		m_pItemList[i]->m_sY           = nY;
		bSendCommand(MSGID_REQUEST_SETITEMPOS, NULL, i, nX, nY, NULL, NULL);
		m_pItemList[i]->m_cItemType    = cItemType;
		m_pItemList[i]->m_cEquipPos    = cEquipPos;
		m_bIsItemDisabled[i]           = FALSE;
		m_bIsItemEquipped[i]           = FALSE;
		m_pItemList[i]->m_sLevelLimit  = sLevelLimit;
		m_pItemList[i]->m_cGenderLimit = cGenderLimit;
		m_pItemList[i]->m_wCurLifeSpan = wCurLifeSpan;
		m_pItemList[i]->m_wWeight      = wWeight;
		m_pItemList[i]->m_sSprite      = sSprite;
		m_pItemList[i]->m_sSpriteFrame = sSpriteFrame;
		m_pItemList[i]->m_cItemColor   = cItemColor;    // v1.4

		// fixed v1.11
		for (j = 0; j < DEF_MAXITEMS; j++)
		if (m_cItemOrder[j] == -1) {
			m_cItemOrder[j] = i;
			return;
		}

		return;
	}
}

void CGame::NotifyMsg_ItemReleased(char * pData)
{
 char * cp;
 short * sp, sEquipPos, sItemIndex;
 char cTxt[120];

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	sp = (short *)cp;
	sEquipPos = *sp;
	cp += 2;
	sp = (short *)cp;
	sItemIndex = *sp;
	cp += 2;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);
	wsprintf(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
	AddEventList(cTxt, 10);
	m_bIsItemEquipped[sItemIndex] = FALSE;
	m_sItemEquipmentStatus[	m_pItemList[sItemIndex]->m_cEquipPos ] = -1;

	if(memcmp(m_pItemList[sItemIndex]->m_cName, "AngelicPendant", 14) == 0) PlaySound('E', 53, 0);
	else PlaySound('E', 29, 0);
}

void CGame::NotifyMsg_ItemRepaired(char * pData)
{
 char * cp, cTxt[120];
 DWORD * dwp, dwItemID, dwLife;

	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

	dwp = (DWORD *)cp;
	dwItemID = *dwp;
	cp += 4;

	dwp = (DWORD *)cp;
	dwLife = *dwp;
	cp += 4;

	m_pItemList[dwItemID]->m_wCurLifeSpan = (WORD)dwLife;
	m_bIsItemDisabled[dwItemID] = FALSE;
	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName( m_pItemList[dwItemID], cStr1, cStr2, cStr3 );

	wsprintf(cTxt, NOTIFYMSG_ITEMREPAIRED1, cStr1);

	AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_ItemToBank(char *pData)
{
 char * cp, cIndex;
 DWORD * dwp, dwCount, dwAttribute;
 char  cName[21], cItemType, cEquipPos, cGenderLimit, cItemColor;
 BOOL  bIsEquipped;
 short * sp, sSprite, sSpriteFrame, sLevelLimit, sItemEffectValue2, sItemSpecEffectValue2;
 WORD  * wp, wWeight, wCurLifeSpan;
 char  cTxt[120];

	cp = (pData + DEF_INDEX2_MSGTYPE + 2);

	cIndex = *cp;
	cp++;

	cp++;

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;

	dwp = (DWORD *)cp;
	dwCount = *dwp;
	cp += 4;

	cItemType = *cp;
	cp++;

	cEquipPos = *cp;
	cp++;

	bIsEquipped = (BOOL)*cp;
	cp++;

	sp = (short *)cp;
	sLevelLimit = *sp;
	cp += 2;

	cGenderLimit = *cp;
	cp++;

	wp = (WORD *)cp;
	wCurLifeSpan = *wp;
	cp += 2;

	wp = (WORD *)cp;
	wWeight = *wp;
	cp += 2;

	sp = (short *)cp;
	sSprite = *sp;
	cp += 2;

	sp = (short *)cp;
	sSpriteFrame = *sp;
	cp += 2;

	cItemColor = *cp;
	cp++;

	// v1.432
	sp = (short *)cp;
	sItemEffectValue2 = *sp;
	cp += 2;

	dwp = (DWORD *)cp;
	dwAttribute = *dwp;
	cp += 4;
	sItemSpecEffectValue2 = (short) *cp ;
	cp ++ ;

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(cName, dwAttribute, cStr1, cStr2, cStr3);


	if (m_pBankList[cIndex] == NULL) {
		m_pBankList[cIndex] = new class CItem;

		memcpy(m_pBankList[cIndex]->m_cName, cName, 20);
		m_pBankList[cIndex]->m_dwCount = dwCount;

		m_pBankList[cIndex]->m_cItemType = cItemType;
		m_pBankList[cIndex]->m_cEquipPos = cEquipPos;

		m_pBankList[cIndex]->m_sLevelLimit  = sLevelLimit;
		m_pBankList[cIndex]->m_cGenderLimit = cGenderLimit;
		m_pBankList[cIndex]->m_wCurLifeSpan = wCurLifeSpan;
		m_pBankList[cIndex]->m_wWeight      = wWeight;
		m_pBankList[cIndex]->m_sSprite      = sSprite;
		m_pBankList[cIndex]->m_sSpriteFrame = sSpriteFrame;
		m_pBankList[cIndex]->m_cItemColor   = cItemColor;
		m_pBankList[cIndex]->m_sItemEffectValue2  = sItemEffectValue2;
		m_pBankList[cIndex]->m_dwAttribute        = dwAttribute;
		m_pBankList[cIndex]->m_sItemSpecEffectValue2 = sItemSpecEffectValue2 ;

		ZeroMemory(cTxt, sizeof(cTxt));
		if( dwCount == 1 ) wsprintf(cTxt, NOTIFYMSG_ITEMTOBANK3, cStr1);
		else wsprintf(cTxt, NOTIFYMSG_ITEMTOBANK2, dwCount, cStr1);

		if( m_bIsDialogEnabled[14] == TRUE ) m_stDialogBoxInfo[14].sView = DEF_MAXBANKITEMS-12;
		AddEventList(cTxt, 10);
	}
}


void CGame::NotifyMsg_Killed(char * pData)
{ char * cp, cAttackerName[21];
	m_bCommandAvailable = FALSE;
	m_cCommand = DEF_OBJECTSTOP;
	m_iHP = 0;
	m_cCommand = -1;
	// Restart
	m_bItemUsingStatus = FALSE;
	ClearSkillUsingStatus();
	ZeroMemory(cAttackerName, sizeof(cAttackerName));
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	memcpy(cAttackerName, cp, 20);
	cp += 20;
/*	if (strlen(cAttackerName) == 0) // removed in v2.20 (bug?) Many servers send the info themselves.
		AddEventList(NOTIFYMSG_KILLED1, 10);
	else
	{	wsprintf(G_cTxt, NOTIFYMSG_KILLED2, cAttackerName);
		AddEventList(G_cTxt, 10);
	}*/
	// Snoopy: reduced 3 lines -> 2 lines
	AddEventList(NOTIFYMSG_KILLED1, 10);
	AddEventList(NOTIFYMSG_KILLED3, 10);
	//AddEventList(NOTIFYMSG_KILLED4, 10);//"Log Out
}

// This msg is sent by server when lvl-up
void CGame::NotifyMsg_LevelUp(char * pData)
{char * cp;
 int  * ip;
 int i, iPrevLevel;
 char cTxt[120];

	iPrevLevel = m_iLevel;

	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);

	ip  = (int *)cp;
	m_iLevel = *ip;
	cp += 4;

	ip   = (int *)cp;
	m_iStr = *ip;
	cp  += 4;

	ip   = (int *)cp;
	m_iVit = *ip;
	cp  += 4;

	ip   = (int *)cp;
	m_iDex = *ip;
	cp  += 4;

	ip   = (int *)cp;
	m_iInt = *ip;
	cp  += 4;

	ip   = (int *)cp;
	m_iMag = *ip;
	cp  += 4;

	ip   = (int *)cp;
	m_iCharisma = *ip;
	cp  += 4;

	// CLEROTH - LU
	m_iLU_Point = m_iLevel*3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
	m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;

	wsprintf(cTxt, NOTIFYMSG_LEVELUP1, m_iLevel);// "Level up!!! Level %d!"
	AddEventList(cTxt, 10);

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

	_RemoveChatMsgListByObjectID(m_sPlayerObjectID);

	for (i = 1; i < DEF_MAXCHATMSGS; i++)
	if (m_pChatMsgList[i] == NULL) {
		ZeroMemory(cTxt, sizeof(cTxt));
		strcpy(cTxt, "Level up!");
		m_pChatMsgList[i] = new class CMsg(23, cTxt, m_dwCurTime);
		m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;

		if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == FALSE) {
			delete m_pChatMsgList[i];
			m_pChatMsgList[i] = NULL;
		}
		return;
	}
}

// CLEROTH - LU
void CGame::NotifyMsg_SettingSuccess(char * pData)
{char * cp;
 int  * ip;
 int iPrevLevel;
 char cTxt[120];
	iPrevLevel = m_iLevel;
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	ip  = (int *)cp;
	m_iLevel = *ip;
	cp += 4;
	ip   = (int *)cp;
	m_iStr = *ip;
	cp  += 4;
	ip   = (int *)cp;
	m_iVit = *ip;
	cp  += 4;
	ip   = (int *)cp;
	m_iDex = *ip;
	cp  += 4;
	ip   = (int *)cp;
	m_iInt = *ip;
	cp  += 4;
	ip   = (int *)cp;
	m_iMag = *ip;
	cp  += 4;
	ip   = (int *)cp;
	m_iCharisma = *ip;
	cp  += 4;
	wsprintf(cTxt, "Your stat has been changed.");
	AddEventList(cTxt, 10);
	// CLEROTH - LU
	m_iLU_Point = m_iLevel*3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
	m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
}

void CGame::NotifyMsg_MagicEffectOff(char * pData)
{char * cp;
 WORD * wp;
 short  sMagicType, sMagicEffect;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	sMagicType = (short)*wp;
	cp += 2;
	wp = (WORD *)cp;
	sMagicEffect = (short)*wp;
	cp += 2;
	switch (sMagicType) {
	case DEF_MAGICTYPE_PROTECT:
		switch (sMagicEffect) {
		case 1: // "Protection from arrows has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF1, 10);
			break;
		case 2:	// "Protection from magic has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF2, 10);
			break;
		case 3:	// "Defense shield effect has vanished."
		case 4:	// "Defense shield effect has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF3, 10);
			break;
		case 5:	// "Absolute Magic Protection has been vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF14, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_HOLDOBJECT:
		switch (sMagicEffect) {
		case 1:	// "Hold person magic effect has vanished."
			m_bParalyze = FALSE;
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF4, 10);
			break;

		case 2:	// "Paralysis magic effect has vanished."
			m_bParalyze = FALSE;
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF5, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_INVISIBILITY:
		switch (sMagicEffect) {
		case 1:	// "Invisibility magic effect has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF6, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_CONFUSE:
		switch (sMagicEffect) {
		case 1:	// "Language confuse magic effect has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF7, 10);
			break;
		case 2:	// "Confusion magic has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF8, 10);
			m_bIsConfusion = FALSE;
			break;
		case 3:	// "Illusion magic has vanished."
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF9, 10);
			m_iIlusionOwnerH = NULL;
			break;
		case 4:	// "At last, you gather your senses." // snoopy
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF15, 10);
			m_bIllusionMVT = FALSE;
			break;
		}
		break;

	case DEF_MAGICTYPE_POISON:
		if (m_bIsPoisoned) AddEventList(NOTIFYMSG_MAGICEFFECT_OFF10, 10);
		m_bIsPoisoned = FALSE;
		break;

	case DEF_MAGICTYPE_BERSERK:
		switch (sMagicEffect) {
		case 1:
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF11, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_POLYMORPH:
		switch (sMagicEffect) {
		case 1:
			AddEventList(NOTIFYMSG_MAGICEFFECT_OFF12, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_ICE:
		AddEventList(NOTIFYMSG_MAGICEFFECT_OFF13, 10);
		break;
	}
}

void CGame::NotifyMsg_MagicEffectOn(char * pData)
{char * cp;
 DWORD * dwp;
 WORD * wp;
 short  sMagicType, sMagicEffect, sOwnerH;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	sMagicType = (short)*wp;
	cp += 2;
	dwp = (DWORD *)cp;
	sMagicEffect = (short)*dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	sOwnerH = (short)*dwp;
	cp += 4;
	switch (sMagicType) {
	case DEF_MAGICTYPE_PROTECT:
		switch (sMagicEffect) {
		case 1: // "You are completely protected from arrows!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON1, 10);
			break;
		case 2: // "You are protected from magic!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON2, 10);
			break;
		case 3: // "Defense ratio increased by a magic shield!"
		case 4: // "Defense ratio increased by a magic shield!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON3, 10);
			break;
		case 5: // "You are completely protected from magic!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON14, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_HOLDOBJECT:
		switch (sMagicEffect) {
		case 1: // "You were bounded by a Hold Person spell! Unable to move!"
			m_bParalyze = TRUE;
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON4, 10);
			break;
		case 2: // "You were bounded by a Paralysis spell! Unable to move!"
			m_bParalyze = TRUE;
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON5, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_INVISIBILITY:
		switch (sMagicEffect) {
		case 1: // "You are now invisible, no one can see you!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON6, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_CONFUSE:
		switch (sMagicEffect) {
		case 1:	// Confuse Language "No one understands you because of language confusion magic!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON7, 10);
			break;

		case 2: // Confusion "Confusion magic casted, impossible to determine player allegience."
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON8, 10);
			m_bIsConfusion = TRUE;
			break;

		case 3:	// Illusion "Illusion magic casted, impossible to tell who is who!"
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON9, 10);
			_SetIlusionEffect(sOwnerH);
			break;

		case 4:	// IllusionMouvement "You are thrown into confusion, and you are flustered yourself." // snoopy
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON15, 10);
			m_bIllusionMVT = TRUE;
			break;
		}
		break;

	case DEF_MAGICTYPE_POISON:
		AddEventList(NOTIFYMSG_MAGICEFFECT_ON10, 10);
		m_bIsPoisoned = TRUE;
		break;

	case DEF_MAGICTYPE_BERSERK:
		switch (sMagicEffect) {
		case 1:
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON11, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_POLYMORPH:
		switch (sMagicEffect) {
		case 1:
			AddEventList(NOTIFYMSG_MAGICEFFECT_ON12, 10);
			break;
		}
		break;

	case DEF_MAGICTYPE_ICE:
		AddEventList(NOTIFYMSG_MAGICEFFECT_ON13, 10);
		break;
	}
}

void CGame::NotifyMsg_MagicStudyFail(char * pData)
{
 char * cp, cMagicNum, cName[31], cFailCode;
 char cTxt[120];
 int  * ip, iCost, iReqInt;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	cFailCode = *cp;
	cp++;
	cMagicNum = *cp;
	cp++;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 30);
	cp += 30;
	ip = (int *)cp;
	iCost = *ip;
	cp += 4;
	ip = (int *)cp;
	iReqInt = *ip;
	cp += 4;
/*	// Snoopy: remove special CLEROTH's feature
	ip = (int *)cp;
	iReqStr = *ip;
	cp += 4;
	// CLEROTH
	wsprintf(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL4, cName, iCost, iReqInt, iReqStr);
	AddEventList(cTxt, 10);*/

	if (iCost > 0)
	{	wsprintf(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL1, cName);
		AddEventList(cTxt, 10);
	}else
	{	wsprintf(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL2,  cName);
		AddEventList(cTxt, 10);
		wsprintf(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL3, iReqInt);
		AddEventList(cTxt, 10);
	}
}

void CGame::NotifyMsg_MagicStudySuccess(char * pData)
{char * cp, cMagicNum, cName[31];
 char cTxt[120];
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	cMagicNum = *cp;
	cp++;
	m_cMagicMastery[cMagicNum] = 1;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 30);
	wsprintf(cTxt, NOTIFYMSG_MAGICSTUDY_SUCCESS1, cName);
	AddEventList(cTxt, 10);
	PlaySound('E', 23, 0);
}

void CGame::NotifyMsg_MP(char * pData)
{DWORD * dwp;
 int iPrevMP;
 char cTxt[120];
	iPrevMP = m_iMP;
	dwp = (DWORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
	m_iMP = (int)*dwp;
	if (abs(m_iMP - iPrevMP) < 10) return;
	if (m_iMP > iPrevMP)
	{	wsprintf(cTxt, NOTIFYMSG_MP_UP, m_iMP - iPrevMP);//"MP°
		AddEventList(cTxt, 10);
		PlaySound('E', 21, 0);
	}else
	{	wsprintf(cTxt, NOTIFYMSG_MP_DOWN, iPrevMP - m_iMP);//"MP°
		AddEventList(cTxt, 10);
	}
}

void CGame::NotifyMsg_NewGuildsMan(char * pData)
{char * cp, cName[12], cTxt[120];
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	wsprintf(cTxt, NOTIFYMSG_NEW_GUILDMAN1, cName);
	AddEventList(cTxt, 10);
	ClearGuildNameList();
}

void CGame::NotifyMsg_PKcaptured(char *pData)
{char  * cp;
 DWORD * dwp;
 WORD  * wp;
 int     iPKcount, iLevel, iExp, iRewardGold;
 char cTxt[120], cName[12];
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	iPKcount = *wp;
	cp += 2;
	wp = (WORD *)cp;
	iLevel = *wp;
	cp += 2;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	cp += 10;
	dwp = (DWORD *)cp;
	iRewardGold = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iExp = *dwp;
	cp += 4;
	wsprintf(cTxt, NOTIFYMSG_PK_CAPTURED1, iLevel, cName, iPKcount);
	AddEventList(cTxt, 10);
	wsprintf(cTxt, EXP_INCREASED, iExp - m_iExp);
	AddEventList(cTxt, 10);
	wsprintf(cTxt, NOTIFYMSG_PK_CAPTURED3, iExp - m_iExp);
	AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_PKpenalty(char *pData)
{char  * cp;
 DWORD * dwp;
 int     iPKcount, iExp, iStr, iVit, iDex, iInt, iMag, iChr;
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	dwp = (DWORD *)cp;
	iExp = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iStr = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iVit = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iDex = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iInt = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iMag = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iChr = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
	iPKcount = *dwp;
	cp += 4;
	wsprintf(G_cTxt, NOTIFYMSG_PK_PENALTY1, iPKcount);
	AddEventList(G_cTxt, 10);
	if (m_iExp > iExp)
	{	wsprintf(G_cTxt, NOTIFYMSG_PK_PENALTY2, m_iExp - iExp);
		AddEventList(G_cTxt, 10);
	}
	m_iExp = iExp;
	m_iStr = iStr;
	m_iVit = iVit;
	m_iDex = iDex;
	m_iInt = iInt;
	m_iMag = iMag;
	m_iCharisma = iChr;
	m_iPKCount = iPKcount;
}

void CGame::NotifyMsg_PlayerShutUp(char * pData)
{char * cp, cName[12];
 WORD * wp, wTime;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wTime = *wp;
	cp += 2;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	cp += 10;
	if (memcmp(m_cPlayerName, cName, 10) == 0)
		 wsprintf(G_cTxt, NOTIFYMSG_PLAYER_SHUTUP1, wTime);
	else wsprintf(G_cTxt, NOTIFYMSG_PLAYER_SHUTUP2, cName, wTime);

	AddEventList(G_cTxt, 10);
}

void CGame::NotifyMsg_PlayerStatus(BOOL bOnGame, char * pData)
{char cName[12], cMapName[12], * cp;
 WORD * wp ;
 WORD  dx= 1 ,dy = 1;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	cp += 10;
	ZeroMemory(cMapName, sizeof(cMapName));
	memcpy(cMapName, cp, 10);
	cp += 10;
	wp = (WORD * ) cp ;
	dx = (WORD ) *wp ;
	cp += 2 ;
	wp = (WORD * ) cp ;
	dy = (WORD ) *wp ;
	cp += 2 ;
	ZeroMemory(G_cTxt, sizeof(G_cTxt));
	if (bOnGame == TRUE) {
		if (strlen(cMapName) == 0)
			 wsprintf(G_cTxt, NOTIFYMSG_PLAYER_STATUS1, cName);
		else wsprintf(G_cTxt, NOTIFYMSG_PLAYER_STATUS2, cName, cMapName, dx, dy);
	}
	else wsprintf(G_cTxt, NOTIFYMSG_PLAYER_STATUS3, cName);
	AddEventList(G_cTxt, 10);
}


void CGame::NotifyMsg_QuestReward(char *pData)
{short * sp, sWho, sFlag;
 char  * cp, cRewardName[21], cTxt[120];
 int   * ip, iAmount, iIndex, iPreCon;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	sp = (short *)cp;
	sWho = *sp;
	cp += 2;
	sp = (short *)cp;
	sFlag = *sp;
	cp += 2;
	ip = (int *)cp;
	iAmount = *ip;
	cp += 4;
	ZeroMemory(cRewardName, sizeof(cRewardName));
	memcpy(cRewardName, cp, 20);
	cp += 20;
	iPreCon = m_iContribution;
	ip = (int *)cp;
	m_iContribution = *ip;
//	m_iContributionPrice = 0;
	cp += 4;

	if (sFlag == 1)
	{	m_stQuest.sWho          = NULL;
		m_stQuest.sQuestType    = NULL;
		m_stQuest.sContribution = NULL;
		m_stQuest.sTargetType   = NULL;
		m_stQuest.sTargetCount  = NULL;
		m_stQuest.sX     = NULL;
		m_stQuest.sY     = NULL;
		m_stQuest.sRange = NULL;
		m_stQuest.sCurrentCount = NULL;
		m_stQuest.bIsQuestCompleted = FALSE;
		ZeroMemory(m_stQuest.cTargetName, sizeof(m_stQuest.cTargetName));
		EnableDialogBox(21, 0, sWho+110, 0);
		iIndex = m_stDialogBoxInfo[21].sV1;
		m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
		iIndex++;
		ZeroMemory(cTxt, sizeof(cTxt));
		if (memcmp(cRewardName, "°æÇèÄ¡", 6) == 0)
		{	if (iAmount > 0) wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD1, iAmount);
		}else
		{	wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD2, iAmount, cRewardName);
		}
		m_pMsgTextList2[iIndex] = new class CMsg(NULL, cTxt, NULL);
		iIndex++;
		m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
		iIndex++;
		ZeroMemory(cTxt, sizeof(cTxt));
		if (iPreCon < m_iContribution)
			 wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD3, m_iContribution - iPreCon);
		else wsprintf(cTxt, NOTIFYMSG_QUEST_REWARD4, iPreCon - m_iContribution);

		m_pMsgTextList2[iIndex] = new class CMsg(NULL, "  ", NULL);
		iIndex++;
	}
	else EnableDialogBox(21, 0, sWho+120, 0);
}

void CGame::NotifyMsg_RatingPlayer(char * pData)
{//int * ip;
 char * cp, cName[12];
 WORD  cValue;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	cValue = *cp;
	cp++;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	cp += 10;
//	ip = (int *)cp;
//	m_iRating = *ip;
	cp += 4;
	ZeroMemory(G_cTxt, sizeof(G_cTxt));
	if (memcmp(m_cPlayerName, cName, 10) == 0)
	{	if (cValue == 1)
		{	 strcpy(G_cTxt, NOTIFYMSG_RATING_PLAYER1);
			 PlaySound('E', 23, 0);
 		}
	}else
	{	if (cValue == 1)
			 wsprintf(G_cTxt, NOTIFYMSG_RATING_PLAYER2, cName);
		else wsprintf(G_cTxt, NOTIFYMSG_RATING_PLAYER3, cName);
	}
	AddEventList(G_cTxt, 10);
}


void CGame::NotifyMsg_ServerChange(char * pData)
{
 char * cp, cWorldServerAddr[16];	//Snoopy: change names for better readability
 int * ip, iWorldServerPort;		//Snoopy: change names for better readability

	ZeroMemory(m_cMapName, sizeof(m_cMapName));
	ZeroMemory(m_cMapMessage, sizeof(m_cMapMessage));
	ZeroMemory(cWorldServerAddr, sizeof(cWorldServerAddr));

	// v1.43
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(m_cMapName, cp, 10);

//	m_cMapIndex = GetOfficialMapName(m_cMapName, m_cMapMessage);
	cp += 10;

	memcpy(cWorldServerAddr, cp, 15);
	cp += 15;
	ip = (int *)cp;
	iWorldServerPort = *ip;
	cp += 4;
	if (m_pGSock != NULL)
	{	delete m_pGSock;
		m_pGSock = NULL;
	}
	if (m_pLSock != NULL)
	{	delete m_pLSock;
		m_pLSock = NULL;
	}
	m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
	if (m_iGameServerMode == 1) // LAN
	{	m_pLSock->bConnect(m_cLogServerAddr, iWorldServerPort, WM_USER_LOGSOCKETEVENT);
	}else
	{	m_pLSock->bConnect(cWorldServerAddr, iWorldServerPort, WM_USER_LOGSOCKETEVENT);
	}
	m_pLSock->bInitBufferSize(30000);

	m_bIsPoisoned = FALSE;

	ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
	m_dwConnectMode  = MSGID_REQUEST_ENTERGAME;
	//m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW; //Gateway
	m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW_TOWLSBUTMLS;
	ZeroMemory(m_cMsg, sizeof(m_cMsg));
	strcpy(m_cMsg,"55");
}

void CGame::NotifyMsg_SetItemCount(char * pData)
{char  * cp;
 WORD  * wp;
 DWORD * dwp;
 short  sItemIndex;
 DWORD  dwCount;
 BOOL   bIsItemUseResponse;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	sItemIndex = *wp;
	cp += 2;
	dwp = (DWORD *)cp;
	dwCount = *dwp;
	cp += 4;
	bIsItemUseResponse = (BOOL)*cp;
	cp++;
	if (m_pItemList[sItemIndex] != NULL)
	{	m_pItemList[sItemIndex]->m_dwCount = dwCount;
		if (bIsItemUseResponse == TRUE) m_bIsItemDisabled[sItemIndex] = FALSE;
	}
}

void CGame::NotifyMsg_ShowMap(char * pData)
{char * cp;
 WORD * wp, w1, w2;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	w1 = *wp;
	cp += 2;
	wp = (WORD *)cp;
	w2 = *wp;
	cp += 2;
	if (w2 == 0) AddEventList(NOTIFYMSG_SHOW_MAP1, 10);
	else EnableDialogBox(22, NULL, w1, w2 -1);
}

void CGame::NotifyMsg_Skill(char *pData)
{ WORD * wp;
 short sSkillIndex, sValue;
 char * cp;
 char cTxt[120];
 int i;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	sSkillIndex = (short)*wp;
	cp += 2;
	wp = (WORD *)cp;
	sValue = (short)*wp;
	cp += 2;
	_RemoveChatMsgListByObjectID(m_sPlayerObjectID);
	if (m_pSkillCfgList[sSkillIndex]->m_iLevel < sValue)
	{	wsprintf(cTxt, NOTIFYMSG_SKILL1, m_pSkillCfgList[sSkillIndex]->m_cName, sValue - m_pSkillCfgList[sSkillIndex]->m_iLevel);
		AddEventList(cTxt, 10);
		PlaySound('E', 23, 0);
		for (i = 1; i < DEF_MAXCHATMSGS; i++)
		if (m_pChatMsgList[i] == NULL)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, "%s +%d%%", m_pSkillCfgList[sSkillIndex]->m_cName, sValue - m_pSkillCfgList[sSkillIndex]->m_iLevel);
			m_pChatMsgList[i] = new class CMsg(20, cTxt, m_dwCurTime);
			m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;
			if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == FALSE)
			{	delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
			break;
		}
	}else if (m_pSkillCfgList[sSkillIndex]->m_iLevel > sValue) {
		wsprintf(cTxt, NOTIFYMSG_SKILL2, m_pSkillCfgList[sSkillIndex]->m_cName, m_pSkillCfgList[sSkillIndex]->m_iLevel - sValue);
		AddEventList(cTxt, 10);
		PlaySound('E', 24, 0);
		for (i = 1; i < DEF_MAXCHATMSGS; i++)
		if (m_pChatMsgList[i] == NULL)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, "%s -%d%%", m_pSkillCfgList[sSkillIndex]->m_cName, sValue - m_pSkillCfgList[sSkillIndex]->m_iLevel);
			m_pChatMsgList[i] = new class CMsg(20, cTxt, m_dwCurTime);
			m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;
			if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == FALSE)
			{	delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
			break;
	}	}
	m_pSkillCfgList[sSkillIndex]->m_iLevel = sValue;
	m_cSkillMastery[sSkillIndex] = (unsigned char)sValue;
}


void CGame::NotifyMsg_SkillTrainSuccess(char * pData)
{char * cp, cSkillNum, cSkillLevel;
 char cTemp[120];
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	cSkillNum = *cp;
	cp++;
	cSkillLevel = *cp;
	cp++;
	ZeroMemory(cTemp, sizeof(cTemp));
	wsprintf(cTemp, NOTIFYMSG_SKILL_TRAIN_SUCCESS1, m_pSkillCfgList[cSkillNum]->m_cName, cSkillLevel);
	AddEventList(cTemp, 10);
	m_pSkillCfgList[cSkillNum]->m_iLevel = cSkillLevel;
	m_cSkillMastery[cSkillNum] = (unsigned char)cSkillLevel;
	PlaySound('E', 23, 0);
}

void CGame::NotifyMsg_SkillUsingEnd(char * pData)
{char * cp;
 WORD * wp, wResult;
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wResult = * wp;
	switch (wResult) {
	case NULL:
		AddEventList(NOTIFYMSG_SKILL_USINGEND1, 10);
		break;
	case 1:
		AddEventList(NOTIFYMSG_SKILL_USINGEND2, 10);
		break;
	}
	m_bSkillUsingStatus = FALSE;
}

void CGame::NotifyMsg_SP(char * pData)
{DWORD * dwp;
 int iPrevSP;
	iPrevSP = m_iSP;
	dwp = (DWORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
	m_iSP = (int)*dwp;
	if (abs(m_iSP - iPrevSP) < 10) return;
	if (m_iSP > iPrevSP)
	{	wsprintf(G_cTxt, NOTIFYMSG_SP_UP, m_iSP - iPrevSP);
		AddEventList(G_cTxt, 10);
		PlaySound('E', 21, 0);
	}else
	{	wsprintf(G_cTxt, NOTIFYMSG_SP_DOWN, iPrevSP - m_iSP);
		AddEventList(G_cTxt, 10);
	}
}

void CGame::NotifyMsg_TotalUsers(char * pData)
{	WORD *wp;
	int iTotal;
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
	iTotal = (int)*wp;
	wsprintf(G_cTxt, NOTIFYMSG_TOTAL_USER1, iTotal);
	AddEventList(G_cTxt, 10);
}

void CGame::NotifyMsg_WhisperMode(BOOL bActive, char * pData)
{
	char cName[12], *cp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	if (bActive == TRUE)
	{
		wsprintf(G_cTxt, NOTIFYMSG_WHISPERMODE1, cName);
		if (m_pWhisperMsg[DEF_MAXWHISPERMSG - 1] != NULL) {
			delete m_pWhisperMsg[DEF_MAXWHISPERMSG - 1];
			m_pWhisperMsg[DEF_MAXWHISPERMSG - 1] = NULL;
		}
		for (int i = DEF_MAXWHISPERMSG - 2; i >= 0; i--) {
			m_pWhisperMsg[i+1] = m_pWhisperMsg[i];
			m_pWhisperMsg[i] = NULL;
		}
		m_pWhisperMsg[0] = new class CMsg(NULL, cName, NULL);
		m_cWhisperIndex = 0;
	}
	else wsprintf(G_cTxt, NOTIFYMSG_WHISPERMODE2, cName);

	AddEventList(G_cTxt, 10);
}

void CGame::DrawDialogBox_CrusadeJob(short msX, short msY)
{short sX, sY;

	sX = m_stDialogBoxInfo[33].sX;
	sY = m_stDialogBoxInfo[33].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);

	switch (m_stDialogBoxInfo[33].cMode) {
	case 1:
		PutAlignedString(sX +24, sX +246, sY +45+20, DRAWDIALOGBOX_CRUSADEJOB1);
		PutAlignedString(sX +24, sX +246, sY +60+20, DRAWDIALOGBOX_CRUSADEJOB2);
		PutAlignedString(sX +24, sX +246, sY +75+20, DRAWDIALOGBOX_CRUSADEJOB3);
		PutAlignedString(sX +24, sX +246, sY +90+20, DRAWDIALOGBOX_CRUSADEJOB4);

		if( m_bCitizen == TRUE )
		{	if( m_bAresden )
			{	if (m_iGuildRank == 0)
				{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
						 PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB5, 255,255,255);//(Commander)"
 					else PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB5, 4,0,50);//(Commander)"
				}else
				{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
						 PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB7, 255,255,255);//(Soldier)"
 					else PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB7, 4,0,50);//(Soldier)"
					if (m_iGuildRank != -1)
					{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
							 PutAlignedString(sX +24, sX +246, sY+175, DRAWDIALOGBOX_CRUSADEJOB9, 255,255,255);//(Constructor)"
 						else PutAlignedString(sX +24, sX +246, sY+175, DRAWDIALOGBOX_CRUSADEJOB9, 4,0,50);//(Constructor)"

				}	}
			}else if( m_bAresden == FALSE )
			{	if (m_iGuildRank == 0)
				{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
						 PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB5, 255,255,255);//(Commander)"
 					else PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB5, 4,0,50);//(Commander)"
				}else
				{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
						 PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB7, 255,255,255);//(Soldier)"
 					else PutAlignedString(sX +24, sX +246, sY+150, DRAWDIALOGBOX_CRUSADEJOB7, 4,0,50);//(Soldier)"
					if (m_iGuildRank != -1)
					{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
							 PutAlignedString(sX +24, sX +246, sY+175, DRAWDIALOGBOX_CRUSADEJOB9, 255,255,255);//(Constructor)"
 						else PutAlignedString(sX +24, sX +246, sY+175, DRAWDIALOGBOX_CRUSADEJOB9, 4,0,50);//(Constructor)"
		}	}	}	}

		PutAlignedString(sX +24, sX +246, sY +290 -40,   DRAWDIALOGBOX_CRUSADEJOB10);
		PutAlignedString(sX +24, sX +246, sY +305 -40,   DRAWDIALOGBOX_CRUSADEJOB17);

		if ((msX > sX + 210) && (msX < sX + 260) && (msY >= sY + 296) && (msY <= sY + 316))
			 PutString_SprFont(sX +50+160, sY +296, "Help", 6,6,20);
		else PutString_SprFont(sX +50+160, sY +296, "Help", 0, 0, 7);
		break;

	case 2:
		PutAlignedString(sX +24, sX +246, sY +90+20, DRAWDIALOGBOX_CRUSADEJOB18);
		switch (m_iCrusadeDuty) {
		case 1: PutAlignedString(sX +24, sX +246, sY+125, DRAWDIALOGBOX_CRUSADEJOB19); break;//"(Soldier)
		case 2: PutAlignedString(sX +24, sX +246, sY+125, DRAWDIALOGBOX_CRUSADEJOB20); break;//"(Constructor)
		case 3: PutAlignedString(sX +24, sX +246, sY+125, DRAWDIALOGBOX_CRUSADEJOB21); break;//"(Commander)
		}

		PutAlignedString(sX +24, sX +246, sY +145, DRAWDIALOGBOX_CRUSADEJOB22);
		if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 160) && (msY < sY + 175))
			 PutAlignedString(sX +24, sX +246, sY+160, DRAWDIALOGBOX_CRUSADEJOB23, 255,255,255);
 		else PutAlignedString(sX +24, sX +246, sY+160, DRAWDIALOGBOX_CRUSADEJOB23, 4,0,50);

		PutAlignedString(sX +24, sX +246, sY +175, DRAWDIALOGBOX_CRUSADEJOB25);
		PutAlignedString(sX +24, sX +246, sY +190, DRAWDIALOGBOX_CRUSADEJOB26);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	}
}

void CGame::_Draw_OnLogin(char *pAccount, char *pPassword, int msX, int msY, int iFrame)
{
 BOOL bFlag = TRUE;
 DWORD dwTime = timeGetTime();

    m_DDraw.ClearBackB4();

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 0,0,0, TRUE);
	DrawVersion();

	if ((iFrame >= 15) && (iFrame <= 20)) m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->PutTransSprite25(39,121, 2, TRUE);
	else if (iFrame > 20) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 39,121, 2, TRUE);

	if (m_cCurFocus != 1) {
		if (m_Misc.bCheckValidName(pAccount) != FALSE)
			 PutString2(180, 162, pAccount, 200,200,200);
		else PutString2(180, 162, pAccount, 200,100,100);
	}
	if ((m_Misc.bCheckValidName(pAccount) == FALSE) || (strlen(pAccount) == 0)) bFlag = FALSE;

	if (m_cCurFocus != 2) {
		if ((m_Misc.bCheckValidString(pPassword) != FALSE))
			 PutString(180, 185, pPassword, RGB(200,200,200), TRUE, 1);
		else PutString(180, 185, pPassword, RGB(200,100,100), TRUE, 1);
	}
	if ((m_Misc.bCheckValidString(pPassword) == FALSE) || (strlen(pPassword) == 0)) bFlag = FALSE;

	if (m_cCurFocus == 1)
		ShowReceivedString();
	else
	if (m_cCurFocus == 2)
		ShowReceivedString(TRUE);

	if (bFlag == TRUE)
	{	if (m_cCurFocus == 3) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 80,282, 3, TRUE);
	}
	if (m_cCurFocus == 4) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 256,282,4, TRUE);
	if ((m_bIsHideLocalCursor != TRUE) && (msX != 0) && (msY != 0)) {
	m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
	}
}

void CGame::ShowEventList(DWORD dwTime)
{ int i;

	m_DDraw._GetBackBufferDC();
	for (i = 0; i < 6; i++)
	if ((dwTime - m_stEventHistory[i].dwTime) < 5000)
	{	switch (m_stEventHistory[i].cColor) {
		case 0:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(225,225,225), FALSE, 1, TRUE);
			break;
		case 1:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(130,255,130), FALSE, 1, TRUE);
			break;
		case 2:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(255,130,130), FALSE, 1, TRUE);
			break;
		case 3:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(130,130,255), FALSE, 1, TRUE);
			break;
		case 4:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(230, 230, 130), FALSE, 1, TRUE);
			break;
		case 10:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(180,255,180), FALSE, 1, TRUE);
			break;
		case 20:
			PutString(10, 10 + i*15, m_stEventHistory[i].cTxt, RGB(150,150,170), FALSE, 1, TRUE);
			break;
		}
	}

	for (i = 0; i < 6; i++)
	if ((dwTime - m_stEventHistory2[i].dwTime) < 5000)
	{	switch (m_stEventHistory2[i].cColor) {
		case 0:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(225,225,225), FALSE, 1, TRUE);
			break;
		case 1:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(130,255,130), FALSE, 1, TRUE);
			break;
		case 2:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(255,130,130), FALSE, 1, TRUE);
			break;
		case 3:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(130,130,255), FALSE, 1, TRUE);
			break;
		case 4:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(230, 230, 130), FALSE, 1, TRUE);
			break;
		case 10:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(180,255,180), FALSE, 1, TRUE);
			break;
		case 20:
			PutString(10, 322 + i*15, m_stEventHistory2[i].cTxt, RGB(150,150,170), FALSE, 1, TRUE);
			break;
	}	}
	if (m_bSkillUsingStatus	== TRUE)
	{	PutString(280 -29, 280 -52, SHOW_EVENT_LIST1, RGB(235,235,235), FALSE, 1, TRUE);
	}
	m_DDraw._ReleaseBackBufferDC();
}

void CGame::RequestTeleportAndWaitData()
{	// Snoopy: removed that, Noob Dungeon is now at farm...
	/*if (strcmp(m_cMapName, "aresden") == 0)
	{	if ( ((m_sPlayerX == 188) && (m_sPlayerY == 105))  ||
			 ((m_sPlayerX == 187) && (m_sPlayerY == 105))  ||
			 ((m_sPlayerX == 187) && (m_sPlayerY == 106))  ||
			 ((m_sPlayerX == 186) && (m_sPlayerY == 106))  ||
			 ((m_sPlayerX == 186) && (m_sPlayerY == 107))  )
		{	if ( (m_iLevel < 30) || (m_iLevel>80) )
			{	AddEventList(REQUEST_TELEPORT_AND_WAIT_DATA1, 10);
				return;
	}	}	}
	if (strcmp(m_cMapName, "elvine") == 0)
	{	if ( ((m_sPlayerX == 218) && (m_sPlayerY == 109))  ||
			 ((m_sPlayerX == 217) && (m_sPlayerY == 109))  ||
			 ((m_sPlayerX == 217) && (m_sPlayerY == 110))  ||
			 ((m_sPlayerX == 216) && (m_sPlayerY == 110))  ||
			 ((m_sPlayerX == 216) && (m_sPlayerY == 111))  )
		{	if ( (m_iLevel < 30) || (m_iLevel>80) )
			{	AddEventList(REQUEST_TELEPORT_AND_WAIT_DATA1, 10);
				return;
	}	}	}*/
	bSendCommand(MSGID_REQUEST_TELEPORT, NULL, NULL, NULL, NULL, NULL, NULL);
	ChangeGameMode(DEF_GAMEMODE_ONWAITINGINITDATA);
}

void CGame::InitDataResponseHandler(char * pData)
{
 int * ip, i;
 short * sp, sX, sY;
 char  * cp, cMapFileName[32], cTxt[120], cPreCurLocation[12];
 BOOL  bIsObserverMode;
 HANDLE hFile;
 DWORD  dwFileSize;

	ZeroMemory( cPreCurLocation, sizeof(cPreCurLocation) );
	m_bParalyze = FALSE;
	m_pMapData->Init();

	m_sMonsterID = 0;
	m_dwMonsterEventTime = 0;

	DisableDialogBox(7);
	DisableDialogBox(11);
	DisableDialogBox(13);
	DisableDialogBox(14);
	DisableDialogBox(16);
	DisableDialogBox(22);
	DisableDialogBox(20);
	DisableDialogBox(21);
	DisableDialogBox(23);
	DisableDialogBox(51); // Gail's diag

	m_cCommand = DEF_OBJECTSTOP;
	//m_bCommandAvailable = TRUE;
	m_cCommandCount = 0;
	m_bIsGetPointingMode = FALSE;
	m_iPointCommandType  = -1;
	m_iIlusionOwnerH = NULL;
	m_cIlusionOwnerType = NULL;
	m_bIsTeleportRequested = FALSE;
	m_bIsConfusion = FALSE;
	m_bSkillUsingStatus = FALSE;

	m_bItemUsingStatus = FALSE ;

	m_cRestartCount = -1;
	m_dwRestartCountTime = NULL;

	for (i = 0; i < DEF_MAXEFFECTS; i++)
	{	if (m_pEffectList[i] != NULL) delete m_pEffectList[i];
		m_pEffectList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXWHETHEROBJECTS; i++)
	{	m_stWhetherObject[i].sX    = 0;
		m_stWhetherObject[i].sBX   = 0;
		m_stWhetherObject[i].sY    = 0;
		m_stWhetherObject[i].cStep = 0;
	}

	for (i = 0; i < DEF_MAXGUILDNAMES; i++)
	{	m_stGuildName[i].dwRefTime = 0;
		m_stGuildName[i].iGuildRank = -1;
		ZeroMemory(m_stGuildName[i].cCharName, sizeof(m_stGuildName[i].cCharName));
		ZeroMemory(m_stGuildName[i].cGuildName, sizeof(m_stGuildName[i].cGuildName));
	}

	for (i = 0; i < DEF_MAXCHATMSGS; i++) {
		if (m_pChatMsgList[i] != NULL) delete m_pChatMsgList[i];
		m_pChatMsgList[i] = NULL;
	}

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	// PlayerObjectID
	sp = (short *)cp;
	m_sPlayerObjectID = *sp;
	cp += 2;

	sp = (short *)cp;
	sX = *sp;
	cp += 2;

	sp = (short *)cp;
	sY = *sp;
	cp += 2;

	sp = (short *)cp;
	m_sPlayerType = *sp;
	cp += 2;

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

	ip = (int *)cp; // v1.4
	m_iPlayerApprColor = *ip;
	cp += 4;

	// CLEROTH - BLACK FIX
	ip = (int *)cp;
	m_iPlayerStatus = *ip;
	cp += 4;

	//Snoopy MIM fix
	if ((m_iPlayerStatus & 0x00200000) == 0x00200000)
	{	m_bIllusionMVT = TRUE;
	}else
	{	m_bIllusionMVT = FALSE;
	}
	ZeroMemory(m_cMapName, sizeof(m_cMapName));
	ZeroMemory(m_cMapMessage, sizeof(m_cMapMessage));
	memcpy(m_cMapName, cp, 10);
	m_cMapIndex = GetOfficialMapName(m_cMapName, m_cMapMessage);
	if( m_cMapIndex < 0 )
	{	m_stDialogBoxInfo[9].sSizeX = -1;
		m_stDialogBoxInfo[9].sSizeY = -1;
	}else
	{	m_stDialogBoxInfo[9].sSizeX = 128;
		m_stDialogBoxInfo[9].sSizeY = 128;
	}
	cp += 10;

	strcpy( cPreCurLocation, m_cCurLocation );
	ZeroMemory(m_cCurLocation, sizeof(m_cCurLocation));
	memcpy(m_cCurLocation, cp, 10);
	cp += 10;

	G_cSpriteAlphaDegree = *cp;
	cp++;

	m_cWhetherStatus = *cp;
	cp++;
	switch (G_cSpriteAlphaDegree) { //Snoopy:  Xmas bulbs
	// Will be sent by server if DayTime is 3 (and a snowy weather)
	case 1:	m_bIsXmas = FALSE; break;
	case 2: m_bIsXmas = FALSE; break;
	case 3: // Snoopy Special night with chrismas bulbs
		if (m_cWhetherStatus >3) m_bIsXmas = TRUE;
		else m_bIsXmas = FALSE;
		G_cSpriteAlphaDegree = 2;
		break;
	}
	ip = (int *)cp;
	m_iContribution = *ip;
//	m_iContributionPrice = 0;
	cp += 4;
	bIsObserverMode = (BOOL)*cp;
	cp++;
	ip = (int *)cp;
//	m_iRating = *ip;
	cp += 4;
	ip = (int *)cp;
	m_iHP = *ip;
	cp += 4;
    m_cDiscount = (char )*cp;
    cp++;

	if (m_cWhetherStatus != NULL)
		 SetWhetherStatus(TRUE, m_cWhetherStatus);
	else SetWhetherStatus(FALSE, m_cWhetherStatus);

	ZeroMemory(cMapFileName, sizeof(cMapFileName));
	strcat(cMapFileName, "mapdata\\");
	// CLEROTH - MW MAPS
	if(memcmp(m_cMapName,"defaultmw", 9)==0)
	{	strcat(cMapFileName, "mw\\defaultmw");
	}else
	{	strcat(cMapFileName, m_cMapName);
	}

	strcat(cMapFileName, ".amd");
	m_pMapData->OpenMapDataFile(cMapFileName);

	m_pMapData->m_sPivotX = sX;
	m_pMapData->m_sPivotY = sY;

	m_sPlayerX   = sX + 14 + 5;
	m_sPlayerY   = sY + 12 + 5;

	m_cPlayerDir = 5;

	if (bIsObserverMode == FALSE)
	{	m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
							                  m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, // v1.4
											  m_iPlayerStatus, m_cPlayerName,
											  DEF_OBJECTSTOP, NULL, NULL, NULL);
	}

	m_sViewDstX = m_sViewPointX = (sX+4+5)*32;
	m_sViewDstY = m_sViewPointY = (sY+5+5)*32;
	_ReadMapData(sX + 4 + 5, sY + 5 + 5, cp);
	m_bIsRedrawPDBGS = TRUE;
    // ------------------------------------------------------------------------+
	wsprintf(cTxt, INITDATA_RESPONSE_HANDLER1, m_cMapMessage);
	AddEventList(cTxt, 10);

	m_stDialogBoxInfo[6].sX  =  150;
    m_stDialogBoxInfo[6].sY  =  130;

	if (   ( memcmp( m_cCurLocation, "middleland"	,10 ) == 0 )
		|| ( memcmp( m_cCurLocation, "dglv2"		, 5 ) == 0 )
		|| ( memcmp( m_cCurLocation, "middled1n"	, 9 ) == 0 ))
    	EnableDialogBox(6, NULL,NULL, NULL);

// Snoopy: removed for v351 compatibility. Maybe usefull later...
/*	BOOL bPrevSafe, bNowSafe;
	if( memcmp( cPreCurLocation, m_cLocation, 3 ) == 0 )
		bPrevSafe = TRUE;
	else bPrevSafe = FALSE;

	if( memcmp( m_cCurLocation, m_cLocation, 3 ) == 0 )
		bNowSafe = TRUE;
	else bNowSafe = FALSE;

	if( memcmp( m_cCurLocation, "2nd", 3 ) == 0 ) bNowSafe = TRUE;
	if( m_iPKCount != 0 ) bNowSafe = FALSE;

	if( bPrevSafe )
	{	if( bNowSafe == FALSE ) SetTopMsg(DEF_MSG_DANGERZONE, 5);
	}else
	{	if( bNowSafe ) SetTopMsg(DEF_MSG_SAFEZONE, 5);
	}*/

    // ------------------------------------------------------------------------+

	ChangeGameMode(DEF_GAMEMODE_ONMAINGAME);
	m_DDraw.ClearBackB4();

	//v1.41
	if ((m_sPlayerAppr2 & 0xF000) != 0)
		 m_bIsCombatMode = TRUE;
	else m_bIsCombatMode = FALSE;

	//v1.42
	if (m_bIsFirstConn == TRUE)
	{	m_bIsFirstConn = FALSE;
		hFile = CreateFile("contents\\contents1000.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			dwFileSize = 0;
		else
		{	dwFileSize = GetFileSize(hFile, NULL);
			CloseHandle(hFile);
		}
		bSendCommand(MSGID_REQUEST_NOTICEMENT, NULL, NULL, (int)dwFileSize, NULL, NULL, NULL);
	}
	//cp += 2;
}

void CGame::MotionEventHandler(char * pData)
{WORD  * wp, wEventType, wObjectID;
 short * sp, sX, sY, sType, sAppr1, sAppr2, sAppr3, sAppr4, sV1, sV2, sV3, sPrevAppr2;
 int iStatus;
 char  * cp, cDir, cName[12];
 int   * ip, iApprColor, iLoc;
 char    cTxt[120];
 int i;
	ZeroMemory(cName, sizeof(cName));
	sV1 = sV2 = sV3 = NULL;
	wp   = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wEventType = *wp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	wObjectID = *wp;
	cp += 2;
	iLoc = 0;
	if (wObjectID < 30000)
	{	if (wObjectID < 10000) 	// Player
		{	sp  = (short *)cp;
			sX = *sp;
			cp += 2;
			sp  = (short *)cp;
			sY = *sp;
			cp += 2;
			sp  = (short *)cp;
			sType = *sp;
			cp += 2;
			cDir = *cp;
			cp++;
			memcpy(cName, cp, 10);
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
			ip = (int *)cp; // v1.4
			iApprColor = *ip;
			cp += 4;

			// CLEROTH - CRASH BUG ( STATUS )
			ip  = (int *)cp;
			iStatus = *ip;
			cp += 4;

			iLoc = *cp;
			cp++;
		}else 	// Npc or mob
		{	sp  = (short *)cp;
			sX = *sp;
			cp += 2;
			sp  = (short *)cp;
			sY = *sp;
			cp += 2;
			sp  = (short *)cp;
			sType = *sp;
			cp += 2;
			cDir = *cp;
			cp++;
			memcpy(cName, cp, 5);
			cp += 5;
			sAppr1 = sAppr3 = sAppr4 = 0;
			sp  = (short *)cp;
			sAppr2 = *sp;
			cp += 2;
			ip  = (int *)cp;
			iStatus = *ip;
			cp += 4;
			iLoc = *cp;
			cp++;
		}
	}else
	{	switch (wEventType) {
		case DEF_OBJECTMAGIC:
		case DEF_OBJECTDAMAGEMOVE:
		case DEF_OBJECTDAMAGE:
			cDir = *cp;
			cp++;
			sV1 = (short)*cp; //Damage
			cp++;
			sV2 = (short)*cp; //
			cp++;
  			break;

		case DEF_OBJECTDYING:
			cDir = *cp;
			cp++;
			sV1 = (short)*cp; //Damage
			cp++;
			sV2 = (short)*cp; //
			cp++;
			sp  = (short *)cp;
			sX = *sp;
			cp += 2;
			sp  = (short *)cp;
			sY = *sp;
			cp += 2;
			break;

		case DEF_OBJECTATTACK:
			cDir = *cp;
			cp++;
			sV1 = *cp;
			cp++;
			sV2 = *cp;
			cp++;
			sp = (short *)cp;
			sV3 = *sp;
			cp += 2;
			break;

		default:
			cDir = *cp;
			cp++;
			break;
	}	}

	if ((wEventType == DEF_OBJECTNULLACTION) && (memcmp(cName, m_cPlayerName, 10) == 0))
	{	m_sPlayerType   = sType;
		m_sPlayerAppr1  = sAppr1;
		sPrevAppr2      = m_sPlayerAppr2;
		m_sPlayerAppr2  = sAppr2;
		m_sPlayerAppr3  = sAppr3;
		m_sPlayerAppr4  = sAppr4;
		m_iPlayerApprColor = iApprColor;
		m_iPlayerStatus    = iStatus;
		if ((sPrevAppr2 & 0xF000) == 0)
		{	if ((sAppr2 & 0xF000) != 0)
			{	AddEventList(MOTION_EVENT_HANDLER1, 10);
				m_bIsCombatMode = TRUE;
			}
		}else
		{	if ((sAppr2 & 0xF000) == 0)
			{	AddEventList(MOTION_EVENT_HANDLER2, 10);
				m_bIsCombatMode = FALSE;
		}	}
		if (m_cCommand != DEF_OBJECTRUN) m_pMapData->bSetOwner(wObjectID, sX, sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, (char)wEventType, sV1, sV2, sV3, iLoc);
	}else m_pMapData->bSetOwner(wObjectID, sX, sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, (char)wEventType, sV1, sV2, sV3, iLoc);

	switch (wEventType) {
	case DEF_OBJECTMAGIC: // Casting
		_RemoveChatMsgListByObjectID(wObjectID - 30000);

		for (i = 1; i < DEF_MAXCHATMSGS; i++)
		if (m_pChatMsgList[i] == NULL)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			wsprintf(cTxt, "%s!", m_pMagicCfgList[sV1]->m_cName);
			m_pChatMsgList[i] = new class CMsg(41, cTxt, m_dwCurTime);
			m_pChatMsgList[i]->m_iObjectID = wObjectID - 30000;
			if (m_pMapData->bSetChatMsgOwner(wObjectID - 30000, -10, -10, i) == FALSE)
			{	delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
			return;
		}
		break;

	case DEF_OBJECTDYING:
		_RemoveChatMsgListByObjectID(wObjectID - 30000);
		for (i = 1; i < DEF_MAXCHATMSGS; i++)
		if (m_pChatMsgList[i] == NULL)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			if (sV1 > 0)
				wsprintf(cTxt, "-%dPts!", sV1); //pts
			else strcpy(cTxt, "Critical!");
			int iFontType;
			if ((sV1 >= 0) && (sV1 < 12))		iFontType = 21;
			else if ((sV1 >= 12) && (sV1 < 40)) iFontType = 22;
			else if ((sV1 >= 40) || (sV1 < 0))	iFontType = 23;
			m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
			m_pChatMsgList[i]->m_iObjectID = wObjectID - 30000;
			if (m_pMapData->bSetChatMsgOwner(wObjectID - 30000, -10, -10, i) == FALSE)
			{	delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
			return;
		}
		break;

	case DEF_OBJECTDAMAGEMOVE:
	case DEF_OBJECTDAMAGE:
		if (memcmp(cName, m_cPlayerName, 10) == 0)
		{	m_bIsGetPointingMode = FALSE;
			m_iPointCommandType	 = -1;
			m_stMCursor.sCursorFrame = 0;
			ClearSkillUsingStatus();
		}
		_RemoveChatMsgListByObjectID(wObjectID - 30000);

		for (i = 1; i < DEF_MAXCHATMSGS; i++)
		if (m_pChatMsgList[i] == NULL)
		{	ZeroMemory(cTxt, sizeof(cTxt));
			if (sV1 != 0)
			{	if (sV1 > 0)
					wsprintf(cTxt, "-%dPts", sV1); //pts
				else strcpy(cTxt, "Critical!");
				int iFontType;
				if ((sV1 >= 0) && (sV1 < 12))		iFontType = 21;
				else if ((sV1 >= 12) && (sV1 < 40)) iFontType = 22;
				else if ((sV1 >= 40) || (sV1 < 0))	iFontType = 23;

				m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
			}else
			{	strcpy(cTxt, " * Failed! *");
				m_pChatMsgList[i] = new class CMsg(22, cTxt, m_dwCurTime);
				PlaySound('C', 17, 0);
			}
			m_pChatMsgList[i]->m_iObjectID = wObjectID - 30000;
			if (m_pMapData->bSetChatMsgOwner(wObjectID - 30000, -10, -10, i) == FALSE)
			{	delete m_pChatMsgList[i];
				m_pChatMsgList[i] = NULL;
			}
			return;
		}
		break;
	}
}

void CGame::DrawDialogBox_Commander(int msX, int msY) // Snoopy: Fixed for 351
{short sX, sY, szX, szY, MapSzX, MapSzY;
 DWORD dwTime = G_dwGlobalTime;
 double dV1, dV2, dV3;
 int i, tX, tY;
	sX = m_stDialogBoxInfo[36].sX;
	sY = m_stDialogBoxInfo[36].sY;
	szX = m_stDialogBoxInfo[36].sSizeX;
	if ((dwTime - m_dwCommanderCommandRequestedTime) > 1000*10)
	{	_RequestMapStatus("middleland", 3);
		_RequestMapStatus("middleland", 1);
		m_dwCommanderCommandRequestedTime = dwTime;
	}

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY-5, 0, FALSE, m_bDialogTrans); // Main image
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 15, FALSE, m_bDialogTrans);

	switch (m_stDialogBoxInfo[36].cMode) {
	case 0: // Main dlg
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20,          sY + 340, 3, dwTime); // btn
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50,      sY + 340, 1, dwTime); // btn
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100,     sY + 340, 2, dwTime); // btn
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150,     sY + 340, 30,dwTime); // Btn TP
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 +74, sY + 340, 4, dwTime); // btn ?
		//PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER1);//"Middleland warfare building structure situation"
		PutAlignedString(sX, sX + szX, sY + 37, DRAW_DIALOGBOX_COMMANDER1);//"Middleland warfare building structure situation"

		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 17, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER2, 255,255,255);//"Middleland teleport position set"
		}else if ( (msX >= sX +20 +50) && (msX <= sX +20 +46 +50)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY + 340, 15, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER3, 255,255,255);//"Teleport to the selected area"
		}else if ( (msX >= sX +20 +100) && (msX <= sX +20 +46 +100)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52)) {
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY + 340, 16, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER4, 255,255,255);//"Recall warfare units"
		}else if ((msX >= sX +20 +150) && (msX <= sX +20 +46 +150)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY + 340, 24,dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER5, 255,255,255);//"Middleland construction building set"
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER6, 255,255,255);//"Commander's duty help"
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, FALSE, m_bDialogTrans);// Map
		break;

	case 1: // Set TP
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 20, dwTime); //btn <-
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);  //btn ?
		PutAlignedString(sX, sX + szX, sY + 40,  DRAW_DIALOGBOX_COMMANDER7); // "Click and select the teleport location."

		if (   (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 19, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER8, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER9, 255,255,255);
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, FALSE, m_bDialogTrans);

		if (   (msX >= sX + 15) && (msX <= sX + 15 + 278)
			&& (msY >= sY + 60) && (msY <= sY + 60 + 272)) // shows TP posit on map following the mouse
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, msX, msY, 42, FALSE, TRUE);
		}
		break;

	case 2: // Use TP
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50,  sY + 340, 1, dwTime);       // Btn TP
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 20, dwTime); // Btn <-
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);  // Btn ?
		PutAlignedString(sX, sX + szX, sY + 40,  DRAW_DIALOGBOX_COMMANDER10); // "Teleport to the selected area"

		if (   (msX >= sX +20 +50) && (msX <= sX +20 +46 +50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50,  sY + 340, 15, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER11, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 19, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER12, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER13, 255,255,255);
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, FALSE, m_bDialogTrans);
		break;

	case 3: // Choose summon
		if( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY +220, 6, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY +220, 5, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY +220, 7, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY +220, 35, dwTime);
		}else if ( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY +220, 9, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY +220, 8, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY +220, 7, dwTime);
			m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY +220, 35, dwTime);
		}
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 20, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);

		PutAlignedString(sX, sX + szX, sY + 40,  DRAW_DIALOGBOX_COMMANDER14); // "Recall warfare units"

		wsprintf(G_cTxt, "%s %d",DRAW_DIALOGBOX_COMMANDER15, m_iConstructionPoint);
		PutAlignedString(sX, sX +323, sY +190,  G_cTxt);

		if( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
		{	if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 3000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY +220, 11, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER16, 255,255,255);//"¹(Battle Golem)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER17, 255,255,255);//"3000"
			}else if ((msX >= sX +20 +50) && (msX <= sX +20 +50 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 2000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY +220, 10, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER18, 255,255,255);//"(Temple Knight)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER19, 255,255,255);//"2000"
			}else if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 1000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY +220, 12, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER20, 255,255,255);//"(Light War Beetle)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER21, 255,255,255);//" 1000"
			}else if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{ 	if (m_iConstructionPoint >= 5000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY +220, 29, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER22, 255,255,255);//"(Catapult)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER23, 255,255,255);// 1500"
			}else if ((msX >= sX +20) && (msX <= sX +380) && (msY > sY +140) && (msY < sY +160))
			{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER24, 255,255,255);
			}else if ((msX >= sX +20) && (msX <= sX +380) && (msY > sY +160) && (msY < sY +175))
			{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER25, 255,255,255);
			}else if ( (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
					&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 19, dwTime);
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER26, 255,255,255);
			}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
					&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER27, 255,255,255); //"Warfare units recall related help"
			}
		}else if ( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
		{	if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 3000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY +220, 14, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER28, 255,255,255);//"(God's Hand Knight Cavalry)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER29, 255,255,255);//"3000"
			}else if ( (msX >= sX +20 +50) && (msX <= sX +20 +50 +45)
					&& (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 2000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY +220, 13, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER30, 255,255,255);//"°(God's Hand Knight)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER31, 255,255,255);//"2000"
			}else if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 1000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY +220, 12, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER32, 255,255,255);//"(Light War Beetle)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER33, 255,255,255);//" 1000"
			}else if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 5000)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY +220, 29, dwTime);
				}
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER34, 255,255,255);//"(Catapult)"
				PutString2(msX +20, msY +50, DRAW_DIALOGBOX_COMMANDER35, 255,255,255);//" 1500"
			}else if ((msX >= sX +20) && (msX <= sX +380) && (msY > sY +140) && (msY < sY +160))
			{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER36, 255,255,255);
			}else if ((msX >= sX +20) && (msX <= sX +380) && (msY > sY +160) && (msY < sY +175))
			{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER37, 255,255,255);
			}else if ( (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
					&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 19, dwTime);
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER38, 255,255,255);

			}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
					&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
			{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
				PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER39, 255,255,255);
		}	}
		PutAlignedString(sX, sX +323, sY +80,  DRAW_DIALOGBOX_COMMANDER40);
		PutAlignedString(sX, sX +323, sY +95,  DRAW_DIALOGBOX_COMMANDER41);
		PutAlignedString(sX, sX +323, sY +110, DRAW_DIALOGBOX_COMMANDER42);

		switch (m_stDialogBoxInfo[36].sV1) {
		case 0:
			PutAlignedString(sX, sX +323, sY +140,  DRAW_DIALOGBOX_COMMANDER43, 255, 255, 255);//"Guard Mode"
			PutAlignedString(sX, sX +323, sY +160,  DRAW_DIALOGBOX_COMMANDER44, 4,0,50);//"Hold Mode"
			break;
		case 1:
			PutAlignedString(sX, sX +323, sY +140,  DRAW_DIALOGBOX_COMMANDER43, 4,0,50);//"Guard Mode"
			PutAlignedString(sX, sX +323, sY +160,  DRAW_DIALOGBOX_COMMANDER44, 255, 255, 255);//"Hold Mode"
			break;
		}
		break;

	case 4: // Set Construction point
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 20, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);
		PutAlignedString(sX, sX + szX, sY + 40,  DRAW_DIALOGBOX_COMMANDER47); // "Select the construction area and click."

		if (   (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 19, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER48, 255,255,255); // "Returns to commander's main menu"
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
			PutString2(msX +20, msY +35, DRAW_DIALOGBOX_COMMANDER49, 255,255,255); // "Construction area set related help"
		}
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21);
		if (   (msX >= sX + 15) && (msX <= sX + 15 + 278)
			&& (msY >= sY + 60) && (msY <= sY + 60 + 272)) // shows posit on map following the mouse
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, msX, msY, 41, FALSE, TRUE);
		}
		break;
	}

	switch (m_stDialogBoxInfo[36].cMode) {
	case 0: // Main
	case 1: // Set TP
	case 2: // Use TP
	case 4: // Set construc
		szX = NULL;
		szY = NULL;
		MapSzX = NULL;
		MapSzY = NULL;
		if (strcmp(m_cStatusMapName, "aresden") == 0)
		{	szX = 250;
			szY = 250;
		}else if (strcmp(m_cStatusMapName, "elvine") == 0)
		{	szX = 250;
			szY = 250;
		}else if (strcmp(m_cStatusMapName, "middleland") == 0)
		{	szX = 279;
			szY = 280;
			MapSzX = 524;
			MapSzY = 524;
		}
		if (szX != NULL)
		{	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
			if (m_stCrusadeStructureInfo[i].cType != NULL)
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_stCrusadeStructureInfo[i].sX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_stCrusadeStructureInfo[i].sY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				switch (m_stCrusadeStructureInfo[i].cType) {
				case 38:
					if (m_stCrusadeStructureInfo[i].cSide == 1)
						 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 39, FALSE, TRUE); // Base
					else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 37, FALSE, TRUE);
					break;
				case 36:
				case 37:
				case 39:
					if (m_stCrusadeStructureInfo[i].cSide == 1)
						 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 38, FALSE, TRUE); // Base
					else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 36, FALSE, TRUE);
					break;
				case 42:
					DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 40); // ManaStone
					break;
			}	}
			if (m_iTeleportLocX != -1)
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_iTeleportLocX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_iTeleportLocY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				if ((m_stDialogBoxInfo[36].cMode == 1) && (tY >= 30) && (tY <= 494)) // Place the TP
				{	  DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 42, FALSE, TRUE); //TP
				}else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 42, FALSE, TRUE); //TP
			}
			if ((m_stDialogBoxInfo[36].cMode != 2) && (m_iConstructLocX != -1))
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_iConstructLocX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_iConstructLocY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 41, FALSE, TRUE); // Contr pt
			}
			if (strcmp(m_cMapName, "middleland") == 0)
			{	dV1 = (double)MapSzX;//m_pMapData->m_sMapSizeX;
				dV2 = (double)m_sPlayerX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;//m_pMapData->m_sMapSizeY;
				dV2 = (double)m_sPlayerY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 43); // Player place
		}	}
		if (m_stDialogBoxInfo[36].cMode != 3)
		{	if (   (msX >= sX + 15) && (msX <= sX + 15 +278)
				&& (msY >= sY + 60) && (msY <= sY + 60 +272)) // Draw mouse coordinates
			{	dV1 = (double)(msX - (sX + 15));
				dV2 = (double)MapSzX;//(752.0f);
				dV3 = (dV2*dV1)/szX;//280.0f;
				tX = (int)dV3;
				dV1 = (double)(msY - (sY + 60));
				dV2 = (double)MapSzX;//(680.0f);
				dV3 = (dV2*dV1)/szY;//253.0f;
				tY = (int)dV3;
				if (tX < 30) tX = 30;
				if (tY < 30) tY = 30;
				if (tX > MapSzX-30) tX = MapSzX-30;
				if (tY > MapSzY-30) tY = MapSzY-30;
				wsprintf(G_cTxt, "%d,%d", tX, tY);
				PutString_SprFont3(msX + 10, msY -10, G_cTxt, m_wR[13]*4, m_wG[13]*4, m_wB[13]*4, FALSE, 2);
		}	}
		break;
	}
}

void CGame::DrawDialogBox_Constructor(int msX, int msY) // Snoopy: Fixed for 351
{short sX, sY, szX, szY, MapSzX, MapSzY;
 DWORD dwTime = G_dwGlobalTime;
 double dV1, dV2, dV3;
 int tX, tY;
 char cMapName[12];
	sX = m_stDialogBoxInfo[37].sX;
	sY = m_stDialogBoxInfo[37].sY;
	szX = m_stDialogBoxInfo[37].sSizeX;
	if ((dwTime - m_dwCommanderCommandRequestedTime) > 1000*10)
	{	_RequestMapStatus("middleland", 1);
		m_dwCommanderCommandRequestedTime = dwTime;
	}

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY-5, 0, FALSE, m_bDialogTrans); // Main image
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 16, FALSE, m_bDialogTrans);

	switch (m_stDialogBoxInfo[37].cMode) {
	case 0: // Main dlg
		if (m_iConstructLocX != -1)
		{	ZeroMemory(cMapName, sizeof(cMapName));
			GetOfficialMapName(m_cConstructMapName, cMapName);
			wsprintf(G_cTxt, DRAW_DIALOGBOX_CONSTRUCTOR1, cMapName, m_iConstructLocX, m_iConstructLocY);
			PutAlignedString(sX, sX + szX, sY + 40, G_cTxt);
		}else PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_CONSTRUCTOR2); //"Construction unavailable: Unable to construct"
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, FALSE, m_bDialogTrans); // Map

		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 24, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 30, dwTime);

		if (   (msX >= sX +20 +50) && (msX <= sX +20 +46 +50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY + 340, 15, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY + 340,  1, dwTime);

		if (   (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{     m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340,  4, dwTime);

		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR3, 255,255,255);
		}else if ( (msX >= sX +20 +50) && (msX <= sX +20 +46 +50)
				&& (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR4, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR5, 255,255,255);
		}
		break;

	case 1: // Select building
		PutAlignedString(sX, sX +szX, sY +40,  DRAW_DIALOGBOX_CONSTRUCTOR6); //"Select war building"
		PutAlignedString(sX, sX +323, sY +80,  DRAW_DIALOGBOX_CONSTRUCTOR7); //"Constructs the war building here."
		PutAlignedString(sX, sX +323, sY +95,  DRAW_DIALOGBOX_CONSTRUCTOR8); //"Press the building icon and"
		PutAlignedString(sX, sX +323, sY +110, DRAW_DIALOGBOX_CONSTRUCTOR9); //"the base will be formed and slowly finished"
		PutAlignedString(sX, sX +323, sY +125, DRAW_DIALOGBOX_CONSTRUCTOR10);//"Attack the building with Pickaxe."
		PutAlignedString(sX, sX +323, sY +140, DRAW_DIALOGBOX_CONSTRUCTOR11);//"Building is not activated"
		PutAlignedString(sX, sX +323, sY +155, DRAW_DIALOGBOX_CONSTRUCTOR12);//"while constructing."

		if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY +220, 27, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY +220, 33, dwTime);

		if ((msX >= sX +20 +50) && (msX <= sX +20 +50 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY +220, 28, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY +220, 34, dwTime);

		if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY +220, 26, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100, sY +220, 32, dwTime);

		if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY +220, 25, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150, sY +220, 31, dwTime);

		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 322, 19, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 322, 20, dwTime);

		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 322, 18, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 322, 4, dwTime);

		if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR13, 255,255,255);//"(Mana Collector)"
		}else if ((msX >= sX +20 +50) && (msX <= sX +20 +50 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR14, 255,255,255);//"(Detector)"
		}else if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR15, 255,255,255);//"(Arrow Guard Tower)"
		}else if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR16, 255,255,255);//(Cannon Guard Tower)"
		}else if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR17, 255,255,255);
		}else if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR18, 255,255,255);
		}
		break;

	case 2: // Teleport
		PutAlignedString(sX, sX + szX, sY + 40,  DRAW_DIALOGBOX_CONSTRUCTOR19); //"Teleport to position that commander pointed"
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, FALSE, m_bDialogTrans); // map

		if (   (msX >= sX +20 +50) && (msX <= sX +20 +46 +50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY + 340, 15, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +50, sY + 340, 1, dwTime);

		if (   (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 19, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +100 + 74, sY + 340, 20, dwTime);

		if (   (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);

		if ((msX >= sX +20 +50) && (msX <= sX +20 +46 +50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR20, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR21, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_CONSTRUCTOR22, 255,255,255);
		}
		break;
	}

	switch (m_stDialogBoxInfo[37].cMode) {
	case 0: // Main dlg
	case 2: // TP
		szX = NULL;
		szY = NULL;
		MapSzX = NULL;
		MapSzY = NULL;
		if (strcmp(m_cStatusMapName, "aresden") == 0)
		{	szX = 250;
			szY = 250;
		}else if (strcmp(m_cStatusMapName, "elvine") == 0)
		{	szX = 250;
			szY = 250;
		}else if (strcmp(m_cStatusMapName, "middleland") == 0)
		{	szX = 279;
			szY = 280;
			MapSzX = 524;
			MapSzY = 524;
		}
		if (szX != 0)
		{	for (int i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
			if (m_stCrusadeStructureInfo[i].cType == 42)
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_stCrusadeStructureInfo[i].sX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_stCrusadeStructureInfo[i].sY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				switch (m_stCrusadeStructureInfo[i].cType) {
				case 42:
					DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 40); // ManaStone
					break;
			}	}
			if (m_iTeleportLocX != -1)
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_iTeleportLocX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_iTeleportLocY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 42, FALSE, TRUE); //TP
			}
			if ((m_stDialogBoxInfo[37].cMode != 2) && (m_iConstructLocX != -1))
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_iConstructLocX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_iConstructLocY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 41, FALSE, TRUE); // Contr pt
			}
			if (strcmp(m_cMapName, "middleland") == 0)
			{	dV1 = (double)MapSzX;//m_pMapData->m_sMapSizeX;
				dV2 = (double)m_sPlayerX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;//m_pMapData->m_sMapSizeY;
				dV2 = (double)m_sPlayerY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 43); // Player place
		}	}
		if (   (msX >= sX + 15) && (msX <= sX + 15 +278)
			&& (msY >= sY + 60) && (msY <= sY + 60 +272))  // Draw mouse coordinates
		{	dV1 = (double)(msX - (sX + 15));
			dV2 = (double)MapSzX;//(752.0f);
			dV3 = (dV2*dV1)/szX;//280.0f;
			tX = (int)dV3;
			dV1 = (double)(msY - (sY + 60));
			dV2 = (double)MapSzX;//(680.0f);
			dV3 = (dV2*dV1)/szY;//253.0f;
			tY = (int)dV3;
			if (tX < 30) tX = 30;
			if (tY < 30) tY = 30;
			if (tX > MapSzX-30) tX = MapSzX-30;
			if (tY > MapSzY-30) tY = MapSzY-30;
			wsprintf(G_cTxt, "%d,%d", tX, tY);
			PutString_SprFont3(msX + 10, msY -10, G_cTxt, m_wR[13]*4, m_wG[13]*4, m_wB[13]*4, FALSE, 2);
		}
		break;
	}
}

void CGame::DrawDialogBox_Soldier(int msX, int msY) // Snoopy: Fixed for 351
{short sX, sY, szX, szY, MapSzX, MapSzY;
 DWORD dwTime = G_dwGlobalTime;
 char cMapName[120];
 double dV1, dV2, dV3;
 int tX, tY;
	sX = m_stDialogBoxInfo[38].sX;
	sY = m_stDialogBoxInfo[38].sY;
	szX = m_stDialogBoxInfo[38].sSizeX;
	if ((dwTime - m_dwCommanderCommandRequestedTime) > 1000*10)
	{	_RequestMapStatus("middleland", 1);
		m_dwCommanderCommandRequestedTime = dwTime;
	}

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY-5, 0, FALSE, m_bDialogTrans);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, FALSE, m_bDialogTrans);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 17, FALSE, m_bDialogTrans); // Crusade Soldier Menu Text

	switch (m_stDialogBoxInfo[38].cMode) {
	case 0: // Main dlg, Map
		if (m_iTeleportLocX != -1)
		{	ZeroMemory(cMapName, sizeof(cMapName));
			GetOfficialMapName(m_cTeleportMapName, cMapName);
			wsprintf(G_cTxt, DRAW_DIALOGBOX_SOLDIER1, cMapName, m_iTeleportLocX, m_iTeleportLocY);
			PutAlignedString(sX, sX + szX, sY + 40, G_cTxt);					// "Teleport position: %s near %d, %d"
		}else PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_SOLDIER2); //"Teleport position is not set."

		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 15, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 1, dwTime);

		if (   (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);

		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY +340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_SOLDIER3, 255,255,255); // "Teleport to position that commander pointed"
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY +340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_SOLDIER4, 255,255,255); // "Help for soldier"
		}
		break;

	case 1: // TP now
		PutAlignedString(sX, sX + szX, sY + 40,  DRAW_DIALOGBOX_SOLDIER5); // "Teleport to position that commander pointed"
		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 15, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20, sY + 340, 1, dwTime);

		if (   (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	  m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74 -50, sY + 340, 19, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74 -50, sY + 340, 20, dwTime);

		if (   (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{     m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 18, dwTime);
		}else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX +20 +150 + 74, sY + 340, 4, dwTime);

		if (   (msX >= sX +20) && (msX <= sX +20 +46)
			&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_SOLDIER6, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_SOLDIER7, 255,255,255);
		}else if ( (msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74)
				&& (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	PutString2(msX +20, msY +35, DRAW_DIALOGBOX_SOLDIER8, 255,255,255);//"Help for teleport"
		}
		break;
	}

	switch (m_stDialogBoxInfo[38].cMode) {
	case 0: // Main
	case 1: // TP
		szX = NULL;
		szY = NULL;
		MapSzX = NULL;
		MapSzY = NULL;
		if (strcmp(m_cStatusMapName, "aresden") == 0)
		{	szX = 250;
			szY = 250;
		}else if (strcmp(m_cStatusMapName, "elvine") == 0)
		{	szX = 250;
			szY = 250;
		}else if (strcmp(m_cStatusMapName, "middleland") == 0)
		{	szX = 279;
			szY = 280;	  // Fix for ML
			MapSzX = 524; // Fix for ML
			MapSzY = 524; // Fix for ML
		}
		if (szX != 0)
		{	for (int i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
			if (m_stCrusadeStructureInfo[i].cType == 42)
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_stCrusadeStructureInfo[i].sX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_stCrusadeStructureInfo[i].sY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				switch (m_stCrusadeStructureInfo[i].cType) {
				case 42:
					DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 40); // ManaStone
					break;
			}	}
			if (m_iTeleportLocX != -1)
			{	dV1 = (double)MapSzX;
				dV2 = (double)m_iTeleportLocX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;
				dV2 = (double)m_iTeleportLocY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 42, FALSE, TRUE); //TP
			}
			if (strcmp(m_cMapName, "middleland") == 0)
			{	dV1 = (double)MapSzX;//m_pMapData->m_sMapSizeX;
				dV2 = (double)m_sPlayerX;
				dV3 = (dV2*(double)szX)/dV1;
				tX  = (int)dV3;
				dV1 = (double)MapSzY;//m_pMapData->m_sMapSizeY;
				dV2 = (double)m_sPlayerY;
				dV3 = (dV2*(double)szY)/dV1;
				tY  = (int)dV3;
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX +tX + 15, sY +tY + 60, 43); // Player place
		}	}
		if (   (msX >= sX + 15) && (msX <= sX + 15 +278)
			&& (msY >= sY + 60) && (msY <= sY + 60 +272))  // Draw mouse coordinates
		{	dV1 = (double)(msX - (sX + 15));
			dV2 = (double)MapSzX;//(752.0f);
			dV3 = (dV2*dV1)/szX;//280.0f;
			tX = (int)dV3;
			dV1 = (double)(msY - (sY + 60));
			dV2 = (double)MapSzX;//(680.0f);
			dV3 = (dV2*dV1)/szY;//253.0f;
			tY = (int)dV3;
			if (tX < 30) tX = 30;
			if (tY < 30) tY = 30;
			if (tX > MapSzX-30) tX = MapSzX-30;
			if (tY > MapSzY-30) tY = MapSzY-30;
			wsprintf(G_cTxt, "%d,%d", tX, tY);
			PutString_SprFont3(msX + 10, msY -10, G_cTxt, m_wR[13]*4, m_wG[13]*4, m_wB[13]*4, FALSE, 2);
		}
		break;
	}
}

void CGame::GrandMagicResult(char *pMapName, int iV1, int iV2, int iV3, int iV4, int iHP1, int iHP2, int iHP3, int iHP4)
{int i, iTxtIdx=0;
 char cTemp[120];

	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{	if (m_pMsgTextList[i] != NULL)
			delete m_pMsgTextList[i];
		m_pMsgTextList[i] = NULL;
	}

	for (i = 0; i < 92; i++)
	if (m_pGameMsgList[i] == NULL) return;

	if (strcmp(pMapName, "aresden") == 0)
	{	m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[2]->m_pMsg, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[3]->m_pMsg, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, " ", NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[4]->m_pMsg, iV1);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[5]->m_pMsg, iV2);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[6]->m_pMsg, iV3);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[58]->m_pMsg, iV4);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, " ", NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d %d %d %d", NOTIFY_MSG_STRUCTURE_HP, iHP1,iHP2,iHP3,iHP4);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, " ", NULL);

		if (iV2 == 0) {
			if( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
			{	PlaySound('E', 25, 0, 0);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[59]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[60]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[61]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[62]->m_pMsg, NULL);
				for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
			}else if ( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
			{	PlaySound('E', 25, 0, 0);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[69]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[70]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[71]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[72]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[73]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[74]->m_pMsg, NULL);
				for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
			}else PlaySound('E', 25, 0, 0);
		}else
		{	if (iV1 != 0)
			{	if( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
				{	PlaySound('E', 23, 0, 0);
					PlaySound('C', 21, 0, 0);
					PlaySound('C', 22, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[63]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[64]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[65]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else if ( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
				{	PlaySound('E', 24, 0, 0);
					PlaySound('C', 12, 0, 0);
					PlaySound('C', 13, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[75]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[76]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[77]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[78]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[79]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[80]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[81]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[82]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else PlaySound('E', 25, 0, 0);
			}else
			{	if( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
				{	PlaySound('E', 23, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[66]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[67]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[68]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else if ( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
				{	PlaySound('E', 24, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[83]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[84]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[85]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[86]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[87]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[88]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[89]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[90]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else PlaySound('E', 25, 0, 0);
		}	}
	}else if (strcmp(pMapName, "elvine") == 0)
	{	m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[7]->m_pMsg, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[8]->m_pMsg, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, " ", NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[4]->m_pMsg, iV1);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[5]->m_pMsg, iV2);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[6]->m_pMsg, iV3);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d", m_pGameMsgList[58]->m_pMsg, iV4);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, " ", NULL);

		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%s %d %d %d %d", NOTIFY_MSG_STRUCTURE_HP, iHP1,iHP2,iHP3,iHP4);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, cTemp, NULL);
		m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, " ", NULL);

		if (iV2 == 0) {
			if ( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
			{	PlaySound('E', 25, 0, 0);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[59]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[60]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[61]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[62]->m_pMsg, NULL);
				for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
			}else if ( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
			{	PlaySound('E', 25, 0, 0);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[69]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[70]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[71]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[72]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[73]->m_pMsg, NULL);
				m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[74]->m_pMsg, NULL);
				for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
			}else PlaySound('E', 25, 0, 0);
		}else
		{	if (iV1 != 0) {
				if ( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
				{	PlaySound('E', 23, 0, 0);
					PlaySound('C', 21, 0, 0);
					PlaySound('C', 22, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[63]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[64]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[65]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else if ( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
				{	PlaySound('E', 24, 0, 0);
					PlaySound('C', 12, 0, 0);
					PlaySound('C', 13, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[75]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[76]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[77]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[78]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[79]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[80]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[81]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[82]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else PlaySound('E', 25, 0, 0);
			}else
			{	if ( (m_bCitizen == TRUE) && (m_bAresden == TRUE) )
				{	PlaySound('E', 23, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[66]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[67]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[68]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}
				else if ( (m_bCitizen == TRUE) && (m_bAresden == FALSE) )
				{	PlaySound('E', 24, 0, 0);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[83]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[84]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[85]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[86]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[87]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[88]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[89]->m_pMsg, NULL);
					m_pMsgTextList[iTxtIdx++] = new class CMsg(NULL, m_pGameMsgList[90]->m_pMsg, NULL);
					for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
				}else PlaySound('E', 25, 0, 0);
	}	}	}

	EnableDialogBox(18, NULL, NULL, NULL);
}

void CGame::DrawDialogBox_Help(int msX, int msY)
{ short sX, sY, szX;

	sX = m_stDialogBoxInfo[35].sX;
	sY = m_stDialogBoxInfo[35].sY;
	szX = m_stDialogBoxInfo[35].sSizeX;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*0) && (msY < sY +50+15*1))
		 PutAlignedString(sX, sX+szX, sY + 50 +15*0, DRAW_DIALOGBOX_HELP2, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*0, DRAW_DIALOGBOX_HELP2, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*1) && (msY < sY +50+15*2))
		 PutAlignedString(sX, sX+szX, sY + 50 +15*1, DRAW_DIALOGBOX_HELP1, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*1, DRAW_DIALOGBOX_HELP1, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*2) && (msY < sY +50+15*3))
		PutAlignedString(sX, sX+szX, sY + 50 +15*2, DRAW_DIALOGBOX_HELP3, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*2, DRAW_DIALOGBOX_HELP3, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*3) && (msY < sY +50+15*4))
		PutAlignedString(sX, sX+szX, sY + 50 +15*3, DRAW_DIALOGBOX_HELP4, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*3, DRAW_DIALOGBOX_HELP4, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*4) && (msY < sY +50+15*5))
		PutAlignedString(sX, sX+szX, sY + 50 +15*4, DRAW_DIALOGBOX_HELP5, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*4, DRAW_DIALOGBOX_HELP5, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*5) && (msY < sY +50+15*6))
		PutAlignedString(sX, sX+szX, sY + 50 +15*5, DRAW_DIALOGBOX_HELP6, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*5, DRAW_DIALOGBOX_HELP6, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*6) && (msY < sY +50+15*7))
		PutAlignedString(sX, sX+szX, sY + 50 +15*6, DRAW_DIALOGBOX_HELP7, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*6, DRAW_DIALOGBOX_HELP7, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*7) && (msY < sY +50+15*8))
		PutAlignedString(sX, sX+szX, sY + 50 +15*7, DRAW_DIALOGBOX_HELP8, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*7, DRAW_DIALOGBOX_HELP8, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*8) && (msY < sY +50+15*9))
		PutAlignedString(sX, sX+szX, sY + 50 +15*8, DRAW_DIALOGBOX_HELP9, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*8, DRAW_DIALOGBOX_HELP9, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*9) && (msY < sY +50+15*10))
		PutAlignedString(sX, sX+szX, sY + 50 +15*9, DRAW_DIALOGBOX_HELP10, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*9, DRAW_DIALOGBOX_HELP10, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*10) && (msY < sY +50+15*11))
		PutAlignedString(sX, sX+szX, sY + 50 +15*10, DRAW_DIALOGBOX_HELP11, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*10, DRAW_DIALOGBOX_HELP11, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*11) && (msY < sY +50+15*12))
		PutAlignedString(sX, sX+szX, sY + 50 +15*11,DRAW_DIALOGBOX_HELP12, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*11,DRAW_DIALOGBOX_HELP12, 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*12) && (msY < sY +50+15*13))
		PutAlignedString(sX, sX+szX, sY + 50 +15*12,"F.A.Q.", 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*12,"F.A.Q.", 4, 0, 50);
	if ((msX >= sX+25) && (msX <= sX+248) && (msY >= sY +50+15*13) && (msY < sY +50+15*14))
		PutAlignedString(sX, sX+szX, sY + 50 +15*13,DRAW_DIALOGBOX_HELP13, 255, 255, 255);
	else PutAlignedString(sX, sX+szX, sY + 50 +15*13,DRAW_DIALOGBOX_HELP13, 4, 0, 50);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void CGame::DrawDialogBox_ItemUpgrade(int msX, int msY)
{int i, sX, sY, iValue;
 char cItemColor, cStr1[120], cStr2[120], cStr3[120];
 DWORD dwTime = timeGetTime();

	sX = m_stDialogBoxInfo[34].sX;
	sY = m_stDialogBoxInfo[34].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT , sX, sY, 5); //Item Upgrade Text

	switch (m_stDialogBoxInfo[34].cMode) {
	case 1://Gizon box Drag item needed to be upgraded"
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, DRAW_DIALOGBOX_ITEMUPGRADE1); // Drag item needed to be upgraded"
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE2); // "from the inventory. Then press"
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, DRAW_DIALOGBOX_ITEMUPGRADE3); // 'Upgrade' button."
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
		wsprintf(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE11, m_iGizonItemUpgradeLeft);		// "Item upgrade point : %d"
		PutAlignedString(sX + 24, sX + 248, sY + 100, G_cTxt);
		if (m_stDialogBoxInfo[34].sV1 != -1)
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
			iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
			iValue = iValue*(iValue+6)/8 + 2;
			if (   (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos >= 11)
				&& (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemType == 1))
			{	if(   (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(STR)", 19) == 0)
					|| (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(DEX)", 19) == 0)
					|| (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(INT)", 19) == 0)
					|| (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(MAG)", 19) == 0))
				{	iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
					switch (iValue) {
					case 0:	iValue = 10; break;
					case 1: iValue = 11; break;
					case 2: iValue = 13; break;
					case 3: iValue = 16; break;
					case 4: iValue = 20; break;
					case 5: iValue = 25; break;
					case 6: iValue = 31; break;
					case 7: iValue = 38; break;
					case 8: iValue = 46; break;
					case 9: iValue = 55; break;
			}	}	}
			wsprintf( G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE12, iValue ); //"Needed upgrade point : %d"
			if( m_iGizonItemUpgradeLeft < iValue )
				 PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt, 195,25,25);
			else PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt);
			i = m_stDialogBoxInfo[34].sV1;
			cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
			if (   (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
			}else
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
			}
			ZeroMemory(cStr1, sizeof(cStr1));
			ZeroMemory(cStr2, sizeof(cStr2));
			ZeroMemory(cStr3, sizeof(cStr3));
			GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
			PutAlignedString(sX + 24, sX + 248, sY +230 +20, cStr1);
			PutAlignedString(sX + 24, sX + 248, sY +245 +20, cStr2);
			PutAlignedString(sX + 24, sX + 248, sY +260 +20, cStr3);
			if( m_iGizonItemUpgradeLeft < iValue )
				DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
			else
			{	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
					DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY +DEF_BTNPOSY, 47);
				else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY +DEF_BTNPOSY, 46);
			}
		}
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
		// Cancel
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 2: // in progress
		PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 -117 -170, DRAW_DIALOGBOX_ITEMUPGRADE5);
		PutAlignedString(sX + 24, sX + 248, sY + 55 + 45 + 282 -117 -170, DRAW_DIALOGBOX_ITEMUPGRADE6);
		if (m_stDialogBoxInfo[34].sV1 != -1)
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
			i = m_stDialogBoxInfo[34].sV1;
			cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
			if (   (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
			}else
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
			}
			if ((rand() % 5) == 0) m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutTransSprite25(sX + 134, sY +182, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, dwTime);
			ZeroMemory(cStr1, sizeof(cStr1));
			ZeroMemory(cStr2, sizeof(cStr2));
			ZeroMemory(cStr3, sizeof(cStr3));
			GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
			PutAlignedString(sX + 24, sX + 248, sY +230 +20, cStr1);
			PutAlignedString(sX + 24, sX + 248, sY +245 +20, cStr2);
			PutAlignedString(sX + 24, sX + 248, sY +260 +20, cStr3);
		}
		if (((dwTime - m_stDialogBoxInfo[34].dwV1)/1000 > 4) && (m_stDialogBoxInfo[34].dwV1 != NULL))
		{	m_stDialogBoxInfo[34].dwV1 = NULL;
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_UPGRADEITEM, NULL, m_stDialogBoxInfo[34].sV1, NULL, NULL, NULL);
		}
		break;

	case 3: // Congratulations
		PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 -117 -170, DRAW_DIALOGBOX_ITEMUPGRADE7);//"Congratulation! item upgrade"
		PutAlignedString(sX + 24, sX + 248, sY + 55 + 45 + 282 -117 -170, DRAW_DIALOGBOX_ITEMUPGRADE8);//"has been succeeded."
		if (m_stDialogBoxInfo[34].sV1 != -1)
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
			i = m_stDialogBoxInfo[34].sV1;
			cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
			if (   (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
			}else
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
			}
			ZeroMemory(cStr1, sizeof(cStr1));
			ZeroMemory(cStr2, sizeof(cStr2));
			ZeroMemory(cStr3, sizeof(cStr3));
			GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
			PutAlignedString(sX + 24, sX + 248, sY +230 +20, cStr1);
			PutAlignedString(sX + 24, sX + 248, sY +245 +20, cStr2);
			PutAlignedString(sX + 24, sX + 248, sY +260 +20, cStr3);
		}
		// OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 4: // Failed
		PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 -117 -170, DRAW_DIALOGBOX_ITEMUPGRADE9);//"Item upgrade has failed."
		if ((m_stDialogBoxInfo[34].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[34].sV1] == NULL))
		{	PlaySound('E', 24, 0, 0);
			m_stDialogBoxInfo[34].cMode = 7;
			return;
		}
		if (m_stDialogBoxInfo[34].sV1 != -1)
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
			i = m_stDialogBoxInfo[34].sV1;
			cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
			if (   (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
			}else
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
			}
			ZeroMemory(cStr1, sizeof(cStr1));
			ZeroMemory(cStr2, sizeof(cStr2));
			ZeroMemory(cStr3, sizeof(cStr3));
			GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
			PutAlignedString(sX + 24, sX + 248, sY +230 +20, cStr1);
			PutAlignedString(sX + 24, sX + 248, sY +245 +20, cStr2);
			PutAlignedString(sX + 24, sX + 248, sY +260 +20, cStr3);
		}

		// OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 5: // select Stone/ Gizon
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE13); // "Select which kind of items to upgrade."
		if ((msX > sX +24) && (msX < sX +248) && (msY > sY +100) && (msY < sY +115))
		{	PutAlignedString(sX + 24, sX + 248, sY + 100, DRAW_DIALOGBOX_ITEMUPGRADE14, 255,255,255); // "Normal item upgrade"
			PutAlignedString(sX + 24, sX + 248, sY + 150, DRAW_DIALOGBOX_ITEMUPGRADE16); // "Upgrading a normal item."
			PutAlignedString(sX + 24, sX + 248, sY + 165, DRAW_DIALOGBOX_ITEMUPGRADE17); // "With upgrading weapon"
			PutAlignedString(sX + 24, sX + 248, sY + 180, DRAW_DIALOGBOX_ITEMUPGRADE18); // "items, Stone of Xelima"
			PutAlignedString(sX + 24, sX + 248, sY + 195, DRAW_DIALOGBOX_ITEMUPGRADE19); // "is needed. With upgrading"
			PutAlignedString(sX + 24, sX + 248, sY + 210, DRAW_DIALOGBOX_ITEMUPGRADE20); // "armor items, Stone of"
			PutAlignedString(sX + 24, sX + 248, sY + 225, DRAW_DIALOGBOX_ITEMUPGRADE21); // "Merien is needed."
			PutAlignedString(sX + 24, sX + 248, sY + 255, DRAW_DIALOGBOX_ITEMUPGRADE26); // "* Majestic items cannot be"
			PutAlignedString(sX + 24, sX + 248, sY + 270, DRAW_DIALOGBOX_ITEMUPGRADE27); // "upgraded with this performance."
		}else PutAlignedString(sX + 24, sX + 248, sY + 100, DRAW_DIALOGBOX_ITEMUPGRADE14, 4,0,50); // "Normal item upgrade"
		if ((msX > sX +24) && (msX < sX +248) && (msY > sY +120) && (msY < sY +135))
		{	PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_ITEMUPGRADE15, 255,255,255); // "Majestic item upgrade"
			PutAlignedString(sX + 24, sX + 248, sY + 150, DRAW_DIALOGBOX_ITEMUPGRADE22); // "Upgrading majestic items."
			PutAlignedString(sX + 24, sX + 248, sY + 165, DRAW_DIALOGBOX_ITEMUPGRADE23); // "In order to upgrade majestic items,"
			PutAlignedString(sX + 24, sX + 248, sY + 180, DRAW_DIALOGBOX_ITEMUPGRADE24); // "enough upgrade points for"
			PutAlignedString(sX + 24, sX + 248, sY + 195, DRAW_DIALOGBOX_ITEMUPGRADE25); // "majestic items are required."
			PutAlignedString(sX + 24, sX + 248, sY + 225, DRAW_DIALOGBOX_ITEMUPGRADE28); // "* Normal items cannot be"
			PutAlignedString(sX + 24, sX + 248, sY + 240, DRAW_DIALOGBOX_ITEMUPGRADE29); // "upgraded with this performance."
		}else PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_ITEMUPGRADE15, 4,0,50); // "Majestic item upgrade"
		// Cancel
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 6: // Stone upgrade
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, DRAW_DIALOGBOX_ITEMUPGRADE31); // "After bring a normal item to"
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE32); //
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, DRAW_DIALOGBOX_ITEMUPGRADE33); //
		if( m_stDialogBoxInfo[34].sV2 == 0 )
		{	PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, DRAW_DIALOGBOX_ITEMUPGRADE41, 195,25,25);//"You can upgrade only armor."
		}else
		{	wsprintf(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE34, m_stDialogBoxInfo[34].sV2);//"The number of upgrade(weapon): %d"
			PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, G_cTxt);
		}
		if( m_stDialogBoxInfo[34].sV3 == 0 )
		{	PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, DRAW_DIALOGBOX_ITEMUPGRADE42, 195,25,25);//"You can upgrade only weapon."
		}else
		{	wsprintf(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE35, m_stDialogBoxInfo[34].sV3);//"The number of upgrade(armor): %d"
			PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, G_cTxt);
		}

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

		if (m_stDialogBoxInfo[34].sV1 != -1)
		{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
			i = m_stDialogBoxInfo[34].sV1;
			cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
			if (   (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
				|| (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0], dwTime);
			}else
			{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY +182
					, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0], dwTime);
			}

			ZeroMemory(cStr1, sizeof(cStr1));
			ZeroMemory(cStr2, sizeof(cStr2));
			ZeroMemory(cStr3, sizeof(cStr3));
			GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
			PutAlignedString(sX + 24, sX + 248, sY +230 +20, cStr1);
			PutAlignedString(sX + 24, sX + 248, sY +245 +20, cStr2);
			PutAlignedString(sX + 24, sX + 248, sY +260 +20, cStr3);
			if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
				 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 47);
			else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
		}
		// Cancel
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
		break;

	case 7: // lost item
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE36);//"Due to the failure of upgrade, the"
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 145, DRAW_DIALOGBOX_ITEMUPGRADE37);//"item is gone. Try next time!"
		// OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 8: // impossible deja an max
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE38);//"Upgrading the item is not possible any more."
		// OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 9: // impossible
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE39);//"Upgrading the item is not possible."
		// OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 10: // plus de gizons
		PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE40);//"A point to upgrade items is not present"
		// OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;
	}
}

LONG CGame::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{   HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);
    if (retval == ERROR_SUCCESS)
	{  long datasize = MAX_PATH;
        TCHAR data[MAX_PATH];
        RegQueryValue(hkey, NULL, data, &datasize);
        lstrcpy(retdata,data);
        RegCloseKey(hkey);
    }
    return retval;
}

void CGame::GoHomepage()
{	LPCTSTR	url;
	url = MSG_HOMEPAGE;
	int		showcmd = SW_SHOW;
	char	key[MAX_PATH + MAX_PATH];
	SendMessage( G_hWnd, WM_ACTIVATEAPP, 0, 0 );
    // First try ShellExecute()
    HINSTANCE result = ShellExecute(NULL, "open", url, NULL,NULL, showcmd);

    // If it failed, get the .htm regkey and lookup the program
    if ((UINT)result <= HINSTANCE_ERROR)
	{  if (GetRegKey(HKEY_CLASSES_ROOT, ".htm", key) == ERROR_SUCCESS)
		{   lstrcat(key, "\\shell\\open\\command");

            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS)
			{  char *pos;
                pos = strstr(key, "\"%1\"");
                if (pos == NULL)					// No quotes found
				{  pos = strstr(key, "%1");			// Check for %1, without quotes
                    if (pos == NULL)				// No parameter at all...
                        pos = key+lstrlen(key)-1;
                    else *pos = '\0';				// Remove the parameter
                }else    *pos = '\0';				// Remove the parameter
                lstrcat(pos, " ");
                lstrcat(pos, url);
                result = (HINSTANCE) WinExec(key,showcmd);
    }   }   }
}

// num : 1 - F2, 2 - F3
void CGame::UseShortCut( int num )
{int index;
	if( num < 3 ) index = num+1;
	else index = num+7;
	if(m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
	if (m_bCtrlPressed == TRUE)
	{	if (m_sRecentShortCut == -1)
		{	AddEventList(MSG_SHORTCUT1, 10);
			wsprintf( G_cTxt, MSG_SHORTCUT2, index );// [F%d]
			AddEventList(G_cTxt, 10);
			wsprintf( G_cTxt, MSG_SHORTCUT3, index );// [Control]-[F%d]
			AddEventList(G_cTxt, 10);
		}else
		{	m_sShortCut[num] = m_sRecentShortCut;
			if (m_sShortCut[num] < 100)
			{	if (m_pItemList[m_sShortCut[num]] == NULL)
				{	m_sShortCut[num] = -1;
					m_sRecentShortCut = -1;
					return;
				}
				char cStr1[64], cStr2[64], cStr3[64];
				ZeroMemory(cStr1, sizeof(cStr1));
				ZeroMemory(cStr2, sizeof(cStr2));
				ZeroMemory(cStr3, sizeof(cStr3));

				GetItemName(m_pItemList[m_sShortCut[num]], cStr1, cStr2, cStr3);
				wsprintf(G_cTxt, MSG_SHORTCUT4, cStr1, cStr2, cStr3, index);// (%s %s %s) [F%d]
				AddEventList(G_cTxt, 10);
			}else if (m_sShortCut[num] >= 100)
			{	if (m_pMagicCfgList[m_sShortCut[num]-100] == NULL)
				{	m_sShortCut[num] = -1;
					m_sRecentShortCut = -1;
					return;
				}
				wsprintf(G_cTxt, MSG_SHORTCUT5, m_pMagicCfgList[m_sShortCut[num]-100]->m_cName, index);// %s) [F%d]
				AddEventList(G_cTxt, 10);
		}	}
	}else
	{	if (m_sShortCut[num] == -1)
		{	AddEventList(MSG_SHORTCUT1, 10);
			wsprintf( G_cTxt, MSG_SHORTCUT2, index );// [F%d]
			AddEventList(G_cTxt, 10);
			wsprintf( G_cTxt, MSG_SHORTCUT3, index );// [Control]-[F%d]
			AddEventList(G_cTxt, 10);
		}else if (m_sShortCut[num] < 100)
		{	ItemEquipHandler((char)m_sShortCut[num]);
		}
		else if (m_sShortCut[num] >= 100) UseMagic(m_sShortCut[num]-100);
	}
}

int CGame::iGetManaCost(int iMagicNo)
{	int i, iManaSave, iManaCost;
	iManaSave = 0;
	if( iMagicNo < 0 || iMagicNo >= 100 ) return 1;
	for( i=0; i<DEF_MAXITEMS ; i++ )
	{	if( m_pItemList[i] == NULL ) continue;
		if( m_bIsItemEquipped[i] == TRUE )
		{	if(      strcmp( m_pItemList[i]->m_cName, "MagicWand(MS10)" ) == 0)		iManaSave += 10;
			else if( strcmp( m_pItemList[i]->m_cName, "MagicWand(MS20)" ) == 0)		iManaSave += 20;
			else if( strcmp( m_pItemList[i]->m_cName, "MagicWand(MS30-LLF)" ) == 0) iManaSave += 30;
			else if( strcmp( m_pItemList[i]->m_cName, "WizMagicWand(MS10)" ) == 0)	iManaSave += 10;
			else if( strcmp( m_pItemList[i]->m_cName, "WizMagicWand(MS20)" ) == 0)	iManaSave += 20;
			else if( strcmp( m_pItemList[i]->m_cName, "MagicNecklace(MS10)" ) == 0) iManaSave += 10;
			else if( strcmp( m_pItemList[i]->m_cName, "DarkMageMagicStaff" ) == 0)	iManaSave += 25;
			else if( strcmp( m_pItemList[i]->m_cName, "DarkMageMagicStaffW" ) == 0) iManaSave += 25;
			else if( strcmp( m_pItemList[i]->m_cName, "DarkMageMagicWand" ) == 0)	iManaSave += 28;
			else if( strcmp( m_pItemList[i]->m_cName, "NecklaceOfLiche") ==0)   	iManaSave += 15;
			// Snoopy: v351 wands
			else if( strcmp( m_pItemList[i]->m_cName, "DarkMageTempleWand" ) == 0)	iManaSave += 28;
			else if( strcmp( m_pItemList[i]->m_cName, "BerserkWand(MS.20)" ) == 0)	iManaSave += 20;
			else if( strcmp( m_pItemList[i]->m_cName, "BerserkWand(MS.10)" ) == 0)	iManaSave += 10;
			else if( strcmp( m_pItemList[i]->m_cName, "KlonessWand(MS.20)" ) == 0)	iManaSave += 20;
			else if( strcmp( m_pItemList[i]->m_cName, "KlonessWand(MS.10)" ) == 0)	iManaSave += 10;
			else if( strcmp( m_pItemList[i]->m_cName, "ResurWand(MS.20)" ) == 0)	iManaSave += 20;
			else if( strcmp( m_pItemList[i]->m_cName, "ResurWand(MS.10)" ) == 0)	iManaSave += 10;

	}	}
	// Snoopy: MS max = 80%
	if (iManaSave > 80) iManaSave = 80;
	iManaCost = m_pMagicCfgList[iMagicNo]->m_sValue1;
	if (m_bIsSafeAttackMode) iManaCost += (iManaCost/2) - (iManaCost / 10);
	if (iManaSave > 0)
	{	double dV1 = (double)iManaSave;
		double dV2 = (double)(dV1 / 100.0f);
		double dV3 = (double)iManaCost;
		dV1 = dV2 * dV3;
		dV2 = dV3 - dV1;
		iManaCost = (int)dV2;
	}
	if( iManaCost < 1 ) iManaCost = 1;
	return iManaCost;
}

void CGame::UseMagic(int iMagicNo)
{	if( iMagicNo < 0 || iMagicNo >= 100 ) return;
	if ((m_cMagicMastery[iMagicNo] == NULL) || (m_pMagicCfgList[iMagicNo] == NULL)) return;

	// Casting
	if (m_iHP <= 0) return;
	if (m_bIsGetPointingMode == TRUE) return;
	if (iGetManaCost(iMagicNo) > m_iMP) return;
	if (_bIsItemOnHand() == TRUE)
	{	AddEventList(DLGBOX_CLICK_MAGIC1, 10);
		return;
	}
	if (m_bSkillUsingStatus == TRUE)
	{	AddEventList(DLGBOX_CLICK_MAGIC2, 10);
		return;
	}
	if ((m_sPlayerAppr2 & 0xF000) == 0) bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, NULL, NULL, NULL, NULL, NULL);
	m_cCommand = DEF_OBJECTMAGIC;
	m_iCastingMagicType = iMagicNo;
	m_sMagicShortCut    = iMagicNo;
	m_sRecentShortCut   = iMagicNo + 100;
	m_iPointCommandType = iMagicNo + 100;
	//m_bIsGetPointingMode = TRUE;
	DisableDialogBox(3);
}


void CGame::ReleaseEquipHandler(char cEquipPos)
{	char cStr1[64], cStr2[64], cStr3[64];
	if( m_sItemEquipmentStatus[cEquipPos] < 0 ) return;
	// Remove Angelic Stats
	if (   (cEquipPos >= 11)
		&& (m_pItemList[m_sItemEquipmentStatus[cEquipPos]]->m_cItemType == 1))
	{	char cItemID = m_sItemEquipmentStatus[cEquipPos];
		if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(STR)", 19) == 0)
		{	m_iAngelicStr = 0;
		}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(DEX)", 19) == 0)
		{	m_iAngelicDex = 0;
		}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(INT)", 19) == 0)
		{	m_iAngelicInt = 0;
		}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(MAG)", 19) == 0)
		{	m_iAngelicMag = 0;
	}	}

	GetItemName(m_pItemList[m_sItemEquipmentStatus[cEquipPos]], cStr1, cStr2, cStr3);
	wsprintf(G_cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
	AddEventList(G_cTxt, 10);
	m_bIsItemEquipped[m_sItemEquipmentStatus[cEquipPos]] = FALSE;
	m_sItemEquipmentStatus[cEquipPos] = -1;
}

void CGame::ItemEquipHandler(char cItemID)
{	if (bCheckItemOperationEnabled(cItemID) == FALSE) return;
	if (m_bIsItemEquipped[cItemID] == TRUE) return;
	if (m_pItemList[cItemID]->m_cEquipPos == DEF_EQUIPPOS_NONE)
	{	AddEventList(BITEMDROP_CHARACTER3, 10);//"The item is not available."
		return;
	}
	if ( m_pItemList[cItemID]->m_wCurLifeSpan == 0 )
	{	AddEventList(BITEMDROP_CHARACTER1, 10); //"The item is exhausted. Fix it to use it."
		return;
	}
	if (m_pItemList[cItemID]->m_wWeight / 100 > m_iStr + m_iAngelicStr)
	{	AddEventList(BITEMDROP_CHARACTER2, 10);
		return;
	}
	if (((m_pItemList[cItemID]->m_dwAttribute & 0x00000001) == 0) && (m_pItemList[cItemID]->m_sLevelLimit > m_iLevel)   )
	{	AddEventList(BITEMDROP_CHARACTER4, 10);
		return;
	}
	if (m_bSkillUsingStatus == TRUE)
	{	AddEventList(BITEMDROP_CHARACTER5, 10);
		return;
	}
	if (m_pItemList[cItemID]->m_cGenderLimit != 0)
	{	switch (m_sPlayerType) {
		case 1:
		case 2:
		case 3:
			if (m_pItemList[cItemID]->m_cGenderLimit != 1)
			{	AddEventList(BITEMDROP_CHARACTER6, 10);
				return;
			}
			break;
		case 4:
		case 5:
		case 6:
			if (m_pItemList[cItemID]->m_cGenderLimit != 2)
			{	AddEventList(BITEMDROP_CHARACTER7, 10);
				return;
			}
			break;
	}	}

	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_EQUIPITEM, NULL, cItemID, NULL, NULL, NULL);
	m_sRecentShortCut = cItemID;
	ReleaseEquipHandler(m_pItemList[cItemID]->m_cEquipPos);
	switch( m_pItemList[cItemID]->m_cEquipPos )	{
	case DEF_EQUIPPOS_HEAD:
	case DEF_EQUIPPOS_BODY:
	case DEF_EQUIPPOS_ARMS:
	case DEF_EQUIPPOS_PANTS:
	case DEF_EQUIPPOS_BOOTS:
	case DEF_EQUIPPOS_BACK:
		ReleaseEquipHandler(DEF_EQUIPPOS_FULLBODY);
		break;
	case DEF_EQUIPPOS_FULLBODY:
		ReleaseEquipHandler(DEF_EQUIPPOS_HEAD);
		ReleaseEquipHandler(DEF_EQUIPPOS_BODY);
		ReleaseEquipHandler(DEF_EQUIPPOS_ARMS);
		ReleaseEquipHandler(DEF_EQUIPPOS_PANTS);
		ReleaseEquipHandler(DEF_EQUIPPOS_BOOTS);
		ReleaseEquipHandler(DEF_EQUIPPOS_BACK);
		break;
	case DEF_EQUIPPOS_LHAND:
	case DEF_EQUIPPOS_RHAND:
		ReleaseEquipHandler(DEF_EQUIPPOS_TWOHAND);
		break;
	case DEF_EQUIPPOS_TWOHAND:
		ReleaseEquipHandler(DEF_EQUIPPOS_RHAND);
		ReleaseEquipHandler(DEF_EQUIPPOS_LHAND);
		break;
	}

	m_sItemEquipmentStatus[ m_pItemList[cItemID]->m_cEquipPos ] = cItemID;
	m_bIsItemEquipped[cItemID] = TRUE;

	// Add Angelic Stats
	if (   (m_pItemList[cItemID]->m_cItemType == 1)
		&& (m_pItemList[cItemID]->m_cEquipPos >= 11))
	{	int iAngelValue = 0;
		if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(STR)", 19) == 0)
		{	iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
			m_iAngelicStr = 1 + iAngelValue;
		}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(DEX)", 19) == 0)
		{	iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
			m_iAngelicDex = 1 + iAngelValue;
		}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(INT)", 19) == 0)
		{	iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
			m_iAngelicInt = 1 + iAngelValue;
		}else if(memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(MAG)", 19) == 0)
		{	iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
			m_iAngelicMag = 1 + iAngelValue;
	}	}

	char cStr1[64], cStr2[64], cStr3[64];
	GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);
	wsprintf(G_cTxt, BITEMDROP_CHARACTER9, cStr1);
	AddEventList(G_cTxt, 10);
	PlaySound('E', 28, 0);
}

/*********************************************************************************************************************
**  void CheckActiveAura(short sX, short sY, DWORD dwTime, short sOwnerType)( initially Cleroth fixed by Snoopy )	**
**  description			: Generates special auras around players													**
**						: v351 implements this in each drawn function,beter to regroup in single function.			**
**********************************************************************************************************************/
void CGame::CheckActiveAura(short sX, short sY, DWORD dwTime, short sOwnerType)
{	// Used at the beginning of character drawing
	// DefenseShield
	if ((_tmp_iStatus & 0x02000000) != 0)
		//m_pEffectSpr[80]->PutTransSprite(sX+75, sY+107, _tmp_iEffectFrame%17, dwTime);
		m_pEffectSpr[80]->PutTransSprite50(sX+75, sY+107, _tmp_iEffectFrame%17, dwTime);

	// Protection From Magic
	if ((_tmp_iStatus & 0x04000000) != 0)
		//m_pEffectSpr[79]->PutTransSprite(sX+101, sY+135, _tmp_iEffectFrame%15, dwTime);
		m_pEffectSpr[79]->PutTransSprite70(sX+101, sY+135, _tmp_iEffectFrame%15, dwTime);

	// Protection From Arrow
	if ((_tmp_iStatus & 0x08000000) != 0)
		//m_pEffectSpr[72]->PutTransSprite(sX, sY+35, _tmp_iEffectFrame%30, dwTime);
		m_pEffectSpr[72]->PutTransSprite70(sX, sY+35, _tmp_iEffectFrame%30, dwTime);

	// Illusion
	if ((_tmp_iStatus & 0x01000000) != 0)
		//m_pEffectSpr[73]->PutTransSprite(sX+125, sY+95, _tmp_iEffectFrame%24, dwTime);
		m_pEffectSpr[73]->PutTransSprite70(sX+125, sY+130 - _iAttackerHeight[sOwnerType], _tmp_iEffectFrame%24, dwTime);

	// Illusion movement
	if ((_tmp_iStatus & 0x00200000) != 0)
		//m_pEffectSpr[151]->PutTransSprite(sX+90, sY+55, _tmp_iEffectFrame%24, dwTime);
		m_pEffectSpr[151]->PutTransSprite70(sX+90, sY+90 - _iAttackerHeight[sOwnerType], _tmp_iEffectFrame%24, dwTime);

	// Slate red  (HP)  Flame au sol
	if ((_tmp_iStatus & 0x00400000) != 0)
		//m_pEffectSpr[149]->PutTransSprite(sX+90, sY+120, _tmp_iEffectFrame%15, dwTime);
		m_pEffectSpr[149]->PutTransSprite70(sX+90, sY+120, _tmp_iEffectFrame%15, dwTime);

	// Slate Blue (Mana) Bleu au sol
	if ((_tmp_iStatus & 0x00800000) != 0)
		//m_pEffectSpr[150]->PutTransSprite(sX+1, sY+26, _tmp_iEffectFrame%15, dwTime);
		m_pEffectSpr[150]->PutTransSprite70(sX+1, sY+26, _tmp_iEffectFrame%15, dwTime);

	// Slate Green (XP) Mauve au sol
	if ((_tmp_iStatus & 0x00010000) != 0)
		//m_pEffectSpr[148]->PutTransSprite(sX, sY+32, _tmp_iEffectFrame%23, dwTime);
		m_pEffectSpr[148]->PutTransSprite70(sX, sY+32, _tmp_iEffectFrame%23, dwTime);

	// Hero Flag (Heldenian)  Flameches d'entangle
	if ((_tmp_iStatus & 0x00020000) != 0)
		//m_pEffectSpr[87]->PutTransSprite(sX+53, sY+54, _tmp_iEffectFrame%29, dwTime);
		m_pEffectSpr[87]->PutTransSprite70(sX+53, sY+54, _tmp_iEffectFrame%29, dwTime);
}

/*********************************************************************************************************************
**  void CheckActiveAura2(short sX, short sY, DWORD dwTime,  _tmp_sOwnerType) ( initially Cleroth fixed by Snoopy )	**
**  description			: Generates poison aura around players. This one should be use later...						**
**						: v351 implements this in each drawn function,beter to regroup in single function.			**
**********************************************************************************************************************/
void CGame::CheckActiveAura2(short sX, short sY, DWORD dwTime, short sOwnerType)
{	// Poison
	if ((_tmp_iStatus & 0x80) != 0)
		//m_pEffectSpr[81]->PutTransSprite(sX+115, sY+85, _tmp_iEffectFrame%21, dwTime);
		m_pEffectSpr[81]->PutTransSprite70(sX+115, sY+120 - _iAttackerHeight[sOwnerType], _tmp_iEffectFrame%21, dwTime);
//	_iAttackerHeight[]
}

// 3.51 Level Up Dialog - Changes stats Using Majestic points - Diuuude
void CGame::DrawDialogBox_ChangeStatsMajestic(short msX, short msY)
{
 short sX, sY, szX;
 DWORD dwTime = m_dwCurTime;
 char cTxt[120];
 int iStats;
	sX = m_stDialogBoxInfo[42].sX;
	sY = m_stDialogBoxInfo[42].sY;
	szX = m_stDialogBoxInfo[42].sSizeX;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 2);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX+16, sY+100, 4);

	PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_LEVELUP_SETTING14);
	PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_LEVELUP_SETTING15);

	// Majestic Points Left - Display in green if > 0
	PutString(sX + 20,  sY + 85, DRAW_DIALOGBOX_LEVELUP_SETTING16, RGB(0,0,0));
	wsprintf(cTxt, "%d", m_iGizonItemUpgradeLeft);
	if (m_iGizonItemUpgradeLeft > 0)
	{	PutString(sX + 73,  sY + 102, cTxt, RGB(0,255,0));
	}else
	{	PutString(sX + 73,  sY + 102, cTxt, RGB(0,0,0));
	}
	// Display only MouseOver Button for - (+ is disabled)
	// Strength
	PutString(sX + 24, sY + 125, DRAW_DIALOGBOX_LEVELUP_SETTING4, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iStr);
	PutString(sX + 109, sY + 125, cTxt, RGB(25,35,25));
	iStats = m_iStr + m_cLU_Str;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_iStr)
	{	PutString(sX + 162, sY + 125, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 125, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 127, 6, dwTime);

	// Vitality
	PutString(sX + 24, sY + 144, DRAW_DIALOGBOX_LEVELUP_SETTING5, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iVit);
	PutString(sX + 109, sY + 144, cTxt, RGB(25,35,25));
	iStats = m_iVit + m_cLU_Vit;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_iVit)
	{	PutString(sX + 162, sY + 144, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 144, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 146, 6, dwTime);

	// Dexterity
	PutString(sX + 24, sY + 163, DRAW_DIALOGBOX_LEVELUP_SETTING6, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iDex);
	PutString(sX + 109, sY + 163, cTxt, RGB(25,35,25));
	iStats = m_iDex + m_cLU_Dex;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_iDex)
	{	PutString(sX + 162, sY + 163, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 163, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 165, 6, dwTime);

	// Intelligence
	PutString(sX + 24, sY + 182, DRAW_DIALOGBOX_LEVELUP_SETTING7, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iInt);
	PutString(sX + 109, sY + 182, cTxt, RGB(25,35,25));
	iStats = m_iInt + m_cLU_Int;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_iInt)
	{	PutString(sX + 162, sY + 182, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 182, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 184, 6, dwTime);

	// Magic
	PutString(sX + 24, sY + 201, DRAW_DIALOGBOX_LEVELUP_SETTING8, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iMag);
	PutString(sX + 109, sY + 201, cTxt, RGB(25,35,25));
	iStats = m_iMag + m_cLU_Mag;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_iMag)
	{	PutString(sX + 162, sY + 201, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 201, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 203, 6, dwTime);

	// Charisma
	PutString(sX + 24, sY + 220, DRAW_DIALOGBOX_LEVELUP_SETTING9, RGB(5,5,5));
	wsprintf(cTxt, "%d", m_iCharisma);
	PutString(sX + 109, sY + 220, cTxt, RGB(25,35,25));
	iStats = m_iCharisma + m_cLU_Char;
	wsprintf(cTxt, "%d", iStats);
	if (iStats < m_iCharisma)
	{	PutString(sX + 162, sY + 220, cTxt, RGB(255,0,0));
	}else
	{	PutString(sX + 162, sY + 220, cTxt, RGB(25,35,25));
	}
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228))
		m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 222, 6, dwTime);

	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 17);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 16);

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}


// 3.51 LevelUp Box - Change stats using Majestic - Diuuude
void CGame::DlgBoxClick_ChangeStatsMajestic(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[42].sX;
	sY = m_stDialogBoxInfo[42].sY;

	if ((cStateChange1 != 0) || (cStateChange2 != 0) || (cStateChange3 != 0)){
	// Strength UP - Diuuude
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_cLU_Str < 0))
		{	if (cStateChange1 == DEF_STR)
			{	cStateChange1 = 0;
				m_cLU_Str += 1;
				m_iLU_Point -= 1;
			}else if (cStateChange2 == DEF_STR)
			{	cStateChange2 = 0;
				m_cLU_Str += 1;
				m_iLU_Point -= 1;
			}else if (cStateChange3 == DEF_STR)
			{	cStateChange3 = 0;
				m_cLU_Str += 1;
				m_iLU_Point -= 1;
			}
			PlaySound('E', 14, 5);
		}

		// Vitality UP - Diuuude
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_cLU_Vit < 0)) {
			if (cStateChange1 == DEF_VIT)
			{	cStateChange1 = 0;
				m_cLU_Vit += 1;
				m_iLU_Point -= 1;
			}else if (cStateChange2 == DEF_VIT)
			{	cStateChange2 = 0;
				m_cLU_Vit += 1;
				m_iLU_Point -= 1;
			}else if (cStateChange3 == DEF_VIT)
			{	cStateChange3 = 0;
				m_cLU_Vit += 1;
				m_iLU_Point -= 1;
			}
			PlaySound('E', 14, 5);
		}

		// Dexterity UP - Diuuude
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_cLU_Dex < 0)) {
			if (cStateChange1 == DEF_DEX){
				cStateChange1 = 0;
				m_cLU_Dex += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange2 == DEF_DEX){
				cStateChange2 = 0;
				m_cLU_Dex += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange3 == DEF_DEX){
				cStateChange3 = 0;
				m_cLU_Dex += 1;
				m_iLU_Point -= 1;
			}
			PlaySound('E', 14, 5);
		}

		// Intelligence UP - Diuuude
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_cLU_Int < 0)) {
			if (cStateChange1 == DEF_INT){
				cStateChange1 = 0;
				m_cLU_Int += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange2 == DEF_INT){
				cStateChange2 = 0;
				m_cLU_Int += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange3 == DEF_INT){
				cStateChange3 = 0;
				m_cLU_Int += 1;
				m_iLU_Point -= 1;
			}
			PlaySound('E', 14, 5);
		}

		// Magic UP - Diuuude
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_cLU_Mag < 0)) {
			if (cStateChange1 == DEF_MAG){
				cStateChange1 = 0;
				m_cLU_Mag += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange2 == DEF_MAG){
				cStateChange2 = 0;
				m_cLU_Mag += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange3 == DEF_MAG){
				cStateChange3 = 0;
				m_cLU_Mag += 1;
				m_iLU_Point -= 1;
			}
			PlaySound('E', 14, 5);
		}

		// Charisma UP - Diuuude
		if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_cLU_Char < 0)) {
			if (cStateChange1 == DEF_CHR){
				cStateChange1 = 0;
				m_cLU_Char += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange2 == DEF_CHR){
				cStateChange2 = 0;
				m_cLU_Char += 1;
				m_iLU_Point -= 1;
			}
			else if (cStateChange3 == DEF_CHR){
				cStateChange3 = 0;
				m_cLU_Char += 1;
				m_iLU_Point -= 1;
			}
			PlaySound('E', 14, 5);
		}
	}

	if ((cStateChange1 == 0) || (cStateChange2 == 0) || (cStateChange3 == 0) && (m_iGizonItemUpgradeLeft > 0))
	{	// Strength DOWN - Diuuude
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_iStr > 10))
		{	if (cStateChange1 == 0)
			{	cStateChange1 = DEF_STR;
				m_cLU_Str -= 1;
				m_iLU_Point += 1;
			}else if (cStateChange2 == 0)
			{	cStateChange2 = DEF_STR;
				m_cLU_Str -= 1;
				m_iLU_Point += 1;
			}else
			{	cStateChange3 = DEF_STR;
				m_cLU_Str -= 1;
				m_iLU_Point += 1;
			}
			PlaySound('E', 14, 5);
		}

		// Vitality DOWN - Diuuude
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_iVit > 10)) {
			if (cStateChange1 == 0){
				cStateChange1 = DEF_VIT;
				m_cLU_Vit -= 1;
				m_iLU_Point += 1;
			}
			else if (cStateChange2 == 0){
				cStateChange2 = DEF_VIT;
				m_cLU_Vit -= 1;
				m_iLU_Point += 1;
			}
			else{
				cStateChange3 = DEF_VIT;
				m_cLU_Vit -= 1;
				m_iLU_Point += 1;
			}
			PlaySound('E', 14, 5);
		}

		// Dexterity DOWN - Diuuude
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_iDex > 10)) {
			if (cStateChange1 == 0){
				cStateChange1 = DEF_DEX;
				m_cLU_Dex -= 1;
				m_iLU_Point += 1;
			}
			else if (cStateChange2 == 0){
				cStateChange2 = DEF_DEX;
				m_cLU_Dex -= 1;
				m_iLU_Point += 1;
			}
			else{
				cStateChange3 = DEF_DEX;
				m_cLU_Dex -= 1;
				m_iLU_Point += 1;
			}
			PlaySound('E', 14, 5);
		}

		// Intelligence DOWN - Diuuude
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_iInt > 10))
		{	if (cStateChange1 == 0)
			{	cStateChange1 = DEF_INT;
				m_cLU_Int -= 1;
				m_iLU_Point += 1;
			}else if (cStateChange2 == 0)
			{	cStateChange2 = DEF_INT;
				m_cLU_Int -= 1;
				m_iLU_Point += 1;
			}else
			{	cStateChange3 = DEF_INT;
				m_cLU_Int -= 1;
				m_iLU_Point += 1;
			}
			PlaySound('E', 14, 5);
		}

		// Magic DOWN - Diuuude
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_iMag > 10)) {
			if (cStateChange1 == 0){
				cStateChange1 = DEF_MAG;
				m_cLU_Mag -= 1;
				m_iLU_Point += 1;
			}
			else if (cStateChange2 == 0){
				cStateChange2 = DEF_MAG;
				m_cLU_Mag -= 1;
				m_iLU_Point += 1;
			}
			else{
				cStateChange3 = DEF_MAG;
				m_cLU_Mag -= 1;
				m_iLU_Point += 1;
			}
			PlaySound('E', 14, 5);
		}

		// Charisma DOWN - Diuuude
		if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_iCharisma > 10)) {
			if (cStateChange1 == 0){
				cStateChange1 = DEF_CHR;
				m_cLU_Char -= 1;
				m_iLU_Point += 1;
			}
			else if (cStateChange2 == 0){
				cStateChange2 = DEF_CHR;
				m_cLU_Char -= 1;
				m_iLU_Point += 1;
			}
			else{
				cStateChange3 = DEF_CHR;
				m_cLU_Char -= 1;
				m_iLU_Point += 1;
			}
			PlaySound('E', 14, 5);
		}
	}else
	{	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Send command to HG - Diuuude
			bSendCommand(MSGID_STATECHANGEPOINT, NULL, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(42);
			PlaySound('E', 14, 5);
	}	}
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		DisableDialogBox(42);
		PlaySound('E', 14, 5);
	}
}

void CGame::DrawAngel(int iSprite, short sX, short sY, char cFrame, DWORD dwTime)
{	if  ((_tmp_iStatus & 0x1000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT+iSprite]->PutSpriteFast(sX, sY, cFrame, dwTime);  //AngelicPendant(STR)
	else if ((_tmp_iStatus & 0x2000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT+(50*1)+iSprite]->PutSpriteFast(sX, sY, cFrame, dwTime); //AngelicPendant(DEX)
	else if ((_tmp_iStatus & 0x4000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT+(50*2)+iSprite]->PutSpriteFast(sX, sY-20, cFrame, dwTime);//AngelicPendant(INT)
	else if ((_tmp_iStatus & 0x8000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT+(50*3)+iSprite]->PutSpriteFast(sX, sY-20, cFrame, dwTime);//AngelicPendant(MAG)

}
/*********************************************************************************************************************
**  int CGame::bHasHeroSet( short m_sAppr3, short m_sAppr3, char OwnerType)		( Snoopy )							**
**  description			:: check weather the object (is character) is using a hero set (1:war, 2:mage)				**
**********************************************************************************************************************/
int CGame::bHasHeroSet(short Appr3, short Appr4, char OwnerType)
{	char cArmor, cLeg, cBerk, cHat;
	cArmor = (Appr3 & 0xF000) >> 12;
	cLeg   = (Appr3 & 0x0F00) >> 8;
	cHat   = (Appr3 & 0x00F0) >> 4;
	cBerk  =  Appr3 & 0x000F;
	switch (OwnerType){
	case 1:
	case 2:
	case 3:
		if ((cArmor == 8) &&(cLeg == 5)&&(cHat == 9) &&(cBerk == 3)) return (1); // Warr elv M
		if ((cArmor == 9) &&(cLeg == 6)&&(cHat == 10)&&(cBerk == 4)) return (1); // Warr ares M
		if ((cArmor == 10)&&(cLeg == 5)&&(cHat == 11)&&(cBerk == 3)) return (2); // Mage elv M
		if ((cArmor == 11)&&(cLeg == 6)&&(cHat == 12)&&(cBerk == 4)) return (2); // Mage ares M
		break;
	case 4:
	case 5:
	case 6: // fixed
		if ((cArmor == 9) &&(cLeg == 6)&&(cHat == 9) &&(cBerk == 4)) return (1); //warr elv W
		if ((cArmor == 10)&&(cLeg == 7)&&(cHat == 10)&&(cBerk == 5)) return (1); //warr ares W
		if ((cArmor == 11)&&(cLeg == 6)&&(cHat == 11)&&(cBerk == 4)) return (2); //mage elv W
		if ((cArmor == 12)&&(cLeg == 7)&&(cHat == 12)&&(cBerk == 5)) return (2); //mage ares W
		break;
	}
	return 0;
}
/*********************************************************************************************************************
**  void ShowHeldenianVictory( short sSide)				( Snoopy )													**
**  description			: Shows the Heldenian's End window															**
**********************************************************************************************************************/
void CGame::ShowHeldenianVictory(short sSide)
{	int i, iPlayerSide;
	DisableDialogBox(18);
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{	if (m_pMsgTextList[i] != NULL)
			delete m_pMsgTextList[i];
		m_pMsgTextList[i] = NULL;
	}
	if( m_bCitizen == FALSE ) iPlayerSide = 0;
	else if (m_bAresden == TRUE) iPlayerSide = 1;
	else if (m_bAresden == FALSE) iPlayerSide = 2;
	switch (sSide) {
	case 0:
		PlaySound('E', 25, 0, 0);
		m_pMsgTextList[0] = new class CMsg(NULL, "Heldenian holy war has been closed!", NULL);
		m_pMsgTextList[1] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[2] = new class CMsg(NULL, "Heldenian Holy war ended", NULL);
		m_pMsgTextList[3] = new class CMsg(NULL, "in a tie.", NULL);
		break;
	case 1:
		PlaySound('E', 25, 0, 0);
		m_pMsgTextList[0] = new class CMsg(NULL, "Heldenian holy war has been closed!", NULL);
		m_pMsgTextList[1] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[2] = new class CMsg(NULL, "Heldenian Holy war ended", NULL);
		m_pMsgTextList[3] = new class CMsg(NULL, "in favor of Aresden.", NULL);
		break;
	case 2:
		PlaySound('E', 25, 0, 0);
		m_pMsgTextList[0] = new class CMsg(NULL, "Heldenian holy war has been closed!", NULL);
		m_pMsgTextList[1] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[2] = new class CMsg(NULL, "Heldenian Holy war ended", NULL);
		m_pMsgTextList[3] = new class CMsg(NULL, "in favor of Elvine.", NULL);
		break;
	}
	m_pMsgTextList[4] = new class CMsg(NULL, " ", NULL);

	if (   ((iPlayerSide != 1) && (iPlayerSide != 2))   // Player not a normal citizen
		|| (sSide == 0))								// or no winner
	{	PlaySound('E', 25, 0, 0);
		m_pMsgTextList[5] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[6] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[7] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[8] = new class CMsg(NULL, " ", NULL);
	}else
	{ 	if (sSide == iPlayerSide)
		{	PlaySound('E', 23, 0, 0);
			PlaySound('C', 21, 0, 0);
			PlaySound('C', 22, 0, 0);
			m_pMsgTextList[5] = new class CMsg(NULL, "Congratulation.", NULL);
			m_pMsgTextList[6] = new class CMsg(NULL, "As cityzen of victory,", NULL);
			m_pMsgTextList[7] = new class CMsg(NULL, "You will recieve a reward.", NULL);
			m_pMsgTextList[8] = new class CMsg(NULL, "      ", NULL);
		}else
		{	PlaySound('E', 24, 0, 0);
			PlaySound('C', 12, 0, 0);
			PlaySound('C', 13, 0, 0);
			m_pMsgTextList[5] = new class CMsg(NULL, "To our regret", NULL);
			m_pMsgTextList[6] = new class CMsg(NULL, "As cityzen of defeat,", NULL);
			m_pMsgTextList[7] = new class CMsg(NULL, "You cannot recieve any reward.", NULL);
			m_pMsgTextList[8] = new class CMsg(NULL, "     ", NULL);
	}	}
	for (i = 9; i < 18; i++)
		m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
	EnableDialogBox(18, NULL, NULL, NULL);
	DisableDialogBox(36);
	DisableDialogBox(37);
	DisableDialogBox(38);
}

/*********************************************************************************************************************
**  void DrawDialogBox_Resurect(short msX, short msY) 				( Snoopy )										**
**  description			: Asks the player if he accepts resurection													**
**********************************************************************************************************************/
void CGame::DrawDialogBox_Resurect(short msX, short msY)
{short sX, sY;
//00476D02  |. 68 A4474C00    PUSH 004C47A4                    ;  ASCII "Someone intend to resurrect you."
//00476D41  |. 68 8C474C00    PUSH 004C478C                    ;  ASCII "Will you revive here?"
	sX = m_stDialogBoxInfo[50].sX;
	sY = m_stDialogBoxInfo[50].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	PutString(sX + 50, sY + 20, "Someone intend to resurrect you.", RGB(4,0,50));
	PutString(sX + 80, sY + 35, "Will you revive here?", RGB(4,0,50));

	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55 ,19);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55 , 18);

	if ((msX >= sX + 170 ) && (msX <= sX + 170 + DEF_BTNSZX ) && (msY >= sY + 55 ) && (msY <= sY + 55 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170 , sY + 55 , 3);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55 , 2);
}

/*********************************************************************************************************************
**  void DlgBoxClick_ItemDrop(short msX, short msY)			( Snoopy )												**
**  description			: Response of the player if he accepts resurection or not									**
**********************************************************************************************************************/
void CGame::DlgBoxClick_Resurect(short msX, short msY)
{short sX, sY;
//#define DEF_REQUEST_RESURRECTPLAYER_YES				0x0FC94214
//#define DEF_REQUEST_RESURRECTPLAYER_NO				0x0FC94215
	sX = m_stDialogBoxInfo[50].sX;
	sY = m_stDialogBoxInfo[50].sY;
	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
	{   // yes
		bSendCommand(DEF_REQUEST_RESURRECTPLAYER_YES, 0, 0, 0, 0 ,0, NULL, 0);
		DisableDialogBox(50);
	}else if ((msX >= sX + 170 ) && (msX <= sX + 170 + DEF_BTNSZX ) && (msY >= sY + 55 ) && (msY <= sY + 55 + DEF_BTNSZY))
	{	// no
		bSendCommand(DEF_REQUEST_RESURRECTPLAYER_NO, 0, 0, 0, 0 ,0, NULL, 0);
		DisableDialogBox(50);
	}
}

/*********************************************************************************************************************
**  void 	ResponseHeldenianTeleportList(char *pData)									(  Snoopy )					**
**  description			: Gail's TP																					**
**********************************************************************************************************************/
void CGame::ResponseHeldenianTeleportList(char *pData)
{	char *cp;
	int  *ip, i;
#ifdef _DEBUG
	AddEventList("Teleport ???", 10);
#endif
	cp = pData + 6;
	ip = (int*) cp;
	m_iTeleportMapCount = *ip;
	cp += 4;
	for ( i = 0 ; i < m_iTeleportMapCount ; i++)
	{	ip = (int*)cp;
		m_stTeleportList[i].iIndex = *ip;
		cp += 4;
		ZeroMemory(m_stTeleportList[i].mapname, sizeof(m_stTeleportList[i].mapname) );
		memcpy(m_stTeleportList[i].mapname, cp, 10);
		cp += 10;
		ip = (int*)cp;
		m_stTeleportList[i].iX = *ip;
		cp += 4;
		ip = (int*)cp;
		m_stTeleportList[i].iY = *ip;
		cp += 4;
		ip = (int*)cp;
		m_stTeleportList[i].iCost = *ip;
		cp += 4;
	}
}

/*********************************************************************************************************************
**  void DrawDialogBox_CMDHallMenu(short msX, short msY)			( Snoopy )										**
**  description			: Draw the diag																				**
**********************************************************************************************************************/
void CGame::DrawDialogBox_CMDHallMenu(short msX, short msY)
{short sX, sY, szX;
 char cTxt[120];
	sX = m_stDialogBoxInfo[51].sX;
	sY = m_stDialogBoxInfo[51].sY;
	szX = m_stDialogBoxInfo[51].sSizeX;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

	switch (m_stDialogBoxInfo[51].cMode) {
	case 0: // initial diag
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
			 PutAlignedString(sX, sX + szX, sY + 70, "Teleport to Battle Field", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 70, "Teleport to Battle Field", 4,0,50);

		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
			 PutAlignedString(sX, sX + szX, sY + 95, "Hire a soldier", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 95, "Hire a soldier", 4,0,50);

		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
			 PutAlignedString(sX, sX + szX, sY + 120, "Taking Flags", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 120, "Taking Flags", 4,0,50);
		// Angels
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
			 PutAlignedString(sX, sX + szX, sY + 145, "Receive a Tutelary Angel", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 145, "Receive a Tutelary Angel", 4,0,50);
		break;

	case 1: // TP diag
		if( m_iTeleportMapCount > 0 )
		{	//PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_CITYHALL_MENU69, 55,25,25); // "Teleporting to dungeon level 2."
			//PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU70, 55,25,25); // "5000Gold is required"
			//PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU71, 55,25,25); //
			//PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU72, 55,25,25);//
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

	case 2: // Soldier diag
		PutAlignedString(sX, sX + szX, sY + 45, "You will hire a soldier by summon points", 255,255,255);
		if ((m_iConstructionPoint >= 2000) && (m_bIsCrusadeMode == FALSE))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
				 PutAlignedString(sX, sX + szX, sY + 70, "Sorceress             2000 Point", 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 70, "Sorceress             2000 Point", 4,0,50);
		}else PutAlignedString(sX, sX + szX, sY + 70, "Sorceress             2000 Point", 65,65,65);

		if ((m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == FALSE))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
			 PutAlignedString(sX, sX + szX, sY + 95, "Ancient Temple Knight 3000 Point", 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 95, "Ancient Temple Knight 3000 Point", 4,0,50);
		}else PutAlignedString(sX, sX + szX, sY + 95, "Ancient Temple Knight 3000 Point", 65,65,65);

		if ((m_iConstructionPoint >= 1500) && (m_bIsCrusadeMode == FALSE))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
				PutAlignedString(sX, sX + szX, sY + 120, "Elf Master            1500 Point", 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 120, "Elf Master            1500 Point", 4,0,50);
		}else PutAlignedString(sX, sX + szX, sY + 120, "Elf Master            1500 Point", 65,65,65);

		if ((m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == FALSE))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 171))
				PutAlignedString(sX, sX + szX, sY + 145, "Dark Shadow Knight    3000 Point", 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 145, "Dark Shadow Knight    3000 Point", 4,0,50);
		}else PutAlignedString(sX, sX + szX, sY + 145, "Dark Shadow Knight    3000 Point", 65,65,65);

		if ((m_iConstructionPoint >= 4000) && (m_bIsCrusadeMode == FALSE))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
				PutAlignedString(sX, sX + szX, sY + 170, "Heavy Battle Tank     4000 Point", 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 170, "Heavy Battle Tank     4000 Point", 4,0,50);
		}else PutAlignedString(sX, sX + szX, sY + 170, "Heavy Battle Tank     4000 Point", 65,65,65);

		if ((m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == FALSE))
		{	if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
				PutAlignedString(sX, sX + szX, sY + 195, "Barbarian             3000 Point", 255,255,255);
			else PutAlignedString(sX, sX + szX, sY + 195, "Barbarian             3000 Point", 4,0,50);
		}else PutAlignedString(sX, sX + szX, sY + 195, "Barbarian             3000 Point", 65,65,65);

		PutAlignedString(sX, sX + szX, sY + 220,"You should join a guild to hire soldiers.", 4,0,50);
		wsprintf(G_cTxt,"Summon points : %d", m_iConstructionPoint);
		PutAlignedString(sX, sX + szX, sY + 250, G_cTxt, 4,0,50);
		PutAlignedString(sX, sX + szX, sY + 280, "Maximum summon points : 12000 points.", 4,0,50);
		PutAlignedString(sX, sX + szX, sY + 300, "Maximum hiring number : 5 ", 4,0,50);
		break;

	case 3: // Hire a Flag Diag
		PutAlignedString(sX, sX + szX, sY + 45,"You may acquire Flags with EK points.", 4,0,50);
		PutAlignedString(sX, sX + szX, sY + 70,"Price is 10 EK per Flag.", 4,0,50);
		if( (msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 140) && (msY <= sY + 165) )
			PutAlignedString(sX, sX + szX, sY + 140, "Take a Flag", 255,255,255);
		else
			PutAlignedString(sX, sX + szX, sY + 140, "Take a Flag", 250,250,0);
		break;

	case 4: // Tutelar Angel Diag
		PutAlignedString(sX, sX + szX, sY + 45, "5 magesty points will be deducted", 4,0,50);
		PutAlignedString(sX, sX + szX, sY + 80, "upon receiving the Pendant of Tutelary Angel.", 4,0,50);
		PutAlignedString(sX, sX + szX, sY + 105, "Would you like to receive the Tutelary Angel?", 4,0,50);
		wsprintf(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE11, m_iGizonItemUpgradeLeft);// "Item upgrade point : %d"
		PutAlignedString(sX, sX + szX, sY + 140, G_cTxt, 0,0,0);

		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 175) && (msY < sY + 200)
			&& (m_iGizonItemUpgradeLeft >4))
			 PutAlignedString(sX, sX + szX, sY + 175, "Tutelary Angel (STR) will be handed out.", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 175, "Tutelary Angel (STR) will be handed out.", 250,250,0);

		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 200) && (msY < sY + 225)
			&& (m_iGizonItemUpgradeLeft >4))
			 PutAlignedString(sX, sX + szX, sY + 200, "Tutelary Angel (DEX) will be handed out.", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 200, "Tutelary Angel (DEX) will be handed out.", 250,250,0);

		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 225) && (msY < sY + 250)
			&& (m_iGizonItemUpgradeLeft >4))
			 PutAlignedString(sX, sX + szX, sY + 225, "Tutelary Angel (INT) will be handed out.", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 225, "Tutelary Angel (INT) will be handed out.", 250,250,0);

		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 250) && (msY < sY + 275)
			&& (m_iGizonItemUpgradeLeft >4))
			 PutAlignedString(sX, sX + szX, sY + 250, "Tutelary Angel (MAG) will be handed out.", 255,255,255);
		else PutAlignedString(sX, sX + szX, sY + 250, "Tutelary Angel (MAG) will be handed out.", 250,250,0);

		break;
	}
}

/*********************************************************************************************************************
**  void DlgBoxClick_CMDHallMenu(short msX, short msY)			( Snoopy )											**
**  description			: Response of the player if he accepts resurection or not									**
**********************************************************************************************************************/
void CGame::DlgBoxClick_CMDHallMenu(short msX, short msY)
{short sX, sY;
	sX = m_stDialogBoxInfo[51].sX;
	sY = m_stDialogBoxInfo[51].sY;
	switch (m_stDialogBoxInfo[51].cMode) {
	case 0: // initial diag
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
		{	m_stDialogBoxInfo[51].cMode = 1; // TP diag
			m_iTeleportMapCount = -1;
			bSendCommand(MSGID_REQUEST_HELDENIAN_TP_LIST, NULL, NULL, NULL, NULL, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
		{	m_stDialogBoxInfo[51].cMode = 2; // Soldier Diag
			PlaySound('E', 14, 5);
		}
		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145)
			/*&& (m_iEnemyKillCount >= 3)*/)
		{	m_stDialogBoxInfo[51].cMode = 3; // Flag Diag
			PlaySound('E', 14, 5);
		}
		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145)
			/*&& (m_iEnemyKillCount >= 3)*/)
		{	m_stDialogBoxInfo[51].cMode = 3; // Flag Diag
			PlaySound('E', 14, 5);
		}

		if (   (msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170)
			/*&& (m_iGizonItemUpgradeLeft >= 5)*/)
		{	m_stDialogBoxInfo[51].cMode = 4; // Flag Diag
			PlaySound('E', 14, 5);
		}


	case 1: // TP now
		if( m_iTeleportMapCount > 0 )
		{	for( int i=0 ; i<m_iTeleportMapCount ; i++ )
			{	if( (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i*15) && (msY <= sY + 144 + i*15) )
				{	bSendCommand(MSGID_REQUEST_HELDENIAN_TP, NULL, NULL, m_stTeleportList[i].iIndex, NULL, NULL, NULL);
					DisableDialogBox(51);
					return;
		}	}	}
		break;

	case 2: // Buy a soldier scroll
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 70) && (msY < sY + 95)
			&& (m_iConstructionPoint >= 2000) && (m_bIsCrusadeMode == FALSE)) // Sorceress
		{	bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 875, 1, 2, 3, 4, "Gail", 5);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 95) && (msY < sY + 120)
			&& (m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == FALSE)) // ATK
		{	bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 876, 0, 0, 0, 0, "Gail", 0);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 120) && (msY < sY + 145)
			&& (m_iConstructionPoint >= 1500) && (m_bIsCrusadeMode == FALSE)) // Elf
		{	bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 877, 0, 0, 0, 0, "Gail", 0);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 145) && (msY < sY + 170)
			&& (m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == FALSE)) // DSK
		{	bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 878, 0, 0, 0, 0, "Gail", 0);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 170) && (msY < sY + 195)
			&& (m_iConstructionPoint >= 4000) && (m_bIsCrusadeMode == FALSE)) // HBT
		{	bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 879, 0, 0, 0, 0, "Gail", 0);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 195) && (msY < sY + 220)
			&& (m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == FALSE)) // Barbarian
		{	bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 880, 0, 0, 0, 0, "Gail", 0);
			PlaySound('E', 14, 5);
		}
		break;

	case 3: // Buy a Flag
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 140) && (msY <= sY + 165)
			&& (m_iEnemyKillCount >=3))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETOCCUPYFLAG, 0, 0, 0, 0, 0, 0);
			PlaySound('E', 14, 5);
		}
		break;

	case 4: // Buy an Angel
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 175) && (msY <= sY + 200)
			&& ( m_iGizonItemUpgradeLeft>=5))
		{	bSendCommand(DEF_REQUEST_ANGEL, NULL, NULL, 1, NULL, NULL, "Gail", NULL);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 200) && (msY <= sY + 225)
			&& ( m_iGizonItemUpgradeLeft>=5))
		{	bSendCommand(DEF_REQUEST_ANGEL, NULL, NULL, 2, NULL, NULL, "Gail", NULL);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 225) && (msY <= sY + 250)
			&& ( m_iGizonItemUpgradeLeft>=5))
		{	bSendCommand(DEF_REQUEST_ANGEL, NULL, NULL, 3, NULL, NULL, "Gail", NULL);
			PlaySound('E', 14, 5);
		}
		if (   (msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 250) && (msY <= sY + 275)
			&& ( m_iGizonItemUpgradeLeft>=5))
		{	bSendCommand(DEF_REQUEST_ANGEL, NULL, NULL, 4, NULL, NULL, "Gail", NULL);
			PlaySound('E', 14, 5);
		}

		break;
	}
}
/*********************************************************************************************************************
**  bool DKGlare(int iWeaponIndex, int iWeaponIndex, int *iWeaponGlare)	( Snoopy )									**
**  description			: test glowing condition for DK set															**
**********************************************************************************************************************/
void CGame::DKGlare(int iWeaponColor, int iWeaponIndex, int *iWeaponGlare)
{	if (iWeaponColor != 9) return;
	if (   ((iWeaponIndex >= DEF_SPRID_WEAPON_M + 64*14)&&(iWeaponIndex < DEF_SPRID_WEAPON_M + 64*14 + 56)) //msw3
		|| ((iWeaponIndex >= DEF_SPRID_WEAPON_W + 64*14)&&(iWeaponIndex < DEF_SPRID_WEAPON_W + 64*14 + 56))) //wsw3
	{	*iWeaponGlare = 3;
	}else if (  ((iWeaponIndex >= DEF_SPRID_WEAPON_M + 64*37)&&(iWeaponIndex < DEF_SPRID_WEAPON_M + 64*37 + 56)) //MStaff3
		|| ((iWeaponIndex >= DEF_SPRID_WEAPON_W + 64*37)&&(iWeaponIndex < DEF_SPRID_WEAPON_W + 64*37 + 56)))//WStaff3
	{	*iWeaponGlare = 2;
	}
}
/*********************************************************************************************************************
**  void DrawDruncncity()	( Snoopy )																				**
**  description			: 	Placeholder for Druncncity effects (nota: bubbles already coded)						**
**********************************************************************************************************************/
void CGame::DrawDruncncity()
{	//DebugLog("druncncity");
}

// Manque ondulations et coloration des persos en verdatre....
// Druncncity:
/*401E60  /$ 83EC 7C            SUB ESP,7C
00401E63  |. 56                 PUSH ESI
00401E64  |. 8BF1               MOV ESI,ECX
00401E66  |. 8B86 10000300      MOV EAX,DWORD PTR DS:[ESI+30010]
00401E6C  |. 85C0               TEST EAX,EAX
00401E6E  |. 75 05              JNZ SHORT 00401E75
00401E70  |. 5E                 POP ESI
00401E71  |. 83C4 7C            ADD ESP,7C
00401E74  |. C3                 RETN
00401E75  |> 6A 00              PUSH 0
00401E77  |. 8D5424 08          LEA EDX,DWORD PTR SS:[ESP+8]
00401E7B  |. 6A 01              PUSH 1
00401E7D  |. C74424 0C 7C000000 MOV DWORD PTR SS:[ESP+C],7C
00401E85  |. 8B08               MOV ECX,DWORD PTR DS:[EAX]
00401E87  |. 52                 PUSH EDX
00401E88  |. 6A 00              PUSH 0
00401E8A  |. 50                 PUSH EAX
00401E8B  |. FF51 64            CALL NEAR DWORD PTR DS:[ECX+64]
00401E8E  |. 85C0               TEST EAX,EAX
00401E90  |. 74 07              JE SHORT 00401E99
00401E92  |. 33C0               XOR EAX,EAX
00401E94  |. 5E                 POP ESI
00401E95  |. 83C4 7C            ADD ESP,7C
00401E98  |. C3                 RETN
00401E99  |> 8B4C24 0C          MOV ECX,DWORD PTR SS:[ESP+C]
00401E9D  |. 8B4424 28          MOV EAX,DWORD PTR SS:[ESP+28]
00401EA1  |. 8B5424 10          MOV EDX,DWORD PTR SS:[ESP+10]
00401EA5  |. 83C1 D8            ADD ECX,-28
00401EA8  |. 50                 PUSH EAX                                ; /Arg3
00401EA9  |. 51                 PUSH ECX                                ; |Arg2
00401EAA  |. 8B8E DC010300      MOV ECX,DWORD PTR DS:[ESI+301DC]        ; |
00401EB0  |. 52                 PUSH EDX                                ; |Arg1
00401EB1  |. E8 4AF2FFFF        CALL 00401100                           ; \Original.00401100
00401EB6  |. 8B86 10000300      MOV EAX,DWORD PTR DS:[ESI+30010]
00401EBC  |. 6A 00              PUSH 0
00401EBE  |. 50                 PUSH EAX
00401EBF  |. 8B08               MOV ECX,DWORD PTR DS:[EAX]
00401EC1  |. FF91 80000000      CALL NEAR DWORD PTR DS:[ECX+80]
00401EC7  |. B8 01000000        MOV EAX,1
00401ECC  |. 5E                 POP ESI
00401ECD  |. 83C4 7C            ADD ESP,7C
00401ED0  \. C3                 RETN*/

/*00401100  /$ 81EC C0010000      SUB ESP,1C0                             ;   colore le personage
00401106  |. 53                 PUSH EBX
00401107  |. 56                 PUSH ESI
00401108  |. 8BF1               MOV ESI,ECX
0040110A  |. 33DB               XOR EBX,EBX
0040110C  |. 8B8C24 D4010000    MOV ECX,DWORD PTR SS:[ESP+1D4]
00401113  |. 3BCB               CMP ECX,EBX
00401115  |. 0F84 CE030000      JE 004014E9
0040111B  |. 55                 PUSH EBP
0040111C  |. 8BAC24 D0010000    MOV EBP,DWORD PTR SS:[ESP+1D0]
00401123  |. 0FAFAC24 D4010000  IMUL EBP,DWORD PTR SS:[ESP+1D4]
0040112B  |. 57                 PUSH EDI
0040112C  |. 896C24 14          MOV DWORD PTR SS:[ESP+14],EBP
00401130  |. 8D442D 00          LEA EAX,DWORD PTR SS:[EBP+EBP]
00401134  |. 894424 10          MOV DWORD PTR SS:[ESP+10],EAX
00401138  |. 50                 PUSH EAX
00401139  |. 8B46 34            MOV EAX,DWORD PTR DS:[ESI+34]
0040113C  |. 51                 PUSH ECX
0040113D  |. 50                 PUSH EAX
0040113E  |. FF15 E0C04B00      CALL NEAR DWORD PTR DS:[4BC0E0]         ;  Original.00401000
00401144  |. BA 06000000        MOV EDX,6
00401149  |. B9 03000000        MOV ECX,3
0040114E  |. 899424 80000000    MOV DWORD PTR SS:[ESP+80],EDX
00401155  |. 899424 84000000    MOV DWORD PTR SS:[ESP+84],EDX
0040115C  |. 899424 88000000    MOV DWORD PTR SS:[ESP+88],EDX
00401163  |. 899424 8C000000    MOV DWORD PTR SS:[ESP+8C],EDX
0040116A  |. 899424 90000000    MOV DWORD PTR SS:[ESP+90],EDX
00401171  |. 899424 94000000    MOV DWORD PTR SS:[ESP+94],EDX
00401178  |. 899424 98000000    MOV DWORD PTR SS:[ESP+98],EDX
0040117F  |. 899424 9C000000    MOV DWORD PTR SS:[ESP+9C],EDX
00401186  |. 899424 A0000000    MOV DWORD PTR SS:[ESP+A0],EDX
0040118D  |. 899424 A4000000    MOV DWORD PTR SS:[ESP+A4],EDX
00401194  |. BF 04000000        MOV EDI,4
00401199  |. B8 05000000        MOV EAX,5
0040119E  |. BA 02000000        MOV EDX,2
004011A3  |. 83C4 0C            ADD ESP,0C
004011A6  |. 894C24 18          MOV DWORD PTR SS:[ESP+18],ECX
004011AA  |. 894C24 1C          MOV DWORD PTR SS:[ESP+1C],ECX
004011AE  |. 894C24 20          MOV DWORD PTR SS:[ESP+20],ECX
004011B2  |. 894C24 24          MOV DWORD PTR SS:[ESP+24],ECX
004011B6  |. 894C24 28          MOV DWORD PTR SS:[ESP+28],ECX
004011BA  |. 897C24 2C          MOV DWORD PTR SS:[ESP+2C],EDI
004011BE  |. 897C24 30          MOV DWORD PTR SS:[ESP+30],EDI
004011C2  |. 897C24 34          MOV DWORD PTR SS:[ESP+34],EDI
004011C6  |. 897C24 38          MOV DWORD PTR SS:[ESP+38],EDI
004011CA  |. 897C24 3C          MOV DWORD PTR SS:[ESP+3C],EDI
004011CE  |. 897C24 40          MOV DWORD PTR SS:[ESP+40],EDI
004011D2  |. 897C24 44          MOV DWORD PTR SS:[ESP+44],EDI
004011D6  |. 897C24 48          MOV DWORD PTR SS:[ESP+48],EDI
004011DA  |. 894424 4C          MOV DWORD PTR SS:[ESP+4C],EAX
004011DE  |. 894424 50          MOV DWORD PTR SS:[ESP+50],EAX
004011E2  |. 894424 54          MOV DWORD PTR SS:[ESP+54],EAX
004011E6  |. 894424 58          MOV DWORD PTR SS:[ESP+58],EAX
004011EA  |. 894424 5C          MOV DWORD PTR SS:[ESP+5C],EAX
004011EE  |. 894424 60          MOV DWORD PTR SS:[ESP+60],EAX
004011F2  |. 894424 64          MOV DWORD PTR SS:[ESP+64],EAX
004011F6  |. 894424 68          MOV DWORD PTR SS:[ESP+68],EAX
004011FA  |. 894424 6C          MOV DWORD PTR SS:[ESP+6C],EAX
004011FE  |. 894424 70          MOV DWORD PTR SS:[ESP+70],EAX
00401202  |. 898424 9C000000    MOV DWORD PTR SS:[ESP+9C],EAX
00401209  |. 898424 A0000000    MOV DWORD PTR SS:[ESP+A0],EAX
00401210  |. 898424 A4000000    MOV DWORD PTR SS:[ESP+A4],EAX
00401217  |. 898424 A8000000    MOV DWORD PTR SS:[ESP+A8],EAX
0040121E  |. 898424 AC000000    MOV DWORD PTR SS:[ESP+AC],EAX
00401225  |. 898424 B0000000    MOV DWORD PTR SS:[ESP+B0],EAX
0040122C  |. 898424 B4000000    MOV DWORD PTR SS:[ESP+B4],EAX
00401233  |. 898424 B8000000    MOV DWORD PTR SS:[ESP+B8],EAX
0040123A  |. 898424 BC000000    MOV DWORD PTR SS:[ESP+BC],EAX
00401241  |. 89BC24 C0000000    MOV DWORD PTR SS:[ESP+C0],EDI
00401248  |. 89BC24 C4000000    MOV DWORD PTR SS:[ESP+C4],EDI
0040124F  |. 89BC24 C8000000    MOV DWORD PTR SS:[ESP+C8],EDI
00401256  |. 89BC24 CC000000    MOV DWORD PTR SS:[ESP+CC],EDI
0040125D  |. 89BC24 D0000000    MOV DWORD PTR SS:[ESP+D0],EDI
00401264  |. 89BC24 D4000000    MOV DWORD PTR SS:[ESP+D4],EDI
0040126B  |. 89BC24 D8000000    MOV DWORD PTR SS:[ESP+D8],EDI
00401272  |. 89BC24 DC000000    MOV DWORD PTR SS:[ESP+DC],EDI
00401279  |. 89BC24 E0000000    MOV DWORD PTR SS:[ESP+E0],EDI
00401280  |. 898C24 E4000000    MOV DWORD PTR SS:[ESP+E4],ECX
00401287  |. 898C24 E8000000    MOV DWORD PTR SS:[ESP+E8],ECX
0040128E  |. 898C24 EC000000    MOV DWORD PTR SS:[ESP+EC],ECX
00401295  |. 898C24 F0000000    MOV DWORD PTR SS:[ESP+F0],ECX
0040129C  |. 898C24 F4000000    MOV DWORD PTR SS:[ESP+F4],ECX
004012A3  |. 898C24 F8000000    MOV DWORD PTR SS:[ESP+F8],ECX
004012AA  |. 898C24 FC000000    MOV DWORD PTR SS:[ESP+FC],ECX
004012B1  |. 898C24 00010000    MOV DWORD PTR SS:[ESP+100],ECX
004012B8  |. 899424 04010000    MOV DWORD PTR SS:[ESP+104],EDX
004012BF  |. 899424 08010000    MOV DWORD PTR SS:[ESP+108],EDX
004012C6  |. 899424 0C010000    MOV DWORD PTR SS:[ESP+10C],EDX
004012CD  |. 899424 10010000    MOV DWORD PTR SS:[ESP+110],EDX
004012D4  |. 898C24 BC010000    MOV DWORD PTR SS:[ESP+1BC],ECX
004012DB  |. 898C24 C0010000    MOV DWORD PTR SS:[ESP+1C0],ECX
004012E2  |. 898C24 C4010000    MOV DWORD PTR SS:[ESP+1C4],ECX
004012E9  |. 898C24 C8010000    MOV DWORD PTR SS:[ESP+1C8],ECX
004012F0  |. 898C24 CC010000    MOV DWORD PTR SS:[ESP+1CC],ECX
004012F7  |. B8 01000000        MOV EAX,1
004012FC  |. 33C9               XOR ECX,ECX
004012FE  |. 3BEB               CMP EBP,EBX
00401300  |. 899424 14010000    MOV DWORD PTR SS:[ESP+114],EDX
00401307  |. 899424 18010000    MOV DWORD PTR SS:[ESP+118],EDX
0040130E  |. 899424 1C010000    MOV DWORD PTR SS:[ESP+11C],EDX
00401315  |. 899424 20010000    MOV DWORD PTR SS:[ESP+120],EDX
0040131C  |. 899424 24010000    MOV DWORD PTR SS:[ESP+124],EDX
00401323  |. 898424 28010000    MOV DWORD PTR SS:[ESP+128],EAX
0040132A  |. 898424 2C010000    MOV DWORD PTR SS:[ESP+12C],EAX
00401331  |. 898424 30010000    MOV DWORD PTR SS:[ESP+130],EAX
00401338  |. 898424 34010000    MOV DWORD PTR SS:[ESP+134],EAX
0040133F  |. 898424 38010000    MOV DWORD PTR SS:[ESP+138],EAX
00401346  |. 898424 3C010000    MOV DWORD PTR SS:[ESP+13C],EAX
0040134D  |. 898424 40010000    MOV DWORD PTR SS:[ESP+140],EAX
00401354  |. 898424 44010000    MOV DWORD PTR SS:[ESP+144],EAX
0040135B  |. 898424 48010000    MOV DWORD PTR SS:[ESP+148],EAX
00401362  |. 898424 4C010000    MOV DWORD PTR SS:[ESP+14C],EAX
00401369  |. 898424 50010000    MOV DWORD PTR SS:[ESP+150],EAX
00401370  |. 899C24 54010000    MOV DWORD PTR SS:[ESP+154],EBX
00401377  |. 899C24 58010000    MOV DWORD PTR SS:[ESP+158],EBX
0040137E  |. 899C24 5C010000    MOV DWORD PTR SS:[ESP+15C],EBX
00401385  |. 899C24 60010000    MOV DWORD PTR SS:[ESP+160],EBX
0040138C  |. 899C24 64010000    MOV DWORD PTR SS:[ESP+164],EBX
00401393  |. 899C24 68010000    MOV DWORD PTR SS:[ESP+168],EBX
0040139A  |. 899C24 6C010000    MOV DWORD PTR SS:[ESP+16C],EBX
004013A1  |. 899C24 70010000    MOV DWORD PTR SS:[ESP+170],EBX
004013A8  |. 899C24 74010000    MOV DWORD PTR SS:[ESP+174],EBX
004013AF  |. 899C24 78010000    MOV DWORD PTR SS:[ESP+178],EBX
004013B6  |. 898424 7C010000    MOV DWORD PTR SS:[ESP+17C],EAX
004013BD  |. 898424 80010000    MOV DWORD PTR SS:[ESP+180],EAX
004013C4  |. 898424 84010000    MOV DWORD PTR SS:[ESP+184],EAX
004013CB  |. 898424 88010000    MOV DWORD PTR SS:[ESP+188],EAX
004013D2  |. 898424 8C010000    MOV DWORD PTR SS:[ESP+18C],EAX
004013D9  |. 898424 90010000    MOV DWORD PTR SS:[ESP+190],EAX
004013E0  |. 898424 94010000    MOV DWORD PTR SS:[ESP+194],EAX
004013E7  |. 898424 98010000    MOV DWORD PTR SS:[ESP+198],EAX
004013EE  |. 898424 9C010000    MOV DWORD PTR SS:[ESP+19C],EAX
004013F5  |. 899424 A0010000    MOV DWORD PTR SS:[ESP+1A0],EDX
004013FC  |. 899424 A4010000    MOV DWORD PTR SS:[ESP+1A4],EDX
00401403  |. 899424 A8010000    MOV DWORD PTR SS:[ESP+1A8],EDX
0040140A  |. 899424 AC010000    MOV DWORD PTR SS:[ESP+1AC],EDX
00401411  |. 899424 B0010000    MOV DWORD PTR SS:[ESP+1B0],EDX
00401418  |. 899424 B4010000    MOV DWORD PTR SS:[ESP+1B4],EDX
0040141F  |. 899424 B8010000    MOV DWORD PTR SS:[ESP+1B8],EDX
00401426  |. 0F8E A1000000      JLE 004014CD
0040142C  |> 83F9 0A            /CMP ECX,0A
0040142F  |. 7D 10              |JGE SHORT 00401441
00401431  |. 8B56 34            |MOV EDX,DWORD PTR DS:[ESI+34]
00401434  |. 8B46 30            |MOV EAX,DWORD PTR DS:[ESI+30]
00401437  |. 66:8B144A          |MOV DX,WORD PTR DS:[EDX+ECX*2]
0040143B  |. 66:891448          |MOV WORD PTR DS:[EAX+ECX*2],DX
0040143F  |. EB 7F              |JMP SHORT 004014C0
00401441  |> 8BC1               |MOV EAX,ECX
00401443  |. BD 80020000        |MOV EBP,280
00401448  |. 99                 |CDQ
00401449  |. F7FD               |IDIV EBP
0040144B  |. 3BD3               |CMP EDX,EBX
0040144D  |. 75 11              |JNZ SHORT 00401460
0040144F  |. 8B6E 38            |MOV EBP,DWORD PTR DS:[ESI+38]
00401452  |. 45                 |INC EBP
00401453  |. 8BC5               |MOV EAX,EBP
00401455  |. 896E 38            |MOV DWORD PTR DS:[ESI+38],EBP
00401458  |. 83F8 6E            |CMP EAX,6E
0040145B  |. 7C 03              |JL SHORT 00401460
0040145D  |. 895E 38            |MOV DWORD PTR DS:[ESI+38],EBX
00401460  |> 3BD7               |CMP EDX,EDI
00401462  |. 7D 19              |JGE SHORT 0040147D
00401464  |. 8B46 38            |MOV EAX,DWORD PTR DS:[ESI+38]
00401467  |. 395484 18          |CMP DWORD PTR SS:[ESP+EAX*4+18],EDX
0040146B  |. 7E 10              |JLE SHORT 0040147D
0040146D  |. 8B56 34            |MOV EDX,DWORD PTR DS:[ESI+34]
00401470  |. 8B46 30            |MOV EAX,DWORD PTR DS:[ESI+30]
00401473  |. 66:8B144A          |MOV DX,WORD PTR DS:[EDX+ECX*2]
00401477  |. 66:891448          |MOV WORD PTR DS:[EAX+ECX*2],DX
0040147B  |. EB 43              |JMP SHORT 004014C0
0040147D  |> 81FA 7B020000      |CMP EDX,27B
00401483  |. 7E 20              |JLE SHORT 004014A5
00401485  |. 8B46 38            |MOV EAX,DWORD PTR DS:[ESI+38]
00401488  |. 8B4484 18          |MOV EAX,DWORD PTR SS:[ESP+EAX*4+18]
0040148C  |. 05 7B020000        |ADD EAX,27B
00401491  |. 3BC2               |CMP EAX,EDX
00401493  |. 7D 10              |JGE SHORT 004014A5
00401495  |. 8B56 34            |MOV EDX,DWORD PTR DS:[ESI+34]
00401498  |. 8B46 30            |MOV EAX,DWORD PTR DS:[ESI+30]
0040149B  |. 66:8B144A          |MOV DX,WORD PTR DS:[EDX+ECX*2]
0040149F  |. 66:891448          |MOV WORD PTR DS:[EAX+ECX*2],DX
004014A3  |. EB 1B              |JMP SHORT 004014C0
004014A5  |> 8B46 38            |MOV EAX,DWORD PTR DS:[ESI+38]
004014A8  |. 8BD1               |MOV EDX,ECX
004014AA  |. 8B6C84 18          |MOV EBP,DWORD PTR SS:[ESP+EAX*4+18]
004014AE  |. 8B46 34            |MOV EAX,DWORD PTR DS:[ESI+34]
004014B1  |. 2BD5               |SUB EDX,EBP
004014B3  |. 8B6E 30            |MOV EBP,DWORD PTR DS:[ESI+30]
004014B6  |. 66:8B5450 08       |MOV DX,WORD PTR DS:[EAX+EDX*2+8]
004014BB  |. 66:89544D 00       |MOV WORD PTR SS:[EBP+ECX*2],DX
004014C0  |> 8B4424 14          |MOV EAX,DWORD PTR SS:[ESP+14]
004014C4  |. 41                 |INC ECX
004014C5  |. 3BC8               |CMP ECX,EAX
004014C7  |.^0F8C 5FFFFFFF      \JL 0040142C
004014CD  |> 8B4424 10          MOV EAX,DWORD PTR SS:[ESP+10]
004014D1  |. 8B4E 30            MOV ECX,DWORD PTR DS:[ESI+30]
004014D4  |. 8B9424 DC010000    MOV EDX,DWORD PTR SS:[ESP+1DC]
004014DB  |. 50                 PUSH EAX                                ; /Arg3
004014DC  |. 51                 PUSH ECX                                ; |Arg2
004014DD  |. 52                 PUSH EDX                                ; |Arg1
004014DE  |. FF15 E0C04B00      CALL NEAR DWORD PTR DS:[4BC0E0]         ; \Original.00401000
004014E4  |. 83C4 0C            ADD ESP,0C
004014E7  |. 5F                 POP EDI
004014E8  |. 5D                 POP EBP
004014E9  |> 5E                 POP ESI
004014EA  |. 5B                 POP EBX
004014EB  |. 81C4 C0010000      ADD ESP,1C0
004014F1  \. C2 0C00            RETN 0C*/

/*********************************************************************************************************************
**  void CGame::Abaddon_corpse(int sX, int sY);		( Snoopy )														**
**  description			: Placeholder for abaddon's death lightnings												**
**********************************************************************************************************************/
void CGame::Abaddon_corpse(int sX, int sY)
{	int ir = (rand()%20)-10;
	_DrawThunderEffect(sX+30 , 0, sX+30 , sY-10 , ir, ir, 1);
	_DrawThunderEffect(sX+30 , 0, sX+30 , sY-10 , ir+2, ir, 2);
	_DrawThunderEffect(sX+30 , 0, sX+30 , sY-10 , ir-2, ir, 2);
	ir = (rand()%20)-10;
	_DrawThunderEffect(sX-20 , 0, sX-20 , sY-35 , ir, ir, 1);
	_DrawThunderEffect(sX-20 , 0, sX-20 , sY-35 , ir+2, ir, 2);
	_DrawThunderEffect(sX-20 , 0, sX-20 , sY-35 , ir-2, ir, 2);
	ir = (rand()%20)-10;
	_DrawThunderEffect(sX-10 , 0, sX-10 , sY+30	, ir, ir, 1);
	_DrawThunderEffect(sX-10 , 0, sX-10 , sY+30	, ir+2, ir+2, 2);
	_DrawThunderEffect(sX-10 , 0, sX-10 , sY+30	, ir-2, ir+2, 2);
	ir = (rand()%20)-10;
	_DrawThunderEffect(sX+50 , 0, sX+50 , sY+35	, ir, ir, 1);
	_DrawThunderEffect(sX+50 , 0, sX+50 , sY+35	, ir+2, ir+2, 2);
	_DrawThunderEffect(sX+50 , 0, sX+50 , sY+35	, ir-2, ir+2, 2);
	ir = (rand()%20)-10;
	_DrawThunderEffect(sX+65 , 0, sX+65 , sY-5	, ir, ir, 1);
	_DrawThunderEffect(sX+65 , 0, sX+65 , sY-5	, ir+2, ir+2, 2);
	_DrawThunderEffect(sX+65 , 0, sX+65 , sY-5	, ir-2, ir+2, 2);
	ir = (rand()%20)-10;
	_DrawThunderEffect(sX+45 , 0, sX+45 , sY-50	, ir, ir, 1);
	_DrawThunderEffect(sX+45 , 0, sX+45 , sY-50	, ir+2, ir+2, 2);
	_DrawThunderEffect(sX+45 , 0, sX+45 , sY-50	, ir-2, ir+2, 2);

	for (int x=sX-50; x<=sX+100; x+= rand()%35)
	for (int y=sY-30; y<=sY+50; y+= rand()%45)
	{	ir = (rand()%20)-10;
		_DrawThunderEffect(x , 0, x , y, ir, ir, 2);
	}
}

/*********************************************************************************************************************
**  void DebugLog(char * cStr)			( Snoopy )																	**
**  description			: writes data into "Debug.txt"																**
**********************************************************************************************************************/
void CGame::DebugLog(char * cStr)
{FILE * pFile;
 char cBuffer[512];
 SYSTEMTIME SysTime;
	pFile = fopen("Debug.txt", "at");
	if (pFile == NULL) return;
	ZeroMemory(cBuffer, sizeof(cBuffer));
	GetLocalTime(&SysTime);
	wsprintf(cBuffer, "(%4d:%2d:%2d_%2d:%2d:%2d) - ", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute,SysTime.wSecond);
	strcat(cBuffer, cStr);
	strcat(cBuffer, "\n");
	fwrite(cBuffer, 1, strlen(cBuffer), pFile);
	fclose(pFile);
}