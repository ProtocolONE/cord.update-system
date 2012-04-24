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
import "." as Blocks

Item{
    id: authModule

    state: "Normal"

    property int openHeight: 292
    property bool isAuthMenuOpen: (authRectangleBlock.height == openHeight)
    property bool isAuthorized: false
    property bool firstClick: false

    signal openAnimationFinished()
    signal closeAnimationStart()
    signal settingsButtonClicked();

    Keys.onPressed: {
        if (event.key == Qt.Key_Escape && isAuthMenuOpen){
            switchAnimation();
            event.accepted = true;
        }
    }

    Component.onCompleted: {
        authManager.autoLogin();
        console.log("[DEBUG][QML] authManager autoLogin called.");
        loginTextInput.focus = true;
    }

    AuthManagerViewModel {
        id: authManager
        objectName: "authManager"

        accountName: loginTextInput.editText
        password: passwordTextInput.editText
        autoSaveAuth: rememberCheckBox.isChecked

        onAuthSuccess:{
            console.log("[AUTH] Success, userId " + authManager.userId);
            if (firstClick)
                switchAnimation();
            authOpenButtonAnimation.start();
            isAuthorized = true;
            mainWindow.authSuccessSlot(authManager.userId, authManager.appKey, authManager.cookie);

            mainWindow.refreshBalance();
            balanceTimer.start();
        }

        onAuthError:{
            balanceTimer.stop();
            console.log("[DEBUG][QML] Error " + resultCode);
            authGoError.start();
        }

        Timer {
            id: balanceTimer
            interval: 60000
            running: false
            repeat: true
            onTriggered: mainWindow.refreshBalance();
        }
    }

    SequentialAnimation{
        id: authOpenBlockAnimation;
        ParallelAnimation{
            NumberAnimation {  target: authRectangleBlock; property: "height"; easing.type: Easing.InQuad; from: 0; to: openHeight; duration: 350;   }
            NumberAnimation { target: authModuleSubstateId; property: "opacity"; from: 0; to: 0.5; duration: 350; }
        }
        onCompleted: openAnimationFinished();
    }

    SequentialAnimation{
        id: authCloseBlockAnimation;
        ParallelAnimation{
            NumberAnimation {  target: authRectangleBlock; property: "height"; easing.type: Easing.InQuad; from: openHeight; to: 0; duration: 350; }
            NumberAnimation { target: authModuleSubstateId; property: "opacity"; from: 0.5; to: 0; duration: 350; }
        }
        onStarted: closeAnimationStart();
    }

    SequentialAnimation{
        id: authOpenButtonAnimation
        NumberAnimation { target: loginButtonRectangle; easing.type: Easing.OutQuad; property: "anchors.topMargin"; from: 35; to: -58; duration: 120; }
        ParallelAnimation{
            NumberAnimation { target: nickNameView; easing.type: Easing.OutQuad; property: "anchors.rightMargin"; from: -nickNameView.width; to: 20; duration: 200; }
            NumberAnimation { target: nickNameView; easing.type: Easing.OutQuad; property: "opacity"; from: 0; to: 1; duration: 150; }

        }
    }
    SequentialAnimation{
        id: authCloseButtonAnimation
        ParallelAnimation{
            NumberAnimation { target: nickNameView; easing.type: Easing.OutQuad; property: "anchors.rightMargin"; from: 20; to: -nickNameView.width; duration: 200; }
            NumberAnimation { target: nickNameView; easing.type: Easing.OutQuad; property: "opacity"; from: 1; to: 0; duration: 150; }

        }
        NumberAnimation { target: loginButtonRectangle; easing.type: Easing.OutQuad; property: "anchors.topMargin"; from: -58; to: 35; duration: 120; }
    }

    function testAndCloseNickNameView(){
        if (nickNameView.isMenuOpen)
            nickNameView.switchMenu();
    }

    function authSlot(){
        if (!authOpenButtonAnimation.running && !isAuthorized){
            authManager.login("generic");
            console.log("[DEBUG][QML] Attempt to generic auth.");
        }
    }

    function deauthSlot(){
        if (!authCloseButtonAnimation.running && isAuthorized){
            authCloseButtonAnimation.start();
            isAuthorized = false;
         //   loginTextInput.clear();
            passwordTextInput.clear();
            mainWindow.logout();
            authManager.logout();

            if (qGNA_main.state == "SettingsPage"){
                qGNA_main.lastState = "HomePage"
                qGNA_main.state = "HomePage"
            }
            console.log("[QML] deauth user.")
        }
    }
    function switchAnimation(){
        if (authRectangleBlock.height == openHeight )
            authCloseBlockAnimation.start();
        else if (!authCloseBlockAnimation.running)
            authOpenBlockAnimation.start();
    }

    Blocks.NickNameView{
        id: nickNameView
        anchors.top: parent.top
        anchors.topMargin: 35
        anchors.right: parent.right
        anchors.rightMargin: 20
        opacity: 0
        upText: mainWindow.nickName
        downText: mainWindow.balance + " рублей"
        avatarSource: mainWindow.smallAvatarUrl

        onQuitClicked: {
            deauthSlot();
        }
        onSettingsClicked: {
            switchMenu();
            settingsButtonClicked();
        }
        onMoneyClicked: {
            mainWindow.openExternalBrowser("http://www.gamenet.ru/money");
        }

        Component.onCompleted: {
            console.log("[DEBUG][QML] Avatar url - " + mainWindow.smallAvatarUrl );
        }
    }

    Elements.LoginButton{
        id: loginButtonRectangle
        enabled: !isAuthMenuOpen
        buttonText: qsTr("Login") + mainWindow.emptyString;
        onMouseCLicked: {
            if (!isAuthMenuOpen){
                firstClick = true;
                switchAnimation();
            }
        }
    }
    Rectangle{
        id: authModuleSubstateId
        anchors.fill: parent
        color: "#000000"
        opacity: 0
    }
    Rectangle{
        id: authRectangleBlock
        height: 0
        color: "#329800"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        SequentialAnimation {
            id: authGoShow
            PropertyAnimation { target: authError; easing.type: Easing.InCubic; property: "opacity"; to: 0; duration: 200 }
            ScriptAction {
                script: {
                    authModule.state = "Normal";
                }
            }
            PropertyAnimation { target: authBody; easing.type: Easing.InCubic; property: "opacity"; to: 1; duration: 200 }
        }

        SequentialAnimation {
            id: authGoError
            PropertyAnimation { target: authBody; easing.type: Easing.InCubic; property: "opacity"; to: 0; duration: 200 }
            ScriptAction {
                script: {
                    authModule.state = "LoginFailed";
                }
            }
            PropertyAnimation { target: authError; easing.type: Easing.InCubic; property: "opacity"; to: 1; duration: 200 }
        }

        Item{
            id: authErrorBlock
            anchors.fill: parent
            visible: true

            Keys.onPressed: {
                if (event.key == Qt.Key_Return  || event.key == Qt.Key_Enter){
                    if (authModule.state == "LoginFailed"){
                        authGoShow.start();
                        event.accepted = true;
                    }
                }
            }

            Item {
                id: authError
                width: 275
                anchors {left: parent.left; leftMargin: 275; top: parent.top; topMargin: 30}
                visible: true

                Text {
                    id: authErrorText
                    //width: 280
                    color: "#ffff66"
                    text: qsTr("You entered the wrong username or password.\nPlease try again.") + mainWindow.emptyString
                    anchors {top: parent.top; topMargin: 0; left: parent.left; leftMargin: 0}
                    wrapMode: Text.WordWrap
                    font {family: "Tahoma"; pointSize: 13; bold: false }
                }

                Elements.Button{
                    id: forgotPasswordOKbutton
                    buttonText: qsTr("OK") + mainWindow.emptyString
                    width: 68
                    focus: true
                    anchors {top: parent.top; topMargin: 50; left: parent.left; leftMargin: 0}

                    onButtonPressed:{
                        authGoShow.start();
                    }
                }

                Text {
                    id: forgotPassword
                    color: "#fff"
                    text: qsTr("Forgot your password") + mainWindow.emptyString
                    font.underline: true
                    anchors {top: parent.top; topMargin: 92; left: parent.left; leftMargin: 0}
                    wrapMode: Text.NoWrap
                  //  font {family: "Arial"; pointSize: 12}
                    font.family: "Segoe UI Semibold"
                    font.bold: false
                    font.pixelSize: 14
                    font.weight: "Normal"
                    smooth: true
                    opacity: 0.7

                    NumberAnimation { id: opacityUp; target: forgotPassword; property: "opacity"; from: 0.7; to: 1.0; duration: 200 }
                    NumberAnimation { id: opacityDown; target: forgotPassword; property: "opacity"; from: 1; to: 0.7; duration: 200 }

                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            opacityUp.start();
                        }
                        onExited: {
                            opacityDown.start();
                        }
                        onClicked: {
                            mainWindow.openExternalBrowser("http://www.gamenet.ru/restore");
                        }
                    }

                    CursorShapeArea {
                      anchors.fill: parent
                      cursorShape: Qt.PointingHandCursor
                    }
                }
            }
        }

        Rectangle{
            id: authBody
            anchors.fill: parent
            color: "transparent"
            visible: false

            Rectangle{
                height: 1
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                color: "#65b23f"
            }

            Rectangle{
                x: 319
                width: 208
                height: 28
                anchors.horizontalCenterOffset: 20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 30

                Elements.Input{
                    id: loginTextInput
                    anchors.fill: parent
                    textEchoMode: TextInput.Normal
                    editDefaultText: qsTr("login") + mainWindow.emptyString
                    onEnterPressed: authSlot();
                    focus: true
                    onTabPressed: {
                        if (isAuthMenuOpen){
                            loginTextInput.editFocus = false;
                            passwordTextInput.editFocus = true;
                        }
                    }
                }
            }

            Rectangle{
                x: 319
                width: 208
                height: 28
                anchors.horizontalCenterOffset: 20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 68

                Elements.Input{
                    id: passwordTextInput
                    anchors.fill: parent
                    textEchoMode: TextInput.Password
                    editDefaultText: qsTr("password") + mainWindow.emptyString
                    onEnterPressed: authSlot();
                    onTabPressed: {
                        if (isAuthMenuOpen){
                            loginTextInput.editFocus = true;
                            passwordTextInput.editFocus = false;
                        }
                    }
                }
            }

            Text {
                id: authText
                width: 220
                color: "#ffffff"
                text: qsTr("Enter your username, password and press enter, or authorize your account using VKontakte") + mainWindow.emptyString
                anchors {top: parent.top; topMargin: 26; left: parent.left; leftMargin: 40}
                wrapMode: Text.WordWrap
                font {family: "Arial"; pointSize: 12}
            }

            Text {
                id: registrationButton
                color: "#fff"
                text: qsTr("Registration") + mainWindow.emptyString
                font.underline: true
                anchors {top: parent.top; topMargin: 26; left: parent.left; leftMargin: 565}
                wrapMode: Text.NoWrap
                opacity: 0.85
                font {family: "Arial"; pointSize: 14}

                NumberAnimation { id: regButtonOpacityUp; target: registrationButton; property: "opacity"; from: 0.85; to: 1.0; duration: 200 }
                NumberAnimation { id: regButtonOpacityDown; target: registrationButton; property: "opacity"; from: 1.0; to: 0.85; duration: 200 }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        mainWindow.openExternalBrowser("http://www.gamenet.ru/register");
                    }
                    onEntered: regButtonOpacityUp.start();
                    onExited: regButtonOpacityDown.start();
                }

                CursorShapeArea {
                  anchors.fill: parent
                  cursorShape: Qt.PointingHandCursor
                }
            }

            Elements.CheckBox{
                id: rememberCheckBox
                x: 316
                y: 104
                buttonText: qsTr("Remember me") + mainWindow.emptyString
            }

            Elements.Button{
                x: 316
                y: 135
                buttonText: qsTr("Login") + mainWindow.emptyString
                onButtonPressed: authSlot();
            }

            Elements.ButtonVk{
                anchors {top: parent.top; topMargin: 65; left: parent.left; leftMargin: 565}
                buttonText: qsTr("Vk login") + mainWindow.emptyString
                onButtonPressed: authManager.login("vkontakte");
            }

            Elements.ButtonCancel{
                x: 400
                y: 135
                buttonText: qsTr("Cancel") + mainWindow.emptyString
                onButtonPressed: switchAnimation();
            }
        }

    }

    states: [
        State {
            name: "Normal"
            PropertyChanges { target: authErrorBlock; visible: false }
            PropertyChanges { target: authErrorBlock; focus: false }
            PropertyChanges { target: authBody; visible: true }
            PropertyChanges { target: loginTextInput; editFocus: true }
            PropertyChanges { target: passwordTextInput; editFocus: false }
        },
        State {
            name: "LoginFailed"
            PropertyChanges { target: authErrorBlock; visible: true }
            PropertyChanges { target: authErrorBlock; focus: true }
            PropertyChanges { target: authBody; visible: false }
        }
    ]

}

