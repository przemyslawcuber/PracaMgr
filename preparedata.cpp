#include "preparedata.h"
#include "conversationgroup.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

PrepareData::PrepareData()
{

}

PrepareData::~PrepareData()
{

}

void PrepareData::_prepareData(QList<Packet* > & dataSet) {
    for (int i = 0; i < dataSet.size(); i++) {
        Packet * packet = dataSet.at(i);
        bool exist = false;
        for (int j = 0; j < _conversationGroup.size(); j++) {
            if (packet->getId() == _conversationGroup.at(j)->_id) {
                _conversationGroup.at(j)->_conversationGroup.append(packet);
                exist = true;
                break;
            }
        }
        if (exist == false) {
            ConversationGroup * conversationGroup = new ConversationGroup();
            conversationGroup->_id = packet->getId();
            conversationGroup->_conversationGroup.append(packet);
            _conversationGroup.append(conversationGroup);
        }
    }
    qDebug() << _conversationGroup.size();
}

void PrepareData::writeData() {
    QString filename = "/home/cherubim/Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << "" << endl;
        for (int i = 0; i < _conversationGroup.size(); i++) {
            stream << i << " " << _conversationGroup.at(i)->_conversationGroup.size() << endl;
        }
    }
    file.close();
}
