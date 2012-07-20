/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_UPDATEFILEINFO_H_
#define _GGS_UPDATESYSTEM_UPDATEFILEINFO_H_

#include "UpdateSystem_global.h"
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QMetaType>

namespace GGS 
{
  namespace UpdateSystem
  {
    class UPDATESYSTEMSHARED_EXPORT UpdateFileInfo : QObject
    {
      Q_OBJECT
    public:
      explicit UpdateFileInfo(QObject *parent = 0);
      UpdateFileInfo(const UpdateFileInfo& c);
      UpdateFileInfo& operator=(const UpdateFileInfo &p);

      virtual ~UpdateFileInfo();

      void setPath(const QString& path);
      void setHash(const QString& hash);
      void setRawLength(quint64 rawLength);
      void setArchiveLength(quint64 archiveLength);
      void setForceCheck(bool forceCheck);

      const QString& relativePath() const;
      const QString& hash() const;
      quint64 rawLength() const;
      quint64 archiveLength() const;
      bool forceCheck() const;

      UPDATESYSTEMSHARED_EXPORT friend QDataStream& operator<< (QDataStream& stream, const UpdateFileInfo& c);
      UPDATESYSTEMSHARED_EXPORT friend QDataStream& operator>> (QDataStream& stream, UpdateFileInfo& c);

    private:
      QString _relativePath;
      QString _hash;
      quint64 _rawLength;
      quint64 _archiveLength;
      bool _forceCheck;
    };



  }
}

Q_DECLARE_METATYPE(GGS::UpdateSystem::UpdateFileInfo);
Q_DECLARE_METATYPE(GGS::UpdateSystem::UpdateFileInfo *);

#endif // _GGS_UPDATESYSTEM_UPDATEFILEINFO_H_