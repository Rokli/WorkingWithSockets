#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    bool flag;

private:
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    void SendToClient(QString str);
public slots:
    void incomingConnection(qintptr socketDescriptor)override;
    void SlotReadyRead();
};

#endif // SERVER_H
