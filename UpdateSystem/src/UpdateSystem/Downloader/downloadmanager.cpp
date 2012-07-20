/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Downloader/downloadmanager.h>

namespace GGS {
  namespace Downloader {
    void DownloadManager::downloadFile(const QString &url, const QString &filePath)
    {
      if(!this->_resultCallback) {
        throw new std::exception("can't download file without result callback");
      }

      QUrl uri(url);
      if(!uri.isValid())
      {
        this->_resultCallback->downloadResult(true, BadUrl);
        return;
      }

      QString cleanPath = QDir::cleanPath(filePath);
      int lastIndex = cleanPath.lastIndexOf('/');
      if(lastIndex != -1) {
        QString targetDirectory = cleanPath.mid(0, lastIndex + 1);
        QDir targetPath(cleanPath);
        if(!targetPath.exists(targetDirectory)) {
          targetPath.mkpath(targetDirectory);
        }
      }

      this->_file = new QFile(cleanPath);
      if(!this->_file->open(QIODevice::WriteOnly)) {
        delete this->_file;
        this->_resultCallback->downloadResult(true, CanNotOpenTargetFile);
        return;
      }

      this->_isResultCallbackCalled = false;
      this->_networkError = QNetworkReply::NoError;
      this->_reply = this->_manager->get(QNetworkRequest(uri));

      connect(this->_reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
      connect(this->_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(slotDownloadProgress(qint64,qint64)));
      connect(this->_reply, SIGNAL(finished()), this, SLOT(slotReplyDownloadFinished()));
      connect(this->_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    }

    void DownloadManager::slotDownloadProgress(qint64 recieved, qint64 total)
    {
      this->_resultCallback->downloadProgress(recieved, total);
    }

    void DownloadManager::slotReadyRead()
    {
      QNetworkReply *reply2 = qobject_cast<QNetworkReply *>(QObject::sender());
      if (reply2) {
        QVariant statusCodeV = reply2->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCodeV == 200) {
          if(this->_file) {
            this->_file->write(this->_reply->readAll());
          }
        }
      }
    }

    void DownloadManager::slotReplyDownloadFinished()
    {
      if (this->_file) {
        this->_file->close();
        delete this->_file;        
      }

      QVariant statusCodeV;
      QNetworkReply *reply2 = qobject_cast<QNetworkReply *>(QObject::sender());
      if (reply2) {
        statusCodeV = reply2->attribute(QNetworkRequest::HttpStatusCodeAttribute);
      }

      this->_reply->deleteLater();

      if (!this->_isResultCallbackCalled) {
        this->_isResultCallbackCalled = true;
        if(statusCodeV == 200)
          this->_resultCallback->downloadResult(false, NoError);
        else
          this->_resultCallback->downloadResult(true, NetworkErrok);
      }
    }

    DownloadManager::~DownloadManager() 
    {
    }

    DownloadManager::DownloadManager( QObject *parent )
      : QObject(parent)
    {
      this->_resultCallback = 0;
      this->_reply = 0;
      this->_manager = new QNetworkAccessManager(this);
    }

    void DownloadManager::slotError( QNetworkReply::NetworkError error )
    {
      if (this->_file) {
        this->_file->close();
        delete this->_file;
      }

      this->_networkError = error;
      if (!this->_isResultCallbackCalled) {
        this->_isResultCallbackCalled = true;
        this->_resultCallback->downloadResult(true, NetworkErrok);
      }

      this->_reply->deleteLater();
    }

    void DownloadManager::setResultCallback( DownloadResultInterface *result )
    {
      this->_resultCallback = result;
    }

  }
}