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
    QMap<int,Client*> CameraClient,PhoneClient,DoorClient;//<pid,Client>
    QMap<qintptr,int> list;//<socket,pid>

    void display();
private slots:
    void getData(const Data&);
    void getNewCamera(Client*,int);
    void getNewDoor(Client*,int);
    void getNewPhone(Client*,int);

signals:
//      int pid
//     qintptr socket
    void sendNewClient(int,qintptr);

//    camera phone door
    void sendClientCount(int,int,int);

//    int pid
//    qintptr socket
    void sendDisconnect(int,qintptr);
};

#endif // SERVER_H
