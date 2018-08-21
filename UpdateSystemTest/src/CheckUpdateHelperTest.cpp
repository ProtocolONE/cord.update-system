#include <UpdateSystem/CheckUpdateHelper.h>

#include "TestEventLoopFinisher.h"

#include <gtest/gtest.h>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtTest/QSignalSpy>

using namespace P1::UpdateSystem;
class CheckUpdateHelperTest : public ::testing::Test
{
public:
  CheckUpdateHelper _helper;

  void check() {
    QEventLoop loop;
    TestEventLoopFinisher killer(&loop, 50000);
    QObject::connect(&_helper, SIGNAL(finished(P1::UpdateSystem::CheckUpdateHelper::Results)), 
      &killer, SLOT(terminateLoop()));
    QSignalSpy spy(&_helper, SIGNAL(finished(P1::UpdateSystem::CheckUpdateHelper::Results)));

    QTimer::singleShot(0, &_helper, SLOT(checkUpdate()));
    loop.exec();
    ASSERT_FALSE(killer.isKilledByTimeout());
    ASSERT_EQ(1, spy.count());

    QList<QVariant> arguments = spy.takeFirst();
    this->_result = arguments.at(0).value<P1::UpdateSystem::CheckUpdateHelper::Results>();
  }

  CheckUpdateHelper::Results _result;
};


TEST_F(CheckUpdateHelperTest, FakeUrlTest)
{
  _helper.setUpdateUrl("fakeUrl");
  check();
  ASSERT_EQ(P1::UpdateSystem::CheckUpdateHelper::Error, this->_result);
}

TEST_F(CheckUpdateHelperTest, NormalTest)
{
  _helper.setUpdateUrl("http://fs0.gamenet.ru/update/qgna/live/update.crc.7z");
  check();
  ASSERT_EQ(CheckUpdateHelper::NotFound, this->_result);
  check();
  ASSERT_EQ(CheckUpdateHelper::NotFound, this->_result);
  _helper.setUpdateUrl("http://fs0.gamenet.ru/update/qgna/tst/update.crc.7z");
  check();
  ASSERT_EQ(CheckUpdateHelper::FoundUpdate, this->_result);
}