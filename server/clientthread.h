/**
 * @file clientthread.h
 * @author oppaiは愛 kengsini250@gmail.com)
 * @brief マルチスレッド
 * @version 1.3
 * @date 2020-01-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <client.h>
#include <QThread>

//#include <QMetaType>

class ClientThread : public QObject
{
    Q_OBJECT
public:
    explicit ClientThread(QObject *parent = nullptr,int id = -1);
    ~ClientThread();
private:
    qintptr socketID;
    Client* client;

public slots:
    /*!
     * @brief NewClient <br>
     * マルチスレッドの入り口
     */
    void NewClient();

    /*!
     * @brief データの転送 <br>
     * lambdaを使ってもいい
     */
    void getData(const Data&);
    void getNewCamera(int i);
    void getNewDoor(int i);
    void getNewPhone(int i);

signals:
    /*!
     * @brief SendToServer <br>
     * マイコンからのデータがサーバーに送る
     * @param data 画像データ
     */
    void SendToServer(const Data& data);

    /*!
     * @brief   NewCamera <br>
     * マイコンの標識とクライアントがサーバーに送る
     * @param Client* クライアント
     * @param pid マイコンの標識
     */
    void NewCamera(Client*,int pid);

    /*!
     * @brief   NewDoor <br>
     * マイコンの標識とクライアントがサーバーに送る
     * @param Client* クライアント
     * @param pid マイコンの標識
     */
    void NewDoor(Client*,int pid);

    /*!
     * @brief   NewPhone
     * マイコンの標識とクライアントがサーバーに送る
     * @param Client* クライアント
     * @param pid マイコンの標識
     */
    void NewPhone(Client*,int pid);

    /*!
     * @brief sendExit <br>
     * マイコンの標識とクライアントがサーバーに送る
     * @param socketfd ソケット記述子
     */
    void sendExit(qintptr socketfd);
};

#endif // CLIENTTHREAD_H
