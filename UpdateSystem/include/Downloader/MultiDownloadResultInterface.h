/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_DOWNLOADER_MULTIFILEDOWNLOADRESULTINTERFACE_H_
#define _GGS_UPDATESYSTEM_DOWNLOADER_MULTIFILEDOWNLOADRESULTINTERFACE_H_

#include "DownloadResultInterface.h"

namespace GGS {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT MultiFileDownloadResultInterface
    {
    public:
      ~MultiFileDownloadResultInterface() {};

      virtual void fileDownloaded(const QString& filePath) = 0;
      virtual void downloadResult(bool isError, DownloadResults error) = 0;
      virtual void downloadProgress(quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize) = 0; 
      virtual void downloadWarning(bool isError, DownloadResults error) = 0;
    };
  }
}

#endif // _GGS_UPDATESYSTEM_DOWNLOADER_MULTIFILEDOWNLOADRESULTINTERFACE_H_