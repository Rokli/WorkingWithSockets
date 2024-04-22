#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include <QDir>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    bool flag;
    QString path = "/";
    quint16 nextBlockSize;
    QDir prevDir;
    void SendToClient(QStringList subdirs);
    void OffServer();
private:
    QVector<QTcpSocket*> sockets;
    QByteArray data;
public slots:
    void incomingConnection(qintptr socketDescriptor)override;
    void SlotReadyRead();
};

#endif // SERVER_H
