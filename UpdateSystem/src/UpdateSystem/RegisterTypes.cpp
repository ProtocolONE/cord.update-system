#include <UpdateSystem/CheckUpdateHelper.h>

#include <QtCore/QMetaType>

namespace P1 {
  namespace UpdateSystem {

    UPDATESYSTEMSHARED_EXPORT void registerTypes()
    {
      qRegisterMetaType<P1::UpdateSystem::CheckUpdateHelper::Results>("P1::UpdateSystem::CheckUpdateHelper::Results");
    }
  }
}

