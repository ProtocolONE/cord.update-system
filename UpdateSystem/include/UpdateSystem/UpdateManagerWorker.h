/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_UPDATE_MANAGER_WORKER_H_
#define _GGS_UPDATESYSTEM_UPDATE_MANAGER_WORKER_H_

//#ifdef _DEBUG
//  #ifdef WIN32
//    #include <Windows.h>
//  #endif
//  #include <vld.h>
//#endif

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

namespace GGS {
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
        void updateWarning(GGS::Downloader::DownloadResults error);
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

      GGS::Extractor::SevenZipExtactor *_extractor;
      GGS::UpdateSystem::UpdateInfoGetter *_updateInfoGetter; 
    };

  }
}
#endif // _GGS_UPDATESYSTEM_UPDATE_MANAGER_WORKER_H_