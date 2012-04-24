
import QtQuick 1.0
import qGNA.Library 1.0
import "." as Blocks
import "../Elements" as Elements

Rectangle {
    width: 800
    height: 400
    color: "transparent"

    property string labelImage
    property int lastGameIndex
    property int currentIndex : qGNA_main.currentGameIndex;
    property int animationType: 0       // 0 - scale back image, 1 - back image move to left, 2 - back image move to right

    property variant backgroundImages: ["../images/bsBackImage.png", "../images/caBackImage.png",
                                        "../images/gna-mw2-large.png", "../images/gna-rot-large.png",
                                        "../images/gna-aika-large.png", "../images/gna-warinc-large.png",
                                        "../images/gaBackImage.png"]

    property variant gameNames: ["Blood and Soul", "Combat Arms", "Magic World 2", "Rage of Titans", "Aika 2", "WarInc", "Golden Age"]
    property variant gameIds: ["71", "15", "84", "72", "631", "70", "83"]
    // 631  - aika, 71 - BS, 72 - ROT, 70 - WarInc, 84 - MW2, 83 - Golden Age, 15 - Combat Arms

    signal finishAnimation();
    signal homeButtonClicked();


    function changeGame(index, imageSource, textSource){
         backgroundImage.source = imageSource;
         labelTextImage.text = textSource;

        if (index < currentIndex){
            backgroundImage.x = -800;
            animationType = 1;
        }
        else{
            backgroundImage.x = 800;
            animationType = 2;
        }

         backgroundImage.scale = 1;
         newsBlock.visible = false;
         labelTextImage.visible = false;
         playButtonId.visible = false;
         playButtonId.progressPercent = -1;
         playButtonId.allreadyDownloaded = false;
         newsBlock.reloadNews();
         switchAnimation.start();
    }

    function gamesButtonClicked(index){
        if (currentIndex == index || switchAnimation.running )
            return;

        lastGameIndex = currentIndex;
        changeGame(index, backgroundImages[index], gameNames[index] );
        currentIndex = index;
    }

    SequentialAnimation{
        id: switchAnimation
        running: true;

        ParallelAnimation{
            NumberAnimation { target: backgroundImage; easing.type: Easing.OutQuad;
                                property: animationType == 0 ? "scale" : "x";
                                from: animationType == 0 ? 0.7 : animationType == 1 ? -800 : 800;
                                to: animationType == 0 ? 1 : 0;
                                duration: 150 }

            NumberAnimation {   target: backgroundImage2;
                                property: "x";
                                from: 0
                                to: animationType == 1 ?  800 : -800;
                                duration: 150 }

            SequentialAnimation{
                PauseAnimation { duration: 25 }
                NumberAnimation { target: popupGamesMenu; easing.type: Easing.OutQuad; property: "anchors.bottomMargin"; from: -133; to: 0; duration: 1 }
            }

            SequentialAnimation{
                PauseAnimation { duration: 250 }
                PropertyAnimation { target: labelTextImage; easing.type: Easing.OutQuad; property: "visible"; to: true; }
                NumberAnimation { target: labelTextImage; easing.type: Easing.OutQuad; property: "anchors.leftMargin"; from: -300; to: 32; duration: 200 }
            }

            SequentialAnimation{
                PauseAnimation { duration: 500 }
                PropertyAnimation { target: playButtonId; easing.type: Easing.OutQuad; property: "visible"; to: true; }
                NumberAnimation{ target: playButtonId; easing.type: Easing.OutQuad; property: "anchors.rightMargin"; from: -200; to: 20; duration: 200 }
            }
        }
    }

   Image{
       id: backgroundImage
       source: backgroundImages[currentIndex]
       scale: 0.7
   }

   Image{
       id: backgroundImage2
       source: backgroundImages[lastGameIndex]
       scale: 1
       visible: animationType > 0
   }

   Image{
       id: rightArrowImage
       source: "../images/rightArrow.png"
       opacity: 0.5
       visible: true

       anchors.top: parent.top
       anchors.topMargin: 150
       anchors.right: parent.right
       anchors.rightMargin: 10

       MouseArea{
           anchors.fill: parent
           hoverEnabled: true
           onEntered: rightArrowImage.opacity = 1;
           onExited: rightArrowImage.opacity = 0.5;
           onClicked: {
               if (currentIndex == gameNames.length-1)
                   gamesButtonClicked(0);
               else
                   gamesButtonClicked(currentIndex+1);
           }
       }
       CursorShapeArea {
         anchors.fill: parent
         cursorShape: Qt.PointingHandCursor
       }
   }

   Text{
       id: labelTextImage
       anchors.top: parent.top
       anchors.topMargin: 19
       anchors.left: parent.left
       visible: false
       text: gameNames[currentIndex]

       font.family: "Segoe UI Light"
       font.bold: false
       font.pixelSize: 46
       opacity: 1
       smooth: true

       color: "white"
   }

   Blocks.NewsBlock{
       id: newsBlock
       anchors.top: parent.top
       anchors.topMargin: 108
       anchors.left: parent.left
       anchors.leftMargin: 31
       visible: false
       filterGameId: gameIds[currentIndex]

       SequentialAnimation{
           id: newsAnimation
           PauseAnimation { duration: 350 }
              PropertyAnimation { target: newsBlock; easing.type: Easing.OutQuad; property: "visible"; to: true; }
              NumberAnimation{ target: newsBlock; easing.type: Easing.OutQuad; property: "anchors.leftMargin"; from: -350; to: 31; duration: 200 }
       }

       onNewsReady: {
           newsAnimation.start();
       }
   }

    Blocks.PopupGamesMenu{
        id: popupGamesMenu
        height: 133
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        onHomeClicked: homeButtonClicked();
    }


    Blocks.MiniGamesView{
        id: miniGamesListView
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        onItemClicked: gamesButtonClicked(index);

        visible: qGNA_main.isPageControlAccepted
    }

    Elements.ButtonBig{
        id: playButtonId
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 65
        anchors.right: parent.right
        anchors.rightMargin: 34
        visible: false

        buttonText: qsTr("Download") + mainWindow.emptyString
        buttonDownloadedText: qsTr("Play") + mainWindow.emptyString

        isMouseAreaAccepted: qGNA_main.isPageControlAccepted
    }

    Text{
        id: gameDownloadInfoText
        text: playButtonId.progressPercent >= 0 && playButtonId.progressPercent < 100 ? qsTr("Download game: ") + playButtonId.progressPercent + " " + qsTr("of 100 Mb...") + mainWindow.emptyString : qsTr("The game is ready for start") + mainWindow.emptyString;
        anchors.left: parent.left
        anchors.leftMargin: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 80
        font.family: "Tahoma"
        font.bold: false
        font.pixelSize: 24
        font.weight: "Light"
        color: playButtonId.progressPercent >= 0 && playButtonId.progressPercent < 100 ? "#ffb900" : "#33cc00"
        opacity: 1
        smooth: true
        visible: playButtonId.progressPercent >= 0
    }
}
