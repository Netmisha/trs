#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDomDocument>
/**
 * @brief The TestInfo (in JS jast Test) class. Provide methods to get test info
 * and add or get some data to test. Also include events to finish test
 */
class TestInfo : public QObject
{
    Q_OBJECT
public:
    explicit TestInfo(QObject *parent = 0);
signals:
    void testFinish(QString);
    void testBegin(QString);
    void sendMessage(QString);
public slots:
    /**
     * @brief setPath: set path to file, which contains current test
     * @param path a string argument
     */
    void setPath(QString path);
    /**
     * @brief setName: set name of current test
     * @param name a string argument
     */
    void setName(QString name);
    /**
     * @brief getPath: get path to file, which contains current test
     * @return path a string, consist path of current test
     */
    Q_INVOKABLE QString getPath();
    /**
     * @brief getName: get name of current test
     * @return name a string, consist name of current test
     */
    Q_INVOKABLE QString getName();
    /**
     * @brief getCurrentDir: string; get dir, which contains current file
     * @return dir a string, consist folder name of current test
     */
    Q_INVOKABLE QString getCurrentDir();
    /**
     * @brief setData: set user data to current test, if data doesn`t exist, create it
     * @param tag a string argument
     * @param data a string argument
     */
    Q_INVOKABLE void setData(QString tag, QString data);
    /**
     * @brief getData: get user data from current test
     * @param tag a string argument
     * @return data a string, consist data of current tag
     */
    Q_INVOKABLE QString getData(QString tag);
    /**
    * @brief delData: delete user data from current test
     * @param tag a string argument
     * @return result of deleting data, string
    */
    Q_INVOKABLE QString delData(QString tag);
    /**
    * @brief clearAllData: delete all user data from current test
     * @return result of deleting data, string
    */
    Q_INVOKABLE QString clearAllData();
    /**
    * @brief isData: checks, whether data exist
     * @param tag a string argument
     * @return bool, result of checking data
    */
    Q_INVOKABLE bool isData(QString tag);
    /**
    * @brief BEGIN: send message, that test is start
    */
    Q_INVOKABLE void BEGIN();
    /**
    * @brief ExitOnFinish: specifies that the defult finishing of test will be ignored
    * and user invokes it manually
     * @param exit a boolen argument
    */
    Q_INVOKABLE void ExitOnFinish(bool exit);
    /**
    * @brief FAIL: finishing the test with fail message
     * @param msg a string argument, may doesn`t accept a paramet
    */
    Q_INVOKABLE void FAIL(QString msg="");
    /**
    * @brief SUCCESS: finishing the test with success message
     * @param msg a string argument, may doesn`t accept a paramet
    */
    Q_INVOKABLE void SUCCESS(QString msg="");
    /**
    * @brief VERIFY: compare two paramets, if false finishing the test with fail message
     * @param value a boolean argument
    */
    Q_INVOKABLE void VERIFY(bool value);
    /**
    * @brief isFirstRun: if the test first run
     * @param value a boolean argument
    */
    Q_INVOKABLE bool isFirstRun();
    void setFirstRun(bool value);
     Q_INVOKABLE void msg(QString msg);
protected:
    QString LoopMsg;
    QString currentPath;
    QString testName;
    bool defaultExit=true;
    bool finished=false;
    bool firstRun=false;
};

#endif // TEST_H
