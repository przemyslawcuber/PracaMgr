#ifndef PREPAREDATA_H
#define PREPAREDATA_H

#include <QList>
#include <QVector>
#include "packet.h"
#include "conversationgroup.h"

class PrepareData
{
public:
    PrepareData();
    ~PrepareData();

    void _prepareData(QList<Packet *> &dataSet);
    void writeData();
    QVector<ConversationGroup *> _conversationGroup;
};

#endif // PREPAREDATA_H
