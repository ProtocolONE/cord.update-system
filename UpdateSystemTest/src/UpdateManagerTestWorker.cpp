#include "UpdateManagerTestWorker.h"


UpdateManagerTestWorker::UpdateManagerTestWorker(QObject *parrent)
  : QObject(parrent)
{
}


UpdateManagerTestWorker::~UpdateManagerTestWorker(void)
{
}

void UpdateManagerTestWorker::doSimpleTest()
{
  this->_target->checkUpdate();
  //Qt::HANDLE q1 = this->thread()->currentThreadId();
  //GGS::UpdateSystem::UpdateManager *manager = new GGS::UpdateSystem::UpdateManager(this);

  //GGS::Downloader::DownloadManager *downloader = new GGS::Downloader::DownloadManager(this);
  //GGS::UpdateSystem::UpdateInfoGetter *updateInfoGetter = new GGS::UpdateSystem::UpdateInfoGetter(this);

  //GGS::Extractor::SevenZipExtactor *extractor = new GGS::Extractor::SevenZipExtactor();

  //GGS::Downloader::MultiFileDownloader *multik = new GGS::Downloader::MultiFileDownloader(this); 

  //updateInfoGetter->setExtractor(extractor);
  //updateInfoGetter->setDownloader(downloader);

  //GGS::Downloader::DownloadManager *downloader2 = new GGS::Downloader::DownloadManager(this);
  //multik->setDownloader(downloader2);

  //manager->setMultiDownloader(multik);
  //manager->setUpdateInfoGetter(updateInfoGetter);
  //manager->checkUpdate();
  //updateInfoGetter->

  //updateInfoGetter.setResultCallback(&manager);
  //updateInfoGetter.setDownloader(&downloader);
  //downloader.downloadFile(QString("http://fs0.gamenet.ru/update/gna/live/update.crc.7z"), QString("123"));

  //updateInfoGetter.setExtractor(&extractor);

  //updateInfoGetter.start();


  //GGS::Extractor::SevenZipExtactor extractor;
  //GGS::Downloader::DownloadManager downloader;
  //GGS::Downloader::RetryFileDownloader retryDownloader;

  //retryDownloader.setDownloader(&downloader);

  //updateInfoGetter.setExtractor(&extractor);
  //updateInfoGetter.setDownloader(&retryDownloader);

  //manager.setUpdateInfoGetter(&updateInfoGetter);


  //manager.checkUpdate();

  //GGS::Downloader::MultiFileDownloader *multik = new GGS::Downloader::MultiFileDownloader(this); 
  //GGS::Downloader::DownloadManager *manager = new GGS::Downloader::DownloadManager(this);
  //manager->setResultCallback(multik);
  //manager->downloadFile(QString("http://fs0.gamenet.ru/update/gna/live/update.crc.7z"), QString("123"));
}
