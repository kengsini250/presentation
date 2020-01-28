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
    void connectToServer();
    void receivedata();

signals:
    void SendToServer(const Data&);
    void NewCamera(int);
    void NewDoor(int);
    void NewPhone(int);
};

#endif // CLIENT_H
