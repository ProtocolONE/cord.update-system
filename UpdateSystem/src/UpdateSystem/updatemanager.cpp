#include <UpdateSystem/updatemanager.h>
#include <QtCore/QDebug>
#include <windows.h>

namespace P1 { 
  namespace UpdateSystem {
    UpdateManager::UpdateManager(QObject *parrent)
      : QObject(parrent)
    {
      this->_changeContainer = new UpdateInfoContainer(this);
    }

    UpdateManager::~UpdateManager()
    {
    }

    int getDiskFreeSpaceInMb(LPCWSTR drive)
    {
      ULARGE_INTEGER freeBytes;
      freeBytes.QuadPart = 0L;

      if (!GetDiskFreeSpaceEx(drive, &freeBytes, NULL, NULL))
        return 0;

      return freeBytes.QuadPart / 1048576;
    }

    void UpdateManager::infoGetterUpdateProggress(quint64 current, quint64 total)
    {
      Q_UNUSED(current);
      Q_UNUSED(total);
    }

    void UpdateManager::checkUpdate()
    {
      qDebug() << "UpdateManager: Start checking update.";
      this->_totalUpdateSize = 0;
      this->_changeContainer->clear();
      this->_updateInstaller->clearOldFiles();
      this->getUpdateList();
    }

    void UpdateManager::setUpdateInfoGetter(UpdateInfoGetterInterface *updateInfoGetter) { 
      this->_updateInfoGetter = updateInfoGetter; 
      this->_updateInfoGetter->setResultCallback(this);
    }

    void UpdateManager::setMultiDownloader(P1::Downloader::MultiFileDownloadInterface *multidownloader) { 
      this->_multiDownloader = multidownloader; 
      this->_multiDownloader->setResultCallback(this);
    }

    void UpdateManager::setUpdateSubDir(const QString& updateSubDir) { 
      this->_updateSubDir = updateSubDir; 
    }

    void UpdateManager::getUpdateList()
    {
      emit updateStateChanged(crcFileDownload);

      if (getDiskFreeSpaceInMb(L".") < 10) {
        this->updateInfoCallback(NotEnoughSpace); 
        return;
      }

      this->_updateInfoGetter->start();
    }

    void UpdateManager::updateInfoCallback( UpdateInfoGetterResults error )
    {
      qDebug() << "UpdateManager: Getting update info result " << error;
      if (error != NoError){
        switch(error){
          case NoError:  qDebug() << "[ERROR] Update no error"; break;
          case DownloadError:  qDebug() << "[ERROR] Update download error"; break;
          case ExtractError:  qDebug() << "[ERROR] Update extract error"; break;
          case XmlContentError:  qDebug() << "[ERROR] Update xml content error"; break;
          case BadArguments:  qDebug() << "[[ERROR] Update bad arguments"; break;
          case CanNotDeleteOldUpdateFiles:  qDebug() << "[ERROR] Update CanNotDeleteOldUpdateFiles"; break;
        }

        emit this->updateError(error);
        return;
      }

      this->_changeContainer->clear();
      UpdateInfoContainer *updateInfo = this->_updateInfoGetter->updateInfo(); 
      const QList<UpdateFileInfo* > *info = updateInfo->getFiles();
      QList<UpdateFileInfo* >::const_iterator end = info->end();
      quint64 rawSize = 0;

      for (QList<UpdateFileInfo* >::const_iterator it = info->begin(); it != end; ++it) {
        QString hash = (*it)->hash();
        QString targetFile = this->_targetDirectory;
        targetFile.append((*it)->relativePath());
        QString realHash = this->_fileHasher->getFileHash(targetFile);

        if (realHash.compare(hash) != 0) {
          qDebug() << "UpdateManager: Changed file " << (*it)->relativePath();
          this->_totalUpdateSize += (*it)->archiveLength();

          UpdateFileInfo* fileInfo = new UpdateFileInfo();
          fileInfo->setPath((*it)->relativePath());
          fileInfo->setHash((*it)->hash());
          fileInfo->setRawLength((*it)->rawLength());
          fileInfo->setArchiveLength((*it)->archiveLength());
          fileInfo->setForceCheck((*it)->forceCheck());

          rawSize +=  fileInfo->archiveLength() + fileInfo->rawLength();

          this->_changeContainer->addFileInfo(fileInfo);
        }
      }

      if (rawSize > 0 && getDiskFreeSpaceInMb(L".") < (rawSize / 1048576)) {
        this->updateInfoCallback(NotEnoughSpace); 
        return;
      }

      updateInfo->clear();
      this->downloadChangedFiles();  
    }

    void UpdateManager::downloadChangedFiles()
    {
      const QList<UpdateFileInfo* > *changedFiles = this->_changeContainer->getFiles();
      if ( changedFiles->count() <= 0 ) {
        emit this->allCompleted(false);
        emit noUpdatesFound();
        return;
      }

      emit updateStateChanged(updateFilesDownloading);

      QList<UpdateFileInfo* >::const_iterator end = changedFiles->end();
      for (QList<UpdateFileInfo* >::const_iterator it = changedFiles->begin(); it != end; ++it) {
        QString url = this->_updateBaseUrl;
        url.append((*it)->relativePath());
        url.replace('\\', '/');

        QString targetFile = this->_targetDirectory;
        targetFile.append(getUpdateSubDir() + "/");
        targetFile.append((*it)->relativePath());
        this->_multiDownloader->addFile(url, targetFile);
      }

      this->_multiDownloader->start();
    }

    void UpdateManager::fileDownloaded(const QString& filePath)
    {
      qDebug() << "UpdateManager: File downloaded " << filePath;
      emit this->fileDownloadString(filePath);
    }

    void UpdateManager::downloadResult(bool isError, P1::Downloader::DownloadResults error)
    {
      Q_UNUSED(isError);
      emit updatesFound();

      if (error != P1::Downloader::NoError)
        emit this->downloadError(error);
    }

    void UpdateManager::installUpdates(){
      if (this->_changeContainer->getFiles()->size()){
        this->_updateInstaller->installUpdate(this->_changeContainer);
        this->_changeContainer->clear();
        emit this->allCompleted(true);
      } 
    }

    void UpdateManager::downloadProgress(quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize)
    {
      Q_UNUSED(currentFileDownloadSize);
      Q_UNUSED(currestFileSize);
      emit this->downloadUpdateProgress(downloadSize, this->_totalUpdateSize);
    }

    void UpdateManager::downloadWarning(bool isError, P1::Downloader::DownloadResults error)
    {
      Q_UNUSED(isError);
      emit this->downloadUpdateWarning(error);
    }

    void UpdateManager::setTargetDirectory(const QString& targetDirectory)
    {
      this->_targetDirectory = targetDirectory;
    }

    void UpdateManager::setUpdateBaseUrl(const QString& baseUrl)
    {
      this->_updateBaseUrl = baseUrl;
    }

    void UpdateManager::setFileHasher(P1::Hasher::FileHashInterface *fileHasher)
    {
      this->_fileHasher = fileHasher;
    }

    void UpdateManager::setUpdateInstaller(UpdateInstallerInterface *updateInstaller)
    {
      this->_updateInstaller = updateInstaller;
    }

    const QString& UpdateManager::getUpdateSubDir()
    {
      return this->_updateSubDir;
    }

  }
}