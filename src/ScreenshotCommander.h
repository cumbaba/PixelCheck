#ifndef SCREENSHOTCOMMANDER_H
#define SCREENSHOTCOMMANDER_H

#include <QObject>
#include <QPixmap>

#include "PropertyMacros.h"

class ScreenshotCommander : public QObject {
        Q_OBJECT

    public:
        explicit ScreenshotCommander(QObject* const parent = nullptr);

        CHANGING_PROPERTY(bool, IsWaitingForInput)

    signals:
        void signalIsWaitingForInputChanged();

    public slots:

        void takeBase();
        void takeSample();
        void focusAreaReceived();

    private:
        void take();

        QPixmap baseImage;
        QPixmap sampleImage;
        bool isExpectingBase;
};

#endif // SCREENSHOTCOMMANDER_H
