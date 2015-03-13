/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_DOWNLOADER_MULTIFILEDOWNLOADER_H_
#define _GGS_UPDATESYSTEM_DOWNLOADER_MULTIFILEDOWNLOADER_H_

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/filedownloaderinterface.h>
#include <UpdateSystem/Downloader/MultiFileDownloadInterface.h>
#include <UpdateSystem/Downloader/MultiDownloadResultInterface.h>

#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QDir>

namespace GGS {
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

      // UNDONE: возмонжо и не нужен
      quint64 _currentFileTotalSize;
      QPair<QString,QString> _currentFile;

      FileDownloaderInterface *_downloader;
      MultiFileDownloadResultInterface *_resultCallback;

      QNetworkReply::NetworkError _networkError;
      QQueue< QPair<QString,QString> > _fileQueue;
    };
  }
}
#endif // _GGS_UPDATESYSTEM_DOWNLOADER_MULTIFILEDOWNLOADER_H_