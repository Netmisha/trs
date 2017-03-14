#include "trscore.h"
#include <QDesktopWidget>
#include <QObject>
TRSCore::TRSCore(QObject *parent) : QObject(parent) {
    process=new QProcess();
}


QString TRSCore::getFileData(QString filePath){
    QFile *xmlFile = new QFile(filePath);
    QString streamData;
    QMessageBox msgBox;
    if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        msgBox.setText("Could not open XML file. Check your path");
        msgBox.exec();
        return "";
    }
    QTextStream stream(xmlFile);
    while(!stream.atEnd()){
        streamData.append(stream.readLine());
    }
    xmlFile->close();
    return streamData;

}
bool TRSCore::StartApp(QString appName) {
    process->start(appName);
    if(process->error()<5) {
        qDebug()<<process->errorString();
        return false;
    }
    else {
        process->waitForStarted();
        return true;
    }
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
QString TRSCore::GetTopWnd()
{
    HWND wind = GetForegroundWindow();
    wchar_t buff[2048];
    GetWindowText(wind, buff, 2048);
    return QString::fromWCharArray(buff);

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

int TRSCore::GetAppWidth(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    RECT win_rect;
    if(GetWindowRect(windowHandle, &win_rect)) {
        return win_rect.right-win_rect.left;
    }
    return -1;
}

int TRSCore::GetAppHeight(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    RECT win_rect;
    if(GetWindowRect(windowHandle, &win_rect)) {
        return win_rect.bottom-win_rect.top;
    }
    return -1;
}
QRect TRSCore::GetAppRect(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    RECT win_rect;
    QRect qwin_rect(QPoint(-1, -1),QPoint(-1,-1));
    if(GetWindowRect(windowHandle, &win_rect)) {
        qwin_rect.setTopLeft(QPoint(win_rect.top, win_rect.left));
        qwin_rect.setBottomRight(QPoint(win_rect.bottom,win_rect.right));
    }
    return qwin_rect;
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
void TRSCore::CloseWindow(QString windowName)
{
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    SendMessage(windowHandle, WM_SYSCOMMAND, SC_CLOSE, 0);
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

bool TRSCore::isKeyExist(QString key)
{
    key.replace("/","\\");
    QSettings regSetting(key.left(key.lastIndexOf("\\")), QSettings::NativeFormat);
    return regSetting.contains(key.right(key.length()-key.lastIndexOf("\\")-1));
}

QVariant TRSCore::getKeyValue(QString key)
{
    key.replace("/","\\");
    QSettings regSetting(key.left(key.lastIndexOf("\\")), QSettings::NativeFormat);
    return regSetting.value(key.right(key.length()-key.lastIndexOf("\\")-1));
}

void TRSCore::setKeyValue(QString key, QVariant value)
{
    key.replace("/","\\");
    QSettings regSetting(key.left(key.lastIndexOf("\\")), QSettings::NativeFormat);
    regSetting.setValue(key.right(key.length()-key.lastIndexOf("\\")-1), value);
}
QString TRSCore::List(QString path)
{
    path.replace("/","\\");
    if(path=="") {
        return "Invalid path.";
    }
    QString data;
    QSettings regSetting(path, QSettings::NativeFormat);
    QStringList list=regSetting.allKeys();
    for(auto& it:list) {
        data+=path+"\\"+it+"\n";
    }
    if(data.size()>1000000) {
        return "A lot of data";
    }
    return data;
}

