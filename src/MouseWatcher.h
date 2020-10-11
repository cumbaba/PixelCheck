#ifndef MOUSEWATCHER_H
#define MOUSEWATCHER_H

#include <QObject>
#include <QMouseEvent>

class MouseWatcher : public QObject {
        Q_OBJECT

    public:
        MouseWatcher(QObject* const parent = nullptr);
        ~MouseWatcher();

        int getScreenNumber()const;
        bool isWatching()const;

        void watchClick();
        QPixmap getClickedArea();

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
