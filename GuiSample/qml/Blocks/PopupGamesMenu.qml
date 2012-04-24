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
import "../Delegates" as Delegates
import "../Models" as Models

Item{
    id: downPopupMenu

    signal homeClicked();

    Rectangle{
        height: 1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "white"
        opacity: 0.15
    }

    Rectangle{
        color: "black"
        anchors.topMargin: 1
        anchors.fill: parent
        opacity: 0.20
    }

    Image{
        id: hoveImage
        anchors.left: parent.left
        anchors.leftMargin: 36
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 22
        source: "../images/homeIcon.png"
        opacity: 0.5

        NumberAnimation { id: hoveImagehoverOpacityUp; easing.type: Easing.OutQuad; target: hoveImage; property: "opacity"; from: 0.5; to: 0.8; duration: 150 }
        NumberAnimation { id: hoveImagehoverOpacityDown; easing.type: Easing.OutQuad; target: hoveImage; property: "opacity"; from: 0.8; to: 0.5; duration: 150 }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: hoveImagehoverOpacityUp.start();
            onExited: hoveImagehoverOpacityDown.start();
            onClicked: homeClicked();
        }

        CursorShapeArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
        }
    }

    Rectangle{
        height: 1
        anchors.left: parent.left
        anchors.leftMargin: 59
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 26
        color: "#ffffff"
        anchors.right: parent.right
        anchors.rightMargin: 142
        opacity: 0.5
    }

    Text{
        id: gamenetLink
        text: "www.gamenet.ru"
        font.underline: true
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 21
        font.family: "Tahoma"
        font.bold: false
        font.pixelSize: 12
        font.weight: "Light"
        color: "#ffffff"
        opacity: 0.5
        smooth: true

        NumberAnimation { id: gamenetLinkhoverOpacityUp; easing.type: Easing.OutQuad; target: gamenetLink; property: "opacity"; from: 0.5; to: 0.8; duration: 150 }
        NumberAnimation { id: gamenetLinkhoverOpacityDown; easing.type: Easing.OutQuad; target: gamenetLink; property: "opacity"; from: 0.8; to: 0.5; duration: 150 }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: gamenetLinkhoverOpacityUp.start();
            onExited: gamenetLinkhoverOpacityDown.start();
            onClicked: mainWindow.openExternalBrowser("http://www.gamenet.ru/");
        }

        CursorShapeArea {
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
        }
    }

}
