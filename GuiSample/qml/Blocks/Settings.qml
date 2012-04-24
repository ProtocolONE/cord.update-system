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
    id: settingsPageId
    color: "transparent"
    state: "GeneralPage"

    signal finishAnimation();

    function navigationTextClicked(index){
        switch (index){
        case 0: { settingsPageId.state = "GeneralPage"; break }
        case 1: { settingsPageId.state = "DownloadPage"; break }
        case 2: { settingsPageId.state = "NotificationsPage"; break }
        }

    }

    SequentialAnimation{
        id: startSettingsAnimation;
        running: true;

        ParallelAnimation{
            NumberAnimation{ target: mainClickText; easing.type: Easing.OutQuad; property: "anchors.topMargin"; from: 40; to: 15; duration: 250 }
            NumberAnimation{ target: mainClickText; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 250 }

        }
        onCompleted: finishAnimation();
    }

    Text{
        id: mainClickText
        text: qsTr("Settings") + mainWindow.emptyString
        style: Text.Normal

        anchors.left: parent.left
        anchors.leftMargin: 38
        anchors.top: parent.top
        anchors.topMargin: 15

        font.family: "Segoe UI Light"
        font.bold: false
        font.pixelSize: 46
        opacity: 0
        smooth: true

        color: "white"
    }

    ListView{
        id: listViewId
        anchors.left: parent.left
        anchors.leftMargin: 31
        anchors.top: parent.top
        anchors.topMargin: 110
        height: pageLoader.height
        width: 228
        currentIndex: 0
        interactive: false
        clip: true
        spacing: 3

        Elements.ScrollBar {
                        flickable: parent
                        vertical: true
                        hideScrollBarsWhenStopped: false
                        visible: false
                    }

        delegate: Elements.TextClick{
                    id: generalMenuText
                    state: itemState
                    opacity: 0
                    buttonText: qsTr(itemText) + mainWindow.emptyString

                    onTextClicked: {
                        if (listViewId.currentIndex != index){
                            listViewId.currentItem.state = "Normal";
                            navigationTextClicked(index);
                            listViewId.currentIndex = index;

                            console.log(listViewId.currentIndex + " index " + index);
                        }
                    }

                    SequentialAnimation{
                        running: true;
                        PauseAnimation { duration: animationPause }
                        ParallelAnimation{
                            NumberAnimation{ target: generalMenuText; easing.type: Easing.OutQuad; property: "x"; from: -60; to: 0; duration: 250 }
                            NumberAnimation{ target: generalMenuText; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 250 }
                        }
                    }
                }


        model: ListModel{
            ListElement{
                itemText: QT_TR_NOOP("General");
                itemState: "Active";
                animationPause: 0
            }
            ListElement{
                itemText: QT_TR_NOOP("Download");
                itemState: "Normal"
                animationPause: 100
            }
            ListElement{
                itemText: QT_TR_NOOP("Notifications");
                itemState: "Normal"
                animationPause: 150
            }
        }

    }
/*
    Elements.TextClick{
        id: generalMenuText
        anchors.left: parent.left
        anchors.leftMargin: 31
        anchors.top: parent.top
        anchors.topMargin: 110
        state: "Active"
        opacity: 0

        buttonText: qsTr("General") + mainWindow.emptyString

        onTextClicked: { navigationTextClicked(0) }
    }

    Elements.TextClick{
        id: downloadMenuText
        anchors.left: parent.left
        anchors.leftMargin: 31
        anchors.top: parent.top
        anchors.topMargin: 145
        opacity: 0

        buttonText: qsTr("Download") + mainWindow.emptyString

       onTextClicked: { navigationTextClicked(1) }
    }

    Elements.TextClick{
        id: notificationsMenuText
        anchors.left: parent.left
        anchors.leftMargin: 31
        anchors.top: parent.top
        anchors.topMargin: 180
        opacity: 0

        buttonText: qsTr("Notifications") + mainWindow.emptyString

        onTextClicked: { navigationTextClicked(2) }
    }
*/
    Elements.Button2{
        anchors.left: parent.left
        anchors.leftMargin: 300
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 49
        width: 70

        onButtonClicked:{
            qGNA_main.state = qGNA_main.lastState;
        }
    }

    Elements.Button3{
        anchors.left: parent.left
        anchors.leftMargin: 380
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 49
        buttonText: qsTr("Default settings") + mainWindow.emptyString
    }

    Loader {
        id: pageLoader;
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 301
        anchors.top: parent.top
        anchors.topMargin: 116
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        focus: true;
    }

    states: [
        State {
            name: "GeneralPage"
            PropertyChanges { target: pageLoader; source: "SettingsGeneralPage.qml" }
        },
        State {
            name: "DownloadPage"
            PropertyChanges { target: pageLoader; source: "SettingsDownloadPage.qml" }
        },
        State {
            name: "NotificationsPage"
            PropertyChanges { target: pageLoader; source: "SettingsNotificationsPage.qml" }
        }
    ]

}
