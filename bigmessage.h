#ifndef BIGMESSAGE_H
#define BIGMESSAGE_H

#include <QWidget>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

namespace Ui {
class BigMessage;
}

class BigMessage : public QWidget
{
    Q_OBJECT

public:
    explicit BigMessage(QWidget *parent = 0);
    ~BigMessage();
    void setText(QString str);

private:
    Ui::BigMessage *ui;
    QStringList mymsglist;

signals:
    void enterButtonpressed();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();
};

#endif // BIGMESSAGE_H
