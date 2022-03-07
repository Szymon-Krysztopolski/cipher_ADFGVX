#include <iostream>
#include <QDebug>
#include "mainwindow.h"
using namespace std;

#define n 6

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

QString find(char c){
    QString tmp;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        if(c==main_table[i][j]){
            tmp.append(title_table[j]);
            tmp.append(title_table[i]);
        }
    }
    if(tmp.isEmpty()) tmp=QString(QChar(c));
    return tmp;
}

QChar find_2(QChar c1, QChar c2){

    char k=c1.toLatin1();
    char w=c2.toLatin1();
    int x=-1,y=-1;

    for(int i=0;i<n;i++){
        if(k==title_table[i]) x=i;
        if(w==title_table[i]) y=i;
    }
    if (x==-1 || y==-1)
        return QChar('?');
    return QChar(main_table[y][x]);
}

int* order(QString key){
    int *ord = new int[key.size()];
    QString tmp=key;
    int min;

    for(int i=0;i<key.size();i++) ord[i]=i;

    for(int i=0;i<key.size();i++) {
        min=i;
        for(int j=0;j<key.size();j++){
            if(tmp[min]>tmp[j]){
                min=j;
            }
        }
        tmp[min]='|';
        ord[i]=min;

        //qDebug()<<i<<ord[i]<<min<<ord[min]<<tmp<<key;
    }
    return ord;
}

QString ADFGVX_code(QString text, QString key){
    if(text.isEmpty() || key.isEmpty())
        return QString("error");
    text=text.toUpper();

    QString QCryptogram, result;
    QVector<QChar*> vec;

    for(int i=0;i<text.size();i++){
        QCryptogram.append(find(text[i].toLatin1()));
        //qDebug()<<*find(text[i].toLatin1());
    }

    int i=0,j=0;
    while(i<QCryptogram.size()){
        if(i%key.size()==0){
            vec.push_back(new QChar[key.size()]);
            j=0;
        }
        //qDebug()<<i<<j<<key.size();
        vec[vec.size()-1][j]=QCryptogram[i];

        j++;
        i++;
    }
    while(i++%key.size()!=0)vec[vec.size()-1][j++]='-';
    //for(int i=0;i<vec.size();i++) for(int j=0;j<key.size();j++) qDebug()<<vec[i][j];

    int *ord=order(key);
    for(int i=0;i<key.size();i++){
        for(int j=0;j<vec.size();j++){
            result.append(vec[j][ord[i]]);
        }
    }
    //qDebug()<<result<<" "<<vec.size()<<" "<<key.size();

    vec.clear();
    delete [] ord;
    return result;
}

QString ADFGVX_decode(QString cipher, QString key){
    if(cipher.isEmpty() || key.isEmpty() || cipher.size()%key.size()!=0)
        return QString("error");
    cipher=cipher.toUpper();

    QString QCryptogram, result;
    int *ord=order(key);
    int h=cipher.size()/key.size();
    //if(h==0)h=1;
    QChar vec[key.size()][h];

    int k=0;
    for(int j=0;j<key.size();j++) for(int i=0;i<h;i++) {
        vec[ord[j]][i]=cipher[k++];
        //qDebug()<<vec[j][i]<<j<<i;
    }

    for(int i=0;i<h;i++) for(int j=0;j<key.size();j++){
        QCryptogram.append(vec[j][i]);
    }
    //qDebug()<<QCryptogram<<QCryptogram.size();

    int i=0;
    while(i<QCryptogram.size()){
        if(QCryptogram[i]>='A' && QCryptogram[i]<='Z' && i+1<QCryptogram.size()) {
            result.append(find_2(QCryptogram[i],QCryptogram[i+1]));
            i+=2;
        } else {
            if(QCryptogram[i]!='-') result.append(QCryptogram[i]);
            i++;
        }
    }

    delete [] ord;
    return result;
}








