/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_DOWNLOAD_IN_MEMORY_INTERFACE_H_
#define _GGS_UPDATESYSTEM_DOWNLOAD_IN_MEMORY_INTERFACE_H_

#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>

namespace GGS {
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
#endif // _GGS_UPDATESYSTEM_DOWNLOAD_IN_MEMORY_INTERFACE_H_