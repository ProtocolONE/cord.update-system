/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_UPDATE_InsTALLER_H_
#define _GGS_UPDATESYSTEM_UPDATE_InsTALLER_H_

#include "UpdateSystem_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTime>
#include <QtCore/QDir>

#include "UpdateInstallerInterface.h"
#include "UpdateInfoContainer.h"

namespace GGS {
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
#endif // _GGS_UPDATESYSTEM_UPDATE_InsTALLER_H_