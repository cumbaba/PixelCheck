#ifndef TEXTDETECTOR_H
#define TEXTDETECTOR_H

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

class TextDetector {

    public:
        static void detectTexts(const cv::Mat& in);

};

#endif // TEXTDETECTOR_H
