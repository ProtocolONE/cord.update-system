#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Extractor/ExtractorInterface.h>
#include <QtCore/QObject>

namespace SevenZip {
  class SevenZipLibrary;
}

namespace P1 {
  namespace Extractor {
    class UPDATESYSTEMSHARED_EXPORT SevenZipExtractor : public QObject, public ExtractorInterface 
    {
      Q_OBJECT
    public:
      explicit SevenZipExtractor(QObject *parent = 0);
      ~SevenZipExtractor();

      ExtractionResult extract(const QString& archivePath, const QString& extractDirectory);

    private:
      ExtractionResult slowExtract(const QString& archivePath, const QString& extractDirectory);

      SevenZip::SevenZipLibrary* _lib;
    };
  }
}
