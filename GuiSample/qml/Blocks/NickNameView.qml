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

Rectangle {
    id: nickNameViewClass
    width: getWidgetWidth();
    height: 66
    color: "transparent"
    border { color: "#ff9900"; width: 0 }

    property string avatarSource: "../images/avatar.png"
    property string upText
    property string downText
    property bool isMenuOpen: false

    signal quitClicked();
    signal settingsClicked();
    signal moneyClicked();

    function getWidgetWidth(){

        if ( upTextWidget.width > downTextWidget.width ){
            if ( upTextWidget.width > 65 )
                return 85 + upTextWidget.width;
            else
                return 150;
        } else if ( downTextWidget.width > 65)
            return 85 + downTextWidget.width;
        else
            return 150;
    }

    function switchMenu(){
        if (isMenuOpen){
            opacityBlockUp.start();
        } else {
            opacityBlockDown.start();
        }
    }

    function buttonMenuPressed(buttonIndex){
        if (buttonIndex == 0){
            moneyClicked();
            switchMenu();
        }
        else if (buttonIndex == 1)
            settingsClicked();
        else {
            switchMenu();
            quitClicked();
        }
    }

    SequentialAnimation{
        id: opacityBlockUp;
        ParallelAnimation{
            NumberAnimation{ target: opacityBlock; easing.type: Easing.OutQuad; property: "opacity"; from: 0.95; to: 0.5; duration: 150 }
            NumberAnimation{ target: menuListView; easing.type: Easing.OutQuad; property: "opacity"; from: 1; to: 0; duration: 150 }
            NumberAnimation{ target: nickNameViewClass; easing.type: Easing.OutQuad; property: "height"; from: 213; to: 66; duration: 150 }
            PropertyAnimation{ target: nickNameViewClass; easing.type: Easing.OutQuad; property: "border.width"; to: 0; duration: 100 }
        }
        onCompleted: isMenuOpen = false;
    }
    SequentialAnimation{
        id: opacityBlockDown;
        ParallelAnimation{
            NumberAnimation{ target: opacityBlock; easing.type: Easing.OutQuad; property: "opacity"; from: 0.5; to: 0.95; duration: 150 }
            NumberAnimation{ target: menuListView; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
            NumberAnimation{ target: nickNameViewClass; easing.type: Easing.OutQuad; property: "height"; from: 66; to: 213; duration: 150 }
            PropertyAnimation{ target: nickNameViewClass; easing.type: Easing.OutQuad; property: "border.width"; to: 1; duration: 100 }
        }
        onCompleted: isMenuOpen = true;
    }

    MouseArea{
        anchors.fill: parent;
        onReleased: switchMenu();
    }

    Rectangle{
        id: opacityBlock
        anchors.fill: parent
        opacity: 0.5
        color: "#000000"
        anchors.leftMargin: 1
        anchors.topMargin: 1
    }

    Rectangle{
        color:  "transparent"

        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4

        width: 58
        height: 58

        Rectangle{
            color: "#ffffff"
            opacity: 0.33
            anchors.fill: parent
            smooth: true
        }

        Image{
            x: 1
            y: 1
            /*
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
    */
            width: 56
            height: 56
            source: avatarSource
            opacity: 1
            smooth: true
            fillMode: Image.PreserveAspectFit
        }


    }


    Text{
        id: upTextWidget
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 70
        smooth: true
        font.family: fontTahoma.name
        font.pixelSize: 15
        color: "#ffffff"
        text: upText
        font.bold: false
    }

    Text{
        id: downTextWidget
        anchors.top: parent.top
        anchors.topMargin: 41
        anchors.left: parent.left
        anchors.leftMargin: 70
        smooth: true
        font.family: fontTahoma.name
        font.pixelSize: 15
        color: "#ffffff"
        text: downText
        font.bold: false
    }

    ListView {
        id: menuListView
        anchors.top: parent.top
        anchors.topMargin: 63
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        interactive: false
        visible: isMenuOpen

        delegate: Rectangle {
            id: mainImageButtonRectangle
            color: "transparent"

            width: menuListView.width
            height: menuListView.height / 3 > 50 ? 50 : menuListView.height / 3

            Rectangle{
                height: 1
                color: "#ffffff"
                opacity: 0.5
                anchors.left: parent.left
                anchors.leftMargin: 1
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.top: parent.top
                anchors.topMargin: 0
            }

            Image{
                id: imageIcon
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5
                source: imageSource
                opacity: 0.4
            }

            Text{
                id: imageButtonTextId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 28 + imageIcon.width
                text: qsTr(value) + mainWindow.emptyString;
                anchors.horizontalCenterOffset: 10
                font.family: fontTahoma.name
                font.bold: false
                font.pixelSize: 15
                color: "#cccccc"
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: buttonMenuPressed(index);
                onEntered: {
                    mainImageButtonRectangle.color = "#ff9800"
                    imageButtonTextId.color = "#dddddd"
                    imageIcon.opacity = 1
                }
                onExited: {
                    mainImageButtonRectangle.color = "transparent"
                    imageIcon.opacity = 0.4
                    imageButtonTextId.color = "#cccccc"
                }
            }
        }

        model: ListModel {
            ListElement {
                imageSource: "../images/moneyIcon.png"
                value: QT_TR_NOOP("Money")
            }
            ListElement {
                imageSource: "../images/settingsIcon.png"
                value: QT_TR_NOOP("Settings")
            }
            ListElement {
                imageSource: "../images/quitIcon.png"
                value: QT_TR_NOOP("Quit")
            }
        }
    }

}
