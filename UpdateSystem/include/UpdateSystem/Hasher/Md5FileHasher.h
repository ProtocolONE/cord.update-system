/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_HASHER_MD5_FILE_HASHER_H_
#define _GGS_HASHER_MD5_FILE_HASHER_H_

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Hasher/FileHashInterface.h>

#include <QtCore/QThread>
#include <QtCore/QObject>
#include <QtCore/QCryptographicHash>
#include <QtCore/QFile>

#include <QtCore/QWaitCondition>

namespace GGS {
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

#endif // _GGS_HASHER_MD5_FILE_HASHER_H_