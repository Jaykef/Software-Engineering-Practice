#include "mainwindow.h"
#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include<QDebug>
#include <QTimer>

class QWidgetSerialRx : public QWidget
{
public:
    QWidgetSerialRx(QWidget * parent = 0):QWidget(parent)
    {
        if( 0 != this->SerialInit()){
            qDebug()<<"SerialInit failed";
            return;
        }
    }
public:
    QSerialPort * com;
public:
    int SerialInit(void);//初始化
public slots:
    void readData();//读数据
    void rxDataHandle(char datah,char datal);//处理数据

};

int QWidgetSerialRx::SerialInit(void)
{
    qDebug()<<"SerialInit";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug()<<"Name:"<<info.portName();
        qDebug()<<"Description:"<<info.description();
        qDebug()<<"Manufacturer:"<<info.manufacturer();
        qDebug()<<"Serial Number:"<<info.serialNumber();
    }
    //打开串口
    com = new QSerialPort();
    com->setPortName("COM3");
    if(!com->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Serial open failed!";
        return -1;
    }
    else
        qDebug()<<"Serial open success:"<<com->portName();
    //设定串口参数
    com->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
    com->setDataBits(QSerialPort::Data8);
    com->setFlowControl(QSerialPort::NoFlowControl);
    com->setParity(QSerialPort::NoParity);
    com->setStopBits(QSerialPort::OneStop);

    connect(com,&QSerialPort::readyRead,this,&QWidgetSerialRx::readData);
    return 0;
}

void QWidgetSerialRx::readData()
{
    qDebug()<<"readData";
    while(!com->atEnd())
    {
        QByteArray data = this->com->read(2);
        this->rxDataHandle(data[0],data[1]);
    }
}

void QWidgetSerialRx::rxDataHandle(char datah,char datal)
{
    int datai;
    //qDebug()<<datah<<datal;
    datai = (unsigned int)datah << 8 |((unsigned int)datal &0x00FF);
    qDebug()<<datai;
    //调用画波形函数
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QWidgetSerialRx *com = new QWidgetSerialRx();

    return a.exec();
}
