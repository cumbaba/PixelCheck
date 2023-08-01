#include "MouseWatcher.h"

#include <QApplication>
#include <QScreen>

#include <iostream>

/*QPoint cursorPos = QCursor::pos();
QScreen *screen = QGuiApplication::screenAt(cursorPos);
if (screen) {
    QRect rect(cursorPos.x() - 50, cursorPos.y() - 50, 100, 100);
    QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());
}*/

MouseWatcher::MouseWatcher(QObject* const parent): QObject(parent),
    cursorImageWidth(40),
    cursorImageHeight(40) {

    cursorImageMonitor.setInterval(100);

    QObject::connect(&cursorImageMonitor, &QTimer::timeout, this, &MouseWatcher::updateCursorImage);
}

MouseWatcher::~MouseWatcher() {
    cursorImageMonitor.stop();
    cursorImageMonitor.disconnect();
}


MouseWatcher& MouseWatcher::instance() {
    static MouseWatcher _instance;
    return _instance;
}

void MouseWatcher::CaptureMouseClick() {
    if (!instance().isClickCaptureOn) {
        instance().isClickCaptureOn = true;
        QCoreApplication::instance()->installEventFilter(&instance());
    }
}

void MouseWatcher::StartCursorImageWatch() {
    if (!instance().cursorImageMonitor.isActive()) {
        instance().cursorImageMonitor.start();
    }
}
void MouseWatcher::StopCursorImageWatch() {
    if (instance().cursorImageMonitor.isActive()) {
        instance().cursorImageMonitor.stop();
    }
}

bool MouseWatcher::eventFilter(QObject* const object, QEvent* const event) {
    if (isClickCaptureOn) {
        if (event->type() == QEvent::MouseButtonPress) {
            clickStart = GetMousePosition();
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            isClickCaptureOn = false;
            QCoreApplication::instance()->removeEventFilter(this);

            clickEnd = GetMousePosition();

            emit signalClickFinished();
        }
    }

    // standard event processing
    return QObject::eventFilter(object, event);
}

void MouseWatcher::updateCursorImage() {
    auto pos = GetMousePosition();
    QScreen *screen = QGuiApplication::screenAt(pos);

    if (screen) {
        emit signalCursorImageUpdate(screen->grabWindow(0,
                                                        pos.x() - cursorImageWidth / 2,
                                                        pos.y() - cursorImageHeight / 2,
                                                        cursorImageWidth,
                                                        cursorImageHeight));
    }
}

QPixmap MouseWatcher::doGetClickedArea() {
    auto area =  QRect(clickStart, clickEnd);

    std::cout << "[p1] x: " << area.x() << " y: " << area.y() <<
              " [p2] w: " << area.width() << " w: " << area.height() << std::endl;


    auto pos = GetMousePosition();
    QScreen *screen = QGuiApplication::screenAt(pos);

    if (screen) {
        return screen->grabWindow(0,
                                area.x(),
                                area.y(),
                                area.width(),
                                area.height());
    }
}

QPoint MouseWatcher::GetMousePosition() {
    QRect mouseScreenGeometry = QGuiApplication::screenAt(QCursor::pos())->geometry();
    return QCursor::pos() - mouseScreenGeometry.topLeft();
}

QPixmap MouseWatcher::GetLastTakenCursorImage() {
    return instance().lastTakenCursorImage;
}

void MouseWatcher::SetCursorImageHeight(const unsigned int aCursorImageHeight) {
    if (instance().cursorImageHeight != aCursorImageHeight) {
        instance().cursorImageHeight = aCursorImageHeight;
    }
}

void MouseWatcher::SetCursorImageWidth(const unsigned int aCursorImageWidth) {
    if (instance().cursorImageWidth != aCursorImageWidth) {
        instance().cursorImageWidth = aCursorImageWidth;
    }
}

QPixmap MouseWatcher::GetClickedArea() {
    return instance().doGetClickedArea();
}
