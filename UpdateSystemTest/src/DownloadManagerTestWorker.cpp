#include "DownloadManagerTestWorker.h"

// HACK: ������ � �����-�� ������.
bool RemoveDirectoryFull(QDir &aDir);

DownloadManagerTestWorker::DownloadManagerTestWorker(void)
{
  this->_manager = 0;
}


DownloadManagerTestWorker::~DownloadManagerTestWorker(void)
{
  if(this->_manager != 0) {
    delete this->_manager;
  }
}

void DownloadManagerTestWorker::downloadUpdateCrcTest(const QString& uri, const QString& path)
{
  this->_manager = new P1::Downloader::DownloadManager();
  this->_manager->setResultCallback(this->_resultCallback);
  this->_manager->downloadFile(uri, path);
}
