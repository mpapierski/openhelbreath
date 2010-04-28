#include "childwin.h"
#include "ui_childwin.h"

ChildWin::ChildWin(QWidget *parent) :
    QWidget(parent), 
    ui(new Ui::ChildWin),
    Changed(false)
{
    ui->setupUi(this);
}

ChildWin::~ChildWin()
{
    delete ui;
}

void ChildWin::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool ChildWin::loadFromFile(QString fileName)
{
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
        Spr.Offset = dwASDfileLoc;
        Spr.BMP.loadFromData(BMPData);
        Sprites.append(Spr);
        fclose(fin);
    }
    this->pakFileName = fileName;
    refresh();

    return true;
}


void ChildWin::refresh()
{
    ui->treeWidget->clear();
    for (int i = 0; i < Sprites.count(); i++)
    {
        QTreeWidgetItem * Root = new QTreeWidgetItem(ui->treeWidget);
        Root->setText(0, QString().sprintf("%d", i));
        Root->setText(1, Sprites[i].Offset > -1 ? QString().sprintf("0x%08X", Sprites[i].Offset) : "?");
        for (int j = 0; j < Sprites[i].framesCount(); j++)
        {
            QTreeWidgetItem * Child = new QTreeWidgetItem(Root);

            Child->setText(0, QString().sprintf("%d", j));
            Child->setText(1, "");
        }
    }
    refresh_title();
}

void ChildWin::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    int SpriteID = getSpriteID(), FrameID = getFrameID();
    qDebug("SpriteID:%d FrameID:%d", SpriteID, FrameID);
    QGraphicsScene * view = new QGraphicsScene;
    view->addPixmap(QPixmap().fromImage(Sprites[SpriteID].BMP));
    if (FrameID > -1)
    {
        for (int i = 0; i < Sprites[SpriteID].framesCount(); i++)
        {
            SpriteFrame SF = Sprites[SpriteID].Frames[i];
            QPen P(QColor(255, 0, 0));
            QBrush B;
            if (i == FrameID)
            {
                P.setColor(QColor(255, 255, 0));
                B.setColor(P.color());
                B.setStyle(Qt::BDiagPattern);
            }
            view->addRect(SF.X, SF.Y, SF.Width, SF.Height, P, B);
        }
    }
    ui->graphicsView->setScene(view);
}

void ChildWin::closeEvent(QCloseEvent *e)
{
    if (!isChanged())
        return;

    switch (QMessageBox::warning(this, TITLEBAR,
          QString("The sprite in the <b>%1</b> file has changed.\n\nDo you want to save the changes?").arg(pakFileName),
          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
    {
    case QMessageBox::Yes:
        qDebug() << "Yes";
        break;
    case QMessageBox::No:
        qDebug() << "No";
        break;
    default:
        e->ignore();
        return;
    }
    e->accept();
}

bool ChildWin::saveToFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << file.fileName() << ": " << file.errorString();
        return false;
    }
    qDebug() << "Save to " << fileName;
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);
    out.writeRawData(DEF_PAKSIG, strlen(DEF_PAKSIG));
    for (int i = strlen(DEF_PAKSIG); i < 20; i++)
        out << qint8(0);
    qint32 SprCount = Sprites.count();
    out << SprCount;
    // Header(20) + Count(4) + ((Offset(4), BMPSize(4)) * Count)
    qint32 Cur = 20 + 4 + 8 * (Sprites.count());
    for (int i = 0; i < Sprites.count(); i++)
    {
        qint32 FrameSize = Sprites[i].getFramesSize();
        qint32 BmpSize = Sprites[i].getBitmapSize();
        out << Cur;
        out << BmpSize;
        Cur += FrameSize + BmpSize;
    }
    for (int i = 0; i < Sprites.count(); i++)
    {
        out.writeRawData(DEF_SPRSIG, 100);
        out << Sprites[i].framesCount();
        for (int j = 0; j < Sprites[i].framesCount(); j++)
        {
            const SpriteFrame & F = Sprites[i].Frames[j];
            out << F.X << F.Y << F.Width << F.Height << F.FX << F.FY;
        }
        out << qint32(0);

        QImage Tmp(Sprites[i].BMP);
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        Tmp.convertToFormat(QImage::Format_Indexed8);
        Tmp.save(&buffer, "BMP");
        out.writeRawData(bytes.constData(), bytes.count());
    }
    file.close();
    return true;
}

qint32 Sprite::getBitmapSize()
{

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    QImage Tmp(BMP);
    Tmp.convertToFormat(QImage::Format_Indexed8);
    Tmp.save(&buffer, "BMP");
    return buffer.size();
}

qint32 Sprite::getFramesSize()
{
    // Header(100) + FrameCount(4) + ( Frame(12) * FrameCount ) + Padding?(4)
    return 100 + 4 + 12 * framesCount() + 4;
}

void ChildWin::refresh_title()
{
    QString T;
    if (this->isChanged())
        T = "*";
    T.append(this->pakFileName);
    setWindowTitle(T);
}

int ChildWin::getFrameID()
{
    QTreeWidgetItem *Item = ui->treeWidget->currentItem();
    bool OK;
    return Item->parent() ? Item->text(0).toInt(&OK, 10) : -1;
}

int ChildWin::getSpriteID()
{
    QTreeWidgetItem *Item = ui->treeWidget->currentItem();
    bool OK;
    return Item->parent() ? Item->parent()->text(0).toInt(&OK, 10) : Item->text(0).toInt(&OK, 10);
}

void ChildWin::removeSprite(int SpriteID)
{
    if (SpriteID < 0 || SpriteID > Sprites.count())
        return;
    Sprites.removeAt(SpriteID);
    setChanged(true);
    refresh();
}

void ChildWin::addSprite(QString FileName)
{
    Sprite New;
    New.BMP.load(FileName);
    const QSize Dim = New.BMP.size();
    SpriteFrame Fr;
    Fr.X = 0;
    Fr.Y = 0;
    Fr.Width = Dim.width();
    Fr.Height = Dim.height();
    New.Frames.append(Fr);
    Sprites.append(New);
    setChanged(true);
    refresh();
}
