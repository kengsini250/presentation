#include "showimage.h"

ShowImage::ShowImage(QObject *parent) : QObject(parent)
{
    pic = new PhoneVideo;
}

void ShowImage::setImage(QImage image)
{
    pic->img = image;
    emit callQmlRefeshImg();
}
