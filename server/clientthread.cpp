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
//    connect(client,&Client::NewCamera,this,&ClientThread::getNewCamera);
//    connect(client,&Client::NewDoor,this,&ClientThread::getNewDoor);
//    connect(client,&Client::NewPhone,this,&ClientThread::getNewPhone);
//    connect(client,&Client::SendToServer,this,&ClientThread::getData);

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

void ClientThread::getData(const Data& d)
{
    //    qDebug()<<"Client Thread Class : "<<QThread::currentThreadId();
    emit SendToServer(d);
}

void ClientThread::getNewCamera(int pid)
{
    qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
    emit NewCamera(client,pid);
}

void ClientThread::getNewDoor(int pid)
{
    qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
    emit NewDoor(client,pid);
}

void ClientThread::getNewPhone(int pid)
{
    qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
    emit NewPhone(client,pid);
}
