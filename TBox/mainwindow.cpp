#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trsmanager.h"
#include "mainsetting.h"
#include "datamanager.h"
#include "testinfo.h"
#include "filesave.h"
QWebView * view;

class MainTree : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit MainTree(QObject *parent = 0) :
        QStandardItemModel(parent){
        m_roleNameMapping[MainTree_Role_Name] = "name_role";
    }
    virtual ~MainTree() = default;
    enum MainTree_Roles{
        MainTree_Role_Name = Qt::DisplayRole
    };
    QHash<int, QByteArray> roleNames() const override{
        return m_roleNameMapping;
    }
    public slots:
    Q_INVOKABLE void RunNext();
    Q_INVOKABLE void Load(QString path);
    Q_INVOKABLE QString getFile(QModelIndex);
    Q_INVOKABLE QString FindTest(QModelIndex);
    Q_INVOKABLE void FindJSFile(QString);

    Q_INVOKABLE static QStringList getTestsName(QString);
    Q_INVOKABLE static QString getSuiteName(QString);
    Q_INVOKABLE static QString getJS(QString, QString);
    Q_INVOKABLE static void setJS(QString, QString, QString);
    Q_INVOKABLE void Run();
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
private:
    QStandardItem * Parse(QString, QStandardItem *);
    QStandardItem * AddItemToTree(QString);
    void ParseFolder(QString);
    bool CheckTest(TreeInfo);
    QHash<int, QByteArray> m_roleNameMapping;
    QVector<TreeInfo> treeData;
    QString rootDir;
    QModelIndex currentIndex;
    bool run=false;
    QStringList tags;
    QString currentTag="All";
    DataManager dm;
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    view = ui->webView;
    CreateHtml();
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    TRSManager *trs=new TRSManager();
    view->page()->mainFrame()->addToJavaScriptWindowObject("trs", trs);
    TRSCore *trscore=new TRSCore();
    view->page()->mainFrame()->addToJavaScriptWindowObject("core", trscore);
    TestInfo *testinfo=new TestInfo();
    view->page()->mainFrame()->addToJavaScriptWindowObject("Test", testinfo);
    view->load(QUrl("file:///"+QDir::currentPath()+"/"+"test.html"));
    //view->setVisible(false);
    qmlRegisterType<MainTree>("cMainTree", 1, 0, "MainTree" );
    qmlRegisterType<MainSetting>("MainSetting", 1, 0, "Setting" );
    qmlRegisterType<FileSaveDialog>("FileSave", 1, 0, "FileSaveDialog");
    QQuickView* qmlView = new QQuickView();
    QWidget* container = QWidget::createWindowContainer(qmlView, ui->centralWidget);
    QObject::connect(trs, SIGNAL(RunNext()),this, SLOT(RunNext()));
    QObject::connect(trs, SIGNAL(writeMSG(QString)),this, SLOT(writeMSG(QString)));
    qmlView->setSource(QUrl("qrc:/MainForm.ui.qml"));
    object = qmlView->rootObject();
    ui->verticalLayout->addWidget(container);
    QWebSettings* settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    settings->setAttribute(QWebSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);
}
MainWindow::~MainWindow(){
    QMetaObject::invokeMethod(object, "closeAll");
    delete ui;
}
void MainWindow::RunNext(){
    QMetaObject::invokeMethod(object, "runNext");
}
void MainWindow::writeMSG(QString msg){
    QMetaObject::invokeMethod(object, "writeLog", Q_ARG(QVariant, msg));
}
void MainWindow::CreateHtml() {
    QFile file(QDir::currentPath()+"/"+"test.html");
    if(!file.exists()) {
        file.open(QIODevice::WriteOnly);
        QString page="<html>\n\t<head>\n\t</head>\n\t<body>\n\t</body>\n</html>";
        file.write(page.toLatin1());
        file.close();
    }
}
void MainTree::RunNext(){
    while (treeData.size()>0 && run) {
        TreeInfo* ti = treeData.begin();
        if(ti->repeat<=0) {
            treeData.removeFirst();
            ti = treeData.begin();
        }
        if (ti->type == "test" && CheckTest(*ti)) {
            ti->repeat--;
            TRSManager::Run(getJS(ti->file, ti->name), ti->file, ti->name);
            break;
        }
        else {
            treeData.removeFirst();
            ti = treeData.begin();
        }
    }
    if (treeData.size()==0 || !run) {
        Load(rootDir);
        run = false;
    }
}
void MainTree::Load(QString path) {
    if(path=="") {
        path=rootDir;
    }
    if(path!=rootDir) {
        rootDir=path;
    }
    this->clear();
    treeData.clear();
    if(rootDir!="") {
        ParseFolder(path);
    }
}
void MainTree::setRootDir(QString path) {
    rootDir=path;
}
QString MainTree::AddNewTest(QString name, QString dis, QString exe, QString tag, QString rep, QString disable) {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            QString res= dm.AddTest(it.file, name, dis, tag, exe, rep, disable);
            if(res!="") {
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
    return "exist";
}
QString MainTree::AddNewSuite(QString name, QString dis, QString rep, QString disable) {
    for (auto&it : treeData) {
        if (it.item == currentIndex) {
            QString res=dm.AddSuite(it.file, name, dis, rep, disable);
            if(res!="") {
                TreeInfo info;
                info.file = it.file;
                info.file.data()[info.file.lastIndexOf("/")+1]='\0';
                info.file = QString(info.file.data())+name+"/suite.xml";
                info.item = this->indexFromItem(AddItemToTree(name));
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
            }
            else if(it.type == "suite") {
                dm.Set(it.file+"/suite/"+path, data);
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
    for (auto it =treeData.begin(); it!=treeData.end(); it++) {
        if (it->item == currentIndex) {
            if(it->type=="suite") {
                dm.RemoveSuite(it->file);   // need fixing!!!!!!!!!!!!!!!!!
                QStandardItem * root=this->itemFromIndex(currentIndex);
                it=treeData.erase(it);
                while(root->hasChildren()){
                    it=treeData.erase(it);
                    this->removeRow(root->child(0)->index().row(), currentIndex);
                }
                this->removeRow(currentIndex.row(), currentIndex.parent());
                break;
            }
            else {
                dm.RemoveTest(it->file, it->name);
                this->removeRow(currentIndex.row(), currentIndex.parent());
                currentIndex=(--it)->item;
                treeData.erase(++it);
                break;
            }
        }
    }
    return "";
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
void MainTree::FindJSFile(QString data) {
    for (auto&it : treeData) {
        if (it.item == currentIndex && it.type == "test") {
            setJS(it.file, it.name, data);
        }
    }
}
void MainTree::RunOne() {
    for (auto&it : treeData) {
        if (it.item == currentIndex && it.type == "test") {
            view->page()->mainFrame()->evaluateJavaScript("Test.setPath('"+it.file+"'); Test.setName('"+it.name+"');"+getJS(it.file, it.name));
        }
    }
}
void MainTree::Run() {
    run=true;
    while (treeData.size()>0) {
        TreeInfo * ti = treeData.begin();
        if (ti->type == "test" && CheckTest(*ti)) {
            ti->repeat--;
             view->page()->mainFrame()->evaluateJavaScript("Test.setPath('"+ti->file+"'); Test.setName('"+ti->name+"');"+getJS(ti->file, ti->name) + "trs.RunNext();");
        }
        else {
            treeData.removeFirst();
            ti = treeData.begin();
        }
    }
    if (treeData.size()==0 || !run) {
        Load(rootDir);
        run = false;
    }
}
QStringList MainTree::GetTags() {
    return tags;
}
void MainTree::Stop() {
    run=false;
}
QStandardItem * MainTree::Parse(QString path, QStandardItem * root) {
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    QStandardItem * suite;
    QStringList chilSuite;
    while (it.hasNext()) {
        it.next();
        if (it.filePath().contains("/.") || it.filePath().contains("/.")) {
            continue;
        }
        else {
            if (it.filePath().contains(".xml")) {
                QString name = getSuiteName(it.filePath());
                suite = new QStandardItem(name);
                root->appendRow(suite);
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
                        if(!tags.contains(i)) {
                            tags.push_back(i);
                        }
                    }
                    treeData.push_back(info);
                }
            }
            if (it.fileInfo().isDir()) {
                chilSuite.push_back(it.filePath());
            }
        }
    }
    for(auto&ind:chilSuite) {
        Parse(ind, suite);
    }
    return suite;
}
QStandardItem * MainTree::AddItemToTree(QString name) {
    QStandardItem * item = new QStandardItem(name);
    this->itemFromIndex(currentIndex)->appendRow(item);
    return item;
}
void MainTree::ParseFolder(QString path)
{
    QStandardItem * root = new QStandardItem(QString("Tests"));
    this->appendRow(root);
    tags.clear();
    tags.push_back("All");
    Parse(path, root);
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
    }
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
#include "mainwindow.moc"
