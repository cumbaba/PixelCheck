TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += src/main.cpp \
    src/ImageComparisonService.cpp \
    src/ScreenshotCommander.cpp \
    src/ScreenshotTaker.cpp \
    src/tools/Magnifier.cpp \
    src/tools/MouseWatcher.cpp \
    src/utils/ImageUtils.cpp \
    src/utils/Converter.cpp \
    src/utils/WinUtils.cpp

HEADERS += \
    src/ImageComparisonService.h \
    src/ScreenshotCommander.h \
    src/ScreenshotTaker.h \
    src/tools/Magnifier.h \
    src/tools/MouseWatcher.h \
    src/utils/ImageUtils.h \
    src/utils/Converter.h \
    src/utils/WinUtils.h
    src/utils/PropertyMacros.h \

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

LIBS += -lKernel32
