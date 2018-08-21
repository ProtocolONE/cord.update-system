#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/UpdateFileInfo.h>

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QHash>

namespace P1 
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
