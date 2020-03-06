#ifndef RECORD_H
#define RECORD_H

#include <QFile>
#include <QDateTime>
#include <QTextStream>

class Record
{
private:
    QFile file;
public:
    Record(QString filename);
    void getData(QString data);
private:
    void updateFile(QString data);
};

#endif // RECORD_H
