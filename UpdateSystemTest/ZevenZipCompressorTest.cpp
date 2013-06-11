#include "gtest/gtest.h"

#include <QtGui/QApplication>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore>
#include <QDebug>

#include <UpdateSystem/Compressor/ZevenZipCompressor.h>

TEST(SevenZipCompressor, CompressTest) 
{

}
/*
TEST(SevenZipExtractor, ExtractTest) 
{
  QString rootDirPath = QApplication::applicationDirPath();
  QString fixturePath = rootDirPath;
  fixturePath.append("/UpdateSystemTestFixtures/");

  QString workingPath = rootDirPath;
  workingPath.append("/UpdateSystemTestWork/");

  QDir workDir(workingPath);
  if(workDir.exists()) {
    RemoveDirectory(workDir);
  }

  ASSERT_TRUE( workDir.mkpath(workingPath) );

  QString normalArchive = fixturePath;
  normalArchive.append("1_update.crc.7z");

  GGS::Extractor::SevenZipExtactor *extractor = new GGS::Extractor::SevenZipExtactor();
  GGS::Extractor::ExtractorInterface *iextractor = static_cast<GGS::Extractor::ExtractorInterface *>(extractor);
  GGS::Extractor::ExtractionResult result = iextractor->extract(normalArchive, workingPath);

  ASSERT_EQ(GGS::Extractor::NoError, result);

  result = iextractor->extract(normalArchive, workingPath);
  ASSERT_EQ(GGS::Extractor::NoError, result);

  QString notExistingArchive = rootDirPath;
  notExistingArchive.append("some_fake_archive.7z");
  result = iextractor->extract(notExistingArchive, workingPath);
  ASSERT_EQ(GGS::Extractor::NoArchive, result);

  QString badArchive = fixturePath;
  badArchive.append("test.txt");
  result = iextractor->extract(badArchive, workingPath);
  ASSERT_EQ(GGS::Extractor::BadArchive, result);

  QString badArchive2 = fixturePath;
  badArchive2.append("currupted_test.txt.7z");
  result = iextractor->extract(badArchive2, workingPath);
  ASSERT_EQ(GGS::Extractor::BadArchive, result);

  delete extractor;

  // TODO: придумать способ протестировать поведение распаковшика при залоченом файле QFile не лочит файл =(
  // ¬озможно просто использовать WinApi с соответствующим дефайном
}*/