#include <gtest/gtest.h>

#include <QtCore/QThread>

#include "MemoryLeaksChecker.h"

#include "DownloadInMemoryTestWorker.h"

#include <UpdateSystem/Downloader/MemoryDownloader.h>
#include <UpdateSystem/Downloader/DownloadInMemoryInterface.h>

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
  using P1::Downloader::DownloadInMemoryInterface;
  using P1::Downloader::MemoryDownloader;
  
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
  using P1::Downloader::DownloadInMemoryInterface;
  using P1::Downloader::MemoryDownloader;

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