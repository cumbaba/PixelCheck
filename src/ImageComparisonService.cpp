#include "ImageComparisonService.h"

#include "ScreenshotTaker.h"

#include <opencv2/core/core.hpp>
#include <opencv2//highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

ImageComparisonService::ImageComparisonService(QObject* const parent) : QObject(parent) {
}

ImageComparisonService::~ImageComparisonService() {}

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
                    && minHeight < baseImage.height() && minHeight < sampleImage.height()
                    && minWidth < baseImage.width() && minWidth < sampleImage.width());
}

void ImageComparisonService::compare() {
    // read an image
    cv::Mat image = cv::imread("C:/Users/User/Cumhur-Private-Projects/PixelCheck/aha.jpg", 1);
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", image);

}
