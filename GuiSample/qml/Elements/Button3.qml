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
    id: button3Id
    width: buttonText2.width + 30
    height: 28
    opacity: 0.7

    border { color: "white"; width: 1 }

    property string buttonText
    property color buttonHighlightColor: "#ff9800"

    signal buttonClicked();

    color: "transparent"


    Text{
        id: buttonText2
        text: buttonText
        anchors.verticalCenterOffset: -1
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.verticalCenter: parent.verticalCenter
        font.family: "Tahoma"
        font.bold: false
        font.pixelSize: 16
        font.weight: "Light"
        opacity: 0.7
        smooth: true

        color: "white"
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            button3Id.color = buttonHighlightColor;
            button3Id.opacity = 1;
            buttonText2.opacity = 1;
        }
        onExited: {
            button3Id.color = "transparent"
            button3Id.opacity = 0.7;
            buttonText2.opacity = 0.7;
        }
        onClicked: buttonClicked();
    }
}
