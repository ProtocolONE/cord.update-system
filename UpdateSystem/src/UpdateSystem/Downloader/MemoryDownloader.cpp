/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Downloader/MemoryDownloader.h>

namespace GGS {
  namespace Downloader {
    MemoryDownloader::MemoryDownloader(QObject *parent)
      : QObject(parent)
    {
      this->manager = new QNetworkAccessManager(this);
    }

    MemoryDownloader::~MemoryDownloader(void)
    {
    }

    void MemoryDownloader::DownloadUrl( const QString& url, QByteArray *responseBuffer )
    {
      QUrl uri(url);
      if(!uri.isValid())
      {
        emit this->slotError(QNetworkReply::ContentOperationNotPermittedError);
        return;
      }

      this->reply = this->manager->get(QNetworkRequest(uri));
      this->response = responseBuffer;
      connect(this->reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
      connect(this->reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
      connect(this->reply, SIGNAL(finished()), this, SLOT(slotReplayDownloadFinished()));
      connect(this->reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    }

    void MemoryDownloader::slotReadyRead()
    {
      QNetworkReply *reply2 = qobject_cast<QNetworkReply *>(QObject::sender());
      if (reply2) {
        QVariant statusCodeV = reply2->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCodeV == 200) {
          this->response->append(reply2->readAll());
        }
      }
    }

    void MemoryDownloader::slotReplayDownloadFinished()
    {
      emit this->downloadComplited();
    }

    void MemoryDownloader::slotError( QNetworkReply::NetworkError error )
    {
      emit this->downloadError(error);
    }
  }
}