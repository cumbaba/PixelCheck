import QtQuick 2.0

Rectangle {
    property point point1
    property point point2

    color: "transparent"

    Rectangle {
        id: chosenRect
        color: parent.color

        x: point1.x
        y: point1.y
        width: point2.x - point1.x
        height: point2.y - point1.y

        // TODO make it a special color
        border.color: "red"
        border.width: 1
    }

    Rectangle {
        id: topGreyArea
        anchors {
            top: parent.top
            left: parent.left
        }
        height: point1.y
        width: parent.width

        color: "gray"
        opacity: 0.1
    }

    Rectangle {
        id: leftGreyArea
        anchors {
            top: topGreyArea.bottom
            left: parent.left
        }

        height: point2.y - point1.y
        width: point1.x

        color: "gray"
        opacity: 0.1
    }

    Rectangle {
        anchors {
            top: leftGreyArea.bottom
            right: rightGreyArea.left
        }

        height: parent.height - point2.y
        width: point2.x

        color: "gray"
        opacity: 0.1
    }

    Rectangle {
        id: rightGreyArea
        anchors {
            top: topGreyArea.bottom
            right: parent.right
        }

        height: parent.height
        width: parent.width - point2.x

        color: "gray"
        opacity: 0.1
    }

    function reset() {
        point1 = Qt.point(0,0)
        point2 = Qt.point(0,0)
    }
}
