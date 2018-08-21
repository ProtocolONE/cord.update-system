#pragma once

#include <QtCore/QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include <UpdateSystem/Downloader/DownloadResultInterface.h>
#include <UpdateSystem/Downloader/downloadmanager.h>

class DownloadManagerTestWorker : public QObject
{
  Q_OBJECT
public:
  DownloadManagerTestWorker(void);
  ~DownloadManagerTestWorker(void);

  void setResultCallback(P1::Downloader::DownloadResultInterface *result) { this->_resultCallback = result; }

public slots:
  void downloadUpdateCrcTest(const QString& uri, const QString& path);

private:
  P1::Downloader::DownloadResultInterface *_resultCallback;
  P1::Downloader::DownloadManager *_manager;

};
