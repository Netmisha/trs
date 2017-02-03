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
#include "highlighter.h"
#include "selectfolderdialog.h"
#include <QWebInspector>
#include <QDesktopServices>
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
private slots:
private:
    Ui::MainWindow *ui;
    QObject *object;
    TRSManager *trs;
    TRSCore *trscore;
    TestInfo *testinfo;
    QQuickView* qmlView;
    SelectFolderDialog *selectFolder;
};

#endif // MAINWINDOW_H
