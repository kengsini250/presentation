/**
 * @file client.h
 * @author oppaiは愛 kengsini250@gmail.com)
 * @brief クライアント
 * @version 1.3
 * @date 2020-01-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include "Dataformat.h"

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    Client(qintptr id );
    ~Client();

private:
    /*!
     * @brief receivedata <br>
     * マイコンからのデータがサーバーに送る
     */
    void receivedata();

signals:
    /*!
     * @brief SendToServer <br>
     * 画像がサーバーに送る
     * @param data 画像データ
     */
    void SendToServer(const Data& data);

    /*!
     * @brief NewCamera <br>
     * マイコンの標識がサーバーに送る
     * @param pid マイコンの標識
     */
    void NewCamera(int pid);

    /*!
     * @brief NewDoor <br>
     * マイコンの標識がサーバーに送る
     * @param pid マイコンの標識
     */
    void NewDoor(int pid);

    /*!
     * @brief NewPhone <br>
     * マイコンの標識がサーバーに送る
     * @param pid マイコンの標識
     */
    void NewPhone(int pid);
};

#endif // CLIENT_H
