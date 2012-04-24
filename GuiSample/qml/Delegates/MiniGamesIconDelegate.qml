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

Image {
    id: gameIconDelegate
    property string animationFromProperty: "x"
    property bool isActive: false

    signal mouseHover(int num);
    signal noMouseAtItem();
    signal mouseClicked(int num);

    function activeAnimation(reverse){
        if (reverse){
            delegateDownAnimation.start(); borderRectangleDelegate.visible = false
        } else {
            delegateUpAnimation.start(); borderRectangleDelegate.visible = true
        }
    }

    Elements.CBorder{ id: borderRectangleDelegate }

    SequentialAnimation{
        running: true
        PauseAnimation { duration: animationPause }
        ParallelAnimation{
            NumberAnimation{ target: gameIconDelegate; easing.type: Easing.OutQuad; property: animationFromProperty; from: animationFrom; to: animationTo; duration: animationDuration }
            NumberAnimation{ target: gameIconDelegate; easing.type: Easing.OutQuad; property: "opacity"; from: animationOpacityFrom; to: animationOpacityTo; duration: animationOpacityDuration }
        }
    }

    NumberAnimation{ id: delegateDownAnimation; running: false; easing.type: Easing.OutQuad; target: gameIconDelegate; property: "scale"; from: 1; to: 0.971; duration: 105 }
    NumberAnimation{ id: delegateUpAnimation; running:false; easing.type: Easing.OutQuad; target: gameIconDelegate; property: "scale"; from: 0.971; to: 1; duration: 105 }

    opacity: 0
    scale: 0.94
    smooth: true
    source: imageSource
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: { activeAnimation(false); mouseHover(index); }
        onExited: { activeAnimation(true); noMouseAtItem(); }
        onClicked: mouseClicked(index);
    }
}
