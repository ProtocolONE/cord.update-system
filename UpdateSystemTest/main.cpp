#ifdef _DEBUG
  #ifdef WIN32
  #include <Windows.h>
  #endif
#endif

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <gtest/gtest.h>

#include <QtCore/QMetaType>
#include <UpdateSystem/CheckUpdateHelper.h>
#include <UpdateSystem/RegisterTypes.h>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  P1::UpdateSystem::registerTypes();

  testing::InitGoogleTest(&argc, argv);
  return  RUN_ALL_TESTS();
}
