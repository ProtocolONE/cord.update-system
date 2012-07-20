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

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Extractor/ExtractorInterface.h>
#include <QtCore/QObject>

namespace GGS {
  namespace Extractor {
    class UPDATESYSTEMSHARED_EXPORT SevenZipExtactor : public QObject, public ExtractorInterface 
    {
      Q_OBJECT
    public:
      explicit SevenZipExtactor(QObject *parent = 0);
      ~SevenZipExtactor();

      ExtractionResult extract(const QString& archivePath, const QString& extractDirectory);

    private:
      ExtractionResult slowExtract(const QString& archivePath, const QString& extractDirectory);
    };
  }
}
#endif //_GGS_UPDATESYSTEM_SEVENZIPEXTRACTOR_H_