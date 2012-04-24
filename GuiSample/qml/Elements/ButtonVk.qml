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
    id: buttonVk

    property color buttonColor: "#00000000"
    property color buttonColorHover: "#006600"
    property string buttonText: qsTr("Enter Vkontakte") + mainWindow.emptyString

    signal buttonPressed();

    width: 165
    height: 27
    color: buttonColor
    border.color: "#fff"

    Image {
        width: 22
        height: 22
        anchors {left: parent.left; leftMargin: 3; top: parent.top; topMargin: 3}
        source: "../images/button_vk.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        width: 0
        height: 0
        text: buttonText
        anchors {fill: parent; leftMargin: 29}
        verticalAlignment: Text.AlignVCenter
        color: "#fff"
        font.pixelSize: 16
    }

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            buttonVk.color = buttonColorHover
        }
        onExited: {
            buttonVk.color = buttonColor
        }

        onClicked: {
            buttonPressed();
        }
    }
}
