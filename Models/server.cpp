#include "server.h"

Server::Server(){
    if(this->listen(QHostAddress::Any,2323)){
        qDebug() << "Сервер включен";
    }else{
        qDebug() << "Сервер не включился";
    }
}
void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::SlotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    sockets.push_back(socket);
    qDebug()<<"client connected" << socketDescriptor;
}
void Server::SlotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        qDebug() << "read...";
        QString str;
        in >> str;
        qDebug() << str;
        SendToClient("333");
    }
    else{
        qDebug() << "DataStream error";
    }
}
void Server::SendToClient(QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << str;
    // socket->write(data);
    for(int i = 0; i < sockets.size();i++){
        sockets[i]->write(data);
    }
}
