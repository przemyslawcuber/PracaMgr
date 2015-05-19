#ifndef CONVERSATIONGROUP_H
#define CONVERSATIONGROUP_H

#include "packet.h"
#include <QVector>

class ConversationGroup
{
public:
    ConversationGroup();
    ~ConversationGroup();
    qint16 _id;
    QVector<Packet* > _conversationGroup;
};

#endif // CONVERSATIONGROUP_H
