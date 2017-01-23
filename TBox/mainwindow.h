#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQmlContext>
#include <QQmlEngine>
#include <QWebInspector>
#include <QUrl>
#include <QVariant>
#include <QQuickView>
#include <QQuickItem>
#include <QBoxLayout>
#include <QTreeView>
#include <QVector>
#include "maintree.h"
#include "trscore.h"

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
    void RunNext();
    void writeMSG(QString);
private slots:
    void on_actionStart_triggered();

    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
    QObject *object;

    TRSCore a;
};

#endif // MAINWINDOW_H
