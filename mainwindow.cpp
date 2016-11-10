#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSysTrayIcon = new QSystemTrayIcon(this);
    //新建托盘要显示的icon
    QIcon icon = QIcon(":/image/image/myico.png");
    //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip(QObject::trUtf8("测试系统托盘图标"));
    //在系统托盘显示此对象
    mSysTrayIcon->show();
    connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    createActions();
    createMenu();

    QPixmap pix;
    pix.load(":/image/image/mymsg.png");
    resize(pix.size());
    setMask(pix.mask());

    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
    this->move(QApplication::desktop()->screenGeometry(0).width() - 100, 50);

    setMouseTracking(true);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    ui->label->resize(50,10);
    ui->label->move(0,57);
    ui->label->setText("0");

    setDialog =new QDialog();
    setDialog->setFixedSize(400, 100);
    setDialog->move(QApplication::desktop()->screenGeometry(0).width() /2 - 200,
                    QApplication::desktop()->screenGeometry(0).height() /2 - 50);
    setDialog->setWindowFlags(Qt::FramelessWindowHint);

    QLabel *label = new QLabel(setDialog);
    label->setText(tr("工作时间:"));
    label->move(20, 40);
    workedit = new QLineEdit(setDialog);
    workedit->setFixedSize(100, 30);
    workedit->move(80, 30);

    QLabel *label1 = new QLabel(setDialog);
    label1->setText(tr("休息时间:"));
    label1->move(220, 40);
    sleepedit = new QLineEdit(setDialog);
    sleepedit->setFixedSize(100, 30);
    sleepedit->move(280, 30);

    QPushButton * setButton = new QPushButton(setDialog);
    setButton->move(300,70);
    setButton->setText(tr("确定"));
    connect(setButton, SIGNAL(clicked(bool)), this, SLOT(updateSetting()));

    workTimeTotal = 45 * 60;
    worktime = workTimeTotal;
    sleepTimeTotal = 5 * 60;
    sleeptime = sleepTimeTotal;

    worktimer = new QTimer(this);
    sleeptimer = new QTimer(this);

    connect(worktimer, SIGNAL(timeout()), this, SLOT(workTimeOut()));
    connect(sleeptimer, SIGNAL(timeout()), this, SLOT(sleepTimeOut()));
    worktimer->start(1000);

    workMessage = new BigMessage();
    sleepMessage = new BigMessage();
    showMessage = new BigMessage();

    connect(workMessage, SIGNAL(enterButtonpressed()), this, SLOT(startNew()));
    connect(sleepMessage, SIGNAL(enterButtonpressed()), this, SLOT(startNew()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        //双击后显示主程序窗口
        this->show();
        break;
    default:
        break;
    }

}

void MainWindow::on_showSetting()
{
    setDialog->show();
}

void MainWindow::on_exitAppAction()
{
    exit(0);
}

void MainWindow::updateSetting()
{
    QString temp = workedit->text();
    if(!temp.isEmpty())
    {
        workTimeTotal = temp.toInt() * 60;
    }
    temp.clear();
    temp = sleepedit->text();
    if(!temp.isEmpty())
    {
        sleepTimeTotal = temp.toInt() * 60;
    }
    setDialog->hide();

}

void MainWindow::workTimeOut()
{
    if(worktime <= 0)
    {
        worktimer->stop();
        workMessage->show();
        workMessage->setText(tr("工作时间这么长了，休息一下，喝口水，出去转一圈吧，当然你也可以和我聊聊天啊"));
    }
    else
    {
        worktime--;
        ui->label->setText(QString::number(worktime/60) + ":" + QString::number(worktime%60));
        qDebug()<<worktime;
    }
}

void MainWindow::sleepTimeOut()
{
    if(sleeptime <= 0)
    {
        sleeptimer->stop();
        sleepMessage->show();
        sleepMessage->setText(tr("别玩了，赶紧回来干活"));
    }
    else
    {
        sleeptime--;
        ui->label->setText(QString::number(sleeptime/60)  + ":" + QString::number(sleeptime%60));
    }
}

void MainWindow::startNew()
{
    if(worktime == 0)
    {
        worktime = workTimeTotal;
        sleeptimer->start(1000);
    }
    else if(sleeptime == 0)
    {
        sleeptime = sleepTimeTotal;
        worktimer->start(1000);
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/image/image/mymsg.png"));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        offset = event->globalPos() - this->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    if(event->buttons() && Qt::LeftButton)
    {
        QPoint temp;
        temp = event->globalPos() - offset;
        this->move(temp);
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    if(showMessage->isHidden() && workMessage->isHidden() && sleepMessage->isHidden())
    {
        showMessage->setText(tr("怎么想我了啊，想我就在心里亲我一口啊"));
        showMessage->show();
    }

}


void MainWindow::createActions()
{
    mShowMainAction = new QAction(QObject::trUtf8("设置时间"),this);
    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_showSetting()));

    mExitAppAction = new QAction(QObject::trUtf8("退出"),this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));

}

void MainWindow::createMenu()
{
    mMenu = new QMenu(this);
    mMenu->addAction(mShowMainAction);

    mMenu->addSeparator();

    mMenu->addAction(mExitAppAction);

    mSysTrayIcon->setContextMenu(mMenu);
}


