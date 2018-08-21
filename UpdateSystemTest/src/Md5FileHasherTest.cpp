#include <UpdateSystem/Hasher/Md5FileHasher.h>

#include <gtest/gtest.h>
#include "MemoryLeaksChecker.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QTime>

class Md5FileHasherTest : public ::testing::Test
{
public:
  Md5FileHasherTest()
  {
    this->leakChecker.start();
  }

  ~Md5FileHasherTest()
  {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest(std::string("Memory leak detected!").c_str());  

  }

  virtual void SetUp() {
    this->appDir = QCoreApplication::applicationDirPath();
    this->fixture = this->appDir;
    fixture.append("/UpdateSystemTestFixtures/");
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  QString getHashString(const QString& name)
  {
    P1::Hasher::Md5FileHasher hasher;
    QString file = this->fixture;
    file.append(name);
    return hasher.getFileHash(file);
  }

  QString appDir;
  QString fixture;



private: 
  void failTest(const char* message) 
  { 
    FAIL() << message; delete message;
  }

  MemoryLeaksChecker leakChecker;
};

TEST_F(Md5FileHasherTest, GoodMd5hashTest)
{
  ASSERT_EQ(0, this->getHashString("unexistingfile").compare(""));
  ASSERT_EQ(0, this->getHashString("1_update.crc").compare("43ea1d690ce66812103aff58bf6a5009"));
  ASSERT_EQ(0, this->getHashString("1_update.crc.7z").compare("7eb2fc35a680c83104801e7c2dda5528"));
  ASSERT_EQ(0, this->getHashString("currupted_test.txt.7z").compare("7747809c6360fe0e28947ac4020d808a"));
  ASSERT_EQ(0, this->getHashString("test.txt").compare("098f6bcd4621d373cade4e832627b4f6"));
  ASSERT_EQ(0, this->getHashString("test.txt.7z").compare("0a550326468024d1828443dca0bcf62c"));

  QTime time;
  time.setHMS(0,0,0,0);
  time.start();
  
  ASSERT_EQ(0, this->getHashString("bigFile.dat").compare("d4a921262de670b556ce3ef174ac271f"));
  int elapsed = time.elapsed(); // sad - very sad 1700 ms
}