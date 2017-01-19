


#ifndef QT_NO_WIDGETS
#include <QtWidgets/QApplication>
typedef QApplication Application;
#else
#include <QtGui/QGuiApplication>
typedef QGuiApplication Application;
#endif
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QQuickView>
#include <QtGui/QGuiApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QMessageBox>
#include <database.h>
#include <QStandardItem>
#include <treemodel.h>
#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QQmlApplicationEngine>

 int main(int argc, char **argv)
{
      QGuiApplication app(argc, argv);
      DataBase dataB;
      dataB.InitDB();
      dataB.getDataFromDB();
      QQmlApplicationEngine engine;
      TreeModel obj;
      engine.rootContext()->setContextProperty("DD",&obj);
      //qmlRegisterType<TreeModel>("models", 1, 0, "MyTreeModel" );
      engine.rootContext()->setContextProperty("dataB",&dataB);
      engine.load(QUrl(QLatin1String("qrc:/report_window.qml")));
      return app.exec();;
}
