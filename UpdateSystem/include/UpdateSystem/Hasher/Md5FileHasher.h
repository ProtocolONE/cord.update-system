#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Hasher/FileHashInterface.h>

#include <QtCore/QThread>
#include <QtCore/QObject>
#include <QtCore/QCryptographicHash>
#include <QtCore/QFile>

#include <QtCore/QWaitCondition>

namespace P1 {
  namespace Hasher {
    class UPDATESYSTEMSHARED_EXPORT Md5FileHasher : 
      public QObject,
      public FileHashInterface
    {
      Q_OBJECT
    public:
      Md5FileHasher(QObject *parrent = 0);
      virtual ~Md5FileHasher();

      QString getFileHash(const QString& filePath);
    };
  }
}
