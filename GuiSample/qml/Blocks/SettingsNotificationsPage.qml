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
    id: mainNotificationsPageRectangle

    color: "transparent"

    property int animationType: 0;

    ParallelAnimation{
        id: opacityAnimation;
        running: true;

    //    NumberAnimation{ target: mainNotificationsPageRectangle; property: "opacity"; from: 0; to: 1; duration: 300 }
         NumberAnimation{ target: line1; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
         NumberAnimation{ target: line2; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
         NumberAnimation{ target: line3; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
         NumberAnimation{ target: line4; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
         NumberAnimation{ target: line5; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 200 }
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
            SequentialAnimation{
                PauseAnimation { duration: 175 }
                ParallelAnimation{
                    NumberAnimation{ target: line4; easing.type: Easing.OutQuad; property: "x"; from: 100; to: 0; duration: 150 }
                    NumberAnimation{ target: line4; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
                }
            }
            SequentialAnimation{
                PauseAnimation { duration: 200 }
                ParallelAnimation{
                    NumberAnimation{ target: line5; easing.type: Easing.OutQuad; property: "x"; from: 100; to: 0; duration: 150 }
                    NumberAnimation{ target: line5; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150 }
                }
            }
        }
        onCompleted: animationType = 1;
    }

    Elements.CheckBox{
        id: line1
        buttonText: qsTr("Show notifications when deployed GameNet") + mainWindow.emptyString
        state: "Normal"
        opacity: 0
    }

    Elements.CheckBox{
        id: line2
        anchors.top: parent.top
        anchors.topMargin: 26
        buttonText: qsTr("Start/end game downloads") + mainWindow.emptyString
        state: "Normal"
        opacity: 0
    }

    Elements.CheckBox{
        id: line3
        anchors.top: parent.top
        anchors.topMargin: 52
        buttonText: qsTr("Join/Disconnect friend from network") + mainWindow.emptyString
        state: "Normal"
        opacity: 0
    }

    Elements.CheckBox{
        id: line4
        anchors.top: parent.top
        anchors.topMargin: 78
        buttonText: qsTr("Join/Disconnect friend from game") + mainWindow.emptyString
        state: "Normal"
        opacity: 0
    }

    Elements.CheckBox{
        id: line5
        anchors.top: parent.top
        anchors.topMargin: 104
        buttonText: qsTr("New message") + mainWindow.emptyString
        state: "Normal"
        opacity: 0
    }
}
