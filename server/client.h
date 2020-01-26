#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include "Dataformat.h"

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    Client(qintptr id = -1);
    Client(QObject* p = nullptr,qintptr id = -1);
    qintptr getSocketID(){
        return socketID;
    }

private:
    void connectToServer();
    void receivedata();
    qintptr socketID;

signals:
    void SendToServer(Data);
    void NewCamera(int);
    void NewDoor(int);
    void NewPhone(int);
};

#endif // CLIENT_H
