#ifndef READPCAPFILE_H
#define READPCAPFILE_H

#include <QObject>


class ReadPcapFile : public QObject
{
    Q_OBJECT

public:
    ReadPcapFile();
    ~ReadPcapFile();
    void setFileName(QString fileName);

private:
    QString _fileName;

public slots:
    void readFile(const QString &fileName);

signals:
    void resultReady(const QString &result);
};


#endif // READPCAPFILE_H
