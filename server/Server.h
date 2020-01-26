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
    QMap<qintptr,Client*> CameraClient,PhoneClient,DoorClient;
    QMap<qintptr,int> list;
private slots:
    void getData(Data d);
    void getNewCamera(Client*,int);
    void getNewDoor(Client*,int);
    void getNewPhone(Client*,int);
};

#endif // SERVER_H
