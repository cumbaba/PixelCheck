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
    src/utils/WinUtils.cpp \
    src/utils/TextDetector.cpp

HEADERS += \
    src/ImageComparisonService.h \
    src/ScreenshotCommander.h \
    src/ScreenshotTaker.h \
    src/tools/Magnifier.h \
    src/tools/MouseWatcher.h \
    src/utils/ImageUtils.h \
    src/utils/Converter.h \
    src/utils/WinUtils.h \
    src/utils/TextDetector.h
    src/utils/PropertyMacros.h \

RESOURCES += src/qml.qrc \
            resources/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


# opencv
INCLUDEPATH += $$PWD/lib/opencv/include
DEPENDPATH += $$PWD/lib/opencv/include

LIBS += -L$$PWD/lib/opencv/bin/ -lopencv_core440 \
                                -lopencv_highgui440 \
                                -lopencv_imgcodecs440 \
                                -lopencv_imgproc440 \
                                -lopencv_features2d440 \
                                -lopencv_calib3d440

LIBS += -lKernel32

# tesseract
INCLUDEPATH += $$PWD/lib/tesseract/include
DEPENDPATH += $$PWD/lib/tesseract/include

LIBS += -L$$PWD/lib/tesseract/bin/ -lQt5.4tesseract3.02.02


