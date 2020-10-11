#ifndef IMAGECOMPARISON_H
#define IMAGECOMPARISON_H

#include <QObject>
#include <QPixmap>
#include <QString>

#include "PropertyMacros.h"

class ImageComparison : public QObject {
        Q_OBJECT

    public:
        static ImageComparison& instance();

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
        ImageComparison(QObject* const parent = nullptr);
        virtual ~ImageComparison();
        QPixmap baseImage;
        QPixmap sampleImage;

};

#endif // IMAGECOMPARISON_H
