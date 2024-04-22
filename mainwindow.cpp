#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(server.flag){
        ui->serverView->append("Сервер включился");
    }else{
        ui->serverView->append("Сервер не включился");
    }
    client.SetUI(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_transferToServer_clicked()
{
    ui->clientView->append("Клиент получил\t" + QTime::currentTime().toString());
    client.SendServer(ui->listDirectory->currentText());
    ui->serverView->append("Сервер получил\t"+ QTime::currentTime().toString());
}


void MainWindow::on_connection_clicked()
{
    if(client.SetAddress(ui->IPText->text())){
        client.ConnectServer();
        ui->connection->hide();
    }

}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->clientView->append("Клиент получил\t" + QTime::currentTime().toString());
    ui->listDirectory->setItemText(0,server.directory.absoluteFilePath(item->text()));
    QString ss = server.directory.absoluteFilePath(item->text());
    if(item->text().contains("txt")){
        QFile file(ss);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QString fileContent = in.readAll();
        ui->clientView->append(fileContent);
        file.close();
    }
    ui->serverView->append("Сервер получил\t"+ QTime::currentTime().toString());
    qWarning() << server.path;
    client.SendServer(item->text());
}


void MainWindow::on_serverDisconnect_2_clicked()
{
    ui->clientView->append("Произошло рассоединение");
    client.CloseConnection();
    ui->connection->show();
}


void MainWindow::on_exit_clicked()
{
    QApplication::exit();
}


void MainWindow::on_transferToClient_clicked()
{
    // server.SendToClient(server.prevDir.entryList(QDir::Dirs | QDir::Files));
}


void MainWindow::on_serverOff_clicked()
{
    ui->serverView->append("Сервер отключен");
    server.OffServer();
}

