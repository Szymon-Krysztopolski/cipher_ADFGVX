#include <iostream>
#include <QDebug>
#include "mainwindow.h"
using namespace std;

const int n=6;

const char title_table[]={'A','D','F','G','V','X'};
const char main_table[n][n]={
    //A   D   F   G   V   X
    {'R','E','C','6','H','V'}, //A
    {'L','I','F','J','5','W'}, //D
    {'O','4','A','S','D','T'}, //F
    {'Z','3','Q','2','0','X'}, //G
    {'M','1','N','8','U','7'}, //V
    {'B','K','Y','9','P','G'}  //X
};

char find(char c){
    char x;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        if(c==main_table[i][j])
            x=title_table[j];
    }

    return x;
}

QString ADFGVX_code(QString text, QString key){
    if(text.isEmpty() || key.isEmpty())
        return QString("error");
    text=text.toUpper();

    string cryptogram;
    cryptogram.resize(text.size());

    for(int i=0;i<text.size();i++){
        cryptogram[i]=find(text[i].toLatin1());
    }
    QString QCryptogram=QString::fromStdString(cryptogram);
    QCryptogram=QCryptogram.toUpper();


    QVector<QString*> vec;
    QString tmp[2]={text,QCryptogram};


    int i=0,j=0,s=0;
    while(i<2*text.size()){
        if(i%key.size()==0){
            vec.push_back(new QString[key.size()]);
            j=0;
        }
        //qDebug()<<i<<" "<<j<<" "<<s<<" "<<key.size();
        vec[vec.size()-1][j]=tmp[s].at(i/2);

        s^=1;
        j++;
        i++;
    }
    //for(int i=0;i<vec.size();i++) for(int j=0;j<key.size();j++) qDebug()<<vec[i][j];

    return QCryptogram;
}

QString ADFGVX_decode(QString cipher, QString key){
    return cipher+"-2-"+key;
}








