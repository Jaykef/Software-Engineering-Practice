#ifndef OUTTIMER_H
#define OUTTIMER_H
#include<QTimer>
#include<QString>
#include<QLabel>

class OutTimer : public QLabel//继承自QLabel
{
public:
    OutTimer();
    QString getCurrentTimeString();//定义一个方法
    QTimer *tm;// 定时器
    void refreshTime();//刷新时间
    int count;
protected:
    virtual void mousePressEvent(QMouseEvent *ev);
};

#endif // OUTTIMER_H
