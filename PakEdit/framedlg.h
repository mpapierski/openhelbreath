#ifndef FRAMEDLG_H
#define FRAMEDLG_H

#include <QWidget>
#include <QDialog>
#include <QDebug>

namespace Ui {
    class FrameDlg;
}

class FrameDlg : public QDialog {
    Q_OBJECT
public:
    FrameDlg(QWidget *parent = 0);
    ~FrameDlg();
    void apply();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FrameDlg *ui;
};

#endif // FRAMEDLG_H
