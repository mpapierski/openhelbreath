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
