#include "client.h"

Client::Client(Ui::MainWindow *ui){
    this->ui = ui;
    connect(socket, &QTcpSocket::readyRead, this, &Client::ReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
}
void Client::SetAddress(QString address){
    this->address = address;
}
void Client::ConnectServer(){
    socket->connectToHost(address,5000);
}
void Client::ChangeDirectory(QString directory){
    this->directory = directory;
}
void Client::ReadyRead(){
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        QString str;
        in >> str;
        ui->serverView->append(str);
    }else{
        ui->serverView->append("Параша noполучилась");
    }
}
void Client::SendServer(QString str){
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<str;
    socket->write(data);
}
