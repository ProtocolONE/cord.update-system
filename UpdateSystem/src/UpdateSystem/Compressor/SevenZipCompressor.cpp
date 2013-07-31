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
#include <QtCore/QFile>
#include <QTCore/QDir>
#include <WinError.h>

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

CompressorInterface::CompressionResult SevenZipCompressor::compressFile(const QString& sourcePath, const QString& targetPath)
{
  using namespace SevenZip::intl;
  if (!QFile::exists(sourcePath))
    return CompressorInterface::ReadError;

  QString sourcePath2 = QDir::toNativeSeparators(sourcePath);
  QString targetPath2 = QDir::toNativeSeparators(targetPath);

  QFileInfo info(targetPath2);
  QDir archivePathDir = info.dir();
  QString pathToFile = info.absolutePath();
  if (!archivePathDir.exists())
    archivePathDir.mkpath(pathToFile);

  QFileInfo sourceInfo(sourcePath2);
  QDir sourceDirInfo = sourceInfo.dir();
  QString sourceDirPath = QDir::toNativeSeparators(sourceDirInfo.absolutePath()) + "\\";

  std::vector<wchar_t> source;
  source.resize(sourcePath2.size() + 1);

  std::vector<wchar_t> sourceDir;
  sourceDir.resize(sourceDirPath.size() + 1);

  std::vector<wchar_t> target;
  target.resize(targetPath2.size() + 1);

  int length = sourcePath2.toWCharArray(source.data());
  source[length] = L'\0';
  length = targetPath2.toWCharArray(target.data());
  target[length] = L'\0';
  length = sourceDirPath.toWCharArray(sourceDir.data());
  sourceDir[length] = L'\0';

  try {
    SevenZip::SevenZipLibrary lib;
    lib.Load();

    SevenZip::SevenZipCompressor compressor(lib, target.data());

    switch(this->_level) {
    case None: compressor.SetCompressionLevel(SevenZip::CompressionLevel::None); break;
    case Fast: compressor.SetCompressionLevel(SevenZip::CompressionLevel::Fast); break;
    case Low: compressor.SetCompressionLevel(SevenZip::CompressionLevel::Low); break;
    case Normal:  compressor.SetCompressionLevel(SevenZip::CompressionLevel::Normal); break;
    case High:  compressor.SetCompressionLevel(SevenZip::CompressionLevel::High); break;
    case Ultra: 
    default: compressor.SetCompressionLevel(SevenZip::CompressionLevel::Ultra); break;
    }

    compressor.CompressFile(sourceDir.data(), source.data());
  } catch(SevenZip::SevenZipException& ex) {

    ::std::wstring des(ex.GetMessage().GetString());

    DEBUG_LOG << "7-zip exception: " 
      << QString::fromWCharArray(des.c_str()) 
      << " source path: "
      << sourcePath2
      << " target file path: "
      << targetPath2;

    return WriteError;

  } catch(...) {
    DEBUG_LOG << "Unknown 7-zip exception";
    return UnknownError;
  }

  return CompressorInterface::NoError;
}