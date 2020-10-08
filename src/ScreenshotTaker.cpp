#include "ScreenshotTaker.h"

#include <QObject>
#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>

#include <iostream>

ScreenshotTaker::ScreenshotTaker() {}

ScreenshotTaker& ScreenshotTaker::instance() {
    static ScreenshotTaker _instance;
    return _instance;
}

void ScreenshotTaker::SetWindow(QQuickWindow* aWindow) {
    instance().doSetWindow(aWindow);
}


void ScreenshotTaker::TurnOn() {
    instance().doTurnOn();
}

void ScreenshotTaker::doSetWindow(QQuickWindow* aWindow) {
    window = aWindow;
    window->setFlags(Qt::WindowStaysOnTopHint | window->flags());
}

void ScreenshotTaker::doTurnOn() {
    if (!mouseWatcher.isWatching()) {
        mouseWatcher.watchClick();
        //wtf
//        QObject::connect(this, &ScreenshotTaker::signalClickFinished,
//                this, &ScreenshotTaker::onFinish);

        QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::CrossCursor));
    }
}

void ScreenshotTaker::onFinish() {
    if (mouseWatcher.isWatching()) {
        window->setWindowState(Qt::WindowState::WindowNoState);
        window->setFlags(Qt::WindowType::Window);

        QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));


        std::cout << "[p1] x: " << mouseWatcher.getClickedArea().x() << " y: " << mouseWatcher.getClickedArea().y()
                  << " [p2] x: " << mouseWatcher.getClickedArea().x() + mouseWatcher.getClickedArea().width() << " y: "
                  << mouseWatcher.getClickedArea().y() +  mouseWatcher.getClickedArea().height() <<
                  std::endl;

        lastTakenShot = QApplication::desktop()->screen(mouseWatcher.getScreenNumber())->grab(mouseWatcher.getClickedArea());
    }
}
