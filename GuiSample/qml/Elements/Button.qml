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
    id: buttonT1

    property color buttonColor: "#00000000"
    property color buttonColorHover: "#006600"

    signal buttonPressed();
    property string buttonText

    color: buttonColor
    border.color: "#fff"
    height: 27
    width: 70

    Image {
        id: buttonT1Img
        anchors {fill: parent; leftMargin: 1; topMargin: 1}
        sourceSize.height: 27
        source: "../images/button_bg.png"
    }

    Text {
        id: text1
        x: 24
        y: 7
        text: buttonText
        font.bold: false
        color: "#ffffff"
        font.family: fontTahoma.name
        font.weight: "Light"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 16
    }

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            buttonPressed();
        }

        onEntered: {
            buttonT1Img.source = ""
            buttonT1.color = buttonColorHover
        }
        onExited: {
            buttonT1Img.source = "../images/button_bg.png"
            buttonT1.color = buttonColor
        }
    }
}


/*
Rectangle {
    width: 70
    height: 28

    signal buttonPressed();

    color: "transparent"
    border { color: "#ffffff"; width: 1 }

    property string buttonText
    property Gradient buttonActiveGradient: Gradient{ GradientStop { position: 1; color: "#177e00" } GradientStop { position: 0; color: "#32b003" } }
    property Gradient nullGradient: Gradient {}

    Text {
        id: text1
        x: 24
        y: 7
        text: buttonText
        font.bold: true
        color: "#ffffff"
        font.family: fontTahoma.name
        font.weight: "Light"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 18
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onPressed: parent.gradient = buttonActiveGradient
        onReleased: { parent.gradient = nullGradient; buttonPressed() }
        onEntered: parent.color = "#177e00"
        onExited: parent.color = "transparent"
    }
}
*/
