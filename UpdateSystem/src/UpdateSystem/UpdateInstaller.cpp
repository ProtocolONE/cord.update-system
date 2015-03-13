/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/UpdateInstaller.h>

#include <QtCore/QDebug>

namespace GGS {
  namespace UpdateSystem {
    UpdateInstaller::UpdateInstaller(QObject *parrent)
      : QObject(parrent)
    {
      this->_updateSubDir = ".";
    }

    UpdateInstaller::~UpdateInstaller()
    {
    }

    void UpdateInstaller::setUpdateSubDir(const QString& updateSubDir)
    {
      this->_updateSubDir = updateSubDir;

      if (this->_updateSubDir[_updateSubDir.size()-1] == QChar('/'))
        this->_updateSubDir = QString(_updateSubDir.data(), this->_updateSubDir.size() - 1);
    }

    void UpdateInstaller::setTargetDirectory(const QString& targetDirectory)
    {
      this->_targetDirectory = targetDirectory; 
    }

    void UpdateInstaller::installUpdate(UpdateInfoContainer *changedInfo)
    {
      qDebug() << "UpdateInstaller: Start installing update";
      const QList<UpdateFileInfo* > *changedFiles = changedInfo->getFiles();
      if (changedFiles->count() <= 0) {
        emit updateError(noChangeFiles);
        return;
      }

      if (this->_updateSubDir == ".") {
        qDebug() << "[ERROR][UpdateInstaller] updateSubDir not set.";
      }

      QString updateDirectory = this->_targetDirectory;
      updateDirectory.append(_updateSubDir + "/");
      QList<UpdateFileInfo* >::const_iterator end = changedFiles->end();
      QDir dir;

      for (QList<UpdateFileInfo* >::const_iterator it = changedFiles->begin(); it != end; ++it) {
        QString updatedFilePath = updateDirectory;
        updatedFilePath.append((*it)->relativePath());

        QString oldFilePath = this->_targetDirectory;
        oldFilePath.append((*it)->relativePath());

        if (!this->deleteFileWithRename(oldFilePath)) {
          emit updateError(cannotDeletedFilesWithRename);
          return;
        }

        QString cleanPath = QDir::cleanPath(oldFilePath);
        int lastIndex = cleanPath.lastIndexOf('/');
        if (lastIndex != -1) {
          QString targetDirectory = cleanPath.mid(0, lastIndex + 1);
          QDir targetPath(cleanPath);
          if(!targetPath.exists(targetDirectory)) {
            targetPath.mkpath(targetDirectory);
          }
        }

        dir.rename(updatedFilePath, oldFilePath);
      }
    }

    bool UpdateInstaller::deleteFileWithRename( const QString& filePath )
    {
      if (!QFile::exists(filePath))
        return true;

      if (QFile::remove(filePath))
        return true;

      QTime time = QTime::currentTime();
      qsrand((uint)time.msec());
      int randomValue = qrand() % ((999 + 1) - 100) + 100;
      QString tempFileName = QString("%1.old.%2.old").arg(filePath).arg(randomValue);

      if(QFile::exists(tempFileName) && !QFile::remove(tempFileName)) {
        return false;
      }

      if(!QFile::rename(filePath, tempFileName)) {
        return false;
      }

      return true;
    }

    void UpdateInstaller::clearOldFiles()
    {
      this->deleteOldFilesInDirectoryRecursive(this->_targetDirectory);
    }

    void UpdateInstaller::deleteOldFilesInDirectoryRecursive(QString& targetDirPath)
    {
      QStringList filters;
      filters << "*.old.*.old";

      QDir targetDir(targetDirPath);
      targetDir.setNameFilters(filters);
      QFileInfoList list = targetDir.entryInfoList(QDir::Files);
      QFileInfoList::Iterator end = list.end();
      for (QFileInfoList::Iterator it = list.begin(); it != end; ++it) {
        QString filePath = it->absoluteFilePath();
        QFile::remove(filePath);
      }

      QDir targetDirForSubs(targetDirPath);
      QFileInfoList subDirs = targetDirForSubs.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
      QFileInfoList::Iterator subend = subDirs.end();

      for (QFileInfoList::Iterator it = subDirs.begin(); it != subend; ++it) {
        QString filePath = it->absoluteFilePath();
        this->deleteOldFilesInDirectoryRecursive(filePath);
      }
    }

  }
}