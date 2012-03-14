/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "Extractor/SevenZipExtractor.h"

#define SZ_OK 0

#define SZ_ERROR_DATA 1
#define SZ_ERROR_MEM 2
#define SZ_ERROR_CRC 3
#define SZ_ERROR_UNSUPPORTED 4
#define SZ_ERROR_PARAM 5
#define SZ_ERROR_INPUT_EOF 6
#define SZ_ERROR_OUTPUT_EOF 7
#define SZ_ERROR_READ 8
#define SZ_ERROR_WRITE 9
#define SZ_ERROR_PROGRESS 10
#define SZ_ERROR_FAIL 11
#define SZ_ERROR_THREAD 12
#define SZ_ERROR_OPEN_ARCHIVE 113

#define SZ_ERROR_ARCHIVE 16
#define SZ_ERROR_NO_ARCHIVE 17

GGS::Extractor::ExtractionResult GGS::Extractor::SevenZipExtactor::extract( const QString& archivePath, const QString& extractDirectory )
{
  wchar_t archive[261];
  wchar_t target[261];
  int length = archivePath.toWCharArray(archive);
  archive[length] = L'\0';
  length = extractDirectory.toWCharArray(target);
  target[length] = L'\0';

  int result = GGS::SevenZip::ExtractW(archive, target);
  switch(result) {
    case SZ_OK:
      return NoError;
  
    case SZ_ERROR_READ:
      return ReadError;
  
    case SZ_ERROR_WRITE:
      return WriteError;
  
    case SZ_ERROR_NO_ARCHIVE:
    case SZ_ERROR_OPEN_ARCHIVE:
      return NoArchive;
  
    case SZ_ERROR_DATA:
    case SZ_ERROR_MEM:
    case SZ_ERROR_CRC:
    case SZ_ERROR_UNSUPPORTED:
    case SZ_ERROR_PARAM:
    case SZ_ERROR_INPUT_EOF:
    case SZ_ERROR_OUTPUT_EOF:
    case SZ_ERROR_FAIL:
    case SZ_ERROR_ARCHIVE:
      return BadArchive;
  
    default:
      return UnknownError;
    }
}

  GGS::Extractor::SevenZipExtactor::SevenZipExtactor()
  {

  }
