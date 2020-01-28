#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new Server(this);

    connect(server,&Server::sendNewClient,[&](int pid,qintptr socketID){
        ui->textBrowser->append("new client");
        ui->textBrowser->append("pid : " + QString::number(pid) + "   socket : " + QString::number(socketID));
    });
    connect(server,&Server::sendDisconnect,[&](int pid,qintptr socketID){
        ui->textBrowser->append("disconnect");
        ui->textBrowser->append("pid : " + QString::number(pid) + "   socket : " + QString::number(socketID));
    });
    connect(server,&Server::sendClientCount,[&](int camera,int phone,int door){
        ui->textBrowser->append("-----------------------------------");
        ui->textBrowser->append("Camera : " + QString::number(camera));
        ui->textBrowser->append("Phone : " + QString::number(phone));
        ui->textBrowser->append("Door : " + QString::number(door));
        ui->textBrowser->append("-----------------------------------");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

