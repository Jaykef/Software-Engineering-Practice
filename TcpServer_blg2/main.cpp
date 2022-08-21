#include "mainwindow.h"
#include <QApplication>
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDebug>
#include <QObject>

class TcpServer:public QTcpServer
{
public:
    QHostAddress * ip;
    quint16 port;
    QTcpSocket * currentClient;
public:
    explicit TcpServer(QObject *parent = 0);
    bool ServerStart();
    qint64 SendData(QTcpSocket *tcpClient,const char *data,qint64 len);
public slots:
    void NewConnectionSlot();
    void onReadData();
    void onDisconnectedSlot();
};

TcpServer::TcpServer(QObject *parent):QTcpServer((QObject *)parent)
{
    ip = new QHostAddress("127.0.0.1");
    port = 8888;
    connect(this,&TcpServer::newConnection,this,TcpServer::NewConnectionSlot());
}

void TcpServer::NewConnectionSlot()
{
    qDebug()<<"New Connection";
    currentClient = this->nextPendingConnection();//当前最新连接进来的socket
    qDebug()<<"ip:"<<currentClient->peerAddress().toString()<<":"<<currentClient->peerPort();

    connect(currentClient,&QTcpSocket::readyRead,this,&TcpServer::onReadData);
    connect(currentClient,&QTcpSocket::disconnected,this,&TcpServer::onDisconnectedSlot);
}

void TcpServer::onDisconnectedSlot()
{
    qDebug()<<"onDisconnectedSlot";
}

void TcpServer::onReadData()
{
    qDebug()<<"tcpserver recv data:";
    QByteArray buffer = currentClient->readAll();
    if(!buffer.isEmpty()){
        qDebug()<<"read data from client:"<<buffer;
    }
}

qint64 TcpServer::SendData(QTcpSocket *tcpClient, const char *data, qint64 len)
{
    qDebug()<<"Send data ...";
    qint64 slen = tcpClient->write(data,len);//发送数据
    qDebug()<<"len:"<<slen<< " bytes";
    return slen;
}

bool TcpServer::ServerStart()
{
    qDebug()<<"try to start a tcp server at "<<ip->toString()<<":"<<port;
    bool ret = this->listen(*ip,port);//开始侦听
    if(ret){
        qDebug()<<"tcp server started!";
    }else
        qDebug()<<"tcp server start failed!";
    return ret;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TcpServer * ts = new TcpServer();
    ts->ServerStart();

    return a.exec();
}
