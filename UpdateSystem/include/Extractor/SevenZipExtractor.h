/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_SEVENZIPEXTRACTOR_H_
#define _GGS_UPDATESYSTEM_SEVENZIPEXTRACTOR_H_

#include "UpdateSystem_global.h"
#include "ExtractorInterface.h"

#include <string>
#include "7zMain.h"

namespace GGS 
{
  namespace Extractor 
  {
      class UPDATESYSTEMSHARED_EXPORT SevenZipExtactor 
        : public ExtractorInterface 
      {
      public:
        SevenZipExtactor();
        virtual ~SevenZipExtactor() {};

        GGS::Extractor::ExtractionResult extract( const QString& archivePath, const QString& extractDirectory );
      };
  }
}
#endif //_GGS_UPDATESYSTEM_SEVENZIPEXTRACTOR_H_