#pragma once

#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>

namespace P1 {
  namespace Downloader {
    class DownloadInMemoryInterface 
    {
    public :
      virtual ~DownloadInMemoryInterface() {};
      virtual void DownloadUrl(const QString& url, QByteArray *responseBuffer ) = 0;

      virtual void downloadComplited() = 0;
      virtual void downloadError(QNetworkReply::NetworkError error) = 0;
    };
  }
}
