TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += src/main.cpp \
    src/MouseWatcher.cpp \
    src/ScreenshotCommander.cpp \
    src/ScreenshotTaker.cpp

HEADERS += \
    src/MouseWatcher.h \
    src/PropertyMacros.h \
    src/ScreenshotCommander.h \
    src/ScreenshotTaker.h

RESOURCES += src/qml.qrc \
            resources/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

