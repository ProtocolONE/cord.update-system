#ifndef _GGS_TEST_UPDATE_MANAGER_TEST_WORKER_H_
#define _GGS_TEST_UPDATE_MANAGER_TEST_WORKER_H_

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

  GGS::UpdateSystem::UpdateManager *_target;
public slots:
  void doSimpleTest();
};

#endif // _GGS_TEST_UPDATE_MANAGER_TEST_WORKER_H_