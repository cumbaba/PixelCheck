#include "ScreenshotCommander.h"

#include "ScreenshotTaker.h"
#include "ImageComparisonService.h"

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
        ImageComparisonService::setBaseImage(baseImage);
    }
    else {
        sampleImage = ScreenshotTaker::GetScreenshot();
        ImageComparisonService::setSampleImage(sampleImage);
    }
}

void ScreenshotCommander::take() {
    ScreenshotTaker::TurnOn();
    setIsWaitingForInput(true);
}
