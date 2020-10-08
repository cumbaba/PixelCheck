#include "ScreenshotCommander.h"

#include <QGuiApplication>
#include <QCursor>
#include <QScreen>
#include <QThread>

#include <stdio.h>
#include <iostream>


#include "ScreenshotTaker.h"
ScreenshotCommander::ScreenshotCommander(QObject* parent):
    QObject(parent),
    IsWaitingForInput(false),
    isExpectingBase(true) {
}

void ScreenshotCommander::takeBase() {
    std::cout << "aha" << std::endl;
    isExpectingBase = true;
    take();
}

void ScreenshotCommander::takeSample() {
    std::cout << "baha" << std::endl;
    isExpectingBase = false;
    take();
}

void ScreenshotCommander::focusAreaReceived() {
    setIsWaitingForInput(false);
}

void ScreenshotCommander::take() {
    ScreenshotTaker::TurnOn();
    setIsWaitingForInput(true);
}
