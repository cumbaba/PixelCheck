#ifndef CONVERTER_H
#define CONVERTER_H

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

class Converter {

    public:
        static QImage cvMatToQImage(const cv::Mat& inMat);
        static QPixmap cvMatToQPixmap(const cv::Mat& inMat);

        // If inImage exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inImage's
        // data with the cv::Mat directly
        //    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
        //    NOTE: This does not cover all cases - it should be easy to add new ones as required.
        static cv::Mat QPixmapToCvMat(const QPixmap& inPixmap, bool inCloneImageData = true);

        // If inPixmap exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inPixmap's data
        // with the cv::Mat directly
        //    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
        static cv::Mat QImageToCvMat(const QImage& inImage, bool inCloneImageData = true);

        static cv::Size toCvSize(const QSize& size);

};

#endif // CONVERTER_H
