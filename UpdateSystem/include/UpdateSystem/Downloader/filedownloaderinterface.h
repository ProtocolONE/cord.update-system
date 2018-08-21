#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/DownloadResultInterface.h>

#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>

namespace P1 {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT FileDownloaderInterface
    {
    public:
      virtual ~FileDownloaderInterface() {};

      virtual void setResultCallback(DownloadResultInterface *result) = 0;
      virtual void downloadFile(const QString& url,const QString& filePath) = 0;

      virtual QNetworkReply::NetworkError getNetworkError() = 0;

    };

  }
}

