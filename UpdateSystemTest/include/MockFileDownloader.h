#pragma once

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include <UpdateSystem/Downloader/filedownloaderinterface.h>
#include <UpdateSystem/Downloader/DownloadResultInterface.h>

class MockFileDownloader: public QObject,
                          public P1::Downloader::FileDownloaderInterface
{
  Q_OBJECT

public:
  MockFileDownloader(void);
  virtual ~MockFileDownloader(void);

  void addDownloadeInfo(const QString& expectedUrl, const QString& pathToFakeFile);

  virtual void downloadFile( const QString& url,const QString& filePath );
  virtual void setResultCallback( P1::Downloader::DownloadResultInterface *result );
  virtual QNetworkReply::NetworkError getNetworkError() { return this->_networkError; }
  
signals:
  void downloadComplited();
  void downloadError( QNetworkReply::NetworkError error );

private:
  QNetworkReply::NetworkError _networkError;
  QHash<QString, QString> _fakeFiles;
  P1::Downloader::DownloadResultInterface *_resultCallback;
};
