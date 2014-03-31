/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once

#include <UpdateSystem/UpdateManagerWorker.h>

#include <UpdateSystem/updatemanager.h>
#include <UpdateSystem/UpdateInfoGetterInterface.h>
#include <UpdateSystem/UpdateInfoGetterResultInterface.h>
#include <UpdateSystem/UpdateInfoGetter.h>
#include <UpdateSystem/Extractor/SevenZipExtractor.h>

#include <UpdateSystem/Downloader/RetryFileDownloader.h>
#include <UpdateSystem/Downloader/downloadmanager.h>
#include <UpdateSystem/Downloader/MultiFileDownloader.h>
#include <UpdateSystem/Downloader/MultiFileDownloaderWithExtracter.h>
#include <UpdateSystem/Hasher/Md5FileHasher.h>

#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QPointer>
#include <QtCore/QProcess>
#include <QtDeclarative/QDeclarativeItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace GGS {
  namespace UpdateSystem {
    class UpdateManagerViewModel : public QDeclarativeItem
    {
      Q_OBJECT
      Q_PROPERTY(QString updateUrl READ updateUrl WRITE setUpdateUrl NOTIFY updateUrlChanged)
      Q_PROPERTY(QString installPath READ installPath WRITE setInstallPath NOTIFY installPathChanged)
      Q_PROPERTY(int updateState READ updateState)

    public:
      UpdateManagerViewModel();
      virtual ~UpdateManagerViewModel();

      QString updateUrl() const;
      void setUpdateUrl(const QString& updateUrl);

      QString installPath() const;
      void setInstallPath(const QString& installPath);

      int updateState();

    public slots:
      void startCheckUpdate();
      void startCheckUpdateRetry();

    signals:
      void updateUrlChanged();
      void installPathChanged();
      void downloadUpdateProgress(quint64 currentSize, quint64 totalSize);
      void allCompleted(bool isNeedRestart);
      void fileDownloadString(QString str);
      void downloadUpdateWarning(GGS::Downloader::DownloadResults error);
      void downloadError(int errorCode);
      void updateError(int errorCode);
      void updateStateChanged(int updateState);
      void noUpdatesFound();
      void updatesFound();
      void installUpdates();
      void downloadRetryNumber(int retryNumber);

    private slots:
      void updateThreadFinished();
      void setUpdateState(int updateState);

    private:
      GGS::UpdateSystem::UpdateManagerWorker *_updateManagerWorker;
      QString _updateUrl;
      QString _installPath;
      int _updateState;
      QThread* _updateThread;

    };
  }
}
