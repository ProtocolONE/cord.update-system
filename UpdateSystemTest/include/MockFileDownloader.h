#ifndef _GGS_UPDATESYSTEM_TEST_MOCK_FILE_DOWNLOADER_H_
#define _GGS_UPDATESYSTEM_TEST_MOCK_FILE_DOWNLOADER_H_

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#include "Downloader/FileDownloaderInterface.h"
#include "Downloader/DownloadResultInterface.h"

class MockFileDownloader :  public QObject,
                            public GGS::Downloader::FileDownloaderInterface
{
  Q_OBJECT

public:
  MockFileDownloader(void);
  virtual ~MockFileDownloader(void);

  void addDownloadeInfo(const QString& expectedUrl, const QString& pathToFakeFile);

  virtual void downloadFile( const QString& url,const QString& filePath );
  virtual void setResultCallback( GGS::Downloader::DownloadResultInterface *result );
  virtual QNetworkReply::NetworkError getNetworkError() { return this->_networkError; }
  
signals:
  void downloadComplited();
  void downloadError( QNetworkReply::NetworkError error );

private:
  QNetworkReply::NetworkError _networkError;
  QHash<QString, QString> _fakeFiles;
  GGS::Downloader::DownloadResultInterface *_resultCallback;
};

#endif // _GGS_UPDATESYSTEM_TEST_MOCK_FILE_DOWNLOADER_H_