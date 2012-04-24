import QtQuick 1.0
import qGNA.Library 1.0

Rectangle{
    color: "transparent"

    property variant flickable
    property bool vertical: true
    property bool hideScrollBarsWhenStopped: true
    property int scrollbarWidth: 19

    width: vertical ? scrollbarWidth : parent.width
    height: vertical ? parent.height : scrollbarWidth
    x: vertical ? parent.width - width : 0
    y: vertical ? 0 : parent.height - height

    clip: true;

    Rectangle{
        anchors.fill: parent
        color: "white"
        opacity: 0.2
        clip: true
    }

    Rectangle{
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        height: scrollbarWidth
        color: "transparent"

        Image{
            id: upArrowId
            source: "../images/upArrowWhite.png"
            anchors.top: parent.top
            anchors.topMargin: 7
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.5
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: upArrowId.opacity = 1
            onExited: upArrowId.opacity = 0.5
            onClicked: if (navigationRectangle.visible) flickable.contentY = flickable.contentY - 5;
        }
        CursorShapeArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
        }
    }


    Rectangle{
        id: downArrowId
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        height: scrollbarWidth
        color: "transparent"
        opacity: 0.5

        Image{
            source: "../images/downArrowWhite.png"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 7
            anchors.horizontalCenter: parent.horizontalCenter
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: downArrowId.opacity = 1
            onExited: downArrowId.opacity = 0.5
            onClicked: if (navigationRectangle.visible) flickable.contentY = flickable.contentY + 5;
        }
        CursorShapeArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
        }
    }

    Rectangle{
        anchors.fill: parent
        anchors.bottom: parent.bottom
        anchors.bottomMargin: scrollbarWidth
        anchors.top: parent.top
        anchors.topMargin: scrollbarWidth
        color: "transparent"
        clip: true

        Rectangle {
            id: navigationRectangle
            visible: false
            color: "white"
            opacity: 0.3

            width: vertical ? scrollbarWidth : flickable.visibleArea.widthRatio * parent.width
            height: vertical ? flickable.visibleArea.heightRatio * parent.height : scrollbarWidth

            x: vertical ? parent.width - width : flickable.visibleArea.xPosition * parent.width
            y: vertical ? flickable.visibleArea.yPosition * parent.height : parent.height - height


            Behavior on opacity { NumberAnimation { duration: 200 }}
        }
    }



}

