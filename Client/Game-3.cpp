


BOOL CGame::bEffectFrameCounter()
{int i, x;
 DWORD dwTime;
 BOOL bRet = FALSE;
 short sAbsX, sAbsY, sDist;
 char  cDir;
 long lPan;
	dwTime = m_dwCurTime;
	dwTime += m_pMapData->m_dwFrameAdjustTime;
	for (i = 0; i < DEF_MAXEFFECTS; i++)
	if (m_pEffectList[i] != NULL) {
		if ((dwTime - m_pEffectList[i]->m_dwTime) > m_pEffectList[i]->m_dwFrameTime)
		{	m_pEffectList[i]->m_dwTime = dwTime;
			m_pEffectList[i]->m_cFrame++;
			bRet = TRUE;
			m_pEffectList[i]->m_mX2 = m_pEffectList[i]->m_mX;
			m_pEffectList[i]->m_mY2 = m_pEffectList[i]->m_mY;
			switch (m_pEffectList[i]->m_sType) {
			case 1: // coup normal
				if (m_pEffectList[i]->m_cFrame == 1)
				{	for (int j = 1; j <= m_pEffectList[i]->m_iV1; j++) bAddNewEffect(11, m_pEffectList[i]->m_mX + 15 - (rand() % 30), m_pEffectList[i]->m_mY + 15 - (rand() % 30), NULL, NULL, -1*(rand() % 2));
				}
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 2:	// (Arrow missing target ?)
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32 - 40,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 70);
				if (   (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					&& (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY*32 - 40)) <= 2) )
				{	//bAddNewEffect(14, m_pEffectList[i]->m_mX +(rand() % 5) - 2, m_pEffectList[i]->m_mY +(rand() % 5) - 2, NULL, NULL, 0, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 4: // Gold Drop ,33,69,70
			case 33: //
			case 69:
			case 70:
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 5:
			case 30:
			case 31: // Fire Explosion
			case 252:
				if (m_pEffectList[i]->m_cFrame == 1)
				{	bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
				}
				if (m_pEffectList[i]->m_cFrame == 7)
				{	bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, NULL, NULL);
					bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, NULL, NULL);
					bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, NULL, NULL);
				}
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 6: // Lightning Bolt Burst
				if (m_pEffectList[i]->m_cFrame == 1)
				{	bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
				}
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 7: // Magic Missile Burst
				if (m_pEffectList[i]->m_cFrame == 1)
				{	bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
				}
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 9:  // Burst Type 2
			case 11: // Burst Type 3
				m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
				m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
				m_pEffectList[i]->m_rY++;
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 10: // Lightning Arrow Burst
				if (m_pEffectList[i]->m_cFrame == 1)
				{	bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
				}
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 12: // Burst Type 4
				m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
				m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 13: // Bulles druncncity
				if (m_pEffectList[i]->m_cFrame < 15)
				{	if ((rand() % 2) == 0)
						 m_pEffectList[i]->m_mX++;
					else m_pEffectList[i]->m_mX--;
					m_pEffectList[i]->m_mY--;
				}
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 16: //
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 40);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				if (   (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2)
					&& (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
				{	bAddNewEffect(18, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, NULL, NULL, 0); // testcode 0111 18
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), NULL, NULL, -1*(rand() % 2));
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 17: // Ice-Storm
				cDir = m_Misc.cGetNextMoveDir(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, m_pEffectList[i]->m_mX3, m_pEffectList[i]->m_mY3);
				switch (cDir) {
				case 1:
					m_pEffectList[i]->m_rY -= 2;
					break;
				case 2:
					m_pEffectList[i]->m_rY -= 2;
					m_pEffectList[i]->m_rX += 2;
					break;
				case 3:
					m_pEffectList[i]->m_rX += 2;
					break;
				case 4:
					m_pEffectList[i]->m_rX += 2;
					m_pEffectList[i]->m_rY += 2;
					break;
				case 5:
					m_pEffectList[i]->m_rY += 2;
					break;
				case 6:
					m_pEffectList[i]->m_rX -= 2;
					m_pEffectList[i]->m_rY += 2;
					break;
				case 7:
					m_pEffectList[i]->m_rX -= 2;
					break;
				case 8:
					m_pEffectList[i]->m_rX -= 2;
					m_pEffectList[i]->m_rY -= 2;
					break;
				}
				if (m_pEffectList[i]->m_rX < -10) m_pEffectList[i]->m_rX = -10;
				if (m_pEffectList[i]->m_rX >  10) m_pEffectList[i]->m_rX =  10;
				if (m_pEffectList[i]->m_rY < -10) m_pEffectList[i]->m_rY = -10;
				if (m_pEffectList[i]->m_rY >  10) m_pEffectList[i]->m_rY =  10;
				m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
				m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
				m_pEffectList[i]->m_mY3--;
				if (m_pEffectList[i]->m_cFrame > 10)
				{	m_pEffectList[i]->m_cFrame = 0;
					if (abs(m_pEffectList[i]->m_sY - m_pEffectList[i]->m_mY3) > 100)
					{	delete m_pEffectList[i];
						m_pEffectList[i] = NULL;
				}	}
				break;

			case 20: // Critical strike with a weapon
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27: // Critical strike with a weapon
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32 - 40,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), NULL, NULL, 0);//-1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), NULL, NULL, 0);//-1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), NULL, NULL, 0);//-1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), NULL, NULL, 0);//-1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), NULL, NULL, 0);//-1*(rand() % 4));
				if ( (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2) &&
					 (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY*32 - 40)) <= 2) )
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 34: //
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				bAddNewEffect(33, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, NULL, NULL, -1*(rand() % 4));
				if ( (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2) &&
					 (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2) )
				{	bAddNewEffect(33, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, NULL, NULL, 0); //7
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;


			case 40:
			case 56:
				if (m_pEffectList[i]->m_cFrame == 9)
				{	bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 100)-50), m_pEffectList[i]->m_mY +((rand() % 70)-35), NULL, NULL, 0, 0);
					bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 100)-50), m_pEffectList[i]->m_mY +((rand() % 70)-35), NULL, NULL, 0, 0);
					bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 100)-50), m_pEffectList[i]->m_mY +((rand() % 70)-35), NULL, NULL, 0, 0);
					bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 100)-50), m_pEffectList[i]->m_mY +((rand() % 70)-35), NULL, NULL, 0, 0);
					bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 100)-50), m_pEffectList[i]->m_mY +((rand() % 70)-35), NULL, NULL, 0, 0);
				}
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 41: //Large Type 1, 2, 3, 4
			case 42:
			case 43:
			case 44:
			case 45: // Small Type 1, 2
			case 46:
				if (m_pEffectList[i]->m_cFrame >= 7)
				{	m_pEffectList[i]->m_mX--;
					m_pEffectList[i]->m_mY += m_pEffectList[i]->m_iV1;
					m_pEffectList[i]->m_iV1++;
				}

				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	if ((m_pEffectList[i]->m_sType != 45) && (m_pEffectList[i]->m_sType != 46))
					{	bAddNewEffect(50, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, NULL, NULL, 0);
						bAddNewEffect(14, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
						bAddNewEffect(14, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
						bAddNewEffect(14, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
						bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
						bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
					}
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 47: // Blizzard
			case 48:
			case 49:
				if (m_pEffectList[i]->m_cFrame >= 7)
				{	m_pEffectList[i]->m_mX--;
					m_pEffectList[i]->m_mY += m_pEffectList[i]->m_iV1;
					m_pEffectList[i]->m_iV1 += 4;
				}
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	if (m_pEffectList[i]->m_sType == 49)
						 bAddNewEffect(72, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, NULL, NULL, 0);
					else bAddNewEffect(50, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, NULL, NULL, 0);
					bAddNewEffect(14, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
					bAddNewEffect(14, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
					bAddNewEffect(14, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);

					bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
					bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 60: //
			case 181: // Meteor-Strike
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	bAddNewEffect(61, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, NULL, NULL, 0, 0);
					bAddNewEffect(63, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, NULL, NULL, 0, 0);
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), NULL, NULL, -1*(rand() % 2));
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else if (m_pEffectList[i]->m_cFrame >= 0)
				{	m_pEffectList[i]->m_mX -= 30;
					m_pEffectList[i]->m_mY += 46;
					bAddNewEffect(62, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, NULL, NULL, 0, 0);
				}
				break;

			case 62:
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else if (m_pEffectList[i]->m_cFrame >= 0)
				{	m_pEffectList[i]->m_mX += (rand() % 3) -1;
					m_pEffectList[i]->m_mY += (rand() % 3) -1;
				}
				break;

			case 65: // Building fire after MS (crusade) 65 & 67
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else if (m_pEffectList[i]->m_cFrame >= 0)
				{	m_pEffectList[i]->m_mX += (rand() % 3) -1;
					m_pEffectList[i]->m_mY -= 4 +(rand() % 2);
				}
				break;

			case 66:
			case 203:
			case 204:
			case 205:
			case 206:
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 68:
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else if (m_pEffectList[i]->m_cFrame == 11)
				{	SetCameraShakingEffect(m_pEffectList[i]->m_iV1, 2);
				}
				break;

			case 71:
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				bAddNewEffect(48, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, NULL, NULL, 0);
				bAddNewEffect(51, m_pEffectList[i]->m_mX +((rand() % 20)-10), m_pEffectList[i]->m_mY +((rand() % 20)-10), NULL, NULL, 0, 0);
				if ( (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2) &&
					 (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2) )
				{	bAddNewEffect(49, m_pEffectList[i]->m_mX/* + (rand() % 30) - 15*/, m_pEffectList[i]->m_mY/* + (rand() % 30) - 15*/, NULL, NULL, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 81: // Snoopy: Ajout StromBlade
				m_Misc.GetPoint(m_pEffectList[i]->m_mX
					, m_pEffectList[i]->m_mY
					, m_pEffectList[i]->m_dX*32
					, m_pEffectList[i]->m_dY*32
					, &m_pEffectList[i]->m_mX
					, &m_pEffectList[i]->m_mY
					, &m_pEffectList[i]->m_iErr
					, 10);
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 100: // Magic Missile
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32/* - 40*/,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));

				if ( (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2) &&
					 (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY*32/* - 40*/)) <= 2) )
				{	bAddNewEffect(7, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 110: // Enegy-Bolt
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32/* - 40*/,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY*32) <= 2) )
				{	bAddNewEffect(6, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0); // 6 testcode 0111
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 120: // Fire Ball
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32/* - 40*/,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY*32) <= 2) )
				{	bAddNewEffect(5, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 130: // Fire Strike
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32/* - 40*/,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY*32) <= 2) )
				{	bAddNewEffect(5, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
					bAddNewEffect(5, m_pEffectList[i]->m_dX*32 -30, m_pEffectList[i]->m_dY*32 -15, NULL, NULL, -7);
					bAddNewEffect(5, m_pEffectList[i]->m_dX*32 +35, m_pEffectList[i]->m_dY*32 -30, NULL, NULL, -5);
					bAddNewEffect(5, m_pEffectList[i]->m_dX*32 +20, m_pEffectList[i]->m_dY*32 +30, NULL, NULL, -3);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 137: // Lightning Arrow
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32/* - 40*/,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				if (   (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					&& (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY*32) <= 2) )
				{	bAddNewEffect(10, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 143: // Lightning
			case 151: // Lightning-Bolt
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	bAddNewEffect(10, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	m_pEffectList[i]->m_rX = 5 - (rand() % 10);
					m_pEffectList[i]->m_rY = 5 - (rand() % 10);
				}
				break;

			case 145: // Chill-Wind
				bAddNewEffect(40, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
				bAddNewEffect(40, m_pEffectList[i]->m_dX*32 -30, m_pEffectList[i]->m_dY*32 -15, NULL, NULL, -10);
				bAddNewEffect(40, m_pEffectList[i]->m_dX*32 +35, m_pEffectList[i]->m_dY*32 -30, NULL, NULL, -6);
				bAddNewEffect(40, m_pEffectList[i]->m_dX*32 +20, m_pEffectList[i]->m_dY*32 +30, NULL, NULL, -3);
				delete m_pEffectList[i];
				m_pEffectList[i] = NULL;
				break;

			case 147:  // Triple-Energy-Bolt
				bAddNewEffect(110, m_pEffectList[i]->m_sX , m_pEffectList[i]->m_sY ,
						               m_pEffectList[i]->m_dX -1, m_pEffectList[i]->m_dY-1, 0);
				bAddNewEffect(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						               m_pEffectList[i]->m_dX +1, m_pEffectList[i]->m_dY -1, 0);
				bAddNewEffect(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						               m_pEffectList[i]->m_dX +1, m_pEffectList[i]->m_dY +1, 0);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX)*1000;
				PlaySound('E', 1, sDist, lPan);
				bAddNewEffect(7, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
				delete m_pEffectList[i];
				m_pEffectList[i] = NULL;
				break ;

			case 156: // Mass-Lightning-Arrow
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(137, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						               m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0);
					sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					sAbsY = abs(((m_sViewPointY / 32) + 7)  - m_pEffectList[i]->m_dY);
					if (sAbsX > sAbsY) sDist = sAbsX;
					else sDist = sAbsY;
					lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX)*1000;
					PlaySound('E', 1, sDist, lPan);
				}
				break;

			case 157: // Ice-Strike
				bAddNewEffect(41, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
				for (x = 0; x < 14; x++)
				{	bAddNewEffect(41 + (rand() % 3), m_pEffectList[i]->m_dX*32 +(rand() % 100) - 50 +10, m_pEffectList[i]->m_dY*32 + (rand() % 90) - 45, NULL, NULL, -1*x-1);
				}
				for (x = 0; x < 6; x++)
				{	bAddNewEffect(45 + (rand() % 2), m_pEffectList[i]->m_dX*32 +(rand() % 100) - 50 +10, m_pEffectList[i]->m_dY*32 + (rand() % 90) - 45, NULL, NULL, -1*x-1 -10);
				}
				delete m_pEffectList[i];
				m_pEffectList[i] = NULL;
				break;

			case 160: // Energy-Strike
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(16, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						          m_pEffectList[i]->m_dX*32 + 50 - (rand() % 100), m_pEffectList[i]->m_dY*32 + 50 - (rand() % 100), 0);
					sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					sAbsY = abs(((m_sViewPointY / 32) + 7)  - m_pEffectList[i]->m_dY);
					if (sAbsX > sAbsY) sDist = sAbsX;
					else sDist = sAbsY;
					lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					PlaySound('E', 1, sDist, lPan);
				}
				break;

			case 161: // Mass-Fire-Strike
				m_Misc.GetPoint(m_pEffectList[i]->m_mX,    m_pEffectList[i]->m_mY,
					            m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32/* - 40*/,
								&m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
								&m_pEffectList[i]->m_iErr, 50);
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY*32) <= 2) )
				{	bAddNewEffect(30, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
					bAddNewEffect(31, m_pEffectList[i]->m_dX*32 -30, m_pEffectList[i]->m_dY*32 -15, NULL, NULL, -7);
					bAddNewEffect(31, m_pEffectList[i]->m_dX*32 +35, m_pEffectList[i]->m_dY*32 -30, NULL, NULL, -5);
					bAddNewEffect(31, m_pEffectList[i]->m_dX*32 +20, m_pEffectList[i]->m_dY*32 +30, NULL, NULL, -3);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 163: // Mass-Chill-Wind Chill-Wind
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 -30, m_pEffectList[i]->m_dY*32 -15, NULL, NULL, -10);
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 +35, m_pEffectList[i]->m_dY*32 -30, NULL, NULL, -6);
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 +20, m_pEffectList[i]->m_dY*32 +30, NULL, NULL, -3);
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 +(rand()%100)-50, m_pEffectList[i]->m_dY*32 +(rand()%70)-35, NULL, NULL, -1*(rand()%10));
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 +(rand()%100)-50, m_pEffectList[i]->m_dY*32 +(rand()%70)-35, NULL, NULL, -1*(rand()%10));
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 +(rand()%100)-50, m_pEffectList[i]->m_dY*32 +(rand()%70)-35, NULL, NULL, -1*(rand()%10));
				bAddNewEffect(56, m_pEffectList[i]->m_dX*32 +(rand()%100)-50, m_pEffectList[i]->m_dY*32 +(rand()%70)-35, NULL, NULL, -1*(rand()%10));
				delete m_pEffectList[i];
				m_pEffectList[i] = NULL;
				break;

			case 164: // worm-bite
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	bAddNewEffect(68, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0); // testcode 0111 18
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 170: // Bloody-Shock-Wave
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else if ((m_pEffectList[i]->m_cFrame % 2) == 0)
				{	bAddNewEffect(34, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						          m_pEffectList[i]->m_dX*32 + 30 - (rand() % 60), m_pEffectList[i]->m_dY*32 + 30 - (rand() % 60), 0);
					sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					sAbsY = abs(((m_sViewPointY / 32) + 7)  - m_pEffectList[i]->m_dY);
					if (sAbsX > sAbsY) sDist = sAbsX;
					else sDist = sAbsY;
					lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					PlaySound('E', 1, sDist, lPan);
				}
				break;

			case 172: // Mass-Ice-Strike
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32, m_pEffectList[i]->m_dY*32, NULL, NULL, 0);
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*(rand() % 3));
				for (x = 0; x < 16; x++)
				{	bAddNewEffect(44, m_pEffectList[i]->m_dX*32 +(rand() % 110) - 55 +10, m_pEffectList[i]->m_dY*32 + (rand() % 100) - 50, NULL, NULL, -1*x-1);
				}
				for (x = 0; x < 8; x++)
				{	bAddNewEffect(45 + (rand() % 2), m_pEffectList[i]->m_dX*32 +(rand() % 100) - 50 +10, m_pEffectList[i]->m_dY*32 + (rand() % 90) - 45, NULL, NULL, -1*x-1 -10);
				}
				delete m_pEffectList[i];
				m_pEffectList[i] = NULL;
				break;

			case 174: // Lightning-Strike
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(151, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						          m_pEffectList[i]->m_dX +(rand()%3) -1, m_pEffectList[i]->m_dY +(rand()%3) -1, 0);
					sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					sAbsY = abs(((m_sViewPointY / 32) + 7)  - m_pEffectList[i]->m_dY);
					if (sAbsX > sAbsY) sDist = sAbsX;
					else sDist = sAbsY;
					lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					PlaySound('E', 1, sDist, lPan);
				}
				break;

			case 182: // Mass-Magic-Missile
				m_Misc.GetPoint(m_pEffectList[i]->m_mX
					, m_pEffectList[i]->m_mY
					, m_pEffectList[i]->m_dX*32
					, m_pEffectList[i]->m_dY*32
					, &m_pEffectList[i]->m_mX
					, &m_pEffectList[i]->m_mY
					, &m_pEffectList[i]->m_iErr
					, 50);
				bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, -1*(rand() % 4));
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY*32) <= 2) )
				{	// JLE 0043132A
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(35, m_pEffectList[i]->m_dX*32 +22, m_pEffectList[i]->m_dY*32 -15, NULL, NULL, -7, 1);
					bAddNewEffect(36, m_pEffectList[i]->m_dX*32 -22, m_pEffectList[i]->m_dY*32 -7,  NULL, NULL, -7, 1);
					bAddNewEffect(36, m_pEffectList[i]->m_dX*32 +30, m_pEffectList[i]->m_dY*32 -22, NULL, NULL, -5, 1);
					bAddNewEffect(36, m_pEffectList[i]->m_dX*32 +12, m_pEffectList[i]->m_dY*32 +22, NULL, NULL, -3, 1);
				}
				break;

			case 191: // Blizzard
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else /*if (m_pEffectList[i]->m_cFrame == 1)*/
				{	bAddNewEffect(71, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
						          m_pEffectList[i]->m_dX*32 +(rand()%120)-60, m_pEffectList[i]->m_dY*32 +(rand()%120)-60, 0);
					sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					sAbsY = abs(((m_sViewPointY / 32) + 7)  - m_pEffectList[i]->m_dY);
					if (sAbsX > sAbsY) sDist = sAbsX;
					else sDist = sAbsY;
					lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					PlaySound('E', 1, sDist, lPan);
				}
				break;

			case 196: // Earth-Shock-Wave
				m_Misc.GetPoint(m_pEffectList[i]->m_mX
					, m_pEffectList[i]->m_mY
					, m_pEffectList[i]->m_dX*32
					, m_pEffectList[i]->m_dY*32
					, &m_pEffectList[i]->m_mX
					, &m_pEffectList[i]->m_mY
					, &m_pEffectList[i]->m_iErr
					, 40);
				bAddNewEffect(80, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, NULL, NULL, 0, 1);
				bAddNewEffect(80, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, NULL, NULL, 0, 0);
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					sAbsY = abs(((m_sViewPointY / 32) + 7)  - m_pEffectList[i]->m_dY);
					if (sAbsX > sAbsY) sDist = sAbsX -10;
					else sDist = sAbsY -10;
					lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
					PlaySound('E', 1, sDist, lPan);
				}
				break;

			case 200:
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(203, m_pEffectList[i]->m_sX + 40, m_pEffectList[i]->m_sY + 120, NULL, NULL, 0, 0);
					bAddNewEffect(204, m_pEffectList[i]->m_sX -10, m_pEffectList[i]->m_sY +70, NULL, NULL, 0, 0);
					bAddNewEffect(205, m_pEffectList[i]->m_sX -10, m_pEffectList[i]->m_sY +75, NULL, NULL, 0, 0);
					bAddNewEffect(206, m_pEffectList[i]->m_sX -7, m_pEffectList[i]->m_sY +27, NULL, NULL, 0, 0);
					bAddNewEffect(201, (rand() % 160) + 320, (rand() % 120) + 240, NULL, NULL, 0, 1);
					bAddNewEffect(202, (rand() % 160) + 320, (rand() % 120) + 240, NULL, NULL, 0, 1);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 201:
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(203, m_pEffectList[i]->m_sX + 110, m_pEffectList[i]->m_sY + 120, NULL, NULL, 0, 0);
					bAddNewEffect(204, m_pEffectList[i]->m_sX -10, m_pEffectList[i]->m_sY +70, NULL, NULL, 0, 0);
					bAddNewEffect(205, m_pEffectList[i]->m_sX -10, m_pEffectList[i]->m_sY +75, NULL, NULL, 0, 0);
					bAddNewEffect(202, (rand() % 160) + 320, (rand() % 120) + 240, NULL, NULL, 0, 1);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 202:
				if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(203, m_pEffectList[i]->m_sX + 65, m_pEffectList[i]->m_sY + 120, NULL, NULL, 0, 0);
					bAddNewEffect(204, m_pEffectList[i]->m_sX -10, m_pEffectList[i]->m_sY +70, NULL, NULL, 0, 0);
					bAddNewEffect(205, m_pEffectList[i]->m_sX -10, m_pEffectList[i]->m_sY +75, NULL, NULL, 0, 0);
					bAddNewEffect(206, m_pEffectList[i]->m_sX -7, m_pEffectList[i]->m_sY +27, NULL, NULL, 0, 0);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 250: // Gate round
				m_Misc.GetPoint(m_pEffectList[i]->m_mX
					, m_pEffectList[i]->m_mY
					, m_pEffectList[i]->m_dX*32
					, m_pEffectList[i]->m_dY*32 -40
					, &m_pEffectList[i]->m_mX
					, &m_pEffectList[i]->m_mY
					, &m_pEffectList[i]->m_iErr
					, 10);
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY*32 - 40)) <= 2) )
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 251: // Salmon burst (effect11s)
				m_Misc.GetPoint(m_pEffectList[i]->m_mX
					, m_pEffectList[i]->m_mY
					, m_pEffectList[i]->m_dX*32
					, m_pEffectList[i]->m_dY*32
					, &m_pEffectList[i]->m_mX
					, &m_pEffectList[i]->m_mY
					, &m_pEffectList[i]->m_iErr
					, 50);
				if (    (abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX*32) <= 2)
					 && (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY*32 - 40)) <= 2) )
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}else
				{	bAddNewEffect(252, m_pEffectList[i]->m_dX*32     , m_pEffectList[i]->m_dY*32     , 0, 0, 0, 1);
					bAddNewEffect(252, m_pEffectList[i]->m_dX*32 - 30, m_pEffectList[i]->m_dY*32 - 15, 0, 0, -7, 1);
					bAddNewEffect(252, m_pEffectList[i]->m_dX*32 - 35, m_pEffectList[i]->m_dY*32 - 30, 0, 0, -5, 1);
					bAddNewEffect(252, m_pEffectList[i]->m_dX*32 + 20, m_pEffectList[i]->m_dY*32 + 30, 0, 0, -3, 1);
					delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;

			case 8:
			case 14:
			case 15:
			case 18:
			case 32:
			case 35: //
			case 36: //
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 57:
			case 61:
			case 63:
			case 64:
			case 67:
			case 72:
			case 73:
			case 74:
			case 75:
			case 76:
			case 77:
			case 80: //
			case 82: //

			case 101:
			case 102:
			case 111:
			case 112:
			case 113:
			case 121:
			case 122:
			case 123: // Stamina Rec
			case 124:
			case 125:
			case 126:
			case 127:
			case 128: // Gr Stamina Rec
			case 131:
			case 132:
			case 133:
			case 134:
			case 135:
			case 136:
			case 142:
			case 144:
			case 150: // Berserk : Cirlcle 6 magic
			case 152: // Polymorph
			case 153:
			case 162:
			case 165:
			case 166:
			case 171:
			case 176: //
			case 177: //

			case 180:
			case 183: //
			case 184: // EP's Magic Drain
			case 190:
			case 192:
			case 193:
			case 194:
			case 195:
			case 242: // Mage hero effect
			case 243: // War hero effect
			case 244: // Snoopy: déplacé pour nvx sorts: Aura du casteur de Mass MagicMissile
				if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
				{	delete m_pEffectList[i];
					m_pEffectList[i] = NULL;
				}
				break;
	}	}	}
	return bRet;
}


BOOL   CGame::DrawObject_OnRun(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY)
{int dx, dy;
 int iBodyIndex, iHairIndex, iUndiesIndex, iArmArmorIndex, iBodyArmorIndex, iPantsIndex, iBootsIndex, iWeaponIndex, iShieldIndex, iHelmIndex, iR, iG, iB, iMantleIndex;
 BOOL bInv = FALSE;
 int iWeaponGlare, iShieldGlare;
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
		iBodyIndex  = 500  + (_tmp_sOwnerType - 1 )*8*15 + (4 * 8);
		iUndiesIndex    = DEF_SPRID_UNDIES_M + (_tmp_sAppr1 & 0x000F)*15 + 4;
		iHairIndex	    = DEF_SPRID_HAIR_M + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 4;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_M + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 4;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_M + (_tmp_sAppr3 & 0x000F)*15 + 4;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_M + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 4;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_M + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 4;
		if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
			iWeaponIndex = -1;
		else
		{	iWeaponIndex = DEF_SPRID_WEAPON_M + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*6 + (_tmp_cDir - 1);
		}
		if ((_tmp_sAppr2 & 0x000F) == 0)
			iShieldIndex = -1;
		else iShieldIndex = DEF_SPRID_SHIELD_M + (_tmp_sAppr2 & 0x000F)*8 + 6;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_M + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 4;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_M + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 4;
		break;

	case 4:
	case 5:
	case 6:
		if (((_tmp_sAppr3 & 0x0F00) >> 8) == 1) iSkirtDraw = 1;
		iBodyIndex  = 500  + (_tmp_sOwnerType - 1 )*8*15 + (4 * 8);
		iUndiesIndex    = DEF_SPRID_UNDIES_W + (_tmp_sAppr1 & 0x000F)*15 + 4;
		iHairIndex	    = DEF_SPRID_HAIR_W + ((_tmp_sAppr1 & 0x0F00) >> 8)*15 + 4;
		if ((_tmp_sAppr4 & 0x80) == 0)
		{	if (((_tmp_sAppr3 & 0xF000) >> 12) == 0)
				 iBodyArmorIndex = -1;
			else iBodyArmorIndex = DEF_SPRID_BODYARMOR_W + ((_tmp_sAppr3 & 0xF000) >> 12)*15 + 4;
		}
		if ((_tmp_sAppr3 & 0x000F) == 0)
			 iArmArmorIndex = -1;
		else iArmArmorIndex = DEF_SPRID_BERK_W + (_tmp_sAppr3 & 0x000F)*15 + 4;
		if ((_tmp_sAppr3 & 0x0F00) == 0)
			 iPantsIndex = -1;
		else iPantsIndex = DEF_SPRID_LEGG_W + ((_tmp_sAppr3 & 0x0F00) >> 8)*15 + 4;
		if (((_tmp_sAppr4 & 0xF000) >> 12) == 0)
			 iBootsIndex = -1;
		else iBootsIndex = DEF_SPRID_BOOT_W + ((_tmp_sAppr4 & 0xF000) >> 12)*15 + 4;
		if (((_tmp_sAppr2 & 0x0FF0) >> 4) == 0)
			iWeaponIndex = -1;
		else
		{	iWeaponIndex = DEF_SPRID_WEAPON_W + ((_tmp_sAppr2 & 0x0FF0) >> 4)*64 + 8*6 + (_tmp_cDir - 1);
		}
		if ((_tmp_sAppr2 & 0x000F) == 0)
			iShieldIndex = -1;
		else iShieldIndex = DEF_SPRID_SHIELD_W + (_tmp_sAppr2 & 0x000F)*8 + 6;
		if ((_tmp_sAppr4 & 0x0F00) == 0)
			 iMantleIndex = -1;
		else iMantleIndex = DEF_SPRID_MANTLE_W + ((_tmp_sAppr4 & 0x0F00) >> 8)*15 + 4;
		if ((_tmp_sAppr3 & 0x00F0) == 0)
			 iHelmIndex = -1;
		else iHelmIndex = DEF_SPRID_HEAD_W + ((_tmp_sAppr3 & 0x00F0) >> 4)*15 + 4;
		break;

	default:
		iUndiesIndex    = -1;
		iHairIndex   	= -1;
		iArmArmorIndex  = -1;
		iBodyArmorIndex = -1;
		iPantsIndex     = -1;
		iBootsIndex     = -1;
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
	if (m_bIsCrusadeMode) DrawObjectFOE(sX+dx, sY+dy, _tmp_cFrame);

	if (_tmp_iEffectType != 0)
	{	switch (_tmp_iEffectType) {
		case 1: m_pEffectSpr[26]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Attack Effect
		case 2: m_pEffectSpr[27]->PutTransSprite(sX+dx, sY+dy, _tmp_iEffectFrame, dwTime); break; // Special Ability: Protect Effect
	}	}

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
				if (m_cDetailLevel != 0)
				{	if (sX < 50)
						 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSpriteClip(sX+dx, sY+dy, _tmp_cFrame, dwTime);
					else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutShadowSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				}
				break;
			}

			if (bInv == TRUE)
				//m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite2(sX+dx, sY+dy, _tmp_cFrame, dwTime);
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}
			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);

			if ((iMantleIndex != -1) && (_cMantleDrawingOrderOnRun[_tmp_cDir] == 0))
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

			if ((iMantleIndex != -1) && (_cMantleDrawingOrderOnRun[_tmp_cDir] == 2))
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
				case 1: m_pEffectSpr[45]->PutTransSprite(sX -13+dx, sY -34+dy, 0, dwTime); // GM effect
				case 2: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, m_iDrawFlag, 0, dwTime); break; // Green Glare
				case 3: m_pSprite[iShieldIndex]->PutTransSpriteRGB(sX+dx, sY+dy,  (_tmp_cDir-1) * 8 + _tmp_cFrame, 0, 0, m_iDrawFlag, dwTime); break; // Blue Glare
			}	}

			if ((iMantleIndex != -1) && (_cMantleDrawingOrderOnRun[_tmp_cDir] == 1))
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

			if (bInv == TRUE)
				m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutTransSprite2(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			else
			{	if ((_tmp_iStatus & 0x40) != 0)
					 m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteRGB(sX+dx, sY+dy, _tmp_cFrame, m_wR[10] -m_wR[0]/2, m_wG[10] -m_wG[0]/2, m_wB[10] -m_wB[0]/2, dwTime);
				else m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->PutSpriteFast(sX+dx, sY+dy, _tmp_cFrame, dwTime);
			}

			SetRect(&m_rcBodyRect, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.left, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.top,
				     m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.right, m_pSprite[iBodyIndex + (_tmp_cDir - 1)]->m_rcBound.bottom);


			if ((iMantleIndex != -1) && (_cMantleDrawingOrderOnRun[_tmp_cDir] == 0))
			{	if(bInv) m_pSprite[iMantleIndex]->PutTransSprite25(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				else
				{	if (iMantleColor == 0)
						 m_pSprite[iMantleIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
					else m_pSprite[iMantleIndex]->PutSpriteRGB(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, m_wR[iMantleColor] -m_wR[0], m_wG[iMantleColor] -m_wG[0], m_wB[iMantleColor] -m_wB[0], dwTime);
			}	}

			if (iUndiesIndex != -1)
			{	if(bInv) m_pSprite[iUndiesIndex]->PutTransSprite2(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
				m_pSprite[iUndiesIndex]->PutSpriteFast(sX+dx, sY+dy, (_tmp_cDir-1) * 8 + _tmp_cFrame, dwTime);
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

			if ((iMantleIndex != -1) && (_cMantleDrawingOrderOnRun[_tmp_cDir] == 2))
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

			if ((iMantleIndex != -1) && (_cMantleDrawingOrderOnRun[_tmp_cDir] == 1))
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

		if ((_tmp_iStatus & 0x20) != 0) 	// Berserk
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
	if (   (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top != -1)
		&& (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.top < msY)
		&& (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.bottom > msY)
		&& (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.left < msX)
		&& (m_pSprite[iBodyIndex + (_tmp_cDir -1)]->m_rcBound.right > msX)) return TRUE;
	return FALSE;
}

void CGame::GetPlayerTurn()
{
 char cDir;
 short sX, sY, sCnt1, sCnt2;
 int   iError;

	sX = m_sPlayerX;
	sY = m_sPlayerY;
	sCnt1 = 0;
	m_cPlayerTurn = 0;
	iError = 0;
	while (1) {
		cDir = cGetNextMoveDir(sX, sY, m_sCommX, m_sCommY);
		if (cDir == 0) break;
		switch (cDir) {
		case 1: sY--;       break;
		case 2: sX++; sY--; break;
		case 3: sX++;       break;
		case 4: sX++; sY++; break;
		case 5: sY++;       break;
		case 6: sX--; sY++; break;
		case 7: sX--;       break;
		case 8: sX--; sY--; break;
		}
		sCnt1++;
		if (sCnt1 > 30) break;
	}

	sX = m_sPlayerX;
	sY = m_sPlayerY;
	sCnt2 = 0;
	m_cPlayerTurn = 1;
	iError = 0;
	while (1) {
		cDir = cGetNextMoveDir(sX, sY, m_sCommX, m_sCommY);
		if (cDir == 0) break;
		switch (cDir) {
		case 1: sY--;       break;
		case 2: sX++; sY--; break;
		case 3: sX++;       break;
		case 4: sX++; sY++; break;
		case 5: sY++;       break;
		case 6: sX--; sY++; break;
		case 7: sX--;       break;
		case 8: sX--; sY--; break;
		}
		sCnt2++;
		if (sCnt2 > 30) break;
	}

	if (sCnt1 > sCnt2)
		 m_cPlayerTurn = 0;
	else m_cPlayerTurn = 1;
}


int CGame::_iCheckDlgBoxFocus(short msX, short msY, char cButtonSide)
{int i;
 char         cDlgID;
 short        sX, sY;
 DWORD		  dwTime = m_dwCurTime;
	if (cButtonSide == 1) {
		// Snoopy: 41->61
		for (i = 0; i < 61; i++)
		// Snoopy: 40->60
		if (m_cDialogBoxOrder[60 - i] != NULL) 	// Snoopy: 40->60
		{	cDlgID = m_cDialogBoxOrder[60 - i];
			if ((m_stDialogBoxInfo[cDlgID].sX <= msX)	&& ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) >= msX) &&
				(m_stDialogBoxInfo[cDlgID].sY <= msY)	&& ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) >= msY) )
			{	EnableDialogBox(cDlgID, NULL, NULL, NULL);

				m_stMCursor.sPrevX = msX;
				m_stMCursor.sPrevY = msY;
				m_stMCursor.sDistX = msX - m_stDialogBoxInfo[cDlgID].sX;
				m_stMCursor.sDistY = msY - m_stDialogBoxInfo[cDlgID].sY;

				switch (cDlgID) {
				case 1:
					if (bDlgBoxPress_Character(msX, msY) == FALSE) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					break;

				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:

				case 12:
				case 13:
				case 16:
				case 17:
				case 20:
				case 22:
				case 23:
				case 24:
				case 25:
				case 28:
				case 29:
				case 30:
				case 31:
				case 32:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
				case 40:
				case 50: // resur
				// NPC
				case 67:
				case 68:
				case 69:
					m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
					m_stMCursor.sSelectedObjectID   = cDlgID;
					break;

				case 2:	// (Sell Item)
					if (bDlgBoxPress_Inventory(msX, msY) == FALSE)
					{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					break;

				case 10:
					sX = m_stDialogBoxInfo[10].sX;
					sY = m_stDialogBoxInfo[10].sY;
					if ((msX >= sX + 340) && (msX <= sX + 360) && (msY >= sY + 22) && (msY <= sY + 138)) {
						m_stDialogBoxInfo[10].bIsScrollSelected = TRUE;
						return -1;
					}

					if (m_stDialogBoxInfo[10].bIsScrollSelected == FALSE) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 11:
					sX = m_stDialogBoxInfo[11].sX;
					sY = m_stDialogBoxInfo[11].sY;
					if ((m_stDialogBoxInfo[11].cMode == 0) && (msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 20) && (msY <= sY + 330)) {
						m_stDialogBoxInfo[11].bIsScrollSelected = TRUE;
						return -1;
					}

					if ((m_stDialogBoxInfo[11].bIsScrollSelected == FALSE)) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 14:
					sX = m_stDialogBoxInfo[14].sX;
					sY = m_stDialogBoxInfo[14].sY;
					if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
						m_stDialogBoxInfo[14].bIsScrollSelected = TRUE;
						return -1;
					}

					if (m_stDialogBoxInfo[14].bIsScrollSelected == FALSE) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 15:
					sX = m_stDialogBoxInfo[15].sX;
					sY = m_stDialogBoxInfo[15].sY;
					if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
					{	m_stDialogBoxInfo[15].bIsScrollSelected = TRUE;
						return -1;
					}
					if (m_stDialogBoxInfo[15].bIsScrollSelected == FALSE)
					{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 18:
					sX = m_stDialogBoxInfo[18].sX;
					sY = m_stDialogBoxInfo[18].sY;
					if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
						m_stDialogBoxInfo[18].bIsScrollSelected = TRUE;
						return -1;
					}

					if (m_stDialogBoxInfo[18].bIsScrollSelected == FALSE) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 19:
					sX = m_stDialogBoxInfo[19].sX;
					sY = m_stDialogBoxInfo[19].sY;
					if ((msX >= sX + 126) && (msX <= sX + 238) && (msY >= sY +122) && (msY <= sY +138)) {
						m_stDialogBoxInfo[19].bIsScrollSelected = TRUE;
						return -1;
					}
					if ((msX >= sX + 126) && (msX <= sX + 238) && (msY >= sY +139) && (msY <= sY +155)) {
						m_stDialogBoxInfo[19].bIsScrollSelected = TRUE;
						return -1;
					}

					if (m_stDialogBoxInfo[19].bIsScrollSelected == FALSE) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 21:
					sX = m_stDialogBoxInfo[21].sX;
					sY = m_stDialogBoxInfo[21].sY;
					if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
						m_stDialogBoxInfo[21].bIsScrollSelected = TRUE;
						return -1;
					}

					if (m_stDialogBoxInfo[21].bIsScrollSelected == FALSE) {
						m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					else return -1;
					break;

				case 26:
					if (bDlgBoxPress_SkillDlg(msX, msY) == FALSE)
					{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
						m_stMCursor.sSelectedObjectID   = cDlgID;
					}
					break;

				case 27:
					m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
					m_stMCursor.sSelectedObjectID   = cDlgID;
					break;

				case 41: //Snoopy: Drag exchange confirmation dialog
					m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
					m_stMCursor.sSelectedObjectID   = cDlgID;
					break;

				case 42:  // Snoopy: Drag majestic stats
					m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
					m_stMCursor.sSelectedObjectID   = cDlgID;
					break;

				case 51:  // Snoopy: Drag Gail menu
					m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_DLGBOX;
					m_stMCursor.sSelectedObjectID   = cDlgID;
					break;
				}
				return 1;
		}	}
		return 0;
	}else if (cButtonSide == 2)
	{	if ((dwTime - m_dwDialogCloseTime) < 300) return 0;
		// Snoopy: 40->60
		for (i = 0; i < 61; i++)
		// Snoopy: 40->60
		if (m_cDialogBoxOrder[60 - i] != NULL) {
		// Snoopy: 40->60
			cDlgID = m_cDialogBoxOrder[60 - i];
			if ((m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX) &&
				(m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY) )
			{	if ((cDlgID != 5) && (cDlgID != 6) && (cDlgID != 8) && (cDlgID != 12) && ((cDlgID != 23) || (m_stDialogBoxInfo[23].cMode < 3)) && (cDlgID != 24) && (cDlgID != 27) && (cDlgID != 34) &&
					(cDlgID != 33) && !((cDlgID == 32) && ((m_stDialogBoxInfo[cDlgID].cMode == 1) || (m_stDialogBoxInfo[cDlgID].cMode == 3))))
					DisableDialogBox(cDlgID);
				m_dwDialogCloseTime = dwTime;
				return 1;
	}	}	}
	return 0;
}



void CGame::InitItemList(char * pData)
{char    cTotalItems;
 int     i, iAngelValue;
 short * sp;
 DWORD * dwp;
 WORD  * wp;
 char  * cp;

	for (i = 0; i < DEF_MAXITEMS; i++)
		m_cItemOrder[i] = -1;

	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
		m_sItemEquipmentStatus[i] = -1;

	for (i = 0; i < DEF_MAXITEMS; i++)
		m_bIsItemDisabled[i] = FALSE;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	cTotalItems = *cp;
	cp++;

	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] != NULL)
	{	delete m_pItemList[i];
		m_pItemList[i] = NULL;
	}

	for (i = 0; i < DEF_MAXBANKITEMS; i++)
	if (m_pBankList[i] != NULL)
	{	delete m_pBankList[i];
		m_pBankList[i] = NULL;
	}

	for (i = 0; i < cTotalItems; i++)
	{	m_pItemList[i] = new class CItem;
		memcpy(m_pItemList[i]->m_cName, cp, 20);
		cp += 20;
		dwp = (DWORD *)cp;
		m_pItemList[i]->m_dwCount = *dwp;
		m_pItemList[i]->m_sX      =	40;
		m_pItemList[i]->m_sY      =	30;
		cp += 4;
		m_pItemList[i]->m_cItemType = *cp;
		cp++;
		m_pItemList[i]->m_cEquipPos = *cp;
		cp++;
		if( *cp == 0 ) m_bIsItemEquipped[i] = FALSE;
		else m_bIsItemEquipped[i] = TRUE;
		cp++;
		if (m_bIsItemEquipped[i] == TRUE)
		{	m_sItemEquipmentStatus[m_pItemList[i]->m_cEquipPos] = i;
		}
		sp = (short *)cp;
		m_pItemList[i]->m_sLevelLimit = *sp;
		cp += 2;
		m_pItemList[i]->m_cGenderLimit = *cp;
		cp++;
		wp =(WORD *)cp;
		m_pItemList[i]->m_wCurLifeSpan = *wp;
		cp += 2;
		wp =(WORD *)cp;
		m_pItemList[i]->m_wWeight = *wp;
		cp += 2;
		sp = (short *)cp;
		m_pItemList[i]->m_sSprite = *sp;
		cp += 2;
		sp = (short *)cp;
		m_pItemList[i]->m_sSpriteFrame = *sp;
		cp += 2;
		m_pItemList[i]->m_cItemColor = *cp;
		cp++;
		m_pItemList[i]->m_sItemSpecEffectValue2 = (short)*cp; // v1.41
		cp++;
		dwp = (DWORD *)cp;
		m_pItemList[i]->m_dwAttribute = *dwp;
		cp += 4;
		/*
		m_pItemList[i]->m_bIsCustomMade = (BOOL)*cp;
		cp++;
		*/
		m_cItemOrder[i] = i;
		// Snoopy: Add Angelic Stats
		if (   (m_pItemList[i]->m_cItemType == 1)
			&& (m_bIsItemEquipped[i] == TRUE)
			&& (m_pItemList[i]->m_cEquipPos >= 11))
		{	if(memcmp(m_pItemList[i]->m_cName, "AngelicPandent(STR)", 19) == 0)
			{	iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
				m_iAngelicStr = 1 + iAngelValue;
			}else if(memcmp(m_pItemList[i]->m_cName, "AngelicPandent(DEX)", 19) == 0)
			{	iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
				m_iAngelicDex = 1 + iAngelValue;
			}else if(memcmp(m_pItemList[i]->m_cName, "AngelicPandent(INT)", 19) == 0)
			{	iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
				m_iAngelicInt = 1 + iAngelValue;
			}else if(memcmp(m_pItemList[i]->m_cName, "AngelicPandent(MAG)", 19) == 0)
			{	iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
				m_iAngelicMag = 1 + iAngelValue;
	}	}	}

	cTotalItems = *cp;
	cp++;

	for (i = 0; i < DEF_MAXBANKITEMS; i++)
	if (m_pBankList[i] != NULL)
	{	delete m_pBankList[i];
		m_pBankList[i] = NULL;
	}

	for (i = 0; i < cTotalItems; i++)
	{	m_pBankList[i] = new class CItem;
		memcpy(m_pBankList[i]->m_cName, cp, 20);
		cp += 20;

		dwp = (DWORD *)cp;
		m_pBankList[i]->m_dwCount = *dwp;
		cp += 4;

		m_pBankList[i]->m_sX = 40;
		m_pBankList[i]->m_sY = 30;

		m_pBankList[i]->m_cItemType = *cp;
		cp++;

		m_pBankList[i]->m_cEquipPos = *cp;
		cp++;

		sp = (short *)cp;
		m_pBankList[i]->m_sLevelLimit = *sp;
		cp += 2;

		m_pBankList[i]->m_cGenderLimit = *cp;
		cp++;

		wp =(WORD *)cp;
		m_pBankList[i]->m_wCurLifeSpan = *wp;
		cp += 2;

		wp =(WORD *)cp;
		m_pBankList[i]->m_wWeight = *wp;
		cp += 2;

		sp = (short *)cp;
		m_pBankList[i]->m_sSprite = *sp;
		cp += 2;

		sp = (short *)cp;
		m_pBankList[i]->m_sSpriteFrame = *sp;
		cp += 2;

		m_pBankList[i]->m_cItemColor = *cp;
		cp++;

		m_pBankList[i]->m_sItemSpecEffectValue2 = (short)*cp; // v1.41
		cp++;

		dwp = (DWORD *)cp;
		m_pBankList[i]->m_dwAttribute = *dwp;
		cp += 4;
		/*
		m_pBankList[i]->m_bIsCustomMade = (BOOL)*cp;
		cp++;
		*/
	}

	// Magic, Skill Mastery
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
}

void CGame::DrawDialogBox_GuideMap(short msX, short msY, char cLB)
{int  m_iMaxMapIndex   = DEF_SPRID_INTERFACE_GUIDEMAP + m_cMapIndex +1;
 int  m_iMinMapIndex   = DEF_SPRID_INTERFACE_GUIDEMAP;
 int  m_iMinMapSquare  = m_cMapIndex ;
 //telescope.pak:  frames 1..31 <=> DEF_SPRID_INTERFACE_GUIDEMAP +1...+31 <=> m_cMapIndex 0..30
 //telescope1.pak: frames 1..3  <=> DEF_SPRID_INTERFACE_GUIDEMAP +36..+38 <=> m_cMapIndex 35..37 et +
	if( m_cMapIndex < 0 ) return;
	if (m_cMapIndex >= 35)
	{	m_iMaxMapIndex  = DEF_SPRID_INTERFACE_GUIDEMAP + m_cMapIndex +1;
		m_iMinMapIndex  = DEF_SPRID_INTERFACE_GUIDEMAP + 35;
		m_iMinMapSquare = m_cMapIndex - 35;
	}
	short sX, sY, shX, shY, szX, szY;
	sX = m_stDialogBoxInfo[9].sX;
	sY = m_stDialogBoxInfo[9].sY;
	szX = m_stDialogBoxInfo[9].sSizeX;
	szY = m_stDialogBoxInfo[9].sSizeY;
	if( sX < 20 ) sX = 0;
	if( sY < 20 ) sY = 0;
	if( sX > 640-128-20 ) sX = 640-128;
	if( sY > 427-128-20 ) sY = 427-128;
	for( shX=-2 ; shX<130 ; shX++ )
	{
		m_DDraw.PutPixel( sX+shX, sY-2  , 50,50,50);
		m_DDraw.PutPixel( sX+shX, sY-1  , 50,50,50);
		m_DDraw.PutPixel( sX+shX, sY+128, 50,50,50);
		m_DDraw.PutPixel( sX+shX, sY+129, 50,50,50);
	}
	for( shY=-2 ; shY<130 ; shY++ )
	{
		m_DDraw.PutPixel( sX-2  , sY+shY, 50,50,50);
		m_DDraw.PutPixel( sX-1  , sY+shY, 50,50,50);
		m_DDraw.PutPixel( sX+128, sY+shY, 50,50,50);
		m_DDraw.PutPixel( sX+129, sY+shY, 50,50,50);
	}
	if( m_bZoomMap )
	{	shX = m_sPlayerX-64;
		shY = m_sPlayerY-64;
		if( shX < 0 ) shX = 0;
		if( shY < 0 ) shY = 0;
		if( shX > m_pMapData->m_sMapSizeX-128 ) shX = m_pMapData->m_sMapSizeX-128;
		if( shY > m_pMapData->m_sMapSizeY-128 ) shY = m_pMapData->m_sMapSizeY-128;
		if (m_bDialogTrans) m_pSprite[m_iMaxMapIndex]->PutShiftTransSprite2(sX, sY, shX, shY, 0, m_dwCurTime );
		else m_pSprite[m_iMaxMapIndex]->PutShiftSpriteFast(sX, sY, shX, shY, 0, m_dwCurTime );
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX - shX + m_sPlayerX, sY - shY + m_sPlayerY, 37, m_dwCurTime);

		if( (m_dwCurTime - m_dwMonsterEventTime) < 30000 )
		{	if( (m_dwCurTime%500)< 370 )
			{	if( m_sEventX >= shX && m_sEventX <= shX+128 && m_sEventY >= shY && m_sEventY <= shY+128 )
					m_pSprite[DEF_SPRID_INTERFACE_MONSTER]->PutSpriteFast(sX + m_sEventX - shX, sY + m_sEventY -shY, m_sMonsterID, m_dwCurTime);
			}
		}else
		{	m_dwMonsterEventTime = 0;
			m_sMonsterID = 0;
		}
	}else // Sans zoom
	{	if (m_bDialogTrans) m_pSprite[m_iMinMapIndex]->PutTransSprite2(sX, sY, m_iMinMapSquare, m_dwCurTime);
		else m_pSprite[m_iMinMapIndex]->PutSpriteFastNoColorKey(sX, sY, m_iMinMapSquare, m_dwCurTime);
		shX = (m_sPlayerX*128)/(m_pMapData->m_sMapSizeX);
		shY = (m_sPlayerY*128)/(m_pMapData->m_sMapSizeX);
		m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + shX, sY + shY, 37, m_dwCurTime);

		if( (G_dwGlobalTime - m_dwMonsterEventTime) < 30000 )
		{	if( (m_dwCurTime%500)< 370 )
			{	shX = (m_sEventX*128)/(m_pMapData->m_sMapSizeX);
				shY = (m_sEventY*128)/(m_pMapData->m_sMapSizeX);
				m_pSprite[DEF_SPRID_INTERFACE_MONSTER]->PutSpriteFast(sX + shX, sY + shY, m_sMonsterID, m_dwCurTime);
			}
		}else
		{	m_dwMonsterEventTime = 0;
			m_sMonsterID = 0;
	}	}

	if( cLB != 0 ) return;
	if( msX >= sX && msX < sX+szY && msY >= sY && msY < sY+szY )
	{
		if( sY > 213 ) shY = sY - 17;
		else shY = sY + szY + 4;
		if( m_bZoomMap ) PutString( sX, shY, DEF_MSG_GUIDEMAP_MIN, RGB(200, 200, 120) );//"(-)
		else PutString( sX, shY, DEF_MSG_GUIDEMAP_MAX, RGB(200, 200, 120) );//"(+)

		if( m_bZoomMap )
		{
			shX = m_sPlayerX-64;
			shY = m_sPlayerY-64;
			if( shX < 0 ) shX = 0;
			if( shY < 0 ) shY = 0;
			if( shX > m_pMapData->m_sMapSizeX-128 ) shX = m_pMapData->m_sMapSizeX-128;
			if( shY > m_pMapData->m_sMapSizeY-128 ) shY = m_pMapData->m_sMapSizeY-128;
			shX += msX - sX;
			shY += msY - sY;
		}else
		{	shX = (msX-sX)*m_pMapData->m_sMapSizeX/128;
			shY = (msY-sY)*m_pMapData->m_sMapSizeX/128;
		}
		wsprintf( G_cTxt, "%d, %d", shX, shY );
		if( m_cMapIndex == 11 ) // Aresden: Fixed by Snoopy for v3.51 maps
		{	if( shX >  46 && shX <  66 && shY > 107 && shY < 127 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER );
			else if( shX > 103 && shX < 123 && shY > 86 && shY < 116 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_GUILDHALL );
			else if( shX > 176 && shX < 196 && shY >  62 && shY < 82 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_CATH );
			else if( shX > 135 && shX < 155 && shY > 113 && shY < 133 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_CITYHALL );
			else if( shX > 97 && shX < 117  && shY > 175 && shY < 195 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE );
			else if( shX > 223 && shX < 243 && shY > 124 && shY < 144 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE );
			else if( shX > 118 && shX < 138 && shY > 157 && shY < 177 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_SHOP );
			else if( shX > 148 && shX < 178 && shY > 188 && shY < 208 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH );
			else if( shX > 69 && shX < 89   && shY > 199 && shY < 219 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_DUNGEON );
			else if( shX > 21 && shX < 41  && shY > 266  && shY < 286 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_HUNT);
			else if( shX > 20 && shX < 40  && shY > 13   && shY < 33 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_ML );
			else if( shX > 246 && shX < 266 && shY > 16  && shY < 36 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_ML );
			else if( shX > 265 && shX < 285 && shY > 195 && shY < 215 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_FARM);
			else if( shX > 88 && shX < 108 && shY > 150  && shY < 170 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_CMDHALL );
		}else if( m_cMapIndex == 3 ) // Elvine: Fixed by Snoopy for v3.51 maps
		{	if( shX >  170 && shX < 190 && shY >  65 && shY < 85 )      strcpy( G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER );
			else if( shX >  67 && shX < 87 && shY > 130 && shY < 150 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_GUILDHALL );
			else if( shX > 121 && shX < 141 && shY >  66 && shY < 86 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_CATH );
			else if( shX > 135 && shX < 155 && shY > 117 && shY < 137 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_CITYHALL );
			else if( shX > 190 && shX < 213 && shY > 118 && shY < 138 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE );
			else if( shX > 73  && shX < 103 && shY > 165 && shY < 185 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE );
			else if( shX > 217 && shX < 237 && shY > 142 && shY < 162 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_SHOP );
			else if( shX > 216 && shX < 256 && shY > 99  && shY < 119 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH );
			else if( shX > 251 && shX < 271 && shY >  73 && shY < 93 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_DUNGEON );
			else if( shX > 212 && shX < 232 && shY > 13  && shY < 33 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_HUNT);
			else if( shX > 16 && shX < 36   && shY > 262 && shY < 282 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_ML );
			else if( shX > 244 && shX < 264 && shY > 248 && shY < 268 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_ML );
			else if( shX > 264 && shX < 284 && shY > 177 && shY < 207 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_FARM);
			else if( shX > 207 && shX < 227 && shY > 79  && shY < 99 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_CMDHALL );
		}
		else if( m_cMapIndex == 5 ) // Elvine Farm: Fixed by Snoopy for v3.51 maps
		{	if( shX >  62 && shX < 82 && shY >  187 && shY < 207 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE );
			else if( shX > 81  && shX < 101 && shY > 169 && shY < 189 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_SHOP );
			else if( shX > 101 && shX < 131 && shY > 180 && shY < 200 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH );
			else if( shX > 130 && shX < 150 && shY > 195 && shY < 215 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_DUNGEON );
			else if( shX > 86  && shX < 106 && shY > 139 && shY < 159 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_BARRACK );
		}
		else if( m_cMapIndex == 6 ) // Areden's Farm: Fixed by Snoopy for v3.51 maps
		{	if( shX >  30 && shX < 50 && shY >  80 && shY < 100 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE );
			else if( shX > 55 && shX < 85 && shY > 80 && shY < 100 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH );
			else if( shX > 52 && shX < 72 && shY > 80 && shY < 100 )  strcpy( G_cTxt, DEF_MSG_MAPNAME_SHOP );
			else if( shX > 70 && shX < 90 && shY > 60 && shY < 80 )   strcpy( G_cTxt, DEF_MSG_MAPNAME_DUNGEON );
			else if( shX > 45 && shX < 65 && shY > 123 && shY < 143 ) strcpy( G_cTxt, DEF_MSG_MAPNAME_BARRACK );
		}
		PutString( msX-10, msY-13, G_cTxt, RGB(200, 200, 120) );
	}
}

void CGame::DrawDialogBoxs(short msX, short msY, short msZ, char cLB)
{
 int i;
	if (m_bIsObserverMode == TRUE) return;
	m_DInput.m_sZ = 0;
	//Snoopy: 41->61
	for (i = 0; i < 61; i++)
	if (m_cDialogBoxOrder[i] != NULL)
	{	switch (m_cDialogBoxOrder[i]) {
		case 1:
			//DrawDialogBox_Character(msX, msY); //@@@
			DrawDialogBox_Character(msX, msY);
			break;
		case 2:
			DrawDialogBox_Inventory(msX, msY); //@@@
			break;
		case 3:
			DrawDialogBox_Magic(msX, msY, msZ); //@@@
			break;
		case 4:
			DrawDialogBox_ItemDrop(msX, msY); //@@@
			break;
		case 5:
			DrawDialogBox_15AgeMsg(msX, msY); //@@@
			break;
		case 6:
			DrawDialogBox_WarningMsg(msX, msY); //@@@
			break;
		case 7:
			DrawDialogBox_GuildMenu(msX, msY);
			break;
		case 8:
			DrawDialogBox_GuildOperation(msX, msY);
			break;
		case 9:
			DrawDialogBox_GuideMap(msX, msY, cLB);
			break;
		case 10:
			DrawDialogBox_Chat(msX, msY, msZ, cLB); //@@@
			break;
		case 11:
			DrawDialogBox_Shop(msX, msY, msZ, cLB); //@@@
			break;
		case 12:
			DrawDialogBox_LevelUpSetting(msX, msY); //@@@
			break;
		case 13:
			DrawDialogBox_CityHallMenu(msX, msY);
			break;
		case 14:
			DrawDialogBox_Bank(msX, msY, msZ, cLB); //@@@
			break;
		case 15:
			DrawDialogBox_Skill(msX, msY, msZ, cLB); //@@@
			break;
		case 16:
			DrawDialogBox_MagicShop(msX, msY, msZ); //@@@
			break;
		case 17:
			DrawDialogBox_QueryDropItemAmount();
			break;
		case 18:
			DrawDialogBox_Text(msX, msY, msZ, cLB); //@@@
			break;
		case 19:
			DrawDialogBox_SysMenu(msX, msY, cLB); //@@@
			break;
		case 20:
			DrawDialogBox_NpcActionQuery(msX, msY); //@@@
			break;
		case 21:
			DrawDialogBox_NpcTalk(msX, msY, cLB); //@@@
			break;
		case 22:
			DrawDialogBox_Map();
			break;
		case 23:
			DrawDialogBox_SellorRepairItem(msX, msY); //@@@
			break;
		case 24:
			DrawDialogBox_Fishing(msX, msY);
			break;
		case 25:
			DrawDialogBox_ShutDownMsg(msX, msY); //@@@
			break;
		case 26: // Manuf
			DrawDialogBox_SkillDlg(msX, msY, msZ, cLB);
			break;
		case 27:
			DrawDialogBox_Exchange(msX, msY); //@@@
			break;
		case 28:
			DrawDialogBox_Quest(msX, msY); //@@@
			break;
		case 29:
			DrawDialogBox_GaugePannel(); //@@@
			break;
		case 30:
			DrawDialogBox_IconPannel(msX, msY); //@@@
			break;
		case 31:
			DrawDialogBox_SellList(msX, msY); //@@@
			break;
		case 32:
			DrawDialogBox_Party(msX, msY); //@@@
			break;
		case 33:
			DrawDialogBox_CrusadeJob(msX, msY); //@@@
			break;
		case 34:
			DrawDialogBox_ItemUpgrade(msX, msY);
			break;
		case 35:
			DrawDialogBox_Help(msX, msY); //@@@
			break;
		case 36:
			DrawDialogBox_Commander(msX, msY); //@@@
			break;
		case 37:
			DrawDialogBox_Constructor(msX, msY); //@@@
			break;
		case 38:
			DrawDialogBox_Soldier(msX, msY); //@@@
			break;
		case 40:
			DrawDialogBox_Slates(msX, msY, msZ, cLB);
			break;
		case 41:	//Snoopy: Confirmation Exchange
			DrawDialogBox_ConfirmExchange(msX, msY);
			break;
		case 42:
			DrawDialogBox_ChangeStatsMajestic(msX, msY);
			break;
		case 50: // Snoopy: Resurection?
			DrawDialogBox_Resurect(msX, msY);
			break;
		case 51: // Gail
			DrawDialogBox_CMDHallMenu(msX, msY);
			break;
		}
	}
	if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
	{ 	if (m_iSuperAttackLeft > 0)
		{	if (GetAsyncKeyState(VK_MENU)>>15)
				m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutTransSprite(368, 439, 3, m_dwCurTime);
			wsprintf(G_cTxt, "%d", m_iSuperAttackLeft);
			PutString_SprFont2(380, 454, G_cTxt, 220, 200, 200);
		}
	}else
	{	if (m_iSuperAttackLeft > 0)
		{	wsprintf(G_cTxt, "%d", m_iSuperAttackLeft);
			PutString_SprFont2(380, 454, G_cTxt, 10, 10, 10);
	}	}
}

void CGame::_Draw_CharacterBody(short sX, short sY, short sType)
{
 DWORD dwTime = m_dwCurTime;
 int  iR, iG, iB;

	if (sType <= 3)
	{	m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 0]->PutSpriteFast(sX, sY,  sType-1, dwTime);
		_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18]->PutSpriteRGB(sX, sY, (_tmp_sAppr1 & 0x0F00) >> 8, iR, iG, iB, dwTime);

		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19]->PutSpriteFast(sX, sY, (_tmp_sAppr1 & 0x000F), dwTime);
	}else
	{	m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 40]->PutSpriteFast(sX, sY, sType-4, dwTime);
		_GetHairColorRGB(((_tmp_sAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18 +40]->PutSpriteRGB(sX, sY, (_tmp_sAppr1 & 0x0F00) >> 8, iR, iG, iB, dwTime);
		m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19 +40]->PutSpriteFast(sX, sY, (_tmp_sAppr1 & 0x000F), dwTime);
	}
}


void CGame::EnableDialogBox(int iBoxID, int cType, int sV1, int sV2, char * pString)
{
 int i;
 short sX, sY;

	switch (iBoxID) {
	case 11:
		if (m_bIsDialogEnabled[11] == FALSE)
		{	switch (cType) {
			case NULL:
				break;
			default:
				_LoadShopMenuContents(cType);
				m_stDialogBoxInfo[11].sV1 = cType;
				m_stDialogBoxInfo[11].cMode	= 0;
				m_stDialogBoxInfo[11].sView = 0;
				m_stDialogBoxInfo[11].bFlag = TRUE;
				m_stDialogBoxInfo[11].sV3   = 1;
				break;
		}	}
		break;

	case 12: // levelup diag
		if (m_bIsDialogEnabled[12] == FALSE)
		{	m_stDialogBoxInfo[12].sX = m_stDialogBoxInfo[1].sX + 20;
			m_stDialogBoxInfo[12].sY = m_stDialogBoxInfo[1].sY + 20;
			m_stDialogBoxInfo[12].sV1 = m_iLU_Point;
		}
		break;

	case 3: // Magic Dialog
		break;

	case 4:
		if (m_bIsDialogEnabled[4] == FALSE) {
			m_stDialogBoxInfo[4].sView = cType;
		}
		break;

	case 5:
		if (m_bIsDialogEnabled[5] == FALSE) {
			m_stDialogBoxInfo[5].sView = cType;
		}
		break;

	case 6:
		if (m_bIsDialogEnabled[6] == FALSE) {
			m_stDialogBoxInfo[6].sView = cType;
		}
		break;

	case 7:
		if (m_stDialogBoxInfo[7].cMode == 1) {
			sX = m_stDialogBoxInfo[7].sX;
			sY = m_stDialogBoxInfo[7].sY;
			EndInputString();
			StartInputString(sX + 75, sY + 140, 21, m_cGuildName);
		}
		break;

	case 17: // demande quantité
		if (m_bIsDialogEnabled[17] == FALSE)
		{	m_stDialogBoxInfo[iBoxID].cMode = 1;
			m_stDialogBoxInfo[17].sView	= cType;
			EndInputString();
			ZeroMemory(m_cAmountString, sizeof(m_cAmountString));
			wsprintf( m_cAmountString, "%d", sV1 );
			sX = m_stDialogBoxInfo[17].sX;
			sY = m_stDialogBoxInfo[17].sY;
			StartInputString(sX + 40, sY + 57, 11, m_cAmountString, FALSE);
		}else
		{	if (m_stDialogBoxInfo[17].cMode == 1)
			{	sX = m_stDialogBoxInfo[17].sX;
				sY = m_stDialogBoxInfo[17].sY;
				EndInputString();
				StartInputString(sX + 40, sY + 57, 11, m_cAmountString, FALSE);
		}	}
		break;

	case 18:
		if (m_bIsDialogEnabled[18] == FALSE)
		{	switch (cType) {
			case NULL:
				m_stDialogBoxInfo[18].cMode	= 0;
				m_stDialogBoxInfo[18].sView = 0;
				break;
			default:
				_LoadTextDlgContents(cType);
				m_stDialogBoxInfo[18].cMode	= 0;
				m_stDialogBoxInfo[18].sView = 0;
				break;
		} 	}
		break;

	case 19:
		break;

	case 20: // Talk to npc or unicorn
		m_bIsItemDisabled[m_stDialogBoxInfo[20].sV1] = FALSE;
		if (m_bIsDialogEnabled[20] == FALSE)
		{	m_stDialogBoxInfo[11].sV1 = m_stDialogBoxInfo[11].sV2 = m_stDialogBoxInfo[11].sV3 =
			m_stDialogBoxInfo[11].sV4 = m_stDialogBoxInfo[11].sV5 = m_stDialogBoxInfo[11].sV6 = NULL;
			m_stDialogBoxInfo[20].cMode	= cType;
			m_stDialogBoxInfo[20].sView = 0;
			m_stDialogBoxInfo[20].sV1 = sV1;
			m_stDialogBoxInfo[20].sV2 = sV2;
		}
		break;

	case 21:
		if (m_bIsDialogEnabled[21] == FALSE)
		{	m_stDialogBoxInfo[21].cMode	= cType;
			m_stDialogBoxInfo[21].sView = 0;
			m_stDialogBoxInfo[21].sV1 = _iLoadTextDlgContents2(sV1+20);
			m_stDialogBoxInfo[21].sV2 = sV1+20;
		}
		break;

	case 22:
		if (m_bIsDialogEnabled[22] == FALSE) {
			m_stDialogBoxInfo[22].sV1 = sV1;
			m_stDialogBoxInfo[22].sV2 = sV2;

			m_stDialogBoxInfo[22].sSizeX = 290;
			m_stDialogBoxInfo[22].sSizeY = 290;
		}
		break;

	case 23:
		if (m_bIsDialogEnabled[23] == FALSE) {
			m_stDialogBoxInfo[23].cMode	= cType;
			m_stDialogBoxInfo[23].sV1   = sV1;		// ItemID
			m_stDialogBoxInfo[23].sV2   = sV2;
			if( cType == 2 )
			{	m_stDialogBoxInfo[23].sX = m_stDialogBoxInfo[11].sX;
				m_stDialogBoxInfo[23].sY = m_stDialogBoxInfo[11].sY;
			}
		}
		break;

	case 15:
		break;

	case 24:
		if (m_bIsDialogEnabled[24] == FALSE)
		{	m_stDialogBoxInfo[24].cMode	= cType;
			m_stDialogBoxInfo[24].sV1   = sV1;
			m_stDialogBoxInfo[24].sV2   = sV2;
			m_bSkillUsingStatus = TRUE;
		}
		break;

	case 25:
		if (m_bIsDialogEnabled[25] == FALSE) {
			m_stDialogBoxInfo[25].cMode	= cType;
			m_stDialogBoxInfo[25].sV1   = sV1;
			m_stDialogBoxInfo[25].sV2   = sV2;
		}
		break;

	case 26:
		switch (cType) {
		case 1:
		case 2: //
			if (m_bIsDialogEnabled[26] == FALSE)
			{	m_stDialogBoxInfo[26].cMode	= cType;
				m_stDialogBoxInfo[26].sV1   = -1;
				m_stDialogBoxInfo[26].sV2   = -1;
				m_stDialogBoxInfo[26].sV3   = -1;
				m_stDialogBoxInfo[26].sV4   = -1;
				m_stDialogBoxInfo[26].sV5   = -1;
				m_stDialogBoxInfo[26].sV6   = -1;
				m_stDialogBoxInfo[26].cStr[0] = 0;
				m_bSkillUsingStatus = TRUE;
				m_stDialogBoxInfo[26].sSizeX = 195;
				m_stDialogBoxInfo[26].sSizeY = 215;
				DisableDialogBox(17);
				DisableDialogBox(20);
				DisableDialogBox(23);
			}
			break;

		case 3:	//
			if (m_bIsDialogEnabled[26] == FALSE)
			{	m_stDialogBoxInfo[26].sView = 0;
				m_stDialogBoxInfo[26].cMode	= cType;
				m_stDialogBoxInfo[26].sV1   = -1;
				m_stDialogBoxInfo[26].sV2   = -1;
				m_stDialogBoxInfo[26].sV3   = -1;
				m_stDialogBoxInfo[26].sV4   = -1;
				m_stDialogBoxInfo[26].sV5   = -1;
				m_stDialogBoxInfo[26].sV6   = -1;
				m_stDialogBoxInfo[26].cStr[0] = 0;
				m_stDialogBoxInfo[26].cStr[1] = 0;
				m_stDialogBoxInfo[26].cStr[4] = 0;
				m_bSkillUsingStatus = TRUE;
				_bCheckBuildItemStatus();
				//m_stDialogBoxInfo[26].sX = 0;
				//m_stDialogBoxInfo[26].sY = 0;
				m_stDialogBoxInfo[26].sSizeX = 270;
				m_stDialogBoxInfo[26].sSizeY = 381;
				DisableDialogBox(17);
				DisableDialogBox(20);
				DisableDialogBox(23);
			}
			break;

		case 6:
			if (m_bIsDialogEnabled[26] == FALSE)
			{	m_stDialogBoxInfo[26].cMode	= cType;
				m_stDialogBoxInfo[26].cStr[2] = sV1;
				m_stDialogBoxInfo[26].cStr[3] = sV2;
				m_stDialogBoxInfo[26].sSizeX = 270;
				m_stDialogBoxInfo[26].sSizeY = 381;
				m_bSkillUsingStatus = TRUE;
				_bCheckBuildItemStatus();
				DisableDialogBox(17);
				DisableDialogBox(20);
				DisableDialogBox(23);
			}
			break;
		// Crafting
		case 7:
		case 8:
			if (m_bIsDialogEnabled[26] == FALSE)
			{	m_stDialogBoxInfo[26].cMode	= cType;
				m_stDialogBoxInfo[26].sV1   = -1;
				m_stDialogBoxInfo[26].sV2   = -1;
				m_stDialogBoxInfo[26].sV3   = -1;
				m_stDialogBoxInfo[26].sV4   = -1;
				m_stDialogBoxInfo[26].sV5   = -1;
				m_stDialogBoxInfo[26].sV6   = -1;
				m_stDialogBoxInfo[26].cStr[0] = 0;
				m_stDialogBoxInfo[26].cStr[1] = 0;
				m_bSkillUsingStatus = TRUE;
				//_bCheckCraftItemStatus();
				m_stDialogBoxInfo[26].sSizeX = 195;
				m_stDialogBoxInfo[26].sSizeY = 215;
				DisableDialogBox(17);
				DisableDialogBox(20);
				DisableDialogBox(23);
			}
			break;
		}
		break;

	case 27: // Snoopy: 7 mar 06 (multitrade) case rewriten
		if (m_bIsDialogEnabled[27] == FALSE)
		{	m_stDialogBoxInfo[27].cMode = cType;
			for (i=0; i<8;i++)
			{	ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr1, sizeof(m_stDialogBoxExchangeInfo[i].cStr1));
				ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr2, sizeof(m_stDialogBoxExchangeInfo[i].cStr2));
				m_stDialogBoxExchangeInfo[i].sV1 = -1;
				m_stDialogBoxExchangeInfo[i].sV2 = -1;
				m_stDialogBoxExchangeInfo[i].sV3 = -1;
				m_stDialogBoxExchangeInfo[i].sV4 = -1;
				m_stDialogBoxExchangeInfo[i].sV5 = -1;
				m_stDialogBoxExchangeInfo[i].sV6 = -1;
				m_stDialogBoxExchangeInfo[i].sV7 = -1;
				m_stDialogBoxExchangeInfo[i].dwV1 = 0;
			}
			DisableDialogBox(17);
			DisableDialogBox(20);
			DisableDialogBox(23);
			DisableDialogBox(26);
		}
		break;

	case 41: // Snoopy: 7 mar 06 (MultiTrade) Confirmation dialog
		break;

	case 28:
		if (m_bIsDialogEnabled[28] == FALSE) {
			m_stDialogBoxInfo[28].cMode = cType;
			m_stDialogBoxInfo[28].sX = m_stDialogBoxInfo[1].sX + 20;
			m_stDialogBoxInfo[28].sY = m_stDialogBoxInfo[1].sY + 20;
		}
		break;

	case 32:
		if (m_bIsDialogEnabled[32] == FALSE) {
			m_stDialogBoxInfo[32].cMode = cType;
			m_stDialogBoxInfo[32].sX = m_stDialogBoxInfo[1].sX + 20;
			m_stDialogBoxInfo[32].sY = m_stDialogBoxInfo[1].sY + 20;
		}
		break;

	case 33:
		 if ((m_iHP <= 0) || (m_bCitizen==FALSE)) return;
		if (m_bIsDialogEnabled[33] == FALSE)
		{	m_stDialogBoxInfo[33].cMode = cType;
			m_stDialogBoxInfo[33].sX  = 360;
			m_stDialogBoxInfo[33].sY  = 65;
			m_stDialogBoxInfo[33].sV1 = sV1;
		}
		break;

	case 34:
		if (m_bIsDialogEnabled[34] == FALSE)
		{	int iSoX, iSoM;
			iSoX = iSoM = 0;
			for (i = 0; i < DEF_MAXITEMS; i++)
			if (m_pItemList[i] != NULL)
			{	if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 128)) iSoX++;
				if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 129)) iSoM++;
			}
			if ((iSoX > 0) || (iSoM > 0))
			{	m_stDialogBoxInfo[34].cMode = 6; // Stone upgrade
				m_stDialogBoxInfo[34].sV2 = iSoX;
				m_stDialogBoxInfo[34].sV3 = iSoM;
				m_stDialogBoxInfo[34].sV1  = -1;
				m_stDialogBoxInfo[34].dwV1 = NULL;
			}else if (m_iGizonItemUpgradeLeft >0)
			{	m_stDialogBoxInfo[34].cMode = 1;
				m_stDialogBoxInfo[34].sV2 = -1;
				m_stDialogBoxInfo[34].sV3 = -1;
				m_stDialogBoxInfo[34].sV1  = -1;
				m_stDialogBoxInfo[34].dwV1 = NULL;
			}else
			{	AddEventList(DRAW_DIALOGBOX_ITEMUPGRADE30, 10); // "Stone of Xelima or Merien is not present."
				return;
		}	}
		break;

	case 16:
		if (m_bIsDialogEnabled[iBoxID]  == FALSE) {
			if (m_cSkillMastery[4] == 0) {
				 DisableDialogBox(16);
				 EnableDialogBox(21, 0, 480, 0);
				 return;
			}
			else {
				m_stDialogBoxInfo[iBoxID].cMode = 0;
				m_stDialogBoxInfo[iBoxID].sView = 0;
			}
		}
		break;

	case 14:
		EndInputString();
		if (m_bIsDialogEnabled[iBoxID]  == FALSE) {
			m_stDialogBoxInfo[iBoxID].cMode	= 0;
			m_stDialogBoxInfo[iBoxID].sView = 0;
			EnableDialogBox(2, NULL, NULL, NULL);
		}
		break;

	case 40: // Slates
		if (m_bIsDialogEnabled[40] == FALSE) {
			m_stDialogBoxInfo[40].sView = 0;
			m_stDialogBoxInfo[40].cMode	= cType;
			m_stDialogBoxInfo[40].sV1   = -1;
			m_stDialogBoxInfo[40].sV2   = -1;
			m_stDialogBoxInfo[40].sV3   = -1;
			m_stDialogBoxInfo[40].sV4   = -1;
			m_stDialogBoxInfo[40].sV5   = -1;
			m_stDialogBoxInfo[40].sV6   = -1;
			m_stDialogBoxInfo[40].cStr[0] = 0;
			m_stDialogBoxInfo[40].cStr[1] = 0;
			m_stDialogBoxInfo[40].cStr[4] = 0;

			m_stDialogBoxInfo[40].sSizeX = 180;
			m_stDialogBoxInfo[40].sSizeY = 183;

			DisableDialogBox(17);
			DisableDialogBox(20);
			DisableDialogBox(23);
			DisableDialogBox(26);
		}
		break;
	case 42: // Diuuude: Change stats window
		if (m_bIsDialogEnabled[42] == FALSE) {
			m_stDialogBoxInfo[42].sX = m_stDialogBoxInfo[12].sX+10;
			m_stDialogBoxInfo[42].sY = m_stDialogBoxInfo[12].sY+10;
			m_stDialogBoxInfo[42].cMode	= 0;
			m_stDialogBoxInfo[42].sView = 0;
			m_bSkillUsingStatus = FALSE;
		}
		break;
	case 50: // Snoopy: Resurection
		if (m_bIsDialogEnabled[50] == FALSE)
		{	m_stDialogBoxInfo[50].sX = 185;
			m_stDialogBoxInfo[50].sY = 100;
			m_stDialogBoxInfo[50].cMode	= 0;
			m_stDialogBoxInfo[50].sView = 0;
			m_bSkillUsingStatus = FALSE;
		}
		break;

	default:
		EndInputString();
		if (m_bIsDialogEnabled[iBoxID]  == FALSE) {
			m_stDialogBoxInfo[iBoxID].cMode	= 0;
			m_stDialogBoxInfo[iBoxID].sView = 0;
		}
		break;
	}
	if( iBoxID != 30 )
	{	if (m_bIsDialogEnabled[iBoxID]  == FALSE)
		{	if( m_stDialogBoxInfo[iBoxID].sY > 400 ) m_stDialogBoxInfo[iBoxID].sY = 410;
			if( m_stDialogBoxInfo[iBoxID].sX > 620 ) m_stDialogBoxInfo[iBoxID].sX = 620;
			if( (m_stDialogBoxInfo[iBoxID].sX+m_stDialogBoxInfo[iBoxID].sSizeX) < 10 ) m_stDialogBoxInfo[iBoxID].sX += 20;
			if( (m_stDialogBoxInfo[iBoxID].sY+m_stDialogBoxInfo[iBoxID].sSizeY) < 10 ) m_stDialogBoxInfo[iBoxID].sY += 20;
	}	}
	m_bIsDialogEnabled[iBoxID] = TRUE;
	if (pString != NULL) strcpy(m_stDialogBoxInfo[iBoxID].cStr, pString);
	//Snoopy: 39->59
	for (i = 0; i < 59; i++)
	if (m_cDialogBoxOrder[i] == iBoxID) m_cDialogBoxOrder[i] = NULL;
	//Snoopy: 39->59
	for (i = 1; i < 59; i++)
	if ((m_cDialogBoxOrder[i-1] == NULL) && (m_cDialogBoxOrder[i] != NULL)) {
		m_cDialogBoxOrder[i-1] = m_cDialogBoxOrder[i];
		m_cDialogBoxOrder[i] = NULL;
	}
	//Snoopy: 39->59
	for (i = 0; i < 59; i++)
	if (m_cDialogBoxOrder[i] == NULL) {
		m_cDialogBoxOrder[i] = iBoxID;
		return;
	}
}

void CGame::DisableDialogBox(int iBoxID)
{
 int i;

	switch (iBoxID) {
	case 4:
		m_bIsItemDisabled[m_stDialogBoxInfo[4].sView] = FALSE;
		break;

	case 5:
		m_bIsItemDisabled[m_stDialogBoxInfo[5].sView] = FALSE;
		break;

	case 6:
		m_bIsItemDisabled[m_stDialogBoxInfo[6].sView] = FALSE;
		break;

	case 7:
		if (m_stDialogBoxInfo[7].cMode == 1)
			EndInputString();
		m_stDialogBoxInfo[7].cMode = 0;
		break;

	case 11:
		for (i = 0; i < DEF_MAXMENUITEMS; i++)
		if (m_pItemForSaleList[i] != NULL) {
			delete m_pItemForSaleList[i];
			m_pItemForSaleList[i] = NULL;
		}
		m_stDialogBoxInfo[39].sV3 = 0;
		m_stDialogBoxInfo[39].sV4 = 0; // v1.4
		m_stDialogBoxInfo[39].sV5 = 0;
		m_stDialogBoxInfo[39].sV6 = 0;
		break;

	case 14:
		if (m_stDialogBoxInfo[14].cMode < 0) return;
		break;

	case 17:
		if (m_stDialogBoxInfo[17].cMode == 1) {
			EndInputString();
			m_bIsItemDisabled[m_stDialogBoxInfo[17].sView] = FALSE;
		}
		break;

	case 20: // v1.4
		m_bIsItemDisabled[m_stDialogBoxInfo[20].sV1] = FALSE;
		break;

	case 21:
		if (m_stDialogBoxInfo[21].sV2 == 500)
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GETMAGICABILITY, NULL, NULL, NULL, NULL, NULL);
		}
		break;

	case 24:
		m_bSkillUsingStatus = FALSE;
		break;

	case 26:
		if (m_stDialogBoxInfo[26].sV1 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = FALSE;
		if (m_stDialogBoxInfo[26].sV2 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = FALSE;
		if (m_stDialogBoxInfo[26].sV3 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = FALSE;
		if (m_stDialogBoxInfo[26].sV4 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = FALSE;
		if (m_stDialogBoxInfo[26].sV5 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = FALSE;
		if (m_stDialogBoxInfo[26].sV6 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = FALSE;
		m_bSkillUsingStatus = FALSE;
		break;

	case 27: //Snoopy: 7 mar 06 (multiTrade) case rewriten
		for (i=0; i<8;i++)
		{	ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr1, sizeof(m_stDialogBoxExchangeInfo[i].cStr1));
			ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr2, sizeof(m_stDialogBoxExchangeInfo[i].cStr2));
			m_stDialogBoxExchangeInfo[i].sV1 = -1;
			m_stDialogBoxExchangeInfo[i].sV2 = -1;
			m_stDialogBoxExchangeInfo[i].sV3 = -1;
			m_stDialogBoxExchangeInfo[i].sV4 = -1;
			m_stDialogBoxExchangeInfo[i].sV5 = -1;
			m_stDialogBoxExchangeInfo[i].sV6 = -1;
			m_stDialogBoxExchangeInfo[i].sV7 = -1;
			m_stDialogBoxExchangeInfo[i].dwV1 = 0;
			if (m_bIsItemDisabled[m_stDialogBoxExchangeInfo[i].sItemID] == TRUE)
				m_bIsItemDisabled[m_stDialogBoxExchangeInfo[i].sItemID] = FALSE;
		}
		break;


	case 31:
		for (i = 0; i < DEF_MAXSELLLIST; i++)
		{	if (m_stSellItemList[i].iIndex != -1) m_bIsItemDisabled[m_stSellItemList[i].iIndex] = FALSE;
			m_stSellItemList[i].iIndex = -1;
			m_stSellItemList[i].iAmount = 0;
		}
		break;

	case 34:
		if(m_stDialogBoxInfo[34].sV1 != -1)
		m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = FALSE;
		break;

	case 40:
		m_bIsItemDisabled[m_stDialogBoxInfo[40].sV1] = FALSE;
		m_bIsItemDisabled[m_stDialogBoxInfo[40].sV2] = FALSE;
		m_bIsItemDisabled[m_stDialogBoxInfo[40].sV3] = FALSE;
		m_bIsItemDisabled[m_stDialogBoxInfo[40].sV4] = FALSE;

		ZeroMemory(m_stDialogBoxInfo[40].cStr, sizeof(m_stDialogBoxInfo[40].cStr));
		ZeroMemory(m_stDialogBoxInfo[40].cStr2, sizeof(m_stDialogBoxInfo[40].cStr2));
		ZeroMemory(m_stDialogBoxInfo[40].cStr3, sizeof(m_stDialogBoxInfo[40].cStr3));
		ZeroMemory(m_stDialogBoxInfo[40].cStr4, sizeof(m_stDialogBoxInfo[40].cStr4));
		m_stDialogBoxInfo[40].sV1   = -1;
		m_stDialogBoxInfo[40].sV2   = -1;
		m_stDialogBoxInfo[40].sV3   = -1;
		m_stDialogBoxInfo[40].sV4   = -1;
		m_stDialogBoxInfo[40].sV5   = -1;
		m_stDialogBoxInfo[40].sV6   = -1;
		m_stDialogBoxInfo[40].sV9   = -1;
		m_stDialogBoxInfo[40].sV10   = -1;
		m_stDialogBoxInfo[40].sV11   = -1;
		m_stDialogBoxInfo[40].sV12   = -1;
		m_stDialogBoxInfo[40].sV13   = -1;
		m_stDialogBoxInfo[40].sV14   = -1;
		m_stDialogBoxInfo[40].dwV1   = 0;
		m_stDialogBoxInfo[40].dwV2   = 0;
		break;

	case 42:
		cStateChange1 = 0;
		cStateChange2 = 0;
		cStateChange3 = 0;
	/*	m_cLU_Str = 0;
		m_cLU_Vit = 0;
		m_cLU_Dex = 0;
		m_cLU_Int = 0;
		m_cLU_Mag = 0;
		m_cLU_Char = 0;*/
		break;

 	}

	m_bIsDialogEnabled[iBoxID] = FALSE;
	// Snoopy: 39->59
	for (i = 0; i < 59; i++)
	if (m_cDialogBoxOrder[i] == iBoxID)
		m_cDialogBoxOrder[i] = NULL;

	// Snoopy: 39->59
	for (i = 1; i < 59; i++)
	if ((m_cDialogBoxOrder[i-1] == NULL) && (m_cDialogBoxOrder[i] != NULL))
	{	m_cDialogBoxOrder[i-1] = m_cDialogBoxOrder[i];
		m_cDialogBoxOrder[i] = NULL;
	}
}


int CGame::iGetTopDialogBoxIndex()
{
 int i;
	//Snoopy: 38->58
	for (i = 58; i >= 0; i--)
	if (m_cDialogBoxOrder[i] != NULL)
		return m_cDialogBoxOrder[i];

	return NULL;
}
void CGame::DlgBoxClick_IconPannel(short msX, short msY)
{ short sX, sY;
	sX = m_stDialogBoxInfo[30].sX;
	sY = m_stDialogBoxInfo[30].sY;
	// CLEROTH - LU
/*	if ((msX > 322)	&& (msX < 355) && (434 < msY) && (475 > msY))
	{	if (m_iLU_Point <= 0) return;
		if (m_bIsDialogEnabled[12] == TRUE)
			 DisableDialogBox(12);
		else EnableDialogBox(12, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}*/
	if ((msX > 322)	&& (msX < 355) && (434 < msY) && (475 > msY)) {
		// Crusade
		if (m_bIsCrusadeMode == FALSE) return;
		switch (m_iCrusadeDuty) {
		case 1: // Fighter
			EnableDialogBox(38, NULL, NULL, NULL);
			break;

		case 2: // Constructor
			EnableDialogBox(37, NULL, NULL, NULL);
			break;

		case 3: // Commander
			EnableDialogBox(36, NULL, NULL, NULL);
			break;

		default: break;
		}
		PlaySound('E', 14, 5);
	}

	if ((362 < msX)	&& (404 > msX) && (434 < msY) && (475 > msY)) {
		// Combat Mode Toggle
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, NULL, NULL, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}

	// Character
	if ((413 <= msX) && (446 >= msX) && (434 < msY) && (475 > msY)) {
		if (m_bIsDialogEnabled[1] == TRUE)
			 DisableDialogBox(1);
		else EnableDialogBox(1, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}

	// Inventory
	if ((453 <= msX) && (486 >= msX) && (434 < msY) && (475 > msY)) {
		if (m_bIsDialogEnabled[2] == TRUE)
			 DisableDialogBox(2);
		else EnableDialogBox(2, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}

	// Magic
	if ((490 <= msX) && (522 >= msX) && (434 < msY) && (475 > msY)) {
		if (m_bIsDialogEnabled[3] == TRUE)
			 DisableDialogBox(3);
		else EnableDialogBox(3, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}

	// Skill
	if ((526 <= msX) && (552 >= msX) && (434 < msY) && (475 > msY)) {
		if (m_bIsDialogEnabled[15] == TRUE)
			 DisableDialogBox(15);
		else EnableDialogBox(15, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}

	// Chat
	if ((556 <= msX) && (587 >= msX) && (434 < msY) && (475 > msY)) {
		if (m_bIsDialogEnabled[10] == TRUE)
			 DisableDialogBox(10);
		else EnableDialogBox(10, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}

	// System Menu
	if ((589 <= msX) && (621 >= msX) && (434 < msY) && (475 > msY)) {
		if (m_bIsDialogEnabled[19] == TRUE)
			 DisableDialogBox(19);
		else EnableDialogBox(19, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
	}
}



void CGame::DrawChatMsgs(short sX, short sY, short dX, short dY)
{
 int i;

	for (i = 0; i < DEF_MAXCHATMSGS; i++)
	if (m_pChatMsgList[i] != NULL)
	if ( (m_pChatMsgList[i]->m_sX >= sX) && (m_pChatMsgList[i]->m_sX <= dX) &&
	     (m_pChatMsgList[i]->m_sY >= sY) && (m_pChatMsgList[i]->m_sY <= dY) ) {

		switch (m_pChatMsgList[i]->m_cType) {
		case 41:
		case 42:
		case 21:
		case 22:
		case 23:
			DrawChatMsgBox(m_pChatMsgList[i]->m_sX, m_pChatMsgList[i]->m_sY, i, FALSE);
			break;
		}
	}

	m_DDraw._GetBackBufferDC();
	for (i = 0; i < DEF_MAXCHATMSGS; i++)
	if (m_pChatMsgList[i] != NULL)
	if ( (m_pChatMsgList[i]->m_sX >= sX) && (m_pChatMsgList[i]->m_sX <= dX) &&
	     (m_pChatMsgList[i]->m_sY >= sY) && (m_pChatMsgList[i]->m_sY <= dY) ) {

		switch (m_pChatMsgList[i]->m_cType) {
		case 41:
		case 42:
		case 21:
		case 22:
		case 23:
			break;

		case 20:
		default:
			DrawChatMsgBox(m_pChatMsgList[i]->m_sX, m_pChatMsgList[i]->m_sY, i, TRUE);
			break;
		}
	}
	m_DDraw._ReleaseBackBufferDC();
}



void CGame::_LoadTextDlgContents(int cType)
{char * pContents, * token, cTemp[120], cFileName[120];
 char   seps[] = "\n";
 int    iIndex = 0, i;
 class  CStrTok * pStrTok;
 DWORD  dwFileSize;
 HANDLE hFile;
 FILE * pFile;
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{	if (m_pMsgTextList[i] != NULL)
			delete m_pMsgTextList[i];
		m_pMsgTextList[i] = NULL;
	}
	// cType
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
	else
	{ 	pContents = new char[dwFileSize+1];
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, dwFileSize, 1, pFile);
	}
	fclose(pFile);
	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL )
	{	m_pMsgTextList[iIndex] = new class CMsg(NULL, token, NULL);
		token = pStrTok->pGet();
		iIndex++;
	}
	delete pStrTok;
	delete[] pContents;
}



int CGame::_iLoadTextDlgContents2(int iType)
{char * pContents, * token, cTemp[120], cFileName[120];
 char   seps[] = "\n";
 int    iIndex = 0, i;
 class  CStrTok * pStrTok;
 DWORD  dwFileSize;
 HANDLE hFile;
 FILE * pFile;
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{	if (m_pMsgTextList2[i] != NULL)
			delete m_pMsgTextList2[i];
		m_pMsgTextList2[i] = NULL;
	}
	// cType
	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFileName, sizeof(cFileName));

	wsprintf(cTemp, "contents%d", iType);

	strcat(cFileName, "contents");
	strcat(cFileName, "\\");
	strcat(cFileName, "\\");
	strcat(cFileName, cTemp);
	strcat(cFileName, ".txt");
	hFile = CreateFile(cFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
	pFile = fopen(cFileName, "rt");
	if (pFile == NULL) return -1;
	else
	{	pContents = new char[dwFileSize+1];
		if (pContents == NULL) return -1;
		ZeroMemory(pContents, dwFileSize+1);
		fread(pContents, dwFileSize, 1, pFile);
	}
	fclose(pFile);
	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();
	while( token != NULL )
	{	m_pMsgTextList2[iIndex] = new class CMsg(NULL, token, NULL);
		token = pStrTok->pGet();
		iIndex++;
	}
	delete pStrTok;
	delete[] pContents;
	return iIndex;
}




void CGame::_LoadGameMsgTextContents()
{
 char * pContents, * token, cTemp[120], cFileName[120];
 char   seps[] = ";\n";
 int    iIndex = 0, i;
 class  CStrTok * pStrTok;
 DWORD  dwFileSize;
 HANDLE hFile;
 FILE * pFile;

	for (i = 0; i < DEF_MAXGAMEMSGS; i++) {
		if (m_pGameMsgList[i] != NULL)
			delete m_pGameMsgList[i];
		m_pGameMsgList[i] = NULL;
	}

	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFileName, sizeof(cFileName));

	strcpy(cTemp, "GameMsgList");

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
		m_pGameMsgList[iIndex] = new class CMsg(NULL, token, NULL);
		token = pStrTok->pGet();
		iIndex++;
	}

	delete pStrTok;
	delete[] pContents;
}

void CGame::DlgBoxClick_Party(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[32].sX;
	sY = m_stDialogBoxInfo[32].sY;

	switch (m_stDialogBoxInfo[32].cMode) {
	case 0:
		if (m_iPartyStatus == 0)
		{	if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 80) && (msY < sY + 100))
			{	m_stDialogBoxInfo[32].cMode = 2;
				m_bIsGetPointingMode = TRUE;
				m_iPointCommandType  = 200;
				PlaySound('E', 14, 5);
		}	}

		if (m_iPartyStatus != 0)
		{	if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 100) && (msY < sY + 120))
			{	m_stDialogBoxInfo[32].cMode = 11;
				PlaySound('E', 14, 5);
		}	}

		if (m_iPartyStatus != 0)
		{	if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 120) && (msY < sY + 140))
			{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, NULL, 2, NULL, NULL, m_cMCName);
				m_stDialogBoxInfo[32].cMode = 4;
				PlaySound('E', 14, 5);
		}	}

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) DisableDialogBox(32);
		break;

	case 1:
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY, NULL, 1, NULL, NULL, m_stDialogBoxInfo[32].cStr);
			DisableDialogBox(32);
			PlaySound('E', 14, 5);
		}

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY, NULL, 0, NULL, NULL, m_stDialogBoxInfo[32].cStr);
			DisableDialogBox(32);
			PlaySound('E', 14, 5);
		}
		break;

	case 2:
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			m_stDialogBoxInfo[32].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 3:
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			m_stDialogBoxInfo[32].cMode = 0;
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY, NULL, 2, NULL, NULL, m_stDialogBoxInfo[32].cStr);
			DisableDialogBox(32);
			PlaySound('E', 14, 5);
		}
		break;

	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			m_stDialogBoxInfo[32].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 11:
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, NULL, NULL, NULL, NULL, m_cMCName);
			m_stDialogBoxInfo[32].cMode = 5;
			PlaySound('E', 14, 5);
		}

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			m_stDialogBoxInfo[32].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;
	}
}


void CGame::DlgBoxClick_CrusadeJob(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[33].sX;
	sY = m_stDialogBoxInfo[33].sY;

	switch (m_stDialogBoxInfo[33].cMode) {
	case 1:
		if( m_bCitizen == FALSE )
		{	DisableDialogBox(33);
			PlaySound('E', 14, 5);
		}else if (m_bAresden == TRUE)
		{	if (m_iGuildRank == 0)
			{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, NULL, 3, NULL, NULL, NULL);
					DisableDialogBox(33);
					PlaySound('E', 14, 5);
				}
 			}else
			{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, NULL, 1, NULL, NULL, NULL);
					DisableDialogBox(33);
				}
				if (m_iGuildRank != -1)
				{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
					{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, NULL, 2, NULL, NULL, NULL);
						DisableDialogBox(33);
						PlaySound('E', 14, 5);
			}	}	}
		}else if (m_bAresden == FALSE)
		{	if (m_iGuildRank == 0)
			{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, NULL, 3, NULL, NULL, NULL);
					DisableDialogBox(33);
					PlaySound('E', 14, 5);
				}
			}else
			{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, NULL, 1, NULL, NULL, NULL);
					DisableDialogBox(33);
					PlaySound('E', 14, 5);
				}
				if (m_iGuildRank != -1)
				{	if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
					{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, NULL, 2, NULL, NULL, NULL);
						DisableDialogBox(33);
						PlaySound('E', 14, 5);
		} 	}	}	}

		if ((msX > sX + 210) && (msX < sX + 260) && (msY >= sY + 296) && (msY <= sY + 316))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 813, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 2:
		if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 160) && (msY < sY + 175))
		{	switch (m_iCrusadeDuty) {
			case 1: EnableDialogBox(18, 803, NULL, NULL); break;
			case 2: EnableDialogBox(18, 805, NULL, NULL); break;
			case 3: EnableDialogBox(18, 808, NULL, NULL); break;
		}	}

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			DisableDialogBox(33);
			PlaySound('E', 14, 5);
		}
		break;
	}
}

void CGame::_RequestMapStatus(char * pMapName, int iMode)
{
	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_MAPSTATUS, NULL, iMode, NULL, NULL, pMapName);
}

void CGame::AddMapStatusInfo(char * pData, BOOL bIsLastData)
{
 char * cp, cTotal;
 short * sp, sIndex;
 int i;

	ZeroMemory(m_cStatusMapName, sizeof(m_cStatusMapName));

	cp = (char *)(pData + 6);
	memcpy(m_cStatusMapName, cp, 10);
	cp += 10;

	sp = (short *)cp;
	sIndex = *sp;
	cp += 2;

	cTotal = *cp;
	cp++;

	for (i = 1; i <= cTotal; i++) {
		m_stCrusadeStructureInfo[sIndex].cType = *cp;
		cp++;
		sp = (short *)cp;
		m_stCrusadeStructureInfo[sIndex].sX = *sp;
		cp += 2;
		sp = (short *)cp;
		m_stCrusadeStructureInfo[sIndex].sY = *sp;
		cp += 2;
		m_stCrusadeStructureInfo[sIndex].cSide = *cp;
		cp++;

		sIndex++;
	}

	if (bIsLastData == TRUE) {
		while (sIndex < DEF_MAXCRUSADESTRUCTURES) {
			m_stCrusadeStructureInfo[sIndex].cType = NULL;
			m_stCrusadeStructureInfo[sIndex].sX = NULL;
			m_stCrusadeStructureInfo[sIndex].sY = NULL;
			m_stCrusadeStructureInfo[sIndex].cSide = NULL;
			sIndex++;
		}
	}
}

#ifdef DEF_USING_WIN_IME
bool CGame::GetText(HWND hWnd,UINT msg,WPARAM wparam, LPARAM lparam)
{ 	if( m_pInputBuffer == NULL) return FALSE;
	if( G_hEditWnd == NULL ) return FALSE;
	switch( msg ) {
	case WM_CHAR:
		if( (wparam == 22) || (wparam == 3) || (wparam == 9) || (wparam == 13) ) return TRUE;
		if( strlen(m_pInputBuffer) < m_cInputMaxLen-1 ) SendMessage( G_hEditWnd, msg, wparam, lparam );
		return TRUE;
	case WM_IME_COMPOSITION:
		if( strlen(m_pInputBuffer) < (m_cInputMaxLen -2) ) SendMessage( G_hEditWnd, msg, wparam, lparam );
		return TRUE;
	case WM_IME_CHAR:
	case WM_IME_COMPOSITIONFULL:
	case WM_IME_CONTROL:
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_NOTIFY:
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_SETCONTEXT:
	case WM_IME_KEYDOWN:
	case WM_IME_KEYUP:
	case WM_IME_SELECT:
		SendMessage( G_hEditWnd, msg, wparam, lparam );
		return TRUE;
	case WM_KEYUP:
		SendMessage( G_hEditWnd, msg, wparam, lparam );
		return FALSE;
	case WM_KEYDOWN:
		if( wparam == 8 ) SendMessage( G_hEditWnd, msg, wparam, lparam );
		return FALSE;
	}
	return FALSE;
}

#else // no IME

bool CGame::GetText(HWND hWnd,UINT msg,WPARAM wparam, LPARAM lparam)
{ 	int len;
	HIMC hIMC=NULL;
	if (m_pInputBuffer == NULL) return FALSE;
	switch (msg) {
		case WM_IME_COMPOSITION:
			ZeroMemory(m_cEdit, sizeof(m_cEdit));
			if (lparam & GCS_RESULTSTR)
			{	hIMC = ImmGetContext(hWnd);
				len = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
				if( len > 4 ) len = 4;
				ImmGetCompositionString(hIMC, GCS_RESULTSTR, m_cEdit, len);
				ImmReleaseContext(hWnd, hIMC);
				len = strlen(m_pInputBuffer) + strlen(m_cEdit);
				if (len < m_cInputMaxLen) strcpy(m_pInputBuffer+strlen(m_pInputBuffer),m_cEdit);
				ZeroMemory(m_cEdit, sizeof(m_cEdit));
			}else if (lparam & GCS_COMPSTR)
			{	hIMC = ImmGetContext(hWnd);
				len = ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0);
				if( len > 4 ) len = 4;
				ImmGetCompositionString(hIMC, GCS_COMPSTR, m_cEdit, len);
				ImmReleaseContext(hWnd, hIMC);
				len = strlen(m_pInputBuffer) + strlen(m_cEdit);
				if (len >= m_cInputMaxLen) ZeroMemory(m_cEdit, sizeof(m_cEdit));
			}
			return TRUE;

		case WM_CHAR:
			if(wparam == 8)
			{	if(strlen(m_pInputBuffer) > 0)
				{	len = strlen(m_pInputBuffer);
					switch (GetCharKind(m_pInputBuffer, len-1)) {
					case 1:
						m_pInputBuffer[len-1] = NULL;
						break;
					case 2:
					case 3:
						m_pInputBuffer[len-2]  = NULL;
						m_pInputBuffer[len-1]  = NULL;
						break;
					}
					ZeroMemory(m_cEdit, sizeof(m_cEdit));
				}
			}else if ((wparam != 9) && (wparam != 13) && (wparam != 27))
			{	len = strlen(m_pInputBuffer);
				if (len >= m_cInputMaxLen-1) return FALSE;
				m_pInputBuffer[len] = wparam & 0xff;
				m_pInputBuffer[len+1] = 0;
			}
			return TRUE;
	}
	return FALSE;
}
#endif


int CGame::GetCharKind(char *str, int index)
{	int kind=1;
    do
	{	if(kind==2) kind=3;
		else
		{	if((unsigned char) *str < 128) kind=1;
	    	else kind=2;
		}
		str++;
		index--;
    }
	while(index>=0);
    return kind;
}

void CGame::ShowReceivedString(BOOL bIsHide)
{
	ZeroMemory(G_cTxt, sizeof(G_cTxt));

#ifdef DEF_USING_WIN_IME
	if( G_hEditWnd != NULL ) GetWindowText(G_hEditWnd, m_pInputBuffer, (int)m_cInputMaxLen);
	strcpy(G_cTxt, m_pInputBuffer);
#else
	strcpy(G_cTxt, m_pInputBuffer);
	if( (m_cEdit[0] != 0) && ( strlen(m_pInputBuffer)+strlen(m_cEdit)+1 <= m_cInputMaxLen ) )
	{	strcpy(G_cTxt + strlen(m_pInputBuffer), m_cEdit);
	}
#endif
	if (bIsHide == TRUE)
	{	for (unsigned char i = 0; i < strlen(G_cTxt); i++)
		if (G_cTxt[i] != NULL) G_cTxt[i] = '*';
	}

	if( (G_dwGlobalTime%400) < 210 ) G_cTxt[strlen(G_cTxt)] = '_';

	PutString(m_iInputX+1, m_iInputY+1, G_cTxt, RGB(0,0,0));
	PutString(m_iInputX, m_iInputY+1, G_cTxt, RGB(0,0,0));
	PutString(m_iInputX+1, m_iInputY, G_cTxt, RGB(0,0,0));
	PutString(m_iInputX, m_iInputY, G_cTxt, RGB(255,255,255));
}

void CGame::ClearInputString()
{
	if (m_pInputBuffer != NULL)	ZeroMemory(m_pInputBuffer, sizeof(m_pInputBuffer));
	ZeroMemory(m_cEdit, sizeof(m_cEdit));
#ifdef DEF_USING_WIN_IME
	if (G_hEditWnd != NULL)	SetWindowText(G_hEditWnd, "");
#endif
}

void CGame::StartInputString(int sX, int sY, unsigned char iLen, char * pBuffer, BOOL bIsHide)
{
	m_bInputStatus = TRUE;
	m_iInputX = sX;
	m_iInputY = sY;
	m_pInputBuffer = pBuffer;
	ZeroMemory(m_cEdit, sizeof(m_cEdit));
	m_cInputMaxLen = iLen;
#ifdef DEF_USING_WIN_IME
	if (bIsHide == FALSE) G_hEditWnd = CreateWindow( RICHEDIT_CLASS, NULL, WS_POPUP | ES_SELFIME, sX-5 , sY -1, iLen*12, 16, G_hWnd, (HMENU)0, G_hInstance, NULL);
	else G_hEditWnd = CreateWindow( RICHEDIT_CLASS, NULL, WS_POPUP | ES_PASSWORD | ES_SELFIME, sX-5 , sY -1, iLen*12, 16, G_hWnd, (HMENU)0, G_hInstance, NULL);
	SetWindowText(G_hEditWnd, m_pInputBuffer);
	SendMessage(G_hEditWnd, EM_EXLIMITTEXT, 0, iLen-1 );
	SendMessage(G_hEditWnd, EM_SETLANGOPTIONS, 0, ~IMF_AUTOFONT);
	COMPOSITIONFORM composform;
	composform.dwStyle = CFS_POINT;
	composform.ptCurrentPos.x = sX;
	composform.ptCurrentPos.y = sY;
	HIMC hImc = ImmGetContext(G_hWnd);
	ImmSetCompositionWindow( hImc, &composform );
	int StrLen = strlen( m_pInputBuffer );
	SendMessage(G_hEditWnd, EM_SETSEL, StrLen, StrLen);
#endif
}

void CGame::EndInputString()
{	m_bInputStatus = FALSE;
#ifdef DEF_USING_WIN_IME
	if (G_hEditWnd != NULL)
	{	GetWindowText(G_hEditWnd, m_pInputBuffer, (int)m_cInputMaxLen);
		CANDIDATEFORM candiform;
		SendMessage(G_hEditWnd, WM_IME_CONTROL, IMC_GETCANDIDATEPOS, (LPARAM)&candiform);
		DestroyWindow(G_hEditWnd);
		G_hEditWnd = NULL;
	}
#else
	int len = strlen(m_cEdit);
	if (len > 0)
	{	m_cEdit[len] = 0;
		strcpy(m_pInputBuffer+strlen(m_pInputBuffer),m_cEdit);
		ZeroMemory( m_cEdit, sizeof(m_cEdit) );
	}
#endif
}

void CGame::ReceiveString(char *pString)
{
	strcpy(pString, m_pInputBuffer);

#ifdef DEF_USING_WIN_IME
	if (G_hEditWnd != NULL) GetWindowText(G_hEditWnd, pString, (int)m_cInputMaxLen);
#endif
}

void CGame::DrawNewDialogBox(char cType, int sX, int sY, int iFrame, BOOL bIsNoColorKey, BOOL bIsTrans)
{
 DWORD dwTime = G_dwGlobalTime;

	if (m_pSprite[cType] == NULL) return;
	if (bIsNoColorKey == FALSE)
	{	if (bIsTrans == TRUE)
			 m_pSprite[cType]->PutTransSprite2(sX, sY, iFrame, dwTime);
		else m_pSprite[cType]->PutSpriteFast(sX, sY, iFrame, dwTime);
	}
	else m_pSprite[cType]->PutSpriteFastNoColorKey(sX, sY, iFrame, dwTime);
}

void CGame::DlgBoxClick_Commander(int msX, int msY) // Snoopy: Fixed for 351
{short sX, sY, tX, tY;
 double d1, d2, d3;
	if (m_bIsCrusadeMode == FALSE) return;
	sX = m_stDialogBoxInfo[36].sX;
	sY = m_stDialogBoxInfo[36].sY;

	switch (m_stDialogBoxInfo[36].cMode) {
	case 0: // Main
		if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 1;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +50) && (msX <= sX +20 +46 +50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	if (m_iTeleportLocX == -1)
			{	SetTopMsg(m_pGameMsgList[15]->m_pMsg, 5);
			}else if (strcmp(m_cMapName, m_cTeleportMapName) == 0)
			{	SetTopMsg(m_pGameMsgList[16]->m_pMsg, 5);
			}else
			{	m_stDialogBoxInfo[36].cMode = 2;
				PlaySound('E', 14, 5);
		}	}
		if ((msX >= sX +20 +100) && (msX <= sX +20 +46 +100) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 3;
			m_stDialogBoxInfo[36].sV1   = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150) && (msX <= sX +20 +46 +150) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 4;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 808, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 1: // Set TP
		if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
		{	d1 = (double)(msX - (sX + 15));
			d2 = (double)(524.0f); //(752.0f);
			d3 = (d2*d1)/279.0f;
			tX = (int)d3;
			d1 = (double)(msY - (sY + 60));
			d2 = (double)(524.0f); //(680.0f);
			d3 = (d2*d1)/(280.0f); //253.0f;
			tY = (int)d3;
			if (tX < 30) tX = 30;
			if (tY < 30) tY = 30;
			if (tX > 494) tX = 494;//722;
			if (tY > 494) tY = 494;//650;
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETGUILDTELEPORTLOC, NULL, tX, tY, NULL, "middleland");
			m_stDialogBoxInfo[36].cMode = 0;
			PlaySound('E', 14, 5);
			_RequestMapStatus("middleland", 1);
		}
		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 809, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 2: // Use TP
		if ((msX >= sX +20 +50) && (msX <= sX +20 +46 +50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(36);
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 810, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 3: // Summon Unit
		if( m_bAresden == TRUE )
		{	if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 3000)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 47, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			}	}
			if ((msX >= sX +20 +50) && (msX <= sX +20 +50 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 2000)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 46, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			}	}
			if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 1000)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 43, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			}	}
			if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 1500)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 51, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			}	}
		}else if (m_bAresden == FALSE)
		{	if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 3000)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 45, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			} 	}
			if ((msX >= sX +20 +50) && (msX <= sX +20 +50 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 2000)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 44, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			} 	}
			if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 1000)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 43, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
			}	}
			if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
			{	if (m_iConstructionPoint >= 1500)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 51, 1, m_stDialogBoxInfo[36].sV1, NULL);
					PlaySound('E', 14, 5);
					DisableDialogBox(36);
		}	}	}
		if ((msX >= sX +20) && (msX <= sX +380) && (msY > sY +140) && (msY < sY +160))
		{	m_stDialogBoxInfo[36].sV1   = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20) && (msX <= sX +380) && (msY > sY +160) && (msY < sY +175))
		{	m_stDialogBoxInfo[36].sV1   = 1;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 811, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 4: // Set constr
		if (   (msX >= sX + 15) && (msX <= sX + 15 + 278)
			&& (msY >= sY + 60) && (msY <= sY + 60 + 272))
		{	d1 = (double)(msX - (sX + 15));
			d2 = (double)(524.0);//(752.0f);
			d3 = (d2*d1)/279.0f;
			tX = (int)d3;
			d1 = (double)(msY - (sY + 60));
			d2 = (double)(524.0);//(680.0f);
			d3 = (d2*d1)/(280.0);//253.0f;
			tY = (int)d3;
			if (tX < 30) tX = 30;
			if (tY < 30) tY = 30;
			if (tX > 494) tX = 494;//722;
			if (tY > 494) tY = 494;//650;
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETGUILDCONSTRUCTLOC, NULL, tX, tY, NULL, "middleland");
			m_stDialogBoxInfo[36].cMode = 0;
			PlaySound('E', 14, 5);
			_RequestMapStatus("middleland", 1);
		}
		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[36].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 812, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;
	}
}


void CGame::DlgBoxClick_Constructor(int msX, int msY)  // Snoopy: Fixed for 351
{ short sX, sY;
	if (m_bIsCrusadeMode == FALSE) return;
	sX = m_stDialogBoxInfo[37].sX;
	sY = m_stDialogBoxInfo[37].sY;

	switch (m_stDialogBoxInfo[37].cMode) {
	case 0: // Main
		if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	if (m_iConstructLocX == -1)
			{	SetTopMsg(m_pGameMsgList[14]->m_pMsg, 5);
			}else
			{	m_stDialogBoxInfo[37].cMode = 1;
				PlaySound('E', 14, 5);
		}	}
		if ((msX >= sX +20 +50) && (msX <= sX +20 +46 +50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	if (m_iTeleportLocX == -1)
			{	SetTopMsg(m_pGameMsgList[15]->m_pMsg, 5);
			}else if (strcmp(m_cMapName, m_cTeleportMapName) == 0)
			{	SetTopMsg(m_pGameMsgList[16]->m_pMsg, 5);
			}else
			{	m_stDialogBoxInfo[37].cMode = 2;
				PlaySound('E', 14, 5);
		}	}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 805, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 1: // Choose building
		if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 38, 1, m_stDialogBoxInfo[36].sV1, NULL);
			PlaySound('E', 14, 5);
			DisableDialogBox(37);
		}
		if ((msX >= sX +20 +50) && (msX <= sX +20 +50 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 39, 1, m_stDialogBoxInfo[36].sV1, NULL);
			PlaySound('E', 14, 5);
			DisableDialogBox(37);
		}
		if ((msX >= sX +20 +100) && (msX <= sX +20 +100 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 36, 1, m_stDialogBoxInfo[36].sV1, NULL);
			PlaySound('E', 14, 5);
			DisableDialogBox(37);
		}
		if ((msX >= sX +20 +150) && (msX <= sX +20 +150 +45) && (msY >= sY +220) && (msY <= sY +220 +50))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, NULL, 37, 1, m_stDialogBoxInfo[36].sV1, NULL);
			PlaySound('E', 14, 5);
			DisableDialogBox(37);
		}

		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	m_stDialogBoxInfo[37].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 806, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 2: // Use TP
		if ((msX >= sX +20 +50) && (msX <= sX +20 +46 +50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(37);
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[37].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 807, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;
	}
}


void CGame::DlgBoxClick_Soldier(int msX, int msY) // Snoopy: Fixed for 351
{ short sX, sY;
	if (m_bIsCrusadeMode == FALSE) return;
	sX = m_stDialogBoxInfo[38].sX;
	sY = m_stDialogBoxInfo[38].sY;

	switch (m_stDialogBoxInfo[38].cMode) {
	case 0: // Main dlg
		if ((msX >= sX +20) && (msX <= sX +20 +46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	if (m_iTeleportLocX == -1)
			{	SetTopMsg(m_pGameMsgList[15]->m_pMsg, 5);
			}else if (strcmp(m_cMapName, m_cTeleportMapName) == 0)
			{	SetTopMsg(m_pGameMsgList[16]->m_pMsg, 5);
			}else
			{	m_stDialogBoxInfo[38].cMode = 1;
				PlaySound('E', 14, 5);
		}	}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 803, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 1: // Use TP
		if ((msX >= sX +20) && (msX <= sX +20 +46+50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(38);
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74 -50) && (msX <= sX +20 +46 +150 + 74 -50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	m_stDialogBoxInfo[38].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX +20 +150 + 74) && (msX <= sX +20 +46 +150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
		{	DisableDialogBox(18);
			EnableDialogBox(18, 804, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;
	}
}

void CGame::SetCameraShakingEffect(short sDist, int iMul)
{
 int iDegree;

	iDegree = 5 - sDist;
	if (iDegree <= 0) iDegree = 0;
	iDegree *= 2;

	if (iMul != 0) iDegree *= iMul;

	if (iDegree <= 2) return;

	m_iCameraShakingDegree = iDegree;
}

void CGame::MeteorStrikeComing(int iCode)
{
	switch (iCode) {
	case 1: //
		SetTopMsg(m_pGameMsgList[0]->m_pMsg, 5);
		break;
	case 2: //
		SetTopMsg(m_pGameMsgList[10]->m_pMsg, 10);
		break;
	case 3: //
		SetTopMsg(m_pGameMsgList[91]->m_pMsg, 5);
		break;
	case 4: //
		SetTopMsg(m_pGameMsgList[11]->m_pMsg, 10);
		break;
	}
}

void CGame::DrawObjectFOE(int ix, int iy, int iFrame)
{	if( _iGetFOE(_tmp_iStatus) < 0 ) // red crusade circle
	{	if (iFrame <= 4 ) m_pEffectSpr[38]->PutTransSprite(ix, iy, iFrame, G_dwGlobalTime);
	}
}

void CGame::SetTopMsg(char *pString, unsigned char iLastSec)
{
	ZeroMemory(m_cTopMsg, sizeof(m_cTopMsg));
	strcpy(m_cTopMsg, pString);

	m_iTopMsgLastSec = iLastSec;
	m_dwTopMsgTime   = G_dwGlobalTime;
}

void CGame::DrawTopMsg()
{
	if (strlen(m_cTopMsg) == 0) return;
	m_DDraw.DrawShadowBox(0, 0, 639, 30);

	if ((((G_dwGlobalTime - m_dwTopMsgTime)/250) % 2) == 0)
		PutAlignedString(0, 639, 10, m_cTopMsg, 255,255,255);

	if ( G_dwGlobalTime > (m_iTopMsgLastSec*1000+m_dwTopMsgTime) ) {
		ZeroMemory(m_cTopMsg, sizeof(m_cTopMsg));
	}
}


void CGame::DrawDialogBox_IconPannel(short msX, short msY)
{
 short sX, sY;
 DWORD dwTime = m_dwCurTime;

	sX = m_stDialogBoxInfo[30].sX;
	sY = m_stDialogBoxInfo[30].sY;

	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(sX, sY, 14, dwTime);

	if ((362 < msX)	&& (404 > msX) && (434 < msY) && (475 > msY)) {
		m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(362, 434, 16, dwTime);
	}

	if (m_bIsCombatMode) {
		if (m_bIsSafeAttackMode)
			 m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(368, 440, 4, dwTime);
		else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(368, 440, 5, dwTime);
	}

	if ((m_bIsCrusadeMode) && (m_iCrusadeDuty != 0)) {
		if (m_bAresden == TRUE) {
			if ((322 <= msX) && (355 >= msX) && (434 < msY) && (475 > msY))
				 m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 1, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 2, dwTime);
		}
		else if (m_bAresden == FALSE) {
			if ((322 <= msX) && (355 >= msX) && (434 < msY) && (475 > msY))
				 m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 0, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 15, dwTime);
		}
	}

	// CLEROTH - LU
	if ( m_iLU_Point > 0 ) {
			if ((322 <= msX) && (355 >= msX) && (434 < msY) && (475 > msY))
				 m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 17, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 18, dwTime);
	}

	if ((msY > 436) && (msY < 478))
	{
		if ((msX > 410) && (msX < 447))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(412, 434, 6, dwTime);// Character
		}
		if ((msX > 447) && (msX < 484))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(449, 434, 7, dwTime);// Inventory
		}
		if ((msX > 484) && (msX < 521))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(486, 434, 8, dwTime);// Magic
		}
		if ((msX > 521) && (msX < 558))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(523, 434, 9, dwTime);// Skill
		}
		if ((msX > 558) && (msX < 595))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(560, 434, 10, dwTime);// History
		}
		if ((msX > 595) && (msX < 631))
		{	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(597, 434, 11, dwTime);// System Menu
		}
	}

	if ( ((msX > 144) && (msX < 317) && (msY > 434) && (msY < 477)) || (m_bCtrlPressed) )
	{	int iLev = 0;
		int iCurExp  = iGetLevelExp(m_iLevel);
		int iNextExp = iGetLevelExp(m_iLevel+1);

#ifdef DEF_4XXP_PER_LVL
		if (m_iLevel > 139)
		{	iLev = (m_iLevel-139)*3;
			iNextExp = iGetLevelExp(m_iLevel+iLev);
		}
#endif

		if(m_iExp < iNextExp)
		{	iNextExp = iNextExp - iCurExp;
			if( m_iExp > iCurExp ) iCurExp = m_iExp - iCurExp; // curxp: partie faite
			else iCurExp = 0; // below current lvl !
			short sPerc = 0;
			if( iCurExp > 200000 ) sPerc = short( ((iCurExp>>4)*10000)/(iNextExp>>4) );
			else sPerc = (short)( (iCurExp*10000)/iNextExp );
			wsprintf(G_cTxt, "Rest Exp: %d(%d.%02d%%)", iNextExp-iCurExp, sPerc/100, sPerc%100);
		}else
		{	wsprintf(G_cTxt, "Exp: %d(100.00%)", m_iExp); // "Exp: 151000/150000"
		}
	}else wsprintf(G_cTxt, "%s(%d,%d)", m_cMapMessage, m_sPlayerX, m_sPlayerY);
	PutAlignedString(135, 328, 456, G_cTxt, 200,200,120);
}

void CGame::DrawDialogBox_GaugePannel()
{	int iMaxPoint, iBarWidth;
	// HP bar
	if (m_iAngelicStr !=0) iMaxPoint = m_iVit*3 + m_iLevel*2 + (m_iStr + m_iAngelicStr)/2;
	else				   iMaxPoint = m_iVit*3 + m_iLevel*2 + m_iStr/2;
	if (m_iHP > iMaxPoint) m_iHP = iMaxPoint;
	iBarWidth = 101 - (m_iHP*101)/iMaxPoint;
	if( iBarWidth < 0 ) iBarWidth = 0;
	if( iBarWidth > 101 ) iBarWidth = 101;
	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFastWidth(23, 437,  12, iBarWidth, m_dwCurTime);

	wsprintf(G_cTxt, "%d", (short) m_iHP);
	if (m_bIsPoisoned)
	{	 PutString_SprNum(85, 441, G_cTxt, m_wR[5]*11, m_wG[5]*11, m_wB[5]*11);
		 PutString_SprFont3(35, 440, "Poisoned", m_wR[5]*8, m_wG[5]*8, m_wB[5]*8, TRUE, 2);
	}else PutString_SprNum(85, 441, G_cTxt, 200, 100, 100);

	//MP bar
	iMaxPoint = (m_iMag + m_iAngelicMag)*2 + m_iLevel*2 + (m_iInt + m_iAngelicInt)/2;
	if (m_iMP > iMaxPoint) m_iMP = iMaxPoint;
	iBarWidth = 101 - (m_iMP*101)/iMaxPoint;
	if( iBarWidth < 0 ) iBarWidth = 0;
	if( iBarWidth > 101 ) iBarWidth = 101;
	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFastWidth(23, 459,  12, iBarWidth, m_dwCurTime);
	wsprintf(G_cTxt, "%d", (short) m_iMP);
	PutString_SprNum(85, 463, G_cTxt, 100, 100, 200);

	// SP bar
	if (m_iAngelicStr !=0) iMaxPoint = m_iLevel*2 + (m_iStr + m_iAngelicStr)*2;
	else				   iMaxPoint = m_iLevel*2 + m_iStr*2;
	if (m_iSP > iMaxPoint) m_iSP = iMaxPoint;
	iBarWidth = 167 - (m_iSP*167)/iMaxPoint;
	if( iBarWidth < 0 ) iBarWidth = 0;
	if( iBarWidth > 167 ) iBarWidth = 167;
	m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFastWidth(147, 435, 13, iBarWidth, m_dwCurTime);
}

void CGame::DrawDialogBox_Text(short msX, short msY, short msZ, char cLB)
{
 short sX, sY;
 int i, iTotalLines, iPointerLoc;
 double d1,d2,d3;

	sX = m_stDialogBoxInfo[18].sX;
	sY = m_stDialogBoxInfo[18].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);

	iTotalLines = 0;
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	if (m_pMsgTextList[i] != NULL) iTotalLines++;

	if( iTotalLines > 17 ) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
	if( iGetTopDialogBoxIndex() == 18 && msZ != 0 )
	{
		m_stDialogBoxInfo[18].sView = m_stDialogBoxInfo[18].sView - msZ/60;
		m_DInput.m_sZ = 0;
	}
	if( m_stDialogBoxInfo[18].sView < 0 ) m_stDialogBoxInfo[18].sView = 0;
	if( iTotalLines>17 && m_stDialogBoxInfo[18].sView > iTotalLines-17 ) m_stDialogBoxInfo[18].sView = iTotalLines-17;

	if (iTotalLines > 17) {
		d1 = (double)m_stDialogBoxInfo[18].sView;
		d2 = (double)(iTotalLines-17);
		d3 = (274.0f * d1)/d2;
		iPointerLoc = (int)(d3+0.5);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX+242, sY+35+iPointerLoc, 7);
	}
	else iPointerLoc = 0;

	for (i = 0; i < 17; i++)
	if (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView] != NULL) {
		if (m_bDialogTrans == FALSE) { // v2.173
			switch (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg[0]) {
			case '_': PutAlignedString(sX +24, sX +236, sY + 50 +i*13, (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg+1), 255,255,255); break;
			case ';': PutAlignedString(sX +24, sX +236, sY + 50 +i*13, (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg+1), 4, 0, 50); break;
			default: PutAlignedString(sX +24, sX +236, sY + 50 +i*13, m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg, 45,25,25); break;
			}
		}
		else PutAlignedString(sX +24, sX +236, sY + 50 +i*13, m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg, 0,0,0);
	}

	if (cLB != 0 && iTotalLines > 17) {
		if ((iGetTopDialogBoxIndex() == 18)) {
			if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
				d1 = (double)(msY -(sY+35));
				d2 = (double)(iTotalLines-17);
				d3 = (d1 * d2)/274.0f;
				iPointerLoc = (int)d3;
				if (iPointerLoc > iTotalLines-17) iPointerLoc = iTotalLines-17;
				m_stDialogBoxInfo[18].sView = iPointerLoc;
			}
		}
	}
	else m_stDialogBoxInfo[18].bIsScrollSelected = FALSE;

	if ((msX > sX + DEF_RBTNPOSX) && (msX < sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void CGame::DrawDialogBox_15AgeMsg(short msX, short msY)
{  return;
// Snoopy: removed FeedbackCard & minus 15 age

}


void CGame::DrawDialogBox_WarningMsg(short msX, short msY)//6
{
    short sX, sY;

	sX = m_stDialogBoxInfo[6].sX;
	sY = m_stDialogBoxInfo[6].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 2);

    PutString2(sX + 63, sY + 35, DEF_MSG_WARNING1, 200,200,25);//" ** This is a battle area **"
	PutString(sX + 30, sY + 57, DEF_MSG_WARNING2, RGB(220,130,45) );//"This is a dangerous area where you"
	PutString(sX + 30, sY + 74, DEF_MSG_WARNING3, RGB(220,130,45) );//"cannot protected from others' attack."
	PutString(sX + 30, sY + 92, DEF_MSG_WARNING4, RGB(220,130,45) );//"To play the game in safe, go to the"
	PutString(sX + 30, sY +110, DEF_MSG_WARNING5, RGB(220,130,45) );//" cityhall and change to civilian mode."

	if ((msX >= sX + 122 ) && (msX <= sX + 125 + DEF_BTNSZX ) && (msY >= sY + 127 ) && (msY <= sY + 127 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 122 , sY + 127 , 1);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 122, sY + 127 , 0);

}

void CGame::DrawDialogBox_ItemDrop(short msX, short msY)
{
    short sX, sY;
    char cTxt[120], cStr1[64], cStr2[64], cStr3[64];

	sX = m_stDialogBoxInfo[4].sX;
	sY = m_stDialogBoxInfo[4].sY;

	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

	GetItemName(m_pItemList[m_stDialogBoxInfo[4].sView]->m_cName, m_pItemList[m_stDialogBoxInfo[4].sView]->m_dwAttribute, cStr1, cStr2, cStr3 );

	if (strlen(m_stDialogBoxInfo[4].cStr) == 0)  wsprintf(cTxt, "%s", cStr1);

	if(m_bIsSpecial)
	{	PutString(sX + 35, sY + 20, cTxt, RGB(0,255,50));
		PutString(sX + 36, sY + 20, cTxt, RGB(0,255,50));
	}else
	{	PutString(sX + 35, sY + 20, cTxt, RGB(4,0,50));
		PutString(sX + 36, sY + 20, cTxt, RGB(4,0,50));
	}
	PutString(sX + 35, sY + 36, DRAW_DIALOGBOX_ITEM_DROP1 , RGB(4,0,50));
	PutString(sX + 36, sY + 36, DRAW_DIALOGBOX_ITEM_DROP1, RGB(4,0,50));

	if(m_bItemDrop)
	{	if ((msX >= sX + 35) && (msX <= sX + 240 ) && (msY >= sY + 80) && (msY <= sY + 90))
		{	PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(255,255,255));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(255,255,255));
		}else
		{	PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(4,0,50));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, RGB(4,0,50));
		}
	}else
	{	if ((msX >= sX + 35) && (msX <= sX + 240 ) && (msY >= sY + 80) && (msY <= sY + 90))
		{	PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(255,255,255));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(255,255,255));
		}else
		{	PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(4,0,50));
			PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, RGB(4,0,50));
	}	}

	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55 ,19);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55 , 18);

	if ((msX >= sX + 170 ) && (msX <= sX + 170 + DEF_BTNSZX ) && (msY >= sY + 55 ) && (msY <= sY + 55 + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170 , sY + 55 , 3);
	else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55 , 2);
}

void CGame::DrawDialogBox_NpcTalk(short msX, short msY, char cLB)
{
 short sX, sY;
 int i, iTotalLines, iPointerLoc;
 double d1, d2, d3;
	sX = m_stDialogBoxInfo[21].sX;
	sY = m_stDialogBoxInfo[21].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

	switch (m_stDialogBoxInfo[21].cMode) {
	case 0: //  OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
		break;

	case 1: // Accept / Decline
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
			 DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 41);
		else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 40);
		break;

	case 2: // Next
		if ((msX >= sX + 190) && (msX <= sX + 278) && (msY >= sY + 296) && (msY <= sY + 316))
			 PutString_SprFont(sX + 190, sY + 270, "Next", 6,6,20);
		else PutString_SprFont(sX + 190, sY + 270, "Next", 0,0,7);
		break;
	}

	for (i = 0; i < 17; i++)
	if ((i < DEF_TEXTDLGMAXLINES) && (m_pMsgTextList2[i + m_stDialogBoxInfo[21].sView] != NULL)) {
		PutAlignedString(sX, sX+m_stDialogBoxInfo[21].sSizeX, sY + 57 +i*15, m_pMsgTextList2[i + m_stDialogBoxInfo[21].sView]->m_pMsg, 45,25,25);
	}

	iTotalLines = 0;
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	if (m_pMsgTextList2[i] != NULL) iTotalLines++;

	if (iTotalLines > 17) {
		d1 = (double)m_stDialogBoxInfo[21].sView;
		d2 = (double)(iTotalLines-17);
		d3 = (274.0f * d1)/d2;
		iPointerLoc = (int)d3;
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
	}
	else iPointerLoc = 0;

	if (cLB != 0 && iTotalLines > 17) {
		if ((iGetTopDialogBoxIndex() == 21)) {
			if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320)) {
				d1 = (double)(msY -(sY+40));
				d2 = (double)(iTotalLines-17);
				d3 = (d1 * d2)/274.0f;
				iPointerLoc = (int)d3;

				if (iPointerLoc > iTotalLines) iPointerLoc = iTotalLines;
				m_stDialogBoxInfo[21].sView = iPointerLoc;
			}
		}
	}
	else m_stDialogBoxInfo[21].bIsScrollSelected = FALSE;
}

void CGame::DrawDialogBox_Slates(short msX, short msY, short msZ, char cLB)
{
 int iAdjX, iAdjY;
 short sX, sY;
 DWORD dwTime = m_dwCurTime;

	iAdjX = 5 ;
	iAdjY = 8 ;

	switch (m_stDialogBoxInfo[40].cMode) {
	// Slates Dialog - Diuuude
	case 1:
		sX = m_stDialogBoxInfo[40].sX;
		sY = m_stDialogBoxInfo[40].sY;
		iAdjX = -1;
		iAdjY = -7;

		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX, sY, 4);

		if (m_stDialogBoxInfo[40].sV1 != -1){
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX+20, sY+12, 5);
		}
		if (m_stDialogBoxInfo[40].sV2 != -1){
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX+20, sY+87, 6);
		}
		if (m_stDialogBoxInfo[40].sV3 != -1){
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX+85, sY+32, 7);
		}
		if (m_stDialogBoxInfo[40].sV4 != -1){
			DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX+70, sY+97, 8);
		}

		if ((m_stDialogBoxInfo[40].sV1 != -1) && (m_stDialogBoxInfo[40].sV2 != -1) && (m_stDialogBoxInfo[40].sV3 != -1) && (m_stDialogBoxInfo[40].sV4 != -1)){
			if ((msX >= sX + 120) && (msX <= sX + 180) && (msY >= sY + 150) && (msY <= sY + 165))
				PutString_SprFont(sX + 120, sY + 150, "Casting", 6,6,20);
			else PutString_SprFont(sX + 120, sY + 150, "Casting", 0, 0, 7);
		}

		break;

	// Slates Dialog - Diuuude
	case 2:
		PlaySound('E', 16, 0);
		if (m_stDialogBoxInfo[40].cStr[0] != 0)
		{	sX = m_stDialogBoxInfo[40].sX + iAdjX + (m_stDialogBoxInfo[40].cStr[0] - (rand() % (m_stDialogBoxInfo[40].cStr[0]*2)));
			sY = m_stDialogBoxInfo[40].sY + iAdjY + (m_stDialogBoxInfo[40].cStr[0] - (rand() % (m_stDialogBoxInfo[40].cStr[0]*2)));
		}else
		{	sX = m_stDialogBoxInfo[40].sX;
			sY = m_stDialogBoxInfo[40].sY;
		}
		m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY]->PutSpriteFast(sX, sY, 4, dwTime);
		m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY]->PutSpriteFast(sX+22, sY+14, 3, dwTime);
		//PutString_SprFont(sX + iAdjX + 170, sY + iAdjY + 170, "KURURURURURURURURU!!!", 20,6,6);
		PutAlignedString(199, 438, 201, "KURURURURURURURURU!!!", 220,140,160);
		PutAlignedString(200, 439, 200, "KURURURURURURURURU!!!", 90,220,200);

		if ((dwTime - m_stDialogBoxInfo[40].dwT1) > 1000)
		{	m_stDialogBoxInfo[40].dwT1 = dwTime;
			m_stDialogBoxInfo[40].cStr[0]++;
		}
		if (m_stDialogBoxInfo[40].cStr[0] >= 5)
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_CREATESLATE, NULL, m_stDialogBoxInfo[40].sV1, m_stDialogBoxInfo[40].sV2, m_stDialogBoxInfo[40].sV3, NULL, m_stDialogBoxInfo[40].sV4);
			DisableDialogBox(40);
		}
		break;
	}
}

void CGame::DlgBoxClick_Slates(short msX, short msY)
{
 int iAdjX, iAdjY;
 short sX, sY;

	sX = m_stDialogBoxInfo[40].sX;
	sY = m_stDialogBoxInfo[40].sY;
	iAdjX = 5 ;
	iAdjY = 8 ;
	switch (m_stDialogBoxInfo[40].cMode) {
	// Slates DialogBox - Diuuude
	case 1:
		if ((m_stDialogBoxInfo[40].sV1 != -1) && (m_stDialogBoxInfo[40].sV2 != -1) && (m_stDialogBoxInfo[40].sV3 != -1) && (m_stDialogBoxInfo[40].sV4 != -1)){
			if ((msX >= sX + 120) && (msX <= sX + 180) && (msY >= sY + 150) && (msY <= sY + 165)){
				m_stDialogBoxInfo[40].cMode = 2;
				PlaySound('E', 14, 5);
			}
		}
		break;
	}
}

void CGame::DlgBoxClick_NpcTalk(int msX, int msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[21].sX;
	sY = m_stDialogBoxInfo[21].sY;

	switch (m_stDialogBoxInfo[21].cMode) {
	case 0: //  OK
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			DisableDialogBox(21);
			PlaySound('E', 14, 5);
		}
		break;

	case 1: // Accept / Decline
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Accept
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_QUESTACCEPTED, NULL, NULL, NULL, NULL, NULL);
			DisableDialogBox(21);
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Cancel
			DisableDialogBox(21);
			PlaySound('E', 14, 5);
		}
		break;

	case 2:	// Next
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			DisableDialogBox(21);
			PlaySound('E', 14, 5);
		}
		break;
	}
}


void CGame::DrawDialogBox_Chat(short msX, short msY, short msZ, char cLB)
{short sX, sY;
 int i, iPointerLoc;
 double d1, d2, d3;
	sX = m_stDialogBoxInfo[10].sX;
	sY = m_stDialogBoxInfo[10].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 4, FALSE, m_bDialogTrans);
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 22, FALSE, m_bDialogTrans);

	if ( msZ != 0 && (iGetTopDialogBoxIndex() == 10)) {
		m_stDialogBoxInfo[10].sView = m_stDialogBoxInfo[10].sView + msZ/30;
		m_DInput.m_sZ = 0;
	}
	if( m_stDialogBoxInfo[10].sView < 0 ) m_stDialogBoxInfo[10].sView = 0;
	if( m_stDialogBoxInfo[10].sView > DEF_MAXCHATSCROLLMSGS-8 ) m_stDialogBoxInfo[10].sView = DEF_MAXCHATSCROLLMSGS-8;

	d1 = (double)m_stDialogBoxInfo[10].sView;
	d2 = (double)(105);
	d3 = (d1*d2)/(DEF_MAXCHATSCROLLMSGS-8);
	iPointerLoc = (int)d3;
	iPointerLoc = 105 - iPointerLoc;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX +346, sY + 33 + iPointerLoc, 7);

	for (i = 0; i < 8; i++)
	if (m_pChatScrollList[i + m_stDialogBoxInfo[10].sView] != NULL) {
		switch ( m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_dwTime ) {
		case 0:  PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 230, 230, 230); break;
		case 1:  PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 130, 200, 130); break;
		case 2:  PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 255, 130, 130); break;
		case 3:  PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 130, 130, 255); break;
		case 4:  PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 230, 230, 130); break;
		case 10: PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 180, 255, 180); break;
		case 20: PutString2(sX + 25, sY + 127 - i*13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 150, 150, 170); break;
		}
	}

	if ( (cLB != 0) && (iGetTopDialogBoxIndex()==10) )
	{ 	if ((msX >= sX + 336) && (msX <= sX + 361) && (msY >= sY + 28) && (msY <= sY + 140)) {
			d1 = (double)(msY - (sY + 28));
			d2 = ((DEF_MAXCHATSCROLLMSGS-8)*d1)/105.0f;
			m_stDialogBoxInfo[10].sView = DEF_MAXCHATSCROLLMSGS - 8 - (int)d2;
		}

		if ((msX >= sX + 336) && (msX <= sX + 361) && (msY > sY + 18) && (msY < sY + 28))
			m_stDialogBoxInfo[10].sView = DEF_MAXCHATSCROLLMSGS - 8;

		if ((msX >= sX + 336) && (msX <= sX + 361) && (msY > sY + 140) && (msY < sY + 163))
			m_stDialogBoxInfo[10].sView = 0;
	}
	else m_stDialogBoxInfo[10].bIsScrollSelected = FALSE;
}


void CGame::DlgBoxClick_ItemUpgrade(int msX, int msY)
{short sX, sY;
 int i, iSoX, iSoM;
	sX = m_stDialogBoxInfo[34].sX;
	sY = m_stDialogBoxInfo[34].sY;
	switch (m_stDialogBoxInfo[34].cMode) {
	case 1:	// Upgrade Majestic, items in the window
		if ((m_stDialogBoxInfo[34].sV1 != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	int iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
			iValue = iValue*(iValue+6)/8 + 2;
			if( m_iGizonItemUpgradeLeft < iValue ) break;
			PlaySound('E', 14, 5);
			PlaySound('E', 44, 0);
			m_stDialogBoxInfo[34].cMode = 2;
			m_stDialogBoxInfo[34].dwV1 = timeGetTime();
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			PlaySound('E', 14, 5);
			DisableDialogBox(34);
		}
		break;

	case 3: // sucess
	case 4: // Not possible
	case 7: // Lost item
	case 8: // Failed
	case 9: // Failed
	case 10:// Failed
	case 12:// 12 Need stone!
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// OK
			PlaySound('E', 14, 5);
			DisableDialogBox(34);
		}
		break;
	case 5: // main menu
		if ((msX > sX +24) && (msX < sX +248) && (msY > sY +100) && (msY < sY +115))
		{	PlaySound('E', 14, 5);
			iSoX = iSoM = 0;
			for (i = 0; i < DEF_MAXITEMS; i++)
			if (m_pItemList[i] != NULL)
			{	if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 128)) iSoX++;
				if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 129)) iSoM++;
			}
			if ((iSoX > 0) || (iSoM > 0))
			{	m_stDialogBoxInfo[34].cMode = 6;
				m_stDialogBoxInfo[34].sV2 = iSoX;
				m_stDialogBoxInfo[34].sV3 = iSoM;
			}
			else AddEventList(DRAW_DIALOGBOX_ITEMUPGRADE30, 10); //"Stone of Xelima or Merien is not present."
		}
		if ((msX > sX +24) && (msX < sX +248) && (msY > sY +120) && (msY < sY +135))
		{	m_stDialogBoxInfo[34].cMode = 1;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			PlaySound('E', 14, 5);
			DisableDialogBox(34);
		}
		break;

	case 6: // Upgrade Xelima / Merien
		if ((m_stDialogBoxInfo[34].sV1 != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Upgrade
			PlaySound('E', 14, 5);
			PlaySound('E', 44, 0);
			m_stDialogBoxInfo[34].cMode = 2;
			m_stDialogBoxInfo[34].dwV1 = timeGetTime();
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Cancel
			PlaySound('E', 14, 5);
			DisableDialogBox(34);
		}
		break;
	}
}


void CGame::DlgBoxClick_SellList(short msX, short msY)
{int i, x;
 short sX, sY;
 	sX = m_stDialogBoxInfo[31].sX;
	sY = m_stDialogBoxInfo[31].sY;
	for (i = 0; i < DEF_MAXSELLLIST; i++)
	if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i*15) && (msY <= sY + 55 + 14 + i*15))
	{	if (m_pItemList[m_stSellItemList[i].iIndex] != NULL)
		{	m_bIsItemDisabled[m_stSellItemList[i].iIndex] = FALSE;
			m_stSellItemList[i].iIndex = -1;

			PlaySound('E', 14, 5);

			// ÀçÁ¤·Ä
			for (x = 0; x < DEF_MAXSELLLIST-1; x++)
			if (m_stSellItemList[x].iIndex == -1) {
				m_stSellItemList[x].iIndex  = m_stSellItemList[x+1].iIndex;
				m_stSellItemList[x].iAmount = m_stSellItemList[x+1].iAmount;

				m_stSellItemList[x+1].iIndex  = -1;
				m_stSellItemList[x+1].iAmount = 0;
			}
		}
		return;
	}

	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		// Sell
		bSendCommand(MSGID_REQUEST_SELLITEMLIST, NULL, NULL, NULL, NULL, NULL, NULL);
		PlaySound('E', 14, 5);
		DisableDialogBox(31);
	}

	if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		// Cancel
		PlaySound('E', 14, 5);
		DisableDialogBox(31);
	}
}

// 3.51 LevelUp Box - Diuuude
void CGame::DlgBoxClick_LevelUpSettings(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[12].sX;
	sY = m_stDialogBoxInfo[12].sY;
	// Strength UP - Diuuude
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_iStr <= 200) && (m_iLU_Point > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_iLU_Point >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point -= 5;
				m_cLU_Str += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_iLU_Point > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point--;
				m_cLU_Str++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Vitality UP - Diuuude
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_iVit <= 200) && (m_iLU_Point > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_iLU_Point >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point -= 5;
				m_cLU_Vit += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_iLU_Point > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point--;
				m_cLU_Vit++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Dexterity UP - Diuuude
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_iDex <= 200) && (m_iLU_Point > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_iLU_Point >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point -= 5;
				m_cLU_Dex += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_iLU_Point > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point--;
				m_cLU_Dex++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Intelligence UP - Diuuude
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_iInt <= 200) && (m_iLU_Point > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_iLU_Point >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point -= 5;
				m_cLU_Int += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_iLU_Point > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point--;
				m_cLU_Int++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Magic UP - Diuuude
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_iMag <= 200) && (m_iLU_Point > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_iLU_Point >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point -= 5;
				m_cLU_Mag += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_iLU_Point > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point--;
				m_cLU_Mag++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Charisma UP - Diuuude
	if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_iCharisma <= 200) && (m_iLU_Point > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_iLU_Point >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point -= 5;
				m_cLU_Char += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_iLU_Point > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_iLU_Point--;
				m_cLU_Char++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Strength DOWN - Diuuude
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_cLU_Str > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_cLU_Str >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Str -= 5;
				m_iLU_Point += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_cLU_Str > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Str--;
				m_iLU_Point++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Vitality DOWN - Diuuude
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_cLU_Vit > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_cLU_Vit >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Vit -= 5;
				m_iLU_Point += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_cLU_Vit > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Vit--;
				m_iLU_Point++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Dexterity DOWN - Diuuude
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_cLU_Dex > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_cLU_Dex >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Dex -= 5;
				m_iLU_Point += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_cLU_Dex > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Dex--;
				m_iLU_Point++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Intelligence DOWN - Diuuude
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_cLU_Int > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_cLU_Int >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Int -= 5;
				m_iLU_Point += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_cLU_Int > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Int--;
				m_iLU_Point++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Magic DOWN - Diuuude
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_cLU_Mag > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_cLU_Mag >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Mag -= 5;
				m_iLU_Point += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_cLU_Mag > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Mag--;
				m_iLU_Point++;
			}
			PlaySound('E', 14, 5);
	}	}

	// Charisma DOWN - Diuuude
	if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_cLU_Char > 0))
	{	if (m_bCtrlPressed == TRUE)
		{	if ((m_cLU_Char >= 5)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Char -= 5;
				m_iLU_Point += 5;
			}
			PlaySound('E', 14, 5);
		}else
		{	if ((m_cLU_Char > 0)&&(m_bIsDialogEnabled[42] == FALSE))
			{	m_cLU_Char--;
				m_iLU_Point++;
			}
			PlaySound('E', 14, 5);
	}	}

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
	{	if (m_stDialogBoxInfo[12].sV1 != m_iLU_Point)
		// Send command to HG - Diuuude, Only if changed - Snoopy
		bSendCommand(MSGID_LEVELUPSETTINGS, NULL, NULL, NULL, NULL, NULL, NULL);
		//m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
		DisableDialogBox(12);
		PlaySound('E', 14, 5);
	}
	if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
	{	// Change stats with Majestic
		if (   (m_iGizonItemUpgradeLeft >0) && (m_iLU_Point <= 0)
			&& (m_cLU_Str == 0)&&(m_cLU_Vit == 0)&&(m_cLU_Dex == 0)&&(m_cLU_Int == 0)&&(m_cLU_Mag == 0)&&(m_cLU_Char == 0))
		{	DisableDialogBox(12);
			EnableDialogBox(42, 0, 0, 0);
			//PlaySound('E', 14, 5);
	}	}
}

void CGame::CannotConstruct(int iCode)
{
	switch (iCode) {
	case 1: //
		SetTopMsg(m_pGameMsgList[18]->m_pMsg, 5);
		break;

	case 2: //
		wsprintf(G_cTxt, "%s XY(%d, %d)", m_pGameMsgList[19]->m_pMsg, m_iConstructLocX, m_iConstructLocY);
		SetTopMsg(G_cTxt, 5);
		break;

	case 3: //
		SetTopMsg(m_pGameMsgList[20]->m_pMsg, 5);
		break;
	case 4: //
		SetTopMsg(m_pGameMsgList[20]->m_pMsg, 5);
		break;

	}
}

void CGame::DisplayCommaNumber_G_cTxt(int iGold)
{
 char cGold[20];

	ZeroMemory(cGold, sizeof(cGold));
	ZeroMemory(G_cTxt, sizeof(G_cTxt));
	_itoa(iGold, cGold, 10);
#ifdef DEF_COMMA_GOLD
	iStrLen = strlen(cGold);
	iStrLen--;
	int cnt = 0;
	for (int i = 0 ; i < iStrLen+1 ; i++)
	{	if( (cnt != 0) && ((cnt+1)%4 == 0) )
		{	G_cTxt[cnt] = ',';
			i--;
		}else G_cTxt[cnt] = cGold[iStrLen-i];
		cnt++;
	}
	iStrLen = strlen(G_cTxt);
	G_cTxt[iStrLen] = '\0';
	strrev(G_cTxt);
#else
	strcpy(G_cTxt, cGold);
#endif
}

void CGame::DrawDialogBox_Inventory(int msX, int msY)
{int i;
 short sX, sY;
 DWORD dwTime = m_dwCurTime;
 char cItemColor;
	sX = m_stDialogBoxInfo[2].sX;
	sY = m_stDialogBoxInfo[2].sY;
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX, sY, 0);
	for (i = 0; i < DEF_MAXITEMS; i++)
	if ((m_cItemOrder[i] != -1) && (m_pItemList[m_cItemOrder[i]] != NULL))
	{	if (   ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM)
			&& (m_stMCursor.sSelectedObjectID   ==	m_cItemOrder[i])) || (m_bIsItemEquipped[m_cItemOrder[i]] == TRUE) )
		{}else
		{	cItemColor = m_pItemList[m_cItemOrder[i]]->m_cItemColor;
			if (m_bIsItemDisabled[ m_cItemOrder[i] ] == TRUE)
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutTransSprite2(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
					 	                                                sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame, dwTime);
				else
				{	if (   (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
						|| (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
						|| (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
					{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutTransSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
																			sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
																			m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0],
																			dwTime);
					}else
					{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutTransSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
																			sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
																			m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0],
																			dwTime);
				}	}
			}else
			{	if (cItemColor == 0)
					 m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutSpriteFast(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
																		sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame, dwTime);
				else
				{	if (   (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
						|| (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
						|| (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
					{	m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
																			sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
																			m_wWR[cItemColor] -m_wR[0], m_wWG[cItemColor] -m_wG[0], m_wWB[cItemColor] -m_wB[0],
																			dwTime);
					}else {
						m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
																			sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
																			m_wR[cItemColor] -m_wR[0], m_wG[cItemColor] -m_wG[0], m_wB[cItemColor] -m_wB[0],
																			dwTime);
			}	}	}
			if (   (m_pItemList[m_cItemOrder[i]]->m_cItemType == DEF_ITEMTYPE_CONSUME)
				|| (m_pItemList[m_cItemOrder[i]]->m_cItemType == DEF_ITEMTYPE_ARROW) )
			{	DisplayCommaNumber_G_cTxt((int)m_pItemList[m_cItemOrder[i]]->m_dwCount); // nbe show, as US: 1,200,000
				PutString2(sX + 29 + m_pItemList[m_cItemOrder[i]]->m_sX +10, sY + 41 + m_pItemList[m_cItemOrder[i]]->m_sY +10
					, G_cTxt, 200,200,200);
	}	}	}
	if ((msX >= sX +23) && (msX <= sX +76) && (msY >= sY +172) && (msY <= sY +184))
	{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX+23, sY+172, 1);
	}
	if ((msX >= sX +140) && (msX <= sX +212) && (msY >= sY +172) && (msY <= sY +184))
	{	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX+140, sY+172, 2);
	}
}


void CGame::CrusadeContributionResult(int iWarContribution)
{int i;
 char cTemp[120];
	DisableDialogBox(18);
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{	if (m_pMsgTextList[i] != NULL)
			delete m_pMsgTextList[i];
		m_pMsgTextList[i] = NULL;
	}
	if (iWarContribution > 0)
	{	PlaySound('E', 23, 0, 0);
		PlaySound('C', 21, 0, 0);
		PlaySound('C', 22, 0, 0);
		m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[22]->m_pMsg, NULL); // Congratulations! Your nation
		m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[23]->m_pMsg, NULL); // was victory in the battle!
		m_pMsgTextList[2] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[3] = new class CMsg(NULL, m_pGameMsgList[24]->m_pMsg, NULL); // As a victorious citizen
		m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[25]->m_pMsg, NULL); // You will receive
		m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[26]->m_pMsg, NULL); // a prize
		m_pMsgTextList[6] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[27]->m_pMsg, NULL); // Experience point of the battle contribution:
		ZeroMemory(cTemp, sizeof(cTemp));											//
		wsprintf(cTemp, "+%dExp Points!", iWarContribution);
		m_pMsgTextList[8] = new class CMsg(NULL, cTemp, NULL);
		for (i = 9; i < 18; i++)
		m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);

	}else if (iWarContribution < 0)
	{	PlaySound('E', 24, 0, 0);
		PlaySound('C', 12, 0, 0);
		PlaySound('C', 13, 0, 0);
		m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[28]->m_pMsg, NULL); // Unfortunately! Your country
		m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[29]->m_pMsg, NULL); // have lost the all out war.
		m_pMsgTextList[2] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[3] = new class CMsg(NULL, m_pGameMsgList[30]->m_pMsg, NULL); // As a losser citizen;
		m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[31]->m_pMsg, NULL); // the prize that accomplishes
		m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[32]->m_pMsg, NULL); // will not be given.
		m_pMsgTextList[6] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[33]->m_pMsg, NULL); // I hope you to win
		m_pMsgTextList[8] = new class CMsg(NULL, m_pGameMsgList[34]->m_pMsg, NULL); // in the next battle
		for (i = 9; i < 18; i++)
		m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
	}else if (iWarContribution == 0)
	{	PlaySound('E', 25, 0, 0);
		m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[50]->m_pMsg, NULL); // The battle that you have participated
		m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[51]->m_pMsg, NULL); // is already finished;
		m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[52]->m_pMsg, NULL); //
		m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
		m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[53]->m_pMsg, NULL); // You must connect after finishing
		m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[54]->m_pMsg, NULL); // the previous and before starting
		m_pMsgTextList[6] = new class CMsg(NULL, m_pGameMsgList[55]->m_pMsg, NULL); // the next battle so you can receive
		m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[56]->m_pMsg, NULL); // the prize
		for (i = 8; i < 18; i++)
		m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
	}
	EnableDialogBox(18, NULL, NULL, NULL);
}


void CGame::CrusadeWarResult(int iWinnerSide)
{int i, iPlayerSide;
	DisableDialogBox(18);
	for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
	{	if (m_pMsgTextList[i] != NULL)
			delete m_pMsgTextList[i];
		m_pMsgTextList[i] = NULL;
	}
	if( m_bCitizen == FALSE ) iPlayerSide = 0;
	else if (m_bAresden == TRUE) iPlayerSide = 1;
	else if (m_bAresden == FALSE) iPlayerSide = 2;
	if (iPlayerSide == 0)
	{	switch (iWinnerSide) {
		case 0:
			PlaySound('E', 25, 0, 0);
			m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
			m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[36]->m_pMsg, NULL); // There was a draw in the
			m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[37]->m_pMsg, NULL); // battle
			m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
			break;
		case 1:
			PlaySound('E', 25, 0, 0);
			m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
			m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[38]->m_pMsg, NULL); // Aresden was victorious
			m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[39]->m_pMsg, NULL); // and put an end to the war
			m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
			break;
		case 2:
			PlaySound('E', 25, 0, 0);
			m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
			m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[40]->m_pMsg, NULL); // Elvine was victorious
			m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[41]->m_pMsg, NULL); // and put an end to the war
			m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
			break;
		}
		for (i = 4; i < 18; i++)
			m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
	}else
	{	if (iWinnerSide == 0)
		{	PlaySound('E', 25, 0, 0);
			m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
			m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[36]->m_pMsg, NULL); // There was a draw in the
			m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[37]->m_pMsg, NULL); // battle
			m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
			for (i = 4; i < 18; i++)
				m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
		}else
		{ 	if (iWinnerSide == iPlayerSide)
			{	PlaySound('E', 23, 0, 0);
				PlaySound('C', 21, 0, 0);
				PlaySound('C', 22, 0, 0);
				switch (iWinnerSide) {
				case 1:
					m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!;
					m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[38]->m_pMsg, NULL); // Aresden was victorious;
					m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[39]->m_pMsg, NULL); // and put an end to the war
					m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
					m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[42]->m_pMsg, NULL); // Congratulations!
					m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[43]->m_pMsg, NULL); // As a victorious citizen
					m_pMsgTextList[6] = new class CMsg(NULL, m_pGameMsgList[44]->m_pMsg, NULL); // You will receive
					m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[45]->m_pMsg, NULL); // a prize
					break;
				case 2:
					m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
					m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[40]->m_pMsg, NULL); // Elvine was victorious
					m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[41]->m_pMsg, NULL); // and put an end to the war
					m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
					m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[42]->m_pMsg, NULL); // Congratulations!
					m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[43]->m_pMsg, NULL); // As a victorious citizen
					m_pMsgTextList[6] = new class CMsg(NULL, m_pGameMsgList[44]->m_pMsg, NULL); // You will receive
					m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[45]->m_pMsg, NULL); // a prize
					break;
				}
				for (i = 8; i < 18; i++)
					m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
			}else if (iWinnerSide != iPlayerSide)
			{	PlaySound('E', 24, 0, 0);
				PlaySound('C', 12, 0, 0);
				PlaySound('C', 13, 0, 0);
				switch (iWinnerSide) {
				case 1:
					m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
					m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[38]->m_pMsg, NULL); // Aresden was victorious;
					m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[39]->m_pMsg, NULL); // and put an end to the war
					m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
					m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[46]->m_pMsg, NULL); // Unfortunately,
					m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[47]->m_pMsg, NULL); // As a losser citizen
					m_pMsgTextList[6] = new class CMsg(NULL, m_pGameMsgList[48]->m_pMsg, NULL); // the prize that accomplishes
					m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[49]->m_pMsg, NULL); // will not be given.
					break;
				case 2:
					m_pMsgTextList[0] = new class CMsg(NULL, m_pGameMsgList[35]->m_pMsg, NULL); // All out war finished!
					m_pMsgTextList[1] = new class CMsg(NULL, m_pGameMsgList[40]->m_pMsg, NULL); // Elvine was victorious
					m_pMsgTextList[2] = new class CMsg(NULL, m_pGameMsgList[41]->m_pMsg, NULL); // and put an end to the war
					m_pMsgTextList[3] = new class CMsg(NULL, " ", NULL);
					m_pMsgTextList[4] = new class CMsg(NULL, m_pGameMsgList[46]->m_pMsg, NULL); // Unfortunately,
					m_pMsgTextList[5] = new class CMsg(NULL, m_pGameMsgList[47]->m_pMsg, NULL); // As a losser citizen
					m_pMsgTextList[6] = new class CMsg(NULL, m_pGameMsgList[48]->m_pMsg, NULL); // the prize that accomplishes
					m_pMsgTextList[7] = new class CMsg(NULL, m_pGameMsgList[49]->m_pMsg, NULL); // will not be given.
					break;
				}
				for (i = 8; i < 18; i++)
					m_pMsgTextList[i] = new class CMsg(NULL, " ", NULL);
	}	}	}
	EnableDialogBox(18, NULL, NULL, NULL);
	DisableDialogBox(36);
	DisableDialogBox(37);
	DisableDialogBox(38);
}

void CGame::_Draw_UpdateScreen_OnCreateNewAccount()
{
	m_DDraw.ClearBackB4();
	DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWACCOUNT, 0,0,0, TRUE);
	PutString2(329, 110, m_cAccountName, 200,200,200);
	PutString( 329, 125, m_cAccountPassword, RGB(200,200,200), TRUE, 1);
	PutString( 329, 140, m_cAccountPassword, RGB(200,200,200), TRUE, 1);
	PutString2(300, 202, m_cAccountCountry, 200,200,200);
	PutString2(300, 218, m_cAccountSSN, 200,200,200);
	PutString2(194, 257, m_cEmailAddr, 200,200,200);
}

void CGame::DrawChatMsgBox(short sX, short sY, int iChatIndex, BOOL bIsPreDC)
{
 char cMsg[100], cMsgA[22], cMsgB[22], cMsgC[22], * cp;
 int  iRet, iLines, i, iSize, iSize2, iLoc, iFontSize;
 DWORD dwTime;
 COLORREF rgb;
 BOOL bIsTrans;
 RECT rcRect;
 SIZE Size;

	ZeroMemory(cMsg, sizeof(cMsg));
	ZeroMemory(cMsgA, sizeof(cMsgA));
	ZeroMemory(cMsgB, sizeof(cMsgB));
	ZeroMemory(cMsgC, sizeof(cMsgC));

	dwTime = m_pChatMsgList[iChatIndex]->m_dwTime;
	strcpy(cMsg, m_pChatMsgList[iChatIndex]->m_pMsg);
	cp = (char *)cMsg;
	iLines = 0;

	rgb = RGB(255,255,255);
	switch (m_pChatMsgList[iChatIndex]->m_cType) {
	case 1:
		rgb = RGB(255,255,255);
		break;
	case 20:
		rgb = RGB(255,255,20);
		// ¸Þ½ÃÁö Ç¥½Ã¿¡ µô·¹ÀÌ°¡ °É¸°´Ù.
		if ((m_dwCurTime - dwTime) < 650) return;
		else dwTime += 650;
		break;
	case 41:
		rgb = RGB(255,80,80);
		break;

	case 42:
		rgb = RGB(255,80,80);
		if ((m_dwCurTime - dwTime) < 650) return;
		else dwTime += 650;
		break;
	}

	if (strlen(cp) != 0) {
		memcpy(cMsgA, cp, 20);

		iRet = GetCharKind(cMsgA, 19);
		if (iRet == CODE_HAN1) {
			cMsgA[20] = cp[20];
			cp++;
		}
		cp += 20;
		iLines = 1;
	}

	if (strlen(cp) != 0) {
		memcpy(cMsgB, cp, 20);

		iRet = GetCharKind(cMsgB, 19);
		if (iRet == CODE_HAN1) {
			cMsgB[20] = cp[20];
			cp++;
		}
		cp += 20;
		iLines = 2;
	}

	if (strlen(cp) != 0) {
		memcpy(cMsgC, cp, 20);

		iRet = GetCharKind(cMsgC, 19);
		if (iRet == CODE_HAN1) {
			cMsgC[20] = cp[20];
			cp++;
		}
		cp += 20;
		iLines = 3;
	}

	iSize = 0;
	for (i = 0; i < 20; i++)
	if (cMsgA[i] != 0)

	if ((unsigned char)cMsgA[i] >= 128) {
		iSize += 5;	//6
		i++;
	}
	else iSize += 4;

	iLoc = m_dwCurTime - dwTime;
	switch (m_pChatMsgList[iChatIndex]->m_cType) {
	case 21:
	case 22:
	case 23://...
		if( iLoc > 80 ) iLoc = 10;
		else iLoc = iLoc>>3;
		break;
	default://
		if( iLoc > 352 ) iLoc = 9;
		else if( iLoc > 320 ) iLoc = 10;
		else iLoc = iLoc>>5;
		break;
	}

	if (m_cDetailLevel == 0)
		 bIsTrans = FALSE;
	else bIsTrans = TRUE;

	switch (m_pChatMsgList[iChatIndex]->m_cType) {
	case 41:
	case 42:
		iSize2 = 0;
		for (i = 0; i < 100; i++)
		if (cMsg[i] != 0)
		if ((unsigned char)cMsg[i] >= 128) {
			iSize2 += 5;
			i++;
		}
		else iSize2 += 4;
		if( m_Misc.bCheckIMEString(cMsg) == FALSE )
		{
			PutString(sX - iSize2, sY - 65 - iLoc, cMsg, RGB(180, 30, 30));
			PutString(sX - iSize2+1, sY - 65 - iLoc, cMsg, RGB(180, 30, 30));
		}
		else PutString_SprFont3(sX - iSize2, sY - 65 - iLoc, cMsg, m_wR[14]*4, m_wG[14]*4, m_wB[14]*4, FALSE, 0);
		break;

	case 21:
	case 22:
	case 23:
		iFontSize = 23 - (int)m_pChatMsgList[iChatIndex]->m_cType;
		switch (iLines) {
		case 1:
			PutString_SprFont3(sX - iSize, sY - 65 - iLoc, cMsgA, m_wR[13]*2, m_wG[13]*2, m_wB[13]*2, bIsTrans, iFontSize);
			break;
		case 2:
			PutString_SprFont3(sX - iSize, sY - 81 - iLoc,  cMsgA, m_wR[13]*2, m_wG[13]*2, m_wB[13]*2, bIsTrans, iFontSize);
			PutString_SprFont3(sX - iSize, sY - 65 - iLoc,  cMsgB, m_wR[13]*2, m_wG[13]*2, m_wB[13]*2, bIsTrans, iFontSize);
			break;
		case 3:
			PutString_SprFont3(sX - iSize, sY - 97 - iLoc, cMsgA, m_wR[13]*2, m_wG[13]*2, m_wB[13]*2, bIsTrans, iFontSize);
			PutString_SprFont3(sX - iSize, sY - 81 - iLoc, cMsgB, m_wR[13]*2, m_wG[13]*2, m_wB[13]*2, bIsTrans, iFontSize);
			PutString_SprFont3(sX - iSize, sY - 65 - iLoc, cMsgC, m_wR[13]*2, m_wG[13]*2, m_wB[13]*2, bIsTrans, iFontSize);
			break;
		}
		break;

	case 20:
	default:
		if (bIsPreDC == FALSE)
			m_DDraw._GetBackBufferDC();

		GetTextExtentPoint32(m_DDraw.m_hDC, cMsg, strlen(cMsg), &Size);

		switch (Size.cx / 160) {
		case 0:
			SetRect(&rcRect, sX-80 +1, sY-65 -iLoc, sX+80 +1, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-65 -iLoc +1, sX+80, sY -iLoc +1);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-65 -iLoc, sX+80, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, rgb);
			break;

		case 1:
			SetRect(&rcRect, sX-80 +1, sY-83 -iLoc, sX+80 +1, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-83 -iLoc +1, sX+80, sY -iLoc +1);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-83 -iLoc, sX+80, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, rgb);
			break;

		case 2:
			SetRect(&rcRect, sX-80 +1, sY-101 -iLoc, sX+80 +1, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-101 -iLoc +1, sX+80, sY -iLoc +1);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-101 -iLoc, sX+80, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, rgb);
			break;

		case 3:
			SetRect(&rcRect, sX-80 +1, sY-119 -iLoc, sX+80 +1, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-119 -iLoc +1, sX+80, sY -iLoc +1);
			m_DDraw.DrawText(&rcRect, cMsg, RGB(0,0,0));

			SetRect(&rcRect, sX-80, sY-119 -iLoc, sX+80, sY -iLoc);
			m_DDraw.DrawText(&rcRect, cMsg, rgb);
			break;
		}

		if (bIsPreDC == FALSE)
			m_DDraw._ReleaseBackBufferDC();
		break;
	}
}

void CGame::ClearContents_OnSelectCharacter()
{
	m_cCurFocus = 1;
}



void CGame::UpdateScreen_OnSelectCharacter()
{
 short sX, sY, msX, msY, msZ;
 char  cLB, cRB, cTotalChar;
 char  cMIresult;
 static class CMouseInterface * pMI;
 DWORD dwTime;
 static DWORD dwCTime;

 int iMIbuttonNum;

	dwTime = timeGetTime();
	sX = 0;
	sY = 0;
	cTotalChar = 0;

	if (m_cGameModeCount == 0)
	{	G_cSpriteAlphaDegree = 1;
		InitGameSettings();
		pMI = new class CMouseInterface;
		pMI->AddRect(100, 50, 210, 250);
		pMI->AddRect(211, 50, 321, 250);
		pMI->AddRect(322, 50, 431, 250);
		pMI->AddRect(432, 50, 542, 250);

		pMI->AddRect(360,283,545,315);
		pMI->AddRect(360,316,545,345);
		pMI->AddRect(360,346,545,375);
		pMI->AddRect(360,376,545,405);
		pMI->AddRect(360,406,545,435);

		m_cMaxFocus = 4;
		if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
		if (m_cCurFocus < 1)		   m_cCurFocus = 1;

		m_cArrowPressed = 0;
		m_bEnterPressed = FALSE;

		dwCTime = timeGetTime();
	}

	m_cGameModeCount++;
	if (m_cGameModeCount > 100) m_cGameModeCount = 100;

	if (m_cArrowPressed != 0)
	{	switch (m_cArrowPressed) {
		case 2:
			m_cCurFocus++;
			if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
			break;
		case 4:
			m_cCurFocus--;
			if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
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

	if (m_bEnterPressed == TRUE)
	{	m_bEnterPressed = FALSE;
		PlaySound('E', 14, 5);

		if (m_pCharList[m_cCurFocus-1] != NULL)
		{	if (m_pCharList[m_cCurFocus-1]->m_sSex != NULL)
			{	ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
				strcpy(m_cPlayerName, m_pCharList[m_cCurFocus-1]->m_cName);
				m_iLevel = (int)m_pCharList[m_cCurFocus-1]->m_sLevel;
				if (m_Misc.bCheckValidString(m_cPlayerName) == TRUE)
				{	m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->_iCloseSprite();
					m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->_iCloseSprite();
					m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
					m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort +(rand()%1), WM_USER_LOGSOCKETEVENT);
					m_pLSock->bInitBufferSize(30000);
					ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
					m_dwConnectMode  = MSGID_REQUEST_ENTERGAME;
					m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW;
					ZeroMemory(m_cMsg, sizeof(m_cMsg));
					strcpy(m_cMsg,"33");
					ZeroMemory(m_cMapName, sizeof(m_cMapName));
					memcpy(m_cMapName, m_pCharList[m_cCurFocus-1]->m_cMapName, 10);
					delete pMI;
					return;
			}	}
		}else
		{	_InitOnCreateNewCharacter();
			ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
			delete pMI;
			return;
		}
	}

	m_DInput.UpdateMouseState(&msX, &msY, &msZ, &cLB, &cRB);
	UpdateScreen_OnSelectCharacter(sX, sY, msX, msY);

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

	iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
	if (cMIresult == DEF_MIRESULT_CLICK) {
		PlaySound('E', 14, 5);

		switch (iMIbuttonNum) {
		case 1:
		case 2:
		case 3:
		case 4:
			if (m_cCurFocus != iMIbuttonNum)
				m_cCurFocus = iMIbuttonNum;
			else
			{	if (m_pCharList[m_cCurFocus-1] != NULL)
				{	if (m_pCharList[m_cCurFocus-1]->m_sSex != NULL)
					{	ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
						strcpy(m_cPlayerName, m_pCharList[m_cCurFocus-1]->m_cName);
						m_iLevel = (int)m_pCharList[m_cCurFocus-1]->m_sLevel;
						if (m_Misc.bCheckValidString(m_cPlayerName) == TRUE)
						{	m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->_iCloseSprite();
							m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->_iCloseSprite();
							m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
							m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort +(rand()%1), WM_USER_LOGSOCKETEVENT);
							m_pLSock->bInitBufferSize(30000);
							ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
							m_dwConnectMode  = MSGID_REQUEST_ENTERGAME;
							m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW;
							ZeroMemory(m_cMsg, sizeof(m_cMsg));
							strcpy(m_cMsg,"33");
							ZeroMemory(m_cMapName, sizeof(m_cMapName));
							memcpy(m_cMapName, m_pCharList[m_cCurFocus-1]->m_cMapName, 10);
							delete pMI;
							return;
					}	}
				}else
				{	_InitOnCreateNewCharacter();
					ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
					delete pMI;
					return;
				}
			}
			break;

		case 5:
			if (m_pCharList[m_cCurFocus - 1] != NULL)
			{	if (m_pCharList[m_cCurFocus-1]->m_sSex != NULL)
				{	ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
					strcpy(m_cPlayerName, m_pCharList[m_cCurFocus-1]->m_cName);
					m_iLevel = (int)m_pCharList[m_cCurFocus-1]->m_sLevel;

					if (m_Misc.bCheckValidString(m_cPlayerName) == TRUE) {
						m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->_iCloseSprite();
						m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->_iCloseSprite();
						m_pLSock = new class XSocket(m_hWnd, DEF_SOCKETBLOCKLIMIT);
						m_pLSock->bConnect(m_cLogServerAddr, m_iLogServerPort +(rand()%1), WM_USER_LOGSOCKETEVENT);
						m_pLSock->bInitBufferSize(30000);
						ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
						m_dwConnectMode  = MSGID_REQUEST_ENTERGAME;
						m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW;
						ZeroMemory(m_cMsg, sizeof(m_cMsg));
						strcpy(m_cMsg,"33");
						ZeroMemory(m_cMapName, sizeof(m_cMapName));
						memcpy(m_cMapName, m_pCharList[m_cCurFocus-1]->m_cMapName, 10);
						delete pMI;
						return;
			}	}	}
			break;

		case 6:
			if (m_iTotalChar < 4)
			{	_InitOnCreateNewCharacter();
				ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
				delete pMI;
				return;
			}
			break;

		case 7:
			if ((m_pCharList[m_cCurFocus - 1] != NULL) && (m_pCharList[m_cCurFocus - 1]->m_sLevel < 50))
			{	ChangeGameMode(DEF_GAMEMODE_ONQUERYDELETECHARACTER);
				m_wEnterGameType = m_cCurFocus;
				delete pMI;
				return;
			}
			break;

		case 8:
			ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD);
			delete pMI;
			return;

		case 9:
			ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
			delete pMI;
			return;
		}
	}

//	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
//	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);

	if (m_DDraw.iFlip() == DDERR_SURFACELOST) RestoreSprites();
}

BOOL CGame::bDlgBoxPress_Character(short msX, short msY)
{
	int i;
	short sX, sY, sSprH, sFrame;
	char cEquipPoiStatus[DEF_MAXITEMEQUIPPOS];

	if (m_bIsDialogEnabled[17] == TRUE) return FALSE;

	sX = m_stDialogBoxInfo[1].sX;
	sY = m_stDialogBoxInfo[1].sY;
	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) cEquipPoiStatus[i] = -1;
	for (i = 0; i < DEF_MAXITEMS; i++)
	{	if ((m_pItemList[i] != NULL) && (m_bIsItemEquipped[i] == TRUE))	cEquipPoiStatus[ m_pItemList[i]->m_cEquipPos ] = i;
	}

	if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
	{	if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 72, sY + 135, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_HEAD];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_RFINGER];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_LFINGER];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1) {
			sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY ) )
			{
				m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
			}
		}
		if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY ) )
			{
				m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 90, sY + 170, sFrame, msX, msY ) )
			{
				m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_FULLBODY];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_BODY];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_BOOTS];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_ARMS];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_PANTS];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
		{	sSprH      = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
			sFrame     = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison( sX + 41, sY + 137, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_BACK];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
	}else if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6))
	{	if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 72, sY + 139, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_HEAD];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_RFINGER];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_LFINGER];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 84, sY + 175, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_BODY];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_FULLBODY];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1))
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_BOOTS];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_ARMS];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_PANTS];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
		}	}
		if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
		{	sSprH  = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
			sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
			if( m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH +40]->_bCheckCollison(sX + 45, sY + 143, sFrame, msX, msY ) )
			{	m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = m_sItemEquipmentStatus[DEF_EQUIPPOS_BACK];
				m_stMCursor.sDistX = 0;
				m_stMCursor.sDistY = 0;
				return TRUE;
	}	}	}
	return FALSE;
}

void CGame::DlgBoxClick_CityhallMenu(short msX, short msY)
{short sX, sY;
	sX = m_stDialogBoxInfo[13].sX;
	sY = m_stDialogBoxInfo[13].sY;
	switch (m_stDialogBoxInfo[13].cMode) {
	case 0:
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
		{	if (m_bCitizen == TRUE) return;
			m_stDialogBoxInfo[13].cMode = 1; // citizenship rq
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
		{	if (m_iRewardGold <= 0) return;
			m_stDialogBoxInfo[13].cMode = 5; // rq reward gold
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
		{	if (m_iEnemyKillCount < 100) return;
			m_stDialogBoxInfo[13].cMode = 7;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
		{	if (m_stQuest.sQuestType == NULL) return;
			m_stDialogBoxInfo[13].cMode = 8;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
		{	if (m_bIsCrusadeMode) return;
			if (m_iPKCount != 0) return;
			if (m_bCitizen == FALSE) return;
			if ((m_iLevel > 100) && (m_bHunter==FALSE)) return;
			m_stDialogBoxInfo[13].cMode = 9;
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
		{	m_stDialogBoxInfo[13].cMode = 10;
			m_iTeleportMapCount = -1;
			bSendCommand(MSGID_REQUEST_TELEPORT_LIST, NULL, NULL, NULL, NULL, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 220) && (msY < sY + 245)) {
			if (m_bIsCrusadeMode == FALSE) return;
			EnableDialogBox(33, 1, NULL, NULL);
			PlaySound('E', 14, 5);
		}
		break;

	case 1:
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// Yes Click
			bSendCommand(MSGID_REQUEST_CIVILRIGHT, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL, NULL, NULL);
			m_stDialogBoxInfo[13].cMode = 2;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	// No Click
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 3:	//
	case 4:	// OK°
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// No Click
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 5:
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Yes
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETREWARDMONEY, NULL, NULL, NULL, NULL, NULL);
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);

		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// No
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	// 3.51 Cityhall Menu - Request Hero's Items - Diuuude - fix by Drajwer
	case 7:
 		int iReqHeroItemID;
 		// Hero's Cape
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 95) && (msY <= sY + 110))
 		{	if(m_bAresden == TRUE) iReqHeroItemID = 400;
  			else iReqHeroItemID = 401;
			ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
			memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU47,strlen(DRAW_DIALOGBOX_CITYHALL_MENU47));
  			m_stDialogBoxInfo[13].cMode = 11;
  			m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
  			PlaySound('E', 14, 5);
 		}
 		// Hero's Helm
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 125) && (msY <= sY + 140))
 		{	if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 403;
  			if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 404;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 405;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 406;
 	 		ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
 	 		memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU48,strlen(DRAW_DIALOGBOX_CITYHALL_MENU48));
 	 		m_stDialogBoxInfo[13].cMode = 11;
 	 		m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
 	 		PlaySound('E', 14, 5);
 		}
 		// Hero's Cap
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 155) && (msY <= sY + 170))
 		{	if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 407;
  			if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 408;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 409;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 410;
  			ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
  			memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU49,strlen(DRAW_DIALOGBOX_CITYHALL_MENU49));
  			m_stDialogBoxInfo[13].cMode = 11;
  			m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
  			PlaySound('E', 14, 5);
 		}
 		// Hero's Armor
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 185) && (msY <= sY + 200))
 		{  	if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 411;
  			if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 412;
 	 		if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 413;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 414;
  			ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
  			memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU50,strlen(DRAW_DIALOGBOX_CITYHALL_MENU50));
  			m_stDialogBoxInfo[13].cMode = 11;
  			m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
  			PlaySound('E', 14, 5);
 		}
 		// Hero's Robe
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 215) && (msY <= sY + 230))
 		{	if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 415;
  			if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 416;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 417;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 418;
  			ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
  			memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU51,strlen(DRAW_DIALOGBOX_CITYHALL_MENU51));
  			m_stDialogBoxInfo[13].cMode = 11;
  			m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
  			PlaySound('E', 14, 5);
 		}
 		// Hero's Hauberk
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 245) && (msY <= sY + 260))
  		{	if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 419;
	  		if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 420;
	  		if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 421;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 422;
  			ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
  			memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU52,strlen(DRAW_DIALOGBOX_CITYHALL_MENU52));
  			m_stDialogBoxInfo[13].cMode = 11;
  			m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
  			PlaySound('E', 14, 5);
 		}
 		// Hero's Leggings
 		if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 275) && (msY <= sY + 290))
 		{  	if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 423;
  			if((m_bAresden == TRUE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 424;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 1)) iReqHeroItemID = 425;
  			if((m_bAresden == FALSE) && (m_pCharList[m_cCurFocus-1]->m_sSex == 2)) iReqHeroItemID = 426;
  			ZeroMemory(m_cTakeHeroItemName,sizeof(m_cTakeHeroItemName));
  			memcpy(m_cTakeHeroItemName,DRAW_DIALOGBOX_CITYHALL_MENU53,strlen(DRAW_DIALOGBOX_CITYHALL_MENU53));
  			m_stDialogBoxInfo[13].cMode = 11;
  			m_stDialogBoxInfo[13].sV1=iReqHeroItemID;
  			PlaySound('E', 14, 5);
 		}
 		break;

	case 8:
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Yes
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_CANCELQUEST, NULL, NULL, NULL, NULL, NULL);
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// No
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 9:
		if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Yes
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_HUNTMODE, NULL, NULL, NULL, NULL, NULL);
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// No
			m_stDialogBoxInfo[13].cMode = 0;
			PlaySound('E', 14, 5);
		}
		break;

	case 10:
		if( m_iTeleportMapCount > 0 )
		{	for( int i=0 ; i<m_iTeleportMapCount ; i++ )
			{	if( (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i*15) && (msY <= sY + 144 + i*15) )
				{	bSendCommand(MSGID_REQUEST_CHARGED_TELEPORT, NULL, NULL, m_stTeleportList[i].iIndex, NULL, NULL, NULL);
					DisableDialogBox(13);
					return;
		}	}	}
		break;

	case 11: // Fix Drawjer
		 if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETHEROMANTLE, NULL, m_stDialogBoxInfo[13].sV1, NULL, NULL, NULL);
		  	m_stDialogBoxInfo[13].cMode = 0;
		  	PlaySound('E', 14, 5);
		}
		if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
		{	m_stDialogBoxInfo[13].cMode = 7;
		  	PlaySound('E', 14, 5);
		}
 		break;
	}
}

void CGame::CivilRightAdmissionHandler(char *pData)
{WORD * wp, wResult;
 char * cp;

	wp   = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wResult = *wp;

	switch (wResult) {
	case 0:
		m_stDialogBoxInfo[13].cMode = 4;
		break;

	case 1:
		m_stDialogBoxInfo[13].cMode = 3;
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		ZeroMemory(m_cLocation, sizeof(m_cLocation));
		memcpy(m_cLocation, cp, 10);
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
		break;
	}
}

void CGame::DlgBoxClick_Text(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[18].sX;
	sY = m_stDialogBoxInfo[18].sY;

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		DisableDialogBox(18);
		PlaySound('E', 14, 5);
	}
}

void CGame::DlgBoxClick_Inventory(short msX, short msY)
{int i, sX, sY;
	sX = m_stDialogBoxInfo[2].sX;
	sY = m_stDialogBoxInfo[2].sY;
	if ((msX >= sX +23) && (msX <= sX +76) && (msY >= sY +172) && (msY <= sY +184))
	{	if( m_iGizonItemUpgradeLeft == NULL )
		{	m_iGizonItemUpgradeLeft = 0;
		}
		EnableDialogBox(34, 5, NULL, NULL);
		PlaySound('E', 14, 5);

	}
	if ((msX >= sX +140) && (msX <= sX +212) && (msY >= sY +172) && (msY <= sY +184))
	{	if (m_cSkillMastery[13] == 0)
		{	AddEventList(DLGBOXCLICK_INVENTORY1, 10);
			AddEventList(DLGBOXCLICK_INVENTORY2, 10);//"The manufacturing manual is purchasable in Blacksmith."
		}else if (m_bSkillUsingStatus == TRUE)
		{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);//""You are already using another skill."
			return;
		}else if (_bIsItemOnHand() == TRUE)
		{	AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//""Your hands should be free to use this item."
			return;
		}else
		{	for (i = 0; i < DEF_MAXITEMS; i++)
			if (   (m_pItemList[i] != NULL) && (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX)
				&& (m_pItemList[i]->m_sSpriteFrame == 113)
				&& (m_pItemList[i]->m_wCurLifeSpan > 0))
			{	EnableDialogBox(26, 3, NULL, NULL, NULL);
				AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY12, 10);//"Using a manufacturing skill..."
				PlaySound('E', 14, 5);
				return;
			}
			AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY14, 10);
		}
		PlaySound('E', 14, 5);
	}
}

void CGame::DlgBoxClick_Character(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[1].sX;
	sY = m_stDialogBoxInfo[1].sY;
/*
	if ((msX >= sX + 100) && (msX <= sX + 150) && (msY >= sY + 90) && (msY <= sY + 110)) {
		MessageBox(NULL,"CRASHED!!!!","JK",MB_OK);
		DisableDialogBox(1);
		PlaySound('E', 14, 5);
	}*/

	if ((msX >= sX + 15) && (msX <= sX + 15 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY)) {
		EnableDialogBox(28, 1, NULL, NULL);
		DisableDialogBox(1);
		PlaySound('E', 14, 5);
	}
	else if ((msX >= sX + 98) && (msX <= sX + 98 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY)) {
		EnableDialogBox(32, NULL, NULL, NULL);
		DisableDialogBox(1);
		PlaySound('E', 14, 5);
	}
	else if ((msX >= sX + 180) && (msX <= sX + 180 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY)) {
		EnableDialogBox(12, NULL, NULL, NULL);
		DisableDialogBox(1);
		PlaySound('E', 14, 5);
	}
}

void CGame::DlgBoxClick_FeedBackCard(short msX, short msY)
{

}

void CGame::DlgBoxClick_MagicShop(short msX, short msY)
{
 int i, iCPivot, iYloc, iAdjX, iAdjY ;
 short sX, sY;

	sX = m_stDialogBoxInfo[16].sX;
	sY = m_stDialogBoxInfo[16].sY;

	iAdjX = -20 ;
	iAdjY = -35 ;

	iCPivot = m_stDialogBoxInfo[16].sView*10;

	iYloc = 0;
	for (i = 0; i < 9; i++) {
		if ((m_pMagicCfgList[iCPivot + i] != NULL) && (m_pMagicCfgList[iCPivot + i]->m_bIsVisible)) {
			if ((msX >= sX + iAdjX + 44) && (msX <= sX + iAdjX + 135 + 44) && (msY >= sY + iAdjY + 70 + iYloc +35) && (msY <= sY + iAdjY + 70 + 14 + iYloc +35)) {
				if (m_cMagicMastery[iCPivot + i] == 0)
				{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_STUDYMAGIC, NULL, NULL, NULL, NULL, m_pMagicCfgList[iCPivot + i]->m_cName);
					//bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_STUDYMAGIC, NULL, iCPivot + i, NULL, NULL, NULL); //2002.02.07 »óÇÏ º¯°æ ¹è¿ì°í½ÍÀº ¸ÅÁ÷³×ÀÓ¿¡¼­ ¸¶¹ý¹øÈ£·Î º¯°æ..
					PlaySound('E', 14, 5);
				}
				return;
			}
			iYloc += 18;
		}
	}

	if ((msX >= sX + iAdjX + 42 +31) && (msX <= sX + iAdjX + 50 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 0;
	if ((msX >= sX + iAdjX + 55 +31) && (msX <= sX + iAdjX + 68 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 1;
	if ((msX >= sX + iAdjX + 73 +31) && (msX <= sX + iAdjX + 93 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 2;
	if ((msX >= sX + iAdjX + 98 +31) && (msX <= sX + iAdjX + 113 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 3;
	if ((msX >= sX + iAdjX + 118 +31) && (msX <= sX + iAdjX + 129 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 4;
	if ((msX >= sX + iAdjX + 133 +31) && (msX <= sX + iAdjX + 150 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 5;
	if ((msX >= sX + iAdjX + 154 +31) && (msX <= sX + iAdjX + 177 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 6;
	if ((msX >= sX + iAdjX + 181 +31) && (msX <= sX + iAdjX + 210 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 7;
	if ((msX >= sX + iAdjX + 214 +31) && (msX <= sX + iAdjX + 230 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 8;
	if ((msX >= sX + iAdjX + 234 +31) && (msX <= sX + iAdjX + 245 +31) && (msY >= sY + iAdjY + 248 +35) && (msY <= sY + iAdjY + 260 +35))
		m_stDialogBoxInfo[16].sView = 9;
}

void CGame::_RemoveChatMsgListByObjectID(int iObjectID)
{
 int i;

	for (i = 1; i < DEF_MAXCHATMSGS; i++)
	if ((m_pChatMsgList[i] != NULL) && (m_pChatMsgList[i]->m_iObjectID == iObjectID)) {
		delete m_pChatMsgList[i];
		m_pChatMsgList[i] = NULL;
	}
}

void CGame::PlaySound(char cType, int iNum, int iDist, long lPan)
{
 int iVol;

	if (m_bSoundFlag == FALSE) return;
	if (m_bSoundStat == FALSE) return;

	if (iDist > 10) iDist = 10;

	iVol = (m_cSoundVolume - 100)*20;
	iVol += -200 * iDist;

	if (iVol > 0) iVol = 0;
	if (iVol < -10000) iVol = -10000;

	if (iVol > -2000) {

		switch (cType) {
		case 'C':
			if (m_pCSound[iNum] == NULL) return;
			m_pCSound[iNum]->Play(FALSE, lPan, iVol);
			break;

		case 'M':
			if (m_pMSound[iNum] == NULL) return;
			m_pMSound[iNum]->Play(FALSE, lPan, iVol);
			break;

		case 'E':
			if (m_pESound[iNum] == NULL) return;
			m_pESound[iNum]->Play(FALSE, lPan, iVol);
			break;
		}
	}
}

void CGame::_DrawBlackRect(int iSize)
{
 int ix, iy, sx, sy, dcx, dcy;
 DWORD dwTime;

	dwTime = timeGetTime();

	dcx = 40 - iSize*2;
	dcy = 30 - iSize*2;

	sx = iSize*16;
	sy = iSize*16;

	for (ix = 0; ix < dcx; ix++) {
		m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(ix*16 + sx, iSize*16,       12, dwTime);
		m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(ix*16 + sx, 464 - iSize*16, 12, dwTime);
	}

	for (iy = 0; iy < dcy; iy++) {
		m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(iSize*16,       iy*16 + sy, 12, dwTime);
		m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(624 - iSize*16, iy*16 + sy, 12, dwTime);
	}
}

BOOL CGame::_bCheckItemByType(char cType)
{
 int i;

	for (i = 0; i < DEF_MAXITEMS; i++)
	if ( (m_pItemList[i] != NULL) && (m_pItemList[i]->m_cItemType == cType) ) return TRUE;

	return FALSE;
}


void CGame::DynamicObjectHandler(char * pData)
{
 WORD * wp;
 char * cp;
 short * sp, sX, sY, sV1, sV2, sV3;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE);
	wp = (WORD *)cp;
	cp += 2;

	sp = (short *)cp;
	sX = *sp;
	cp += 2;

	sp = (short *)cp;
	sY = *sp;
	cp += 2;

	sp = (short *)cp;
	sV1 = *sp;
	cp += 2;

	sp = (short *)cp;
	sV2 = *sp;		   // Dyamic Object Index
	cp += 2;

	sp = (short *)cp;
	sV3 = *sp;
	cp += 2;

	switch (*wp) {
	case DEF_MSGTYPE_CONFIRM:// Dynamic Object
		m_pMapData->bSetDynamicObject(sX, sY, sV2, sV1, TRUE);
		break;

	case DEF_MSGTYPE_REJECT:// Dynamic object
		m_pMapData->bSetDynamicObject(sX, sY, sV2, NULL, TRUE);
		break;
	}
}

BOOL CGame::_bIsItemOnHand() // Snoopy: Fixed to remove ShieldCast
{int i;
 WORD wWeaponType;
	for (i = 0; i < DEF_MAXITEMS; i++)
	if ((m_pItemList[i] != NULL) && (m_bIsItemEquipped[i] == TRUE))
	{	if (   (m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
			|| (m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
			return TRUE;
	}
	for (i = 0; i < DEF_MAXITEMS; i++)
	if ((m_pItemList[i] != NULL) && (m_bIsItemEquipped[i] == TRUE))
	{	if (m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
		{	wWeaponType = ((m_sPlayerAppr2 & 0x0FF0) >> 4);
			// Snoopy 34 for all wands.
			if ((wWeaponType >= 34) && (wWeaponType < 40)) return FALSE;
			//else if( wWeaponType == 27 ) return FALSE; // Farming's hoe !
			else return TRUE;
	}	}
	return FALSE;
}

int CGame::_iCalcTotalWeight()
{
 int i, iWeight, iCnt, iTemp;
	iCnt = 0;
	iWeight = 0;
	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] != NULL)
	{	if (   (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_CONSUME)
			|| (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_ARROW) )
		{	iTemp = m_pItemList[i]->m_wWeight * m_pItemList[i]->m_dwCount;
			if (strcmp(m_pItemList[i]->m_cName, "Gold") == 0) iTemp = iTemp / 20;
			iWeight += iTemp;
		}else iWeight += m_pItemList[i]->m_wWeight;
		iCnt++;
	}

	return iWeight;
}

void CGame::DlgBoxClick_15AgeMsg(short msX, short msY)
{	// Snoopy: removed feedback card
	short sX, sY;
	sX = m_stDialogBoxInfo[5].sX;
	sY = m_stDialogBoxInfo[5].sY;
    if ((msX >= sX + 120 ) && (msX <= sX + 120 + DEF_BTNSZX ) && (msY >= sY + 127 ) && (msY <= sY + 127 + DEF_BTNSZY))
	   DisableDialogBox(5);
}


void CGame::DlgBoxClick_WarningMsg(short msX, short msY)// Á¤Áø±¤.
{	short sX, sY;
	sX = m_stDialogBoxInfo[6].sX;
	sY = m_stDialogBoxInfo[6].sY;

    if ((msX >= sX + 120 ) && (msX <= sX + 120 + DEF_BTNSZX ) && (msY >= sY + 127 ) && (msY <= sY + 127 + DEF_BTNSZY))
	   DisableDialogBox(6);
}

void CGame::DlgBoxClick_ItemDrop(short msX, short msY)
{	short sX, sY;
	if (m_cCommand < 0) return;

	sX = m_stDialogBoxInfo[4].sX;
	sY = m_stDialogBoxInfo[4].sY;

	if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
	{
	    m_stDialogBoxInfo[4].cMode = 3;
        bSendCommand(MSGID_COMMAND_COMMON,
                     DEF_COMMONTYPE_ITEMDROP,
                     NULL,
                     m_stDialogBoxInfo[4].sView,
                     1,
                     NULL,
                     m_pItemList[m_stDialogBoxInfo[4].sView]->m_cName);
		//m_stDialogBoxInfo[40].sView ;
		DisableDialogBox(4);
	}

	else if ((msX >= sX + 170 ) && (msX <= sX + 170 + DEF_BTNSZX ) && (msY >= sY + 55 ) && (msY <= sY + 55 + DEF_BTNSZY))
	{

		for (int i = 0; i < DEF_MAXSELLLIST; i++)
	         m_bIsItemDisabled[i] = FALSE;

		DisableDialogBox(4);
	}
    else if ((msX >= sX + 35) && (msX <= sX + 240 ) && (msY >= sY + 80) && (msY <= sY + 90))
	{
	   m_bItemDrop = !m_bItemDrop;
	}
}

void CGame::DlgBoxClick_ItemSellorRepair(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[23].sX;
	sY = m_stDialogBoxInfo[23].sY;

	switch (m_stDialogBoxInfo[23].cMode) {
	case 1:
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Sell
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SELLITEMCONFIRM, NULL, m_stDialogBoxInfo[23].sV1, m_stDialogBoxInfo[23].sV4, m_stDialogBoxInfo[23].sV3, m_pItemList[m_stDialogBoxInfo[23].sV1]->m_cName); //v1.2
			m_stDialogBoxInfo[23].cMode = 3;
		}
		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Cancel
			m_bIsItemDisabled[ m_stDialogBoxInfo[23].sV1 ] = FALSE;
			DisableDialogBox(23);
		}
		break;

	case 2:
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Repair
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEMCONFIRM, NULL, m_stDialogBoxInfo[23].sV1, NULL, NULL, m_pItemList[m_stDialogBoxInfo[23].sV1]->m_cName);
			m_stDialogBoxInfo[23].cMode = 4;
		}
		if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)) {
			// Cancel
			m_bIsItemDisabled[ m_stDialogBoxInfo[23].sV1 ] = FALSE;
			DisableDialogBox(23);
		}
		break;
	}
}


int CGame::iGetLevelExp(int iLevel)
{int iRet;
	if (iLevel == 0) return 0;
	iRet = iGetLevelExp(iLevel - 1) + iLevel * ( 50 + (iLevel * (iLevel / 17) * (iLevel / 17) ) );
	return iRet;
}

int CGame::_iGetTotalItemNum()
{ int i, iCnt;
	iCnt = 0;
	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] != NULL) iCnt++;
	return iCnt;
}

BOOL CGame::bCheckExID(char * pName)
{	if (m_pExID == NULL) return FALSE;
	if (memcmp(m_cPlayerName, pName, 10) == 0) return FALSE;
	char cTxt[12];
	ZeroMemory(cTxt, sizeof(cTxt));
	memcpy(cTxt, m_pExID->m_pMsg, strlen(m_pExID->m_pMsg));
	if (memcmp(cTxt, pName, 10) == 0) return TRUE;
	else return FALSE;
}

void CGame::DrawWhetherEffects()
{
#define MAXNUM 1000
 static int ix1[MAXNUM];
 static int iy2[MAXNUM];
 static int iFrame[MAXNUM];
 static int iNum = 0;
 int i;
 short dX, dY, sCnt;
 char cTempFrame;
 DWORD dwTime = m_dwCurTime;

	switch (m_cWhetherEffectType) {
	case 1:
	case 2:
	case 3: // rain
		switch (m_cWhetherEffectType) {
		case 1: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
		case 2:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
		case 3:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
		}

		for (i = 0; i < sCnt; i++)
		{	if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 20) && (m_stWhetherObject[i].sX != 0))
			{	dX = m_stWhetherObject[i].sX - m_sViewPointX;
				dY = m_stWhetherObject[i].sY - m_sViewPointY;
				cTempFrame = 16 + (m_stWhetherObject[i].cStep / 6);
				m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);
 			}else if ((m_stWhetherObject[i].cStep >= 20) && (m_stWhetherObject[i].cStep < 25) && (m_stWhetherObject[i].sX != 0))
			{	dX = m_stWhetherObject[i].sX - m_sViewPointX;
				dY = m_stWhetherObject[i].sY - m_sViewPointY;
				m_pEffectSpr[11]->PutTransSprite(dX, dY, m_stWhetherObject[i].cStep, dwTime);
		}	}
		break;

	case 4:
	case 5:
	case 6: // Snow
		switch (m_cWhetherEffectType) {
		case 4: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
		case 5:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
		case 6:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
		}
		for (i = 0; i < sCnt; i++)
		{	if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 80))
			{	dX = m_stWhetherObject[i].sX - m_sViewPointX;
				dY = m_stWhetherObject[i].sY - m_sViewPointY;

				// Snoopy: Snow on lower bar
				if (dY >= 460)
				{	cTempFrame = 39 + (m_stWhetherObject[i].cStep / 20)*3;
					dX = m_stWhetherObject[i].sBX;
					dY = 426;
				}else cTempFrame = 39 + (m_stWhetherObject[i].cStep / 20)*3 + (rand() % 3);

				m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);

				if (m_bIsXmas == TRUE)
				{	if( dY == 478 - 53 )
					{	ix1[iNum] = dX;
						iy2[iNum] = dY + (rand()%5);
						iFrame[iNum] = cTempFrame;
						iNum++;
					}
					if( iNum >= MAXNUM ) iNum = 0;
		}	}	}
		if (m_bIsXmas == TRUE)
		{	for (i = 0; i <= MAXNUM; i++)
			{	if( iy2[i] > 10 ) m_pEffectSpr[11]->PutTransSprite(ix1[i], iy2[i], iFrame[i], dwTime);
		}	}
		break;
	}
}

void CGame::WhetherObjectFrameCounter()
{
 int i;
 short sCnt;
 char  cAdd;
 DWORD dwTime = m_dwCurTime;

	if ((dwTime - m_dwWOFtime) < 30) return;
	m_dwWOFtime = dwTime;

	switch (m_cWhetherEffectType) {
	case 1:
	case 2:
	case 3: // Rain
		switch (m_cWhetherEffectType) {
		case 1: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
		case 2:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
		case 3:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
		}
		for (i = 0; i < sCnt; i++)
		{	m_stWhetherObject[i].cStep++;
			if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 20))
			{	cAdd = (40 - m_stWhetherObject[i].cStep);
				if (cAdd < 0) cAdd = 0;
				m_stWhetherObject[i].sY = m_stWhetherObject[i].sY + cAdd;
				if (cAdd != 0)
					m_stWhetherObject[i].sX = m_stWhetherObject[i].sX - 1;
			}else if (m_stWhetherObject[i].cStep >= 25)
			{	if (m_bIsWhetherEffect == FALSE)
				{	m_stWhetherObject[i].sX    = 0;
					m_stWhetherObject[i].sY    = 0;
					m_stWhetherObject[i].cStep = 30;
				}else
				{	m_stWhetherObject[i].sX    = (m_pMapData->m_sPivotX*32) + ((rand() % 940) - 200) + 300;
					m_stWhetherObject[i].sY    = (m_pMapData->m_sPivotY*32) + ((rand() % 800) - 600) + 240;
					m_stWhetherObject[i].cStep = -1*(rand() % 10);
		}	}	}
		break;

	case 4:
	case 5:
	case 6:
		switch (m_cWhetherEffectType) {
		case 4: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
		case 5:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
		case 6:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
		}
		for (i = 0; i < sCnt; i++)
		{	m_stWhetherObject[i].cStep++;
			if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 80))
			{	cAdd = (80 - m_stWhetherObject[i].cStep)/10;
				if (cAdd < 0) cAdd = 0;
				m_stWhetherObject[i].sY = m_stWhetherObject[i].sY + cAdd;

				//Snoopy: Snow on lower bar
				if (m_stWhetherObject[i].sY > (426 + m_sViewPointY))
				{	m_stWhetherObject[i].sY = 470 + m_sViewPointY;
					if ((rand() % 10) !=2) m_stWhetherObject[i].cStep--;
					if (m_stWhetherObject[i].sBX == 0) m_stWhetherObject[i].sBX = m_stWhetherObject[i].sX - m_sViewPointX;


				}else m_stWhetherObject[i].sX += 1 - (rand() % 3);
			}else if (m_stWhetherObject[i].cStep >= 80)
			{	if (m_bIsWhetherEffect == FALSE)
				{	m_stWhetherObject[i].sX    = 0;
					m_stWhetherObject[i].sY    = 0;
					m_stWhetherObject[i].sBX   = 0;
					m_stWhetherObject[i].cStep = 80;
				}else
				{	m_stWhetherObject[i].sX    = (m_pMapData->m_sPivotX*32) + ((rand() % 940) - 200) + 300;
					m_stWhetherObject[i].sY    = (m_pMapData->m_sPivotY*32) + ((rand() % 800) - 600) + 600;
					m_stWhetherObject[i].cStep = -1*(rand() % 10);
					m_stWhetherObject[i].sBX   = 0;
		}	}	}
		break;
	}
}

void CGame::SetWhetherStatus(BOOL bStart, char cType)
{SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	if (bStart == TRUE)
	{	m_bIsWhetherEffect   = TRUE;
		m_cWhetherEffectType = cType;
		if ((m_bSoundStat == TRUE) && (m_bSoundFlag) && (cType >= 1) && (cType <= 3)) m_pESound[38]->Play(TRUE);

		for (int i = 0; i < DEF_MAXWHETHEROBJECTS; i++)
		{	m_stWhetherObject[i].sX    = 1;
			m_stWhetherObject[i].sBX    = 1;
			m_stWhetherObject[i].sY    = 1;
			m_stWhetherObject[i].cStep = -1*(rand() % 40);
		}
		if( cType >= 4 && cType <= 6 )
		{	if( m_bMusicStat ) StartBGM();
		}
	}else
	{	m_bIsWhetherEffect = FALSE;
		m_cWhetherEffectType = NULL;
		if ((m_bSoundStat == TRUE) && (m_bSoundFlag)) m_pESound[38]->bStop();
	}
}

void CGame::DlgBoxClick_ShutDownMsg(short msX, short msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[25].sX;
	sY = m_stDialogBoxInfo[25].sY;
	if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY)) {
		DisableDialogBox(25);
		PlaySound('E', 14, 5);
	}
}

void CGame::DrawLine(int x0, int y0, int x1, int y1, int iR, int iG, int iB)
{
 int dx, dy, x_inc, y_inc, error, index, dstR, dstG, dstB;
 int iResultX, iResultY;
 WORD * pDst;

	if ((x0 == x1) && (y0 == y1)) return;
	error = 0;
	iResultX = x0;
	iResultY = y0;
	dx = x1-x0;
	dy = y1-y0;
	if(dx>=0)
	{	x_inc = 1;
	}else
	{	x_inc = -1;
		dx = -dx;
	}
	if(dy>=0)
	{	y_inc = 1;
	}else
	{	y_inc = -1;
		dy = -dy;
	}
	if(dx>dy)
	{	for(index = 0; index <= dx; index++)
		{	error += dy;
			if(error > dx)
			{	error -= dx;
				iResultY += y_inc;
			}
			iResultX += x_inc;
			if ((iResultX >= 0) && (iResultX < 640) && (iResultY >= 0) && (iResultY < 480)) {
				pDst = (WORD *)m_DDraw.m_pBackB4Addr + iResultX + ((iResultY)*m_DDraw.m_sBackB4Pitch);
				switch (m_DDraw.m_cPixelFormat) {
				case 1:
					dstR = (int)m_DDraw.m_lTransRB100[(pDst[0]&0xF800)>>11][iR];
					dstG = (int)m_DDraw.m_lTransG100[(pDst[0]&0x7E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB100[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<11) | (dstG<<5) | dstB);
					break;

				case 2:
					dstR = (int)m_DDraw.m_lTransRB100[(pDst[0]&0x7C00)>>10][iR];
					dstG = (int)m_DDraw.m_lTransG100[(pDst[0]&0x3E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB100[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<10) | (dstG<<5) | dstB);
					break;
		}	}	}
	}else
	{	for(index = 0; index <= dy; index++)
		{	error += dx;
			if(error > dy)
			{	error -= dy;
				iResultX += x_inc;
			}
			iResultY += y_inc;
			if ((iResultX >= 0) && (iResultX < 640) && (iResultY >= 0) && (iResultY < 480)) {
				pDst = (WORD *)m_DDraw.m_pBackB4Addr + iResultX + ((iResultY)*m_DDraw.m_sBackB4Pitch);
				switch (m_DDraw.m_cPixelFormat) {
				case 1:
					dstR = (int)m_DDraw.m_lTransRB100[(pDst[0]&0xF800)>>11][iR];
					dstG = (int)m_DDraw.m_lTransG100[(pDst[0]&0x7E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB100[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<11) | (dstG<<5) | dstB);
					break;

				case 2:
					dstR = (int)m_DDraw.m_lTransRB100[(pDst[0]&0x7C00)>>10][iR];
					dstG = (int)m_DDraw.m_lTransG100[(pDst[0]&0x3E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB100[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<10) | (dstG<<5) | dstB);
					break;
	}	}	}	}
}


void CGame::DrawLine2(int x0, int y0, int x1, int y1, int iR, int iG, int iB)
{int dx, dy, x_inc, y_inc, error, index, dstR, dstG, dstB;
 int iResultX, iResultY;
 WORD * pDst;
	if ((x0 == x1) && (y0 == y1)) return;

	error = 0;
	iResultX = x0;
	iResultY = y0;
	dx = x1-x0;
	dy = y1-y0;
	if(dx>=0)
	{	x_inc = 1;
	}else
	{	x_inc = -1;
		dx = -dx;
	}
	if(dy>=0)
	{	y_inc = 1;
	}else
	{	y_inc = -1;
		dy = -dy;
	}
	if(dx>dy)
	{	for(index = 0; index <= dx; index++)
		{	error += dy;
			if(error > dx)
			{	error -= dx;
				iResultY += y_inc;
			}
			iResultX += x_inc;
			if ((iResultX >= 0) && (iResultX < 640) && (iResultY >= 0) && (iResultY < 480)) {
				pDst = (WORD *)m_DDraw.m_pBackB4Addr + iResultX + ((iResultY)*m_DDraw.m_sBackB4Pitch);
				switch (m_DDraw.m_cPixelFormat) {
				case 1:
					dstR = (int)m_DDraw.m_lTransRB50[(pDst[0]&0xF800)>>11][iR];
					dstG = (int)m_DDraw.m_lTransG50[(pDst[0]&0x7E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB50[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<11) | (dstG<<5) | dstB);
					break;

				case 2:
					dstR = (int)m_DDraw.m_lTransRB50[(pDst[0]&0x7C00)>>10][iR];
					dstG = (int)m_DDraw.m_lTransG50[(pDst[0]&0x3E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB50[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<10) | (dstG<<5) | dstB);
					break;
		}	}	}
	}else
	{	for(index = 0; index <= dy; index++)
		{	error += dx;
			if(error > dy)
			{	error -= dy;
				iResultX += x_inc;
			}
			iResultY += y_inc;
			if ((iResultX >= 0) && (iResultX < 640) && (iResultY >= 0) && (iResultY < 480)) {
				pDst = (WORD *)m_DDraw.m_pBackB4Addr + iResultX + ((iResultY)*m_DDraw.m_sBackB4Pitch);
				switch (m_DDraw.m_cPixelFormat) {
				case 1:
					dstR = (int)m_DDraw.m_lTransRB50[(pDst[0]&0xF800)>>11][iR];
					dstG = (int)m_DDraw.m_lTransG50[(pDst[0]&0x7E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB50[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<11) | (dstG<<5) | dstB);
					break;

				case 2:
					dstR = (int)m_DDraw.m_lTransRB50[(pDst[0]&0x7C00)>>10][iR];
					dstG = (int)m_DDraw.m_lTransG50[(pDst[0]&0x3E0)>>5][iG];
					dstB = (int)m_DDraw.m_lTransRB50[(pDst[0]&0x1F)][iB];
					*pDst = (WORD)((dstR<<10) | (dstG<<5) | dstB);
					break;
	}	}	}	}
}

void CGame::_DrawThunderEffect(int sX, int sY, int dX, int dY, int rX, int rY, char cType)
{int j, iErr, pX1, pY1, iX1, iY1, tX, tY;
 char cDir;
 DWORD dwTime;
 WORD  wR1, wG1, wB1, wR2, wG2, wB2, wR3, wG3, wB3, wR4, wG4, wB4;
	dwTime = m_dwCurTime;
	sX = pX1 = iX1 = tX = sX;
	sY = pY1 = iY1 = tY = sY;
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(50, 50, 100), &wR1, &wG1, &wB1);
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(30, 30, 100), &wR2, &wG2, &wB2);
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(0, 0, 30), &wR3, &wG3, &wB3);
	m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, RGB(50, 50, 200), &wR4, &wG4, &wB4);

	for (j = 0; j < 100; j++)
	{	switch (cType) {
		case 1:
			DrawLine(pX1, pY1, iX1, iY1, 15, 15, 20);
			DrawLine(pX1-1, pY1, iX1-1, iY1, wR1, wG1, wB1);
			DrawLine(pX1+1, pY1, iX1+1, iY1, wR1, wG1, wB1);
			DrawLine(pX1, pY1-1, iX1, iY1-1, wR1, wG1, wB1);
			DrawLine(pX1, pY1+1, iX1, iY1+1, wR1, wG1, wB1);

			DrawLine(pX1-2, pY1, iX1-2, iY1, wR2, wG2, wB2);
			DrawLine(pX1+2, pY1, iX1+2, iY1, wR2, wG2, wB2);
			DrawLine(pX1, pY1-2, iX1, iY1-2, wR2, wG2, wB2);
			DrawLine(pX1, pY1+2, iX1, iY1+2, wR2, wG2, wB2);

			DrawLine(pX1-1, pY1-1, iX1-1, iY1-1, wR3, wG3, wB3);
			DrawLine(pX1+1, pY1-1, iX1+1, iY1-1, wR3, wG3, wB3);
			DrawLine(pX1+1, pY1-1, iX1+1, iY1-1, wR3, wG3, wB3);
			DrawLine(pX1-1, pY1+1, iX1-1, iY1+1, wR3, wG3, wB3);
			break;

		case 2:
			DrawLine2(pX1, pY1, iX1, iY1, wR4, wG4, wB4);
			break;
		}
		iErr = 0;
		m_Misc.GetPoint(sX, sY, dX, dY, &tX, &tY, &iErr, j*10);
		pX1 = iX1;
		pY1 = iY1;
		cDir = m_Misc.cGetNextMoveDir(iX1, iY1, tX, tY);
		switch (cDir) {
		case 1:	rY -= 5; break;
		case 2: rY -= 5; rX += 5; break;
		case 3:	rX += 5; break;
		case 4: rX += 5; rY += 5; break;
		case 5: rY += 5; break;
		case 6: rX -= 5; rY += 5; break;
		case 7: rX -= 5; break;
		case 8: rX -= 5; rY -= 5; break;
		}
		if (rX < -20) rX = -20;
		if (rX >  20) rX =  20;
		if (rY < -20) rY = -20;
		if (rY >  20) rY =  20;
		iX1 = iX1 + rX;
		iY1 = iY1 + rY;
		if ((abs(tX - dX) < 5) && (abs(tY - dY) < 5)) break;
	}
	switch (cType) {
	case 1:
		m_pEffectSpr[6]->PutTransSprite(iX1, iY1, (rand() % 2), dwTime);
		break;
	}
}

BOOL CGame::bDlgBoxPress_SkillDlg(short msX, short msY)
{int i , iAdjX, iAdjY ;
 char  cItemID;
 short sX, sY, x1, y1, x2, y2, sArray[10];
	sX = m_stDialogBoxInfo[26].sX;
	sY = m_stDialogBoxInfo[26].sY;
	iAdjX = 5 ;
	iAdjY = 10 ;
	switch (m_stDialogBoxInfo[26].cMode) {
	case 1:
		ZeroMemory(sArray, sizeof(sArray));
		sArray[1] = m_stDialogBoxInfo[26].sV1;
		sArray[2] = m_stDialogBoxInfo[26].sV2;
		sArray[3] = m_stDialogBoxInfo[26].sV3;
		sArray[4] = m_stDialogBoxInfo[26].sV4;
		sArray[5] = m_stDialogBoxInfo[26].sV5;
		sArray[6] = m_stDialogBoxInfo[26].sV6;
		for (i = 1; i <= 6; i++)
		if ((sArray[i] != -1) && (m_pItemList[sArray[i]] != NULL))
		{	cItemID = (char)sArray[i];
			switch (i) {
			case 1: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55, sY + iAdjY + 55,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 2: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*1, sY + iAdjY + 55,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 3: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*2, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 4: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55, sY + iAdjY + 100,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 5: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*1, sY + iAdjY + 100,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 6: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*2, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
			}
			x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
			y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
			x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
			y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;
			if ((msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
			{	switch (i) {
				case 1: m_stDialogBoxInfo[26].sV1 = -1; break;
				case 2: m_stDialogBoxInfo[26].sV2 = -1; break;
				case 3: m_stDialogBoxInfo[26].sV3 = -1; break;
				case 4: m_stDialogBoxInfo[26].sV4 = -1; break;
				case 5: m_stDialogBoxInfo[26].sV5 = -1; break;
				case 6: m_stDialogBoxInfo[26].sV6 = -1; break;
				}
				m_bIsItemDisabled[cItemID] = FALSE;
				m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = cItemID;
				m_stMCursor.sDistX = msX + iAdjX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
				m_stMCursor.sDistY = msY + iAdjY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
				return TRUE;
		}	}
		break;

	case 4:
		ZeroMemory(sArray, sizeof(sArray));
		sArray[1] = m_stDialogBoxInfo[26].sV1;
		sArray[2] = m_stDialogBoxInfo[26].sV2;
		sArray[3] = m_stDialogBoxInfo[26].sV3;
		sArray[4] = m_stDialogBoxInfo[26].sV4;
		sArray[5] = m_stDialogBoxInfo[26].sV5;
		sArray[6] = m_stDialogBoxInfo[26].sV6;
		for (i = 1; i <= 6; i++)
		if ((sArray[i] != -1) && (m_pItemList[sArray[i]] != NULL))
		{	cItemID = (char)sArray[i];
			switch (i) {
			case 1: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 +30 +13, sY + iAdjY + 55 +180,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 2: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*1 +30 +13, sY + iAdjY + 55 +180,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 3: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*2 +30 +13, sY + iAdjY + 55 +180, m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 4: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 +30 +13, sY + iAdjY + 100 +180,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 5: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*1 +30 +13, sY + iAdjY + 100 +180,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 6: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55+45*2 +30 +13, sY + iAdjY + 100 +180, m_pItemList[cItemID]->m_sSpriteFrame); break;
			}
			x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
			y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
			x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
			y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;

			if ((msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
			{	switch (i) {
				case 1: m_stDialogBoxInfo[26].sV1 = -1; break;
				case 2: m_stDialogBoxInfo[26].sV2 = -1; break;
				case 3: m_stDialogBoxInfo[26].sV3 = -1; break;
				case 4: m_stDialogBoxInfo[26].sV4 = -1; break;
				case 5: m_stDialogBoxInfo[26].sV5 = -1; break;
				case 6: m_stDialogBoxInfo[26].sV6 = -1; break;
				}
				m_bIsItemDisabled[cItemID] = FALSE;
				m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = cItemID;
				m_stMCursor.sDistX = msX + iAdjX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
				m_stMCursor.sDistY = msY + iAdjY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
				m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
				return TRUE;
		}	}
		break;
	// Crafting
	case 7:
		ZeroMemory(sArray, sizeof(sArray));
		sArray[1] = m_stDialogBoxInfo[26].sV1;
		sArray[2] = m_stDialogBoxInfo[26].sV2;
		sArray[3] = m_stDialogBoxInfo[26].sV3;
		sArray[4] = m_stDialogBoxInfo[26].sV4;
		sArray[5] = m_stDialogBoxInfo[26].sV5;
		sArray[6] = m_stDialogBoxInfo[26].sV6;
		for (i = 1; i <= 6; i++)
		if ((sArray[i] != -1) && (m_pItemList[sArray[i]] != NULL))
		{	cItemID = (char)sArray[i];
			switch (i) {
			case 1: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55, sY + iAdjY + 55,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 2: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65+45*1, sY + iAdjY + 40,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 3: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65+45*2, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 4: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65, sY + iAdjY + 100,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 5: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65+45*1, sY + iAdjY + 115,  m_pItemList[cItemID]->m_sSpriteFrame); break;
			case 6: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 75+45*2, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
			}
			x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
			y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
			x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
			y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;
			if ((msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
			{	switch (i) {
				case 1: m_stDialogBoxInfo[26].sV1 = -1; break;
				case 2: m_stDialogBoxInfo[26].sV2 = -1; break;
				case 3: m_stDialogBoxInfo[26].sV3 = -1; break;
				case 4: m_stDialogBoxInfo[26].sV4 = -1; break;
				case 5: m_stDialogBoxInfo[26].sV5 = -1; break;
				case 6: m_stDialogBoxInfo[26].sV6 = -1; break;
				}
				m_bIsItemDisabled[cItemID] = FALSE;
				m_stMCursor.cSelectedObjectType	= DEF_SELECTEDOBJTYPE_ITEM;
				m_stMCursor.sSelectedObjectID   = cItemID;
				m_stMCursor.sDistX = msX + iAdjX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
				m_stMCursor.sDistY = msY + iAdjY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
				return TRUE;
		}	}
		break;
	}

	return FALSE;
}
// Snoopy: added StormBlade
int CGame::_iGetAttackType()
{WORD wWeaponType;
	wWeaponType = ((m_sPlayerAppr2 & 0x0FF0) >> 4);
	if (wWeaponType == 0)
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[5] >= 100)) return 20;
		else return 1;		// Boxe
	}else if ((wWeaponType >= 1) && (wWeaponType <= 2))
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[7] >= 100)) return 21;
		else return 1;		//Dag, SS
	}else if ((wWeaponType > 2) && (wWeaponType < 20))
	{	if ((wWeaponType == 7)||(wWeaponType == 18)) // Added Kloness Esterk
		{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[9] >= 100)) return 22;
			else return 1;  // Esterk
		}else if (wWeaponType == 15)
		{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[8] >= 100)) return 30;
			else return 5;  // StormBlade
		}else
		{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[8] >= 100)) return 23;
			else return 1;	// LongSwords
		}
	}else if ((wWeaponType >= 20) && (wWeaponType < 29))
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[10] >= 100)) return 24;
		else return 1;		// Haches
	}else if ((wWeaponType >= 30) && (wWeaponType < 33))
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[14] >= 100)) return 26;
		else return 1;		// Hammers
	}else if ((wWeaponType >= 34) && (wWeaponType < 40))
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[21] >= 100)) return 27;
		else return 1;		// Wands
	}else if (wWeaponType >= 40)
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[6] >= 100)) return 25;
		else return 2;		// Bows
	}else if ((wWeaponType == 29) || (wWeaponType == 33))
	{	if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == TRUE) && (m_cSkillMastery[8] >= 100)) return 23;
		else return 1;		// LS
	}
	return 0;
}

int CGame::_iGetWeaponSkillType()
{WORD wWeaponType;
	wWeaponType = ((m_sPlayerAppr2 & 0x0FF0) >> 4);
	if (wWeaponType == 0)
	{	return 5; // Openhand
	}else if ((wWeaponType >= 1) && (wWeaponType < 3))
	{	return 7; // SS
	}else if ((wWeaponType >= 3) && (wWeaponType < 20))
	{	if ((wWeaponType == 7)||(wWeaponType == 18)) // Esterk or KlonessEsterk
			 return 9; // Fencing
		else return 8; // LS
	}else if ((wWeaponType >= 20) && (wWeaponType < 29))
	{	return 10; // Axe (20..28)
	}else if ((wWeaponType >= 30) && (wWeaponType < 33))
	{	return 14; // Hammer (30,31,32)
	}else if ((wWeaponType >= 34) && (wWeaponType < 40))
	{	return 21; // Wand
	}else if (wWeaponType >= 40)
	{	return 6;  // Bow
	}else if ((wWeaponType == 29) || (wWeaponType == 33))
	{	return 8;  // LS LightingBlade || BlackShadow
	}
	return 1; // Fishing !
}

void CGame::NotifyMsg_AdminInfo(char *pData)
{
 char * cp, cStr[256];
 int  * ip, iV1, iV2, iV3, iV4, iV5;

	cp = (char *)(pData + 6);

	ip = (int *)cp;
	iV1 = *ip;
	cp += 4;

	ip = (int *)cp;
	iV2 = *ip;
	cp += 4;

	ip = (int *)cp;
	iV3 = *ip;
	cp += 4;

	ip = (int *)cp;
	iV4 = *ip;
	cp += 4;

	ip = (int *)cp;
	iV5 = *ip;
	cp += 4;

	ZeroMemory(cStr, sizeof(cStr));
	wsprintf(cStr, "%d %d %d %d %d", iV1, iV2, iV3, iV4, iV5);
	AddEventList(cStr);
}

BOOL CGame::_bCheckBadWords(char *pMsg)
{
 char cStr[500];
 int i, iLen;
	ZeroMemory(cStr, sizeof(cStr));
	strcpy(cStr, pMsg);
	iLen = strlen(cStr);

	for (i = 0; i < iLen; i++) {
		if (m_pCGameMonitor->bCheckBadWord((char *)(cStr + i)) == TRUE) return TRUE;
		if ((unsigned char)cStr[i] >= 128) i++;
	}

	return FALSE;
}

/*********************************************************************************************************************
**  void CGame::bItemDrop_ExchangeDialog(short msX, short msY)	(snoopy)											**
**  description			:: modifyed for MultiTrade																	**
**********************************************************************************************************************/
void CGame::bItemDrop_ExchangeDialog(short msX, short msY)
{char cItemID;
	if (m_cCommand < 0) return;
	if (m_stDialogBoxExchangeInfo[3].sV1 != -1) return; //Do not accept item's drop if already 4 items.

	cItemID = (char)m_stMCursor.sSelectedObjectID;
	if ( ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW)) &&
		 (m_pItemList[cItemID]->m_dwCount > 1) )
	{	m_stDialogBoxInfo[17].sX  = msX - 140;
		m_stDialogBoxInfo[17].sY  = msY - 70;
		if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;
		m_stDialogBoxInfo[17].sV1 = m_sPlayerX+1;
		m_stDialogBoxInfo[17].sV2 = m_sPlayerY+1;
		m_stDialogBoxInfo[17].sV3 = 1000;
		m_stDialogBoxInfo[17].sV4 = cItemID;
		//m_stDialogBoxInfo[27].sView = cItemID;
		if (m_stDialogBoxExchangeInfo[0].sV1 == -1)			m_stDialogBoxExchangeInfo[0].sItemID = cItemID;
		else if (m_stDialogBoxExchangeInfo[1].sV1 == -1)	m_stDialogBoxExchangeInfo[1].sItemID = cItemID;
		else if (m_stDialogBoxExchangeInfo[2].sV1 == -1)	m_stDialogBoxExchangeInfo[2].sItemID = cItemID;
		else if (m_stDialogBoxExchangeInfo[3].sV1 == -1)	m_stDialogBoxExchangeInfo[3].sItemID = cItemID;
		else return; // Impossible case, tested at function beginning
		ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
		EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, NULL);
		return;
	}else // hum? déjà on affiche? , bon je désactive, ca devrait plutôt s'afficher lors du retour du serveur.
	{	/*m_stDialogBoxInfo[27].sV1 = m_pItemList[cItemID]->m_sSprite;
		m_stDialogBoxInfo[27].sV2 = m_pItemList[cItemID]->m_sSpriteFrame;
		m_stDialogBoxInfo[27].sV3 = 1;
		m_stDialogBoxInfo[27].sV4 = m_pItemList[cItemID]->m_cItemColor;
		m_stDialogBoxInfo[27].sView = cItemID;*/
		if (m_stDialogBoxExchangeInfo[0].sV1 == -1)			m_stDialogBoxExchangeInfo[0].sItemID = cItemID;
		else if (m_stDialogBoxExchangeInfo[1].sV1 == -1)	m_stDialogBoxExchangeInfo[1].sItemID = cItemID;
		else if (m_stDialogBoxExchangeInfo[2].sV1 == -1)	m_stDialogBoxExchangeInfo[2].sItemID = cItemID;
		else if (m_stDialogBoxExchangeInfo[3].sV1 == -1)	m_stDialogBoxExchangeInfo[3].sItemID = cItemID;
		else return; // Impossible case, tested at function beginning
		m_bIsItemDisabled[cItemID] = TRUE;
		bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETEXCHANGEITEM, NULL, cItemID, 1, NULL, NULL);
//	   :bSendCommand(DWORD dwMsgID,        WORD wCommand,             char cDir, int iV1, int iV2, int iV3, char * pString, int iV4)
		return;
	}
}
/*********************************************************************************************************************
**  void CGame::DlgBoxClick_Exchange(short msX, short msY)		(snoopy)											**
**  description			:: modifyed for MultiTrade																	**
**********************************************************************************************************************/
void CGame::DlgBoxClick_Exchange(short msX, short msY)
{short sX, sY;
	sX = m_stDialogBoxInfo[27].sX ;
	sY = m_stDialogBoxInfo[27].sY ;
	switch (m_stDialogBoxInfo[27].cMode) {
	case 1: // Not yet confirmed the exchange
		if ((msX >= sX + 220) && (msX <= sX + 220 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)) // Exchange
		{	if ( (m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
			{	/*bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CONFIRMEXCHANGEITEM, NULL
					, m_stDialogBoxExchangeInfo[0].sV1 // ItemID; inutilisé par serveur
					, m_stDialogBoxExchangeInfo[0].sV3 // Amount; inutilisé par serveur
					, NULL, NULL);	*/
				PlaySound('E', 14, 5);
				m_stDialogBoxInfo[27].cMode = 2;
				// Show confirmation Diag instead.
				EnableDialogBox(41, NULL, NULL, NULL);
				m_stDialogBoxInfo[41].cMode = 1;
			}
			return;
		}
		if (   (msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)
			&& (m_bIsDialogEnabled[41] == FALSE)) // Cancel only possible if confirmation is not activated
		{	DisableDialogBox(27);
			DisableDialogBox(22);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, NULL, NULL, NULL, NULL, NULL);
			PlaySound('E', 14, 5);
			return;
		}
		break;

	case 2: // Someone already confirmed the exchange
	/*	if ((msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY))  // Cancel
		{	DisableDialogBox(27);
			DisableDialogBox(22);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, NULL, NULL, NULL, NULL, NULL);
			PlaySound('E', 14, 5);
			return;
		}*/
		break;
	}
}
/*********************************************************************************************************************
**  void CGame::DlgBoxClick_ConfirmExchange(short msX, short msY)		(snoopy)									**
**  description			:: click on confirmation diag																**
**********************************************************************************************************************/
void CGame::DlgBoxClick_ConfirmExchange(short msX, short msY)
{short sX, sY;
	sX = m_stDialogBoxInfo[41].sX ;
	sY = m_stDialogBoxInfo[41].sY ;

	switch (m_stDialogBoxInfo[41].cMode) {
	case 1: // Not yet confirmed the exchange
		// yes
		if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
		{	if ( (m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
			{	bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CONFIRMEXCHANGEITEM, NULL
					, m_stDialogBoxExchangeInfo[0].sV1 // ItemID; inutilisé par serveur
					, m_stDialogBoxExchangeInfo[0].sV3 // Amount; inutilisé par serveur
					, NULL, NULL);
				PlaySound('E', 14, 5);
				m_stDialogBoxInfo[27].cMode = 2;
				m_stDialogBoxInfo[41].cMode = 2;
			}
			return;
		}
		// No
		if ((msX >= sX + 170 ) && (msX <= sX + 170 + DEF_BTNSZX ) && (msY >= sY + 55 ) && (msY <= sY + 55 + DEF_BTNSZY))
		{	DisableDialogBox(41);
			DisableDialogBox(27);
			DisableDialogBox(22);
			bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, NULL, NULL, NULL, NULL, NULL);
			PlaySound('E', 14, 5);
			return;
		}
		break;
	case 2: // waiting for other side to confirm
		break;
	}
}

void CGame::DlgBoxClick_Quest(int msX, int msY)
{
 short sX, sY;

	sX = m_stDialogBoxInfo[28].sX;
	sY = m_stDialogBoxInfo[28].sY;

	if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) {
		DisableDialogBox(28);
		PlaySound('E', 14, 5);
	}
}

int CGame::_iGetBankItemCount()
{
 int i, iCnt;

	iCnt = 0;
	for (i = 0; i < DEF_MAXBANKITEMS; i++)
		if (m_pBankList[i] != NULL) iCnt++;

	return iCnt;
}

BOOL CGame::_bDecodeBuildItemContents()
{char cFileName[255], cTemp[255];
 HANDLE hFile;
 FILE * pFile;
 DWORD  dwFileSize;
 char * pBuffer;
 BOOL   bRet;
 int    i;

	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
	if (m_pBuildItemList[i] != NULL)
	{	delete m_pBuildItemList[i];
		m_pBuildItemList[i] = NULL;
	}

	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cFileName, sizeof(cFileName));

	strcpy(cTemp, "BItemcfg");
	strcat(cFileName, "contents");
	strcat(cFileName, "\\");
	strcat(cFileName, "\\");
	strcat(cFileName, cTemp);
	strcat(cFileName, ".txt");

	hFile = CreateFile(cFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFileName, "rt");
	if (pFile == NULL) return FALSE;
	else
	{	pBuffer = new char[dwFileSize+1];
		ZeroMemory(pBuffer, dwFileSize+1);
		fread(pBuffer, dwFileSize, 1, pFile);
		bRet = __bDecodeBuildItemContents(pBuffer);
		delete[] pBuffer;
	}
	fclose(pFile);
	return bRet;
}

BOOL CGame::_bCheckBuildItemStatus()
{int iIndex, i, j, iMatch, iCount;
 char cTempName[21];
 int  iItemCount[DEF_MAXITEMS];

	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
	if (m_pDispBuildItemList[i] != NULL)
	{	delete m_pDispBuildItemList[i];
		m_pDispBuildItemList[i] = NULL;
	}
	iIndex = 0;
	for (i = 0; i < DEF_MAXBUILDITEMS; i++)
	if (m_pBuildItemList[i] != NULL)
	{	// Skill-Limit
		if (m_cSkillMastery[13] >= m_pBuildItemList[i]->m_iSkillLimit)
		{	iMatch = 0;
			m_pDispBuildItemList[iIndex] = new class CBuildItem;
			memcpy(m_pDispBuildItemList[iIndex]->m_cName, m_pBuildItemList[i]->m_cName, 20);

			memcpy(m_pDispBuildItemList[iIndex]->m_cElementName1, m_pBuildItemList[i]->m_cElementName1, 20);
			memcpy(m_pDispBuildItemList[iIndex]->m_cElementName2, m_pBuildItemList[i]->m_cElementName2, 20);
			memcpy(m_pDispBuildItemList[iIndex]->m_cElementName3, m_pBuildItemList[i]->m_cElementName3, 20);
			memcpy(m_pDispBuildItemList[iIndex]->m_cElementName4, m_pBuildItemList[i]->m_cElementName4, 20);
			memcpy(m_pDispBuildItemList[iIndex]->m_cElementName5, m_pBuildItemList[i]->m_cElementName5, 20);
			memcpy(m_pDispBuildItemList[iIndex]->m_cElementName6, m_pBuildItemList[i]->m_cElementName6, 20);

			m_pDispBuildItemList[iIndex]->m_iElementCount[1] = m_pBuildItemList[i]->m_iElementCount[1];
			m_pDispBuildItemList[iIndex]->m_iElementCount[2] = m_pBuildItemList[i]->m_iElementCount[2];
			m_pDispBuildItemList[iIndex]->m_iElementCount[3] = m_pBuildItemList[i]->m_iElementCount[3];
			m_pDispBuildItemList[iIndex]->m_iElementCount[4] = m_pBuildItemList[i]->m_iElementCount[4];
			m_pDispBuildItemList[iIndex]->m_iElementCount[5] = m_pBuildItemList[i]->m_iElementCount[5];
			m_pDispBuildItemList[iIndex]->m_iElementCount[6] = m_pBuildItemList[i]->m_iElementCount[6];

			m_pDispBuildItemList[iIndex]->m_iSprH       = m_pBuildItemList[i]->m_iSprH;
			m_pDispBuildItemList[iIndex]->m_iSprFrame   = m_pBuildItemList[i]->m_iSprFrame;
			m_pDispBuildItemList[iIndex]->m_iMaxSkill   = m_pBuildItemList[i]->m_iMaxSkill;
			m_pDispBuildItemList[iIndex]->m_iSkillLimit = m_pBuildItemList[i]->m_iSkillLimit;

			// ItemCount
			for (j = 0; j < DEF_MAXITEMS; j++)
			if (m_pItemList[j] != NULL)
				 iItemCount[j] = m_pItemList[j]->m_dwCount;
			else iItemCount[j] = 0;

			// Element1
			ZeroMemory(cTempName, sizeof(cTempName));
			memcpy(cTempName, m_pBuildItemList[i]->m_cElementName1, 20);
			iCount = m_pBuildItemList[i]->m_iElementCount[1];
			if (iCount == 0) iMatch++;
			else
			{	for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_pItemList[j] != NULL) {
					if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (DWORD)(iCount)) &&
						(iItemCount[j] > 0))
					{	iMatch++;
						m_pDispBuildItemList[iIndex]->m_bElementFlag[1] = TRUE;
						iItemCount[j] -= iCount;
						goto CBIS_STEP2;
			}	}	}

CBIS_STEP2:;
			// Element2
			ZeroMemory(cTempName, sizeof(cTempName));
			memcpy(cTempName, m_pBuildItemList[i]->m_cElementName2, 20);
			iCount = m_pBuildItemList[i]->m_iElementCount[2];
			if (iCount == 0) iMatch++;
			else
			{	for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_pItemList[j] != NULL)
				{	if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (DWORD)(iCount)) &&
						(iItemCount[j] > 0))
					{	iMatch++;
						m_pDispBuildItemList[iIndex]->m_bElementFlag[2] = TRUE;
						iItemCount[j] -= iCount;
						goto CBIS_STEP3;
			}	}	}

CBIS_STEP3:;
			// Element3
			ZeroMemory(cTempName, sizeof(cTempName));
			memcpy(cTempName, m_pBuildItemList[i]->m_cElementName3, 20);
			iCount = m_pBuildItemList[i]->m_iElementCount[3];
			if (iCount == 0) iMatch++;
			else
			{	for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_pItemList[j] != NULL)
				{	if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (DWORD)(iCount)) &&
						(iItemCount[j] > 0))
					{	iMatch++;
						m_pDispBuildItemList[iIndex]->m_bElementFlag[3] = TRUE;
						iItemCount[j] -= iCount;
						goto CBIS_STEP4;
			}	}	}

CBIS_STEP4:;
		    // Element4 °Ë»ç
			ZeroMemory(cTempName, sizeof(cTempName));
			memcpy(cTempName, m_pBuildItemList[i]->m_cElementName4, 20);
			iCount = m_pBuildItemList[i]->m_iElementCount[4];
			if (iCount == 0) iMatch++;
			else
			{	for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_pItemList[j] != NULL)
				{	if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (DWORD)(iCount)) &&
						(iItemCount[j] > 0))
					{	iMatch++;
						m_pDispBuildItemList[iIndex]->m_bElementFlag[4] = TRUE;
						iItemCount[j] -= iCount;
						goto CBIS_STEP5;
			}	}	}

CBIS_STEP5:;

			// Element5
			ZeroMemory(cTempName, sizeof(cTempName));
			memcpy(cTempName, m_pBuildItemList[i]->m_cElementName5, 20);
			iCount = m_pBuildItemList[i]->m_iElementCount[5];
			if (iCount == 0) iMatch++;
			else
			{	for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_pItemList[j] != NULL)
				{	if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (DWORD)(iCount)) &&
						(iItemCount[j] > 0))
					{	iMatch++;
						m_pDispBuildItemList[iIndex]->m_bElementFlag[5] = TRUE;
						iItemCount[j] -= iCount;
						goto CBIS_STEP6;
			}	}	}

CBIS_STEP6:;

			// Element6
			ZeroMemory(cTempName, sizeof(cTempName));
			memcpy(cTempName, m_pBuildItemList[i]->m_cElementName6, 20);
			iCount = m_pBuildItemList[i]->m_iElementCount[6];
			if (iCount == 0) iMatch++;
			else
			{	for (j = 0; j < DEF_MAXITEMS; j++)
				if (m_pItemList[j] != NULL)
				{	if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (DWORD)(iCount)) &&
						(iItemCount[j] > 0))
					{	iMatch++;
						m_pDispBuildItemList[iIndex]->m_bElementFlag[6] = TRUE;
						iItemCount[j] -= iCount;
						goto CBIS_STEP7;
			}	}	}

CBIS_STEP7:;

			if (iMatch == 6) m_pDispBuildItemList[iIndex]->m_bBuildEnabled = TRUE;
			iIndex++;
	}	}
	return TRUE;
}

BOOL CGame::_ItemDropHistory(char * ItemName)
{BOOL bFlag = FALSE;
	if (m_iItemDropCnt == 0 )
	{	strcpy(m_cItemDrop[m_iItemDropCnt], ItemName);
		m_iItemDropCnt++;
		return TRUE;
	}
	if ( (1 <= m_iItemDropCnt) && (20 >= m_iItemDropCnt) )
	{	for (int i = 0; i < m_iItemDropCnt; i++)
		{	if (strcmp(m_cItemDrop[i], ItemName) == 0)
			{	bFlag = TRUE;
	            break;
		}	}
		if (bFlag)
		{	if (m_bItemDrop)
				return FALSE;
			else
				return TRUE;
		}

		if( 20 < m_iItemDropCnt )
		{	for (int i = 0; i < m_iItemDropCnt ; i++)
            strcpy(m_cItemDrop[i-1], ItemName);
			strcpy(m_cItemDrop[20], ItemName);
			m_iItemDropCnt = 21;
		}else
		{	strcpy(m_cItemDrop[m_iItemDropCnt], ItemName);
			m_iItemDropCnt++;
	}	}
	return TRUE;
}


BOOL CGame::__bDecodeBuildItemContents(char *pBuffer)
{char * pContents, * token;
 char seps[] = "= ,\t\n";
 char cReadModeA = 0;
 char cReadModeB = 0;
 int  iIndex = 0;
 class CStrTok * pStrTok;
	pContents = pBuffer;
	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();

	while( token != NULL )
	{	if (cReadModeA != 0)
		{	switch (cReadModeA) {
			case 1:
				switch (cReadModeB) {
				case 1:
					ZeroMemory(m_pBuildItemList[iIndex]->m_cName, sizeof(m_pBuildItemList[iIndex]->m_cName));
					memcpy(m_pBuildItemList[iIndex]->m_cName, token, strlen(token));
					cReadModeB = 2;
					break;
				case 2:
					m_pBuildItemList[iIndex]->m_iSkillLimit = atoi(token);
					cReadModeB = 3;
					break;
				case 3: // m_cElementName1
					ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName1, sizeof(m_pBuildItemList[iIndex]->m_cElementName1));
					memcpy(m_pBuildItemList[iIndex]->m_cElementName1, token, strlen(token));
					cReadModeB = 4;
					break;
				case 4: // m_iElementCount1
					m_pBuildItemList[iIndex]->m_iElementCount[1] = atoi(token);
					cReadModeB = 5;
					break;
				case 5: // m_cElementName2
					ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName2, sizeof(m_pBuildItemList[iIndex]->m_cElementName2));
					memcpy(m_pBuildItemList[iIndex]->m_cElementName2, token, strlen(token));
					cReadModeB = 6;
					break;
				case 6: // m_iElementCount2
					m_pBuildItemList[iIndex]->m_iElementCount[2] = atoi(token);
					cReadModeB = 7;
					break;
				case 7: // m_cElementName3
					ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName3, sizeof(m_pBuildItemList[iIndex]->m_cElementName3));
					memcpy(m_pBuildItemList[iIndex]->m_cElementName3, token, strlen(token));
					cReadModeB = 8;
					break;
				case 8: // m_iElementCount3
					m_pBuildItemList[iIndex]->m_iElementCount[3] = atoi(token);
					cReadModeB = 9;
					break;
				case 9: // m_cElementName4
					ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName4, sizeof(m_pBuildItemList[iIndex]->m_cElementName4));
					memcpy(m_pBuildItemList[iIndex]->m_cElementName4, token, strlen(token));
					cReadModeB = 10;
					break;
				case 10: // m_iElementCount4
					m_pBuildItemList[iIndex]->m_iElementCount[4] = atoi(token);
					cReadModeB = 11;
					break;
				case 11: // m_cElementName5
					ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName5, sizeof(m_pBuildItemList[iIndex]->m_cElementName5));
					memcpy(m_pBuildItemList[iIndex]->m_cElementName5, token, strlen(token));
					cReadModeB = 12;
					break;
				case 12: // m_iElementCount5
					m_pBuildItemList[iIndex]->m_iElementCount[5] = atoi(token);
					cReadModeB = 13;
					break;
				case 13: // m_cElementName6
					ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName6, sizeof(m_pBuildItemList[iIndex]->m_cElementName6));
					memcpy(m_pBuildItemList[iIndex]->m_cElementName6, token, strlen(token));
					cReadModeB = 14;
					break;
				case 14: // m_iElementCount6
					m_pBuildItemList[iIndex]->m_iElementCount[6] = atoi(token);
					cReadModeB = 15;
					break;

				case 15:
					m_pBuildItemList[iIndex]->m_iSprH = atoi(token);
					cReadModeB = 16;
					break;

				case 16:
					m_pBuildItemList[iIndex]->m_iSprFrame = atoi(token);
					cReadModeB = 17;
					break;

				case 17:
					m_pBuildItemList[iIndex]->m_iMaxSkill = atoi(token);

					cReadModeA = 0;
					cReadModeB = 0;
					iIndex++;
					break;
				}
				break;

			default:
				break;
			}
		}else
		{	if (memcmp(token, "BuildItem", 9) == 0)
			{	cReadModeA = 1;
				cReadModeB = 1;
				m_pBuildItemList[iIndex] = new class CBuildItem;
		}	}
		token = pStrTok->pGet();
	}
	delete pStrTok;
	if ((cReadModeA != 0) || (cReadModeB != 0)) return FALSE;
	return TRUE;
}


BOOL CGame::_bCheckCurrentBuildItemStatus()
{
 int i, iCount2, iMatch, iIndex, iItemIndex[7];
 int iCount;
 int iItemCount[7];
 char cTempName[21];
 BOOL bItemFlag[7];

	iIndex = m_stDialogBoxInfo[26].cStr[0];

	if (m_pBuildItemList[iIndex] == NULL) return FALSE;

	iItemIndex[1] = m_stDialogBoxInfo[26].sV1;
	iItemIndex[2] = m_stDialogBoxInfo[26].sV2;
	iItemIndex[3] = m_stDialogBoxInfo[26].sV3;
	iItemIndex[4] = m_stDialogBoxInfo[26].sV4;
	iItemIndex[5] = m_stDialogBoxInfo[26].sV5;
	iItemIndex[6] = m_stDialogBoxInfo[26].sV6;

	for (i = 1; i <= 6; i++)
	if (iItemIndex[i] != -1)
		 iItemCount[i] = m_pItemList[iItemIndex[i]]->m_dwCount;
	else iItemCount[i] = 0;
	iMatch = 0;
	for (i = 1; i <= 6; i++) bItemFlag[i] = FALSE;

	// Element1
	ZeroMemory(cTempName, sizeof(cTempName));
	memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName1, 20);
	iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[1];
	if (iCount == 0) iMatch++;
	else
	{	for (i = 1; i <= 6; i++)
		{	if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
				(m_pItemList[iItemIndex[i]]->m_dwCount >= (DWORD)(iCount)) &&
				(iItemCount[i] > 0) && (bItemFlag[i] == FALSE))
			{	iMatch++;
				iItemCount[i] -= iCount;
				bItemFlag[i] = TRUE;
				goto CCBIS_STEP2;
	}	}	}

CCBIS_STEP2:;

	// Element2
	ZeroMemory(cTempName, sizeof(cTempName));
	memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName2, 20);
	iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[2];
	if (iCount == 0) iMatch++;
	else
	{	for (i = 1; i <= 6; i++)
		{	if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
				(m_pItemList[iItemIndex[i]]->m_dwCount >= (DWORD)(iCount)) &&
				(iItemCount[i] > 0) && (bItemFlag[i] == FALSE))
			{	iMatch++;
				iItemCount[i] -= iCount;
				bItemFlag[i] = TRUE;
				goto CCBIS_STEP3;
	}	}	}

CCBIS_STEP3:;


	// Element3
	ZeroMemory(cTempName, sizeof(cTempName));
	memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName3, 20);
	iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[3];
	if (iCount == 0) iMatch++;
	else
	{	for (i = 1; i <= 6; i++)
		{	if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
				(m_pItemList[iItemIndex[i]]->m_dwCount >= (DWORD)(iCount)) &&
				(iItemCount[i] > 0) && (bItemFlag[i] == FALSE))
			{	iMatch++;
				iItemCount[i] -= iCount;
				bItemFlag[i] = TRUE;
				goto CCBIS_STEP4;
	}	}	}

CCBIS_STEP4:;

	// Element4
	ZeroMemory(cTempName, sizeof(cTempName));
	memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName4, 20);
	iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[4];
	if (iCount == 0) iMatch++;
	else
	{	for (i = 1; i <= 6; i++)
		{	if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
				(m_pItemList[iItemIndex[i]]->m_dwCount >= (DWORD)(iCount)) &&
				(iItemCount[i] > 0) && (bItemFlag[i] == FALSE))
			{	iMatch++;
				iItemCount[i] -= iCount;
				bItemFlag[i] = TRUE;
				goto CCBIS_STEP5;
	}	}	}

CCBIS_STEP5:;

	// Element5
	ZeroMemory(cTempName, sizeof(cTempName));
	memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName5, 20);
	iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[5];
	if (iCount == 0) iMatch++;
	else
	{	for (i = 1; i <= 6; i++)
		{	if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
				(m_pItemList[iItemIndex[i]]->m_dwCount >= (DWORD)(iCount)) &&
				(iItemCount[i] > 0) && (bItemFlag[i] == FALSE))
			{	iMatch++;
				iItemCount[i] -= iCount;
				bItemFlag[i] = TRUE;
				goto CCBIS_STEP6;
	}	}	}

CCBIS_STEP6:;

	// Element6
	ZeroMemory(cTempName, sizeof(cTempName));
	memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName6, 20);
	iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[6];
	if (iCount == 0) iMatch++;
	else
	{	for (i = 1; i <= 6; i++)
		{	if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
				(m_pItemList[iItemIndex[i]]->m_dwCount >= (DWORD)(iCount)) &&
				(iItemCount[i] > 0) && (bItemFlag[i] == FALSE))
			{	iMatch++;
				iItemCount[i] -= iCount;
				bItemFlag[i] = TRUE;
				goto CCBIS_STEP7;
	}	}	}

CCBIS_STEP7:;

	iCount = 0;
	for (i = 1; i <= 6; i++)
	if (m_pDispBuildItemList[iIndex]->m_iElementCount[i] != 0) iCount++;
	iCount2 = 0;
	for (i = 1; i <= 6; i++)
	if (iItemIndex[i] != -1) iCount2++;
	if ((iMatch == 6) && (iCount == iCount2)) return TRUE;
	return FALSE;
}

void CGame::NoticementHandler(char * pData)
{
 char * cp;
 FILE * pFile;
 WORD * wp;
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	switch (*wp) {
	case DEF_MSGTYPE_CONFIRM:
		break;
	case DEF_MSGTYPE_REJECT:
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		pFile = fopen("contents\\contents1000.txt", "wt");
		if (pFile == NULL) return;
		fwrite(cp, strlen(cp), 1, pFile);
		fclose(pFile);
		m_stDialogBoxInfo[18].sX  =  20;
		m_stDialogBoxInfo[18].sY  =  65;
		EnableDialogBox(18, 1000, NULL, NULL);
		break;
	}
	AddEventList("Press F1 for news and help.", 10);
	if (m_iLevel < 42) EnableDialogBox(35, NULL, NULL, NULL);

}

int CGame::_iGetFOE(int iStatus)
{	BOOL bPK, bCitizen, bAresden, bHunter;
	if( m_iPKCount != 0 ) return -1;
	//	CLEROTH			0x00000000 status is int NOT short ( 3.51 )
	if( iStatus & 0x80000000 ) bPK = TRUE;
	else bPK = FALSE;
	if( iStatus & 0x40000000 ) bCitizen = TRUE;
	else bCitizen = FALSE;
	if( iStatus & 0x20000000 ) bAresden = TRUE;
	else bAresden = FALSE;
	if( iStatus & 0x10000000 ) bHunter = TRUE;
	else bHunter = FALSE;
	if( bPK == TRUE ) return -2;
	if( bCitizen == FALSE ) return 0;
	if( m_bCitizen == FALSE ) return 0;
	if( (m_bAresden == TRUE) && (bAresden == TRUE) ) return 1;
	if( (m_bAresden == FALSE) && (bAresden == FALSE) ) return 1;
	if( m_bIsCrusadeMode == TRUE ) return -1;
	else
	{	if( (m_bHunter == FALSE) && (bHunter == FALSE) ) return -1;
		else return 0;
	}
}

void CGame::_SetIlusionEffect(int iOwnerH)
{
 char cDir;

	m_iIlusionOwnerH = iOwnerH;

	ZeroMemory(m_cName_IE, sizeof(m_cName_IE));
	m_pMapData->GetOwnerStatusByObjectID(iOwnerH, &m_cIlusionOwnerType, &cDir, &m_sAppr1_IE, &m_sAppr2_IE, &m_sAppr3_IE, &m_sAppr4_IE, &m_iStatus_IE, &m_iApprColor_IE, m_cName_IE);
}

void CGame::ResponsePanningHandler(char *pData)
{
 char * cp, cDir;
 short * sp, sX, sY;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE +2);

	sp = (short *)cp;
	sX = *sp;
	cp += 2;

	sp = (short *)cp;
	sY = *sp;
	cp += 2;

	cDir = *cp;
	cp++;

	switch (cDir) {
	case 1: m_sViewDstY -= 32; m_sPlayerY--; break;
	case 2: m_sViewDstY -= 32; m_sPlayerY--; m_sViewDstX += 32; m_sPlayerX++; break;
	case 3: m_sViewDstX += 32; m_sPlayerX++; break;
	case 4: m_sViewDstY += 32; m_sPlayerY++; m_sViewDstX += 32; m_sPlayerX++; break;
	case 5: m_sViewDstY += 32; m_sPlayerY++;break;
	case 6: m_sViewDstY += 32; m_sPlayerY++; m_sViewDstX -= 32; m_sPlayerX--; break;
	case 7: m_sViewDstX -= 32; m_sPlayerX--; break;
	case 8: m_sViewDstY -= 32; m_sPlayerY--; m_sViewDstX -= 32; m_sPlayerX--; break;
	}

	m_pMapData->ShiftMapData(cDir);
	_ReadMapData(sX, sY, cp);

	m_bIsRedrawPDBGS = TRUE;

	m_bIsObserverCommanded = FALSE;
}

BOOL CGame::bReadItemNameConfigFile()
{
 FILE * pFile;
 HANDLE hFile;
 DWORD  dwFileSize;
 char * cp, * token, cReadModeA, cReadModeB;
 char seps[] = "=\n";
 int iIndex;

	cReadModeA = 0;
	cReadModeB = 0;
	iIndex = 0;

	hFile = CreateFile("contents\\ItemName.cfg", GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
	pFile = fopen("contents\\ItemName.cfg", "rt");
	if (pFile == NULL) return FALSE;
	else {
		cp = new char[dwFileSize+2];
		ZeroMemory(cp, dwFileSize+2);
		fread(cp, dwFileSize, 1, pFile);

		token = strtok( cp, seps );
		while( token != NULL )   {

			if (cReadModeA != 0) {
				switch (cReadModeA) {
				case 1:
					switch (cReadModeB) {
					case 1:
						m_pItemNameList[iIndex] = new class CItemName;
						strcpy(m_pItemNameList[iIndex]->m_cOriginName, token);
						cReadModeB = 2;
						break;

					case 2:
						strcpy(m_pItemNameList[iIndex]->m_cName, token);
						cReadModeA = 0;
						cReadModeB = 0;
						iIndex++;
						break;
					}
				}
			}
			else {
				if (memcmp(token, "Item", 4) == 0) {
					cReadModeA = 1;
					cReadModeB = 1;
				}
			}
			token = strtok( NULL, seps );
		}
		delete[] cp;
	}
	if (pFile != NULL) fclose(pFile);

	return TRUE;
}

void CGame::DrawDialogBox_Map()
{
 short sX, sY;
 DWORD dwTime = m_dwCurTime;
 double dV1, dV2, dV3;
 int    tX, tY, szX, szY, dX, dY;

	sX = m_stDialogBoxInfo[22].sX;
	sY = m_stDialogBoxInfo[22].sY;

	szX = 0;
	szY = 0;

	switch (m_stDialogBoxInfo[22].sV1) {
	case 1:
		switch (m_stDialogBoxInfo[22].sV2) {
		case 0: // aresden
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 19;
			dY = 20;
			szX = 260;
			szY = 260;
			break;

		case 1: // elvine
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 20;
			dY = 18;
			szX = 260;
			szY = 260;
			break;

		case 2: // middleland
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 11;
			dY = 31;
			szX = 280;
			szY = 253;
			break;

		case 3: // default
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 52;
			dY = 42;
			szX = 200;
			szY = 200;
			break;

		case 4: // aresden ¸
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 5: // elvine ¸
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 6: // aresden
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;

		case 7: // elvine
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 40;
			dY = 40;
			szX = 220;
			szY = 220;
			break;
		case 8: // aresden
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutTransSprite2(sX, sY, 0, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutSpriteFast(sX, sY, 0, dwTime);
			dX = 40;
			dY = 32;
			szX = 220;
			szY = 220;
			break;

		case 9: // elvine
			if (m_bDialogTrans)
				 m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutTransSprite2(sX, sY, 1, dwTime);
			else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutSpriteFast(sX, sY, 1, dwTime);
			dX = 40;
			dY = 38;
			szX = 220;
			szY = 220;
			break;

		}

		dV1 = (double)m_pMapData->m_sMapSizeX;
		dV2 = (double)m_sPlayerX;
		dV3 = (dV2*(double)szX)/dV1;
		tX  = (int)dV3 +dX;

		dV1 = (double)m_pMapData->m_sMapSizeY;
		if( dV1 == 752 ) dV1 = 680;
		dV2 = (double)m_sPlayerY;
		dV3 = (dV2*(double)szY)/dV1;
		tY  = (int)dV3 +dY;


		//m_pSprite[DEF_SPRID_INTERFACE_MAPS1]->PutSpriteFast(sX +tX, sY +tY, 4, dwTime);
		DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX +tX, sY +tY, 43);
		wsprintf(G_cTxt, "%d,%d", m_sPlayerX, m_sPlayerY);
		PutString_SprFont3(sX + 10 +tX -5, sY + 10 + tY -6, G_cTxt, m_wR[13]*4, m_wG[13]*4, m_wB[13]*4, FALSE, 2);
		break;
   	}
}
/*********************************************************************************************************************
**  void CGame::NotifyMsg_SetExchangeItem(char *pData)		(snoopy)												**
**  description			:: Recieve a msg from gserver and sets the item												**
**********************************************************************************************************************/
void CGame::NotifyMsg_SetExchangeItem(char *pData)
{short * sp, sDir, sSprite, sSpriteFrame, sCurLife, sMaxLife, sPerformance;
 int * ip, iAmount, i;
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

	if (sDir >= 1000)  // Set the item I want to exchange
	{	i = 0;
		while (m_stDialogBoxExchangeInfo[i].sV1 !=-1)
		{	i++;
			if (i>=4) return; // Error situation
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
	//if (i<4) m_stDialogBoxExchangeInfo[i].sItemID = sDir -1000;
}

void CGame::NotifyMsg_DismissGuildApprove(char * pData)
{
 char * cp, cName[24], cLocation[12];
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
	_PutGuildOperationList(cName, 5);
}

void CGame::NotifyMsg_DismissGuildReject(char * pData)
{char * cp, cName[21];
	ZeroMemory(cName, sizeof(cName));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 20);
	cp += 20;
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 6);
}

void CGame::NotifyMsg_DownSkillIndexSet(char *pData)
{
 WORD * wp;
 short sSkillIndex;
 char * cp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	sSkillIndex = (short)*wp;
	cp += 2;
	m_iDownSkillIndex = sSkillIndex;
	m_stDialogBoxInfo[15].bFlag = FALSE;
}

void CGame::NotifyMsg_FishChance(char * pData)
{
 int iFishChance;
 char * cp;
 WORD * wp;
	cp = (char *)(pData	+ DEF_INDEX2_MSGTYPE + 2);
	wp = (WORD *)cp;
	iFishChance = (int)*wp;
	cp += 2;
	m_stDialogBoxInfo[24].sV1 = iFishChance;
}

void CGame::NotifyMsg_GuildDisbanded(char * pData)
{char * cp, cName[24], cLocation[12];
	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cLocation, sizeof(cLocation));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 20);
	cp += 20;
	memcpy(cLocation, cp, 10);
	cp += 10;
	m_Misc.ReplaceString(cName, '_', ' ');
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 7);
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
}

void CGame::NotifyMsg_WhetherChange(char * pData)
{
 char * cp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	m_cWhetherStatus = *cp;
	cp++;

	if (m_cWhetherStatus != NULL)
		 SetWhetherStatus(TRUE,  m_cWhetherStatus);
	else SetWhetherStatus(FALSE, NULL);
}

void CGame::NotifyMsg_TimeChange(char * pData)
{ char * cp;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	G_cSpriteAlphaDegree = *cp;
	switch (G_cSpriteAlphaDegree) {
	case 1:	m_bIsXmas = FALSE; PlaySound('E', 32, 0); break;
	case 2: m_bIsXmas = FALSE; PlaySound('E', 31, 0); break;
	case 3: // Snoopy Special night with chrismas bulbs
		if (m_cWhetherEffectType >3) m_bIsXmas = TRUE;
		else m_bIsXmas = FALSE;
		PlaySound('E', 31, 0);
		G_cSpriteAlphaDegree = 2;break;
	}
	m_cGameModeCount = 1;
	m_bIsRedrawPDBGS = TRUE;
}

void CGame::NotifyMsg_RepairItemPrice(char * pData)
{char * cp, cName[21];
 DWORD * dwp, wV1, wV2, wV3, wV4;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	dwp = (DWORD *)cp;
  	wV1 = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
  	wV2 = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
  	wV3 = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
  	wV4 = *dwp;
	cp += 4;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;
	EnableDialogBox(23, 2, wV1, wV2);
	m_stDialogBoxInfo[23].sV3 = wV3;
}

void CGame::NotifyMsg_SellItemPrice(char * pData)
{char * cp, cName[21];
 DWORD * dwp, wV1, wV2, wV3, wV4;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	dwp = (DWORD *)cp;
  	wV1 = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
  	wV2 = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
  	wV3 = *dwp;
	cp += 4;
	dwp = (DWORD *)cp;
  	wV4 = *dwp;
	cp += 4;
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 20);
	cp += 20;
	EnableDialogBox(23, 1, wV1, wV2);
	m_stDialogBoxInfo[23].sV3 = wV3;
	m_stDialogBoxInfo[23].sV4 = wV4;
}

void CGame::NotifyMsg_QueryDismissGuildPermission(char * pData)
{char * cp, cName[12];
	ZeroMemory(cName, sizeof(cName));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 10);
	cp += 10;
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 2);
}


void CGame::NotifyMsg_QueryJoinGuildPermission(char * pData)
{char * cp, cName[12];
	ZeroMemory(cName, sizeof(cName));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cName, cp, 10);
	cp += 10;
	EnableDialogBox(8, NULL, NULL, NULL);
	_PutGuildOperationList(cName, 1);
}