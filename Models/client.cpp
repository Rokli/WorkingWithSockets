#include "client.h"

Client::Client(){
    socket = new QTcpSocket();
    connect(socket, &QTcpSocket::readyRead, this, &Client::ReadyRead);
    nextBlockSize = 0;
}
void Client::SetUI(Ui::MainWindow *ui){
       this->ui = ui;
}
bool Client::SetAddress(QString address){
    QRegularExpression ipRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    if(ipRegex.match(address).hasMatch()){
        this->address = address;
        return true;
    }else{
        ui->clientView->append("Неправильный IP-адрес");
        return false;
    }
}
void Client::ConnectServer(){
    socket->connectToHost(address,5000);
    ui->listDirectory->addItem("/");
    ui->clientView->append("Успешно подключение");
}
void Client::ChangeDirectory(QString directory){
    this->directory = directory;
}
void Client::ReadyRead(){
    ui->listWidget->clear();
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
            QStringList subdirs;
            in >> subdirs;
            for (const QString &subdir : subdirs) {
                // qWarning() << subdir;
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
void Client::CloseConnection(){
    ui->listWidget->clear();
    socket->disconnectFromHost();
}
