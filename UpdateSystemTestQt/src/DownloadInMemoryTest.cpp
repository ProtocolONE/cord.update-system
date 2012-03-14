#include "gtest/gtest.h"

#include <QtCore/QThread>

#include "MemoryLeaksChecker.h"

#include "DownloadInMemoryTestWorker.h"

#include "Downloader/MemoryDownloader.h"
#include "Downloader/DownloadInMemoryInterface.h"

class DownloadInMemoryTest: public ::testing::Test
{
public:
  DownloadInMemoryTest()
  {
    this->leakChecker.start();
  }

  ~DownloadInMemoryTest()
  {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest(std::string("Memory leak detected!").c_str());  
  }

private: 
  void failTest(const char* message) 
  { 
    FAIL() << message; delete message;
  }

  MemoryLeaksChecker leakChecker;
};

TEST_F(DownloadInMemoryTest, test1)
{
  using GGS::Downloader::DownloadInMemoryInterface;
  using GGS::Downloader::MemoryDownloader;
  
  QThread *thread = new QThread();
  DownloadInMemoryTestWorker * worker = new DownloadInMemoryTestWorker();

  worker->moveToThread(thread);

  //MemoryDownloader *downloader = new MemoryDownloader();
  
  QMetaObject::invokeMethod(worker, "slotStartDowloadFixtureTest", Qt::QueuedConnection);

  thread->start();
  thread->wait(50000);

  if(! worker->IsFinished) {
    FAIL() << "Test failed";
  }

  delete thread;
  delete worker;
  
}

TEST_F(DownloadInMemoryTest, test2)
{
  using GGS::Downloader::DownloadInMemoryInterface;
  using GGS::Downloader::MemoryDownloader;

  QThread *thread = new QThread();
  DownloadInMemoryTestWorker * worker = new DownloadInMemoryTestWorker();

  worker->moveToThread(thread);

  //MemoryDownloader *downloader = new MemoryDownloader();

  QMetaObject::invokeMethod(worker, "slotFailDownloadTest", Qt::QueuedConnection);

  thread->start();
  thread->wait(50000);

  if(! worker->IsFinished) {
    FAIL() << "Test failed";
  }

  delete thread;
  delete worker;

}