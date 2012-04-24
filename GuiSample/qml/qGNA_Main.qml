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
import "." as Current
import "Elements" as Elements
import "Blocks" as Blocks

Elements.Shadow{
    x: 0; y: 0;
    clip: true
    windowWidth: 800
    windowHeight: 400

    signal onWindowPressed(int x, int y);
    signal onWindowReleased(int x, int y);
    signal onWindowClose();
    signal onWindowOpen();
    signal onWindowPositionChanged(int x, int y);
    signal onWindowMinimize();

    Rectangle{
        id: qGNA_main
        x: 0; y: 0;
        width: 800
        height: 400
        state: "LoadingPage"
        color: "transparent"
        clip: true

        property int currentGameIndex
        property string lastState
        property bool isPageControlAccepted: !mainAuthModule.isAuthMenuOpen

        FontLoader { id: fontTahoma; source: "fonts/Tahoma.ttf"}

        ParallelAnimation{
            id: closeAnimation;
            running: false;
            NumberAnimation{ target: qGNA_main; property: "scale"; from: 1; to: 0.05; duration: 150 }
            NumberAnimation{ target: qGNA_main; property: "opacity"; from: 1; to: 0;  duration: 150 }
            onCompleted: onWindowClose()
        }
        ParallelAnimation{
            id: openAnimation;
            running: true;
            NumberAnimation{ target: qGNA_main; property: "scale"; from: 0.05; to: 1; duration: 250 }
            NumberAnimation{ target: qGNA_main; property: "opacity"; from: 0; to: 1;  duration: 250 }
            onCompleted: onWindowOpen()
        }

        Image{
            source: "images/backImage.png"
            anchors.centerIn: parent
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    onWindowPressed(mouseX,mouseY);
                    if (mainAuthModule.visible){
                        mainAuthModule.testAndCloseNickNameView();
                    }
                }
                onReleased: onWindowReleased(mouseX,mouseY);
                onPositionChanged: onWindowPositionChanged(mouseX,mouseY);
            }
        }

        Loader {
            id: pageLoader;
            anchors.fill: parent;
            focus: true;
        }

        Connections {
                 target: pageLoader.item
                 onFinishAnimation: {
                     if (qGNA_main.state == "LoadingPage"){
                         qGNA_main.lastState = "HomePage"
                         qGNA_main.state = "HomePage"
                     }
                  }
        }

        Image {
            id: backTextImage
            x: 37
            y: 33
            smooth: true
            source: "images/gamenet.png"
        }

/*
        Blocks.Auth{
            id: mainAuthModule
            visible: false
            anchors.fill: parent
            onCloseAnimationStart: parent.state == "HomePage" ? pageLoader.visible = true : {}
            onOpenAnimationFinished: parent.state == "HomePage" ? pageLoader.visible = false : {}
            onSettingsButtonClicked: {
                if (parent.state = "SettingsPage")
                    return;

                qGNA_main.lastState = qGNA_main.state;
                parent.state = "SettingsPage";
            }
        }
*/
        Image{
            id: minButtonImage
            x: 760
            y: 10
            source: "images/minButton.png"
            opacity: 0.5
            NumberAnimation{ id: minButtonDownAnimation; running: false; target: minButtonImage; property: "opacity"; from: 0.9; to: 0.5; duration: 225 }
            NumberAnimation{ id: minButtonUpAnimation; running: false; target: minButtonImage; property: "opacity"; from: 0.5; to: 0.9; duration: 225 }
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: { minButtonImage.opacity = 0.5; onWindowMinimize(); }
                onEntered: minButtonUpAnimation.start()
                onExited: minButtonDownAnimation.start()
            }
        }

        Image{
            id: closeButtonImage
            x: 780
            y: 10
            source: "images/closeButton.png"
            opacity: 0.5
            NumberAnimation{ id: closeButtonDownAnimation; running: false; target: closeButtonImage; property: "opacity"; from: 0.9; to: 0.5; duration: 225 }
            NumberAnimation{ id: closeButtonUpAnimation; running: false; target: closeButtonImage; property: "opacity"; from: 0.5; to: 0.9; duration: 225 }
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: closeAnimation.running = true
                onEntered: closeButtonUpAnimation.start()
                onExited: closeButtonDownAnimation.start()
            }
        }

        states: [
            State {
                name: "LoadingPage"
                PropertyChanges { target: pageLoader; source: "Models/LoadScreenModel.qml" }
                //PropertyChanges { target: mainAuthModule; visible: false }
                PropertyChanges { target: backTextImage; visible: true }
            },
            State {
                name: "HomePage"
                PropertyChanges { target: pageLoader; source: "Models/HomeModel.qml" }
                //PropertyChanges { target: mainAuthModule; visible: true }
                PropertyChanges { target: backTextImage; visible: true }
            },
            State {
                name: "GamesSwitchPage"
                PropertyChanges { target: pageLoader; source: "Models/GamesSwitchModel.qml" }
                //PropertyChanges { target: mainAuthModule; visible: true }
                PropertyChanges { target: backTextImage; visible: false }
            },
            State {
                name: "SettingsPage"
                PropertyChanges { target: pageLoader; source: "Models/SettingsModel.qml" }
                //PropertyChanges { target: mainAuthModule; visible: true }
                PropertyChanges { target: backTextImage; visible: false }
            }
        ]
    }
}
