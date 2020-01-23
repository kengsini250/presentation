#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#include <QTimer>

typedef struct{
    QByteArray pid;
    QByteArray data;
}Data;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    QString ipadress ;
    int PID ;

    QByteArray getIPtoUtf8();
    QByteArray getPorttoUtf8();

    QByteArray unEncodePic;
public slots:
    void display();
};

#endif // MAINWINDOW_H
