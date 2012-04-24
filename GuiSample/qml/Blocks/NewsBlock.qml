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

Rectangle {
    width: 313
    height: 135

    property string filterGameId: "631"
    signal newsReady();

    color: "transparent"

    function reloadNews(){
        console.log("Attempt to reload");
        feedModel.reload();
    }

    XmlListModel {
        id: feedModel
        source: "https://api.gamenet.ru/restapi?method=wall.getNews"
        query: "/response/news/row[gameId=" + filterGameId + "]";

        XmlRole { name: "gameId"; query: "gameId/string()" }
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "announcement"; query: "announcement/string()" }

        onStatusChanged: {
            if (feedModel.status == XmlListModel.Ready && feedModel.get(0))
                newsReady();
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "#296cae" //"#007eff"
        opacity: 0.42 //0.5
    }

    Rectangle{
        height: 1
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.3
        color: "#000000"
    }
    Rectangle{
        height: 1
        anchors.verticalCenterOffset: 1
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.5
        color: "#ffffff"
    }

    ListView {
        visible: true;
        width: parent.width; height: parent.height
        model: feedModel
        clip: true
        interactive: false
        delegate:  Elements.NewsItem{
            width: 313
            height: 67
            newsTextDate: qsTr("24 feb 2012")
            newsTextBody: title;
        }
    }
}
