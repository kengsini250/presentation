#include "client.h"

Client::Client(QObject *p,qintptr id):QTcpSocket(p){
    socketID = id;
    connectToServer();
}

void Client::connectToServer()
{
    setSocketDescriptor(socketID);
    connect(this,&Client::readyRead,this,&Client::receivedata);
}

void Client::receivedata()
{
    QByteArray msg = readAll();
    while(waitForReadyRead(90)){
        msg += readAll();
    }

    //qDebug()<<Q_FUNC_INFO<<msg;
    if(msg[0] == PID_HEAD){

        QByteArray temp;
        if(msg[1] == '1'){
            for(auto p = msg.begin()+1;p!=msg.end();p++)
                temp.push_back(*p);
            emit NewCamera(temp.toInt());

        }else if(msg[1] == '2' ){
            for(auto p = msg.begin()+1;p!=msg.end();p++)
                temp.push_back(*p);
            emit NewDoor(temp.toInt());

        }else if(msg[1] == '3' ){
            for(auto p = msg.begin()+1;p!=msg.end();p++)
                temp.push_back(*p);
            emit NewPhone(temp.toInt());
        }
        temp.clear();

    }else if(msg[0] == START){
        Data data;
        DataFormat(msg,&data);
        emit SendToServer(data);
    }
}
