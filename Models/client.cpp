#include "client.h"

Client::Client(){
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Client::ReadyRead);
    nextBlockSize = 0;
    // connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
}
void Client::SetUI(Ui::MainWindow *ui){
       this->ui = ui;
}
void Client::SetAddress(QString address){
    this->address = address;
}
void Client::ConnectServer(){
    socket->connectToHost(address,5000);
    if (socket->state() == QAbstractSocket::ConnectedState) {
        ui->clientView->append("Успешно подключение");
    }else{
       ui->clientView->append("Произошла ошибка во время подключения");
    }
}
void Client::ChangeDirectory(QString directory){
    this->directory = directory;
}
void Client::ReadyRead(){
    ui->listWidget->clear();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        // QStringList subdirs;
        // in >> subdirs;
        // for (const QString &subdir : subdirs) {
        //     qWarning() << subdir;
        //     ui->listWidget->addItem(subdir);
        // }
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
            QStringList subdirs;
            in >> subdirs;
            for (const QString &subdir : subdirs) {
                qWarning() << subdir;
                ui->listWidget->addItem(subdir);
            }
            nextBlockSize = 0;
        }

    }else{
        ui->serverView->append("Не получилось получить данные");
    }
}
void Client::SendServer(QString str){
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<< quint16(0) <<str;
    out.device()->seek(0);
    out << quint16(data.size()-sizeof(quint16));
    socket->write(data);
}
//TODO:
//Сделать закрытие связи  между сервером и клиентом
void Client::CloseConnection(){
    ui->listWidget->clear();
    socket->disconnectFromHost();
}
