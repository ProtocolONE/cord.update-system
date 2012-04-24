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
import "../Elements" as Elements

Rectangle{
    id: gameIconDelegate
    property string animationFromProperty: "x"
    property bool isActive: false
    property bool isAnimationStart: true
    property double normalScale: 0.985
    property double activeScale: 1.0575
    property string imgSource;
    property bool imageSmooth: true;

    signal mouseHover(int num);
    signal noMouseAtItem();
    signal mouseClicked(int num);

    x:0
    y:0
    width: gameIconImageDelegate.width + 1
    height: gameIconImageDelegate.height + 1
    color: "transparent"
    scale: normalScale
    opacity: isAnimationStart ? 0 : 1

    function activeAnimation(reverse){
        if (reverse){
            delegateDownAnimation.start(); borderRectangleDelegate.visible = false
        } else {
            delegateUpAnimation.start(); borderRectangleDelegate.visible = true
        }
    }

    SequentialAnimation{
        running: isAnimationStart
        PauseAnimation { duration: animationPause }
        ParallelAnimation{
            NumberAnimation{ target: gameIconDelegate; easing.type: Easing.OutQuad; property: animationFromProperty; from: animationFrom; to: animationTo; duration: animationDuration }
            NumberAnimation{ target: gameIconDelegate; easing.type: Easing.OutQuad; property: "opacity"; from: animationOpacityFrom; to: animationOpacityTo; duration: animationOpacityDuration }
        }
    }

    NumberAnimation{ id: delegateDownAnimation; easing.type: Easing.OutQuad; running: false; target: gameIconDelegate; property: "scale"; from: activeScale; to: normalScale; duration: 105; onStarted: gameBoxItemBg.visible = true; }
    NumberAnimation{ id: delegateUpAnimation; easing.type: Easing.OutQuad; running: false; target: gameIconDelegate; property: "scale"; from: normalScale; to: activeScale; duration: 105; onStarted: gameBoxItemBg.visible = false; }

    Rectangle {
        visible: true;
        id: gameBoxItemBg
        color: "#fff"
        anchors.fill: parent
        opacity: 0.3
    }

    Image {
        id: gameIconImageDelegate
        x: 1
        y: 1

        Elements.Border{
            id: borderRectangleDelegate;
            borderColor: "#ef8e0c";
            anchors.fill: parent
            anchors.rightMargin: 1
            anchors.bottomMargin: 1
        }

        smooth: imageSmooth
        source: imgSource
        fillMode: Image.Stretch
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: { activeAnimation(false); mouseHover(index); }
        onExited: { activeAnimation(true); noMouseAtItem(); }
        onClicked: mouseClicked(index);
    }
}

