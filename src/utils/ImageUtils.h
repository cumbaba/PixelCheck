#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

class ImageUtils {

    public:
        static QPixmap compare(const QPixmap& base, const QPixmap& sample, const QSize& contentSize);


    private:

        // toleranceInPixels: Checks the pixels arround in case the pixel didn't match
        static bool checkPixel(const cv::Mat& base, const cv::Mat& sample, const cv::Point& basePoint,
                               const int toleranceInPixels = 3);

        static bool comparePixels(const cv::Mat& base, const cv::Mat& sample, const cv::Point& basePoint,
                                  const cv::Point& samplePoint,
                                  const int colorComparisonTolerance = 10);

        // colorComparisonTolerance: max total delta for rgb
        static bool comparePixels(const cv::Mat& base, const cv::Mat& sample, const cv::Point& basePoint,
                                  const int colorComparisonTolerance = 10);

        static cv::Point findContentPosition(const cv::Mat& image, const cv::Size& size);

        static cv::Mat applyCannyEdge(const cv::Mat& image_gray);

        static std::pair<QList<int>, QList<int>> detectLines(const cv::Mat& image);

        static void markPixel(cv::Mat& image, const cv::Point& markPoint);
};

#endif // IMAGEUTILS_H
