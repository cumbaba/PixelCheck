#include "ImageComparisonService.h"

#include "ScreenshotTaker.h"
#include "utils/ImageUtils.h"

ImageComparisonService::ImageComparisonService(QObject* const parent) : QObject(parent) {
    connect(this, &ImageComparisonService::signalApplicationHeightChanged, this, [this] {this->updateIsComparable();});
    connect(this, &ImageComparisonService::signalApplicationWidthChanged, this, [this] {this->updateIsComparable();});
}

ImageComparisonService::~ImageComparisonService() {
    this->disconnect();
}

ImageComparisonService& ImageComparisonService::instance() {
    static ImageComparisonService _instance;
    return _instance;
}

void ImageComparisonService::setBaseImage(const QPixmap& image) {
    instance().baseImage = image;
    instance().updateIsComparable();
}

void ImageComparisonService::setSampleImage(const QPixmap& image) {
    instance().sampleImage = image;
    instance().updateIsComparable();

}
void ImageComparisonService::updateIsComparable() {
    bool ok1 = false;
    bool ok2 = false;

    int minHeight = this->ApplicationHeight.toInt(&ok1);
    int minWidth = this->ApplicationWidth.toInt(&ok2);

    setIsComparable(ok1 && ok2 && minHeight > 0 && minWidth > 0
                    /*&& minHeight < baseImage.height() && minHeight < sampleImage.height()
                    && minWidth < baseImage.width() && minWidth < sampleImage.width()*/);

    if (IsComparable) {
        contentSize = QSize(minWidth, minHeight);
    }
}

void ImageComparisonService::compare() {
    resultImage = ImageUtils::compare(baseImage, sampleImage, contentSize);
}
