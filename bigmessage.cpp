#include "bigmessage.h"
#include "ui_bigmessage.h"
#include <QTime>

BigMessage::BigMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigMessage)
{
    ui->setupUi(this);
    QPixmap pix;
    pix.load(":/image/image/mybigmsg.png");
    resize(pix.size());
    setMask(pix.mask());
    ui->label->move(50, 270);
    ui->label->setWordWrap(true);
    ui->label_2->move(50, 340);
    ui->label_2->setWordWrap(true);
    ui->pushButton->move(540, 385);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    mymsglist << tr("好想从现在开始抱着你，紧紧的抱着你，一直走到上帝面前。")
              << tr("假如可以的话，我愿意花去生命中的每一分每一秒，陪着你。")
              << tr("看着你的眼，我看见了大海，蓝天；更看到了美丽的未来。")
              << tr("看着微笑的你，突然发现，我真是世界上最幸福的人。")
              << tr("你是我生命中所能经历的，最最深切的感觉。")
              << tr("认识你才知道有一种心情叫做依恋，有一种感觉叫做爱。")
              << tr("时间的巨轮无法抹去我对你的思念纵使海枯石烂，你的身影永存於我心中。")
              << tr("天上有多少星光 世间有多少女孩，但天上只有一个月亮 世间只有 一个你。")
              << tr("我不相信永远的爱，因为我只会一天比一天更爱你。")
              << tr("我想将对你的感情，化作暖暖的阳光，期待那洒落的光明能温暖你的心房。")
              << tr("原来等待也可以如此的美丽，因为爱你。")
              << tr("在每一个有你声相伴的夜，不再过於寂寥冷清。")
              << tr("这辈子最疯狂的事，就是爱上了你，最大的希望，就是有你陪我疯一辈子。")
              << tr("这一生我只牵你的手，因为今生有你早已足够。")
              << tr("真的，输了你，赢了世界又如何？")
              << tr("只想牵你的手，看你的眼，光着脚丫子，在海边漫步，只有你，只因你。")
              << tr("不需言语，让我用行动告诉你，什麽叫爱。")
              << tr("不愿意醒来时，台灯投射在墙上只有我孤独的身影。")
              << tr("对你，不管阴晴圆缺，也不变。");



}

BigMessage::~BigMessage()
{
    delete ui;
}

void BigMessage::setText(QString str)
{
    int rand = qrand() % mymsglist.size();
    QString str1 = mymsglist.at(rand);
    ui->label->setText(tr("马哥说： ") + str1);
    ui->label_2->setText(str);
}

void BigMessage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/image/image/mybigmsg.png"));
}

void BigMessage::on_pushButton_clicked()
{
    emit enterButtonpressed();
    this->hide();
}
