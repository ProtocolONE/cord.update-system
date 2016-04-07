/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/filedownloaderinterface.h>
#include <UpdateSystem/Downloader/DownloadResultInterface.h>

#include <QtCore/QPointer>
#include <QtCore/QString>
#include <QtCore/QThread>

#include <QtCore/QUrl>
#include <Qtcore/QFile>
#include <QtCore/QDir>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

namespace GGS {
  namespace Downloader {
    class UPDATESYSTEMSHARED_EXPORT DownloadManager : public QObject,
      public FileDownloaderInterface
    {
      Q_OBJECT
    public:
      explicit DownloadManager(QObject *parent = 0);

      virtual ~DownloadManager();
      void downloadFile(const QString& url, const QString& filePath);

    public slots:
      void slotDownloadProgress(qint64 recieved, qint64 total);
      void slotReadyRead();
      void slotReplyDownloadFinished();
      void slotError(QNetworkReply::NetworkError error);
      void setResultCallback(DownloadResultInterface *result);

      virtual QNetworkReply::NetworkError getNetworkError();

    private :
      QNetworkAccessManager *_manager;
      QPointer<QFile> _file;
      QNetworkReply *_reply;
      QString _filePath;
      QByteArray _requestSalt;

      QNetworkReply::NetworkError _networkError;
      DownloadResultInterface *_resultCallback;
      bool _isResultCallbackCalled;
    };
  }
}
#endif // DOWNLOADMANAGER_H
