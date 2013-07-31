/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#pragma once

#include <UpdateSystem/UpdateSystem_global.h>
#include <UpdateSystem/Compressor/CompressorInferface.h>
#include <QtCore/QObject>

namespace GGS {
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