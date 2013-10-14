/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once

#include "UpdateSystem_global.h"
#include "UpdateInfoContainer.h"

namespace GGS { 
  namespace UpdateSystem {

    enum UpdateInfoGetterResults {
      NoError = 0,
      DownloadError = 1,
      ExtractError = 2,
      XmlContentError = 3,
      BadArguments = 4,
      CanNotDeleteOldUpdateFiles = 5,
      NotEnoughSpace = 6
    };

    class UPDATESYSTEMSHARED_EXPORT UpdateInfoGetterResultsWrapper 
      : public QObject
    {
      Q_OBJECT
        Q_ENUMS(UpdateInfoGetterResultsEnum)
    public:
      enum UpdateInfoGetterResultsEnum {
        NoError = 0,
        DownloadError = 1,
        ExtractError = 2,
        XmlContentError = 3,
        BadArguments = 4,
        CanNotDeleteOldUpdateFiles = 5,
        NotEnoughSpace = 6
      };
    };

    class UPDATESYSTEMSHARED_EXPORT UpdateInfoGetterResultInterface {
    public:
      virtual ~UpdateInfoGetterResultInterface() {};
      virtual void updateInfoCallback(UpdateInfoGetterResults error) = 0;
      virtual void infoGetterUpdateProggress(quint64 current, quint64 total) = 0;
    };
  }
}