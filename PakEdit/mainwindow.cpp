#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::action_open()
{
    QStringList FileNames;
    FileNames = QFileDialog::getOpenFileNames(this, TITLEBAR, "", DIALOG_FILTER);
    foreach (QString File, FileNames)
    {
        ChildWin * NewWin = new ChildWin(ui->mdiArea);
        ui->mdiArea->addSubWindow(NewWin);
        NewWin->loadFromFile(File);
        NewWin->showNormal();
    }
}

void MainWindow::showEvent (QShowEvent *e)
{
    ui->statusBar->addWidget(statusLabel = new QLabel);
}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow* w)
{
    if (w)
        statusLabel->setText(w->windowTitle());
}
void MainWindow::action_aboutQt()
{
    QMessageBox::aboutQt(this, TITLEBAR);
}

void MainWindow::action_new()
{
    ChildWin * NewWin = new ChildWin(ui->mdiArea);
    ui->mdiArea->addSubWindow(NewWin);
    NewWin->showNormal();
}

void MainWindow::action_save()
{
    if (!ui->mdiArea->activeSubWindow())
        return;

    ChildWin * Active = static_cast<ChildWin*>(ui->mdiArea->activeSubWindow()->widget());
    if (!Active->saveToFile(Active->pakFileName))
    {
        QMessageBox::warning(this, TITLEBAR,
                             tr("Cannot write file %1:")
                             .arg(Active->pakFileName));
        return;
    }

    Active->setChanged(false);
}
void MainWindow::action_saveAs()
{
    if (!ui->mdiArea->activeSubWindow())
        return;
    ChildWin * Active = static_cast<ChildWin*>(ui->mdiArea->activeSubWindow()->widget());
    QString FileName;
    if (0 != (FileName = QFileDialog::getSaveFileName(this, TITLEBAR, Active->pakFileName, DIALOG_FILTER)))
    {
        Active->saveToFile(FileName);
        Active->pakFileName = FileName;
        Active->setChanged(false);
    }
}

void MainWindow::action_about()
{
    QMessageBox::information(this, TITLEBAR, TITLEBAR "\nby openhelbreath Team:\nhttp://code.google.com/p/openhelbreath");
}

void MainWindow::action_sprite_add()
{
    if (!ui->mdiArea->activeSubWindow())
        return;
    ChildWin * Active = static_cast<ChildWin*>(ui->mdiArea->activeSubWindow()->widget());
    foreach (QString File, QFileDialog::getOpenFileNames(this, TITLEBAR, "", "BMP (*.bmp)\nPNG (*.png)"))
    {
        Active->addSprite(File);
    }
}

void MainWindow::action_sprite_remove()
{
    if (!ui->mdiArea->activeSubWindow())
        return;
    ChildWin * Active = static_cast<ChildWin*>(ui->mdiArea->activeSubWindow()->widget());
    qDebug("Remove Sprite ID : %d", Active->getSpriteID());
    Active->removeSprite(Active->getSpriteID());
}
