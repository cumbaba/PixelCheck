import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.0

Window {
    id: mainWindow
    visible: true
    width: 300
    height: 200

    color: "transparent"
    MouseArea {
        id: capturer
        anchors.fill: parent

        property point point1
        property point point2

        onPressed: {
            if (ScreenshotCommander.IsWaitingForInput) {
                point1 = Qt.point(mouse.x, mouse.y)
            }
        }

        onMouseXChanged: {
            if (ScreenshotCommander.IsWaitingForInput && capturer.pressed) {
                point2 = Qt.point(mouse.x, mouse.y)
            }
        }

        onMouseYChanged: {
            if (ScreenshotCommander.IsWaitingForInput && capturer.pressed) {
                point2 = Qt.point(mouse.x, mouse.y)
            }
        }

        onReleased: {
            buttonMenu.visible = true

            if (ScreenshotCommander.IsWaitingForInput) {
                point2 = Qt.point(mouse.x, mouse.y)
                ScreenshotCommander.focusAreaReceived()
            }
        }

        onPoint1Changed: {
            ssScreen.point1 = capturer.point1
        }
        onPoint2Changed: {
            ssScreen.point2 = capturer.point2
        }
    }

    ScreenshotScreen {
        id: ssScreen
        anchors.fill: parent
    }

    Rectangle {
        id: buttonMenu

        implicitWidth: 300
        implicitHeight: 200
        anchors.centerIn: parent
        color: "gray"

        Column {
            id: column
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 20
            }

            spacing: 30

            Row {
                id: imageRow
                spacing: 50

                anchors {
                    horizontalCenter: parent.horizontalCenter
                }
                MainMenuButton {
                    id: baseImageTaker

                    onClicked: {
                        buttonMenu.visible = false

                        ssScreen.reset()
                        ScreenshotCommander.takeBase()
                    }

                    text: "Base image"
                }

                MainMenuButton {
                    id: sampleImageTaker

                    onClicked: {
                        buttonMenu.visible = false

                        ssScreen.reset()
                        ScreenshotCommander.takeSample()
                    }
                    text: "Sample image"
                }
            }

            MainMenuButton {
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                onClicked: {

                }

                text: "Compare"
            }
        }
    }
}
