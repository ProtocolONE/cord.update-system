#pragma once

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

namespace P1 {
  namespace UpdateSystem {

    class UPDATESYSTEMSHARED_EXPORT UpdateInfoGetter : public QObject,
      public P1::Downloader::DownloadResultInterface,
      public P1::UpdateSystem::UpdateInfoGetterInterface
    {
      Q_OBJECT

    public:
      explicit UpdateInfoGetter(QObject *parrent = 0);
      ~UpdateInfoGetter();

      void setResultCallback(P1::UpdateSystem::UpdateInfoGetterResultInterface *result);
      void setUpdateCrcUrl(const QString& url);
      void setCurrentDir(const QString& currentDir);
      void setUpdateFileName(const QString& updateFileName);

      UpdateInfoContainer *updateInfo() const;

      void setDownloader(P1::Downloader::FileDownloaderInterface *downloader);
      void setExtractor(Extractor::ExtractorInterface *extractor);

      virtual void downloadResult( bool isError, P1::Downloader::DownloadResults error );
      virtual void downloadProgress(quint64 current, quint64 total); 
      virtual void downloadWarning(bool isError, P1::Downloader::DownloadResults error);

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
      P1::Downloader::FileDownloaderInterface *_downloader;
      Extractor::ExtractorInterface *_extractor;
      P1::UpdateSystem::UpdateInfoGetterResultInterface *_updateInfoResultCallback;

      UpdateInfoContainer *_updateInfo;     
    };

  }
}