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
         MainWindow w;
         if(argc>1) {
             QString command(argv[argc-1]);
             w.AddStartCommand(command);
         }
         return a.exec();
}

