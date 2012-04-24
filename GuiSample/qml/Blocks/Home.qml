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
import "../Models" as Models
import "../Delegates" as Delegates

Rectangle {
    id: cHome
    color: "transparent"
    focus: true

    signal finishAnimation()
    signal mouseItemClicked(int index);

    property int tmpIndex: -1   // need for change current index
    property int currentIndex: bsIcon.isActive ? 0 : homeGamesGridView.currentIndex + 1
    property int mouseIndex: -1
    property bool isKeyboardHighlightEnable: true

    function closeAnimationStart(){
        closeHomeAnimation.start();
    }

    NumberAnimation { id: closeHomeAnimation; easing.type: Easing.OutQuad; target: cHome; property: "opacity"; from: 1; to: 0; duration: 150 }

    function deactiveItems(){
        if (currentIndex == 0){
            if (bsIcon.isActive){
                bsIcon.activeAnimation(true);
                bsIcon.isActive = false
            }
        } else if (homeGamesGridView.currentItem.isActive){
            homeGamesGridView.currentItem.activeAnimation(true);
            homeGamesGridView.currentItem.isActive = false;
        }
    }

    function onMouseIndexChanged(num){
        deactiveItems()
        mouseIndex = num
    }

    Keys.onPressed: {
         if (event.key == Qt.Key_Return){
             if (homeGamesGridView.currentItem && homeGamesGridView.currentItem.isActive){
                 mouseItemClicked(homeGamesGridView.currentIndex + 1)
             } else if (bsIcon.isActive)
                 mouseItemClicked(0)

             event.accepted = true;
         }
        else if (event.key == Qt.Key_Right) {
                if (isKeyboardHighlightEnable){
                    tmpIndex = homeGamesGridView.currentIndex;
                    if (homeGamesGridView.currentItem){
                        if (homeGamesGridView.currentItem.isActive){
                            homeGamesGridView.currentItem.activeAnimation(true);
                            homeGamesGridView.currentItem.isActive = false;
                        }

                    homeGamesGridView.moveCurrentIndexRight();
                }
                else {
                    if (bsIcon.isActive){
                        bsIcon.activeAnimation(true);
                        bsIcon.isActive = false
                    }
                    homeGamesGridView.currentIndex = 0;
                }
                if (tmpIndex == homeGamesGridView.currentIndex && homeGamesGridView.currentIndex == homeGamesGridView.count - 1 ){
                    bsIcon.activeAnimation(false);
                    bsIcon.isActive = true
                    homeGamesGridView.currentIndex = -1;
                    tmpIndex = -1;
                } else if (homeGamesGridView.currentItem){
                    homeGamesGridView.currentItem.activeAnimation(false);
                    homeGamesGridView.currentItem.isActive = true;
                }
            }
            event.accepted = true;
        } else if (event.key == Qt.Key_Left) {
            if (isKeyboardHighlightEnable){
                tmpIndex = homeGamesGridView.currentIndex;

                if (homeGamesGridView.currentItem){
                    if (homeGamesGridView.currentItem.isActive){
                        homeGamesGridView.currentItem.activeAnimation(true);
                        homeGamesGridView.currentItem.isActive = false;
                    }

                    homeGamesGridView.moveCurrentIndexLeft();
                }
                else {
                    if (bsIcon.isActive){
                        bsIcon.activeAnimation(true);
                        bsIcon.isActive = false
                    }
                    homeGamesGridView.currentIndex = homeGamesGridView.count - 1;
                }
                if (tmpIndex == homeGamesGridView.currentIndex && homeGamesGridView.currentIndex == GridView.Beginning ){
                    bsIcon.activeAnimation(false);
                    bsIcon.isActive = true;
                    homeGamesGridView.currentIndex = -1;
                    tmpIndex = -1;
                } else if (homeGamesGridView.currentItem){
                    homeGamesGridView.currentItem.activeAnimation(false);
                    homeGamesGridView.currentItem.isActive = true;
                }
            }

            event.accepted = true;
        } else if (event.key == Qt.Key_Up){
            if (homeGamesGridView.currentItem && isKeyboardHighlightEnable){
                if (homeGamesGridView.currentItem.isActive){
                    homeGamesGridView.currentItem.activeAnimation(true);
                    homeGamesGridView.currentItem.isActive = false;
                }
                homeGamesGridView.moveCurrentIndexUp();
                homeGamesGridView.currentItem.activeAnimation(false);
                homeGamesGridView.currentItem.isActive = true;

            }
            event.accepted = true;
        } else if (event.key == Qt.Key_Down){
            if (homeGamesGridView.currentItem && isKeyboardHighlightEnable){
                if (homeGamesGridView.currentItem.isActive){
                    homeGamesGridView.currentItem.activeAnimation(true);
                    homeGamesGridView.currentItem.isActive = false;
                }
                homeGamesGridView.moveCurrentIndexDown();

                homeGamesGridView.currentItem.activeAnimation(false);
                homeGamesGridView.currentItem.isActive = true;
            }
            event.accepted = true;
        }
    }

    Delegates.GameIconDelegate{
        id: bsIcon
        property int animationPause: 0
        property int animationFrom: -150
        property int animationTo: 40
        property int animationDuration: 250
        property double animationOpacityFrom: 0.1
        property int animationOpacityTo: 1
        property int animationOpacityDuration: 250
        property int index: 0
        x: 40; y: 106

        opacity: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        imgSource: "../images/bs_icon_big.png"
        normalScale: 0.995
        activeScale: 1.0575

        onMouseHover: {
            deactiveItems();
            homeGamesGridView.currentIndex = -1;
            cHome.onMouseIndexChanged(0);
            cHome.isKeyboardHighlightEnable = false;
        }
        onNoMouseAtItem: { cHome.isKeyboardHighlightEnable = true; }
        onMouseClicked: mouseItemClicked(0);
    }

    GridView {
        id: homeGamesGridView
        x: 310
        y: 106 + 6
        width: 135 * 3
        height: 135 * 2
        cellHeight: 255 / 2 + 7
        cellWidth: 135
        clip: false
        interactive: false
        currentIndex: -1

        delegate: Delegates.GameIconDelegate{
            imgSource: imageSource
            onMouseHover: {
                deactiveItems();
                homeGamesGridView.currentIndex = index;
                cHome.onMouseIndexChanged(num + 1);
                cHome.isKeyboardHighlightEnable = false;
            }
            onNoMouseAtItem: { cHome.isKeyboardHighlightEnable = true; }
            onMouseClicked: mouseItemClicked(num + 1);
        }
        model: Models.GamesListModel{}
    }
}
