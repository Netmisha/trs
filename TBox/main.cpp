#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWebEngine/qtwebengineglobal.h>
#include "utils.h"

static QUrl startupUrl()
{
    QUrl ret;
    QStringList args(qApp->arguments());
    args.takeFirst();
    Q_FOREACH (const QString& arg, args) {
        if (arg.startsWith(QLatin1Char('-')))
             continue;
        ret = Utils::fromUserInput(arg);
        if (ret.isValid())
            return ret;
    }
    return QUrl(QStringLiteral("http://qt.io/"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtWebEngine::initialize();
    QQmlApplicationEngine engine;
    Utils utils;
    engine.rootContext()->setContextProperty("utils", &utils);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QMetaObject::invokeMethod(engine.rootObjects().first(), "load", Q_ARG(QVariant, startupUrl()));

    return app.exec();
}
