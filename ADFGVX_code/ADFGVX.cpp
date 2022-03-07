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
    //if(tmp.isEmpty()) tmp=QString(QChar(c));
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

bool valid(QChar c){
    if((c>='A' && c<='Z') || (c>='0' && c<='9'))
        return true;
    else return false;
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

    QString QCryptogram1;

    int *ord=order(key);
    for(int i=0;i<key.size();i++){
        for(int j=0;j<vec.size();j++){
            QCryptogram1.append(vec[j][ord[i]]);
        }
    }
    //qDebug()<<result<<" "<<vec.size()<<" "<<key.size();
    QChar c;
    for(int i=0;i<QCryptogram1.size();i++){
        if(valid(QCryptogram1[i]) && i+1<QCryptogram1.size()){
            c=QCryptogram1[i];
            while(!(valid(QCryptogram1[i+1]))){
                //result.append(QCryptogram1[i++]);
                i++;
            }
            result.append(find_2(c,QCryptogram1[i+1]));
            i++;
        }
    }
    vec.clear();
    delete [] ord;
    return result;
}

QString ADFGVX_decode(QString cipher, QString key){
    if(cipher.isEmpty() || key.isEmpty())
        return QString("error");
    cipher=cipher.toUpper();

    QString QCryptogram, QCryptogram1, result;
    int *ord=order(key);
    int h=0;

    for(int i=0;i<cipher.size();i++){
        if(valid(cipher[i])){
            QCryptogram1.append(find(cipher[i].toLatin1()));
        }
    }
    int mod=QCryptogram1.size()%key.size();
    //qDebug()<<QCryptogram1;

    h=QCryptogram1.size()/key.size();
    if(mod!=0)h++;

    QChar vec[key.size()][h];
    //qDebug()<<key.size()<<h;

    int k=0;
    for(int j=0;j<key.size();j++) for(int i=0;i<h;i++) {
        if(mod==0 || !(i==h-1 && ord[j]>=mod)){
            vec[ord[j]][i]=QCryptogram1[k++];
        } else {
            vec[ord[j]][i]='-';
        }
        //qDebug()<<vec[ord[j]][i]<<j<<i;
    }

    for(int i=0;i<h;i++) for(int j=0;j<key.size();j++){
        QCryptogram.append(vec[j][i]);
    }
    //qDebug()<<QCryptogram<<QCryptogram.size();

    QChar c;
    for(int i=0;i<QCryptogram.size();i++){
        if(valid(QCryptogram[i]) && i+1<QCryptogram.size()){
            c=QCryptogram[i];
            while(!(valid(QCryptogram[i+1]))){
                i++;
            }
            result.append(find_2(c,QCryptogram[i+1]));
            //qDebug()<<find_2(c,QCryptogram[i+1]);
            i++;
        }
    }
    delete [] ord;
    return result;
}








