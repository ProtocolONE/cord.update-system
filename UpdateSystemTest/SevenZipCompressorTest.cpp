#include "gtest/gtest.h"

#include <QtWidgets/QApplication>
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
bool RemoveDirectoryFull(QDir &aDir);

TEST(SevenZipCompressor, CompressorTest) 
{
  GGS::Compressor::SevenZipCompressor comp;
  comp.setCompressionLevel(GGS::Compressor::SevenZipCompressor::Low);

  QString rootDirPath = QApplication::applicationDirPath();
  QString fixturePath = rootDirPath;
  fixturePath.append("/UpdateSystemTestFixtures/ca/");

  QString relativePath("1950/123.txt");

  QString fullSourcePath = fixturePath;
  fullSourcePath.append("live/");
  fullSourcePath.append(relativePath);

  QString expectedTarget = fullSourcePath;
  expectedTarget.append(".7z");
  
  QString targetPath = fixturePath;
  targetPath.append("new/");
  targetPath.append(relativePath);
  targetPath.append(".7z");

  comp.compressFile(fullSourcePath, targetPath);
  ASSERT_TRUE(QFile::exists(targetPath));
  assertFileEqual(expectedTarget, targetPath);
}


