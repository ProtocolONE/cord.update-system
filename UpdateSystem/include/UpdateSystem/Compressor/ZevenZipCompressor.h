#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Compressor/CompressorInferface.h>
#include <QtCore/QObject>

namespace P1 {
  namespace Compressor {

    class UPDATESYSTEMSHARED_EXPORT SevenZipCompressor : public QObject, public CompressorInterface
    {
      Q_OBJECT
    public:
      enum CompressionLevel {
        None = 0,
        Fast = 1,
        Low = 2,
        Normal = 3,
        High = 4,
        Ultra = 5,
      };

      explicit SevenZipCompressor(QObject *parent = 0);
      ~SevenZipCompressor();

      void setCompressionLevel(CompressionLevel level);
      void setNumThreads(int threads);
      
      CompressorInterface::CompressionResult compressFile(const QString& sourcePath, const QString& targetPath);

    private:
      CompressionLevel _level;
      int _numThreads;
    };
  }
}