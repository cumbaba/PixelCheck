#include "MouseWatcher.h"

#include <QObject>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QApplication>

#include <iostream>

int MouseWatcher::getScreenNumber() {
    return screenNumber;
}

QPoint MouseWatcher::getMousePosition() {
    auto globalCursorPos = QCursor::pos();
    screenNumber = QApplication::desktop()->screenNumber(globalCursorPos);
    QRect mouseScreenGeometry = QApplication::desktop()->screen(screenNumber)->geometry();
    return globalCursorPos - mouseScreenGeometry.topLeft();
}


bool MouseWatcher::eventFilter(QObject* const object, QEvent* const event) {
    if (isOn) {
        if (event->type() == QEvent::MouseButtonPress) {
            start = getMousePosition();
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            isOn = false;
            end = getMousePosition();
            QCoreApplication::instance()->removeEventFilter(this);
            emit signalClickFinished();
        }
    }

    // standard event processing
    return QObject::eventFilter(object, event);
}

QRect MouseWatcher::getClickedArea() {
    return QRect(start, end);
}

bool MouseWatcher::isWatching() const {
    return isOn;
}

void MouseWatcher::watchClick() {
    isOn = true;
    QCoreApplication::instance()->installEventFilter(this);
}
