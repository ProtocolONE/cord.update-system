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
import "../Blocks" as Blocks
import qGNA.Library 1.0

Blocks.LoadScreen{
    id: loadScreen
    property string infoText: loadText
    loadPercent: 0

    updateText: qsTr("Initialization...") + mainWindow.emptyString

    Timer {
        id: changeTextTimer
             interval: 1500; running: false; repeat: false
             onTriggered: {
                     loadScreen.updateText = qsTr("Retry checking for updates...") + mainWindow.emptyString;
             }
    }

    UpdateManagerViewModel{
        id: updateManager
        installPath: "tst"

        onDownloadUpdateProgress: {
            loadPercent = 100 * (currentSize / totalSize);
        }

        onUpdatesFound:{
            changeTextTimer.stop();
            console.log("[DEBUG][QML] Found updates.")
            console.log("[DEBUG][QML] Installing updates.");
            installUpdates();
        }

        onNoUpdatesFound:{
            changeTextTimer.stop();
            console.log("[DEBUG][QML] Updates not found.")
        }

        onDownloadRetryNumber:{
            loadScreen.updateText = qsTr("Retry checking for updates...") + mainWindow.emptyString
            changeTextTimer.start();
        }

        onAllCompleted:{
            changeTextTimer.stop();
		if (isNeedRestart) {
			mainWindow.restartApplication()
		}
            console.log("[DEBUG][QML] Update complete with state " + updateState);

            loadScreen.endAnimationStart = true
        }

        onUpdateStateChanged:{
            changeTextTimer.stop();
            if (updateState == 0)
                loadScreen.updateText = qsTr("Checking for updates...") + mainWindow.emptyString
            else if (updateState == 1){
                loadScreen.updateText = qsTr("Downloading updates...") + mainWindow.emptyString
            }
        }

        onUpdateError:{
            loadPercent = 100;
            changeTextTimer.start();

            if (errorCode > 0 ){
                if (updateState == 0)
                    loadScreen.updateText = qsTr("Error checking for updates...") + mainWindow.emptyString
            }

            switch(errorCode){
                case UpdateInfoGetterResults.NoError: console.log("[DEBUG][QML] Update no error"); break;
                case UpdateInfoGetterResults.DownloadError: console.log("[DEBUG][QML] Update download error"); break;
                case UpdateInfoGetterResults.ExtractError: console.log("[DEBUG][QML] Update extract error"); break;
                case UpdateInfoGetterResults.XmlContentError: console.log("[DEBUG][QML] Update xml content error"); break;
                case UpdateInfoGetterResults.BadArguments: console.log("[DEBUG][QML] Update bad arguments"); break;
                case UpdateInfoGetterResults.CanNotDeleteOldUpdateFiles: console.log("[DEBUG][QML] Update CanNotDeleteOldUpdateFiles"); break;
            }
        }
    }

    Component.onCompleted: {
        console.log("[DEBUG][QML] Updater started")

        updateManager.startCheckUpdate();
    }
}