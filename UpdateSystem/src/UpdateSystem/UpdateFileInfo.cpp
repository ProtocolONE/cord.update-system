/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/UpdateFileInfo.h>

namespace GGS {
  namespace UpdateSystem {
    UpdateFileInfo::UpdateFileInfo(QObject *parent)
      : QObject(parent)
      , _relativePath(QString())
      , _hash(QString())
      , _rawLength(0)
      , _archiveLength(0)
      , _forceCheck(false) {
    }

    UpdateFileInfo::UpdateFileInfo(const UpdateFileInfo& c)
      : _relativePath(c._relativePath)
      , _hash(c._hash)
      , _rawLength(c._rawLength)
      , _archiveLength(c._archiveLength)
      , _forceCheck(c._forceCheck)
    {
    }

    UpdateFileInfo::~UpdateFileInfo() {}

    void UpdateFileInfo::setPath( const QString& path )
    {
      _relativePath = path;
    }

    void UpdateFileInfo::setHash( const QString& hash )
    {
      _hash = hash;
    }

    void UpdateFileInfo::setRawLength( quint64 rawLength )
    {
      _rawLength = rawLength;
    }

    void UpdateFileInfo::setArchiveLength( quint64 archiveLength )
    {
      _archiveLength = archiveLength;
    }

    void UpdateFileInfo::setForceCheck( bool forceCheck )
    {
      _forceCheck = forceCheck;
    }

    const QString& UpdateFileInfo::relativePath() const
    {
      return this->_relativePath;;
    }

    const QString& UpdateFileInfo::hash() const
    {
      return this->_hash;
    }

    quint64 UpdateFileInfo::rawLength() const
    {
      return this->_rawLength;
    }

    quint64 UpdateFileInfo::archiveLength() const
    {
      return this->_archiveLength;
    }

    bool UpdateFileInfo::forceCheck() const
    {
      return this->_forceCheck;
    }

    UpdateFileInfo& UpdateFileInfo::operator= (const UpdateFileInfo &p)
    {
      this->_archiveLength = p._archiveLength;
      this->_forceCheck = p._forceCheck;
      this->_hash = p._hash;
      this->_rawLength = p._rawLength;
      this->_relativePath = p._relativePath;
      return *this;
    }

    QDataStream& operator<< (QDataStream& stream, const UpdateFileInfo& c)
    {
      return stream << c._relativePath
                    << c._hash
                    << c._rawLength
                    << c._archiveLength
                    << c._forceCheck;
    }

    QDataStream& operator>> (QDataStream& stream, UpdateFileInfo& c)
    {
      stream >> c._relativePath
             >> c._hash
             >> c._rawLength
             >> c._archiveLength
             >> c._forceCheck;
      return stream;
    }

  }
}