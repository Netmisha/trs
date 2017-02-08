#include "trscore.h"
#include <QDesktopWidget>
#include <QObject>
TRSCore::TRSCore(QObject *parent) : QObject(parent) {
    process=new QProcess();
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

void TRSCore::WindowMinimize(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    ShowWindow(windowHandle, SW_MINIMIZE);
}

void TRSCore::WindowMaximize(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    ShowWindow(windowHandle, SW_MAXIMIZE);
}

void TRSCore::WindowRestore(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
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
int TRSCore::exec(QString command) {
    return system(command.toStdString().c_str());
}
QStringList TRSCore::getList(QString path) {
    QStringList files;
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        it.next();
        if (it.filePath().contains("/.") || it.filePath().contains("/.")) {
            continue;
        }
        else {
            files.push_back(it.filePath());
        }
    }
    return files;
}
QStringList TRSCore::getFullList(QString path) {
    QStringList files;
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        if (it.filePath().contains("/.") || it.filePath().contains("/.")) {
            continue;
        }
        else {
            files.push_back(it.filePath());
        }
    }
    return files;
}
bool TRSCore::isFile(QString path) {
    QFileInfo file(path);
    return file.isFile();
}
bool TRSCore::isDir(QString path) {
    QFileInfo file(path);
    return file.isDir();
}
bool TRSCore::isExist(QString path) {
    QFileInfo file(path);
    return file.exists();
}
bool TRSCore::isReadOnly(QString path) {
    QFileInfo file(path);
    return !file.isWritable();
}
qint64 TRSCore::getSize(QString path) {
    if(isFile(path)) {
        QFileInfo file(path);
        return file.size();
    }
    else {
        qint64 size=0;
        QDirIterator it(path, QDirIterator::Subdirectories);
        QFileInfo file;
        while (it.hasNext()) {
            it.next();
            if (it.filePath().contains("/.") || it.filePath().contains("/.")) {
                continue;
            }
            else {
                file.setFile(it.filePath());
                size+=file.size();
            }
        }
        return size;
    }
}
bool TRSCore::delDir(QString path) {
    if(!QDir(path).exists()) {
        return false;
    }
    QDir qd(path);
    qd.removeRecursively();
    return true;
}
bool TRSCore::delFile(QString path) {
    if(!QFile(path).exists()) {
        return false;
    }
    QFile file(path);
    file.remove();
    return true;
}
