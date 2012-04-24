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
import "../Delegates" as Delegates

ListView {
    height: 46
    anchors.horizontalCenterOffset: 0
    interactive: false
    contentHeight: 46
    highlightFollowsCurrentItem: true
    width: 48*7

    signal itemClicked(int index);

    orientation: ListView.Horizontal

    spacing: 5

    delegate: Delegates.GameIconDelegate{
       normalScale: 0.985
       activeScale: 1.1
       isAnimationStart: true
       animationFromProperty: "y"

       imageSmooth: true
       imgSource: imageSource

       onMouseClicked: itemClicked(num);
    }

    model: ListModel{
        ListElement {
            imageSource: "../images/bs_icon_small.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }
        ListElement {
            imageSource: "../images/ca_icon_mini.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }
        ListElement {
            imageSource: "../images/mw_icon_mini.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }
        ListElement {
            imageSource: "../images/rot_icon_mini.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }

        ListElement {
            imageSource: "../images/aika_icon_mini.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }
        ListElement {
            imageSource: "../images/wi_icon_mini.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }
        ListElement {
            imageSource: "../images/ga_icon_mini.png"
            animationPause: 0
            animationFrom: 150
            animationTo: 0
            animationDuration: 1
            animationOpacityFrom: 0.1
            animationOpacityTo: 1
            animationOpacityDuration: 400
        }
    }
}
