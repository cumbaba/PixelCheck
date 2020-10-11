#include "ScreenshotTaker.h"

#include <QApplication>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QScreen>

ScreenshotTaker::ScreenshotTaker(QObject* const parent) : QObject(parent) {
    QObject::connect(&mouseWatcher, &MouseWatcher::signalClickFinished,
                     this, &ScreenshotTaker::onFinish);
}

ScreenshotTaker::~ScreenshotTaker() {
    mouseWatcher.disconnect();
}

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

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::CrossCursor));
}

void ScreenshotTaker::onFinish() {
    window->setWindowState(Qt::WindowState::WindowNoState);
    window->setFlags(Qt::WindowType::Window);

    window->setMaximumSize(lastSize);
    window->setPosition(lastPosition);

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));

    lastTakenShot = mouseWatcher.getClickedArea();
}
