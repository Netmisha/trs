#ifndef LISMODEL_H
#define LISMODEL_H

#include <QStandardItem>
class LisModel:public QStandardItemModel
{
public:
    LisModel();
     QHash<int, QByteArray> m_roleNameMapping;
     QHash<int, QByteArray> roleNames() const;
     void add_root(){
         QStandardItem *root = new QStandardItem(QString("Data"));
         this->appendRow(root);
     }
};

#endif // LISMODEL_H
