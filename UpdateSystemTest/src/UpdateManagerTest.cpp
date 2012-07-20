


#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include <QtCore/QThread>

#define _CRTDBG_MAP_ALLOC

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
#include <UpdateSystem/UpdateManagerWorker.h>

#include "UpdateManagerTestWorker.h"
#include "Utils.h"

#include <cstdlib>
  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif



class UpdateManagerTest : public ::testing::Test
{
public:
  UpdateManagerTest()
  {
    this->leakChecker.start();
  }

  ~UpdateManagerTest()
  {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest(std::string("Memory leak detected!").c_str());  
  }

  virtual void SetUp() {
    this->appDir = QCoreApplication::applicationDirPath();
    this->workingDir = this->appDir;
    this->workingDir.append("/UpdateManagerTest/");

    QDir dir(this->workingDir);
    if(dir.exists(this->workingDir)){
      Utils::removeDir(dir);
    }

    dir.mkpath(this->workingDir);
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  QString appDir;
  QString workingDir;

private:
  
  void failTest(const char* message) 
  { 
    FAIL() << message; delete message;
  }
  
  MemoryLeaksChecker leakChecker;
};


TEST_F(UpdateManagerTest, test1)
{
  // UNDONE: вынести в поток и сделать нормальный тест
  UpdateManagerTestWorker worker(0);
  GGS::UpdateSystem::UpdateManager manager(&worker);

  GGS::Extractor::SevenZipExtactor extractor;
  GGS::Downloader::DownloadManager downloader(&worker);
  GGS::UpdateSystem::UpdateInfoGetter updateInfoGetter(&worker);
  updateInfoGetter.setDownloader(&downloader);
  updateInfoGetter.setExtractor(&extractor);
  updateInfoGetter.setCurrentDir(QCoreApplication::applicationDirPath());

  manager.setUpdateInfoGetter(&updateInfoGetter);

  GGS::Hasher::Md5FileHasher hasher;
  manager.setFileHasher(&hasher);

  GGS::Downloader::DownloadManager downloader2(&worker);
  GGS::Downloader::MultiFileDownloader multi;
  multi.setDownloader(&downloader2);

  GGS::Downloader::MultiFileDownloaderWithExtracter multi2;
  multi2.setExtractor(&extractor);
  multi2.setMultiDownloader(&multi);

  manager.setMultiDownloader(&multi2);

  manager.setTargetDirectory(this->workingDir);
  manager.setUpdateBaseUrl(QString("http://fs0.gamenet.ru/update/gna/live/"));

  worker._target = &manager;
  QThread thread;

  worker.moveToThread(&thread);
  
  //QMetaObject::invokeMethod(&worker, "doSimpleTest", Qt::QueuedConnection);

  //thread.start();
  //thread.wait(500000);
  //GGS::Downloader::
  //manager.set
  // 

}

TEST_F(UpdateManagerTest, createUpdateWorkerTest)
{
  GGS::UpdateSystem::UpdateManagerWorker worker(0);
  worker.setWorkingDir(QCoreApplication::applicationDirPath());
  worker.setUpdateUrl(QString("http://fs0.gamenet.ru/update/gna/live/update.crc.7z"));
}