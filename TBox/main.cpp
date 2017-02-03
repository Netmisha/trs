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
         return a.exec();
}

