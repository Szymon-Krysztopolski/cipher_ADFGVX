#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ADFGVX.cpp"

const QString PATH = "C:\\Users\\SzP_Technik\\Documents\\cipher_ADFGVX\\ADFGVX_code\\files\\";

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

    if(!ui->checkBox_file->isChecked()){
        QStringList list1 = str.split(' ');

        if(ui->code->isChecked()){
            for(int i=0;i<list1.size();i++){
                tmp+=ADFGVX_code(list1[i],key)+" ";
            }
        }
        else if(ui->decode->isChecked()){
            for(int i=0;i<list1.size();i++){
                tmp+=ADFGVX_decode(list1[i],key)+" ";
            }
        }

        if (!tmp.isEmpty()) {
            tmp.resize(tmp.size()-1);
        }
        ui->textTo->setText(tmp);
    } else {
        //QString path = qApp->applicationDirPath() + "/out.txt";

        tmp="check for out.txt";

        QFile file1(PATH+"out.txt");
        if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))
            tmp="file error1";
        else{
            QTextStream out(&file1);
            //out << "The magic number is: " << 49 << "\n";

            QFile file2(PATH+str);
            if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
                tmp="file error2";
            else{
                QTextStream in(&file2);
                QString text = in.readAll(), myLine;
                QStringList line = text.split('\n');
                for(int i=0;i<line.size();i++){
                    myLine="";
                    QStringList list2 = line[i].split(' ');
                    if(ui->code->isChecked()){
                        for(int i=0;i<list2.size();i++){
                            myLine+=ADFGVX_code(list2[i],key)+" ";
                        }
                    }
                    else if(ui->decode->isChecked()){
                        for(int i=0;i<list2.size();i++){
                            myLine+=ADFGVX_decode(list2[i],key)+" ";
                        }
                    }

                    if (!myLine.isEmpty()) {
                        myLine.resize(myLine.size()-1);
                    }
                    out << myLine << "\n";
                }
                file2.close();
            }
            file1.flush();
            file1.close();
        }
        ui->textTo->setText(tmp);
    }
}

