#ifndef _GGS_DOWNLOAD_MANAGE_TEST_WORKER_H_
#define _GGS_DOWNLOAD_MANAGE_TEST_WORKER_H_


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

  void setResultCallback(GGS::Downloader::DownloadResultInterface *result) { this->_resultCallback = result; }

public slots:
  void downloadUpdateCrcTest(const QString& uri, const QString& path);

private:
  GGS::Downloader::DownloadResultInterface *_resultCallback;
  GGS::Downloader::DownloadManager *_manager;

};

#endif // _GGS_DOWNLOAD_MANAGE_TEST_WORKER_H_