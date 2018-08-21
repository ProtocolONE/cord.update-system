#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/filedownloaderinterface.h>
#include <UpdateSystem/Downloader/DownloadResultInterface.h>
#include <UpdateSystem/Downloader/RetryTimeoutInterface.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>

namespace P1 {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT RetryFileDownloader :
      public QObject,
      public FileDownloaderInterface,
      public DownloadResultInterface
    {
      Q_OBJECT
    public:
      explicit RetryFileDownloader(QObject *parrent = 0);
      virtual ~RetryFileDownloader();

      // FileDownloaderInterface
      virtual void setResultCallback(DownloadResultInterface *result);
      virtual void downloadFile(const QString& url, const QString& filePath);

      // DownloadResultInterface
      virtual void downloadResult(bool isError, DownloadResults error);
      virtual void downloadWarning(bool isError, DownloadResults error);
      virtual void downloadProgress(quint64 current, quint64 total);

      void setDownloader(FileDownloaderInterface *downloader);
      void setTimeout(RetryTimeoutInterface *timeout);
      void setMaxRetry(qint32 maxRetryCount);
      virtual QNetworkReply::NetworkError getNetworkError();;

    private slots:
      void internalStartDownload();

    signals:
      void downloadRetryNumber(int retryNumber);

    private:
      FileDownloaderInterface *_downloader;
      DownloadResultInterface *_resultCallback;
      RetryTimeoutInterface *_timeout;

      QNetworkReply::NetworkError _networkError;

      qint32 _maxRetryCount;
      qint32 _retryCount;

      QString _url;
      QString _filePath;
    };

  }
}

