#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Compressor/CompressorInferface.h>
#include <QtCore/QObject>

namespace P1 {
  namespace Compressor {

    class UPDATESYSTEMSHARED_EXPORT MiniZipCompressor : public QObject, public CompressorInterface
    {
      Q_OBJECT
    public:
      enum CompressionLevel {
        None = 0,
        Fast = 1,
        Best = 2,
        Normal = -1,
      };

      explicit MiniZipCompressor(QObject *parent = 0);
      ~MiniZipCompressor();

      void setCompressionLevel(CompressionLevel level);
      void setNumThreads(int threads);
      
      CompressorInterface::CompressionResult compressFile(const QString& sourcePath, const QString& targetPath);

    private:
      CompressionLevel _level;
      int _numThreads;
      static const int SIZE_BUF = 16384;
    };
  }
}