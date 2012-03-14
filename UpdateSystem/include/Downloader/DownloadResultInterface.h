/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_DOWNLOAD_RESULT_INTERFACE_H_
#define _GGS_DOWNLOAD_RESULT_INTERFACE_H_

#include "UpdateSystem_global.h"
#include <QtNetwork/QNetworkReply>
namespace GGS {
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
#endif // _GGS_DOWNLOAD_RESULT_INTERFACE_H_