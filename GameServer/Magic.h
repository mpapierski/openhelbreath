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
		int m_iValue1, m_iValue2, m_iValue3, 
		    m_iValue4, m_iValue6, m_iValue7,
		    m_iValue8, m_iValue9, m_iValue10,
		    m_iValue11, m_iValue12;
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
