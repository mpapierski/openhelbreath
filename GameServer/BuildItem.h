#ifndef BUILDITEM_H
#define BUILDITEM_H

#pragma pack(1)

class CBuildItem
{
	public:
		int m_iBuildItemID;
		char m_cName[30];
		int m_iSkillLimit;
		struct
		{
			int iItemID;
			int iItemCount;
			int iItemValue;
		} m_pItems[6];
		int m_iAverageValue;
		int m_iMaxSkill;
		int m_iAttribute;
		int m_iMaxValue;
};

#pragma pack()

#endif
