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
#include <UpdateSystem/Hasher/Md5FileHasher>

#include <QtCore/QDateTime>
#include <QtCore/QUrlQuery>
#include <QtCore/QUuid>
#include <QtCore/QCryptographicHash>

#include <QtNetwork/QSslError>

namespace GGS {
  namespace Downloader {
    using GGS::Hasher::Md5FileHasher;

    const QByteArray salt("uvG4A1CG2FiDBATvVIyQukWVPq70nVbL");

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
      
      this->_filePath = QDir::cleanPath(filePath);
      
      int lastIndex = this->_filePath.lastIndexOf('/');
      if(lastIndex != -1) {
        QString targetDirectory = this->_filePath.mid(0, lastIndex + 1);
        QDir targetPath(this->_filePath);
        if(!targetPath.exists(targetDirectory)) {
          targetPath.mkpath(targetDirectory);
        }
      }

      this->_file = new QFile(this->_filePath);
      if(!this->_file->open(QIODevice::WriteOnly)) {
        delete this->_file;
        this->_resultCallback->downloadResult(true, CanNotOpenTargetFile);
        return;
      }
            
      this->_isResultCallbackCalled = false;
      this->_networkError = QNetworkReply::NoError;

      QNetworkRequest request(uri);
      if (uri.scheme() == "https") {
        this->_requestSalt = QCryptographicHash::hash(QUuid::createUuid().toByteArray(), QCryptographicHash::Md5).toHex();
        request.setRawHeader("Content-MD5", this->_requestSalt.toBase64());
      } else {
        this->_requestSalt.clear();
      }
      
      QList<QSslError> expectedSslErrors;
      expectedSslErrors.append(QSslError(QSslError::CertificateExpired));

      this->_reply = this->_manager->get(request);
      this->_reply->ignoreSslErrors(expectedSslErrors);

      connect(this->_reply, &QNetworkReply::readyRead, this, &DownloadManager::slotReadyRead);
      connect(this->_reply, &QNetworkReply::downloadProgress, this, &DownloadManager::slotDownloadProgress);
      connect(this->_reply, &QNetworkReply::finished, this, &DownloadManager::slotReplyDownloadFinished);
      connect(
        this->_reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), 
        this, &DownloadManager::slotError);

      connect(this->_reply, &QNetworkReply::sslErrors, [=](QList<QSslError> errors) {
        foreach(auto error, errors) {
            qDebug() << "SSL error: " << error;
        }
      });
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

      if (this->_isResultCallbackCalled)
        return;

      this->_isResultCallbackCalled = true;
      if (statusCodeV != 200) {
        this->_resultCallback->downloadResult(true, NetworkErrok);
        return;
      }

      if (0 == this->_requestSalt.length()) {
        this->_resultCallback->downloadResult(false, NoError);
        return;
      }

      if (!reply2->hasRawHeader("Content-MD5")) {
        this->_resultCallback->downloadResult(true, NetworkErrok);
        return;
      }

      QString checkMd5 = QString(QByteArray::fromBase64(reply2->rawHeader("Content-MD5")));

      Md5FileHasher hasher;
      QString hash = hasher.getFileHash(this->_filePath);

      this->_requestSalt.append(salt);
      this->_requestSalt.append(hash);
      
      QString realMd5 = QString(QCryptographicHash::hash(this->_requestSalt, QCryptographicHash::Md5).toHex());

      if (checkMd5 != realMd5) {
        this->_resultCallback->downloadResult(true, NetworkErrok);
        return;
      }
      
      this->_resultCallback->downloadResult(false, NoError);
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