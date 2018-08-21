#pragma once

#include "UpdateSystem_global.h"

#include "Extractor/SevenZipExtractor.h"

#include "updatemanager.h"
#include "UpdateInfoGetter.h"
#include "Downloader/DynamicRetryTimeout.h"
#include "Downloader/RetryFileDownloader.h"
#include "Downloader/downloadmanager.h"
#include "Downloader/MultiFileDownloaderWithExtracter.h"
#include "Hasher/Md5FileHasher.h"
#include "UpdateInstaller.h"

#include <QtCore/QObject>
#include <QtCore/QString>

namespace P1 {
  namespace UpdateSystem {

    class UPDATESYSTEMSHARED_EXPORT UpdateManagerWorker : public QObject
    {
      Q_OBJECT

    public:
      explicit UpdateManagerWorker(QObject * parrent = 0);
      ~UpdateManagerWorker(void);

      const QString& updateUrl() const { return this->_updateUrl; }
      void setUpdateUrl(const QString& updateUrl);

      const QString& installSubDir() const { return this->_installSubDir; }
      void setInstallSubDir(const QString& installSubDir) { this->_installSubDir = installSubDir; }

      const QString& workingDir() { return this->_workingDir; }
      void setWorkingDir( const QString& wDir );

    public slots:
        void checkUpdate( );
        void allComplete(bool isNeedRestart);

    signals:
        void fileDownloadedString(QString str);
        void allCompleted(bool isNeedRestart);
        void updateProgressChanged(quint64 currentSize, quint64 totalSize);
        void updateWarning(P1::Downloader::DownloadResults error);
        void updateError(int);
        void updateStateChanged(int);
        void noUpdatesFound();
        void updatesFound();
        void installUpdates();
        void downloadRetryNumber(int);

    private:
      QString _updateUrl;
      QString _installSubDir;
      QString _workingDir;

      UpdateManager *_manager;
      UpdateInstaller *_updateInstaller;

      P1::Extractor::SevenZipExtactor *_extractor;
      P1::UpdateSystem::UpdateInfoGetter *_updateInfoGetter; 
    };

  }
}
