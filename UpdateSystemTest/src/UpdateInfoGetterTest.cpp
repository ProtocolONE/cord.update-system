
#include <UpdateSystem/Extractor/SevenZipExtractor.h>
#include <UpdateSystem/UpdateInfoGetter.h>
#include <UpdateSystem/UpdateInfoContainer.h>

#include <gtest/gtest.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QTextStream>

#include "MemoryLeaksChecker.h"
#include "MockFileDownloader.h"


bool RemoveDirectoryFull(QDir &aDir);

class MockUpdateInfoGetterResult : public P1::UpdateSystem::UpdateInfoGetterResultInterface
{
public:
  MockUpdateInfoGetterResult() { this->_resultCount = 0; }
  ~MockUpdateInfoGetterResult() {};

  virtual void updateInfoCallback(P1::UpdateSystem::UpdateInfoGetterResults result ) 
  {
    this->_resultCount++;
    this->_result = result;
  }

  virtual void infoGetterUpdateProggress(quint64 current, quint64 total)
  {
  }
    
  P1::UpdateSystem::UpdateInfoGetterResults _result;
  int _resultCount;
};

class MockSevenZipExtractor : public P1::Extractor::ExtractorInterface
{
public:
  MockSevenZipExtractor(P1::Extractor::ExtractorInterface *extractor) {
    this->_extractor = extractor;
  }
  virtual ~MockSevenZipExtractor() {

  };

  virtual P1::Extractor::ExtractionResult extract( const QString& archivePath, const QString& extractDirectory ) 
  {
    // TODO: add checks
    return this->_extractor->extract(archivePath, extractDirectory);
  }

  P1::Extractor::ExtractorInterface *_extractor;
};

class MockSimpleStringDownloader : public P1::Downloader::FileDownloaderInterface
{
public:
  ~MockSimpleStringDownloader() {};


  virtual void setResultCallback( P1::Downloader::DownloadResultInterface *result ) 
  {
    this->_resultCallback = result;
  }

  virtual void downloadFile( const QString& url,const QString& filePath ) 
  {
    if(!this->_fakeFiles.contains(url)) {
      this->_networkError = QNetworkReply::HostNotFoundError;
      this->_resultCallback->downloadResult(true, P1::Downloader::NetworkErrok);
      return;
    }

    if(QFile::exists(filePath)) {
      if(!QFile::remove(filePath)) {
        this->_networkError = QNetworkReply::ContentOperationNotPermittedError;
        this->_resultCallback->downloadResult(true, P1::Downloader::NetworkErrok);
        return;
      }
    }

    QFile outputFile(filePath);
    outputFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&outputFile);
    out << this->_fakeFiles[url];
    outputFile.close();
    this->_networkError = QNetworkReply::NoError;
    this->_resultCallback->downloadResult(false, P1::Downloader::NoError);
  }

  void addDownloadeInfo(const QString& expectedUrl, const QString& fakeContent)
  {
    this->_fakeFiles[expectedUrl] = fakeContent;
  }

  virtual QNetworkReply::NetworkError getNetworkError() { return this->_networkError; }

private:
  QNetworkReply::NetworkError _networkError;
  QHash<QString, QString> _fakeFiles;
  P1::Downloader::DownloadResultInterface *_resultCallback;
};

class MockSimpleCopyExtractor : public P1::Extractor::ExtractorInterface
{
public:
  ~MockSimpleCopyExtractor() {};
  virtual P1::Extractor::ExtractionResult extract( const QString& archivePath, const QString& extractDirectory ) 
  {
    if(!QFile::exists(archivePath)) {
      return P1::Extractor::NoArchive;
    }

    QFileInfo fileInfo(archivePath);
    QString fileName = fileInfo.fileName();

    if (fileName.endsWith(".7z", Qt::CaseInsensitive)) {
      fileName.remove(fileName.length() - 3, 3);
    }

    QString targetFilePath = extractDirectory;
    targetFilePath.append("/");
    targetFilePath.append(fileName);

    if (QFile::exists(targetFilePath)) {
      if (!QFile::remove(targetFilePath)) {
        return P1::Extractor::WriteError;
      }
    }

    if (!QFile::copy(archivePath, targetFilePath)) {
       return P1::Extractor::WriteError;
    }

    return P1::Extractor::NoError;
  }
};

class UpdateInfoGetterTest : public ::testing::Test
{
public:
  UpdateInfoGetterTest()
  {
    this->leakChecker.start();
  }

  ~UpdateInfoGetterTest()
  {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest(std::string("Memory leak detected!").c_str());  
  }


  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    this->appDir = QCoreApplication::applicationDirPath();
    this->workingDir = this->appDir;
    this->workingDir.append("/UpdateInfoGetterTest");

    QDir dir(this->workingDir);
    if(dir.exists(this->workingDir)){
      RemoveDirectoryFull(dir);
    }

    dir.mkpath(this->workingDir);

    this->fixture = this->appDir;
    fixture.append("/UpdateSystemTestFixtures");

  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  void XmlUpdateCrcTest(const QString& xmlContent, P1::UpdateSystem::UpdateInfoGetterResults expectedError) 
  {
    MockSimpleStringDownloader downloader;
    downloader.addDownloadeInfo("http://fs0.protocol.one/update/gna/live/update.crc.7z", xmlContent);
    MockSimpleCopyExtractor extractor;
    MockUpdateInfoGetterResult getterResult;

    P1::UpdateSystem::UpdateInfoGetter getter;
    getter.setCurrentDir(QCoreApplication::applicationDirPath());
    getter.setUpdateFileName("update.crc");
    getter.setUpdateCrcUrl(QString("http://fs0.protocol.one/update/gna/live/update.crc.7z"));
    getter.setDownloader(&downloader);
    getter.setExtractor(&extractor);
    getter.setResultCallback(&getterResult);
    getter.start();

    ASSERT_EQ(1, getterResult._resultCount);
    ASSERT_EQ(expectedError, getterResult._result);
  }

  QString appDir;
  QString workingDir;
  QString fixture;
private: 
  void failTest(const char* message) 
  { 
    FAIL() << message; delete message;
  }


  MemoryLeaksChecker leakChecker;
};


TEST_F(UpdateInfoGetterTest, DISABLED_NormalUpdateCrcArchiveTest)
{
  MockFileDownloader *downloader = new MockFileDownloader();

  QString updateCrcFile = this->fixture;
  updateCrcFile.append("/fullpack/update.crc.7z");

  // Добавляем в доунлоадер update.crc
  downloader->addDownloadeInfo("http://fs0.protocol.one/update/gna/live/update.crc.7z", updateCrcFile);

  P1::Extractor::SevenZipExtactor *extractor = new P1::Extractor::SevenZipExtactor();
  MockSevenZipExtractor mockExtractor(extractor);

  P1::UpdateSystem::UpdateInfoGetter *getter = new P1::UpdateSystem::UpdateInfoGetter();

  MockUpdateInfoGetterResult getterResult;
  getter->setCurrentDir(QCoreApplication::applicationDirPath());
  getter->setUpdateFileName("update.crc");
  getter->setUpdateCrcUrl(QString("http://fs0.protocol.one/update/gna/live/update.crc.7z"));
  getter->setDownloader(downloader);
  getter->setExtractor(&mockExtractor);
  getter->setResultCallback(&getterResult);
  getter->start();

  ASSERT_EQ(P1::Downloader::NoError, getterResult._result);
  const QList<P1::UpdateSystem::UpdateFileInfo*>* files = getter->updateInfo()->getFiles();

  ASSERT_EQ(3, files->count());
  QList<P1::UpdateSystem::UpdateFileInfo*>::const_iterator end = files->end();
  int goodResultCount  = 0;
  QString file1("file1.txt");
  QString file2("file2.txt");
  QString file3 = QString::fromLocal8Bit("Папкасфайлами\\файл.txt");

  for (QList<P1::UpdateSystem::UpdateFileInfo*>::const_iterator it = files->begin(); it != end; ++it) {
    if((*it)->relativePath().compare(file1) == 0) {
      if((*it)->hash().compare("826e8142e6baabe8af779f5f490cf5f5") == 0
        && (*it)->rawLength() == 5
        && (*it)->archiveLength() == 124
        && (*it)->forceCheck() == false) {
          goodResultCount++;
      } 
    }

    if((*it)->relativePath().compare(file2) == 0) {
      if((*it)->hash().compare("1c1c96fd2cf8330db0bfa936ce82f3b9") == 0
        && (*it)->rawLength() == 5
        && (*it)->archiveLength() == 124
        && (*it)->forceCheck() == false) {
          goodResultCount++;
      } 
    }

    if((*it)->relativePath().compare(file3) == 0) {
      if((*it)->hash().compare("904e31b6ec0a385280fb78688901d2f6") == 0
        && (*it)->rawLength() == 13
        && (*it)->archiveLength() == 130
        && (*it)->forceCheck() == false) {
          goodResultCount++;
      } 
    }
  }

  ASSERT_EQ(3, goodResultCount);

  delete downloader;
  delete extractor;
  delete getter;
}

TEST_F(UpdateInfoGetterTest, BadXmlTest1)
{
   P1::UpdateSystem::UpdateInfoGetterResults xmlError = P1::UpdateSystem::XmlContentError;
   this->XmlUpdateCrcTest("", xmlError);
   this->XmlUpdateCrcTest("<xml>", xmlError);
   this->XmlUpdateCrcTest("<xml><root></root>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><root></root>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file /></files></UpdateFileList>", xmlError);

   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><root></rootA>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList></UpdateFileListA>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files></filesA></UpdateFileList>", xmlError);

   // Отсутствие какого либо из аттрибутов
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"1147688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" rawLength=\"2780456\" archiveLength=\"1147688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" archiveLength=\"1147688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"1147688\"/></files></UpdateFileList>", xmlError);

   // Плохи атрибуты числа/или булеаны
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"278a0456\" archiveLength=\"1147688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"-2780456\" archiveLength=\"1147688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"1147df688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"-1147688\" check=\"true\" /></files></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"1147688\" check=\"t2rue\" /></files></UpdateFileList>", xmlError);

   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"1147688\" check=\"true\" /></UpdateFileList>", xmlError);
   this->XmlUpdateCrcTest("<?xml version=\"1.0\" encoding=\"utf-8\"?><UpdateFileList><files><file path=\"ProtocolOne.exe\" crc=\"a26883cf98a9f120a3136cf9dd7abe33\" rawLength=\"2780456\" archiveLength=\"1147688\" check=\"true\" /></files></UpdateFileList>", P1::UpdateSystem::NoError);

}

TEST_F(UpdateInfoGetterTest, CanNotDownload)
{
  MockSimpleStringDownloader downloader;
  MockSimpleCopyExtractor extractor;
  MockUpdateInfoGetterResult getterResult;

  P1::UpdateSystem::UpdateInfoGetter getter;
  getter.setCurrentDir(QCoreApplication::applicationDirPath());
  getter.setUpdateFileName("update.crc");
  getter.setUpdateCrcUrl(QString("http://fs0.protocol.one/update/gna/live/update.crc.7z"));
  getter.setDownloader(&downloader);
  getter.setExtractor(&extractor);
  getter.setResultCallback(&getterResult);
  getter.start();

  ASSERT_EQ(1, getterResult._resultCount);
  ASSERT_EQ(P1::UpdateSystem::DownloadError, getterResult._result);

}

TEST_F(UpdateInfoGetterTest, NoDownloader)
{
  MockSimpleCopyExtractor extractor;
  MockUpdateInfoGetterResult getterResult;

  P1::UpdateSystem::UpdateInfoGetter getter;
  getter.setDownloader(0);
  getter.setCurrentDir(QCoreApplication::applicationDirPath());
  getter.setUpdateFileName("update.crc");
  getter.setUpdateCrcUrl(QString("http://fs0.protocol.one/update/gna/live/update.crc.7z"));
  getter.setExtractor(&extractor);
  getter.setResultCallback(&getterResult);
  getter.start();

  ASSERT_EQ(1, getterResult._resultCount);
  ASSERT_EQ(P1::UpdateSystem::BadArguments, getterResult._result);
}

TEST_F(UpdateInfoGetterTest, NoExtractor)
{
  MockSimpleStringDownloader downloader;
  MockUpdateInfoGetterResult getterResult;

  P1::UpdateSystem::UpdateInfoGetter getter;
  getter.setDownloader(&downloader);
  getter.setCurrentDir(QCoreApplication::applicationDirPath());
  getter.setUpdateFileName("update.crc");
  getter.setUpdateCrcUrl(QString("http://fs0.protocol.one/update/gna/live/update.crc.7z"));
  getter.setExtractor(0);
  getter.setResultCallback(&getterResult);
  getter.start();

  ASSERT_EQ(1, getterResult._resultCount);
  ASSERT_EQ(P1::UpdateSystem::BadArguments, getterResult._result);
}