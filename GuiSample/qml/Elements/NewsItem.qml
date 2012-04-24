/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

import QtQuick 1.0
import qGNA.Library 1.0

Rectangle {
    color: "transparent"

    property string newsTextDate
    property string newsTextBody

    clip: true

    Text{
        text: newsTextDate

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 2
        color: "#ffffff"
        wrapMode: Text.WordWrap
  //      textFormat: Text.RichText
        font.pointSize: 8
        opacity: 0.7

 //       onLinkActivated: console.log(link + " link activated")
    }

    Text{
        text: newsTextBody

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "#ffffff"
        wrapMode: Text.WordWrap
  //      textFormat: Text.RichText
        font.pointSize: 10

 //       onLinkActivated: console.log(link + " link activated")
    }

    Rectangle{
        id: commentsRectangle
        height: 13
        width: 20

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        color: "transparent"

        Rectangle{
            anchors.fill: parent
            anchors.bottomMargin: 2
            opacity: 0.5
            color: "white"
        }
        Rectangle{
            width: 1
            height: 1
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            opacity: 0.5
            color: "white"
        }
        Rectangle{
            width: 3
            height: 1
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            opacity: 0.5
            color: "white"
        }
        Text{
            anchors.left: parent.left
            anchors.leftMargin: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 2
            text: "123"
            font.pointSize: 7
            font.family: "Arial"
            color: "#000033"
            opacity: 1
            smooth: true
        }
    }

    Text{
        id: plusOneText
        anchors.left: parent.left
        anchors.leftMargin: 5 + commentsRectangle.width + 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        text: "+1"
        font.pointSize: 8
        font.family: "Arial"
        color: "#c1d4ff"
        opacity: 0.75
        smooth: true

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: plusOneText.opacity = 1
            onExited: plusOneText.opacity = 0.75

        }
        CursorShapeArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
        }
    }

}
