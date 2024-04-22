#include "client.h"

Client::Client(){
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Client::ReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
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
        ui->serverView->append("Успешно подключение");
    }else{
       ui->serverView->append("Произошла ошибка во время подключения");
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
        QStringList subdirs;
        in >> subdirs;
        for (const QString &subdir : subdirs) {
            qWarning() << subdir;
            ui->listWidget->addItem(subdir);
        }

    }else{
        ui->serverView->append("Не получилось получить данные");
    }
}
void Client::SendServer(QString str){
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<str;
    socket->write(data);
}
//TODO:
//Сделать закрытие связи  между сервером и клиентом
void Client::CloseConnection(){

}
