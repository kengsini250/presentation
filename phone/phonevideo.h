#ifndef PHONEVIDEO_H
#define PHONEVIDEO_H

#include <QDebug>
#include <QImage>
#include <QQuickImageProvider>
#include "network.h"

class PhoneVideo :public QQuickImageProvider
{
public:
    explicit PhoneVideo();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // PHONEVIDEO_H
