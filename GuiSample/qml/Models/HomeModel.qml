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

Blocks.Home {
    id: homeModel

    onMouseItemClicked: {
        homeModel.closeAnimationStart();
        mainAuthModule.testAndCloseNickNameView();
        qGNA_main.currentGameIndex = homeModel.currentIndex;
        qGNA_main.state = "GamesSwitchPage";
    }
}
