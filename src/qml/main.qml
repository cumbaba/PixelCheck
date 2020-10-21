import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4

Window {
    id: mainWindow
    visible: true
    width: 300
    height: 240

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
            if (ScreenshotCommander.IsWaitingForInput) {
                point2 = Qt.point(mouse.x, mouse.y)
                ScreenshotCommander.focusAreaReceived()
            }

            buttonMenu.visible = true
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

        implicitWidth: mainWindow.width
        implicitHeight: mainWindow.height
        anchors.centerIn: parent
        color: "gray"

        Column {
            id: column
            width: 250
            height: 180
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 20
            }

            spacing: 10

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

            Row {

                spacing: 40
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                Label {
                    text: "Width:"
                    width: 40
                    font.pixelSize: 15
                }

                TextField {
                    id: width

                    height: 20
                    width: 100
                    font.pixelSize: 15

                    anchors.verticalCenter: heightLabel.verticalCenter
                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            color: "white"
                        }
                    }

                    onTextChanged: {
                        ImageComparisonService.ApplicationWidth = text;
                        ImageComparisonService.updateIsComparable()
                    }
                }
            }

            Row {

                spacing: 40
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                Label {
                    id: heightLabel
                    text: "Height:"
                    width: 40
                    font.pixelSize: 15
                }

                TextField {
                    id: height

                    height: 20
                    width: 100
                    font.pixelSize: 15

                    anchors.verticalCenter: heightLabel.verticalCenter
                    style: TextFieldStyle {
                        textColor: "black"
                        background: Rectangle {
                            color: "white"
                        }
                    }

                    onTextChanged: {
                        ImageComparisonService.ApplicationHeight = text;
                        ImageComparisonService.updateIsComparable()
                    }
                }
            }

            MainMenuButton {
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                enabled: ImageComparisonService.IsComparable
                text: "Compare"

                onClicked: {
                    ImageComparisonService.compare()
                }
            }

            CheckBox {
                width: 50
                height: 50
                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                onCheckedChanged: {
                    if (checked) {
                        Magnifier.turnOn()
                    } else {
                        Magnifier.turnOff()
                    }
                }
                text: "Magnifier"

                Component.onCompleted: {
//                    checked = true
                }
            }
        }
    }
}
