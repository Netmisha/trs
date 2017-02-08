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

#define MOUSEEVENTF_HWHEEL 4096

class TRSCore : public QObject
{
    Q_OBJECT
public:
    explicit TRSCore(QObject *parent = 0);

signals:
    void log(QString);
public slots:
    void StartApp(QString);
    void CloseApp();
    void SetOnTop(QString);
    void Sleep(int);
    int GetScreenWidth();
    int GetScreenHeight();
    void WindowMinimize(QString);
    void WindowMaximize(QString);
    void WindowRestore(QString);
    void CloseWindow(QString);
    void KeyDown(int dkey);
    void KeyUp(int dkey);
    void KeyPress(int dkey);
    void SetMousePos(int x, int y);
    void MouseMove(int x, int y, int pause);
    void MouseDown(int button);
    void MouseUp(int button);
    void MouseClick(int button);
    void MouseWheelDown();
    void MouseWheelUp();
    void MouseWheelLeft();
    void MouseWheelRight();
    void PrintScreen(QString file);
    void PrintScreenA(int x, int y, int w, int h, QString file);
    int exec(QString);
    QStringList getList(QString);
    QStringList getFullList(QString);
    bool isFile(QString);
    bool isDir(QString);
    bool isExist(QString);
    bool isReadOnly(QString);
    qint64 getSize(QString);
    bool delDir(QString);
    bool delFile(QString);
private:
    QProcess *process;
    POINT current_pos;
    HWND windowHandle;
};

#endif // TRSCORE_H
