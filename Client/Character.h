#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct
{
		char Name[10];
		char _Unused;
		short Appr1, Appr2, Appr3, Appr4;
		short Gender, Skin;
		unsigned int Level, Experience;
		short Strength, Vitality, Dexterity, Intelligence, Magic, Agility;
		short Year, Month, Day, Hour, Minute, Second;
		char MapLoc[10];
} CCharacter;

#endif // CHARACTER_H
