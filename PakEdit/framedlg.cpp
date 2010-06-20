#include "framedlg.h"
#include "ui_framedlg.h"

FrameDlg::FrameDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrameDlg)
{
    ui->setupUi(this);
    /*Frame = Edit;
    ui->spinX->setValue(Frame->X);
    ui->spinY->setValue(Frame->Y);
    ui->spinW->setValue(Frame->Width);
    ui->spinH->setValue(Frame->Height);
    ui->spinFixX->setValue(Frame->FX);
    ui->spinFixY->setValue(Frame->FY);*/
}

FrameDlg::~FrameDlg()
{
    delete ui;
}

void FrameDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FrameDlg::apply()
{
    qDebug() << "Apply";
}
