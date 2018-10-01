#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/filedownloaderinterface.h>
#include <UpdateSystem/Downloader/MultiFileDownloadInterface.h>
#include <UpdateSystem/Downloader/MultiDownloadResultInterface.h>

#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QDir>

namespace P1 {
  namespace Downloader {
    class UPDATESYSTEMSHARED_EXPORT MultiFileDownloader :
      public QObject,
      public DownloadResultInterface,
      public MultiFileDownloadInterface
    {
      Q_OBJECT
    public:
      explicit MultiFileDownloader(QObject *parrent = 0);
      virtual ~MultiFileDownloader();

      void setDownloader(FileDownloaderInterface *downloader);

      //MultiFileDownloadInterface
      void setResultCallback(MultiFileDownloadResultInterface *resultCallback);
      void addFile(const QString& url, const QString& targetFilePath);
      void start();

      // DownloadResultInterface
      virtual void downloadResult( bool isError, DownloadResults error );
      virtual void downloadProgress( quint64 current, quint64 total );
      virtual void downloadWarning( bool isError, DownloadResults error );

    private:
      void processNextFile();

      quint64 _complitedFileSized;
      quint64 _currentFileProgres;

      // UNDONE: �������� � �� �����
      quint64 _currentFileTotalSize;
      QPair<QString,QString> _currentFile;

      FileDownloaderInterface *_downloader;
      MultiFileDownloadResultInterface *_resultCallback;

      QNetworkReply::NetworkError _networkError;
      QQueue< QPair<QString,QString> > _fileQueue;
    };
  }
}
