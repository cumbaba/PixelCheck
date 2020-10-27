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
        static cv::Point findContentPosition(const cv::Mat& image, const cv::Size& size);
        static cv::Mat applyCannyEdge(const cv::Mat& image);

        static bool tryRectengale(const cv::Mat& image, const cv::Point& startPoint, const cv::Size& size);

        static std::pair<QList<int>, QList<int>> detectLines(const cv::Mat& s);
};

#endif // IMAGEUTILS_H
