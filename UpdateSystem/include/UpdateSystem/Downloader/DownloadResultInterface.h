#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <QtNetwork/QNetworkReply>

namespace P1 {
  namespace Downloader {
    enum DownloadResults {
      NoError = 0,
      BadUrl = 1,
      CanNotOpenTargetFile = 2,
      NetworkErrok = 3,
      ExtractionError = 4,
    };

    class UPDATESYSTEMSHARED_EXPORT DownloadResultsWrapper 
      : public QObject
    {
      Q_OBJECT
        Q_ENUMS(DownloadResultsEnum)
    public:
      enum DownloadResultsEnum {
        NoError = 0,
        BadUrl = 1,
        CanNotOpenTargetFile = 2,
        NetworkErrok = 3,
        ExtractionError = 4,
      };
    };

    class UPDATESYSTEMSHARED_EXPORT DownloadResultInterface 
    {
    public:
      virtual ~DownloadResultInterface() {};
      virtual void downloadResult(bool isError, DownloadResults error) = 0;
      virtual void downloadProgress(quint64 current, quint64 total) = 0; 
      virtual void downloadWarning(bool isError, DownloadResults error) = 0;
    };
  }
}
