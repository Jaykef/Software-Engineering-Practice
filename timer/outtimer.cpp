#include "outtimer.h"
#include<QString>
#include<QTimer>
#include<QDateTime>
#include<QDebug>

OutTimer::OutTimer()
{
    this->setText(this->getCurrentTimeString());
    tm = new QTimer(this);
    connect(tm,&QTimer::timeout,this,&OutTimer::refreshTime);
    this->setStyleSheet("font-size:30px");
    tm->start(1);
    count = 0;
}

QString OutTimer::getCurrentTimeString()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz");
}

void OutTimer::refreshTime()
{
    this->setText(this->getCurrentTimeString());//更新显示的文字
}

void OutTimer::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<"click";
    count++;
    int k = count % 2;
    if(!k)
        tm->stop();
    else
        tm->start();
}
