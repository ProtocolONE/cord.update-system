/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_HASHER_FILE_HASH_INTERFACE_H_
#define _GGS_UPDATESYSTEM_HASHER_FILE_HASH_INTERFACE_H_

#include "UpdateSystem_global.h"
#include <QtCore/QString>

namespace GGS {
  namespace Hasher {
    class UPDATESYSTEMSHARED_EXPORT FileHashInterface {
    public:
      ~FileHashInterface() {}
      virtual QString getFileHash(const QString& filePath) = 0;
    };
  }
}

#endif // _GGS_UPDATESYSTEM_HASHER_FILE_HASH_INTERFACE_H_