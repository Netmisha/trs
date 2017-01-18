#ifndef MAINTREE_H
#define MAINTREE_H

#include <QObject>
#include <QVector>

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
    Q_INVOKABLE QVector<QString> tests();
    Q_INVOKABLE QVector<MainTree *> suites();
    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setName(QString);
    Q_INVOKABLE void addTest(QString);
    Q_INVOKABLE void addSuite(MainTree *);
private:
    QString path_;
    QString name_;
    QVector<QString> tests_;
    QVector<MainTree *> suites_;
};

#endif // MAINTREE_H
