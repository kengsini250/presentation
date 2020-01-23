#include "network.h"

#define PID_HEAD '!'
#define PID 345

#define START '%'
#define MID '|'
#define END '&'

QImage img;

NetWork::NetWork(QObject *parent) : QObject(parent)
{
    tcpClient = new QTcpSocket(this);

    connect(tcpClient,&QTcpSocket::readyRead,[=]{

        QByteArray temp = tcpClient->readAll();
            while(tcpClient->waitForReadyRead(90)){
                temp += tcpClient->readAll();
        }

        QString stemp = QString::fromLatin1(temp.data(),temp.size());
        QByteArray second = QByteArray::fromBase64(stemp.toLatin1());
        img.loadFromData(second,"JPEG");
        emit pic();
    });
}

void NetWork::sendIpPort()
{
    tcpClient->connectToHost("192.168.2.175",55555,QTcpSocket::ReadWrite);
//    tcpClient->connectToHost("10.42.0.1",55555,QTcpSocket::ReadWrite);
    tcpClient->waitForConnected();
    if(tcpClient->state()==QTcpSocket::ConnectedState)
        tcpClient->write(PID_HEAD + QString::number(PID).toUtf8());
}

void NetWork::sendToServer(QString str)
{
    tcpClient->write(START+QString::number(PID).toUtf8()+MID+str.toUtf8()+END);
}
