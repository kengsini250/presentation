#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <client.h>
#include <QThread>

#include <QMetaType>

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
    void NewClient();

    void getData(const Data&);
    void getNewCamera(int i);
    void getNewDoor(int i);
    void getNewPhone(int i);
signals:
    void SendToServer(const Data&);
    void NewCamera(Client*,int);
    void NewDoor(Client*,int);
    void NewPhone(Client*,int);

    void sendExit(qintptr);
};

#endif // CLIENTTHREAD_H
