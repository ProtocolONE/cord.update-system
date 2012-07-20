/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_DOWNLOAD_MULTIFILEDOWANLOEDERWITHEXTRACTER_H_
#define _GGS_DOWNLOAD_MULTIFILEDOWANLOEDERWITHEXTRACTER_H_

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/MultiFileDownloader.h>
#include <UpdateSystem/Downloader/MultiFileDownloadInterface.h>
#include <UpdateSystem/Downloader/MultiDownloadResultInterface.h>
#include <UpdateSystem/Extractor/ExtractorInterface.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFile>

namespace GGS {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT MultiFileDownloaderWithExtracter : public QObject,
      public MultiFileDownloadInterface,
      public MultiFileDownloadResultInterface
    {
    public:
      explicit MultiFileDownloaderWithExtracter(QObject *parrent = 0);
      virtual ~MultiFileDownloaderWithExtracter();

      virtual void addFile(const QString& url, const QString& targetFilePath);
      virtual void start();

      // MultiFileDownloadResultInterface
      virtual void fileDownloaded(const QString& filePath);
      virtual void downloadResult(bool isError, DownloadResults error);
      virtual void downloadProgress(quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize);
      virtual void downloadWarning(bool isError, DownloadResults error);

      virtual void setResultCallback(MultiFileDownloadResultInterface *resultCallback);
      void setMultiDownloader(MultiFileDownloader *multiDownloader);
      void setExtractor(GGS::Extractor::ExtractorInterface *extractor);

    private:
      MultiFileDownloadResultInterface *_resultCallback;
      MultiFileDownloader *_multiDownloader;
      GGS::Extractor::ExtractorInterface *_extractor;
    };

  }
}

#endif // _GGS_DOWNLOAD_MULTIFILEDOWANLOEDERWITHEXTRACTER_H_