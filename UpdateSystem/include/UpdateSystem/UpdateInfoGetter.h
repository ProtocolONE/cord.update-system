/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_UPDATEINFOGETTER_H_
#define _GGS_UPDATESYSTEM_UPDATEINFOGETTER_H_

#include "UpdateSystem_global.h"

#include "Downloader/FileDownloaderInterface.h"
#include "Extractor/ExtractorInterface.h"
#include "UpdateInfoContainer.h"
#include "UpdateFileInfo.h"

#include "UpdateInfoGetterInterface.h"
#include "UpdateInfoGetterResultInterface.h"

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QTime>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace UpdateSystem {

    class UPDATESYSTEMSHARED_EXPORT UpdateInfoGetter : public QObject,
      public GGS::Downloader::DownloadResultInterface,
      public GGS::UpdateSystem::UpdateInfoGetterInterface
    {
      Q_OBJECT

    public:
      explicit UpdateInfoGetter(QObject *parrent = 0);
      ~UpdateInfoGetter();

      void setResultCallback(GGS::UpdateSystem::UpdateInfoGetterResultInterface *result);
      void setUpdateCrcUrl(const QString& url);
      void setCurrentDir(const QString& currentDir);
      void setUpdateFileName(const QString& updateFileName);

      UpdateInfoContainer *updateInfo() const;

      void setDownloader(GGS::Downloader::FileDownloaderInterface *downloader);
      void setExtractor(Extractor::ExtractorInterface *extractor);

      virtual void downloadResult( bool isError, GGS::Downloader::DownloadResults error );
      virtual void downloadProgress(quint64 current, quint64 total); 
      virtual void downloadWarning(bool isError, GGS::Downloader::DownloadResults error);

    public slots:
      void start();

    signals:
      void downloadProgressEvent(quint64 current, quint64 total);

    private:
      bool deleteOldUpdateFiles();
      bool deleteFileWithRename(const QString& filePath);
      void readUpdateInfoXml(const QString& filePath);
      const QString& getCurrentDir() const;
      const QString& getArchiveFile() const;
      const QString& getUpdateFile() const;

      QString _updateCrcUrl;
      QString _currentDir;
      QString _archiveFile;
      QString _updateFile;
      GGS::Downloader::FileDownloaderInterface *_downloader;
      Extractor::ExtractorInterface *_extractor;
      GGS::UpdateSystem::UpdateInfoGetterResultInterface *_updateInfoResultCallback;

      UpdateInfoContainer *_updateInfo;     
    };

  }
}
#endif //_GGS_UPDATESYSTEM_UPDATEINFOGETTER_H_