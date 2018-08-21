#pragma once

#include <QtCore/QString>

namespace P1 {
  namespace Compressor {

    class CompressorInterface 
    {
    public:
      enum CompressionResult 
      {
        NoError = 0,
        ReadError = 1,
        WriteError = 2,
        UnknownError = 6
      };

      virtual ~CompressorInterface() {};

      virtual CompressionResult compressFile(const QString& sourcePath, const QString& targetPath) = 0;
    };

  }
}
