#include "Server.h"


Server::Server(QMainWindow *p) noexcept:QTcpServer(p)
{
    listen(QHostAddress::Any,55555);
}

Server::~Server()
{}

void Server::incomingConnection(qintptr socketID)
{
    qDebug()<<Q_FUNC_INFO<<"new incommingConnection";
    ClientThread* newConnection = new ClientThread(0,socketID);
    QThread* mythread = new QThread;
    newConnection->moveToThread(mythread);
    mythread->start();

    connect(mythread,&QThread::finished,this,&QObject::deleteLater);

    connect(mythread,&QThread::started,newConnection,&ClientThread::NewClient);

    connect(newConnection,&ClientThread::NewCamera,this,&Server::getNewCamera);
    connect(newConnection,&ClientThread::NewDoor,this,&Server::getNewDoor);
    connect(newConnection,&ClientThread::NewPhone,this,&Server::getNewPhone);
    connect(newConnection,&ClientThread::SendToServer,this,&Server::getData);

    qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
}

void Server::getData(Data d)
{
    //qDebug()<<d.data;
    if(d.pid.at(0) == '1'){
        qDebug()<<Q_FUNC_INFO<<"from camera";

        if(!PhoneClient.empty()){
            qDebug()<<Q_FUNC_INFO<<"to phone ----  phone size : "<<PhoneClient.size();
            for(auto p = PhoneClient.begin();p!= PhoneClient.end();p++){
                (*p)->write(d.data);
            }
        }
    }

    if(d.pid.at(0) == '2'){
        qDebug()<<"from door";
    }

    if(d.pid.at(0) == '3'){
        qDebug()<<"from phone";

        if(!DoorClient.isEmpty()){
            if(d.data.at(0) == 'D'){
                qDebug()<<"to Door";
                for(auto p = DoorClient.begin();p!=DoorClient.end();p++){
                    (*p)->write(d.data);
                }
            }

            if(d.data.at(0) == 'P'){
                qDebug()<<"to Camera";
                for(auto p = CameraClient.begin();p!=CameraClient.end();p++)
                    (*p)->write(d.data);
            }
        }
    }
}

void Server::getNewCamera(Client*c,int i)
{
    qDebug()<<i;
    qDebug()<<c->getSocketID();
    CameraClient.push_back(c);
}

void Server::getNewDoor(Client*c,int i)
{
    qDebug()<<i;
    qDebug()<<c->getSocketID();
    DoorClient.push_back(c);
}

void Server::getNewPhone(Client*c,int i)
{
    qDebug()<<i;
    qDebug()<<c->getSocketID();
    PhoneClient.push_back(c);
}

