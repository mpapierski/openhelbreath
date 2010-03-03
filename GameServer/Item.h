#ifndef ITEM_H
#define ITEM_H

#pragma pack(1)
class CItem {
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
		unsigned char m_cApprValue;
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
