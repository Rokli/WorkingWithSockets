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
    client.SendServer(ui->listDirectory->currentText());
}


void MainWindow::on_connection_clicked()
{
    server.path = "";
    client.SetAddress(ui->IPText->text());
    client.ConnectServer();
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qWarning() << item->text();
    client.SendServer(item->text());
}

