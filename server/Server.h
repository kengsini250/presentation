/**
 * @file Server.h
 * @author oppaiは愛 kengsini250@gmail.com)
 * @brief 
 * @version 1.3
 * @date 2020-01-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include <QDebug>
#include <QThread>

#include "Dataformat.h"
#include "client.h"
#include "clientthread.h"
#include "record.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server() = delete;
    explicit  Server(QMainWindow *p = nullptr)noexcept;
    ~Server();

protected:
    void incomingConnection(qintptr socketID)override;
private:
    /*!
     * @brief <マイコンの標識 , クライアント>
     * @param int マイコンの標識
     * @param Client* クライアント
     */
    QMap<int,Client*> CameraClient,PhoneClient,DoorClient;

    /*!
     * @brief SendToClient
     * @param client
     * @param data
     */
    void SendToClient(QMap<int,Client*> client , Data d);

    /*!
     * @brief <ソケット記述子 , マイコンの標識>
     * @param qintptr ソケット記述子
     * @param int マイコンの標識
     */
    QMap<qintptr,int> list;//<socket,pid>

    Record *file;

    //debug
    void display();

private slots:
    /**
     * @brief データーの転送　<br>
     * マイコンの標識によって、<br>
     * 転送ルールはここで追加します
     *  @param d 画像データ
     */
    void getData(const Data& d);

    /**
     * @brief getNewCamera <br>
     * カメラを追加
     * @param c クライアント
     * @param pid イコンの標識
     */
    void getNewCamera(Client* c,int pid);

    /**
     * @brief getNewDoor <br>
     * ドアを追加
     * @param c クライアント
     * @param pid イコンの標識
     */
    void getNewDoor(Client* c,int pid);

    /**
     * @brief getNewPhone <br>
     * スマホを追加
     * @param c クライアント
     * @param pid イコンの標識
     */
    void getNewPhone(Client* c,int pid);

signals:
    /**
     * @brief メインUIのアップデート
     * 
     * @param pid マイコンの標識
     * @param socketfd ソケット記述子
     */
    void sendNewClient(int pid,qintptr socketfd);

    /**
     * @brief メインUIのアップデート
     * 
     * @param cPid つなげているカメラの量
     * @param pPid つなげているスマホの量
     * @param dPid つなげているドアの量
     */
    void sendClientCount(int cPid,int pPid,int dPid);

    /**
     * @brief メインUIのアップデート
     * 
     * @param pid マイコンの標識
     * @param socketfd ソケット記述子
     */
    void sendDisconnect(int pid,qintptr socketfd);
};

#endif // SERVER_H
