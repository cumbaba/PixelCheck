TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += src/main.cpp \
    src/ScreenshotTaker.cpp \
    src/WindowManager.cpp

HEADERS += \
    src/ScreenshotTaker.h \
    src/PropertyMacros.h \
    src/WindowManager.h

RESOURCES += src/qml.qrc \
            resources/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

