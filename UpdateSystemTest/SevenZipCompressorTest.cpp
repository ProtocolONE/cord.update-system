#include "gtest/gtest.h"

#include <QtGui/QApplication>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore>
#include <QDebug>

#include <UpdateSystem/Extractor/ExtractorInterface.h>
#include <UpdateSystem/Compressor/ZevenZipCompressor.h>
#include <UpdateSystem/Hasher/Md5FileHasher.h>

#define assertFileEqual(f1, f2) { \
  GGS::Hasher::Md5FileHasher hasher; \
  ASSERT_EQ(hasher.getFileHash(f1), hasher.getFileHash(f2)); \
}
bool RemoveDirectory(QDir &aDir);

TEST(SevenZipCompressor, CompressorTest) 
{
  GGS::Compressor::SevenZipCompressor comp;
  comp.setCompressionLevel(GGS::Compressor::SevenZipCompressor::Low);

  QString rootDirPath = QApplication::applicationDirPath();
  QString fixturePath = rootDirPath;
  fixturePath.append("/UpdateSystemTestFixtures/ca/");

  QString workingPath = rootDirPath;
  workingPath.append("/UpdateSystemTestWork/");

  QDir workDir(workingPath);
  if(workDir.exists()) {
    RemoveDirectory(workDir);
  }

  ASSERT_TRUE( workDir.mkpath(workingPath) );

  QString packFileName = "bdcap32.dll";
  QString normalPath = fixturePath + "live/";
  QString arcPath = fixturePath + "new/";
  normalPath.append(packFileName);
  arcPath.append("bdcap32.dll.7z");

  bool g = QFile::exists(normalPath);

  ASSERT_TRUE(QFile::exists(normalPath));
  ASSERT_EQ(0, comp.compress(fixturePath + "live/", packFileName, arcPath));
  ASSERT_TRUE(QFile::exists(arcPath));

  QString distFile = fixturePath + "dist/live/bdcap32.dll.7z";
  bool h = QFile::exists(distFile);
  assertFileEqual(distFile, arcPath);
}