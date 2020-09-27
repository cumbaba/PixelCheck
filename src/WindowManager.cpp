#include "WindowManager.h"
#include <QGuiApplication>
#include <QScreen>

WindowManager& WindowManager::instance() {
    static WindowManager _instance;
    return _instance;
}

void WindowManager::doSetWindow(QQuickWindow* aWindow) {
    window = aWindow;
    window->setFlags(Qt::WindowStaysOnTopHint | window->flags());
}

void WindowManager::doMaximizeWindow() {
    lastSize = window->size();
    lastPosition = window->position();
    window->setMaximumSize(window->screen()->geometry().size());

    window->setWindowState(Qt::WindowState::WindowMaximized);
    window->setFlags(Qt::WindowType::FramelessWindowHint);

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::CrossCursor));
}

void WindowManager::doMinimizeWindow() {
    window->setWindowState(Qt::WindowState::WindowNoState);
    window->setFlags(Qt::WindowType::Window);

    window->setMaximumSize(lastSize);
    window->setPosition(lastPosition);

    QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));
}

QImage WindowManager::doGrab() {

//    QApplication::clipboard()->setImage();
    window->grabWindow().save("asdsadas.jpeg");
    return window->grabWindow();
}
