/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Extractor/SevenZipExtractor.h>
#include <SevenZip/SevenZipExtractor.h>
#include <SevenZip/SevenZipException.h>
#include <SevenZip/OpenArchiveException.h>
#include <SevenZip/ExtractArchiveException.h>

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <WinError.h>

#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

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

#define HRESULT_NOT_ENOUGH_SPACE 0x80070070


GGS::Extractor::SevenZipExtactor::SevenZipExtactor(QObject *parent)
  : QObject(parent)
{
  this->_lib = new SevenZip::SevenZipLibrary;
  this->_lib->Load();
}


GGS::Extractor::SevenZipExtactor::~SevenZipExtactor()
{
  delete this->_lib;
}


GGS::Extractor::ExtractionResult GGS::Extractor::SevenZipExtactor::extract(const QString& archivePath, const QString& extractDirectory)
{
  if (!QFile::exists(archivePath))
    return NoArchive;

  if (archivePath.size() > 260 || extractDirectory.size() > 260) {
    return this->slowExtract(archivePath, extractDirectory);
  }

  wchar_t archive[261];
  wchar_t target[261];

  int length = archivePath.toWCharArray(archive);
  archive[length] = L'\0';
  length = extractDirectory.toWCharArray(target);
  target[length] = L'\0';

  try {
    SevenZip::SevenZipExtractor extractor(*this->_lib, archive);
    extractor.ExtractArchive(target);

  } catch(SevenZip::OpenArchiveException& ex) {
    ::std::wstring des(ex.GetMessage().GetString());
    DEBUG_LOG << "7-zip OpenArchiveException: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target path: "
      << extractDirectory;
    return BadArchive;
  
  } catch(SevenZip::ExtractArchiveException& ex) {
    ::std::wstring des(ex.GetMessage().GetString());
    DEBUG_LOG << "7-zip ExtractArchiveException: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target path: "
      << extractDirectory;
    
    return ex.result() == HRESULT_NOT_ENOUGH_SPACE ? WriteError : BadArchive;

  } catch(SevenZip::SevenZipException& ex) {
    ::std::wstring des(ex.GetMessage().GetString());
    DEBUG_LOG << "7-zip exception: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target path: "
      << extractDirectory;
    return BadArchive;

  } catch(...) {
    
    DEBUG_LOG << "Unknown 7-zip exception";
    return BadArchive;
  }

  return GGS::Extractor::NoError;
}

GGS::Extractor::ExtractionResult GGS::Extractor::SevenZipExtactor::slowExtract(const QString& archivePath, const QString& extractDirectory)
{
  wchar_t *archive = new wchar_t[archivePath.size() + 1];
  wchar_t *target = new wchar_t[extractDirectory.size() + 1];
  
  int length = archivePath.toWCharArray(archive);
  archive[length] = L'\0';
  length = extractDirectory.toWCharArray(target);
  target[length] = L'\0';

  try {
    SevenZip::SevenZipExtractor extractor(*this->_lib, archive);
    extractor.ExtractArchive(target);
  } catch(SevenZip::OpenArchiveException& ex) {
    delete [] archive;
    delete [] target;
    ::std::wstring des(ex.GetMessage().GetString());
    DEBUG_LOG << "7-zip OpenArchiveException: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target path: "
      << extractDirectory;
    return BadArchive;

  } catch(SevenZip::ExtractArchiveException& ex) {
    delete [] archive;
    delete [] target;

    ::std::wstring des(ex.GetMessage().GetString());
    DEBUG_LOG << "7-zip ExtractArchiveException: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target path: "
      << extractDirectory;
    return ex.result() == HRESULT_NOT_ENOUGH_SPACE ? WriteError : BadArchive; // ? под вопросом

  } catch(SevenZip::SevenZipException& ex) {

    delete [] archive;
    delete [] target;

    ::std::wstring des(ex.GetMessage().GetString());
    DEBUG_LOG << "7-zip exception: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target path: "
      << extractDirectory;

    return BadArchive;

  } catch(...) {

    delete [] archive;
    delete [] target;
    DEBUG_LOG << "Unknown 7-zip exception";
    return BadArchive;

  }

  delete [] archive;
  delete [] target;

  return NoError;
}
