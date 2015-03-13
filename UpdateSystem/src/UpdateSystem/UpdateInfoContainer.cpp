/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/UpdateInfoContainer.h>

namespace GGS 
{
  namespace UpdateSystem
  {

    UpdateInfoContainer::UpdateInfoContainer(QObject *parrent)
      : QObject(parrent)
    {
    }

    UpdateInfoContainer::~UpdateInfoContainer(){
      this->clear();
    }

    void UpdateInfoContainer::addFileInfo(UpdateFileInfo *entry) 
    {
      this->_fileInfoHashTable.push_back(entry);
    }

    void UpdateInfoContainer::clear()
    {
      for (QList<UpdateFileInfo*>::iterator it = this->_fileInfoHashTable.begin(); it !=  this->_fileInfoHashTable.end(); ++it)
        delete *it;

      this->_fileInfoHashTable.clear();
    }

    QList<UpdateFileInfo*>* UpdateInfoContainer::getFiles()
    {
      return &this->_fileInfoHashTable;
    }

  }
}