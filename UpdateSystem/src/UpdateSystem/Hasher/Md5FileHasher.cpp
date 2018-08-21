#include <UpdateSystem/Hasher/Md5FileHasher.h>

namespace P1 {
  namespace Hasher {

    Md5FileHasher::Md5FileHasher(QObject *parrent)
      : QObject(parrent) 
    {
    }

    Md5FileHasher::~Md5FileHasher() 
    {
    }

    QString Md5FileHasher::getFileHash(const QString& filePath)
    {     
      QCryptographicHash crypto(QCryptographicHash::Md5);
      QFile file(filePath);
      if (!file.open(QFile::ReadOnly))
        return QString();

      while (!file.atEnd())     
        crypto.addData(file.read(8192));

      file.close();

      return crypto.result().toHex();
    }

  }
}