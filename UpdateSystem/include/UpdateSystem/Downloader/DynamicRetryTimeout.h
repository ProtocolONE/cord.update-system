#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Downloader/RetryTimeoutInterface.h>

#include <QtCore/QObject>
#include <QtCore/QList>

namespace P1 {
  namespace Downloader {
    class UPDATESYSTEMSHARED_EXPORT DynamicRetryTimeout : 
      public QObject,
      public RetryTimeoutInterface
    {
      Q_OBJECT
    public:
      explicit DynamicRetryTimeout(QObject *parrent = 0);
      virtual ~DynamicRetryTimeout();

      virtual int getTimeout( int retryCount );
      void addTimeout(int timeout);

      enum { InfinityRetryCount = -1};

      UPDATESYSTEMSHARED_EXPORT friend DynamicRetryTimeout& operator<< (DynamicRetryTimeout&, qint32 timeout);

    private:
      QList<int> _timeouts;
    };

  }
}
