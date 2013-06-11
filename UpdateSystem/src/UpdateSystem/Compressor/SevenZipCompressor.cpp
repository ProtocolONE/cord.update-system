/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Compressor/ZevenZipCompressor.h>
#include <SevenZip/SevenZipCompressor.h>
#include <SevenZip/SevenZipException.h>
#include <SevenZip/OpenArchiveException.h>
#include <SevenZip/ExtractArchiveException.h>
#include <SevenZip/CompressionLevel.h>

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QTCore/QDir>
#include <WinError.h>

#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

using namespace GGS::Compressor;

SevenZipCompressor::SevenZipCompressor(QObject *parent)
  : QObject(parent), _level(Ultra), _numThreads(1)
{
}

SevenZipCompressor::~SevenZipCompressor()
{

}

void SevenZipCompressor::setNumThreads(int threads)
{
  this->_numThreads = threads;
}

void SevenZipCompressor::setCompressionLevel(CompressionLevel level)
{
 this->_level = level;
}

CompressorInterface::CompressionResult SevenZipCompressor::compress(const QString& targetPath, const QString& fileName, const QString& archivePath)
{
  QString targetFilePath = targetPath + "/" + fileName;

  if (!QFile::exists(targetFilePath))
    return CompressorInterface::ReadError;

  QFileInfo info(archivePath);
  QDir archivePathDir = info.dir();
  QString pathToFile = info.absolutePath();
  if (!archivePathDir.exists())
    archivePathDir.mkpath(pathToFile);

  wchar_t archive[261];
  wchar_t path[261];
  wchar_t target[261];

  int length = archivePath.toWCharArray(archive);
  archive[length] = L'\0';

  length = fileName.toWCharArray(target);
  target[length] = L'\0';

  length = targetPath.toWCharArray(path);
  path[length] = L'\0';

  try {
    SevenZip::SevenZipLibrary lib;
    lib.Load();

    SevenZip::SevenZipCompressor compressor(lib, archive);

    switch(this->_level) {
    case None: compressor.SetCompressionLevel(SevenZip::CompressionLevel::None); break;
    case Fast: compressor.SetCompressionLevel(SevenZip::CompressionLevel::Fast); break;
    case Low: compressor.SetCompressionLevel(SevenZip::CompressionLevel::Low); break;
    case Normal:  compressor.SetCompressionLevel(SevenZip::CompressionLevel::Normal); break;
    case High:  compressor.SetCompressionLevel(SevenZip::CompressionLevel::High); break;
    case Ultra: 
    default: compressor.SetCompressionLevel(SevenZip::CompressionLevel::Ultra); break;
    }

    compressor.CompressFiles(path, target, false);

  } catch(SevenZip::SevenZipException& ex) {

    ::std::wstring des(ex.GetMessage().GetString());
    
    DEBUG_LOG << "7-zip exception: " 
      << QString::fromWCharArray(des.c_str()) 
      << " archive path: "
      << archivePath
      << " target file path: "
      << targetPath + "/" + fileName;

    return WriteError;

  } catch(...) {
    DEBUG_LOG << "Unknown 7-zip exception";
    return UnknownError;
  }

  return NoError;
}