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
        static QPixmap compare(const QPixmap& base, const QPixmap& sample);

};

#endif // IMAGEUTILS_H
