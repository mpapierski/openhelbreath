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

#ifndef ITEM_H
#define ITEM_H

#pragma pack(1)
class CItem
{
	public:
		int m_sIDnum;
		char m_cName[30];
		unsigned char m_cItemType;
		unsigned char m_cEquipPos;
		unsigned char m_sItemEffectType;
		unsigned char m_cItemEffectValue1;
		unsigned char m_cItemEffectValue2;
		unsigned char m_cItemEffectValue3;
		unsigned char m_cItemEffectValue4;
		unsigned char m_cItemEffectValue5;
		unsigned char m_cItemEffectValue6;
		short m_sMaxLifeSpan;
		unsigned char m_cSpecialEffect;
		unsigned char m_cSprite;
		unsigned char m_cSpriteFrame;
		int m_iPrice;
		short m_sWeight;
		short m_sApprValue;
		short m_sSpeed;
		short m_sLevel;
		char m_cGender;
		short m_sSpecialEffectValue1;
		short m_sSpecialEffectValue2;
		char m_cSkill;
		char m_cCategory;
		char m_cColor;

		inline bool const bIsForSale()
		{
			return m_iPrice <= 0;
		}
};

#pragma pack()

#endif
