#pragma once

#include <UpdateSystem/UpdateSystem_global.h>

#include <QtCore/QString>
#include <QtCore/QList>

#include <UpdateSystem/Hasher/FileHashInterface.h>

#include <UpdateSystem/Downloader/downloadmanager.h>
#include <UpdateSystem/Downloader/MultiFileDownloader.h>
#include <UpdateSystem/Downloader/MultiFileDownloadInterface.h>

#include <UpdateSystem/UpdateFileInfo.h>
#include <UpdateSystem/UpdateInfoContainer.h>
#include <UpdateSystem/UpdateInfoGetterInterface.h>
#include <UpdateSystem/UpdateInfoGetterResultInterface.h>
#include <UpdateSystem/UpdateInstallerInterface.h>

namespace P1 { 
  namespace UpdateSystem {

    enum UpdateState{
      crcFileDownload = 0,
      updateFilesDownloading = 1
    };

    class UPDATESYSTEMSHARED_EXPORT UpdateManager : public QObject,
      public UpdateInfoGetterResultInterface,
      public P1::Downloader::MultiFileDownloadResultInterface
    {
      Q_OBJECT
    public:
      friend class UpdateManagerWorker;

      explicit UpdateManager(QObject *parrent = 0);
      virtual ~UpdateManager();;
      void checkUpdate();

      void setTargetDirectory(const QString& targetDirectory); 
      void setUpdateBaseUrl(const QString& baseUrl); 
      void setUpdateSubDir(const QString& updateSubDir);
      void setFileHasher(P1::Hasher::FileHashInterface *fileHasher); 
      void setUpdateInstaller(UpdateInstallerInterface *updateInstaller);
      void setUpdateInfoGetter(UpdateInfoGetterInterface *updateInfoGetter);
      void setMultiDownloader(P1::Downloader::MultiFileDownloadInterface *multidownloader);

      const QString& getUpdateSubDir();

      virtual void updateInfoCallback(UpdateInfoGetterResults error);

      // MultiFileDownloadResultInterface
      virtual void fileDownloaded(const QString& filePath);
      virtual void downloadResult( bool isError, P1::Downloader::DownloadResults error );
      virtual void downloadProgress( quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize );
      virtual void downloadWarning( bool isError, P1::Downloader::DownloadResults error );

    signals:
      void fileDownloadString(QString str);      
      void allCompleted(bool isNeedRestart);
      void downloadUpdateProgress(quint64 currentSize, quint64 totalSize);
      void downloadUpdateWarning(P1::Downloader::DownloadResults error);

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
      P1::Downloader::MultiFileDownloadInterface *_multiDownloader;
      P1::Hasher::FileHashInterface *_fileHasher;
      UpdateInstallerInterface *_updateInstaller;

      quint64 _totalUpdateSize;
    };

  }
}
