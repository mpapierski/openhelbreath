#ifndef CHILDWIN_H
#define CHILDWIN_H

#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QCloseEvent>
#include <QBuffer>
#include <QImage>
#include <QFileDialog>

#include "GlobalDef.h"

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
public:
    Sprite() :
        Offset(-1)
    {
    }

    QList<SpriteFrame> Frames;
    QImage BMP;
    int framesCount() const
    {
        return Frames.count();
    }
    qint32 Offset;
    qint32 getBitmapSize();
    qint32 getFramesSize();
};

namespace Ui {
    class ChildWin;
}

class ChildWin : public QWidget {
    Q_OBJECT
public:
    ChildWin(QWidget *parent = 0);
    ~ChildWin();
    bool loadFromFile(QString fileName);
    bool saveToFile(QString fileName);
    void refresh();
    void refresh_title();
    void removeSprite(int SpriteID);
    void addSprite(QString FileName);

    inline bool isChanged() const
    {
        return Changed;
    }

    void setChanged(bool v)
    {
        Changed = v;
        refresh_title();
    }

    int getFrameID();
    int getSpriteID();

    QList<Sprite> Sprites;
    QString pakFileName;

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    Ui::ChildWin *ui;
    bool Changed;

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);
};

#endif // CHILDWIN_H
