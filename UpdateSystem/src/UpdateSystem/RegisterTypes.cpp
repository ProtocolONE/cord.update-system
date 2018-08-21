#include <UpdateSystem/CheckUpdateHelper.h>

#include <QtCore/QMetaType>

namespace P1 {
  namespace UpdateSystem {

    void registerTypes()
    {
      qRegisterMetaType<P1::UpdateSystem::CheckUpdateHelper::Results>("P1::UpdateSystem::CheckUpdateHelper::Results");
    }
  }
}

