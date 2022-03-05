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
    QString str = ui->textFrom->toPlainText();
    QString key = ui->textKey->toPlainText();

    if(ui->code->isChecked()){
        ui->textTo->setText(ADFGVX_code(str,key));
    }
    else if(ui->decode->isChecked()){
        ui->textTo->setText(ADFGVX_decode(str,key));
    }

}

