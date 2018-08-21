#pragma once

#include "UpdateSystem_global.h"
#include "UpdateInfoContainer.h"

namespace P1 {
  namespace UpdateSystem {

    class UPDATESYSTEMSHARED_EXPORT UpdateInstallerInterface {
    public:
      ~UpdateInstallerInterface() {}
      virtual void installUpdate(UpdateInfoContainer *changedInfo) = 0;
      virtual void clearOldFiles() = 0;
    };

  }
}
