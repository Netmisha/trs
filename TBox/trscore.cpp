#include "trscore.h"
#include <QDesktopWidget>
#include <QObject>
TRSCore::TRSCore(QObject *parent) : QObject(parent) {
    process=new QProcess(this);
}
void TRSCore::StartApp(QString appName) {
    process->start(appName);
    process->waitForStarted();
}
void TRSCore::CloseApp() {
    process->close();
}

void TRSCore::SetOnTop(QString windowName)
{
    windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    SetForegroundWindow(windowHandle);
    while (GetForegroundWindow() != windowHandle)
    {
        windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
        SetForegroundWindow(windowHandle);
        Sleep(200);
    }
}
void TRSCore::Sleep(int msec) {
    QTest::qSleep(msec);
}

int TRSCore::GetScreenWidth()
{
    QDesktopWidget desktop;
    return desktop.geometry().width();
}

int TRSCore::GetScreenHeight()
{
    QDesktopWidget desktop;
    return desktop.geometry().height();
}

void TRSCore::WindowMinimize()
{
    ShowWindow(windowHandle, SW_MINIMIZE);
}

void TRSCore::WindowMaximize()
{
    ShowWindow(windowHandle, SW_MAXIMIZE);
}

void TRSCore::WindowRestore()
{
    ShowWindow(windowHandle, SW_RESTORE);
}
void TRSCore::KeyDown(int dkey){
    keybd_event(dkey, 0, 0, 0);
}
void TRSCore::KeyUp(int dkey){
    keybd_event(dkey, 0, KEYEVENTF_KEYUP, 0);
}
void TRSCore::KeyPress(int dkey){
    KeyDown(dkey);
    KeyUp(dkey);
}
void TRSCore::SetMousePos(int x, int y) {
    current_pos.x = x;
    current_pos.y = y;
    SetCursorPos(x, y);
}
void TRSCore::MouseMove(int x, int y, int pause) {
    auto fun = [&](int _x){ return (_x - current_pos.x)*(y - current_pos.y) / (x - current_pos.x) + current_pos.y; };
    for (int i = current_pos.x; i < x; i++) {
        Sleep(pause);
        SetCursorPos(i, fun(i));
    }
    GetCursorPos(&current_pos);
}
void TRSCore::MouseDown(int button) {
    if (button) {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
    }
}
void TRSCore::MouseUp(int button) {
    if (button) {
        mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
    }
}
void TRSCore::MouseClick(int button) {
    if (button) {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
    }
}
void TRSCore::MouseWheelDown() {
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -WHEEL_DELTA, 0);
}
void TRSCore::MouseWheelUp() {
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA, 0);
}
void TRSCore::MouseWheelLeft() {
    mouse_event(MOUSEEVENTF_HWHEEL, 0, 0, -WHEEL_DELTA, 0);
}
void TRSCore::MouseWheelRight() {
    mouse_event(MOUSEEVENTF_HWHEEL, 0, 0, WHEEL_DELTA, 0);
}
void TRSCore::PrintScreen(QString file) {
    QPixmap originalPixmap;
    QScreen *screen = QGuiApplication::primaryScreen();
    originalPixmap = screen->grabWindow(0);
    originalPixmap.save(file);
}
void TRSCore::PrintScreenA(int x, int y, int w, int h, QString file){
    QPixmap originalPixmap;
    QScreen *screen = QGuiApplication::primaryScreen();
    originalPixmap = screen->grabWindow(0);
    QRect rect(x, y, w, h);
    QPixmap cropped = originalPixmap.copy(rect);
    cropped.save(file);
}
