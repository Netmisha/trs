#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) :
    QStandardItemModel(parent)
{

    m_roleNameMapping[MyTreeModel_Role_Name] = "name_role";
    m_roleNameMapping[MyTreeModel_Role_Description] = "description_role";

    addEntry( "Option A", "Data", "This is Option A" );
    addEntry( "2017", "Year", "das" );


}


void TreeModel::addEntry( const QString& name, const QString& type, const QString& description )
{
    auto childEntry = new QStandardItem( name );
    childEntry->setData( description, MyTreeModel_Role_Description );
    QStandardItem* entry = getBranch( type);
    entry->appendRow( childEntry );
}

void TreeModel::addChild(QString info){



}
QStandardItem *TreeModel::getBranch(const QString &branchName)
{
    QStandardItem* entry;
    auto entries = this->findItems( branchName );
    if ( entries.count() > 0 )
    {
        entry = entries.at(0);
    }
    else
    {
        entry = new QStandardItem( branchName );
        this->appendRow( entry );
    }
    return entry;
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    return m_roleNameMapping;
}
