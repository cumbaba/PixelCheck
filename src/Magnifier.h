#ifndef MAGNIFIER_H
#define MAGNIFIER_H

#include <QObject>

#include <QMainWindow>
class Magnifier : public QObject {
        Q_OBJECT
    public:
        static Magnifier& instance();

    public slots:
        void turnOn();
        void turnOff();

    private:
        Magnifier(QObject* const parent = nullptr);
        virtual ~Magnifier();

        void onCursorImageReceived(const QPixmap& image);
        void coverCenterPixel(QPixmap* image);

        bool isOn;
        QPixmap getMagnifiedImage();
        QMainWindow* window;
};

#endif // MAGNIFIER_H
