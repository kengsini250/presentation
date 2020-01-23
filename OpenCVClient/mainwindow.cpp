#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PID_HEAD '!'

#define START '%'
#define MID '|'
#define END '&'

//#define ip "127.0.0.1"
#define ip "10.192.137.101"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    v.set(3, 480);
    v.set(4, 320);
    v.set(5, 15);

    tcpClient = new QTcpSocket(this);
    connect(ui->Ok,&QAbstractButton::clicked,[=]{

        tcpClient->connectToHost(ip,55555,QTcpSocket::ReadWrite);
        tcpClient->waitForConnected(10000);

        if(tcpClient->state()==QTcpSocket::ConnectedState)
        {
            //send pid
            tcpClient->write(PID_HEAD + QString::number(pid).toUtf8());
        }

        connect(tcpClient,&QTcpSocket::readyRead,
                [=]{
            QByteArray temp = tcpClient->readAll();
        });

        //video
        timer = new QTimer;
        timer->start(50);
        connect(timer,SIGNAL(timeout()),this,SLOT(video()));
    });
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::video()
{
    if(!v.isOpened()){
        v.open(0);
    }
    cv::Mat frame;
    v>>frame;

    if(!frame.empty()){
        cvtColor(frame,frame,CV_BGR2RGB);
//        cvtColor(frame,frame,CV_BGR2GRAY);
        QByteArray Pic;//用于传送
        QBuffer buf(&Pic);//用于IO处理
        QImage img((const unsigned char*)frame.data,
                   frame.cols, frame.rows,QImage::Format_RGB888);
//                   frame.cols, frame.rows,QImage::Format_Grayscale8);
        img.save(&buf,"JPEG");

        //qCompress（压缩）
        // QByteArray first = qCompress(Pic,1);
        //toBase64（加密）
        QByteArray second = Pic.toBase64();

        tcpClient->write(START + QString::number(pid).toUtf8() + MID + second +END);

        ui->video->setPixmap(QPixmap::fromImage(img));
    }
    else
        qDebug()<<"No video data !";
}

