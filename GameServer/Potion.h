#ifndef POTION_H
#define POTION_H

#pragma pack(1)
class CPotion
{
	public:
		int m_iPotionID;
		char m_cName[30];
		struct
		{
			int iItemID;
			int iItemCount;
		} m_iItems[6];
		int m_iSkillLimit;
		int m_iDifficulty;
};
#pragma pack()

#endif
