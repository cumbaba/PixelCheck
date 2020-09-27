#include "ScreenshotTaker.h"

#include <QGuiApplication>
#include <QCursor>
#include <QScreen>
#include <QThread>

#include "WindowManager.h"

#include <stdio.h>
#include <iostream>

ScreenshotTaker::ScreenshotTaker(QObject* parent):
    QObject(parent),
    IsWaitingForInput(false),
    isExpectingBase(true) {
}

void ScreenshotTaker::takeBase() {
    std::cout << "aha" << std::endl;
    isExpectingBase = true;
    take();
}

void ScreenshotTaker::takeSample() {
    std::cout << "baha" << std::endl;
    isExpectingBase = false;
    take();
}

void ScreenshotTaker::focusAreaReceived(const QPoint& point1, const QPoint& point2) {
    setIsWaitingForInput(false);
    WindowManager::minimizeWindow();

    std::cout << "[p1] x: " << point1.x() << " y: " << point1.y() << " [p2] x: " << point2.x() << " y: " << point2.y() <<
              std::endl;
    WindowManager::grab();
}


void ScreenshotTaker::take() {
    setIsWaitingForInput(true);
    WindowManager::maximizeWindow();
}
