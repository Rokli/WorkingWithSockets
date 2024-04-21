#include "scdebug.h"

SCDebug::SCDebug(Ui::MainWindow *ui) {
    this->ui = ui;
}

void SCDebug::TextOutput(QString str){
    ui->textBrowser->append(str);
}
