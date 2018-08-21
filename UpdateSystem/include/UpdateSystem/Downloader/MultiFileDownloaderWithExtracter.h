#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/MultiFileDownloader.h>
#include <UpdateSystem/Downloader/MultiFileDownloadInterface.h>
#include <UpdateSystem/Downloader/MultiDownloadResultInterface.h>
#include <UpdateSystem/Extractor/ExtractorInterface.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFile>

namespace P1 {
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
      void setExtractor(P1::Extractor::ExtractorInterface *extractor);

    private:
      MultiFileDownloadResultInterface *_resultCallback;
      MultiFileDownloader *_multiDownloader;
      P1::Extractor::ExtractorInterface *_extractor;
    };

  }
}

