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
    void KeyDown(int dkey){
        keybd_event(dkey, 0, 0, 0);
    }
    void KeyUp(int dkey){
        keybd_event(dkey, 0, KEYEVENTF_KEYUP, 0);
    }
    void KeyPress(int dkey){
        KeyDown(dkey);
        KeyUp(dkey);
    }
    void SetMousePos(int x, int y) {
        current_pos.x = x;
        current_pos.y = y;
        SetCursorPos(x, y);
    }
    void MouseMove(int x, int y, int pause) {
        auto fun = [&](int _x){ return (_x - current_pos.x)*(y - current_pos.y) / (x - current_pos.x) + current_pos.y; };
        for (int i = current_pos.x; i < x; i++) {
            Sleep(pause);
            SetCursorPos(i, fun(i));
        }
        GetCursorPos(&current_pos);
    }
    void MouseDown(int button) {
        if (button) {
            mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
        }
        else {
            mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
        }
    }
    void MouseUp(int button) {
        if (button) {
            mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
        }
        else {
            mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
        }
    }
    void MouseClick(int button) {
        if (button) {
            mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
            mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
        }
        else {
            mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
        }
    }
    void MouseWheelDown() {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -WHEEL_DELTA, 0);
    }
    void MouseWheelUp() {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA, 0);
    }
    void MouseWheelLeft() {
        mouse_event(MOUSEEVENTF_HWHEEL, 0, 0, -WHEEL_DELTA, 0);
    }
    void MouseWheelRight() {
        mouse_event(MOUSEEVENTF_HWHEEL, 0, 0, WHEEL_DELTA, 0);
    }
    void PrintScreen(QString file) {
        QPixmap originalPixmap;
        QScreen *screen = QGuiApplication::primaryScreen();
        originalPixmap.save(file);
        originalPixmap = screen->grabWindow(0);
    }
    void PrintScreenA(int x, int y, int w, int h, QString file){
        QPixmap originalPixmap;
        QScreen *screen = QGuiApplication::primaryScreen();
        originalPixmap.save(file);
        originalPixmap = screen->grabWindow(0);
    }
private:
    QProcess *process;
    POINT current_pos;
};

#endif // TRSCORE_H
