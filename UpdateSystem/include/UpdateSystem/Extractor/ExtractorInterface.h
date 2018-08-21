#pragma once

#include <QtCore/QString>

namespace P1 
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
