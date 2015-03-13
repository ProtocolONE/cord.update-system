/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/UpdateInfoGetter.h>

#include <QtCore/QDebug>

namespace GGS {
  namespace UpdateSystem {

    UpdateInfoGetter::UpdateInfoGetter(QObject *parrent)
      : QObject(parrent)
    {
      this->_downloader = 0;
      this->_extractor = 0;
      this->_updateInfoResultCallback = 0;
      this->_updateInfo = new UpdateInfoContainer(this);
      this->_currentDir = ".";
      this->_archiveFile  = ".";
      this->_updateFile  = ".";
    }

    UpdateInfoGetter::~UpdateInfoGetter()
    {
    }

    void UpdateInfoGetter::downloadProgress(quint64 current, quint64 total)
    {
       this->_updateInfoResultCallback->infoGetterUpdateProggress(current, total);
    }

    void UpdateInfoGetter::downloadWarning(bool isError, GGS::Downloader::DownloadResults error)
    {
      Q_UNUSED(isError);
      Q_UNUSED(error);
    }

    void UpdateInfoGetter::setUpdateFileName(const QString& updateFileName)
    {
      this->_archiveFile = QString(getCurrentDir()).append("/" + updateFileName + ".7z");
      this->_updateFile = QString(getCurrentDir()).append("/" + updateFileName );
    }

    void UpdateInfoGetter::setCurrentDir(const QString& currentDir)
    {
      if (currentDir[currentDir.size()-1] == QChar('/'))
        this->_currentDir = QString(currentDir.data(), currentDir.size() - 1);
      else
        this->_currentDir = currentDir;
    }

    void UpdateInfoGetter::setDownloader(GGS::Downloader::FileDownloaderInterface *downloader)
    { 
      if (!downloader) {
        qDebug() << "[ERROR][UpdateInfoGetter][ERROR] No downloader set.";
        return;
      }

      this->_downloader = downloader;
      this->_downloader->setResultCallback(this);
    }

    void UpdateInfoGetter::start()
    {
      if (!this->_updateInfoResultCallback) {
        qDebug() << "[ERROR][UpdateInfoGetter][ERROR] No update info result callback set.";
        return;
      }

      if (this->_currentDir == "." ) {
        qDebug() << "[ERROR][UpdateInfoGetter][ERROR] No current directory set.";
        this->_updateInfoResultCallback->updateInfoCallback(BadArguments);
        return;
      }

      if (this->_archiveFile[0] == '.') {
        qDebug() << "[ERROR][UpdateInfoGetter][ERROR] No update file name set.";
        this->_updateInfoResultCallback->updateInfoCallback(BadArguments);
        return;
      }

      if (this->_updateCrcUrl.isEmpty()) {
        qDebug() << "[ERROR][UpdateInfoGetter][ERROR] Attempt to start(), but no updateCrcUrl set.";
        this->_updateInfoResultCallback->updateInfoCallback(BadArguments);
        return;
      }

      if(!this->_downloader || !this->_extractor)
      {
        this->_updateInfoResultCallback->updateInfoCallback(BadArguments);
        return;
      }

      if (!this->deleteOldUpdateFiles()) {
        this->_updateInfoResultCallback->updateInfoCallback(CanNotDeleteOldUpdateFiles);
        return;
      }

      this->_downloader->downloadFile(this->_updateCrcUrl, getArchiveFile());
    }

    void UpdateInfoGetter::downloadResult(bool isError, GGS::Downloader::DownloadResults error)
    {
      Q_UNUSED(error);

      if (isError) {
        this->_updateInfoResultCallback->updateInfoCallback(DownloadError);
        return;
      }

      GGS::Extractor::ExtractionResult result = this->_extractor->extract(getArchiveFile(), getCurrentDir());
      QFile::remove(getArchiveFile());

      switch(result){
      case GGS::Extractor::NoError:
        this->_updateInfo->clear();
        this->readUpdateInfoXml(getUpdateFile());
        break;
      case GGS::Extractor::NoArchive:
        this->_updateInfoResultCallback->updateInfoCallback( DownloadError );
        break;
      default:
        this->_updateInfoResultCallback->updateInfoCallback( ExtractError );
      }
    }

    bool UpdateInfoGetter::deleteOldUpdateFiles()
    {
      if (!this->deleteFileWithRename(getArchiveFile()))
        return false;

      if (!this->deleteFileWithRename(getUpdateFile()))
        return false;

      return true;
    }

    bool UpdateInfoGetter::deleteFileWithRename(const QString& filePath)
    {
      if (!QFile::exists(filePath)) {
        return true;
      }

      if (QFile::remove(filePath)) {
        return true;
      }

      QTime time = QTime::currentTime();
      qsrand((uint)time.msec());
      int randomValue = qrand() % 900 + 100;
      QString tempFileName = QString("%1.old.%2.old").arg(filePath).arg(randomValue);

      if (QFile::exists(tempFileName) && !QFile::remove(tempFileName))
        return false;

      if (!QFile::rename(filePath, tempFileName))
        return false;

      return true;
    }

    void UpdateInfoGetter::readUpdateInfoXml(const QString& filePath)
    {
      QDomDocument doc;
      QFile file(filePath);
      if (!file.open(QIODevice::ReadOnly)) {
        this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
        return;
      }

      if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] Can not set xml content.";
        this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
        return;
      }

      file.close();
      QFile::remove(filePath);

      QDomElement updateFileList = doc.firstChildElement("UpdateFileList");
      if (updateFileList.isNull()) {
        qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] update file list is null.";
        this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
        return;
      }

      QDomElement files = updateFileList.firstChildElement("files");
      if (files.isNull()) {
        qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] No xml content child <files>.";
        this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
        return;
      }

      QDomElement fileInfo = files.firstChildElement("file");
      if (fileInfo.isNull()) {
        this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
        return;
      }

      for (; !fileInfo.isNull(); fileInfo = fileInfo.nextSiblingElement("file")) {
        if(!fileInfo.hasAttribute("path")
          || !fileInfo.hasAttribute("crc")
          || !fileInfo.hasAttribute("rawLength")
          || !fileInfo.hasAttribute("archiveLength")
          || !fileInfo.hasAttribute("check")) {
            qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] Xml content error.";
            this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
            return;
        }

        QString relativePath = fileInfo.attribute("path");
        QString hash = fileInfo.attribute("crc");
        QString rawLengthString = fileInfo.attribute("rawLength");
        QString archiveLengthString = fileInfo.attribute("archiveLength");
        QString checkString = fileInfo.attribute("check");


        bool convertCheck;
        quint64 rawLength = rawLengthString.toULongLong(&convertCheck);
        if (!convertCheck) {
          qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] Xml content no raw length.";
          this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
          return;
        }
        quint64 archiveLength = archiveLengthString.toULongLong(&convertCheck);
        if (!convertCheck) {
          qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] Xml content no archive length.";
          this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
          return;
        }

        bool check;
        if (QString::compare(checkString, "true") == 0) {
          check = true;
        } else if (QString::compare(checkString, "false") == 0) {
          check = false;
        } else {
          qDebug() << "[DEBUG][UpdateInfoGetter][ERROR] Error to check xml content.";
          this->_updateInfoResultCallback->updateInfoCallback( XmlContentError );
          return;
        }

        UpdateFileInfo* fileInfo = new UpdateFileInfo();
        fileInfo->setPath(relativePath);
        fileInfo->setHash(hash);
        fileInfo->setRawLength(rawLength);
        fileInfo->setArchiveLength(archiveLength);
        fileInfo->setForceCheck(check);

        this->_updateInfo->addFileInfo(fileInfo);
      }

      this->_updateInfoResultCallback->updateInfoCallback(NoError);
    }

    void UpdateInfoGetter::setResultCallback(GGS::UpdateSystem::UpdateInfoGetterResultInterface *result)
    {
      this->_updateInfoResultCallback = result;
    }

    void UpdateInfoGetter::setUpdateCrcUrl(const QString& url)
    {
      this->_updateCrcUrl = url;
    }

    UpdateInfoContainer * UpdateInfoGetter::updateInfo() const
    {
      return this->_updateInfo;
    }

    void UpdateInfoGetter::setExtractor(Extractor::ExtractorInterface *extractor)
    {
      this->_extractor = extractor;
    }

    const QString& UpdateInfoGetter::getCurrentDir() const
    {
      return this->_currentDir;
    }

    const QString& UpdateInfoGetter::getArchiveFile() const
    {
      return this->_archiveFile;
    }

    const QString& UpdateInfoGetter::getUpdateFile() const
    {
      return this->_updateFile;
    }
  }
}
