/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef FILEDOWNLOADERINTERFACE_H
#define FILEDOWNLOADERINTERFACE_H

#include "UpdateSystem_global.h"
#include "Downloader/DownloadResultInterface.h"
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>

namespace GGS {
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
#endif // FILEDOWNLOADERINTERFACE_H
