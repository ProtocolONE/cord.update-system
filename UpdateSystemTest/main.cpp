#ifdef _DEBUG
  #ifdef WIN32
  #include <Windows.h>
  #endif
  //#include <vld.h>
#endif

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <gtest/gtest.h>

#include <QtCore/QMetaType>
#include <UpdateSystem/CheckUpdateHelper.h>

#ifdef _DEBUG
#pragma comment(lib, "UpdateSystemX86d.lib")
#else
#pragma comment(lib, "UpdateSystemX86.lib")
#endif 

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  qRegisterMetaType<GGS::UpdateSystem::CheckUpdateHelper::Results>("GGS::UpdateSystem::CheckUpdateHelper::Results");

  testing::InitGoogleTest(&argc, argv);
  return  RUN_ALL_TESTS();
}
