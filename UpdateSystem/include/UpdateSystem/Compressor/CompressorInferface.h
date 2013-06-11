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

#include <QtCore/QString>

namespace GGS 
{
  namespace Compressor
  {

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

      virtual CompressionResult compress(const QString& targetPath, const QString& fileName, const QString& archivePath) = 0;
    };

  }
}
