#ifndef MAINTREE_H
#define MAINTREE_H

#include <QObject>
#include <QVector>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStandardItemModel>

namespace tags {
    const QString kTest="test";
    const QString kSuite="suite";
    const QString kName="name";
    const QString kExecution="execution";
}
struct TestItem{
    QString name;
    QStandardItem * item;
};
class MainTree : public QObject
{
    Q_OBJECT
public:
    explicit MainTree(QObject *parent = 0);
    ~MainTree();
signals:

public slots:
    Q_INVOKABLE QString path();
    Q_INVOKABLE QString name();
    Q_INVOKABLE QVector<TestItem> tests();
    Q_INVOKABLE QVector<MainTree *> suites();
    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setName(QString);
    Q_INVOKABLE void addTest(QString);
    Q_INVOKABLE void addSuite(MainTree *);
    QStringList getTestsName(QString);
    QString getSuiteName(QString);
private:
    QString path_;
    QString name_;
    QStandardItem * item_;
    QVector<TestItem> tests_;
    QVector<MainTree *> suites_;
};

#endif // MAINTREE_H
