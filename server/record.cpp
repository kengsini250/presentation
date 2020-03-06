#include "record.h"

Record::Record(QString filename)
{
    file.setFileName(filename);

}

void Record::getData(QString data)
{
    QString temp = data;
    if(temp == "DN")
    {
        updateFile("Close");
    }
    if(temp == "DY")
    {
        updateFile("Open");
    }

}

void Record::updateFile(QString data)
{
    QString timeData = QDateTime::currentDateTime().toString();
    file.open(QIODevice::Append| QIODevice::Text);
    QTextStream out(&file);
    out<<timeData<<"    "<<data<<"\n";
    file.close();
}
