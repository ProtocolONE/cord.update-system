#include <gtest/gtest.h>

#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore>
#include <QDebug>

#include <UpdateSystem/Compressor/MiniZipCompressor.h>
#include <UpdateSystem/Hasher/Md5FileHasher.h>

#define assertFileEqual(f1, f2) { \
  P1::Hasher::Md5FileHasher hasher; \
  ASSERT_EQ(hasher.getFileHash(f1), hasher.getFileHash(f2)); \
}
bool RemoveDirectoryFull(QDir &aDir);

TEST(MiniZipCompressor, CompressorTest) 
{
  P1::Compressor::MiniZipCompressor comp;
  comp.setCompressionLevel(P1::Compressor::MiniZipCompressor::Best);

  QString rootDirPath = QApplication::applicationDirPath();
  QString fixturePath = rootDirPath;
  fixturePath.append("/UpdateSystemTestFixtures/ca/");
  //fixturePath += QString::fromUtf16((const char16_t *)L"/Жи-Ши не пеши через Ы/ca/");

  QString relativePath("1950/123.txt");
  //QString relativePath = QString::fromUtf16((const char16_t *)L"1950/첫 번째 주문 .txt");

  QString fullSourcePath = fixturePath;
  fullSourcePath.append("live/");
  fullSourcePath.append(relativePath);

  QString expectedTarget = fullSourcePath;
  expectedTarget.append(".zip");
  
  QString targetPath = fixturePath;
  targetPath.append("new/");
  targetPath.append(relativePath);
  targetPath.append(".zip");

  comp.compressFile(fullSourcePath, targetPath);
  ASSERT_TRUE(QFile::exists(targetPath));
  assertFileEqual(expectedTarget, targetPath); // UNDONE comressor changed and test failed.
}


