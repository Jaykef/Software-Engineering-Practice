#include "mainwindow.h"
#include <QApplication>
#include<QTcpSocket>
#include<QHostAddress>

class TcpClient:public QMainWindow
{
public:
    TcpClient(QWidget *parent = 0):QMainWindow(parent)
    {
        tcpClient = new QTcpSocket(this);
        //tcpClient->abort();//断开已有的连接
    }
    ~TcpClient(){
        tcpClient->abort();//断开已有的连接
        delete tcpClient;
    }

public:
    QTcpSocket *tcpClient;
    QHostAddress ip;
    quint16 port;
public:
    void ConServer();
    void DisconServer();
    qint64 SendData(const char * data, qint64 len);
};

void TcpClient::ConServer()
{
    tcpClient->connectToHost(ip,port);
    if(tcpClient->waitForConnected(3000))
    {
        qDebug()<<"connected!";
        return;
    }else
        qDebug()<<"connect failed!";
}

void TcpClient::DisconServer()
{
    qDebug()<<"try to disconnect...";
    tcpClient->disconnectFromHost();
    if(tcpClient->state() == QAbstractSocket::UnconnectedState
            || tcpClient->waitForDisconnected(3000)){
        qDebug()<<"disconnected";
        return;
    }else
        qDebug()<<"disconnect failed!";
}
qint64 TcpClient::SendData(const char *data, qint64 len)
{
    qDebug()<<"send data ...";
    qint64 slen = tcpClient->write(data,len);
    qDebug()<<"sent "<<slen<< " bytes";
    return slen;
}
int main(int argc, char *argv[])
{
    char data[] = {(char)0x32,(char)0x37,(char)0x38,(char)0x36};
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    TcpClient tc;
    tc.ip = "127.0.0.1";
    tc.port = 8888;
    tc.ConServer();
    if(tc.tcpClient->state() == QAbstractSocket::ConnectedState)
        tc.SendData(data,sizeof(data));
    while(1){
        if(tc.tcpClient->state() == QAbstractSocket::ConnectedState){
            if(tc.tcpClient->waitForReadyRead())
            {
                qDebug()<<"read from server";
                QByteArray buffer = tc.tcpClient->readAll();
                if(!buffer.isEmpty())
                {
                    qDebug()<<"data size "<<buffer.size();
                    qDebug()<<buffer;
                    //TODO: process data
                }
            }else
                qDebug()<<"read data timeout. try again";
        }else
            break;
    }
    tc.DisconServer();

    return a.exec();
}
