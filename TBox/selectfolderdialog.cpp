#include "selectfolderdialog.h"

#include <QApplication>
#include <QQuickWindow>
#include <QStandardPaths>

SelectFolderDialog::SelectFolderDialog(QQuickItem *parent)
    : QQuickItem(parent)
    , m_dlgHelper(init_helper())
    , m_modality(Qt::WindowModal)
    , m_options(QSharedPointer<QFileDialogOptions>(new QFileDialogOptions()))
{

    QApplication *appHasQtWidgetsSupport = qobject_cast<QApplication *>(QCoreApplication::instance());
    Q_ASSERT(appHasQtWidgetsSupport);
    Q_UNUSED(appHasQtWidgetsSupport);

    if (valid())
    {
        connect(m_dlgHelper, &QPlatformFileDialogHelper::accept,
                this, &SelectFolderDialog::accept);
        connect(m_dlgHelper, &QPlatformFileDialogHelper::reject,
                this, &SelectFolderDialog::reject);
    }
}

SelectFolderDialog::~SelectFolderDialog()
{
    if (m_dlgHelper)
        m_dlgHelper->hide();
    delete m_dlgHelper;
}

bool SelectFolderDialog::valid()
{
    if (m_dlgHelper) return true;
    else return false;
}

QUrl SelectFolderDialog::fileUrl()
{
    return fileUrl_;
}

void SelectFolderDialog::setFileUrl(QUrl fileUrl)
{
    if (fileUrl_ != fileUrl)
    {
        fileUrl_ = fileUrl;
        emit fileUrlChanged();
    }
}

QString SelectFolderDialog::filename()
{
    return filename_;
}

void SelectFolderDialog::setFilename(QString filename)
{
    if (filename_ != filename)
    {
        filename_ = filename;
        emit filenameChanged();
    }
}

QString SelectFolderDialog::title()
{
    return title_;
}

void SelectFolderDialog::setTitle(QString title)
{
    if (title_ != title)
    {
        title_ = title;
        emit titleChanged();
    }
}

QStringList SelectFolderDialog::nameFilters()
{
    return nameFilters_;
}

void SelectFolderDialog::setNameFilters(QStringList nameFilters)
{
    if (nameFilters_ != nameFilters)
    {
        nameFilters_ = nameFilters;
        emit nameFiltersChanged();
    }
}

QPlatformFileDialogHelper* SelectFolderDialog::init_helper()
{
    return static_cast<QPlatformFileDialogHelper*>(
                QGuiApplicationPrivate::platformTheme()->createPlatformDialogHelper(QPlatformTheme::FileDialog)
                );
}

void SelectFolderDialog::open()
{
    if (!valid()) return;

    QQuickItem *parent = this->parentItem();
    Q_ASSERT(parent);

    QQuickWindow *window = parent->window();
    Q_ASSERT(window);

    m_parentWindow = window;

    m_options->setFileMode(QFileDialogOptions::Directory);
    m_options->setAcceptMode(QFileDialogOptions::AcceptOpen);
    m_options->setOption(QFileDialogOptions::ShowDirsOnly);
    m_options->setWindowTitle(title());
    m_options->setNameFilters(nameFilters());

    /*
     * Mac:
     * Set filename incl. directory via setInitiallySelectedFiles()
     *
     * Windows:
     * Set filename via setInitiallySelectedFiles() and let Windows choose the directory.
     * Default directory: C:\\Users\XYZ\Downloads
     *
     * Gnome:
     * Set directory via QPlatformFileDialogHelper::setDirectory() and leave
     * filename empty, since QGtk2FileDialogHelper can not set non-existing filenames.
     *
     */
    const QString folder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    const QString name = filename();

#ifdef Q_OS_OSX
    QUrl initialSelection = QUrl::fromLocalFile(QFileInfo(folder, name).absoluteFilePath());
    qDebug() << "Initial file:" << initialSelection;
    m_options->setInitiallySelectedFiles(QList<QUrl>() << initialSelection);
#endif
#ifdef Q_OS_WIN
    qDebug() << "Initial filename:" << name;
    m_options->setInitiallySelectedFiles(QList<QUrl>() << QUrl::fromLocalFile(name));
#endif
#ifdef Q_OS_LINUX
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 2))
    // Wohoo, big fix! https://codereview.qt-project.org/91501
    QUrl initialSelection = QUrl::fromLocalFile(QFileInfo(folder, name).absoluteFilePath());
    qDebug() << "Initial file:" << initialSelection;
    m_options->setInitiallySelectedFiles(QList<QUrl>() << initialSelection);
    #else
    qDebug() << "Initial directory:" << folder;
    m_dlgHelper->setDirectory(QUrl::fromLocalFile(folder));
    #endif
#endif

    m_dlgHelper->setOptions(m_options);
    m_dlgHelper->setFilter(); // applyOptions();

    Qt::WindowFlags flags = Qt::Dialog;
    if (!title().isEmpty()) flags |= Qt::WindowTitleHint;

    m_visible = m_dlgHelper->show(flags, m_modality, m_parentWindow);
}

void SelectFolderDialog::close()
{
    if (!valid()) return;

    m_dlgHelper->hide();
    m_visible = false;
}

void SelectFolderDialog::accept()
{
    if (!valid()) return;

    m_dlgHelper->hide();

    QList<QUrl> selectedUrls = m_dlgHelper->selectedFiles();
    if (!selectedUrls.empty())
    {
        setFileUrl(selectedUrls.at(0));
    }

    emit accepted();
}

void SelectFolderDialog::reject()
{
    if (!valid()) return;

    m_dlgHelper->hide();
    emit rejected();
}
