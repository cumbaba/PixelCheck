#ifndef IMAGECOMPARISONSERVICE_H
#define IMAGECOMPARISONSERVICE_H

#include <QObject>
#include <QPixmap>
#include <QString>

#include "utils/PropertyMacros.h"

class ImageComparisonService : public QObject {
        Q_OBJECT

    public:
        static ImageComparisonService& instance();

        static void setBaseImage(const QPixmap& image);
        static void setSampleImage(const QPixmap& image);

        CHANGING_PROPERTY(bool, IsComparable)
        CHANGING_PROPERTY(QString, ApplicationHeight)
        CHANGING_PROPERTY(QString, ApplicationWidth)

    signals:
        void signalIsComparableChanged();
        void signalApplicationHeightChanged();
        void signalApplicationWidthChanged();
        void signalBaseImageChanged();
        void signalSampleImageChanged();

    public slots:
        void updateIsComparable();
        void compare();
    private:
        ImageComparisonService(QObject* const parent = nullptr);
        virtual ~ImageComparisonService();
        QPixmap baseImage;
        QPixmap sampleImage;

};

#endif // IMAGECOMPARISONSERVICE_H
