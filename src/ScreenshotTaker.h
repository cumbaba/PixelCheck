#ifndef SCREENSHOTTAKER_H
#define SCREENSHOTTAKER_H

#include <QPoint>
#include <QPixmap>
#include <QCursor>
#include <QQuickWindow>

#include "MouseWatcher.h"

class ScreenshotTaker {
    public:
        static ScreenshotTaker& instance();
        static void TurnOn();
        static void SetWindow(QQuickWindow* aWindow);

    private:
        ScreenshotTaker();
        ~ScreenshotTaker() {}
        void doSetWindow(QQuickWindow* aWindow);
        void doTurnOn();

        void onStart();
        void onFinish();
        QPoint getMousePosition();

        QPixmap lastTakenShot;

        QQuickWindow* window;

        MouseWatcher mouseWatcher;
};

#endif // SCREENSHOTTAKER_H
