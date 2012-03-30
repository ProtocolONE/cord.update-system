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

#ifdef _DEBUG
#pragma comment(lib, "UpdateSystemX86d.lib")
#else
#pragma comment(lib, "UpdateSystemX86.lib")
#endif 

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    return  RUN_ALL_TESTS();
}