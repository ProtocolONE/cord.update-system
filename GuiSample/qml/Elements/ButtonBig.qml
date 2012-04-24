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

Rectangle {
    id: bigButtonRectangle
    width: 155
    height: 55

    property int progressPercent: -1
    property bool allreadyDownloaded: false
    property bool isMouseAreaAccepted: true
    signal buttonPressed();

    color: "transparent"
    gradient: progressPercent < 0 ? buttonNormalReverseGradient : nullGradient;
    border { color: "#ffffff"; width: 1 }

    property string buttonText
    property string buttonDownloadedText

    property Gradient buttonActiveGradient: Gradient{ GradientStop { position: 1; color: "#177e00" } GradientStop { position: 0; color: "#32b003" } }
    property Gradient buttonNormalGradient: Gradient{ GradientStop { position: 1; color: "#4db523" } GradientStop { position: 0; color: "#237c00" } }
    property Gradient buttonNormalReverseGradient: Gradient{ GradientStop { position: 0; color: "#4db523" } GradientStop { position: 1; color: "#237c00" } }
    property Gradient nullGradient: Gradient {}

    NumberAnimation { id: demoAnimation;
        target: bigButtonRectangle;
        property: "progressPercent";
        from: 0; to: 100;
        duration: 10000;

        onCompleted: {
            gradient = buttonNormalReverseGradient;
            bigButtonMouseArea.visible = true;
            allreadyDownloaded = true;
        }

    }

    Rectangle{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 1

        color: "#000000"
        opacity: 0.6
        visible: progressPercent >= 0 && progressPercent < 100
    }

    Rectangle{
        visible: progressPercent >= 0 && progressPercent < 100
        color: "#cba80d"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        width: ((parent.width - 1) / 100) * progressPercent
    }

    Text {
        id: buttonTextId
        x: 24
        y: 7
        text: allreadyDownloaded ? buttonDownloadedText : buttonText
        font.bold: false
        color: "#ffffff"
        font.family: fontTahoma.name
        font.weight: "Light"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 28
    }

    MouseArea{
        id: bigButtonMouseArea
        visible: isMouseAreaAccepted
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            parent.gradient = nullGradient;
            bigButtonMouseArea.visible = false;
            demoAnimation.start();
        }
        onReleased: { exited(); buttonPressed() }
        onEntered: parent.gradient = buttonNormalGradient;
        onExited: parent.gradient = buttonNormalReverseGradient;
    }
}
