#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent):QTcpServer((QObject *)parent)
{
    ip = new QHostAddress("127.0.0.1");
    port = 8888;
    connect(this,&TcpServer::newConnection,this,TcpServer::NewConnectionSlot);
}

void TcpServer::NewConnectionSlot()
{
    qDebug()<<"New Connection";
    currentClient = this->nextPendingConnection();//当前最新连接进来的socket
    tcpClients.append(currentClient);
    qDebug()<<"ip:"<<currentClient->peerAddress().toString()<<":"<<currentClient->peerPort();

    connect(currentClient,&QTcpSocket::readyRead,this,&TcpServer::onReadData);
    connect(currentClient,&QTcpSocket::disconnected,this,&TcpServer::onDisconnectedSlot);
}
void TcpServer::onDisconnectedSlot()
{
    qDebug()<<"onDisconnectedSlot";
    for(int i=0;i<tcpClients.length();i++){
        if(tcpClients[i]->state() == QAbstractSocket::UnconnectedState){
            qDebug()<<"client disconnected ip:"<<tcpClients[i]->peerAddress().toString()
                   <<":"<<tcpClients[i]->peerPort();
            tcpClients[i]->destroyed();
            tcpClients.removeAt(i);
            i--;
        }
    }
}
void TcpServer::onReadData()
{
    qDebug()<<"tcpserver recv data:";
    for(int i=0;i<tcpClients.length();i++){
        QByteArray buffer = tcpClients[i]->readAll();
        if(!buffer.isEmpty()){
            qDebug()<<"read data from port:"<<QString::number(tcpClients[i]->peerPort())<<"data:"<<buffer;
            QString strData(buffer);
            emit newData(strData);
        }else{
            continue;
        }
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
