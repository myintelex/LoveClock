#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QTimer>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "bigmessage.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showSetting();
    void on_exitAppAction();
    void updateSetting();
    void workTimeOut();
    void sleepTimeOut();
    void startNew();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon * mSysTrayIcon;
    QPoint offset;
    QStringList msgList;
    QDialog * setDialog;
    QLineEdit * workedit;
    QLineEdit * sleepedit;

    int worktime;
    int sleeptime;

    int workTimeTotal;
    int sleepTimeTotal;

    QTimer * worktimer;
    QTimer * sleeptimer;

    BigMessage * workMessage;
    BigMessage * sleepMessage;
    BigMessage * showMessage;

    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;

public:
    void createActions();
    void createMenu();


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
