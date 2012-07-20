#include <UpdateSystem/UpdateFileInfo.h>
#include <UpdateSystem/UpdateInfoContainer.h>

#include "gtest\gtest.h"

#include "MemoryLeaksChecker.h"
#include <QtCore/QDebug>

class UpdateInfoContainerTest : public ::testing::Test
{
public:
  UpdateInfoContainerTest()
  {
    this->leakChecker.start();
  }

  ~UpdateInfoContainerTest()
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

TEST_F(UpdateInfoContainerTest, ConstructorTest) 
{
  using GGS::UpdateSystem::UpdateFileInfo;
  using GGS::UpdateSystem::UpdateInfoContainer;

  QString longhash1("123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123");
  QString path1("123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123");
  quint64 raw1 = 3498057230;
  quint64 archive1 = 2493572389;
  bool force1 = true;

  QString longhash2("1231231231231231231231231231231231231231aaaa23123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123");
  QString path2("12312312312312qweqwe3123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123");
  quint64 raw2 = 1111057230;
  quint64 archive2 = 2223572389;
  bool force2 = false;

  UpdateInfoContainer container;

  UpdateFileInfo* fileInfo = new UpdateFileInfo();
  fileInfo->setPath(path1);
  fileInfo->setHash(longhash1);
  fileInfo->setRawLength(raw1);
  fileInfo->setArchiveLength(archive1);
  fileInfo->setForceCheck(force1);

  UpdateFileInfo* fileInfo2 = new UpdateFileInfo();
  fileInfo2->setPath(path2);
  fileInfo2->setHash(longhash2);
  fileInfo2->setRawLength(raw2);
  fileInfo2->setArchiveLength(archive2);
  fileInfo2->setForceCheck(force2);

  container.addFileInfo(fileInfo);
  container.addFileInfo(fileInfo2);

  bool res1 = false;
  bool res2 = false;

  const QList<UpdateFileInfo*> *files = container.getFiles();
  QList<UpdateFileInfo*>::const_iterator end = files->end();
  for (QList<UpdateFileInfo*>::const_iterator it = files->begin(); it != end; ++it) {
    if((*it)->relativePath().compare(path1) == 0
      && (*it)->hash().compare(longhash1) == 0
      && (*it)->rawLength() == raw1
      && (*it)->archiveLength() == archive1
      && (*it)->forceCheck() == force1)
    {
      res1 = true;

    } else {
      if((*it)->relativePath().compare(path2) == 0
        && (*it)->hash().compare(longhash2) == 0
        && (*it)->rawLength() == raw2
        && (*it)->archiveLength() == archive2
        && (*it)->forceCheck() == force2)
      {
        res2 = true;
      }
    }
  }

  ASSERT_TRUE(res1 && res2);
  container.clear();
}
