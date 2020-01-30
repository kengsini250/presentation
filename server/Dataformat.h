/**
 * @file Dataformat.h
 * @author oppaiは愛 kengsini250@gmail.com)
 * @brief データーのフォーマット
 * @version 1.3
 * @date 2020-01-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DATAFORMAT_H
#define DATAFORMAT_H

//マイコンの標識
#define PID_HEAD '!'

//データフォーマットのルール
/**
 * @define START データーの始まる標識
 */
#define START '%'
/**
 * @define MID マイコンの標識とデーターの間の標識
 */
#define MID '|'
/**
 * @define END データーの終わる標識
 */
#define END '&'

//指示データのフォーマット
#define Raspberry_HEAD 'P'
#define Door_HEAD 'D'

#include <QByteArray>
#include <QtAlgorithms>

typedef struct{
    QByteArray pid;
    //QByteArray size;
    QByteArray data;
}Data;

/*!
 * @brief DataFormat
 * クライアントからもらったデータを処理する
 * @param data 処理したデータ
 * @param temp 処理する前のデータ
 */
void DataFormat(QByteArray data,Data* temp);


#endif // DATAFORMAT_H
