#include "phonevideo.h"

PhoneVideo::PhoneVideo():QQuickImageProvider(QQuickImageProvider::Image){

}

QImage PhoneVideo::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug()<<" QQuickImageProvider Image";
    qDebug()<<"id : "<<id;
    qDebug()<<"size : "<<size;
    qDebug()<<"phone video image size"<<img;
    return img;
}

QPixmap PhoneVideo::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug()<<" QQuickImageProvider Pixmap";
    return QPixmap::fromImage(img);
}
