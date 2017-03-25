#ifndef TRSCORE_H
#define TRSCORE_H

#include <QObject>
#include <QProcess>
#include <QTest>
#include <QTestEventList>
#include <Windows.h>
#include <QPixmap>
#include <QScreen>
#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QFileInfo>
#include <QDirIterator>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QVector>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <testinfo.h>
#include <QSysInfo>
#include <psapi.h>

extern QWebView * view;
#define MOUSEEVENTF_HWHEEL 4096
/**
 * @brief The TRSCore (in JS jast Box) class. Provide methods to simulation
 * all mouse and keyboard events, also to get screen parametrs, features to work with
 * filesystem and registry
 */
class TRSCore : public QObject
{
    Q_OBJECT
public:
    explicit TRSCore(QObject *parent = 0);
signals:
    void log(QString);
    void fail(QString);
public slots:
    /**
     * @brief StartApp: runs application
     * @param waitForStart a bool argument
     * @param path a string argument
     */
    bool StartApp(QString path, bool waitForStart=true);
    /**
     * @brief CloseApp: closes application
     * @param waitForClose a bool argument
     * @param windowName a string argument
     */
    void CloseApp(QString windowName, bool waitForClose=true);
    /**
     * @brief SetOnTop: sets window with some name on top
     * @param windowName a string argument
     */
    void SetOnTop(QString windowName);
    /**
     * @brief waitForStart: returns name of window that is on top
     */

    bool waitForStart(QString windowName, ulong maxTime=0);
    /**
     * @brief GetTopWnd: returns name of window that is on top
     * @return string, window name
     */
    QString GetTopWnd();
    /**
     * @brief Sleep: suspends current process
     * @param time an integer argument
     */
    void Sleep(int time);

    /**
     * @brief Sleep: suspends current process
     * @param time an integer argument
     */
    int TimeElapsed();
    /**
     * @brief GetScreenWidth: returns width of screen
     * @return integer, window width
     */
    int GetScreenWidth();
    /**
     * @brief GetScreenHeight: returns height of screen
     * @return integer, screen height
     */
    int GetScreenHeight();
    /**
     * @brief GetAppWidth: returns width of window with some name
     * @param windowName a string argument
     * @return integer, window width
     */
    int GetAppWidth(QString windowName);
    /**
     * @brief GetAppHeight: returns height of window with some name
     * @param windowName a string argument
     * @return integer, window height
     */
    int GetAppHeight(QString windowName);
    /**
     * @brief GetAppRect: returns rectangle of window with some name
     * @param windowName a string argument
     * @return QString, contains JSON obect
     */
    QString GetAppRect(QString windowName);
    /**
     * @brief GetAppRect: returns rectangle of window with some name
     * @param windowName a string argument
     * @return QString, contains JSON obect
     */
    QString GetChildRect(QString windowName, QString childName);
    /**
     * @brief SetAppPos: sets window position
     * @param windowName a string argument
     * @param x a integer argument
     * @param y a integer argument
     */
    void SetAppPos(QString windowName, int x, int y);
	/**
     * @brief SetAppSize: sets window size
     * @param windowName a string argument
     * @param w a integer argument
     * @param h a integer argument
     */
    void SetAppSize(QString windowName, int w, int h);
	/**
     * @brief SetAppRect: sets window rectangle
     * @param windowName a string argument
     * @param x a integer argument
     * @param y a integer argument
     */
    void SetAppRect(QString windowName, int x, int y, int w, int h);
    /**
     * @brief WindowMinimize: minimaze window with some name
     * @param windowName a string argument
     */
    void WindowMinimize(QString windowName);
    /**
     * @brief WindowMaximize: maximaze window with some name
     * @param windowName a string argument
     */
    void WindowMaximize(QString windowName);
    /**
     * @brief WindowRestore: restore window with some name
     * @param windowName a string argument
     */
    void WindowRestore(QString windowName);
    /**
     * @brief CloseWindow: closes window with some name
     * @param windowName a string argument
     */
    void CloseWindow(QString windowName);
    /**
     * @brief KeyDown: simulates press down on keyboard button
     * @param dkey an integer argument
     */
    void KeyDown(int dkey);
    /**
     * @brief KeyUp: simulates press up on keyboard button
     * @param dkey an integer argument
     */
    void KeyUp(int dkey);
    /**
     * @brief KeyPress: simulates click on keyboard button
     * @param dkey an integer argument
     */
    void KeyPress(int dkey);
    /**
     * @brief SetMousePos: sets mouse cursor to some position
     * @param x an integer argunemt
     * @param y an integer argunemt
     */
    void SetMousePos(int x, int y);
    /**
     * @brief MouseMove: simulates mouse move to some position with some speed
     * @param x an integer argunemt
     * @param y an integer argunemt
     * @param pause an integer argunemt, pause between mouse position change
     */
    void MouseMove(int x, int y, int pause);
    /**
     * @brief MouseDown: simulates press down on mouse button
     * @param button an integer argument, o - left button, 1 - right button
     */
    void MouseDown(int button);
    /**
     * @brief MouseUp: simulates press up on mouse button
     * @param button an integer argument, o - left button, 1 - right button
     */
    void MouseUp(int button);
    /**
     * @brief MouseClick: simulates click on mouse button
     * @param button an integer argument, o - left button, 1 - right button
     */
    void MouseClick(int button);
    /**
     * @brief MouseClickA: simulates click on mouse button
     * @param button an integer argument, o - left button, 1 - right button
     */
    void MouseClickA(int x, int y,int button);
    /**
     * @brief MouseWheelDown: simulates mouse scroll to right on 120 pixels
     */
    void MouseWheelDown();
    /**
     * @brief MouseWheelUp: simulates mouse scroll to right on 120 pixels
     */
    void MouseWheelUp();
    /**
     * @brief MouseWheelLeft: simulates mouse scroll to right on 120 pixels
     */
    void MouseWheelLeft();
    /**
     * @brief MouseWheelRight: simulates mouse scroll to right on 120 pixels
     */
    void MouseWheelRight();
    /**
     * @brief PrintScreen: makes print screen and save to file
     * @param file a string argument
     */
    void PrintScreen(QString file);
    /**
     * @brief exec: makes print screen of current size and save to file
     * @param x an integer argunemt
     * @param y an integer argunemt
     * @param w an integer argunemt
     * @param h an integer argunemt
     * @param file a string argument
     */
    void PrintScreenA(int x, int y, int w, int h, QString file);
    /**
     * @brief exec: executes user command in ShellExecute
     * @param command a string argument
     * @return int, result of command execution
     */
    int exec(QString command);
    /**
     * @brief getList: returns all files and folders of current path
     * @param path a string argument
     * @return string list, which contains all files of folder and sub folders
     */
    QStringList getList(QString path);
    /**
     * @brief getFullList: returns all files, folders of current path and theirs contents
     * @param path a string argument
     * @return string list, which contains all files of folder, sub folders and theirs contents
     */
    QStringList getFullList(QString path);
    /**
     * @brief isFile: checks if current path is file
     * @param path a string argument
     * @return bool, true if it is a file
     */
    bool isFile(QString path);
    /**
     * @brief isDir: checks if current path is folder
     * @param path a string argument
     * @return bool, true if it is a folder
     */
    bool isDir(QString path);
    /**
     * @brief isExist: checks if file or folder exist
     * @param path a string argument
     * @return bool, true if exist
     */
    bool isExist(QString path);
    /**
     * @brief isReadOnly: checks if file or folder is read only
     * @param path a string argument
     * @return bool, true if read only
     */
    bool isReadOnly(QString path);
    /**
     * @brief getSize: gets size of file or folder
     * @param path a string argument
     * @return int64, size of file or folder
     */
    qint64 getSize(QString path);
    /**
     * @brief delDir: removes folder and all its file
     * @param dir a string argument
     * @return bool, true if folder removed
     */
    bool delDir(QString dir);
    /**
     * @brief delFile: removes file
     * @param file a string argument
     * @return bool, true if file removed
     */
    bool delFile(QString file);
    /**
     * @brief isKeyExist: checks if the key exist
     * @param rKey a string argument
     * @return bool, true if key exist
     */
    bool isKeyExist(QString rKey);
    /**
     * @brief getKeyValue: gets value of current key
     * @param rKey a string argument
     * @return string, value of currnet key
     */
    QVariant getKeyValue(QString rKey);
    /**
     * @brief setKeyValue: sets value for current key
     * @param rKey a string argument
     * @param value a string argument
     */
    void setKeyValue(QString rKey, QVariant value);
    /**
     * @brief List: returns all child keys from registry for current key
     * @param rKey a string argument
     * @return string, all child keys
     */
    QString List(QString rKey);
    /**
     * @brief getFileData: reads some file and return its data
     * @param filePath a string argument
     * @return string, data of file
     */
    QString getFileData(QString filePath);
    /**
     * @brief isAlive: checks if the application is running
     * @param windowName a string argument
     * @param emitFail a bool argument, false as default
     * @return bool, true if the application is running
     */
    bool isAlive(QString windowName, bool emitFail=false);
    /**
     * @brief isWin: checks if the current OS is Windows
     * @return bool, true if the OS Win
     */
    bool isWin();
    /**
     * @brief isMac: checks if the current OS is Mac
     * @return bool, true if the OS Mac
     */
    bool isMac();
    /**
     * @brief getBitDepth: returns bit depth of OS
     * @return int, 32 or 64
     */
    QString getBitDepth();
    /**
     * @brief getMemoryStatus(): returns memory status
     * @return string, json which contains information about memory
     */
    QString getMemoryStatus();
    /**
     * @brief getAppMemory: returns memory status
     * @return string, json which contains information about memory
     */
    QString getAppMemory(QString windowName);
    bool isImageEqual(QString path,QString path2);
    unsigned int getQuantColor(QString path,int R,int G,int B);
private:
    QProcess *process;
    POINT current_pos;
    HWND windowHandle;
    QTime elapseTimer;
};

#endif // TRSCORE_H
