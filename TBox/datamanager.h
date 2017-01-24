#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
namespace tags_name {
    const QString kXml = ".xml";
    const QString kName = "name";
    const QString kTest = "test";
}
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = 0);

signals:
public slots:
    Q_INVOKABLE void Set(QString, QString);
    Q_INVOKABLE QString Get(QString);
    Q_INVOKABLE void SetData(QString, QString);
    Q_INVOKABLE QString GetData(QString);
};

#endif // DATAMANAGER_H
