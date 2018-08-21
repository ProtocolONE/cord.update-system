#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/DownloadInMemoryInterface.h>

#include <QtCore/QSharedPointer>
#include <QtCore/QObject>
#include <QtCore/QByteArray>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace P1 {
  namespace Downloader {
    class UPDATESYSTEMSHARED_EXPORT MemoryDownloader : public QObject,
      public DownloadInMemoryInterface
    {
      Q_OBJECT
    public:
      explicit MemoryDownloader(QObject *parent = 0);
      virtual ~MemoryDownloader(void);

      virtual void DownloadUrl( const QString& url, QByteArray *responseBuffer  );

    public slots:
      void slotReadyRead();
      void slotReplayDownloadFinished();
      void slotError(QNetworkReply::NetworkError error);

    signals:
      void downloadComplited();
      void downloadError(QNetworkReply::NetworkError error);
      void downloadProgress(qint64 recieved, qint64 total);

    private:
      QNetworkAccessManager *manager;
      QString url;
      QNetworkReply *reply;
      
      QByteArray *response;
    };
  }
}

