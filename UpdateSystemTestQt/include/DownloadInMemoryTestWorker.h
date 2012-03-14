#ifndef _GGS_TEST_UTILS_DOWNLOAD_IN_MEMORY_WORKER_H_
#define _GGS_TEST_UTILS_DOWNLOAD_IN_MEMORY_WORKER_H_

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QThread>

#include "Downloader/MemoryDownloader.h"


class DownloadInMemoryTestWorker :
  public QObject
{
  Q_OBJECT
public:
  DownloadInMemoryTestWorker(void);
  virtual ~DownloadInMemoryTestWorker(void);

  GGS::Downloader::MemoryDownloader *_downloader;
  QByteArray _response;
  bool IsFinished;
public slots:
  void slotStartDowloadFixtureTest();

  void slotFixtureDowloadComplite();
  
  void slotFailDownloadTest();

  void slotTestShouldNotComplite();
  void slotTestShoulFail();
};

#endif // _GGS_TEST_UTILS_DOWNLOAD_IN_MEMORY_WORKER_H_