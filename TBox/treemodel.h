#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP
#include <qDebug>
#include <QStandardItemModel>
#include <database.h>
#include <QSqlDatabase>
#include <QStringList>
        class TreeModel : public QStandardItemModel
        {
            Q_OBJECT
        public:

            explicit TreeModel(QObject *parent = 0);
            virtual ~TreeModel() = default;
            QHash <int,int> indexes;
            QVector <QString> dbf;
            QVector<QString> year_nodes;

            TreeModel(QVector<QString>);

            enum MyTreeModel_Roles
            {
                MyTreeModel_Role_Name = Qt::DisplayRole,
                MyTreeModel_Role_Description = Qt::WhatsThisRole
            };
            struct node{
                QStandardItem *prev;
                QModelIndex index;
                QStandardItem *curr;
                QString name;
            };
            QVector <node> leaf;
            QSqlDatabase db;
            QVector<QStringList> db_list;
            QStringList db_col;
            QString row_data;
            QStandardItem *filt;
            QStandardItem *rep;
            void ConnectToDb();

            //void TreeModel::ConnectToDb();

            void FillTreeData(QStandardItem *root);
            void add_root();
            QStandardItem *root;
            QHash<int, QByteArray> roleNames() const override;

        private:

            QHash<int, QByteArray> m_roleNameMapping;

        };

#endif // MYTREEMODEL_HPP
