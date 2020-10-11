#ifndef SCREENSHOTTAKER_H
#define SCREENSHOTTAKER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QQuickWindow>

class ScreenshotTaker : public QObject {
        Q_OBJECT
    public:
        static ScreenshotTaker& instance();
        static void TurnOn();
        static void SetWindow(QQuickWindow* aWindow);
        static QPixmap GetScreenshot();

    private:
        ScreenshotTaker(QObject* const parent = nullptr);
        virtual ~ScreenshotTaker();

        void doSetWindow(QQuickWindow* aWindow);
        void doTurnOn();

        void onStart();
        void onFinish();
        QPixmap lastTakenShot;

        QSize lastSize;
        QPoint lastPosition;

        QQuickWindow* window;
};

#endif // SCREENSHOTTAKER_H
