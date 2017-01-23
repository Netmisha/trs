#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



/*
        ParseFolder("D:/Projects/trs/TBox/Tests");
    }

            virtual ~MyTreeModel() = default;

            enum MyTreeModel_Roles
            {
                MyTreeModel_Role_Name = Qt::DisplayRole
            };

            QHash<int, QByteArray> roleNames() const override{
                return m_roleNameMapping;
            }

        private:
            QStandardItem * Parse(QString path) {
                QDirIterator it(path, QDirIterator:: NoIteratorFlags);
                QStandardItem * suite;
                MainTree * itemTree = new MainTree();
                while (it.hasNext()) {
                    it.next();
                    if(it.filePath().contains("/.") || it.filePath().contains("/.")) {
                        continue;
                    }
                    else {
                        if(it.filePath().contains(".xml")) {
                            suite= new QStandardItem (itemTree->getSuiteName(it.filePath()));
                            QStringList list=itemTree->getTestsName(it.filePath());
                            for(auto& iter:list) {
                                QStandardItem * test= new QStandardItem (iter);
                                suite->appendRow(test);
                            }
                        }
                        if(it.fileInfo().isDir()) {
                            suite->appendRow(Parse(it.filePath()));
                        }
                    }
                }
                return suite;
            }
            void ParseFolder(QString path)
            {
                QStandardItem * root= new QStandardItem (QString("Tests"));
                root->appendRow(Parse(path));
                this->appendRow(root);
            }
*/
