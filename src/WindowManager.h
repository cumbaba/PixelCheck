#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QQuickWindow>

class WindowManager {
    public:
        static WindowManager& instance();

        static void setWindow(QQuickWindow* aWindow) {
            instance().doSetWindow(aWindow);
        }
        static void maximizeWindow() {
            instance().doMaximizeWindow();
        }
        static void minimizeWindow() {
            instance().doMinimizeWindow();
        }
        static void grab() {
            instance().doGrab();
        }


    private:
        WindowManager() {}

        void doSetWindow(QQuickWindow* aWindow);
        void doMaximizeWindow();
        void doMinimizeWindow();
        QImage doGrab();

        QSize lastSize;
        QPoint lastPosition;
        QQuickWindow* window;
};

#endif // WINDOWMANAGER_H
