/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_MEMORY_DOWNLOADER_H_
#define _GGS_UPDATESYSTEM_MEMORY_DOWNLOADER_H_

#include "UpdateSystem_global.h"

#include "Downloader/DownloadInMemoryInterface.h"

#include <QtCore/QSharedPointer>
#include <QtCore/QObject>
#include <QtCore/QByteArray>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace GGS {
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

    private:
      QNetworkAccessManager *manager;
      QString url;
      QNetworkReply *reply;
      
      QByteArray *response;
    };
  }
}

#endif // _GGS_UPDATESYSTEM_MEMORY_DOWNLOADER_H_