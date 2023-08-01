#ifndef MAGNIFIER_H
#define MAGNIFIER_H

#include <QObject>

#include <QMainWindow>
#include <QQuickWindow>

class Magnifier : public QObject {
        Q_OBJECT
    public:
        static Magnifier& instance();

    public slots:
        void close(QQuickCloseEvent *close);
        void turnOn();
        void turnOff();
        QUrl getMouseimage();

    private:
        Magnifier(QObject* const parent = nullptr);
        virtual ~Magnifier();

        void onCursorImageReceived(const QPixmap& image);
        void coverCenterPixel(QPixmap* image);

        QPixmap last_image;
        bool isOn;
        QMainWindow* window;
};

#endif // MAGNIFIER_H
