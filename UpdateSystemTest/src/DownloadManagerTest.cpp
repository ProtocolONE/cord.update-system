#ifndef _GGS_DOWNLOAD_MANAGER_TEST_H_
#define _GGS_DOWNLOAD_MANAGER_TEST_H_

#include <UpdateSystem/Downloader/DownloadResultInterface.h>
#include <UpdateSystem/Downloader/filedownloaderinterface.h>

#include <QtCore/QThread>
#include <gtest/gtest.h>

#include "MemoryLeaksChecker.h"
#include "DownloadManagerTestWorker.h"
#include "Utils.h"

class DownloadResultCallback : public GGS::Downloader::DownloadResultInterface
{
public:
  DownloadResultCallback(){
    this->_downloadResultError = GGS::Downloader::NoError;
    this->_networkResult = QNetworkReply::NoError;
    this->_downloadResultCalled = false;
    this->_totalResponseSize = 0;
    this->_downloadProgressCalled = false;
    this->_isAnyError = false;
  }

  virtual ~DownloadResultCallback() {};
  
  void downloadResult(bool isError, GGS::Downloader::DownloadResults error)
  {
    this->_downloadResultError = error;
    this->_downloadResultCalled = true;
    this->_isAnyError = isError;
    this->_thread->quit();
  }

  virtual void downloadProgress( quint64 current, quint64 total ) 
  {
    this->_totalResponseSize = total;
    this->_downloadProgressCalled = true;
  }

  void setThread(QThread *thread) {this->_thread = thread;}

  virtual void downloadWarning( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_isWarningCalled = true;
  }

  QNetworkReply::NetworkError _networkResult;
  GGS::Downloader::DownloadResults _downloadResultError;
  bool _downloadResultCalled;
  quint64 _totalResponseSize;
  bool _downloadProgressCalled;
  bool _isAnyError;

  bool _isWarningCalled;
private:
  QThread *_thread;
};


class DownloadManagerTest : public ::testing::Test
{
public:
  DownloadManagerTest()
  {
    this->leakChecker.start();
  }

  ~DownloadManagerTest()
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

TEST_F(DownloadManagerTest, downloadUpdateCrcTest)
{
  DownloadManagerTestWorker *test = new DownloadManagerTestWorker();
  QThread *thread = new QThread();
  DownloadResultCallback *resultCallback = new DownloadResultCallback();
  resultCallback->setThread(thread);

  test->setResultCallback(resultCallback);
  test->moveToThread(thread);

  QString uri("http://gnlupdate.tst.local/qgna_memorydownloader_fixture.txt");
  QString testDirectory = QCoreApplication::applicationDirPath();
  testDirectory.append("/DownloadManagerTestWorker");
  QDir dir(testDirectory);
  if(dir.exists(testDirectory)){
    Utils::removeDir(dir);
  }

  dir.mkpath(testDirectory);
  QString testFilePath = testDirectory;
  testFilePath.append("/update.crc");

  QMetaObject::invokeMethod(test, "downloadUpdateCrcTest", Qt::QueuedConnection, Q_ARG(QString, uri), Q_ARG(QString, testFilePath));
  thread->start();
  thread->wait(50000);

  ASSERT_TRUE(resultCallback->_downloadResultCalled);
  ASSERT_TRUE(resultCallback->_downloadProgressCalled);
  ASSERT_FALSE(resultCallback->_isAnyError);

  ASSERT_EQ(44, resultCallback->_totalResponseSize);
  ASSERT_EQ(QNetworkReply::NoError, resultCallback->_downloadResultError);

  delete thread;
  delete test;
  delete resultCallback;

  QFile result(testFilePath);
  result.open(QIODevice::Text | QIODevice::ReadOnly);
  QString downloadedString(result.readAll());

  QString expectedString("Test string. Please do not delete or change.");
  ASSERT_EQ(0, expectedString.compare(downloadedString));
}

TEST_F(DownloadManagerTest, downloadUpdateCrcInSubDirectoryTest)
{
  DownloadManagerTestWorker *test = new DownloadManagerTestWorker();
  QThread *thread = new QThread();
  DownloadResultCallback *resultCallback = new DownloadResultCallback();
  resultCallback->setThread(thread);

  test->setResultCallback(resultCallback);
  test->moveToThread(thread);

  QString uri("http://gnlupdate.tst.local/qgna_memorydownloader_fixture.txt");
  QString testDirectory = QCoreApplication::applicationDirPath();
  testDirectory.append("/DownloadManagerTestWorker");
  QDir dir(testDirectory);
  if(dir.exists(testDirectory)){
    Utils::removeDir(dir);
  }

  dir.mkpath(testDirectory);
  QString testFilePath = testDirectory;
  testFilePath.append("/subdir/update.crc");

  QMetaObject::invokeMethod(test, "downloadUpdateCrcTest", Qt::QueuedConnection, Q_ARG(QString, uri), Q_ARG(QString, testFilePath));
  thread->start();
  thread->wait(50000);

  ASSERT_TRUE(resultCallback->_downloadResultCalled);
  ASSERT_TRUE(resultCallback->_downloadProgressCalled);
  ASSERT_FALSE(resultCallback->_isAnyError);

  ASSERT_EQ(44, resultCallback->_totalResponseSize);
  ASSERT_EQ(QNetworkReply::NoError, resultCallback->_downloadResultError);

  delete thread;
  delete test;
  delete resultCallback;

  QFile result(testFilePath);
  result.open(QIODevice::Text | QIODevice::ReadOnly);
  QString downloadedString(result.readAll());

  QString expectedString("Test string. Please do not delete or change.");
  ASSERT_EQ(0, expectedString.compare(downloadedString));
}

TEST_F(DownloadManagerTest, downloadUpdateCrcTest2)
{
  DownloadManagerTestWorker *test = new DownloadManagerTestWorker();
  QThread *thread = new QThread();
  DownloadResultCallback *resultCallback = new DownloadResultCallback();
  resultCallback->setThread(thread);

  test->setResultCallback(resultCallback);
  test->moveToThread(thread);

  QString uri("http://gnlupdate.tst.local/qgna_memorydownloader_fixture.txt");
  QString testDirectory = QCoreApplication::applicationDirPath();
  testDirectory.append("/DownloadManagerTestWorker");
  QDir dir(testDirectory);
  if(dir.exists(testDirectory)){
    Utils::removeDir(dir);
  }

  dir.mkpath(testDirectory);
  QString testFilePath = testDirectory;
  testFilePath.append("/update.crc");

  QMetaObject::invokeMethod(test, "downloadUpdateCrcTest", Qt::QueuedConnection, Q_ARG(QString, uri), Q_ARG(QString, testFilePath));
  thread->start();
  thread->wait(50000);

  ASSERT_TRUE(resultCallback->_downloadResultCalled);
  ASSERT_TRUE(resultCallback->_downloadProgressCalled);
  ASSERT_FALSE(resultCallback->_isAnyError);

  ASSERT_EQ(44, resultCallback->_totalResponseSize);
  ASSERT_EQ(QNetworkReply::NoError, resultCallback->_downloadResultError);

  delete thread;
  delete test;
  delete resultCallback;

  QFile result(testFilePath);
  result.open(QIODevice::Text | QIODevice::ReadOnly);
  QString downloadedString(result.readAll());

  QString expectedString("Test string. Please do not delete or change.");
  ASSERT_EQ(0, expectedString.compare(downloadedString));
}


TEST_F(DownloadManagerTest, downloadUpdateCrcFailWithEmptyUrlTest)
{
  DownloadManagerTestWorker *test = new DownloadManagerTestWorker();
  QThread *thread = new QThread();
  DownloadResultCallback *resultCallback = new DownloadResultCallback();
  resultCallback->setThread(thread);

  test->setResultCallback(resultCallback);
  test->moveToThread(thread);

  QString testDirectory = QCoreApplication::applicationDirPath();
  testDirectory.append("/DownloadManagerTestWorker");
  QDir dir(testDirectory);
  if(dir.exists(testDirectory)){
    Utils::removeDir(dir);
  }

  dir.mkpath(testDirectory);
  QString testFilePath = testDirectory;
  testFilePath.append("/update.crc");

  QMetaObject::invokeMethod(test, "downloadUpdateCrcTest", Qt::QueuedConnection, Q_ARG(QString, 0), Q_ARG(QString, testFilePath));

  thread->start();
  thread->wait(50000);

  ASSERT_TRUE(resultCallback->_isAnyError);
  ASSERT_TRUE(resultCallback->_downloadResultCalled);
  ASSERT_FALSE(resultCallback->_downloadProgressCalled);
  ASSERT_EQ(GGS::Downloader::BadUrl, resultCallback->_downloadResultError);
  //ASSERT_EQ(QNetworkReply::NetworkError::UnknownNetworkError, test.getNetwork
  //  resultCallback->_downloadResultError);

  delete thread;
  delete test;
  delete resultCallback;
}

TEST_F(DownloadManagerTest, downloadUpdateCrcFailWithEmptyFileTest)
{
  DownloadManagerTestWorker *test = new DownloadManagerTestWorker();
  QThread *thread = new QThread();
  DownloadResultCallback *resultCallback = new DownloadResultCallback();
  resultCallback->setThread(thread);

  test->setResultCallback(resultCallback);
  test->moveToThread(thread);

  QString uri("http://gnlupdate.tst.local/qgna_memorydownloader_fixture.txt");
  QMetaObject::invokeMethod(test, "downloadUpdateCrcTest", Qt::QueuedConnection, Q_ARG(QString, uri), Q_ARG(QString, 0));

  thread->start();
  thread->wait(50000);

  ASSERT_TRUE(resultCallback->_isAnyError);
  ASSERT_TRUE(resultCallback->_downloadResultCalled);
  ASSERT_FALSE(resultCallback->_downloadProgressCalled);
  ASSERT_EQ(GGS::Downloader::CanNotOpenTargetFile, resultCallback->_downloadResultError);

  delete thread;
  delete test;
  delete resultCallback;

}
#endif // _GGS_DOWNLOAD_MANAGER_TEST_H_