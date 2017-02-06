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
#include "report.h"
#include "mainsetting.h"
#include "datamanager.h"
#include "testinfo.h"
#include "filesave.h"
#include "highlighter.h"
#include "selectfolderdialog.h"
#include <QWebInspector>
#include <QDesktopServices>
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
    void writeLog(QString);
private slots:
private:
    DataBase O;
    ExportHTML H;
    Ui::MainWindow *ui;
    QObject *object;
    Report *report;
    TRSCore *trscore;
    TestInfo *testinfo;
    QQuickView* qmlView;
    SelectFolderDialog *selectFolder;
};

#endif // MAINWINDOW_H
