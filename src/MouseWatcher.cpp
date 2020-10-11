#include "MouseWatcher.h"

#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

MouseWatcher::MouseWatcher(QObject* const parent): QObject(parent) {}

MouseWatcher::~MouseWatcher() {}

bool MouseWatcher::eventFilter(QObject* const object, QEvent* const event) {
    if (isOn) {
        if (event->type() == QEvent::MouseButtonPress) {
            start = getMousePosition();
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            QCoreApplication::instance()->removeEventFilter(this);

            isOn = false;
            end = getMousePosition();
            emit signalClickFinished();
        }
    }

    // standard event processing
    return QObject::eventFilter(object, event);
}

QPixmap MouseWatcher::getClickedArea() {
    auto area =  QRect(start, end);

    std::cout << "[p1] x: " << area.x() << " y: " << area.y() <<
              " [p2] w: " << area.width() << " w: " << area.height() << std::endl;

    return QPixmap::grabWindow(getScreenNumber(),
                               area.x(),
                               area.y(),
                               area.width(),
                               area.height());
}

void MouseWatcher::watchClick() {
    isOn = true;
    QCoreApplication::instance()->installEventFilter(this);
}

QPoint MouseWatcher::getMousePosition() {
    auto globalCursorPos = QCursor::pos();
    screenNumber = QApplication::desktop()->screenNumber(globalCursorPos);
    QRect mouseScreenGeometry = QApplication::desktop()->screen(screenNumber)->geometry();
    return globalCursorPos - mouseScreenGeometry.topLeft();
}

int MouseWatcher::getScreenNumber() const {
    return screenNumber;
}

bool MouseWatcher::isWatching() const {
    return isOn;
}
