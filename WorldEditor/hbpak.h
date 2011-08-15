#ifndef HBPAK_H
#define HBPAK_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QImage>
#include <QList>
#include <QPainter>
#include <stdio.h>

#define DEF_PAKSIG "<Pak file header>"
#define DEF_SPRSIG "<Sprite File Header>"

typedef struct
{
    quint16 X;
    quint16 Y;
    quint16 Width;
    quint16 Height;
    qint16 FX;
    qint16 FY;
    qint16 Unk1;
    qint16 Unk2;
} SpriteFrame;

class Sprite
{
	private:
		quint32 m_Offset;

	public:

		Sprite() :
			m_Offset(-1)
		{
		}

		QList<SpriteFrame> Frames;
		QImage BMP;

		int framesCount() const
		{
			return Frames.count();
		}

		qint32 getBitmapSize();
		qint32 getFramesSize();

		void setOffset(quint32 offset) { m_Offset = offset; }
		quint32 offset() const { return m_Offset; }
};

class HBPak : public QObject
{
	Q_OBJECT
	private:
		QString m_FileName;
		QList<Sprite> m_Sprites;

	public:
		explicit HBPak(QObject *parent = 0);
		/**
		  * Open and read contents of Helbreath .pak file.
		  * @param fileName File path.
		  * @return Value indicating either success or failure.
		  */
		bool open(const QString& fileName);

		QList<Sprite>& sprites() { return m_Sprites; }

		/**
		  * Cut sprite `spriteID` on `frameID` and store it in sprite
		  * Eventually cache it sometimes.
		  * @param spriteID Sprite ID.
		  * @param frameID Frame ID.
		  * @param sprite Where to store sprite.
		  * @return In case of failure return logical value.
		  */
		bool getSprite(const quint32 spriteID, const quint32 frameID, QImage& sprite);

	signals:

	public slots:

};

#endif // HBPAK_H
