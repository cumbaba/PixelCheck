#include "ImageUtils.h"

#include "Converter.h"

QPixmap ImageUtils::compare(const QPixmap& base, const QPixmap& sample) {
    auto baseMat = Converter::QPixmapToCvMat(base);
    auto sampleMat = Converter::QPixmapToCvMat(sample);

}
