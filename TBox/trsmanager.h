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
class TRSManager : public QObject
{
    Q_OBJECT
public:
    explicit TRSManager(QObject *parent = 0);
signals:
    void RunNext();
    void writeMSG(QString);
public slots:
    static void Run(QString);

private:
};

#endif // TRSMANAGER_H
