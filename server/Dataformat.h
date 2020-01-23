#ifndef DATAFORMAT_H
#define DATAFORMAT_H

#define PID_HEAD '!'

#define START '%'
#define MID '|'
#define END '&'

#define Raspberry_HEAD 'P'
#define Door_HEAD 'D'

#include <QByteArray>
#include <QtAlgorithms>

typedef struct{
    QByteArray pid;
    //QByteArray size;
    QByteArray data;
}Data;

void DataFormat(QByteArray data,Data* temp);

#endif // DATAFORMAT_H
