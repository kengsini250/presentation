#include "Server.h"


Server::Server(QMainWindow *p) noexcept:QTcpServer(p)
{
    listen(QHostAddress::Any,55555);
    file = new Record("recode.txt");
}

Server::~Server()
{
    delete file;
}

void Server::incomingConnection(qintptr socketID)
{
    qDebug()<<Q_FUNC_INFO<<"new incommingConnection";
    ClientThread* newConnection = new ClientThread(0,socketID);
    QThread* mythread = new QThread;
    newConnection->moveToThread(mythread);
    mythread->start();

    connect(mythread,&QThread::finished,newConnection,&QObject::deleteLater);
    connect(mythread,&QThread::started,newConnection,&ClientThread::NewClient);

    connect(newConnection,&ClientThread::NewCamera,this,&Server::getNewCamera);
    connect(newConnection,&ClientThread::NewDoor,this,&Server::getNewDoor);
    connect(newConnection,&ClientThread::NewPhone,this,&Server::getNewPhone);
    connect(newConnection,&ClientThread::SendToServer,this,&Server::getData);

    connect(newConnection,&ClientThread::sendExit,[=](qintptr socketID){
        int pid = list.find(socketID).value();
        emit sendDisconnect(pid,socketID);
        qDebug()<<pid<<" disconnect";
        CameraClient.remove(pid);
        PhoneClient.remove(pid);
        DoorClient.remove(pid);
        list.remove(pid);
        display();
    });

    qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
}

void Server::SendToClient(QMap<int, Client *> client,Data d)
{
    auto p = client.begin();
    while(p!=client.end()){
        p.value()->write(d.data);
        p++;
    }
}

void Server::display()
{
    //    qDebug()<<"-----------------------------------";
    //    qDebug()<<"Camera : "<<CameraClient.size();
    //    qDebug()<<"Door : "<<DoorClient.size();
    //    qDebug()<<"Phone : "<<PhoneClient.size();
    //    qDebug()<<"-----------------------------------";
    emit sendClientCount(
                CameraClient.size(),
                PhoneClient.size(),
                DoorClient.size());
}

void Server::getData(const Data& d)
{
    if(d.pid.at(0) == '1'){
        if(!PhoneClient.empty())
            SendToClient(PhoneClient,d);
    }

    if(d.pid.at(0) == '2'){
        //        qDebug()<<Q_FUNC_INFO<<"from door";
    }

    if(d.pid.at(0) == '3'){
        if(!DoorClient.isEmpty()){
            if(d.data.at(0) == 'D')
                SendToClient(DoorClient,d);
            //make recode file
            file->getData(d.data);
        }
    }
    if(!CameraClient.isEmpty()){
        if(d.data.at(0) == 'P'){
            qDebug()<<"send to  camera" << d.data;
            SendToClient(CameraClient,d);
        }
    }
}

void Server::getNewCamera(Client*c,int pid)
{
    emit sendNewClient(pid,c->socketDescriptor());
    CameraClient.insert(pid,c);
    list.insert(c->socketDescriptor(),pid);
    display();
}

void Server::getNewDoor(Client*c,int pid)
{
    emit sendNewClient(pid,c->socketDescriptor());
    DoorClient.insert(pid,c);
    list.insert(c->socketDescriptor(),pid);
    display();
}

void Server::getNewPhone(Client*c,int pid)
{
    emit sendNewClient(pid,c->socketDescriptor());
    PhoneClient.insert(pid,c);
    list.insert(c->socketDescriptor(),pid);
    display();
}

