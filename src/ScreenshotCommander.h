#ifndef SCREENSHOTCOMMANDER_H
#define SCREENSHOTCOMMANDER_H

#include <QObject>
#include <QQuickWindow>

#include "PropertyMacros.h"

class ScreenshotCommander : public QObject {
        Q_OBJECT

    public:
        explicit ScreenshotCommander(QObject* parent = nullptr);

        CHANGING_PROPERTY(bool, IsWaitingForInput)

    signals:
        void signalIsWaitingForInputChanged();

    public slots:

        void takeBase();
        void takeSample();
        void focusAreaReceived();

    private:
        QPixmap baseImage;
        QPixmap sampleImage;
        void take();

        bool isExpectingBase;
};

#endif // SCREENSHOTCOMMANDER_H
