#ifndef SUITEINFO_H
#define SUITEINFO_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDomDocument>
/**
 * @brief The SuiteInfo (in JS jast Suite) class. Provide some methods to get suite info
 * and add or get some data to suite
 */
class SuiteInfo : public QObject
{
    Q_OBJECT
public:
    explicit SuiteInfo(QObject *parent = 0);
public slots:
    /**
     * @brief setPath: set path to file, which contains current suite
     * @param path a string argument
     */
    void setPath(QString path);
    /**
     * @brief setName: set name of current suite
     * @param name a string argument
     */
    void setName(QString name);
    /**
     * @brief getPath: get path to file, which contains current suite
     * @return path a string, consist path of current suite
     */
    Q_INVOKABLE QString getPath();
    /**
     * @brief getName: get name of current suite
     * @return name a string, consist name of current suite
     */
    Q_INVOKABLE QString getName();
    /**
     * @brief getCurrentDir: get dir, which contains current file
     * @return dir a string, consist folder name of current suite
     */
    Q_INVOKABLE QString getCurrentDir();
    /**
     * @brief setData: set user data to current suite, if data doesn`t exist, create it
     * @param tag a string argument
     * @param data a string argument
     */
    Q_INVOKABLE void setData(QString tag, QString data);
    /**
     * @brief getData: get user data from current suite
     * @param tag a string argument
     * @return data a string, consist data of current tag
     */
    Q_INVOKABLE QString getData(QString tag);
    /**
    * @brief delData: delete user data from current suite
     * @param tag a string argument
     * @return result of deleting data, string
    */
    Q_INVOKABLE QString delData(QString tag);
    /**
    * @brief isData: checks, whether data exist
     * @param tag a string argument
     * @return bool, result of checking data
    */
    Q_INVOKABLE bool isData(QString tag);
protected:
    QString currentPath;
    QString testName;
    bool defaultExit=true;
};

#endif // SUITEINFO_H
