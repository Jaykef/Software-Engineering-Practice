#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDebug>
#include <QObject>

class TcpServer:public QTcpServer
{
    Q_OBJECT
public:
    QHostAddress * ip;
    quint16 port;
    QTcpSocket * currentClient;
private:
    QList<QTcpSocket *> tcpClients;
public:
    explicit TcpServer(QObject *parent = 0);
    bool ServerStart();
    qint64 SendData(QTcpSocket *tcpClient,const char *data,qint64 len);
public slots:
    void NewConnectionSlot();
    void onReadData();
    void onDisconnectedSlot();
signals:
    void newData(QString data);
};

#endif // TCPSERVER_H
