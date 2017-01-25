#include "mainwindow.h"
#include <QApplication>
#include <reporter.h>
#include <export_txt.h>
#include <export_data.h>
#include <QQmlApplicationEngine>
#include <treemodel.h>
#include <QDir>
#include <database.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
          QQmlApplicationEngine engine;
          TreeModel obj;
          DataBase db;
          db.InitDB();
          db.getDataFromDB();
          obj.add_root();

          /*
               Reporter *O = new Reporter;
               export_txt *txt = new export_txt;
               Export_HTML *html_ = new Export_HTML;
               Export_data *E = new Export_data;
               O = E;
               O->export_data(txt);
               O->export_data(html_);
        */

         // export_txt *obj = new export_txt;
         // obj->init(path);
         // O.export_data(obj);
          engine.rootContext()->setContextProperty("DD",&obj);
          //qmlRegisterType<TreeModel>("models", 1, 0, "MyTreeModel" );
         // engine.rootContext()->setContextProperty("dataB",&dataB);
         engine.load(QUrl(QLatin1String("qrc:/report_window.qml")));
    //MainWindow w;
    //w.show();

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
