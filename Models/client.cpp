#include "client.h"

Client::Client(Ui::MainWindow *ui) {
    this->ui = ui;
}

void Client::TextOutput(QString str){
    ui->textBrowser->append(str);
}
