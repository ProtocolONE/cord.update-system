#pragma once

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QThread>

#include <UpdateSystem/Downloader/MemoryDownloader.h>

class DownloadInMemoryTestWorker :
  public QObject
{
  Q_OBJECT
public:
  DownloadInMemoryTestWorker(void);
  virtual ~DownloadInMemoryTestWorker(void);

  P1::Downloader::MemoryDownloader *_downloader;
  QByteArray _response;
  bool IsFinished;
public slots:
  void slotStartDowloadFixtureTest();

  void slotFixtureDowloadComplite();
  
  void slotFailDownloadTest();

  void slotTestShouldNotComplite();
  void slotTestShoulFail();
};
