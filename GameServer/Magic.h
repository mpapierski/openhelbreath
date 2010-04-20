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

#ifndef MAGIC_H
#define MAGIC_H

#pragma pack(1)

class CMagic
{
	public:
		int m_iNum;
		char m_cName[30];
		int m_sType;
		int m_iDelayTime;
		int m_iLastTime;
		int m_iValue1, m_iValue2, m_iValue3, m_iValue4, m_iValue6, m_iValue7, m_iValue8, m_iValue9, m_iValue10, m_iValue11, m_iValue12;
		int m_iIntLimit;
		int m_iGoldCost;
		int m_iCategory;
		int m_iAttribute;

		int asdf;
		inline bool const bIsForSale()
		{
			return m_iGoldCost >= 0;
		}
};

#pragma pack()

#endif
