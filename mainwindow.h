#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <Models/server.h>
#include <Models/client.h>
#include <QTcpServer>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_transferToServer_clicked();

    void on_connection_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_serverDisconnect_2_clicked();

private:
    Ui::MainWindow *ui;
    Client client;
    Server server;
};
#endif // MAINWINDOW_H
