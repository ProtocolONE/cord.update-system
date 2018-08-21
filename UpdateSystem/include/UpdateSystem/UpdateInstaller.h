#pragma once

#include "UpdateSystem_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTime>
#include <QtCore/QDir>

#include "UpdateInstallerInterface.h"
#include "UpdateInfoContainer.h"

namespace P1 {
  namespace UpdateSystem {

    enum updateInstallerCodes {
      noChangeFiles = 0,
      cannotDeletedFilesWithRename = 1
    };

    class UPDATESYSTEMSHARED_EXPORT UpdateInstaller : public QObject,
      public UpdateInstallerInterface
    {
      Q_OBJECT

    public:
      explicit UpdateInstaller(QObject *parrent = 0);
      virtual ~UpdateInstaller(void);

      void clearOldFiles();
      void installUpdate(UpdateInfoContainer *changedInfo);
      void setUpdateSubDir(const QString& updateSubDir);
      void setTargetDirectory(const QString& targetDirectory);

    private:
      bool deleteFileWithRename( const QString& filePath );
      void deleteOldFilesInDirectoryRecursive( QString& targetDir);

    signals:
      void updateError(updateInstallerCodes updateCode);

    private:
      QString _targetDirectory;
      QString _updateSubDir;
    };
  }
}
