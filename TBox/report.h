#ifndef TRSMANAGER_H
#define TRSMANAGER_H

#include <QObject>
#include <QDirIterator>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QVector>
#include <QDebug>
extern QWebView * view;
namespace tags {
    const QString kTest="test";
    const QString kSuite="suite";
    const QString kName="name";
    const QString kExecution="execution";
}
class Report : public QObject
{
    Q_OBJECT
public:
    explicit Report(QObject *parent = 0);
signals:
public slots:
private:
    QObject * object;
};

#endif // TRSMANAGER_H
