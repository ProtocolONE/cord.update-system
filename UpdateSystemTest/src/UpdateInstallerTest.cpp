#include <gtest/gtest.h>
#include "MemoryLeaksChecker.h"

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QtCore/QFileInfoList>

#include <UpdateSystem/UpdateInstaller.h>

// HACK: убрать в какой-то хелпер.
bool RemoveDirectoryFull(QDir &aDir);

class UpdateInstallerTest : public ::testing::Test
{
public:
  UpdateInstallerTest() {
    this->leakChecker.start();
  }

  ~UpdateInstallerTest() {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest(std::string("Memory leak detected!").c_str());  
  }

  virtual void SetUp() {
    this->appDir = QCoreApplication::applicationDirPath();
    this->workingDir = this->appDir;
    this->workingDir.append("/UpdateInstallerTest/");

    QDir dir(this->workingDir);
    if(dir.exists(this->workingDir)){
      RemoveDirectoryFull(dir);
    }

    dir.mkpath(this->workingDir);
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  QString appDir;
  QString workingDir;

private: 
  void failTest(const char* message) 
  { 
    FAIL() << message; delete message;
  }

  MemoryLeaksChecker leakChecker;

};

TEST_F(UpdateInstallerTest, removeOldFilesTest)
{
  QString ff1 = this->workingDir;
  ff1.append("fakefile.txt.old.123.old");

  QString df2 = this->workingDir;
  df2.append("fakedir/");
  QDir dir(df2);
  dir.mkpath(df2);
  QString ff2 = df2;
  ff2.append("fakefile2.txt.old.123.old");

  QFile f1(ff1);
  f1.open(QIODevice::ReadWrite);
  QTextStream out(&f1);
  out << "test1";
  f1.close();

  QFile f2(ff2);
  f2.open(QIODevice::ReadWrite);
  QTextStream out2(&f2);
  out2 << "test2";
  f2.close();


  // Теперь удалим эти 2 файла нашим тестом.

  //QStringList filters;
  //filters << "*.old";

  //QDir targetDir(this->workingDir);
  //targetDir.setNameFilters(filters);
  //QFileInfoList list = targetDir.entryInfoList();

  P1::UpdateSystem::UpdateInstaller installer;
  installer.setTargetDirectory(this->workingDir);
  installer.clearOldFiles();
  ASSERT_FALSE(QFile::exists(ff1));
  ASSERT_FALSE(QFile::exists(ff2));
}