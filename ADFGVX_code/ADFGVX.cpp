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

QString* find(char c){
    QString* tmp=new QString;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        if(c==main_table[i][j]){
            tmp->append(title_table[j]);
            tmp->append(title_table[i]);
        }
    }
    return tmp;
}

int* order(QString key){
    int *ord = new int(key.size());
    for(int i=0;i<key.size();i++) ord[i]=i;
    return ord;
}

QString ADFGVX_code(QString text, QString key){
    if(text.isEmpty() || key.isEmpty())
        return QString("error");
    text=text.toUpper();

    QString *QCryptogram = new QString;

    for(int i=0;i<text.size();i++){
        QCryptogram->append(*find(text[i].toLatin1()));
        qDebug()<<*find(text[i].toLatin1());
    }

    QVector<QString*> vec;



    int i=0,j=0;
    while(i<2*text.size()){
        if(i%key.size()==0){
            vec.push_back(new QString[key.size()]);
            j=0;
        }
        //qDebug()<<i<<" "<<j<<" "<<s<<" "<<key.size();
        vec[vec.size()-1][j]=QCryptogram[i];

        j++;
        i++;
    }
    while(i++%key.size()!=0)vec[vec.size()-1][j++]='-';
    for(int i=0;i<vec.size();i++) for(int j=0;j<key.size();j++) qDebug()<<vec[i][j];

    QString result;
    int *ord=order(key);
    for(int i=0;i<key.size();i++){
        for(int j=0;j<vec.size();j++){
            result.append(vec[j][ord[i]]);
        }
    }
    qDebug()<<result<<" "<<vec.size()<<" "<<key.size();

    return result;
}

QString ADFGVX_decode(QString cipher, QString key){
    return cipher+"-2-"+key;
}








