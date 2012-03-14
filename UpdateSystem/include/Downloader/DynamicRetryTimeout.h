/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATATESYSTEM_DOWNLOADER_DYNAMIC_RETRY_TIMEOUT_H_
#define _GGS_UPDATATESYSTEM_DOWNLOADER_DYNAMIC_RETRY_TIMEOUT_H_

#include <QtCore/QObject>
#include <QtCore/QList>
#include "UpdateSystem_global.h"
#include "Downloader/RetryTimeoutInterface.h"

namespace GGS {
  namespace Downloader {
    class UPDATESYSTEMSHARED_EXPORT DynamicRetryTimeout : 
      public QObject,
      public RetryTimeoutInterface
    {
      Q_OBJECT
    public:
      explicit DynamicRetryTimeout(QObject *parrent = 0);
      virtual ~DynamicRetryTimeout(void);

      virtual int getTimeout( int retryCount );
      void addTimeout( int timeout ) { this->_timeouts.append(timeout); }

      enum { InfinityRetryCount = -1};

    private:
      QList<int> _timeouts;
    };

  }
}
#endif