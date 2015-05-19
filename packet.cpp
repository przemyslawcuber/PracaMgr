#include "packet.h"

Packet::Packet()
{

}

Packet::~Packet()
{

}

void Packet::setSourceIp(const QString & sourceIp) {
    _sourceIp = sourceIp;
}

void Packet::setDestIp(const QString & destIp) {
    _destIp = destIp;
}

void Packet::setId(const qint16 id) {
    _id = id;
}

QString Packet::getSourceIp() const {
    return _sourceIp;
}

QString Packet::setDestIp() const {
    return _destIp;
}

qint16 Packet::getId() const {
    return _id;
}
