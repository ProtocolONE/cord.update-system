/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystemViewModel/updatemanagerviewmodel>

namespace GGS { 
  namespace UpdateSystem {

    UpdateManagerViewModel::UpdateManagerViewModel()
      : _updateState(-1)
      , _updateThread(0)
    {
      this->_updateManagerWorker = new GGS::UpdateSystem::UpdateManagerWorker(0);

      connect(
        this->_updateManagerWorker, SIGNAL(allCompleted(bool)), 
        this, SIGNAL(allCompleted(bool)));

      connect(
        this->_updateManagerWorker, SIGNAL(fileDownloadedString(QString)), 
        this, SIGNAL(fileDownloadString(QString)));

      connect(
        this->_updateManagerWorker, SIGNAL(updateProgressChanged(quint64, quint64)), 
        this, SIGNAL(downloadUpdateProgress(quint64, quint64)));

      connect(
        this->_updateManagerWorker, SIGNAL(updateWarning(GGS::Downloader::DownloadResults)), 
        this, SIGNAL(downloadUpdateWarning(GGS::Downloader::DownloadResults)));

      connect(
        this->_updateManagerWorker, SIGNAL(updateError(int)), 
        this, SIGNAL(updateError(int)));

      connect(
        this->_updateManagerWorker, SIGNAL(updateStateChanged(int)), 
        this, SLOT(setUpdateState(int)));

      connect(
        this->_updateManagerWorker, SIGNAL(noUpdatesFound()), 
        this, SIGNAL(noUpdatesFound()));

      connect(
        this->_updateManagerWorker, SIGNAL(updatesFound()), 
        this, SIGNAL(updatesFound()));

      connect(
        this, SIGNAL(installUpdates()),
        this->_updateManagerWorker, SIGNAL(installUpdates()));

      connect(
        this->_updateManagerWorker, SIGNAL(downloadRetryNumber(int)),
        this, SIGNAL(downloadRetryNumber(int)));
    }
    
    UpdateManagerViewModel::~UpdateManagerViewModel()
    {
    }

    void UpdateManagerViewModel::setUpdateState(int updateState) { 
      this->_updateState = updateState; 
      emit this->updateStateChanged(updateState);
    }

    void UpdateManagerViewModel::updateThreadFinished()
    {
      if (this->_updateThread) {
        this->_updateThread->deleteLater();
        this->_updateThread = 0;
      }

      qDebug() << "[DEBUG] UpdateLater called";
    }

    void UpdateManagerViewModel::startCheckUpdateRetry() {
      if (!this->_updateManagerWorker) {
        return;
      }

      QMetaObject::invokeMethod(this->_updateManagerWorker, "checkUpdate", Qt::QueuedConnection);
    }

    void UpdateManagerViewModel::startCheckUpdate()
    {
      this->_updateThread = new QThread();
      this->_updateThread->setObjectName("Update manager thread");
      connect(this->_updateThread, SIGNAL(finished()), this, SLOT(updateThreadFinished()));

      this->_updateManagerWorker->setInstallSubDir(this->installPath());
      this->_updateManagerWorker->setWorkingDir(QCoreApplication::applicationDirPath());
      this->_updateManagerWorker->moveToThread(this->_updateThread);

      this->_updateThread->start();
      QMetaObject::invokeMethod(this->_updateManagerWorker, "checkUpdate", Qt::QueuedConnection);
    }

    void UpdateManagerViewModel::setUpdateUrl(const QString& updateUrl)
    {
      if (this->_updateUrl != updateUrl) {
        this->_updateUrl = updateUrl;

        if (this->_updateManagerWorker)
          this->_updateManagerWorker->setUpdateUrl(this->_updateUrl);

        emit this->updateUrlChanged();
      }
    }

    void UpdateManagerViewModel::setInstallPath( const QString& installPath )
    {
      if (this->_installPath != installPath) {
        this->_installPath = installPath;
        emit this->installPathChanged();
      }
    }

    QString UpdateManagerViewModel::updateUrl() const
    {
      return this->_updateUrl;
    }

    QString UpdateManagerViewModel::installPath() const
    {
      return this->_installPath;
    }

    int UpdateManagerViewModel::updateState()
    {
      return this->_updateState;
    }

  }
}