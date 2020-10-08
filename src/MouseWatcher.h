#ifndef MOUSEWATCHER_H
#define MOUSEWATCHER_H

#include <QObject>
#include <QMouseEvent>

class MouseWatcher : public QObject {
        Q_OBJECT

    public:
        MouseWatcher() {}
        ~MouseWatcher() {}

        void watchClick();
        int getScreenNumber();

        QRect getClickedArea();
        bool isWatching()const;
    signals:
        void signalClickFinished();

    protected:
        virtual bool eventFilter(QObject* const object, QEvent* const event);

    private:
        QPoint getMousePosition();
        QPoint start;
        QPoint end;
        int screenNumber;
        bool isOn;
};

#endif // MOUSEWATCHER_H
