/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#define TEST_DLL_API __declspec(dllexport)

namespace GGS 
{
namespace SevenZip
{
#ifdef SEVENZIP_LIBRARY
  extern "C" TEST_DLL_API int ExtractW(const wchar_t * PathToArchive, const wchar_t * DestinationPath);
#else
  extern "C" __declspec(dllimport) int ExtractW(const wchar_t * PathToArchive, const wchar_t * DestinationPath);
#endif
}
}