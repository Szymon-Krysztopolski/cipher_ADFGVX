#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ADFGVX.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_butt_run_clicked()
{
    QString tmp;
    QString str = ui->textFrom->toPlainText();
    QString key = ui->textKey->toPlainText();

    QStringList list1 = str.split(" ");

    if(ui->code->isChecked()){
        for(int i=0;i<list1.size();i++){
            tmp+=ADFGVX_code(list1[i],key)+" ";
        }
        if (!tmp.isEmpty()) {
            tmp.resize(tmp.size()-1);
        }
        ui->textTo->setText(tmp);
    }
    else if(ui->decode->isChecked()){
        for(int i=0;i<list1.size();i++){
            tmp+=ADFGVX_decode(list1[i],key)+" ";
        }
        ui->textTo->setText(tmp);
    }

}

