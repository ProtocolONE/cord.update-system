/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/updatemanager.h>
#include <QtCore/QDebug>

namespace GGS { 
  namespace UpdateSystem {
    UpdateManager::UpdateManager(QObject *parrent)
      : QObject(parrent)
    {
      this->_changeContainer = new UpdateInfoContainer(this);
    }

    void UpdateManager::infoGetterUpdateProggress(quint64 current, quint64 total){
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

    void UpdateManager::setMultiDownloader(GGS::Downloader::MultiFileDownloadInterface *multidownloader) { 
      this->_multiDownloader = multidownloader; 
      this->_multiDownloader->setResultCallback(this);
    }

    void UpdateManager::setUpdateSubDir(const QString& updateSubDir) { 
      this->_updateSubDir = updateSubDir; 
    }

    void UpdateManager::getUpdateList()
    {
      emit updateStateChanged(crcFileDownload);
      this->_updateInfoGetter->start();
    }

    void UpdateManager::updateInfoCallback( UpdateInfoGetterResults error )
    {
      qDebug() << "UpdateManager: Getting update info result " << error;
      if(error != NoError){
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
          
          this->_changeContainer->addFileInfo(fileInfo);
        }
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

    void UpdateManager::downloadResult( bool isError, GGS::Downloader::DownloadResults error )
    {
      emit updatesFound();

      if (error != GGS::Downloader::NoError)
        emit this->downloadError(error);
    }

    void UpdateManager::installUpdates(){
      if (this->_changeContainer->getFiles()->size()){
        this->_updateInstaller->installUpdate(this->_changeContainer);
        this->_changeContainer->clear();
        emit this->allCompleted(true);
      } 
    }

    void UpdateManager::downloadProgress( quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize )
    {
      emit this->downloadUpdateProgress(downloadSize, this->_totalUpdateSize);
    }

    void UpdateManager::downloadWarning( bool isError, GGS::Downloader::DownloadResults error )
    {
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

    void UpdateManager::setFileHasher(GGS::Hasher::FileHashInterface *fileHasher)
    {
      this->_fileHasher = fileHasher;
    }

    void UpdateManager::setUpdateInstaller(UpdateInstallerInterface *updateInstaller)
    {
      this->_updateInstaller = updateInstaller;
    }

    const QString& UpdateManager::getUpdateSubDir()
    {
      return _updateSubDir;
    }

  }
}