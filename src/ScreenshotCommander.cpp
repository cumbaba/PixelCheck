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
        baseImage.save("base.jpg");
    }
    else {
        sampleImage = ScreenshotTaker::GetScreenshot();
        sampleImage.save("sample.jpg");
    }
}

void ScreenshotCommander::take() {
    ScreenshotTaker::TurnOn();
    setIsWaitingForInput(true);
}
