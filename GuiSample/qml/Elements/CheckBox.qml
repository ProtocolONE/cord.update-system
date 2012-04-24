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
    id: mainCheckBoxId
    width: 30 + checkBoxTextId.width
    height: 20
    state: "Active"
    color: "transparent"

    property string buttonText
    property bool isChecked: state == "Active";

    signal checked();
    signal unchecked();

    Rectangle{
        id: checkBoxId
        width: 20
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        color: "white"
        opacity: 0.85

        Image{
            id: checkedImageId
            anchors.centerIn: parent
            source: "../images/checkImage.png"
        }
    }

    Text{
        id: checkBoxTextId
        text: buttonText
        style: Text.Normal
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Segoe UI Semibold"
        font.bold: false
        font.pixelSize: 14
        font.weight: "Normal"
        opacity: 0.85
        smooth: true
        color: "white"
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            checkBoxId.opacity = 0.95;
            checkBoxTextId.opacity = 0.95;
        }
        onExited: {
            checkBoxId.opacity = 0.85;
            checkBoxTextId.opacity = 0.85;
        }
        onClicked: {
            if (mainCheckBoxId.state == "Normal"){
                mainCheckBoxId.state = "Checked";
                checked();
            }
            else{
                mainCheckBoxId.state = "Normal";
                unchecked();
            }
        }
    }

    states: [
        State {
            name: "Normal"
            PropertyChanges { target: checkedImageId; visible: false }
            PropertyChanges { target: mainCheckBoxId; isChecked: false }
        },
        State {
            name: "Checked"
            PropertyChanges { target: checkedImageId; visible: true }
            PropertyChanges { target: mainCheckBoxId; isChecked: true }
        }
    ]

}
