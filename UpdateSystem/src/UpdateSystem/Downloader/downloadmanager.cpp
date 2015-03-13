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

#include <QtCore/QDateTime>
#include <QtCore/QUrlQuery>

namespace GGS {
  namespace Downloader {

    DownloadManager::~DownloadManager() 
    {
    }

    DownloadManager::DownloadManager(QObject *parent)
      : QObject(parent)
      , _resultCallback(0)
      , _reply(0)
      , _manager(new QNetworkAccessManager(this))
    {
    }

    void DownloadManager::downloadFile(const QString &url, const QString &filePath)
    {
      if (!this->_resultCallback) {
        throw new std::exception("can't download file without result callback");
      }

      QUrl uri(url);
      if(!uri.isValid()) {
        this->_resultCallback->downloadResult(true, BadUrl);
        return;
      }

      QUrlQuery query(uri);
      query.addQueryItem(QString::number(qrand()), QString::number(QDateTime::currentMSecsSinceEpoch()));
      uri.setQuery(query);
      
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

      QObject::connect(this->_reply, &QNetworkReply::readyRead, this, &DownloadManager::slotReadyRead);
      QObject::connect(this->_reply, &QNetworkReply::downloadProgress, this, &DownloadManager::slotDownloadProgress);
      QObject::connect(this->_reply, &QNetworkReply::finished, this, &DownloadManager::slotReplyDownloadFinished);
      QObject::connect(
        this->_reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), 
        this, &DownloadManager::slotError);
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

    void DownloadManager::slotError(QNetworkReply::NetworkError error)
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

    void DownloadManager::setResultCallback(DownloadResultInterface *result)
    {
      this->_resultCallback = result;
    }

    QNetworkReply::NetworkError DownloadManager::getNetworkError()
    {
      return this->_networkError;
    }

  }
}