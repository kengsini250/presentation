#include "clientthread.h"

ClientThread::ClientThread(QObject *parent,int id) : QObject(parent)
{
    qRegisterMetaType<Data>("Data");
    socketID = id;
    client = new Client(socketID);
}

ClientThread::~ClientThread()
{
}

void ClientThread::NewClient()
{
//    client = new Client(socketID);
    connect(client,&Client::NewCamera,this,&ClientThread::getNewCamera);
    connect(client,&Client::NewDoor,this,&ClientThread::getNewDoor);
    connect(client,&Client::NewPhone,this,&ClientThread::getNewPhone);
    connect(client,&Client::SendToServer,this,&ClientThread::getData);

    connect(client,&QTcpSocket::disconnected,[=]{
        emit sendExit(socketID);
    });
}

void ClientThread::getData(Data d)
{
//    qDebug()<<"Client Thread Class : "<<QThread::currentThreadId();
    emit SendToServer(d);
}

void ClientThread::getNewCamera(int i)
{
    qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
    emit NewCamera(client,i);
}

void ClientThread::getNewDoor(int i)
{
    qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
    emit NewDoor(client,i);
}

void ClientThread::getNewPhone(int i)
{
    qDebug()<<Q_FUNC_INFO<<"Client Thread Class : "<<QThread::currentThreadId();
    emit NewPhone(client,i);
}
