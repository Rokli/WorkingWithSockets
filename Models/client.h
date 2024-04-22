#ifndef CLIENT_H
#define CLIENT_H

#include "qtcpserver.h"
#include "qtcpsocket.h"
#include "ui_mainwindow.h"
#include <qstring.h>


class Client : public QTcpServer
{
    Q_OBJECT
public:

    Client();
    void SetUI(Ui::MainWindow *ui);
    QTcpSocket *socket;
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    Ui::MainWindow *ui;

private:
    QString address;
    QString directory;
public slots:
    void SetAddress(QString address);
    void ConnectServer();
    void ChangeDirectory(QString directory);
    void SendServer(QString str);
    void ReadyRead();
    void CloseConnection();
};

#endif // CLIENT_H
