#include "trscore.h"
#include <QDesktopWidget>
#include <QObject>
#include <qDebug>
TRSCore::TRSCore(QObject *parent) : QObject(parent) {
    process=new QProcess();
    elapseTimer.start();
}
unsigned int TRSCore::getQuantColor(QString path,int R,int G,int B){
    if(R >255 || G>255 || B>255 ){
        emit fail("Strange color");
    }
    if(R <0 || G<0 || B<0 ){
        emit fail("Strange color");
    }
     int countColor = 0;
    QImage img = QImage(path);
   //emit log("Image width:" + QString::number(img.width()) + " height:"+QString::number(img.height()) + " size:"+QString::number(img.width() * img.height()));
    for(int i=0;i<img.height();i++){
        for(int j=0;j<img.width();j++){
            QColor color(img.pixel(j,i));
            if(color.red() == R && color.green() == G && color.blue()== B){
                countColor++;
            }
        }
    }
    return countColor;
}

void TRSCore::setRunAll(bool type)
{
    runAll=type;
}
bool TRSCore::isImageEqual(QString path,QString path2){
     QImage img = QImage(path);
     QImage img2 = QImage(path2);
     if(img.size() != img2.size()){
         return 0;
     }
     QVector<int> img_rgb; // contains img_rgba values
     //linear stretching
     for(int i=0;i<img.width();i++){
         for(int j=0;j<img.height();j++){
             QColor color(img.pixel(i,j)); //QColor (RGB)
             img_rgb.push_back(color.red());
             img_rgb.push_back(color.green());
             img_rgb.push_back(color.blue());
         }
     }
       QVector<int> img2_rgb; // contains img2_rgba values
       for(int i=0;i<img2.width();i++){
           for(int j=0;j<img2.height();j++){
               QColor color(img2.pixel(i,j)); //QColor (RGB)
               img2_rgb.push_back(color.red());
               img2_rgb.push_back(color.green());
               img2_rgb.push_back(color.blue());
           }
       }
    int MSE=0; //Mean Squared Error
    int sum=0;
    for(int i=0;i<img_rgb.size();i++){
        sum+=((img_rgb[i]-img2_rgb[i]) *(img_rgb[i]-img2_rgb[i]))+((img_rgb[i+1]-img2_rgb[i+1])*
                (img_rgb[i+1]-img2_rgb[i+1]))+((img_rgb[i+2]-img2_rgb[i+2]) *(img_rgb[i+2]-img2_rgb[i+2]));
        i+=2;
    }
    MSE = (float)sum/(float)(img.height()*img.width());
    float percent = ((float)(100 * MSE))/(float)img_rgb.size();
    if(percent > 1.5 || MSE < 0){ // 1.5 percent of image which can be damaged
       return 0;
    }else{
       return 1;
    }
}
QString TRSCore::getFileData(QString filePath){
    QFile *xmlFile = new QFile(filePath);
    QString streamData;
    if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        return "";
    }
    QTextStream stream(xmlFile);
    while(!stream.atEnd()){
        streamData.append(stream.readLine());
    }

    xmlFile->close();
    return streamData;

}
bool TRSCore::isAlive(QString windowName, bool emitFail)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return false;
    }
    windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        if(emitFail) {
            emit fail("Application did not run.");
        }
        return false;
    }
    return true;
}

bool TRSCore::isWin()
{
    if(QSysInfo::windowsVersion()!=QSysInfo::WV_None) {
        return true;
    }
    return false;
}

bool TRSCore::isMac()
{
    if(QSysInfo::macVersion()!=QSysInfo::MV_None) {
        return true;
    }
    return false;
}

QString TRSCore::getBitDepth()
{
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    BOOL bIsWow64 = FALSE;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
    if(NULL != fnIsWow64Process) {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64)) {
            return "";
        }
    }
    return bIsWow64?"64":"32";
}

QString TRSCore::getAppMemory(QString windowName)
{
    HWND wndHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    DWORD PID;
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;
    QString res="";
    GetWindowThreadProcessId(wndHandle, &PID);
    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION, FALSE, PID );
    if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) ) {
        res="{\"WorkingSetSize\": ";
        res.append(QString::number(pmc.WorkingSetSize)+",\"PageFaultCount\": ");
        res.append(QString::number(pmc.PageFaultCount)+",\"PagefileUsage\": ");
        res.append(QString::number(pmc.PagefileUsage)+",\"PeakPagefileUsage\": ");
        res.append(QString::number(pmc.PeakPagefileUsage)+",\"PeakWorkingSetSize\": ");
        res.append(QString::number(pmc.PeakWorkingSetSize)+",\"QuotaNonPagedPoolUsage\": ");
        res.append(QString::number(pmc.QuotaNonPagedPoolUsage)+",\"QuotaPagedPoolUsage\": ");
        res.append(QString::number(pmc.QuotaPagedPoolUsage)+",\"QuotaPeakNonPagedPoolUsage\": ");
        res.append(QString::number(pmc.QuotaPeakNonPagedPoolUsage)+",\"QuotaPeakPagedPoolUsage\": ");
        res.append(QString::number(pmc.QuotaPeakPagedPoolUsage)+",}");
    }
    return res;
}

bool TRSCore::isRunAll()
{
    return runAll;
}

bool TRSCore::isSingleRun()
{
    return !runAll;
}
QString TRSCore::getMemoryStatus()
{
    QString res="{\"percent\": ";
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    res.append(QString::number(statex.dwMemoryLoad)+",\"ph_total\": ");
    res.append(QString::number(statex.ullTotalPhys)+",\"ph_usege\": ");
    res.append(QString::number(statex.ullTotalPhys-statex.ullAvailPhys)+",\"vr_total\": ");
    res.append(QString::number(statex.ullTotalVirtual)+",\"vr_usege\": ");
    res.append(QString::number(statex.ullTotalVirtual-statex.ullAvailVirtual)+",}");
    return res;
}
bool TRSCore::StartApp(QString appName, bool waitForStart) {
    process->start(appName);
    if(process->error()<5) {
        qDebug()<<process->errorString();
        emit fail("Application start failed.");
        return false;
    }
    else {
        if(waitForStart) {
            emit log("StartApp Waiting...");
            process->waitForStarted();
        }
        return true;
    }
}
void TRSCore::CloseApp(QString windowName, bool waitForClose) {
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    CloseWindow(windowName);
    if(waitForClose) {
        emit log("CloseApp Waiting...");
    if(!process->waitForFinished()) {
        emit fail("Application close failed.");
        return;
    }
    }
}

void TRSCore::SetOnTop(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }

    windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle == NULL){
        emit fail("Window isnt exist");
        return;
    }

    SetForegroundWindow(windowHandle);
}

bool TRSCore::waitForStart(QString windowName, ulong maxTime){
    emit log("waitForStart Waiting...");
    ulong waitTime = 0;
    windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    SetForegroundWindow(windowHandle);
    while (GetForegroundWindow() != windowHandle)
    {
        windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
        SetForegroundWindow(windowHandle);
        Sleep(200);
        if(maxTime != 0){
            waitTime+=200;
            if (maxTime<waitTime) {
                return false;
            }
        }
    }
    return true;
}

QString TRSCore::GetTopWnd()
{
    HWND wind = GetForegroundWindow();
    wchar_t buff[2048];
    GetWindowText(wind, buff, 2048);
    return QString::fromWCharArray(buff);

}
void TRSCore::Sleep(int msec) {
    if(msec<0) {
        emit fail("Invalid sleep time.");
        return;
    }
    if(msec == 0){
        return;
    }
    QTest::qSleep(msec);
}

int TRSCore::TimeElapsed(){
    return elapseTimer.elapsed();
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
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return -1;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("GetAppWidth Window:"+windowName+" not found.");
        return -1;
    }
    RECT win_rect;
    if(GetWindowRect(windowHandle, &win_rect)) {
        return win_rect.right-win_rect.left;
    }
    emit fail("Can not get window size.");
    return -1;
}

int TRSCore::GetAppHeight(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return -1;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("GetAppHeight:"+windowName+" not found.Window not found.");
        return -1;
    }
    RECT win_rect;
    if(GetWindowRect(windowHandle, &win_rect)) {
        return win_rect.bottom-win_rect.top;
    }
    emit fail("Can not get window size.");
    return -1;
}
QString TRSCore::GetAppRect(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return QString();
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("GetAppRect Window:"+windowName+" not found.");
        return QString();
    }
    RECT win_rect;
    QRect qwin_rect(QPoint(-1, -1),QPoint(-1,-1));
    if(GetWindowRect(windowHandle, &win_rect)) {
        qwin_rect.setTopLeft(QPoint(win_rect.top, win_rect.left));
        qwin_rect.setBottomRight(QPoint(win_rect.bottom,win_rect.right));
        QString rect("{\"x\": "+QString::number(win_rect.left)+",\"y\": "+QString::number(win_rect.top)+
                     ",\"width\": "+QString::number(win_rect.right-win_rect.left)+",\"height\": "+QString::number(win_rect.bottom-win_rect.top)+"}");
        return rect;
    }
    emit fail("Can not get window rect.");
    return QString();
}

QString TRSCore::GetChildRect(QString windowName, QString childName) {
    windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    HWND prev = NULL;
    HWND curr = NULL;
    RECT win_rect;
    curr=FindWindowEx(windowHandle, NULL, NULL ,NULL);
    while (curr) {
        wchar_t buff[2048];
        GetWindowText( curr, buff, 2048);
        if(QString::fromWCharArray(buff)==childName) {
            GetWindowRect(curr, &win_rect);
            return QString("{\"x\": "+QString::number(win_rect.left)+",\"y\": "+QString::number(win_rect.top)+
                         ",\"width\": "+QString::number(win_rect.right-win_rect.left)+",\"height\": "+QString::number(win_rect.bottom-win_rect.top)+"}");
        }
        prev=curr;
        curr=FindWindowEx(windowHandle,prev,NULL,NULL);
    }
    return "";
}
void TRSCore::SetAppPos(QString windowName, int x, int y) {
	if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("SetAppPos Window:"+windowName+" not found.");
        return;
    }
	if(!SetWindowPos(windowHandle, HWND_TOP, x, y, 0, 0, SWP_NOSIZE)) {
		emit fail("Can not set window position.");
        return;
	}
	return;
}
void TRSCore::SetAppSize(QString windowName, int w, int h) {
	if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("SetAppSize Window:"+windowName+" not found.");
        return;
    }
	if(!SetWindowPos(windowHandle, HWND_TOP, 0, 0, w, h, SWP_NOMOVE)) {
		emit fail("Can not set window size.");
        return;
	}
	return;
}
void TRSCore::SetAppRect(QString windowName, int x, int y, int w, int h) {
	if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("SetAppRect Window:"+windowName+" not found.");
        return;
    }
    if(!SetWindowPos(windowHandle, HWND_TOP, x, y, w, h, SWP_SHOWWINDOW)) {
		emit fail("Can not set window size.");
        return;
	}
	return;
}
void TRSCore::WindowMinimize(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("WindowMinimize Window:"+windowName+" not found.");
        return;
    }
    if (!ShowWindow(windowHandle, SW_MINIMIZE)) {
        emit fail("Can not minimaze window.");
        return;
    }
}

void TRSCore::WindowMaximize(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("WindowMaximize Window:"+windowName+" not found.");
        return;
    }
    if (!ShowWindow(windowHandle, SW_MAXIMIZE)) {
        emit fail("Can not maximize window.");
        return;
    }
}

void TRSCore::WindowRestore(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("WindowRestore Window:"+windowName+" not found.");
        return;
    }
    if (!ShowWindow(windowHandle, SW_RESTORE)) {
        emit fail("Can not restore window.");
        return;
    }
}
void TRSCore::CloseWindow(QString windowName)
{
    if(windowName.isEmpty()) {
        emit fail("Invalid window name.");
        return;
    }
    HWND windowHandle = FindWindow(NULL, (const wchar_t*) windowName.utf16());
    if(windowHandle==NULL) {
        emit fail("CloseWindow Window:"+windowName+" not found.");
        return;
    }
    PostMessageA(windowHandle, WM_SYSCOMMAND, SC_CLOSE, 0);
}
void TRSCore::KeyDown(int dkey){
    if(dkey<8) {
        emit fail("Invalid key.");
        return;
    }
    keybd_event(dkey, 0, 0, 0);
}
void TRSCore::KeyUp(int dkey){
    if(dkey<8) {
        emit fail("Invalid key.");
        return;
    }
    keybd_event(dkey, 0, KEYEVENTF_KEYUP, 0);
}
void TRSCore::KeyPress(int dkey){
    if(dkey<8) {
        emit fail("Invalid key.");
        return;
    }
    KeyDown(dkey);
    KeyUp(dkey);
}
void TRSCore::SetMousePos(int x, int y) {
    if(x<0 || y<0) {
        emit fail("Invalid coordinates.");
        return;
    }
    current_pos.x = x;
    current_pos.y = y;
    if(!SetCursorPos(x, y)) {
        emit fail("Can not set mouse at this position.");
    }
}
void TRSCore::MouseMove(int x, int y, int pause) {
    if(x<0 || y<0) {
        emit fail("Invalid coordinates.");
        return;
    }
    int w=current_pos.x-x;
    int h=current_pos.y-y;
    if(fabs(w)>fabs(h)) {
        if(current_pos.x>x) {
            auto fun = [&](int _x){ return (current_pos.x - _x)*(y - current_pos.y) / (current_pos.x - x) + current_pos.y; };
            for (int i = current_pos.x; i > x; i--) {
                Sleep(pause);
                if(!SetCursorPos(i, fun(i))) {
                    emit fail("Can not set mouse at this position.");
                    return;
                }
            }
        }
        else {
            auto fun = [&](int _x){ return (_x - current_pos.x)*(y - current_pos.y) / (x - current_pos.x) + current_pos.y; };
            for (int i = current_pos.x; i < x; i++) {
                Sleep(pause);
                if(!SetCursorPos(i, fun(i))) {
                    emit fail("Can not set mouse at this position.");
                    return;
                }
            }
        }
    }
    else {
        if(current_pos.y>y) {
            auto fun = [&](int _y){ return (current_pos.y - _y)*(x - current_pos.x) / (current_pos.y - y) + current_pos.x; };
            for (int i = current_pos.y; i > y; i--) {
                Sleep(pause);
                if(!SetCursorPos(fun(i), i)) {
                    emit fail("Can not set mouse at this position.");
                    return;
                }
            }
        }
        else {
            auto fun = [&](int _y){ return (_y - current_pos.y)*(x - current_pos.x) / (y - current_pos.y) + current_pos.x; };
            for (int i = current_pos.y; i < y; i++) {
                Sleep(pause);
                if(!SetCursorPos(fun(i), i)) {
                    emit fail("Can not set mouse at this position.");
                    return;
                }
            }
        }
    }
    if(!GetCursorPos(&current_pos)) {
        emit fail("Can not take cursor position.");
        return;
    }
}
void TRSCore::MouseDown(int button) {
    if(button!=0 && button!=1) {
        emit fail("Invalid button.");
        return;
    }
    if (button) {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
    }
}
void TRSCore::MouseUp(int button) {
    if(button!=0 && button!=1) {
        emit fail("Invalid button.");
        return;
    }
    if (button) {
        mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
    }
}
void TRSCore::MouseClick(int button) {
    if(button!=0 && button!=1) {
        emit fail("Invalid button.");
        return;
    }
    if (button) {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, current_pos.x, current_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, current_pos.x, current_pos.y, 0, 0);
    }
    else {
        mouse_event(MOUSEEVENTF_LEFTDOWN, current_pos.x, current_pos.y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, current_pos.x, current_pos.y, 0, 0);
    }
}

void TRSCore::MouseClickA(int x, int y,int button){
    SetMousePos(x,y);
    MouseClick(button);
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
    if(!originalPixmap.save(file)) {
        emit fail("Can not save image to file.");
        return;
    }
}
void TRSCore::PrintScreenA(int x, int y, int w, int h, QString file){
    QPixmap originalPixmap;
    QScreen *screen = QGuiApplication::primaryScreen();
    originalPixmap = screen->grabWindow(0);
    QRect rect(x, y, w, h);
    QPixmap cropped = originalPixmap.copy(rect);
    if(!cropped.save(file)) {
        emit fail("Can not save image to file.");
        return;
    }
}
int TRSCore::exec(QString command) {
    return system(command.toStdString().c_str());
}
QStringList TRSCore::getList(QString path) {
    QStringList files;
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        it.next();
        if (it.fileName()=="." || it.fileName()=="..") {
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
        if (it.fileName()=="." || it.fileName()=="..") {
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
    if(!file.exists()) {
        emit fail("Invalid path.");
        return false;
    }
    return file.isFile();
}
bool TRSCore::isDir(QString path) {
    QFileInfo file(path);
    if(!file.exists()) {
        emit fail("Invalid path.");
        return false;
    }
    return file.isDir();
}
bool TRSCore::isExist(QString path) {
    QFileInfo file(path);
    if(!file.exists()) {
        emit fail("Invalid path.");
        return false;
    }
    return file.exists();
}
bool TRSCore::isReadOnly(QString path) {
    QFileInfo file(path);
    if(!file.exists()) {
        emit fail("Invalid path.");
        return false;
    }
    return !file.isWritable();
}
qint64 TRSCore::getSize(QString path) {
    if(isFile(path)) {
        QFileInfo file(path);
        if(!file.exists()) {
            emit fail("Invalid path.");
            return -1;
        }
        return file.size();
    }
    else {
        qint64 size=0;
        QDirIterator it(path, QDirIterator::Subdirectories);
        QFileInfo file;
        if(!file.exists()) {
            emit fail("Invalid path.");
            return -1;
        }
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
        emit fail("Invalid path.");
        return false;
    }
    QDir qd(path);
    qd.removeRecursively();
    return true;
}
bool TRSCore::delFile(QString path) {
    if(!QFile(path).exists()) {
        emit fail("Invalid path.");
        return false;
    }
    QFile file(path);
    file.remove();
    return true;
}

bool TRSCore::isKeyExist(QString key)
{
    try {
        key.replace("/","\\");
        QSettings regSetting(key.left(key.lastIndexOf("\\")), QSettings::NativeFormat);
        return regSetting.contains(key.right(key.length()-key.lastIndexOf("\\")-1));
    }
    catch (...) {
        emit fail("Key is not accessible.");
        return false;
    }
}

QVariant TRSCore::getKeyValue(QString key)
{
    try {
        key.replace("/","\\");
        QSettings regSetting(key.left(key.lastIndexOf("\\")), QSettings::NativeFormat);
        return regSetting.value(key.right(key.length()-key.lastIndexOf("\\")-1));
    }
    catch (...) {
        emit fail("Key is not accessible.");
        return QVariant();
    }
}

void TRSCore::setKeyValue(QString key, QVariant value)
{
    try {
        key.replace("/","\\");
        QSettings regSetting(key.left(key.lastIndexOf("\\")), QSettings::NativeFormat);
        regSetting.setValue(key.right(key.length()-key.lastIndexOf("\\")-1), value);
    }
    catch (...) {
        emit fail("Key is not accessible.");
    }
}
QString TRSCore::List(QString path)
{
    try {
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
    catch (...) {
        emit fail("Key is not accessible.");
        return QString();
    }

}

