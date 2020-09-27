#ifndef SCREENSHOTTAKER_H
#define SCREENSHOTTAKER_H

#include <QObject>

#include <QQuickWindow>
#include "PropertyMacros.h"

class ScreenshotTaker : public QObject {
        Q_OBJECT

    public:
        explicit ScreenshotTaker(QObject* parent = nullptr);

        CHANGING_PROPERTY(bool, IsWaitingForInput)

    signals:
        void signalIsWaitingForInputChanged();

    public slots:

        void takeBase();
        void takeSample();
        void focusAreaReceived(const QPoint &point1, const QPoint &point2);

    private:
        void take();

        bool isExpectingBase;
};

#endif // SCREENSHOTTAKER_H
