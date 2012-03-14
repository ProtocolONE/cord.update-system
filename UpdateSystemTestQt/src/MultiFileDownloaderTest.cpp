#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "Downloader/MultiDownloadResultInterface.h"
#include "Downloader/MultiFileDownloader.h"
#include "Downloader/filedownloaderinterface.h"
#include "Downloader/DownloadResultInterface.h"

class MultiFileDownloaderTest : public ::testing::Test
{
public:
  MultiFileDownloaderTest()
  {
    this->leakChecker.start();
  }

  ~MultiFileDownloaderTest()
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

class MultiFileDownloaderTest_MockMultiFileDownloaderResult 
  : public GGS::Downloader::MultiFileDownloadResultInterface
{
public:
  MultiFileDownloaderTest_MockMultiFileDownloaderResult() {
    this->_resultCalledCount = 0;
    this->_warningCalledCount = 0;
    this->_progressCalledCount = 0;
    this->_fileDownloadedCount = 0;
  }

  ~MultiFileDownloaderTest_MockMultiFileDownloaderResult() {};

  virtual void downloadResult( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_resultCalledCount++;
    this->_downloadResult = error;
  }

  virtual void downloadProgress( quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize ) 
  {
    this->_progressCalledCount++;
    this->_progresList << currestFileSize;
    this->_totalProgresList << downloadSize;
  }

  virtual void downloadWarning( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_warningCalledCount++;
    this->_warningResult = error;
  }

  virtual void fileDownloaded(const QString& filePath) 
  {
    this->_fileDownloadedCount++;
  }

  quint64 _resultCalledCount;
  quint64 _warningCalledCount;
  quint64 _progressCalledCount;
  quint64 _fileDownloadedCount;

  GGS::Downloader::DownloadResults _downloadResult;
  GGS::Downloader::DownloadResults _warningResult;

  QList<quint64> _progresList;
  QList<quint64> _totalProgresList;
};

class MultiFileDownloaderTest_MockFileDownloaderResult : public GGS::Downloader::DownloadResultInterface{
public:
  MultiFileDownloaderTest_MockFileDownloaderResult() {
    this->_resultCalledCount = 0;
    this->_warningCalledCount = 0;
    this->_progressCalledCount = 0;
  }

  ~MultiFileDownloaderTest_MockFileDownloaderResult(){}

  virtual void downloadResult( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_resultCalledCount++;
    this->_downloadResult = error;
  }

  virtual void downloadProgress( quint64 current, quint64 total ) 
  {
    this->_progressCalledCount++;
  }

  virtual void downloadWarning( bool isError, GGS::Downloader::DownloadResults error ) 
  {
    this->_warningCalledCount++;
    this->_warningResult = error;
  }

  quint32 _resultCalledCount;
  quint32 _warningCalledCount;
  quint32 _progressCalledCount;

  GGS::Downloader::DownloadResults _downloadResult;
  GGS::Downloader::DownloadResults _warningResult;
};

class MultiFileDownloaderTest_FailDownloader 
  : public GGS::Downloader::FileDownloaderInterface {
public:
  MultiFileDownloaderTest_FailDownloader() { this->_isFail = false; }
  ~MultiFileDownloaderTest_FailDownloader() {}

  virtual void setResultCallback( GGS::Downloader::DownloadResultInterface *result ) 
  {
    this->_resultCallback = result;
  }

  virtual void downloadFile( const QString& url,const QString& filePath ) 
  {
    if(!this->_isFail && this->_fakeFiles.contains(url)) {
      for (int i = 0; i < this->_warningCount; i++) {
        this->_resultCallback->downloadWarning(true, GGS::Downloader::NetworkErrok);
      }

      quint64 t = this->_fakeFiles[url];
      this->_resultCallback->downloadProgress(t, t);
      this->_resultCallback->downloadResult(false, GGS::Downloader::NoError);
    } else {
      this->_networkError = QNetworkReply::UnknownNetworkError;
      this->_resultCallback->downloadResult(true, GGS::Downloader::NetworkErrok);
    }
  }

  void setFail (bool isFail) { this->_isFail = isFail; } 
  void setWarningCount( quint64 warningCount ) { this->_warningCount = warningCount; }
  virtual QNetworkReply::NetworkError getNetworkError() { return this->_networkError; }
  virtual void addFile(const QString& url, quint64 fileSize) { this->_fakeFiles[url] = fileSize; }
  
  quint64 _warningCount;
  bool _isFail;
  QHash<QString, quint64 > _fakeFiles;
  QHash<QString, quint64 > _fakeFilesFailCount;
  GGS::Downloader::DownloadResultInterface *_resultCallback;
  QNetworkReply::NetworkError _networkError;
};


TEST_F(MultiFileDownloaderTest, FailTest)
{
  GGS::Downloader::MultiFileDownloader multidownloader;
  
  MultiFileDownloaderTest_FailDownloader failDownloader;
  MultiFileDownloaderTest_MockMultiFileDownloaderResult multiResult;
  MultiFileDownloaderTest_MockFileDownloaderResult result;

  failDownloader.setFail(true);
  multidownloader.addFile(QString("some url"), QString("some file"));
  multidownloader.setDownloader(&failDownloader);
  multidownloader.setResultCallback(&multiResult);
  multidownloader.start();
  
  ASSERT_EQ(1, multiResult._resultCalledCount);
  ASSERT_EQ(GGS::Downloader::NetworkErrok, multiResult._downloadResult);
}

TEST_F(MultiFileDownloaderTest, GoodTest)
{
  GGS::Downloader::MultiFileDownloader multidownloader;

  MultiFileDownloaderTest_FailDownloader failDownloader;
  MultiFileDownloaderTest_MockMultiFileDownloaderResult multiResult; 
  MultiFileDownloaderTest_MockFileDownloaderResult result;

  failDownloader.setFail(false);
  failDownloader.setWarningCount(2);

  failDownloader.addFile(QString("file1"), 10);
  failDownloader.addFile(QString("file2"), 20);
  failDownloader.addFile(QString("file3"), 30);

  multidownloader.addFile(QString("file1"), QString("file4"));
  multidownloader.addFile(QString("file2"), QString("file5"));
  multidownloader.addFile(QString("file3"), QString("file6"));
  multidownloader.setDownloader(&failDownloader);
  multidownloader.setResultCallback(&multiResult);
  multidownloader.start();

  ASSERT_EQ(3, multiResult._fileDownloadedCount);
  ASSERT_EQ(1, multiResult._resultCalledCount);
  ASSERT_EQ(GGS::Downloader::NoError, multiResult._downloadResult);
  
  ASSERT_EQ(10, multiResult._progresList[0]);
  ASSERT_EQ(20, multiResult._progresList[1]);
  ASSERT_EQ(30, multiResult._progresList[2]);
  
  ASSERT_EQ(10, multiResult._totalProgresList[0]);
  ASSERT_EQ(30, multiResult._totalProgresList[1]);
  ASSERT_EQ(60, multiResult._totalProgresList[2]);
  
  ASSERT_EQ(6, multiResult._warningCalledCount);
}
