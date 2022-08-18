#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <qmath.h>

class QWidgetDraw : public QWidget
{
public:
    QWidgetDraw(){}
    virtual void paintEvent(QPaintEvent * event){
        //qDebug()<<"paintEvent";
        QPainter *qpainter = new QPainter();
        qpainter->begin(this);
        this->draw(qpainter);
        qpainter->end();
    }

    void draw(QPainter * qpainter)
    {
        //qpainter->drawLine(20,20,100,100);
        qpainter->drawRect(20,20,600,400);
        drawDivide(qpainter,20,20,2,2,600,400);
        drawDivide(qpainter,20,20,15,10,300,200);

        int step = 300/15;
        qpainter->drawEllipse(20+step*(5-3),20+step*(5-3),step*6,step*6);//圆心在（5，5），半径是3
        qpainter->drawEllipse(20+step*(10-1),20+step*(2-1),step*2,step*2);//圆心在（10，2），半径是1
        qpainter->drawEllipse(20+step*(12-1),20+step*(4-1),step*2,step*2);//圆心在（12，4），半径是1
        qpainter->drawEllipse(20+step*(12-1),20+step*(7-1),step*2,step*2);//圆心在（12，7），半径是1
        qpainter->drawEllipse(20+step*(10-1),20+step*(9-1),step*2,step*2);//圆心在（10，9），半径是1

        drawStart(qpainter,20+step*(5),20+step*(5),step*3,0,Qt::OddEvenFill);
        drawStart(qpainter,20+step*(10),20+step*(2),step*1,-(90+qTan(3/5)/M_PI*180),Qt::OddEvenFill);
        drawStart(qpainter,20+step*(12),20+step*(4),step*1,-(90+qTan(1/7)/M_PI*180),Qt::OddEvenFill);
        drawStart(qpainter,20+step*(12),20+step*(7),step*1,-(90+qTan(2/7)/M_PI*180),Qt::OddEvenFill);
        drawStart(qpainter,20+step*(10),20+step*(9),step*1,-(90+qTan(4/5)/M_PI*180),Qt::OddEvenFill);

    }

    void drawDivide(QPainter * qpainter,int x, int y, int wCnt, int hCnt, int w, int h)
    {
        int step = w/wCnt;
        for(int num=0;num<wCnt;num++)
            qpainter->drawLine(x+num*step,y,x+num*step,y+h);
        step = h/hCnt;
        for(int i=0;i<hCnt;i++)
            qpainter->drawLine(x,y+i*step,x+w,y+i*step);
    }

    void drawStart(QPainter * painter,qreal x, qreal y, qreal radius, qreal rotate, Qt::FillRule fillStyle)
    {
        qreal degree = 2*M_PI *(180/10)/360;

        QVector<QPoint> points;
        points<<QPoint(0,-radius)<<QPoint(-radius*qTan(degree),0)<<QPoint(radius*qTan(degree),0);

        painter->setBrush(QColor("#F4F408"));//填充色
        painter->setPen(QColor("#F4F408"));//边缘色

        painter->resetTransform();
        painter->translate(x,y);
        painter->rotate(rotate);//坐标系总体旋转
        //drawTriangle(painter,points,fillStyle);
        for(int cnt=0;cnt<5;cnt++){
            drawTriangle(painter,points,fillStyle);
            painter->rotate(72);
        }

        painter->resetTransform();
    }

    void drawTriangle(QPainter * painter, QVector<QPoint> &points, Qt::FillRule fillStyle)
    {
        painter->drawPolygon(points,fillStyle);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QWidgetDraw * widgetDraw = new QWidgetDraw();
    widgetDraw->setStyleSheet("background-color:red");
    widgetDraw->resize(640,440);
    widgetDraw->show();

    return a.exec();
}
