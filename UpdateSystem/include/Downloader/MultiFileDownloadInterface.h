/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_DOWNLOAD_MULTIFILEDOWNLOADINTERFACE_H_
#define _GGS_DOWNLOAD_MULTIFILEDOWNLOADINTERFACE_H_

#include <QtCore/QString>
#include "Downloader/MultiDownloadResultInterface.h"
namespace GGS {
  namespace Downloader {

    class MultiFileDownloadInterface {
    public:
      ~MultiFileDownloadInterface() {}
      virtual void setResultCallback(MultiFileDownloadResultInterface *resultCallback) = 0;
      virtual void addFile(const QString& url, const QString& targetFilePath) = 0;
      virtual void start() = 0;
    };

  }
}
#endif // _GGS_DOWNLOAD_MULTIFILEDOWNLOADINTERFACE_H_