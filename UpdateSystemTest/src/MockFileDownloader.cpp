#include "MockFileDownloader.h"


MockFileDownloader::MockFileDownloader(void)
{
}


MockFileDownloader::~MockFileDownloader(void)
{
}

void MockFileDownloader::downloadFile( const QString& url,const QString& filePath )
{
  if(this->_fakeFiles.contains(url)) {
    QString fakeFilePath = this->_fakeFiles[url];
    if(!QFile::exists(fakeFilePath)) {
      this->_networkError = QNetworkReply::HostNotFoundError;
        this->_resultCallback->downloadResult(true, GGS::Downloader::NetworkErrok);
        return;
    }

    if(QFile::exists(filePath)) {
      if(!QFile::remove(filePath)) {
        this->_networkError = QNetworkReply::ContentOperationNotPermittedError;
        this->_resultCallback->downloadResult(true, GGS::Downloader::NetworkErrok);
        return;
      }
    }

    if(!QFile::copy(fakeFilePath, filePath)) {
      this->_networkError = QNetworkReply::ContentOperationNotPermittedError;
      this->_resultCallback->downloadResult(true, GGS::Downloader::NetworkErrok);
    } else {
      QFileInfo fileInfo(filePath);
      quint64 fileSize = fileInfo.size();

      this->_resultCallback->downloadProgress(0, fileSize);
      this->_resultCallback->downloadProgress(fileSize, fileSize);
      this->_networkError = QNetworkReply::NoError;
      this->_resultCallback->downloadResult(false, GGS::Downloader::NoError);
    }

  } else {
    this->_networkError = QNetworkReply::HostNotFoundError;
    this->_resultCallback->downloadResult(true, GGS::Downloader::NetworkErrok);
  }
}


void MockFileDownloader::addDownloadeInfo( const QString& expectedUrl, const QString& pathToFakeFile )
{
  this->_fakeFiles[expectedUrl] = pathToFakeFile;
}

void MockFileDownloader::setResultCallback( GGS::Downloader::DownloadResultInterface *result )
{
  this->_resultCallback = result;
}
