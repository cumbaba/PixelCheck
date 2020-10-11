#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QIcon>
#include <QQmlEngine>

#include "ScreenshotCommander.h"
#include "ScreenshotTaker.h"

void customMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    Q_UNUSED(context)

    if (type != QtWarningMsg || !msg.contains("setGeometry: Unable to set geometry ")) {
        QByteArray localMsg = msg.toLocal8Bit();
        fprintf(stdout, localMsg.constData());
    }
}

int main(int argc, char* argv[]) {
    qInstallMessageHandler(customMessageOutput);

    QApplication  app(argc, argv);
    app.setWindowIcon(QIcon("resources/check.svg"));

    QQmlApplicationEngine engine;

    auto ssTaker = new ScreenshotCommander();

    engine.rootContext()->setContextProperty("ScreenshotCommander", ssTaker);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    auto* window = qobject_cast<QQuickWindow*>(engine.rootObjects()[0]);

    if (!window) {
        qFatal("Error: Your root item has to be a window.");
        return -1;
    }

    ScreenshotTaker::SetWindow(window);

    return app.exec();
}
