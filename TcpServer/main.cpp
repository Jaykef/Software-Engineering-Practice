#include "mainwindow.h"
#include <QApplication>
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDebug>

class TcpServer:public QTcpServer
{
public:
    QHostAddress ip;
    quint16 port;
public:
    TcpServer(QObject *parent = 0);
    bool ServerStart();
private:
    QList<QTcpSocket *> tcpClients;
    QTcpSocket * currentClient;
    QList<QHostAddress> localaddrs;
private slots:
    void NewConnectionSlot();
};

TcpServer::TcpServer(QObject *parent):QTcpServer((QObject *)parent)
{
    localaddrs = QNetworkInterface::allAddresses();
    foreach (QHostAddress ha, localaddrs) {
        qDebug()<<ha.toString();
        quint32 ip32 = ha.toIPv4Address();
        qDebug()<<ip32;//2130706433 = 0x7F 0x00 0x00 0x01 = 127 0 0 1
        quint8 ip81 = (quint8)ip32 % 0xFF;
        quint8 ip82 = (quint8)(ip32>>8) & 0x000000FF;
        quint8 ip83 = (quint8)(ip32>>16) & 0x000000FF;
        quint8 ip84 = (quint8)(ip32>>24) & 0x000000FF;
        qDebug()<<ip81<<ip82<<ip83<<ip84;
    }
    ip = "127.0.0.1";
    port = 8888;

    connect(this,&TcpServer::newConnection,this,TcpServer::NewConnectionSlot);
}

void TcpServer::NewConnectionSlot()
{
    qDebug()<<"New Connection";
}

bool TcpServer::ServerStart()
{
    qDebug()<<"try to start a tcp server at "<<ip.toString()<<":"<<port;
    bool ret = this->listen(ip,port);
    if(ret)
        qDebug()<<"tcp server started!";
    else
        qDebug()<<"tcp server start failed!";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TcpServer *ts =new TcpServer();
    ts->ServerStart();

    return a.exec();
}
