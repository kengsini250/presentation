#include "clientthread.h"

ClientThread::ClientThread(QObject *parent,int id) : QObject(parent)
{
//    qRegisterMetaType<Data>("Data");
    socketID = id;
    client = new Client(socketID);
}

ClientThread::~ClientThread()
{
}

void ClientThread::NewClient()
{
    connect(client,&Client::NewCamera,[&](int pid){
        qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
        emit NewCamera(client,pid);
    });
    connect(client,&Client::NewDoor,[&](int pid){
        qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
        emit NewDoor(client,pid);
    });
    connect(client,&Client::NewPhone,[&](int pid){
        qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
        emit NewPhone(client,pid);
    });
    connect(client,&Client::SendToServer,[&](const Data& d){
        emit SendToServer(d);
    });

    connect(client,&QTcpSocket::disconnected,[=]{
        client->close();
        emit sendExit(socketID);
    });

}
