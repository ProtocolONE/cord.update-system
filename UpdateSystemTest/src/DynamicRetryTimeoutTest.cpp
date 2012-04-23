#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include <UpdateSystem/Downloader/DynamicRetryTimeout.h>

class DynamicRetryTimeoutTest : public ::testing::Test
{
public:
  DynamicRetryTimeoutTest()
  {
    this->leakChecker.start();
  }

  ~DynamicRetryTimeoutTest()
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

TEST_F(DynamicRetryTimeoutTest, EmptyTest)
{
  GGS::Downloader::DynamicRetryTimeout timeout;
  ASSERT_EQ( 0, timeout.getTimeout(-1) );
  ASSERT_EQ( 0, timeout.getTimeout(0) );
  ASSERT_EQ( 0, timeout.getTimeout(10) );
}

TEST_F(DynamicRetryTimeoutTest, SingleTest)
{
  GGS::Downloader::DynamicRetryTimeout timeout;
  timeout.addTimeout(1000);
  ASSERT_EQ( 0, timeout.getTimeout(-1) );
  ASSERT_EQ( 0, timeout.getTimeout(0) );
  ASSERT_EQ( 1000, timeout.getTimeout(1) );
  ASSERT_EQ( 1000, timeout.getTimeout(10) );
}

TEST_F(DynamicRetryTimeoutTest, MultiTest)
{
  GGS::Downloader::DynamicRetryTimeout timeout;
  timeout.addTimeout(1000);
  timeout.addTimeout(2000);
  timeout.addTimeout(3000);
  ASSERT_EQ( 0, timeout.getTimeout(-1) );
  ASSERT_EQ( 0, timeout.getTimeout(0) );
  ASSERT_EQ( 1000, timeout.getTimeout(1) );
  ASSERT_EQ( 2000, timeout.getTimeout(2) );
  ASSERT_EQ( 3000, timeout.getTimeout(3) );
  ASSERT_EQ( 3000, timeout.getTimeout(10) );
}