#include "UpdateManagerTestWorker.h"


UpdateManagerTestWorker::UpdateManagerTestWorker(QObject *parrent)
  : QObject(parrent)
{
}


UpdateManagerTestWorker::~UpdateManagerTestWorker(void)
{
}

void UpdateManagerTestWorker::doSimpleTest()
{
  this->_target->checkUpdate();
}
