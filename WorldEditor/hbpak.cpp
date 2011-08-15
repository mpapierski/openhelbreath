#include "hbpak.h"

HBPak::HBPak(QObject *parent) :
	QObject(parent)
{

}

bool HBPak::open(const QString& fileName)
{
	m_FileName = fileName;

	FILE * fin = fopen(fileName.toAscii(), "rb");
	char Sig[20];
	fread(&Sig, 1, 20, fin);
	qDebug() << Sig;
	if (strncmp(Sig, DEF_PAKSIG, strlen(DEF_PAKSIG)) == 0)
	{
		qDebug() << fileName << " is valid pak file.";
	}
	else
	{
		qDebug() << fileName << " is not valid pak file.";
		return false;
	}

	int SprCount;
	fread(&SprCount, 4, 1, fin);
	qDebug() << SprCount;

	struct
	{
	int Offset;
	int Unk;
	} Offsets[SprCount];

	fread(&Offsets, 8, SprCount, fin);

	for (int i = 0; i < SprCount; i++)
	{
		qDebug() << "Offsets[" << i << "] = (" << Offsets[i].Offset << "," << Offsets[i].Unk << ")";
	}
	fclose(fin);

	for (int i = 0; i < SprCount; i++)
	{
		Sprite Spr;
		int dwASDfileLoc;
		int dwASDfileSize;

		fin = fopen(fileName.toAscii(), "rb");
		fseek(fin, 24 + i * 8,SEEK_SET);
		fread(&dwASDfileLoc, 4, 1, fin);
		fread(&dwASDfileSize, 4, 1, fin);

		fseek(fin, dwASDfileLoc, SEEK_SET);
		char SigSpr[100];
		fread(&SigSpr, 1, 100, fin);
		if (strncmp(SigSpr, DEF_SPRSIG, strlen(DEF_SPRSIG)) != 0)
		{
			qDebug() << "Sprite " << i << "is not valid sprite.";
			continue;
		}

		int TotalFrame;
		fread(&TotalFrame, 4, 1, fin);

		for (int j = 0; j < TotalFrame; j++)
		{
			SpriteFrame Rect;
			fread(&Rect, 2, 6, fin);
			Spr.Frames.append(Rect);
		}

		int dwBitmapFileStartLoc = dwASDfileLoc  + (108 + (12*TotalFrame));
		int dwBitmapFileSize     = dwASDfileSize - (108 + (12*TotalFrame));

		fseek(fin, dwBitmapFileStartLoc, SEEK_SET);
		QByteArray BMPData(dwBitmapFileSize, 0);
		qDebug() << "BMP Size: " << dwBitmapFileSize;

		fread(BMPData.begin(), 1, dwBitmapFileSize, fin);
		Spr.setOffset(dwASDfileLoc);
		Spr.BMP.loadFromData(BMPData);
		m_Sprites.append(Spr);
		fclose(fin);
	}

	return true;
}
