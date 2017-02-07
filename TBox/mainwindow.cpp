#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <databasemanager.h>
#include <QObject>
#include <QTime>
QWebView * view;
QObject * contextObject;
class MainTree : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit MainTree(QObject *parent = 0) :
        QStandardItemModel(parent){
        m_roleNameMapping[MainTree_Role_Name] = "name_role";
        QObject::connect(this,SIGNAL(sendTestName(QString)),&data_base_man,SLOT(getTestName(QString)));
        QObject::connect(this,SIGNAL(sendSuiteName(QString)),&data_base_man,SLOT(getSuiteName(QString)));
        QObject::connect(this,SIGNAL(sessionN()),&data_base_man,SLOT(sessionNum()));
    }
    virtual ~MainTree() = default;
    enum MainTree_Roles{
        MainTree_Role_Name = Qt::DisplayRole
    };
    QHash<int, QByteArray> roleNames() const override{
        return m_roleNameMapping;
    }
    DataBaseManager data_base_man;
    public slots:
    void testFinished(QString);
    void acceptMessage(QString);
    Q_INVOKABLE QString Load(QString path);
    Q_INVOKABLE QString getFile(QModelIndex);
    Q_INVOKABLE QString FindTest(QModelIndex);
    Q_INVOKABLE void setCurrentItem(QModelIndex);
    Q_INVOKABLE void FindJSFile(QString);
    Q_INVOKABLE static QStringList getTestsName(QString);
    Q_INVOKABLE static QString getSuiteName(QString);
    Q_INVOKABLE static QString getJS(QString, QString);
    Q_INVOKABLE static void setJS(QString, QString, QString);
    Q_INVOKABLE bool Run();
    Q_INVOKABLE void RunOne();
    Q_INVOKABLE QStringList GetTags();
    Q_INVOKABLE void Stop();
    Q_INVOKABLE void setRootDir(QString);
    Q_INVOKABLE QString AddNewTest(QString, QString, QString, QString, QString, QString);
    Q_INVOKABLE QString AddNewSuite(QString, QString, QString, QString);
    Q_INVOKABLE QString AddRootSuite(QString, QString, QString, QString);
    Q_INVOKABLE void setCurrentTag(QString);
    Q_INVOKABLE void Set(QString, QString);
    Q_INVOKABLE QString Get(QString);
    Q_INVOKABLE QString GetType();
    Q_INVOKABLE QString Remove();
    Q_INVOKABLE QModelIndex getCurrentIndex();
    Q_INVOKABLE QStringList List(QString);
    Q_INVOKABLE bool IsFolderEmpty(QString);
    Q_INVOKABLE void setViewStatus(bool);
    Q_INVOKABLE void showInspector();
    Q_INVOKABLE void openFolder();
    Q_INVOKABLE QStringList GetSuiteList();
    Q_INVOKABLE QStringList getHeaders(QString, QString);
    Q_INVOKABLE void WriteLog(QString);
private:
    void CreateHtml(TreeInfo&);
    void Parse(QString, QStandardItem *);
    QStandardItem * AddItemToTree(QString);
    QString ParseFolder(QString);
    bool CheckTest(TreeInfo);
    QHash<int, QByteArray> m_roleNameMapping;
    QVector<TreeInfo> treeData;
    QString rootDir;
    QModelIndex currentIndex;
    bool run=false;
    QStringList tags;
    QString currentTag="All";
    DataManager dm;
    QVector<TreeInfo> testForRun;
    Report *report=nullptr;
    TestInfo *testinfo=nullptr;
    TRSCore* trscore=nullptr;
signals:
    void sendTestName(QString);
    void sendSuiteName(QString);
    void sessionN();
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    view = new QWebView();
    qmlRegisterType<MainTree>("cMainTree", 1, 0, "MainTree" );
    qmlRegisterType<MainSetting>("MainSetting", 1, 0, "Setting" );
    qmlRegisterType<FileSaveDialog>("FileSave", 1, 0, "FileSaveDialog");
    qmlView = new QQuickView();
    O.setEngi(qmlView);
    qmlView->rootContext()->setContextProperty("DD",&O);
    QObject::connect(&O,SIGNAL(PassHTMLdata(QVector<QStringList*>,QStringList,int,QString)),&H,SLOT(ReceiveHTMLdata(QVector<QStringList*>,QStringList,int,QString)));
    QObject::connect(&O,SIGNAL(sendExportPath(QString)),&H,SLOT(ReceiveHTMLpath(QString)));
    qmlView->setGeometry(QRect(200,200,800,600));
    qmlView->setResizeMode(QQuickView::SizeRootObjectToView);
    qmlView->setIcon(QIcon(QPixmap(":/icons/icons/tbox.png")));
    qmlRegisterType<Highlighter>("Highlighter", 1, 0, "HighL" );
    qmlView->setSource(QUrl("qrc:/MainForm.ui.qml"));
    object = qmlView->rootObject();
    contextObject=object;
    selectFolder=new SelectFolderDialog();
    selectFolder->setObject(object);
    qmlView->rootContext()->setContextProperty("selectFolderDialog", selectFolder);
    QWebSettings* settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    settings->setAttribute(QWebSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);
    qmlView->show();
    view->page()->setProperty("_q_webInspectorServerPort",9876);
    QMetaObject::invokeMethod(object, "checkRootDir");
}
MainWindow::~MainWindow(){
    delete ui;
    view->deleteLater();
    qmlView->deleteLater();
    selectFolder->deleteLater();
}
void MainWindow::writeLog(QString msg){
    QTime time=QTime::currentTime();
    QMetaObject::invokeMethod(object, "writeLog", Q_ARG(QVariant, time.toString()+":"+QString::number(time.msec())+" "+msg));
}
void MainTree::testFinished(QString msg) {
    WriteLog(msg);
    run=false;
    if(testForRun.isEmpty()) {
        return;
    }
    if(testForRun.first().repeat>0) {
        testForRun.first().repeat--;
        CreateHtml(testForRun.first());
    }
    else {
        testForRun.removeFirst();
        if(!testForRun.isEmpty()) {
            CreateHtml(testForRun.first());
        }
        else {
            WriteLog("All tests finished.");
        }
    }
}
void MainTree::acceptMessage(QString msg) {
    WriteLog(msg);
}
QString MainTree::Load(QString path) {
    if(path=="") {
        path=rootDir;
    }
    if(path!=rootDir) {
        rootDir=path;
    }
    this->clear();
    treeData.clear();
    QString res;
    if(rootDir!="") {
        res=ParseFolder(path);
        if(res!="") {
            this->clear();
            treeData.clear();
            return res;
        }
    }
    return res;
}
void MainTree::setRootDir(QString path) {
    rootDir=path;
}
QString MainTree::AddNewTest(QString name, QString dis, QString exe, QString tag, QString rep, QString disable) {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            rep=rep==""?"1":rep;
            QString res= dm.AddTest(it.file, name, dis, tag, exe, rep, disable);
            if(res=="") {
                TreeInfo info;
                info.file = it.file;
                info.item = this->indexFromItem(AddItemToTree(name));
                info.name = name;
                info.type = "test";
                info.repeat = rep.toInt();
                treeData.push_back(info);
                QStringList t=tag.split(",");
                for(auto&i:t) {
                    if(!tags.contains(i)) {
                        tags.push_back(i);
                    }
                }
            }
            return res;
        }
    }
    return "does not exist";
}
QString MainTree::AddNewSuite(QString name, QString dis, QString rep, QString disable) {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            rep=rep==""?"1":rep;
            QString res=dm.AddSuite(it.file, name, dis, rep, disable);
            if(res=="") {
                TreeInfo info;
                info.file = it.file;
                info.file.data()[info.file.lastIndexOf("/")+1]='\0';
                info.file = QString(info.file.data())+name+"/suite.xml";
                QStandardItem * item = new QStandardItem(name);
                this->itemFromIndex(currentIndex)->appendRow(item);
                info.item = this->indexFromItem(item);
                info.name = name;
                info.type = "suite";
                info.repeat = rep.toInt();
                treeData.push_back(info);
            }
            return res;
        }
    }
    return "exist";
}
QString MainTree::AddRootSuite(QString name, QString dis, QString rep, QString disable) {
    return dm.AddRoot(rootDir+"/suite.xml", name, dis, rep, disable);

}
void MainTree::setCurrentTag(QString tag) {
    currentTag=tag;
}
void MainTree::Set(QString path, QString data) {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            if (it.type == "test") {
                dm.Set(it.file+"/suite/test/"+it.name+"/"+path, data);
                if(path==tags_name::kName) {
                    it.name=data;
                    this->itemFromIndex(currentIndex)->setText(data);
                }
                if(path==tags_name::kRepeat) {
                    it.repeat=data.toInt();
                }
            }
            else if(it.type == "suite") {
                dm.Set(it.file+"/suite/"+path, data);
                if(path==tags_name::kName) {
                    it.name=data;
                    this->itemFromIndex(currentIndex)->setText(data);
                }
            }
        }
    }
}
QString MainTree::Get(QString path) {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            if (it.type == "test") {
                return dm.Get(it.file+"/suite/test/"+it.name+"/"+path);
            }
            else if(it.type == "suite") {
                return dm.Get(it.file+"/suite/"+path);
            }
        }
    }
    return "";
}
QString MainTree::GetType() {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            return it.type;
        }
    }
    return "";
}
QString MainTree::Remove() {
    QString res="Does not exist";
    for (auto it =treeData.begin(); it!=treeData.end(); it++) {
        if (it->item == currentIndex) {
            if(it->type=="suite") {
                return dm.RemoveSuite(it->file);

            }
            else {
                return dm.RemoveTest(it->file, it->name);
            }
        }
    }
    memset((void*)&currentIndex, 0, sizeof(currentIndex));
    return res;
}
QModelIndex MainTree::getCurrentIndex() {
    return currentIndex;
}
QStringList MainTree::List(QString path) {
    QDirIterator it(path, QDirIterator::Subdirectories);
    QStringList files;
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
bool MainTree::IsFolderEmpty(QString path) {
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        it.next();
        if (it.filePath().contains(".xml")) {
            return false;
        }
    }
    return true;
}
void MainTree::setViewStatus(bool status) {
    if(status) {
        view->show();
    }
    else {
        view->close();
    }
}
void MainTree::showInspector() {
    QString link = "http://127.0.0.1:9876/webkit/inspector/inspector.html?page=1";
    QDesktopServices::openUrl(QUrl(link));
}
void MainTree::openFolder() {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            QDesktopServices::openUrl(QUrl::fromLocalFile(QString(it.file).split("/suite.xml")[0]));
        }
    }
}
QStringList MainTree::GetSuiteList() {
    QStringList suites;
    for (auto&it : treeData) {
        if (it.type == "suite") {
            suites.push_back(it.name);
        }
    }
    return suites;
}
QStringList MainTree::getHeaders(QString file, QString test) {
    return dm.getHeaders(file, test);
}
QString MainTree::getFile(QModelIndex item) {
    for (auto&it : treeData) {
        if (it.item == item) {
            return it.file;
        }
    }
    return NULL;
}
QString MainTree::FindTest(QModelIndex item) {
    currentIndex=item;
    for (auto&it : treeData) {
        if (it.item == item && it.type == "test") {
            return getJS(it.file, it.name);
        }
    }
    return "";
}
void MainTree::setCurrentItem(QModelIndex idx) {
    currentIndex=idx;
}
void MainTree::FindJSFile(QString data) {
    for (auto&it : treeData) {
        if (it.item == currentIndex && it.type == "test") {
            setJS(it.file, it.name, data);
        }
    }
}
void MainTree::RunOne(){
    if(run) {
        return;
    }
    emit sessionN();
    for (auto& it:treeData) {
        if (it.item == currentIndex && it.type == "test") {
           testForRun.push_back(it);
           testForRun.first().repeat=0;
           CreateHtml(testForRun.first());
           break;
        }
        else if (it.item == currentIndex && it.type == "suite"){
            emit sendSuiteName(it.name);
            testForRun.clear();
            for(int i=0; i<this->itemFromIndex(currentIndex)->rowCount(); i++) {
                for (auto&it2 : treeData) {
                    if (it2.item == currentIndex.child(i,0) && it2.type == "test" && CheckTest(it2) && it2.repeat>0) {
                        testForRun.push_back(it2);
                        break;
                    }
                }
            }
            if(!testForRun.isEmpty()) {
                testForRun.first().repeat--;
                CreateHtml(testForRun.first());
            }
        }
    }
}
bool MainTree::Run() {
    if(run) {
        return false;
    }
    emit sessionN();
    testForRun.clear();
    for(auto&it:treeData) {
        if (it.type == "test" && CheckTest(it) && it.repeat>0) {
            testForRun.push_back(it);
        }else{
            emit sendSuiteName(it.name);
        }
    }
    if(!testForRun.isEmpty()) {
        testForRun.first().repeat--;
        CreateHtml(testForRun.first());
    }
    return true;
}
QStringList MainTree::GetTags() {
    return tags;
}
void MainTree::Stop() {
    run=false;
}
void MainTree::Parse(QString path, QStandardItem * suite) {
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    QStringList chilSuite;
    bool isValid=false;
    while (it.hasNext()) {
        it.next();
        if (it.filePath().contains("/.") || it.filePath().contains("/.")) {
            continue;
        }
        else {
            if (it.filePath().contains(".xml")) {
                isValid=true;
                QString name = getSuiteName(it.filePath());
                suite->setText(name);
                TreeInfo info;
                info.file = it.filePath();
                info.item = this->indexFromItem(suite);
                info.name = name;
                info.type = "suite";
                info.repeat = dm.Get(info.file+"/suite/repeat").toInt();
                treeData.push_back(info);
                QStringList list = getTestsName(it.filePath());
                for (auto& iter : list) {
                    QStandardItem * test = new QStandardItem(iter);
                    suite->appendRow(test);
                    TreeInfo info;
                    info.item = this->indexFromItem(test);
                    info.name = iter;
                    info.file = it.filePath();
                    info.type = "test";
                    info.repeat = dm.Get(info.file+"/suite/test/"+iter+"/repeat").toInt();
                    QStringList t=dm.Get(info.file+"/suite/test/"+iter+"/tag").split(",");
                    for(auto&i:t) {
                        if(!tags.contains(i) && !i.isEmpty()) {
                            tags.push_back(i);
                        }
                    }
                    treeData.push_back(info);
                }
            }
            if (it.fileInfo().isDir() && !IsFolderEmpty(it.filePath())) {
                chilSuite.push_back(it.filePath());
            }
        }
    }
    if(isValid) {
        for(auto&ind:chilSuite) {
           QStandardItem * child = new QStandardItem("");
           suite->appendRow(child);
           Parse(ind, child);
        }
    }
}
QStandardItem * MainTree::AddItemToTree(QString name) {
    QStandardItem * item = new QStandardItem(name);
    int i=0;
    while(this->itemFromIndex(currentIndex)->child(i)!=0) {
        if(this->itemFromIndex(currentIndex)->child(i)->hasChildren()){
            break;
        }
        i++;
    }
    this->itemFromIndex(currentIndex)->insertRow(i,item);
    int k=this->itemFromIndex(currentIndex)->rowCount()-1;
    while (k!=i) {
            auto it =treeData.begin();
            QStandardItem * itt=this->itemFromIndex(currentIndex)->child(k-1);
            while (it!=treeData.end()) {
                if(it->item==itt->index()) {
                    it->item=this->itemFromIndex(currentIndex)->child(k)->index();
                    break;
                }
               it++;
            }
            k--;
        }
    return item;
}
QString MainTree::ParseFolder(QString path) {
    QStandardItem * suite = new QStandardItem("");
    this->appendRow(suite);
    tags.clear();
    tags.push_back("All");
    Parse(path, suite);
    if(treeData.isEmpty()) {
        tags.clear();
        this->clear();
        tags.push_back("All");
        return "Invalid folder";
    }
    return "";
}
bool MainTree::CheckTest(TreeInfo info) {
    if(dm.Get(info.file+"/suite/disable")=="false") {
        if(dm.Get(info.file+"/suite/test/"+info.name+"/disable")=="false") {
            if(currentTag=="All") {
                return true;
            }
            else {
                if(dm.Get(info.file+"/suite/test/"+info.name+"/tag").contains(currentTag)) {
                    return true;
                }
            }
        }
        WriteLog("\""+info.name+"\" is disabled.");
        return false;
    }
    WriteLog("\""+info.name+"\" :Parent suite is disabled.");
    return false;
}
QStringList MainTree::getTestsName(QString file_name) {
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    QStringList testList;
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kTest) {
                testList.push_back(Rxml.attributes().value(tags::kName).toString());
            }
        }
        Rxml.readNext();
    }
    file.close();
    return testList;
}
QString MainTree::getSuiteName(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kSuite) {
                return Rxml.attributes().value(tags::kName).toString();
            }
        }
        Rxml.readNext();
    }
    file.close();
    return "";
}
QString MainTree::getJS(QString file_name, QString test_name) {
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    file_name.data()[file_name.lastIndexOf('/')+1]='\0';
    QString exe=QString(file_name.data());
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kTest) {
                if(Rxml.attributes().value(tags::kName).toString()==test_name) {
                    while(Rxml.name()!=tags::kExecution) {
                        Rxml.readNext();
                    }
                    exe+= Rxml.readElementText();
                    break;
                }
            }
        }
        Rxml.readNext();
    }
    file.close();
    file.setFileName(exe);
    file.open(QIODevice::ReadOnly);
    QString data(file.readAll());
    return data;
}
void MainTree::setJS(QString file_name, QString test_name, QString data) {
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader Rxml;
    file_name.data()[file_name.lastIndexOf('/')+1]='\0';
    QString exe=QString(file_name.data());
    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {
            if(Rxml.name() == tags::kTest) {
                if(Rxml.attributes().value(tags::kName).toString()==test_name) {
                    while(Rxml.name()!=tags::kExecution) {
                        Rxml.readNext();
                    }
                    exe+= Rxml.readElementText();
                    break;
                }
            }
        }
        Rxml.readNext();
    }
    file.close();
    file.setFileName(exe);
    file.open(QIODevice::WriteOnly);
    file.write(data.toLatin1());
    file.close();
}
void MainTree::CreateHtml(TreeInfo &it) {
    run=true;
    emit sendTestName(it.name);
    emit sendSuiteName(it.file);
    data_base_man.sessionStart();
    QStringList headers = getHeaders(it.file, it.name);
    QFile file(it.getPath()+"/"+"test.html");
    if(report!=nullptr) {
        delete report;
        delete testinfo;
        delete trscore;
    }
    delete view->page();
    view->setPage(new QWebPage());
    view->page()->setProperty("_q_webInspectorServerPort",9876);
    /*QFile file(testForRun.first().getPath()+"/"+"test.html");
    file.remove();*/
    report=new Report();
    view->page()->mainFrame()->addToJavaScriptWindowObject("Report", report);
    trscore=new TRSCore();
    view->page()->mainFrame()->addToJavaScriptWindowObject("Box", trscore);
    QObject::connect(trscore, SIGNAL(log(QString)), this, SLOT(WriteLog(QString)));
    testinfo=new TestInfo();
    testinfo->setName(it.name);
    testinfo->setPath(it.file);
    QObject::connect(testinfo, SIGNAL(testBegin(QString)), this, SLOT(WriteLog(QString)));
    QObject::connect(testinfo, SIGNAL(testFinish(QString)), this, SLOT(testFinished(QString)));
    QObject::connect(testinfo, SIGNAL(sendMessage(QString)), this, SLOT(acceptMessage(QString)));
    QObject::connect(report, SIGNAL(sendMessage(QString)), this, SLOT(acceptMessage(QString)));
    view->page()->mainFrame()->addToJavaScriptWindowObject("Test", testinfo);
    file.open(QIODevice::WriteOnly);
    QString page="<html>\n\t<head>";
    for(auto& h:headers) {
        page+="\n\t\t<script src=\""+h+"\" type=\"text/javascript\" charset=\"utf-8\"></script>";
    }
    page+="\n\t\t<script type=\"text/javascript\">\n\t\tTest.BEGIN();"+getJS(it.file, it.name)+"\n\t\tTest.FINISH()</script>";
    page+="\n\t</head>\n\t<body>\n\t</body>\n</html>";
    file.write(page.toLatin1());
    file.close();
    view->load(QUrl("file:///"+it.getPath()+"/"+"test.html"));
}
void MainTree::WriteLog(QString msg) {
    QTime time=QTime::currentTime();
    QMetaObject::invokeMethod(contextObject, "writeLog", Q_ARG(QVariant, time.toString()+":"+QString::number(time.msec())+" "+msg));
}
#include "mainwindow.moc"
