/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef UPDATEMANAGERVIEWMODEL_H
#define UPDATEMANAGERVIEWMODEL_H

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

// TODO при появлении 
#ifdef UPDATESYSTEMVIEWMODEL_LIB
# define UPDATESYSTEMVIEWMODEL Q_DECL_EXPORT
#else
# define UPDATESYSTEMVIEWMODEL Q_DECL_IMPORT
#endif

namespace GGS {
  namespace UpdateSystem {
		class UPDATESYSTEMVIEWMODEL UpdateManagerViewModel : public QDeclarativeItem
		{
			Q_OBJECT
      Q_PROPERTY(QString updateUrl READ updateUrl WRITE setUpdateUrl NOTIFY updateUrlChanged)
      Q_PROPERTY(QString installPath READ installPath WRITE setInstallPath NOTIFY installPathChanged)
      Q_PROPERTY(int updateState READ updateState)
      Q_PROPERTY(QString updateArea READ updateArea WRITE setUpdateArea NOTIFY updateAreaChanged)

    public:
      UpdateManagerViewModel();
      ~UpdateManagerViewModel();

      const QString& updateUrl() const { return this->_updateUrl; }
      void setUpdateUrl(const QString& updateUrl);

      const QString& installPath() const { return this->_installPath; }
      void setInstallPath(const QString& installPath);

      int updateState() { return this->_updateState; }

      QString updateArea() const;
      void setUpdateArea(QString area);

		public slots:
			void startCheckUpdate();
      		void startCheckUpdateRetry();

    signals:
      void updateUrlChanged();
      void installPathChanged();
      void updateAreaChanged();
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

		private:
			GGS::UpdateSystem::UpdateManagerWorker *_updateManagerWorker;
      QString _updateUrl;
      QString _installPath;
      int _updateState;
      QThread* _updateThread;
      QString _updateArea;

		private slots:
			void updateThreadFinished();
      void setUpdateState(int updateState);
		};
  }
}
#endif // UPDATEMANAGERVIEWMODEL_H
