/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_UPDATEINFOCONTAINER_H_
#define _GGS_UPDATESYSTEM_UPDATEINFOCONTAINER_H_

#include "UpdateSystem_global.h"

#include "UpdateFileInfo.h"
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QHash>

namespace GGS 
{
  namespace UpdateSystem
  {

    class UPDATESYSTEMSHARED_EXPORT UpdateInfoContainer : public QObject
    {
      Q_OBJECT
    public:
      explicit UpdateInfoContainer(QObject *parrent = 0);
      virtual ~UpdateInfoContainer();

      void clear();
      void addFileInfo(UpdateFileInfo *entry);

      QList<UpdateFileInfo*>* getFiles();;

    private:
      QList<UpdateFileInfo *> _fileInfoHashTable;
    };

  }
}
#endif // _GGS_UPDATESYSTEM_UPDATEINFOCONTAINER_H_
