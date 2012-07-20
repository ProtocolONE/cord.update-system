/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Downloader/DynamicRetryTimeout.h>

namespace GGS {
  namespace Downloader {

    DynamicRetryTimeout::DynamicRetryTimeout(QObject *parrent)
      : QObject(parrent)
    {
    }

    DynamicRetryTimeout::~DynamicRetryTimeout()
    {
    }

    int DynamicRetryTimeout::getTimeout(int retryCount)
    {
      int maxTimeoutIndex = this->_timeouts.count() - 1;
      if (maxTimeoutIndex < 0)
        return 0;

      int i = retryCount - 1;

      if (i < 0)
        return 0;

      if (i > maxTimeoutIndex)
        return this->_timeouts[maxTimeoutIndex];

      return this->_timeouts[i];
    }

    void DynamicRetryTimeout::addTimeout(int timeout)
    {
      this->_timeouts.append(timeout);
    }

    DynamicRetryTimeout& operator<< (DynamicRetryTimeout& dynamicTimout, qint32 timeout)
    {
      dynamicTimout._timeouts.append(timeout);
      return dynamicTimout;
    }
  }

}