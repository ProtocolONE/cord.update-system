
#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include <UpdateSystem/Downloader/DownloadResultInterface.h>
#include <UpdateSystem/Downloader/DynamicRetryTimeout.h>
#include <UpdateSystem/Downloader/RetryFileDownloader.h>

class RetryFileDownloaderTest : public ::testing::Test
{
public:
  RetryFileDownloaderTest()
  {
    this->leakChecker.start();
  }

  ~RetryFileDownloaderTest()
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

class MockFailDownloader : public GGS::Downloader::FileDownloaderInterface {
public:
  MockFailDownloader() { this->_failCount = 0; this->_retryCount = 0; }
  ~MockFailDownloader() {}

  virtual void setResultCallback( GGS::Downloader::DownloadResultInterface *result ) 
  {
    this->_resultCallback = result;
  }

  virtual void downloadFile( const QString& url,const QString& filePath ) 
  {
    if(this->_failCount <= 0) {
      this->_resultCallback->downloadResult(false, GGS::Downloader::NoError);
      return;
    }

    this->_retryCount++;
    if(this->_retryCount <= this->_failCount) {
      this->_networkError = QNetworkReply::UnknownNetworkError;
      this->_resultCallback->downloadResult(true, GGS::Downloader::NetworkErrok);
    } else {
      this->_resultCallback->downloadResult(false, GGS::Downloader::NoError);
    }
  }

  void setFailCountBeforeGood(int count) { this->_failCount = count; }

  virtual QNetworkReply::NetworkError getNetworkError() { return this->_networkError; }

private:
  int _failCount;
  int _retryCount;
  QHash<QString, QString> _fakeFiles;
  GGS::Downloader::DownloadResultInterface *_resultCallback;
  QNetworkReply::NetworkError _networkError;
};

class MockFailDownloadResultCallback : public GGS::Downloader::DownloadResultInterface
{
public:
  MockFailDownloadResultCallback() 
  : _resultCount(0)
  , _warningCount(0)
  , _lastError(GGS::Downloader::NoError)
  , _lastWarning(GGS::Downloader::NoError)
  { 
  }

  ~MockFailDownloadResultCallback() {}

  virtual void downloadResult( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_resultCount++;
    this->_lastError = error;
  }

  virtual void downloadProgress( quint64 current, quint64 total ) 
  {
  }

  virtual void downloadWarning( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_warningCount++;
    this->_lastWarning = error;
  }

  int _resultCount;
  int _warningCount;
  GGS::Downloader::DownloadResults _lastError;
  GGS::Downloader::DownloadResults _lastWarning;
};

TEST_F(RetryFileDownloaderTest, NormalTest)
{
  GGS::Downloader::RetryFileDownloader target;
  MockFailDownloadResultCallback retryResult;
  GGS::Downloader::DynamicRetryTimeout timeout;
  MockFailDownloader downloader;
  downloader.setFailCountBeforeGood(0);
  
  target.setTimeout(&timeout);

  target.setDownloader(&downloader);
  target.setResultCallback(&retryResult);

  target.downloadFile(QString("qwe"), QString("asd"));

  ASSERT_EQ(QNetworkReply::NoError, retryResult._lastError);
  ASSERT_EQ(1, retryResult._resultCount);
}

TEST_F(RetryFileDownloaderTest, SingleFailThenGood)
{
  GGS::Downloader::RetryFileDownloader target;
  MockFailDownloadResultCallback retryResult;
  GGS::Downloader::DynamicRetryTimeout timeout;
  MockFailDownloader downloader;
  downloader.setFailCountBeforeGood(3);

  target.setMaxRetry(5);
  target.setTimeout(&timeout);

  target.setDownloader(&downloader);
  target.setResultCallback(&retryResult);

  target.downloadFile(QString("qwe"), QString("asd"));

  ASSERT_EQ(QNetworkReply::NoError, retryResult._lastError);
  ASSERT_EQ(3, retryResult._warningCount);
  ASSERT_EQ(1, retryResult._resultCount);
}

TEST_F(RetryFileDownloaderTest, FailSingleTry)
{
  GGS::Downloader::RetryFileDownloader target;
  MockFailDownloadResultCallback retryResult;
  GGS::Downloader::DynamicRetryTimeout timeout;
  MockFailDownloader downloader;
  downloader.setFailCountBeforeGood(5);

  target.setMaxRetry(2);
  target.setTimeout(&timeout);

  target.setDownloader(&downloader);
  target.setResultCallback(&retryResult);

  target.downloadFile(QString("qwe"), QString("asd"));

  ASSERT_EQ(GGS::Downloader::NetworkErrok, retryResult._lastError);
  ASSERT_EQ(1, retryResult._resultCount);
  ASSERT_EQ(1, retryResult._warningCount);
}