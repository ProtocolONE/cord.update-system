#pragma once

#include "UpdateSystem_global.h"
#include "UpdateInfoContainer.h"

namespace P1 { 
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