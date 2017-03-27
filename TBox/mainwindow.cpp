#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <databasemanager.h>
#include <QObject>
#include <QTime>
QWebView * view;
QObject * contextObject;
const int kDefaultPort=9876;
class MainTree : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit MainTree(QObject *parent = 0) :
        QStandardItemModel(parent){
        rootSuite = new TreeInfo();
        m_roleNameMapping[MainTree_Role_Name] = "name_role";
        QObject::connect(this,SIGNAL(sendTestName(QString)),&data_base_man,SLOT(getTestName(QString)));
        QObject::connect(this,SIGNAL(sendSuiteName(QString)),&data_base_man,SLOT(getSuiteName(QString)));
        QObject::connect(this,SIGNAL(sendRepeatTest(QString)),&data_base_man,SLOT(getRepeatNum(QString)));
        QObject::connect(this,SIGNAL(sendDescTest(QString)),&data_base_man,SLOT(getDescTest(QString)));
        QObject::connect(this,SIGNAL(sendSuiteInfo(QString,QString)),&data_base_man,SLOT(getSuiteInfo(QString,QString)));
        QObject::connect(this,SIGNAL(sessionN()),&data_base_man,SLOT(sessionNum()));
        QObject::connect(this,SIGNAL(sendTestMessage(QString)),&data_base_man,SLOT(getTestMsg(QString)));
        QObject::connect(this,SIGNAL(sendSMTPMail()),this,SLOT(sendMail()));
    }
    virtual ~MainTree() {
        delete rootSuite;
        delete testinfo;
        delete suiteinfo;
        delete trscore;
    }
    enum MainTree_Roles{
        MainTree_Role_Name = Qt::DisplayRole
    };
    QHash<int, QByteArray> roleNames() const override{
        return m_roleNameMapping;
    }
    QStringList SuiteData;
    DataBaseManager data_base_man;
    public slots:
    void testFinished(QString);
    void testFail(QString);
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
    Q_INVOKABLE void setRootDir(QString);
    Q_INVOKABLE void setMailCredentials(QString username,QString password,QString MailTo);
    Q_INVOKABLE QString AddNewTest(QString, QString, QString, QString, QString, QString, QString);
    Q_INVOKABLE QString AddNewSuite(QString, QString, QString, QString);
    Q_INVOKABLE QString AddRootSuite(QString, QString, QString, QString);
    Q_INVOKABLE void setCurrentTag(QString);
    Q_INVOKABLE void Set(QString, QString);
    Q_INVOKABLE QString Get(QString);
    Q_INVOKABLE QString GetType(QModelIndex);
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
    Q_INVOKABLE void OpenInEditor(QString);
    Q_INVOKABLE void Terminate();
private:
    void CreateHtml(TreeInfo *);
    void Parse(QString, QStandardItem *, TreeInfo *);
    QStandardItem * AddItemToTree(QString);
    QString ParseFolder(QString);
    QHash<int, QByteArray> m_roleNameMapping;
    TreeInfo *rootSuite;
    TreeInfo *itemForRun=nullptr;
    TreeInfo *currentTest=nullptr;
    QString rootDir;
    QModelIndex currentIndex;
    bool run=false;
    QStringList tags;
    QString currentTag="All";
    DataManager dm;
    TestInfo *testinfo=nullptr;
    SuiteInfo *suiteinfo=nullptr;
    TRSCore* trscore=nullptr;
    QString username = "default";
    QString password="default";
    QString MailTo="default";
    QString testFile;
    bool runOne = false;
    bool importantTestFail = false;
signals:
    void sendTestName(QString);
    void sendSuiteName(QString);
    void sendRepeatTest(QString);
    void sendDescTest(QString);
    void sendSuiteInfo(QString,QString);
    void sessionN();
    void sendTestMessage(QString msg);
    void sendSMTPMail();
private slots:
    void sendMail();
    void mailSent(QString);
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
    QObject::connect(&O,SIGNAL(PassHTMLdata(QVector<QStringList*>,int,QStringList,QStringList,QVector<QStringList*>,QString)),
                     &H,SLOT(ReceiveHTMLdata(QVector<QStringList*>,int,QStringList,QStringList,QVector<QStringList*>,QString)));
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
    view->page()->setProperty("_q_webInspectorServerPort",kDefaultPort);
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
void MainTree::setMailCredentials(QString Username, QString Password, QString mailTo){
    username = Username;
    password = Password;
    MailTo = mailTo;
}
void MainTree::sendMail()
{
    if(!(username == "default" || password == "default" || MailTo == "default")){
     QString T;
     T.append(QDate::currentDate().toString("dd/MM/yyyy"));
     QString T1;
     T1.append(QDate::currentDate().toString("yyyy/MM/dd"));
     DataBase O;
    QQuickView *t = new QQuickView;
    O.setEngi(t);
    O.defaultTableValue(T1,T1);
    QList <QObject*> obj = O.getReportList();
    QString q = QString::number(O.getReportList().size());
    O.row_selected("0");
    QDir path_;
    QString Path = path_.absolutePath();
    QString tempPath;
    QRegExp exp("/");
    QStringList p;
    p = Path.split(exp);
    Path.clear();
    for(int i=0;i<p.size();i++){
        tempPath.append(p.at(i)+"//");
    }
    Path.append(tempPath+"WebViewSessionTable.html");
    QString folderPath = tempPath+"SMTPSend//";
    if(QDir("SMTPSend").exists()){
        QFile::copy(Path,folderPath+"ReportFile.html");
    }else{
        QDir().mkdir("SMTPSend");
        QFile::copy(Path,folderPath+"ReportFile.html");
    }

    Smtp* smtp = new Smtp(username,password,"smtp-ua.globallogic.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QStringList PP; PP.append(folderPath+"ReportFile.html");
    smtp->sendMail(username,MailTo,"Report file","Report file",PP);

    QString folderRemove = folderPath;
    QDir direc;direc.remove(folderRemove+"ReportFile.html");
    }

}
void MainTree::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
void MainWindow::AddStartCommand(QString command)
{
    if(command == "run") {
        QMetaObject::invokeMethod(object, "startRun");
    }
}
void MainTree::testFinished(QString msg) {
    if(!run) {
        return;
    }
    emit sendTestMessage(msg);
    WriteLog(msg);
    data_base_man.sessionEnd();
    run=false;
    QFile file(currentTest->getPath()+"/"+"test.html");
    qDebug() << file.fileName();
    file.remove();
    if(msg.contains("fail")) {
        if(dm.Get(currentTest->getFile()+"/suite/test/"+currentTest->getName()+"/important")=="true") {
            importantTestFail=true;
            currentTest->setAsFail();
            WriteLog("All tests from this suite stoped.");
        }
    }
    currentTest=itemForRun->getNextTest();
    if(currentTest) {
        CreateHtml(currentTest);
            }
    else {
            QMetaObject::invokeMethod(contextObject, "setStopDisable");
             emit sendSMTPMail();
            WriteLog("All tests finished.");
            rootSuite->ResetAllRepeat();
            delete view->page();
        }
}
void MainTree::testFail(QString msg)
{
    delete view->page();
    if(dm.Get(currentTest->getFile()+"/suite/test/"+currentTest->getName()+"/important")=="true") {
        importantTestFail=true;
        currentTest->setAsFail();
    }
    testFinished("fail_"+msg);
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
    delete rootSuite;
    this->clear();
    rootSuite = new TreeInfo();
    QString res;
    if(rootDir!="") {
        res=ParseFolder(path);
        if(res!="") {
            delete rootSuite;
            return res;
        }
    }
    return res;
}
void MainTree::setRootDir(QString path) {
    rootDir=path;
}
QString MainTree::AddNewTest(QString name, QString dis, QString exe, QString tag, QString rep, QString disable, QString important) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return "Suite does not exist";
    }
            rep=rep==""?"1":rep;
    QString res= dm.AddTest(it->getFile(), name, dis, tag, exe, rep, disable,important);
            if(res=="") {
        TreeInfo * test = new TreeInfo();
        test->setParent(it);
        test->setFile(it->getFile());
        test->setItem(this->indexFromItem(AddItemToTree(name)));
        test->setName(name);
        test->setType("test");
        test->setBaseRepeat(rep.toInt());
        it->addChildTests(test);
                QStringList t=tag.split(",");
                for(auto&i:t) {
                    if(!tags.contains(i)) {
                        tags.push_back(i);
                    }
                }
        currentIndex=test->getItem();
        QMetaObject::invokeMethod(contextObject, "selectItem", Q_ARG(QVariant, currentIndex));
            }
            return res;
}
QString MainTree::AddNewSuite(QString name, QString dis, QString rep, QString disable) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return "Suite does not exist";
    }
            rep=rep==""?"1":rep;
    QString res=dm.AddSuite(it->getFile(), name, dis, rep, disable);
            if(res=="") {
        TreeInfo *suite = new TreeInfo();
        QString parentFile=it->getFile();
        parentFile.data()[parentFile.lastIndexOf("/")+1]='\0';
        parentFile = QString(parentFile.data())+name+"/suite.xml";
        suite->setFile(parentFile);
                QStandardItem * item = new QStandardItem(name);
                this->itemFromIndex(currentIndex)->appendRow(item);
        suite->setItem(this->indexFromItem(item));
        suite->setName(name);
        suite->setType("suite");
        suite->setBaseRepeat(rep.toInt());
        suite->setParent(it);
        it->addChildSuites(suite);
        currentIndex=suite->getItem();
        qDebug() << "AddNewSuite";
        QMetaObject::invokeMethod(contextObject, "selectItem", Q_ARG(QVariant, currentIndex));
            }
            return res;
}
QString MainTree::AddRootSuite(QString name, QString dis, QString rep, QString disable) {
    return dm.AddRoot(rootDir+"/suite.xml", name, dis, rep, disable);
}
void MainTree::setCurrentTag(QString tag) {
    currentTag=tag;
}
void MainTree::Set(QString path, QString data) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return;
                }
    if (it->getType() == "test") {
        dm.Set(it->getFile()+"/suite/test/"+it->getName()+"/"+path, data);
                }
    else if(it->getType() == "suite") {
        dm.Set(it->getFile()+"/suite/"+path, data);
            }
                if(path==tags_name::kName) {
        it->setName(data);
                    this->itemFromIndex(currentIndex)->setText(data);
                }
    if(path==tags_name::kRepeat) {
        it->setBaseRepeat(data.toInt());
            }
    if(path==tags_name::kDisable) {
        it->setDisable(data=="true"?true:false);
    }
}
QString MainTree::Get(QString path) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return "";
            }
    if (it->getType() == "test") {
        return dm.Get(it->getFile()+"/suite/test/"+it->getName()+"/"+path);
        }
    else if(it->getType() == "suite") {
        return dm.Get(it->getFile()+"/suite/"+path);
    }
    return "";
}
QString MainTree::GetType(QModelIndex index) {
    auto it = rootSuite->FindByItem(index);
    if(!it) {
        return "";
    }
    return it->getType();
}
QString MainTree::Remove() {
    QString res="Does not exist";
    auto it = rootSuite->FindByItem(currentIndex);
    TreeInfo * prev=nullptr;
    if(!it) {
        return res;
    }
    if(it->getType()=="suite") {
        res = dm.RemoveSuite(it->getFile());
            }
            else {
        res = dm.RemoveTest(it->getFile(), it->getName());
            }
    auto root=this->itemFromIndex(currentIndex)->parent();
    auto parent = it->getParent();
    int row=currentIndex.row();
    root->removeRow(row);
    if(parent->getChildTests().contains(it)) {
        bool found=false;
        for(auto&i:parent->getChildTests()) {
            if(i==it) {
                found=true;
                continue;
            }
            if(found) {
                i->setItem(root->child(row++)->index());
            }
        }
        for(auto&i:parent->getChildSuites()) {
            i->setItem(root->child(row++)->index());
        }
        prev=parent->getChildTests().indexOf(it)==0?parent:parent->getChildTests().at(parent->getChildTests().indexOf(it)-1);
        parent->getChildTests().removeAll(it);
    }
    else if(parent->getChildSuites().contains(it)) {
        bool found=false;
        for(auto&i:parent->getChildSuites()) {
            if(i==it) {
                found=true;
                continue;
            }
            if(found) {
                i->setItem(root->child(row++)->index());
            }
        }
        if(!parent->getChildSuites().indexOf(it)) {
            prev=parent->getChildTests().isEmpty()?parent:parent->getChildTests().last();
        }
        else {
            prev=parent->getChildSuites().at(parent->getChildSuites().indexOf(it)-1);
        }
        parent->getChildSuites().removeAll(it);
    }
    currentIndex=prev->getItem();
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
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString(it->getFile()).split("/suite.xml")[0]));
}
QStringList MainTree::GetSuiteList() {
    return rootSuite->getSuites();
}
QStringList MainTree::getHeaders(QString file, QString test) {
    return dm.getHeaders(file, test);
}
QString MainTree::getFile(QModelIndex item) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return "";
    }
    return it->getFile();
}
QString MainTree::FindTest(QModelIndex item) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return "";
        }
    if(it->getType()=="test") {
        return getJS(it->getFile(), it->getName());
    }
    currentIndex=item;
    return "";
}
void MainTree::setCurrentItem(QModelIndex idx) {
    currentIndex=idx;
}
void MainTree::FindJSFile(QString data) {
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return;
        }
    if(it->getType()=="test") {
        return setJS(it->getFile(), it->getName(), data);
    }
}
void MainTree::RunOne(){
    if(run) {
        return;
    }
    emit sessionN();
    rootSuite->ResetAllRepeat();
    itemForRun = rootSuite->FindByItem(currentIndex);
    if(!itemForRun) {
        return;
    }
    if (itemForRun->getType() == "test") {
           runOne = true;
       itemForRun->setRepeat(0);
       CreateHtml(itemForRun);
       return;
            }
    if (itemForRun->getType() == "suite"){
        //itemForRun->DecreaseRepeat();
        auto it = itemForRun->getNextTest();
        if(it) {
            CreateHtml(it);
        }
    }

}
bool MainTree::Run() {
    if(run) {
        return false;
    }
    emit sessionN();
    rootSuite->ResetAllRepeat();
    itemForRun=rootSuite;
    auto it = rootSuite->getNextTest();
    if(it) {
        CreateHtml(it);
        }
    return true;
}
QStringList MainTree::GetTags() {
    return tags;
}
void MainTree::Parse(QString path, QStandardItem * rootItem, TreeInfo * rootSuite) {
    if(!rootSuite) {
        return;
    }
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    QStringList chilSuite;
    bool isValid=false;
    while (it.hasNext()) {
        it.next();
        if (it.filePath().contains("/.") || it.filePath().contains("/.")) {
            continue;
        }
        else {
            if (it.filePath().contains("suite.xml")) {
                isValid=true;
                QString name = getSuiteName(it.filePath());
                rootItem->setText(name);
                rootSuite->setFile(it.filePath());
                rootSuite->setItem(this->indexFromItem(rootItem));
                rootSuite->setName(name);
                rootSuite->setType("suite");
                rootSuite->setBaseRepeat(dm.Get(rootSuite->getFile()+"/suite/repeat").toInt());
                rootSuite->setDisable(dm.Get(rootSuite->getFile()+"/suite/disable")=="true"?true:false);
                QStringList list = getTestsName(it.filePath());
                for (auto& iter : list) {
                    QStandardItem * testItem = new QStandardItem(iter);
                    rootItem->appendRow(testItem);
                    TreeInfo * test = new TreeInfo();
                    test->setParent(rootSuite);
                    test->setFile(it.filePath());
                    test->setItem(this->indexFromItem(testItem));
                    test->setName(iter);
                    test->setType("test");
                    test->setBaseRepeat(dm.Get(test->getFile()+"/suite/test/"+iter+"/repeat").toInt());
                    test->setDisable(dm.Get(test->getFile()+"/suite/test/"+iter+"/disable")=="true"?true:false);
                    QStringList t=dm.Get(test->getFile()+"/suite/test/"+iter+"/tag").split(",");
                    for(auto&i:t) {
                        if(!tags.contains(i) && !i.isEmpty()) {
                            tags.push_back(i);
                        }
                    }
                    rootSuite->addChildTests(test);
                }
            }
            if (it.fileInfo().isDir() && !IsFolderEmpty(it.filePath())) {
                chilSuite.push_back(it.filePath());
            }
        }
    }
    if(isValid) {
        for(auto&ind:chilSuite) {
           QStandardItem * childItem = new QStandardItem("");
           TreeInfo * childSuite = new TreeInfo();
           rootItem->appendRow(childItem);
           childSuite->setParent(rootSuite);
           rootSuite->addChildSuites(childSuite);
           Parse(ind, childItem, childSuite);
        }
    }
}
QStandardItem * MainTree::AddItemToTree(QString name) {
    QStandardItem * item = new QStandardItem(name);
    QStandardItem * root=this->itemFromIndex(currentIndex);
    auto suite = rootSuite->FindByItem(currentIndex);
    int row=0;
    if(!suite->getChildTests().isEmpty()) {
        row=suite->getChildTests().size();
    }
    this->itemFromIndex(currentIndex)->insertRow(row,item);
    for(auto&it:suite->getChildSuites()) {
        it->setItem(root->child(++row)->index());
    }
    return item;
}
QString MainTree::ParseFolder(QString path) {
    QStandardItem * rootItem = new QStandardItem("");
    this->appendRow(rootItem);
    tags.clear();
    tags.push_back("All");
    Parse(path, rootItem, rootSuite);
    if(!rootSuite->isValid()) {
        tags.clear();
        this->clear();
        delete rootSuite;
        tags.push_back("All");
        return "Invalid folder";
    }
    return "";

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
            if(Rxml.name() == tags_name::kTest) {
                testList.push_back(Rxml.attributes().value(tags_name::kName).toString());
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
            if(Rxml.name() == tags_name::kSuite) {
                return Rxml.attributes().value(tags_name::kName).toString();
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
            if(Rxml.name() == tags_name::kTest) {
                if(Rxml.attributes().value(tags_name::kName).toString()==test_name) {
                    while(Rxml.name()!=tags_name::kExecution) {
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
            if(Rxml.name() == tags_name::kTest) {
                if(Rxml.attributes().value(tags_name::kName).toString()==test_name) {
                    while(Rxml.name()!=tags_name::kExecution) {
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
void MainTree::CreateHtml(TreeInfo *it) {
    if(runOne == false){
        emit sendSuiteInfo(dm.Get(it->getFile()+"/suite/"+"description"),
                           dm.Get(it->getFile()+"/file/"+"repeat"));
         emit sendRepeatTest (dm.Get(it->getFile()+"/suite/test/"+it->getName()+"/repeat"));
    }else if(runOne == true){
        emit sendSuiteInfo(dm.Get(it->getFile()+"/suite/"+"description"),
                           "1");
        emit sendRepeatTest ("1");
        runOne = false;
    }
    emit sendTestName(it->getName());
    emit sendSuiteName(getSuiteName(it->getFile()));
    emit sendDescTest(dm.Get(it->getFile()+"/suite/test/"+it->getName()+"/"+"description"));
    data_base_man.sessionStart();
    run=true;
    QStringList headers = getHeaders(it->getFile(), it->getName());
    QFile file(it->getPath()+"/"+"test.html");
    if(testinfo!=nullptr) {
        delete testinfo;
        delete suiteinfo;
        delete trscore;
    }
    if(view->page()){
        delete view->page();
    }
    currentTest=it;
    view->setPage(new QWebPage());
    view->page()->setProperty("_q_webInspectorServerPort",kDefaultPort);
    trscore=new TRSCore();
    view->page()->mainFrame()->addToJavaScriptWindowObject("Box", trscore);
    QObject::connect(trscore, SIGNAL(log(QString)), this, SLOT(WriteLog(QString)));
    QObject::connect(trscore, SIGNAL(fail(QString)), this, SLOT(testFail(QString)));
    testinfo=new TestInfo();
    testinfo->setName(it->getName());
    testinfo->setPath(it->getFile());
    QObject::connect(testinfo, SIGNAL(testBegin(QString)), this, SLOT(WriteLog(QString)));
    QObject::connect(testinfo, SIGNAL(testFinish(QString)), this, SLOT(testFinished(QString)));
    QObject::connect(testinfo, SIGNAL(sendMessage(QString)), this, SLOT(acceptMessage(QString)));
    view->page()->mainFrame()->addToJavaScriptWindowObject("Test", testinfo);
    suiteinfo=new SuiteInfo();
    suiteinfo->setName(this->itemFromIndex(it->getItem())->parent()->text());
    suiteinfo->setPath(it->getFile());
    view->page()->mainFrame()->addToJavaScriptWindowObject("Suite", suiteinfo);
    file.open(QIODevice::WriteOnly);
    QString page="<html>\n\t<head>";
    for(auto& h:headers) {
        page+="\n\t\t<script src=\""+h+"\" type=\"text/javascript\" charset=\"utf-8\"></script>";
    }
    QFile tools(":/js/tools.js");
    tools.open(QIODevice::ReadOnly);
    if(tools.isOpen()) {
        QString tooljs(tools.readAll());
        page+="\n\t\t<script type=\"text/javascript\">\n\t\t"+tooljs+"</script>";
        tools.close();
    }
    page+="\n\t\t<script type=\"text/javascript\">\n\t\ttry{\n\t\tTest.BEGIN();"+getJS(it->getFile(), it->getName())+"\n\t\tTest.SUCCESS();\n}\ncatch (err) {Box.log(err);}</script>";
    page+="\n\t</head>\n\t<body>\n\t</body>\n</html>";
    file.write(page.toLatin1());
    file.close();
    view->load(QUrl("file:///"+it->getPath()+"/"+"test.html"));

}
void MainTree::WriteLog(QString msg) {
    QTime time=QTime::currentTime();
    qDebug() << time.toString()+":"+QString::number(time.msec())+" "+"Box: "+msg;
    QMetaObject::invokeMethod(contextObject, "writeLog", Q_ARG(QVariant, time.toString()+":"+QString::number(time.msec())+" "+msg));
}
void MainTree::OpenInEditor(QString editor) {
    QString file;
    auto it = rootSuite->FindByItem(currentIndex);
    if(!it) {
        return;
    }
    if (it->getType() == "test") {
        file = it->getFile();
            file.data()[file.lastIndexOf('/')+1]='\0';
            file=QString(file.data());
            file+="\""+Get(tags_name::kExecution)+"\"";
    }
    ShellExecute(NULL, NULL, (const wchar_t*) editor.utf16(), (const wchar_t*) file.utf16(), NULL, SW_SHOWNORMAL);
}
void MainTree::Terminate() {
    delete view->page();
    run=false;
    WriteLog("All tests stopped.\n\n");
    rootSuite->ResetAllRepeat();
}
#include "mainwindow.moc"
