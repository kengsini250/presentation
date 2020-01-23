#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QString>
#include <QImage>
#include <QBuffer>
#include <QDataStream>

extern QImage img;

typedef struct{
    QByteArray pid;
    QByteArray data;
}Data;

class NetWork : public QObject
{
    Q_OBJECT
public:
    explicit NetWork(QObject *parent = nullptr);
    Q_INVOKABLE void sendIpPort();
    Q_INVOKABLE void sendToServer(QString str);
private:
    QTcpSocket *tcpClient;
signals:
    //test
    void pic();
};

#endif // NETWORK_H
