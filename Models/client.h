#ifndef CLIENT_H
#define CLIENT_H

#include "ui_mainwindow.h"
class Client
{
public:
    Client(Ui::MainWindow *ui);
    void TextOutput(QString str);
private:
    Ui::MainWindow *ui;

};

#endif // CLIENT_H
