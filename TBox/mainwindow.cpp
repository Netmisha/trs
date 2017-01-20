#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trsmanager.h"
QWebView * view;
struct TreeInfo {
    QString file;
    QString name;
    QString type;
    QModelIndex item;
};
class MyTreeModel : public QStandardItemModel
        {
            Q_OBJECT
        public:
            explicit MyTreeModel(QObject *parent = 0) :
        QStandardItemModel(parent)
            {

                m_roleNameMapping[MyTreeModel_Role_Name] = "name_role";

                ParseFolder("D:/Projects/trs/TBox/Tests");
            }

            virtual ~MyTreeModel() = default;

            enum MyTreeModel_Roles
            {
                MyTreeModel_Role_Name = Qt::DisplayRole
            };

            QHash<int, QByteArray> roleNames() const override{
                return m_roleNameMapping;
            }
public slots:
    Q_INVOKABLE void Reload() {
        this->clear();
        ParseFolder("D:/Projects/trs/TBox/Tests");
    }
    Q_INVOKABLE QString getFile(QModelIndex item) {
        currentScript="";
        for(auto&it:treeData) {
            if(it.item==item) {
                return it.file;
            }
        }
        return NULL;
    }
    Q_INVOKABLE QString getJS(QModelIndex item) {
                currentScript="";
        for(auto&it:treeData) {
            if(it.item==item && it.type=="test") {
                currentScript=TRSManager::getJS(it.file, it.name);
                return currentScript;
            }
        }
        return "";
    }
    Q_INVOKABLE void Run() {
        TRSManager::Run(currentScript);
    }
    private:
        QStandardItem * Parse(QString path, QStandardItem * root) {
            QDirIterator it(path, QDirIterator:: NoIteratorFlags);
            QStandardItem * suite;
            while (it.hasNext()) {
                it.next();
                if(it.filePath().contains("/.") || it.filePath().contains("/.")) {
                    continue;
                }
                else {
                    if(it.filePath().contains(".xml")) {
                        QString name = TRSManager::getSuiteName(it.filePath());
                        suite= new QStandardItem (name);
                        root->appendRow(suite);
                        TreeInfo info;
                        info.file=it.filePath();
                        info.item=this->indexFromItem(suite);
                        info.name=name;
                        info.type="suite";
                        treeData.push_back(info);
                        QStringList list=TRSManager::getTestsName(it.filePath());
                        for(auto& iter:list) {
                            QStandardItem * test= new QStandardItem (iter);
                            suite->appendRow(test);
                            TreeInfo info;
                            info.item=this->indexFromItem(test);
                            info.name=iter;
                            info.file=it.filePath();
                            info.type="test";
                            treeData.push_back(info);
                        }
                    }
                    if(it.fileInfo().isDir()) {
                        Parse(it.filePath(),suite);
                    }
                }
            }
            return suite;
        }
        void ParseFolder(QString path)
        {
            QStandardItem * root= new QStandardItem (QString("Tests"));
            this->appendRow(root);
            Parse(path,root);
        }
        QHash<int, QByteArray> m_roleNameMapping;
        QVector<TreeInfo> treeData;
        QString currentScript="";
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = ui->webView;
    view->page()->mainFrame()->addToJavaScriptWindowObject("myoperations", new TRSManager);
    view->setVisible(false);
    qmlRegisterType<MyTreeModel>("ca.models", 1, 0, "MyTreeModel" );

    QQuickView* qmlView = new QQuickView();
    TRSManager trs;

    QWidget* container = QWidget::createWindowContainer(qmlView, ui->centralWidget);
    qmlView->rootContext()->setContextProperty("trsCore", &trs);
    qmlView->setSource(QUrl("qrc:/MainForm.ui.qml"));
    ui->verticalLayout->addWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.moc"
