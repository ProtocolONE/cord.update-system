/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#ifndef _GGS_UPDATESYSTEM_EXTRACTINTERFACE_H_
#define _GGS_UPDATESYSTEM_EXTRACTINTERFACE_H_

#include <QtCore/QString>

namespace GGS 
{
  namespace Extractor 
  {
    enum ExtractionResult 
    {
      NoError = 0,
      ReadError = 1,
      WriteError = 2,
      BadArchive = 3,
      OpenError = 4,
      NoArchive = 5,
      UnknownError = 6
    };

    class ExtractorInterface 
    {
    public:
      virtual ~ExtractorInterface() {};

      virtual ExtractionResult extract(const QString& archivePath, const QString& extractDirectory) = 0;
    };

  }
}
#endif //_GGS_UPDATESYSTEM_EXTRACTINTERFACE_H_
