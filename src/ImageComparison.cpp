#include "ImageComparison.h"

#include "ScreenshotTaker.h"

ImageComparison::ImageComparison(QObject* const parent) : QObject(parent) {
}

ImageComparison::~ImageComparison() {

}

ImageComparison& ImageComparison::instance() {
    static ImageComparison _instance;
    return _instance;
}

void ImageComparison::setBaseImage(const QPixmap& image) {
    instance().baseImage = image;
    instance().updateIsComparable();
}

void ImageComparison::setSampleImage(const QPixmap& image) {
    instance().sampleImage = image;
    instance().updateIsComparable();

}
void ImageComparison::updateIsComparable() {
    bool ok1 = false;
    bool ok2 = false;

    int minHeight = this->ApplicationHeight.toInt(&ok1);
    int minWidth = this->ApplicationWidth.toInt(&ok2);

    setIsComparable(ok1 && ok2 && minHeight > 0 && minWidth > 0
                    && minHeight < baseImage.height() && minHeight < sampleImage.height()
                    && minWidth < baseImage.width() && minWidth < sampleImage.width());
}
