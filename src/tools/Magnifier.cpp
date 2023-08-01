#include "Magnifier.h"

#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QBuffer>

#include "MouseWatcher.h"

Magnifier::Magnifier(QObject* const parent) : QObject(parent) {
    window = new QMainWindow();

    window->setGeometry(100, 100, 200, 200);
    window->setWindowState(Qt::WindowState::WindowActive);
    window->setWindowFlags(window->windowFlags() | Qt::SubWindow | Qt::WindowStaysOnTopHint);

    QObject::connect(&MouseWatcher::instance(), &MouseWatcher::signalCursorImageUpdate,
                     this, &Magnifier::onCursorImageReceived);

    window->show();
}

Magnifier::~Magnifier() {}

void Magnifier::close(QQuickCloseEvent* close) {
    Q_UNUSED(close)

    QObject::disconnect(&MouseWatcher::instance(), &MouseWatcher::signalCursorImageUpdate,
                        this, &Magnifier::onCursorImageReceived);
    MouseWatcher::StopCursorImageWatch();
    window->close();
    delete window;
    QCoreApplication::quit();
}

Magnifier& Magnifier::instance() {
    static Magnifier _instance;
    return _instance;
}

void Magnifier::turnOn() {
    if (!isOn) {
        isOn = true;

        MouseWatcher::StartCursorImageWatch();
        window->setVisible(isOn);
    }
}

void Magnifier::turnOff() {
    if (isOn) {
        isOn = false;

        MouseWatcher::StopCursorImageWatch();
        window->setVisible(isOn);
    }
}

QUrl Magnifier::getMouseimage() {
    const auto imageToUrl = [] (const QImage& image)->QUrl
    {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "png");
        QString base64 = QString::fromUtf8(byteArray.toBase64());
        return QString("data:image/png;base64,") + base64;
    };


    return imageToUrl(last_image.toImage());
}

void Magnifier::onCursorImageReceived(const QPixmap& image) {
    auto scaledImage = image.scaled(window->size(), Qt::IgnoreAspectRatio);
    coverCenterPixel(&scaledImage);
/*
    QPalette palette;
    palette.setBrush( QPalette::ColorRole::Window, scaledImage);*/

    last_image = scaledImage;

  // window->setPalette(palette);

}

void Magnifier::coverCenterPixel(QPixmap* image) {
    QPainter* paint = new QPainter(image);
    paint->setPen(QColor(255, 80, 180, 255));
    paint->drawRect(99, 99, 6, 6);
    delete paint;
}
;
