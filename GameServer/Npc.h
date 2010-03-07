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
