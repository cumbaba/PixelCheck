#include "ScreenshotCommander.h"

#include "ScreenshotTaker.h"

ScreenshotCommander::ScreenshotCommander(QObject* const parent) : QObject(parent),
    IsWaitingForInput(false),
    isExpectingBase(true) {
}

void ScreenshotCommander::takeBase() {
    isExpectingBase = true;
    take();
}

void ScreenshotCommander::takeSample() {
    isExpectingBase = false;
    take();
}

void ScreenshotCommander::focusAreaReceived() {
    setIsWaitingForInput(false);

    if (isExpectingBase) {
        baseImage = ScreenshotTaker::GetScreenshot();
    }
    else {
        sampleImage = ScreenshotTaker::GetScreenshot();
    }
}

void ScreenshotCommander::take() {
    ScreenshotTaker::TurnOn();
    setIsWaitingForInput(true);
}
