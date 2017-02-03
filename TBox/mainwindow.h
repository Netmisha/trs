#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQmlContext>
#include <QQmlEngine>
#include <QWebInspector>
#include <QUrl>
#include <QObject>
#include <QVariant>
#include <QQuickView>
#include <QQuickItem>
#include <QBoxLayout>
#include <QTreeView>
#include <QVector>
#include "maintree.h"
#include "trscore.h"
#include "trsmanager.h"
#include "mainsetting.h"
#include "datamanager.h"
#include "testinfo.h"
#include "filesave.h"
#include <QQmlApplicationEngine>
#include <database.h>
#include <reportform.h>
#include <databasemanager.h>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void writeMSG(QString);

private:
    void CreateHtml();
    DataBase O;
    ExportHTML H;
    Ui::MainWindow *ui;
    QObject *object;
    TRSCore a;
};

#endif // MAINWINDOW_H
