#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "GlobalDef.h"
#include "childwin.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    QLabel * statusLabel;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void action_open();
    void action_aboutQt();
    void action_new();
    void action_save();
    void action_saveAs();
    void action_about();
    void action_sprite_add();
    void action_sprite_remove();
protected:
    void changeEvent(QEvent *e);
    void showEvent (QShowEvent *e);
private:
    Ui::MainWindow *ui;


private slots:
    void on_mdiArea_subWindowActivated(QMdiSubWindow* w);
};

#endif // MAINWINDOW_H
