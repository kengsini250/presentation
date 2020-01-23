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
    QList<Client*> CameraClient,PhoneClient,DoorClient;
//    QThread* mythread;
private slots:
    void getData(Data d);
    void getNewCamera(Client*,int i);
    void getNewDoor(Client*,int i);
    void getNewPhone(Client*,int i);
};

#endif // SERVER_H
