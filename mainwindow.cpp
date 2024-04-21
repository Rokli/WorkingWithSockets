#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Server server;
    if(server.flag){
        ui->textBrowser->append("Сервер включился");
    }else{
        ui->textBrowser->append("Сервер не включился");
    }
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::SlotsReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    socket->connectToHost("127.0.0.1",2323);
}

void MainWindow::SlotsReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        QString str;
        in >> str;
        ui->textBrowser->append(str);
    }else{
        ui->textBrowser->append("Параша noполучилась");
    }
}

void MainWindow::SendToServer(QString str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<str;
    socket->write(data);
}


void MainWindow::on_transferToServer_clicked()
{
    SendToServer("урааа");
}

