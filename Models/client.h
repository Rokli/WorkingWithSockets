#ifndef CLIENT_H
#define CLIENT_H

#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "ui_mainwindow.h"
#include <qstring.h>


class Client : public QTcpServer
{
public:
    Client(Ui::MainWindow *ui);
    void SetAddress(QString address);
    void ConnectServer();
    void ChangeDirectory(QString directory);
    void SendServer(QString str);
    void ReadyRead();
    void CloseConnection();
    QTcpSocket *socket;
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    Ui::MainWindow *ui;
private:
    QString address;
    QString directory;

};

#endif // CLIENT_H
