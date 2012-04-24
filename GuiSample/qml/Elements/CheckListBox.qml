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
    id: checkListBoxId
    height: 30

    color: "transparent"

    property string buttonText;
    property string textWidth: mainClickText.width
    property string buttonCheckListBoxText;
    property int checkListBoxX
    property int checkListBoxWidth
    property bool checkBoxType; // false - textEdit, true - dropListBox

    property bool isListActive: checkListBoxRectangle.height != checkListBoxId.height

    property ListModel listModel;
    property Component componentDelegate;

    signal itemClicked(string lang);
    signal listDropped();

    function switchAnimation(){
        if (checkListBoxRectangle.height == checkListBoxId.height){
            listDropped();
            checkListBoxRectangle.border.width = 1;
            checkListBoxRectangle.color = "#ea8a07";  //f28a0d
            checkListBoxRectangle.height = checkListBoxId.height + listViewId.height;
        }
        else {
            checkListBoxRectangle.border.width = 0;
            checkListBoxRectangle.color = "white";
            checkListBoxRectangle.height = checkListBoxId.height;
            mainClickText.opacity = 0.8;
            checkListBoxRectangle.opacity = 0.8;
        }

        listViewId.visible = !listViewId.visible;
    }

    function getCheckBoxX(){
        if (checkListBoxX < 0)
            return mainClickText.width + 10;

            return checkListBoxX;
    }

    Text{
        id: mainClickText
        text: buttonText
        style: Text.Normal
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Segoe UI Semibold"
        font.bold: false
        font.pixelSize: 14
        font.weight: "Normal"
        opacity: 0.8
        smooth: true
        color: "white"
    }

    Rectangle{
        id: checkListBoxRectangle
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: getCheckBoxX()
        opacity: 0.8
        height: parent.height
        width: checkListBoxWidth

        border { color: "#ea8a07"; width: 0 }

        Text{
            id: buttonCheckListBoxTextId
            text: buttonCheckListBoxText
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 3
            font.family: "Segoe UI Semibold"
            font.bold: false
            font.pixelSize: 15
            //font.weight: "Light"
            smooth: true
            color: "black"
        }

        Image{
            anchors.verticalCenterOffset: 1
            source: "../images/downArrow.png"
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 12
            visible: checkBoxType
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true;
            onEntered: {
                mainClickText.opacity = 1;
                checkListBoxRectangle.opacity = 1;
            }
            onExited: {
                if (!isListActive){
                    mainClickText.opacity = 0.8;
                    checkListBoxRectangle.opacity = 0.8;
                }
            }
            onClicked: switchAnimation();
        }

        ListView{
            id: listViewId
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            height: listViewId.count * 30
            interactive: false

            visible: false
/*
            highlightFollowsCurrentItem: true

            highlight: Rectangle{
                color: "green"
                opacity: 0.8
                x: 1
                y: 1
                width: checkListBoxWidth - 1
                height: 30
            }
*/
            delegate: componentDelegate
            model: listModel
        }
    }
}
