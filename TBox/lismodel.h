#ifndef LISMODEL_H
#define LISMODEL_H
#include <qdebug.h>
#include <QStandardItem>
class LisModel
{
public:
    LisModel();
     QHash<int, QByteArray> m_roleNameMapping;
     QHash<int, QByteArray> roleNames() const;

};

#endif // LISMODEL_H
