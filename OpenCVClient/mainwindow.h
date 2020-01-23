#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QBuffer>
#include <QDataStream>
#include <QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "imgproc/types_c.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct{
    QByteArray pid;
    QByteArray data;
}Data;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    QString ipadress ;

    cv::VideoCapture v;
    QTimer*  timer;

    int pid = 123;
private slots:
    void video();
};
#endif // MAINWINDOW_H
