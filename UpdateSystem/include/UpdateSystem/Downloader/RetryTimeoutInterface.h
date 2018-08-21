#pragma once

#include <UpdateSystem/UpdateSystem_global.h>

namespace P1 {
  namespace Downloader {
    class UPDATESYSTEMSHARED_EXPORT RetryTimeoutInterface 
    {
    public:
      virtual ~RetryTimeoutInterface() {}
      virtual int getTimeout(int retryCount) = 0;
    };
  }
}
