#include <gtest/gtest.h>

#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDebug>

#include <UpdateSystem/Extractor/MiniZipExtractor.h>

bool RemoveDirectoryFull(QDir &aDir);

TEST(MiniZipExtractor, ExtractTest)
{
  QString rootDirPath = QApplication::applicationDirPath();
  QString fixturePath = rootDirPath;
  fixturePath.append("/UpdateSystemTestFixtures/");
  //fixturePath += QString::fromUtf16((const char16_t *)L"/Жи-Ши не пеши через Ы/");

  QString workingPath = rootDirPath;
  workingPath.append("/UpdateSystemTestWork/");
  //workingPath += QString::fromUtf16((const char16_t *)L"/Жи-Ши пеши через И/");

  QDir workDir(workingPath);
  if(workDir.exists()) {
    RemoveDirectoryFull(workDir);
  }

  ASSERT_TRUE( workDir.mkpath(workingPath) );

  QString normalArchive = fixturePath;
  normalArchive.append("1_update.crc.zip");
  //normalArchive += QString::fromUtf16((const char16_t *)L"첫 번째 주문 .zip");

  P1::Extractor::MiniZipExtractor *extractor = new P1::Extractor::MiniZipExtractor();
  P1::Extractor::ExtractorInterface *iextractor = static_cast<P1::Extractor::ExtractorInterface *>(extractor);
  P1::Extractor::ExtractionResult result = iextractor->extract(normalArchive, workingPath);

  ASSERT_EQ(P1::Extractor::NoError, result);

  result = iextractor->extract(normalArchive, workingPath);
  ASSERT_EQ(P1::Extractor::NoError, result);

  QString notExistingArchive = rootDirPath;
  notExistingArchive.append("\\some_fake_archive.zip");
  result = iextractor->extract(notExistingArchive, workingPath);
  ASSERT_EQ(P1::Extractor::NoArchive, result);

  QString badArchive = fixturePath;
  badArchive.append("test.txt");
  result = iextractor->extract(badArchive, workingPath);
  ASSERT_EQ(P1::Extractor::BadArchive, result);

  QString badArchive2 = fixturePath;
  badArchive2.append("currupted_test.txt.zip");
  result = iextractor->extract(badArchive2, workingPath);
  ASSERT_EQ(P1::Extractor::BadArchive, result);

  delete extractor;

  // TODO: придумать способ протестировать поведение распаковшика при залоченом файле QFile не лочит файл =(
  // Возможно просто использовать WinApi с соответствующим дефайном
}