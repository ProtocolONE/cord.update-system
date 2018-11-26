#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Extractor/ExtractorInterface.h>
#include <QtCore/QObject>

namespace SevenZip {
  class SevenZipLibrary;
}

typedef void* unzFile;

namespace P1 {
  namespace Extractor {
    class UPDATESYSTEMSHARED_EXPORT MiniZipExtactor : public QObject, public ExtractorInterface 
    {
      Q_OBJECT
    public:
      explicit MiniZipExtactor(QObject *parent = 0);
      ~MiniZipExtactor();

      ExtractionResult extract(const QString& archivePath, const QString& extractDirectory);

    private:
      std::wstring a2w(const std::string& str) const;
      ExtractionResult extractFile(unzFile uf, const QString& extractDirectory) const;
      static const int SIZE_BUF = 16384;
    };
  }
}
