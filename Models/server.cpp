#include "server.h"
Server::Server(){
    if(this->listen(QHostAddress::Any,5000)){
        flag = true;
    }else{
        flag = false;
    }
    nextBlockSize = 0;
}
void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::SlotReadyRead);
    sockets.push_back(socket);
    qWarning()<<"client connected";
}
void Server::SlotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        for(;;){
            if(nextBlockSize == 0){
                if(socket->bytesAvailable() < 2){
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize){
                break;
            }
            QString str;
            in >> str;
            path = path + "/" + str;
            QDir directory(path);
            nextBlockSize = 0;
            SendToClient(directory.entryList(QDir::Dirs | QDir::Files));
            break;
        }
    }
    else{
        qWarning() << "DataStream error";
    }
}
void Server::SendToClient(QStringList subdirs){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<< quint16(0) << subdirs;
    out.device()->seek(0);
    out << quint16(data.size()-sizeof(quint16));
    for(int i = 0; i < sockets.size();i++){
        sockets[i]->write(data);
    }
}
void Server::OffServer(){
    this->disconnect();
}
