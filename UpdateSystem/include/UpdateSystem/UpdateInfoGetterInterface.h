#pragma once

#include "UpdateInfoGetterResultInterface.h"
#include "UpdateInfoContainer.h"

namespace P1 { 
  namespace UpdateSystem {

    class UpdateInfoGetterInterface {
    public:
      ~UpdateInfoGetterInterface() {}
      virtual void start() = 0;
      virtual void setResultCallback(P1::UpdateSystem::UpdateInfoGetterResultInterface *result) = 0;
      virtual UpdateInfoContainer *updateInfo() const = 0;
    };

  }
}
