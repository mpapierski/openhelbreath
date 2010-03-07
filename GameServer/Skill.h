#ifndef SKILL_H
#define SKILL_H

#pragma pack(1)
class CSkill
{
	public:
		int m_iSkillID;
		char m_cName[30];
		int m_iType;
		int m_iValue[6];
};
#pragma pack()

#endif
