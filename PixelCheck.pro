TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += src/main.cpp \
    src/MouseWatcher.cpp \
    src/ScreenshotCommander.cpp \
    src/ScreenshotTaker.cpp \
    src/Magnifier.cpp \
    src/ImageComparison.cpp

HEADERS += \
    src/MouseWatcher.h \
    src/PropertyMacros.h \
    src/ScreenshotCommander.h \
    src/ScreenshotTaker.h \
    src/Magnifier.h \
    src/ImageComparison.h

RESOURCES += src/qml.qrc \
            resources/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += $$PWD/lib/opencv/include

LIBS += $$PWD/lib/opencv/bin/libopencv_core440.dll
LIBS += $$PWD/lib/opencv/bin/libopencv_highgui440.dll
LIBS += $$PWD/lib/opencv/bin/libopencv_imgcodecs440.dll
LIBS += $$PWD/lib/opencv/bin/libopencv_imgproc440.dll
LIBS += $$PWD/lib/opencv/bin/libopencv_features2d440.dll
LIBS += $$PWD/lib/opencv/bin/libopencv_calib3d440.dll
