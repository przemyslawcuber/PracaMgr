#ifndef PACKET_H
#define PACKET_H

#include <QString>

class Packet
{
public:
    Packet();
    ~Packet();

    void setSourceIp(const QString & sourceIp);
    void setDestIp(const QString & destIp);
    void setId(const qint16 id);
    QString getSourceIp() const;
    QString setDestIp() const;
    qint16 getId() const;


private:
    QString _sourceIp;
    QString _destIp;
    qint16 _id;
};

#endif // PACKET_H
