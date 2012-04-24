
import QtQuick 1.0

Rectangle {
    id: buttonT2
    color: "#00000000"
    border.color: "#fff"
    opacity: 0.7
    height: 27
    width: 70

    signal buttonPressed();
    property string buttonText;

    Text {
        id: text1
        x: 24
        y: 7
        text: buttonText
        font.bold: false
        color: "#ffffff"
        font.family: fontTahoma.name
        font.weight: "Light"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 16
    }

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            buttonT2.color = "#006600"
            //buttonT2.opacity = 1
        }
        onExited: {
            buttonT2.color = "transparent"
            //buttonT2.opacity = 0.7
        }
        onClicked: buttonPressed()
    }
}
