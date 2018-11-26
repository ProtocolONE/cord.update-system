#include <UpdateSystem/UpdateManagerWorker.h>

#include <QtCore/QDebug>
#include <QtCore/QThread>

namespace P1 {
  namespace UpdateSystem {

    const QString updateSubDir = "update";
    const QString updateCrcFileName = "update.crc";

    UpdateManagerWorker::UpdateManagerWorker(P1::Extractor::ExtractorInterface* extractor,  QObject * parrent)
      : _extractor(extractor), QObject(parrent)
    {
      this->_updateInfoGetter = new P1::UpdateSystem::UpdateInfoGetter(this);

      this->_updateInfoGetter->setExtractor(this->_extractor);

      P1::Downloader::DynamicRetryTimeout* dynamicRetryTimeout = new P1::Downloader::DynamicRetryTimeout(this);
      *dynamicRetryTimeout << 5000 << 10000 << 15000 << 30000;

      P1::Downloader::RetryFileDownloader* retryDownloader = new P1::Downloader::RetryFileDownloader(this);
      retryDownloader->setMaxRetry(P1::Downloader::DynamicRetryTimeout::InfinityRetryCount);
      retryDownloader->setTimeout(dynamicRetryTimeout);

      P1::Downloader::DownloadManager* downloader = new P1::Downloader::DownloadManager(this);
      retryDownloader->setDownloader(downloader);

      this->_updateInfoGetter->setDownloader(retryDownloader);

      P1::Downloader::RetryFileDownloader* retryDownloader2 = new P1::Downloader::RetryFileDownloader(this);
      retryDownloader2->setMaxRetry(P1::Downloader::DynamicRetryTimeout::InfinityRetryCount);
      retryDownloader2->setTimeout(dynamicRetryTimeout);

      P1::Downloader::DownloadManager* downloader2 = new P1::Downloader::DownloadManager(this);
      retryDownloader2->setDownloader(downloader2);

      P1::Downloader::MultiFileDownloader* multi = new P1::Downloader::MultiFileDownloader(this);
      multi->setDownloader(retryDownloader2);
      P1::Downloader::MultiFileDownloaderWithExtracter* multiExtractor = new P1::Downloader::MultiFileDownloaderWithExtracter(this);
      multiExtractor->setExtractor(this->_extractor);
      multiExtractor->setMultiDownloader(multi);

      P1::Hasher::Md5FileHasher* hasher = new P1::Hasher::Md5FileHasher(this);

      this->_manager = new UpdateManager(this);
      this->_manager->setUpdateInfoGetter(this->_updateInfoGetter);
      this->_manager->setMultiDownloader(multiExtractor);
      this->_manager->setFileHasher(hasher);
      this->_manager->setUpdateSubDir(updateSubDir);

      this->_updateInstaller = new UpdateInstaller(this);
      this->_updateInstaller->setUpdateSubDir(updateSubDir);

      this->_manager->setUpdateInstaller(this->_updateInstaller);

      connect(this->_manager, &UpdateManager::allCompleted,
        this, &UpdateManagerWorker::allComplete);

      connect(this->_manager, &UpdateManager::fileDownloadString,
        this, &UpdateManagerWorker::fileDownloadedString);

      connect(this->_manager, &UpdateManager::downloadUpdateProgress,
        this, &UpdateManagerWorker::updateProgressChanged);

      connect(this->_manager, &UpdateManager::downloadUpdateWarning,
        this, &UpdateManagerWorker::updateWarning);

      connect(this->_manager, &UpdateManager::updateError,
        this, &UpdateManagerWorker::updateError);

      connect(this->_manager, &UpdateManager::updateStateChanged,
        this, &UpdateManagerWorker::updateStateChanged);

      connect(this->_manager, &UpdateManager::noUpdatesFound,
        this, &UpdateManagerWorker::noUpdatesFound);

      connect(this->_manager, &UpdateManager::updatesFound,
        this, &UpdateManagerWorker::updatesFound);

      connect(this, &UpdateManagerWorker::installUpdates,
        this->_manager, &UpdateManager::installUpdates);

      connect(retryDownloader, &P1::Downloader::RetryFileDownloader::downloadRetryNumber,
        this, &UpdateManagerWorker::downloadRetryNumber);
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