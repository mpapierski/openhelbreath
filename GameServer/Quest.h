/*
 This file is part of OpenHelbreath.
 OpenHelbreath is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenHelbreath is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenHelbreath.  If not, see <http://www.gnu.org/licenses/>.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QUEST_H
#define QUEST_H

#pragma pack(1)
class CQuest
{
	public:
		int m_iQuestIndex;
		int m_iSide;
		int m_iType;
		int m_iTargetType;
		int m_iMaxCount;
		int m_iFrom;
		int m_iMinLevel;
		int m_iMaxLevel;
		int m_iRequiredSkillNum;
		int m_iRequiredSkillLevel;
		int m_iTimeLimit;
		int m_iAssignType;
		struct
		{
				int iType;
				int iAmount;
		} m_pReward[3];

		int m_iContribution;
		int m_iContributionLimit;

		int m_iResponseMode;
		char m_cTargetName[30];
		int m_iX;
		int m_iY;
		int m_iRange;
		int m_iQuestID;
		int m_iReqContribution;
};
#pragma pack()

#endif
