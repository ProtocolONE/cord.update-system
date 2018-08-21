#pragma once

#include <UpdateSystem/updatemanager.h>
#include <UpdateSystem/UpdateInfoGetterInterface.h>
#include <UpdateSystem/UpdateInfoGetterResultInterface.h>
#include <UpdateSystem/UpdateInfoGetter.h>
#include <UpdateSystem/Extractor/SevenZipExtractor.h>
#include <UpdateSystem/Downloader/RetryFileDownloader.h>
#include <UpdateSystem/Downloader/downloadmanager.h>
#include <UpdateSystem/Downloader/MultiFileDownloader.h>
#include <UpdateSystem/Hasher/Md5FileHasher.h>

#include <QtCore/QObject>

class UpdateManagerTestWorker : public QObject
{
  Q_OBJECT
public:
  UpdateManagerTestWorker(QObject *parrent = 0);
  virtual ~UpdateManagerTestWorker(void);

  P1::UpdateSystem::UpdateManager *_target;
public slots:
  void doSimpleTest();
};
