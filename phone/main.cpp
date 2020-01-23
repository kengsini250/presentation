#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQml>
#include <QQmlEngine>
#include "network.h"
#include "phonevideo.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<NetWork>("Network.module",1,0,"Network");

    QQmlApplicationEngine engine;
    PhoneVideo* pv = new PhoneVideo;
    engine.addImageProvider(QLatin1String("pic"), pv);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
