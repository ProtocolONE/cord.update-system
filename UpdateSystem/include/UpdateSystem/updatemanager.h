/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <UpdateSystem/UpdateSystem_global>

#include <QtCore/QString>
#include <QtCore/QList>

#include <UpdateSystem/Hasher/FileHashInterface>

#include <UpdateSystem/Downloader/downloadmanager>
#include <UpdateSystem/Downloader/MultiFileDownloader>
#include <UpdateSystem/Downloader/MultiFileDownloadInterface>

#include <UpdateSystem/UpdateFileInfo>
#include <UpdateSystem/UpdateInfoContainer>
#include <UpdateSystem/UpdateInfoGetterInterface>
#include <UpdateSystem/UpdateInfoGetterResultInterface>
#include <UpdateSystem/UpdateInstallerInterface>

namespace GGS { 
  namespace UpdateSystem {

    enum UpdateState{
      crcFileDownload = 0,
      updateFilesDownloading = 1
    };

    class UPDATESYSTEMSHARED_EXPORT UpdateManager : public QObject,
      public UpdateInfoGetterResultInterface,
      public GGS::Downloader::MultiFileDownloadResultInterface
    {
      Q_OBJECT
    public:
      explicit UpdateManager(QObject *parrent = 0);
      ~UpdateManager() {};
      void checkUpdate();

      void setTargetDirectory(const QString& targetDirectory); 
      void setUpdateBaseUrl(const QString& baseUrl); 
      void setUpdateSubDir(const QString& updateSubDir);
      void setFileHasher(GGS::Hasher::FileHashInterface *fileHasher); 
      void setUpdateInstaller(UpdateInstallerInterface *updateInstaller);
      void setUpdateInfoGetter(UpdateInfoGetterInterface *updateInfoGetter);
      void setMultiDownloader(GGS::Downloader::MultiFileDownloadInterface *multidownloader);

      const QString& getUpdateSubDir();

      virtual void updateInfoCallback(UpdateInfoGetterResults error);

      // MultiFileDownloadResultInterface
      virtual void fileDownloaded(const QString& filePath);
      virtual void downloadResult( bool isError, GGS::Downloader::DownloadResults error );
      virtual void downloadProgress( quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize );
      virtual void downloadWarning( bool isError, GGS::Downloader::DownloadResults error );

    signals:
      void fileDownloadString(QString str);      
      void allCompleted(bool isNeedRestart);
      void downloadUpdateProgress(quint64 currentSize, quint64 totalSize);
      void downloadUpdateWarning(GGS::Downloader::DownloadResults error);

      void downloadError(int);
      void updateError(int);
      void updateStateChanged(int);
      void noUpdatesFound();
      void updatesFound();

    private slots:
      void infoGetterUpdateProggress(quint64 current, quint64 total);
      void installUpdates();

    private:
      void getUpdateList();
      void downloadChangedFiles();

      QString _updateBaseUrl;
      QString _targetDirectory;
      QString _updateSubDir;

      UpdateInfoContainer *_changeContainer;

      UpdateInfoGetterInterface *_updateInfoGetter;
      GGS::Downloader::MultiFileDownloadInterface *_multiDownloader;
      GGS::Hasher::FileHashInterface *_fileHasher;
      UpdateInstallerInterface *_updateInstaller;

      quint64 _totalUpdateSize;
    };

  }
}
#endif // UPDATEMANAGER_H
