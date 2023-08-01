#ifndef MOUSEWATCHER_H
#define MOUSEWATCHER_H

#include <QObject>
#include <QMouseEvent>
#include <QPixmap>
#include <QTimer>

class MouseWatcher : public QObject {
        Q_OBJECT

    public:
        static MouseWatcher& instance();

        static void StartCursorImageWatch();
        static void StopCursorImageWatch();
        static void CaptureMouseClick();

        static QPixmap GetClickedArea();
        static QPoint GetMousePosition();
        static QPixmap GetLastTakenCursorImage();

        static void SetCursorImageHeight(const unsigned int aCursorImageHeight);
        static void SetCursorImageWidth(const unsigned int aCursorImageWidth);

    signals:
        void signalCursorImageUpdate(const QPixmap& image);
        void signalClickFinished();

    protected:
        virtual bool eventFilter(QObject* const object, QEvent* const event);

    private:
        MouseWatcher(QObject* const parent = nullptr);
        virtual ~MouseWatcher();

        void doWatchClick();
        QPixmap doGetClickedArea();

        void updateCursorImage();

        QPixmap lastTakenCursorImage;
        QPoint clickStart;
        QPoint clickEnd;
        QPoint lastCursorPosition;

        QTimer cursorImageMonitor;

        unsigned int cursorImageWidth;
        unsigned int cursorImageHeight;
        int screenNumber;

        bool isClickCaptureOn;
};

#endif // MOUSEWATCHER_H
