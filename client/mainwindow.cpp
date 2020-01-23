#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PID_HEAD '!'

#define START '%'
#define MID '|'
#define END '&'

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->ipAddress->setText("192.168.1.2");
    ui->ipAddress->setText("127.0.0.1");
    ui->Port->setText("55555");

    //QTimer* timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MainWindow::display);
    //timer->start(1000);

    tcpClient = new QTcpSocket(this);
    connect(ui->Ok,&QAbstractButton::clicked,[=]{
        PID = ui->pidEdit->text().toInt();
        QString ip_temp = ui->ipAddress->text();

        ui->textBrowser->append(ip_temp);
        unsigned short port = ui->Port->text().toUShort();

        tcpClient->connectToHost(ip_temp,port,QTcpSocket::ReadWrite);
        tcpClient->waitForConnected(10000);

        if(tcpClient->state()==QTcpSocket::ConnectedState)
        {
            ui->Ok->setDisabled(true);
            ui->textBrowser->append(QString::number(port));
            ui->textBrowser->append("connected!");

            //send pid
            tcpClient->write(PID_HEAD + QString::number(PID).toUtf8());
        }

        connect(tcpClient,&QTcpSocket::readyRead,
                [=]{
            QByteArray msg = tcpClient->readAll();
//            while(tcpClient->waitForReadyRead(1)){
//                msg += tcpClient->readAll();
//            }
            QString stemp = QString::fromLatin1(msg.data(),msg.size());
            //QByteArray second;
            unEncodePic = QByteArray::fromBase64(stemp.toLatin1());

            QImage img;
            img.loadFromData(unEncodePic,"JPEG");
             ui->video->setPixmap(QPixmap::fromImage(img));
             unEncodePic.clear();
//            QByteArray first = qUncompress(second);
//            QImage img;
//            img.loadFromData(second,"JPEG");

//            ui->video->setPixmap(QPixmap::fromImage(img));
        });
    });

    connect(ui->pushButton,&QAbstractButton::clicked,[=]{
        tcpClient->write(START + QString::number(PID).toUtf8() + MID + ui->lineEdit->text().toUtf8()+END);
        ui->lineEdit->clear();
    });

    connect(ui->cclean,&QAbstractButton::clicked,[=]{
        ui->textBrowser->clear();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::getIPtoUtf8()
{
    QHostAddress myip = tcpClient->peerAddress();
    qDebug()<<myip.toString().toUtf8();
    return myip.toString().toUtf8();
}

QByteArray MainWindow::getPorttoUtf8()
{
    unsigned short myport = tcpClient->peerPort();
    qDebug()<<QString::number(myport).toUtf8();
    return QString::number(myport).toUtf8();
}

void MainWindow::display()
{
    QImage img;
    img.loadFromData(unEncodePic,"JPEG");
     ui->video->setPixmap(QPixmap::fromImage(img));
     unEncodePic.clear();
}
