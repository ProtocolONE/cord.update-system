/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Hasher/Md5FileHasher.h>

namespace GGS {
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