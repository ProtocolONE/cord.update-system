#include <UpdateSystem/UpdateInfoContainer.h>

namespace P1 
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