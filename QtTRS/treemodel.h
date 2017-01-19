#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP
#include <qDebug>
#include <QStandardItemModel>


        class TreeModel : public QStandardItemModel
        {
            Q_OBJECT
        public:
            explicit TreeModel(QObject *parent = 0);
            virtual ~TreeModel() = default;

            enum MyTreeModel_Roles
            {
                MyTreeModel_Role_Name = Qt::DisplayRole,
                MyTreeModel_Role_Description = Qt::WhatsThisRole
            };

            QHash<int, QByteArray> roleNames() const override;
            void addEntry( const QString& name, const QString& type, const QString& description );
            void addChild(QString info);
                        QStandardItem* getBranch( const QString& branchName );
        private:

            QHash<int, QByteArray> m_roleNameMapping;

        };

#endif // MYTREEMODEL_HPP
