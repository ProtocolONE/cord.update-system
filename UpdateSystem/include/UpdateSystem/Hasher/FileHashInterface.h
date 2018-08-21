#pragma once

#include <UpdateSystem/UpdateSystem_global.h>

#include <QtCore/QString>

namespace P1 {
  namespace Hasher {
    class UPDATESYSTEMSHARED_EXPORT FileHashInterface {
    public:
      ~FileHashInterface() {}
      virtual QString getFileHash(const QString& filePath) = 0;
    };
  }
}

