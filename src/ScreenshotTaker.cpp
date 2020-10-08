#include "ScreenshotTaker.h"

#include <QApplication>
#include <QGuiApplication>
#include <QObject>
#include <QDesktopWidget>
#include <QScreen>

#include <iostream>

ScreenshotTaker::ScreenshotTaker(QObject* const parent) : QObject(parent) {}

ScreenshotTaker::~ScreenshotTaker() {}

ScreenshotTaker& ScreenshotTaker::instance() {
    static ScreenshotTaker _instance;
    return _instance;
}

void ScreenshotTaker::SetWindow(QQuickWindow* aWindow) {
    instance().doSetWindow(aWindow);
}

QPixmap ScreenshotTaker::GetScreenshot() {
    return instance().lastTakenShot;
}


void ScreenshotTaker::TurnOn() {
    instance().doTurnOn();
}

void ScreenshotTaker::doSetWindow(QQuickWindow* aWindow) {
    window = aWindow;
    window->setFlags(Qt::WindowStaysOnTopHint | window->flags());
}

void ScreenshotTaker::doTurnOn() {
    lastSize = window->size();
    lastPosition = window->position();
    window->setMaximumSize(window->screen()->geometry().size());

    window->setWindowState(Qt::WindowState::WindowMaximized);
    window->setFlags(Qt::WindowType::FramelessWindowHint);

    mouseWatcher.watchClick();
    QObject::connect(&mouseWatcher, &MouseWatcher::signalClickFinished,
                     this, &ScreenshotTaker::onFinish);

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::CrossCursor));
}

void ScreenshotTaker::onFinish() {
    QObject::disconnect(&mouseWatcher, &MouseWatcher::signalClickFinished,
                        this, &ScreenshotTaker::onFinish);

    window->setWindowState(Qt::WindowState::WindowNoState);
    window->setFlags(Qt::WindowType::Window);

    window->setMaximumSize(lastSize);
    window->setPosition(lastPosition);

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));


    std::cout << "[p1] x: " << mouseWatcher.getClickedArea().x() << " y: " << mouseWatcher.getClickedArea().y()
              << " [p2] w: " <<  mouseWatcher.getClickedArea().width() << " w: "
              <<   mouseWatcher.getClickedArea().height() <<
              std::endl;

    lastTakenShot = QApplication::desktop()->screen(mouseWatcher.getScreenNumber())->grab(mouseWatcher.getClickedArea());
}
