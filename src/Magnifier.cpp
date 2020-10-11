#include "Magnifier.h"

#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QPainter>

#include "MouseWatcher.h"

Magnifier::Magnifier(QObject* const parent) : QObject(parent) {
    window = new QMainWindow(QApplication::desktop());

    window->setGeometry(100, 100, 200, 200);
    window->setWindowState(Qt::WindowState::WindowActive);
    window->setWindowFlags(window->windowFlags() | Qt::SubWindow | Qt::WindowStaysOnTopHint);

    QObject::connect(&MouseWatcher::instance(), &MouseWatcher::signalCursorImageUpdate,
                     this, &Magnifier::onCursorImageReceived);
}

void Magnifier::close(QQuickCloseEvent* close) {
    Q_UNUSED(close)

    QObject::disconnect(&MouseWatcher::instance(), &MouseWatcher::signalCursorImageUpdate,
                        this, &Magnifier::onCursorImageReceived);
    MouseWatcher::StopCursorImageWatch();
    window->close();
    delete window;
    QCoreApplication::quit();
}

Magnifier::~Magnifier() {
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

void Magnifier::onCursorImageReceived(const QPixmap& image) {
    auto scaledImage = image.scaled(window->size(), Qt::IgnoreAspectRatio);
    coverCenterPixel(&scaledImage);

    QPalette palette;
    palette.setBrush(QPalette::Background, scaledImage);

    window->setPalette(palette);
}

void Magnifier::coverCenterPixel(QPixmap* image) {
    QPainter* paint = new QPainter(image);
    paint->setPen(QColor(255, 80, 180, 255));
    paint->drawRect(99, 99, 6, 6);
    delete paint;
}
