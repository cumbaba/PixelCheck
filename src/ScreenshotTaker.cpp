#include "ScreenshotTaker.h"

#include <QApplication>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QScreen>

#include "tools/MouseWatcher.h"

ScreenshotTaker::ScreenshotTaker(QObject* const parent) : QObject(parent) {
    QObject::connect(&MouseWatcher::instance(), &MouseWatcher::signalClickFinished,
                     this, &ScreenshotTaker::onFinish);
}

ScreenshotTaker::~ScreenshotTaker() {
    this->disconnect();
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
    window->setFlags(window->flags() | Qt::WindowStaysOnTopHint);
}

void ScreenshotTaker::doTurnOn() {
    lastSize = window->size();
    lastPosition = window->position();

    window->setMaximumSize(window->screen()->geometry().size());
    window->setWindowState(Qt::WindowState::WindowMaximized);
    window->setFlags(window->flags() | Qt::WindowType::FramelessWindowHint);

    MouseWatcher::CaptureMouseClick();

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::CrossCursor));
}

void ScreenshotTaker::onFinish() {
    lastTakenShot = MouseWatcher::GetClickedArea();

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));

    window->setWindowState(Qt::WindowState::WindowNoState);
    window->setFlags(window->flags() ^ Qt::WindowType::FramelessWindowHint);

    window->setMaximumSize(lastSize);
    window->setPosition(lastPosition);
}
