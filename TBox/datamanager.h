#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
namespace tags_name {
    const QString kXml = ".xml";
    const QString kName = "name";
    const QString kDescription = "description";
    const QString kTag = "tag";
    const QString kDisable = "disable";
    const QString kExecution = "execution";
    const QString kResult = "result";
    const QString kRepeat = "repeat";
    const QString kPause = "pause";
    const QString kMaxTime = "maxTime";
    const QString kTest = "test";
    const QString kData = "data";
}
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = 0);

signals:
public slots:
    void Set(QString, QString);
    QString AddTest(QString, QString, QString, QString, QString, QString, QString);
    QString AddSuite(QString, QString);
    QString Get(QString);
private:
};

#endif // DATAMANAGER_H
