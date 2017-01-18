#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trsmanager.h"
#include <QDebug>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QQmlContext>
#include <QQmlEngine>
#include <QUrl>
#include <QVariant>
#include <QQuickView>
#include <QQuickItem>
#include <QBoxLayout>

QWebView *view;
class MyJavaScriptOperations : public QObject {
    Q_OBJECT
public:
    MyJavaScriptOperations(){

        qDebug() << "In constructor";
    }

public:
    Q_INVOKABLE void submit()
    {
        QVariant f1result = view->page()->mainFrame()->evaluateJavaScript("test()");
        qDebug() << f1result.toString();
    }

    Q_INVOKABLE void display(){

        qDebug() << "In display method";

    }
    Q_INVOKABLE QString ParseFolder(QString path)
    {
        qDebug() << "In ParseFolder method";
        QDirIterator it(path, QDirIterator::Subdirectories);
        QString files;
        while (it.hasNext()) {
            files+=it.next()+"\n";
        }
        return files;
    }

};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = ui->webView;
    view->resize(400, 500);
    view->page()->mainFrame()->addToJavaScriptWindowObject("myoperations", new MyJavaScriptOperations);
    view->load(QUrl("qrc:/html/test.html"));
    view->setVisible(false);
    QQuickView* qmlView = new QQuickView();
    MyJavaScriptOperations trs;
    qmlView->engine()->rootContext()->setContextProperty("trs", &trs);
    QWidget* container = QWidget::createWindowContainer(qmlView, ui->centralWidget);
    qmlView->setSource(QUrl("qrc:/MainForm.ui.qml"));
    ui->verticalLayout->addWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.moc"
