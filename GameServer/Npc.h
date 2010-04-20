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

#ifndef NPC_H
#define NPC_H

#pragma pack(1)
class CNpc
{
	public:
		char m_cName[30];
		short m_sType;
		short m_sHitDice;
		short m_sDefenseRatio;
		short m_sHitRatio;
		short m_sMinBravery;

		int m_iExpDice;

		short m_sAttackDiceThrow;
		short m_sAttackDiceRange;

		short m_sSize;
		short m_sSide;
		short m_sActionLimit;

		short m_sActionTime;
		short m_sResistMagic;
		short m_sMagicLevel;

		short m_sDayOfWeekLimit;
		short m_sChatMsgPresence;
		short m_sTargetSearchRange;

		int m_iRegenTime;

		short m_sAttribute;
		short m_sAbsDamage;
		short m_sMaxMana;
		short m_sMagicHitRatio;
		short m_sAttackRange;

		short m_sAreaSize;

		int m_iGoldRatio;
};

#pragma pack()

#endif
