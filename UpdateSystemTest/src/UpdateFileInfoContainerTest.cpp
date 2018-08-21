#include <gtest/gtest.h>

#include "MemoryLeaksChecker.h"

#include <UpdateSystem/UpdateFileInfo.h>

class UpdateFileInfoTest : public ::testing::Test
{
public:
  UpdateFileInfoTest()
  {
    this->leakChecker.start();
  }

  ~UpdateFileInfoTest()
  {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest(std::string("Memory leak detected!").c_str());  
  }

private: 
  void failTest(const char* message) 
  { 
    FAIL() << message; delete message;
  }

  MemoryLeaksChecker leakChecker;
};

TEST_F(UpdateFileInfoTest, ConstructorTest) 
{
  using P1::UpdateSystem::UpdateFileInfo;
  QString path("somefile.txt");
  QString hash("12378902345902345");
  quint64 rawLength = 123123;
  quint64 archiveLength = 123;
  bool forceCheck = false;

  UpdateFileInfo *info = new UpdateFileInfo();
  info->setPath(path);
  info->setHash(hash);
  info->setRawLength(rawLength);
  info->setArchiveLength(archiveLength);
  info->setForceCheck(forceCheck);

  ASSERT_EQ(0, QString::compare(path, info->relativePath()));
  ASSERT_EQ(0, QString::compare(hash, info->hash()));

  ASSERT_EQ(rawLength, info->rawLength());
  ASSERT_EQ(archiveLength, info->archiveLength());
  ASSERT_EQ(forceCheck, info->forceCheck());

  delete info;
}

