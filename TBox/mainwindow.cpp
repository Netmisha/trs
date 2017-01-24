#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trsmanager.h"
#include "mainsetting.h"
#include "datamanager.h"
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
    Q_INVOKABLE void Stop();
    Q_INVOKABLE void setRootDir(QString);
private:
    QStandardItem * Parse(QString, QStandardItem *);
    void ParseFolder(QString);
    QHash<int, QByteArray> m_roleNameMapping;
    QVector<TreeInfo> treeData;
    QString rootDir;
    QModelIndex currentIndex;
    bool run=false;
};
void fun() {
    DataManager d;
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/name");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/description");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/tag");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/repeat");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/repeat/pause");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/maxTime");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/disable");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/application");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/windowName");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/author");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/date");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/version");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/mail");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/copyright");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/license");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/metadata/info");


    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/name");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/description");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/tag");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/disable");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/execution");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/result");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/repeat");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/repeat/pause");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test1/maxTime");


    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/name");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/description");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/tag");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/disable");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/execution");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/result");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/repeat");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/repeat/pause");
    qDebug() << d.Get(QDir::currentPath()+"/Tests/suite.xml/suite/test/Test2/maxTime");
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    view = ui->webView;
    fun();
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    TRSManager *trs=new TRSManager();
    view->page()->mainFrame()->addToJavaScriptWindowObject("trs", trs);
    TRSCore *trscore=new TRSCore();
    view->page()->mainFrame()->addToJavaScriptWindowObject("core", trscore);
    view->load(QUrl("file:///"+QDir::currentPath()+"/"+"test.html"));
    //view->setVisible(false);
    qmlRegisterType<MainTree>("cMainTree", 1, 0, "MainTree" );
    qmlRegisterType<MainSetting>("MainSetting", 1, 0, "Setting" );
    QQuickView* qmlView = new QQuickView();
    QWidget* container = QWidget::createWindowContainer(qmlView, ui->centralWidget);
    QObject::connect(trs, SIGNAL(RunNext()),this, SLOT(RunNext()));
    QObject::connect(trs, SIGNAL(writeMSG(QString)),this, SLOT(writeMSG(QString)));
    qmlView->setSource(QUrl("qrc:/MainForm.ui.qml"));
    object = qmlView->rootObject();
    ui->verticalLayout->addWidget(container);
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::RunNext(){
    QMetaObject::invokeMethod(object, "runNext");
}
void MainWindow::writeMSG(QString msg){
    QMetaObject::invokeMethod(object, "writeLog", Q_ARG(QVariant, msg));
}

void MainTree::RunNext(){
    while (treeData.size()>0 && run) {
        TreeInfo ti = treeData.first();
        treeData.removeFirst();
        if (ti.type == "test") {
            TRSManager::Run(getJS(ti.file, ti.name));
            break;
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
    ParseFolder(path);
}
void MainTree::setRootDir(QString path) {
    rootDir=path;
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
    currentIndex=this->index(0,0);
    for (auto&it : treeData) {
        if (it.item == item && it.type == "test") {
            currentIndex=item;
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
void MainTree::Run() {
    run=true;
    while (treeData.size()>0) {
        TreeInfo ti = treeData.first();
        treeData.removeFirst();
        if (ti.type == "test") {
             TRSManager::Run(getJS(ti.file, ti.name));
            break;
        }
    }
}
void MainTree::Stop() {
    run=false;
}
QStandardItem * MainTree::Parse(QString path, QStandardItem * root) {
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    QStandardItem * suite;
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
                    treeData.push_back(info);
                }
            }
            if (it.fileInfo().isDir()) {
                Parse(it.filePath(), suite);
            }
        }
    }
    return suite;
}
void MainTree::ParseFolder(QString path)
{
    QStandardItem * root = new QStandardItem(QString("Tests"));
    this->appendRow(root);
    Parse(path, root);
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
