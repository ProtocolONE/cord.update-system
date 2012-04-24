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
    id: mainGeneralPageRectangle
    color: "transparent"
    property int animationType: 0;

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if (line1.isListActive)
                line1.switchAnimation();
            if (mainAuthModule.visible){
                mainAuthModule.testAndCloseNickNameView();
            }
        }
    }


    ParallelAnimation{
        id: opacityAnimation;
        running: true;

      //  NumberAnimation{ target: mainGeneralPageRectangle; property: "opacity"; from: 0; to: 1; duration: 20 }
        NumberAnimation{ target: line1; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
        NumberAnimation{ target: line2; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
        NumberAnimation{ target: line3; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
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
                }
            }
        }
        onCompleted: animationType = 1;
    }

    property Component componentListBoxDelegate: Rectangle{
                                                  id: delegateRectangle
                                                      x: 1
                                                      color: "white"
                                                      width: checkListBoxWidth - 1
                                                      height: 30

                                                   Text{
                                                      height: 18
                                                      x: 9
                                                      y: 3
                                                      //anchors.horizontalCenter: parent.horizontalCenter
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
                                                           buttonCheckListBoxText = textValue;
                                                           mainClickText.opacity = 0.8;
                                                           checkListBoxRectangle.opacity = 0.8;
                                                       }
                                                    }
                                                   CursorShapeArea {
                                                     anchors.fill: parent
                                                     cursorShape: Qt.PointingHandCursor
                                                   }
                                              }

    Elements.CheckBox{
        id: line3
        buttonText: qsTr("Run in a minimized") + mainWindow.emptyString
        anchors.top: parent.top
        anchors.topMargin: 52 + 10
        opacity: 0
    }
    Elements.CheckBox{
        id: line2
        anchors.top: parent.top
        anchors.topMargin: 26 + 10
        buttonText: qsTr("Autostart GameNet") + mainWindow.emptyString
        opacity: 0
    }
    Elements.CheckListBox{
        id: line1
        anchors.top: parent.top
        anchors.topMargin: 0
        width: 393
        checkListBoxX: -1
        checkListBoxWidth: 100
        checkBoxType: true
        buttonText: qsTr("Language") + mainWindow.emptyString
        buttonCheckListBoxText: mainWindow.language == "ru" ? "Русский" : mainWindow.language == "en" ? "English" : "";
        onItemClicked: mainWindow.selectLanguage(lang);

        opacity: 0
        componentDelegate: componentListBoxDelegate

        listModel: ListModel {
            ListElement {
                textValue: QT_TR_NOOP("Russian")
                shortValue: "ru"
            }
            ListElement {
                textValue: "English"
                shortValue: "en"
            }
        }
    }
}
