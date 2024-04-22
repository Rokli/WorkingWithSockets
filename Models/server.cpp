#include "server.h"

Server::Server(){
    if(this->listen(QHostAddress::Any,5000)){
        qWarning() << "Сервер включен";
        flag = true;
    }else{
        qWarning() << "Сервер не включился";
    }
}
void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::SlotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    sockets.push_back(socket);
    qWarning()<<"client connected";
}
void Server::SlotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        qWarning() << "read...";
        QString str;
        in >> str;
        qWarning() << str;
        SendToClient(str);
    }
    else{
        qWarning() << "DataStream error";
    }
}
void Server::SendToClient(QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << str;
    for(int i = 0; i < sockets.size();i++){
        sockets[i]->write(data);
    }
}
