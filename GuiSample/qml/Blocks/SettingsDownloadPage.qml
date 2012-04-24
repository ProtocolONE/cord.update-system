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
import "../Elements" as Elements


Rectangle {
    id: mainDownloadPageRectangle
    color: "transparent"

    property int animationTypeVar: 1;
    property Component componentListBoxDelegate: Rectangle{
                                                  id: delegateRectangle
                                                      x: 1
                                                      color: "white"
                                                      width: checkListBoxWidth - 1
                                                      height: 30

                                                   Text{
                                                      height: 18
                                                      x: 9
                                                      //anchors.horizontalCenter: parent.horizontalCenter
                                                      y: 3
                                                      text: qsTr(textValue) + mainWindow.emptyString

                                                      font.family: "Segoe UI Semibold"
                                                      font.bold: false
                                                      font.pixelSize: 15
                                                      smooth: true
                                                  }

                                                   MouseArea{
                                                       anchors.fill: parent
                                                       hoverEnabled: true
                                                       onEntered: {
                                                           delegateRectangle.color = "#eab46b"
                                                       }
                                                       onExited: {
                                                           delegateRectangle.color = "white"
                                                       }
                                                       onClicked: {
                                                           itemClicked(shortValue);
                                                           switchAnimation();
                                                           buttonCheckListBoxText = qsTr(textValue) + mainWindow.emptyString;
                                                           mainClickText.opacity = 0.8;
                                                           checkListBoxRectangle.opacity = 0.8;
                                                       }
                                                    }
                                                   CursorShapeArea {
                                                     anchors.fill: parent
                                                     cursorShape: Qt.PointingHandCursor
                                                   }
                                              }

    function deactiveAllItems(){
        if (line1.isListActive)
            line1.switchAnimation();
        if (line2.isListActive)
            line2.switchAnimation();
    }


    ParallelAnimation{
        id: opacityAnimation;
        running: true;

        //NumberAnimation{ target: mainDownloadPageRectangle; property: "opacity"; from: 0; to: 1; duration: 150 }
        NumberAnimation{ target: line1; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
        NumberAnimation{ target: line2; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
        NumberAnimation{ target: line3; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
        NumberAnimation{ target: autoSetButton; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 0.7; duration: 200 }
        NumberAnimation{ target: line4; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
        }


    MouseArea{
        anchors.fill: parent
        onClicked: {
            deactiveAllItems();
            if (mainAuthModule.visible){
                mainAuthModule.testAndCloseNickNameView();
            }
        }
    }
/*
    ListView{
        anchors.fill: parent
        anchors.rightMargin: 10
        interactive: false

*/
    /*
        Elements.ScrollBar {
                        flickable: parent
                        vertical: true
                        hideScrollBarsWhenStopped: false
                        visible: false
                    }
*/
//        delegate: Item{

            function getLeftCoord(){
                return Math.max(Math.max(line1.textWidth,line2.textWidth), Math.max(line3.textWidth,line4.textWidth)) + 20;
            }

            SequentialAnimation{
                running: false;

                ParallelAnimation{
                    SequentialAnimation{
                        PauseAnimation { duration: 50 }
                        ParallelAnimation{
                            NumberAnimation{ target: line1; easing.type: Easing.OutQuad; property: "x"; from: 100; to: 0; duration: 150 }
                            NumberAnimation{ target: line1; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
                        }
                    }
                    SequentialAnimation{
                        PauseAnimation { duration: 100 }
                        ParallelAnimation{
                            NumberAnimation{ target: line2; easing.type: Easing.OutQuad; property: "x"; from: 100; to: 0; duration: 150 }
                            NumberAnimation{ target: line2; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
                        }
                    }
                    SequentialAnimation{
                        PauseAnimation { duration: 150 }
                        ParallelAnimation{
                            NumberAnimation{ target: line3; easing.type: Easing.OutQuad; property: "x"; from: 100; to: 0; duration: 150 }
                            NumberAnimation{ target: line3; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
                            NumberAnimation{ target: autoSetButton; easing.type: Easing.OutQuad; property: "anchors.leftMargin"; from: 300; to: getLeftCoord() + line3.checkListBoxWidth + 7; duration: 150 }
                            NumberAnimation{ target: autoSetButton; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 0.7; duration: 150 }
                        }
                    }
                    SequentialAnimation{
                        PauseAnimation { duration: 200 }
                        ParallelAnimation{
                            NumberAnimation{ target: line4; easing.type: Easing.OutQuad; property: "x"; from: 100; to: 0; duration: 150 }
                            NumberAnimation{ target: line4; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
                        }
                    }
                }
                onCompleted: animationTypeVar = 2;
            }

            Elements.TextEditArea{
                x: 0
                id: line4
                anchors.top: parent.top
                anchors.topMargin: 108
                width: 393
                checkListBoxX: getLeftCoord()
                checkListBoxWidth: 69
                buttonText: qsTr("Simultaneous connections") + mainWindow.emptyString
                buttonCheckListBoxText: "200"
                opacity: 0
            }

            Elements.TextEditArea{
                x: 0
                id: line3
                anchors.top: parent.top
                anchors.topMargin: 72
                width: 393
                checkListBoxX: getLeftCoord()
                checkListBoxWidth: 69
                buttonText: qsTr("Port for incoming connections") + mainWindow.emptyString
                buttonCheckListBoxText: "25"
                opacity: 0
            }

            Elements.Button3{
                id: autoSetButton
                anchors.top: parent.top
                anchors.topMargin: 72
                anchors.left: parent.left
                anchors.leftMargin: getLeftCoord() + line3.checkListBoxWidth + 7
                buttonText: qsTr("Autoset") + mainWindow.emptyString
                onButtonClicked: line3.buttonCheckListBoxText = "155"
                opacity: 0
            }

            Elements.CheckListBox{
                id: line2
                x: 0
                anchors.top: parent.top
                anchors.topMargin: 36
                width: 393
                checkListBoxX: getLeftCoord()
                checkListBoxWidth: 148
                checkBoxType: true
                buttonText: qsTr("Upload speed limit") + mainWindow.emptyString
                buttonCheckListBoxText: qsTr("Unlimited") + mainWindow.emptyString
                onListDropped: {
                    if (line1.isListActive)
                        line1.switchAnimation();
                }

                opacity: 0
                componentDelegate: componentListBoxDelegate

                listModel: ListModel {
                    ListElement {
                        textValue: QT_TR_NOOP("Unlimited")
                        shortValue: "100"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("50 Mbit/s")
                        shortValue: "50"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("25 Mbit/s")
                        shortValue: "25"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("10 Mbit/s")
                        shortValue: "10"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("5 Mbit/s")
                        shortValue: "5"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("2 Mbit/s")
                        shortValue: "2"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("1 Mbit/s")
                        shortValue: "1"
                    }
                }
            }

            Elements.CheckListBox{
                id: line1
                x: 0
                width: 393
                checkListBoxX: getLeftCoord()
                checkListBoxWidth: 148
                checkBoxType: true
                buttonText: qsTr("Download speed limit") + mainWindow.emptyString
                buttonCheckListBoxText: qsTr("Unlimited") + mainWindow.emptyString
                componentDelegate: componentListBoxDelegate
                onListDropped: {
                    if (line2.isListActive)
                        line2.switchAnimation();
                }
                opacity: 0
                listModel: ListModel {
                    ListElement {
                        textValue: QT_TR_NOOP("Unlimited")
                        shortValue: "100"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("50 Mbit/s")
                        shortValue: "50"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("25 Mbit/s")
                        shortValue: "25"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("10 Mbit/s")
                        shortValue: "10"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("5 Mbit/s")
                        shortValue: "5"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("2 Mbit/s")
                        shortValue: "2"
                    }
                    ListElement {
                        textValue: QT_TR_NOOP("1 Mbit/s")
                        shortValue: "1"
                    }
                }
            }
       // }
/*
        model: ListModel{
            ListElement{ tmp: "123" }
            ListElement{ isAnimStart: true; }
        }*/
  //  }


}
