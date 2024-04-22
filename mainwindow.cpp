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
    ui->clientView->append("Отправил данные");
    client.SendServer(ui->listDirectory->currentText());
    ui->serverView->append("Принял данные");
}


void MainWindow::on_connection_clicked()
{
    client.SetAddress(ui->IPText->text());
    client.ConnectServer();
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->clientView->append("Отправил данные");
    ui->listDirectory->setItemText(0,ui->listDirectory->itemText(0)+item->text());
    ui->serverView->append("Принял данные");
    qWarning() << server.path;
    client.SendServer(item->text());
}


void MainWindow::on_serverDisconnect_2_clicked()
{
    ui->clientView->append("Произошло рассоединение");
    client.CloseConnection();
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

