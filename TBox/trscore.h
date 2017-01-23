#ifndef TRSCORE_H
#define TRSCORE_H

#include <QObject>
#include <QProcess>
#include <QTest>
#include <QTestEventList>
#include <Windows.h>
#include <QPixmap>
#include <QScreen>

#define MOUSEEVENTF_HWHEEL 4096

class TRSCore : public QObject
{
    Q_OBJECT
public:
    explicit TRSCore(QObject *parent = 0);

signals:

public slots:
    void StartApp(QString);
    void CloseApp();
    void Sleep(int);
    int GetScreenWidth();
    int GetScreenHeight();
    void WindowMinimize();
    void WindowMaximize();
    void WindowRestore();
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
private:
    QProcess *process;
    POINT current_pos;
};

#endif // TRSCORE_H
