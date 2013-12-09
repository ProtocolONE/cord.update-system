/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/UpdateManagerWorker.h>

#include <QtCore/QDebug>
#include <QtCore/QThread>

namespace GGS {
  namespace UpdateSystem {

    const QString updateSubDir = "update";
    const QString updateCrcFileName = "update.crc";

    UpdateManagerWorker::UpdateManagerWorker(QObject * parrent)
      : QObject(parrent)
    {
      this->_updateInfoGetter = new GGS::UpdateSystem::UpdateInfoGetter(this);

      this->_extractor = new GGS::Extractor::SevenZipExtactor();
      this->_updateInfoGetter->setExtractor(this->_extractor);

      GGS::Downloader::DynamicRetryTimeout* dynamicRetryTimeout = new GGS::Downloader::DynamicRetryTimeout(this);
      *dynamicRetryTimeout << 5000 << 10000 << 15000 << 30000;

      GGS::Downloader::RetryFileDownloader* retryDownloader = new GGS::Downloader::RetryFileDownloader(this);
      retryDownloader->setMaxRetry(GGS::Downloader::DynamicRetryTimeout::InfinityRetryCount);
      retryDownloader->setTimeout(dynamicRetryTimeout);

      GGS::Downloader::DownloadManager* downloader = new GGS::Downloader::DownloadManager(this);     
      retryDownloader->setDownloader(downloader);

      this->_updateInfoGetter->setDownloader(retryDownloader);

      GGS::Downloader::RetryFileDownloader* retryDownloader2 = new GGS::Downloader::RetryFileDownloader(this);
      retryDownloader2->setMaxRetry(GGS::Downloader::DynamicRetryTimeout::InfinityRetryCount);
      retryDownloader2->setTimeout(dynamicRetryTimeout);

      GGS::Downloader::DownloadManager* downloader2 = new GGS::Downloader::DownloadManager(this);     
      retryDownloader2->setDownloader(downloader2);

      GGS::Downloader::MultiFileDownloader* multi = new GGS::Downloader::MultiFileDownloader(this);
      multi->setDownloader(retryDownloader2);
      GGS::Downloader::MultiFileDownloaderWithExtracter* multiExtractor = new GGS::Downloader::MultiFileDownloaderWithExtracter(this);
      multiExtractor->setExtractor(this->_extractor);
      multiExtractor->setMultiDownloader(multi);

      GGS::Hasher::Md5FileHasher* hasher = new GGS::Hasher::Md5FileHasher(this);

      this->_manager = new UpdateManager(this);
      this->_manager->setUpdateInfoGetter(this->_updateInfoGetter);
      this->_manager->setMultiDownloader(multiExtractor);
      this->_manager->setFileHasher(hasher);
      this->_manager->setUpdateSubDir(updateSubDir);

      this->_updateInstaller = new UpdateInstaller(this);
      this->_updateInstaller->setUpdateSubDir(updateSubDir);

      this->_manager->setUpdateInstaller(this->_updateInstaller);

      connect(
        this->_manager, SIGNAL(allCompleted(bool)), 
        this, SLOT(allComplete(bool)));

      connect(
        this->_manager, SIGNAL(fileDownloadString(QString)), 
        this, SIGNAL(fileDownloadedString(QString)));

      connect(
        this->_manager, SIGNAL(downloadUpdateProgress(quint64, quint64)), 
        this, SIGNAL(updateProgressChanged(quint64, quint64)));

      connect(
        this->_manager, SIGNAL(downloadUpdateWarning(GGS::Downloader::DownloadResults)), 
        this, SIGNAL(updateWarning(GGS::Downloader::DownloadResults)));

      connect(
        this->_manager, SIGNAL(updateError(int)), 
        this, SIGNAL(updateError(int)));

      connect(
        this->_manager, SIGNAL(updateStateChanged(int)), 
        this, SIGNAL(updateStateChanged(int)));

      connect(
        this->_manager, SIGNAL(noUpdatesFound()), 
        this, SIGNAL(noUpdatesFound()));

      connect(
        this->_manager, SIGNAL(updatesFound()), 
        this, SIGNAL(updatesFound()));

      connect(
        this, SIGNAL(installUpdates()),
        this->_manager, SLOT(installUpdates()));

      connect(
        retryDownloader, SIGNAL(downloadRetryNumber(int)),
        this, SIGNAL(downloadRetryNumber(int)));
    }

    UpdateManagerWorker::~UpdateManagerWorker(void)
    {
      delete this->_extractor;
    }

    void UpdateManagerWorker::setWorkingDir(const QString& wDir) 
    { 
      this->_workingDir = wDir; 
      this->_updateInfoGetter->setCurrentDir(workingDir());
      this->_updateInfoGetter->setUpdateFileName(updateCrcFileName);

      if (_updateUrl.isEmpty()) {
        qDebug() << "[ERROR] No update url set.";
        return;
      }

      QString workDir = workingDir() + "/";

      if (this->_installSubDir.size())
        workDir.append(this->_installSubDir + "/");

      this->_manager->setUpdateBaseUrl(this->_updateUrl);
      this->_updateInstaller->setTargetDirectory(workDir);
      this->_manager->setTargetDirectory(workDir);
    }

    void UpdateManagerWorker::setUpdateUrl(const QString& updateUrl) 
    { 
      QString updateCrcUrl = updateUrl;
      updateCrcUrl.append(updateCrcFileName + ".7z");

      this->_updateInfoGetter->setUpdateCrcUrl(updateCrcUrl);
      this->_updateUrl = updateUrl; 
    }

    void UpdateManagerWorker::checkUpdate()
    {
      qsrand(QDateTime::currentMSecsSinceEpoch());
      this->_manager->checkUpdate();
    }

    void UpdateManagerWorker::allComplete(bool isNeedRestart)
    {
      emit this->allCompleted(isNeedRestart);
      this->deleteLater();
    }
  }
}