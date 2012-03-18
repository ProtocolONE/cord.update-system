/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_DOWNLOADER_RETRY_FILEDOWNLOADER_H_
#define _GGS_UPDATESYSTEM_DOWNLOADER_RETRY_FILEDOWNLOADER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include "UpdateSystem_global.h"
#include "Downloader/filedownloaderinterface.h"
#include "Downloader/DownloadResultInterface.h"
#include "Downloader/RetryTimeoutInterface.h"

namespace GGS {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT RetryFileDownloader :
      public QObject,
      public FileDownloaderInterface,
      public DownloadResultInterface
    {
      Q_OBJECT
    public:
      explicit RetryFileDownloader(QObject *parrent = 0);
      virtual ~RetryFileDownloader(void);

      // FileDownloaderInterface
      virtual void setResultCallback( DownloadResultInterface *result ) { this->_resultCallback = result; }
      virtual void downloadFile( const QString& url, const QString& filePath );

      // DownloadResultInterface
      virtual void downloadResult( bool isError, DownloadResults error );
      virtual void downloadWarning( bool isError, DownloadResults error );
      virtual void downloadProgress( quint64 current, quint64 total );

      void setDownloader(FileDownloaderInterface *downloader) { this->_downloader = downloader; }
      void setTimeout(RetryTimeoutInterface *timeout) { this->_timeout = timeout; }
      void setMaxRetry(qint32 maxRetryCount) { this->_maxRetryCount = maxRetryCount; }
      virtual QNetworkReply::NetworkError getNetworkError() { return this->_networkError; };

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

#endif // _GGS_UPDATESYSTEM_DOWNLOADER_RETRY_FILEDOWNLOADER_H_