#include "mainwindow.h"
#include <QApplication>
#include <reporter.h>
#include <QQmlApplicationEngine>
#include <treemodel.h>
#include <QDir>
#include <database.h>
#include <reportform.h>
#include <QObject>
#include <databasemanager.h>
#include <exporthtml.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
         QQmlApplicationEngine *engine = new QQmlApplicationEngine ;

         MainWindow w;

          return a.exec();

          // ExportHTML d_html;




/*
    DataBase O;
          ExportHTML H;
          O.setEngi(engine);

          QObject::connect(&O,SIGNAL(PassHTMLdata(QVector<QVector<QStringList*>>,QStringList,int,QString)),&H,SLOT(ReceiveHTMLdata(QVector<QVector<QStringList*>>,QStringList,int,QString)));
          engine->rootContext()->setContextProperty("DD",&O);
          engine->load(QUrl(QLatin1String("qrc:/report_window.qml")));
          return a.exec();
*/

}

    /*
          TreeModel obj;
          DataBase db;
          db.InitDB();
          db.getDataFromDB();
          obj.add_root();


               Reporter *O = new Reporter;
               export_txt *txt = new export_txt;
               Export_HTML *html_ = new Export_HTML;
               Export_data *E = new Export_data;
               O = E;
               O->export_data(txt);
               O->export_data(html_);


         // export_txt *obj = new export_txt;
         // obj->init(path);
         // O.export_data(obj);

          //qmlRegisterType<TreeModel>("models", 1, 0, "MyTreeModel" );
         // engine.rootContext()->setContextProperty("dataB",&dataB);
         engine.load(QUrl(QLatin1String("qrc:/report_window.qml")));

*/


