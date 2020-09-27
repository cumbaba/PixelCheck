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
            if (ScreenshotTaker.IsWaitingForInput) {
                indicator.visible = true
                indicator.x = mouse.x
                indicator.y = mouse.y
                point1 = Qt.point(mouse.x, mouse.y)
            }
        }

        Rectangle {
            id: indicator

            border.color: "red"
            border.width: 1
            color: "transparent"
        }

        onPoint2Changed: {
            indicator.width = point2.x - point1.x
            indicator.height = point2.y - point1.y
        }

        onMouseXChanged: {
            if (ScreenshotTaker.IsWaitingForInput && capturer.pressed) {
                point2 = Qt.point(mouse.x, mouse.y)
            }
        }

        onMouseYChanged: {
            if (ScreenshotTaker.IsWaitingForInput && capturer.pressed) {
                point2 = Qt.point(mouse.x, mouse.y)
            }
        }

        onReleased: {

            buttonMenu.visible = true

            if (ScreenshotTaker.IsWaitingForInput) {
                point2 = Qt.point(mouse.x, mouse.y)


                ScreenshotTaker.focusAreaReceived(point1, point2)
                indicator.visible = false
            }
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: "gray"
        opacity: 0.1
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

                        ScreenshotTaker.takeBase()
                    }

                    text: "Base image"
                }

                MainMenuButton {
                    id: sampleImageTaker

                    onClicked: {
                        buttonMenu.visible = false

                        ScreenshotTaker.takeSample()
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
