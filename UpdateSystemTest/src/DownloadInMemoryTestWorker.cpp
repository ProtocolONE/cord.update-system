#include "DownloadInMemoryTestWorker.h"


DownloadInMemoryTestWorker::DownloadInMemoryTestWorker(void)
{
}


DownloadInMemoryTestWorker::~DownloadInMemoryTestWorker(void)
{
}

void DownloadInMemoryTestWorker::slotStartDowloadFixtureTest()
{
  this->_downloader = new P1::Downloader::MemoryDownloader(this);
  this->IsFinished = false;
  QString uri("http://gnlupdate.tst.local/qgna_memorydownloader_fixture.txt");
  // this->_downloader
  connect(this->_downloader, SIGNAL(downloadComplited()), this, SLOT(slotFixtureDowloadComplite()));
  this->_downloader->DownloadUrl(uri, &this->_response);
}

void DownloadInMemoryTestWorker::slotFailDownloadTest()
{
  this->_downloader = new P1::Downloader::MemoryDownloader(this);
  this->IsFinished = false;
  
  QString uri;
  connect(this->_downloader, SIGNAL(downloadComplited()), this, SLOT(slotTestShouldNotComplite()));
  connect(this->_downloader, SIGNAL(downloadError(QNetworkReply::NetworkError)), this, SLOT(slotTestShoulFail()));
  this->_downloader->DownloadUrl(uri, &this->_response);
}

void DownloadInMemoryTestWorker::slotFixtureDowloadComplite()
{
  QString responseString(this->_response);
  QString expectiongString("Test string. Please do not delete or change.");
  if (responseString.compare(expectiongString) == 0) {
    this->IsFinished = true;
  } else {
    this->IsFinished = false;
  }

  this->thread()->quit();
}

void DownloadInMemoryTestWorker::slotTestShoulFail()
{
  this->IsFinished = true;
  this->thread()->quit();
}

void DownloadInMemoryTestWorker::slotTestShouldNotComplite()
{
  this->IsFinished = false;
  this->thread()->quit();
}
